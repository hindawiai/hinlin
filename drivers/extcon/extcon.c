<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/extcon/extcon.c - External Connector (extcon) framework.
 *
 * Copyright (C) 2015 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 *
 * Copyright (C) 2012 Samsung Electronics
 * Author: Donggeun Kim <dg77.kim@samsung.com>
 * Author: MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * based on android/drivers/चयन/चयन_class.c
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश "extcon.h"

#घोषणा SUPPORTED_CABLE_MAX	32

अटल स्थिर काष्ठा __extcon_info अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;

पूर्ण extcon_info[] = अणु
	[EXTCON_NONE] = अणु
		.type = EXTCON_TYPE_MISC,
		.id = EXTCON_NONE,
		.name = "NONE",
	पूर्ण,

	/* USB बाह्यal connector */
	[EXTCON_USB] = अणु
		.type = EXTCON_TYPE_USB,
		.id = EXTCON_USB,
		.name = "USB",
	पूर्ण,
	[EXTCON_USB_HOST] = अणु
		.type = EXTCON_TYPE_USB,
		.id = EXTCON_USB_HOST,
		.name = "USB-HOST",
	पूर्ण,

	/* Charging बाह्यal connector */
	[EXTCON_CHG_USB_SDP] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_SDP,
		.name = "SDP",
	पूर्ण,
	[EXTCON_CHG_USB_DCP] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_DCP,
		.name = "DCP",
	पूर्ण,
	[EXTCON_CHG_USB_CDP] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_CDP,
		.name = "CDP",
	पूर्ण,
	[EXTCON_CHG_USB_ACA] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_ACA,
		.name = "ACA",
	पूर्ण,
	[EXTCON_CHG_USB_FAST] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_FAST,
		.name = "FAST-CHARGER",
	पूर्ण,
	[EXTCON_CHG_USB_SLOW] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_SLOW,
		.name = "SLOW-CHARGER",
	पूर्ण,
	[EXTCON_CHG_WPT] = अणु
		.type = EXTCON_TYPE_CHG,
		.id = EXTCON_CHG_WPT,
		.name = "WPT",
	पूर्ण,
	[EXTCON_CHG_USB_PD] = अणु
		.type = EXTCON_TYPE_CHG | EXTCON_TYPE_USB,
		.id = EXTCON_CHG_USB_PD,
		.name = "PD",
	पूर्ण,

	/* Jack बाह्यal connector */
	[EXTCON_JACK_MICROPHONE] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_MICROPHONE,
		.name = "MICROPHONE",
	पूर्ण,
	[EXTCON_JACK_HEADPHONE] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_HEADPHONE,
		.name = "HEADPHONE",
	पूर्ण,
	[EXTCON_JACK_LINE_IN] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_LINE_IN,
		.name = "LINE-IN",
	पूर्ण,
	[EXTCON_JACK_LINE_OUT] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_LINE_OUT,
		.name = "LINE-OUT",
	पूर्ण,
	[EXTCON_JACK_VIDEO_IN] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_VIDEO_IN,
		.name = "VIDEO-IN",
	पूर्ण,
	[EXTCON_JACK_VIDEO_OUT] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_VIDEO_OUT,
		.name = "VIDEO-OUT",
	पूर्ण,
	[EXTCON_JACK_SPDIF_IN] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_SPDIF_IN,
		.name = "SPDIF-IN",
	पूर्ण,
	[EXTCON_JACK_SPDIF_OUT] = अणु
		.type = EXTCON_TYPE_JACK,
		.id = EXTCON_JACK_SPDIF_OUT,
		.name = "SPDIF-OUT",
	पूर्ण,

	/* Display बाह्यal connector */
	[EXTCON_DISP_HDMI] = अणु
		.type = EXTCON_TYPE_DISP,
		.id = EXTCON_DISP_HDMI,
		.name = "HDMI",
	पूर्ण,
	[EXTCON_DISP_MHL] = अणु
		.type = EXTCON_TYPE_DISP,
		.id = EXTCON_DISP_MHL,
		.name = "MHL",
	पूर्ण,
	[EXTCON_DISP_DVI] = अणु
		.type = EXTCON_TYPE_DISP,
		.id = EXTCON_DISP_DVI,
		.name = "DVI",
	पूर्ण,
	[EXTCON_DISP_VGA] = अणु
		.type = EXTCON_TYPE_DISP,
		.id = EXTCON_DISP_VGA,
		.name = "VGA",
	पूर्ण,
	[EXTCON_DISP_DP] = अणु
		.type = EXTCON_TYPE_DISP | EXTCON_TYPE_USB,
		.id = EXTCON_DISP_DP,
		.name = "DP",
	पूर्ण,
	[EXTCON_DISP_HMD] = अणु
		.type = EXTCON_TYPE_DISP | EXTCON_TYPE_USB,
		.id = EXTCON_DISP_HMD,
		.name = "HMD",
	पूर्ण,

	/* Miscellaneous बाह्यal connector */
	[EXTCON_DOCK] = अणु
		.type = EXTCON_TYPE_MISC,
		.id = EXTCON_DOCK,
		.name = "DOCK",
	पूर्ण,
	[EXTCON_JIG] = अणु
		.type = EXTCON_TYPE_MISC,
		.id = EXTCON_JIG,
		.name = "JIG",
	पूर्ण,
	[EXTCON_MECHANICAL] = अणु
		.type = EXTCON_TYPE_MISC,
		.id = EXTCON_MECHANICAL,
		.name = "MECHANICAL",
	पूर्ण,

	अणु /* sentinel */ पूर्ण
पूर्ण;

/**
 * काष्ठा extcon_cable - An पूर्णांकernal data क्रम an बाह्यal connector.
 * @edev:		the extcon device
 * @cable_index:	the index of this cable in the edev
 * @attr_g:		the attribute group क्रम the cable
 * @attr_name:		"name" sysfs entry
 * @attr_state:		"state" sysfs entry
 * @attrs:		the array poपूर्णांकing to attr_name and attr_state क्रम attr_g
 */
काष्ठा extcon_cable अणु
	काष्ठा extcon_dev *edev;
	पूर्णांक cable_index;

	काष्ठा attribute_group attr_g;
	काष्ठा device_attribute attr_name;
	काष्ठा device_attribute attr_state;

	काष्ठा attribute *attrs[3]; /* to be fed to attr_g.attrs */

	जोड़ extcon_property_value usb_propval[EXTCON_PROP_USB_CNT];
	जोड़ extcon_property_value chg_propval[EXTCON_PROP_CHG_CNT];
	जोड़ extcon_property_value jack_propval[EXTCON_PROP_JACK_CNT];
	जोड़ extcon_property_value disp_propval[EXTCON_PROP_DISP_CNT];

	अचिन्हित दीर्घ usb_bits[BITS_TO_LONGS(EXTCON_PROP_USB_CNT)];
	अचिन्हित दीर्घ chg_bits[BITS_TO_LONGS(EXTCON_PROP_CHG_CNT)];
	अचिन्हित दीर्घ jack_bits[BITS_TO_LONGS(EXTCON_PROP_JACK_CNT)];
	अचिन्हित दीर्घ disp_bits[BITS_TO_LONGS(EXTCON_PROP_DISP_CNT)];
पूर्ण;

अटल काष्ठा class *extcon_class;

अटल LIST_HEAD(extcon_dev_list);
अटल DEFINE_MUTEX(extcon_dev_list_lock);

अटल पूर्णांक check_mutually_exclusive(काष्ठा extcon_dev *edev, u32 new_state)
अणु
	पूर्णांक i = 0;

	अगर (!edev->mutually_exclusive)
		वापस 0;

	क्रम (i = 0; edev->mutually_exclusive[i]; i++) अणु
		पूर्णांक weight;
		u32 correspondants = new_state & edev->mutually_exclusive[i];

		/* calculate the total number of bits set */
		weight = hweight32(correspondants);
		अगर (weight > 1)
			वापस i + 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक find_cable_index_by_id(काष्ठा extcon_dev *edev, स्थिर अचिन्हित पूर्णांक id)
अणु
	पूर्णांक i;

	/* Find the the index of extcon cable in edev->supported_cable */
	क्रम (i = 0; i < edev->max_supported; i++) अणु
		अगर (edev->supported_cable[i] == id)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_extcon_type(अचिन्हित पूर्णांक prop)
अणु
	चयन (prop) अणु
	हाल EXTCON_PROP_USB_MIN ... EXTCON_PROP_USB_MAX:
		वापस EXTCON_TYPE_USB;
	हाल EXTCON_PROP_CHG_MIN ... EXTCON_PROP_CHG_MAX:
		वापस EXTCON_TYPE_CHG;
	हाल EXTCON_PROP_JACK_MIN ... EXTCON_PROP_JACK_MAX:
		वापस EXTCON_TYPE_JACK;
	हाल EXTCON_PROP_DISP_MIN ... EXTCON_PROP_DISP_MAX:
		वापस EXTCON_TYPE_DISP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool is_extcon_attached(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक index)
अणु
	वापस !!(edev->state & BIT(index));
पूर्ण

अटल bool is_extcon_changed(काष्ठा extcon_dev *edev, पूर्णांक index,
				bool new_state)
अणु
	पूर्णांक state = !!(edev->state & BIT(index));
	वापस (state != new_state);
पूर्ण

अटल bool is_extcon_property_supported(अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक prop)
अणु
	पूर्णांक type;

	/* Check whether the property is supported or not. */
	type = get_extcon_type(prop);
	अगर (type < 0)
		वापस false;

	/* Check whether a specअगरic extcon id supports the property or not. */
	वापस !!(extcon_info[id].type & type);
पूर्ण

अटल पूर्णांक is_extcon_property_capability(काष्ठा extcon_dev *edev,
				अचिन्हित पूर्णांक id, पूर्णांक index,अचिन्हित पूर्णांक prop)
अणु
	काष्ठा extcon_cable *cable;
	पूर्णांक type, ret;

	/* Check whether the property is supported or not. */
	type = get_extcon_type(prop);
	अगर (type < 0)
		वापस type;

	cable = &edev->cables[index];

	चयन (type) अणु
	हाल EXTCON_TYPE_USB:
		ret = test_bit(prop - EXTCON_PROP_USB_MIN, cable->usb_bits);
		अवरोध;
	हाल EXTCON_TYPE_CHG:
		ret = test_bit(prop - EXTCON_PROP_CHG_MIN, cable->chg_bits);
		अवरोध;
	हाल EXTCON_TYPE_JACK:
		ret = test_bit(prop - EXTCON_PROP_JACK_MIN, cable->jack_bits);
		अवरोध;
	हाल EXTCON_TYPE_DISP:
		ret = test_bit(prop - EXTCON_PROP_DISP_MIN, cable->disp_bits);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम init_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id, पूर्णांक index)
अणु
	अचिन्हित पूर्णांक type = extcon_info[id].type;
	काष्ठा extcon_cable *cable = &edev->cables[index];

	अगर (EXTCON_TYPE_USB & type)
		स_रखो(cable->usb_propval, 0, माप(cable->usb_propval));
	अगर (EXTCON_TYPE_CHG & type)
		स_रखो(cable->chg_propval, 0, माप(cable->chg_propval));
	अगर (EXTCON_TYPE_JACK & type)
		स_रखो(cable->jack_propval, 0, माप(cable->jack_propval));
	अगर (EXTCON_TYPE_DISP & type)
		स_रखो(cable->disp_propval, 0, माप(cable->disp_propval));
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक i, count = 0;
	काष्ठा extcon_dev *edev = dev_get_drvdata(dev);

	अगर (edev->max_supported == 0)
		वापस प्र_लिखो(buf, "%u\n", edev->state);

	क्रम (i = 0; i < edev->max_supported; i++) अणु
		count += प्र_लिखो(buf + count, "%s=%d\n",
				extcon_info[edev->supported_cable[i]].name,
				 !!(edev->state & BIT(i)));
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा extcon_dev *edev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", edev->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार cable_name_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा extcon_cable *cable = container_of(attr, काष्ठा extcon_cable,
						  attr_name);
	पूर्णांक i = cable->cable_index;

	वापस प्र_लिखो(buf, "%s\n",
			extcon_info[cable->edev->supported_cable[i]].name);
पूर्ण

अटल sमाप_प्रकार cable_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा extcon_cable *cable = container_of(attr, काष्ठा extcon_cable,
						  attr_state);

	पूर्णांक i = cable->cable_index;

	वापस प्र_लिखो(buf, "%d\n",
		extcon_get_state(cable->edev, cable->edev->supported_cable[i]));
पूर्ण

/**
 * extcon_sync() - Synchronize the state क्रम an बाह्यal connector.
 * @edev:	the extcon device
 *
 * Note that this function send a notअगरication in order to synchronize
 * the state and property of an बाह्यal connector.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id)
अणु
	अक्षर name_buf[120];
	अक्षर state_buf[120];
	अक्षर *prop_buf;
	अक्षर *envp[3];
	पूर्णांक env_offset = 0;
	पूर्णांक length;
	पूर्णांक index;
	पूर्णांक state;
	अचिन्हित दीर्घ flags;

	अगर (!edev)
		वापस -EINVAL;

	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	spin_lock_irqsave(&edev->lock, flags);
	state = !!(edev->state & BIT(index));
	spin_unlock_irqrestore(&edev->lock, flags);

	/*
	 * Call functions in a raw notअगरier chain क्रम the specअगरic one
	 * बाह्यal connector.
	 */
	raw_notअगरier_call_chain(&edev->nh[index], state, edev);

	/*
	 * Call functions in a raw notअगरier chain क्रम the all supported
	 * बाह्यal connectors.
	 */
	raw_notअगरier_call_chain(&edev->nh_all, state, edev);

	spin_lock_irqsave(&edev->lock, flags);
	/* This could be in पूर्णांकerrupt handler */
	prop_buf = (अक्षर *)get_zeroed_page(GFP_ATOMIC);
	अगर (!prop_buf) अणु
		/* Unlock early beक्रमe uevent */
		spin_unlock_irqrestore(&edev->lock, flags);

		dev_err(&edev->dev, "out of memory in extcon_set_state\n");
		kobject_uevent(&edev->dev.kobj, KOBJ_CHANGE);

		वापस -ENOMEM;
	पूर्ण

	length = name_show(&edev->dev, शून्य, prop_buf);
	अगर (length > 0) अणु
		अगर (prop_buf[length - 1] == '\n')
			prop_buf[length - 1] = 0;
		snम_लिखो(name_buf, माप(name_buf), "NAME=%s", prop_buf);
		envp[env_offset++] = name_buf;
	पूर्ण

	length = state_show(&edev->dev, शून्य, prop_buf);
	अगर (length > 0) अणु
		अगर (prop_buf[length - 1] == '\n')
			prop_buf[length - 1] = 0;
		snम_लिखो(state_buf, माप(state_buf), "STATE=%s", prop_buf);
		envp[env_offset++] = state_buf;
	पूर्ण
	envp[env_offset] = शून्य;

	/* Unlock early beक्रमe uevent */
	spin_unlock_irqrestore(&edev->lock, flags);
	kobject_uevent_env(&edev->dev.kobj, KOBJ_CHANGE, envp);
	मुक्त_page((अचिन्हित दीर्घ)prop_buf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_sync);

/**
 * extcon_get_state() - Get the state of an बाह्यal connector.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_get_state(काष्ठा extcon_dev *edev, स्थिर अचिन्हित पूर्णांक id)
अणु
	पूर्णांक index, state;
	अचिन्हित दीर्घ flags;

	अगर (!edev)
		वापस -EINVAL;

	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	spin_lock_irqsave(&edev->lock, flags);
	state = is_extcon_attached(edev, index);
	spin_unlock_irqrestore(&edev->lock, flags);

	वापस state;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_get_state);

/**
 * extcon_set_state() - Set the state of an बाह्यal connector.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @state:	the new state of an बाह्यal connector.
 *		the शेष semantics is true: attached / false: detached.
 *
 * Note that this function set the state of an बाह्यal connector without
 * a notअगरication. To synchronize the state of an बाह्यal connector,
 * have to use extcon_set_state_sync() and extcon_sync().
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_set_state(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id, bool state)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक index, ret = 0;

	अगर (!edev)
		वापस -EINVAL;

	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	spin_lock_irqsave(&edev->lock, flags);

	/* Check whether the बाह्यal connector's state is changed. */
	अगर (!is_extcon_changed(edev, index, state))
		जाओ out;

	अगर (check_mutually_exclusive(edev,
		(edev->state & ~BIT(index)) | (state & BIT(index)))) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	/*
	 * Initialize the value of extcon property beक्रमe setting
	 * the detached state क्रम an बाह्यal connector.
	 */
	अगर (!state)
		init_property(edev, id, index);

	/* Update the state क्रम an बाह्यal connector. */
	अगर (state)
		edev->state |= BIT(index);
	अन्यथा
		edev->state &= ~(BIT(index));
out:
	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_set_state);

/**
 * extcon_set_state_sync() - Set the state of an बाह्यal connector with sync.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @state:	the new state of बाह्यal connector.
 *		the शेष semantics is true: attached / false: detached.
 *
 * Note that this function set the state of बाह्यal connector
 * and synchronize the state by sending a notअगरication.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_set_state_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id, bool state)
अणु
	पूर्णांक ret, index;
	अचिन्हित दीर्घ flags;

	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	/* Check whether the बाह्यal connector's state is changed. */
	spin_lock_irqsave(&edev->lock, flags);
	ret = is_extcon_changed(edev, index, state);
	spin_unlock_irqrestore(&edev->lock, flags);
	अगर (!ret)
		वापस 0;

	ret = extcon_set_state(edev, id, state);
	अगर (ret < 0)
		वापस ret;

	वापस extcon_sync(edev, id);
पूर्ण
EXPORT_SYMBOL_GPL(extcon_set_state_sync);

/**
 * extcon_get_property() - Get the property value of an बाह्यal connector.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @prop:	the property id indicating an extcon property
 * @prop_val:	the poपूर्णांकer which store the value of extcon property
 *
 * Note that when getting the property value of बाह्यal connector,
 * the बाह्यal connector should be attached. If detached state, function
 * वापस 0 without property value. Also, the each property should be
 * included in the list of supported properties according to extcon type.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_get_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value *prop_val)
अणु
	काष्ठा extcon_cable *cable;
	अचिन्हित दीर्घ flags;
	पूर्णांक index, ret = 0;

	*prop_val = (जोड़ extcon_property_value)अणु0पूर्ण;

	अगर (!edev)
		वापस -EINVAL;

	/* Check whether the property is supported or not */
	अगर (!is_extcon_property_supported(id, prop))
		वापस -EINVAL;

	/* Find the cable index of बाह्यal connector by using id */
	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	spin_lock_irqsave(&edev->lock, flags);

	/* Check whether the property is available or not. */
	अगर (!is_extcon_property_capability(edev, id, index, prop)) अणु
		spin_unlock_irqrestore(&edev->lock, flags);
		वापस -EPERM;
	पूर्ण

	/*
	 * Check whether the बाह्यal connector is attached.
	 * If बाह्यal connector is detached, the user can not
	 * get the property value.
	 */
	अगर (!is_extcon_attached(edev, index)) अणु
		spin_unlock_irqrestore(&edev->lock, flags);
		वापस 0;
	पूर्ण

	cable = &edev->cables[index];

	/* Get the property value according to extcon type */
	चयन (prop) अणु
	हाल EXTCON_PROP_USB_MIN ... EXTCON_PROP_USB_MAX:
		*prop_val = cable->usb_propval[prop - EXTCON_PROP_USB_MIN];
		अवरोध;
	हाल EXTCON_PROP_CHG_MIN ... EXTCON_PROP_CHG_MAX:
		*prop_val = cable->chg_propval[prop - EXTCON_PROP_CHG_MIN];
		अवरोध;
	हाल EXTCON_PROP_JACK_MIN ... EXTCON_PROP_JACK_MAX:
		*prop_val = cable->jack_propval[prop - EXTCON_PROP_JACK_MIN];
		अवरोध;
	हाल EXTCON_PROP_DISP_MIN ... EXTCON_PROP_DISP_MAX:
		*prop_val = cable->disp_propval[prop - EXTCON_PROP_DISP_MIN];
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_get_property);

/**
 * extcon_set_property() - Set the property value of an बाह्यal connector.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @prop:	the property id indicating an extcon property
 * @prop_val:	the poपूर्णांकer including the new value of extcon property
 *
 * Note that each property should be included in the list of supported
 * properties according to the extcon type.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_set_property(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value prop_val)
अणु
	काष्ठा extcon_cable *cable;
	अचिन्हित दीर्घ flags;
	पूर्णांक index, ret = 0;

	अगर (!edev)
		वापस -EINVAL;

	/* Check whether the property is supported or not */
	अगर (!is_extcon_property_supported(id, prop))
		वापस -EINVAL;

	/* Find the cable index of बाह्यal connector by using id */
	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	spin_lock_irqsave(&edev->lock, flags);

	/* Check whether the property is available or not. */
	अगर (!is_extcon_property_capability(edev, id, index, prop)) अणु
		spin_unlock_irqrestore(&edev->lock, flags);
		वापस -EPERM;
	पूर्ण

	cable = &edev->cables[index];

	/* Set the property value according to extcon type */
	चयन (prop) अणु
	हाल EXTCON_PROP_USB_MIN ... EXTCON_PROP_USB_MAX:
		cable->usb_propval[prop - EXTCON_PROP_USB_MIN] = prop_val;
		अवरोध;
	हाल EXTCON_PROP_CHG_MIN ... EXTCON_PROP_CHG_MAX:
		cable->chg_propval[prop - EXTCON_PROP_CHG_MIN] = prop_val;
		अवरोध;
	हाल EXTCON_PROP_JACK_MIN ... EXTCON_PROP_JACK_MAX:
		cable->jack_propval[prop - EXTCON_PROP_JACK_MIN] = prop_val;
		अवरोध;
	हाल EXTCON_PROP_DISP_MIN ... EXTCON_PROP_DISP_MAX:
		cable->disp_propval[prop - EXTCON_PROP_DISP_MIN] = prop_val;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_set_property);

/**
 * extcon_set_property_sync() - Set property of an बाह्यal connector with sync.
 * @prop_val:	the poपूर्णांकer including the new value of extcon property
 *
 * Note that when setting the property value of बाह्यal connector,
 * the बाह्यal connector should be attached. The each property should
 * be included in the list of supported properties according to extcon type.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_set_property_sync(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				अचिन्हित पूर्णांक prop,
				जोड़ extcon_property_value prop_val)
अणु
	पूर्णांक ret;

	ret = extcon_set_property(edev, id, prop, prop_val);
	अगर (ret < 0)
		वापस ret;

	वापस extcon_sync(edev, id);
पूर्ण
EXPORT_SYMBOL_GPL(extcon_set_property_sync);

/**
 * extcon_get_property_capability() - Get the capability of the property
 *					क्रम an बाह्यal connector.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @prop:	the property id indicating an extcon property
 *
 * Returns 1 अगर the property is available or 0 अगर not available.
 */
पूर्णांक extcon_get_property_capability(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
					अचिन्हित पूर्णांक prop)
अणु
	पूर्णांक index;

	अगर (!edev)
		वापस -EINVAL;

	/* Check whether the property is supported or not */
	अगर (!is_extcon_property_supported(id, prop))
		वापस -EINVAL;

	/* Find the cable index of बाह्यal connector by using id */
	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	वापस is_extcon_property_capability(edev, id, index, prop);
पूर्ण
EXPORT_SYMBOL_GPL(extcon_get_property_capability);

/**
 * extcon_set_property_capability() - Set the capability of the property
 *					क्रम an बाह्यal connector.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @prop:	the property id indicating an extcon property
 *
 * Note that this function set the capability of the property
 * क्रम an बाह्यal connector in order to mark the bit in capability
 * biपंचांगap which mean the available state of the property.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_set_property_capability(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
					अचिन्हित पूर्णांक prop)
अणु
	काष्ठा extcon_cable *cable;
	पूर्णांक index, type, ret = 0;

	अगर (!edev)
		वापस -EINVAL;

	/* Check whether the property is supported or not. */
	अगर (!is_extcon_property_supported(id, prop))
		वापस -EINVAL;

	/* Find the cable index of बाह्यal connector by using id. */
	index = find_cable_index_by_id(edev, id);
	अगर (index < 0)
		वापस index;

	type = get_extcon_type(prop);
	अगर (type < 0)
		वापस type;

	cable = &edev->cables[index];

	चयन (type) अणु
	हाल EXTCON_TYPE_USB:
		__set_bit(prop - EXTCON_PROP_USB_MIN, cable->usb_bits);
		अवरोध;
	हाल EXTCON_TYPE_CHG:
		__set_bit(prop - EXTCON_PROP_CHG_MIN, cable->chg_bits);
		अवरोध;
	हाल EXTCON_TYPE_JACK:
		__set_bit(prop - EXTCON_PROP_JACK_MIN, cable->jack_bits);
		अवरोध;
	हाल EXTCON_TYPE_DISP:
		__set_bit(prop - EXTCON_PROP_DISP_MIN, cable->disp_bits);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_set_property_capability);

/**
 * extcon_get_extcon_dev() - Get the extcon device instance from the name.
 * @extcon_name:	the extcon name provided with extcon_dev_रेजिस्टर()
 *
 * Return the poपूर्णांकer of extcon device अगर success or ERR_PTR(err) अगर fail.
 */
काष्ठा extcon_dev *extcon_get_extcon_dev(स्थिर अक्षर *extcon_name)
अणु
	काष्ठा extcon_dev *sd;

	अगर (!extcon_name)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&extcon_dev_list_lock);
	list_क्रम_each_entry(sd, &extcon_dev_list, entry) अणु
		अगर (!म_भेद(sd->name, extcon_name))
			जाओ out;
	पूर्ण
	sd = शून्य;
out:
	mutex_unlock(&extcon_dev_list_lock);
	वापस sd;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_get_extcon_dev);

/**
 * extcon_रेजिस्टर_notअगरier() - Register a notअगरier block to get notअगरied by
 *				any state changes from the extcon.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @nb:		a notअगरier block to be रेजिस्टरed
 *
 * Note that the second parameter given to the callback of nb (val) is
 * the current state of an बाह्यal connector and the third pameter
 * is the poपूर्णांकer of extcon device.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_रेजिस्टर_notअगरier(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
			     काष्ठा notअगरier_block *nb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, idx;

	अगर (!edev || !nb)
		वापस -EINVAL;

	idx = find_cable_index_by_id(edev, id);
	अगर (idx < 0)
		वापस idx;

	spin_lock_irqsave(&edev->lock, flags);
	ret = raw_notअगरier_chain_रेजिस्टर(&edev->nh[idx], nb);
	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_रेजिस्टर_notअगरier);

/**
 * extcon_unरेजिस्टर_notअगरier() - Unरेजिस्टर a notअगरier block from the extcon.
 * @edev:	the extcon device
 * @id:		the unique id indicating an बाह्यal connector
 * @nb:		a notअगरier block to be रेजिस्टरed
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_unरेजिस्टर_notअगरier(काष्ठा extcon_dev *edev, अचिन्हित पूर्णांक id,
				काष्ठा notअगरier_block *nb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, idx;

	अगर (!edev || !nb)
		वापस -EINVAL;

	idx = find_cable_index_by_id(edev, id);
	अगर (idx < 0)
		वापस idx;

	spin_lock_irqsave(&edev->lock, flags);
	ret = raw_notअगरier_chain_unरेजिस्टर(&edev->nh[idx], nb);
	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_unरेजिस्टर_notअगरier);

/**
 * extcon_रेजिस्टर_notअगरier_all() - Register a notअगरier block क्रम all connectors.
 * @edev:	the extcon device
 * @nb:		a notअगरier block to be रेजिस्टरed
 *
 * Note that this function रेजिस्टरs a notअगरier block in order to receive
 * the state change of all supported बाह्यal connectors from extcon device.
 * And the second parameter given to the callback of nb (val) is
 * the current state and the third pameter is the poपूर्णांकer of extcon device.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_रेजिस्टर_notअगरier_all(काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!edev || !nb)
		वापस -EINVAL;

	spin_lock_irqsave(&edev->lock, flags);
	ret = raw_notअगरier_chain_रेजिस्टर(&edev->nh_all, nb);
	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_रेजिस्टर_notअगरier_all);

/**
 * extcon_unरेजिस्टर_notअगरier_all() - Unरेजिस्टर a notअगरier block from extcon.
 * @edev:	the extcon device
 * @nb:		a notअगरier block to be रेजिस्टरed
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_unरेजिस्टर_notअगरier_all(काष्ठा extcon_dev *edev,
				काष्ठा notअगरier_block *nb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!edev || !nb)
		वापस -EINVAL;

	spin_lock_irqsave(&edev->lock, flags);
	ret = raw_notअगरier_chain_unरेजिस्टर(&edev->nh_all, nb);
	spin_unlock_irqrestore(&edev->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_unरेजिस्टर_notअगरier_all);

अटल काष्ठा attribute *extcon_attrs[] = अणु
	&dev_attr_state.attr,
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(extcon);

अटल पूर्णांक create_extcon_class(व्योम)
अणु
	अगर (!extcon_class) अणु
		extcon_class = class_create(THIS_MODULE, "extcon");
		अगर (IS_ERR(extcon_class))
			वापस PTR_ERR(extcon_class);
		extcon_class->dev_groups = extcon_groups;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम extcon_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल स्थिर अक्षर *muex_name = "mutually_exclusive";
अटल व्योम dummy_sysfs_dev_release(काष्ठा device *dev)
अणु
पूर्ण

/*
 * extcon_dev_allocate() - Allocate the memory of extcon device.
 * @supported_cable:	the array of the supported बाह्यal connectors
 *			ending with EXTCON_NONE.
 *
 * Note that this function allocates the memory क्रम extcon device 
 * and initialize शेष setting क्रम the extcon device.
 *
 * Returns the poपूर्णांकer memory of allocated extcon_dev अगर success
 * or ERR_PTR(err) अगर fail.
 */
काष्ठा extcon_dev *extcon_dev_allocate(स्थिर अचिन्हित पूर्णांक *supported_cable)
अणु
	काष्ठा extcon_dev *edev;

	अगर (!supported_cable)
		वापस ERR_PTR(-EINVAL);

	edev = kzalloc(माप(*edev), GFP_KERNEL);
	अगर (!edev)
		वापस ERR_PTR(-ENOMEM);

	edev->max_supported = 0;
	edev->supported_cable = supported_cable;

	वापस edev;
पूर्ण

/*
 * extcon_dev_मुक्त() - Free the memory of extcon device.
 * @edev:	the extcon device
 */
व्योम extcon_dev_मुक्त(काष्ठा extcon_dev *edev)
अणु
	kमुक्त(edev);
पूर्ण
EXPORT_SYMBOL_GPL(extcon_dev_मुक्त);

/**
 * extcon_dev_रेजिस्टर() - Register an new extcon device
 * @edev:	the extcon device to be रेजिस्टरed
 *
 * Among the members of edev काष्ठा, please set the "user initializing data"
 * करो not set the values of "internal data", which are initialized by
 * this function.
 *
 * Note that beक्रमe calling this funciton, have to allocate the memory
 * of an extcon device by using the extcon_dev_allocate(). And the extcon
 * dev should include the supported_cable inक्रमmation.
 *
 * Returns 0 अगर success or error number अगर fail.
 */
पूर्णांक extcon_dev_रेजिस्टर(काष्ठा extcon_dev *edev)
अणु
	पूर्णांक ret, index = 0;
	अटल atomic_t edev_no = ATOMIC_INIT(-1);

	अगर (!extcon_class) अणु
		ret = create_extcon_class();
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!edev || !edev->supported_cable)
		वापस -EINVAL;

	क्रम (; edev->supported_cable[index] != EXTCON_NONE; index++);

	edev->max_supported = index;
	अगर (index > SUPPORTED_CABLE_MAX) अणु
		dev_err(&edev->dev,
			"exceed the maximum number of supported cables\n");
		वापस -EINVAL;
	पूर्ण

	edev->dev.class = extcon_class;
	edev->dev.release = extcon_dev_release;

	edev->name = dev_name(edev->dev.parent);
	अगर (IS_ERR_OR_शून्य(edev->name)) अणु
		dev_err(&edev->dev,
			"extcon device name is null\n");
		वापस -EINVAL;
	पूर्ण
	dev_set_name(&edev->dev, "extcon%lu",
			(अचिन्हित दीर्घ)atomic_inc_वापस(&edev_no));

	अगर (edev->max_supported) अणु
		अक्षर *str;
		काष्ठा extcon_cable *cable;

		edev->cables = kसुस्मृति(edev->max_supported,
				       माप(काष्ठा extcon_cable),
				       GFP_KERNEL);
		अगर (!edev->cables) अणु
			ret = -ENOMEM;
			जाओ err_sysfs_alloc;
		पूर्ण
		क्रम (index = 0; index < edev->max_supported; index++) अणु
			cable = &edev->cables[index];

			str = kaप्र_लिखो(GFP_KERNEL, "cable.%d", index);
			अगर (!str) अणु
				क्रम (index--; index >= 0; index--) अणु
					cable = &edev->cables[index];
					kमुक्त(cable->attr_g.name);
				पूर्ण
				ret = -ENOMEM;

				जाओ err_alloc_cables;
			पूर्ण

			cable->edev = edev;
			cable->cable_index = index;
			cable->attrs[0] = &cable->attr_name.attr;
			cable->attrs[1] = &cable->attr_state.attr;
			cable->attrs[2] = शून्य;
			cable->attr_g.name = str;
			cable->attr_g.attrs = cable->attrs;

			sysfs_attr_init(&cable->attr_name.attr);
			cable->attr_name.attr.name = "name";
			cable->attr_name.attr.mode = 0444;
			cable->attr_name.show = cable_name_show;

			sysfs_attr_init(&cable->attr_state.attr);
			cable->attr_state.attr.name = "state";
			cable->attr_state.attr.mode = 0444;
			cable->attr_state.show = cable_state_show;
		पूर्ण
	पूर्ण

	अगर (edev->max_supported && edev->mutually_exclusive) अणु
		अक्षर *name;

		/* Count the size of mutually_exclusive array */
		क्रम (index = 0; edev->mutually_exclusive[index]; index++)
			;

		edev->attrs_muex = kसुस्मृति(index + 1,
					   माप(काष्ठा attribute *),
					   GFP_KERNEL);
		अगर (!edev->attrs_muex) अणु
			ret = -ENOMEM;
			जाओ err_muex;
		पूर्ण

		edev->d_attrs_muex = kसुस्मृति(index,
					     माप(काष्ठा device_attribute),
					     GFP_KERNEL);
		अगर (!edev->d_attrs_muex) अणु
			ret = -ENOMEM;
			kमुक्त(edev->attrs_muex);
			जाओ err_muex;
		पूर्ण

		क्रम (index = 0; edev->mutually_exclusive[index]; index++) अणु
			name = kaप्र_लिखो(GFP_KERNEL, "0x%x",
					 edev->mutually_exclusive[index]);
			अगर (!name) अणु
				क्रम (index--; index >= 0; index--) अणु
					kमुक्त(edev->d_attrs_muex[index].attr.
					      name);
				पूर्ण
				kमुक्त(edev->d_attrs_muex);
				kमुक्त(edev->attrs_muex);
				ret = -ENOMEM;
				जाओ err_muex;
			पूर्ण
			sysfs_attr_init(&edev->d_attrs_muex[index].attr);
			edev->d_attrs_muex[index].attr.name = name;
			edev->d_attrs_muex[index].attr.mode = 0000;
			edev->attrs_muex[index] = &edev->d_attrs_muex[index]
							.attr;
		पूर्ण
		edev->attr_g_muex.name = muex_name;
		edev->attr_g_muex.attrs = edev->attrs_muex;

	पूर्ण

	अगर (edev->max_supported) अणु
		edev->extcon_dev_type.groups =
			kसुस्मृति(edev->max_supported + 2,
				माप(काष्ठा attribute_group *),
				GFP_KERNEL);
		अगर (!edev->extcon_dev_type.groups) अणु
			ret = -ENOMEM;
			जाओ err_alloc_groups;
		पूर्ण

		edev->extcon_dev_type.name = dev_name(&edev->dev);
		edev->extcon_dev_type.release = dummy_sysfs_dev_release;

		क्रम (index = 0; index < edev->max_supported; index++)
			edev->extcon_dev_type.groups[index] =
				&edev->cables[index].attr_g;
		अगर (edev->mutually_exclusive)
			edev->extcon_dev_type.groups[index] =
				&edev->attr_g_muex;

		edev->dev.type = &edev->extcon_dev_type;
	पूर्ण

	ret = device_रेजिस्टर(&edev->dev);
	अगर (ret) अणु
		put_device(&edev->dev);
		जाओ err_dev;
	पूर्ण

	spin_lock_init(&edev->lock);
	edev->nh = devm_kसुस्मृति(&edev->dev, edev->max_supported,
				माप(*edev->nh), GFP_KERNEL);
	अगर (!edev->nh) अणु
		ret = -ENOMEM;
		device_unरेजिस्टर(&edev->dev);
		जाओ err_dev;
	पूर्ण

	क्रम (index = 0; index < edev->max_supported; index++)
		RAW_INIT_NOTIFIER_HEAD(&edev->nh[index]);

	RAW_INIT_NOTIFIER_HEAD(&edev->nh_all);

	dev_set_drvdata(&edev->dev, edev);
	edev->state = 0;

	mutex_lock(&extcon_dev_list_lock);
	list_add(&edev->entry, &extcon_dev_list);
	mutex_unlock(&extcon_dev_list_lock);

	वापस 0;

err_dev:
	अगर (edev->max_supported)
		kमुक्त(edev->extcon_dev_type.groups);
err_alloc_groups:
	अगर (edev->max_supported && edev->mutually_exclusive) अणु
		क्रम (index = 0; edev->mutually_exclusive[index]; index++)
			kमुक्त(edev->d_attrs_muex[index].attr.name);
		kमुक्त(edev->d_attrs_muex);
		kमुक्त(edev->attrs_muex);
	पूर्ण
err_muex:
	क्रम (index = 0; index < edev->max_supported; index++)
		kमुक्त(edev->cables[index].attr_g.name);
err_alloc_cables:
	अगर (edev->max_supported)
		kमुक्त(edev->cables);
err_sysfs_alloc:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_dev_रेजिस्टर);

/**
 * extcon_dev_unरेजिस्टर() - Unरेजिस्टर the extcon device.
 * @edev:	the extcon device to be unरेजिस्टरed.
 *
 * Note that this करोes not call kमुक्त(edev) because edev was not allocated
 * by this class.
 */
व्योम extcon_dev_unरेजिस्टर(काष्ठा extcon_dev *edev)
अणु
	पूर्णांक index;

	अगर (!edev)
		वापस;

	mutex_lock(&extcon_dev_list_lock);
	list_del(&edev->entry);
	mutex_unlock(&extcon_dev_list_lock);

	अगर (IS_ERR_OR_शून्य(get_device(&edev->dev))) अणु
		dev_err(&edev->dev, "Failed to unregister extcon_dev (%s)\n",
				dev_name(&edev->dev));
		वापस;
	पूर्ण

	device_unरेजिस्टर(&edev->dev);

	अगर (edev->mutually_exclusive && edev->max_supported) अणु
		क्रम (index = 0; edev->mutually_exclusive[index];
				index++)
			kमुक्त(edev->d_attrs_muex[index].attr.name);
		kमुक्त(edev->d_attrs_muex);
		kमुक्त(edev->attrs_muex);
	पूर्ण

	क्रम (index = 0; index < edev->max_supported; index++)
		kमुक्त(edev->cables[index].attr_g.name);

	अगर (edev->max_supported) अणु
		kमुक्त(edev->extcon_dev_type.groups);
		kमुक्त(edev->cables);
	पूर्ण

	put_device(&edev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(extcon_dev_unरेजिस्टर);

#अगर_घोषित CONFIG_OF

/*
 * extcon_find_edev_by_node - Find the extcon device from devicetree.
 * @node	: OF node identअगरying edev
 *
 * Return the poपूर्णांकer of extcon device अगर success or ERR_PTR(err) अगर fail.
 */
काष्ठा extcon_dev *extcon_find_edev_by_node(काष्ठा device_node *node)
अणु
	काष्ठा extcon_dev *edev;

	mutex_lock(&extcon_dev_list_lock);
	list_क्रम_each_entry(edev, &extcon_dev_list, entry)
		अगर (edev->dev.parent && edev->dev.parent->of_node == node)
			जाओ out;
	edev = ERR_PTR(-EPROBE_DEFER);
out:
	mutex_unlock(&extcon_dev_list_lock);

	वापस edev;
पूर्ण

/*
 * extcon_get_edev_by_phandle - Get the extcon device from devicetree.
 * @dev		: the instance to the given device
 * @index	: the index पूर्णांकo list of extcon_dev
 *
 * Return the poपूर्णांकer of extcon device अगर success or ERR_PTR(err) अगर fail.
 */
काष्ठा extcon_dev *extcon_get_edev_by_phandle(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा device_node *node;
	काष्ठा extcon_dev *edev;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	अगर (!dev->of_node) अणु
		dev_dbg(dev, "device does not have a device node entry\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	node = of_parse_phandle(dev->of_node, "extcon", index);
	अगर (!node) अणु
		dev_dbg(dev, "failed to get phandle in %pOF node\n",
			dev->of_node);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	edev = extcon_find_edev_by_node(node);
	of_node_put(node);

	वापस edev;
पूर्ण

#अन्यथा

काष्ठा extcon_dev *extcon_find_edev_by_node(काष्ठा device_node *node)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

काष्ठा extcon_dev *extcon_get_edev_by_phandle(काष्ठा device *dev, पूर्णांक index)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

#पूर्ण_अगर /* CONFIG_OF */

EXPORT_SYMBOL_GPL(extcon_find_edev_by_node);
EXPORT_SYMBOL_GPL(extcon_get_edev_by_phandle);

/**
 * extcon_get_edev_name() - Get the name of the extcon device.
 * @edev:	the extcon device
 */
स्थिर अक्षर *extcon_get_edev_name(काष्ठा extcon_dev *edev)
अणु
	वापस !edev ? शून्य : edev->name;
पूर्ण
EXPORT_SYMBOL_GPL(extcon_get_edev_name);

अटल पूर्णांक __init extcon_class_init(व्योम)
अणु
	वापस create_extcon_class();
पूर्ण
module_init(extcon_class_init);

अटल व्योम __निकास extcon_class_निकास(व्योम)
अणु
	class_destroy(extcon_class);
पूर्ण
module_निकास(extcon_class_निकास);

MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_DESCRIPTION("External Connector (extcon) framework");
MODULE_LICENSE("GPL v2");
