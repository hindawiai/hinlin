<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Accelerated Function Unit (AFU)
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fpga-dfl.h>

#समावेश "dfl-afu.h"

#घोषणा RST_POLL_INVL 10 /* us */
#घोषणा RST_POLL_TIMEOUT 1000 /* us */

/**
 * __afu_port_enable - enable a port by clear reset
 * @pdev: port platक्रमm device.
 *
 * Enable Port by clear the port soft reset bit, which is set by शेष.
 * The AFU is unable to respond to any MMIO access जबतक in reset.
 * __afu_port_enable function should only be used after __afu_port_disable
 * function.
 *
 * The caller needs to hold lock क्रम protection.
 */
पूर्णांक __afu_port_enable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	व्योम __iomem *base;
	u64 v;

	WARN_ON(!pdata->disable_count);

	अगर (--pdata->disable_count != 0)
		वापस 0;

	base = dfl_get_feature_ioaddr_by_id(&pdev->dev, PORT_FEATURE_ID_HEADER);

	/* Clear port soft reset */
	v = पढ़ोq(base + PORT_HDR_CTRL);
	v &= ~PORT_CTRL_SFTRST;
	ग_लिखोq(v, base + PORT_HDR_CTRL);

	/*
	 * HW clears the ack bit to indicate that the port is fully out
	 * of reset.
	 */
	अगर (पढ़ोq_poll_समयout(base + PORT_HDR_CTRL, v,
			       !(v & PORT_CTRL_SFTRST_ACK),
			       RST_POLL_INVL, RST_POLL_TIMEOUT)) अणु
		dev_err(&pdev->dev, "timeout, failure to enable device\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __afu_port_disable - disable a port by hold reset
 * @pdev: port platक्रमm device.
 *
 * Disable Port by setting the port soft reset bit, it माला_दो the port पूर्णांकo reset.
 *
 * The caller needs to hold lock क्रम protection.
 */
पूर्णांक __afu_port_disable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	व्योम __iomem *base;
	u64 v;

	अगर (pdata->disable_count++ != 0)
		वापस 0;

	base = dfl_get_feature_ioaddr_by_id(&pdev->dev, PORT_FEATURE_ID_HEADER);

	/* Set port soft reset */
	v = पढ़ोq(base + PORT_HDR_CTRL);
	v |= PORT_CTRL_SFTRST;
	ग_लिखोq(v, base + PORT_HDR_CTRL);

	/*
	 * HW sets ack bit to 1 when all outstanding requests have been drained
	 * on this port and minimum soft reset pulse width has elapsed.
	 * Driver polls port_soft_reset_ack to determine अगर reset करोne by HW.
	 */
	अगर (पढ़ोq_poll_समयout(base + PORT_HDR_CTRL, v,
			       v & PORT_CTRL_SFTRST_ACK,
			       RST_POLL_INVL, RST_POLL_TIMEOUT)) अणु
		dev_err(&pdev->dev, "timeout, failure to disable device\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function resets the FPGA Port and its accelerator (AFU) by function
 * __port_disable and __port_enable (set port soft reset bit and then clear
 * it). Userspace can करो Port reset at any समय, e.g. during DMA or Partial
 * Reconfiguration. But it should never cause any प्रणाली level issue, only
 * functional failure (e.g. DMA or PR operation failure) and be recoverable
 * from the failure.
 *
 * Note: the accelerator (AFU) is not accessible when its port is in reset
 * (disabled). Any attempts on MMIO access to AFU जबतक in reset, will
 * result errors reported via port error reporting sub feature (अगर present).
 */
अटल पूर्णांक __port_reset(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = __afu_port_disable(pdev);
	अगर (ret)
		वापस ret;

	वापस __afu_port_enable(pdev);
पूर्ण

अटल पूर्णांक port_reset(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	mutex_lock(&pdata->lock);
	ret = __port_reset(pdev);
	mutex_unlock(&pdata->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक port_get_id(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(&pdev->dev, PORT_FEATURE_ID_HEADER);

	वापस FIELD_GET(PORT_CAP_PORT_NUM, पढ़ोq(base + PORT_HDR_CAP));
पूर्ण

अटल sमाप_प्रकार
id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक id = port_get_id(to_platक्रमm_device(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार
ltr_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + PORT_HDR_CTRL);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "%x\n", (u8)FIELD_GET(PORT_CTRL_LATENCY, v));
पूर्ण

अटल sमाप_प्रकार
ltr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	bool ltr;
	u64 v;

	अगर (kstrtobool(buf, &ltr))
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + PORT_HDR_CTRL);
	v &= ~PORT_CTRL_LATENCY;
	v |= FIELD_PREP(PORT_CTRL_LATENCY, ltr ? 1 : 0);
	ग_लिखोq(v, base + PORT_HDR_CTRL);
	mutex_unlock(&pdata->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(ltr);

अटल sमाप_प्रकार
ap1_event_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + PORT_HDR_STS);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "%x\n", (u8)FIELD_GET(PORT_STS_AP1_EVT, v));
पूर्ण

अटल sमाप_प्रकार
ap1_event_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	bool clear;

	अगर (kstrtobool(buf, &clear) || !clear)
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	ग_लिखोq(PORT_STS_AP1_EVT, base + PORT_HDR_STS);
	mutex_unlock(&pdata->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(ap1_event);

अटल sमाप_प्रकार
ap2_event_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + PORT_HDR_STS);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "%x\n", (u8)FIELD_GET(PORT_STS_AP2_EVT, v));
पूर्ण

अटल sमाप_प्रकार
ap2_event_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	bool clear;

	अगर (kstrtobool(buf, &clear) || !clear)
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	ग_लिखोq(PORT_STS_AP2_EVT, base + PORT_HDR_STS);
	mutex_unlock(&pdata->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(ap2_event);

अटल sमाप_प्रकार
घातer_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	v = पढ़ोq(base + PORT_HDR_STS);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%x\n", (u8)FIELD_GET(PORT_STS_PWR_STATE, v));
पूर्ण
अटल DEVICE_ATTR_RO(घातer_state);

अटल sमाप_प्रकार
userclk_freqcmd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	u64 userclk_freq_cmd;
	व्योम __iomem *base;

	अगर (kstrtou64(buf, 0, &userclk_freq_cmd))
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	ग_लिखोq(userclk_freq_cmd, base + PORT_HDR_USRCLK_CMD0);
	mutex_unlock(&pdata->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(userclk_freqcmd);

अटल sमाप_प्रकार
userclk_freqcntrcmd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	u64 userclk_freqcntr_cmd;
	व्योम __iomem *base;

	अगर (kstrtou64(buf, 0, &userclk_freqcntr_cmd))
		वापस -EINVAL;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	ग_लिखोq(userclk_freqcntr_cmd, base + PORT_HDR_USRCLK_CMD1);
	mutex_unlock(&pdata->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(userclk_freqcntrcmd);

अटल sमाप_प्रकार
userclk_freqsts_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	u64 userclk_freqsts;
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	userclk_freqsts = पढ़ोq(base + PORT_HDR_USRCLK_STS0);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)userclk_freqsts);
पूर्ण
अटल DEVICE_ATTR_RO(userclk_freqsts);

अटल sमाप_प्रकार
userclk_freqcntrsts_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	u64 userclk_freqcntrsts;
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	mutex_lock(&pdata->lock);
	userclk_freqcntrsts = पढ़ोq(base + PORT_HDR_USRCLK_STS1);
	mutex_unlock(&pdata->lock);

	वापस प्र_लिखो(buf, "0x%llx\n",
		       (अचिन्हित दीर्घ दीर्घ)userclk_freqcntrsts);
पूर्ण
अटल DEVICE_ATTR_RO(userclk_freqcntrsts);

अटल काष्ठा attribute *port_hdr_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_ltr.attr,
	&dev_attr_ap1_event.attr,
	&dev_attr_ap2_event.attr,
	&dev_attr_घातer_state.attr,
	&dev_attr_userclk_freqcmd.attr,
	&dev_attr_userclk_freqcntrcmd.attr,
	&dev_attr_userclk_freqsts.attr,
	&dev_attr_userclk_freqcntrsts.attr,
	शून्य,
पूर्ण;

अटल umode_t port_hdr_attrs_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	umode_t mode = attr->mode;
	व्योम __iomem *base;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_HEADER);

	अगर (dfl_feature_revision(base) > 0) अणु
		/*
		 * userclk sysfs पूर्णांकerfaces are only visible in हाल port
		 * revision is 0, as hardware with revision >0 करोesn't
		 * support this.
		 */
		अगर (attr == &dev_attr_userclk_freqcmd.attr ||
		    attr == &dev_attr_userclk_freqcntrcmd.attr ||
		    attr == &dev_attr_userclk_freqsts.attr ||
		    attr == &dev_attr_userclk_freqcntrsts.attr)
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group port_hdr_group = अणु
	.attrs      = port_hdr_attrs,
	.is_visible = port_hdr_attrs_visible,
पूर्ण;

अटल पूर्णांक port_hdr_init(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dfl_feature *feature)
अणु
	port_reset(pdev);

	वापस 0;
पूर्ण

अटल दीर्घ
port_hdr_ioctl(काष्ठा platक्रमm_device *pdev, काष्ठा dfl_feature *feature,
	       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	चयन (cmd) अणु
	हाल DFL_FPGA_PORT_RESET:
		अगर (!arg)
			ret = port_reset(pdev);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	शेष:
		dev_dbg(&pdev->dev, "%x cmd not handled", cmd);
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id port_hdr_id_table[] = अणु
	अणु.id = PORT_FEATURE_ID_HEADER,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops port_hdr_ops = अणु
	.init = port_hdr_init,
	.ioctl = port_hdr_ioctl,
पूर्ण;

अटल sमाप_प्रकार
afu_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(dev);
	व्योम __iomem *base;
	u64 guidl, guidh;

	base = dfl_get_feature_ioaddr_by_id(dev, PORT_FEATURE_ID_AFU);

	mutex_lock(&pdata->lock);
	अगर (pdata->disable_count) अणु
		mutex_unlock(&pdata->lock);
		वापस -EBUSY;
	पूर्ण

	guidl = पढ़ोq(base + GUID_L);
	guidh = पढ़ोq(base + GUID_H);
	mutex_unlock(&pdata->lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%016llx%016llx\n", guidh, guidl);
पूर्ण
अटल DEVICE_ATTR_RO(afu_id);

अटल काष्ठा attribute *port_afu_attrs[] = अणु
	&dev_attr_afu_id.attr,
	शून्य
पूर्ण;

अटल umode_t port_afu_attrs_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entries are visible only अगर related निजी feature is
	 * क्रमागतerated.
	 */
	अगर (!dfl_get_feature_by_id(dev, PORT_FEATURE_ID_AFU))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group port_afu_group = अणु
	.attrs      = port_afu_attrs,
	.is_visible = port_afu_attrs_visible,
पूर्ण;

अटल पूर्णांक port_afu_init(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dfl_feature *feature)
अणु
	काष्ठा resource *res = &pdev->resource[feature->resource_index];

	वापस afu_mmio_region_add(dev_get_platdata(&pdev->dev),
				   DFL_PORT_REGION_INDEX_AFU,
				   resource_size(res), res->start,
				   DFL_PORT_REGION_MMAP | DFL_PORT_REGION_READ |
				   DFL_PORT_REGION_WRITE);
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id port_afu_id_table[] = अणु
	अणु.id = PORT_FEATURE_ID_AFU,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops port_afu_ops = अणु
	.init = port_afu_init,
पूर्ण;

अटल पूर्णांक port_stp_init(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dfl_feature *feature)
अणु
	काष्ठा resource *res = &pdev->resource[feature->resource_index];

	वापस afu_mmio_region_add(dev_get_platdata(&pdev->dev),
				   DFL_PORT_REGION_INDEX_STP,
				   resource_size(res), res->start,
				   DFL_PORT_REGION_MMAP | DFL_PORT_REGION_READ |
				   DFL_PORT_REGION_WRITE);
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id port_stp_id_table[] = अणु
	अणु.id = PORT_FEATURE_ID_STP,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops port_stp_ops = अणु
	.init = port_stp_init,
पूर्ण;

अटल दीर्घ
port_uपूर्णांक_ioctl(काष्ठा platक्रमm_device *pdev, काष्ठा dfl_feature *feature,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल DFL_FPGA_PORT_UINT_GET_IRQ_NUM:
		वापस dfl_feature_ioctl_get_num_irqs(pdev, feature, arg);
	हाल DFL_FPGA_PORT_UINT_SET_IRQ:
		वापस dfl_feature_ioctl_set_irq(pdev, feature, arg);
	शेष:
		dev_dbg(&pdev->dev, "%x cmd not handled", cmd);
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dfl_feature_id port_uपूर्णांक_id_table[] = अणु
	अणु.id = PORT_FEATURE_ID_UINT,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dfl_feature_ops port_uपूर्णांक_ops = अणु
	.ioctl = port_uपूर्णांक_ioctl,
पूर्ण;

अटल काष्ठा dfl_feature_driver port_feature_drvs[] = अणु
	अणु
		.id_table = port_hdr_id_table,
		.ops = &port_hdr_ops,
	पूर्ण,
	अणु
		.id_table = port_afu_id_table,
		.ops = &port_afu_ops,
	पूर्ण,
	अणु
		.id_table = port_err_id_table,
		.ops = &port_err_ops,
	पूर्ण,
	अणु
		.id_table = port_stp_id_table,
		.ops = &port_stp_ops,
	पूर्ण,
	अणु
		.id_table = port_uपूर्णांक_id_table,
		.ops = &port_uपूर्णांक_ops,
	पूर्ण,
	अणु
		.ops = शून्य,
	पूर्ण
पूर्ण;

अटल पूर्णांक afu_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा platक्रमm_device *fdev = dfl_fpga_inode_to_feature_dev(inode);
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	पूर्णांक ret;

	pdata = dev_get_platdata(&fdev->dev);
	अगर (WARN_ON(!pdata))
		वापस -ENODEV;

	mutex_lock(&pdata->lock);
	ret = dfl_feature_dev_use_begin(pdata, filp->f_flags & O_EXCL);
	अगर (!ret) अणु
		dev_dbg(&fdev->dev, "Device File Opened %d Times\n",
			dfl_feature_dev_use_count(pdata));
		filp->निजी_data = fdev;
	पूर्ण
	mutex_unlock(&pdata->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक afu_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा platक्रमm_device *pdev = filp->निजी_data;
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	काष्ठा dfl_feature *feature;

	dev_dbg(&pdev->dev, "Device File Release\n");

	pdata = dev_get_platdata(&pdev->dev);

	mutex_lock(&pdata->lock);
	dfl_feature_dev_use_end(pdata);

	अगर (!dfl_feature_dev_use_count(pdata)) अणु
		dfl_fpga_dev_क्रम_each_feature(pdata, feature)
			dfl_fpga_set_irq_triggers(feature, 0,
						  feature->nr_irqs, शून्य);
		__port_reset(pdev);
		afu_dma_region_destroy(pdata);
	पूर्ण
	mutex_unlock(&pdata->lock);

	वापस 0;
पूर्ण

अटल दीर्घ afu_ioctl_check_extension(काष्ठा dfl_feature_platक्रमm_data *pdata,
				      अचिन्हित दीर्घ arg)
अणु
	/* No extension support क्रम now */
	वापस 0;
पूर्ण

अटल दीर्घ
afu_ioctl_get_info(काष्ठा dfl_feature_platक्रमm_data *pdata, व्योम __user *arg)
अणु
	काष्ठा dfl_fpga_port_info info;
	काष्ठा dfl_afu *afu;
	अचिन्हित दीर्घ minsz;

	minsz = दुरत्वend(काष्ठा dfl_fpga_port_info, num_umsgs);

	अगर (copy_from_user(&info, arg, minsz))
		वापस -EFAULT;

	अगर (info.argsz < minsz)
		वापस -EINVAL;

	mutex_lock(&pdata->lock);
	afu = dfl_fpga_pdata_get_निजी(pdata);
	info.flags = 0;
	info.num_regions = afu->num_regions;
	info.num_umsgs = afu->num_umsgs;
	mutex_unlock(&pdata->lock);

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ afu_ioctl_get_region_info(काष्ठा dfl_feature_platक्रमm_data *pdata,
				      व्योम __user *arg)
अणु
	काष्ठा dfl_fpga_port_region_info rinfo;
	काष्ठा dfl_afu_mmio_region region;
	अचिन्हित दीर्घ minsz;
	दीर्घ ret;

	minsz = दुरत्वend(काष्ठा dfl_fpga_port_region_info, offset);

	अगर (copy_from_user(&rinfo, arg, minsz))
		वापस -EFAULT;

	अगर (rinfo.argsz < minsz || rinfo.padding)
		वापस -EINVAL;

	ret = afu_mmio_region_get_by_index(pdata, rinfo.index, &region);
	अगर (ret)
		वापस ret;

	rinfo.flags = region.flags;
	rinfo.size = region.size;
	rinfo.offset = region.offset;

	अगर (copy_to_user(arg, &rinfo, माप(rinfo)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ
afu_ioctl_dma_map(काष्ठा dfl_feature_platक्रमm_data *pdata, व्योम __user *arg)
अणु
	काष्ठा dfl_fpga_port_dma_map map;
	अचिन्हित दीर्घ minsz;
	दीर्घ ret;

	minsz = दुरत्वend(काष्ठा dfl_fpga_port_dma_map, iova);

	अगर (copy_from_user(&map, arg, minsz))
		वापस -EFAULT;

	अगर (map.argsz < minsz || map.flags)
		वापस -EINVAL;

	ret = afu_dma_map_region(pdata, map.user_addr, map.length, &map.iova);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(arg, &map, माप(map))) अणु
		afu_dma_unmap_region(pdata, map.iova);
		वापस -EFAULT;
	पूर्ण

	dev_dbg(&pdata->dev->dev, "dma map: ua=%llx, len=%llx, iova=%llx\n",
		(अचिन्हित दीर्घ दीर्घ)map.user_addr,
		(अचिन्हित दीर्घ दीर्घ)map.length,
		(अचिन्हित दीर्घ दीर्घ)map.iova);

	वापस 0;
पूर्ण

अटल दीर्घ
afu_ioctl_dma_unmap(काष्ठा dfl_feature_platक्रमm_data *pdata, व्योम __user *arg)
अणु
	काष्ठा dfl_fpga_port_dma_unmap unmap;
	अचिन्हित दीर्घ minsz;

	minsz = दुरत्वend(काष्ठा dfl_fpga_port_dma_unmap, iova);

	अगर (copy_from_user(&unmap, arg, minsz))
		वापस -EFAULT;

	अगर (unmap.argsz < minsz || unmap.flags)
		वापस -EINVAL;

	वापस afu_dma_unmap_region(pdata, unmap.iova);
पूर्ण

अटल दीर्घ afu_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा platक्रमm_device *pdev = filp->निजी_data;
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	काष्ठा dfl_feature *f;
	दीर्घ ret;

	dev_dbg(&pdev->dev, "%s cmd 0x%x\n", __func__, cmd);

	pdata = dev_get_platdata(&pdev->dev);

	चयन (cmd) अणु
	हाल DFL_FPGA_GET_API_VERSION:
		वापस DFL_FPGA_API_VERSION;
	हाल DFL_FPGA_CHECK_EXTENSION:
		वापस afu_ioctl_check_extension(pdata, arg);
	हाल DFL_FPGA_PORT_GET_INFO:
		वापस afu_ioctl_get_info(pdata, (व्योम __user *)arg);
	हाल DFL_FPGA_PORT_GET_REGION_INFO:
		वापस afu_ioctl_get_region_info(pdata, (व्योम __user *)arg);
	हाल DFL_FPGA_PORT_DMA_MAP:
		वापस afu_ioctl_dma_map(pdata, (व्योम __user *)arg);
	हाल DFL_FPGA_PORT_DMA_UNMAP:
		वापस afu_ioctl_dma_unmap(pdata, (व्योम __user *)arg);
	शेष:
		/*
		 * Let sub-feature's ioctl function to handle the cmd
		 * Sub-feature's ioctl वापसs -ENODEV when cmd is not
		 * handled in this sub feature, and वापसs 0 and other
		 * error code अगर cmd is handled.
		 */
		dfl_fpga_dev_क्रम_each_feature(pdata, f)
			अगर (f->ops && f->ops->ioctl) अणु
				ret = f->ops->ioctl(pdev, f, cmd, arg);
				अगर (ret != -ENODEV)
					वापस ret;
			पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा afu_vma_ops = अणु
#अगर_घोषित CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक afu_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा platक्रमm_device *pdev = filp->निजी_data;
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	u64 size = vma->vm_end - vma->vm_start;
	काष्ठा dfl_afu_mmio_region region;
	u64 offset;
	पूर्णांक ret;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	pdata = dev_get_platdata(&pdev->dev);

	offset = vma->vm_pgoff << PAGE_SHIFT;
	ret = afu_mmio_region_get_by_offset(pdata, offset, size, &region);
	अगर (ret)
		वापस ret;

	अगर (!(region.flags & DFL_PORT_REGION_MMAP))
		वापस -EINVAL;

	अगर ((vma->vm_flags & VM_READ) && !(region.flags & DFL_PORT_REGION_READ))
		वापस -EPERM;

	अगर ((vma->vm_flags & VM_WRITE) &&
	    !(region.flags & DFL_PORT_REGION_WRITE))
		वापस -EPERM;

	/* Support debug access to the mapping */
	vma->vm_ops = &afu_vma_ops;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	वापस remap_pfn_range(vma, vma->vm_start,
			(region.phys + (offset - region.offset)) >> PAGE_SHIFT,
			size, vma->vm_page_prot);
पूर्ण

अटल स्थिर काष्ठा file_operations afu_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = afu_खोलो,
	.release = afu_release,
	.unlocked_ioctl = afu_ioctl,
	.mmap = afu_mmap,
पूर्ण;

अटल पूर्णांक afu_dev_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_afu *afu;

	afu = devm_kzalloc(&pdev->dev, माप(*afu), GFP_KERNEL);
	अगर (!afu)
		वापस -ENOMEM;

	afu->pdata = pdata;

	mutex_lock(&pdata->lock);
	dfl_fpga_pdata_set_निजी(pdata, afu);
	afu_mmio_region_init(pdata);
	afu_dma_region_init(pdata);
	mutex_unlock(&pdata->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक afu_dev_destroy(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	mutex_lock(&pdata->lock);
	afu_mmio_region_destroy(pdata);
	afu_dma_region_destroy(pdata);
	dfl_fpga_pdata_set_निजी(pdata, शून्य);
	mutex_unlock(&pdata->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक port_enable_set(काष्ठा platक्रमm_device *pdev, bool enable)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	mutex_lock(&pdata->lock);
	अगर (enable)
		ret = __afu_port_enable(pdev);
	अन्यथा
		ret = __afu_port_disable(pdev);
	mutex_unlock(&pdata->lock);

	वापस ret;
पूर्ण

अटल काष्ठा dfl_fpga_port_ops afu_port_ops = अणु
	.name = DFL_FPGA_FEATURE_DEV_PORT,
	.owner = THIS_MODULE,
	.get_id = port_get_id,
	.enable_set = port_enable_set,
पूर्ण;

अटल पूर्णांक afu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	ret = afu_dev_init(pdev);
	अगर (ret)
		जाओ निकास;

	ret = dfl_fpga_dev_feature_init(pdev, port_feature_drvs);
	अगर (ret)
		जाओ dev_destroy;

	ret = dfl_fpga_dev_ops_रेजिस्टर(pdev, &afu_fops, THIS_MODULE);
	अगर (ret) अणु
		dfl_fpga_dev_feature_uinit(pdev);
		जाओ dev_destroy;
	पूर्ण

	वापस 0;

dev_destroy:
	afu_dev_destroy(pdev);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक afu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_dbg(&pdev->dev, "%s\n", __func__);

	dfl_fpga_dev_ops_unरेजिस्टर(pdev);
	dfl_fpga_dev_feature_uinit(pdev);
	afu_dev_destroy(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group *afu_dev_groups[] = अणु
	&port_hdr_group,
	&port_afu_group,
	&port_err_group,
	शून्य
पूर्ण;

अटल काष्ठा platक्रमm_driver afu_driver = अणु
	.driver	= अणु
		.name	    = DFL_FPGA_FEATURE_DEV_PORT,
		.dev_groups = afu_dev_groups,
	पूर्ण,
	.probe   = afu_probe,
	.हटाओ  = afu_हटाओ,
पूर्ण;

अटल पूर्णांक __init afu_init(व्योम)
अणु
	पूर्णांक ret;

	dfl_fpga_port_ops_add(&afu_port_ops);

	ret = platक्रमm_driver_रेजिस्टर(&afu_driver);
	अगर (ret)
		dfl_fpga_port_ops_del(&afu_port_ops);

	वापस ret;
पूर्ण

अटल व्योम __निकास afu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&afu_driver);

	dfl_fpga_port_ops_del(&afu_port_ops);
पूर्ण

module_init(afu_init);
module_निकास(afu_निकास);

MODULE_DESCRIPTION("FPGA Accelerated Function Unit driver");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dfl-port");
