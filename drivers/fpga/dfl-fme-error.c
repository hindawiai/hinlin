<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Management Engine Error Management
 *
 * Copyright 2019 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Mitchel, Henry <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/fpga-dfl.h>
#समावेश <linux/uaccess.h>

#समावेश "dfl.h"
#समावेश "dfl-fme.h"

#घोषणा FME_ERROR_MASK		0x8
#घोषणा FME_ERROR		0x10
#घोषणा MBP_ERROR		BIT_ULL(6)
#घोषणा PCIE0_ERROR_MASK	0x18
#घोषणा PCIE0_ERROR		0x20
#घोषणा PCIE1_ERROR_MASK	0x28
#घोषणा PCIE1_ERROR		0x30
#घोषणा FME_FIRST_ERROR		0x38
#घोषणा FME_NEXT_ERROR		0x40
#घोषणा RAS_NONFAT_ERROR_MASK	0x48
#घोषणा RAS_NONFAT_ERROR	0x50
#घोषणा RAS_CATFAT_ERROR_MASK	0x58
#घोषणा RAS_CATFAT_ERROR	0x60
#घोषणा RAS_ERROR_INJECT	0x68
#घोषणा INJECT_ERROR_MASK	GENMASK_ULL(2, 0)

#घोषणा ERROR_MASK		GENMASK_ULL(63, 0)

अटल sमाप_प्रकार pcie0_errors_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 value;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	value = पढ़ोq(base + PCIE0_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)value);
पूर्ण

अटल sमाप_प्रकार pcie0_errors_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	पूर्णांक ret = 0;
	u64 v, val;

	अगर (kstrtou64(buf, 0, &val))
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	ग_लिखोq(GENMASK_ULL(63, 0), base + PCIE0_ERROR_MASK);

	v = पढ़ोq(base + PCIE0_ERROR);
	अगर (val == v)
		ग_लिखोq(v, base + PCIE0_ERROR);
	अन्यथा
		ret = -EINVAL;

	ग_लिखोq(0ULL, base + PCIE0_ERROR_MASK);
	mutex_unlock(&pdata->lock);
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(pcie0_errors);

अटल sमाप_प्रकार pcie1_errors_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 value;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	value = पढ़ोq(base + PCIE1_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)value);
पूर्ण

अटल sमाप_प्रकार pcie1_errors_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	पूर्णांक ret = 0;
	u64 v, val;

	अगर (kstrtou64(buf, 0, &val))
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	ग_लिखोq(GENMASK_ULL(63, 0), base + PCIE1_ERROR_MASK);

	v = पढ़ोq(base + PCIE1_ERROR);
	अगर (val == v)
		ग_लिखोq(v, base + PCIE1_ERROR);
	अन्यथा
		ret = -EINVAL;

	ग_लिखोq(0ULL, base + PCIE1_ERROR_MASK);
	mutex_unlock(&pdata->lock);
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(pcie1_errors);

अटल sमाप_प्रकार nonfatal_errors_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	वापस प्र_लिखो(buf, "0x%llx\n",
		       (अचिन्हित दीर्घ दीर्घ)पढ़ोq(base + RAS_NONFAT_ERROR));
पूर्ण
अटल DEVICE_ATTR_RO(nonfatal_errors);

अटल sमाप_प्रकार catfatal_errors_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	वापस प्र_लिखो(buf, "0x%llx\n",
		       (अचिन्हित दीर्घ दीर्घ)पढ़ोq(base + RAS_CATFAT_ERROR));
पूर्ण
अटल DEVICE_ATTR_RO(catfatal_errors);

अटल sमाप_प्रकार inject_errors_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + RAS_ERROR_INJECT);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n",
		       (अचिन्हित दीर्घ दीर्घ)FIELD_GET(INJECT_ERROR_MASK, v));
पूर्ण

अटल sमाप_प्रकार inject_errors_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u8 inject_error;
	u64 v;

	अगर (kstrtou8(buf, 0, &inject_error))
		वापस -EINVAL;

	अगर (inject_error & ~INJECT_ERROR_MASK)
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + RAS_ERROR_INJECT);
	v &= ~INJECT_ERROR_MASK;
	v |= FIELD_PREP(INJECT_ERROR_MASK, inject_error);
	ग_लिखोq(v, base + RAS_ERROR_INJECT);
	mutex_unlock(&pdata->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(inject_errors);

अटल sमाप_प्रकार fme_errors_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 value;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	value = पढ़ोq(base + FME_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)value);
पूर्ण

अटल sमाप_प्रकार fme_errors_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 v, val;
	पूर्णांक ret = 0;

	अगर (kstrtou64(buf, 0, &val))
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	ग_लिखोq(GENMASK_ULL(63, 0), base + FME_ERROR_MASK);

	v = पढ़ोq(base + FME_ERROR);
	अगर (val == v)
		ग_लिखोq(v, base + FME_ERROR);
	अन्यथा
		ret = -EINVAL;

	/* Workaround: disable MBP_ERROR अगर feature revision is 0 */
	ग_लिखोq(dfl_feature_revision(base) ? 0ULL : MBP_ERROR,
	       base + FME_ERROR_MASK);
	mutex_unlock(&pdata->lock);
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(fme_errors);

अटल sमाप_प्रकार first_error_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 value;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	value = पढ़ोq(base + FME_FIRST_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)value);
पूर्ण
अटल DEVICE_ATTR_RO(first_error);

अटल sमाप_प्रकार next_error_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 value;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);
	value = पढ़ोq(base + FME_NEXT_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)value);
पूर्ण
अटल DEVICE_ATTR_RO(next_error);

अटल काष्ठा attribute *fme_global_err_attrs[] = अणु
	&dev_attr_pcie0_errors.attr,
	&dev_attr_pcie1_errors.attr,
	&dev_attr_nonfatal_errors.attr,
	&dev_attr_catfatal_errors.attr,
	&dev_attr_inject_errors.attr,
	&dev_attr_fme_errors.attr,
	&dev_attr_first_error.attr,
	&dev_attr_next_error.attr,
	शून्य,
पूर्ण;

अटल umode_t fme_global_err_attrs_visible(काष्ठा kobject *kobj,
					    काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entries are visible only अगर related निजी feature is
	 * क्रमागतerated.
	 */
	अगर (!dfl_get_feature_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR))
		वापस 0;

	वापस attr->mode;
पूर्ण

स्थिर काष्ठा attribute_group fme_global_err_group = अणु
	.name       = "errors",
	.attrs      = fme_global_err_attrs,
	.is_visible = fme_global_err_attrs_visible,
पूर्ण;

अटल व्योम fme_err_mask(काष्ठा device *dev, bool mask)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR);

	mutex_lock(&pdata->lock);

	/* Workaround: keep MBP_ERROR always masked अगर revision is 0 */
	अगर (dfl_feature_revision(base))
		ग_लिखोq(mask ? ERROR_MASK : 0, base + FME_ERROR_MASK);
	अन्यथा
		ग_लिखोq(mask ? ERROR_MASK : MBP_ERROR, base + FME_ERROR_MASK);

	ग_लिखोq(mask ? ERROR_MASK : 0, base + PCIE0_ERROR_MASK);
	ग_लिखोq(mask ? ERROR_MASK : 0, base + PCIE1_ERROR_MASK);
	ग_लिखोq(mask ? ERROR_MASK : 0, base + RAS_NONFAT_ERROR_MASK);
	ग_लिखोq(mask ? ERROR_MASK : 0, base + RAS_CATFAT_ERROR_MASK);

	mutex_unlock(&pdata->lock);
पूर्ण

अटल पूर्णांक fme_global_err_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dfl_feature *feature)
अणु
	fme_err_mask(&pdev->dev, false);

	वापस 0;
पूर्ण

अटल व्योम fme_global_err_uinit(काष्ठा platक्रमm_device *pdev,
				 काष्ठा dfl_feature *feature)
अणु
	fme_err_mask(&pdev->dev, true);
पूर्ण

अटल दीर्घ
fme_global_error_ioctl(काष्ठा platक्रमm_device *pdev,
		       काष्ठा dfl_feature *feature,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल DFL_FPGA_FME_ERR_GET_IRQ_NUM:
		वापस dfl_feature_ioctl_get_num_irqs(pdev, feature, arg);
	हाल DFL_FPGA_FME_ERR_SET_IRQ:
		वापस dfl_feature_ioctl_set_irq(pdev, feature, arg);
	शेष:
		dev_dbg(&pdev->dev, "%x cmd not handled", cmd);
		वापस -ENODEV;
	पूर्ण
पूर्ण

स्थिर काष्ठा dfl_feature_id fme_global_err_id_table[] = अणु
	अणु.id = FME_FEATURE_ID_GLOBAL_ERR,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

स्थिर काष्ठा dfl_feature_ops fme_global_err_ops = अणु
	.init = fme_global_err_init,
	.uinit = fme_global_err_uinit,
	.ioctl = fme_global_error_ioctl,
पूर्ण;
