<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery driver क्रम One Laptop Per Child board.
 *
 *	Copyright तऊ 2006-2010  David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/olpc-ec.h>


#घोषणा EC_BAT_VOLTAGE	0x10	/* uपूर्णांक16_t,	*9.76/32,    mV   */
#घोषणा EC_BAT_CURRENT	0x11	/* पूर्णांक16_t,	*15.625/120, mA   */
#घोषणा EC_BAT_ACR	0x12	/* पूर्णांक16_t,	*6250/15,    तगAh  */
#घोषणा EC_BAT_TEMP	0x13	/* uपूर्णांक16_t,	*100/256,   तओC  */
#घोषणा EC_AMB_TEMP	0x14	/* uपूर्णांक16_t,	*100/256,   तओC  */
#घोषणा EC_BAT_STATUS	0x15	/* uपूर्णांक8_t,	biपंचांगask */
#घोषणा EC_BAT_SOC	0x16	/* uपूर्णांक8_t,	percentage */
#घोषणा EC_BAT_SERIAL	0x17	/* uपूर्णांक8_t[6] */
#घोषणा EC_BAT_EEPROM	0x18	/* uपूर्णांक8_t adr as input, uपूर्णांक8_t output */
#घोषणा EC_BAT_ERRCODE	0x1f	/* uपूर्णांक8_t,	biपंचांगask */

#घोषणा BAT_STAT_PRESENT	0x01
#घोषणा BAT_STAT_FULL		0x02
#घोषणा BAT_STAT_LOW		0x04
#घोषणा BAT_STAT_DESTROY	0x08
#घोषणा BAT_STAT_AC		0x10
#घोषणा BAT_STAT_CHARGING	0x20
#घोषणा BAT_STAT_DISCHARGING	0x40
#घोषणा BAT_STAT_TRICKLE	0x80

#घोषणा BAT_ERR_INFOFAIL	0x02
#घोषणा BAT_ERR_OVERVOLTAGE	0x04
#घोषणा BAT_ERR_OVERTEMP	0x05
#घोषणा BAT_ERR_GAUGESTOP	0x06
#घोषणा BAT_ERR_OUT_OF_CONTROL	0x07
#घोषणा BAT_ERR_ID_FAIL		0x09
#घोषणा BAT_ERR_ACR_FAIL	0x10

#घोषणा BAT_ADDR_MFR_TYPE	0x5F

काष्ठा olpc_battery_data अणु
	काष्ठा घातer_supply *olpc_ac;
	काष्ठा घातer_supply *olpc_bat;
	अक्षर bat_serial[17];
	bool new_proto;
	bool little_endian;
पूर्ण;

/*********************************************************************
 *		Power
 *********************************************************************/

अटल पूर्णांक olpc_ac_get_prop(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक8_t status;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = olpc_ec_cmd(EC_BAT_STATUS, शून्य, 0, &status, 1);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = !!(status & BAT_STAT_AC);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property olpc_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc olpc_ac_desc = अणु
	.name = "olpc_ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = olpc_ac_props,
	.num_properties = ARRAY_SIZE(olpc_ac_props),
	.get_property = olpc_ac_get_prop,
पूर्ण;

अटल पूर्णांक olpc_bat_get_status(काष्ठा olpc_battery_data *data,
		जोड़ घातer_supply_propval *val, uपूर्णांक8_t ec_byte)
अणु
	अगर (data->new_proto) अणु
		अगर (ec_byte & (BAT_STAT_CHARGING | BAT_STAT_TRICKLE))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (ec_byte & BAT_STAT_DISCHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (ec_byte & BAT_STAT_FULL)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा /* er,... */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण अन्यथा अणु
		/* Older EC didn't report अक्षरge/disअक्षरge bits */
		अगर (!(ec_byte & BAT_STAT_AC)) /* No AC means disअक्षरging */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (ec_byte & BAT_STAT_FULL)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा /* Not _necessarily_ true but EC करोesn't tell all yet */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक olpc_bat_get_health(जोड़ घातer_supply_propval *val)
अणु
	uपूर्णांक8_t ec_byte;
	पूर्णांक ret;

	ret = olpc_ec_cmd(EC_BAT_ERRCODE, शून्य, 0, &ec_byte, 1);
	अगर (ret)
		वापस ret;

	चयन (ec_byte) अणु
	हाल 0:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;

	हाल BAT_ERR_OVERTEMP:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अवरोध;

	हाल BAT_ERR_OVERVOLTAGE:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अवरोध;

	हाल BAT_ERR_INFOFAIL:
	हाल BAT_ERR_OUT_OF_CONTROL:
	हाल BAT_ERR_ID_FAIL:
	हाल BAT_ERR_ACR_FAIL:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अवरोध;

	शेष:
		/* Eep. We करोn't know this failure code */
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक olpc_bat_get_mfr(जोड़ घातer_supply_propval *val)
अणु
	uपूर्णांक8_t ec_byte;
	पूर्णांक ret;

	ec_byte = BAT_ADDR_MFR_TYPE;
	ret = olpc_ec_cmd(EC_BAT_EEPROM, &ec_byte, 1, &ec_byte, 1);
	अगर (ret)
		वापस ret;

	चयन (ec_byte >> 4) अणु
	हाल 1:
		val->strval = "Gold Peak";
		अवरोध;
	हाल 2:
		val->strval = "BYD";
		अवरोध;
	शेष:
		val->strval = "Unknown";
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक olpc_bat_get_tech(जोड़ घातer_supply_propval *val)
अणु
	uपूर्णांक8_t ec_byte;
	पूर्णांक ret;

	ec_byte = BAT_ADDR_MFR_TYPE;
	ret = olpc_ec_cmd(EC_BAT_EEPROM, &ec_byte, 1, &ec_byte, 1);
	अगर (ret)
		वापस ret;

	चयन (ec_byte & 0xf) अणु
	हाल 1:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_NiMH;
		अवरोध;
	हाल 2:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LiFe;
		अवरोध;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक olpc_bat_get_अक्षरge_full_design(जोड़ घातer_supply_propval *val)
अणु
	uपूर्णांक8_t ec_byte;
	जोड़ घातer_supply_propval tech;
	पूर्णांक ret, mfr;

	ret = olpc_bat_get_tech(&tech);
	अगर (ret)
		वापस ret;

	ec_byte = BAT_ADDR_MFR_TYPE;
	ret = olpc_ec_cmd(EC_BAT_EEPROM, &ec_byte, 1, &ec_byte, 1);
	अगर (ret)
		वापस ret;

	mfr = ec_byte >> 4;

	चयन (tech.पूर्णांकval) अणु
	हाल POWER_SUPPLY_TECHNOLOGY_NiMH:
		चयन (mfr) अणु
		हाल 1: /* Gold Peak */
			val->पूर्णांकval = 3000000*.8;
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_TECHNOLOGY_LiFe:
		चयन (mfr) अणु
		हाल 1: /* Gold Peak, fall through */
		हाल 2: /* BYD */
			val->पूर्णांकval = 2800000;
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक olpc_bat_get_अक्षरge_now(जोड़ घातer_supply_propval *val)
अणु
	uपूर्णांक8_t soc;
	जोड़ घातer_supply_propval full;
	पूर्णांक ret;

	ret = olpc_ec_cmd(EC_BAT_SOC, शून्य, 0, &soc, 1);
	अगर (ret)
		वापस ret;

	ret = olpc_bat_get_अक्षरge_full_design(&full);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = soc * (full.पूर्णांकval / 100);
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_bat_get_voltage_max_design(जोड़ घातer_supply_propval *val)
अणु
	uपूर्णांक8_t ec_byte;
	जोड़ घातer_supply_propval tech;
	पूर्णांक mfr;
	पूर्णांक ret;

	ret = olpc_bat_get_tech(&tech);
	अगर (ret)
		वापस ret;

	ec_byte = BAT_ADDR_MFR_TYPE;
	ret = olpc_ec_cmd(EC_BAT_EEPROM, &ec_byte, 1, &ec_byte, 1);
	अगर (ret)
		वापस ret;

	mfr = ec_byte >> 4;

	चयन (tech.पूर्णांकval) अणु
	हाल POWER_SUPPLY_TECHNOLOGY_NiMH:
		चयन (mfr) अणु
		हाल 1: /* Gold Peak */
			val->पूर्णांकval = 6000000;
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_TECHNOLOGY_LiFe:
		चयन (mfr) अणु
		हाल 1: /* Gold Peak */
			val->पूर्णांकval = 6400000;
			अवरोध;
		हाल 2: /* BYD */
			val->पूर्णांकval = 6500000;
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल u16 ecword_to_cpu(काष्ठा olpc_battery_data *data, u16 ec_word)
अणु
	अगर (data->little_endian)
		वापस le16_to_cpu((__क्रमce __le16)ec_word);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)ec_word);
पूर्ण

/*********************************************************************
 *		Battery properties
 *********************************************************************/
अटल पूर्णांक olpc_bat_get_property(काष्ठा घातer_supply *psy,
				 क्रमागत घातer_supply_property psp,
				 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा olpc_battery_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;
	u16 ec_word;
	uपूर्णांक8_t ec_byte;
	__be64 ser_buf;

	ret = olpc_ec_cmd(EC_BAT_STATUS, शून्य, 0, &ec_byte, 1);
	अगर (ret)
		वापस ret;

	/* Theoretically there's a race here -- the battery could be
	   हटाओd immediately after we check whether it's present, and
	   then we query क्रम some other property of the now-असलent battery.
	   It करोesn't matter though -- the EC will वापस the last-known
	   inक्रमmation, and it's as अगर we just ran that _little_ bit faster
	   and managed to पढ़ो it out beक्रमe the battery went away. */
	अगर (!(ec_byte & (BAT_STAT_PRESENT | BAT_STAT_TRICKLE)) &&
			psp != POWER_SUPPLY_PROP_PRESENT)
		वापस -ENODEV;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = olpc_bat_get_status(data, val, ec_byte);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		अगर (ec_byte & BAT_STAT_TRICKLE)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अन्यथा अगर (ec_byte & BAT_STAT_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!(ec_byte & (BAT_STAT_PRESENT |
					    BAT_STAT_TRICKLE));
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (ec_byte & BAT_STAT_DESTROY)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा अणु
			ret = olpc_bat_get_health(val);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		ret = olpc_bat_get_mfr(val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		ret = olpc_bat_get_tech(val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = olpc_ec_cmd(EC_BAT_VOLTAGE, शून्य, 0, (व्योम *)&ec_word, 2);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = ecword_to_cpu(data, ec_word) * 9760L / 32;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = olpc_ec_cmd(EC_BAT_CURRENT, शून्य, 0, (व्योम *)&ec_word, 2);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = ecword_to_cpu(data, ec_word) * 15625L / 120;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = olpc_ec_cmd(EC_BAT_SOC, शून्य, 0, &ec_byte, 1);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = ec_byte;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		अगर (ec_byte & BAT_STAT_FULL)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा अगर (ec_byte & BAT_STAT_LOW)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = olpc_bat_get_अक्षरge_full_design(val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = olpc_bat_get_अक्षरge_now(val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = olpc_ec_cmd(EC_BAT_TEMP, शून्य, 0, (व्योम *)&ec_word, 2);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = ecword_to_cpu(data, ec_word) * 10 / 256;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_AMBIENT:
		ret = olpc_ec_cmd(EC_AMB_TEMP, शून्य, 0, (व्योम *)&ec_word, 2);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = (पूर्णांक)ecword_to_cpu(data, ec_word) * 10 / 256;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		ret = olpc_ec_cmd(EC_BAT_ACR, शून्य, 0, (व्योम *)&ec_word, 2);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = ecword_to_cpu(data, ec_word) * 6250 / 15;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		ret = olpc_ec_cmd(EC_BAT_SERIAL, शून्य, 0, (व्योम *)&ser_buf, 8);
		अगर (ret)
			वापस ret;

		प्र_लिखो(data->bat_serial, "%016llx", (दीर्घ दीर्घ)be64_to_cpu(ser_buf));
		val->strval = data->bat_serial;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		ret = olpc_bat_get_voltage_max_design(val);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property olpc_xo1_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TEMP_AMBIENT,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
पूर्ण;

/* XO-1.5 करोes not have ambient temperature property */
अटल क्रमागत घातer_supply_property olpc_xo15_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
पूर्ण;

/* EEPROM पढ़ोing goes completely around the घातer_supply API, sadly */

#घोषणा EEPROM_START	0x20
#घोषणा EEPROM_END	0x80
#घोषणा EEPROM_SIZE	(EEPROM_END - EEPROM_START)

अटल sमाप_प्रकार olpc_bat_eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	uपूर्णांक8_t ec_byte;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		ec_byte = EEPROM_START + off + i;
		ret = olpc_ec_cmd(EC_BAT_EEPROM, &ec_byte, 1, &buf[i], 1);
		अगर (ret) अणु
			pr_err("olpc-battery: "
			       "EC_BAT_EEPROM cmd @ 0x%x failed - %d!\n",
			       ec_byte, ret);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute olpc_bat_eeprom = अणु
	.attr = अणु
		.name = "eeprom",
		.mode = S_IRUGO,
	पूर्ण,
	.size = EEPROM_SIZE,
	.पढ़ो = olpc_bat_eeprom_पढ़ो,
पूर्ण;

/* Allow userspace to see the specअगरic error value pulled from the EC */

अटल sमाप_प्रकार olpc_bat_error_पढ़ो(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	uपूर्णांक8_t ec_byte;
	sमाप_प्रकार ret;

	ret = olpc_ec_cmd(EC_BAT_ERRCODE, शून्य, 0, &ec_byte, 1);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", ec_byte);
पूर्ण

अटल काष्ठा device_attribute olpc_bat_error = अणु
	.attr = अणु
		.name = "error",
		.mode = S_IRUGO,
	पूर्ण,
	.show = olpc_bat_error_पढ़ो,
पूर्ण;

अटल काष्ठा attribute *olpc_bat_sysfs_attrs[] = अणु
	&olpc_bat_error.attr,
	शून्य
पूर्ण;

अटल काष्ठा bin_attribute *olpc_bat_sysfs_bin_attrs[] = अणु
	&olpc_bat_eeprom,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group olpc_bat_sysfs_group = अणु
	.attrs = olpc_bat_sysfs_attrs,
	.bin_attrs = olpc_bat_sysfs_bin_attrs,

पूर्ण;

अटल स्थिर काष्ठा attribute_group *olpc_bat_sysfs_groups[] = अणु
	&olpc_bat_sysfs_group,
	शून्य
पूर्ण;

/*********************************************************************
 *		Initialisation
 *********************************************************************/

अटल काष्ठा घातer_supply_desc olpc_bat_desc = अणु
	.name = "olpc_battery",
	.get_property = olpc_bat_get_property,
	.use_क्रम_apm = 1,
पूर्ण;

अटल पूर्णांक olpc_battery_suspend(काष्ठा platक्रमm_device *pdev,
				pm_message_t state)
अणु
	काष्ठा olpc_battery_data *data = platक्रमm_get_drvdata(pdev);

	अगर (device_may_wakeup(&data->olpc_ac->dev))
		olpc_ec_wakeup_set(EC_SCI_SRC_ACPWR);
	अन्यथा
		olpc_ec_wakeup_clear(EC_SCI_SRC_ACPWR);

	अगर (device_may_wakeup(&data->olpc_bat->dev))
		olpc_ec_wakeup_set(EC_SCI_SRC_BATTERY | EC_SCI_SRC_BATSOC
				   | EC_SCI_SRC_BATERR);
	अन्यथा
		olpc_ec_wakeup_clear(EC_SCI_SRC_BATTERY | EC_SCI_SRC_BATSOC
				     | EC_SCI_SRC_BATERR);

	वापस 0;
पूर्ण

अटल पूर्णांक olpc_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config bat_psy_cfg = अणुपूर्ण;
	काष्ठा घातer_supply_config ac_psy_cfg = अणुपूर्ण;
	काष्ठा olpc_battery_data *data;
	uपूर्णांक8_t status;
	uपूर्णांक8_t ecver;
	पूर्णांक ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, data);

	/* See अगर the EC is alपढ़ोy there and get the EC revision */
	ret = olpc_ec_cmd(EC_FIRMWARE_REV, शून्य, 0, &ecver, 1);
	अगर (ret)
		वापस ret;

	अगर (of_find_compatible_node(शून्य, शून्य, "olpc,xo1.75-ec")) अणु
		/* XO 1.75 */
		data->new_proto = true;
		data->little_endian = true;
	पूर्ण अन्यथा अगर (ecver > 0x44) अणु
		/* XO 1 or 1.5 with a new EC firmware. */
		data->new_proto = true;
	पूर्ण अन्यथा अगर (ecver < 0x44) अणु
		/*
		 * We've seen a number of EC protocol changes; this driver
		 * requires the latest EC protocol, supported by 0x44 and above.
		 */
		prपूर्णांकk(KERN_NOTICE "OLPC EC version 0x%02x too old for "
			"battery driver.\n", ecver);
		वापस -ENXIO;
	पूर्ण

	ret = olpc_ec_cmd(EC_BAT_STATUS, शून्य, 0, &status, 1);
	अगर (ret)
		वापस ret;

	/* Ignore the status. It करोesn't actually matter */

	ac_psy_cfg.of_node = pdev->dev.of_node;
	ac_psy_cfg.drv_data = data;

	data->olpc_ac = devm_घातer_supply_रेजिस्टर(&pdev->dev, &olpc_ac_desc,
								&ac_psy_cfg);
	अगर (IS_ERR(data->olpc_ac))
		वापस PTR_ERR(data->olpc_ac);

	अगर (of_device_is_compatible(pdev->dev.of_node, "olpc,xo1.5-battery")) अणु
		/* XO-1.5 */
		olpc_bat_desc.properties = olpc_xo15_bat_props;
		olpc_bat_desc.num_properties = ARRAY_SIZE(olpc_xo15_bat_props);
	पूर्ण अन्यथा अणु
		/* XO-1 */
		olpc_bat_desc.properties = olpc_xo1_bat_props;
		olpc_bat_desc.num_properties = ARRAY_SIZE(olpc_xo1_bat_props);
	पूर्ण

	bat_psy_cfg.of_node = pdev->dev.of_node;
	bat_psy_cfg.drv_data = data;
	bat_psy_cfg.attr_grp = olpc_bat_sysfs_groups;

	data->olpc_bat = devm_घातer_supply_रेजिस्टर(&pdev->dev, &olpc_bat_desc,
								&bat_psy_cfg);
	अगर (IS_ERR(data->olpc_bat))
		वापस PTR_ERR(data->olpc_bat);

	अगर (olpc_ec_wakeup_available()) अणु
		device_set_wakeup_capable(&data->olpc_ac->dev, true);
		device_set_wakeup_capable(&data->olpc_bat->dev, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id olpc_battery_ids[] = अणु
	अणु .compatible = "olpc,xo1-battery" पूर्ण,
	अणु .compatible = "olpc,xo1.5-battery" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, olpc_battery_ids);

अटल काष्ठा platक्रमm_driver olpc_battery_driver = अणु
	.driver = अणु
		.name = "olpc-battery",
		.of_match_table = olpc_battery_ids,
	पूर्ण,
	.probe = olpc_battery_probe,
	.suspend = olpc_battery_suspend,
पूर्ण;

module_platक्रमm_driver(olpc_battery_driver);

MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Battery driver for One Laptop Per Child 'XO' machine");
