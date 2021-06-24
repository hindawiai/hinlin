<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2014 NVIDIA Corporation
 * Copyright तऊ 2015 Broadcom Corporation
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/brcmstb/brcmstb.h>
#समावेश <linux/sys_soc.h>

अटल u32 family_id;
अटल u32 product_id;

अटल स्थिर काष्ठा of_device_id brcmstb_machine_match[] = अणु
	अणु .compatible = "brcm,brcmstb", पूर्ण,
	अणु पूर्ण
पूर्ण;

u32 brcmstb_get_family_id(व्योम)
अणु
	वापस family_id;
पूर्ण
EXPORT_SYMBOL(brcmstb_get_family_id);

u32 brcmstb_get_product_id(व्योम)
अणु
	वापस product_id;
पूर्ण
EXPORT_SYMBOL(brcmstb_get_product_id);

अटल स्थिर काष्ठा of_device_id sun_top_ctrl_match[] = अणु
	अणु .compatible = "brcm,bcm7125-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7346-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7358-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7360-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7362-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7420-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7425-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7429-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,bcm7435-sun-top-ctrl", पूर्ण,
	अणु .compatible = "brcm,brcmstb-sun-top-ctrl", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init brcmstb_soc_device_early_init(व्योम)
अणु
	काष्ठा device_node *sun_top_ctrl;
	व्योम __iomem *sun_top_ctrl_base;
	पूर्णांक ret = 0;

	/* We could be on a multi-platक्रमm kernel, करोn't make this fatal but
	 * bail out early
	 */
	sun_top_ctrl = of_find_matching_node(शून्य, sun_top_ctrl_match);
	अगर (!sun_top_ctrl)
		वापस ret;

	sun_top_ctrl_base = of_iomap(sun_top_ctrl, 0);
	अगर (!sun_top_ctrl_base) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	family_id = पढ़ोl(sun_top_ctrl_base);
	product_id = पढ़ोl(sun_top_ctrl_base + 0x4);
	iounmap(sun_top_ctrl_base);
out:
	of_node_put(sun_top_ctrl);
	वापस ret;
पूर्ण
early_initcall(brcmstb_soc_device_early_init);

अटल पूर्णांक __init brcmstb_soc_device_init(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा device_node *sun_top_ctrl;
	काष्ठा soc_device *soc_dev;
	पूर्णांक ret = 0;

	/* We could be on a multi-platक्रमm kernel, करोn't make this fatal but
	 * bail out early
	 */
	sun_top_ctrl = of_find_matching_node(शून्य, sun_top_ctrl_match);
	अगर (!sun_top_ctrl)
		वापस ret;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	soc_dev_attr->family = kaप्र_लिखो(GFP_KERNEL, "%x",
					 family_id >> 28 ?
					 family_id >> 16 : family_id >> 8);
	soc_dev_attr->soc_id = kaप्र_लिखो(GFP_KERNEL, "%x",
					 product_id >> 28 ?
					 product_id >> 16 : product_id >> 8);
	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "%c%d",
					 ((product_id & 0xf0) >> 4) + 'A',
					   product_id & 0xf);

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->family);
		kमुक्त(soc_dev_attr->soc_id);
		kमुक्त(soc_dev_attr->revision);
		kमुक्त(soc_dev_attr);
		ret = -ENOMEM;
	पूर्ण
out:
	of_node_put(sun_top_ctrl);
	वापस ret;
पूर्ण
arch_initcall(brcmstb_soc_device_init);
