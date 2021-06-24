<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell 88PM80x Interface
 *
 * Copyright (C) 2012 Marvell International Ltd.
 * Qiao Zhou <zhouqiao@marvell.com>
 */

#अगर_अघोषित __LINUX_MFD_88PM80X_H
#घोषणा __LINUX_MFD_88PM80X_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/atomic.h>

क्रमागत अणु
	CHIP_INVALID = 0,
	CHIP_PM800,
	CHIP_PM805,
	CHIP_PM860,
	CHIP_MAX,
पूर्ण;

क्रमागत अणु
	PM800_ID_BUCK1 = 0,
	PM800_ID_BUCK2,
	PM800_ID_BUCK3,
	PM800_ID_BUCK4,
	PM800_ID_BUCK5,

	PM800_ID_LDO1,
	PM800_ID_LDO2,
	PM800_ID_LDO3,
	PM800_ID_LDO4,
	PM800_ID_LDO5,
	PM800_ID_LDO6,
	PM800_ID_LDO7,
	PM800_ID_LDO8,
	PM800_ID_LDO9,
	PM800_ID_LDO10,
	PM800_ID_LDO11,
	PM800_ID_LDO12,
	PM800_ID_LDO13,
	PM800_ID_LDO14,
	PM800_ID_LDO15,
	PM800_ID_LDO16,
	PM800_ID_LDO17,
	PM800_ID_LDO18,
	PM800_ID_LDO19,

	PM800_ID_RG_MAX,
पूर्ण;
#घोषणा PM800_MAX_REGULATOR	PM800_ID_RG_MAX	/* 5 Bucks, 19 LDOs */
#घोषणा PM800_NUM_BUCK (5)	/*5 Bucks */
#घोषणा PM800_NUM_LDO (19)	/*19 Bucks */

/* page 0 basic: slave adder 0x60 */

#घोषणा PM800_STATUS_1			(0x01)
#घोषणा PM800_ONKEY_STS1		BIT(0)
#घोषणा PM800_EXTON_STS1		BIT(1)
#घोषणा PM800_CHG_STS1			BIT(2)
#घोषणा PM800_BAT_STS1			BIT(3)
#घोषणा PM800_VBUS_STS1			BIT(4)
#घोषणा PM800_LDO_PGOOD_STS1		BIT(5)
#घोषणा PM800_BUCK_PGOOD_STS1		BIT(6)

#घोषणा PM800_STATUS_2			(0x02)
#घोषणा PM800_RTC_ALARM_STS2		BIT(0)

/* Wakeup Registers */
#घोषणा PM800_WAKEUP1			(0x0D)

#घोषणा PM800_WAKEUP2			(0x0E)
#घोषणा PM800_WAKEUP2_INV_INT		BIT(0)
#घोषणा PM800_WAKEUP2_INT_CLEAR		BIT(1)
#घोषणा PM800_WAKEUP2_INT_MASK		BIT(2)

#घोषणा PM800_POWER_UP_LOG		(0x10)

/* Referance and low घातer रेजिस्टरs */
#घोषणा PM800_LOW_POWER1		(0x20)
#घोषणा PM800_LOW_POWER2		(0x21)
#घोषणा PM800_LOW_POWER_CONFIG3		(0x22)
#घोषणा PM800_LOW_POWER_CONFIG4		(0x23)

/* GPIO रेजिस्टर */
#घोषणा PM800_GPIO_0_1_CNTRL		(0x30)
#घोषणा PM800_GPIO0_VAL			BIT(0)
#घोषणा PM800_GPIO0_GPIO_MODE(x)	(x << 1)
#घोषणा PM800_GPIO1_VAL			BIT(4)
#घोषणा PM800_GPIO1_GPIO_MODE(x)	(x << 5)

#घोषणा PM800_GPIO_2_3_CNTRL		(0x31)
#घोषणा PM800_GPIO2_VAL			BIT(0)
#घोषणा PM800_GPIO2_GPIO_MODE(x)	(x << 1)
#घोषणा PM800_GPIO3_VAL			BIT(4)
#घोषणा PM800_GPIO3_GPIO_MODE(x)	(x << 5)
#घोषणा PM800_GPIO3_MODE_MASK		0x1F
#घोषणा PM800_GPIO3_HEADSET_MODE	PM800_GPIO3_GPIO_MODE(6)

#घोषणा PM800_GPIO_4_CNTRL		(0x32)
#घोषणा PM800_GPIO4_VAL			BIT(0)
#घोषणा PM800_GPIO4_GPIO_MODE(x)	(x << 1)

#घोषणा PM800_HEADSET_CNTRL		(0x38)
#घोषणा PM800_HEADSET_DET_EN		BIT(7)
#घोषणा PM800_HSDET_SLP			BIT(1)
/* PWM रेजिस्टर */
#घोषणा PM800_PWM1			(0x40)
#घोषणा PM800_PWM2			(0x41)
#घोषणा PM800_PWM3			(0x42)
#घोषणा PM800_PWM4			(0x43)

/* RTC Registers */
#घोषणा PM800_RTC_CONTROL		(0xD0)
#घोषणा PM800_RTC_MISC1			(0xE1)
#घोषणा PM800_RTC_MISC2			(0xE2)
#घोषणा PM800_RTC_MISC3			(0xE3)
#घोषणा PM800_RTC_MISC4			(0xE4)
#घोषणा PM800_RTC_MISC5			(0xE7)
/* bit definitions of RTC Register 1 (0xD0) */
#घोषणा PM800_ALARM1_EN			BIT(0)
#घोषणा PM800_ALARM_WAKEUP		BIT(4)
#घोषणा PM800_ALARM			BIT(5)
#घोषणा PM800_RTC1_USE_XO		BIT(7)

/* Regulator Control Registers: BUCK1,BUCK5,LDO1 have DVC */

/* buck रेजिस्टरs */
#घोषणा PM800_SLEEP_BUCK1		(0x30)

/* BUCK Sleep Mode Register 1: BUCK[1..4] */
#घोषणा PM800_BUCK_SLP1			(0x5A)
#घोषणा PM800_BUCK1_SLP1_SHIFT		0
#घोषणा PM800_BUCK1_SLP1_MASK		(0x3 << PM800_BUCK1_SLP1_SHIFT)

/* page 2 GPADC: slave adder 0x02 */
#घोषणा PM800_GPADC_MEAS_EN1		(0x01)
#घोषणा PM800_MEAS_EN1_VBAT		BIT(2)
#घोषणा PM800_GPADC_MEAS_EN2		(0x02)
#घोषणा PM800_MEAS_EN2_RFTMP		BIT(0)
#घोषणा PM800_MEAS_GP0_EN		BIT(2)
#घोषणा PM800_MEAS_GP1_EN		BIT(3)
#घोषणा PM800_MEAS_GP2_EN		BIT(4)
#घोषणा PM800_MEAS_GP3_EN		BIT(5)
#घोषणा PM800_MEAS_GP4_EN		BIT(6)

#घोषणा PM800_GPADC_MISC_CONFIG1	(0x05)
#घोषणा PM800_GPADC_MISC_CONFIG2	(0x06)
#घोषणा PM800_GPADC_MISC_GPFSM_EN	BIT(0)
#घोषणा PM800_GPADC_SLOW_MODE(x)	(x << 3)

#घोषणा PM800_GPADC_MISC_CONFIG3	(0x09)
#घोषणा PM800_GPADC_MISC_CONFIG4	(0x0A)

#घोषणा PM800_GPADC_PREBIAS1		(0x0F)
#घोषणा PM800_GPADC0_GP_PREBIAS_TIME(x)	(x << 0)
#घोषणा PM800_GPADC_PREBIAS2		(0x10)

#घोषणा PM800_GP_BIAS_ENA1		(0x14)
#घोषणा PM800_GPADC_GP_BIAS_EN0		BIT(0)
#घोषणा PM800_GPADC_GP_BIAS_EN1		BIT(1)
#घोषणा PM800_GPADC_GP_BIAS_EN2		BIT(2)
#घोषणा PM800_GPADC_GP_BIAS_EN3		BIT(3)

#घोषणा PM800_GP_BIAS_OUT1		(0x15)
#घोषणा PM800_BIAS_OUT_GP0		BIT(0)
#घोषणा PM800_BIAS_OUT_GP1		BIT(1)
#घोषणा PM800_BIAS_OUT_GP2		BIT(2)
#घोषणा PM800_BIAS_OUT_GP3		BIT(3)

#घोषणा PM800_GPADC0_LOW_TH		0x20
#घोषणा PM800_GPADC1_LOW_TH		0x21
#घोषणा PM800_GPADC2_LOW_TH		0x22
#घोषणा PM800_GPADC3_LOW_TH		0x23
#घोषणा PM800_GPADC4_LOW_TH		0x24

#घोषणा PM800_GPADC0_UPP_TH		0x30
#घोषणा PM800_GPADC1_UPP_TH		0x31
#घोषणा PM800_GPADC2_UPP_TH		0x32
#घोषणा PM800_GPADC3_UPP_TH		0x33
#घोषणा PM800_GPADC4_UPP_TH		0x34

#घोषणा PM800_VBBAT_MEAS1		0x40
#घोषणा PM800_VBBAT_MEAS2		0x41
#घोषणा PM800_VBAT_MEAS1		0x42
#घोषणा PM800_VBAT_MEAS2		0x43
#घोषणा PM800_VSYS_MEAS1		0x44
#घोषणा PM800_VSYS_MEAS2		0x45
#घोषणा PM800_VCHG_MEAS1		0x46
#घोषणा PM800_VCHG_MEAS2		0x47
#घोषणा PM800_TINT_MEAS1		0x50
#घोषणा PM800_TINT_MEAS2		0x51
#घोषणा PM800_PMOD_MEAS1		0x52
#घोषणा PM800_PMOD_MEAS2		0x53

#घोषणा PM800_GPADC0_MEAS1		0x54
#घोषणा PM800_GPADC0_MEAS2		0x55
#घोषणा PM800_GPADC1_MEAS1		0x56
#घोषणा PM800_GPADC1_MEAS2		0x57
#घोषणा PM800_GPADC2_MEAS1		0x58
#घोषणा PM800_GPADC2_MEAS2		0x59
#घोषणा PM800_GPADC3_MEAS1		0x5A
#घोषणा PM800_GPADC3_MEAS2		0x5B
#घोषणा PM800_GPADC4_MEAS1		0x5C
#घोषणा PM800_GPADC4_MEAS2		0x5D

#घोषणा PM800_GPADC4_AVG1		0xA8
#घोषणा PM800_GPADC4_AVG2		0xA9

/* 88PM805 Registers */
#घोषणा PM805_MAIN_POWERUP		(0x01)
#घोषणा PM805_INT_STATUS0		(0x02)	/* क्रम ena/dis all पूर्णांकerrupts */

#घोषणा PM805_STATUS0_INT_CLEAR		(1 << 0)
#घोषणा PM805_STATUS0_INV_INT		(1 << 1)
#घोषणा PM800_STATUS0_INT_MASK		(1 << 2)

#घोषणा PM805_INT_STATUS1		(0x03)

#घोषणा PM805_INT1_HP1_SHRT		BIT(0)
#घोषणा PM805_INT1_HP2_SHRT		BIT(1)
#घोषणा PM805_INT1_MIC_CONFLICT		BIT(2)
#घोषणा PM805_INT1_CLIP_FAULT		BIT(3)
#घोषणा PM805_INT1_LDO_OFF		BIT(4)
#घोषणा PM805_INT1_SRC_DPLL_LOCK	BIT(5)

#घोषणा PM805_INT_STATUS2		(0x04)

#घोषणा PM805_INT2_MIC_DET		BIT(0)
#घोषणा PM805_INT2_SHRT_BTN_DET		BIT(1)
#घोषणा PM805_INT2_VOLM_BTN_DET		BIT(2)
#घोषणा PM805_INT2_VOLP_BTN_DET		BIT(3)
#घोषणा PM805_INT2_RAW_PLL_FAULT	BIT(4)
#घोषणा PM805_INT2_FINE_PLL_FAULT	BIT(5)

#घोषणा PM805_INT_MASK1			(0x05)
#घोषणा PM805_INT_MASK2			(0x06)
#घोषणा PM805_SHRT_BTN_DET		BIT(1)

/* number of status and पूर्णांक reg in a row */
#घोषणा PM805_INT_REG_NUM		(2)

#घोषणा PM805_MIC_DET1			(0x07)
#घोषणा PM805_MIC_DET_EN_MIC_DET	BIT(0)
#घोषणा PM805_MIC_DET2			(0x08)
#घोषणा PM805_MIC_DET_STATUS1		(0x09)

#घोषणा PM805_MIC_DET_STATUS3		(0x0A)
#घोषणा PM805_AUTO_SEQ_STATUS1		(0x0B)
#घोषणा PM805_AUTO_SEQ_STATUS2		(0x0C)

#घोषणा PM805_ADC_SETTING1		(0x10)
#घोषणा PM805_ADC_SETTING2		(0x11)
#घोषणा PM805_ADC_SETTING3		(0x11)
#घोषणा PM805_ADC_GAIN1			(0x12)
#घोषणा PM805_ADC_GAIN2			(0x13)
#घोषणा PM805_DMIC_SETTING		(0x15)
#घोषणा PM805_DWS_SETTING		(0x16)
#घोषणा PM805_MIC_CONFLICT_STS		(0x17)

#घोषणा PM805_PDM_SETTING1		(0x20)
#घोषणा PM805_PDM_SETTING2		(0x21)
#घोषणा PM805_PDM_SETTING3		(0x22)
#घोषणा PM805_PDM_CONTROL1		(0x23)
#घोषणा PM805_PDM_CONTROL2		(0x24)
#घोषणा PM805_PDM_CONTROL3		(0x25)

#घोषणा PM805_HEADPHONE_SETTING		(0x26)
#घोषणा PM805_HEADPHONE_GAIN_A2A	(0x27)
#घोषणा PM805_HEADPHONE_SHORT_STATE	(0x28)
#घोषणा PM805_EARPHONE_SETTING		(0x29)
#घोषणा PM805_AUTO_SEQ_SETTING		(0x2A)

काष्ठा pm80x_rtc_pdata अणु
	पूर्णांक		vrtc;
	पूर्णांक		rtc_wakeup;
पूर्ण;

काष्ठा pm80x_subchip अणु
	काष्ठा i2c_client *घातer_page;	/* chip client क्रम घातer page */
	काष्ठा i2c_client *gpadc_page;	/* chip client क्रम gpadc page */
	काष्ठा regmap *regmap_घातer;
	काष्ठा regmap *regmap_gpadc;
	अचिन्हित लघु घातer_page_addr;	/* घातer page I2C address */
	अचिन्हित लघु gpadc_page_addr;	/* gpadc page I2C address */
पूर्ण;

काष्ठा pm80x_chip अणु
	काष्ठा pm80x_subchip *subchip;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा i2c_client *companion;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip *regmap_irq_chip;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक type;
	पूर्णांक irq;
	पूर्णांक irq_mode;
	अचिन्हित दीर्घ wu_flag;
	spinlock_t lock;
पूर्ण;

काष्ठा pm80x_platक्रमm_data अणु
	काष्ठा pm80x_rtc_pdata *rtc;
	/*
	 * For the regulator not defined, set regulators[not_defined] to be
	 * शून्य. num_regulators are the number of regulators supposed to be
	 * initialized. If all regulators are not defined, set num_regulators
	 * to be 0.
	 */
	काष्ठा regulator_init_data *regulators[PM800_ID_RG_MAX];
	अचिन्हित पूर्णांक num_regulators;
	पूर्णांक irq_mode;		/* Clear पूर्णांकerrupt by पढ़ो/ग_लिखो(0/1) */
	पूर्णांक batt_det;		/* enable/disable */
	पूर्णांक (*plat_config)(काष्ठा pm80x_chip *chip,
				काष्ठा pm80x_platक्रमm_data *pdata);
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops pm80x_pm_ops;
बाह्य स्थिर काष्ठा regmap_config pm80x_regmap_config;

अटल अंतरभूत पूर्णांक pm80x_request_irq(काष्ठा pm80x_chip *pm80x, पूर्णांक irq,
				     irq_handler_t handler, अचिन्हित दीर्घ flags,
				     स्थिर अक्षर *name, व्योम *data)
अणु
	अगर (!pm80x->irq_data)
		वापस -EINVAL;
	वापस request_thपढ़ोed_irq(regmap_irq_get_virq(pm80x->irq_data, irq),
				    शून्य, handler, flags, name, data);
पूर्ण

अटल अंतरभूत व्योम pm80x_मुक्त_irq(काष्ठा pm80x_chip *pm80x, पूर्णांक irq, व्योम *data)
अणु
	अगर (!pm80x->irq_data)
		वापस;
	मुक्त_irq(regmap_irq_get_virq(pm80x->irq_data, irq), data);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल अंतरभूत पूर्णांक pm80x_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(dev))
		set_bit(irq, &chip->wu_flag);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pm80x_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	अगर (device_may_wakeup(dev))
		clear_bit(irq, &chip->wu_flag);

	वापस 0;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक pm80x_init(काष्ठा i2c_client *client);
बाह्य पूर्णांक pm80x_deinit(व्योम);
#पूर्ण_अगर /* __LINUX_MFD_88PM80X_H */
