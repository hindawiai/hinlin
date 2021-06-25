<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PPS sysfs support
 *
 * Copyright (C) 2007-2009   Roकरोlfo Giometti <giometti@linux.it>
 */


#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/pps_kernel.h>

/*
 * Attribute functions
 */

अटल sमाप_प्रकार निश्चित_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	अगर (!(pps->info.mode & PPS_CAPTUREASSERT))
		वापस 0;

	वापस प्र_लिखो(buf, "%lld.%09d#%d\n",
			(दीर्घ दीर्घ) pps->निश्चित_tu.sec, pps->निश्चित_tu.nsec,
			pps->निश्चित_sequence);
पूर्ण
अटल DEVICE_ATTR_RO(निश्चित);

अटल sमाप_प्रकार clear_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	अगर (!(pps->info.mode & PPS_CAPTURECLEAR))
		वापस 0;

	वापस प्र_लिखो(buf, "%lld.%09d#%d\n",
			(दीर्घ दीर्घ) pps->clear_tu.sec, pps->clear_tu.nsec,
			pps->clear_sequence);
पूर्ण
अटल DEVICE_ATTR_RO(clear);

अटल sमाप_प्रकार mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%4x\n", pps->info.mode);
पूर्ण
अटल DEVICE_ATTR_RO(mode);

अटल sमाप_प्रकार echo_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", !!pps->info.echo);
पूर्ण
अटल DEVICE_ATTR_RO(echo);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", pps->info.name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार path_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pps_device *pps = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", pps->info.path);
पूर्ण
अटल DEVICE_ATTR_RO(path);

अटल काष्ठा attribute *pps_attrs[] = अणु
	&dev_attr_निश्चित.attr,
	&dev_attr_clear.attr,
	&dev_attr_mode.attr,
	&dev_attr_echo.attr,
	&dev_attr_name.attr,
	&dev_attr_path.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pps_group = अणु
	.attrs = pps_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *pps_groups[] = अणु
	&pps_group,
	शून्य,
पूर्ण;
