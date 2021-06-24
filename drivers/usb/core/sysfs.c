<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/core/sysfs.c
 *
 * (C) Copyright 2002 David Brownell
 * (C) Copyright 2002,2004 Greg Kroah-Harपंचांगan
 * (C) Copyright 2002,2004 IBM Corp.
 *
 * All of the sysfs file attributes क्रम usb devices and पूर्णांकerfaces.
 *
 * Released under the GPLv2 only.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/of.h>
#समावेश "usb.h"

/* Active configuration fields */
#घोषणा usb_actconfig_show(field, क्रमmat_string)			\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा usb_device *udev;					\
	काष्ठा usb_host_config *actconfig;				\
	sमाप_प्रकार rc;							\
									\
	udev = to_usb_device(dev);					\
	rc = usb_lock_device_पूर्णांकerruptible(udev);			\
	अगर (rc < 0)							\
		वापस -EINTR;						\
	actconfig = udev->actconfig;					\
	अगर (actconfig)							\
		rc = प्र_लिखो(buf, क्रमmat_string,			\
				actconfig->desc.field);			\
	usb_unlock_device(udev);					\
	वापस rc;							\
पूर्ण									\

#घोषणा usb_actconfig_attr(field, क्रमmat_string)		\
	usb_actconfig_show(field, क्रमmat_string)		\
	अटल DEVICE_ATTR_RO(field)

usb_actconfig_attr(bNumInterfaces, "%2d\n");
usb_actconfig_attr(bmAttributes, "%2x\n");

अटल sमाप_प्रकार bMaxPower_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_host_config *actconfig;
	sमाप_प्रकार rc;

	udev = to_usb_device(dev);
	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;
	actconfig = udev->actconfig;
	अगर (actconfig)
		rc = प्र_लिखो(buf, "%dmA\n", usb_get_max_घातer(udev, actconfig));
	usb_unlock_device(udev);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(bMaxPower);

अटल sमाप_प्रकार configuration_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_host_config *actconfig;
	sमाप_प्रकार rc;

	udev = to_usb_device(dev);
	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;
	actconfig = udev->actconfig;
	अगर (actconfig && actconfig->string)
		rc = प्र_लिखो(buf, "%s\n", actconfig->string);
	usb_unlock_device(udev);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(configuration);

/* configuration value is always present, and r/w */
usb_actconfig_show(bConfigurationValue, "%u\n");

अटल sमाप_प्रकार bConfigurationValue_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);
	पूर्णांक			config, value, rc;

	अगर (माला_पूछो(buf, "%d", &config) != 1 || config < -1 || config > 255)
		वापस -EINVAL;
	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;
	value = usb_set_configuration(udev, config);
	usb_unlock_device(udev);
	वापस (value < 0) ? value : count;
पूर्ण
अटल DEVICE_ATTR_IGNORE_LOCKDEP(bConfigurationValue, S_IRUGO | S_IWUSR,
		bConfigurationValue_show, bConfigurationValue_store);

#अगर_घोषित CONFIG_OF
अटल sमाप_प्रकार devspec_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा device_node *of_node = dev->of_node;

	वापस प्र_लिखो(buf, "%pOF\n", of_node);
पूर्ण
अटल DEVICE_ATTR_RO(devspec);
#पूर्ण_अगर

/* String fields */
#घोषणा usb_string_attr(name)						\
अटल sमाप_प्रकार  name##_show(काष्ठा device *dev,				\
		काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा usb_device *udev;					\
	पूर्णांक retval;							\
									\
	udev = to_usb_device(dev);					\
	retval = usb_lock_device_पूर्णांकerruptible(udev);			\
	अगर (retval < 0)							\
		वापस -EINTR;						\
	retval = प्र_लिखो(buf, "%s\n", udev->name);			\
	usb_unlock_device(udev);					\
	वापस retval;							\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

usb_string_attr(product);
usb_string_attr(manufacturer);
usb_string_attr(serial);

अटल sमाप_प्रकार speed_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा usb_device *udev;
	अक्षर *speed;

	udev = to_usb_device(dev);

	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		speed = "1.5";
		अवरोध;
	हाल USB_SPEED_UNKNOWN:
	हाल USB_SPEED_FULL:
		speed = "12";
		अवरोध;
	हाल USB_SPEED_HIGH:
		speed = "480";
		अवरोध;
	हाल USB_SPEED_WIRELESS:
		speed = "480";
		अवरोध;
	हाल USB_SPEED_SUPER:
		speed = "5000";
		अवरोध;
	हाल USB_SPEED_SUPER_PLUS:
		अगर (udev->ssp_rate == USB_SSP_GEN_2x2)
			speed = "20000";
		अन्यथा
			speed = "10000";
		अवरोध;
	शेष:
		speed = "unknown";
	पूर्ण
	वापस प्र_लिखो(buf, "%s\n", speed);
पूर्ण
अटल DEVICE_ATTR_RO(speed);

अटल sमाप_प्रकार rx_lanes_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->rx_lanes);
पूर्ण
अटल DEVICE_ATTR_RO(rx_lanes);

अटल sमाप_प्रकार tx_lanes_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->tx_lanes);
पूर्ण
अटल DEVICE_ATTR_RO(tx_lanes);

अटल sमाप_प्रकार busnum_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->bus->busnum);
पूर्ण
अटल DEVICE_ATTR_RO(busnum);

अटल sमाप_प्रकार devnum_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->devnum);
पूर्ण
अटल DEVICE_ATTR_RO(devnum);

अटल sमाप_प्रकार devpath_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%s\n", udev->devpath);
पूर्ण
अटल DEVICE_ATTR_RO(devpath);

अटल sमाप_प्रकार version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा usb_device *udev;
	u16 bcdUSB;

	udev = to_usb_device(dev);
	bcdUSB = le16_to_cpu(udev->descriptor.bcdUSB);
	वापस प्र_लिखो(buf, "%2x.%02x\n", bcdUSB >> 8, bcdUSB & 0xff);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार maxchild_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->maxchild);
पूर्ण
अटल DEVICE_ATTR_RO(maxchild);

अटल sमाप_प्रकार quirks_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "0x%x\n", udev->quirks);
पूर्ण
अटल DEVICE_ATTR_RO(quirks);

अटल sमाप_प्रकार aव्योम_reset_quirk_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", !!(udev->quirks & USB_QUIRK_RESET));
पूर्ण

अटल sमाप_प्रकार aव्योम_reset_quirk_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device	*udev = to_usb_device(dev);
	पूर्णांक			val, rc;

	अगर (माला_पूछो(buf, "%d", &val) != 1 || val < 0 || val > 1)
		वापस -EINVAL;
	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;
	अगर (val)
		udev->quirks |= USB_QUIRK_RESET;
	अन्यथा
		udev->quirks &= ~USB_QUIRK_RESET;
	usb_unlock_device(udev);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(aव्योम_reset_quirk);

अटल sमाप_प्रकार urbnum_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा usb_device *udev;

	udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", atomic_पढ़ो(&udev->urbnum));
पूर्ण
अटल DEVICE_ATTR_RO(urbnum);

अटल sमाप_प्रकार removable_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा usb_device *udev;
	अक्षर *state;

	udev = to_usb_device(dev);

	चयन (udev->removable) अणु
	हाल USB_DEVICE_REMOVABLE:
		state = "removable";
		अवरोध;
	हाल USB_DEVICE_FIXED:
		state = "fixed";
		अवरोध;
	शेष:
		state = "unknown";
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", state);
पूर्ण
अटल DEVICE_ATTR_RO(removable);

अटल sमाप_प्रकार lपंचांग_capable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (usb_device_supports_lपंचांग(to_usb_device(dev)))
		वापस प्र_लिखो(buf, "%s\n", "yes");
	वापस प्र_लिखो(buf, "%s\n", "no");
पूर्ण
अटल DEVICE_ATTR_RO(lपंचांग_capable);

#अगर_घोषित	CONFIG_PM

अटल sमाप_प्रकार persist_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);

	वापस प्र_लिखो(buf, "%d\n", udev->persist_enabled);
पूर्ण

अटल sमाप_प्रकार persist_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	पूर्णांक value, rc;

	/* Hubs are always enabled क्रम USB_PERSIST */
	अगर (udev->descriptor.bDeviceClass == USB_CLASS_HUB)
		वापस -EPERM;

	अगर (माला_पूछो(buf, "%d", &value) != 1)
		वापस -EINVAL;

	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;
	udev->persist_enabled = !!value;
	usb_unlock_device(udev);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(persist);

अटल पूर्णांक add_persist_attributes(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	अगर (is_usb_device(dev)) अणु
		काष्ठा usb_device *udev = to_usb_device(dev);

		/* Hubs are स्वतःmatically enabled क्रम USB_PERSIST,
		 * no poपूर्णांक in creating the attribute file.
		 */
		अगर (udev->descriptor.bDeviceClass != USB_CLASS_HUB)
			rc = sysfs_add_file_to_group(&dev->kobj,
					&dev_attr_persist.attr,
					घातer_group_name);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम हटाओ_persist_attributes(काष्ठा device *dev)
अणु
	sysfs_हटाओ_file_from_group(&dev->kobj,
			&dev_attr_persist.attr,
			घातer_group_name);
पूर्ण

अटल sमाप_प्रकार connected_duration_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);

	वापस प्र_लिखो(buf, "%u\n",
			jअगरfies_to_msecs(jअगरfies - udev->connect_समय));
पूर्ण
अटल DEVICE_ATTR_RO(connected_duration);

/*
 * If the device is resumed, the last समय the device was suspended has
 * been pre-subtracted from active_duration.  We add the current समय to
 * get the duration that the device was actually active.
 *
 * If the device is suspended, the active_duration is up-to-date.
 */
अटल sमाप_प्रकार active_duration_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	पूर्णांक duration;

	अगर (udev->state != USB_STATE_SUSPENDED)
		duration = jअगरfies_to_msecs(jअगरfies + udev->active_duration);
	अन्यथा
		duration = jअगरfies_to_msecs(udev->active_duration);
	वापस प्र_लिखो(buf, "%u\n", duration);
पूर्ण
अटल DEVICE_ATTR_RO(active_duration);

अटल sमाप_प्रकार स्वतःsuspend_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", dev->घातer.स्वतःsuspend_delay / 1000);
पूर्ण

अटल sमाप_प्रकार स्वतःsuspend_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	पूर्णांक value;

	अगर (माला_पूछो(buf, "%d", &value) != 1 || value >= पूर्णांक_उच्च/1000 ||
			value <= -पूर्णांक_उच्च/1000)
		वापस -EINVAL;

	pm_runसमय_set_स्वतःsuspend_delay(dev, value * 1000);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(स्वतःsuspend);

अटल स्थिर अक्षर on_string[] = "on";
अटल स्थिर अक्षर स्वतः_string[] = "auto";

अटल व्योम warn_level(व्योम)
अणु
	अटल पूर्णांक level_warned;

	अगर (!level_warned) अणु
		level_warned = 1;
		prपूर्णांकk(KERN_WARNING "WARNING! power/level is deprecated; "
				"use power/control instead\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार level_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	स्थिर अक्षर *p = स्वतः_string;

	warn_level();
	अगर (udev->state != USB_STATE_SUSPENDED && !udev->dev.घातer.runसमय_स्वतः)
		p = on_string;
	वापस प्र_लिखो(buf, "%s\n", p);
पूर्ण

अटल sमाप_प्रकार level_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	पूर्णांक len = count;
	अक्षर *cp;
	पूर्णांक rc = count;
	पूर्णांक rv;

	warn_level();
	cp = स_प्रथम(buf, '\n', count);
	अगर (cp)
		len = cp - buf;

	rv = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rv < 0)
		वापस -EINTR;

	अगर (len == माप on_string - 1 &&
			म_भेदन(buf, on_string, len) == 0)
		usb_disable_स्वतःsuspend(udev);

	अन्यथा अगर (len == माप स्वतः_string - 1 &&
			म_भेदन(buf, स्वतः_string, len) == 0)
		usb_enable_स्वतःsuspend(udev);

	अन्यथा
		rc = -EINVAL;

	usb_unlock_device(udev);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(level);

अटल sमाप_प्रकार usb2_hardware_lpm_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	स्थिर अक्षर *p;

	अगर (udev->usb2_hw_lpm_allowed == 1)
		p = "enabled";
	अन्यथा
		p = "disabled";

	वापस प्र_लिखो(buf, "%s\n", p);
पूर्ण

अटल sमाप_प्रकार usb2_hardware_lpm_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	bool value;
	पूर्णांक ret;

	ret = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (ret < 0)
		वापस -EINTR;

	ret = strtobool(buf, &value);

	अगर (!ret) अणु
		udev->usb2_hw_lpm_allowed = value;
		अगर (value)
			ret = usb_enable_usb2_hardware_lpm(udev);
		अन्यथा
			ret = usb_disable_usb2_hardware_lpm(udev);
	पूर्ण

	usb_unlock_device(udev);

	अगर (!ret)
		वापस count;

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(usb2_hardware_lpm);

अटल sमाप_प्रकार usb2_lpm_l1_समयout_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->l1_params.समयout);
पूर्ण

अटल sमाप_प्रकार usb2_lpm_l1_समयout_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	u16 समयout;

	अगर (kstrtou16(buf, 0, &समयout))
		वापस -EINVAL;

	udev->l1_params.समयout = समयout;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb2_lpm_l1_समयout);

अटल sमाप_प्रकार usb2_lpm_besl_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	वापस प्र_लिखो(buf, "%d\n", udev->l1_params.besl);
पूर्ण

अटल sमाप_प्रकार usb2_lpm_besl_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	u8 besl;

	अगर (kstrtou8(buf, 0, &besl) || besl > 15)
		वापस -EINVAL;

	udev->l1_params.besl = besl;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb2_lpm_besl);

अटल sमाप_प्रकार usb3_hardware_lpm_u1_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	स्थिर अक्षर *p;
	पूर्णांक rc;

	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;

	अगर (udev->usb3_lpm_u1_enabled)
		p = "enabled";
	अन्यथा
		p = "disabled";

	usb_unlock_device(udev);

	वापस प्र_लिखो(buf, "%s\n", p);
पूर्ण
अटल DEVICE_ATTR_RO(usb3_hardware_lpm_u1);

अटल sमाप_प्रकार usb3_hardware_lpm_u2_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	स्थिर अक्षर *p;
	पूर्णांक rc;

	rc = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (rc < 0)
		वापस -EINTR;

	अगर (udev->usb3_lpm_u2_enabled)
		p = "enabled";
	अन्यथा
		p = "disabled";

	usb_unlock_device(udev);

	वापस प्र_लिखो(buf, "%s\n", p);
पूर्ण
अटल DEVICE_ATTR_RO(usb3_hardware_lpm_u2);

अटल काष्ठा attribute *usb2_hardware_lpm_attr[] = अणु
	&dev_attr_usb2_hardware_lpm.attr,
	&dev_attr_usb2_lpm_l1_समयout.attr,
	&dev_attr_usb2_lpm_besl.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group usb2_hardware_lpm_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= usb2_hardware_lpm_attr,
पूर्ण;

अटल काष्ठा attribute *usb3_hardware_lpm_attr[] = अणु
	&dev_attr_usb3_hardware_lpm_u1.attr,
	&dev_attr_usb3_hardware_lpm_u2.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group usb3_hardware_lpm_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= usb3_hardware_lpm_attr,
पूर्ण;

अटल काष्ठा attribute *घातer_attrs[] = अणु
	&dev_attr_स्वतःsuspend.attr,
	&dev_attr_level.attr,
	&dev_attr_connected_duration.attr,
	&dev_attr_active_duration.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group घातer_attr_group = अणु
	.name	= घातer_group_name,
	.attrs	= घातer_attrs,
पूर्ण;

अटल पूर्णांक add_घातer_attributes(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	अगर (is_usb_device(dev)) अणु
		काष्ठा usb_device *udev = to_usb_device(dev);
		rc = sysfs_merge_group(&dev->kobj, &घातer_attr_group);
		अगर (udev->usb2_hw_lpm_capable == 1)
			rc = sysfs_merge_group(&dev->kobj,
					&usb2_hardware_lpm_attr_group);
		अगर ((udev->speed == USB_SPEED_SUPER ||
		     udev->speed == USB_SPEED_SUPER_PLUS) &&
				udev->lpm_capable == 1)
			rc = sysfs_merge_group(&dev->kobj,
					&usb3_hardware_lpm_attr_group);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम हटाओ_घातer_attributes(काष्ठा device *dev)
अणु
	sysfs_unmerge_group(&dev->kobj, &usb2_hardware_lpm_attr_group);
	sysfs_unmerge_group(&dev->kobj, &घातer_attr_group);
पूर्ण

#अन्यथा

#घोषणा add_persist_attributes(dev)	0
#घोषणा हटाओ_persist_attributes(dev)	करो अणुपूर्ण जबतक (0)

#घोषणा add_घातer_attributes(dev)	0
#घोषणा हटाओ_घातer_attributes(dev)	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर	/* CONFIG_PM */


/* Descriptor fields */
#घोषणा usb_descriptor_attr_le16(field, क्रमmat_string)			\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		अक्षर *buf)						\
अणु									\
	काष्ठा usb_device *udev;					\
									\
	udev = to_usb_device(dev);					\
	वापस प्र_लिखो(buf, क्रमmat_string, 				\
			le16_to_cpu(udev->descriptor.field));		\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

usb_descriptor_attr_le16(idVenकरोr, "%04x\n");
usb_descriptor_attr_le16(idProduct, "%04x\n");
usb_descriptor_attr_le16(bcdDevice, "%04x\n");

#घोषणा usb_descriptor_attr(field, क्रमmat_string)			\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		अक्षर *buf)						\
अणु									\
	काष्ठा usb_device *udev;					\
									\
	udev = to_usb_device(dev);					\
	वापस प्र_लिखो(buf, क्रमmat_string, udev->descriptor.field);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

usb_descriptor_attr(bDeviceClass, "%02x\n");
usb_descriptor_attr(bDeviceSubClass, "%02x\n");
usb_descriptor_attr(bDeviceProtocol, "%02x\n");
usb_descriptor_attr(bNumConfigurations, "%d\n");
usb_descriptor_attr(bMaxPacketSize0, "%d\n");


/* show अगर the device is authorized (1) or not (0) */
अटल sमाप_प्रकार authorized_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *usb_dev = to_usb_device(dev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", usb_dev->authorized);
पूर्ण

/*
 * Authorize a device to be used in the प्रणाली
 *
 * Writing a 0 deauthorizes the device, writing a 1 authorizes it.
 */
अटल sमाप_प्रकार authorized_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार size)
अणु
	sमाप_प्रकार result;
	काष्ठा usb_device *usb_dev = to_usb_device(dev);
	अचिन्हित val;
	result = माला_पूछो(buf, "%u\n", &val);
	अगर (result != 1)
		result = -EINVAL;
	अन्यथा अगर (val == 0)
		result = usb_deauthorize_device(usb_dev);
	अन्यथा
		result = usb_authorize_device(usb_dev);
	वापस result < 0 ? result : size;
पूर्ण
अटल DEVICE_ATTR_IGNORE_LOCKDEP(authorized, S_IRUGO | S_IWUSR,
				  authorized_show, authorized_store);

/* "Safely remove a device" */
अटल sमाप_प्रकार हटाओ_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	पूर्णांक rc = 0;

	usb_lock_device(udev);
	अगर (udev->state != USB_STATE_NOTATTACHED) अणु

		/* To aव्योम races, first unconfigure and then हटाओ */
		usb_set_configuration(udev, -1);
		rc = usb_हटाओ_device(udev);
	पूर्ण
	अगर (rc == 0)
		rc = count;
	usb_unlock_device(udev);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_IGNORE_LOCKDEP(हटाओ, S_IWUSR, शून्य, हटाओ_store);


अटल काष्ठा attribute *dev_attrs[] = अणु
	/* current configuration's attributes */
	&dev_attr_configuration.attr,
	&dev_attr_bNumInterfaces.attr,
	&dev_attr_bConfigurationValue.attr,
	&dev_attr_bmAttributes.attr,
	&dev_attr_bMaxPower.attr,
	/* device attributes */
	&dev_attr_urbnum.attr,
	&dev_attr_idVenकरोr.attr,
	&dev_attr_idProduct.attr,
	&dev_attr_bcdDevice.attr,
	&dev_attr_bDeviceClass.attr,
	&dev_attr_bDeviceSubClass.attr,
	&dev_attr_bDeviceProtocol.attr,
	&dev_attr_bNumConfigurations.attr,
	&dev_attr_bMaxPacketSize0.attr,
	&dev_attr_speed.attr,
	&dev_attr_rx_lanes.attr,
	&dev_attr_tx_lanes.attr,
	&dev_attr_busnum.attr,
	&dev_attr_devnum.attr,
	&dev_attr_devpath.attr,
	&dev_attr_version.attr,
	&dev_attr_maxchild.attr,
	&dev_attr_quirks.attr,
	&dev_attr_aव्योम_reset_quirk.attr,
	&dev_attr_authorized.attr,
	&dev_attr_हटाओ.attr,
	&dev_attr_removable.attr,
	&dev_attr_lपंचांग_capable.attr,
#अगर_घोषित CONFIG_OF
	&dev_attr_devspec.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group dev_attr_grp = अणु
	.attrs = dev_attrs,
पूर्ण;

/* When modअगरying this list, be sure to modअगरy dev_string_attrs_are_visible()
 * accordingly.
 */
अटल काष्ठा attribute *dev_string_attrs[] = अणु
	&dev_attr_manufacturer.attr,
	&dev_attr_product.attr,
	&dev_attr_serial.attr,
	शून्य
पूर्ण;

अटल umode_t dev_string_attrs_are_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा usb_device *udev = to_usb_device(dev);

	अगर (a == &dev_attr_manufacturer.attr) अणु
		अगर (udev->manufacturer == शून्य)
			वापस 0;
	पूर्ण अन्यथा अगर (a == &dev_attr_product.attr) अणु
		अगर (udev->product == शून्य)
			वापस 0;
	पूर्ण अन्यथा अगर (a == &dev_attr_serial.attr) अणु
		अगर (udev->serial == शून्य)
			वापस 0;
	पूर्ण
	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group dev_string_attr_grp = अणु
	.attrs =	dev_string_attrs,
	.is_visible =	dev_string_attrs_are_visible,
पूर्ण;

स्थिर काष्ठा attribute_group *usb_device_groups[] = अणु
	&dev_attr_grp,
	&dev_string_attr_grp,
	शून्य
पूर्ण;

/* Binary descriptors */

अटल sमाप_प्रकार
पढ़ो_descriptors(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा usb_device *udev = to_usb_device(dev);
	माप_प्रकार nleft = count;
	माप_प्रकार srclen, n;
	पूर्णांक cfgno;
	व्योम *src;
	पूर्णांक retval;

	retval = usb_lock_device_पूर्णांकerruptible(udev);
	अगर (retval < 0)
		वापस -EINTR;
	/* The binary attribute begins with the device descriptor.
	 * Following that are the raw descriptor entries क्रम all the
	 * configurations (config plus subsidiary descriptors).
	 */
	क्रम (cfgno = -1; cfgno < udev->descriptor.bNumConfigurations &&
			nleft > 0; ++cfgno) अणु
		अगर (cfgno < 0) अणु
			src = &udev->descriptor;
			srclen = माप(काष्ठा usb_device_descriptor);
		पूर्ण अन्यथा अणु
			src = udev->rawdescriptors[cfgno];
			srclen = __le16_to_cpu(udev->config[cfgno].desc.
					wTotalLength);
		पूर्ण
		अगर (off < srclen) अणु
			n = min(nleft, srclen - (माप_प्रकार) off);
			स_नकल(buf, src + off, n);
			nleft -= n;
			buf += n;
			off = 0;
		पूर्ण अन्यथा अणु
			off -= srclen;
		पूर्ण
	पूर्ण
	usb_unlock_device(udev);
	वापस count - nleft;
पूर्ण

अटल काष्ठा bin_attribute dev_bin_attr_descriptors = अणु
	.attr = अणु.name = "descriptors", .mode = 0444पूर्ण,
	.पढ़ो = पढ़ो_descriptors,
	.size = 18 + 65535,	/* dev descr + max-size raw descriptor */
पूर्ण;

/*
 * Show & store the current value of authorized_शेष
 */
अटल sमाप_प्रकार authorized_शेष_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *rh_usb_dev = to_usb_device(dev);
	काष्ठा usb_bus *usb_bus = rh_usb_dev->bus;
	काष्ठा usb_hcd *hcd;

	hcd = bus_to_hcd(usb_bus);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", hcd->dev_policy);
पूर्ण

अटल sमाप_प्रकार authorized_शेष_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार result;
	अचिन्हित पूर्णांक val;
	काष्ठा usb_device *rh_usb_dev = to_usb_device(dev);
	काष्ठा usb_bus *usb_bus = rh_usb_dev->bus;
	काष्ठा usb_hcd *hcd;

	hcd = bus_to_hcd(usb_bus);
	result = माला_पूछो(buf, "%u\n", &val);
	अगर (result == 1) अणु
		hcd->dev_policy = val <= USB_DEVICE_AUTHORIZE_INTERNAL ?
			val : USB_DEVICE_AUTHORIZE_ALL;
		result = size;
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	वापस result;
पूर्ण
अटल DEVICE_ATTR_RW(authorized_शेष);

/*
 * पूर्णांकerface_authorized_शेष_show - show शेष authorization status
 * क्रम USB पूर्णांकerfaces
 *
 * note: पूर्णांकerface_authorized_शेष is the शेष value
 *       क्रम initializing the authorized attribute of पूर्णांकerfaces
 */
अटल sमाप_प्रकार पूर्णांकerface_authorized_शेष_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_device *usb_dev = to_usb_device(dev);
	काष्ठा usb_hcd *hcd = bus_to_hcd(usb_dev->bus);

	वापस प्र_लिखो(buf, "%u\n", !!HCD_INTF_AUTHORIZED(hcd));
पूर्ण

/*
 * पूर्णांकerface_authorized_शेष_store - store शेष authorization status
 * क्रम USB पूर्णांकerfaces
 *
 * note: पूर्णांकerface_authorized_शेष is the शेष value
 *       क्रम initializing the authorized attribute of पूर्णांकerfaces
 */
अटल sमाप_प्रकार पूर्णांकerface_authorized_शेष_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *usb_dev = to_usb_device(dev);
	काष्ठा usb_hcd *hcd = bus_to_hcd(usb_dev->bus);
	पूर्णांक rc = count;
	bool val;

	अगर (strtobool(buf, &val) != 0)
		वापस -EINVAL;

	अगर (val)
		set_bit(HCD_FLAG_INTF_AUTHORIZED, &hcd->flags);
	अन्यथा
		clear_bit(HCD_FLAG_INTF_AUTHORIZED, &hcd->flags);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(पूर्णांकerface_authorized_शेष);

/* Group all the USB bus attributes */
अटल काष्ठा attribute *usb_bus_attrs[] = अणु
		&dev_attr_authorized_शेष.attr,
		&dev_attr_पूर्णांकerface_authorized_शेष.attr,
		शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group usb_bus_attr_group = अणु
	.name = शून्य,	/* we want them in the same directory */
	.attrs = usb_bus_attrs,
पूर्ण;


अटल पूर्णांक add_शेष_authorized_attributes(काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	अगर (is_usb_device(dev))
		rc = sysfs_create_group(&dev->kobj, &usb_bus_attr_group);

	वापस rc;
पूर्ण

अटल व्योम हटाओ_शेष_authorized_attributes(काष्ठा device *dev)
अणु
	अगर (is_usb_device(dev)) अणु
		sysfs_हटाओ_group(&dev->kobj, &usb_bus_attr_group);
	पूर्ण
पूर्ण

पूर्णांक usb_create_sysfs_dev_files(काष्ठा usb_device *udev)
अणु
	काष्ठा device *dev = &udev->dev;
	पूर्णांक retval;

	retval = device_create_bin_file(dev, &dev_bin_attr_descriptors);
	अगर (retval)
		जाओ error;

	retval = add_persist_attributes(dev);
	अगर (retval)
		जाओ error;

	retval = add_घातer_attributes(dev);
	अगर (retval)
		जाओ error;

	अगर (is_root_hub(udev)) अणु
		retval = add_शेष_authorized_attributes(dev);
		अगर (retval)
			जाओ error;
	पूर्ण
	वापस retval;

error:
	usb_हटाओ_sysfs_dev_files(udev);
	वापस retval;
पूर्ण

व्योम usb_हटाओ_sysfs_dev_files(काष्ठा usb_device *udev)
अणु
	काष्ठा device *dev = &udev->dev;

	अगर (is_root_hub(udev))
		हटाओ_शेष_authorized_attributes(dev);

	हटाओ_घातer_attributes(dev);
	हटाओ_persist_attributes(dev);
	device_हटाओ_bin_file(dev, &dev_bin_attr_descriptors);
पूर्ण

/* Interface Association Descriptor fields */
#घोषणा usb_पूर्णांकf_assoc_attr(field, क्रमmat_string)			\
अटल sमाप_प्रकार								\
iad_##field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,	\
		अक्षर *buf)						\
अणु									\
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);		\
									\
	वापस प्र_लिखो(buf, क्रमmat_string,				\
			पूर्णांकf->पूर्णांकf_assoc->field); 			\
पूर्ण									\
अटल DEVICE_ATTR_RO(iad_##field)

usb_पूर्णांकf_assoc_attr(bFirstInterface, "%02x\n");
usb_पूर्णांकf_assoc_attr(bInterfaceCount, "%02d\n");
usb_पूर्णांकf_assoc_attr(bFunctionClass, "%02x\n");
usb_पूर्णांकf_assoc_attr(bFunctionSubClass, "%02x\n");
usb_पूर्णांकf_assoc_attr(bFunctionProtocol, "%02x\n");

/* Interface fields */
#घोषणा usb_पूर्णांकf_attr(field, क्रमmat_string)				\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr,		\
		अक्षर *buf)						\
अणु									\
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);		\
									\
	वापस प्र_लिखो(buf, क्रमmat_string,				\
			पूर्णांकf->cur_altsetting->desc.field); 		\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

usb_पूर्णांकf_attr(bInterfaceNumber, "%02x\n");
usb_पूर्णांकf_attr(bAlternateSetting, "%2d\n");
usb_पूर्णांकf_attr(bNumEndpoपूर्णांकs, "%02x\n");
usb_पूर्णांकf_attr(bInterfaceClass, "%02x\n");
usb_पूर्णांकf_attr(bInterfaceSubClass, "%02x\n");
usb_पूर्णांकf_attr(bInterfaceProtocol, "%02x\n");

अटल sमाप_प्रकार पूर्णांकerface_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	अक्षर *string;

	पूर्णांकf = to_usb_पूर्णांकerface(dev);
	string = READ_ONCE(पूर्णांकf->cur_altsetting->string);
	अगर (!string)
		वापस 0;
	वापस प्र_लिखो(buf, "%s\n", string);
पूर्ण
अटल DEVICE_ATTR_RO(पूर्णांकerface);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_device *udev;
	काष्ठा usb_host_पूर्णांकerface *alt;

	पूर्णांकf = to_usb_पूर्णांकerface(dev);
	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	alt = READ_ONCE(पूर्णांकf->cur_altsetting);

	वापस प्र_लिखो(buf, "usb:v%04Xp%04Xd%04Xdc%02Xdsc%02Xdp%02X"
			"ic%02Xisc%02Xip%02Xin%02X\n",
			le16_to_cpu(udev->descriptor.idVenकरोr),
			le16_to_cpu(udev->descriptor.idProduct),
			le16_to_cpu(udev->descriptor.bcdDevice),
			udev->descriptor.bDeviceClass,
			udev->descriptor.bDeviceSubClass,
			udev->descriptor.bDeviceProtocol,
			alt->desc.bInterfaceClass,
			alt->desc.bInterfaceSubClass,
			alt->desc.bInterfaceProtocol,
			alt->desc.bInterfaceNumber);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार supports_स्वतःsuspend_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक s;

	s = device_lock_पूर्णांकerruptible(dev);
	अगर (s < 0)
		वापस -EINTR;
	/* Devices will be स्वतःsuspended even when an पूर्णांकerface isn't claimed */
	s = (!dev->driver || to_usb_driver(dev->driver)->supports_स्वतःsuspend);
	device_unlock(dev);

	वापस प्र_लिखो(buf, "%u\n", s);
पूर्ण
अटल DEVICE_ATTR_RO(supports_स्वतःsuspend);

/*
 * पूर्णांकerface_authorized_show - show authorization status of an USB पूर्णांकerface
 * 1 is authorized, 0 is deauthorized
 */
अटल sमाप_प्रकार पूर्णांकerface_authorized_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);

	वापस प्र_लिखो(buf, "%u\n", पूर्णांकf->authorized);
पूर्ण

/*
 * पूर्णांकerface_authorized_store - authorize or deauthorize an USB पूर्णांकerface
 */
अटल sमाप_प्रकार पूर्णांकerface_authorized_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	bool val;

	अगर (strtobool(buf, &val) != 0)
		वापस -EINVAL;

	अगर (val)
		usb_authorize_पूर्णांकerface(पूर्णांकf);
	अन्यथा
		usb_deauthorize_पूर्णांकerface(पूर्णांकf);

	वापस count;
पूर्ण
अटल काष्ठा device_attribute dev_attr_पूर्णांकerface_authorized =
		__ATTR(authorized, S_IRUGO | S_IWUSR,
		पूर्णांकerface_authorized_show, पूर्णांकerface_authorized_store);

अटल काष्ठा attribute *पूर्णांकf_attrs[] = अणु
	&dev_attr_bInterfaceNumber.attr,
	&dev_attr_bAlternateSetting.attr,
	&dev_attr_bNumEndpoपूर्णांकs.attr,
	&dev_attr_bInterfaceClass.attr,
	&dev_attr_bInterfaceSubClass.attr,
	&dev_attr_bInterfaceProtocol.attr,
	&dev_attr_modalias.attr,
	&dev_attr_supports_स्वतःsuspend.attr,
	&dev_attr_पूर्णांकerface_authorized.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group पूर्णांकf_attr_grp = अणु
	.attrs = पूर्णांकf_attrs,
पूर्ण;

अटल काष्ठा attribute *पूर्णांकf_assoc_attrs[] = अणु
	&dev_attr_iad_bFirstInterface.attr,
	&dev_attr_iad_bInterfaceCount.attr,
	&dev_attr_iad_bFunctionClass.attr,
	&dev_attr_iad_bFunctionSubClass.attr,
	&dev_attr_iad_bFunctionProtocol.attr,
	शून्य,
पूर्ण;

अटल umode_t पूर्णांकf_assoc_attrs_are_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);

	अगर (पूर्णांकf->पूर्णांकf_assoc == शून्य)
		वापस 0;
	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group पूर्णांकf_assoc_attr_grp = अणु
	.attrs =	पूर्णांकf_assoc_attrs,
	.is_visible =	पूर्णांकf_assoc_attrs_are_visible,
पूर्ण;

स्थिर काष्ठा attribute_group *usb_पूर्णांकerface_groups[] = अणु
	&पूर्णांकf_attr_grp,
	&पूर्णांकf_assoc_attr_grp,
	शून्य
पूर्ण;

व्योम usb_create_sysfs_पूर्णांकf_files(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकf->sysfs_files_created || पूर्णांकf->unरेजिस्टरing)
		वापस;

	अगर (!alt->string && !(udev->quirks & USB_QUIRK_CONFIG_INTF_STRINGS))
		alt->string = usb_cache_string(udev, alt->desc.iInterface);
	अगर (alt->string && device_create_file(&पूर्णांकf->dev, &dev_attr_पूर्णांकerface)) अणु
		/* This is not a serious error */
		dev_dbg(&पूर्णांकf->dev, "interface string descriptor file not created\n");
	पूर्ण
	पूर्णांकf->sysfs_files_created = 1;
पूर्ण

व्योम usb_हटाओ_sysfs_पूर्णांकf_files(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अगर (!पूर्णांकf->sysfs_files_created)
		वापस;

	device_हटाओ_file(&पूर्णांकf->dev, &dev_attr_पूर्णांकerface);
	पूर्णांकf->sysfs_files_created = 0;
पूर्ण
