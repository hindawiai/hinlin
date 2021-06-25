<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Management Engine (FME)
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fpga-dfl.h>

#समावेश "dfl.h"
#समावेश "dfl-fme.h"

अटल sमाप_प्रकार ports_num_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_CAP);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 (अचिन्हित पूर्णांक)FIELD_GET(FME_CAP_NUM_PORTS, v));
पूर्ण
अटल DEVICE_ATTR_RO(ports_num);

/*
 * Bitstream (अटल FPGA region) identअगरier number. It contains the
 * detailed version and other inक्रमmation of this अटल FPGA region.
 */
अटल sमाप_प्रकार bitstream_id_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_BITSTREAM_ID);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)v);
पूर्ण
अटल DEVICE_ATTR_RO(bitstream_id);

/*
 * Bitstream (अटल FPGA region) meta data. It contains the synthesis
 * date, seed and other inक्रमmation of this अटल FPGA region.
 */
अटल sमाप_प्रकार bitstream_metadata_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_BITSTREAM_MD);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)v);
पूर्ण
अटल DEVICE_ATTR_RO(bitstream_metadata);

अटल sमाप_प्रकार cache_size_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_CAP);

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)FIELD_GET(FME_CAP_CACHE_SIZE, v));
पूर्ण
अटल DEVICE_ATTR_RO(cache_size);

अटल sमाप_प्रकार fabric_version_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_CAP);

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)FIELD_GET(FME_CAP_FABRIC_VERID, v));
पूर्ण
अटल DEVICE_ATTR_RO(fabric_version);

अटल sमाप_प्रकार socket_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_CAP);

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)FIELD_GET(FME_CAP_SOCKET_ID, v));
पूर्ण
अटल DEVICE_ATTR_RO(socket_id);

अटल काष्ठा attribute *fme_hdr_attrs[] = अणु
	&dev_attr_ports_num.attr,
	&dev_attr_bitstream_id.attr,
	&dev_attr_bitstream_metadata.attr,
	&dev_attr_cache_size.attr,
	&dev_attr_fabric_version.attr,
	&dev_attr_socket_id.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_hdr_group = अणु
	.attrs = fme_hdr_attrs,
पूर्ण;

अटल दीर्घ fme_hdr_ioctl_release_port(काष्ठा dfl_feature_platक्रमm_data *pdata,
				       अचिन्हित दीर्घ arg)
अणु
	काष्ठा dfl_fpga_cdev *cdev = pdata->dfl_cdev;
	पूर्णांक port_id;

	अगर (get_user(port_id, (पूर्णांक __user *)arg))
		वापस -EFAULT;

	वापस dfl_fpga_cdev_release_port(cdev, port_id);
पूर्ण

अटल दीर्घ fme_hdr_ioctl_assign_port(काष्ठा dfl_feature_platक्रमm_data *pdata,
				      अचिन्हित दीर्घ arg)
अणु
	काष्ठा dfl_fpga_cdev *cdev = pdata->dfl_cdev;
	पूर्णांक port_id;

	अगर (get_user(port_id, (पूर्णांक __user *)arg))
		वापस -EFAULT;

	वापस dfl_fpga_cdev_assign_port(cdev, port_id);
पूर्ण

अटल दीर्घ fme_hdr_ioctl(काष्ठा platक्रमm_device *pdev,
			  काष्ठा dfl_feature *feature,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	चयन (cmd) अणु
	हाल DFL_FPGA_FME_PORT_RELEASE:
		वापस fme_hdr_ioctl_release_port(pdata, arg);
	हाल DFL_FPGA_FME_PORT_ASSIGN:
		वापस fme_hdr_ioctl_assign_port(pdata, arg);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id fme_hdr_id_table[] = अणु
	अणु.id = FME_FEATURE_ID_HEADER,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops fme_hdr_ops = अणु
	.ioctl = fme_hdr_ioctl,
पूर्ण;

#घोषणा FME_THERM_THRESHOLD	0x8
#घोषणा TEMP_THRESHOLD1		GENMASK_ULL(6, 0)
#घोषणा TEMP_THRESHOLD1_EN	BIT_ULL(7)
#घोषणा TEMP_THRESHOLD2		GENMASK_ULL(14, 8)
#घोषणा TEMP_THRESHOLD2_EN	BIT_ULL(15)
#घोषणा TRIP_THRESHOLD		GENMASK_ULL(30, 24)
#घोषणा TEMP_THRESHOLD1_STATUS	BIT_ULL(32)		/* threshold1 reached */
#घोषणा TEMP_THRESHOLD2_STATUS	BIT_ULL(33)		/* threshold2 reached */
/* threshold1 policy: 0 - AP2 (90% throttle) / 1 - AP1 (50% throttle) */
#घोषणा TEMP_THRESHOLD1_POLICY	BIT_ULL(44)

#घोषणा FME_THERM_RDSENSOR_FMT1	0x10
#घोषणा FPGA_TEMPERATURE	GENMASK_ULL(6, 0)

#घोषणा FME_THERM_CAP		0x20
#घोषणा THERM_NO_THROTTLE	BIT_ULL(0)

#घोषणा MD_PRE_DEG

अटल bool fme_thermal_throttle_support(व्योम __iomem *base)
अणु
	u64 v = पढ़ोq(base + FME_THERM_CAP);

	वापस FIELD_GET(THERM_NO_THROTTLE, v) ? false : true;
पूर्ण

अटल umode_t thermal_hwmon_attrs_visible(स्थिर व्योम *drvdata,
					   क्रमागत hwmon_sensor_types type,
					   u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा dfl_feature *feature = drvdata;

	/* temperature is always supported, and check hardware cap क्रम others */
	अगर (attr == hwmon_temp_input)
		वापस 0444;

	वापस fme_thermal_throttle_support(feature->ioaddr) ? 0444 : 0;
पूर्ण

अटल पूर्णांक thermal_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	u64 v;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		v = पढ़ोq(feature->ioaddr + FME_THERM_RDSENSOR_FMT1);
		*val = (दीर्घ)(FIELD_GET(FPGA_TEMPERATURE, v) * 1000);
		अवरोध;
	हाल hwmon_temp_max:
		v = पढ़ोq(feature->ioaddr + FME_THERM_THRESHOLD);
		*val = (दीर्घ)(FIELD_GET(TEMP_THRESHOLD1, v) * 1000);
		अवरोध;
	हाल hwmon_temp_crit:
		v = पढ़ोq(feature->ioaddr + FME_THERM_THRESHOLD);
		*val = (दीर्घ)(FIELD_GET(TEMP_THRESHOLD2, v) * 1000);
		अवरोध;
	हाल hwmon_temp_emergency:
		v = पढ़ोq(feature->ioaddr + FME_THERM_THRESHOLD);
		*val = (दीर्घ)(FIELD_GET(TRIP_THRESHOLD, v) * 1000);
		अवरोध;
	हाल hwmon_temp_max_alarm:
		v = पढ़ोq(feature->ioaddr + FME_THERM_THRESHOLD);
		*val = (दीर्घ)FIELD_GET(TEMP_THRESHOLD1_STATUS, v);
		अवरोध;
	हाल hwmon_temp_crit_alarm:
		v = पढ़ोq(feature->ioaddr + FME_THERM_THRESHOLD);
		*val = (दीर्घ)FIELD_GET(TEMP_THRESHOLD2_STATUS, v);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops thermal_hwmon_ops = अणु
	.is_visible = thermal_hwmon_attrs_visible,
	.पढ़ो = thermal_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *thermal_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT | HWMON_T_EMERGENCY |
				 HWMON_T_MAX   | HWMON_T_MAX_ALARM |
				 HWMON_T_CRIT  | HWMON_T_CRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info thermal_hwmon_chip_info = अणु
	.ops = &thermal_hwmon_ops,
	.info = thermal_hwmon_info,
पूर्ण;

अटल sमाप_प्रकार temp1_max_policy_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	u64 v;

	v = पढ़ोq(feature->ioaddr + FME_THERM_THRESHOLD);

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)FIELD_GET(TEMP_THRESHOLD1_POLICY, v));
पूर्ण

अटल DEVICE_ATTR_RO(temp1_max_policy);

अटल काष्ठा attribute *thermal_extra_attrs[] = अणु
	&dev_attr_temp1_max_policy.attr,
	शून्य,
पूर्ण;

अटल umode_t thermal_extra_attrs_visible(काष्ठा kobject *kobj,
					   काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);

	वापस fme_thermal_throttle_support(feature->ioaddr) ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group thermal_extra_group = अणु
	.attrs		= thermal_extra_attrs,
	.is_visible	= thermal_extra_attrs_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(thermal_extra);

अटल पूर्णांक fme_thermal_mgmt_init(काष्ठा platक्रमm_device *pdev,
				 काष्ठा dfl_feature *feature)
अणु
	काष्ठा device *hwmon;

	/*
	 * create hwmon to allow userspace monitoring temperature and other
	 * threshold inक्रमmation.
	 *
	 * temp1_input      -> FPGA device temperature
	 * temp1_max        -> hardware threshold 1 -> 50% or 90% throttling
	 * temp1_crit       -> hardware threshold 2 -> 100% throttling
	 * temp1_emergency  -> hardware trip_threshold to shutकरोwn FPGA
	 * temp1_max_alarm  -> hardware threshold 1 alarm
	 * temp1_crit_alarm -> hardware threshold 2 alarm
	 *
	 * create device specअगरic sysfs पूर्णांकerfaces, e.g. पढ़ो temp1_max_policy
	 * to understand the actual hardware throttling action (50% vs 90%).
	 *
	 * If hardware करोesn't support स्वतःmatic throttling per thresholds,
	 * then all above sysfs पूर्णांकerfaces are not visible except temp1_input
	 * क्रम temperature.
	 */
	hwmon = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
						     "dfl_fme_thermal", feature,
						     &thermal_hwmon_chip_info,
						     thermal_extra_groups);
	अगर (IS_ERR(hwmon)) अणु
		dev_err(&pdev->dev, "Fail to register thermal hwmon\n");
		वापस PTR_ERR(hwmon);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id fme_thermal_mgmt_id_table[] = अणु
	अणु.id = FME_FEATURE_ID_THERMAL_MGMT,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops fme_thermal_mgmt_ops = अणु
	.init = fme_thermal_mgmt_init,
पूर्ण;

#घोषणा FME_PWR_STATUS		0x8
#घोषणा FME_LATENCY_TOLERANCE	BIT_ULL(18)
#घोषणा PWR_CONSUMED		GENMASK_ULL(17, 0)

#घोषणा FME_PWR_THRESHOLD	0x10
#घोषणा PWR_THRESHOLD1		GENMASK_ULL(6, 0)	/* in Watts */
#घोषणा PWR_THRESHOLD2		GENMASK_ULL(14, 8)	/* in Watts */
#घोषणा PWR_THRESHOLD_MAX	0x7f			/* in Watts */
#घोषणा PWR_THRESHOLD1_STATUS	BIT_ULL(16)
#घोषणा PWR_THRESHOLD2_STATUS	BIT_ULL(17)

#घोषणा FME_PWR_XEON_LIMIT	0x18
#घोषणा XEON_PWR_LIMIT		GENMASK_ULL(14, 0)	/* in 0.1 Watts */
#घोषणा XEON_PWR_EN		BIT_ULL(15)
#घोषणा FME_PWR_FPGA_LIMIT	0x20
#घोषणा FPGA_PWR_LIMIT		GENMASK_ULL(14, 0)	/* in 0.1 Watts */
#घोषणा FPGA_PWR_EN		BIT_ULL(15)

अटल पूर्णांक घातer_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	u64 v;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		v = पढ़ोq(feature->ioaddr + FME_PWR_STATUS);
		*val = (दीर्घ)(FIELD_GET(PWR_CONSUMED, v) * 1000000);
		अवरोध;
	हाल hwmon_घातer_max:
		v = पढ़ोq(feature->ioaddr + FME_PWR_THRESHOLD);
		*val = (दीर्घ)(FIELD_GET(PWR_THRESHOLD1, v) * 1000000);
		अवरोध;
	हाल hwmon_घातer_crit:
		v = पढ़ोq(feature->ioaddr + FME_PWR_THRESHOLD);
		*val = (दीर्घ)(FIELD_GET(PWR_THRESHOLD2, v) * 1000000);
		अवरोध;
	हाल hwmon_घातer_max_alarm:
		v = पढ़ोq(feature->ioaddr + FME_PWR_THRESHOLD);
		*val = (दीर्घ)FIELD_GET(PWR_THRESHOLD1_STATUS, v);
		अवरोध;
	हाल hwmon_घातer_crit_alarm:
		v = पढ़ोq(feature->ioaddr + FME_PWR_THRESHOLD);
		*val = (दीर्घ)FIELD_GET(PWR_THRESHOLD2_STATUS, v);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक घातer_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev->parent);
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	u64 v;

	val = clamp_val(val / 1000000, 0, PWR_THRESHOLD_MAX);

	mutex_lock(&pdata->lock);

	चयन (attr) अणु
	हाल hwmon_घातer_max:
		v = पढ़ोq(feature->ioaddr + FME_PWR_THRESHOLD);
		v &= ~PWR_THRESHOLD1;
		v |= FIELD_PREP(PWR_THRESHOLD1, val);
		ग_लिखोq(v, feature->ioaddr + FME_PWR_THRESHOLD);
		अवरोध;
	हाल hwmon_घातer_crit:
		v = पढ़ोq(feature->ioaddr + FME_PWR_THRESHOLD);
		v &= ~PWR_THRESHOLD2;
		v |= FIELD_PREP(PWR_THRESHOLD2, val);
		ग_लिखोq(v, feature->ioaddr + FME_PWR_THRESHOLD);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&pdata->lock);

	वापस ret;
पूर्ण

अटल umode_t घातer_hwmon_attrs_visible(स्थिर व्योम *drvdata,
					 क्रमागत hwmon_sensor_types type,
					 u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_घातer_input:
	हाल hwmon_घातer_max_alarm:
	हाल hwmon_घातer_crit_alarm:
		वापस 0444;
	हाल hwmon_घातer_max:
	हाल hwmon_घातer_crit:
		वापस 0644;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops घातer_hwmon_ops = अणु
	.is_visible = घातer_hwmon_attrs_visible,
	.पढ़ो = घातer_hwmon_पढ़ो,
	.ग_लिखो = घातer_hwmon_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *घातer_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(घातer, HWMON_P_INPUT |
				  HWMON_P_MAX   | HWMON_P_MAX_ALARM |
				  HWMON_P_CRIT  | HWMON_P_CRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info घातer_hwmon_chip_info = अणु
	.ops = &घातer_hwmon_ops,
	.info = घातer_hwmon_info,
पूर्ण;

अटल sमाप_प्रकार घातer1_xeon_limit_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	u16 xeon_limit = 0;
	u64 v;

	v = पढ़ोq(feature->ioaddr + FME_PWR_XEON_LIMIT);

	अगर (FIELD_GET(XEON_PWR_EN, v))
		xeon_limit = FIELD_GET(XEON_PWR_LIMIT, v);

	वापस प्र_लिखो(buf, "%u\n", xeon_limit * 100000);
पूर्ण

अटल sमाप_प्रकार घातer1_fpga_limit_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	u16 fpga_limit = 0;
	u64 v;

	v = पढ़ोq(feature->ioaddr + FME_PWR_FPGA_LIMIT);

	अगर (FIELD_GET(FPGA_PWR_EN, v))
		fpga_limit = FIELD_GET(FPGA_PWR_LIMIT, v);

	वापस प्र_लिखो(buf, "%u\n", fpga_limit * 100000);
पूर्ण

अटल sमाप_प्रकार घातer1_ltr_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature *feature = dev_get_drvdata(dev);
	u64 v;

	v = पढ़ोq(feature->ioaddr + FME_PWR_STATUS);

	वापस प्र_लिखो(buf, "%u\n",
		       (अचिन्हित पूर्णांक)FIELD_GET(FME_LATENCY_TOLERANCE, v));
पूर्ण

अटल DEVICE_ATTR_RO(घातer1_xeon_limit);
अटल DEVICE_ATTR_RO(घातer1_fpga_limit);
अटल DEVICE_ATTR_RO(घातer1_ltr);

अटल काष्ठा attribute *घातer_extra_attrs[] = अणु
	&dev_attr_घातer1_xeon_limit.attr,
	&dev_attr_घातer1_fpga_limit.attr,
	&dev_attr_घातer1_ltr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(घातer_extra);

अटल पूर्णांक fme_घातer_mgmt_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dfl_feature *feature)
अणु
	काष्ठा device *hwmon;

	hwmon = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev,
						     "dfl_fme_power", feature,
						     &घातer_hwmon_chip_info,
						     घातer_extra_groups);
	अगर (IS_ERR(hwmon)) अणु
		dev_err(&pdev->dev, "Fail to register power hwmon\n");
		वापस PTR_ERR(hwmon);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id fme_घातer_mgmt_id_table[] = अणु
	अणु.id = FME_FEATURE_ID_POWER_MGMT,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops fme_घातer_mgmt_ops = अणु
	.init = fme_घातer_mgmt_init,
पूर्ण;

अटल काष्ठा dfl_feature_driver fme_feature_drvs[] = अणु
	अणु
		.id_table = fme_hdr_id_table,
		.ops = &fme_hdr_ops,
	पूर्ण,
	अणु
		.id_table = fme_pr_mgmt_id_table,
		.ops = &fme_pr_mgmt_ops,
	पूर्ण,
	अणु
		.id_table = fme_global_err_id_table,
		.ops = &fme_global_err_ops,
	पूर्ण,
	अणु
		.id_table = fme_thermal_mgmt_id_table,
		.ops = &fme_thermal_mgmt_ops,
	पूर्ण,
	अणु
		.id_table = fme_घातer_mgmt_id_table,
		.ops = &fme_घातer_mgmt_ops,
	पूर्ण,
	अणु
		.id_table = fme_perf_id_table,
		.ops = &fme_perf_ops,
	पूर्ण,
	अणु
		.ops = शून्य,
	पूर्ण,
पूर्ण;

अटल दीर्घ fme_ioctl_check_extension(काष्ठा dfl_feature_platक्रमm_data *pdata,
				      अचिन्हित दीर्घ arg)
अणु
	/* No extension support क्रम now */
	वापस 0;
पूर्ण

अटल पूर्णांक fme_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा platक्रमm_device *fdev = dfl_fpga_inode_to_feature_dev(inode);
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&fdev->dev);
	पूर्णांक ret;

	अगर (WARN_ON(!pdata))
		वापस -ENODEV;

	mutex_lock(&pdata->lock);
	ret = dfl_feature_dev_use_begin(pdata, filp->f_flags & O_EXCL);
	अगर (!ret) अणु
		dev_dbg(&fdev->dev, "Device File Opened %d Times\n",
			dfl_feature_dev_use_count(pdata));
		filp->निजी_data = pdata;
	पूर्ण
	mutex_unlock(&pdata->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fme_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = filp->निजी_data;
	काष्ठा platक्रमm_device *pdev = pdata->dev;
	काष्ठा dfl_feature *feature;

	dev_dbg(&pdev->dev, "Device File Release\n");

	mutex_lock(&pdata->lock);
	dfl_feature_dev_use_end(pdata);

	अगर (!dfl_feature_dev_use_count(pdata))
		dfl_fpga_dev_क्रम_each_feature(pdata, feature)
			dfl_fpga_set_irq_triggers(feature, 0,
						  feature->nr_irqs, शून्य);
	mutex_unlock(&pdata->lock);

	वापस 0;
पूर्ण

अटल दीर्घ fme_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = filp->निजी_data;
	काष्ठा platक्रमm_device *pdev = pdata->dev;
	काष्ठा dfl_feature *f;
	दीर्घ ret;

	dev_dbg(&pdev->dev, "%s cmd 0x%x\n", __func__, cmd);

	चयन (cmd) अणु
	हाल DFL_FPGA_GET_API_VERSION:
		वापस DFL_FPGA_API_VERSION;
	हाल DFL_FPGA_CHECK_EXTENSION:
		वापस fme_ioctl_check_extension(pdata, arg);
	शेष:
		/*
		 * Let sub-feature's ioctl function to handle the cmd.
		 * Sub-feature's ioctl वापसs -ENODEV when cmd is not
		 * handled in this sub feature, and वापसs 0 or other
		 * error code अगर cmd is handled.
		 */
		dfl_fpga_dev_क्रम_each_feature(pdata, f) अणु
			अगर (f->ops && f->ops->ioctl) अणु
				ret = f->ops->ioctl(pdev, f, cmd, arg);
				अगर (ret != -ENODEV)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fme_dev_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_fme *fme;

	fme = devm_kzalloc(&pdev->dev, माप(*fme), GFP_KERNEL);
	अगर (!fme)
		वापस -ENOMEM;

	fme->pdata = pdata;

	mutex_lock(&pdata->lock);
	dfl_fpga_pdata_set_निजी(pdata, fme);
	mutex_unlock(&pdata->lock);

	वापस 0;
पूर्ण

अटल व्योम fme_dev_destroy(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	mutex_lock(&pdata->lock);
	dfl_fpga_pdata_set_निजी(pdata, शून्य);
	mutex_unlock(&pdata->lock);
पूर्ण

अटल स्थिर काष्ठा file_operations fme_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fme_खोलो,
	.release	= fme_release,
	.unlocked_ioctl = fme_ioctl,
पूर्ण;

अटल पूर्णांक fme_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = fme_dev_init(pdev);
	अगर (ret)
		जाओ निकास;

	ret = dfl_fpga_dev_feature_init(pdev, fme_feature_drvs);
	अगर (ret)
		जाओ dev_destroy;

	ret = dfl_fpga_dev_ops_रेजिस्टर(pdev, &fme_fops, THIS_MODULE);
	अगर (ret)
		जाओ feature_uinit;

	वापस 0;

feature_uinit:
	dfl_fpga_dev_feature_uinit(pdev);
dev_destroy:
	fme_dev_destroy(pdev);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक fme_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dfl_fpga_dev_ops_unरेजिस्टर(pdev);
	dfl_fpga_dev_feature_uinit(pdev);
	fme_dev_destroy(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group *fme_dev_groups[] = अणु
	&fme_hdr_group,
	&fme_global_err_group,
	शून्य
पूर्ण;

अटल काष्ठा platक्रमm_driver fme_driver = अणु
	.driver	= अणु
		.name       = DFL_FPGA_FEATURE_DEV_FME,
		.dev_groups = fme_dev_groups,
	पूर्ण,
	.probe   = fme_probe,
	.हटाओ  = fme_हटाओ,
पूर्ण;

module_platक्रमm_driver(fme_driver);

MODULE_DESCRIPTION("FPGA Management Engine driver");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dfl-fme");
