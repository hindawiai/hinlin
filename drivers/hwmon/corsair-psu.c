<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * corsair-psu.c - Linux driver क्रम Corsair घातer supplies with HID sensors पूर्णांकerface
 * Copyright (C) 2020 Wilken Gottwalt <wilken.gottwalt@posteo.net>
 */

#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hid.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/*
 * Corsair protocol क्रम PSUs
 *
 * message size = 64 bytes (request and response, little endian)
 * request:
 *	[length][command][param0][param1][paramX]...
 * reply:
 *	[echo of length][echo of command][data0][data1][dataX]...
 *
 *	- commands are byte sized opcodes
 *	- length is the sum of all bytes of the commands/params
 *	- the micro-controller of most of these PSUs support concatenation in the request and reply,
 *	  but it is better to not rely on this (it is also hard to parse)
 *	- the driver uses raw events to be accessible from userspace (though this is not really
 *	  supported, it is just there क्रम convenience, may be हटाओd in the future)
 *	- a reply always start with the length and command in the same order the request used it
 *	- length of the reply data is specअगरic to the command used
 *	- some of the commands work on a rail and can be चयनed to a specअगरic rail (0 = 12v,
 *	  1 = 5v, 2 = 3.3v)
 *	- the क्रमmat of the init command 0xFE is swapped length/command bytes
 *	- parameter bytes amount and values are specअगरic to the command (rail setting is the only
 *	  क्रम now that uses non-zero values)
 *	- there are much more commands, especially क्रम configuring the device, but they are not
 *	  supported because a wrong command/length can lockup the micro-controller
 *	- the driver supports debugfs क्रम values not fitting पूर्णांकo the hwmon class
 *	- not every device class (HXi, RMi or AXi) supports all commands
 *	- it is a pure sensors पढ़ोing driver (will not support configuring)
 */

#घोषणा DRIVER_NAME		"corsair-psu"

#घोषणा REPLY_SIZE		16 /* max length of a reply to a single command */
#घोषणा CMD_BUFFER_SIZE		64
#घोषणा CMD_TIMEOUT_MS		250
#घोषणा SECONDS_PER_HOUR	(60 * 60)
#घोषणा SECONDS_PER_DAY		(SECONDS_PER_HOUR * 24)
#घोषणा RAIL_COUNT		3 /* 3v3 + 5v + 12v */
#घोषणा TEMP_COUNT		2

#घोषणा PSU_CMD_SELECT_RAIL	0x00 /* expects length 2 */
#घोषणा PSU_CMD_RAIL_VOLTS_HCRIT 0x40 /* the rest of the commands expect length 3 */
#घोषणा PSU_CMD_RAIL_VOLTS_LCRIT 0x44
#घोषणा PSU_CMD_RAIL_AMPS_HCRIT	0x46
#घोषणा PSU_CMD_TEMP_HCRIT	0x4F
#घोषणा PSU_CMD_IN_VOLTS	0x88
#घोषणा PSU_CMD_IN_AMPS		0x89
#घोषणा PSU_CMD_RAIL_VOLTS	0x8B
#घोषणा PSU_CMD_RAIL_AMPS	0x8C
#घोषणा PSU_CMD_TEMP0		0x8D
#घोषणा PSU_CMD_TEMP1		0x8E
#घोषणा PSU_CMD_FAN		0x90
#घोषणा PSU_CMD_RAIL_WATTS	0x96
#घोषणा PSU_CMD_VEND_STR	0x99
#घोषणा PSU_CMD_PROD_STR	0x9A
#घोषणा PSU_CMD_TOTAL_WATTS	0xEE
#घोषणा PSU_CMD_TOTAL_UPTIME	0xD1
#घोषणा PSU_CMD_UPTIME		0xD2
#घोषणा PSU_CMD_INIT		0xFE

#घोषणा L_IN_VOLTS		"v_in"
#घोषणा L_OUT_VOLTS_12V		"v_out +12v"
#घोषणा L_OUT_VOLTS_5V		"v_out +5v"
#घोषणा L_OUT_VOLTS_3_3V	"v_out +3.3v"
#घोषणा L_IN_AMPS		"curr in"
#घोषणा L_AMPS_12V		"curr +12v"
#घोषणा L_AMPS_5V		"curr +5v"
#घोषणा L_AMPS_3_3V		"curr +3.3v"
#घोषणा L_FAN			"psu fan"
#घोषणा L_TEMP0			"vrm temp"
#घोषणा L_TEMP1			"case temp"
#घोषणा L_WATTS			"power total"
#घोषणा L_WATTS_12V		"power +12v"
#घोषणा L_WATTS_5V		"power +5v"
#घोषणा L_WATTS_3_3V		"power +3.3v"

अटल स्थिर अक्षर *स्थिर label_watts[] = अणु
	L_WATTS,
	L_WATTS_12V,
	L_WATTS_5V,
	L_WATTS_3_3V
पूर्ण;

अटल स्थिर अक्षर *स्थिर label_volts[] = अणु
	L_IN_VOLTS,
	L_OUT_VOLTS_12V,
	L_OUT_VOLTS_5V,
	L_OUT_VOLTS_3_3V
पूर्ण;

अटल स्थिर अक्षर *स्थिर label_amps[] = अणु
	L_IN_AMPS,
	L_AMPS_12V,
	L_AMPS_5V,
	L_AMPS_3_3V
पूर्ण;

काष्ठा corsairpsu_data अणु
	काष्ठा hid_device *hdev;
	काष्ठा device *hwmon_dev;
	काष्ठा dentry *debugfs;
	काष्ठा completion रुको_completion;
	काष्ठा mutex lock; /* क्रम locking access to cmd_buffer */
	u8 *cmd_buffer;
	अक्षर venकरोr[REPLY_SIZE];
	अक्षर product[REPLY_SIZE];
	दीर्घ temp_crit[TEMP_COUNT];
	दीर्घ in_crit[RAIL_COUNT];
	दीर्घ in_lcrit[RAIL_COUNT];
	दीर्घ curr_crit[RAIL_COUNT];
	u8 temp_crit_support;
	u8 in_crit_support;
	u8 in_lcrit_support;
	u8 curr_crit_support;
	bool in_curr_cmd_support; /* not all commands are supported on every PSU */
पूर्ण;

/* some values are SMBus LINEAR11 data which need a conversion */
अटल पूर्णांक corsairpsu_linear11_to_पूर्णांक(स्थिर u16 val, स्थिर पूर्णांक scale)
अणु
	स्थिर पूर्णांक exp = ((s16)val) >> 11;
	स्थिर पूर्णांक mant = (((s16)(val & 0x7ff)) << 5) >> 5;
	स्थिर पूर्णांक result = mant * scale;

	वापस (exp >= 0) ? (result << exp) : (result >> -exp);
पूर्ण

अटल पूर्णांक corsairpsu_usb_cmd(काष्ठा corsairpsu_data *priv, u8 p0, u8 p1, u8 p2, व्योम *data)
अणु
	अचिन्हित दीर्घ समय;
	पूर्णांक ret;

	स_रखो(priv->cmd_buffer, 0, CMD_BUFFER_SIZE);
	priv->cmd_buffer[0] = p0;
	priv->cmd_buffer[1] = p1;
	priv->cmd_buffer[2] = p2;

	reinit_completion(&priv->रुको_completion);

	ret = hid_hw_output_report(priv->hdev, priv->cmd_buffer, CMD_BUFFER_SIZE);
	अगर (ret < 0)
		वापस ret;

	समय = रुको_क्रम_completion_समयout(&priv->रुको_completion,
					   msecs_to_jअगरfies(CMD_TIMEOUT_MS));
	अगर (!समय)
		वापस -ETIMEDOUT;

	/*
	 * at the start of the reply is an echo of the send command/length in the same order it
	 * was send, not every command is supported on every device class, अगर a command is not
	 * supported, the length value in the reply is okay, but the command value is set to 0
	 */
	अगर (p0 != priv->cmd_buffer[0] || p1 != priv->cmd_buffer[1])
		वापस -EOPNOTSUPP;

	अगर (data)
		स_नकल(data, priv->cmd_buffer + 2, REPLY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक corsairpsu_init(काष्ठा corsairpsu_data *priv)
अणु
	/*
	 * PSU_CMD_INIT uses swapped length/command and expects 2 parameter bytes, this command
	 * actually generates a reply, but we करोn't need it
	 */
	वापस corsairpsu_usb_cmd(priv, PSU_CMD_INIT, 3, 0, शून्य);
पूर्ण

अटल पूर्णांक corsairpsu_fwinfo(काष्ठा corsairpsu_data *priv)
अणु
	पूर्णांक ret;

	ret = corsairpsu_usb_cmd(priv, 3, PSU_CMD_VEND_STR, 0, priv->venकरोr);
	अगर (ret < 0)
		वापस ret;

	ret = corsairpsu_usb_cmd(priv, 3, PSU_CMD_PROD_STR, 0, priv->product);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक corsairpsu_request(काष्ठा corsairpsu_data *priv, u8 cmd, u8 rail, व्योम *data)
अणु
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	चयन (cmd) अणु
	हाल PSU_CMD_RAIL_VOLTS_HCRIT:
	हाल PSU_CMD_RAIL_VOLTS_LCRIT:
	हाल PSU_CMD_RAIL_AMPS_HCRIT:
	हाल PSU_CMD_RAIL_VOLTS:
	हाल PSU_CMD_RAIL_AMPS:
	हाल PSU_CMD_RAIL_WATTS:
		ret = corsairpsu_usb_cmd(priv, 2, PSU_CMD_SELECT_RAIL, rail, शून्य);
		अगर (ret < 0)
			जाओ cmd_fail;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = corsairpsu_usb_cmd(priv, 3, cmd, 0, data);

cmd_fail:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक corsairpsu_get_value(काष्ठा corsairpsu_data *priv, u8 cmd, u8 rail, दीर्घ *val)
अणु
	u8 data[REPLY_SIZE];
	दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = corsairpsu_request(priv, cmd, rail, data);
	अगर (ret < 0)
		वापस ret;

	/*
	 * the biggest value here comes from the upसमय command and to exceed MAXINT total upसमय
	 * needs to be about 68 years, the rest are u16 values and the biggest value coming out of
	 * the LINEAR11 conversion are the watts values which are about 1200 क्रम the strongest psu
	 * supported (HX1200i)
	 */
	पंचांगp = ((दीर्घ)data[3] << 24) + (data[2] << 16) + (data[1] << 8) + data[0];
	चयन (cmd) अणु
	हाल PSU_CMD_RAIL_VOLTS_HCRIT:
	हाल PSU_CMD_RAIL_VOLTS_LCRIT:
	हाल PSU_CMD_RAIL_AMPS_HCRIT:
	हाल PSU_CMD_TEMP_HCRIT:
	हाल PSU_CMD_IN_VOLTS:
	हाल PSU_CMD_IN_AMPS:
	हाल PSU_CMD_RAIL_VOLTS:
	हाल PSU_CMD_RAIL_AMPS:
	हाल PSU_CMD_TEMP0:
	हाल PSU_CMD_TEMP1:
		*val = corsairpsu_linear11_to_पूर्णांक(पंचांगp & 0xFFFF, 1000);
		अवरोध;
	हाल PSU_CMD_FAN:
		*val = corsairpsu_linear11_to_पूर्णांक(पंचांगp & 0xFFFF, 1);
		अवरोध;
	हाल PSU_CMD_RAIL_WATTS:
	हाल PSU_CMD_TOTAL_WATTS:
		*val = corsairpsu_linear11_to_पूर्णांक(पंचांगp & 0xFFFF, 1000000);
		अवरोध;
	हाल PSU_CMD_TOTAL_UPTIME:
	हाल PSU_CMD_UPTIME:
		*val = पंचांगp;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम corsairpsu_get_criticals(काष्ठा corsairpsu_data *priv)
अणु
	दीर्घ पंचांगp;
	पूर्णांक rail;

	क्रम (rail = 0; rail < TEMP_COUNT; ++rail) अणु
		अगर (!corsairpsu_get_value(priv, PSU_CMD_TEMP_HCRIT, rail, &पंचांगp)) अणु
			priv->temp_crit_support |= BIT(rail);
			priv->temp_crit[rail] = पंचांगp;
		पूर्ण
	पूर्ण

	क्रम (rail = 0; rail < RAIL_COUNT; ++rail) अणु
		अगर (!corsairpsu_get_value(priv, PSU_CMD_RAIL_VOLTS_HCRIT, rail, &पंचांगp)) अणु
			priv->in_crit_support |= BIT(rail);
			priv->in_crit[rail] = पंचांगp;
		पूर्ण

		अगर (!corsairpsu_get_value(priv, PSU_CMD_RAIL_VOLTS_LCRIT, rail, &पंचांगp)) अणु
			priv->in_lcrit_support |= BIT(rail);
			priv->in_lcrit[rail] = पंचांगp;
		पूर्ण

		अगर (!corsairpsu_get_value(priv, PSU_CMD_RAIL_AMPS_HCRIT, rail, &पंचांगp)) अणु
			priv->curr_crit_support |= BIT(rail);
			priv->curr_crit[rail] = पंचांगp;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम corsairpsu_check_cmd_support(काष्ठा corsairpsu_data *priv)
अणु
	दीर्घ पंचांगp;

	priv->in_curr_cmd_support = !corsairpsu_get_value(priv, PSU_CMD_IN_AMPS, 0, &पंचांगp);
पूर्ण

अटल umode_t corsairpsu_hwmon_temp_is_visible(स्थिर काष्ठा corsairpsu_data *priv, u32 attr,
						पूर्णांक channel)
अणु
	umode_t res = 0444;

	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_label:
	हाल hwmon_temp_crit:
		अगर (channel > 0 && !(priv->temp_crit_support & BIT(channel - 1)))
			res = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल umode_t corsairpsu_hwmon_fan_is_visible(स्थिर काष्ठा corsairpsu_data *priv, u32 attr,
					       पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_fan_input:
	हाल hwmon_fan_label:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t corsairpsu_hwmon_घातer_is_visible(स्थिर काष्ठा corsairpsu_data *priv, u32 attr,
						 पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_घातer_input:
	हाल hwmon_घातer_label:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t corsairpsu_hwmon_in_is_visible(स्थिर काष्ठा corsairpsu_data *priv, u32 attr,
					      पूर्णांक channel)
अणु
	umode_t res = 0444;

	चयन (attr) अणु
	हाल hwmon_in_input:
	हाल hwmon_in_label:
	हाल hwmon_in_crit:
		अगर (channel > 0 && !(priv->in_crit_support & BIT(channel - 1)))
			res = 0;
		अवरोध;
	हाल hwmon_in_lcrit:
		अगर (channel > 0 && !(priv->in_lcrit_support & BIT(channel - 1)))
			res = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल umode_t corsairpsu_hwmon_curr_is_visible(स्थिर काष्ठा corsairpsu_data *priv, u32 attr,
						पूर्णांक channel)
अणु
	umode_t res = 0444;

	चयन (attr) अणु
	हाल hwmon_curr_input:
		अगर (channel == 0 && !priv->in_curr_cmd_support)
			res = 0;
		अवरोध;
	हाल hwmon_curr_label:
	हाल hwmon_curr_crit:
		अगर (channel > 0 && !(priv->curr_crit_support & BIT(channel - 1)))
			res = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल umode_t corsairpsu_hwmon_ops_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
					       u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा corsairpsu_data *priv = data;

	चयन (type) अणु
	हाल hwmon_temp:
		वापस corsairpsu_hwmon_temp_is_visible(priv, attr, channel);
	हाल hwmon_fan:
		वापस corsairpsu_hwmon_fan_is_visible(priv, attr, channel);
	हाल hwmon_घातer:
		वापस corsairpsu_hwmon_घातer_is_visible(priv, attr, channel);
	हाल hwmon_in:
		वापस corsairpsu_hwmon_in_is_visible(priv, attr, channel);
	हाल hwmon_curr:
		वापस corsairpsu_hwmon_curr_is_visible(priv, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक corsairpsu_hwmon_temp_पढ़ो(काष्ठा corsairpsu_data *priv, u32 attr, पूर्णांक channel,
				      दीर्घ *val)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस corsairpsu_get_value(priv, channel ? PSU_CMD_TEMP1 : PSU_CMD_TEMP0,
					    channel, val);
	हाल hwmon_temp_crit:
		*val = priv->temp_crit[channel];
		err = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक corsairpsu_hwmon_घातer_पढ़ो(काष्ठा corsairpsu_data *priv, u32 attr, पूर्णांक channel,
				       दीर्घ *val)
अणु
	अगर (attr == hwmon_घातer_input) अणु
		चयन (channel) अणु
		हाल 0:
			वापस corsairpsu_get_value(priv, PSU_CMD_TOTAL_WATTS, 0, val);
		हाल 1 ... 3:
			वापस corsairpsu_get_value(priv, PSU_CMD_RAIL_WATTS, channel - 1, val);
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक corsairpsu_hwmon_in_पढ़ो(काष्ठा corsairpsu_data *priv, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_in_input:
		चयन (channel) अणु
		हाल 0:
			वापस corsairpsu_get_value(priv, PSU_CMD_IN_VOLTS, 0, val);
		हाल 1 ... 3:
			वापस corsairpsu_get_value(priv, PSU_CMD_RAIL_VOLTS, channel - 1, val);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_in_crit:
		*val = priv->in_crit[channel - 1];
		err = 0;
		अवरोध;
	हाल hwmon_in_lcrit:
		*val = priv->in_lcrit[channel - 1];
		err = 0;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक corsairpsu_hwmon_curr_पढ़ो(काष्ठा corsairpsu_data *priv, u32 attr, पूर्णांक channel,
				      दीर्घ *val)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_curr_input:
		चयन (channel) अणु
		हाल 0:
			वापस corsairpsu_get_value(priv, PSU_CMD_IN_AMPS, 0, val);
		हाल 1 ... 3:
			वापस corsairpsu_get_value(priv, PSU_CMD_RAIL_AMPS, channel - 1, val);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_curr_crit:
		*val = priv->curr_crit[channel - 1];
		err = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक corsairpsu_hwmon_ops_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
				     पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा corsairpsu_data *priv = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_temp:
		वापस corsairpsu_hwmon_temp_पढ़ो(priv, attr, channel, val);
	हाल hwmon_fan:
		अगर (attr == hwmon_fan_input)
			वापस corsairpsu_get_value(priv, PSU_CMD_FAN, 0, val);
		वापस -EOPNOTSUPP;
	हाल hwmon_घातer:
		वापस corsairpsu_hwmon_घातer_पढ़ो(priv, attr, channel, val);
	हाल hwmon_in:
		वापस corsairpsu_hwmon_in_पढ़ो(priv, attr, channel, val);
	हाल hwmon_curr:
		वापस corsairpsu_hwmon_curr_पढ़ो(priv, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक corsairpsu_hwmon_ops_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
					    u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	अगर (type == hwmon_temp && attr == hwmon_temp_label) अणु
		*str = channel ? L_TEMP1 : L_TEMP0;
		वापस 0;
	पूर्ण अन्यथा अगर (type == hwmon_fan && attr == hwmon_fan_label) अणु
		*str = L_FAN;
		वापस 0;
	पूर्ण अन्यथा अगर (type == hwmon_घातer && attr == hwmon_घातer_label && channel < 4) अणु
		*str = label_watts[channel];
		वापस 0;
	पूर्ण अन्यथा अगर (type == hwmon_in && attr == hwmon_in_label && channel < 4) अणु
		*str = label_volts[channel];
		वापस 0;
	पूर्ण अन्यथा अगर (type == hwmon_curr && attr == hwmon_curr_label && channel < 4) अणु
		*str = label_amps[channel];
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops corsairpsu_hwmon_ops = अणु
	.is_visible	= corsairpsu_hwmon_ops_is_visible,
	.पढ़ो		= corsairpsu_hwmon_ops_पढ़ो,
	.पढ़ो_string	= corsairpsu_hwmon_ops_पढ़ो_string,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *corsairpsu_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_CRIT,
			   HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_CRIT),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_LABEL),
	HWMON_CHANNEL_INFO(घातer,
			   HWMON_P_INPUT | HWMON_P_LABEL,
			   HWMON_P_INPUT | HWMON_P_LABEL,
			   HWMON_P_INPUT | HWMON_P_LABEL,
			   HWMON_P_INPUT | HWMON_P_LABEL),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL | HWMON_I_LCRIT | HWMON_I_CRIT,
			   HWMON_I_INPUT | HWMON_I_LABEL | HWMON_I_LCRIT | HWMON_I_CRIT,
			   HWMON_I_INPUT | HWMON_I_LABEL | HWMON_I_LCRIT | HWMON_I_CRIT),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL | HWMON_C_CRIT,
			   HWMON_C_INPUT | HWMON_C_LABEL | HWMON_C_CRIT,
			   HWMON_C_INPUT | HWMON_C_LABEL | HWMON_C_CRIT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info corsairpsu_chip_info = अणु
	.ops	= &corsairpsu_hwmon_ops,
	.info	= corsairpsu_info,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल व्योम prपूर्णांक_upसमय(काष्ठा seq_file *seqf, u8 cmd)
अणु
	काष्ठा corsairpsu_data *priv = seqf->निजी;
	दीर्घ val;
	पूर्णांक ret;

	ret = corsairpsu_get_value(priv, cmd, 0, &val);
	अगर (ret < 0) अणु
		seq_माला_दो(seqf, "N/A\n");
		वापस;
	पूर्ण

	अगर (val > SECONDS_PER_DAY) अणु
		seq_म_लिखो(seqf, "%ld day(s), %02ld:%02ld:%02ld\n", val / SECONDS_PER_DAY,
			   val % SECONDS_PER_DAY / SECONDS_PER_HOUR, val % SECONDS_PER_HOUR / 60,
			   val % 60);
		वापस;
	पूर्ण

	seq_म_लिखो(seqf, "%02ld:%02ld:%02ld\n", val % SECONDS_PER_DAY / SECONDS_PER_HOUR,
		   val % SECONDS_PER_HOUR / 60, val % 60);
पूर्ण

अटल पूर्णांक upसमय_show(काष्ठा seq_file *seqf, व्योम *unused)
अणु
	prपूर्णांक_upसमय(seqf, PSU_CMD_UPTIME);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(upसमय);

अटल पूर्णांक upसमय_प्रकारotal_show(काष्ठा seq_file *seqf, व्योम *unused)
अणु
	prपूर्णांक_upसमय(seqf, PSU_CMD_TOTAL_UPTIME);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(upसमय_प्रकारotal);

अटल पूर्णांक venकरोr_show(काष्ठा seq_file *seqf, व्योम *unused)
अणु
	काष्ठा corsairpsu_data *priv = seqf->निजी;

	seq_म_लिखो(seqf, "%s\n", priv->venकरोr);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(venकरोr);

अटल पूर्णांक product_show(काष्ठा seq_file *seqf, व्योम *unused)
अणु
	काष्ठा corsairpsu_data *priv = seqf->निजी;

	seq_म_लिखो(seqf, "%s\n", priv->product);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(product);

अटल व्योम corsairpsu_debugfs_init(काष्ठा corsairpsu_data *priv)
अणु
	अक्षर name[32];

	scnम_लिखो(name, माप(name), "%s-%s", DRIVER_NAME, dev_name(&priv->hdev->dev));

	priv->debugfs = debugfs_create_dir(name, शून्य);
	debugfs_create_file("uptime", 0444, priv->debugfs, priv, &upसमय_fops);
	debugfs_create_file("uptime_total", 0444, priv->debugfs, priv, &upसमय_प्रकारotal_fops);
	debugfs_create_file("vendor", 0444, priv->debugfs, priv, &venकरोr_fops);
	debugfs_create_file("product", 0444, priv->debugfs, priv, &product_fops);
पूर्ण

#अन्यथा

अटल व्योम corsairpsu_debugfs_init(काष्ठा corsairpsu_data *priv)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक corsairpsu_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा corsairpsu_data *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&hdev->dev, माप(काष्ठा corsairpsu_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->cmd_buffer = devm_kदो_स्मृति(&hdev->dev, CMD_BUFFER_SIZE, GFP_KERNEL);
	अगर (!priv->cmd_buffer)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret)
		वापस ret;

	ret = hid_hw_खोलो(hdev);
	अगर (ret)
		जाओ fail_and_stop;

	priv->hdev = hdev;
	hid_set_drvdata(hdev, priv);
	mutex_init(&priv->lock);
	init_completion(&priv->रुको_completion);

	hid_device_io_start(hdev);

	ret = corsairpsu_init(priv);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "unable to initialize device (%d)\n", ret);
		जाओ fail_and_stop;
	पूर्ण

	ret = corsairpsu_fwinfo(priv);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "unable to query firmware (%d)\n", ret);
		जाओ fail_and_stop;
	पूर्ण

	corsairpsu_get_criticals(priv);
	corsairpsu_check_cmd_support(priv);

	priv->hwmon_dev = hwmon_device_रेजिस्टर_with_info(&hdev->dev, "corsairpsu", priv,
							  &corsairpsu_chip_info, 0);

	अगर (IS_ERR(priv->hwmon_dev)) अणु
		ret = PTR_ERR(priv->hwmon_dev);
		जाओ fail_and_बंद;
	पूर्ण

	corsairpsu_debugfs_init(priv);

	वापस 0;

fail_and_बंद:
	hid_hw_बंद(hdev);
fail_and_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम corsairpsu_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा corsairpsu_data *priv = hid_get_drvdata(hdev);

	debugfs_हटाओ_recursive(priv->debugfs);
	hwmon_device_unरेजिस्टर(priv->hwmon_dev);
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक corsairpsu_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report, u8 *data,
				पूर्णांक size)
अणु
	काष्ठा corsairpsu_data *priv = hid_get_drvdata(hdev);

	अगर (completion_करोne(&priv->रुको_completion))
		वापस 0;

	स_नकल(priv->cmd_buffer, data, min(CMD_BUFFER_SIZE, size));
	complete(&priv->रुको_completion);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक corsairpsu_resume(काष्ठा hid_device *hdev)
अणु
	काष्ठा corsairpsu_data *priv = hid_get_drvdata(hdev);

	/* some PSUs turn off the microcontroller during standby, so a reinit is required */
	वापस corsairpsu_init(priv);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा hid_device_id corsairpsu_idtable[] = अणु
	अणु HID_USB_DEVICE(0x1b1c, 0x1c03) पूर्ण, /* Corsair HX550i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c04) पूर्ण, /* Corsair HX650i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c05) पूर्ण, /* Corsair HX750i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c06) पूर्ण, /* Corsair HX850i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c07) पूर्ण, /* Corsair HX1000i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c08) पूर्ण, /* Corsair HX1200i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c09) पूर्ण, /* Corsair RM550i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c0a) पूर्ण, /* Corsair RM650i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c0b) पूर्ण, /* Corsair RM750i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c0c) पूर्ण, /* Corsair RM850i */
	अणु HID_USB_DEVICE(0x1b1c, 0x1c0d) पूर्ण, /* Corsair RM1000i */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(hid, corsairpsu_idtable);

अटल काष्ठा hid_driver corsairpsu_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= corsairpsu_idtable,
	.probe		= corsairpsu_probe,
	.हटाओ		= corsairpsu_हटाओ,
	.raw_event	= corsairpsu_raw_event,
#अगर_घोषित CONFIG_PM
	.resume		= corsairpsu_resume,
	.reset_resume	= corsairpsu_resume,
#पूर्ण_अगर
पूर्ण;
module_hid_driver(corsairpsu_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wilken Gottwalt <wilken.gottwalt@posteo.net>");
MODULE_DESCRIPTION("Linux driver for Corsair power supplies with HID sensors interface");
