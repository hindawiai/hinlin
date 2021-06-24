<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <linux/pm_runसमय.स>
#समावेश "core.h"

अटल sमाप_प्रकार fw_version_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dev);
	काष्ठा catpt_fw_version version;
	पूर्णांक ret;

	pm_runसमय_get_sync(cdev->dev);

	ret = catpt_ipc_get_fw_version(cdev, &version);

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	वापस प्र_लिखो(buf, "%d.%d.%d.%d\n", version.type, version.major,
		       version.minor, version.build);
पूर्ण
अटल DEVICE_ATTR_RO(fw_version);

अटल sमाप_प्रकार fw_info_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", cdev->ipc.config.fw_info);
पूर्ण
अटल DEVICE_ATTR_RO(fw_info);

अटल काष्ठा attribute *catpt_attrs[] = अणु
	&dev_attr_fw_version.attr,
	&dev_attr_fw_info.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group catpt_attr_group = अणु
	.attrs = catpt_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *catpt_attr_groups[] = अणु
	&catpt_attr_group,
	शून्य
पूर्ण;
