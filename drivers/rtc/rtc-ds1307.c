<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rtc-ds1307.c - RTC driver क्रम some mostly-compatible I2C chips.
 *
 *  Copyright (C) 2005 James Chapman (ds1337 core)
 *  Copyright (C) 2006 David Brownell
 *  Copyright (C) 2009 Matthias Fuchs (rx8025 support)
 *  Copyright (C) 2012 Bertअक्रम Aअक्षरd (nvram access fixes)
 */

#समावेश <linux/bcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/rtc/ds1307.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

/*
 * We can't determine type by probing, but अगर we expect pre-Linux code
 * to have set the chip up as a घड़ी (turning on the oscillator and
 * setting the date and समय), Linux can ignore the non-घड़ी features.
 * That's a natural job क्रम a factory or repair bench.
 */
क्रमागत ds_type अणु
	unknown_ds_type, /* always first and 0 */
	ds_1307,
	ds_1308,
	ds_1337,
	ds_1338,
	ds_1339,
	ds_1340,
	ds_1341,
	ds_1388,
	ds_3231,
	m41t0,
	m41t00,
	m41t11,
	mcp794xx,
	rx_8025,
	rx_8130,
	last_ds_type /* always last */
	/* rs5c372 too?  dअगरferent address... */
पूर्ण;

/* RTC रेजिस्टरs करोn't dअगरfer much, except क्रम the century flag */
#घोषणा DS1307_REG_SECS		0x00	/* 00-59 */
#	define DS1307_BIT_CH		0x80
#	define DS1340_BIT_nEOSC		0x80
#	define MCP794XX_BIT_ST		0x80
#घोषणा DS1307_REG_MIN		0x01	/* 00-59 */
#	define M41T0_BIT_OF		0x80
#घोषणा DS1307_REG_HOUR		0x02	/* 00-23, or 1-12अणुam,pmपूर्ण */
#	define DS1307_BIT_12HR		0x40	/* in REG_HOUR */
#	define DS1307_BIT_PM		0x20	/* in REG_HOUR */
#	define DS1340_BIT_CENTURY_EN	0x80	/* in REG_HOUR */
#	define DS1340_BIT_CENTURY	0x40	/* in REG_HOUR */
#घोषणा DS1307_REG_WDAY		0x03	/* 01-07 */
#	define MCP794XX_BIT_VBATEN	0x08
#घोषणा DS1307_REG_MDAY		0x04	/* 01-31 */
#घोषणा DS1307_REG_MONTH	0x05	/* 01-12 */
#	define DS1337_BIT_CENTURY	0x80	/* in REG_MONTH */
#घोषणा DS1307_REG_YEAR		0x06	/* 00-99 */

/*
 * Other रेजिस्टरs (control, status, alarms, trickle अक्षरge, NVRAM, etc)
 * start at 7, and they dअगरfer a LOT. Only control and status matter क्रम
 * basic RTC date and समय functionality; be careful using them.
 */
#घोषणा DS1307_REG_CONTROL	0x07		/* or ds1338 */
#	define DS1307_BIT_OUT		0x80
#	define DS1338_BIT_OSF		0x20
#	define DS1307_BIT_SQWE		0x10
#	define DS1307_BIT_RS1		0x02
#	define DS1307_BIT_RS0		0x01
#घोषणा DS1337_REG_CONTROL	0x0e
#	define DS1337_BIT_nEOSC		0x80
#	define DS1339_BIT_BBSQI		0x20
#	define DS3231_BIT_BBSQW		0x40 /* same as BBSQI */
#	define DS1337_BIT_RS2		0x10
#	define DS1337_BIT_RS1		0x08
#	define DS1337_BIT_INTCN		0x04
#	define DS1337_BIT_A2IE		0x02
#	define DS1337_BIT_A1IE		0x01
#घोषणा DS1340_REG_CONTROL	0x07
#	define DS1340_BIT_OUT		0x80
#	define DS1340_BIT_FT		0x40
#	define DS1340_BIT_CALIB_SIGN	0x20
#	define DS1340_M_CALIBRATION	0x1f
#घोषणा DS1340_REG_FLAG		0x09
#	define DS1340_BIT_OSF		0x80
#घोषणा DS1337_REG_STATUS	0x0f
#	define DS1337_BIT_OSF		0x80
#	define DS3231_BIT_EN32KHZ	0x08
#	define DS1337_BIT_A2I		0x02
#	define DS1337_BIT_A1I		0x01
#घोषणा DS1339_REG_ALARM1_SECS	0x07

#घोषणा DS13XX_TRICKLE_CHARGER_MAGIC	0xa0

#घोषणा RX8025_REG_CTRL1	0x0e
#	define RX8025_BIT_2412		0x20
#घोषणा RX8025_REG_CTRL2	0x0f
#	define RX8025_BIT_PON		0x10
#	define RX8025_BIT_VDET		0x40
#	define RX8025_BIT_XST		0x20

#घोषणा RX8130_REG_ALARM_MIN		0x17
#घोषणा RX8130_REG_ALARM_HOUR		0x18
#घोषणा RX8130_REG_ALARM_WEEK_OR_DAY	0x19
#घोषणा RX8130_REG_EXTENSION		0x1c
#घोषणा RX8130_REG_EXTENSION_WADA	BIT(3)
#घोषणा RX8130_REG_FLAG			0x1d
#घोषणा RX8130_REG_FLAG_VLF		BIT(1)
#घोषणा RX8130_REG_FLAG_AF		BIT(3)
#घोषणा RX8130_REG_CONTROL0		0x1e
#घोषणा RX8130_REG_CONTROL0_AIE		BIT(3)
#घोषणा RX8130_REG_CONTROL1		0x1f
#घोषणा RX8130_REG_CONTROL1_INIEN	BIT(4)
#घोषणा RX8130_REG_CONTROL1_CHGEN	BIT(5)

#घोषणा MCP794XX_REG_CONTROL		0x07
#	define MCP794XX_BIT_ALM0_EN	0x10
#	define MCP794XX_BIT_ALM1_EN	0x20
#घोषणा MCP794XX_REG_ALARM0_BASE	0x0a
#घोषणा MCP794XX_REG_ALARM0_CTRL	0x0d
#घोषणा MCP794XX_REG_ALARM1_BASE	0x11
#घोषणा MCP794XX_REG_ALARM1_CTRL	0x14
#	define MCP794XX_BIT_ALMX_IF	BIT(3)
#	define MCP794XX_BIT_ALMX_C0	BIT(4)
#	define MCP794XX_BIT_ALMX_C1	BIT(5)
#	define MCP794XX_BIT_ALMX_C2	BIT(6)
#	define MCP794XX_BIT_ALMX_POL	BIT(7)
#	define MCP794XX_MSK_ALMX_MATCH	(MCP794XX_BIT_ALMX_C0 | \
					 MCP794XX_BIT_ALMX_C1 | \
					 MCP794XX_BIT_ALMX_C2)

#घोषणा M41TXX_REG_CONTROL	0x07
#	define M41TXX_BIT_OUT		BIT(7)
#	define M41TXX_BIT_FT		BIT(6)
#	define M41TXX_BIT_CALIB_SIGN	BIT(5)
#	define M41TXX_M_CALIBRATION	GENMASK(4, 0)

#घोषणा DS1388_REG_WDOG_HUN_SECS	0x08
#घोषणा DS1388_REG_WDOG_SECS		0x09
#घोषणा DS1388_REG_FLAG			0x0b
#	define DS1388_BIT_WF		BIT(6)
#	define DS1388_BIT_OSF		BIT(7)
#घोषणा DS1388_REG_CONTROL		0x0c
#	define DS1388_BIT_RST		BIT(0)
#	define DS1388_BIT_WDE		BIT(1)
#	define DS1388_BIT_nEOSC		BIT(7)

/* negative offset step is -2.034ppm */
#घोषणा M41TXX_NEG_OFFSET_STEP_PPB	2034
/* positive offset step is +4.068ppm */
#घोषणा M41TXX_POS_OFFSET_STEP_PPB	4068
/* Min and max values supported with 'offset' पूर्णांकerface by M41TXX */
#घोषणा M41TXX_MIN_OFFSET	((-31) * M41TXX_NEG_OFFSET_STEP_PPB)
#घोषणा M41TXX_MAX_OFFSET	((31) * M41TXX_POS_OFFSET_STEP_PPB)

काष्ठा ds1307 अणु
	क्रमागत ds_type		type;
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	स्थिर अक्षर		*name;
	काष्ठा rtc_device	*rtc;
#अगर_घोषित CONFIG_COMMON_CLK
	काष्ठा clk_hw		clks[2];
#पूर्ण_अगर
पूर्ण;

काष्ठा chip_desc अणु
	अचिन्हित		alarm:1;
	u16			nvram_offset;
	u16			nvram_size;
	u8			offset; /* रेजिस्टर's offset */
	u8			century_reg;
	u8			century_enable_bit;
	u8			century_bit;
	u8			bbsqi_bit;
	irq_handler_t		irq_handler;
	स्थिर काष्ठा rtc_class_ops *rtc_ops;
	u16			trickle_अक्षरger_reg;
	u8			(*करो_trickle_setup)(काष्ठा ds1307 *, u32,
						    bool);
	/* Does the RTC require trickle-resistor-ohms to select the value of
	 * the resistor between Vcc and Vbackup?
	 */
	bool			requires_trickle_resistor;
	/* Some RTC's batteries and supercaps were अक्षरged by शेष, others
	 * allow अक्षरging but were not configured previously to करो so.
	 * Remember this behavior to stay backwards compatible.
	 */
	bool			अक्षरge_शेष;
पूर्ण;

अटल स्थिर काष्ठा chip_desc chips[last_ds_type];

अटल पूर्णांक ds1307_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	काष्ठा ds1307	*ds1307 = dev_get_drvdata(dev);
	पूर्णांक		पंचांगp, ret;
	स्थिर काष्ठा chip_desc *chip = &chips[ds1307->type];
	u8 regs[7];

	अगर (ds1307->type == rx_8130) अणु
		अचिन्हित पूर्णांक regflag;
		ret = regmap_पढ़ो(ds1307->regmap, RX8130_REG_FLAG, &regflag);
		अगर (ret) अणु
			dev_err(dev, "%s error %d\n", "read", ret);
			वापस ret;
		पूर्ण

		अगर (regflag & RX8130_REG_FLAG_VLF) अणु
			dev_warn_once(dev, "oscillator failed, set time!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* पढ़ो the RTC date and समय रेजिस्टरs all at once */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, chip->offset, regs,
			       माप(regs));
	अगर (ret) अणु
		dev_err(dev, "%s error %d\n", "read", ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%s: %7ph\n", "read", regs);

	/* अगर oscillator fail bit is set, no data can be trusted */
	अगर (ds1307->type == m41t0 &&
	    regs[DS1307_REG_MIN] & M41T0_BIT_OF) अणु
		dev_warn_once(dev, "oscillator failed, set time!\n");
		वापस -EINVAL;
	पूर्ण

	पंचांगp = regs[DS1307_REG_SECS];
	चयन (ds1307->type) अणु
	हाल ds_1307:
	हाल m41t0:
	हाल m41t00:
	हाल m41t11:
		अगर (पंचांगp & DS1307_BIT_CH)
			वापस -EINVAL;
		अवरोध;
	हाल ds_1308:
	हाल ds_1338:
		अगर (पंचांगp & DS1307_BIT_CH)
			वापस -EINVAL;

		ret = regmap_पढ़ो(ds1307->regmap, DS1307_REG_CONTROL, &पंचांगp);
		अगर (ret)
			वापस ret;
		अगर (पंचांगp & DS1338_BIT_OSF)
			वापस -EINVAL;
		अवरोध;
	हाल ds_1340:
		अगर (पंचांगp & DS1340_BIT_nEOSC)
			वापस -EINVAL;

		ret = regmap_पढ़ो(ds1307->regmap, DS1340_REG_FLAG, &पंचांगp);
		अगर (ret)
			वापस ret;
		अगर (पंचांगp & DS1340_BIT_OSF)
			वापस -EINVAL;
		अवरोध;
	हाल ds_1388:
		ret = regmap_पढ़ो(ds1307->regmap, DS1388_REG_FLAG, &पंचांगp);
		अगर (ret)
			वापस ret;
		अगर (पंचांगp & DS1388_BIT_OSF)
			वापस -EINVAL;
		अवरोध;
	हाल mcp794xx:
		अगर (!(पंचांगp & MCP794XX_BIT_ST))
			वापस -EINVAL;

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	t->पंचांग_sec = bcd2bin(regs[DS1307_REG_SECS] & 0x7f);
	t->पंचांग_min = bcd2bin(regs[DS1307_REG_MIN] & 0x7f);
	पंचांगp = regs[DS1307_REG_HOUR] & 0x3f;
	t->पंचांग_hour = bcd2bin(पंचांगp);
	/* rx8130 is bit position, not BCD */
	अगर (ds1307->type == rx_8130)
		t->पंचांग_wday = fls(regs[DS1307_REG_WDAY] & 0x7f);
	अन्यथा
		t->पंचांग_wday = bcd2bin(regs[DS1307_REG_WDAY] & 0x07) - 1;
	t->पंचांग_mday = bcd2bin(regs[DS1307_REG_MDAY] & 0x3f);
	पंचांगp = regs[DS1307_REG_MONTH] & 0x1f;
	t->पंचांग_mon = bcd2bin(पंचांगp) - 1;
	t->पंचांग_year = bcd2bin(regs[DS1307_REG_YEAR]) + 100;

	अगर (regs[chip->century_reg] & chip->century_bit &&
	    IS_ENABLED(CONFIG_RTC_DRV_DS1307_CENTURY))
		t->पंचांग_year += 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"read", t->पंचांग_sec, t->पंचांग_min,
		t->पंचांग_hour, t->पंचांग_mday,
		t->पंचांग_mon, t->पंचांग_year, t->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1307_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *t)
अणु
	काष्ठा ds1307	*ds1307 = dev_get_drvdata(dev);
	स्थिर काष्ठा chip_desc *chip = &chips[ds1307->type];
	पूर्णांक		result;
	पूर्णांक		पंचांगp;
	u8		regs[7];

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", t->पंचांग_sec, t->पंचांग_min,
		t->पंचांग_hour, t->पंचांग_mday,
		t->पंचांग_mon, t->पंचांग_year, t->पंचांग_wday);

	अगर (t->पंचांग_year < 100)
		वापस -EINVAL;

#अगर_घोषित CONFIG_RTC_DRV_DS1307_CENTURY
	अगर (t->पंचांग_year > (chip->century_bit ? 299 : 199))
		वापस -EINVAL;
#अन्यथा
	अगर (t->पंचांग_year > 199)
		वापस -EINVAL;
#पूर्ण_अगर

	regs[DS1307_REG_SECS] = bin2bcd(t->पंचांग_sec);
	regs[DS1307_REG_MIN] = bin2bcd(t->पंचांग_min);
	regs[DS1307_REG_HOUR] = bin2bcd(t->पंचांग_hour);
	/* rx8130 is bit position, not BCD */
	अगर (ds1307->type == rx_8130)
		regs[DS1307_REG_WDAY] = 1 << t->पंचांग_wday;
	अन्यथा
		regs[DS1307_REG_WDAY] = bin2bcd(t->पंचांग_wday + 1);
	regs[DS1307_REG_MDAY] = bin2bcd(t->पंचांग_mday);
	regs[DS1307_REG_MONTH] = bin2bcd(t->पंचांग_mon + 1);

	/* assume 20YY not 19YY */
	पंचांगp = t->पंचांग_year - 100;
	regs[DS1307_REG_YEAR] = bin2bcd(पंचांगp);

	अगर (chip->century_enable_bit)
		regs[chip->century_reg] |= chip->century_enable_bit;
	अगर (t->पंचांग_year > 199 && chip->century_bit)
		regs[chip->century_reg] |= chip->century_bit;

	चयन (ds1307->type) अणु
	हाल ds_1308:
	हाल ds_1338:
		regmap_update_bits(ds1307->regmap, DS1307_REG_CONTROL,
				   DS1338_BIT_OSF, 0);
		अवरोध;
	हाल ds_1340:
		regmap_update_bits(ds1307->regmap, DS1340_REG_FLAG,
				   DS1340_BIT_OSF, 0);
		अवरोध;
	हाल ds_1388:
		regmap_update_bits(ds1307->regmap, DS1388_REG_FLAG,
				   DS1388_BIT_OSF, 0);
		अवरोध;
	हाल mcp794xx:
		/*
		 * these bits were cleared when preparing the date/समय
		 * values and need to be set again beक्रमe writing the
		 * regsfer out to the device.
		 */
		regs[DS1307_REG_SECS] |= MCP794XX_BIT_ST;
		regs[DS1307_REG_WDAY] |= MCP794XX_BIT_VBATEN;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(dev, "%s: %7ph\n", "write", regs);

	result = regmap_bulk_ग_लिखो(ds1307->regmap, chip->offset, regs,
				   माप(regs));
	अगर (result) अणु
		dev_err(dev, "%s error %d\n", "write", result);
		वापस result;
	पूर्ण

	अगर (ds1307->type == rx_8130) अणु
		/* clear Voltage Loss Flag as data is available now */
		result = regmap_ग_लिखो(ds1307->regmap, RX8130_REG_FLAG,
				      ~(u8)RX8130_REG_FLAG_VLF);
		अगर (result) अणु
			dev_err(dev, "%s error %d\n", "write", result);
			वापस result;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds1337_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा ds1307		*ds1307 = dev_get_drvdata(dev);
	पूर्णांक			ret;
	u8			regs[9];

	/* पढ़ो all ALARM1, ALARM2, and status रेजिस्टरs at once */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, DS1339_REG_ALARM1_SECS,
			       regs, माप(regs));
	अगर (ret) अणु
		dev_err(dev, "%s error %d\n", "alarm read", ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%s: %4ph, %3ph, %2ph\n", "alarm read",
		&regs[0], &regs[4], &regs[7]);

	/*
	 * report alarm समय (ALARM1); assume 24 hour and day-of-month modes,
	 * and that all four fields are checked matches
	 */
	t->समय.पंचांग_sec = bcd2bin(regs[0] & 0x7f);
	t->समय.पंचांग_min = bcd2bin(regs[1] & 0x7f);
	t->समय.पंचांग_hour = bcd2bin(regs[2] & 0x3f);
	t->समय.पंचांग_mday = bcd2bin(regs[3] & 0x3f);

	/* ... and status */
	t->enabled = !!(regs[7] & DS1337_BIT_A1IE);
	t->pending = !!(regs[8] & DS1337_BIT_A1I);

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, enabled=%d, pending=%d\n",
		"alarm read", t->समय.पंचांग_sec, t->समय.पंचांग_min,
		t->समय.पंचांग_hour, t->समय.पंचांग_mday,
		t->enabled, t->pending);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1337_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा ds1307		*ds1307 = dev_get_drvdata(dev);
	अचिन्हित अक्षर		regs[9];
	u8			control, status;
	पूर्णांक			ret;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, enabled=%d, pending=%d\n",
		"alarm set", t->समय.पंचांग_sec, t->समय.पंचांग_min,
		t->समय.पंचांग_hour, t->समय.पंचांग_mday,
		t->enabled, t->pending);

	/* पढ़ो current status of both alarms and the chip */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, DS1339_REG_ALARM1_SECS, regs,
			       माप(regs));
	अगर (ret) अणु
		dev_err(dev, "%s error %d\n", "alarm write", ret);
		वापस ret;
	पूर्ण
	control = regs[7];
	status = regs[8];

	dev_dbg(dev, "%s: %4ph, %3ph, %02x %02x\n", "alarm set (old status)",
		&regs[0], &regs[4], control, status);

	/* set ALARM1, using 24 hour and day-of-month modes */
	regs[0] = bin2bcd(t->समय.पंचांग_sec);
	regs[1] = bin2bcd(t->समय.पंचांग_min);
	regs[2] = bin2bcd(t->समय.पंचांग_hour);
	regs[3] = bin2bcd(t->समय.पंचांग_mday);

	/* set ALARM2 to non-garbage */
	regs[4] = 0;
	regs[5] = 0;
	regs[6] = 0;

	/* disable alarms */
	regs[7] = control & ~(DS1337_BIT_A1IE | DS1337_BIT_A2IE);
	regs[8] = status & ~(DS1337_BIT_A1I | DS1337_BIT_A2I);

	ret = regmap_bulk_ग_लिखो(ds1307->regmap, DS1339_REG_ALARM1_SECS, regs,
				माप(regs));
	अगर (ret) अणु
		dev_err(dev, "can't set alarm time\n");
		वापस ret;
	पूर्ण

	/* optionally enable ALARM1 */
	अगर (t->enabled) अणु
		dev_dbg(dev, "alarm IRQ armed\n");
		regs[7] |= DS1337_BIT_A1IE;	/* only ALARM1 is used */
		regmap_ग_लिखो(ds1307->regmap, DS1337_REG_CONTROL, regs[7]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds1307_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1307		*ds1307 = dev_get_drvdata(dev);

	वापस regmap_update_bits(ds1307->regmap, DS1337_REG_CONTROL,
				  DS1337_BIT_A1IE,
				  enabled ? DS1337_BIT_A1IE : 0);
पूर्ण

अटल u8 करो_trickle_setup_ds1339(काष्ठा ds1307 *ds1307, u32 ohms, bool diode)
अणु
	u8 setup = (diode) ? DS1307_TRICKLE_CHARGER_DIODE :
		DS1307_TRICKLE_CHARGER_NO_DIODE;

	setup |= DS13XX_TRICKLE_CHARGER_MAGIC;

	चयन (ohms) अणु
	हाल 250:
		setup |= DS1307_TRICKLE_CHARGER_250_OHM;
		अवरोध;
	हाल 2000:
		setup |= DS1307_TRICKLE_CHARGER_2K_OHM;
		अवरोध;
	हाल 4000:
		setup |= DS1307_TRICKLE_CHARGER_4K_OHM;
		अवरोध;
	शेष:
		dev_warn(ds1307->dev,
			 "Unsupported ohm value %u in dt\n", ohms);
		वापस 0;
	पूर्ण
	वापस setup;
पूर्ण

अटल u8 करो_trickle_setup_rx8130(काष्ठा ds1307 *ds1307, u32 ohms, bool diode)
अणु
	/* make sure that the backup battery is enabled */
	u8 setup = RX8130_REG_CONTROL1_INIEN;
	अगर (diode)
		setup |= RX8130_REG_CONTROL1_CHGEN;

	वापस setup;
पूर्ण

अटल irqवापस_t rx8130_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ds1307           *ds1307 = dev_id;
	u8 ctl[3];
	पूर्णांक ret;

	rtc_lock(ds1307->rtc);

	/* Read control रेजिस्टरs. */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, RX8130_REG_EXTENSION, ctl,
			       माप(ctl));
	अगर (ret < 0)
		जाओ out;
	अगर (!(ctl[1] & RX8130_REG_FLAG_AF))
		जाओ out;
	ctl[1] &= ~RX8130_REG_FLAG_AF;
	ctl[2] &= ~RX8130_REG_CONTROL0_AIE;

	ret = regmap_bulk_ग_लिखो(ds1307->regmap, RX8130_REG_EXTENSION, ctl,
				माप(ctl));
	अगर (ret < 0)
		जाओ out;

	rtc_update_irq(ds1307->rtc, 1, RTC_AF | RTC_IRQF);

out:
	rtc_unlock(ds1307->rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rx8130_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	u8 ald[3], ctl[3];
	पूर्णांक ret;

	/* Read alarm रेजिस्टरs. */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, RX8130_REG_ALARM_MIN, ald,
			       माप(ald));
	अगर (ret < 0)
		वापस ret;

	/* Read control रेजिस्टरs. */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, RX8130_REG_EXTENSION, ctl,
			       माप(ctl));
	अगर (ret < 0)
		वापस ret;

	t->enabled = !!(ctl[2] & RX8130_REG_CONTROL0_AIE);
	t->pending = !!(ctl[1] & RX8130_REG_FLAG_AF);

	/* Report alarm 0 समय assuming 24-hour and day-of-month modes. */
	t->समय.पंचांग_sec = -1;
	t->समय.पंचांग_min = bcd2bin(ald[0] & 0x7f);
	t->समय.पंचांग_hour = bcd2bin(ald[1] & 0x7f);
	t->समय.पंचांग_wday = -1;
	t->समय.पंचांग_mday = bcd2bin(ald[2] & 0x7f);
	t->समय.पंचांग_mon = -1;
	t->समय.पंचांग_year = -1;
	t->समय.पंचांग_yday = -1;
	t->समय.पंचांग_isdst = -1;

	dev_dbg(dev, "%s, sec=%d min=%d hour=%d wday=%d mday=%d mon=%d enabled=%d\n",
		__func__, t->समय.पंचांग_sec, t->समय.पंचांग_min, t->समय.पंचांग_hour,
		t->समय.पंचांग_wday, t->समय.पंचांग_mday, t->समय.पंचांग_mon, t->enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक rx8130_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	u8 ald[3], ctl[3];
	पूर्णांक ret;

	dev_dbg(dev, "%s, sec=%d min=%d hour=%d wday=%d mday=%d mon=%d "
		"enabled=%d pending=%d\n", __func__,
		t->समय.पंचांग_sec, t->समय.पंचांग_min, t->समय.पंचांग_hour,
		t->समय.पंचांग_wday, t->समय.पंचांग_mday, t->समय.पंचांग_mon,
		t->enabled, t->pending);

	/* Read control रेजिस्टरs. */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, RX8130_REG_EXTENSION, ctl,
			       माप(ctl));
	अगर (ret < 0)
		वापस ret;

	ctl[0] &= RX8130_REG_EXTENSION_WADA;
	ctl[1] &= ~RX8130_REG_FLAG_AF;
	ctl[2] &= ~RX8130_REG_CONTROL0_AIE;

	ret = regmap_bulk_ग_लिखो(ds1307->regmap, RX8130_REG_EXTENSION, ctl,
				माप(ctl));
	अगर (ret < 0)
		वापस ret;

	/* Hardware alarm precision is 1 minute! */
	ald[0] = bin2bcd(t->समय.पंचांग_min);
	ald[1] = bin2bcd(t->समय.पंचांग_hour);
	ald[2] = bin2bcd(t->समय.पंचांग_mday);

	ret = regmap_bulk_ग_लिखो(ds1307->regmap, RX8130_REG_ALARM_MIN, ald,
				माप(ald));
	अगर (ret < 0)
		वापस ret;

	अगर (!t->enabled)
		वापस 0;

	ctl[2] |= RX8130_REG_CONTROL0_AIE;

	वापस regmap_ग_लिखो(ds1307->regmap, RX8130_REG_CONTROL0, ctl[2]);
पूर्ण

अटल पूर्णांक rx8130_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	पूर्णांक ret, reg;

	ret = regmap_पढ़ो(ds1307->regmap, RX8130_REG_CONTROL0, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (enabled)
		reg |= RX8130_REG_CONTROL0_AIE;
	अन्यथा
		reg &= ~RX8130_REG_CONTROL0_AIE;

	वापस regmap_ग_लिखो(ds1307->regmap, RX8130_REG_CONTROL0, reg);
पूर्ण

अटल irqवापस_t mcp794xx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ds1307           *ds1307 = dev_id;
	काष्ठा mutex            *lock = &ds1307->rtc->ops_lock;
	पूर्णांक reg, ret;

	mutex_lock(lock);

	/* Check and clear alarm 0 पूर्णांकerrupt flag. */
	ret = regmap_पढ़ो(ds1307->regmap, MCP794XX_REG_ALARM0_CTRL, &reg);
	अगर (ret)
		जाओ out;
	अगर (!(reg & MCP794XX_BIT_ALMX_IF))
		जाओ out;
	reg &= ~MCP794XX_BIT_ALMX_IF;
	ret = regmap_ग_लिखो(ds1307->regmap, MCP794XX_REG_ALARM0_CTRL, reg);
	अगर (ret)
		जाओ out;

	/* Disable alarm 0. */
	ret = regmap_update_bits(ds1307->regmap, MCP794XX_REG_CONTROL,
				 MCP794XX_BIT_ALM0_EN, 0);
	अगर (ret)
		जाओ out;

	rtc_update_irq(ds1307->rtc, 1, RTC_AF | RTC_IRQF);

out:
	mutex_unlock(lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mcp794xx_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	u8 regs[10];
	पूर्णांक ret;

	/* Read control and alarm 0 रेजिस्टरs. */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, MCP794XX_REG_CONTROL, regs,
			       माप(regs));
	अगर (ret)
		वापस ret;

	t->enabled = !!(regs[0] & MCP794XX_BIT_ALM0_EN);

	/* Report alarm 0 समय assuming 24-hour and day-of-month modes. */
	t->समय.पंचांग_sec = bcd2bin(regs[3] & 0x7f);
	t->समय.पंचांग_min = bcd2bin(regs[4] & 0x7f);
	t->समय.पंचांग_hour = bcd2bin(regs[5] & 0x3f);
	t->समय.पंचांग_wday = bcd2bin(regs[6] & 0x7) - 1;
	t->समय.पंचांग_mday = bcd2bin(regs[7] & 0x3f);
	t->समय.पंचांग_mon = bcd2bin(regs[8] & 0x1f) - 1;
	t->समय.पंचांग_year = -1;
	t->समय.पंचांग_yday = -1;
	t->समय.पंचांग_isdst = -1;

	dev_dbg(dev, "%s, sec=%d min=%d hour=%d wday=%d mday=%d mon=%d "
		"enabled=%d polarity=%d irq=%d match=%lu\n", __func__,
		t->समय.पंचांग_sec, t->समय.पंचांग_min, t->समय.पंचांग_hour,
		t->समय.पंचांग_wday, t->समय.पंचांग_mday, t->समय.पंचांग_mon, t->enabled,
		!!(regs[6] & MCP794XX_BIT_ALMX_POL),
		!!(regs[6] & MCP794XX_BIT_ALMX_IF),
		(regs[6] & MCP794XX_MSK_ALMX_MATCH) >> 4);

	वापस 0;
पूर्ण

/*
 * We may have a अक्रमom RTC weekday, thereक्रमe calculate alarm weekday based
 * on current weekday we पढ़ो from the RTC समयkeeping regs
 */
अटल पूर्णांक mcp794xx_alm_weekday(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग_alarm)
अणु
	काष्ठा rtc_समय पंचांग_now;
	पूर्णांक days_now, days_alarm, ret;

	ret = ds1307_get_समय(dev, &पंचांग_now);
	अगर (ret)
		वापस ret;

	days_now = भाग_s64(rtc_पंचांग_to_समय64(&पंचांग_now), 24 * 60 * 60);
	days_alarm = भाग_s64(rtc_पंचांग_to_समय64(पंचांग_alarm), 24 * 60 * 60);

	वापस (पंचांग_now.पंचांग_wday + days_alarm - days_now) % 7 + 1;
पूर्ण

अटल पूर्णांक mcp794xx_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	अचिन्हित अक्षर regs[10];
	पूर्णांक wday, ret;

	wday = mcp794xx_alm_weekday(dev, &t->समय);
	अगर (wday < 0)
		वापस wday;

	dev_dbg(dev, "%s, sec=%d min=%d hour=%d wday=%d mday=%d mon=%d "
		"enabled=%d pending=%d\n", __func__,
		t->समय.पंचांग_sec, t->समय.पंचांग_min, t->समय.पंचांग_hour,
		t->समय.पंचांग_wday, t->समय.पंचांग_mday, t->समय.पंचांग_mon,
		t->enabled, t->pending);

	/* Read control and alarm 0 रेजिस्टरs. */
	ret = regmap_bulk_पढ़ो(ds1307->regmap, MCP794XX_REG_CONTROL, regs,
			       माप(regs));
	अगर (ret)
		वापस ret;

	/* Set alarm 0, using 24-hour and day-of-month modes. */
	regs[3] = bin2bcd(t->समय.पंचांग_sec);
	regs[4] = bin2bcd(t->समय.पंचांग_min);
	regs[5] = bin2bcd(t->समय.पंचांग_hour);
	regs[6] = wday;
	regs[7] = bin2bcd(t->समय.पंचांग_mday);
	regs[8] = bin2bcd(t->समय.पंचांग_mon + 1);

	/* Clear the alarm 0 पूर्णांकerrupt flag. */
	regs[6] &= ~MCP794XX_BIT_ALMX_IF;
	/* Set alarm match: second, minute, hour, day, date, month. */
	regs[6] |= MCP794XX_MSK_ALMX_MATCH;
	/* Disable पूर्णांकerrupt. We will not enable until completely programmed */
	regs[0] &= ~MCP794XX_BIT_ALM0_EN;

	ret = regmap_bulk_ग_लिखो(ds1307->regmap, MCP794XX_REG_CONTROL, regs,
				माप(regs));
	अगर (ret)
		वापस ret;

	अगर (!t->enabled)
		वापस 0;
	regs[0] |= MCP794XX_BIT_ALM0_EN;
	वापस regmap_ग_लिखो(ds1307->regmap, MCP794XX_REG_CONTROL, regs[0]);
पूर्ण

अटल पूर्णांक mcp794xx_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);

	वापस regmap_update_bits(ds1307->regmap, MCP794XX_REG_CONTROL,
				  MCP794XX_BIT_ALM0_EN,
				  enabled ? MCP794XX_BIT_ALM0_EN : 0);
पूर्ण

अटल पूर्णांक m41txx_rtc_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ctrl_reg;
	u8 val;

	regmap_पढ़ो(ds1307->regmap, M41TXX_REG_CONTROL, &ctrl_reg);

	val = ctrl_reg & M41TXX_M_CALIBRATION;

	/* check अगर positive */
	अगर (ctrl_reg & M41TXX_BIT_CALIB_SIGN)
		*offset = (val * M41TXX_POS_OFFSET_STEP_PPB);
	अन्यथा
		*offset = -(val * M41TXX_NEG_OFFSET_STEP_PPB);

	वापस 0;
पूर्ण

अटल पूर्णांक m41txx_rtc_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ctrl_reg;

	अगर ((offset < M41TXX_MIN_OFFSET) || (offset > M41TXX_MAX_OFFSET))
		वापस -दुस्फल;

	अगर (offset >= 0) अणु
		ctrl_reg = DIV_ROUND_CLOSEST(offset,
					     M41TXX_POS_OFFSET_STEP_PPB);
		ctrl_reg |= M41TXX_BIT_CALIB_SIGN;
	पूर्ण अन्यथा अणु
		ctrl_reg = DIV_ROUND_CLOSEST(असल(offset),
					     M41TXX_NEG_OFFSET_STEP_PPB);
	पूर्ण

	वापस regmap_update_bits(ds1307->regmap, M41TXX_REG_CONTROL,
				  M41TXX_M_CALIBRATION | M41TXX_BIT_CALIB_SIGN,
				  ctrl_reg);
पूर्ण

#अगर_घोषित CONFIG_WATCHDOG_CORE
अटल पूर्णांक ds1388_wdt_start(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा ds1307 *ds1307 = watchकरोg_get_drvdata(wdt_dev);
	u8 regs[2];
	पूर्णांक ret;

	ret = regmap_update_bits(ds1307->regmap, DS1388_REG_FLAG,
				 DS1388_BIT_WF, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(ds1307->regmap, DS1388_REG_CONTROL,
				 DS1388_BIT_WDE | DS1388_BIT_RST, 0);
	अगर (ret)
		वापस ret;

	/*
	 * watchकरोg समयouts are measured in seconds. So ignore hundredths of
	 * seconds field.
	 */
	regs[0] = 0;
	regs[1] = bin2bcd(wdt_dev->समयout);

	ret = regmap_bulk_ग_लिखो(ds1307->regmap, DS1388_REG_WDOG_HUN_SECS, regs,
				माप(regs));
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(ds1307->regmap, DS1388_REG_CONTROL,
				  DS1388_BIT_WDE | DS1388_BIT_RST,
				  DS1388_BIT_WDE | DS1388_BIT_RST);
पूर्ण

अटल पूर्णांक ds1388_wdt_stop(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा ds1307 *ds1307 = watchकरोg_get_drvdata(wdt_dev);

	वापस regmap_update_bits(ds1307->regmap, DS1388_REG_CONTROL,
				  DS1388_BIT_WDE | DS1388_BIT_RST, 0);
पूर्ण

अटल पूर्णांक ds1388_wdt_ping(काष्ठा watchकरोg_device *wdt_dev)
अणु
	काष्ठा ds1307 *ds1307 = watchकरोg_get_drvdata(wdt_dev);
	u8 regs[2];

	वापस regmap_bulk_पढ़ो(ds1307->regmap, DS1388_REG_WDOG_HUN_SECS, regs,
				माप(regs));
पूर्ण

अटल पूर्णांक ds1388_wdt_set_समयout(काष्ठा watchकरोg_device *wdt_dev,
				  अचिन्हित पूर्णांक val)
अणु
	काष्ठा ds1307 *ds1307 = watchकरोg_get_drvdata(wdt_dev);
	u8 regs[2];

	wdt_dev->समयout = val;
	regs[0] = 0;
	regs[1] = bin2bcd(wdt_dev->समयout);

	वापस regmap_bulk_ग_लिखो(ds1307->regmap, DS1388_REG_WDOG_HUN_SECS, regs,
				 माप(regs));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops rx8130_rtc_ops = अणु
	.पढ़ो_समय      = ds1307_get_समय,
	.set_समय       = ds1307_set_समय,
	.पढ़ो_alarm     = rx8130_पढ़ो_alarm,
	.set_alarm      = rx8130_set_alarm,
	.alarm_irq_enable = rx8130_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा rtc_class_ops mcp794xx_rtc_ops = अणु
	.पढ़ो_समय      = ds1307_get_समय,
	.set_समय       = ds1307_set_समय,
	.पढ़ो_alarm     = mcp794xx_पढ़ो_alarm,
	.set_alarm      = mcp794xx_set_alarm,
	.alarm_irq_enable = mcp794xx_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा rtc_class_ops m41txx_rtc_ops = अणु
	.पढ़ो_समय      = ds1307_get_समय,
	.set_समय       = ds1307_set_समय,
	.पढ़ो_alarm	= ds1337_पढ़ो_alarm,
	.set_alarm	= ds1337_set_alarm,
	.alarm_irq_enable = ds1307_alarm_irq_enable,
	.पढ़ो_offset	= m41txx_rtc_पढ़ो_offset,
	.set_offset	= m41txx_rtc_set_offset,
पूर्ण;

अटल स्थिर काष्ठा chip_desc chips[last_ds_type] = अणु
	[ds_1307] = अणु
		.nvram_offset	= 8,
		.nvram_size	= 56,
	पूर्ण,
	[ds_1308] = अणु
		.nvram_offset	= 8,
		.nvram_size	= 56,
	पूर्ण,
	[ds_1337] = अणु
		.alarm		= 1,
		.century_reg	= DS1307_REG_MONTH,
		.century_bit	= DS1337_BIT_CENTURY,
	पूर्ण,
	[ds_1338] = अणु
		.nvram_offset	= 8,
		.nvram_size	= 56,
	पूर्ण,
	[ds_1339] = अणु
		.alarm		= 1,
		.century_reg	= DS1307_REG_MONTH,
		.century_bit	= DS1337_BIT_CENTURY,
		.bbsqi_bit	= DS1339_BIT_BBSQI,
		.trickle_अक्षरger_reg = 0x10,
		.करो_trickle_setup = &करो_trickle_setup_ds1339,
		.requires_trickle_resistor = true,
		.अक्षरge_शेष = true,
	पूर्ण,
	[ds_1340] = अणु
		.century_reg	= DS1307_REG_HOUR,
		.century_enable_bit = DS1340_BIT_CENTURY_EN,
		.century_bit	= DS1340_BIT_CENTURY,
		.करो_trickle_setup = &करो_trickle_setup_ds1339,
		.trickle_अक्षरger_reg = 0x08,
		.requires_trickle_resistor = true,
		.अक्षरge_शेष = true,
	पूर्ण,
	[ds_1341] = अणु
		.century_reg	= DS1307_REG_MONTH,
		.century_bit	= DS1337_BIT_CENTURY,
	पूर्ण,
	[ds_1388] = अणु
		.offset		= 1,
		.trickle_अक्षरger_reg = 0x0a,
	पूर्ण,
	[ds_3231] = अणु
		.alarm		= 1,
		.century_reg	= DS1307_REG_MONTH,
		.century_bit	= DS1337_BIT_CENTURY,
		.bbsqi_bit	= DS3231_BIT_BBSQW,
	पूर्ण,
	[rx_8130] = अणु
		.alarm		= 1,
		/* this is battery backed SRAM */
		.nvram_offset	= 0x20,
		.nvram_size	= 4,	/* 32bit (4 word x 8 bit) */
		.offset		= 0x10,
		.irq_handler = rx8130_irq,
		.rtc_ops = &rx8130_rtc_ops,
		.trickle_अक्षरger_reg = RX8130_REG_CONTROL1,
		.करो_trickle_setup = &करो_trickle_setup_rx8130,
	पूर्ण,
	[m41t0] = अणु
		.rtc_ops	= &m41txx_rtc_ops,
	पूर्ण,
	[m41t00] = अणु
		.rtc_ops	= &m41txx_rtc_ops,
	पूर्ण,
	[m41t11] = अणु
		/* this is battery backed SRAM */
		.nvram_offset	= 8,
		.nvram_size	= 56,
		.rtc_ops	= &m41txx_rtc_ops,
	पूर्ण,
	[mcp794xx] = अणु
		.alarm		= 1,
		/* this is battery backed SRAM */
		.nvram_offset	= 0x20,
		.nvram_size	= 0x40,
		.irq_handler = mcp794xx_irq,
		.rtc_ops = &mcp794xx_rtc_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ds1307_id[] = अणु
	अणु "ds1307", ds_1307 पूर्ण,
	अणु "ds1308", ds_1308 पूर्ण,
	अणु "ds1337", ds_1337 पूर्ण,
	अणु "ds1338", ds_1338 पूर्ण,
	अणु "ds1339", ds_1339 पूर्ण,
	अणु "ds1388", ds_1388 पूर्ण,
	अणु "ds1340", ds_1340 पूर्ण,
	अणु "ds1341", ds_1341 पूर्ण,
	अणु "ds3231", ds_3231 पूर्ण,
	अणु "m41t0", m41t0 पूर्ण,
	अणु "m41t00", m41t00 पूर्ण,
	अणु "m41t11", m41t11 पूर्ण,
	अणु "mcp7940x", mcp794xx पूर्ण,
	अणु "mcp7941x", mcp794xx पूर्ण,
	अणु "pt7c4338", ds_1307 पूर्ण,
	अणु "rx8025", rx_8025 पूर्ण,
	अणु "isl12057", ds_1337 पूर्ण,
	अणु "rx8130", rx_8130 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds1307_id);

अटल स्थिर काष्ठा of_device_id ds1307_of_match[] = अणु
	अणु
		.compatible = "dallas,ds1307",
		.data = (व्योम *)ds_1307
	पूर्ण,
	अणु
		.compatible = "dallas,ds1308",
		.data = (व्योम *)ds_1308
	पूर्ण,
	अणु
		.compatible = "dallas,ds1337",
		.data = (व्योम *)ds_1337
	पूर्ण,
	अणु
		.compatible = "dallas,ds1338",
		.data = (व्योम *)ds_1338
	पूर्ण,
	अणु
		.compatible = "dallas,ds1339",
		.data = (व्योम *)ds_1339
	पूर्ण,
	अणु
		.compatible = "dallas,ds1388",
		.data = (व्योम *)ds_1388
	पूर्ण,
	अणु
		.compatible = "dallas,ds1340",
		.data = (व्योम *)ds_1340
	पूर्ण,
	अणु
		.compatible = "dallas,ds1341",
		.data = (व्योम *)ds_1341
	पूर्ण,
	अणु
		.compatible = "maxim,ds3231",
		.data = (व्योम *)ds_3231
	पूर्ण,
	अणु
		.compatible = "st,m41t0",
		.data = (व्योम *)m41t0
	पूर्ण,
	अणु
		.compatible = "st,m41t00",
		.data = (व्योम *)m41t00
	पूर्ण,
	अणु
		.compatible = "st,m41t11",
		.data = (व्योम *)m41t11
	पूर्ण,
	अणु
		.compatible = "microchip,mcp7940x",
		.data = (व्योम *)mcp794xx
	पूर्ण,
	अणु
		.compatible = "microchip,mcp7941x",
		.data = (व्योम *)mcp794xx
	पूर्ण,
	अणु
		.compatible = "pericom,pt7c4338",
		.data = (व्योम *)ds_1307
	पूर्ण,
	अणु
		.compatible = "epson,rx8025",
		.data = (व्योम *)rx_8025
	पूर्ण,
	अणु
		.compatible = "isil,isl12057",
		.data = (व्योम *)ds_1337
	पूर्ण,
	अणु
		.compatible = "epson,rx8130",
		.data = (व्योम *)rx_8130
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1307_of_match);

/*
 * The ds1337 and ds1339 both have two alarms, but we only use the first
 * one (with a "seconds" field).  For ds1337 we expect nINTA is our alarm
 * संकेत; ds1339 chips have only one alarm संकेत.
 */
अटल irqवापस_t ds1307_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ds1307		*ds1307 = dev_id;
	काष्ठा mutex		*lock = &ds1307->rtc->ops_lock;
	पूर्णांक			stat, ret;

	mutex_lock(lock);
	ret = regmap_पढ़ो(ds1307->regmap, DS1337_REG_STATUS, &stat);
	अगर (ret)
		जाओ out;

	अगर (stat & DS1337_BIT_A1I) अणु
		stat &= ~DS1337_BIT_A1I;
		regmap_ग_लिखो(ds1307->regmap, DS1337_REG_STATUS, stat);

		ret = regmap_update_bits(ds1307->regmap, DS1337_REG_CONTROL,
					 DS1337_BIT_A1IE, 0);
		अगर (ret)
			जाओ out;

		rtc_update_irq(ds1307->rtc, 1, RTC_AF | RTC_IRQF);
	पूर्ण

out:
	mutex_unlock(lock);

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

अटल स्थिर काष्ठा rtc_class_ops ds13xx_rtc_ops = अणु
	.पढ़ो_समय	= ds1307_get_समय,
	.set_समय	= ds1307_set_समय,
	.पढ़ो_alarm	= ds1337_पढ़ो_alarm,
	.set_alarm	= ds1337_set_alarm,
	.alarm_irq_enable = ds1307_alarm_irq_enable,
पूर्ण;

अटल sमाप_प्रकार frequency_test_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev->parent);
	bool freq_test_en;
	पूर्णांक ret;

	ret = kstrtobool(buf, &freq_test_en);
	अगर (ret) अणु
		dev_err(dev, "Failed to store RTC Frequency Test attribute\n");
		वापस ret;
	पूर्ण

	regmap_update_bits(ds1307->regmap, M41TXX_REG_CONTROL, M41TXX_BIT_FT,
			   freq_test_en ? M41TXX_BIT_FT : 0);

	वापस count;
पूर्ण

अटल sमाप_प्रकार frequency_test_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev->parent);
	अचिन्हित पूर्णांक ctrl_reg;

	regmap_पढ़ो(ds1307->regmap, M41TXX_REG_CONTROL, &ctrl_reg);

	वापस scnम_लिखो(buf, PAGE_SIZE, (ctrl_reg & M41TXX_BIT_FT) ? "on\n" :
			"off\n");
पूर्ण

अटल DEVICE_ATTR_RW(frequency_test);

अटल काष्ठा attribute *rtc_freq_test_attrs[] = अणु
	&dev_attr_frequency_test.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtc_freq_test_attr_group = अणु
	.attrs		= rtc_freq_test_attrs,
पूर्ण;

अटल पूर्णांक ds1307_add_frequency_test(काष्ठा ds1307 *ds1307)
अणु
	पूर्णांक err;

	चयन (ds1307->type) अणु
	हाल m41t0:
	हाल m41t00:
	हाल m41t11:
		err = rtc_add_group(ds1307->rtc, &rtc_freq_test_attr_group);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------*/

अटल पूर्णांक ds1307_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा ds1307 *ds1307 = priv;
	स्थिर काष्ठा chip_desc *chip = &chips[ds1307->type];

	वापस regmap_bulk_पढ़ो(ds1307->regmap, chip->nvram_offset + offset,
				val, bytes);
पूर्ण

अटल पूर्णांक ds1307_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा ds1307 *ds1307 = priv;
	स्थिर काष्ठा chip_desc *chip = &chips[ds1307->type];

	वापस regmap_bulk_ग_लिखो(ds1307->regmap, chip->nvram_offset + offset,
				 val, bytes);
पूर्ण

/*----------------------------------------------------------------------*/

अटल u8 ds1307_trickle_init(काष्ठा ds1307 *ds1307,
			      स्थिर काष्ठा chip_desc *chip)
अणु
	u32 ohms, अक्षरgeable;
	bool diode = chip->अक्षरge_शेष;

	अगर (!chip->करो_trickle_setup)
		वापस 0;

	अगर (device_property_पढ़ो_u32(ds1307->dev, "trickle-resistor-ohms",
				     &ohms) && chip->requires_trickle_resistor)
		वापस 0;

	/* aux-voltage-अक्षरgeable takes precedence over the deprecated
	 * trickle-diode-disable
	 */
	अगर (!device_property_पढ़ो_u32(ds1307->dev, "aux-voltage-chargeable",
				     &अक्षरgeable)) अणु
		चयन (अक्षरgeable) अणु
		हाल 0:
			diode = false;
			अवरोध;
		हाल 1:
			diode = true;
			अवरोध;
		शेष:
			dev_warn(ds1307->dev,
				 "unsupported aux-voltage-chargeable value\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (device_property_पढ़ो_bool(ds1307->dev,
					     "trickle-diode-disable")) अणु
		diode = false;
	पूर्ण

	वापस chip->करो_trickle_setup(ds1307, ohms, diode);
पूर्ण

/*----------------------------------------------------------------------*/

#अगर IS_REACHABLE(CONFIG_HWMON)

/*
 * Temperature sensor support क्रम ds3231 devices.
 */

#घोषणा DS3231_REG_TEMPERATURE	0x11

/*
 * A user-initiated temperature conversion is not started by this function,
 * so the temperature is updated once every 64 seconds.
 */
अटल पूर्णांक ds3231_hwmon_पढ़ो_temp(काष्ठा device *dev, s32 *mC)
अणु
	काष्ठा ds1307 *ds1307 = dev_get_drvdata(dev);
	u8 temp_buf[2];
	s16 temp;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(ds1307->regmap, DS3231_REG_TEMPERATURE,
			       temp_buf, माप(temp_buf));
	अगर (ret)
		वापस ret;
	/*
	 * Temperature is represented as a 10-bit code with a resolution of
	 * 0.25 degree celsius and encoded in two's complement क्रमmat.
	 */
	temp = (temp_buf[0] << 8) | temp_buf[1];
	temp >>= 6;
	*mC = temp * 250;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ds3231_hwmon_show_temp(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	s32 temp;

	ret = ds3231_hwmon_पढ़ो_temp(dev, &temp);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण
अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, ds3231_hwmon_show_temp,
			  शून्य, 0);

अटल काष्ठा attribute *ds3231_hwmon_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ds3231_hwmon);

अटल व्योम ds1307_hwmon_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
	काष्ठा device *dev;

	अगर (ds1307->type != ds_3231)
		वापस;

	dev = devm_hwmon_device_रेजिस्टर_with_groups(ds1307->dev, ds1307->name,
						     ds1307,
						     ds3231_hwmon_groups);
	अगर (IS_ERR(dev)) अणु
		dev_warn(ds1307->dev, "unable to register hwmon device %ld\n",
			 PTR_ERR(dev));
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम ds1307_hwmon_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_RTC_DRV_DS1307_HWMON */

/*----------------------------------------------------------------------*/

/*
 * Square-wave output support क्रम DS3231
 * Datasheet: https://datasheets.maximपूर्णांकegrated.com/en/ds/DS3231.pdf
 */
#अगर_घोषित CONFIG_COMMON_CLK

क्रमागत अणु
	DS3231_CLK_SQW = 0,
	DS3231_CLK_32KHZ,
पूर्ण;

#घोषणा clk_sqw_to_ds1307(clk)	\
	container_of(clk, काष्ठा ds1307, clks[DS3231_CLK_SQW])
#घोषणा clk_32khz_to_ds1307(clk)	\
	container_of(clk, काष्ठा ds1307, clks[DS3231_CLK_32KHZ])

अटल पूर्णांक ds3231_clk_sqw_rates[] = अणु
	1,
	1024,
	4096,
	8192,
पूर्ण;

अटल पूर्णांक ds1337_ग_लिखो_control(काष्ठा ds1307 *ds1307, u8 mask, u8 value)
अणु
	काष्ठा mutex *lock = &ds1307->rtc->ops_lock;
	पूर्णांक ret;

	mutex_lock(lock);
	ret = regmap_update_bits(ds1307->regmap, DS1337_REG_CONTROL,
				 mask, value);
	mutex_unlock(lock);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ ds3231_clk_sqw_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ds1307 *ds1307 = clk_sqw_to_ds1307(hw);
	पूर्णांक control, ret;
	पूर्णांक rate_sel = 0;

	ret = regmap_पढ़ो(ds1307->regmap, DS1337_REG_CONTROL, &control);
	अगर (ret)
		वापस ret;
	अगर (control & DS1337_BIT_RS1)
		rate_sel += 1;
	अगर (control & DS1337_BIT_RS2)
		rate_sel += 2;

	वापस ds3231_clk_sqw_rates[rate_sel];
पूर्ण

अटल दीर्घ ds3231_clk_sqw_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(ds3231_clk_sqw_rates) - 1; i >= 0; i--) अणु
		अगर (ds3231_clk_sqw_rates[i] <= rate)
			वापस ds3231_clk_sqw_rates[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3231_clk_sqw_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ds1307 *ds1307 = clk_sqw_to_ds1307(hw);
	पूर्णांक control = 0;
	पूर्णांक rate_sel;

	क्रम (rate_sel = 0; rate_sel < ARRAY_SIZE(ds3231_clk_sqw_rates);
			rate_sel++) अणु
		अगर (ds3231_clk_sqw_rates[rate_sel] == rate)
			अवरोध;
	पूर्ण

	अगर (rate_sel == ARRAY_SIZE(ds3231_clk_sqw_rates))
		वापस -EINVAL;

	अगर (rate_sel & 1)
		control |= DS1337_BIT_RS1;
	अगर (rate_sel & 2)
		control |= DS1337_BIT_RS2;

	वापस ds1337_ग_लिखो_control(ds1307, DS1337_BIT_RS1 | DS1337_BIT_RS2,
				control);
पूर्ण

अटल पूर्णांक ds3231_clk_sqw_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ds1307 *ds1307 = clk_sqw_to_ds1307(hw);

	वापस ds1337_ग_लिखो_control(ds1307, DS1337_BIT_INTCN, 0);
पूर्ण

अटल व्योम ds3231_clk_sqw_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ds1307 *ds1307 = clk_sqw_to_ds1307(hw);

	ds1337_ग_लिखो_control(ds1307, DS1337_BIT_INTCN, DS1337_BIT_INTCN);
पूर्ण

अटल पूर्णांक ds3231_clk_sqw_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा ds1307 *ds1307 = clk_sqw_to_ds1307(hw);
	पूर्णांक control, ret;

	ret = regmap_पढ़ो(ds1307->regmap, DS1337_REG_CONTROL, &control);
	अगर (ret)
		वापस ret;

	वापस !(control & DS1337_BIT_INTCN);
पूर्ण

अटल स्थिर काष्ठा clk_ops ds3231_clk_sqw_ops = अणु
	.prepare = ds3231_clk_sqw_prepare,
	.unprepare = ds3231_clk_sqw_unprepare,
	.is_prepared = ds3231_clk_sqw_is_prepared,
	.recalc_rate = ds3231_clk_sqw_recalc_rate,
	.round_rate = ds3231_clk_sqw_round_rate,
	.set_rate = ds3231_clk_sqw_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ ds3231_clk_32khz_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	वापस 32768;
पूर्ण

अटल पूर्णांक ds3231_clk_32khz_control(काष्ठा ds1307 *ds1307, bool enable)
अणु
	काष्ठा mutex *lock = &ds1307->rtc->ops_lock;
	पूर्णांक ret;

	mutex_lock(lock);
	ret = regmap_update_bits(ds1307->regmap, DS1337_REG_STATUS,
				 DS3231_BIT_EN32KHZ,
				 enable ? DS3231_BIT_EN32KHZ : 0);
	mutex_unlock(lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ds3231_clk_32khz_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ds1307 *ds1307 = clk_32khz_to_ds1307(hw);

	वापस ds3231_clk_32khz_control(ds1307, true);
पूर्ण

अटल व्योम ds3231_clk_32khz_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ds1307 *ds1307 = clk_32khz_to_ds1307(hw);

	ds3231_clk_32khz_control(ds1307, false);
पूर्ण

अटल पूर्णांक ds3231_clk_32khz_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा ds1307 *ds1307 = clk_32khz_to_ds1307(hw);
	पूर्णांक status, ret;

	ret = regmap_पढ़ो(ds1307->regmap, DS1337_REG_STATUS, &status);
	अगर (ret)
		वापस ret;

	वापस !!(status & DS3231_BIT_EN32KHZ);
पूर्ण

अटल स्थिर काष्ठा clk_ops ds3231_clk_32khz_ops = अणु
	.prepare = ds3231_clk_32khz_prepare,
	.unprepare = ds3231_clk_32khz_unprepare,
	.is_prepared = ds3231_clk_32khz_is_prepared,
	.recalc_rate = ds3231_clk_32khz_recalc_rate,
पूर्ण;

अटल स्थिर अक्षर *ds3231_clks_names[] = अणु
	[DS3231_CLK_SQW] = "ds3231_clk_sqw",
	[DS3231_CLK_32KHZ] = "ds3231_clk_32khz",
पूर्ण;

अटल काष्ठा clk_init_data ds3231_clks_init[] = अणु
	[DS3231_CLK_SQW] = अणु
		.ops = &ds3231_clk_sqw_ops,
	पूर्ण,
	[DS3231_CLK_32KHZ] = अणु
		.ops = &ds3231_clk_32khz_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ds3231_clks_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
	काष्ठा device_node *node = ds1307->dev->of_node;
	काष्ठा clk_onecell_data	*onecell;
	पूर्णांक i;

	onecell = devm_kzalloc(ds1307->dev, माप(*onecell), GFP_KERNEL);
	अगर (!onecell)
		वापस -ENOMEM;

	onecell->clk_num = ARRAY_SIZE(ds3231_clks_init);
	onecell->clks = devm_kसुस्मृति(ds1307->dev, onecell->clk_num,
				     माप(onecell->clks[0]), GFP_KERNEL);
	अगर (!onecell->clks)
		वापस -ENOMEM;

	/* optional override of the घड़ीname */
	device_property_पढ़ो_string_array(ds1307->dev, "clock-output-names",
					  ds3231_clks_names,
					  ARRAY_SIZE(ds3231_clks_names));

	क्रम (i = 0; i < ARRAY_SIZE(ds3231_clks_init); i++) अणु
		काष्ठा clk_init_data init = ds3231_clks_init[i];

		/*
		 * Interrupt संकेत due to alarm conditions and square-wave
		 * output share same pin, so करोn't initialize both.
		 */
		अगर (i == DS3231_CLK_SQW && test_bit(RTC_FEATURE_ALARM, ds1307->rtc->features))
			जारी;

		init.name = ds3231_clks_names[i];
		ds1307->clks[i].init = &init;

		onecell->clks[i] = devm_clk_रेजिस्टर(ds1307->dev,
						     &ds1307->clks[i]);
		अगर (IS_ERR(onecell->clks[i]))
			वापस PTR_ERR(onecell->clks[i]);
	पूर्ण

	अगर (node)
		of_clk_add_provider(node, of_clk_src_onecell_get, onecell);

	वापस 0;
पूर्ण

अटल व्योम ds1307_clks_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
	पूर्णांक ret;

	अगर (ds1307->type != ds_3231)
		वापस;

	ret = ds3231_clks_रेजिस्टर(ds1307);
	अगर (ret) अणु
		dev_warn(ds1307->dev, "unable to register clock device %d\n",
			 ret);
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम ds1307_clks_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_COMMON_CLK */

#अगर_घोषित CONFIG_WATCHDOG_CORE
अटल स्थिर काष्ठा watchकरोg_info ds1388_wdt_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "DS1388 watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops ds1388_wdt_ops = अणु
	.owner = THIS_MODULE,
	.start = ds1388_wdt_start,
	.stop = ds1388_wdt_stop,
	.ping = ds1388_wdt_ping,
	.set_समयout = ds1388_wdt_set_समयout,

पूर्ण;

अटल व्योम ds1307_wdt_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
	काष्ठा watchकरोg_device	*wdt;
	पूर्णांक err;
	पूर्णांक val;

	अगर (ds1307->type != ds_1388)
		वापस;

	wdt = devm_kzalloc(ds1307->dev, माप(*wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस;

	err = regmap_पढ़ो(ds1307->regmap, DS1388_REG_FLAG, &val);
	अगर (!err && val & DS1388_BIT_WF)
		wdt->bootstatus = WDIOF_CARDRESET;

	wdt->info = &ds1388_wdt_info;
	wdt->ops = &ds1388_wdt_ops;
	wdt->समयout = 99;
	wdt->max_समयout = 99;
	wdt->min_समयout = 1;

	watchकरोg_init_समयout(wdt, 0, ds1307->dev);
	watchकरोg_set_drvdata(wdt, ds1307);
	devm_watchकरोg_रेजिस्टर_device(ds1307->dev, wdt);
पूर्ण
#अन्यथा
अटल व्योम ds1307_wdt_रेजिस्टर(काष्ठा ds1307 *ds1307)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_WATCHDOG_CORE */

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक ds1307_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ds1307		*ds1307;
	स्थिर व्योम		*match;
	पूर्णांक			err = -ENODEV;
	पूर्णांक			पंचांगp;
	स्थिर काष्ठा chip_desc	*chip;
	bool			want_irq;
	bool			ds1307_can_wakeup_device = false;
	अचिन्हित अक्षर		regs[8];
	काष्ठा ds1307_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	u8			trickle_अक्षरger_setup = 0;

	ds1307 = devm_kzalloc(&client->dev, माप(काष्ठा ds1307), GFP_KERNEL);
	अगर (!ds1307)
		वापस -ENOMEM;

	dev_set_drvdata(&client->dev, ds1307);
	ds1307->dev = &client->dev;
	ds1307->name = client->name;

	ds1307->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(ds1307->regmap)) अणु
		dev_err(ds1307->dev, "regmap allocation failed\n");
		वापस PTR_ERR(ds1307->regmap);
	पूर्ण

	i2c_set_clientdata(client, ds1307);

	match = device_get_match_data(&client->dev);
	अगर (match) अणु
		ds1307->type = (क्रमागत ds_type)match;
		chip = &chips[ds1307->type];
	पूर्ण अन्यथा अगर (id) अणु
		chip = &chips[id->driver_data];
		ds1307->type = id->driver_data;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	want_irq = client->irq > 0 && chip->alarm;

	अगर (!pdata)
		trickle_अक्षरger_setup = ds1307_trickle_init(ds1307, chip);
	अन्यथा अगर (pdata->trickle_अक्षरger_setup)
		trickle_अक्षरger_setup = pdata->trickle_अक्षरger_setup;

	अगर (trickle_अक्षरger_setup && chip->trickle_अक्षरger_reg) अणु
		dev_dbg(ds1307->dev,
			"writing trickle charger info 0x%x to 0x%x\n",
			trickle_अक्षरger_setup, chip->trickle_अक्षरger_reg);
		regmap_ग_लिखो(ds1307->regmap, chip->trickle_अक्षरger_reg,
			     trickle_अक्षरger_setup);
	पूर्ण

/*
 * For devices with no IRQ directly connected to the SoC, the RTC chip
 * can be क्रमced as a wakeup source by stating that explicitly in
 * the device's .dts file using the "wakeup-source" boolean property.
 * If the "wakeup-source" property is set, करोn't request an IRQ.
 * This will guarantee the 'wakealarm' sysfs entry is available on the device,
 * अगर supported by the RTC.
 */
	अगर (chip->alarm && device_property_पढ़ो_bool(&client->dev, "wakeup-source"))
		ds1307_can_wakeup_device = true;

	चयन (ds1307->type) अणु
	हाल ds_1337:
	हाल ds_1339:
	हाल ds_1341:
	हाल ds_3231:
		/* get रेजिस्टरs that the "rtc" पढ़ो below won't पढ़ो... */
		err = regmap_bulk_पढ़ो(ds1307->regmap, DS1337_REG_CONTROL,
				       regs, 2);
		अगर (err) अणु
			dev_dbg(ds1307->dev, "read error %d\n", err);
			जाओ निकास;
		पूर्ण

		/* oscillator off?  turn it on, so घड़ी can tick. */
		अगर (regs[0] & DS1337_BIT_nEOSC)
			regs[0] &= ~DS1337_BIT_nEOSC;

		/*
		 * Using IRQ or defined as wakeup-source?
		 * Disable the square wave and both alarms.
		 * For some variants, be sure alarms can trigger when we're
		 * running on Vbackup (BBSQI/BBSQW)
		 */
		अगर (want_irq || ds1307_can_wakeup_device) अणु
			regs[0] |= DS1337_BIT_INTCN | chip->bbsqi_bit;
			regs[0] &= ~(DS1337_BIT_A2IE | DS1337_BIT_A1IE);
		पूर्ण

		regmap_ग_लिखो(ds1307->regmap, DS1337_REG_CONTROL,
			     regs[0]);

		/* oscillator fault?  clear flag, and warn */
		अगर (regs[1] & DS1337_BIT_OSF) अणु
			regmap_ग_लिखो(ds1307->regmap, DS1337_REG_STATUS,
				     regs[1] & ~DS1337_BIT_OSF);
			dev_warn(ds1307->dev, "SET TIME!\n");
		पूर्ण
		अवरोध;

	हाल rx_8025:
		err = regmap_bulk_पढ़ो(ds1307->regmap,
				       RX8025_REG_CTRL1 << 4 | 0x08, regs, 2);
		अगर (err) अणु
			dev_dbg(ds1307->dev, "read error %d\n", err);
			जाओ निकास;
		पूर्ण

		/* oscillator off?  turn it on, so घड़ी can tick. */
		अगर (!(regs[1] & RX8025_BIT_XST)) अणु
			regs[1] |= RX8025_BIT_XST;
			regmap_ग_लिखो(ds1307->regmap,
				     RX8025_REG_CTRL2 << 4 | 0x08,
				     regs[1]);
			dev_warn(ds1307->dev,
				 "oscillator stop detected - SET TIME!\n");
		पूर्ण

		अगर (regs[1] & RX8025_BIT_PON) अणु
			regs[1] &= ~RX8025_BIT_PON;
			regmap_ग_लिखो(ds1307->regmap,
				     RX8025_REG_CTRL2 << 4 | 0x08,
				     regs[1]);
			dev_warn(ds1307->dev, "power-on detected\n");
		पूर्ण

		अगर (regs[1] & RX8025_BIT_VDET) अणु
			regs[1] &= ~RX8025_BIT_VDET;
			regmap_ग_लिखो(ds1307->regmap,
				     RX8025_REG_CTRL2 << 4 | 0x08,
				     regs[1]);
			dev_warn(ds1307->dev, "voltage drop detected\n");
		पूर्ण

		/* make sure we are running in 24hour mode */
		अगर (!(regs[0] & RX8025_BIT_2412)) अणु
			u8 hour;

			/* चयन to 24 hour mode */
			regmap_ग_लिखो(ds1307->regmap,
				     RX8025_REG_CTRL1 << 4 | 0x08,
				     regs[0] | RX8025_BIT_2412);

			err = regmap_bulk_पढ़ो(ds1307->regmap,
					       RX8025_REG_CTRL1 << 4 | 0x08,
					       regs, 2);
			अगर (err) अणु
				dev_dbg(ds1307->dev, "read error %d\n", err);
				जाओ निकास;
			पूर्ण

			/* correct hour */
			hour = bcd2bin(regs[DS1307_REG_HOUR]);
			अगर (hour == 12)
				hour = 0;
			अगर (regs[DS1307_REG_HOUR] & DS1307_BIT_PM)
				hour += 12;

			regmap_ग_लिखो(ds1307->regmap,
				     DS1307_REG_HOUR << 4 | 0x08, hour);
		पूर्ण
		अवरोध;
	हाल ds_1388:
		err = regmap_पढ़ो(ds1307->regmap, DS1388_REG_CONTROL, &पंचांगp);
		अगर (err) अणु
			dev_dbg(ds1307->dev, "read error %d\n", err);
			जाओ निकास;
		पूर्ण

		/* oscillator off?  turn it on, so घड़ी can tick. */
		अगर (पंचांगp & DS1388_BIT_nEOSC) अणु
			पंचांगp &= ~DS1388_BIT_nEOSC;
			regmap_ग_लिखो(ds1307->regmap, DS1388_REG_CONTROL, पंचांगp);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* पढ़ो RTC रेजिस्टरs */
	err = regmap_bulk_पढ़ो(ds1307->regmap, chip->offset, regs,
			       माप(regs));
	अगर (err) अणु
		dev_dbg(ds1307->dev, "read error %d\n", err);
		जाओ निकास;
	पूर्ण

	अगर (ds1307->type == mcp794xx &&
	    !(regs[DS1307_REG_WDAY] & MCP794XX_BIT_VBATEN)) अणु
		regmap_ग_लिखो(ds1307->regmap, DS1307_REG_WDAY,
			     regs[DS1307_REG_WDAY] |
			     MCP794XX_BIT_VBATEN);
	पूर्ण

	पंचांगp = regs[DS1307_REG_HOUR];
	चयन (ds1307->type) अणु
	हाल ds_1340:
	हाल m41t0:
	हाल m41t00:
	हाल m41t11:
		/*
		 * NOTE: ignores century bits; fix beक्रमe deploying
		 * प्रणालीs that will run through year 2100.
		 */
		अवरोध;
	हाल rx_8025:
		अवरोध;
	शेष:
		अगर (!(पंचांगp & DS1307_BIT_12HR))
			अवरोध;

		/*
		 * Be sure we're in 24 hour mode.  Multi-master प्रणालीs
		 * take note...
		 */
		पंचांगp = bcd2bin(पंचांगp & 0x1f);
		अगर (पंचांगp == 12)
			पंचांगp = 0;
		अगर (regs[DS1307_REG_HOUR] & DS1307_BIT_PM)
			पंचांगp += 12;
		regmap_ग_लिखो(ds1307->regmap, chip->offset + DS1307_REG_HOUR,
			     bin2bcd(पंचांगp));
	पूर्ण

	ds1307->rtc = devm_rtc_allocate_device(ds1307->dev);
	अगर (IS_ERR(ds1307->rtc))
		वापस PTR_ERR(ds1307->rtc);

	अगर (want_irq || ds1307_can_wakeup_device)
		device_set_wakeup_capable(ds1307->dev, true);
	अन्यथा
		clear_bit(RTC_FEATURE_ALARM, ds1307->rtc->features);

	अगर (ds1307_can_wakeup_device && !want_irq) अणु
		dev_info(ds1307->dev,
			 "'wakeup-source' is set, request for an IRQ is disabled!\n");
		/* We cannot support UIE mode अगर we करो not have an IRQ line */
		ds1307->rtc->uie_unsupported = 1;
	पूर्ण

	अगर (want_irq) अणु
		err = devm_request_thपढ़ोed_irq(ds1307->dev, client->irq, शून्य,
						chip->irq_handler ?: ds1307_irq,
						IRQF_SHARED | IRQF_ONESHOT,
						ds1307->name, ds1307);
		अगर (err) अणु
			client->irq = 0;
			device_set_wakeup_capable(ds1307->dev, false);
			clear_bit(RTC_FEATURE_ALARM, ds1307->rtc->features);
			dev_err(ds1307->dev, "unable to request IRQ!\n");
		पूर्ण अन्यथा अणु
			dev_dbg(ds1307->dev, "got IRQ %d\n", client->irq);
		पूर्ण
	पूर्ण

	ds1307->rtc->ops = chip->rtc_ops ?: &ds13xx_rtc_ops;
	err = ds1307_add_frequency_test(ds1307);
	अगर (err)
		वापस err;

	err = devm_rtc_रेजिस्टर_device(ds1307->rtc);
	अगर (err)
		वापस err;

	अगर (chip->nvram_size) अणु
		काष्ठा nvmem_config nvmem_cfg = अणु
			.name = "ds1307_nvram",
			.word_size = 1,
			.stride = 1,
			.size = chip->nvram_size,
			.reg_पढ़ो = ds1307_nvram_पढ़ो,
			.reg_ग_लिखो = ds1307_nvram_ग_लिखो,
			.priv = ds1307,
		पूर्ण;

		devm_rtc_nvmem_रेजिस्टर(ds1307->rtc, &nvmem_cfg);
	पूर्ण

	ds1307_hwmon_रेजिस्टर(ds1307);
	ds1307_clks_रेजिस्टर(ds1307);
	ds1307_wdt_रेजिस्टर(ds1307);

	वापस 0;

निकास:
	वापस err;
पूर्ण

अटल काष्ठा i2c_driver ds1307_driver = अणु
	.driver = अणु
		.name	= "rtc-ds1307",
		.of_match_table = ds1307_of_match,
	पूर्ण,
	.probe		= ds1307_probe,
	.id_table	= ds1307_id,
पूर्ण;

module_i2c_driver(ds1307_driver);

MODULE_DESCRIPTION("RTC driver for DS1307 and similar chips");
MODULE_LICENSE("GPL");
