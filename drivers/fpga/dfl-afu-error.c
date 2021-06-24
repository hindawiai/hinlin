<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Accelerated Function Unit (AFU) Error Reporting
 *
 * Copyright 2019 Intel Corporation, Inc.
 *
 * Authors:
 *   Wu Hao <hao.wu@linux.पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Mitchel Henry <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/fpga-dfl.h>
#समावेश <linux/uaccess.h>

#समावेश "dfl-afu.h"

#घोषणा PORT_ERROR_MASK		0x8
#घोषणा PORT_ERROR		0x10
#घोषणा PORT_FIRST_ERROR	0x18
#घोषणा PORT_MALFORMED_REQ0	0x20
#घोषणा PORT_MALFORMED_REQ1	0x28

#घोषणा ERROR_MASK		GENMASK_ULL(63, 0)

/* mask or unmask port errors by the error mask रेजिस्टर. */
अटल व्योम __afu_port_err_mask(काष्ठा device *dev, bool mask)
अणु
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_ERROR);

	ग_लिखोq(mask ? ERROR_MASK : 0, base + PORT_ERROR_MASK);
पूर्ण

अटल व्योम afu_port_err_mask(काष्ठा device *dev, bool mask)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);

	mutex_lock(&pdata->lock);
	__afu_port_err_mask(dev, mask);
	mutex_unlock(&pdata->lock);
पूर्ण

/* clear port errors. */
अटल पूर्णांक afu_port_err_clear(काष्ठा device *dev, u64 err)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	व्योम __iomem *base_err, *base_hdr;
	पूर्णांक enable_ret = 0, ret = -EBUSY;
	u64 v;

	base_err = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_ERROR);
	base_hdr = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);

	/*
	 * clear Port Errors
	 *
	 * - Check क्रम AP6 State
	 * - Halt Port by keeping Port in reset
	 * - Set PORT Error mask to all 1 to mask errors
	 * - Clear all errors
	 * - Set Port mask to all 0 to enable errors
	 * - All errors start capturing new errors
	 * - Enable Port by pulling the port out of reset
	 */

	/* अगर device is still in AP6 घातer state, can not clear any error. */
	v = पढ़ोq(base_hdr + PORT_HDR_STS);
	अगर (FIELD_GET(PORT_STS_PWR_STATE, v) == PORT_STS_PWR_STATE_AP6) अणु
		dev_err(dev, "Could not clear errors, device in AP6 state.\n");
		जाओ करोne;
	पूर्ण

	/* Halt Port by keeping Port in reset */
	ret = __afu_port_disable(pdev);
	अगर (ret)
		जाओ करोne;

	/* Mask all errors */
	__afu_port_err_mask(dev, true);

	/* Clear errors अगर err input matches with current port errors.*/
	v = पढ़ोq(base_err + PORT_ERROR);

	अगर (v == err) अणु
		ग_लिखोq(v, base_err + PORT_ERROR);

		v = पढ़ोq(base_err + PORT_FIRST_ERROR);
		ग_लिखोq(v, base_err + PORT_FIRST_ERROR);
	पूर्ण अन्यथा अणु
		dev_warn(dev, "%s: received 0x%llx, expected 0x%llx\n",
			 __func__, v, err);
		ret = -EINVAL;
	पूर्ण

	/* Clear mask */
	__afu_port_err_mask(dev, false);

	/* Enable the Port by clearing the reset */
	enable_ret = __afu_port_enable(pdev);

करोne:
	mutex_unlock(&pdata->lock);
	वापस enable_ret ? enable_ret : ret;
पूर्ण

अटल sमाप_प्रकार errors_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 error;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_ERROR);

	mutex_lock(&pdata->lock);
	error = पढ़ोq(base + PORT_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)error);
पूर्ण

अटल sमाप_प्रकार errors_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buff, माप_प्रकार count)
अणु
	u64 value;
	पूर्णांक ret;

	अगर (kstrtou64(buff, 0, &value))
		वापस -EINVAL;

	ret = afu_port_err_clear(dev, value);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(errors);

अटल sमाप_प्रकार first_error_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 error;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_ERROR);

	mutex_lock(&pdata->lock);
	error = पढ़ोq(base + PORT_FIRST_ERROR);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)error);
पूर्ण
अटल DEVICE_ATTR_RO(first_error);

अटल sमाप_प्रकार first_malक्रमmed_req_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 req0, req1;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_ERROR);

	mutex_lock(&pdata->lock);
	req0 = पढ़ोq(base + PORT_MALFORMED_REQ0);
	req1 = पढ़ोq(base + PORT_MALFORMED_REQ1);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%016llx%016llx\n",
		       (अचिन्हित दीर्घ दीर्घ)req1, (अचिन्हित दीर्घ दीर्घ)req0);
पूर्ण
अटल DEVICE_ATTR_RO(first_malक्रमmed_req);

अटल काष्ठा attribute *port_err_attrs[] = अणु
	&dev_attr_errors.attr,
	&dev_attr_first_error.attr,
	&dev_attr_first_malक्रमmed_req.attr,
	शून्य,
पूर्ण;

अटल umode_t port_err_attrs_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entries are visible only अगर related निजी feature is
	 * क्रमागतerated.
	 */
	अगर (!dfl_get_feature_by_id(dev, PORT_FEATURE_ID_ERROR))
		वापस 0;

	वापस attr->mode;
पूर्ण

स्थिर काष्ठा attribute_group port_err_group = अणु
	.name       = "errors",
	.attrs      = port_err_attrs,
	.is_visible = port_err_attrs_visible,
पूर्ण;

अटल पूर्णांक port_err_init(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dfl_feature *feature)
अणु
	afu_port_err_mask(&pdev->dev, false);

	वापस 0;
पूर्ण

अटल व्योम port_err_uinit(काष्ठा platक्रमm_device *pdev,
			   काष्ठा dfl_feature *feature)
अणु
	afu_port_err_mask(&pdev->dev, true);
पूर्ण

अटल दीर्घ
port_err_ioctl(काष्ठा platक्रमm_device *pdev, काष्ठा dfl_feature *feature,
	       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल DFL_FPGA_PORT_ERR_GET_IRQ_NUM:
		वापस dfl_feature_ioctl_get_num_irqs(pdev, feature, arg);
	हाल DFL_FPGA_PORT_ERR_SET_IRQ:
		वापस dfl_feature_ioctl_set_irq(pdev, feature, arg);
	शेष:
		dev_dbg(&pdev->dev, "%x cmd not handled", cmd);
		वापस -ENODEV;
	पूर्ण
पूर्ण

स्थिर काष्ठा dfl_feature_id port_err_id_table[] = अणु
	अणु.id = PORT_FEATURE_ID_ERROR,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

स्थिर काष्ठा dfl_feature_ops port_err_ops = अणु
	.init = port_err_init,
	.uinit = port_err_uinit,
	.ioctl = port_err_ioctl,
पूर्ण;
