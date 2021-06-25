<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI BQ24257 अक्षरger driver
 *
 * Copyright (C) 2015 Intel Corporation
 *
 * Datasheets:
 * https://www.ti.com/product/bq24250
 * https://www.ti.com/product/bq24251
 * https://www.ti.com/product/bq24257
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश <linux/acpi.h>
#समावेश <linux/of.h>

#घोषणा BQ24257_REG_1			0x00
#घोषणा BQ24257_REG_2			0x01
#घोषणा BQ24257_REG_3			0x02
#घोषणा BQ24257_REG_4			0x03
#घोषणा BQ24257_REG_5			0x04
#घोषणा BQ24257_REG_6			0x05
#घोषणा BQ24257_REG_7			0x06

#घोषणा BQ24257_MANUFACTURER		"Texas Instruments"
#घोषणा BQ24257_PG_GPIO			"pg"

#घोषणा BQ24257_ILIM_SET_DELAY		1000	/* msec */

/*
 * When adding support क्रम new devices make sure that क्रमागत bq2425x_chip and
 * bq2425x_chip_name[] always stay in sync!
 */
क्रमागत bq2425x_chip अणु
	BQ24250,
	BQ24251,
	BQ24257,
पूर्ण;

अटल स्थिर अक्षर *स्थिर bq2425x_chip_name[] = अणु
	"bq24250",
	"bq24251",
	"bq24257",
पूर्ण;

क्रमागत bq24257_fields अणु
	F_WD_FAULT, F_WD_EN, F_STAT, F_FAULT,			    /* REG 1 */
	F_RESET, F_IILIMIT, F_EN_STAT, F_EN_TERM, F_CE, F_HZ_MODE,  /* REG 2 */
	F_VBAT, F_USB_DET,					    /* REG 3 */
	F_ICHG, F_ITERM,					    /* REG 4 */
	F_LOOP_STATUS, F_LOW_CHG, F_DPDM_EN, F_CE_STATUS, F_VINDPM, /* REG 5 */
	F_X2_TMR_EN, F_TMR, F_SYSOFF, F_TS_EN, F_TS_STAT,	    /* REG 6 */
	F_VOVP, F_CLR_VDP, F_FORCE_BATDET, F_FORCE_PTM,		    /* REG 7 */

	F_MAX_FIELDS
पूर्ण;

/* initial field values, converted from uV/uA */
काष्ठा bq24257_init_data अणु
	u8 ichg;	/* अक्षरge current      */
	u8 vbat;	/* regulation voltage  */
	u8 iterm;	/* termination current */
	u8 iilimit;	/* input current limit */
	u8 vovp;	/* over voltage protection voltage */
	u8 vindpm;	/* VDMP input threshold voltage */
पूर्ण;

काष्ठा bq24257_state अणु
	u8 status;
	u8 fault;
	bool घातer_good;
पूर्ण;

काष्ठा bq24257_device अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा घातer_supply *अक्षरger;

	क्रमागत bq2425x_chip chip;

	काष्ठा regmap *rmap;
	काष्ठा regmap_field *rmap_fields[F_MAX_FIELDS];

	काष्ठा gpio_desc *pg;

	काष्ठा delayed_work iilimit_setup_work;

	काष्ठा bq24257_init_data init_data;
	काष्ठा bq24257_state state;

	काष्ठा mutex lock; /* protect state data */

	bool iilimit_स्वतःset_enable;
पूर्ण;

अटल bool bq24257_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BQ24257_REG_2:
	हाल BQ24257_REG_4:
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config bq24257_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ24257_REG_7,
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = bq24257_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा reg_field bq24257_reg_fields[] = अणु
	/* REG 1 */
	[F_WD_FAULT]		= REG_FIELD(BQ24257_REG_1, 7, 7),
	[F_WD_EN]		= REG_FIELD(BQ24257_REG_1, 6, 6),
	[F_STAT]		= REG_FIELD(BQ24257_REG_1, 4, 5),
	[F_FAULT]		= REG_FIELD(BQ24257_REG_1, 0, 3),
	/* REG 2 */
	[F_RESET]		= REG_FIELD(BQ24257_REG_2, 7, 7),
	[F_IILIMIT]		= REG_FIELD(BQ24257_REG_2, 4, 6),
	[F_EN_STAT]		= REG_FIELD(BQ24257_REG_2, 3, 3),
	[F_EN_TERM]		= REG_FIELD(BQ24257_REG_2, 2, 2),
	[F_CE]			= REG_FIELD(BQ24257_REG_2, 1, 1),
	[F_HZ_MODE]		= REG_FIELD(BQ24257_REG_2, 0, 0),
	/* REG 3 */
	[F_VBAT]		= REG_FIELD(BQ24257_REG_3, 2, 7),
	[F_USB_DET]		= REG_FIELD(BQ24257_REG_3, 0, 1),
	/* REG 4 */
	[F_ICHG]		= REG_FIELD(BQ24257_REG_4, 3, 7),
	[F_ITERM]		= REG_FIELD(BQ24257_REG_4, 0, 2),
	/* REG 5 */
	[F_LOOP_STATUS]		= REG_FIELD(BQ24257_REG_5, 6, 7),
	[F_LOW_CHG]		= REG_FIELD(BQ24257_REG_5, 5, 5),
	[F_DPDM_EN]		= REG_FIELD(BQ24257_REG_5, 4, 4),
	[F_CE_STATUS]		= REG_FIELD(BQ24257_REG_5, 3, 3),
	[F_VINDPM]		= REG_FIELD(BQ24257_REG_5, 0, 2),
	/* REG 6 */
	[F_X2_TMR_EN]		= REG_FIELD(BQ24257_REG_6, 7, 7),
	[F_TMR]			= REG_FIELD(BQ24257_REG_6, 5, 6),
	[F_SYSOFF]		= REG_FIELD(BQ24257_REG_6, 4, 4),
	[F_TS_EN]		= REG_FIELD(BQ24257_REG_6, 3, 3),
	[F_TS_STAT]		= REG_FIELD(BQ24257_REG_6, 0, 2),
	/* REG 7 */
	[F_VOVP]		= REG_FIELD(BQ24257_REG_7, 5, 7),
	[F_CLR_VDP]		= REG_FIELD(BQ24257_REG_7, 4, 4),
	[F_FORCE_BATDET]	= REG_FIELD(BQ24257_REG_7, 3, 3),
	[F_FORCE_PTM]		= REG_FIELD(BQ24257_REG_7, 2, 2)
पूर्ण;

अटल स्थिर u32 bq24257_vbat_map[] = अणु
	3500000, 3520000, 3540000, 3560000, 3580000, 3600000, 3620000, 3640000,
	3660000, 3680000, 3700000, 3720000, 3740000, 3760000, 3780000, 3800000,
	3820000, 3840000, 3860000, 3880000, 3900000, 3920000, 3940000, 3960000,
	3980000, 4000000, 4020000, 4040000, 4060000, 4080000, 4100000, 4120000,
	4140000, 4160000, 4180000, 4200000, 4220000, 4240000, 4260000, 4280000,
	4300000, 4320000, 4340000, 4360000, 4380000, 4400000, 4420000, 4440000
पूर्ण;

#घोषणा BQ24257_VBAT_MAP_SIZE		ARRAY_SIZE(bq24257_vbat_map)

अटल स्थिर u32 bq24257_ichg_map[] = अणु
	500000, 550000, 600000, 650000, 700000, 750000, 800000, 850000, 900000,
	950000, 1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000,
	1350000, 1400000, 1450000, 1500000, 1550000, 1600000, 1650000, 1700000,
	1750000, 1800000, 1850000, 1900000, 1950000, 2000000
पूर्ण;

#घोषणा BQ24257_ICHG_MAP_SIZE		ARRAY_SIZE(bq24257_ichg_map)

अटल स्थिर u32 bq24257_iterm_map[] = अणु
	50000, 75000, 100000, 125000, 150000, 175000, 200000, 225000
पूर्ण;

#घोषणा BQ24257_ITERM_MAP_SIZE		ARRAY_SIZE(bq24257_iterm_map)

अटल स्थिर u32 bq24257_iilimit_map[] = अणु
	100000, 150000, 500000, 900000, 1500000, 2000000
पूर्ण;

#घोषणा BQ24257_IILIMIT_MAP_SIZE	ARRAY_SIZE(bq24257_iilimit_map)

अटल स्थिर u32 bq24257_vovp_map[] = अणु
	6000000, 6500000, 7000000, 8000000, 9000000, 9500000, 10000000,
	10500000
पूर्ण;

#घोषणा BQ24257_VOVP_MAP_SIZE		ARRAY_SIZE(bq24257_vovp_map)

अटल स्थिर u32 bq24257_vindpm_map[] = अणु
	4200000, 4280000, 4360000, 4440000, 4520000, 4600000, 4680000,
	4760000
पूर्ण;

#घोषणा BQ24257_VINDPM_MAP_SIZE		ARRAY_SIZE(bq24257_vindpm_map)

अटल पूर्णांक bq24257_field_पढ़ो(काष्ठा bq24257_device *bq,
			      क्रमागत bq24257_fields field_id)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	ret = regmap_field_पढ़ो(bq->rmap_fields[field_id], &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक bq24257_field_ग_लिखो(काष्ठा bq24257_device *bq,
			       क्रमागत bq24257_fields field_id, u8 val)
अणु
	वापस regmap_field_ग_लिखो(bq->rmap_fields[field_id], val);
पूर्ण

अटल u8 bq24257_find_idx(u32 value, स्थिर u32 *map, u8 map_size)
अणु
	u8 idx;

	क्रम (idx = 1; idx < map_size; idx++)
		अगर (value < map[idx])
			अवरोध;

	वापस idx - 1;
पूर्ण

क्रमागत bq24257_status अणु
	STATUS_READY,
	STATUS_CHARGE_IN_PROGRESS,
	STATUS_CHARGE_DONE,
	STATUS_FAULT,
पूर्ण;

क्रमागत bq24257_fault अणु
	FAULT_NORMAL,
	FAULT_INPUT_OVP,
	FAULT_INPUT_UVLO,
	FAULT_SLEEP,
	FAULT_BAT_TS,
	FAULT_BAT_OVP,
	FAULT_TS,
	FAULT_TIMER,
	FAULT_NO_BAT,
	FAULT_ISET,
	FAULT_INPUT_LDO_LOW,
पूर्ण;

अटल पूर्णांक bq24257_get_input_current_limit(काष्ठा bq24257_device *bq,
					   जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;

	ret = bq24257_field_पढ़ो(bq, F_IILIMIT);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The "External ILIM" and "Production & Test" modes are not exposed
	 * through this driver and not being covered by the lookup table.
	 * Should such a mode have become active let's वापस an error rather
	 * than exceeding the bounds of the lookup table and वापसing
	 * garbage.
	 */
	अगर (ret >= BQ24257_IILIMIT_MAP_SIZE)
		वापस -ENODATA;

	val->पूर्णांकval = bq24257_iilimit_map[ret];

	वापस 0;
पूर्ण

अटल पूर्णांक bq24257_set_input_current_limit(काष्ठा bq24257_device *bq,
					स्थिर जोड़ घातer_supply_propval *val)
अणु
	/*
	 * Address the हाल where the user manually sets an input current limit
	 * जबतक the अक्षरger स्वतः-detection mechanism is is active. In this
	 * हाल we want to पात and go straight to the user-specअगरied value.
	 */
	अगर (bq->iilimit_स्वतःset_enable)
		cancel_delayed_work_sync(&bq->iilimit_setup_work);

	वापस bq24257_field_ग_लिखो(bq, F_IILIMIT,
				   bq24257_find_idx(val->पूर्णांकval,
						    bq24257_iilimit_map,
						    BQ24257_IILIMIT_MAP_SIZE));
पूर्ण

अटल पूर्णांक bq24257_घातer_supply_get_property(काष्ठा घातer_supply *psy,
					     क्रमागत घातer_supply_property psp,
					     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24257_device *bq = घातer_supply_get_drvdata(psy);
	काष्ठा bq24257_state state;

	mutex_lock(&bq->lock);
	state = bq->state;
	mutex_unlock(&bq->lock);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!state.घातer_good)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (state.status == STATUS_READY)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अन्यथा अगर (state.status == STATUS_CHARGE_IN_PROGRESS)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (state.status == STATUS_CHARGE_DONE)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ24257_MANUFACTURER;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq2425x_chip_name[bq->chip];
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = state.घातer_good;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		चयन (state.fault) अणु
		हाल FAULT_NORMAL:
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
			अवरोध;

		हाल FAULT_INPUT_OVP:
		हाल FAULT_BAT_OVP:
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
			अवरोध;

		हाल FAULT_TS:
		हाल FAULT_BAT_TS:
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
			अवरोध;

		हाल FAULT_TIMER:
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
			अवरोध;

		शेष:
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		val->पूर्णांकval = bq24257_ichg_map[bq->init_data.ichg];
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = bq24257_ichg_map[BQ24257_ICHG_MAP_SIZE - 1];
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->पूर्णांकval = bq24257_vbat_map[bq->init_data.vbat];
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->पूर्णांकval = bq24257_vbat_map[BQ24257_VBAT_MAP_SIZE - 1];
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		val->पूर्णांकval = bq24257_iterm_map[bq->init_data.iterm];
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस bq24257_get_input_current_limit(bq, val);

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq24257_घातer_supply_set_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property prop,
					स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24257_device *bq = घातer_supply_get_drvdata(psy);

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस bq24257_set_input_current_limit(bq, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bq24257_घातer_supply_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक bq24257_get_chip_state(काष्ठा bq24257_device *bq,
				  काष्ठा bq24257_state *state)
अणु
	पूर्णांक ret;

	ret = bq24257_field_पढ़ो(bq, F_STAT);
	अगर (ret < 0)
		वापस ret;

	state->status = ret;

	ret = bq24257_field_पढ़ो(bq, F_FAULT);
	अगर (ret < 0)
		वापस ret;

	state->fault = ret;

	अगर (bq->pg)
		state->घातer_good = !gpiod_get_value_cansleep(bq->pg);
	अन्यथा
		/*
		 * If we have a chip without a dedicated घातer-good GPIO or
		 * some other explicit bit that would provide this inक्रमmation
		 * assume the घातer is good अगर there is no supply related
		 * fault - and not good otherwise. There is a possibility क्रम
		 * other errors to mask that घातer in fact is not good but this
		 * is probably the best we can करो here.
		 */
		चयन (state->fault) अणु
		हाल FAULT_INPUT_OVP:
		हाल FAULT_INPUT_UVLO:
		हाल FAULT_INPUT_LDO_LOW:
			state->घातer_good = false;
			अवरोध;
		शेष:
			state->घातer_good = true;
		पूर्ण

	वापस 0;
पूर्ण

अटल bool bq24257_state_changed(काष्ठा bq24257_device *bq,
				  काष्ठा bq24257_state *new_state)
अणु
	पूर्णांक ret;

	mutex_lock(&bq->lock);
	ret = (bq->state.status != new_state->status ||
	       bq->state.fault != new_state->fault ||
	       bq->state.घातer_good != new_state->घातer_good);
	mutex_unlock(&bq->lock);

	वापस ret;
पूर्ण

क्रमागत bq24257_loop_status अणु
	LOOP_STATUS_NONE,
	LOOP_STATUS_IN_DPM,
	LOOP_STATUS_IN_CURRENT_LIMIT,
	LOOP_STATUS_THERMAL,
पूर्ण;

क्रमागत bq24257_in_ilimit अणु
	IILIMIT_100,
	IILIMIT_150,
	IILIMIT_500,
	IILIMIT_900,
	IILIMIT_1500,
	IILIMIT_2000,
	IILIMIT_EXT,
	IILIMIT_NONE,
पूर्ण;

क्रमागत bq24257_vovp अणु
	VOVP_6000,
	VOVP_6500,
	VOVP_7000,
	VOVP_8000,
	VOVP_9000,
	VOVP_9500,
	VOVP_10000,
	VOVP_10500
पूर्ण;

क्रमागत bq24257_vindpm अणु
	VINDPM_4200,
	VINDPM_4280,
	VINDPM_4360,
	VINDPM_4440,
	VINDPM_4520,
	VINDPM_4600,
	VINDPM_4680,
	VINDPM_4760
पूर्ण;

क्रमागत bq24257_port_type अणु
	PORT_TYPE_DCP,		/* Dedicated Charging Port */
	PORT_TYPE_CDP,		/* Charging Downstream Port */
	PORT_TYPE_SDP,		/* Standard Downstream Port */
	PORT_TYPE_NON_STANDARD,
पूर्ण;

क्रमागत bq24257_safety_समयr अणु
	SAFETY_TIMER_45,
	SAFETY_TIMER_360,
	SAFETY_TIMER_540,
	SAFETY_TIMER_NONE,
पूर्ण;

अटल पूर्णांक bq24257_iilimit_स्वतःset(काष्ठा bq24257_device *bq)
अणु
	पूर्णांक loop_status;
	पूर्णांक iilimit;
	पूर्णांक port_type;
	पूर्णांक ret;
	स्थिर u8 new_iilimit[] = अणु
		[PORT_TYPE_DCP] = IILIMIT_2000,
		[PORT_TYPE_CDP] = IILIMIT_2000,
		[PORT_TYPE_SDP] = IILIMIT_500,
		[PORT_TYPE_NON_STANDARD] = IILIMIT_500
	पूर्ण;

	ret = bq24257_field_पढ़ो(bq, F_LOOP_STATUS);
	अगर (ret < 0)
		जाओ error;

	loop_status = ret;

	ret = bq24257_field_पढ़ो(bq, F_IILIMIT);
	अगर (ret < 0)
		जाओ error;

	iilimit = ret;

	/*
	 * All USB ports should be able to handle 500mA. If not, DPM will lower
	 * the अक्षरging current to accommodate the घातer source. No need to set
	 * a lower IILIMIT value.
	 */
	अगर (loop_status == LOOP_STATUS_IN_DPM && iilimit == IILIMIT_500)
		वापस 0;

	ret = bq24257_field_पढ़ो(bq, F_USB_DET);
	अगर (ret < 0)
		जाओ error;

	port_type = ret;

	ret = bq24257_field_ग_लिखो(bq, F_IILIMIT, new_iilimit[port_type]);
	अगर (ret < 0)
		जाओ error;

	ret = bq24257_field_ग_लिखो(bq, F_TMR, SAFETY_TIMER_360);
	अगर (ret < 0)
		जाओ error;

	ret = bq24257_field_ग_लिखो(bq, F_CLR_VDP, 1);
	अगर (ret < 0)
		जाओ error;

	dev_dbg(bq->dev, "port/loop = %d/%d -> iilimit = %d\n",
		port_type, loop_status, new_iilimit[port_type]);

	वापस 0;

error:
	dev_err(bq->dev, "%s: Error communicating with the chip.\n", __func__);
	वापस ret;
पूर्ण

अटल व्योम bq24257_iilimit_setup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bq24257_device *bq = container_of(work, काष्ठा bq24257_device,
						 iilimit_setup_work.work);

	bq24257_iilimit_स्वतःset(bq);
पूर्ण

अटल व्योम bq24257_handle_state_change(काष्ठा bq24257_device *bq,
					काष्ठा bq24257_state *new_state)
अणु
	पूर्णांक ret;
	काष्ठा bq24257_state old_state;

	mutex_lock(&bq->lock);
	old_state = bq->state;
	mutex_unlock(&bq->lock);

	/*
	 * Handle BQ2425x state changes observing whether the D+/D- based input
	 * current limit स्वतःset functionality is enabled.
	 */
	अगर (!new_state->घातer_good) अणु
		dev_dbg(bq->dev, "Power removed\n");
		अगर (bq->iilimit_स्वतःset_enable) अणु
			cancel_delayed_work_sync(&bq->iilimit_setup_work);

			/* activate D+/D- port detection algorithm */
			ret = bq24257_field_ग_लिखो(bq, F_DPDM_EN, 1);
			अगर (ret < 0)
				जाओ error;
		पूर्ण
		/*
		 * When घातer is हटाओd always वापस to the शेष input
		 * current limit as configured during probe.
		 */
		ret = bq24257_field_ग_लिखो(bq, F_IILIMIT, bq->init_data.iilimit);
		अगर (ret < 0)
			जाओ error;
	पूर्ण अन्यथा अगर (!old_state.घातer_good) अणु
		dev_dbg(bq->dev, "Power inserted\n");

		अगर (bq->iilimit_स्वतःset_enable)
			/* configure input current limit */
			schedule_delayed_work(&bq->iilimit_setup_work,
				      msecs_to_jअगरfies(BQ24257_ILIM_SET_DELAY));
	पूर्ण अन्यथा अगर (new_state->fault == FAULT_NO_BAT) अणु
		dev_warn(bq->dev, "Battery removed\n");
	पूर्ण अन्यथा अगर (new_state->fault == FAULT_TIMER) अणु
		dev_err(bq->dev, "Safety timer expired! Battery dead?\n");
	पूर्ण

	वापस;

error:
	dev_err(bq->dev, "%s: Error communicating with the chip.\n", __func__);
पूर्ण

अटल irqवापस_t bq24257_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	पूर्णांक ret;
	काष्ठा bq24257_device *bq = निजी;
	काष्ठा bq24257_state state;

	ret = bq24257_get_chip_state(bq, &state);
	अगर (ret < 0)
		वापस IRQ_HANDLED;

	अगर (!bq24257_state_changed(bq, &state))
		वापस IRQ_HANDLED;

	dev_dbg(bq->dev, "irq(state changed): status/fault/pg = %d/%d/%d\n",
		state.status, state.fault, state.घातer_good);

	bq24257_handle_state_change(bq, &state);

	mutex_lock(&bq->lock);
	bq->state = state;
	mutex_unlock(&bq->lock);

	घातer_supply_changed(bq->अक्षरger);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bq24257_hw_init(काष्ठा bq24257_device *bq)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा bq24257_state state;

	स्थिर काष्ठा अणु
		पूर्णांक field;
		u32 value;
	पूर्ण init_data[] = अणु
		अणुF_ICHG, bq->init_data.ichgपूर्ण,
		अणुF_VBAT, bq->init_data.vbatपूर्ण,
		अणुF_ITERM, bq->init_data.itermपूर्ण,
		अणुF_VOVP, bq->init_data.vovpपूर्ण,
		अणुF_VINDPM, bq->init_data.vindpmपूर्ण,
	पूर्ण;

	/*
	 * Disable the watchकरोg समयr to prevent the IC from going back to
	 * शेष settings after 50 seconds of I2C inactivity.
	 */
	ret = bq24257_field_ग_लिखो(bq, F_WD_EN, 0);
	अगर (ret < 0)
		वापस ret;

	/* configure the अक्षरge currents and voltages */
	क्रम (i = 0; i < ARRAY_SIZE(init_data); i++) अणु
		ret = bq24257_field_ग_लिखो(bq, init_data[i].field,
					  init_data[i].value);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = bq24257_get_chip_state(bq, &state);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&bq->lock);
	bq->state = state;
	mutex_unlock(&bq->lock);

	अगर (!bq->iilimit_स्वतःset_enable) अणु
		dev_dbg(bq->dev, "manually setting iilimit = %u\n",
			bq->init_data.iilimit);

		/* program fixed input current limit */
		ret = bq24257_field_ग_लिखो(bq, F_IILIMIT,
					  bq->init_data.iilimit);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (!state.घातer_good)
		/* activate D+/D- detection algorithm */
		ret = bq24257_field_ग_लिखो(bq, F_DPDM_EN, 1);
	अन्यथा अगर (state.fault != FAULT_NO_BAT)
		ret = bq24257_iilimit_स्वतःset(bq);

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property bq24257_घातer_supply_props[] = अणु
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
पूर्ण;

अटल अक्षर *bq24257_अक्षरger_supplied_to[] = अणु
	"main-battery",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bq24257_घातer_supply_desc = अणु
	.name = "bq24257-charger",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = bq24257_घातer_supply_props,
	.num_properties = ARRAY_SIZE(bq24257_घातer_supply_props),
	.get_property = bq24257_घातer_supply_get_property,
	.set_property = bq24257_घातer_supply_set_property,
	.property_is_ग_लिखोable = bq24257_घातer_supply_property_is_ग_लिखोable,
पूर्ण;

अटल sमाप_प्रकार bq24257_show_ovp_voltage(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq24257_device *bq = घातer_supply_get_drvdata(psy);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 bq24257_vovp_map[bq->init_data.vovp]);
पूर्ण

अटल sमाप_प्रकार bq24257_show_in_dpm_voltage(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq24257_device *bq = घातer_supply_get_drvdata(psy);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 bq24257_vindpm_map[bq->init_data.vindpm]);
पूर्ण

अटल sमाप_प्रकार bq24257_sysfs_show_enable(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq24257_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	अगर (म_भेद(attr->attr.name, "high_impedance_enable") == 0)
		ret = bq24257_field_पढ़ो(bq, F_HZ_MODE);
	अन्यथा अगर (म_भेद(attr->attr.name, "sysoff_enable") == 0)
		ret = bq24257_field_पढ़ो(bq, F_SYSOFF);
	अन्यथा
		वापस -EINVAL;

	अगर (ret < 0)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार bq24257_sysfs_set_enable(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf,
					माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq24257_device *bq = घातer_supply_get_drvdata(psy);
	दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	अगर (म_भेद(attr->attr.name, "high_impedance_enable") == 0)
		ret = bq24257_field_ग_लिखो(bq, F_HZ_MODE, (bool)val);
	अन्यथा अगर (म_भेद(attr->attr.name, "sysoff_enable") == 0)
		ret = bq24257_field_ग_लिखो(bq, F_SYSOFF, (bool)val);
	अन्यथा
		वापस -EINVAL;

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(ovp_voltage, S_IRUGO, bq24257_show_ovp_voltage, शून्य);
अटल DEVICE_ATTR(in_dpm_voltage, S_IRUGO, bq24257_show_in_dpm_voltage, शून्य);
अटल DEVICE_ATTR(high_impedance_enable, S_IWUSR | S_IRUGO,
		   bq24257_sysfs_show_enable, bq24257_sysfs_set_enable);
अटल DEVICE_ATTR(sysoff_enable, S_IWUSR | S_IRUGO,
		   bq24257_sysfs_show_enable, bq24257_sysfs_set_enable);

अटल काष्ठा attribute *bq24257_अक्षरger_sysfs_attrs[] = अणु
	&dev_attr_ovp_voltage.attr,
	&dev_attr_in_dpm_voltage.attr,
	&dev_attr_high_impedance_enable.attr,
	&dev_attr_sysoff_enable.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(bq24257_अक्षरger_sysfs);

अटल पूर्णांक bq24257_घातer_supply_init(काष्ठा bq24257_device *bq)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = bq, पूर्ण;

	psy_cfg.attr_grp = bq24257_अक्षरger_sysfs_groups;
	psy_cfg.supplied_to = bq24257_अक्षरger_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(bq24257_अक्षरger_supplied_to);

	bq->अक्षरger = devm_घातer_supply_रेजिस्टर(bq->dev,
						 &bq24257_घातer_supply_desc,
						 &psy_cfg);

	वापस PTR_ERR_OR_ZERO(bq->अक्षरger);
पूर्ण

अटल व्योम bq24257_pg_gpio_probe(काष्ठा bq24257_device *bq)
अणु
	bq->pg = devm_gpiod_get_optional(bq->dev, BQ24257_PG_GPIO, GPIOD_IN);

	अगर (PTR_ERR(bq->pg) == -EPROBE_DEFER) अणु
		dev_info(bq->dev, "probe retry requested for PG pin\n");
		वापस;
	पूर्ण अन्यथा अगर (IS_ERR(bq->pg)) अणु
		dev_err(bq->dev, "error probing PG pin\n");
		bq->pg = शून्य;
		वापस;
	पूर्ण

	अगर (bq->pg)
		dev_dbg(bq->dev, "probed PG pin = %d\n", desc_to_gpio(bq->pg));
पूर्ण

अटल पूर्णांक bq24257_fw_probe(काष्ठा bq24257_device *bq)
अणु
	पूर्णांक ret;
	u32 property;

	/* Required properties */
	ret = device_property_पढ़ो_u32(bq->dev, "ti,charge-current", &property);
	अगर (ret < 0)
		वापस ret;

	bq->init_data.ichg = bq24257_find_idx(property, bq24257_ichg_map,
					      BQ24257_ICHG_MAP_SIZE);

	ret = device_property_पढ़ो_u32(bq->dev, "ti,battery-regulation-voltage",
				       &property);
	अगर (ret < 0)
		वापस ret;

	bq->init_data.vbat = bq24257_find_idx(property, bq24257_vbat_map,
					      BQ24257_VBAT_MAP_SIZE);

	ret = device_property_पढ़ो_u32(bq->dev, "ti,termination-current",
				       &property);
	अगर (ret < 0)
		वापस ret;

	bq->init_data.iterm = bq24257_find_idx(property, bq24257_iterm_map,
					       BQ24257_ITERM_MAP_SIZE);

	/* Optional properties. If not provided use reasonable शेष. */
	ret = device_property_पढ़ो_u32(bq->dev, "ti,current-limit",
				       &property);
	अगर (ret < 0) अणु
		bq->iilimit_स्वतःset_enable = true;

		/*
		 * Explicitly set a शेष value which will be needed क्रम
		 * devices that करोn't support the स्वतःmatic setting of the input
		 * current limit through the अक्षरger type detection mechanism.
		 */
		bq->init_data.iilimit = IILIMIT_500;
	पूर्ण अन्यथा
		bq->init_data.iilimit =
				bq24257_find_idx(property,
						 bq24257_iilimit_map,
						 BQ24257_IILIMIT_MAP_SIZE);

	ret = device_property_पढ़ो_u32(bq->dev, "ti,ovp-voltage",
				       &property);
	अगर (ret < 0)
		bq->init_data.vovp = VOVP_6500;
	अन्यथा
		bq->init_data.vovp = bq24257_find_idx(property,
						      bq24257_vovp_map,
						      BQ24257_VOVP_MAP_SIZE);

	ret = device_property_पढ़ो_u32(bq->dev, "ti,in-dpm-voltage",
				       &property);
	अगर (ret < 0)
		bq->init_data.vindpm = VINDPM_4360;
	अन्यथा
		bq->init_data.vindpm =
				bq24257_find_idx(property,
						 bq24257_vindpm_map,
						 BQ24257_VINDPM_MAP_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक bq24257_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा acpi_device_id *acpi_id;
	काष्ठा bq24257_device *bq;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(dev, "No support for SMBUS_BYTE_DATA\n");
		वापस -ENODEV;
	पूर्ण

	bq = devm_kzalloc(dev, माप(*bq), GFP_KERNEL);
	अगर (!bq)
		वापस -ENOMEM;

	bq->client = client;
	bq->dev = dev;

	अगर (ACPI_HANDLE(dev)) अणु
		acpi_id = acpi_match_device(dev->driver->acpi_match_table,
					    &client->dev);
		अगर (!acpi_id) अणु
			dev_err(dev, "Failed to match ACPI device\n");
			वापस -ENODEV;
		पूर्ण
		bq->chip = (क्रमागत bq2425x_chip)acpi_id->driver_data;
	पूर्ण अन्यथा अणु
		bq->chip = (क्रमागत bq2425x_chip)id->driver_data;
	पूर्ण

	mutex_init(&bq->lock);

	bq->rmap = devm_regmap_init_i2c(client, &bq24257_regmap_config);
	अगर (IS_ERR(bq->rmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(bq->rmap);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(bq24257_reg_fields); i++) अणु
		स्थिर काष्ठा reg_field *reg_fields = bq24257_reg_fields;

		bq->rmap_fields[i] = devm_regmap_field_alloc(dev, bq->rmap,
							     reg_fields[i]);
		अगर (IS_ERR(bq->rmap_fields[i])) अणु
			dev_err(dev, "cannot allocate regmap field\n");
			वापस PTR_ERR(bq->rmap_fields[i]);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, bq);

	अगर (!dev->platक्रमm_data) अणु
		ret = bq24257_fw_probe(bq);
		अगर (ret < 0) अणु
			dev_err(dev, "Cannot read device properties.\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	/*
	 * The BQ24250 करोesn't support the D+/D- based अक्षरger type detection
	 * used क्रम the स्वतःmatic setting of the input current limit setting so
	 * explicitly disable that feature.
	 */
	अगर (bq->chip == BQ24250)
		bq->iilimit_स्वतःset_enable = false;

	अगर (bq->iilimit_स्वतःset_enable)
		INIT_DELAYED_WORK(&bq->iilimit_setup_work,
				  bq24257_iilimit_setup_work);

	/*
	 * The BQ24250 करोesn't have a dedicated Power Good (PG) pin so let's
	 * not probe क्रम it and instead use a SW-based approach to determine
	 * the PG state. We also use a SW-based approach क्रम all other devices
	 * अगर the PG pin is either not defined or can't be probed.
	 */
	अगर (bq->chip != BQ24250)
		bq24257_pg_gpio_probe(bq);

	अगर (PTR_ERR(bq->pg) == -EPROBE_DEFER)
		वापस PTR_ERR(bq->pg);
	अन्यथा अगर (!bq->pg)
		dev_info(bq->dev, "using SW-based power-good detection\n");

	/* reset all रेजिस्टरs to शेषs */
	ret = bq24257_field_ग_लिखो(bq, F_RESET, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Put the RESET bit back to 0, in cache. For some reason the HW always
	 * वापसs 1 on this bit, so this is the only way to aव्योम resetting the
	 * chip every समय we update another field in this रेजिस्टर.
	 */
	ret = bq24257_field_ग_लिखो(bq, F_RESET, 0);
	अगर (ret < 0)
		वापस ret;

	ret = bq24257_hw_init(bq);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot initialize the chip.\n");
		वापस ret;
	पूर्ण

	ret = bq24257_घातer_supply_init(bq);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register power supply\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					bq24257_irq_handler_thपढ़ो,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					bq2425x_chip_name[bq->chip], bq);
	अगर (ret) अणु
		dev_err(dev, "Failed to request IRQ #%d\n", client->irq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq24257_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bq24257_device *bq = i2c_get_clientdata(client);

	अगर (bq->iilimit_स्वतःset_enable)
		cancel_delayed_work_sync(&bq->iilimit_setup_work);

	bq24257_field_ग_लिखो(bq, F_RESET, 1); /* reset to शेषs */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bq24257_suspend(काष्ठा device *dev)
अणु
	काष्ठा bq24257_device *bq = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (bq->iilimit_स्वतःset_enable)
		cancel_delayed_work_sync(&bq->iilimit_setup_work);

	/* reset all रेजिस्टरs to शेष (and activate standalone mode) */
	ret = bq24257_field_ग_लिखो(bq, F_RESET, 1);
	अगर (ret < 0)
		dev_err(bq->dev, "Cannot reset chip to standalone mode.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bq24257_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा bq24257_device *bq = dev_get_drvdata(dev);

	ret = regcache_drop_region(bq->rmap, BQ24257_REG_1, BQ24257_REG_7);
	अगर (ret < 0)
		वापस ret;

	ret = bq24257_field_ग_लिखो(bq, F_RESET, 0);
	अगर (ret < 0)
		वापस ret;

	ret = bq24257_hw_init(bq);
	अगर (ret < 0) अणु
		dev_err(bq->dev, "Cannot init chip after resume.\n");
		वापस ret;
	पूर्ण

	/* संकेत userspace, maybe state changed जबतक suspended */
	घातer_supply_changed(bq->अक्षरger);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops bq24257_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bq24257_suspend, bq24257_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id bq24257_i2c_ids[] = अणु
	अणु "bq24250", BQ24250 पूर्ण,
	अणु "bq24251", BQ24251 पूर्ण,
	अणु "bq24257", BQ24257 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq24257_i2c_ids);

अटल स्थिर काष्ठा of_device_id bq24257_of_match[] = अणु
	अणु .compatible = "ti,bq24250", पूर्ण,
	अणु .compatible = "ti,bq24251", पूर्ण,
	अणु .compatible = "ti,bq24257", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq24257_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id bq24257_acpi_match[] = अणु
	अणु "BQ242500", BQ24250 पूर्ण,
	अणु "BQ242510", BQ24251 पूर्ण,
	अणु "BQ242570", BQ24257 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bq24257_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver bq24257_driver = अणु
	.driver = अणु
		.name = "bq24257-charger",
		.of_match_table = of_match_ptr(bq24257_of_match),
		.acpi_match_table = ACPI_PTR(bq24257_acpi_match),
		.pm = &bq24257_pm,
	पूर्ण,
	.probe = bq24257_probe,
	.हटाओ = bq24257_हटाओ,
	.id_table = bq24257_i2c_ids,
पूर्ण;
module_i2c_driver(bq24257_driver);

MODULE_AUTHOR("Laurentiu Palcu <laurentiu.palcu@intel.com>");
MODULE_DESCRIPTION("bq24257 charger driver");
MODULE_LICENSE("GPL");
