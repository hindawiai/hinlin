<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A driver क्रम the RTC embedded in the Cirrus Logic EP93XX processors
 * Copyright (c) 2006 Tower Technologies
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gfp.h>

#घोषणा EP93XX_RTC_DATA			0x000
#घोषणा EP93XX_RTC_MATCH		0x004
#घोषणा EP93XX_RTC_STATUS		0x008
#घोषणा  EP93XX_RTC_STATUS_INTR		 BIT(0)
#घोषणा EP93XX_RTC_LOAD			0x00C
#घोषणा EP93XX_RTC_CONTROL		0x010
#घोषणा  EP93XX_RTC_CONTROL_MIE		 BIT(0)
#घोषणा EP93XX_RTC_SWCOMP		0x108
#घोषणा  EP93XX_RTC_SWCOMP_DEL_MASK	 0x001f0000
#घोषणा  EP93XX_RTC_SWCOMP_DEL_SHIFT	 16
#घोषणा  EP93XX_RTC_SWCOMP_INT_MASK	 0x0000ffff
#घोषणा  EP93XX_RTC_SWCOMP_INT_SHIFT	 0

काष्ठा ep93xx_rtc अणु
	व्योम __iomem	*mmio_base;
	काष्ठा rtc_device *rtc;
पूर्ण;

अटल पूर्णांक ep93xx_rtc_get_swcomp(काष्ठा device *dev, अचिन्हित लघु *preload,
				 अचिन्हित लघु *delete)
अणु
	काष्ठा ep93xx_rtc *ep93xx_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ comp;

	comp = पढ़ोl(ep93xx_rtc->mmio_base + EP93XX_RTC_SWCOMP);

	अगर (preload)
		*preload = (comp & EP93XX_RTC_SWCOMP_INT_MASK)
				>> EP93XX_RTC_SWCOMP_INT_SHIFT;

	अगर (delete)
		*delete = (comp & EP93XX_RTC_SWCOMP_DEL_MASK)
				>> EP93XX_RTC_SWCOMP_DEL_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ep93xx_rtc *ep93xx_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समय;

	समय = पढ़ोl(ep93xx_rtc->mmio_base + EP93XX_RTC_DATA);

	rtc_समय64_to_पंचांग(समय, पंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ep93xx_rtc *ep93xx_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ secs = rtc_पंचांग_to_समय64(पंचांग);

	ग_लिखोl(secs + 1, ep93xx_rtc->mmio_base + EP93XX_RTC_LOAD);
	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	अचिन्हित लघु preload, delete;

	ep93xx_rtc_get_swcomp(dev, &preload, &delete);

	seq_म_लिखो(seq, "preload\t\t: %d\n", preload);
	seq_म_लिखो(seq, "delete\t\t: %d\n", delete);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ep93xx_rtc_ops = अणु
	.पढ़ो_समय	= ep93xx_rtc_पढ़ो_समय,
	.set_समय	= ep93xx_rtc_set_समय,
	.proc		= ep93xx_rtc_proc,
पूर्ण;

अटल sमाप_प्रकार comp_preload_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित लघु preload;

	ep93xx_rtc_get_swcomp(dev->parent, &preload, शून्य);

	वापस प्र_लिखो(buf, "%d\n", preload);
पूर्ण
अटल DEVICE_ATTR_RO(comp_preload);

अटल sमाप_प्रकार comp_delete_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित लघु delete;

	ep93xx_rtc_get_swcomp(dev->parent, शून्य, &delete);

	वापस प्र_लिखो(buf, "%d\n", delete);
पूर्ण
अटल DEVICE_ATTR_RO(comp_delete);

अटल काष्ठा attribute *ep93xx_rtc_attrs[] = अणु
	&dev_attr_comp_preload.attr,
	&dev_attr_comp_delete.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ep93xx_rtc_sysfs_files = अणु
	.attrs	= ep93xx_rtc_attrs,
पूर्ण;

अटल पूर्णांक ep93xx_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_rtc *ep93xx_rtc;
	पूर्णांक err;

	ep93xx_rtc = devm_kzalloc(&pdev->dev, माप(*ep93xx_rtc), GFP_KERNEL);
	अगर (!ep93xx_rtc)
		वापस -ENOMEM;

	ep93xx_rtc->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ep93xx_rtc->mmio_base))
		वापस PTR_ERR(ep93xx_rtc->mmio_base);

	platक्रमm_set_drvdata(pdev, ep93xx_rtc);

	ep93xx_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(ep93xx_rtc->rtc))
		वापस PTR_ERR(ep93xx_rtc->rtc);

	ep93xx_rtc->rtc->ops = &ep93xx_rtc_ops;
	ep93xx_rtc->rtc->range_max = U32_MAX;

	err = rtc_add_group(ep93xx_rtc->rtc, &ep93xx_rtc_sysfs_files);
	अगर (err)
		वापस err;

	वापस devm_rtc_रेजिस्टर_device(ep93xx_rtc->rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_rtc_driver = अणु
	.driver		= अणु
		.name	= "ep93xx-rtc",
	पूर्ण,
	.probe		= ep93xx_rtc_probe,
पूर्ण;

module_platक्रमm_driver(ep93xx_rtc_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("EP93XX RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ep93xx-rtc");
