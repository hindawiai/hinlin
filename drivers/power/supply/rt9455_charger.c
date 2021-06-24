<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Richtek RT9455WSC battery अक्षरger.
 *
 * Copyright (C) 2015 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/regmap.h>

#घोषणा RT9455_MANUFACTURER			"Richtek"
#घोषणा RT9455_MODEL_NAME			"RT9455"
#घोषणा RT9455_DRIVER_NAME			"rt9455-charger"

#घोषणा RT9455_IRQ_NAME				"interrupt"

#घोषणा RT9455_PWR_RDY_DELAY			1 /* 1 second */
#घोषणा RT9455_MAX_CHARGING_TIME		21600 /* 6 hrs */
#घोषणा RT9455_BATT_PRESENCE_DELAY		60 /* 60 seconds */

#घोषणा RT9455_CHARGE_MODE			0x00
#घोषणा RT9455_BOOST_MODE			0x01

#घोषणा RT9455_FAULT				0x03

#घोषणा RT9455_IAICR_100MA			0x00
#घोषणा RT9455_IAICR_500MA			0x01
#घोषणा RT9455_IAICR_NO_LIMIT			0x03

#घोषणा RT9455_CHARGE_DISABLE			0x00
#घोषणा RT9455_CHARGE_ENABLE			0x01

#घोषणा RT9455_PWR_FAULT			0x00
#घोषणा RT9455_PWR_GOOD				0x01

#घोषणा RT9455_REG_CTRL1			0x00 /* CTRL1 reg address */
#घोषणा RT9455_REG_CTRL2			0x01 /* CTRL2 reg address */
#घोषणा RT9455_REG_CTRL3			0x02 /* CTRL3 reg address */
#घोषणा RT9455_REG_DEV_ID			0x03 /* DEV_ID reg address */
#घोषणा RT9455_REG_CTRL4			0x04 /* CTRL4 reg address */
#घोषणा RT9455_REG_CTRL5			0x05 /* CTRL5 reg address */
#घोषणा RT9455_REG_CTRL6			0x06 /* CTRL6 reg address */
#घोषणा RT9455_REG_CTRL7			0x07 /* CTRL7 reg address */
#घोषणा RT9455_REG_IRQ1				0x08 /* IRQ1 reg address */
#घोषणा RT9455_REG_IRQ2				0x09 /* IRQ2 reg address */
#घोषणा RT9455_REG_IRQ3				0x0A /* IRQ3 reg address */
#घोषणा RT9455_REG_MASK1			0x0B /* MASK1 reg address */
#घोषणा RT9455_REG_MASK2			0x0C /* MASK2 reg address */
#घोषणा RT9455_REG_MASK3			0x0D /* MASK3 reg address */

क्रमागत rt9455_fields अणु
	F_STAT, F_BOOST, F_PWR_RDY, F_OTG_PIN_POLARITY, /* CTRL1 reg fields */

	F_IAICR, F_TE_SHDN_EN, F_HIGHER_OCP, F_TE, F_IAICR_INT, F_HIZ,
	F_OPA_MODE, /* CTRL2 reg fields */

	F_VOREG, F_OTG_PL, F_OTG_EN, /* CTRL3 reg fields */

	F_VENDOR_ID, F_CHIP_REV, /* DEV_ID reg fields */

	F_RST, /* CTRL4 reg fields */

	F_TMR_EN, F_MIVR, F_IPREC, F_IEOC_PERCENTAGE, /* CTRL5 reg fields*/

	F_IAICR_SEL, F_ICHRG, F_VPREC, /* CTRL6 reg fields */

	F_BATD_EN, F_CHG_EN, F_VMREG, /* CTRL7 reg fields */

	F_TSDI, F_VINOVPI, F_BATAB, /* IRQ1 reg fields */

	F_CHRVPI, F_CHBATOVI, F_CHTERMI, F_CHRCHGI, F_CH32MI, F_CHTREGI,
	F_CHMIVRI, /* IRQ2 reg fields */

	F_BSTBUSOVI, F_BSTOLI, F_BSTLOWVI, F_BST32SI, /* IRQ3 reg fields */

	F_TSDM, F_VINOVPIM, F_BATABM, /* MASK1 reg fields */

	F_CHRVPIM, F_CHBATOVIM, F_CHTERMIM, F_CHRCHGIM, F_CH32MIM, F_CHTREGIM,
	F_CHMIVRIM, /* MASK2 reg fields */

	F_BSTVINOVIM, F_BSTOLIM, F_BSTLOWVIM, F_BST32SIM, /* MASK3 reg fields */

	F_MAX_FIELDS
पूर्ण;

अटल स्थिर काष्ठा reg_field rt9455_reg_fields[] = अणु
	[F_STAT]		= REG_FIELD(RT9455_REG_CTRL1, 4, 5),
	[F_BOOST]		= REG_FIELD(RT9455_REG_CTRL1, 3, 3),
	[F_PWR_RDY]		= REG_FIELD(RT9455_REG_CTRL1, 2, 2),
	[F_OTG_PIN_POLARITY]	= REG_FIELD(RT9455_REG_CTRL1, 1, 1),

	[F_IAICR]		= REG_FIELD(RT9455_REG_CTRL2, 6, 7),
	[F_TE_SHDN_EN]		= REG_FIELD(RT9455_REG_CTRL2, 5, 5),
	[F_HIGHER_OCP]		= REG_FIELD(RT9455_REG_CTRL2, 4, 4),
	[F_TE]			= REG_FIELD(RT9455_REG_CTRL2, 3, 3),
	[F_IAICR_INT]		= REG_FIELD(RT9455_REG_CTRL2, 2, 2),
	[F_HIZ]			= REG_FIELD(RT9455_REG_CTRL2, 1, 1),
	[F_OPA_MODE]		= REG_FIELD(RT9455_REG_CTRL2, 0, 0),

	[F_VOREG]		= REG_FIELD(RT9455_REG_CTRL3, 2, 7),
	[F_OTG_PL]		= REG_FIELD(RT9455_REG_CTRL3, 1, 1),
	[F_OTG_EN]		= REG_FIELD(RT9455_REG_CTRL3, 0, 0),

	[F_VENDOR_ID]		= REG_FIELD(RT9455_REG_DEV_ID, 4, 7),
	[F_CHIP_REV]		= REG_FIELD(RT9455_REG_DEV_ID, 0, 3),

	[F_RST]			= REG_FIELD(RT9455_REG_CTRL4, 7, 7),

	[F_TMR_EN]		= REG_FIELD(RT9455_REG_CTRL5, 7, 7),
	[F_MIVR]		= REG_FIELD(RT9455_REG_CTRL5, 4, 5),
	[F_IPREC]		= REG_FIELD(RT9455_REG_CTRL5, 2, 3),
	[F_IEOC_PERCENTAGE]	= REG_FIELD(RT9455_REG_CTRL5, 0, 1),

	[F_IAICR_SEL]		= REG_FIELD(RT9455_REG_CTRL6, 7, 7),
	[F_ICHRG]		= REG_FIELD(RT9455_REG_CTRL6, 4, 6),
	[F_VPREC]		= REG_FIELD(RT9455_REG_CTRL6, 0, 2),

	[F_BATD_EN]		= REG_FIELD(RT9455_REG_CTRL7, 6, 6),
	[F_CHG_EN]		= REG_FIELD(RT9455_REG_CTRL7, 4, 4),
	[F_VMREG]		= REG_FIELD(RT9455_REG_CTRL7, 0, 3),

	[F_TSDI]		= REG_FIELD(RT9455_REG_IRQ1, 7, 7),
	[F_VINOVPI]		= REG_FIELD(RT9455_REG_IRQ1, 6, 6),
	[F_BATAB]		= REG_FIELD(RT9455_REG_IRQ1, 0, 0),

	[F_CHRVPI]		= REG_FIELD(RT9455_REG_IRQ2, 7, 7),
	[F_CHBATOVI]		= REG_FIELD(RT9455_REG_IRQ2, 5, 5),
	[F_CHTERMI]		= REG_FIELD(RT9455_REG_IRQ2, 4, 4),
	[F_CHRCHGI]		= REG_FIELD(RT9455_REG_IRQ2, 3, 3),
	[F_CH32MI]		= REG_FIELD(RT9455_REG_IRQ2, 2, 2),
	[F_CHTREGI]		= REG_FIELD(RT9455_REG_IRQ2, 1, 1),
	[F_CHMIVRI]		= REG_FIELD(RT9455_REG_IRQ2, 0, 0),

	[F_BSTBUSOVI]		= REG_FIELD(RT9455_REG_IRQ3, 7, 7),
	[F_BSTOLI]		= REG_FIELD(RT9455_REG_IRQ3, 6, 6),
	[F_BSTLOWVI]		= REG_FIELD(RT9455_REG_IRQ3, 5, 5),
	[F_BST32SI]		= REG_FIELD(RT9455_REG_IRQ3, 3, 3),

	[F_TSDM]		= REG_FIELD(RT9455_REG_MASK1, 7, 7),
	[F_VINOVPIM]		= REG_FIELD(RT9455_REG_MASK1, 6, 6),
	[F_BATABM]		= REG_FIELD(RT9455_REG_MASK1, 0, 0),

	[F_CHRVPIM]		= REG_FIELD(RT9455_REG_MASK2, 7, 7),
	[F_CHBATOVIM]		= REG_FIELD(RT9455_REG_MASK2, 5, 5),
	[F_CHTERMIM]		= REG_FIELD(RT9455_REG_MASK2, 4, 4),
	[F_CHRCHGIM]		= REG_FIELD(RT9455_REG_MASK2, 3, 3),
	[F_CH32MIM]		= REG_FIELD(RT9455_REG_MASK2, 2, 2),
	[F_CHTREGIM]		= REG_FIELD(RT9455_REG_MASK2, 1, 1),
	[F_CHMIVRIM]		= REG_FIELD(RT9455_REG_MASK2, 0, 0),

	[F_BSTVINOVIM]		= REG_FIELD(RT9455_REG_MASK3, 7, 7),
	[F_BSTOLIM]		= REG_FIELD(RT9455_REG_MASK3, 6, 6),
	[F_BSTLOWVIM]		= REG_FIELD(RT9455_REG_MASK3, 5, 5),
	[F_BST32SIM]		= REG_FIELD(RT9455_REG_MASK3, 3, 3),
पूर्ण;

#घोषणा GET_MASK(fid)	(BIT(rt9455_reg_fields[fid].msb + 1) - \
			 BIT(rt9455_reg_fields[fid].lsb))

/*
 * Each array initialised below shows the possible real-world values क्रम a
 * group of bits beदीर्घing to RT9455 रेजिस्टरs. The arrays are sorted in
 * ascending order. The index of each real-world value represents the value
 * that is encoded in the group of bits beदीर्घing to RT9455 रेजिस्टरs.
 */
/* REG06[6:4] (ICHRG) in uAh */
अटल स्थिर पूर्णांक rt9455_ichrg_values[] = अणु
	 500000,  650000,  800000,  950000, 1100000, 1250000, 1400000, 1550000
पूर्ण;

/*
 * When the अक्षरger is in अक्षरge mode, REG02[7:2] represent battery regulation
 * voltage.
 */
/* REG02[7:2] (VOREG) in uV */
अटल स्थिर पूर्णांक rt9455_voreg_values[] = अणु
	3500000, 3520000, 3540000, 3560000, 3580000, 3600000, 3620000, 3640000,
	3660000, 3680000, 3700000, 3720000, 3740000, 3760000, 3780000, 3800000,
	3820000, 3840000, 3860000, 3880000, 3900000, 3920000, 3940000, 3960000,
	3980000, 4000000, 4020000, 4040000, 4060000, 4080000, 4100000, 4120000,
	4140000, 4160000, 4180000, 4200000, 4220000, 4240000, 4260000, 4280000,
	4300000, 4330000, 4350000, 4370000, 4390000, 4410000, 4430000, 4450000,
	4450000, 4450000, 4450000, 4450000, 4450000, 4450000, 4450000, 4450000,
	4450000, 4450000, 4450000, 4450000, 4450000, 4450000, 4450000, 4450000
पूर्ण;

/*
 * When the अक्षरger is in boost mode, REG02[7:2] represent boost output
 * voltage.
 */
/* REG02[7:2] (Boost output voltage) in uV */
अटल स्थिर पूर्णांक rt9455_boost_voltage_values[] = अणु
	4425000, 4450000, 4475000, 4500000, 4525000, 4550000, 4575000, 4600000,
	4625000, 4650000, 4675000, 4700000, 4725000, 4750000, 4775000, 4800000,
	4825000, 4850000, 4875000, 4900000, 4925000, 4950000, 4975000, 5000000,
	5025000, 5050000, 5075000, 5100000, 5125000, 5150000, 5175000, 5200000,
	5225000, 5250000, 5275000, 5300000, 5325000, 5350000, 5375000, 5400000,
	5425000, 5450000, 5475000, 5500000, 5525000, 5550000, 5575000, 5600000,
	5600000, 5600000, 5600000, 5600000, 5600000, 5600000, 5600000, 5600000,
	5600000, 5600000, 5600000, 5600000, 5600000, 5600000, 5600000, 5600000,
पूर्ण;

/* REG07[3:0] (VMREG) in uV */
अटल स्थिर पूर्णांक rt9455_vmreg_values[] = अणु
	4200000, 4220000, 4240000, 4260000, 4280000, 4300000, 4320000, 4340000,
	4360000, 4380000, 4400000, 4430000, 4450000, 4450000, 4450000, 4450000
पूर्ण;

/* REG05[5:4] (IEOC_PERCENTAGE) */
अटल स्थिर पूर्णांक rt9455_ieoc_percentage_values[] = अणु
	10, 30, 20, 30
पूर्ण;

/* REG05[1:0] (MIVR) in uV */
अटल स्थिर पूर्णांक rt9455_mivr_values[] = अणु
	4000000, 4250000, 4500000, 5000000
पूर्ण;

/* REG05[1:0] (IAICR) in uA */
अटल स्थिर पूर्णांक rt9455_iaicr_values[] = अणु
	100000, 500000, 1000000, 2000000
पूर्ण;

काष्ठा rt9455_info अणु
	काष्ठा i2c_client		*client;
	काष्ठा regmap			*regmap;
	काष्ठा regmap_field		*regmap_fields[F_MAX_FIELDS];
	काष्ठा घातer_supply		*अक्षरger;
#अगर IS_ENABLED(CONFIG_USB_PHY)
	काष्ठा usb_phy			*usb_phy;
	काष्ठा notअगरier_block		nb;
#पूर्ण_अगर
	काष्ठा delayed_work		pwr_rdy_work;
	काष्ठा delayed_work		max_अक्षरging_समय_work;
	काष्ठा delayed_work		batt_presence_work;
	u32				voreg;
	u32				boost_voltage;
पूर्ण;

/*
 * Iterate through each element of the 'tbl' array until an element whose value
 * is greater than v is found. Return the index of the respective element,
 * or the index of the last element in the array, अगर no such element is found.
 */
अटल अचिन्हित पूर्णांक rt9455_find_idx(स्थिर पूर्णांक tbl[], पूर्णांक tbl_size, पूर्णांक v)
अणु
	पूर्णांक i;

	/*
	 * No need to iterate until the last index in the table because
	 * अगर no element greater than v is found in the table,
	 * or अगर only the last element is greater than v,
	 * function वापसs the index of the last element.
	 */
	क्रम (i = 0; i < tbl_size - 1; i++)
		अगर (v <= tbl[i])
			वापस i;

	वापस (tbl_size - 1);
पूर्ण

अटल पूर्णांक rt9455_get_field_val(काष्ठा rt9455_info *info,
				क्रमागत rt9455_fields field,
				स्थिर पूर्णांक tbl[], पूर्णांक tbl_size, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(info->regmap_fields[field], &v);
	अगर (ret)
		वापस ret;

	v = (v >= tbl_size) ? (tbl_size - 1) : v;
	*val = tbl[v];

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_set_field_val(काष्ठा rt9455_info *info,
				क्रमागत rt9455_fields field,
				स्थिर पूर्णांक tbl[], पूर्णांक tbl_size, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक idx = rt9455_find_idx(tbl, tbl_size, val);

	वापस regmap_field_ग_लिखो(info->regmap_fields[field], idx);
पूर्ण

अटल पूर्णांक rt9455_रेजिस्टर_reset(काष्ठा rt9455_info *info)
अणु
	काष्ठा device *dev = &info->client->dev;
	अचिन्हित पूर्णांक v;
	पूर्णांक ret, limit = 100;

	ret = regmap_field_ग_लिखो(info->regmap_fields[F_RST], 0x01);
	अगर (ret) अणु
		dev_err(dev, "Failed to set RST bit\n");
		वापस ret;
	पूर्ण

	/*
	 * To make sure that reset operation has finished, loop until RST bit
	 * is set to 0.
	 */
	करो अणु
		ret = regmap_field_पढ़ो(info->regmap_fields[F_RST], &v);
		अगर (ret) अणु
			dev_err(dev, "Failed to read RST bit\n");
			वापस ret;
		पूर्ण

		अगर (!v)
			अवरोध;

		usleep_range(10, 100);
	पूर्ण जबतक (--limit);

	अगर (!limit)
		वापस -EIO;

	वापस 0;
पूर्ण

/* Charger घातer supply property routines */
अटल क्रमागत घातer_supply_property rt9455_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल अक्षर *rt9455_अक्षरger_supplied_to[] = अणु
	"main-battery",
पूर्ण;

अटल पूर्णांक rt9455_अक्षरger_get_status(काष्ठा rt9455_info *info,
				     जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक v, pwr_rdy;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(info->regmap_fields[F_PWR_RDY],
				&pwr_rdy);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read PWR_RDY bit\n");
		वापस ret;
	पूर्ण

	/*
	 * If PWR_RDY bit is unset, the battery is disअक्षरging. Otherwise,
	 * STAT bits value must be checked.
	 */
	अगर (!pwr_rdy) अणु
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		वापस 0;
	पूर्ण

	ret = regmap_field_पढ़ो(info->regmap_fields[F_STAT], &v);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read STAT bits\n");
		वापस ret;
	पूर्ण

	चयन (v) अणु
	हाल 0:
		/*
		 * If PWR_RDY bit is set, but STAT bits value is 0, the अक्षरger
		 * may be in one of the following हालs:
		 * 1. CHG_EN bit is 0.
		 * 2. CHG_EN bit is 1 but the battery is not connected.
		 * In any of these हालs, POWER_SUPPLY_STATUS_NOT_CHARGING is
		 * वापसed.
		 */
		val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		वापस 0;
	हाल 1:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		वापस 0;
	हाल 2:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		वापस 0;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_health(काष्ठा rt9455_info *info,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा device *dev = &info->client->dev;
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ1, &v);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ1 register\n");
		वापस ret;
	पूर्ण

	अगर (v & GET_MASK(F_TSDI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		वापस 0;
	पूर्ण
	अगर (v & GET_MASK(F_VINOVPI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		वापस 0;
	पूर्ण
	अगर (v & GET_MASK(F_BATAB)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ2, &v);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ2 register\n");
		वापस ret;
	पूर्ण

	अगर (v & GET_MASK(F_CHBATOVI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		वापस 0;
	पूर्ण
	अगर (v & GET_MASK(F_CH32MI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ3, &v);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ3 register\n");
		वापस ret;
	पूर्ण

	अगर (v & GET_MASK(F_BSTBUSOVI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		वापस 0;
	पूर्ण
	अगर (v & GET_MASK(F_BSTOLI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		वापस 0;
	पूर्ण
	अगर (v & GET_MASK(F_BSTLOWVI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		वापस 0;
	पूर्ण
	अगर (v & GET_MASK(F_BST32SI)) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
		वापस 0;
	पूर्ण

	ret = regmap_field_पढ़ो(info->regmap_fields[F_STAT], &v);
	अगर (ret) अणु
		dev_err(dev, "Failed to read STAT bits\n");
		वापस ret;
	पूर्ण

	अगर (v == RT9455_FAULT) अणु
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_battery_presence(काष्ठा rt9455_info *info,
					       जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(info->regmap_fields[F_BATAB], &v);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read BATAB bit\n");
		वापस ret;
	पूर्ण

	/*
	 * Since BATAB is 1 when battery is NOT present and 0 otherwise,
	 * !BATAB is वापसed.
	 */
	val->पूर्णांकval = !v;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_online(काष्ठा rt9455_info *info,
				     जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(info->regmap_fields[F_PWR_RDY], &v);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read PWR_RDY bit\n");
		वापस ret;
	पूर्ण

	val->पूर्णांकval = (पूर्णांक)v;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_current(काष्ठा rt9455_info *info,
				      जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक curr;
	पूर्णांक ret;

	ret = rt9455_get_field_val(info, F_ICHRG,
				   rt9455_ichrg_values,
				   ARRAY_SIZE(rt9455_ichrg_values),
				   &curr);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read ICHRG value\n");
		वापस ret;
	पूर्ण

	val->पूर्णांकval = curr;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_current_max(काष्ठा rt9455_info *info,
					  जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक idx = ARRAY_SIZE(rt9455_ichrg_values) - 1;

	val->पूर्णांकval = rt9455_ichrg_values[idx];

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_voltage(काष्ठा rt9455_info *info,
				      जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक voltage;
	पूर्णांक ret;

	ret = rt9455_get_field_val(info, F_VOREG,
				   rt9455_voreg_values,
				   ARRAY_SIZE(rt9455_voreg_values),
				   &voltage);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read VOREG value\n");
		वापस ret;
	पूर्ण

	val->पूर्णांकval = voltage;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_voltage_max(काष्ठा rt9455_info *info,
					  जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक idx = ARRAY_SIZE(rt9455_vmreg_values) - 1;

	val->पूर्णांकval = rt9455_vmreg_values[idx];

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_term_current(काष्ठा rt9455_info *info,
					   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ichrg, ieoc_percentage, ret;

	ret = rt9455_get_field_val(info, F_ICHRG,
				   rt9455_ichrg_values,
				   ARRAY_SIZE(rt9455_ichrg_values),
				   &ichrg);
	अगर (ret) अणु
		dev_err(dev, "Failed to read ICHRG value\n");
		वापस ret;
	पूर्ण

	ret = rt9455_get_field_val(info, F_IEOC_PERCENTAGE,
				   rt9455_ieoc_percentage_values,
				   ARRAY_SIZE(rt9455_ieoc_percentage_values),
				   &ieoc_percentage);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IEOC value\n");
		वापस ret;
	पूर्ण

	val->पूर्णांकval = ichrg * ieoc_percentage / 100;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_अक्षरger_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा rt9455_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		वापस rt9455_अक्षरger_get_status(info, val);
	हाल POWER_SUPPLY_PROP_HEALTH:
		वापस rt9455_अक्षरger_get_health(info, val);
	हाल POWER_SUPPLY_PROP_PRESENT:
		वापस rt9455_अक्षरger_get_battery_presence(info, val);
	हाल POWER_SUPPLY_PROP_ONLINE:
		वापस rt9455_अक्षरger_get_online(info, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस rt9455_अक्षरger_get_current(info, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		वापस rt9455_अक्षरger_get_current_max(info, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		वापस rt9455_अक्षरger_get_voltage(info, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		वापस rt9455_अक्षरger_get_voltage_max(info, val);
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_SYSTEM;
		वापस 0;
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस rt9455_अक्षरger_get_term_current(info, val);
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = RT9455_MODEL_NAME;
		वापस 0;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = RT9455_MANUFACTURER;
		वापस 0;
	शेष:
		वापस -ENODATA;
	पूर्ण
पूर्ण

अटल पूर्णांक rt9455_hw_init(काष्ठा rt9455_info *info, u32 ichrg,
			  u32 ieoc_percentage,
			  u32 mivr, u32 iaicr)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक idx, ret;

	ret = rt9455_रेजिस्टर_reset(info);
	अगर (ret) अणु
		dev_err(dev, "Power On Reset failed\n");
		वापस ret;
	पूर्ण

	/* Set TE bit in order to enable end of अक्षरge detection */
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_TE], 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to set TE bit\n");
		वापस ret;
	पूर्ण

	/* Set TE_SHDN_EN bit in order to enable end of अक्षरge detection */
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_TE_SHDN_EN], 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to set TE_SHDN_EN bit\n");
		वापस ret;
	पूर्ण

	/*
	 * Set BATD_EN bit in order to enable battery detection
	 * when अक्षरging is करोne
	 */
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_BATD_EN], 1);
	अगर (ret) अणु
		dev_err(dev, "Failed to set BATD_EN bit\n");
		वापस ret;
	पूर्ण

	/*
	 * Disable Safety Timer. In अक्षरge mode, this समयr terminates अक्षरging
	 * अगर no पढ़ो or ग_लिखो via I2C is करोne within 32 minutes. This समयr
	 * aव्योमs overअक्षरging the baterry when the OS is not loaded and the
	 * अक्षरger is connected to a घातer source.
	 * In boost mode, this समयr triggers BST32SI पूर्णांकerrupt अगर no पढ़ो or
	 * ग_लिखो via I2C is करोne within 32 seconds.
	 * When the OS is loaded and the अक्षरger driver is inserted, it is used
	 * delayed_work, named max_अक्षरging_समय_work, to aव्योम overअक्षरging
	 * the battery.
	 */
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_TMR_EN], 0x00);
	अगर (ret) अणु
		dev_err(dev, "Failed to disable Safety Timer\n");
		वापस ret;
	पूर्ण

	/* Set ICHRG to value retrieved from device-specअगरic data */
	ret = rt9455_set_field_val(info, F_ICHRG,
				   rt9455_ichrg_values,
				   ARRAY_SIZE(rt9455_ichrg_values), ichrg);
	अगर (ret) अणु
		dev_err(dev, "Failed to set ICHRG value\n");
		वापस ret;
	पूर्ण

	/* Set IEOC Percentage to value retrieved from device-specअगरic data */
	ret = rt9455_set_field_val(info, F_IEOC_PERCENTAGE,
				   rt9455_ieoc_percentage_values,
				   ARRAY_SIZE(rt9455_ieoc_percentage_values),
				   ieoc_percentage);
	अगर (ret) अणु
		dev_err(dev, "Failed to set IEOC Percentage value\n");
		वापस ret;
	पूर्ण

	/* Set VOREG to value retrieved from device-specअगरic data */
	ret = rt9455_set_field_val(info, F_VOREG,
				   rt9455_voreg_values,
				   ARRAY_SIZE(rt9455_voreg_values),
				   info->voreg);
	अगर (ret) अणु
		dev_err(dev, "Failed to set VOREG value\n");
		वापस ret;
	पूर्ण

	/* Set VMREG value to maximum (4.45V). */
	idx = ARRAY_SIZE(rt9455_vmreg_values) - 1;
	ret = rt9455_set_field_val(info, F_VMREG,
				   rt9455_vmreg_values,
				   ARRAY_SIZE(rt9455_vmreg_values),
				   rt9455_vmreg_values[idx]);
	अगर (ret) अणु
		dev_err(dev, "Failed to set VMREG value\n");
		वापस ret;
	पूर्ण

	/*
	 * Set MIVR to value retrieved from device-specअगरic data.
	 * If no value is specअगरied, शेष value क्रम MIVR is 4.5V.
	 */
	अगर (mivr == -1)
		mivr = 4500000;

	ret = rt9455_set_field_val(info, F_MIVR,
				   rt9455_mivr_values,
				   ARRAY_SIZE(rt9455_mivr_values), mivr);
	अगर (ret) अणु
		dev_err(dev, "Failed to set MIVR value\n");
		वापस ret;
	पूर्ण

	/*
	 * Set IAICR to value retrieved from device-specअगरic data.
	 * If no value is specअगरied, शेष value क्रम IAICR is 500 mA.
	 */
	अगर (iaicr == -1)
		iaicr = 500000;

	ret = rt9455_set_field_val(info, F_IAICR,
				   rt9455_iaicr_values,
				   ARRAY_SIZE(rt9455_iaicr_values), iaicr);
	अगर (ret) अणु
		dev_err(dev, "Failed to set IAICR value\n");
		वापस ret;
	पूर्ण

	/*
	 * Set IAICR_INT bit so that IAICR value is determined by IAICR bits
	 * and not by OTG pin.
	 */
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_IAICR_INT], 0x01);
	अगर (ret) अणु
		dev_err(dev, "Failed to set IAICR_INT bit\n");
		वापस ret;
	पूर्ण

	/*
	 * Disable CHMIVRI पूर्णांकerrupt. Because the driver sets MIVR value,
	 * CHMIVRI is triggered, but there is no action to be taken by the
	 * driver when CHMIVRI is triggered.
	 */
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_CHMIVRIM], 0x01);
	अगर (ret) अणु
		dev_err(dev, "Failed to mask CHMIVRI interrupt\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_USB_PHY)
/*
 * Beक्रमe setting the अक्षरger पूर्णांकo boost mode, boost output voltage is
 * set. This is needed because boost output voltage may dअगरfer from battery
 * regulation voltage. F_VOREG bits represent either battery regulation voltage
 * or boost output voltage, depending on the mode the अक्षरger is. Both battery
 * regulation voltage and boost output voltage are पढ़ो from DT/ACPI during
 * probe.
 */
अटल पूर्णांक rt9455_set_boost_voltage_beक्रमe_boost_mode(काष्ठा rt9455_info *info)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	ret = rt9455_set_field_val(info, F_VOREG,
				   rt9455_boost_voltage_values,
				   ARRAY_SIZE(rt9455_boost_voltage_values),
				   info->boost_voltage);
	अगर (ret) अणु
		dev_err(dev, "Failed to set boost output voltage value\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Beक्रमe setting the अक्षरger पूर्णांकo अक्षरge mode, battery regulation voltage is
 * set. This is needed because boost output voltage may dअगरfer from battery
 * regulation voltage. F_VOREG bits represent either battery regulation voltage
 * or boost output voltage, depending on the mode the अक्षरger is. Both battery
 * regulation voltage and boost output voltage are पढ़ो from DT/ACPI during
 * probe.
 */
अटल पूर्णांक rt9455_set_voreg_beक्रमe_अक्षरge_mode(काष्ठा rt9455_info *info)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	ret = rt9455_set_field_val(info, F_VOREG,
				   rt9455_voreg_values,
				   ARRAY_SIZE(rt9455_voreg_values),
				   info->voreg);
	अगर (ret) अणु
		dev_err(dev, "Failed to set VOREG value\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_irq_handler_check_irq1_रेजिस्टर(काष्ठा rt9455_info *info,
						  bool *_is_battery_असलent,
						  bool *_alert_userspace)
अणु
	अचिन्हित पूर्णांक irq1, mask1, mask2;
	काष्ठा device *dev = &info->client->dev;
	bool is_battery_असलent = false;
	bool alert_userspace = false;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ1, &irq1);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ1 register\n");
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_MASK1, &mask1);
	अगर (ret) अणु
		dev_err(dev, "Failed to read MASK1 register\n");
		वापस ret;
	पूर्ण

	अगर (irq1 & GET_MASK(F_TSDI)) अणु
		dev_err(dev, "Thermal shutdown fault occurred\n");
		alert_userspace = true;
	पूर्ण

	अगर (irq1 & GET_MASK(F_VINOVPI)) अणु
		dev_err(dev, "Overvoltage input occurred\n");
		alert_userspace = true;
	पूर्ण

	अगर (irq1 & GET_MASK(F_BATAB)) अणु
		dev_err(dev, "Battery absence occurred\n");
		is_battery_असलent = true;
		alert_userspace = true;

		अगर ((mask1 & GET_MASK(F_BATABM)) == 0) अणु
			ret = regmap_field_ग_लिखो(info->regmap_fields[F_BATABM],
						 0x01);
			अगर (ret) अणु
				dev_err(dev, "Failed to mask BATAB interrupt\n");
				वापस ret;
			पूर्ण
		पूर्ण

		ret = regmap_पढ़ो(info->regmap, RT9455_REG_MASK2, &mask2);
		अगर (ret) अणु
			dev_err(dev, "Failed to read MASK2 register\n");
			वापस ret;
		पूर्ण

		अगर (mask2 & GET_MASK(F_CHTERMIM)) अणु
			ret = regmap_field_ग_लिखो(
				info->regmap_fields[F_CHTERMIM], 0x00);
			अगर (ret) अणु
				dev_err(dev, "Failed to unmask CHTERMI interrupt\n");
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (mask2 & GET_MASK(F_CHRCHGIM)) अणु
			ret = regmap_field_ग_लिखो(
				info->regmap_fields[F_CHRCHGIM], 0x00);
			अगर (ret) अणु
				dev_err(dev, "Failed to unmask CHRCHGI interrupt\n");
				वापस ret;
			पूर्ण
		पूर्ण

		/*
		 * When the battery is असलent, max_अक्षरging_समय_work is
		 * cancelled, since no अक्षरging is करोne.
		 */
		cancel_delayed_work_sync(&info->max_अक्षरging_समय_work);
		/*
		 * Since no पूर्णांकerrupt is triggered when the battery is
		 * reconnected, max_अक्षरging_समय_work is not rescheduled.
		 * Thereक्रमe, batt_presence_work is scheduled to check whether
		 * the battery is still असलent or not.
		 */
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &info->batt_presence_work,
				   RT9455_BATT_PRESENCE_DELAY * HZ);
	पूर्ण

	*_is_battery_असलent = is_battery_असलent;

	अगर (alert_userspace)
		*_alert_userspace = alert_userspace;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_irq_handler_check_irq2_रेजिस्टर(काष्ठा rt9455_info *info,
						  bool is_battery_असलent,
						  bool *_alert_userspace)
अणु
	अचिन्हित पूर्णांक irq2, mask2;
	काष्ठा device *dev = &info->client->dev;
	bool alert_userspace = false;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ2, &irq2);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ2 register\n");
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_MASK2, &mask2);
	अगर (ret) अणु
		dev_err(dev, "Failed to read MASK2 register\n");
		वापस ret;
	पूर्ण

	अगर (irq2 & GET_MASK(F_CHRVPI)) अणु
		dev_dbg(dev, "Charger fault occurred\n");
		/*
		 * CHRVPI bit is set in 2 हालs:
		 * 1. when the घातer source is connected to the अक्षरger.
		 * 2. when the घातer source is disconnected from the अक्षरger.
		 * To identअगरy the हाल, PWR_RDY bit is checked. Because
		 * PWR_RDY bit is set / cleared after CHRVPI पूर्णांकerrupt is
		 * triggered, it is used delayed_work to later पढ़ो PWR_RDY bit.
		 * Also, करो not set to true alert_userspace, because there is no
		 * need to notअगरy userspace when CHRVPI पूर्णांकerrupt has occurred.
		 * Userspace will be notअगरied after PWR_RDY bit is पढ़ो.
		 */
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &info->pwr_rdy_work,
				   RT9455_PWR_RDY_DELAY * HZ);
	पूर्ण
	अगर (irq2 & GET_MASK(F_CHBATOVI)) अणु
		dev_err(dev, "Battery OVP occurred\n");
		alert_userspace = true;
	पूर्ण
	अगर (irq2 & GET_MASK(F_CHTERMI)) अणु
		dev_dbg(dev, "Charge terminated\n");
		अगर (!is_battery_असलent) अणु
			अगर ((mask2 & GET_MASK(F_CHTERMIM)) == 0) अणु
				ret = regmap_field_ग_लिखो(
					info->regmap_fields[F_CHTERMIM], 0x01);
				अगर (ret) अणु
					dev_err(dev, "Failed to mask CHTERMI interrupt\n");
					वापस ret;
				पूर्ण
				/*
				 * Update MASK2 value, since CHTERMIM bit is
				 * set.
				 */
				mask2 = mask2 | GET_MASK(F_CHTERMIM);
			पूर्ण
			cancel_delayed_work_sync(&info->max_अक्षरging_समय_work);
			alert_userspace = true;
		पूर्ण
	पूर्ण
	अगर (irq2 & GET_MASK(F_CHRCHGI)) अणु
		dev_dbg(dev, "Recharge request\n");
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_CHG_EN],
					 RT9455_CHARGE_ENABLE);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable charging\n");
			वापस ret;
		पूर्ण
		अगर (mask2 & GET_MASK(F_CHTERMIM)) अणु
			ret = regmap_field_ग_लिखो(
				info->regmap_fields[F_CHTERMIM], 0x00);
			अगर (ret) अणु
				dev_err(dev, "Failed to unmask CHTERMI interrupt\n");
				वापस ret;
			पूर्ण
			/* Update MASK2 value, since CHTERMIM bit is cleared. */
			mask2 = mask2 & ~GET_MASK(F_CHTERMIM);
		पूर्ण
		अगर (!is_battery_असलent) अणु
			/*
			 * No need to check whether the अक्षरger is connected to
			 * घातer source when CHRCHGI is received, since CHRCHGI
			 * is not triggered अगर the अक्षरger is not connected to
			 * the घातer source.
			 */
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &info->max_अक्षरging_समय_work,
					   RT9455_MAX_CHARGING_TIME * HZ);
			alert_userspace = true;
		पूर्ण
	पूर्ण
	अगर (irq2 & GET_MASK(F_CH32MI)) अणु
		dev_err(dev, "Charger fault. 32 mins timeout occurred\n");
		alert_userspace = true;
	पूर्ण
	अगर (irq2 & GET_MASK(F_CHTREGI)) अणु
		dev_warn(dev,
			 "Charger warning. Thermal regulation loop active\n");
		alert_userspace = true;
	पूर्ण
	अगर (irq2 & GET_MASK(F_CHMIVRI)) अणु
		dev_dbg(dev,
			"Charger warning. Input voltage MIVR loop active\n");
	पूर्ण

	अगर (alert_userspace)
		*_alert_userspace = alert_userspace;

	वापस 0;
पूर्ण

अटल पूर्णांक rt9455_irq_handler_check_irq3_रेजिस्टर(काष्ठा rt9455_info *info,
						  bool *_alert_userspace)
अणु
	अचिन्हित पूर्णांक irq3, mask3;
	काष्ठा device *dev = &info->client->dev;
	bool alert_userspace = false;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ3, &irq3);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ3 register\n");
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_MASK3, &mask3);
	अगर (ret) अणु
		dev_err(dev, "Failed to read MASK3 register\n");
		वापस ret;
	पूर्ण

	अगर (irq3 & GET_MASK(F_BSTBUSOVI)) अणु
		dev_err(dev, "Boost fault. Overvoltage input occurred\n");
		alert_userspace = true;
	पूर्ण
	अगर (irq3 & GET_MASK(F_BSTOLI)) अणु
		dev_err(dev, "Boost fault. Overload\n");
		alert_userspace = true;
	पूर्ण
	अगर (irq3 & GET_MASK(F_BSTLOWVI)) अणु
		dev_err(dev, "Boost fault. Battery voltage too low\n");
		alert_userspace = true;
	पूर्ण
	अगर (irq3 & GET_MASK(F_BST32SI)) अणु
		dev_err(dev, "Boost fault. 32 seconds timeout occurred.\n");
		alert_userspace = true;
	पूर्ण

	अगर (alert_userspace) अणु
		dev_info(dev, "Boost fault occurred, therefore the charger goes into charge mode\n");
		ret = rt9455_set_voreg_beक्रमe_अक्षरge_mode(info);
		अगर (ret) अणु
			dev_err(dev, "Failed to set VOREG before entering charge mode\n");
			वापस ret;
		पूर्ण
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_OPA_MODE],
					 RT9455_CHARGE_MODE);
		अगर (ret) अणु
			dev_err(dev, "Failed to set charger in charge mode\n");
			वापस ret;
		पूर्ण
		*_alert_userspace = alert_userspace;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rt9455_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt9455_info *info = data;
	काष्ठा device *dev;
	bool alert_userspace = false;
	bool is_battery_असलent = false;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	अगर (!info)
		वापस IRQ_NONE;

	dev = &info->client->dev;

	अगर (irq != info->client->irq) अणु
		dev_err(dev, "Interrupt is not for RT9455 charger\n");
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_field_पढ़ो(info->regmap_fields[F_STAT], &status);
	अगर (ret) अणु
		dev_err(dev, "Failed to read STAT bits\n");
		वापस IRQ_HANDLED;
	पूर्ण
	dev_dbg(dev, "Charger status is %d\n", status);

	/*
	 * Each function that processes an IRQ रेजिस्टर receives as output
	 * parameter alert_userspace poपूर्णांकer. alert_userspace is set to true
	 * in such a function only अगर an पूर्णांकerrupt has occurred in the
	 * respective पूर्णांकerrupt रेजिस्टर. This way, it is aव्योमed the following
	 * हाल: पूर्णांकerrupt occurs only in IRQ1 रेजिस्टर,
	 * rt9455_irq_handler_check_irq1_रेजिस्टर() function sets to true
	 * alert_userspace, but rt9455_irq_handler_check_irq2_रेजिस्टर()
	 * and rt9455_irq_handler_check_irq3_रेजिस्टर() functions set to false
	 * alert_userspace and घातer_supply_changed() is never called.
	 */
	ret = rt9455_irq_handler_check_irq1_रेजिस्टर(info, &is_battery_असलent,
						     &alert_userspace);
	अगर (ret) अणु
		dev_err(dev, "Failed to handle IRQ1 register\n");
		वापस IRQ_HANDLED;
	पूर्ण

	ret = rt9455_irq_handler_check_irq2_रेजिस्टर(info, is_battery_असलent,
						     &alert_userspace);
	अगर (ret) अणु
		dev_err(dev, "Failed to handle IRQ2 register\n");
		वापस IRQ_HANDLED;
	पूर्ण

	ret = rt9455_irq_handler_check_irq3_रेजिस्टर(info, &alert_userspace);
	अगर (ret) अणु
		dev_err(dev, "Failed to handle IRQ3 register\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (alert_userspace) अणु
		/*
		 * Someबार, an पूर्णांकerrupt occurs जबतक rt9455_probe() function
		 * is executing and घातer_supply_रेजिस्टर() is not yet called.
		 * Do not call घातer_supply_changed() in this हाल.
		 */
		अगर (info->अक्षरger)
			घातer_supply_changed(info->अक्षरger);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rt9455_discover_अक्षरger(काष्ठा rt9455_info *info, u32 *ichrg,
				   u32 *ieoc_percentage,
				   u32 *mivr, u32 *iaicr)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	अगर (!dev->of_node && !ACPI_HANDLE(dev)) अणु
		dev_err(dev, "No support for either device tree or ACPI\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * ICHRG, IEOC_PERCENTAGE, VOREG and boost output voltage are mandatory
	 * parameters.
	 */
	ret = device_property_पढ़ो_u32(dev, "richtek,output-charge-current",
				       ichrg);
	अगर (ret) अणु
		dev_err(dev, "Error: missing \"output-charge-current\" property\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "richtek,end-of-charge-percentage",
				       ieoc_percentage);
	अगर (ret) अणु
		dev_err(dev, "Error: missing \"end-of-charge-percentage\" property\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev,
				       "richtek,battery-regulation-voltage",
				       &info->voreg);
	अगर (ret) अणु
		dev_err(dev, "Error: missing \"battery-regulation-voltage\" property\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "richtek,boost-output-voltage",
				       &info->boost_voltage);
	अगर (ret) अणु
		dev_err(dev, "Error: missing \"boost-output-voltage\" property\n");
		वापस ret;
	पूर्ण

	/*
	 * MIVR and IAICR are optional parameters. Do not वापस error अगर one of
	 * them is not present in ACPI table or device tree specअगरication.
	 */
	device_property_पढ़ो_u32(dev, "richtek,min-input-voltage-regulation",
				 mivr);
	device_property_पढ़ो_u32(dev, "richtek,avg-input-current-regulation",
				 iaicr);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_USB_PHY)
अटल पूर्णांक rt9455_usb_event_none(काष्ठा rt9455_info *info,
				 u8 opa_mode, u8 iaicr)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	अगर (opa_mode == RT9455_BOOST_MODE) अणु
		ret = rt9455_set_voreg_beक्रमe_अक्षरge_mode(info);
		अगर (ret) अणु
			dev_err(dev, "Failed to set VOREG before entering charge mode\n");
			वापस ret;
		पूर्ण
		/*
		 * If the अक्षरger is in boost mode, and it has received
		 * USB_EVENT_NONE, this means the consumer device घातered by the
		 * अक्षरger is not connected anymore.
		 * In this हाल, the अक्षरger goes पूर्णांकo अक्षरge mode.
		 */
		dev_dbg(dev, "USB_EVENT_NONE received, therefore the charger goes into charge mode\n");
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_OPA_MODE],
					 RT9455_CHARGE_MODE);
		अगर (ret) अणु
			dev_err(dev, "Failed to set charger in charge mode\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "USB_EVENT_NONE received, therefore IAICR is set to its minimum value\n");
	अगर (iaicr != RT9455_IAICR_100MA) अणु
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_IAICR],
					 RT9455_IAICR_100MA);
		अगर (ret) अणु
			dev_err(dev, "Failed to set IAICR value\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक rt9455_usb_event_vbus(काष्ठा rt9455_info *info,
				 u8 opa_mode, u8 iaicr)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	अगर (opa_mode == RT9455_BOOST_MODE) अणु
		ret = rt9455_set_voreg_beक्रमe_अक्षरge_mode(info);
		अगर (ret) अणु
			dev_err(dev, "Failed to set VOREG before entering charge mode\n");
			वापस ret;
		पूर्ण
		/*
		 * If the अक्षरger is in boost mode, and it has received
		 * USB_EVENT_VBUS, this means the consumer device घातered by the
		 * अक्षरger is not connected anymore.
		 * In this हाल, the अक्षरger goes पूर्णांकo अक्षरge mode.
		 */
		dev_dbg(dev, "USB_EVENT_VBUS received, therefore the charger goes into charge mode\n");
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_OPA_MODE],
					 RT9455_CHARGE_MODE);
		अगर (ret) अणु
			dev_err(dev, "Failed to set charger in charge mode\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "USB_EVENT_VBUS received, therefore IAICR is set to 500 mA\n");
	अगर (iaicr != RT9455_IAICR_500MA) अणु
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_IAICR],
					 RT9455_IAICR_500MA);
		अगर (ret) अणु
			dev_err(dev, "Failed to set IAICR value\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक rt9455_usb_event_id(काष्ठा rt9455_info *info,
			       u8 opa_mode, u8 iaicr)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	अगर (opa_mode == RT9455_CHARGE_MODE) अणु
		ret = rt9455_set_boost_voltage_beक्रमe_boost_mode(info);
		अगर (ret) अणु
			dev_err(dev, "Failed to set boost output voltage before entering boost mode\n");
			वापस ret;
		पूर्ण
		/*
		 * If the अक्षरger is in अक्षरge mode, and it has received
		 * USB_EVENT_ID, this means a consumer device is connected and
		 * it should be घातered by the अक्षरger.
		 * In this हाल, the अक्षरger goes पूर्णांकo boost mode.
		 */
		dev_dbg(dev, "USB_EVENT_ID received, therefore the charger goes into boost mode\n");
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_OPA_MODE],
					 RT9455_BOOST_MODE);
		अगर (ret) अणु
			dev_err(dev, "Failed to set charger in boost mode\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "USB_EVENT_ID received, therefore IAICR is set to its minimum value\n");
	अगर (iaicr != RT9455_IAICR_100MA) अणु
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_IAICR],
					 RT9455_IAICR_100MA);
		अगर (ret) अणु
			dev_err(dev, "Failed to set IAICR value\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक rt9455_usb_event_अक्षरger(काष्ठा rt9455_info *info,
				    u8 opa_mode, u8 iaicr)
अणु
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	अगर (opa_mode == RT9455_BOOST_MODE) अणु
		ret = rt9455_set_voreg_beक्रमe_अक्षरge_mode(info);
		अगर (ret) अणु
			dev_err(dev, "Failed to set VOREG before entering charge mode\n");
			वापस ret;
		पूर्ण
		/*
		 * If the अक्षरger is in boost mode, and it has received
		 * USB_EVENT_CHARGER, this means the consumer device घातered by
		 * the अक्षरger is not connected anymore.
		 * In this हाल, the अक्षरger goes पूर्णांकo अक्षरge mode.
		 */
		dev_dbg(dev, "USB_EVENT_CHARGER received, therefore the charger goes into charge mode\n");
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_OPA_MODE],
					 RT9455_CHARGE_MODE);
		अगर (ret) अणु
			dev_err(dev, "Failed to set charger in charge mode\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "USB_EVENT_CHARGER received, therefore IAICR is set to no current limit\n");
	अगर (iaicr != RT9455_IAICR_NO_LIMIT) अणु
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_IAICR],
					 RT9455_IAICR_NO_LIMIT);
		अगर (ret) अणु
			dev_err(dev, "Failed to set IAICR value\n");
			वापस NOTIFY_DONE;
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक rt9455_usb_event(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ event, व्योम *घातer)
अणु
	काष्ठा rt9455_info *info = container_of(nb, काष्ठा rt9455_info, nb);
	काष्ठा device *dev = &info->client->dev;
	अचिन्हित पूर्णांक opa_mode, iaicr;
	पूर्णांक ret;

	/*
	 * Determine whether the अक्षरger is in अक्षरge mode
	 * or in boost mode.
	 */
	ret = regmap_field_पढ़ो(info->regmap_fields[F_OPA_MODE],
				&opa_mode);
	अगर (ret) अणु
		dev_err(dev, "Failed to read OPA_MODE value\n");
		वापस NOTIFY_DONE;
	पूर्ण

	ret = regmap_field_पढ़ो(info->regmap_fields[F_IAICR],
				&iaicr);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IAICR value\n");
		वापस NOTIFY_DONE;
	पूर्ण

	dev_dbg(dev, "Received USB event %lu\n", event);
	चयन (event) अणु
	हाल USB_EVENT_NONE:
		वापस rt9455_usb_event_none(info, opa_mode, iaicr);
	हाल USB_EVENT_VBUS:
		वापस rt9455_usb_event_vbus(info, opa_mode, iaicr);
	हाल USB_EVENT_ID:
		वापस rt9455_usb_event_id(info, opa_mode, iaicr);
	हाल USB_EVENT_CHARGER:
		वापस rt9455_usb_event_अक्षरger(info, opa_mode, iaicr);
	शेष:
		dev_err(dev, "Unknown USB event\n");
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर

अटल व्योम rt9455_pwr_rdy_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt9455_info *info = container_of(work, काष्ठा rt9455_info,
						pwr_rdy_work.work);
	काष्ठा device *dev = &info->client->dev;
	अचिन्हित पूर्णांक pwr_rdy;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(info->regmap_fields[F_PWR_RDY], &pwr_rdy);
	अगर (ret) अणु
		dev_err(dev, "Failed to read PWR_RDY bit\n");
		वापस;
	पूर्ण
	चयन (pwr_rdy) अणु
	हाल RT9455_PWR_FAULT:
		dev_dbg(dev, "Charger disconnected from power source\n");
		cancel_delayed_work_sync(&info->max_अक्षरging_समय_work);
		अवरोध;
	हाल RT9455_PWR_GOOD:
		dev_dbg(dev, "Charger connected to power source\n");
		ret = regmap_field_ग_लिखो(info->regmap_fields[F_CHG_EN],
					 RT9455_CHARGE_ENABLE);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable charging\n");
			वापस;
		पूर्ण
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &info->max_अक्षरging_समय_work,
				   RT9455_MAX_CHARGING_TIME * HZ);
		अवरोध;
	पूर्ण
	/*
	 * Notअगरy userspace that the अक्षरger has been either connected to or
	 * disconnected from the घातer source.
	 */
	घातer_supply_changed(info->अक्षरger);
पूर्ण

अटल व्योम rt9455_max_अक्षरging_समय_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt9455_info *info = container_of(work, काष्ठा rt9455_info,
						max_अक्षरging_समय_work.work);
	काष्ठा device *dev = &info->client->dev;
	पूर्णांक ret;

	dev_err(dev, "Battery has been charging for at least 6 hours and is not yet fully charged. Battery is dead, therefore charging is disabled.\n");
	ret = regmap_field_ग_लिखो(info->regmap_fields[F_CHG_EN],
				 RT9455_CHARGE_DISABLE);
	अगर (ret)
		dev_err(dev, "Failed to disable charging\n");
पूर्ण

अटल व्योम rt9455_batt_presence_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt9455_info *info = container_of(work, काष्ठा rt9455_info,
						batt_presence_work.work);
	काष्ठा device *dev = &info->client->dev;
	अचिन्हित पूर्णांक irq1, mask1;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, RT9455_REG_IRQ1, &irq1);
	अगर (ret) अणु
		dev_err(dev, "Failed to read IRQ1 register\n");
		वापस;
	पूर्ण

	/*
	 * If the battery is still असलent, batt_presence_work is rescheduled.
	 * Otherwise, max_अक्षरging_समय is scheduled.
	 */
	अगर (irq1 & GET_MASK(F_BATAB)) अणु
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &info->batt_presence_work,
				   RT9455_BATT_PRESENCE_DELAY * HZ);
	पूर्ण अन्यथा अणु
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &info->max_अक्षरging_समय_work,
				   RT9455_MAX_CHARGING_TIME * HZ);

		ret = regmap_पढ़ो(info->regmap, RT9455_REG_MASK1, &mask1);
		अगर (ret) अणु
			dev_err(dev, "Failed to read MASK1 register\n");
			वापस;
		पूर्ण

		अगर (mask1 & GET_MASK(F_BATABM)) अणु
			ret = regmap_field_ग_लिखो(info->regmap_fields[F_BATABM],
						 0x00);
			अगर (ret)
				dev_err(dev, "Failed to unmask BATAB interrupt\n");
		पूर्ण
		/*
		 * Notअगरy userspace that the battery is now connected to the
		 * अक्षरger.
		 */
		घातer_supply_changed(info->अक्षरger);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc rt9455_अक्षरger_desc = अणु
	.name			= RT9455_DRIVER_NAME,
	.type			= POWER_SUPPLY_TYPE_USB,
	.properties		= rt9455_अक्षरger_properties,
	.num_properties		= ARRAY_SIZE(rt9455_अक्षरger_properties),
	.get_property		= rt9455_अक्षरger_get_property,
पूर्ण;

अटल bool rt9455_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT9455_REG_DEV_ID:
	हाल RT9455_REG_IRQ1:
	हाल RT9455_REG_IRQ2:
	हाल RT9455_REG_IRQ3:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool rt9455_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RT9455_REG_DEV_ID:
	हाल RT9455_REG_CTRL5:
	हाल RT9455_REG_CTRL6:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rt9455_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.ग_लिखोable_reg	= rt9455_is_ग_लिखोable_reg,
	.अस्थिर_reg	= rt9455_is_अस्थिर_reg,
	.max_रेजिस्टर	= RT9455_REG_MASK3,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक rt9455_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा rt9455_info *info;
	काष्ठा घातer_supply_config rt9455_अक्षरger_config = अणुपूर्ण;
	/*
	 * Mandatory device-specअगरic data values. Also, VOREG and boost output
	 * voltage are mandatory values, but they are stored in rt9455_info
	 * काष्ठाure.
	 */
	u32 ichrg, ieoc_percentage;
	/* Optional device-specअगरic data values. */
	u32 mivr = -1, iaicr = -1;
	पूर्णांक i, ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(dev, "No support for SMBUS_BYTE_DATA\n");
		वापस -ENODEV;
	पूर्ण
	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->client = client;
	i2c_set_clientdata(client, info);

	info->regmap = devm_regmap_init_i2c(client,
					    &rt9455_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		dev_err(dev, "Failed to initialize register map\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < F_MAX_FIELDS; i++) अणु
		info->regmap_fields[i] =
			devm_regmap_field_alloc(dev, info->regmap,
						rt9455_reg_fields[i]);
		अगर (IS_ERR(info->regmap_fields[i])) अणु
			dev_err(dev,
				"Failed to allocate regmap field = %d\n", i);
			वापस PTR_ERR(info->regmap_fields[i]);
		पूर्ण
	पूर्ण

	ret = rt9455_discover_अक्षरger(info, &ichrg, &ieoc_percentage,
				      &mivr, &iaicr);
	अगर (ret) अणु
		dev_err(dev, "Failed to discover charger\n");
		वापस ret;
	पूर्ण

#अगर IS_ENABLED(CONFIG_USB_PHY)
	info->usb_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	अगर (IS_ERR(info->usb_phy)) अणु
		dev_err(dev, "Failed to get USB transceiver\n");
	पूर्ण अन्यथा अणु
		info->nb.notअगरier_call = rt9455_usb_event;
		ret = usb_रेजिस्टर_notअगरier(info->usb_phy, &info->nb);
		अगर (ret) अणु
			dev_err(dev, "Failed to register USB notifier\n");
			/*
			 * If usb_रेजिस्टर_notअगरier() fails, set notअगरier_call
			 * to शून्य, to aव्योम calling usb_unरेजिस्टर_notअगरier().
			 */
			info->nb.notअगरier_call = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	INIT_DEFERRABLE_WORK(&info->pwr_rdy_work, rt9455_pwr_rdy_work_callback);
	INIT_DEFERRABLE_WORK(&info->max_अक्षरging_समय_work,
			     rt9455_max_अक्षरging_समय_work_callback);
	INIT_DEFERRABLE_WORK(&info->batt_presence_work,
			     rt9455_batt_presence_work_callback);

	rt9455_अक्षरger_config.of_node		= dev->of_node;
	rt9455_अक्षरger_config.drv_data		= info;
	rt9455_अक्षरger_config.supplied_to	= rt9455_अक्षरger_supplied_to;
	rt9455_अक्षरger_config.num_supplicants	=
					ARRAY_SIZE(rt9455_अक्षरger_supplied_to);
	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					rt9455_irq_handler_thपढ़ो,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					RT9455_DRIVER_NAME, info);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IRQ handler\n");
		जाओ put_usb_notअगरier;
	पूर्ण

	ret = rt9455_hw_init(info, ichrg, ieoc_percentage, mivr, iaicr);
	अगर (ret) अणु
		dev_err(dev, "Failed to set charger to its default values\n");
		जाओ put_usb_notअगरier;
	पूर्ण

	info->अक्षरger = devm_घातer_supply_रेजिस्टर(dev, &rt9455_अक्षरger_desc,
						   &rt9455_अक्षरger_config);
	अगर (IS_ERR(info->अक्षरger)) अणु
		dev_err(dev, "Failed to register charger\n");
		ret = PTR_ERR(info->अक्षरger);
		जाओ put_usb_notअगरier;
	पूर्ण

	वापस 0;

put_usb_notअगरier:
#अगर IS_ENABLED(CONFIG_USB_PHY)
	अगर (info->nb.notअगरier_call)  अणु
		usb_unरेजिस्टर_notअगरier(info->usb_phy, &info->nb);
		info->nb.notअगरier_call = शून्य;
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक rt9455_हटाओ(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा rt9455_info *info = i2c_get_clientdata(client);

	ret = rt9455_रेजिस्टर_reset(info);
	अगर (ret)
		dev_err(&info->client->dev, "Failed to set charger to its default values\n");

#अगर IS_ENABLED(CONFIG_USB_PHY)
	अगर (info->nb.notअगरier_call)
		usb_unरेजिस्टर_notअगरier(info->usb_phy, &info->nb);
#पूर्ण_अगर

	cancel_delayed_work_sync(&info->pwr_rdy_work);
	cancel_delayed_work_sync(&info->max_अक्षरging_समय_work);
	cancel_delayed_work_sync(&info->batt_presence_work);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rt9455_i2c_id_table[] = अणु
	अणु RT9455_DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt9455_i2c_id_table);

अटल स्थिर काष्ठा of_device_id rt9455_of_match[] = अणु
	अणु .compatible = "richtek,rt9455", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt9455_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt9455_i2c_acpi_match[] = अणु
	अणु "RT945500", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt9455_i2c_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver rt9455_driver = अणु
	.probe		= rt9455_probe,
	.हटाओ		= rt9455_हटाओ,
	.id_table	= rt9455_i2c_id_table,
	.driver = अणु
		.name		= RT9455_DRIVER_NAME,
		.of_match_table	= of_match_ptr(rt9455_of_match),
		.acpi_match_table = ACPI_PTR(rt9455_i2c_acpi_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(rt9455_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anda-Maria Nicolae <anda-maria.nicolae@intel.com>");
MODULE_DESCRIPTION("Richtek RT9455 Charger Driver");
