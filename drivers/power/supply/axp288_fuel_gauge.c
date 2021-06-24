<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * axp288_fuel_gauge.c - Xघातer AXP288 PMIC Fuel Gauge Driver
 *
 * Copyright (C) 2016-2017 Hans de Goede <hdegoede@redhat.com>
 * Copyright (C) 2014 Intel Corporation
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा PS_STAT_VBUS_TRIGGER		(1 << 0)
#घोषणा PS_STAT_BAT_CHRG_सूची		(1 << 2)
#घोषणा PS_STAT_VBAT_ABOVE_VHOLD	(1 << 3)
#घोषणा PS_STAT_VBUS_VALID		(1 << 4)
#घोषणा PS_STAT_VBUS_PRESENT		(1 << 5)

#घोषणा CHRG_STAT_BAT_SAFE_MODE		(1 << 3)
#घोषणा CHRG_STAT_BAT_VALID			(1 << 4)
#घोषणा CHRG_STAT_BAT_PRESENT		(1 << 5)
#घोषणा CHRG_STAT_CHARGING			(1 << 6)
#घोषणा CHRG_STAT_PMIC_OTP			(1 << 7)

#घोषणा CHRG_CCCV_CC_MASK			0xf     /* 4 bits */
#घोषणा CHRG_CCCV_CC_BIT_POS		0
#घोषणा CHRG_CCCV_CC_OFFSET			200     /* 200mA */
#घोषणा CHRG_CCCV_CC_LSB_RES		200     /* 200mA */
#घोषणा CHRG_CCCV_ITERM_20P			(1 << 4)    /* 20% of CC */
#घोषणा CHRG_CCCV_CV_MASK			0x60        /* 2 bits */
#घोषणा CHRG_CCCV_CV_BIT_POS		5
#घोषणा CHRG_CCCV_CV_4100MV			0x0     /* 4.10V */
#घोषणा CHRG_CCCV_CV_4150MV			0x1     /* 4.15V */
#घोषणा CHRG_CCCV_CV_4200MV			0x2     /* 4.20V */
#घोषणा CHRG_CCCV_CV_4350MV			0x3     /* 4.35V */
#घोषणा CHRG_CCCV_CHG_EN			(1 << 7)

#घोषणा FG_CNTL_OCV_ADJ_STAT		(1 << 2)
#घोषणा FG_CNTL_OCV_ADJ_EN			(1 << 3)
#घोषणा FG_CNTL_CAP_ADJ_STAT		(1 << 4)
#घोषणा FG_CNTL_CAP_ADJ_EN			(1 << 5)
#घोषणा FG_CNTL_CC_EN				(1 << 6)
#घोषणा FG_CNTL_GAUGE_EN			(1 << 7)

#घोषणा FG_15BIT_WORD_VALID			(1 << 15)
#घोषणा FG_15BIT_VAL_MASK			0x7fff

#घोषणा FG_REP_CAP_VALID			(1 << 7)
#घोषणा FG_REP_CAP_VAL_MASK			0x7F

#घोषणा FG_DES_CAP1_VALID			(1 << 7)
#घोषणा FG_DES_CAP_RES_LSB			1456    /* 1.456mAhr */

#घोषणा FG_DES_CC_RES_LSB			1456    /* 1.456mAhr */

#घोषणा FG_OCV_CAP_VALID			(1 << 7)
#घोषणा FG_OCV_CAP_VAL_MASK			0x7F
#घोषणा FG_CC_CAP_VALID				(1 << 7)
#घोषणा FG_CC_CAP_VAL_MASK			0x7F

#घोषणा FG_LOW_CAP_THR1_MASK		0xf0    /* 5% tp 20% */
#घोषणा FG_LOW_CAP_THR1_VAL			0xa0    /* 15 perc */
#घोषणा FG_LOW_CAP_THR2_MASK		0x0f    /* 0% to 15% */
#घोषणा FG_LOW_CAP_WARN_THR			14  /* 14 perc */
#घोषणा FG_LOW_CAP_CRIT_THR			4   /* 4 perc */
#घोषणा FG_LOW_CAP_SHDN_THR			0   /* 0 perc */

#घोषणा NR_RETRY_CNT    3
#घोषणा DEV_NAME	"axp288_fuel_gauge"

/* 1.1mV per LSB expressed in uV */
#घोषणा VOLTAGE_FROM_ADC(a)			((a * 11) / 10)
/* properties converted to uV, uA */
#घोषणा PROP_VOLT(a)		((a) * 1000)
#घोषणा PROP_CURR(a)		((a) * 1000)

#घोषणा AXP288_FG_INTR_NUM	6
क्रमागत अणु
	QWBTU_IRQ = 0,
	WBTU_IRQ,
	QWBTO_IRQ,
	WBTO_IRQ,
	WL2_IRQ,
	WL1_IRQ,
पूर्ण;

क्रमागत अणु
	BAT_TEMP = 0,
	PMIC_TEMP,
	SYSTEM_TEMP,
	BAT_CHRG_CURR,
	BAT_D_CURR,
	BAT_VOLT,
	IIO_CHANNEL_NUM
पूर्ण;

काष्ठा axp288_fg_info अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *regmap_irqc;
	पूर्णांक irq[AXP288_FG_INTR_NUM];
	काष्ठा iio_channel *iio_channel[IIO_CHANNEL_NUM];
	काष्ठा घातer_supply *bat;
	काष्ठा mutex lock;
	पूर्णांक status;
	पूर्णांक max_volt;
	काष्ठा dentry *debug_file;
पूर्ण;

अटल क्रमागत घातer_supply_property fuel_gauge_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
पूर्ण;

अटल पूर्णांक fuel_gauge_reg_पढ़ोb(काष्ठा axp288_fg_info *info, पूर्णांक reg)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val;

	क्रम (i = 0; i < NR_RETRY_CNT; i++) अणु
		ret = regmap_पढ़ो(info->regmap, reg, &val);
		अगर (ret == -EBUSY)
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "axp288 reg read err:%d\n", ret);
		वापस ret;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक fuel_gauge_reg_ग_लिखोb(काष्ठा axp288_fg_info *info, पूर्णांक reg, u8 val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(info->regmap, reg, (अचिन्हित पूर्णांक)val);

	अगर (ret < 0)
		dev_err(&info->pdev->dev, "axp288 reg write err:%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fuel_gauge_पढ़ो_15bit_word(काष्ठा axp288_fg_info *info, पूर्णांक reg)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(info->regmap, reg, buf, 2);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "Error reading reg 0x%02x err: %d\n",
			reg, ret);
		वापस ret;
	पूर्ण

	ret = get_unaligned_be16(buf);
	अगर (!(ret & FG_15BIT_WORD_VALID)) अणु
		dev_err(&info->pdev->dev, "Error reg 0x%02x contents not valid\n",
			reg);
		वापस -ENXIO;
	पूर्ण

	वापस ret & FG_15BIT_VAL_MASK;
पूर्ण

अटल पूर्णांक fuel_gauge_पढ़ो_12bit_word(काष्ठा axp288_fg_info *info, पूर्णांक reg)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(info->regmap, reg, buf, 2);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "Error reading reg 0x%02x err: %d\n",
			reg, ret);
		वापस ret;
	पूर्ण

	/* 12-bit data values have upper 8 bits in buf[0], lower 4 in buf[1] */
	वापस (buf[0] << 4) | ((buf[1] >> 4) & 0x0f);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक fuel_gauge_debug_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा axp288_fg_info *info = s->निजी;
	पूर्णांक raw_val, ret;

	seq_म_लिखो(s, " PWR_STATUS[%02x] : %02x\n",
		AXP20X_PWR_INPUT_STATUS,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_PWR_INPUT_STATUS));
	seq_म_लिखो(s, "PWR_OP_MODE[%02x] : %02x\n",
		AXP20X_PWR_OP_MODE,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_PWR_OP_MODE));
	seq_म_लिखो(s, " CHRG_CTRL1[%02x] : %02x\n",
		AXP20X_CHRG_CTRL1,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_CHRG_CTRL1));
	seq_म_लिखो(s, "       VLTF[%02x] : %02x\n",
		AXP20X_V_LTF_DISCHRG,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_V_LTF_DISCHRG));
	seq_म_लिखो(s, "       VHTF[%02x] : %02x\n",
		AXP20X_V_HTF_DISCHRG,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_V_HTF_DISCHRG));
	seq_म_लिखो(s, "    CC_CTRL[%02x] : %02x\n",
		AXP20X_CC_CTRL,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_CC_CTRL));
	seq_म_लिखो(s, "BATTERY CAP[%02x] : %02x\n",
		AXP20X_FG_RES,
		fuel_gauge_reg_पढ़ोb(info, AXP20X_FG_RES));
	seq_म_लिखो(s, "    FG_RDC1[%02x] : %02x\n",
		AXP288_FG_RDC1_REG,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_RDC1_REG));
	seq_म_लिखो(s, "    FG_RDC0[%02x] : %02x\n",
		AXP288_FG_RDC0_REG,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_RDC0_REG));
	seq_म_लिखो(s, "     FG_OCV[%02x] : %04x\n",
		AXP288_FG_OCVH_REG,
		fuel_gauge_पढ़ो_12bit_word(info, AXP288_FG_OCVH_REG));
	seq_म_लिखो(s, " FG_DES_CAP[%02x] : %04x\n",
		AXP288_FG_DES_CAP1_REG,
		fuel_gauge_पढ़ो_15bit_word(info, AXP288_FG_DES_CAP1_REG));
	seq_म_लिखो(s, "  FG_CC_MTR[%02x] : %04x\n",
		AXP288_FG_CC_MTR1_REG,
		fuel_gauge_पढ़ो_15bit_word(info, AXP288_FG_CC_MTR1_REG));
	seq_म_लिखो(s, " FG_OCV_CAP[%02x] : %02x\n",
		AXP288_FG_OCV_CAP_REG,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_OCV_CAP_REG));
	seq_म_लिखो(s, "  FG_CC_CAP[%02x] : %02x\n",
		AXP288_FG_CC_CAP_REG,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_CC_CAP_REG));
	seq_म_लिखो(s, " FG_LOW_CAP[%02x] : %02x\n",
		AXP288_FG_LOW_CAP_REG,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_LOW_CAP_REG));
	seq_म_लिखो(s, "TUNING_CTL0[%02x] : %02x\n",
		AXP288_FG_TUNE0,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_TUNE0));
	seq_म_लिखो(s, "TUNING_CTL1[%02x] : %02x\n",
		AXP288_FG_TUNE1,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_TUNE1));
	seq_म_लिखो(s, "TUNING_CTL2[%02x] : %02x\n",
		AXP288_FG_TUNE2,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_TUNE2));
	seq_म_लिखो(s, "TUNING_CTL3[%02x] : %02x\n",
		AXP288_FG_TUNE3,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_TUNE3));
	seq_म_लिखो(s, "TUNING_CTL4[%02x] : %02x\n",
		AXP288_FG_TUNE4,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_TUNE4));
	seq_म_लिखो(s, "TUNING_CTL5[%02x] : %02x\n",
		AXP288_FG_TUNE5,
		fuel_gauge_reg_पढ़ोb(info, AXP288_FG_TUNE5));

	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_TEMP], &raw_val);
	अगर (ret >= 0)
		seq_म_लिखो(s, "axp288-batttemp : %d\n", raw_val);
	ret = iio_पढ़ो_channel_raw(info->iio_channel[PMIC_TEMP], &raw_val);
	अगर (ret >= 0)
		seq_म_लिखो(s, "axp288-pmictemp : %d\n", raw_val);
	ret = iio_पढ़ो_channel_raw(info->iio_channel[SYSTEM_TEMP], &raw_val);
	अगर (ret >= 0)
		seq_म_लिखो(s, "axp288-systtemp : %d\n", raw_val);
	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_CHRG_CURR], &raw_val);
	अगर (ret >= 0)
		seq_म_लिखो(s, "axp288-chrgcurr : %d\n", raw_val);
	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_D_CURR], &raw_val);
	अगर (ret >= 0)
		seq_म_लिखो(s, "axp288-dchrgcur : %d\n", raw_val);
	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_VOLT], &raw_val);
	अगर (ret >= 0)
		seq_म_लिखो(s, "axp288-battvolt : %d\n", raw_val);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(fuel_gauge_debug);

अटल व्योम fuel_gauge_create_debugfs(काष्ठा axp288_fg_info *info)
अणु
	info->debug_file = debugfs_create_file("fuelgauge", 0666, शून्य,
		info, &fuel_gauge_debug_fops);
पूर्ण

अटल व्योम fuel_gauge_हटाओ_debugfs(काष्ठा axp288_fg_info *info)
अणु
	debugfs_हटाओ(info->debug_file);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fuel_gauge_create_debugfs(काष्ठा axp288_fg_info *info)
अणु
पूर्ण
अटल अंतरभूत व्योम fuel_gauge_हटाओ_debugfs(काष्ठा axp288_fg_info *info)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम fuel_gauge_get_status(काष्ठा axp288_fg_info *info)
अणु
	पूर्णांक pwr_stat, fg_res, curr, ret;

	pwr_stat = fuel_gauge_reg_पढ़ोb(info, AXP20X_PWR_INPUT_STATUS);
	अगर (pwr_stat < 0) अणु
		dev_err(&info->pdev->dev,
			"PWR STAT read failed:%d\n", pwr_stat);
		वापस;
	पूर्ण

	/* Report full अगर Vbus is valid and the reported capacity is 100% */
	अगर (!(pwr_stat & PS_STAT_VBUS_VALID))
		जाओ not_full;

	fg_res = fuel_gauge_reg_पढ़ोb(info, AXP20X_FG_RES);
	अगर (fg_res < 0) अणु
		dev_err(&info->pdev->dev, "FG RES read failed: %d\n", fg_res);
		वापस;
	पूर्ण
	अगर (!(fg_res & FG_REP_CAP_VALID))
		जाओ not_full;

	fg_res &= ~FG_REP_CAP_VALID;
	अगर (fg_res == 100) अणु
		info->status = POWER_SUPPLY_STATUS_FULL;
		वापस;
	पूर्ण

	/*
	 * Someबार the अक्षरger turns itself off beक्रमe fg-res reaches 100%.
	 * When this happens the AXP288 reports a not-अक्षरging status and
	 * 0 mA disअक्षरge current.
	 */
	अगर (fg_res < 90 || (pwr_stat & PS_STAT_BAT_CHRG_सूची))
		जाओ not_full;

	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_D_CURR], &curr);
	अगर (ret < 0) अणु
		dev_err(&info->pdev->dev, "FG get current failed: %d\n", ret);
		वापस;
	पूर्ण
	अगर (curr == 0) अणु
		info->status = POWER_SUPPLY_STATUS_FULL;
		वापस;
	पूर्ण

not_full:
	अगर (pwr_stat & PS_STAT_BAT_CHRG_सूची)
		info->status = POWER_SUPPLY_STATUS_CHARGING;
	अन्यथा
		info->status = POWER_SUPPLY_STATUS_DISCHARGING;
पूर्ण

अटल पूर्णांक fuel_gauge_get_vbatt(काष्ठा axp288_fg_info *info, पूर्णांक *vbatt)
अणु
	पूर्णांक ret = 0, raw_val;

	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_VOLT], &raw_val);
	अगर (ret < 0)
		जाओ vbatt_पढ़ो_fail;

	*vbatt = VOLTAGE_FROM_ADC(raw_val);
vbatt_पढ़ो_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक fuel_gauge_get_current(काष्ठा axp288_fg_info *info, पूर्णांक *cur)
अणु
	पूर्णांक ret, disअक्षरge;

	/* First check disअक्षरge current, so that we करो only 1 पढ़ो on bat. */
	ret = iio_पढ़ो_channel_raw(info->iio_channel[BAT_D_CURR], &disअक्षरge);
	अगर (ret < 0)
		वापस ret;

	अगर (disअक्षरge > 0) अणु
		*cur = -1 * disअक्षरge;
		वापस 0;
	पूर्ण

	वापस iio_पढ़ो_channel_raw(info->iio_channel[BAT_CHRG_CURR], cur);
पूर्ण

अटल पूर्णांक fuel_gauge_get_vocv(काष्ठा axp288_fg_info *info, पूर्णांक *vocv)
अणु
	पूर्णांक ret;

	ret = fuel_gauge_पढ़ो_12bit_word(info, AXP288_FG_OCVH_REG);
	अगर (ret >= 0)
		*vocv = VOLTAGE_FROM_ADC(ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fuel_gauge_battery_health(काष्ठा axp288_fg_info *info)
अणु
	पूर्णांक ret, vocv, health = POWER_SUPPLY_HEALTH_UNKNOWN;

	ret = fuel_gauge_get_vocv(info, &vocv);
	अगर (ret < 0)
		जाओ health_पढ़ो_fail;

	अगर (vocv > info->max_volt)
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	अन्यथा
		health = POWER_SUPPLY_HEALTH_GOOD;

health_पढ़ो_fail:
	वापस health;
पूर्ण

अटल पूर्णांक fuel_gauge_get_property(काष्ठा घातer_supply *ps,
		क्रमागत घातer_supply_property prop,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp288_fg_info *info = घातer_supply_get_drvdata(ps);
	पूर्णांक ret = 0, value;

	mutex_lock(&info->lock);
	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		fuel_gauge_get_status(info);
		val->पूर्णांकval = info->status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = fuel_gauge_battery_health(info);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = fuel_gauge_get_vbatt(info, &value);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;
		val->पूर्णांकval = PROP_VOLT(value);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_OCV:
		ret = fuel_gauge_get_vocv(info, &value);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;
		val->पूर्णांकval = PROP_VOLT(value);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = fuel_gauge_get_current(info, &value);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;
		val->पूर्णांकval = PROP_CURR(value);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = fuel_gauge_reg_पढ़ोb(info, AXP20X_PWR_OP_MODE);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;

		अगर (ret & CHRG_STAT_BAT_PRESENT)
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = fuel_gauge_reg_पढ़ोb(info, AXP20X_FG_RES);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;

		अगर (!(ret & FG_REP_CAP_VALID))
			dev_err(&info->pdev->dev,
				"capacity measurement not valid\n");
		val->पूर्णांकval = (ret & FG_REP_CAP_VAL_MASK);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		ret = fuel_gauge_reg_पढ़ोb(info, AXP288_FG_LOW_CAP_REG);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;
		val->पूर्णांकval = (ret & 0x0f);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = fuel_gauge_पढ़ो_15bit_word(info, AXP288_FG_CC_MTR1_REG);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;

		val->पूर्णांकval = ret * FG_DES_CAP_RES_LSB;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = fuel_gauge_पढ़ो_15bit_word(info, AXP288_FG_DES_CAP1_REG);
		अगर (ret < 0)
			जाओ fuel_gauge_पढ़ो_err;

		val->पूर्णांकval = ret * FG_DES_CAP_RES_LSB;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = PROP_VOLT(info->max_volt);
		अवरोध;
	शेष:
		mutex_unlock(&info->lock);
		वापस -EINVAL;
	पूर्ण

	mutex_unlock(&info->lock);
	वापस 0;

fuel_gauge_पढ़ो_err:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fuel_gauge_set_property(काष्ठा घातer_supply *ps,
		क्रमागत घातer_supply_property prop,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp288_fg_info *info = घातer_supply_get_drvdata(ps);
	पूर्णांक ret = 0;

	mutex_lock(&info->lock);
	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		अगर ((val->पूर्णांकval < 0) || (val->पूर्णांकval > 15)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = fuel_gauge_reg_पढ़ोb(info, AXP288_FG_LOW_CAP_REG);
		अगर (ret < 0)
			अवरोध;
		ret &= 0xf0;
		ret |= (val->पूर्णांकval & 0xf);
		ret = fuel_gauge_reg_ग_लिखोb(info, AXP288_FG_LOW_CAP_REG, ret);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fuel_gauge_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		ret = 1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t fuel_gauge_thपढ़ो_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा axp288_fg_info *info = dev;
	पूर्णांक i;

	क्रम (i = 0; i < AXP288_FG_INTR_NUM; i++) अणु
		अगर (info->irq[i] == irq)
			अवरोध;
	पूर्ण

	अगर (i >= AXP288_FG_INTR_NUM) अणु
		dev_warn(&info->pdev->dev, "spurious interrupt!!\n");
		वापस IRQ_NONE;
	पूर्ण

	चयन (i) अणु
	हाल QWBTU_IRQ:
		dev_info(&info->pdev->dev,
			"Quit Battery under temperature in work mode IRQ (QWBTU)\n");
		अवरोध;
	हाल WBTU_IRQ:
		dev_info(&info->pdev->dev,
			"Battery under temperature in work mode IRQ (WBTU)\n");
		अवरोध;
	हाल QWBTO_IRQ:
		dev_info(&info->pdev->dev,
			"Quit Battery over temperature in work mode IRQ (QWBTO)\n");
		अवरोध;
	हाल WBTO_IRQ:
		dev_info(&info->pdev->dev,
			"Battery over temperature in work mode IRQ (WBTO)\n");
		अवरोध;
	हाल WL2_IRQ:
		dev_info(&info->pdev->dev, "Low Batt Warning(2) INTR\n");
		अवरोध;
	हाल WL1_IRQ:
		dev_info(&info->pdev->dev, "Low Batt Warning(1) INTR\n");
		अवरोध;
	शेष:
		dev_warn(&info->pdev->dev, "Spurious Interrupt!!!\n");
	पूर्ण

	घातer_supply_changed(info->bat);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fuel_gauge_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा axp288_fg_info *info = घातer_supply_get_drvdata(psy);

	घातer_supply_changed(info->bat);
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc fuel_gauge_desc = अणु
	.name			= DEV_NAME,
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= fuel_gauge_props,
	.num_properties		= ARRAY_SIZE(fuel_gauge_props),
	.get_property		= fuel_gauge_get_property,
	.set_property		= fuel_gauge_set_property,
	.property_is_ग_लिखोable	= fuel_gauge_property_is_ग_लिखोable,
	.बाह्यal_घातer_changed	= fuel_gauge_बाह्यal_घातer_changed,
पूर्ण;

अटल व्योम fuel_gauge_init_irq(काष्ठा axp288_fg_info *info)
अणु
	पूर्णांक ret, i, pirq;

	क्रम (i = 0; i < AXP288_FG_INTR_NUM; i++) अणु
		pirq = platक्रमm_get_irq(info->pdev, i);
		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		अगर (info->irq[i] < 0) अणु
			dev_warn(&info->pdev->dev,
				"regmap_irq get virq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			जाओ पूर्णांकr_failed;
		पूर्ण
		ret = request_thपढ़ोed_irq(info->irq[i],
				शून्य, fuel_gauge_thपढ़ो_handler,
				IRQF_ONESHOT, DEV_NAME, info);
		अगर (ret) अणु
			dev_warn(&info->pdev->dev,
				"request irq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			जाओ पूर्णांकr_failed;
		पूर्ण अन्यथा अणु
			dev_info(&info->pdev->dev, "HW IRQ %d -> VIRQ %d\n",
				pirq, info->irq[i]);
		पूर्ण
	पूर्ण
	वापस;

पूर्णांकr_failed:
	क्रम (; i > 0; i--) अणु
		मुक्त_irq(info->irq[i - 1], info);
		info->irq[i - 1] = -1;
	पूर्ण
पूर्ण

/*
 * Some devices have no battery (HDMI sticks) and the axp288 battery's
 * detection reports one despite it not being there.
 * Please keep this listed sorted alphabetically.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id axp288_fuel_gauge_blacklist[] = अणु
	अणु
		/* ACEPC T8 Cherry Trail Z8350 mini PC */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "T8"),
			/* also match on somewhat unique bios-version */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1.000"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ACEPC T11 Cherry Trail Z8350 mini PC */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "T11"),
			/* also match on somewhat unique bios-version */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1.000"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ECS EF20EA */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "EF20EA"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Intel Cherry Trail Compute Stick, Winकरोws version */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel"),
			DMI_MATCH(DMI_PRODUCT_NAME, "STK1AW32SC"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Intel Cherry Trail Compute Stick, version without an OS */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel"),
			DMI_MATCH(DMI_PRODUCT_NAME, "STK1A32SC"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Meegopad T02 */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "MEEGOPAD T02"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Meegopad T08 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Default string"),
			DMI_MATCH(DMI_BOARD_VENDOR, "To be filled by OEM."),
			DMI_MATCH(DMI_BOARD_NAME, "T3 MRD"),
			DMI_MATCH(DMI_BOARD_VERSION, "V1.1"),
		पूर्ण,
	पूर्ण,
	अणु	/* Mele PCG03 Mini PC */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Mini PC"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Mini PC"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Minix Neo Z83-4 mini PC */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MINIX"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Z83-4"),
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक axp288_fuel_gauge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा axp288_fg_info *info;
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	अटल स्थिर अक्षर * स्थिर iio_chan_name[] = अणु
		[BAT_TEMP] = "axp288-batt-temp",
		[PMIC_TEMP] = "axp288-pmic-temp",
		[SYSTEM_TEMP] = "axp288-system-temp",
		[BAT_CHRG_CURR] = "axp288-chrg-curr",
		[BAT_D_CURR] = "axp288-chrg-d-curr",
		[BAT_VOLT] = "axp288-batt-volt",
	पूर्ण;
	अचिन्हित पूर्णांक val;

	अगर (dmi_check_प्रणाली(axp288_fuel_gauge_blacklist))
		वापस -ENODEV;

	/*
	 * On some devices the fuelgauge and अक्षरger parts of the axp288 are
	 * not used, check that the fuelgauge is enabled (CC_CTRL != 0).
	 */
	ret = regmap_पढ़ो(axp20x->regmap, AXP20X_CC_CTRL, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val == 0)
		वापस -ENODEV;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->pdev = pdev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;

	platक्रमm_set_drvdata(pdev, info);

	mutex_init(&info->lock);

	क्रम (i = 0; i < IIO_CHANNEL_NUM; i++) अणु
		/*
		 * Note cannot use devm_iio_channel_get because x86 प्रणालीs
		 * lack the device<->channel maps which iio_channel_get will
		 * try to use when passed a non शून्य device poपूर्णांकer.
		 */
		info->iio_channel[i] =
			iio_channel_get(शून्य, iio_chan_name[i]);
		अगर (IS_ERR(info->iio_channel[i])) अणु
			ret = PTR_ERR(info->iio_channel[i]);
			dev_dbg(&pdev->dev, "error getting iiochan %s: %d\n",
				iio_chan_name[i], ret);
			/* Wait क्रम axp288_adc to load */
			अगर (ret == -ENODEV)
				ret = -EPROBE_DEFER;

			जाओ out_मुक्त_iio_chan;
		पूर्ण
	पूर्ण

	ret = fuel_gauge_reg_पढ़ोb(info, AXP288_FG_DES_CAP1_REG);
	अगर (ret < 0)
		जाओ out_मुक्त_iio_chan;

	अगर (!(ret & FG_DES_CAP1_VALID)) अणु
		dev_err(&pdev->dev, "axp288 not configured by firmware\n");
		ret = -ENODEV;
		जाओ out_मुक्त_iio_chan;
	पूर्ण

	ret = fuel_gauge_reg_पढ़ोb(info, AXP20X_CHRG_CTRL1);
	अगर (ret < 0)
		जाओ out_मुक्त_iio_chan;
	चयन ((ret & CHRG_CCCV_CV_MASK) >> CHRG_CCCV_CV_BIT_POS) अणु
	हाल CHRG_CCCV_CV_4100MV:
		info->max_volt = 4100;
		अवरोध;
	हाल CHRG_CCCV_CV_4150MV:
		info->max_volt = 4150;
		अवरोध;
	हाल CHRG_CCCV_CV_4200MV:
		info->max_volt = 4200;
		अवरोध;
	हाल CHRG_CCCV_CV_4350MV:
		info->max_volt = 4350;
		अवरोध;
	पूर्ण

	psy_cfg.drv_data = info;
	info->bat = घातer_supply_रेजिस्टर(&pdev->dev, &fuel_gauge_desc, &psy_cfg);
	अगर (IS_ERR(info->bat)) अणु
		ret = PTR_ERR(info->bat);
		dev_err(&pdev->dev, "failed to register battery: %d\n", ret);
		जाओ out_मुक्त_iio_chan;
	पूर्ण

	fuel_gauge_create_debugfs(info);
	fuel_gauge_init_irq(info);

	वापस 0;

out_मुक्त_iio_chan:
	क्रम (i = 0; i < IIO_CHANNEL_NUM; i++)
		अगर (!IS_ERR_OR_शून्य(info->iio_channel[i]))
			iio_channel_release(info->iio_channel[i]);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id axp288_fg_id_table[] = अणु
	अणु .name = DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, axp288_fg_id_table);

अटल पूर्णांक axp288_fuel_gauge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp288_fg_info *info = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	घातer_supply_unरेजिस्टर(info->bat);
	fuel_gauge_हटाओ_debugfs(info);

	क्रम (i = 0; i < AXP288_FG_INTR_NUM; i++)
		अगर (info->irq[i] >= 0)
			मुक्त_irq(info->irq[i], info);

	क्रम (i = 0; i < IIO_CHANNEL_NUM; i++)
		iio_channel_release(info->iio_channel[i]);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver axp288_fuel_gauge_driver = अणु
	.probe = axp288_fuel_gauge_probe,
	.हटाओ = axp288_fuel_gauge_हटाओ,
	.id_table = axp288_fg_id_table,
	.driver = अणु
		.name = DEV_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axp288_fuel_gauge_driver);

MODULE_AUTHOR("Ramakrishna Pallala <ramakrishna.pallala@intel.com>");
MODULE_AUTHOR("Todd Brandt <todd.e.brandt@linux.intel.com>");
MODULE_DESCRIPTION("Xpower AXP288 Fuel Gauge Driver");
MODULE_LICENSE("GPL");
