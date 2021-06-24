<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd
 *              http://www.samsung.com
 */

#अगर_अघोषित __LINUX_MFD_SEC_CORE_H
#घोषणा __LINUX_MFD_SEC_CORE_H

/* Macros to represent minimum voltages क्रम LDO/BUCK */
#घोषणा MIN_3000_MV		3000000
#घोषणा MIN_2500_MV		2500000
#घोषणा MIN_2000_MV		2000000
#घोषणा MIN_1800_MV		1800000
#घोषणा MIN_1500_MV		1500000
#घोषणा MIN_1400_MV		1400000
#घोषणा MIN_1000_MV		1000000

#घोषणा MIN_900_MV		900000
#घोषणा MIN_850_MV		850000
#घोषणा MIN_800_MV		800000
#घोषणा MIN_750_MV		750000
#घोषणा MIN_650_MV		650000
#घोषणा MIN_600_MV		600000
#घोषणा MIN_500_MV		500000

/* Ramp delay in uV/us */
#घोषणा RAMP_DELAY_12_MVUS	12000

/* Macros to represent steps क्रम LDO/BUCK */
#घोषणा STEP_50_MV		50000
#घोषणा STEP_25_MV		25000
#घोषणा STEP_12_5_MV		12500
#घोषणा STEP_6_25_MV		6250

काष्ठा gpio_desc;

क्रमागत sec_device_type अणु
	S5M8751X,
	S5M8763X,
	S5M8767X,
	S2MPA01,
	S2MPS11X,
	S2MPS13X,
	S2MPS14X,
	S2MPS15X,
	S2MPU02,
पूर्ण;

/**
 * काष्ठा sec_pmic_dev - s2m/s5m master device क्रम sub-drivers
 * @dev:		Master device of the chip
 * @pdata:		Platक्रमm data populated with data from DTS
 *			or board files
 * @regmap_pmic:	Regmap associated with PMIC's I2C address
 * @i2c:		I2C client of the मुख्य driver
 * @device_type:	Type of device, matches क्रमागत sec_device_type
 * @irq_base:		Base IRQ number क्रम device, required क्रम IRQs
 * @irq:		Generic IRQ number क्रम device
 * @irq_data:		Runसमय data काष्ठाure क्रम IRQ controller
 * @wakeup:		Whether or not this is a wakeup device
 */
काष्ठा sec_pmic_dev अणु
	काष्ठा device *dev;
	काष्ठा sec_platक्रमm_data *pdata;
	काष्ठा regmap *regmap_pmic;
	काष्ठा i2c_client *i2c;

	अचिन्हित दीर्घ device_type;
	पूर्णांक irq_base;
	पूर्णांक irq;
	काष्ठा regmap_irq_chip_data *irq_data;

	bool wakeup;
पूर्ण;

पूर्णांक sec_irq_init(काष्ठा sec_pmic_dev *sec_pmic);
व्योम sec_irq_निकास(काष्ठा sec_pmic_dev *sec_pmic);
पूर्णांक sec_irq_resume(काष्ठा sec_pmic_dev *sec_pmic);

काष्ठा sec_platक्रमm_data अणु
	काष्ठा sec_regulator_data	*regulators;
	काष्ठा sec_opmode_data		*opmode;
	पूर्णांक				device_type;
	पूर्णांक				num_regulators;

	पूर्णांक				irq_base;
	पूर्णांक				(*cfg_pmic_irq)(व्योम);

	bool				wakeup;
	bool				buck_voltage_lock;

	पूर्णांक				buck_gpios[3];
	पूर्णांक				buck_ds[3];
	अचिन्हित पूर्णांक			buck2_voltage[8];
	bool				buck2_gpiodvs;
	अचिन्हित पूर्णांक			buck3_voltage[8];
	bool				buck3_gpiodvs;
	अचिन्हित पूर्णांक			buck4_voltage[8];
	bool				buck4_gpiodvs;

	पूर्णांक				buck_set1;
	पूर्णांक				buck_set2;
	पूर्णांक				buck_set3;
	पूर्णांक				buck2_enable;
	पूर्णांक				buck3_enable;
	पूर्णांक				buck4_enable;
	पूर्णांक				buck_शेष_idx;
	पूर्णांक				buck2_शेष_idx;
	पूर्णांक				buck3_शेष_idx;
	पूर्णांक				buck4_शेष_idx;

	पूर्णांक				buck_ramp_delay;

	पूर्णांक				buck2_ramp_delay;
	पूर्णांक				buck34_ramp_delay;
	पूर्णांक				buck5_ramp_delay;
	पूर्णांक				buck16_ramp_delay;
	पूर्णांक				buck7810_ramp_delay;
	पूर्णांक				buck9_ramp_delay;
	पूर्णांक				buck24_ramp_delay;
	पूर्णांक				buck3_ramp_delay;
	पूर्णांक				buck7_ramp_delay;
	पूर्णांक				buck8910_ramp_delay;

	bool				buck1_ramp_enable;
	bool				buck2_ramp_enable;
	bool				buck3_ramp_enable;
	bool				buck4_ramp_enable;
	bool				buck6_ramp_enable;

	पूर्णांक				buck2_init;
	पूर्णांक				buck3_init;
	पूर्णांक				buck4_init;
	/* Whether or not manually set PWRHOLD to low during shutकरोwn. */
	bool				manual_घातeroff;
	/* Disable the WRSTBI (buck voltage warm reset) when probing? */
	bool				disable_wrstbi;
पूर्ण;

/**
 * sec_regulator_data - regulator data
 * @id: regulator id
 * @initdata: regulator init data (contraपूर्णांकs, supplies, ...)
 */
काष्ठा sec_regulator_data अणु
	पूर्णांक				id;
	काष्ठा regulator_init_data	*initdata;
	काष्ठा device_node		*reg_node;
	काष्ठा gpio_desc		*ext_control_gpiod;
पूर्ण;

/*
 * sec_opmode_data - regulator operation mode data
 * @id: regulator id
 * @mode: regulator operation mode
 */
काष्ठा sec_opmode_data अणु
	पूर्णांक id;
	अचिन्हित पूर्णांक mode;
पूर्ण;

/*
 * samsung regulator operation mode
 * SEC_OPMODE_OFF	Regulator always OFF
 * SEC_OPMODE_ON	Regulator always ON
 * SEC_OPMODE_LOWPOWER  Regulator is on in low-घातer mode
 * SEC_OPMODE_SUSPEND   Regulator is changed by PWREN pin
 *			If PWREN is high, regulator is on
 *			If PWREN is low, regulator is off
 */

क्रमागत sec_opmode अणु
	SEC_OPMODE_OFF,
	SEC_OPMODE_ON,
	SEC_OPMODE_LOWPOWER,
	SEC_OPMODE_SUSPEND,
पूर्ण;

#पूर्ण_अगर /*  __LINUX_MFD_SEC_CORE_H */
