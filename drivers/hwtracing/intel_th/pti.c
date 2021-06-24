<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub PTI output driver
 *
 * Copyright (C) 2014-2016 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>

#समावेश "intel_th.h"
#समावेश "pti.h"

काष्ठा pti_device अणु
	व्योम __iomem		*base;
	काष्ठा पूर्णांकel_th_device	*thdev;
	अचिन्हित पूर्णांक		mode;
	अचिन्हित पूर्णांक		मुक्तclk;
	अचिन्हित पूर्णांक		clkभाग;
	अचिन्हित पूर्णांक		patgen;
	अचिन्हित पूर्णांक		lpp_dest_mask;
	अचिन्हित पूर्णांक		lpp_dest;
पूर्ण;

/* map PTI widths to MODE settings of PTI_CTL रेजिस्टर */
अटल स्थिर अचिन्हित पूर्णांक pti_mode[] = अणु
	0, 4, 8, 0, 12, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0,
पूर्ण;

अटल पूर्णांक pti_width_mode(अचिन्हित पूर्णांक width)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pti_mode); i++)
		अगर (pti_mode[i] == width)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", pti_mode[pti->mode]);
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = pti_width_mode(val);
	अगर (ret < 0)
		वापस ret;

	pti->mode = ret;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(mode);

अटल sमाप_प्रकार
मुक्तrunning_घड़ी_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", pti->मुक्तclk);
पूर्ण

अटल sमाप_प्रकार
मुक्तrunning_घड़ी_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	pti->मुक्तclk = !!val;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(मुक्तrunning_घड़ी);

अटल sमाप_प्रकार
घड़ी_भागider_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   अक्षर *buf)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", 1u << pti->clkभाग);
पूर्ण

अटल sमाप_प्रकार
घड़ी_भागider_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (!is_घातer_of_2(val) || val > 8 || !val)
		वापस -EINVAL;

	pti->clkभाग = val;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(घड़ी_भागider);

अटल काष्ठा attribute *pti_output_attrs[] = अणु
	&dev_attr_mode.attr,
	&dev_attr_मुक्तrunning_घड़ी.attr,
	&dev_attr_घड़ी_भागider.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pti_output_group = अणु
	.attrs	= pti_output_attrs,
पूर्ण;

अटल पूर्णांक पूर्णांकel_th_pti_activate(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(&thdev->dev);
	u32 ctl = PTI_EN;

	अगर (pti->patgen)
		ctl |= pti->patgen << __ffs(PTI_PATGENMODE);
	अगर (pti->मुक्तclk)
		ctl |= PTI_FCEN;
	ctl |= pti->mode << __ffs(PTI_MODE);
	ctl |= pti->clkभाग << __ffs(PTI_CLKDIV);
	ctl |= pti->lpp_dest << __ffs(LPP_DEST);

	ioग_लिखो32(ctl, pti->base + REG_PTI_CTL);

	पूर्णांकel_th_trace_enable(thdev);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_pti_deactivate(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(&thdev->dev);

	पूर्णांकel_th_trace_disable(thdev);

	ioग_लिखो32(0, pti->base + REG_PTI_CTL);
पूर्ण

अटल व्योम पढ़ो_hw_config(काष्ठा pti_device *pti)
अणु
	u32 ctl = ioपढ़ो32(pti->base + REG_PTI_CTL);

	pti->mode	= (ctl & PTI_MODE) >> __ffs(PTI_MODE);
	pti->clkभाग	= (ctl & PTI_CLKDIV) >> __ffs(PTI_CLKDIV);
	pti->मुक्तclk	= !!(ctl & PTI_FCEN);

	अगर (!pti_mode[pti->mode])
		pti->mode = pti_width_mode(4);
	अगर (!pti->clkभाग)
		pti->clkभाग = 1;

	अगर (pti->thdev->output.type == GTH_LPP) अणु
		अगर (ctl & LPP_PTIPRESENT)
			pti->lpp_dest_mask |= LPP_DEST_PTI;
		अगर (ctl & LPP_BSSBPRESENT)
			pti->lpp_dest_mask |= LPP_DEST_EXI;
		अगर (ctl & LPP_DEST)
			pti->lpp_dest = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_th_pti_probe(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा device *dev = &thdev->dev;
	काष्ठा resource *res;
	काष्ठा pti_device *pti;
	व्योम __iomem *base;

	res = पूर्णांकel_th_device_get_resource(thdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!base)
		वापस -ENOMEM;

	pti = devm_kzalloc(dev, माप(*pti), GFP_KERNEL);
	अगर (!pti)
		वापस -ENOMEM;

	pti->thdev = thdev;
	pti->base = base;

	पढ़ो_hw_config(pti);

	dev_set_drvdata(dev, pti);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_pti_हटाओ(काष्ठा पूर्णांकel_th_device *thdev)
अणु
पूर्ण

अटल काष्ठा पूर्णांकel_th_driver पूर्णांकel_th_pti_driver = अणु
	.probe	= पूर्णांकel_th_pti_probe,
	.हटाओ	= पूर्णांकel_th_pti_हटाओ,
	.activate	= पूर्णांकel_th_pti_activate,
	.deactivate	= पूर्णांकel_th_pti_deactivate,
	.attr_group	= &pti_output_group,
	.driver	= अणु
		.name	= "pti",
		.owner	= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lpp_dest_str[] = अणु "pti", "exi" पूर्ण;

अटल sमाप_प्रकार lpp_dest_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);
	sमाप_प्रकार ret = 0;
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(lpp_dest_str) - 1; i >= 0; i--) अणु
		स्थिर अक्षर *fmt = pti->lpp_dest == i ? "[%s] " : "%s ";

		अगर (!(pti->lpp_dest_mask & BIT(i)))
			जारी;

		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				 fmt, lpp_dest_str[i]);
	पूर्ण

	अगर (ret)
		buf[ret - 1] = '\n';

	वापस ret;
पूर्ण

अटल sमाप_प्रकार lpp_dest_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pti_device *pti = dev_get_drvdata(dev);
	पूर्णांक i;

	i = sysfs_match_string(lpp_dest_str, buf);
	अगर (i < 0)
		वापस i;

	अगर (!(pti->lpp_dest_mask & BIT(i)))
		वापस -EINVAL;

	pti->lpp_dest = i;
	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(lpp_dest);

अटल काष्ठा attribute *lpp_output_attrs[] = अणु
	&dev_attr_mode.attr,
	&dev_attr_मुक्तrunning_घड़ी.attr,
	&dev_attr_घड़ी_भागider.attr,
	&dev_attr_lpp_dest.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lpp_output_group = अणु
	.attrs	= lpp_output_attrs,
पूर्ण;

अटल काष्ठा पूर्णांकel_th_driver पूर्णांकel_th_lpp_driver = अणु
	.probe		= पूर्णांकel_th_pti_probe,
	.हटाओ		= पूर्णांकel_th_pti_हटाओ,
	.activate	= पूर्णांकel_th_pti_activate,
	.deactivate	= पूर्णांकel_th_pti_deactivate,
	.attr_group	= &lpp_output_group,
	.driver	= अणु
		.name	= "lpp",
		.owner	= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init पूर्णांकel_th_pti_lpp_init(व्योम)
अणु
	पूर्णांक err;

	err = पूर्णांकel_th_driver_रेजिस्टर(&पूर्णांकel_th_pti_driver);
	अगर (err)
		वापस err;

	err = पूर्णांकel_th_driver_रेजिस्टर(&पूर्णांकel_th_lpp_driver);
	अगर (err) अणु
		पूर्णांकel_th_driver_unरेजिस्टर(&पूर्णांकel_th_pti_driver);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

module_init(पूर्णांकel_th_pti_lpp_init);

अटल व्योम __निकास पूर्णांकel_th_pti_lpp_निकास(व्योम)
अणु
	पूर्णांकel_th_driver_unरेजिस्टर(&पूर्णांकel_th_pti_driver);
	पूर्णांकel_th_driver_unरेजिस्टर(&पूर्णांकel_th_lpp_driver);
पूर्ण

module_निकास(पूर्णांकel_th_pti_lpp_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub PTI/LPP output driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
