<शैली गुरु>
/* linux/mfd/tps6507x.h
 *
 * Functions to access TPS65070 घातer management chip.
 *
 * Copyright (c) 2009 RidgeRun (todd.fischer@ridgerun.com)
 *
 *
 *  For licencing details see kernel-base/COPYING
 */

#अगर_अघोषित __LINUX_MFD_TPS6507X_H
#घोषणा __LINUX_MFD_TPS6507X_H

/*
 * ----------------------------------------------------------------------------
 * Registers, all 8 bits
 * ----------------------------------------------------------------------------
 */


/* Register definitions */
#घोषणा	TPS6507X_REG_PPATH1			0X01
#घोषणा	TPS6507X_CHG_USB			BIT(7)
#घोषणा	TPS6507X_CHG_AC				BIT(6)
#घोषणा	TPS6507X_CHG_USB_PW_ENABLE		BIT(5)
#घोषणा	TPS6507X_CHG_AC_PW_ENABLE		BIT(4)
#घोषणा	TPS6507X_CHG_AC_CURRENT			BIT(2)
#घोषणा	TPS6507X_CHG_USB_CURRENT		BIT(0)

#घोषणा	TPS6507X_REG_INT			0X02
#घोषणा	TPS6507X_REG_MASK_AC_USB		BIT(7)
#घोषणा	TPS6507X_REG_MASK_TSC			BIT(6)
#घोषणा	TPS6507X_REG_MASK_PB_IN			BIT(5)
#घोषणा	TPS6507X_REG_TSC_INT			BIT(3)
#घोषणा	TPS6507X_REG_PB_IN_INT			BIT(2)
#घोषणा	TPS6507X_REG_AC_USB_APPLIED		BIT(1)
#घोषणा	TPS6507X_REG_AC_USB_REMOVED		BIT(0)

#घोषणा	TPS6507X_REG_CHGCONFIG0			0X03

#घोषणा	TPS6507X_REG_CHGCONFIG1			0X04
#घोषणा	TPS6507X_CON_CTRL1_DCDC1_ENABLE		BIT(4)
#घोषणा	TPS6507X_CON_CTRL1_DCDC2_ENABLE		BIT(3)
#घोषणा	TPS6507X_CON_CTRL1_DCDC3_ENABLE		BIT(2)
#घोषणा	TPS6507X_CON_CTRL1_LDO1_ENABLE		BIT(1)
#घोषणा	TPS6507X_CON_CTRL1_LDO2_ENABLE		BIT(0)

#घोषणा	TPS6507X_REG_CHGCONFIG2			0X05

#घोषणा	TPS6507X_REG_CHGCONFIG3			0X06

#घोषणा	TPS6507X_REG_ADCONFIG			0X07
#घोषणा	TPS6507X_ADCONFIG_AD_ENABLE		BIT(7)
#घोषणा	TPS6507X_ADCONFIG_START_CONVERSION	BIT(6)
#घोषणा	TPS6507X_ADCONFIG_CONVERSION_DONE	BIT(5)
#घोषणा	TPS6507X_ADCONFIG_VREF_ENABLE		BIT(4)
#घोषणा	TPS6507X_ADCONFIG_INPUT_AD_IN1		0
#घोषणा	TPS6507X_ADCONFIG_INPUT_AD_IN2		1
#घोषणा	TPS6507X_ADCONFIG_INPUT_AD_IN3		2
#घोषणा	TPS6507X_ADCONFIG_INPUT_AD_IN4		3
#घोषणा	TPS6507X_ADCONFIG_INPUT_TS_PIN		4
#घोषणा	TPS6507X_ADCONFIG_INPUT_BAT_CURRENT	5
#घोषणा	TPS6507X_ADCONFIG_INPUT_AC_VOLTAGE	6
#घोषणा	TPS6507X_ADCONFIG_INPUT_SYS_VOLTAGE	7
#घोषणा	TPS6507X_ADCONFIG_INPUT_CHARGER_VOLTAGE 8
#घोषणा	TPS6507X_ADCONFIG_INPUT_BAT_VOLTAGE	9
#घोषणा	TPS6507X_ADCONFIG_INPUT_THRESHOLD_VOLTAGE 10
#घोषणा	TPS6507X_ADCONFIG_INPUT_ISET1_VOLTAGE	11
#घोषणा	TPS6507X_ADCONFIG_INPUT_ISET2_VOLTAGE	12
#घोषणा	TPS6507X_ADCONFIG_INPUT_REAL_TSC	14
#घोषणा	TPS6507X_ADCONFIG_INPUT_TSC		15

#घोषणा	TPS6507X_REG_TSCMODE			0X08
#घोषणा	TPS6507X_TSCMODE_X_POSITION		0
#घोषणा	TPS6507X_TSCMODE_Y_POSITION		1
#घोषणा	TPS6507X_TSCMODE_PRESSURE		2
#घोषणा	TPS6507X_TSCMODE_X_PLATE		3
#घोषणा	TPS6507X_TSCMODE_Y_PLATE		4
#घोषणा	TPS6507X_TSCMODE_STANDBY		5
#घोषणा	TPS6507X_TSCMODE_ADC_INPUT		6
#घोषणा	TPS6507X_TSCMODE_DISABLE		7

#घोषणा	TPS6507X_REG_ADRESULT_1			0X09

#घोषणा	TPS6507X_REG_ADRESULT_2			0X0A
#घोषणा	TPS6507X_REG_ADRESULT_2_MASK		(BIT(1) | BIT(0))

#घोषणा	TPS6507X_REG_PGOOD			0X0B

#घोषणा	TPS6507X_REG_PGOODMASK			0X0C

#घोषणा	TPS6507X_REG_CON_CTRL1			0X0D
#घोषणा	TPS6507X_CON_CTRL1_DCDC1_ENABLE		BIT(4)
#घोषणा	TPS6507X_CON_CTRL1_DCDC2_ENABLE		BIT(3)
#घोषणा	TPS6507X_CON_CTRL1_DCDC3_ENABLE		BIT(2)
#घोषणा	TPS6507X_CON_CTRL1_LDO1_ENABLE		BIT(1)
#घोषणा	TPS6507X_CON_CTRL1_LDO2_ENABLE		BIT(0)

#घोषणा	TPS6507X_REG_CON_CTRL2			0X0E

#घोषणा	TPS6507X_REG_CON_CTRL3			0X0F

#घोषणा	TPS6507X_REG_DEFDCDC1			0X10
#घोषणा TPS6507X_DEFDCDC1_DCDC1_EXT_ADJ_EN	BIT(7)
#घोषणा TPS6507X_DEFDCDC1_DCDC1_MASK		0X3F

#घोषणा	TPS6507X_REG_DEFDCDC2_LOW		0X11
#घोषणा TPS6507X_DEFDCDC2_LOW_DCDC2_MASK	0X3F

#घोषणा	TPS6507X_REG_DEFDCDC2_HIGH		0X12
#घोषणा TPS6507X_DEFDCDC2_HIGH_DCDC2_MASK	0X3F

#घोषणा	TPS6507X_REG_DEFDCDC3_LOW		0X13
#घोषणा TPS6507X_DEFDCDC3_LOW_DCDC3_MASK	0X3F

#घोषणा	TPS6507X_REG_DEFDCDC3_HIGH		0X14
#घोषणा TPS6507X_DEFDCDC3_HIGH_DCDC3_MASK	0X3F

#घोषणा	TPS6507X_REG_DEFSLEW			0X15

#घोषणा	TPS6507X_REG_LDO_CTRL1			0X16
#घोषणा TPS6507X_REG_LDO_CTRL1_LDO1_MASK	0X0F

#घोषणा	TPS6507X_REG_DEFLDO2			0X17
#घोषणा TPS6507X_REG_DEFLDO2_LDO2_MASK		0X3F

#घोषणा	TPS6507X_REG_WLED_CTRL1			0X18

#घोषणा	TPS6507X_REG_WLED_CTRL2			0X19

/* VDCDC MASK */
#घोषणा TPS6507X_DEFDCDCX_DCDC_MASK		0X3F

#घोषणा TPS6507X_MAX_REGISTER			0X19

/**
 * काष्ठा tps6507x_board - packages regulator and touchscreen init data
 * @tps6507x_regulator_data: regulator initialization values
 *
 * Board data may be used to initialize regulator and touchscreen.
 */

काष्ठा tps6507x_board अणु
	काष्ठा regulator_init_data *tps6507x_pmic_init_data;
	काष्ठा touchscreen_init_data *tps6507x_ts_init_data;
पूर्ण;

/**
 * काष्ठा tps6507x_dev - tps6507x sub-driver chip access routines
 * @पढ़ो_dev() - I2C रेजिस्टर पढ़ो function
 * @ग_लिखो_dev() - I2C रेजिस्टर ग_लिखो function
 *
 * Device data may be used to access the TPS6507x chip
 */

काष्ठा tps6507x_dev अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;
	पूर्णांक (*पढ़ो_dev)(काष्ठा tps6507x_dev *tps6507x, अक्षर reg, पूर्णांक size,
			व्योम *dest);
	पूर्णांक (*ग_लिखो_dev)(काष्ठा tps6507x_dev *tps6507x, अक्षर reg, पूर्णांक size,
			 व्योम *src);

	/* Client devices */
	काष्ठा tps6507x_pmic *pmic;
पूर्ण;

#पूर्ण_अगर /*  __LINUX_MFD_TPS6507X_H */
