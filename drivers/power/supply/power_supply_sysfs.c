<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Sysfs पूर्णांकerface क्रम the universal घातer supply monitor class
 *
 *  Copyright तऊ 2007  David Woodhouse <dwmw2@infradead.org>
 *  Copyright तऊ 2007  Anton Vorontsov <cbou@mail.ru>
 *  Copyright तऊ 2004  Szabolcs Gyurko
 *  Copyright तऊ 2003  Ian Molton <spyro@f2s.com>
 *
 *  Modअगरied: 2004, Oct     Szabolcs Gyurko
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>

#समावेश "power_supply.h"

#घोषणा MAX_PROP_NAME_LEN 30

काष्ठा घातer_supply_attr अणु
	स्थिर अक्षर *prop_name;
	अक्षर attr_name[MAX_PROP_NAME_LEN + 1];
	काष्ठा device_attribute dev_attr;
	स्थिर अक्षर * स्थिर *text_values;
	पूर्णांक text_values_len;
पूर्ण;

#घोषणा _POWER_SUPPLY_ATTR(_name, _text, _len)	\
[POWER_SUPPLY_PROP_ ## _name] =			\
अणु						\
	.prop_name = #_name,			\
	.attr_name = #_name "\0",		\
	.text_values = _text,			\
	.text_values_len = _len,		\
पूर्ण

#घोषणा POWER_SUPPLY_ATTR(_name) _POWER_SUPPLY_ATTR(_name, शून्य, 0)
#घोषणा _POWER_SUPPLY_ENUM_ATTR(_name, _text)	\
	_POWER_SUPPLY_ATTR(_name, _text, ARRAY_SIZE(_text))
#घोषणा POWER_SUPPLY_ENUM_ATTR(_name)	\
	_POWER_SUPPLY_ENUM_ATTR(_name, POWER_SUPPLY_ ## _name ## _TEXT)

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_TYPE_TEXT[] = अणु
	[POWER_SUPPLY_TYPE_UNKNOWN]		= "Unknown",
	[POWER_SUPPLY_TYPE_BATTERY]		= "Battery",
	[POWER_SUPPLY_TYPE_UPS]			= "UPS",
	[POWER_SUPPLY_TYPE_MAINS]		= "Mains",
	[POWER_SUPPLY_TYPE_USB]			= "USB",
	[POWER_SUPPLY_TYPE_USB_DCP]		= "USB_DCP",
	[POWER_SUPPLY_TYPE_USB_CDP]		= "USB_CDP",
	[POWER_SUPPLY_TYPE_USB_ACA]		= "USB_ACA",
	[POWER_SUPPLY_TYPE_USB_TYPE_C]		= "USB_C",
	[POWER_SUPPLY_TYPE_USB_PD]		= "USB_PD",
	[POWER_SUPPLY_TYPE_USB_PD_DRP]		= "USB_PD_DRP",
	[POWER_SUPPLY_TYPE_APPLE_BRICK_ID]	= "BrickID",
	[POWER_SUPPLY_TYPE_WIRELESS]		= "Wireless",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_USB_TYPE_TEXT[] = अणु
	[POWER_SUPPLY_USB_TYPE_UNKNOWN]		= "Unknown",
	[POWER_SUPPLY_USB_TYPE_SDP]		= "SDP",
	[POWER_SUPPLY_USB_TYPE_DCP]		= "DCP",
	[POWER_SUPPLY_USB_TYPE_CDP]		= "CDP",
	[POWER_SUPPLY_USB_TYPE_ACA]		= "ACA",
	[POWER_SUPPLY_USB_TYPE_C]		= "C",
	[POWER_SUPPLY_USB_TYPE_PD]		= "PD",
	[POWER_SUPPLY_USB_TYPE_PD_DRP]		= "PD_DRP",
	[POWER_SUPPLY_USB_TYPE_PD_PPS]		= "PD_PPS",
	[POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID]	= "BrickID",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_STATUS_TEXT[] = अणु
	[POWER_SUPPLY_STATUS_UNKNOWN]		= "Unknown",
	[POWER_SUPPLY_STATUS_CHARGING]		= "Charging",
	[POWER_SUPPLY_STATUS_DISCHARGING]	= "Discharging",
	[POWER_SUPPLY_STATUS_NOT_CHARGING]	= "Not charging",
	[POWER_SUPPLY_STATUS_FULL]		= "Full",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_CHARGE_TYPE_TEXT[] = अणु
	[POWER_SUPPLY_CHARGE_TYPE_UNKNOWN]	= "Unknown",
	[POWER_SUPPLY_CHARGE_TYPE_NONE]		= "N/A",
	[POWER_SUPPLY_CHARGE_TYPE_TRICKLE]	= "Trickle",
	[POWER_SUPPLY_CHARGE_TYPE_FAST]		= "Fast",
	[POWER_SUPPLY_CHARGE_TYPE_STANDARD]	= "Standard",
	[POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE]	= "Adaptive",
	[POWER_SUPPLY_CHARGE_TYPE_CUSTOM]	= "Custom",
	[POWER_SUPPLY_CHARGE_TYPE_LONGLIFE]	= "Long Life",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_HEALTH_TEXT[] = अणु
	[POWER_SUPPLY_HEALTH_UNKNOWN]		    = "Unknown",
	[POWER_SUPPLY_HEALTH_GOOD]		    = "Good",
	[POWER_SUPPLY_HEALTH_OVERHEAT]		    = "Overheat",
	[POWER_SUPPLY_HEALTH_DEAD]		    = "Dead",
	[POWER_SUPPLY_HEALTH_OVERVOLTAGE]	    = "Over voltage",
	[POWER_SUPPLY_HEALTH_UNSPEC_FAILURE]	    = "Unspecified failure",
	[POWER_SUPPLY_HEALTH_COLD]		    = "Cold",
	[POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE] = "Watchdog timer expire",
	[POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE]   = "Safety timer expire",
	[POWER_SUPPLY_HEALTH_OVERCURRENT]	    = "Over current",
	[POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED]  = "Calibration required",
	[POWER_SUPPLY_HEALTH_WARM]		    = "Warm",
	[POWER_SUPPLY_HEALTH_COOL]		    = "Cool",
	[POWER_SUPPLY_HEALTH_HOT]		    = "Hot",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_TECHNOLOGY_TEXT[] = अणु
	[POWER_SUPPLY_TECHNOLOGY_UNKNOWN]	= "Unknown",
	[POWER_SUPPLY_TECHNOLOGY_NiMH]		= "NiMH",
	[POWER_SUPPLY_TECHNOLOGY_LION]		= "Li-ion",
	[POWER_SUPPLY_TECHNOLOGY_LIPO]		= "Li-poly",
	[POWER_SUPPLY_TECHNOLOGY_LiFe]		= "LiFe",
	[POWER_SUPPLY_TECHNOLOGY_NiCd]		= "NiCd",
	[POWER_SUPPLY_TECHNOLOGY_LiMn]		= "LiMn",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_CAPACITY_LEVEL_TEXT[] = अणु
	[POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN]	= "Unknown",
	[POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL]	= "Critical",
	[POWER_SUPPLY_CAPACITY_LEVEL_LOW]	= "Low",
	[POWER_SUPPLY_CAPACITY_LEVEL_NORMAL]	= "Normal",
	[POWER_SUPPLY_CAPACITY_LEVEL_HIGH]	= "High",
	[POWER_SUPPLY_CAPACITY_LEVEL_FULL]	= "Full",
पूर्ण;

अटल स्थिर अक्षर * स्थिर POWER_SUPPLY_SCOPE_TEXT[] = अणु
	[POWER_SUPPLY_SCOPE_UNKNOWN]	= "Unknown",
	[POWER_SUPPLY_SCOPE_SYSTEM]	= "System",
	[POWER_SUPPLY_SCOPE_DEVICE]	= "Device",
पूर्ण;

अटल काष्ठा घातer_supply_attr घातer_supply_attrs[] = अणु
	/* Properties of type `पूर्णांक' */
	POWER_SUPPLY_ENUM_ATTR(STATUS),
	POWER_SUPPLY_ENUM_ATTR(CHARGE_TYPE),
	POWER_SUPPLY_ENUM_ATTR(HEALTH),
	POWER_SUPPLY_ATTR(PRESENT),
	POWER_SUPPLY_ATTR(ONLINE),
	POWER_SUPPLY_ATTR(AUTHENTIC),
	POWER_SUPPLY_ENUM_ATTR(TECHNOLOGY),
	POWER_SUPPLY_ATTR(CYCLE_COUNT),
	POWER_SUPPLY_ATTR(VOLTAGE_MAX),
	POWER_SUPPLY_ATTR(VOLTAGE_MIN),
	POWER_SUPPLY_ATTR(VOLTAGE_MAX_DESIGN),
	POWER_SUPPLY_ATTR(VOLTAGE_MIN_DESIGN),
	POWER_SUPPLY_ATTR(VOLTAGE_NOW),
	POWER_SUPPLY_ATTR(VOLTAGE_AVG),
	POWER_SUPPLY_ATTR(VOLTAGE_OCV),
	POWER_SUPPLY_ATTR(VOLTAGE_BOOT),
	POWER_SUPPLY_ATTR(CURRENT_MAX),
	POWER_SUPPLY_ATTR(CURRENT_NOW),
	POWER_SUPPLY_ATTR(CURRENT_AVG),
	POWER_SUPPLY_ATTR(CURRENT_BOOT),
	POWER_SUPPLY_ATTR(POWER_NOW),
	POWER_SUPPLY_ATTR(POWER_AVG),
	POWER_SUPPLY_ATTR(CHARGE_FULL_DESIGN),
	POWER_SUPPLY_ATTR(CHARGE_EMPTY_DESIGN),
	POWER_SUPPLY_ATTR(CHARGE_FULL),
	POWER_SUPPLY_ATTR(CHARGE_EMPTY),
	POWER_SUPPLY_ATTR(CHARGE_NOW),
	POWER_SUPPLY_ATTR(CHARGE_AVG),
	POWER_SUPPLY_ATTR(CHARGE_COUNTER),
	POWER_SUPPLY_ATTR(CONSTANT_CHARGE_CURRENT),
	POWER_SUPPLY_ATTR(CONSTANT_CHARGE_CURRENT_MAX),
	POWER_SUPPLY_ATTR(CONSTANT_CHARGE_VOLTAGE),
	POWER_SUPPLY_ATTR(CONSTANT_CHARGE_VOLTAGE_MAX),
	POWER_SUPPLY_ATTR(CHARGE_CONTROL_LIMIT),
	POWER_SUPPLY_ATTR(CHARGE_CONTROL_LIMIT_MAX),
	POWER_SUPPLY_ATTR(CHARGE_CONTROL_START_THRESHOLD),
	POWER_SUPPLY_ATTR(CHARGE_CONTROL_END_THRESHOLD),
	POWER_SUPPLY_ATTR(INPUT_CURRENT_LIMIT),
	POWER_SUPPLY_ATTR(INPUT_VOLTAGE_LIMIT),
	POWER_SUPPLY_ATTR(INPUT_POWER_LIMIT),
	POWER_SUPPLY_ATTR(ENERGY_FULL_DESIGN),
	POWER_SUPPLY_ATTR(ENERGY_EMPTY_DESIGN),
	POWER_SUPPLY_ATTR(ENERGY_FULL),
	POWER_SUPPLY_ATTR(ENERGY_EMPTY),
	POWER_SUPPLY_ATTR(ENERGY_NOW),
	POWER_SUPPLY_ATTR(ENERGY_AVG),
	POWER_SUPPLY_ATTR(CAPACITY),
	POWER_SUPPLY_ATTR(CAPACITY_ALERT_MIN),
	POWER_SUPPLY_ATTR(CAPACITY_ALERT_MAX),
	POWER_SUPPLY_ATTR(CAPACITY_ERROR_MARGIN),
	POWER_SUPPLY_ENUM_ATTR(CAPACITY_LEVEL),
	POWER_SUPPLY_ATTR(TEMP),
	POWER_SUPPLY_ATTR(TEMP_MAX),
	POWER_SUPPLY_ATTR(TEMP_MIN),
	POWER_SUPPLY_ATTR(TEMP_ALERT_MIN),
	POWER_SUPPLY_ATTR(TEMP_ALERT_MAX),
	POWER_SUPPLY_ATTR(TEMP_AMBIENT),
	POWER_SUPPLY_ATTR(TEMP_AMBIENT_ALERT_MIN),
	POWER_SUPPLY_ATTR(TEMP_AMBIENT_ALERT_MAX),
	POWER_SUPPLY_ATTR(TIME_TO_EMPTY_NOW),
	POWER_SUPPLY_ATTR(TIME_TO_EMPTY_AVG),
	POWER_SUPPLY_ATTR(TIME_TO_FULL_NOW),
	POWER_SUPPLY_ATTR(TIME_TO_FULL_AVG),
	POWER_SUPPLY_ENUM_ATTR(TYPE),
	POWER_SUPPLY_ATTR(USB_TYPE),
	POWER_SUPPLY_ENUM_ATTR(SCOPE),
	POWER_SUPPLY_ATTR(PRECHARGE_CURRENT),
	POWER_SUPPLY_ATTR(CHARGE_TERM_CURRENT),
	POWER_SUPPLY_ATTR(CALIBRATE),
	POWER_SUPPLY_ATTR(MANUFACTURE_YEAR),
	POWER_SUPPLY_ATTR(MANUFACTURE_MONTH),
	POWER_SUPPLY_ATTR(MANUFACTURE_DAY),
	/* Properties of type `स्थिर अक्षर *' */
	POWER_SUPPLY_ATTR(MODEL_NAME),
	POWER_SUPPLY_ATTR(MANUFACTURER),
	POWER_SUPPLY_ATTR(SERIAL_NUMBER),
पूर्ण;

अटल काष्ठा attribute *
__घातer_supply_attrs[ARRAY_SIZE(घातer_supply_attrs) + 1];

अटल काष्ठा घातer_supply_attr *to_ps_attr(काष्ठा device_attribute *attr)
अणु
	वापस container_of(attr, काष्ठा घातer_supply_attr, dev_attr);
पूर्ण

अटल क्रमागत घातer_supply_property dev_attr_psp(काष्ठा device_attribute *attr)
अणु
	वापस  to_ps_attr(attr) - घातer_supply_attrs;
पूर्ण

अटल sमाप_प्रकार घातer_supply_show_usb_type(काष्ठा device *dev,
					  स्थिर काष्ठा घातer_supply_desc *desc,
					  जोड़ घातer_supply_propval *value,
					  अक्षर *buf)
अणु
	क्रमागत घातer_supply_usb_type usb_type;
	sमाप_प्रकार count = 0;
	bool match = false;
	पूर्णांक i;

	क्रम (i = 0; i < desc->num_usb_types; ++i) अणु
		usb_type = desc->usb_types[i];

		अगर (value->पूर्णांकval == usb_type) अणु
			count += प्र_लिखो(buf + count, "[%s] ",
					 POWER_SUPPLY_USB_TYPE_TEXT[usb_type]);
			match = true;
		पूर्ण अन्यथा अणु
			count += प्र_लिखो(buf + count, "%s ",
					 POWER_SUPPLY_USB_TYPE_TEXT[usb_type]);
		पूर्ण
	पूर्ण

	अगर (!match) अणु
		dev_warn(dev, "driver reporting unsupported connected type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (count)
		buf[count - 1] = '\n';

	वापस count;
पूर्ण

अटल sमाप_प्रकार घातer_supply_show_property(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf) अणु
	sमाप_प्रकार ret;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा घातer_supply_attr *ps_attr = to_ps_attr(attr);
	क्रमागत घातer_supply_property psp = dev_attr_psp(attr);
	जोड़ घातer_supply_propval value;

	अगर (psp == POWER_SUPPLY_PROP_TYPE) अणु
		value.पूर्णांकval = psy->desc->type;
	पूर्ण अन्यथा अणु
		ret = घातer_supply_get_property(psy, psp, &value);

		अगर (ret < 0) अणु
			अगर (ret == -ENODATA)
				dev_dbg(dev, "driver has no data for `%s' property\n",
					attr->attr.name);
			अन्यथा अगर (ret != -ENODEV && ret != -EAGAIN)
				dev_err_ratelimited(dev,
					"driver failed to report `%s' property: %zd\n",
					attr->attr.name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ps_attr->text_values_len > 0 &&
	    value.पूर्णांकval < ps_attr->text_values_len && value.पूर्णांकval >= 0) अणु
		वापस प्र_लिखो(buf, "%s\n", ps_attr->text_values[value.पूर्णांकval]);
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_USB_TYPE:
		ret = घातer_supply_show_usb_type(dev, psy->desc,
						&value, buf);
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME ... POWER_SUPPLY_PROP_SERIAL_NUMBER:
		ret = प्र_लिखो(buf, "%s\n", value.strval);
		अवरोध;
	शेष:
		ret = प्र_लिखो(buf, "%d\n", value.पूर्णांकval);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार घातer_supply_store_property(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count) अणु
	sमाप_प्रकार ret;
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा घातer_supply_attr *ps_attr = to_ps_attr(attr);
	क्रमागत घातer_supply_property psp = dev_attr_psp(attr);
	जोड़ घातer_supply_propval value;

	ret = -EINVAL;
	अगर (ps_attr->text_values_len > 0) अणु
		ret = __sysfs_match_string(ps_attr->text_values,
					   ps_attr->text_values_len, buf);
	पूर्ण

	/*
	 * If no match was found, then check to see अगर it is an पूर्णांकeger.
	 * Integer values are valid क्रम क्रमागतs in addition to the text value.
	 */
	अगर (ret < 0) अणु
		दीर्घ दीर्घ_val;

		ret = kम_से_दीर्घ(buf, 10, &दीर्घ_val);
		अगर (ret < 0)
			वापस ret;

		ret = दीर्घ_val;
	पूर्ण

	value.पूर्णांकval = ret;

	ret = घातer_supply_set_property(psy, psp, &value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल umode_t घातer_supply_attr_is_visible(काष्ठा kobject *kobj,
					   काष्ठा attribute *attr,
					   पूर्णांक attrno)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	umode_t mode = S_IRUSR | S_IRGRP | S_IROTH;
	पूर्णांक i;

	अगर (!घातer_supply_attrs[attrno].prop_name)
		वापस 0;

	अगर (attrno == POWER_SUPPLY_PROP_TYPE)
		वापस mode;

	क्रम (i = 0; i < psy->desc->num_properties; i++) अणु
		पूर्णांक property = psy->desc->properties[i];

		अगर (property == attrno) अणु
			अगर (psy->desc->property_is_ग_लिखोable &&
			    psy->desc->property_is_ग_लिखोable(psy, property) > 0)
				mode |= S_IWUSR;

			वापस mode;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group घातer_supply_attr_group = अणु
	.attrs = __घातer_supply_attrs,
	.is_visible = घातer_supply_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *घातer_supply_attr_groups[] = अणु
	&घातer_supply_attr_group,
	शून्य,
पूर्ण;

अटल व्योम str_to_lower(अक्षर *str)
अणु
	जबतक (*str) अणु
		*str = छोटे(*str);
		str++;
	पूर्ण
पूर्ण

व्योम घातer_supply_init_attrs(काष्ठा device_type *dev_type)
अणु
	पूर्णांक i;

	dev_type->groups = घातer_supply_attr_groups;

	क्रम (i = 0; i < ARRAY_SIZE(घातer_supply_attrs); i++) अणु
		काष्ठा device_attribute *attr;

		अगर (!घातer_supply_attrs[i].prop_name) अणु
			pr_warn("%s: Property %d skipped because it is missing from power_supply_attrs\n",
				__func__, i);
			प्र_लिखो(घातer_supply_attrs[i].attr_name, "_err_%d", i);
		पूर्ण अन्यथा अणु
			str_to_lower(घातer_supply_attrs[i].attr_name);
		पूर्ण

		attr = &घातer_supply_attrs[i].dev_attr;

		attr->attr.name = घातer_supply_attrs[i].attr_name;
		attr->show = घातer_supply_show_property;
		attr->store = घातer_supply_store_property;
		__घातer_supply_attrs[i] = &attr->attr;
	पूर्ण
पूर्ण

अटल पूर्णांक add_prop_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env,
			   क्रमागत घातer_supply_property prop, अक्षर *prop_buf)
अणु
	पूर्णांक ret = 0;
	काष्ठा घातer_supply_attr *pwr_attr;
	काष्ठा device_attribute *dev_attr;
	अक्षर *line;

	pwr_attr = &घातer_supply_attrs[prop];
	dev_attr = &pwr_attr->dev_attr;

	ret = घातer_supply_show_property(dev, dev_attr, prop_buf);
	अगर (ret == -ENODEV || ret == -ENODATA) अणु
		/*
		 * When a battery is असलent, we expect -ENODEV. Don't पात;
		 * send the uevent with at least the the PRESENT=0 property
		 */
		वापस 0;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	line = म_अक्षर(prop_buf, '\n');
	अगर (line)
		*line = 0;

	वापस add_uevent_var(env, "POWER_SUPPLY_%s=%s",
			      pwr_attr->prop_name, prop_buf);
पूर्ण

पूर्णांक घातer_supply_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	पूर्णांक ret = 0, j;
	अक्षर *prop_buf;

	अगर (!psy || !psy->desc) अणु
		dev_dbg(dev, "No power supply yet\n");
		वापस ret;
	पूर्ण

	ret = add_uevent_var(env, "POWER_SUPPLY_NAME=%s", psy->desc->name);
	अगर (ret)
		वापस ret;

	prop_buf = (अक्षर *)get_zeroed_page(GFP_KERNEL);
	अगर (!prop_buf)
		वापस -ENOMEM;

	ret = add_prop_uevent(dev, env, POWER_SUPPLY_PROP_TYPE, prop_buf);
	अगर (ret)
		जाओ out;

	क्रम (j = 0; j < psy->desc->num_properties; j++) अणु
		ret = add_prop_uevent(dev, env, psy->desc->properties[j],
				      prop_buf);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	मुक्त_page((अचिन्हित दीर्घ)prop_buf);

	वापस ret;
पूर्ण
