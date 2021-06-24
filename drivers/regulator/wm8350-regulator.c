<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// wm8350.c  --  Voltage and current regulation क्रम the Wolfson WM8350 PMIC
//
// Copyright 2007, 2008 Wolfson Microelectronics PLC.
//
// Author: Liam Girdwood
//         linux@wolfsonmicro.com

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/pmic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

/* Maximum value possible क्रम VSEL */
#घोषणा WM8350_DCDC_MAX_VSEL 0x66

/* Microamps */
अटल स्थिर अचिन्हित पूर्णांक isink_cur[] = अणु
	4,
	5,
	6,
	7,
	8,
	10,
	11,
	14,
	16,
	19,
	23,
	27,
	32,
	39,
	46,
	54,
	65,
	77,
	92,
	109,
	130,
	154,
	183,
	218,
	259,
	308,
	367,
	436,
	518,
	616,
	733,
	872,
	1037,
	1233,
	1466,
	1744,
	2073,
	2466,
	2933,
	3487,
	4147,
	4932,
	5865,
	6975,
	8294,
	9864,
	11730,
	13949,
	16589,
	19728,
	23460,
	27899,
	33178,
	39455,
	46920,
	55798,
	66355,
	78910,
	93840,
	111596,
	132710,
	157820,
	187681,
	223191
पूर्ण;

/* turn on ISINK followed by DCDC */
अटल पूर्णांक wm8350_isink_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक isink = rdev_get_id(rdev);

	चयन (isink) अणु
	हाल WM8350_ISINK_A:
		चयन (wm8350->pmic.isink_A_dcdc) अणु
		हाल WM8350_DCDC_2:
		हाल WM8350_DCDC_5:
			wm8350_set_bits(wm8350, WM8350_POWER_MGMT_7,
					WM8350_CS1_ENA);
			wm8350_set_bits(wm8350, WM8350_CSA_FLASH_CONTROL,
					WM8350_CS1_DRIVE);
			wm8350_set_bits(wm8350, WM8350_DCDC_LDO_REQUESTED,
					1 << (wm8350->pmic.isink_A_dcdc -
					      WM8350_DCDC_1));
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल WM8350_ISINK_B:
		चयन (wm8350->pmic.isink_B_dcdc) अणु
		हाल WM8350_DCDC_2:
		हाल WM8350_DCDC_5:
			wm8350_set_bits(wm8350, WM8350_POWER_MGMT_7,
					WM8350_CS2_ENA);
			wm8350_set_bits(wm8350, WM8350_CSB_FLASH_CONTROL,
					WM8350_CS2_DRIVE);
			wm8350_set_bits(wm8350, WM8350_DCDC_LDO_REQUESTED,
					1 << (wm8350->pmic.isink_B_dcdc -
					      WM8350_DCDC_1));
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_isink_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक isink = rdev_get_id(rdev);

	चयन (isink) अणु
	हाल WM8350_ISINK_A:
		चयन (wm8350->pmic.isink_A_dcdc) अणु
		हाल WM8350_DCDC_2:
		हाल WM8350_DCDC_5:
			wm8350_clear_bits(wm8350, WM8350_DCDC_LDO_REQUESTED,
					  1 << (wm8350->pmic.isink_A_dcdc -
						WM8350_DCDC_1));
			wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_7,
					  WM8350_CS1_ENA);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल WM8350_ISINK_B:
		चयन (wm8350->pmic.isink_B_dcdc) अणु
		हाल WM8350_DCDC_2:
		हाल WM8350_DCDC_5:
			wm8350_clear_bits(wm8350, WM8350_DCDC_LDO_REQUESTED,
					  1 << (wm8350->pmic.isink_B_dcdc -
						WM8350_DCDC_1));
			wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_7,
					  WM8350_CS2_ENA);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_isink_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक isink = rdev_get_id(rdev);

	चयन (isink) अणु
	हाल WM8350_ISINK_A:
		वापस wm8350_reg_पढ़ो(wm8350, WM8350_CURRENT_SINK_DRIVER_A) &
		    0x8000;
	हाल WM8350_ISINK_B:
		वापस wm8350_reg_पढ़ो(wm8350, WM8350_CURRENT_SINK_DRIVER_B) &
		    0x8000;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8350_isink_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक isink = rdev_get_id(rdev);
	पूर्णांक reg;

	चयन (isink) अणु
	हाल WM8350_ISINK_A:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_CSA_FLASH_CONTROL);
		अवरोध;
	हाल WM8350_ISINK_B:
		reg = wm8350_reg_पढ़ो(wm8350, WM8350_CSB_FLASH_CONTROL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (reg & WM8350_CS1_FLASH_MODE) अणु
		चयन (reg & WM8350_CS1_ON_RAMP_MASK) अणु
		हाल 0:
			वापस 0;
		हाल 1:
			वापस 1950;
		हाल 2:
			वापस 3910;
		हाल 3:
			वापस 7800;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (reg & WM8350_CS1_ON_RAMP_MASK) अणु
		हाल 0:
			वापस 0;
		हाल 1:
			वापस 250000;
		हाल 2:
			वापस 500000;
		हाल 3:
			वापस 1000000;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण


पूर्णांक wm8350_isink_set_flash(काष्ठा wm8350 *wm8350, पूर्णांक isink, u16 mode,
			   u16 trigger, u16 duration, u16 on_ramp, u16 off_ramp,
			   u16 drive)
अणु
	चयन (isink) अणु
	हाल WM8350_ISINK_A:
		wm8350_reg_ग_लिखो(wm8350, WM8350_CSA_FLASH_CONTROL,
				 (mode ? WM8350_CS1_FLASH_MODE : 0) |
				 (trigger ? WM8350_CS1_TRIGSRC : 0) |
				 duration | on_ramp | off_ramp | drive);
		अवरोध;
	हाल WM8350_ISINK_B:
		wm8350_reg_ग_लिखो(wm8350, WM8350_CSB_FLASH_CONTROL,
				 (mode ? WM8350_CS2_FLASH_MODE : 0) |
				 (trigger ? WM8350_CS2_TRIGSRC : 0) |
				 duration | on_ramp | off_ramp | drive);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_isink_set_flash);

अटल पूर्णांक wm8350_dcdc_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक sel, volt_reg, dcdc = rdev_get_id(rdev);
	u16 val;

	dev_dbg(wm8350->dev, "%s %d mV %d\n", __func__, dcdc, uV / 1000);

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		volt_reg = WM8350_DCDC1_LOW_POWER;
		अवरोध;
	हाल WM8350_DCDC_3:
		volt_reg = WM8350_DCDC3_LOW_POWER;
		अवरोध;
	हाल WM8350_DCDC_4:
		volt_reg = WM8350_DCDC4_LOW_POWER;
		अवरोध;
	हाल WM8350_DCDC_6:
		volt_reg = WM8350_DCDC6_LOW_POWER;
		अवरोध;
	हाल WM8350_DCDC_2:
	हाल WM8350_DCDC_5:
	शेष:
		वापस -EINVAL;
	पूर्ण

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	/* all DCDCs have same mV bits */
	val = wm8350_reg_पढ़ो(wm8350, volt_reg) & ~WM8350_DC1_VSEL_MASK;
	wm8350_reg_ग_लिखो(wm8350, volt_reg, val | sel);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_dcdc_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 val;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC1_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC1_LOW_POWER,
			val | wm8350->pmic.dcdc1_hib_mode);
		अवरोध;
	हाल WM8350_DCDC_3:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC3_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC3_LOW_POWER,
			val | wm8350->pmic.dcdc3_hib_mode);
		अवरोध;
	हाल WM8350_DCDC_4:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC4_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC4_LOW_POWER,
			val | wm8350->pmic.dcdc4_hib_mode);
		अवरोध;
	हाल WM8350_DCDC_6:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC6_LOW_POWER)
			& ~WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC6_LOW_POWER,
			val | wm8350->pmic.dcdc6_hib_mode);
		अवरोध;
	हाल WM8350_DCDC_2:
	हाल WM8350_DCDC_5:
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_dcdc_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 val;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC1_LOW_POWER);
		wm8350->pmic.dcdc1_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC1_LOW_POWER,
				 val | WM8350_DCDC_HIB_MODE_DIS);
		अवरोध;
	हाल WM8350_DCDC_3:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC3_LOW_POWER);
		wm8350->pmic.dcdc3_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC3_LOW_POWER,
				 val | WM8350_DCDC_HIB_MODE_DIS);
		अवरोध;
	हाल WM8350_DCDC_4:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC4_LOW_POWER);
		wm8350->pmic.dcdc4_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC4_LOW_POWER,
				 val | WM8350_DCDC_HIB_MODE_DIS);
		अवरोध;
	हाल WM8350_DCDC_6:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC6_LOW_POWER);
		wm8350->pmic.dcdc6_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC6_LOW_POWER,
				 val | WM8350_DCDC_HIB_MODE_DIS);
		अवरोध;
	हाल WM8350_DCDC_2:
	हाल WM8350_DCDC_5:
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_dcdc25_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 val;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_2:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC2_CONTROL)
		    & ~WM8350_DC2_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC2_CONTROL, val |
		    (WM8350_DC2_HIB_MODE_ACTIVE << WM8350_DC2_HIB_MODE_SHIFT));
		अवरोध;
	हाल WM8350_DCDC_5:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC5_CONTROL)
		    & ~WM8350_DC5_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC5_CONTROL, val |
		    (WM8350_DC5_HIB_MODE_ACTIVE << WM8350_DC5_HIB_MODE_SHIFT));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_dcdc25_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 val;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_2:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC2_CONTROL)
		    & ~WM8350_DC2_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC2_CONTROL, val |
		    (WM8350_DC2_HIB_MODE_DISABLE << WM8350_DC2_HIB_MODE_SHIFT));
		अवरोध;
	हाल WM8350_DCDC_5:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC5_CONTROL)
		    & ~WM8350_DC5_HIB_MODE_MASK;
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC5_CONTROL, val |
		    (WM8350_DC5_HIB_MODE_DISABLE << WM8350_DC5_HIB_MODE_SHIFT));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_dcdc_set_suspend_mode(काष्ठा regulator_dev *rdev,
	अचिन्हित पूर्णांक mode)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 *hib_mode;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		hib_mode = &wm8350->pmic.dcdc1_hib_mode;
		अवरोध;
	हाल WM8350_DCDC_3:
		hib_mode = &wm8350->pmic.dcdc3_hib_mode;
		अवरोध;
	हाल WM8350_DCDC_4:
		hib_mode = &wm8350->pmic.dcdc4_hib_mode;
		अवरोध;
	हाल WM8350_DCDC_6:
		hib_mode = &wm8350->pmic.dcdc6_hib_mode;
		अवरोध;
	हाल WM8350_DCDC_2:
	हाल WM8350_DCDC_5:
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		*hib_mode = WM8350_DCDC_HIB_MODE_IMAGE;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		*hib_mode = WM8350_DCDC_HIB_MODE_STANDBY;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		*hib_mode = WM8350_DCDC_HIB_MODE_LDO_IM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा linear_range wm8350_lकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 15, 50000),
	REGULATOR_LINEAR_RANGE(1800000, 16, 31, 100000),
पूर्ण;

अटल पूर्णांक wm8350_lकरो_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक sel, volt_reg, lकरो = rdev_get_id(rdev);
	u16 val;

	dev_dbg(wm8350->dev, "%s %d mV %d\n", __func__, lकरो, uV / 1000);

	चयन (lकरो) अणु
	हाल WM8350_LDO_1:
		volt_reg = WM8350_LDO1_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_2:
		volt_reg = WM8350_LDO2_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_3:
		volt_reg = WM8350_LDO3_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_4:
		volt_reg = WM8350_LDO4_LOW_POWER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sel = regulator_map_voltage_linear_range(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	/* all LDOs have same mV bits */
	val = wm8350_reg_पढ़ो(wm8350, volt_reg) & ~WM8350_LDO1_VSEL_MASK;
	wm8350_reg_ग_लिखो(wm8350, volt_reg, val | sel);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_lकरो_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक volt_reg, lकरो = rdev_get_id(rdev);
	u16 val;

	चयन (lकरो) अणु
	हाल WM8350_LDO_1:
		volt_reg = WM8350_LDO1_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_2:
		volt_reg = WM8350_LDO2_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_3:
		volt_reg = WM8350_LDO3_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_4:
		volt_reg = WM8350_LDO4_LOW_POWER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* all LDOs have same mV bits */
	val = wm8350_reg_पढ़ो(wm8350, volt_reg) & ~WM8350_LDO1_HIB_MODE_MASK;
	wm8350_reg_ग_लिखो(wm8350, volt_reg, val);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_lकरो_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक volt_reg, lकरो = rdev_get_id(rdev);
	u16 val;

	चयन (lकरो) अणु
	हाल WM8350_LDO_1:
		volt_reg = WM8350_LDO1_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_2:
		volt_reg = WM8350_LDO2_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_3:
		volt_reg = WM8350_LDO3_LOW_POWER;
		अवरोध;
	हाल WM8350_LDO_4:
		volt_reg = WM8350_LDO4_LOW_POWER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* all LDOs have same mV bits */
	val = wm8350_reg_पढ़ो(wm8350, volt_reg) & ~WM8350_LDO1_HIB_MODE_MASK;
	wm8350_reg_ग_लिखो(wm8350, volt_reg, val | WM8350_LDO1_HIB_MODE_DIS);
	वापस 0;
पूर्ण

पूर्णांक wm8350_dcdc_set_slot(काष्ठा wm8350 *wm8350, पूर्णांक dcdc, u16 start,
			 u16 stop, u16 fault)
अणु
	पूर्णांक slot_reg;
	u16 val;

	dev_dbg(wm8350->dev, "%s %d start %d stop %d\n",
		__func__, dcdc, start, stop);

	/* slot valid ? */
	अगर (start > 15 || stop > 15)
		वापस -EINVAL;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		slot_reg = WM8350_DCDC1_TIMEOUTS;
		अवरोध;
	हाल WM8350_DCDC_2:
		slot_reg = WM8350_DCDC2_TIMEOUTS;
		अवरोध;
	हाल WM8350_DCDC_3:
		slot_reg = WM8350_DCDC3_TIMEOUTS;
		अवरोध;
	हाल WM8350_DCDC_4:
		slot_reg = WM8350_DCDC4_TIMEOUTS;
		अवरोध;
	हाल WM8350_DCDC_5:
		slot_reg = WM8350_DCDC5_TIMEOUTS;
		अवरोध;
	हाल WM8350_DCDC_6:
		slot_reg = WM8350_DCDC6_TIMEOUTS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = wm8350_reg_पढ़ो(wm8350, slot_reg) &
	    ~(WM8350_DC1_ENSLOT_MASK | WM8350_DC1_SDSLOT_MASK |
	      WM8350_DC1_ERRACT_MASK);
	wm8350_reg_ग_लिखो(wm8350, slot_reg,
			 val | (start << WM8350_DC1_ENSLOT_SHIFT) |
			 (stop << WM8350_DC1_SDSLOT_SHIFT) |
			 (fault << WM8350_DC1_ERRACT_SHIFT));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_dcdc_set_slot);

पूर्णांक wm8350_lकरो_set_slot(काष्ठा wm8350 *wm8350, पूर्णांक lकरो, u16 start, u16 stop)
अणु
	पूर्णांक slot_reg;
	u16 val;

	dev_dbg(wm8350->dev, "%s %d start %d stop %d\n",
		__func__, lकरो, start, stop);

	/* slot valid ? */
	अगर (start > 15 || stop > 15)
		वापस -EINVAL;

	चयन (lकरो) अणु
	हाल WM8350_LDO_1:
		slot_reg = WM8350_LDO1_TIMEOUTS;
		अवरोध;
	हाल WM8350_LDO_2:
		slot_reg = WM8350_LDO2_TIMEOUTS;
		अवरोध;
	हाल WM8350_LDO_3:
		slot_reg = WM8350_LDO3_TIMEOUTS;
		अवरोध;
	हाल WM8350_LDO_4:
		slot_reg = WM8350_LDO4_TIMEOUTS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = wm8350_reg_पढ़ो(wm8350, slot_reg) & ~WM8350_LDO1_SDSLOT_MASK;
	wm8350_reg_ग_लिखो(wm8350, slot_reg, val | ((start << 10) | (stop << 6)));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_lकरो_set_slot);

पूर्णांक wm8350_dcdc25_set_mode(काष्ठा wm8350 *wm8350, पूर्णांक dcdc, u16 mode,
			   u16 ilim, u16 ramp, u16 feedback)
अणु
	u16 val;

	dev_dbg(wm8350->dev, "%s %d mode: %s %s\n", __func__, dcdc,
		mode ? "normal" : "boost", ilim ? "low" : "normal");

	चयन (dcdc) अणु
	हाल WM8350_DCDC_2:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC2_CONTROL)
		    & ~(WM8350_DC2_MODE_MASK | WM8350_DC2_ILIM_MASK |
			WM8350_DC2_RMP_MASK | WM8350_DC2_FBSRC_MASK);
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC2_CONTROL, val |
				 (mode << WM8350_DC2_MODE_SHIFT) |
				 (ilim << WM8350_DC2_ILIM_SHIFT) |
				 (ramp << WM8350_DC2_RMP_SHIFT) |
				 (feedback << WM8350_DC2_FBSRC_SHIFT));
		अवरोध;
	हाल WM8350_DCDC_5:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC5_CONTROL)
		    & ~(WM8350_DC5_MODE_MASK | WM8350_DC5_ILIM_MASK |
			WM8350_DC5_RMP_MASK | WM8350_DC5_FBSRC_MASK);
		wm8350_reg_ग_लिखो(wm8350, WM8350_DCDC5_CONTROL, val |
				 (mode << WM8350_DC5_MODE_SHIFT) |
				 (ilim << WM8350_DC5_ILIM_SHIFT) |
				 (ramp << WM8350_DC5_RMP_SHIFT) |
				 (feedback << WM8350_DC5_FBSRC_SHIFT));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_dcdc25_set_mode);

अटल पूर्णांक क्रमce_continuous_enable(काष्ठा wm8350 *wm8350, पूर्णांक dcdc, पूर्णांक enable)
अणु
	पूर्णांक reg = 0, ret;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		reg = WM8350_DCDC1_FORCE_PWM;
		अवरोध;
	हाल WM8350_DCDC_3:
		reg = WM8350_DCDC3_FORCE_PWM;
		अवरोध;
	हाल WM8350_DCDC_4:
		reg = WM8350_DCDC4_FORCE_PWM;
		अवरोध;
	हाल WM8350_DCDC_6:
		reg = WM8350_DCDC6_FORCE_PWM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (enable)
		ret = wm8350_set_bits(wm8350, reg,
			WM8350_DCDC1_FORCE_PWM_ENA);
	अन्यथा
		ret = wm8350_clear_bits(wm8350, reg,
			WM8350_DCDC1_FORCE_PWM_ENA);
	वापस ret;
पूर्ण

अटल पूर्णांक wm8350_dcdc_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 val;

	अगर (dcdc < WM8350_DCDC_1 || dcdc > WM8350_DCDC_6)
		वापस -EINVAL;

	अगर (dcdc == WM8350_DCDC_2 || dcdc == WM8350_DCDC_5)
		वापस -EINVAL;

	val = 1 << (dcdc - WM8350_DCDC_1);

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		/* क्रमce continuous mode */
		wm8350_set_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, val);
		wm8350_clear_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		क्रमce_continuous_enable(wm8350, dcdc, 1);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		/* active / pulse skipping */
		wm8350_set_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, val);
		wm8350_clear_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		क्रमce_continuous_enable(wm8350, dcdc, 0);
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		/* standby mode */
		क्रमce_continuous_enable(wm8350, dcdc, 0);
		wm8350_clear_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		wm8350_clear_bits(wm8350, WM8350_DCDC_ACTIVE_OPTIONS, val);
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		/* LDO mode */
		क्रमce_continuous_enable(wm8350, dcdc, 0);
		wm8350_set_bits(wm8350, WM8350_DCDC_SLEEP_OPTIONS, val);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक wm8350_dcdc_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);
	पूर्णांक dcdc = rdev_get_id(rdev);
	u16 mask, sleep, active, क्रमce;
	पूर्णांक mode = REGULATOR_MODE_NORMAL;
	पूर्णांक reg;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
		reg = WM8350_DCDC1_FORCE_PWM;
		अवरोध;
	हाल WM8350_DCDC_3:
		reg = WM8350_DCDC3_FORCE_PWM;
		अवरोध;
	हाल WM8350_DCDC_4:
		reg = WM8350_DCDC4_FORCE_PWM;
		अवरोध;
	हाल WM8350_DCDC_6:
		reg = WM8350_DCDC6_FORCE_PWM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask = 1 << (dcdc - WM8350_DCDC_1);
	active = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC_ACTIVE_OPTIONS) & mask;
	क्रमce = wm8350_reg_पढ़ो(wm8350, reg) & WM8350_DCDC1_FORCE_PWM_ENA;
	sleep = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC_SLEEP_OPTIONS) & mask;

	dev_dbg(wm8350->dev, "mask %x active %x sleep %x force %x",
		mask, active, sleep, क्रमce);

	अगर (active && !sleep) अणु
		अगर (क्रमce)
			mode = REGULATOR_MODE_FAST;
		अन्यथा
			mode = REGULATOR_MODE_NORMAL;
	पूर्ण अन्यथा अगर (!active && !sleep)
		mode = REGULATOR_MODE_IDLE;
	अन्यथा अगर (sleep)
		mode = REGULATOR_MODE_STANDBY;

	वापस mode;
पूर्ण

अटल अचिन्हित पूर्णांक wm8350_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	वापस REGULATOR_MODE_NORMAL;
पूर्ण

काष्ठा wm8350_dcdc_efficiency अणु
	पूर्णांक uA_load_min;
	पूर्णांक uA_load_max;
	अचिन्हित पूर्णांक mode;
पूर्ण;

अटल स्थिर काष्ठा wm8350_dcdc_efficiency dcdc1_6_efficiency[] = अणु
	अणु0, 10000, REGULATOR_MODE_STANDBYपूर्ण,       /* 0 - 10mA - LDO */
	अणु10000, 100000, REGULATOR_MODE_IDLEपूर्ण,     /* 10mA - 100mA - Standby */
	अणु100000, 1000000, REGULATOR_MODE_NORMALपूर्ण, /* > 100mA - Active */
	अणु-1, -1, REGULATOR_MODE_NORMALपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wm8350_dcdc_efficiency dcdc3_4_efficiency[] = अणु
	अणु0, 10000, REGULATOR_MODE_STANDBYपूर्ण,      /* 0 - 10mA - LDO */
	अणु10000, 100000, REGULATOR_MODE_IDLEपूर्ण,    /* 10mA - 100mA - Standby */
	अणु100000, 800000, REGULATOR_MODE_NORMALपूर्ण, /* > 100mA - Active */
	अणु-1, -1, REGULATOR_MODE_NORMALपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक get_mode(पूर्णांक uA, स्थिर काष्ठा wm8350_dcdc_efficiency *eff)
अणु
	पूर्णांक i = 0;

	जबतक (eff[i].uA_load_min != -1) अणु
		अगर (uA >= eff[i].uA_load_min && uA <= eff[i].uA_load_max)
			वापस eff[i].mode;
		i++;
	पूर्ण
	वापस REGULATOR_MODE_NORMAL;
पूर्ण

/* Query the regulator क्रम it's most efficient mode @ uV,uA
 * WM8350 regulator efficiency is pretty similar over
 * dअगरferent input and output uV.
 */
अटल अचिन्हित पूर्णांक wm8350_dcdc_get_optimum_mode(काष्ठा regulator_dev *rdev,
						 पूर्णांक input_uV, पूर्णांक output_uV,
						 पूर्णांक output_uA)
अणु
	पूर्णांक dcdc = rdev_get_id(rdev), mode;

	चयन (dcdc) अणु
	हाल WM8350_DCDC_1:
	हाल WM8350_DCDC_6:
		mode = get_mode(output_uA, dcdc1_6_efficiency);
		अवरोध;
	हाल WM8350_DCDC_3:
	हाल WM8350_DCDC_4:
		mode = get_mode(output_uA, dcdc3_4_efficiency);
		अवरोध;
	शेष:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	पूर्ण
	वापस mode;
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm8350_dcdc_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_mode = wm8350_dcdc_get_mode,
	.set_mode = wm8350_dcdc_set_mode,
	.get_optimum_mode = wm8350_dcdc_get_optimum_mode,
	.set_suspend_voltage = wm8350_dcdc_set_suspend_voltage,
	.set_suspend_enable = wm8350_dcdc_set_suspend_enable,
	.set_suspend_disable = wm8350_dcdc_set_suspend_disable,
	.set_suspend_mode = wm8350_dcdc_set_suspend_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops wm8350_dcdc2_5_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_suspend_enable = wm8350_dcdc25_set_suspend_enable,
	.set_suspend_disable = wm8350_dcdc25_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops wm8350_lकरो_ops = अणु
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_mode = wm8350_lकरो_get_mode,
	.set_suspend_voltage = wm8350_lकरो_set_suspend_voltage,
	.set_suspend_enable = wm8350_lकरो_set_suspend_enable,
	.set_suspend_disable = wm8350_lकरो_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops wm8350_isink_ops = अणु
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.enable = wm8350_isink_enable,
	.disable = wm8350_isink_disable,
	.is_enabled = wm8350_isink_is_enabled,
	.enable_समय = wm8350_isink_enable_समय,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc wm8350_reg[NUM_WM8350_REGULATORS] = अणु
	अणु
		.name = "DCDC1",
		.id = WM8350_DCDC_1,
		.ops = &wm8350_dcdc_ops,
		.irq = WM8350_IRQ_UV_DC1,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_DCDC_MAX_VSEL + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsel_reg = WM8350_DCDC1_CONTROL,
		.vsel_mask = WM8350_DC1_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_DC1_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC2",
		.id = WM8350_DCDC_2,
		.ops = &wm8350_dcdc2_5_ops,
		.irq = WM8350_IRQ_UV_DC2,
		.type = REGULATOR_VOLTAGE,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_DC2_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC3",
		.id = WM8350_DCDC_3,
		.ops = &wm8350_dcdc_ops,
		.irq = WM8350_IRQ_UV_DC3,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_DCDC_MAX_VSEL + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsel_reg = WM8350_DCDC3_CONTROL,
		.vsel_mask = WM8350_DC3_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_DC3_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC4",
		.id = WM8350_DCDC_4,
		.ops = &wm8350_dcdc_ops,
		.irq = WM8350_IRQ_UV_DC4,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_DCDC_MAX_VSEL + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsel_reg = WM8350_DCDC4_CONTROL,
		.vsel_mask = WM8350_DC4_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_DC4_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC5",
		.id = WM8350_DCDC_5,
		.ops = &wm8350_dcdc2_5_ops,
		.irq = WM8350_IRQ_UV_DC5,
		.type = REGULATOR_VOLTAGE,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_DC5_ENA,
		.owner = THIS_MODULE,
	 पूर्ण,
	अणु
		.name = "DCDC6",
		.id = WM8350_DCDC_6,
		.ops = &wm8350_dcdc_ops,
		.irq = WM8350_IRQ_UV_DC6,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_DCDC_MAX_VSEL + 1,
		.min_uV = 850000,
		.uV_step = 25000,
		.vsel_reg = WM8350_DCDC6_CONTROL,
		.vsel_mask = WM8350_DC6_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_DC6_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO1",
		.id = WM8350_LDO_1,
		.ops = &wm8350_lकरो_ops,
		.irq = WM8350_IRQ_UV_LDO1,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_LDO1_VSEL_MASK + 1,
		.linear_ranges = wm8350_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8350_lकरो_ranges),
		.vsel_reg = WM8350_LDO1_CONTROL,
		.vsel_mask = WM8350_LDO1_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_LDO1_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO2",
		.id = WM8350_LDO_2,
		.ops = &wm8350_lकरो_ops,
		.irq = WM8350_IRQ_UV_LDO2,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_LDO2_VSEL_MASK + 1,
		.linear_ranges = wm8350_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8350_lकरो_ranges),
		.vsel_reg = WM8350_LDO2_CONTROL,
		.vsel_mask = WM8350_LDO2_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_LDO2_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO3",
		.id = WM8350_LDO_3,
		.ops = &wm8350_lकरो_ops,
		.irq = WM8350_IRQ_UV_LDO3,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_LDO3_VSEL_MASK + 1,
		.linear_ranges = wm8350_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8350_lकरो_ranges),
		.vsel_reg = WM8350_LDO3_CONTROL,
		.vsel_mask = WM8350_LDO3_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_LDO3_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO4",
		.id = WM8350_LDO_4,
		.ops = &wm8350_lकरो_ops,
		.irq = WM8350_IRQ_UV_LDO4,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8350_LDO4_VSEL_MASK + 1,
		.linear_ranges = wm8350_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8350_lकरो_ranges),
		.vsel_reg = WM8350_LDO4_CONTROL,
		.vsel_mask = WM8350_LDO4_VSEL_MASK,
		.enable_reg = WM8350_DCDC_LDO_REQUESTED,
		.enable_mask = WM8350_LDO4_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "ISINKA",
		.id = WM8350_ISINK_A,
		.ops = &wm8350_isink_ops,
		.irq = WM8350_IRQ_CS1,
		.type = REGULATOR_CURRENT,
		.owner = THIS_MODULE,
		.curr_table = isink_cur,
		.n_current_limits = ARRAY_SIZE(isink_cur),
		.csel_reg = WM8350_CURRENT_SINK_DRIVER_A,
		.csel_mask = WM8350_CS1_ISEL_MASK,
	 पूर्ण,
	अणु
		.name = "ISINKB",
		.id = WM8350_ISINK_B,
		.ops = &wm8350_isink_ops,
		.irq = WM8350_IRQ_CS2,
		.type = REGULATOR_CURRENT,
		.owner = THIS_MODULE,
		.curr_table = isink_cur,
		.n_current_limits = ARRAY_SIZE(isink_cur),
		.csel_reg = WM8350_CURRENT_SINK_DRIVER_B,
		.csel_mask = WM8350_CS2_ISEL_MASK,
	 पूर्ण,
पूर्ण;

अटल irqवापस_t pmic_uv_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = (काष्ठा regulator_dev *)data;

	अगर (irq == WM8350_IRQ_CS1 || irq == WM8350_IRQ_CS2)
		regulator_notअगरier_call_chain(rdev,
					      REGULATOR_EVENT_REGULATION_OUT,
					      शून्य);
	अन्यथा
		regulator_notअगरier_call_chain(rdev,
					      REGULATOR_EVENT_UNDER_VOLTAGE,
					      शून्य);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm8350_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8350 *wm8350 = dev_get_drvdata(&pdev->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;
	u16 val;

	अगर (pdev->id < WM8350_DCDC_1 || pdev->id > WM8350_ISINK_B)
		वापस -ENODEV;

	/* करो any regulatior specअगरic init */
	चयन (pdev->id) अणु
	हाल WM8350_DCDC_1:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC1_LOW_POWER);
		wm8350->pmic.dcdc1_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		अवरोध;
	हाल WM8350_DCDC_3:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC3_LOW_POWER);
		wm8350->pmic.dcdc3_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		अवरोध;
	हाल WM8350_DCDC_4:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC4_LOW_POWER);
		wm8350->pmic.dcdc4_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		अवरोध;
	हाल WM8350_DCDC_6:
		val = wm8350_reg_पढ़ो(wm8350, WM8350_DCDC6_LOW_POWER);
		wm8350->pmic.dcdc6_hib_mode = val & WM8350_DCDC_HIB_MODE_MASK;
		अवरोध;
	पूर्ण

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = dev_get_drvdata(&pdev->dev);
	config.regmap = wm8350->regmap;

	/* रेजिस्टर regulator */
	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &wm8350_reg[pdev->id],
				       &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "failed to register %s\n",
			wm8350_reg[pdev->id].name);
		वापस PTR_ERR(rdev);
	पूर्ण

	/* रेजिस्टर regulator IRQ */
	ret = wm8350_रेजिस्टर_irq(wm8350, wm8350_reg[pdev->id].irq,
				  pmic_uv_handler, 0, "UV", rdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register regulator %s IRQ\n",
			wm8350_reg[pdev->id].name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8350_regulator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_dev *rdev = platक्रमm_get_drvdata(pdev);
	काष्ठा wm8350 *wm8350 = rdev_get_drvdata(rdev);

	wm8350_मुक्त_irq(wm8350, wm8350_reg[pdev->id].irq, rdev);

	वापस 0;
पूर्ण

पूर्णांक wm8350_रेजिस्टर_regulator(काष्ठा wm8350 *wm8350, पूर्णांक reg,
			      काष्ठा regulator_init_data *initdata)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;
	अगर (reg < 0 || reg >= NUM_WM8350_REGULATORS)
		वापस -EINVAL;

	अगर (wm8350->pmic.pdev[reg])
		वापस -EBUSY;

	अगर (reg >= WM8350_DCDC_1 && reg <= WM8350_DCDC_6 &&
	    reg > wm8350->pmic.max_dcdc)
		वापस -ENODEV;
	अगर (reg >= WM8350_ISINK_A && reg <= WM8350_ISINK_B &&
	    reg > wm8350->pmic.max_isink)
		वापस -ENODEV;

	pdev = platक्रमm_device_alloc("wm8350-regulator", reg);
	अगर (!pdev)
		वापस -ENOMEM;

	wm8350->pmic.pdev[reg] = pdev;

	initdata->driver_data = wm8350;

	pdev->dev.platक्रमm_data = initdata;
	pdev->dev.parent = wm8350->dev;
	platक्रमm_set_drvdata(pdev, wm8350);

	ret = platक्रमm_device_add(pdev);

	अगर (ret != 0) अणु
		dev_err(wm8350->dev, "Failed to register regulator %d: %d\n",
			reg, ret);
		platक्रमm_device_put(pdev);
		wm8350->pmic.pdev[reg] = शून्य;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_रेजिस्टर_regulator);

/**
 * wm8350_रेजिस्टर_led - Register a WM8350 LED output
 *
 * @wm8350: The WM8350 device to configure.
 * @lednum: LED device index to create.
 * @dcdc: The DCDC to use क्रम the LED.
 * @isink: The ISINK to use क्रम the LED.
 * @pdata: Configuration क्रम the LED.
 *
 * The WM8350 supports the use of an ISINK together with a DCDC to
 * provide a घातer-efficient LED driver.  This function रेजिस्टरs the
 * regulators and instantiates the platक्रमm device क्रम a LED.  The
 * operating modes क्रम the LED regulators must be configured using
 * wm8350_isink_set_flash(), wm8350_dcdc25_set_mode() and
 * wm8350_dcdc_set_slot() prior to calling this function.
 */
पूर्णांक wm8350_रेजिस्टर_led(काष्ठा wm8350 *wm8350, पूर्णांक lednum, पूर्णांक dcdc, पूर्णांक isink,
			काष्ठा wm8350_led_platक्रमm_data *pdata)
अणु
	काष्ठा wm8350_led *led;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	अगर (lednum >= ARRAY_SIZE(wm8350->pmic.led) || lednum < 0) अणु
		dev_err(wm8350->dev, "Invalid LED index %d\n", lednum);
		वापस -ENODEV;
	पूर्ण

	led = &wm8350->pmic.led[lednum];

	अगर (led->pdev) अणु
		dev_err(wm8350->dev, "LED %d already allocated\n", lednum);
		वापस -EINVAL;
	पूर्ण

	pdev = platक्रमm_device_alloc("wm8350-led", lednum);
	अगर (pdev == शून्य) अणु
		dev_err(wm8350->dev, "Failed to allocate LED %d\n", lednum);
		वापस -ENOMEM;
	पूर्ण

	led->isink_consumer.dev_name = dev_name(&pdev->dev);
	led->isink_consumer.supply = "led_isink";
	led->isink_init.num_consumer_supplies = 1;
	led->isink_init.consumer_supplies = &led->isink_consumer;
	led->isink_init.स्थिरraपूर्णांकs.min_uA = 0;
	led->isink_init.स्थिरraपूर्णांकs.max_uA = pdata->max_uA;
	led->isink_init.स्थिरraपूर्णांकs.valid_ops_mask
		= REGULATOR_CHANGE_CURRENT | REGULATOR_CHANGE_STATUS;
	led->isink_init.स्थिरraपूर्णांकs.valid_modes_mask = REGULATOR_MODE_NORMAL;
	ret = wm8350_रेजिस्टर_regulator(wm8350, isink, &led->isink_init);
	अगर (ret != 0) अणु
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	led->dcdc_consumer.dev_name = dev_name(&pdev->dev);
	led->dcdc_consumer.supply = "led_vcc";
	led->dcdc_init.num_consumer_supplies = 1;
	led->dcdc_init.consumer_supplies = &led->dcdc_consumer;
	led->dcdc_init.स्थिरraपूर्णांकs.valid_modes_mask = REGULATOR_MODE_NORMAL;
	led->dcdc_init.स्थिरraपूर्णांकs.valid_ops_mask =  REGULATOR_CHANGE_STATUS;
	ret = wm8350_रेजिस्टर_regulator(wm8350, dcdc, &led->dcdc_init);
	अगर (ret != 0) अणु
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	चयन (isink) अणु
	हाल WM8350_ISINK_A:
		wm8350->pmic.isink_A_dcdc = dcdc;
		अवरोध;
	हाल WM8350_ISINK_B:
		wm8350->pmic.isink_B_dcdc = dcdc;
		अवरोध;
	पूर्ण

	pdev->dev.platक्रमm_data = pdata;
	pdev->dev.parent = wm8350->dev;
	ret = platक्रमm_device_add(pdev);
	अगर (ret != 0) अणु
		dev_err(wm8350->dev, "Failed to register LED %d: %d\n",
			lednum, ret);
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	led->pdev = pdev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm8350_रेजिस्टर_led);

अटल काष्ठा platक्रमm_driver wm8350_regulator_driver = अणु
	.probe = wm8350_regulator_probe,
	.हटाओ = wm8350_regulator_हटाओ,
	.driver		= अणु
		.name	= "wm8350-regulator",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init wm8350_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&wm8350_regulator_driver);
पूर्ण
subsys_initcall(wm8350_regulator_init);

अटल व्योम __निकास wm8350_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wm8350_regulator_driver);
पूर्ण
module_निकास(wm8350_regulator_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood");
MODULE_DESCRIPTION("WM8350 voltage and current regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8350-regulator");
