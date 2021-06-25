<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stephen Evanchik <evanchsa@gmail.com>
 *
 * Trademarks are the property of their respective owners.
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/serपन.स>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/libps2.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#समावेश "psmouse.h"
#समावेश "trackpoint.h"

अटल स्थिर अक्षर * स्थिर trackpoपूर्णांक_variants[] = अणु
	[TP_VARIANT_IBM]		= "IBM",
	[TP_VARIANT_ALPS]		= "ALPS",
	[TP_VARIANT_ELAN]		= "Elan",
	[TP_VARIANT_NXP]		= "NXP",
	[TP_VARIANT_JYT_SYNAPTICS]	= "JYT_Synaptics",
	[TP_VARIANT_SYNAPTICS]		= "Synaptics",
पूर्ण;

/*
 * Power-on Reset: Resets all trackpoपूर्णांक parameters, including RAM values,
 * to शेषs.
 * Returns zero on success, non-zero on failure.
 */
अटल पूर्णांक trackpoपूर्णांक_घातer_on_reset(काष्ठा ps2dev *ps2dev)
अणु
	u8 param[2] = अणु TP_POR पूर्ण;
	पूर्णांक err;

	err = ps2_command(ps2dev, param, MAKE_PS2_CMD(1, 2, TP_COMMAND));
	अगर (err)
		वापस err;

	/* Check क्रम success response -- 0xAA00 */
	अगर (param[0] != 0xAA || param[1] != 0x00)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Device IO: पढ़ो, ग_लिखो and toggle bit
 */
अटल पूर्णांक trackpoपूर्णांक_पढ़ो(काष्ठा ps2dev *ps2dev, u8 loc, u8 *results)
अणु
	results[0] = loc;

	वापस ps2_command(ps2dev, results, MAKE_PS2_CMD(1, 1, TP_COMMAND));
पूर्ण

अटल पूर्णांक trackpoपूर्णांक_ग_लिखो(काष्ठा ps2dev *ps2dev, u8 loc, u8 val)
अणु
	u8 param[3] = अणु TP_WRITE_MEM, loc, val पूर्ण;

	वापस ps2_command(ps2dev, param, MAKE_PS2_CMD(3, 0, TP_COMMAND));
पूर्ण

अटल पूर्णांक trackpoपूर्णांक_toggle_bit(काष्ठा ps2dev *ps2dev, u8 loc, u8 mask)
अणु
	u8 param[3] = अणु TP_TOGGLE, loc, mask पूर्ण;

	/* Bad things will happen अगर the loc param isn't in this range */
	अगर (loc < 0x20 || loc >= 0x2F)
		वापस -EINVAL;

	वापस ps2_command(ps2dev, param, MAKE_PS2_CMD(3, 0, TP_COMMAND));
पूर्ण

अटल पूर्णांक trackpoपूर्णांक_update_bit(काष्ठा ps2dev *ps2dev,
				 u8 loc, u8 mask, u8 value)
अणु
	पूर्णांक retval;
	u8 data;

	retval = trackpoपूर्णांक_पढ़ो(ps2dev, loc, &data);
	अगर (retval)
		वापस retval;

	अगर (((data & mask) == mask) != !!value)
		retval = trackpoपूर्णांक_toggle_bit(ps2dev, loc, mask);

	वापस retval;
पूर्ण

/*
 * Trackpoपूर्णांक-specअगरic attributes
 */
काष्ठा trackpoपूर्णांक_attr_data अणु
	माप_प्रकार field_offset;
	u8 command;
	u8 mask;
	bool inverted;
	u8 घातer_on_शेष;
पूर्ण;

अटल sमाप_प्रकार trackpoपूर्णांक_show_पूर्णांक_attr(काष्ठा psmouse *psmouse,
					व्योम *data, अक्षर *buf)
अणु
	काष्ठा trackpoपूर्णांक_data *tp = psmouse->निजी;
	काष्ठा trackpoपूर्णांक_attr_data *attr = data;
	u8 value = *(u8 *)((व्योम *)tp + attr->field_offset);

	अगर (attr->inverted)
		value = !value;

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार trackpoपूर्णांक_set_पूर्णांक_attr(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा trackpoपूर्णांक_data *tp = psmouse->निजी;
	काष्ठा trackpoपूर्णांक_attr_data *attr = data;
	u8 *field = (व्योम *)tp + attr->field_offset;
	u8 value;
	पूर्णांक err;

	err = kstrtou8(buf, 10, &value);
	अगर (err)
		वापस err;

	*field = value;
	err = trackpoपूर्णांक_ग_लिखो(&psmouse->ps2dev, attr->command, value);

	वापस err ?: count;
पूर्ण

#घोषणा TRACKPOINT_INT_ATTR(_name, _command, _शेष)				\
	अटल काष्ठा trackpoपूर्णांक_attr_data trackpoपूर्णांक_attr_##_name = अणु		\
		.field_offset = दुरत्व(काष्ठा trackpoपूर्णांक_data, _name),	\
		.command = _command,						\
		.घातer_on_शेष = _शेष,					\
	पूर्ण;									\
	PSMOUSE_DEFINE_ATTR(_name, S_IWUSR | S_IRUGO,				\
			    &trackpoपूर्णांक_attr_##_name,				\
			    trackpoपूर्णांक_show_पूर्णांक_attr, trackpoपूर्णांक_set_पूर्णांक_attr)

अटल sमाप_प्रकार trackpoपूर्णांक_set_bit_attr(काष्ठा psmouse *psmouse, व्योम *data,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा trackpoपूर्णांक_data *tp = psmouse->निजी;
	काष्ठा trackpoपूर्णांक_attr_data *attr = data;
	bool *field = (व्योम *)tp + attr->field_offset;
	bool value;
	पूर्णांक err;

	err = kstrtobool(buf, &value);
	अगर (err)
		वापस err;

	अगर (attr->inverted)
		value = !value;

	अगर (*field != value) अणु
		*field = value;
		err = trackpoपूर्णांक_toggle_bit(&psmouse->ps2dev,
					    attr->command, attr->mask);
	पूर्ण

	वापस err ?: count;
पूर्ण


#घोषणा TRACKPOINT_BIT_ATTR(_name, _command, _mask, _inv, _शेष)	\
अटल काष्ठा trackpoपूर्णांक_attr_data trackpoपूर्णांक_attr_##_name = अणु		\
	.field_offset		= दुरत्व(काष्ठा trackpoपूर्णांक_data,	\
					   _name),			\
	.command		= _command,				\
	.mask			= _mask,				\
	.inverted		= _inv,					\
	.घातer_on_शेष	= _शेष,				\
	पूर्ण;								\
PSMOUSE_DEFINE_ATTR(_name, S_IWUSR | S_IRUGO,				\
		    &trackpoपूर्णांक_attr_##_name,				\
		    trackpoपूर्णांक_show_पूर्णांक_attr, trackpoपूर्णांक_set_bit_attr)

TRACKPOINT_INT_ATTR(sensitivity, TP_SENS, TP_DEF_SENS);
TRACKPOINT_INT_ATTR(speed, TP_SPEED, TP_DEF_SPEED);
TRACKPOINT_INT_ATTR(inertia, TP_INERTIA, TP_DEF_INERTIA);
TRACKPOINT_INT_ATTR(reach, TP_REACH, TP_DEF_REACH);
TRACKPOINT_INT_ATTR(draghys, TP_DRAGHYS, TP_DEF_DRAGHYS);
TRACKPOINT_INT_ATTR(mindrag, TP_MINDRAG, TP_DEF_MINDRAG);
TRACKPOINT_INT_ATTR(thresh, TP_THRESH, TP_DEF_THRESH);
TRACKPOINT_INT_ATTR(upthresh, TP_UP_THRESH, TP_DEF_UP_THRESH);
TRACKPOINT_INT_ATTR(zसमय, TP_Z_TIME, TP_DEF_Z_TIME);
TRACKPOINT_INT_ATTR(jenks, TP_JENKS_CURV, TP_DEF_JENKS_CURV);
TRACKPOINT_INT_ATTR(drअगरt_समय, TP_DRIFT_TIME, TP_DEF_DRIFT_TIME);

TRACKPOINT_BIT_ATTR(press_to_select, TP_TOGGLE_PTSON, TP_MASK_PTSON, false,
		    TP_DEF_PTSON);
TRACKPOINT_BIT_ATTR(skipback, TP_TOGGLE_SKIPBACK, TP_MASK_SKIPBACK, false,
		    TP_DEF_SKIPBACK);
TRACKPOINT_BIT_ATTR(ext_dev, TP_TOGGLE_EXT_DEV, TP_MASK_EXT_DEV, true,
		    TP_DEF_EXT_DEV);

अटल bool trackpoपूर्णांक_is_attr_available(काष्ठा psmouse *psmouse,
					 काष्ठा attribute *attr)
अणु
	काष्ठा trackpoपूर्णांक_data *tp = psmouse->निजी;

	वापस tp->variant_id == TP_VARIANT_IBM ||
		attr == &psmouse_attr_sensitivity.dattr.attr ||
		attr == &psmouse_attr_press_to_select.dattr.attr;
पूर्ण

अटल umode_t trackpoपूर्णांक_is_attr_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा serio *serio = to_serio_port(dev);
	काष्ठा psmouse *psmouse = serio_get_drvdata(serio);

	वापस trackpoपूर्णांक_is_attr_available(psmouse, attr) ? attr->mode : 0;
पूर्ण

अटल काष्ठा attribute *trackpoपूर्णांक_attrs[] = अणु
	&psmouse_attr_sensitivity.dattr.attr,
	&psmouse_attr_speed.dattr.attr,
	&psmouse_attr_inertia.dattr.attr,
	&psmouse_attr_reach.dattr.attr,
	&psmouse_attr_draghys.dattr.attr,
	&psmouse_attr_mindrag.dattr.attr,
	&psmouse_attr_thresh.dattr.attr,
	&psmouse_attr_upthresh.dattr.attr,
	&psmouse_attr_zसमय.dattr.attr,
	&psmouse_attr_jenks.dattr.attr,
	&psmouse_attr_drअगरt_समय.dattr.attr,
	&psmouse_attr_press_to_select.dattr.attr,
	&psmouse_attr_skipback.dattr.attr,
	&psmouse_attr_ext_dev.dattr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group trackpoपूर्णांक_attr_group = अणु
	.is_visible	= trackpoपूर्णांक_is_attr_visible,
	.attrs		= trackpoपूर्णांक_attrs,
पूर्ण;

#घोषणा TRACKPOINT_UPDATE(_घातer_on, _psmouse, _tp, _name)		\
करो अणु									\
	काष्ठा trackpoपूर्णांक_attr_data *_attr = &trackpoपूर्णांक_attr_##_name;	\
									\
	अगर ((!_घातer_on || _tp->_name != _attr->घातer_on_शेष) &&	\
	    trackpoपूर्णांक_is_attr_available(_psmouse,			\
				&psmouse_attr_##_name.dattr.attr)) अणु	\
		अगर (!_attr->mask)					\
			trackpoपूर्णांक_ग_लिखो(&_psmouse->ps2dev,		\
					 _attr->command, _tp->_name);	\
		अन्यथा							\
			trackpoपूर्णांक_update_bit(&_psmouse->ps2dev,	\
					_attr->command, _attr->mask,	\
					_tp->_name);			\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा TRACKPOINT_SET_POWER_ON_DEFAULT(_tp, _name)			\
करो अणु									\
	_tp->_name = trackpoपूर्णांक_attr_##_name.घातer_on_शेष;		\
पूर्ण जबतक (0)

अटल पूर्णांक trackpoपूर्णांक_start_protocol(काष्ठा psmouse *psmouse,
				     u8 *variant_id, u8 *firmware_id)
अणु
	u8 param[2] = अणु 0 पूर्ण;
	पूर्णांक error;

	error = ps2_command(&psmouse->ps2dev,
			    param, MAKE_PS2_CMD(0, 2, TP_READ_ID));
	अगर (error)
		वापस error;

	चयन (param[0]) अणु
	हाल TP_VARIANT_IBM:
	हाल TP_VARIANT_ALPS:
	हाल TP_VARIANT_ELAN:
	हाल TP_VARIANT_NXP:
	हाल TP_VARIANT_JYT_SYNAPTICS:
	हाल TP_VARIANT_SYNAPTICS:
		अगर (variant_id)
			*variant_id = param[0];
		अगर (firmware_id)
			*firmware_id = param[1];
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * Write parameters to trackpad.
 * in_घातer_on_state: Set to true अगर TP is in शेष / घातer-on state (ex. अगर
 *		      घातer-on reset was run). If so, values will only be
 *		      written to TP अगर they dअगरfer from घातer-on शेष.
 */
अटल पूर्णांक trackpoपूर्णांक_sync(काष्ठा psmouse *psmouse, bool in_घातer_on_state)
अणु
	काष्ठा trackpoपूर्णांक_data *tp = psmouse->निजी;

	अगर (!in_घातer_on_state && tp->variant_id == TP_VARIANT_IBM) अणु
		/*
		 * Disable features that may make device unusable
		 * with this driver.
		 */
		trackpoपूर्णांक_update_bit(&psmouse->ps2dev, TP_TOGGLE_TWOHAND,
				      TP_MASK_TWOHAND, TP_DEF_TWOHAND);

		trackpoपूर्णांक_update_bit(&psmouse->ps2dev, TP_TOGGLE_SOURCE_TAG,
				      TP_MASK_SOURCE_TAG, TP_DEF_SOURCE_TAG);

		trackpoपूर्णांक_update_bit(&psmouse->ps2dev, TP_TOGGLE_MB,
				      TP_MASK_MB, TP_DEF_MB);
	पूर्ण

	/*
	 * These properties can be changed in this driver. Only
	 * configure them अगर the values are non-शेष or अगर the TP is in
	 * an unknown state.
	 */
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, sensitivity);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, inertia);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, speed);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, reach);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, draghys);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, mindrag);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, thresh);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, upthresh);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, zसमय);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, jenks);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, drअगरt_समय);

	/* toggles */
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, press_to_select);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, skipback);
	TRACKPOINT_UPDATE(in_घातer_on_state, psmouse, tp, ext_dev);

	वापस 0;
पूर्ण

अटल व्योम trackpoपूर्णांक_शेषs(काष्ठा trackpoपूर्णांक_data *tp)
अणु
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, sensitivity);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, speed);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, reach);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, draghys);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, mindrag);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, thresh);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, upthresh);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, zसमय);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, jenks);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, drअगरt_समय);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, inertia);

	/* toggles */
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, press_to_select);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, skipback);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, ext_dev);
पूर्ण

अटल व्योम trackpoपूर्णांक_disconnect(काष्ठा psmouse *psmouse)
अणु
	device_हटाओ_group(&psmouse->ps2dev.serio->dev,
			    &trackpoपूर्णांक_attr_group);

	kमुक्त(psmouse->निजी);
	psmouse->निजी = शून्य;
पूर्ण

अटल पूर्णांक trackpoपूर्णांक_reconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा trackpoपूर्णांक_data *tp = psmouse->निजी;
	पूर्णांक error;
	bool was_reset;

	error = trackpoपूर्णांक_start_protocol(psmouse, शून्य, शून्य);
	अगर (error)
		वापस error;

	was_reset = tp->variant_id == TP_VARIANT_IBM &&
		    trackpoपूर्णांक_घातer_on_reset(&psmouse->ps2dev) == 0;

	error = trackpoपूर्णांक_sync(psmouse, was_reset);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

पूर्णांक trackpoपूर्णांक_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	काष्ठा ps2dev *ps2dev = &psmouse->ps2dev;
	काष्ठा trackpoपूर्णांक_data *tp;
	u8 variant_id;
	u8 firmware_id;
	u8 button_info;
	पूर्णांक error;

	error = trackpoपूर्णांक_start_protocol(psmouse, &variant_id, &firmware_id);
	अगर (error)
		वापस error;

	अगर (!set_properties)
		वापस 0;

	tp = kzalloc(माप(*tp), GFP_KERNEL);
	अगर (!tp)
		वापस -ENOMEM;

	trackpoपूर्णांक_शेषs(tp);
	tp->variant_id = variant_id;
	tp->firmware_id = firmware_id;

	psmouse->निजी = tp;

	psmouse->venकरोr = trackpoपूर्णांक_variants[variant_id];
	psmouse->name = "TrackPoint";

	psmouse->reconnect = trackpoपूर्णांक_reconnect;
	psmouse->disconnect = trackpoपूर्णांक_disconnect;

	अगर (variant_id != TP_VARIANT_IBM) अणु
		/* Newer variants करो not support extended button query. */
		button_info = 0x33;
	पूर्ण अन्यथा अणु
		error = trackpoपूर्णांक_पढ़ो(ps2dev, TP_EXT_BTN, &button_info);
		अगर (error) अणु
			psmouse_warn(psmouse,
				     "failed to get extended button data, assuming 3 buttons\n");
			button_info = 0x33;
		पूर्ण अन्यथा अगर (!button_info) अणु
			psmouse_warn(psmouse,
				     "got 0 in extended button data, assuming 3 buttons\n");
			button_info = 0x33;
		पूर्ण
	पूर्ण

	अगर ((button_info & 0x0f) >= 3)
		input_set_capability(psmouse->dev, EV_KEY, BTN_MIDDLE);

	__set_bit(INPUT_PROP_POINTER, psmouse->dev->propbit);
	__set_bit(INPUT_PROP_POINTING_STICK, psmouse->dev->propbit);

	अगर (variant_id != TP_VARIANT_IBM ||
	    trackpoपूर्णांक_घातer_on_reset(ps2dev) != 0) अणु
		/*
		 * Write शेषs to TP अगर we did not reset the trackpoपूर्णांक.
		 */
		trackpoपूर्णांक_sync(psmouse, false);
	पूर्ण

	error = device_add_group(&ps2dev->serio->dev, &trackpoपूर्णांक_attr_group);
	अगर (error) अणु
		psmouse_err(psmouse,
			    "failed to create sysfs attributes, error: %d\n",
			    error);
		kमुक्त(psmouse->निजी);
		psmouse->निजी = शून्य;
		वापस -1;
	पूर्ण

	psmouse_info(psmouse,
		     "%s TrackPoint firmware: 0x%02x, buttons: %d/%d\n",
		     psmouse->venकरोr, firmware_id,
		     (button_info & 0xf0) >> 4, button_info & 0x0f);

	वापस 0;
पूर्ण

