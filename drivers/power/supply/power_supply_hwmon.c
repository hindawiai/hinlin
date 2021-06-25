<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  घातer_supply_hwmon.c - घातer supply hwmon support.
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

काष्ठा घातer_supply_hwmon अणु
	काष्ठा घातer_supply *psy;
	अचिन्हित दीर्घ *props;
पूर्ण;

अटल स्थिर अक्षर *स्थिर ps_temp_label[] = अणु
	"temp",
	"ambient temp",
पूर्ण;

अटल पूर्णांक घातer_supply_hwmon_in_to_property(u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_in_average:
		वापस POWER_SUPPLY_PROP_VOLTAGE_AVG;
	हाल hwmon_in_min:
		वापस POWER_SUPPLY_PROP_VOLTAGE_MIN;
	हाल hwmon_in_max:
		वापस POWER_SUPPLY_PROP_VOLTAGE_MAX;
	हाल hwmon_in_input:
		वापस POWER_SUPPLY_PROP_VOLTAGE_NOW;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक घातer_supply_hwmon_curr_to_property(u32 attr)
अणु
	चयन (attr) अणु
	हाल hwmon_curr_average:
		वापस POWER_SUPPLY_PROP_CURRENT_AVG;
	हाल hwmon_curr_max:
		वापस POWER_SUPPLY_PROP_CURRENT_MAX;
	हाल hwmon_curr_input:
		वापस POWER_SUPPLY_PROP_CURRENT_NOW;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक घातer_supply_hwmon_temp_to_property(u32 attr, पूर्णांक channel)
अणु
	अगर (channel) अणु
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस POWER_SUPPLY_PROP_TEMP_AMBIENT;
		हाल hwmon_temp_min_alarm:
			वापस POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN;
		हाल hwmon_temp_max_alarm:
			वापस POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस POWER_SUPPLY_PROP_TEMP;
		हाल hwmon_temp_max:
			वापस POWER_SUPPLY_PROP_TEMP_MAX;
		हाल hwmon_temp_min:
			वापस POWER_SUPPLY_PROP_TEMP_MIN;
		हाल hwmon_temp_min_alarm:
			वापस POWER_SUPPLY_PROP_TEMP_ALERT_MIN;
		हाल hwmon_temp_max_alarm:
			वापस POWER_SUPPLY_PROP_TEMP_ALERT_MAX;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
घातer_supply_hwmon_to_property(क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस घातer_supply_hwmon_in_to_property(attr);
	हाल hwmon_curr:
		वापस घातer_supply_hwmon_curr_to_property(attr);
	हाल hwmon_temp:
		वापस घातer_supply_hwmon_temp_to_property(attr, channel);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool घातer_supply_hwmon_is_a_label(क्रमागत hwmon_sensor_types type,
					   u32 attr)
अणु
	वापस type == hwmon_temp && attr == hwmon_temp_label;
पूर्ण

काष्ठा hwmon_type_attr_list अणु
	स्थिर u32 *attrs;
	माप_प्रकार n_attrs;
पूर्ण;

अटल स्थिर u32 ps_temp_attrs[] = अणु
	hwmon_temp_input,
	hwmon_temp_min, hwmon_temp_max,
	hwmon_temp_min_alarm, hwmon_temp_max_alarm,
पूर्ण;

अटल स्थिर काष्ठा hwmon_type_attr_list ps_type_attrs[hwmon_max] = अणु
	[hwmon_temp] = अणु ps_temp_attrs, ARRAY_SIZE(ps_temp_attrs) पूर्ण,
पूर्ण;

अटल bool घातer_supply_hwmon_has_input(
	स्थिर काष्ठा घातer_supply_hwmon *psyhw,
	क्रमागत hwmon_sensor_types type, पूर्णांक channel)
अणु
	स्थिर काष्ठा hwmon_type_attr_list *attr_list = &ps_type_attrs[type];
	माप_प्रकार i;

	क्रम (i = 0; i < attr_list->n_attrs; ++i) अणु
		पूर्णांक prop = घातer_supply_hwmon_to_property(type,
			attr_list->attrs[i], channel);

		अगर (prop >= 0 && test_bit(prop, psyhw->props))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool घातer_supply_hwmon_is_writable(क्रमागत hwmon_sensor_types type,
					   u32 attr)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस attr == hwmon_in_min ||
		       attr == hwmon_in_max;
	हाल hwmon_curr:
		वापस attr == hwmon_curr_max;
	हाल hwmon_temp:
		वापस attr == hwmon_temp_max ||
		       attr == hwmon_temp_min ||
		       attr == hwmon_temp_min_alarm ||
		       attr == hwmon_temp_max_alarm;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल umode_t घातer_supply_hwmon_is_visible(स्थिर व्योम *data,
					     क्रमागत hwmon_sensor_types type,
					     u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा घातer_supply_hwmon *psyhw = data;
	पूर्णांक prop;

	अगर (घातer_supply_hwmon_is_a_label(type, attr)) अणु
		अगर (घातer_supply_hwmon_has_input(psyhw, type, channel))
			वापस 0444;
		अन्यथा
			वापस 0;
	पूर्ण

	prop = घातer_supply_hwmon_to_property(type, attr, channel);
	अगर (prop < 0 || !test_bit(prop, psyhw->props))
		वापस 0;

	अगर (घातer_supply_property_is_ग_लिखोable(psyhw->psy, prop) > 0 &&
	    घातer_supply_hwmon_is_writable(type, attr))
		वापस 0644;

	वापस 0444;
पूर्ण

अटल पूर्णांक घातer_supply_hwmon_पढ़ो_string(काष्ठा device *dev,
					  क्रमागत hwmon_sensor_types type,
					  u32 attr, पूर्णांक channel,
					  स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		*str = ps_temp_label[channel];
		अवरोध;
	शेष:
		/* unreachable, but see:
		 * gcc bug #51513 [1] and clang bug #978 [2]
		 *
		 * [1] https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51513
		 * [2] https://github.com/ClangBuiltLinux/linux/issues/978
		 */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
घातer_supply_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा घातer_supply_hwmon *psyhw = dev_get_drvdata(dev);
	काष्ठा घातer_supply *psy = psyhw->psy;
	जोड़ घातer_supply_propval pspval;
	पूर्णांक ret, prop;

	prop = घातer_supply_hwmon_to_property(type, attr, channel);
	अगर (prop < 0)
		वापस prop;

	ret  = घातer_supply_get_property(psy, prop, &pspval);
	अगर (ret)
		वापस ret;

	चयन (type) अणु
	/*
	 * Both voltage and current is reported in units of
	 * microvolts/microamps, so we need to adjust it to
	 * milliamps(volts)
	 */
	हाल hwmon_curr:
	हाल hwmon_in:
		pspval.पूर्णांकval = DIV_ROUND_CLOSEST(pspval.पूर्णांकval, 1000);
		अवरोध;
	/*
	 * Temp needs to be converted from 1/10 C to milli-C
	 */
	हाल hwmon_temp:
		अगर (check_mul_overflow(pspval.पूर्णांकval, 100,
				       &pspval.पूर्णांकval))
			वापस -EOVERFLOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*val = pspval.पूर्णांकval;

	वापस 0;
पूर्ण

अटल पूर्णांक
घातer_supply_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा घातer_supply_hwmon *psyhw = dev_get_drvdata(dev);
	काष्ठा घातer_supply *psy = psyhw->psy;
	जोड़ घातer_supply_propval pspval;
	पूर्णांक prop;

	prop = घातer_supply_hwmon_to_property(type, attr, channel);
	अगर (prop < 0)
		वापस prop;

	pspval.पूर्णांकval = val;

	चयन (type) अणु
	/*
	 * Both voltage and current is reported in units of
	 * microvolts/microamps, so we need to adjust it to
	 * milliamps(volts)
	 */
	हाल hwmon_curr:
	हाल hwmon_in:
		अगर (check_mul_overflow(pspval.पूर्णांकval, 1000,
				       &pspval.पूर्णांकval))
			वापस -EOVERFLOW;
		अवरोध;
	/*
	 * Temp needs to be converted from 1/10 C to milli-C
	 */
	हाल hwmon_temp:
		pspval.पूर्णांकval = DIV_ROUND_CLOSEST(pspval.पूर्णांकval, 100);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस घातer_supply_set_property(psy, prop, &pspval);
पूर्ण

अटल स्थिर काष्ठा hwmon_ops घातer_supply_hwmon_ops = अणु
	.is_visible	= घातer_supply_hwmon_is_visible,
	.पढ़ो		= घातer_supply_hwmon_पढ़ो,
	.ग_लिखो		= घातer_supply_hwmon_ग_लिखो,
	.पढ़ो_string	= घातer_supply_hwmon_पढ़ो_string,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *घातer_supply_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_LABEL     |
			   HWMON_T_INPUT     |
			   HWMON_T_MAX       |
			   HWMON_T_MIN       |
			   HWMON_T_MIN_ALARM,

			   HWMON_T_LABEL     |
			   HWMON_T_INPUT     |
			   HWMON_T_MIN_ALARM |
			   HWMON_T_MAX_ALARM),

	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_AVERAGE |
			   HWMON_C_MAX     |
			   HWMON_C_INPUT),

	HWMON_CHANNEL_INFO(in,
			   HWMON_I_AVERAGE |
			   HWMON_I_MIN     |
			   HWMON_I_MAX     |
			   HWMON_I_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info घातer_supply_hwmon_chip_info = अणु
	.ops = &घातer_supply_hwmon_ops,
	.info = घातer_supply_hwmon_info,
पूर्ण;

अटल व्योम घातer_supply_hwmon_biपंचांगap_मुक्त(व्योम *data)
अणु
	biपंचांगap_मुक्त(data);
पूर्ण

पूर्णांक घातer_supply_add_hwmon_sysfs(काष्ठा घातer_supply *psy)
अणु
	स्थिर काष्ठा घातer_supply_desc *desc = psy->desc;
	काष्ठा घातer_supply_hwmon *psyhw;
	काष्ठा device *dev = &psy->dev;
	काष्ठा device *hwmon;
	पूर्णांक ret, i;
	स्थिर अक्षर *name;

	अगर (!devres_खोलो_group(dev, घातer_supply_add_hwmon_sysfs,
			       GFP_KERNEL))
		वापस -ENOMEM;

	psyhw = devm_kzalloc(dev, माप(*psyhw), GFP_KERNEL);
	अगर (!psyhw) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	psyhw->psy = psy;
	psyhw->props = biपंचांगap_zalloc(POWER_SUPPLY_PROP_TIME_TO_FULL_AVG + 1,
				     GFP_KERNEL);
	अगर (!psyhw->props) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ret = devm_add_action_or_reset(dev, घातer_supply_hwmon_biपंचांगap_मुक्त,
			      psyhw->props);
	अगर (ret)
		जाओ error;

	क्रम (i = 0; i < desc->num_properties; i++) अणु
		स्थिर क्रमागत घातer_supply_property prop = desc->properties[i];

		चयन (prop) अणु
		हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		हाल POWER_SUPPLY_PROP_TEMP:
		हाल POWER_SUPPLY_PROP_TEMP_MAX:
		हाल POWER_SUPPLY_PROP_TEMP_MIN:
		हाल POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
		हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		हाल POWER_SUPPLY_PROP_TEMP_AMBIENT:
		हाल POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN:
		हाल POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX:
		हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
			set_bit(prop, psyhw->props);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	name = psy->desc->name;
	अगर (म_अक्षर(name, '-')) अणु
		अक्षर *new_name;

		new_name = devm_kstrdup(dev, name, GFP_KERNEL);
		अगर (!new_name) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		strreplace(new_name, '-', '_');
		name = new_name;
	पूर्ण
	hwmon = devm_hwmon_device_रेजिस्टर_with_info(dev, name,
						psyhw,
						&घातer_supply_hwmon_chip_info,
						शून्य);
	ret = PTR_ERR_OR_ZERO(hwmon);
	अगर (ret)
		जाओ error;

	devres_बंद_group(dev, घातer_supply_add_hwmon_sysfs);
	वापस 0;
error:
	devres_release_group(dev, शून्य);
	वापस ret;
पूर्ण

व्योम घातer_supply_हटाओ_hwmon_sysfs(काष्ठा घातer_supply *psy)
अणु
	devres_release_group(&psy->dev, घातer_supply_add_hwmon_sysfs);
पूर्ण
