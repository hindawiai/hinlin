<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ROHM BD99954 अक्षरger driver
 *
 * Copyright (C) 2020 Rohm Semiconductors
 *	Originally written by:
 *		Mikko Mutanen <mikko.mutanen@fi.rohmeurope.com>
 *		Markus Laine <markus.laine@fi.rohmeurope.com>
 *	Bugs added by:
 *		Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>
 */

/*
 *   The battery अक्षरging profile of BD99954.
 *
 *   Curve (1) represents अक्षरging current.
 *   Curve (2) represents battery voltage.
 *
 *   The BD99954 data sheet भागides अक्षरging to three phases.
 *   a) Trickle-अक्षरge with स्थिरant current (8).
 *   b) pre-अक्षरge with स्थिरant current (6)
 *   c) fast-अक्षरge, first with स्थिरant current (5) phase. After
 *      the battery voltage has reached target level (4) we have स्थिरant
 *      voltage phase until अक्षरging current has dropped to termination
 *      level (7)
 *
 *    V ^                                                        ^ I
 *      .                                                        .
 *      .                                                        .
 *(4)` `.` ` ` ` ` ` ` ` ` ` ` ` ` ` ----------------------------.
 *      .                           :/                           .
 *      .                     o----+/:/ ` ` ` ` ` ` ` ` ` ` ` ` `.` ` (5)
 *      .                     +   ::  +                          .
 *      .                     +  /-   --                         .
 *      .                     +`/-     +                         .
 *      .                     o/-      -:                        .
 *      .                    .s.        +`                       .
 *      .                  .--+         `/                       .
 *      .               ..``  +          .:                      .
 *      .             -`      +           --                     .
 *      .    (2)  ...``       +            :-                    .
 *      .    ...``            +             -:                   .
 *(3)` `.`.""  ` ` ` `+-------- ` ` ` ` ` ` `.:` ` ` ` ` ` ` ` ` .` ` (6)
 *      .             +                       `:.                .
 *      .             +                         -:               .
 *      .             +                           -:.            .
 *      .             +                             .--.         .
 *      .   (1)       +                                `.+` ` ` `.` ` (7)
 *      -..............` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` + ` ` ` .` ` (8)
 *      .                                                +       -
 *      -------------------------------------------------+++++++++-->
 *      |   trickle   |  pre  |          fast            |
 *
 * Details of DT properties क्रम dअगरferent limits can be found from BD99954
 * device tree binding करोcumentation.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linear_range.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

#समावेश "bd99954-charger.h"

काष्ठा battery_data अणु
	u16 preअक्षरge_current;	/* Trickle-अक्षरge Current */
	u16 fc_reg_voltage;	/* Fast Charging Regulation Voltage */
	u16 voltage_min;
	u16 voltage_max;
पूर्ण;

/* Initial field values, converted to initial रेजिस्टर values */
काष्ठा bd9995x_init_data अणु
	u16 vsysreg_set;	/* VSYS Regulation Setting */
	u16 ibus_lim_set;	/* VBUS input current limitation */
	u16 icc_lim_set;	/* VCC/VACP Input Current Limit Setting */
	u16 itrich_set;		/* Trickle-अक्षरge Current Setting */
	u16 iprech_set;		/* Pre-Charge Current Setting */
	u16 ichg_set;		/* Fast-Charge स्थिरant current */
	u16 vfastchg_reg_set1;	/* Fast Charging Regulation Voltage */
	u16 vprechg_th_set;	/* Pre-अक्षरge Voltage Threshold Setting */
	u16 vrechg_set;		/* Re-अक्षरge Battery Voltage Setting */
	u16 vbatovp_set;	/* Battery Over Voltage Threshold Setting */
	u16 iterm_set;		/* Charging termination current */
पूर्ण;

काष्ठा bd9995x_state अणु
	u8 online;
	u16 chgsपंचांग_status;
	u16 vbat_vsys_status;
	u16 vbus_vcc_status;
पूर्ण;

काष्ठा bd9995x_device अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा घातer_supply *अक्षरger;

	काष्ठा regmap *rmap;
	काष्ठा regmap_field *rmap_fields[F_MAX_FIELDS];

	पूर्णांक chip_id;
	पूर्णांक chip_rev;
	काष्ठा bd9995x_init_data init_data;
	काष्ठा bd9995x_state state;

	काष्ठा mutex lock; /* Protect state data */
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9995x_पढ़ोonly_reg_ranges[] = अणु
	regmap_reg_range(CHGSTM_STATUS, SEL_ILIM_VAL),
	regmap_reg_range(IOUT_DACIN_VAL, IOUT_DACIN_VAL),
	regmap_reg_range(VCC_UCD_STATUS, VCC_IDD_STATUS),
	regmap_reg_range(VBUS_UCD_STATUS, VBUS_IDD_STATUS),
	regmap_reg_range(CHIP_ID, CHIP_REV),
	regmap_reg_range(SYSTEM_STATUS, SYSTEM_STATUS),
	regmap_reg_range(IBATP_VAL, VBAT_AVE_VAL),
	regmap_reg_range(VTH_VAL, EXTIADP_AVE_VAL),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9995x_ग_लिखोable_regs = अणु
	.no_ranges = bd9995x_पढ़ोonly_reg_ranges,
	.n_no_ranges = ARRAY_SIZE(bd9995x_पढ़ोonly_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9995x_अस्थिर_reg_ranges[] = अणु
	regmap_reg_range(CHGSTM_STATUS, WDT_STATUS),
	regmap_reg_range(VCC_UCD_STATUS, VCC_IDD_STATUS),
	regmap_reg_range(VBUS_UCD_STATUS, VBUS_IDD_STATUS),
	regmap_reg_range(INT0_STATUS, INT7_STATUS),
	regmap_reg_range(SYSTEM_STATUS, SYSTEM_CTRL_SET),
	regmap_reg_range(IBATP_VAL, EXTIADP_AVE_VAL), /* Measurement regs */
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9995x_अस्थिर_regs = अणु
	.yes_ranges = bd9995x_अस्थिर_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(bd9995x_अस्थिर_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg regmap_range_cfg[] = अणु
	अणु
	.selector_reg     = MAP_SET,
	.selector_mask    = 0xFFFF,
	.selector_shअगरt   = 0,
	.winकरोw_start     = 0,
	.winकरोw_len       = 0x100,
	.range_min        = 0 * 0x100,
	.range_max        = 3 * 0x100,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bd9995x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.reg_stride = 1,

	.max_रेजिस्टर = 3 * 0x100,
	.cache_type = REGCACHE_RBTREE,

	.ranges = regmap_range_cfg,
	.num_ranges = ARRAY_SIZE(regmap_range_cfg),
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.wr_table = &bd9995x_ग_लिखोable_regs,
	.अस्थिर_table = &bd9995x_अस्थिर_regs,
पूर्ण;

क्रमागत bd9995x_chrg_fault अणु
	CHRG_FAULT_NORMAL,
	CHRG_FAULT_INPUT,
	CHRG_FAULT_THERMAL_SHUTDOWN,
	CHRG_FAULT_TIMER_EXPIRED,
पूर्ण;

अटल पूर्णांक bd9995x_get_prop_batt_health(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, पंचांगp;

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_BATTEMP], &पंचांगp);
	अगर (ret)
		वापस POWER_SUPPLY_HEALTH_UNKNOWN;

	/* TODO: Check these against datasheet page 34 */

	चयन (पंचांगp) अणु
	हाल ROOM:
		वापस POWER_SUPPLY_HEALTH_GOOD;
	हाल HOT1:
	हाल HOT2:
	हाल HOT3:
		वापस POWER_SUPPLY_HEALTH_OVERHEAT;
	हाल COLD1:
	हाल COLD2:
		वापस POWER_SUPPLY_HEALTH_COLD;
	हाल TEMP_DIS:
	हाल BATT_OPEN:
	शेष:
		वापस POWER_SUPPLY_HEALTH_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक bd9995x_get_prop_अक्षरge_type(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, पंचांगp;

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_CHGSTM_STATE], &पंचांगp);
	अगर (ret)
		वापस POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;

	चयन (पंचांगp) अणु
	हाल CHGSTM_TRICKLE_CHARGE:
	हाल CHGSTM_PRE_CHARGE:
		वापस POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
	हाल CHGSTM_FAST_CHARGE:
		वापस POWER_SUPPLY_CHARGE_TYPE_FAST;
	हाल CHGSTM_TOP_OFF:
	हाल CHGSTM_DONE:
	हाल CHGSTM_SUSPEND:
		वापस POWER_SUPPLY_CHARGE_TYPE_NONE;
	शेष: /* Rest of the states are error related, no अक्षरging */
		वापस POWER_SUPPLY_CHARGE_TYPE_NONE;
	पूर्ण
पूर्ण

अटल bool bd9995x_get_prop_batt_present(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, पंचांगp;

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_BATTEMP], &पंचांगp);
	अगर (ret)
		वापस false;

	वापस पंचांगp != BATT_OPEN;
पूर्ण

अटल पूर्णांक bd9995x_get_prop_batt_voltage(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, पंचांगp;

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_VBAT_VAL], &पंचांगp);
	अगर (ret)
		वापस 0;

	पंचांगp = min(पंचांगp, 19200);

	वापस पंचांगp * 1000;
पूर्ण

अटल पूर्णांक bd9995x_get_prop_batt_current(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, पंचांगp;

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_IBATP_VAL], &पंचांगp);
	अगर (ret)
		वापस 0;

	वापस पंचांगp * 1000;
पूर्ण

#घोषणा DEFAULT_BATTERY_TEMPERATURE 250

अटल पूर्णांक bd9995x_get_prop_batt_temp(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, पंचांगp;

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_THERM_VAL], &पंचांगp);
	अगर (ret)
		वापस DEFAULT_BATTERY_TEMPERATURE;

	वापस (200 - पंचांगp) * 10;
पूर्ण

अटल पूर्णांक bd9995x_घातer_supply_get_property(काष्ठा घातer_supply *psy,
					     क्रमागत घातer_supply_property psp,
					     जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret, पंचांगp;
	काष्ठा bd9995x_device *bd = घातer_supply_get_drvdata(psy);
	काष्ठा bd9995x_state state;

	mutex_lock(&bd->lock);
	state = bd->state;
	mutex_unlock(&bd->lock);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		चयन (state.chgsपंचांग_status) अणु
		हाल CHGSTM_TRICKLE_CHARGE:
		हाल CHGSTM_PRE_CHARGE:
		हाल CHGSTM_FAST_CHARGE:
		हाल CHGSTM_TOP_OFF:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;

		हाल CHGSTM_DONE:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
			अवरोध;

		हाल CHGSTM_SUSPEND:
		हाल CHGSTM_TEMPERATURE_ERROR_1:
		हाल CHGSTM_TEMPERATURE_ERROR_2:
		हाल CHGSTM_TEMPERATURE_ERROR_3:
		हाल CHGSTM_TEMPERATURE_ERROR_4:
		हाल CHGSTM_TEMPERATURE_ERROR_5:
		हाल CHGSTM_TEMPERATURE_ERROR_6:
		हाल CHGSTM_TEMPERATURE_ERROR_7:
		हाल CHGSTM_THERMAL_SHUT_DOWN_1:
		हाल CHGSTM_THERMAL_SHUT_DOWN_2:
		हाल CHGSTM_THERMAL_SHUT_DOWN_3:
		हाल CHGSTM_THERMAL_SHUT_DOWN_4:
		हाल CHGSTM_THERMAL_SHUT_DOWN_5:
		हाल CHGSTM_THERMAL_SHUT_DOWN_6:
		हाल CHGSTM_THERMAL_SHUT_DOWN_7:
		हाल CHGSTM_BATTERY_ERROR:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;

		शेष:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BD9995X_MANUFACTURER;
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = state.online;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = regmap_field_पढ़ो(bd->rmap_fields[F_IBATP_VAL], &पंचांगp);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = पंचांगp * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_AVG:
		ret = regmap_field_पढ़ो(bd->rmap_fields[F_IBATP_AVE_VAL], &पंचांगp);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = पंचांगp * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		/*
		 * Currently the DT uses this property to give the
		 * target current क्रम fast-अक्षरging स्थिरant current phase.
		 * I think it is correct in a sense.
		 *
		 * Yet, this prop we पढ़ो and वापस here is the programmed
		 * safety limit क्रम combined input currents. This feels
		 * also correct in a sense.
		 *
		 * However, this results a mismatch to DT value and value
		 * पढ़ो from sysfs.
		 */
		ret = regmap_field_पढ़ो(bd->rmap_fields[F_SEL_ILIM_VAL], &पंचांगp);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = पंचांगp * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		अगर (!state.online) अणु
			val->पूर्णांकval = 0;
			अवरोध;
		पूर्ण

		ret = regmap_field_पढ़ो(bd->rmap_fields[F_VFASTCHG_REG_SET1],
					&पंचांगp);
		अगर (ret)
			वापस ret;

		/*
		 * The actual range : 2560 to 19200 mV. No matter what the
		 * रेजिस्टर says
		 */
		val->पूर्णांकval = clamp_val(पंचांगp << 4, 2560, 19200);
		val->पूर्णांकval *= 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = regmap_field_पढ़ो(bd->rmap_fields[F_ITERM_SET], &पंचांगp);
		अगर (ret)
			वापस ret;
		/* Start step is 64 mA */
		val->पूर्णांकval = पंचांगp << 6;
		/* Maximum is 1024 mA - no matter what रेजिस्टर says */
		val->पूर्णांकval = min(val->पूर्णांकval, 1024);
		val->पूर्णांकval *= 1000;
		अवरोध;

	/* Battery properties which we access through अक्षरger */
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = bd9995x_get_prop_batt_present(bd);
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = bd9995x_get_prop_batt_voltage(bd);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = bd9995x_get_prop_batt_current(bd);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		val->पूर्णांकval = bd9995x_get_prop_अक्षरge_type(bd);
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = bd9995x_get_prop_batt_health(bd);
		अवरोध;

	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = bd9995x_get_prop_batt_temp(bd);
		अवरोध;

	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = "bd99954";
		अवरोध;

	शेष:
		वापस -EINVAL;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd9995x_get_chip_state(काष्ठा bd9995x_device *bd,
				  काष्ठा bd9995x_state *state)
अणु
	पूर्णांक i, ret, पंचांगp;
	काष्ठा अणु
		काष्ठा regmap_field *id;
		u16 *data;
	पूर्ण state_fields[] = अणु
		अणु
			bd->rmap_fields[F_CHGSTM_STATE], &state->chgsपंचांग_status,
		पूर्ण, अणु
			bd->rmap_fields[F_VBAT_VSYS_STATUS],
			&state->vbat_vsys_status,
		पूर्ण, अणु
			bd->rmap_fields[F_VBUS_VCC_STATUS],
			&state->vbus_vcc_status,
		पूर्ण,
	पूर्ण;


	क्रम (i = 0; i < ARRAY_SIZE(state_fields); i++) अणु
		ret = regmap_field_पढ़ो(state_fields[i].id, &पंचांगp);
		अगर (ret)
			वापस ret;

		*state_fields[i].data = पंचांगp;
	पूर्ण

	अगर (state->vbus_vcc_status & STATUS_VCC_DET ||
	    state->vbus_vcc_status & STATUS_VBUS_DET)
		state->online = 1;
	अन्यथा
		state->online = 0;

	वापस 0;
पूर्ण

अटल irqवापस_t bd9995x_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा bd9995x_device *bd = निजी;
	पूर्णांक ret, status, mask, i;
	अचिन्हित दीर्घ पंचांगp;
	काष्ठा bd9995x_state state;

	/*
	 * The bd9995x करोes not seem to generate big amount of पूर्णांकerrupts.
	 * The logic regarding which पूर्णांकerrupts can cause relevant
	 * status changes seem to be pretty complex.
	 *
	 * So lets implement really simple and hopefully bullet-proof handler:
	 * It करोes not really matter which IRQ we handle, we just go and
	 * re-पढ़ो all पूर्णांकeresting statuses + give the framework a nudge.
	 *
	 * Other option would be building a _complex_ and error prone logic
	 * trying to decide what could have been changed (resulting this IRQ
	 * we are now handling). During the normal operation the BD99954 करोes
	 * not seem to be generating much of पूर्णांकerrupts so benefit from such
	 * logic would probably be minimal.
	 */

	ret = regmap_पढ़ो(bd->rmap, INT0_STATUS, &status);
	अगर (ret) अणु
		dev_err(bd->dev, "Failed to read IRQ status\n");
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_INT0_SET], &mask);
	अगर (ret) अणु
		dev_err(bd->dev, "Failed to read IRQ mask\n");
		वापस IRQ_NONE;
	पूर्ण

	/* Handle only IRQs that are not masked */
	status &= mask;
	पंचांगp = status;

	/* Lowest bit करोes not represent any sub-रेजिस्टरs */
	पंचांगp >>= 1;

	/*
	 * Mask and ack IRQs we will handle (+ the idiot bit)
	 */
	ret = regmap_field_ग_लिखो(bd->rmap_fields[F_INT0_SET], 0);
	अगर (ret) अणु
		dev_err(bd->dev, "Failed to mask F_INT0\n");
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_ग_लिखो(bd->rmap, INT0_STATUS, status);
	अगर (ret) अणु
		dev_err(bd->dev, "Failed to ack F_INT0\n");
		जाओ err_umask;
	पूर्ण

	क्रम_each_set_bit(i, &पंचांगp, 7) अणु
		पूर्णांक sub_status, sub_mask;
		पूर्णांक sub_status_reg[] = अणु
			INT1_STATUS, INT2_STATUS, INT3_STATUS, INT4_STATUS,
			INT5_STATUS, INT6_STATUS, INT7_STATUS,
		पूर्ण;
		काष्ठा regmap_field *sub_mask_f[] = अणु
			bd->rmap_fields[F_INT1_SET],
			bd->rmap_fields[F_INT2_SET],
			bd->rmap_fields[F_INT3_SET],
			bd->rmap_fields[F_INT4_SET],
			bd->rmap_fields[F_INT5_SET],
			bd->rmap_fields[F_INT6_SET],
			bd->rmap_fields[F_INT7_SET],
		पूर्ण;

		/* Clear sub IRQs */
		ret = regmap_पढ़ो(bd->rmap, sub_status_reg[i], &sub_status);
		अगर (ret) अणु
			dev_err(bd->dev, "Failed to read IRQ sub-status\n");
			जाओ err_umask;
		पूर्ण

		ret = regmap_field_पढ़ो(sub_mask_f[i], &sub_mask);
		अगर (ret) अणु
			dev_err(bd->dev, "Failed to read IRQ sub-mask\n");
			जाओ err_umask;
		पूर्ण

		/* Ack active sub-statuses */
		sub_status &= sub_mask;

		ret = regmap_ग_लिखो(bd->rmap, sub_status_reg[i], sub_status);
		अगर (ret) अणु
			dev_err(bd->dev, "Failed to ack sub-IRQ\n");
			जाओ err_umask;
		पूर्ण
	पूर्ण

	ret = regmap_field_ग_लिखो(bd->rmap_fields[F_INT0_SET], mask);
	अगर (ret)
		/* May as well retry once */
		जाओ err_umask;

	/* Read whole chip state */
	ret = bd9995x_get_chip_state(bd, &state);
	अगर (ret < 0) अणु
		dev_err(bd->dev, "Failed to read chip state\n");
	पूर्ण अन्यथा अणु
		mutex_lock(&bd->lock);
		bd->state = state;
		mutex_unlock(&bd->lock);

		घातer_supply_changed(bd->अक्षरger);
	पूर्ण

	वापस IRQ_HANDLED;

err_umask:
	ret = regmap_field_ग_लिखो(bd->rmap_fields[F_INT0_SET], mask);
	अगर (ret)
		dev_err(bd->dev,
		"Failed to un-mask F_INT0 - IRQ permanently disabled\n");

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक __bd9995x_chip_reset(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret, state;
	पूर्णांक rst_check_counter = 10;
	u16 पंचांगp = ALLRST | OTPLD;

	ret = regmap_raw_ग_लिखो(bd->rmap, SYSTEM_CTRL_SET, &पंचांगp, 2);
	अगर (ret < 0)
		वापस ret;

	करो अणु
		ret = regmap_field_पढ़ो(bd->rmap_fields[F_OTPLD_STATE], &state);
		अगर (ret)
			वापस ret;

		msleep(10);
	पूर्ण जबतक (state == 0 && --rst_check_counter);

	अगर (!rst_check_counter) अणु
		dev_err(bd->dev, "chip reset not completed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	पंचांगp = 0;
	ret = regmap_raw_ग_लिखो(bd->rmap, SYSTEM_CTRL_SET, &पंचांगp, 2);

	वापस ret;
पूर्ण

अटल पूर्णांक bd9995x_hw_init(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा bd9995x_state state;
	काष्ठा bd9995x_init_data *id = &bd->init_data;

	स्थिर काष्ठा अणु
		क्रमागत bd9995x_fields id;
		u16 value;
	पूर्ण init_data[] = अणु
		/* Enable the अक्षरging trigger after SDP अक्षरger attached */
		अणुF_SDP_CHG_TRIG_EN,	1पूर्ण,
		/* Enable अक्षरging trigger after SDP अक्षरger attached */
		अणुF_SDP_CHG_TRIG,	1पूर्ण,
		/* Disable अक्षरging trigger by BC1.2 detection */
		अणुF_VBUS_BC_DISEN,	1पूर्ण,
		/* Disable अक्षरging trigger by BC1.2 detection */
		अणुF_VCC_BC_DISEN,	1पूर्ण,
		/* Disable स्वतःmatic limitation of the input current */
		अणुF_ILIM_AUTO_DISEN,	1पूर्ण,
		/* Select current limitation when SDP अक्षरger attached*/
		अणुF_SDP_500_SEL,		1पूर्ण,
		/* Select current limitation when DCP अक्षरger attached */
		अणुF_DCP_2500_SEL,	1पूर्ण,
		अणुF_VSYSREG_SET,		id->vsysreg_setपूर्ण,
		/* Activate USB अक्षरging and DC/DC converter */
		अणुF_USB_SUS,		0पूर्ण,
		/* DCDC घड़ी: 1200 kHz*/
		अणुF_DCDC_CLK_SEL,	3पूर्ण,
		/* Enable अक्षरging */
		अणुF_CHG_EN,		1पूर्ण,
		/* Disable Input current Limit setting voltage measurement */
		अणुF_EXTIADPEN,		0पूर्ण,
		/* Disable input current limiting */
		अणुF_VSYS_PRIORITY,	1पूर्ण,
		अणुF_IBUS_LIM_SET,	id->ibus_lim_setपूर्ण,
		अणुF_ICC_LIM_SET,		id->icc_lim_setपूर्ण,
		/* Charge Termination Current Setting to 0*/
		अणुF_ITERM_SET,		id->iterm_setपूर्ण,
		/* Trickle-अक्षरge Current Setting */
		अणुF_ITRICH_SET,		id->itrich_setपूर्ण,
		/* Pre-अक्षरge Current setting */
		अणुF_IPRECH_SET,		id->iprech_setपूर्ण,
		/* Fast Charge Current क्रम स्थिरant current phase */
		अणुF_ICHG_SET,		id->ichg_setपूर्ण,
		/* Fast Charge Voltage Regulation Setting */
		अणुF_VFASTCHG_REG_SET1,	id->vfastchg_reg_set1पूर्ण,
		/* Set Pre-अक्षरge Voltage Threshold क्रम trickle अक्षरging. */
		अणुF_VPRECHG_TH_SET,	id->vprechg_th_setपूर्ण,
		अणुF_VRECHG_SET,		id->vrechg_setपूर्ण,
		अणुF_VBATOVP_SET,		id->vbatovp_setपूर्ण,
		/* Reverse buck boost voltage Setting */
		अणुF_VRBOOST_SET,		0पूर्ण,
		/* Disable fast-अक्षरging watchकरोg */
		अणुF_WDT_FST,		0पूर्ण,
		/* Disable pre-अक्षरging watchकरोg */
		अणुF_WDT_PRE,		0पूर्ण,
		/* Power save off */
		अणुF_POWER_SAVE_MODE,	0पूर्ण,
		अणुF_INT1_SET,		INT1_ALLपूर्ण,
		अणुF_INT2_SET,		INT2_ALLपूर्ण,
		अणुF_INT3_SET,		INT3_ALLपूर्ण,
		अणुF_INT4_SET,		INT4_ALLपूर्ण,
		अणुF_INT5_SET,		INT5_ALLपूर्ण,
		अणुF_INT6_SET,		INT6_ALLपूर्ण,
		अणुF_INT7_SET,		INT7_ALLपूर्ण,
	पूर्ण;

	/*
	 * Currently we initialize अक्षरger to a known state at startup.
	 * If we want to allow क्रम example the boot code to initialize
	 * अक्षरger we should get rid of this.
	 */
	ret = __bd9995x_chip_reset(bd);
	अगर (ret < 0)
		वापस ret;

	/* Initialize currents/voltages and other parameters */
	क्रम (i = 0; i < ARRAY_SIZE(init_data); i++) अणु
		ret = regmap_field_ग_लिखो(bd->rmap_fields[init_data[i].id],
					 init_data[i].value);
		अगर (ret) अणु
			dev_err(bd->dev, "failed to initialize charger (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = bd9995x_get_chip_state(bd, &state);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&bd->lock);
	bd->state = state;
	mutex_unlock(&bd->lock);

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property bd9995x_घातer_supply_props[] = अणु
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_AVG,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	/* Battery props we access through अक्षरger */
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_MODEL_NAME,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bd9995x_घातer_supply_desc = अणु
	.name = "bd9995x-charger",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = bd9995x_घातer_supply_props,
	.num_properties = ARRAY_SIZE(bd9995x_घातer_supply_props),
	.get_property = bd9995x_घातer_supply_get_property,
पूर्ण;

/*
 * Limit configurations क्रम vbus-input-current and vcc-vacp-input-current
 * Minimum limit is 0 uA. Max is 511 * 32000 uA = 16352000 uA. This is
 * configured by writing a रेजिस्टर so that each increment in रेजिस्टर
 * value equals to 32000 uA limit increment.
 *
 * Eg, value 0x0 is limit 0, value 0x1 is limit 32000, ...
 * Describe the setting in linear_range table.
 */
अटल स्थिर काष्ठा linear_range input_current_limit_ranges[] = अणु
	अणु
		.min = 0,
		.step = 32000,
		.min_sel = 0x0,
		.max_sel = 0x1ff,
	पूर्ण,
पूर्ण;

/* Possible trickle, pre-अक्षरging and termination current values */
अटल स्थिर काष्ठा linear_range अक्षरging_current_ranges[] = अणु
	अणु
		.min = 0,
		.step = 64000,
		.min_sel = 0x0,
		.max_sel = 0x10,
	पूर्ण, अणु
		.min = 1024000,
		.step = 0,
		.min_sel = 0x11,
		.max_sel = 0x1f,
	पूर्ण,
पूर्ण;

/*
 * Fast अक्षरging voltage regulation, starting re-अक्षरging limit
 * and battery over voltage protection have same possible values
 */
अटल स्थिर काष्ठा linear_range अक्षरge_voltage_regulation_ranges[] = अणु
	अणु
		.min = 2560000,
		.step = 0,
		.min_sel = 0,
		.max_sel = 0xA0,
	पूर्ण, अणु
		.min = 2560000,
		.step = 16000,
		.min_sel = 0xA0,
		.max_sel = 0x4B0,
	पूर्ण, अणु
		.min = 19200000,
		.step = 0,
		.min_sel = 0x4B0,
		.max_sel = 0x7FF,
	पूर्ण,
पूर्ण;

/* Possible VSYS voltage regulation values */
अटल स्थिर काष्ठा linear_range vsys_voltage_regulation_ranges[] = अणु
	अणु
		.min = 2560000,
		.step = 0,
		.min_sel = 0,
		.max_sel = 0x28,
	पूर्ण, अणु
		.min = 2560000,
		.step = 64000,
		.min_sel = 0x28,
		.max_sel = 0x12C,
	पूर्ण, अणु
		.min = 19200000,
		.step = 0,
		.min_sel = 0x12C,
		.max_sel = 0x1FF,
	पूर्ण,
पूर्ण;

/* Possible settings क्रम चयनing from trickle to pre-अक्षरging limits */
अटल स्थिर काष्ठा linear_range trickle_to_pre_threshold_ranges[] = अणु
	अणु
		.min = 2048000,
		.step = 0,
		.min_sel = 0,
		.max_sel = 0x20,
	पूर्ण, अणु
		.min = 2048000,
		.step = 64000,
		.min_sel = 0x20,
		.max_sel = 0x12C,
	पूर्ण, अणु
		.min = 19200000,
		.step = 0,
		.min_sel = 0x12C,
		.max_sel = 0x1FF
	पूर्ण
पूर्ण;

/* Possible current values क्रम fast-अक्षरging स्थिरant current phase */
अटल स्थिर काष्ठा linear_range fast_अक्षरge_current_ranges[] = अणु
	अणु
		.min = 0,
		.step = 64000,
		.min_sel = 0,
		.max_sel = 0xFF,
	पूर्ण
पूर्ण;

काष्ठा battery_init अणु
	स्थिर अक्षर *name;
	पूर्णांक *info_data;
	स्थिर काष्ठा linear_range *range;
	पूर्णांक ranges;
	u16 *data;
पूर्ण;

काष्ठा dt_init अणु
	अक्षर *prop;
	स्थिर काष्ठा linear_range *range;
	पूर्णांक ranges;
	u16 *data;
पूर्ण;

अटल पूर्णांक bd9995x_fw_probe(काष्ठा bd9995x_device *bd)
अणु
	पूर्णांक ret;
	काष्ठा घातer_supply_battery_info info;
	u32 property;
	पूर्णांक i;
	पूर्णांक regval;
	bool found;
	काष्ठा bd9995x_init_data *init = &bd->init_data;
	काष्ठा battery_init battery_inits[] = अणु
		अणु
			.name = "trickle-charging current",
			.info_data = &info.trickleअक्षरge_current_ua,
			.range = &अक्षरging_current_ranges[0],
			.ranges = 2,
			.data = &init->itrich_set,
		पूर्ण, अणु
			.name = "pre-charging current",
			.info_data = &info.preअक्षरge_current_ua,
			.range = &अक्षरging_current_ranges[0],
			.ranges = 2,
			.data = &init->iprech_set,
		पूर्ण, अणु
			.name = "pre-to-trickle charge voltage threshold",
			.info_data = &info.preअक्षरge_voltage_max_uv,
			.range = &trickle_to_pre_threshold_ranges[0],
			.ranges = 2,
			.data = &init->vprechg_th_set,
		पूर्ण, अणु
			.name = "charging termination current",
			.info_data = &info.अक्षरge_term_current_ua,
			.range = &अक्षरging_current_ranges[0],
			.ranges = 2,
			.data = &init->iterm_set,
		पूर्ण, अणु
			.name = "charging re-start voltage",
			.info_data = &info.अक्षरge_restart_voltage_uv,
			.range = &अक्षरge_voltage_regulation_ranges[0],
			.ranges = 2,
			.data = &init->vrechg_set,
		पूर्ण, अणु
			.name = "battery overvoltage limit",
			.info_data = &info.overvoltage_limit_uv,
			.range = &अक्षरge_voltage_regulation_ranges[0],
			.ranges = 2,
			.data = &init->vbatovp_set,
		पूर्ण, अणु
			.name = "fast-charging max current",
			.info_data = &info.स्थिरant_अक्षरge_current_max_ua,
			.range = &fast_अक्षरge_current_ranges[0],
			.ranges = 1,
			.data = &init->ichg_set,
		पूर्ण, अणु
			.name = "fast-charging voltage",
			.info_data = &info.स्थिरant_अक्षरge_voltage_max_uv,
			.range = &अक्षरge_voltage_regulation_ranges[0],
			.ranges = 2,
			.data = &init->vfastchg_reg_set1,
		पूर्ण,
	पूर्ण;
	काष्ठा dt_init props[] = अणु
		अणु
			.prop = "rohm,vsys-regulation-microvolt",
			.range = &vsys_voltage_regulation_ranges[0],
			.ranges = 2,
			.data = &init->vsysreg_set,
		पूर्ण, अणु
			.prop = "rohm,vbus-input-current-limit-microamp",
			.range = &input_current_limit_ranges[0],
			.ranges = 1,
			.data = &init->ibus_lim_set,
		पूर्ण, अणु
			.prop = "rohm,vcc-input-current-limit-microamp",
			.range = &input_current_limit_ranges[0],
			.ranges = 1,
			.data = &init->icc_lim_set,
		पूर्ण,
	पूर्ण;

	/*
	 * The घातer_supply_get_battery_info() करोes not support getting values
	 * from ACPI. Let's fix it अगर ACPI is required here.
	 */
	ret = घातer_supply_get_battery_info(bd->अक्षरger, &info);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(battery_inits); i++) अणु
		पूर्णांक val = *battery_inits[i].info_data;
		स्थिर काष्ठा linear_range *range = battery_inits[i].range;
		पूर्णांक ranges = battery_inits[i].ranges;

		अगर (val == -EINVAL)
			जारी;

		ret = linear_range_get_selector_low_array(range, ranges, val,
							  &regval, &found);
		अगर (ret) अणु
			dev_err(bd->dev, "Unsupported value for %s\n",
				battery_inits[i].name);

			घातer_supply_put_battery_info(bd->अक्षरger, &info);
			वापस -EINVAL;
		पूर्ण
		अगर (!found) अणु
			dev_warn(bd->dev,
				 "Unsupported value for %s - using smaller\n",
				 battery_inits[i].name);
		पूर्ण
		*(battery_inits[i].data) = regval;
	पूर्ण

	घातer_supply_put_battery_info(bd->अक्षरger, &info);

	क्रम (i = 0; i < ARRAY_SIZE(props); i++) अणु
		ret = device_property_पढ़ो_u32(bd->dev, props[i].prop,
					       &property);
		अगर (ret < 0) अणु
			dev_err(bd->dev, "failed to read %s", props[i].prop);

			वापस ret;
		पूर्ण

		ret = linear_range_get_selector_low_array(props[i].range,
							  props[i].ranges,
							  property, &regval,
							  &found);
		अगर (ret) अणु
			dev_err(bd->dev, "Unsupported value for '%s'\n",
				props[i].prop);

			वापस -EINVAL;
		पूर्ण

		अगर (!found) अणु
			dev_warn(bd->dev,
				 "Unsupported value for '%s' - using smaller\n",
				 props[i].prop);
		पूर्ण

		*(props[i].data) = regval;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bd9995x_chip_reset(व्योम *bd)
अणु
	__bd9995x_chip_reset(bd);
पूर्ण

अटल पूर्णांक bd9995x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा bd9995x_device *bd;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	bd = devm_kzalloc(dev, माप(*bd), GFP_KERNEL);
	अगर (!bd)
		वापस -ENOMEM;

	bd->client = client;
	bd->dev = dev;
	psy_cfg.drv_data = bd;
	psy_cfg.of_node = dev->of_node;

	mutex_init(&bd->lock);

	bd->rmap = devm_regmap_init_i2c(client, &bd9995x_regmap_config);
	अगर (IS_ERR(bd->rmap)) अणु
		dev_err(dev, "Failed to setup register access via i2c\n");
		वापस PTR_ERR(bd->rmap);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(bd9995x_reg_fields); i++) अणु
		स्थिर काष्ठा reg_field *reg_fields = bd9995x_reg_fields;

		bd->rmap_fields[i] = devm_regmap_field_alloc(dev, bd->rmap,
							     reg_fields[i]);
		अगर (IS_ERR(bd->rmap_fields[i])) अणु
			dev_err(dev, "cannot allocate regmap field\n");
			वापस PTR_ERR(bd->rmap_fields[i]);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, bd);

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_CHIP_ID], &bd->chip_id);
	अगर (ret) अणु
		dev_err(dev, "Cannot read chip ID.\n");
		वापस ret;
	पूर्ण

	अगर (bd->chip_id != BD99954_ID) अणु
		dev_err(dev, "Chip with ID=0x%x, not supported!\n",
			bd->chip_id);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_field_पढ़ो(bd->rmap_fields[F_CHIP_REV], &bd->chip_rev);
	अगर (ret) अणु
		dev_err(dev, "Cannot read revision.\n");
		वापस ret;
	पूर्ण

	dev_info(bd->dev, "Found BD99954 chip rev %d\n", bd->chip_rev);

	/*
	 * We need to init the psy beक्रमe we can call
	 * घातer_supply_get_battery_info() क्रम it
	 */
	bd->अक्षरger = devm_घातer_supply_रेजिस्टर(bd->dev,
						 &bd9995x_घातer_supply_desc,
						&psy_cfg);
	अगर (IS_ERR(bd->अक्षरger)) अणु
		dev_err(dev, "Failed to register power supply\n");
		वापस PTR_ERR(bd->अक्षरger);
	पूर्ण

	ret = bd9995x_fw_probe(bd);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot read device properties.\n");
		वापस ret;
	पूर्ण

	ret = bd9995x_hw_init(bd);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot initialize the chip.\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, bd9995x_chip_reset, bd);
	अगर (ret)
		वापस ret;

	वापस devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					 bd9995x_irq_handler_thपढ़ो,
					 IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					 BD9995X_IRQ_PIN, bd);
पूर्ण

अटल स्थिर काष्ठा of_device_id bd9995x_of_match[] = अणु
	अणु .compatible = "rohm,bd99954", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bd9995x_of_match);

अटल काष्ठा i2c_driver bd9995x_driver = अणु
	.driver = अणु
		.name = "bd9995x-charger",
		.of_match_table = bd9995x_of_match,
	पूर्ण,
	.probe_new = bd9995x_probe,
पूर्ण;
module_i2c_driver(bd9995x_driver);

MODULE_AUTHOR("Laine Markus <markus.laine@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD99954 charger driver");
MODULE_LICENSE("GPL");
