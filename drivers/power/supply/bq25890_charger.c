<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI BQ25890 अक्षरger driver
 *
 * Copyright (C) 2015 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/usb/phy.h>

#समावेश <linux/acpi.h>
#समावेश <linux/of.h>

#घोषणा BQ25890_MANUFACTURER		"Texas Instruments"
#घोषणा BQ25890_IRQ_PIN			"bq25890_irq"

#घोषणा BQ25890_ID			3
#घोषणा BQ25895_ID			7
#घोषणा BQ25896_ID			0

क्रमागत bq25890_chip_version अणु
	BQ25890,
	BQ25892,
	BQ25895,
	BQ25896,
पूर्ण;

अटल स्थिर अक्षर *स्थिर bq25890_chip_name[] = अणु
	"BQ25890",
	"BQ25892",
	"BQ25895",
	"BQ25896",
पूर्ण;

क्रमागत bq25890_fields अणु
	F_EN_HIZ, F_EN_ILIM, F_IILIM,				     /* Reg00 */
	F_BHOT, F_BCOLD, F_VINDPM_OFS,				     /* Reg01 */
	F_CONV_START, F_CONV_RATE, F_BOOSTF, F_ICO_EN,
	F_HVDCP_EN, F_MAXC_EN, F_FORCE_DPM, F_AUTO_DPDM_EN,	     /* Reg02 */
	F_BAT_LOAD_EN, F_WD_RST, F_OTG_CFG, F_CHG_CFG, F_SYSVMIN,
	F_MIN_VBAT_SEL,						     /* Reg03 */
	F_PUMPX_EN, F_ICHG,					     /* Reg04 */
	F_IPRECHG, F_ITERM,					     /* Reg05 */
	F_VREG, F_BATLOWV, F_VRECHG,				     /* Reg06 */
	F_TERM_EN, F_STAT_DIS, F_WD, F_TMR_EN, F_CHG_TMR,
	F_JEITA_ISET,						     /* Reg07 */
	F_BATCMP, F_VCLAMP, F_TREG,				     /* Reg08 */
	F_FORCE_ICO, F_TMR2X_EN, F_BATFET_DIS, F_JEITA_VSET,
	F_BATFET_DLY, F_BATFET_RST_EN, F_PUMPX_UP, F_PUMPX_DN,	     /* Reg09 */
	F_BOOSTV, F_PFM_OTG_DIS, F_BOOSTI,			     /* Reg0A */
	F_VBUS_STAT, F_CHG_STAT, F_PG_STAT, F_SDP_STAT, F_0B_RSVD,
	F_VSYS_STAT,						     /* Reg0B */
	F_WD_FAULT, F_BOOST_FAULT, F_CHG_FAULT, F_BAT_FAULT,
	F_NTC_FAULT,						     /* Reg0C */
	F_FORCE_VINDPM, F_VINDPM,				     /* Reg0D */
	F_THERM_STAT, F_BATV,					     /* Reg0E */
	F_SYSV,							     /* Reg0F */
	F_TSPCT,						     /* Reg10 */
	F_VBUS_GD, F_VBUSV,					     /* Reg11 */
	F_ICHGR,						     /* Reg12 */
	F_VDPM_STAT, F_IDPM_STAT, F_IDPM_LIM,			     /* Reg13 */
	F_REG_RST, F_ICO_OPTIMIZED, F_PN, F_TS_PROखाता, F_DEV_REV,   /* Reg14 */

	F_MAX_FIELDS
पूर्ण;

/* initial field values, converted to रेजिस्टर values */
काष्ठा bq25890_init_data अणु
	u8 ichg;	/* अक्षरge current		*/
	u8 vreg;	/* regulation voltage		*/
	u8 iterm;	/* termination current		*/
	u8 iprechg;	/* preअक्षरge current		*/
	u8 sysvmin;	/* minimum प्रणाली voltage limit */
	u8 boostv;	/* boost regulation voltage	*/
	u8 boosti;	/* boost current limit		*/
	u8 boostf;	/* boost frequency		*/
	u8 ilim_en;	/* enable ILIM pin		*/
	u8 treg;	/* thermal regulation threshold */
	u8 rbatcomp;	/* IBAT sense resistor value    */
	u8 vclamp;	/* IBAT compensation voltage limit */
पूर्ण;

काष्ठा bq25890_state अणु
	u8 online;
	u8 chrg_status;
	u8 chrg_fault;
	u8 vsys_status;
	u8 boost_fault;
	u8 bat_fault;
पूर्ण;

काष्ठा bq25890_device अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा घातer_supply *अक्षरger;

	काष्ठा usb_phy *usb_phy;
	काष्ठा notअगरier_block usb_nb;
	काष्ठा work_काष्ठा usb_work;
	अचिन्हित दीर्घ usb_event;

	काष्ठा regmap *rmap;
	काष्ठा regmap_field *rmap_fields[F_MAX_FIELDS];

	क्रमागत bq25890_chip_version chip_version;
	काष्ठा bq25890_init_data init_data;
	काष्ठा bq25890_state state;

	काष्ठा mutex lock; /* protect state data */
पूर्ण;

अटल स्थिर काष्ठा regmap_range bq25890_पढ़ोonly_reg_ranges[] = अणु
	regmap_reg_range(0x0b, 0x0c),
	regmap_reg_range(0x0e, 0x13),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bq25890_ग_लिखोable_regs = अणु
	.no_ranges = bq25890_पढ़ोonly_reg_ranges,
	.n_no_ranges = ARRAY_SIZE(bq25890_पढ़ोonly_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range bq25890_अस्थिर_reg_ranges[] = अणु
	regmap_reg_range(0x00, 0x00),
	regmap_reg_range(0x02, 0x02),
	regmap_reg_range(0x09, 0x09),
	regmap_reg_range(0x0b, 0x14),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bq25890_अस्थिर_regs = अणु
	.yes_ranges = bq25890_अस्थिर_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(bq25890_अस्थिर_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config bq25890_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = 0x14,
	.cache_type = REGCACHE_RBTREE,

	.wr_table = &bq25890_ग_लिखोable_regs,
	.अस्थिर_table = &bq25890_अस्थिर_regs,
पूर्ण;

अटल स्थिर काष्ठा reg_field bq25890_reg_fields[] = अणु
	/* REG00 */
	[F_EN_HIZ]		= REG_FIELD(0x00, 7, 7),
	[F_EN_ILIM]		= REG_FIELD(0x00, 6, 6),
	[F_IILIM]		= REG_FIELD(0x00, 0, 5),
	/* REG01 */
	[F_BHOT]		= REG_FIELD(0x01, 6, 7),
	[F_BCOLD]		= REG_FIELD(0x01, 5, 5),
	[F_VINDPM_OFS]		= REG_FIELD(0x01, 0, 4),
	/* REG02 */
	[F_CONV_START]		= REG_FIELD(0x02, 7, 7),
	[F_CONV_RATE]		= REG_FIELD(0x02, 6, 6),
	[F_BOOSTF]		= REG_FIELD(0x02, 5, 5),
	[F_ICO_EN]		= REG_FIELD(0x02, 4, 4),
	[F_HVDCP_EN]		= REG_FIELD(0x02, 3, 3),  // reserved on BQ25896
	[F_MAXC_EN]		= REG_FIELD(0x02, 2, 2),  // reserved on BQ25896
	[F_FORCE_DPM]		= REG_FIELD(0x02, 1, 1),
	[F_AUTO_DPDM_EN]	= REG_FIELD(0x02, 0, 0),
	/* REG03 */
	[F_BAT_LOAD_EN]		= REG_FIELD(0x03, 7, 7),
	[F_WD_RST]		= REG_FIELD(0x03, 6, 6),
	[F_OTG_CFG]		= REG_FIELD(0x03, 5, 5),
	[F_CHG_CFG]		= REG_FIELD(0x03, 4, 4),
	[F_SYSVMIN]		= REG_FIELD(0x03, 1, 3),
	[F_MIN_VBAT_SEL]	= REG_FIELD(0x03, 0, 0), // BQ25896 only
	/* REG04 */
	[F_PUMPX_EN]		= REG_FIELD(0x04, 7, 7),
	[F_ICHG]		= REG_FIELD(0x04, 0, 6),
	/* REG05 */
	[F_IPRECHG]		= REG_FIELD(0x05, 4, 7),
	[F_ITERM]		= REG_FIELD(0x05, 0, 3),
	/* REG06 */
	[F_VREG]		= REG_FIELD(0x06, 2, 7),
	[F_BATLOWV]		= REG_FIELD(0x06, 1, 1),
	[F_VRECHG]		= REG_FIELD(0x06, 0, 0),
	/* REG07 */
	[F_TERM_EN]		= REG_FIELD(0x07, 7, 7),
	[F_STAT_DIS]		= REG_FIELD(0x07, 6, 6),
	[F_WD]			= REG_FIELD(0x07, 4, 5),
	[F_TMR_EN]		= REG_FIELD(0x07, 3, 3),
	[F_CHG_TMR]		= REG_FIELD(0x07, 1, 2),
	[F_JEITA_ISET]		= REG_FIELD(0x07, 0, 0), // reserved on BQ25895
	/* REG08 */
	[F_BATCMP]		= REG_FIELD(0x08, 5, 7),
	[F_VCLAMP]		= REG_FIELD(0x08, 2, 4),
	[F_TREG]		= REG_FIELD(0x08, 0, 1),
	/* REG09 */
	[F_FORCE_ICO]		= REG_FIELD(0x09, 7, 7),
	[F_TMR2X_EN]		= REG_FIELD(0x09, 6, 6),
	[F_BATFET_DIS]		= REG_FIELD(0x09, 5, 5),
	[F_JEITA_VSET]		= REG_FIELD(0x09, 4, 4), // reserved on BQ25895
	[F_BATFET_DLY]		= REG_FIELD(0x09, 3, 3),
	[F_BATFET_RST_EN]	= REG_FIELD(0x09, 2, 2),
	[F_PUMPX_UP]		= REG_FIELD(0x09, 1, 1),
	[F_PUMPX_DN]		= REG_FIELD(0x09, 0, 0),
	/* REG0A */
	[F_BOOSTV]		= REG_FIELD(0x0A, 4, 7),
	[F_BOOSTI]		= REG_FIELD(0x0A, 0, 2), // reserved on BQ25895
	[F_PFM_OTG_DIS]		= REG_FIELD(0x0A, 3, 3), // BQ25896 only
	/* REG0B */
	[F_VBUS_STAT]		= REG_FIELD(0x0B, 5, 7),
	[F_CHG_STAT]		= REG_FIELD(0x0B, 3, 4),
	[F_PG_STAT]		= REG_FIELD(0x0B, 2, 2),
	[F_SDP_STAT]		= REG_FIELD(0x0B, 1, 1), // reserved on BQ25896
	[F_VSYS_STAT]		= REG_FIELD(0x0B, 0, 0),
	/* REG0C */
	[F_WD_FAULT]		= REG_FIELD(0x0C, 7, 7),
	[F_BOOST_FAULT]		= REG_FIELD(0x0C, 6, 6),
	[F_CHG_FAULT]		= REG_FIELD(0x0C, 4, 5),
	[F_BAT_FAULT]		= REG_FIELD(0x0C, 3, 3),
	[F_NTC_FAULT]		= REG_FIELD(0x0C, 0, 2),
	/* REG0D */
	[F_FORCE_VINDPM]	= REG_FIELD(0x0D, 7, 7),
	[F_VINDPM]		= REG_FIELD(0x0D, 0, 6),
	/* REG0E */
	[F_THERM_STAT]		= REG_FIELD(0x0E, 7, 7),
	[F_BATV]		= REG_FIELD(0x0E, 0, 6),
	/* REG0F */
	[F_SYSV]		= REG_FIELD(0x0F, 0, 6),
	/* REG10 */
	[F_TSPCT]		= REG_FIELD(0x10, 0, 6),
	/* REG11 */
	[F_VBUS_GD]		= REG_FIELD(0x11, 7, 7),
	[F_VBUSV]		= REG_FIELD(0x11, 0, 6),
	/* REG12 */
	[F_ICHGR]		= REG_FIELD(0x12, 0, 6),
	/* REG13 */
	[F_VDPM_STAT]		= REG_FIELD(0x13, 7, 7),
	[F_IDPM_STAT]		= REG_FIELD(0x13, 6, 6),
	[F_IDPM_LIM]		= REG_FIELD(0x13, 0, 5),
	/* REG14 */
	[F_REG_RST]		= REG_FIELD(0x14, 7, 7),
	[F_ICO_OPTIMIZED]	= REG_FIELD(0x14, 6, 6),
	[F_PN]			= REG_FIELD(0x14, 3, 5),
	[F_TS_PROखाता]		= REG_FIELD(0x14, 2, 2),
	[F_DEV_REV]		= REG_FIELD(0x14, 0, 1)
पूर्ण;

/*
 * Most of the val -> idx conversions can be computed, given the minimum,
 * maximum and the step between values. For the rest of conversions, we use
 * lookup tables.
 */
क्रमागत bq25890_table_ids अणु
	/* range tables */
	TBL_ICHG,
	TBL_ITERM,
	TBL_IILIM,
	TBL_VREG,
	TBL_BOOSTV,
	TBL_SYSVMIN,
	TBL_VBATCOMP,
	TBL_RBATCOMP,

	/* lookup tables */
	TBL_TREG,
	TBL_BOOSTI,
पूर्ण;

/* Thermal Regulation Threshold lookup table, in degrees Celsius */
अटल स्थिर u32 bq25890_treg_tbl[] = अणु 60, 80, 100, 120 पूर्ण;

#घोषणा BQ25890_TREG_TBL_SIZE		ARRAY_SIZE(bq25890_treg_tbl)

/* Boost mode current limit lookup table, in uA */
अटल स्थिर u32 bq25890_boosti_tbl[] = अणु
	500000, 700000, 1100000, 1300000, 1600000, 1800000, 2100000, 2400000
पूर्ण;

#घोषणा BQ25890_BOOSTI_TBL_SIZE		ARRAY_SIZE(bq25890_boosti_tbl)

काष्ठा bq25890_range अणु
	u32 min;
	u32 max;
	u32 step;
पूर्ण;

काष्ठा bq25890_lookup अणु
	स्थिर u32 *tbl;
	u32 size;
पूर्ण;

अटल स्थिर जोड़ अणु
	काष्ठा bq25890_range  rt;
	काष्ठा bq25890_lookup lt;
पूर्ण bq25890_tables[] = अणु
	/* range tables */
	/* TODO: BQ25896 has max ICHG 3008 mA */
	[TBL_ICHG] =	अणु .rt = अणु0,	  5056000, 64000पूर्ण पूर्ण,	 /* uA */
	[TBL_ITERM] =	अणु .rt = अणु64000,   1024000, 64000पूर्ण पूर्ण,	 /* uA */
	[TBL_IILIM] =   अणु .rt = अणु100000,  3250000, 50000पूर्ण पूर्ण,	 /* uA */
	[TBL_VREG] =	अणु .rt = अणु3840000, 4608000, 16000पूर्ण पूर्ण,	 /* uV */
	[TBL_BOOSTV] =	अणु .rt = अणु4550000, 5510000, 64000पूर्ण पूर्ण,	 /* uV */
	[TBL_SYSVMIN] = अणु .rt = अणु3000000, 3700000, 100000पूर्ण पूर्ण,	 /* uV */
	[TBL_VBATCOMP] =अणु .rt = अणु0,        224000, 32000पूर्ण पूर्ण,	 /* uV */
	[TBL_RBATCOMP] =अणु .rt = अणु0,        140000, 20000पूर्ण पूर्ण,	 /* uOhm */

	/* lookup tables */
	[TBL_TREG] =	अणु .lt = अणुbq25890_treg_tbl, BQ25890_TREG_TBL_SIZEपूर्ण पूर्ण,
	[TBL_BOOSTI] =	अणु .lt = अणुbq25890_boosti_tbl, BQ25890_BOOSTI_TBL_SIZEपूर्ण पूर्ण
पूर्ण;

अटल पूर्णांक bq25890_field_पढ़ो(काष्ठा bq25890_device *bq,
			      क्रमागत bq25890_fields field_id)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	ret = regmap_field_पढ़ो(bq->rmap_fields[field_id], &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक bq25890_field_ग_लिखो(काष्ठा bq25890_device *bq,
			       क्रमागत bq25890_fields field_id, u8 val)
अणु
	वापस regmap_field_ग_लिखो(bq->rmap_fields[field_id], val);
पूर्ण

अटल u8 bq25890_find_idx(u32 value, क्रमागत bq25890_table_ids id)
अणु
	u8 idx;

	अगर (id >= TBL_TREG) अणु
		स्थिर u32 *tbl = bq25890_tables[id].lt.tbl;
		u32 tbl_size = bq25890_tables[id].lt.size;

		क्रम (idx = 1; idx < tbl_size && tbl[idx] <= value; idx++)
			;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा bq25890_range *rtbl = &bq25890_tables[id].rt;
		u8 rtbl_size;

		rtbl_size = (rtbl->max - rtbl->min) / rtbl->step + 1;

		क्रम (idx = 1;
		     idx < rtbl_size && (idx * rtbl->step + rtbl->min <= value);
		     idx++)
			;
	पूर्ण

	वापस idx - 1;
पूर्ण

अटल u32 bq25890_find_val(u8 idx, क्रमागत bq25890_table_ids id)
अणु
	स्थिर काष्ठा bq25890_range *rtbl;

	/* lookup table? */
	अगर (id >= TBL_TREG)
		वापस bq25890_tables[id].lt.tbl[idx];

	/* range table */
	rtbl = &bq25890_tables[id].rt;

	वापस (rtbl->min + idx * rtbl->step);
पूर्ण

क्रमागत bq25890_status अणु
	STATUS_NOT_CHARGING,
	STATUS_PRE_CHARGING,
	STATUS_FAST_CHARGING,
	STATUS_TERMINATION_DONE,
पूर्ण;

क्रमागत bq25890_chrg_fault अणु
	CHRG_FAULT_NORMAL,
	CHRG_FAULT_INPUT,
	CHRG_FAULT_THERMAL_SHUTDOWN,
	CHRG_FAULT_TIMER_EXPIRED,
पूर्ण;

अटल bool bq25890_is_adc_property(क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल irqवापस_t __bq25890_handle_irq(काष्ठा bq25890_device *bq);

अटल पूर्णांक bq25890_घातer_supply_get_property(काष्ठा घातer_supply *psy,
					     क्रमागत घातer_supply_property psp,
					     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq25890_device *bq = घातer_supply_get_drvdata(psy);
	काष्ठा bq25890_state state;
	bool करो_adc_conv;
	पूर्णांक ret;

	mutex_lock(&bq->lock);
	/* update state in हाल we lost an पूर्णांकerrupt */
	__bq25890_handle_irq(bq);
	state = bq->state;
	करो_adc_conv = !state.online && bq25890_is_adc_property(psp);
	अगर (करो_adc_conv)
		bq25890_field_ग_लिखो(bq, F_CONV_START, 1);
	mutex_unlock(&bq->lock);

	अगर (करो_adc_conv)
		regmap_field_पढ़ो_poll_समयout(bq->rmap_fields[F_CONV_START],
			ret, !ret, 25000, 1000000);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!state.online)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (state.chrg_status == STATUS_NOT_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अन्यथा अगर (state.chrg_status == STATUS_PRE_CHARGING ||
			 state.chrg_status == STATUS_FAST_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (state.chrg_status == STATUS_TERMINATION_DONE)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;

		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		अगर (!state.online || state.chrg_status == STATUS_NOT_CHARGING ||
		    state.chrg_status == STATUS_TERMINATION_DONE)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अन्यथा अगर (state.chrg_status == STATUS_PRE_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_STANDARD;
		अन्यथा अगर (state.chrg_status == STATUS_FAST_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अन्यथा /* unreachable */
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ25890_MANUFACTURER;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq25890_chip_name[bq->chip_version];
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = state.online;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (!state.chrg_fault && !state.bat_fault && !state.boost_fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अन्यथा अगर (state.bat_fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अन्यथा अगर (state.chrg_fault == CHRG_FAULT_TIMER_EXPIRED)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
		अन्यथा अगर (state.chrg_fault == CHRG_FAULT_THERMAL_SHUTDOWN)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = bq25890_find_val(bq->init_data.ichg, TBL_ICHG);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		अगर (!state.online) अणु
			val->पूर्णांकval = 0;
			अवरोध;
		पूर्ण

		ret = bq25890_field_पढ़ो(bq, F_BATV); /* पढ़ो measured value */
		अगर (ret < 0)
			वापस ret;

		/* converted_val = 2.304V + ADC_val * 20mV (table 10.3.15) */
		val->पूर्णांकval = 2304000 + ret * 20000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->पूर्णांकval = bq25890_find_val(bq->init_data.vreg, TBL_VREG);
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		val->पूर्णांकval = bq25890_find_val(bq->init_data.iprechg, TBL_ITERM);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		val->पूर्णांकval = bq25890_find_val(bq->init_data.iterm, TBL_ITERM);
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq25890_field_पढ़ो(bq, F_IILIM);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = bq25890_find_val(ret, TBL_IILIM);
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq25890_field_पढ़ो(bq, F_SYSV); /* पढ़ो measured value */
		अगर (ret < 0)
			वापस ret;

		/* converted_val = 2.304V + ADC_val * 20mV (table 10.3.15) */
		val->पूर्णांकval = 2304000 + ret * 20000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = bq25890_field_पढ़ो(bq, F_ICHGR); /* पढ़ो measured value */
		अगर (ret < 0)
			वापस ret;

		/* converted_val = ADC_val * 50mA (table 10.3.19) */
		val->पूर्णांकval = ret * -50000;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq25890_get_chip_state(काष्ठा bq25890_device *bq,
				  काष्ठा bq25890_state *state)
अणु
	पूर्णांक i, ret;

	काष्ठा अणु
		क्रमागत bq25890_fields id;
		u8 *data;
	पूर्ण state_fields[] = अणु
		अणुF_CHG_STAT,	&state->chrg_statusपूर्ण,
		अणुF_PG_STAT,	&state->onlineपूर्ण,
		अणुF_VSYS_STAT,	&state->vsys_statusपूर्ण,
		अणुF_BOOST_FAULT, &state->boost_faultपूर्ण,
		अणुF_BAT_FAULT,	&state->bat_faultपूर्ण,
		अणुF_CHG_FAULT,	&state->chrg_faultपूर्ण
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(state_fields); i++) अणु
		ret = bq25890_field_पढ़ो(bq, state_fields[i].id);
		अगर (ret < 0)
			वापस ret;

		*state_fields[i].data = ret;
	पूर्ण

	dev_dbg(bq->dev, "S:CHG/PG/VSYS=%d/%d/%d, F:CHG/BOOST/BAT=%d/%d/%d\n",
		state->chrg_status, state->online, state->vsys_status,
		state->chrg_fault, state->boost_fault, state->bat_fault);

	वापस 0;
पूर्ण

अटल irqवापस_t __bq25890_handle_irq(काष्ठा bq25890_device *bq)
अणु
	काष्ठा bq25890_state new_state;
	पूर्णांक ret;

	ret = bq25890_get_chip_state(bq, &new_state);
	अगर (ret < 0)
		वापस IRQ_NONE;

	अगर (!स_भेद(&bq->state, &new_state, माप(new_state)))
		वापस IRQ_NONE;

	अगर (!new_state.online && bq->state.online) अणु	    /* घातer हटाओd */
		/* disable ADC */
		ret = bq25890_field_ग_लिखो(bq, F_CONV_START, 0);
		अगर (ret < 0)
			जाओ error;
	पूर्ण अन्यथा अगर (new_state.online && !bq->state.online) अणु /* घातer inserted */
		/* enable ADC, to have control of अक्षरge current/voltage */
		ret = bq25890_field_ग_लिखो(bq, F_CONV_START, 1);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	bq->state = new_state;
	घातer_supply_changed(bq->अक्षरger);

	वापस IRQ_HANDLED;
error:
	dev_err(bq->dev, "Error communicating with the chip: %pe\n",
		ERR_PTR(ret));
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bq25890_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा bq25890_device *bq = निजी;
	irqवापस_t ret;

	mutex_lock(&bq->lock);
	ret = __bq25890_handle_irq(bq);
	mutex_unlock(&bq->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक bq25890_chip_reset(काष्ठा bq25890_device *bq)
अणु
	पूर्णांक ret;
	पूर्णांक rst_check_counter = 10;

	ret = bq25890_field_ग_लिखो(bq, F_REG_RST, 1);
	अगर (ret < 0)
		वापस ret;

	करो अणु
		ret = bq25890_field_पढ़ो(bq, F_REG_RST);
		अगर (ret < 0)
			वापस ret;

		usleep_range(5, 10);
	पूर्ण जबतक (ret == 1 && --rst_check_counter);

	अगर (!rst_check_counter)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक bq25890_hw_init(काष्ठा bq25890_device *bq)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	स्थिर काष्ठा अणु
		क्रमागत bq25890_fields id;
		u32 value;
	पूर्ण init_data[] = अणु
		अणुF_ICHG,	 bq->init_data.ichgपूर्ण,
		अणुF_VREG,	 bq->init_data.vregपूर्ण,
		अणुF_ITERM,	 bq->init_data.itermपूर्ण,
		अणुF_IPRECHG,	 bq->init_data.iprechgपूर्ण,
		अणुF_SYSVMIN,	 bq->init_data.sysvminपूर्ण,
		अणुF_BOOSTV,	 bq->init_data.boostvपूर्ण,
		अणुF_BOOSTI,	 bq->init_data.boostiपूर्ण,
		अणुF_BOOSTF,	 bq->init_data.boostfपूर्ण,
		अणुF_EN_ILIM,	 bq->init_data.ilim_enपूर्ण,
		अणुF_TREG,	 bq->init_data.tregपूर्ण,
		अणुF_BATCMP,	 bq->init_data.rbatcompपूर्ण,
		अणुF_VCLAMP,	 bq->init_data.vclampपूर्ण,
	पूर्ण;

	ret = bq25890_chip_reset(bq);
	अगर (ret < 0) अणु
		dev_dbg(bq->dev, "Reset failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* disable watchकरोg */
	ret = bq25890_field_ग_लिखो(bq, F_WD, 0);
	अगर (ret < 0) अणु
		dev_dbg(bq->dev, "Disabling watchdog failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* initialize currents/voltages and other parameters */
	क्रम (i = 0; i < ARRAY_SIZE(init_data); i++) अणु
		ret = bq25890_field_ग_लिखो(bq, init_data[i].id,
					  init_data[i].value);
		अगर (ret < 0) अणु
			dev_dbg(bq->dev, "Writing init data failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Configure ADC क्रम continuous conversions when अक्षरging */
	ret = bq25890_field_ग_लिखो(bq, F_CONV_RATE, !!bq->state.online);
	अगर (ret < 0) अणु
		dev_dbg(bq->dev, "Config ADC failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = bq25890_get_chip_state(bq, &bq->state);
	अगर (ret < 0) अणु
		dev_dbg(bq->dev, "Get state failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर क्रमागत घातer_supply_property bq25890_घातer_supply_props[] = अणु
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल अक्षर *bq25890_अक्षरger_supplied_to[] = अणु
	"main-battery",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bq25890_घातer_supply_desc = अणु
	.name = "bq25890-charger",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = bq25890_घातer_supply_props,
	.num_properties = ARRAY_SIZE(bq25890_घातer_supply_props),
	.get_property = bq25890_घातer_supply_get_property,
पूर्ण;

अटल पूर्णांक bq25890_घातer_supply_init(काष्ठा bq25890_device *bq)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = bq, पूर्ण;

	psy_cfg.supplied_to = bq25890_अक्षरger_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(bq25890_अक्षरger_supplied_to);

	bq->अक्षरger = घातer_supply_रेजिस्टर(bq->dev, &bq25890_घातer_supply_desc,
					    &psy_cfg);

	वापस PTR_ERR_OR_ZERO(bq->अक्षरger);
पूर्ण

अटल व्योम bq25890_usb_work(काष्ठा work_काष्ठा *data)
अणु
	पूर्णांक ret;
	काष्ठा bq25890_device *bq =
			container_of(data, काष्ठा bq25890_device, usb_work);

	चयन (bq->usb_event) अणु
	हाल USB_EVENT_ID:
		/* Enable boost mode */
		ret = bq25890_field_ग_लिखो(bq, F_OTG_CFG, 1);
		अगर (ret < 0)
			जाओ error;
		अवरोध;

	हाल USB_EVENT_NONE:
		/* Disable boost mode */
		ret = bq25890_field_ग_लिखो(bq, F_OTG_CFG, 0);
		अगर (ret < 0)
			जाओ error;

		घातer_supply_changed(bq->अक्षरger);
		अवरोध;
	पूर्ण

	वापस;

error:
	dev_err(bq->dev, "Error switching to boost/charger mode.\n");
पूर्ण

अटल पूर्णांक bq25890_usb_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				व्योम *priv)
अणु
	काष्ठा bq25890_device *bq =
			container_of(nb, काष्ठा bq25890_device, usb_nb);

	bq->usb_event = val;
	queue_work(प्रणाली_घातer_efficient_wq, &bq->usb_work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक bq25890_get_chip_version(काष्ठा bq25890_device *bq)
अणु
	पूर्णांक id, rev;

	id = bq25890_field_पढ़ो(bq, F_PN);
	अगर (id < 0) अणु
		dev_err(bq->dev, "Cannot read chip ID.\n");
		वापस id;
	पूर्ण

	rev = bq25890_field_पढ़ो(bq, F_DEV_REV);
	अगर (rev < 0) अणु
		dev_err(bq->dev, "Cannot read chip revision.\n");
		वापस rev;
	पूर्ण

	चयन (id) अणु
	हाल BQ25890_ID:
		bq->chip_version = BQ25890;
		अवरोध;

	/* BQ25892 and BQ25896 share same ID 0 */
	हाल BQ25896_ID:
		चयन (rev) अणु
		हाल 2:
			bq->chip_version = BQ25896;
			अवरोध;
		हाल 1:
			bq->chip_version = BQ25892;
			अवरोध;
		शेष:
			dev_err(bq->dev,
				"Unknown device revision %d, assume BQ25892\n",
				rev);
			bq->chip_version = BQ25892;
		पूर्ण
		अवरोध;

	हाल BQ25895_ID:
		bq->chip_version = BQ25895;
		अवरोध;

	शेष:
		dev_err(bq->dev, "Unknown chip ID %d\n", id);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq25890_irq_probe(काष्ठा bq25890_device *bq)
अणु
	काष्ठा gpio_desc *irq;

	irq = devm_gpiod_get(bq->dev, BQ25890_IRQ_PIN, GPIOD_IN);
	अगर (IS_ERR(irq)) अणु
		dev_err(bq->dev, "Could not probe irq pin.\n");
		वापस PTR_ERR(irq);
	पूर्ण

	वापस gpiod_to_irq(irq);
पूर्ण

अटल पूर्णांक bq25890_fw_पढ़ो_u32_props(काष्ठा bq25890_device *bq)
अणु
	पूर्णांक ret;
	u32 property;
	पूर्णांक i;
	काष्ठा bq25890_init_data *init = &bq->init_data;
	काष्ठा अणु
		अक्षर *name;
		bool optional;
		क्रमागत bq25890_table_ids tbl_id;
		u8 *conv_data; /* holds converted value from given property */
	पूर्ण props[] = अणु
		/* required properties */
		अणु"ti,charge-current", false, TBL_ICHG, &init->ichgपूर्ण,
		अणु"ti,battery-regulation-voltage", false, TBL_VREG, &init->vregपूर्ण,
		अणु"ti,termination-current", false, TBL_ITERM, &init->itermपूर्ण,
		अणु"ti,precharge-current", false, TBL_ITERM, &init->iprechgपूर्ण,
		अणु"ti,minimum-sys-voltage", false, TBL_SYSVMIN, &init->sysvminपूर्ण,
		अणु"ti,boost-voltage", false, TBL_BOOSTV, &init->boostvपूर्ण,
		अणु"ti,boost-max-current", false, TBL_BOOSTI, &init->boostiपूर्ण,

		/* optional properties */
		अणु"ti,thermal-regulation-threshold", true, TBL_TREG, &init->tregपूर्ण,
		अणु"ti,ibatcomp-micro-ohms", true, TBL_RBATCOMP, &init->rbatcompपूर्ण,
		अणु"ti,ibatcomp-clamp-microvolt", true, TBL_VBATCOMP, &init->vclampपूर्ण,
	पूर्ण;

	/* initialize data क्रम optional properties */
	init->treg = 3; /* 120 degrees Celsius */
	init->rbatcomp = init->vclamp = 0; /* IBAT compensation disabled */

	क्रम (i = 0; i < ARRAY_SIZE(props); i++) अणु
		ret = device_property_पढ़ो_u32(bq->dev, props[i].name,
					       &property);
		अगर (ret < 0) अणु
			अगर (props[i].optional)
				जारी;

			dev_err(bq->dev, "Unable to read property %d %s\n", ret,
				props[i].name);

			वापस ret;
		पूर्ण

		*props[i].conv_data = bq25890_find_idx(property,
						       props[i].tbl_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq25890_fw_probe(काष्ठा bq25890_device *bq)
अणु
	पूर्णांक ret;
	काष्ठा bq25890_init_data *init = &bq->init_data;

	ret = bq25890_fw_पढ़ो_u32_props(bq);
	अगर (ret < 0)
		वापस ret;

	init->ilim_en = device_property_पढ़ो_bool(bq->dev, "ti,use-ilim-pin");
	init->boostf = device_property_पढ़ो_bool(bq->dev, "ti,boost-low-freq");

	वापस 0;
पूर्ण

अटल पूर्णांक bq25890_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा bq25890_device *bq;
	पूर्णांक ret;
	पूर्णांक i;

	bq = devm_kzalloc(dev, माप(*bq), GFP_KERNEL);
	अगर (!bq)
		वापस -ENOMEM;

	bq->client = client;
	bq->dev = dev;

	mutex_init(&bq->lock);

	bq->rmap = devm_regmap_init_i2c(client, &bq25890_regmap_config);
	अगर (IS_ERR(bq->rmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(bq->rmap);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(bq25890_reg_fields); i++) अणु
		स्थिर काष्ठा reg_field *reg_fields = bq25890_reg_fields;

		bq->rmap_fields[i] = devm_regmap_field_alloc(dev, bq->rmap,
							     reg_fields[i]);
		अगर (IS_ERR(bq->rmap_fields[i])) अणु
			dev_err(dev, "cannot allocate regmap field\n");
			वापस PTR_ERR(bq->rmap_fields[i]);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, bq);

	ret = bq25890_get_chip_version(bq);
	अगर (ret) अणु
		dev_err(dev, "Cannot read chip ID or unknown chip.\n");
		वापस ret;
	पूर्ण

	अगर (!dev->platक्रमm_data) अणु
		ret = bq25890_fw_probe(bq);
		अगर (ret < 0) अणु
			dev_err(dev, "Cannot read device properties.\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	ret = bq25890_hw_init(bq);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot initialize the chip.\n");
		वापस ret;
	पूर्ण

	अगर (client->irq <= 0)
		client->irq = bq25890_irq_probe(bq);

	अगर (client->irq < 0) अणु
		dev_err(dev, "No irq resource found.\n");
		वापस client->irq;
	पूर्ण

	/* OTG reporting */
	bq->usb_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	अगर (!IS_ERR_OR_शून्य(bq->usb_phy)) अणु
		INIT_WORK(&bq->usb_work, bq25890_usb_work);
		bq->usb_nb.notअगरier_call = bq25890_usb_notअगरier;
		usb_रेजिस्टर_notअगरier(bq->usb_phy, &bq->usb_nb);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					bq25890_irq_handler_thपढ़ो,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					BQ25890_IRQ_PIN, bq);
	अगर (ret)
		जाओ irq_fail;

	ret = bq25890_घातer_supply_init(bq);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register power supply\n");
		जाओ irq_fail;
	पूर्ण

	वापस 0;

irq_fail:
	अगर (!IS_ERR_OR_शून्य(bq->usb_phy))
		usb_unरेजिस्टर_notअगरier(bq->usb_phy, &bq->usb_nb);

	वापस ret;
पूर्ण

अटल पूर्णांक bq25890_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bq25890_device *bq = i2c_get_clientdata(client);

	घातer_supply_unरेजिस्टर(bq->अक्षरger);

	अगर (!IS_ERR_OR_शून्य(bq->usb_phy))
		usb_unरेजिस्टर_notअगरier(bq->usb_phy, &bq->usb_nb);

	/* reset all रेजिस्टरs to शेष values */
	bq25890_chip_reset(bq);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bq25890_suspend(काष्ठा device *dev)
अणु
	काष्ठा bq25890_device *bq = dev_get_drvdata(dev);

	/*
	 * If अक्षरger is हटाओd, जबतक in suspend, make sure ADC is diabled
	 * since it consumes slightly more घातer.
	 */
	वापस bq25890_field_ग_लिखो(bq, F_CONV_RATE, 0);
पूर्ण

अटल पूर्णांक bq25890_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा bq25890_device *bq = dev_get_drvdata(dev);

	mutex_lock(&bq->lock);

	ret = bq25890_get_chip_state(bq, &bq->state);
	अगर (ret < 0)
		जाओ unlock;

	/* Re-enable ADC only अगर अक्षरger is plugged in. */
	अगर (bq->state.online) अणु
		ret = bq25890_field_ग_लिखो(bq, F_CONV_RATE, 1);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	/* संकेत userspace, maybe state changed जबतक suspended */
	घातer_supply_changed(bq->अक्षरger);

unlock:
	mutex_unlock(&bq->lock);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops bq25890_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bq25890_suspend, bq25890_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id bq25890_i2c_ids[] = अणु
	अणु "bq25890", 0 पूर्ण,
	अणु "bq25892", 0 पूर्ण,
	अणु "bq25895", 0 पूर्ण,
	अणु "bq25896", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq25890_i2c_ids);

अटल स्थिर काष्ठा of_device_id bq25890_of_match[] = अणु
	अणु .compatible = "ti,bq25890", पूर्ण,
	अणु .compatible = "ti,bq25892", पूर्ण,
	अणु .compatible = "ti,bq25895", पूर्ण,
	अणु .compatible = "ti,bq25896", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq25890_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id bq25890_acpi_match[] = अणु
	अणु"BQ258900", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bq25890_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver bq25890_driver = अणु
	.driver = अणु
		.name = "bq25890-charger",
		.of_match_table = of_match_ptr(bq25890_of_match),
		.acpi_match_table = ACPI_PTR(bq25890_acpi_match),
		.pm = &bq25890_pm,
	पूर्ण,
	.probe = bq25890_probe,
	.हटाओ = bq25890_हटाओ,
	.id_table = bq25890_i2c_ids,
पूर्ण;
module_i2c_driver(bq25890_driver);

MODULE_AUTHOR("Laurentiu Palcu <laurentiu.palcu@intel.com>");
MODULE_DESCRIPTION("bq25890 charger driver");
MODULE_LICENSE("GPL");
