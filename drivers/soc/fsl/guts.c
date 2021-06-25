<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale QorIQ Platक्रमms GUTS Driver
 *
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 */

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fsl/guts.h>

काष्ठा guts अणु
	काष्ठा ccsr_guts __iomem *regs;
	bool little_endian;
पूर्ण;

काष्ठा fsl_soc_die_attr अणु
	अक्षर	*die;
	u32	svr;
	u32	mask;
पूर्ण;

अटल काष्ठा guts *guts;
अटल काष्ठा soc_device_attribute soc_dev_attr;
अटल काष्ठा soc_device *soc_dev;
अटल काष्ठा device_node *root;


/* SoC die attribute definition क्रम QorIQ platक्रमm */
अटल स्थिर काष्ठा fsl_soc_die_attr fsl_soc_die[] = अणु
	/*
	 * Power Architecture-based SoCs T Series
	 */

	/* Die: T4240, SoC: T4240/T4160/T4080 */
	अणु .die		= "T4240",
	  .svr		= 0x82400000,
	  .mask		= 0xfff00000,
	पूर्ण,
	/* Die: T1040, SoC: T1040/T1020/T1042/T1022 */
	अणु .die		= "T1040",
	  .svr		= 0x85200000,
	  .mask		= 0xfff00000,
	पूर्ण,
	/* Die: T2080, SoC: T2080/T2081 */
	अणु .die		= "T2080",
	  .svr		= 0x85300000,
	  .mask		= 0xfff00000,
	पूर्ण,
	/* Die: T1024, SoC: T1024/T1014/T1023/T1013 */
	अणु .die		= "T1024",
	  .svr		= 0x85400000,
	  .mask		= 0xfff00000,
	पूर्ण,

	/*
	 * ARM-based SoCs LS Series
	 */

	/* Die: LS1043A, SoC: LS1043A/LS1023A */
	अणु .die		= "LS1043A",
	  .svr		= 0x87920000,
	  .mask		= 0xffff0000,
	पूर्ण,
	/* Die: LS2080A, SoC: LS2080A/LS2040A/LS2085A */
	अणु .die		= "LS2080A",
	  .svr		= 0x87010000,
	  .mask		= 0xff3f0000,
	पूर्ण,
	/* Die: LS1088A, SoC: LS1088A/LS1048A/LS1084A/LS1044A */
	अणु .die		= "LS1088A",
	  .svr		= 0x87030000,
	  .mask		= 0xff3f0000,
	पूर्ण,
	/* Die: LS1012A, SoC: LS1012A */
	अणु .die		= "LS1012A",
	  .svr		= 0x87040000,
	  .mask		= 0xffff0000,
	पूर्ण,
	/* Die: LS1046A, SoC: LS1046A/LS1026A */
	अणु .die		= "LS1046A",
	  .svr		= 0x87070000,
	  .mask		= 0xffff0000,
	पूर्ण,
	/* Die: LS2088A, SoC: LS2088A/LS2048A/LS2084A/LS2044A */
	अणु .die		= "LS2088A",
	  .svr		= 0x87090000,
	  .mask		= 0xff3f0000,
	पूर्ण,
	/* Die: LS1021A, SoC: LS1021A/LS1020A/LS1022A */
	अणु .die		= "LS1021A",
	  .svr		= 0x87000000,
	  .mask		= 0xfff70000,
	पूर्ण,
	/* Die: LX2160A, SoC: LX2160A/LX2120A/LX2080A */
	अणु .die          = "LX2160A",
	  .svr          = 0x87360000,
	  .mask         = 0xff3f0000,
	पूर्ण,
	/* Die: LS1028A, SoC: LS1028A */
	अणु .die          = "LS1028A",
	  .svr          = 0x870b0000,
	  .mask         = 0xff3f0000,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा fsl_soc_die_attr *fsl_soc_die_match(
	u32 svr, स्थिर काष्ठा fsl_soc_die_attr *matches)
अणु
	जबतक (matches->svr) अणु
		अगर (matches->svr == (svr & matches->mask))
			वापस matches;
		matches++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल u32 fsl_guts_get_svr(व्योम)
अणु
	u32 svr = 0;

	अगर (!guts || !guts->regs)
		वापस svr;

	अगर (guts->little_endian)
		svr = ioपढ़ो32(&guts->regs->svr);
	अन्यथा
		svr = ioपढ़ो32be(&guts->regs->svr);

	वापस svr;
पूर्ण

अटल पूर्णांक fsl_guts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	स्थिर काष्ठा fsl_soc_die_attr *soc_die;
	स्थिर अक्षर *machine;
	u32 svr;

	/* Initialize guts */
	guts = devm_kzalloc(dev, माप(*guts), GFP_KERNEL);
	अगर (!guts)
		वापस -ENOMEM;

	guts->little_endian = of_property_पढ़ो_bool(np, "little-endian");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	guts->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(guts->regs))
		वापस PTR_ERR(guts->regs);

	/* Register soc device */
	root = of_find_node_by_path("/");
	अगर (of_property_पढ़ो_string(root, "model", &machine))
		of_property_पढ़ो_string_index(root, "compatible", 0, &machine);
	अगर (machine)
		soc_dev_attr.machine = machine;

	svr = fsl_guts_get_svr();
	soc_die = fsl_soc_die_match(svr, fsl_soc_die);
	अगर (soc_die) अणु
		soc_dev_attr.family = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						     "QorIQ %s", soc_die->die);
	पूर्ण अन्यथा अणु
		soc_dev_attr.family = devm_kaप्र_लिखो(dev, GFP_KERNEL, "QorIQ");
	पूर्ण
	अगर (!soc_dev_attr.family)
		वापस -ENOMEM;
	soc_dev_attr.soc_id = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					     "svr:0x%08x", svr);
	अगर (!soc_dev_attr.soc_id)
		वापस -ENOMEM;
	soc_dev_attr.revision = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%d.%d",
					       (svr >>  4) & 0xf, svr & 0xf);
	अगर (!soc_dev_attr.revision)
		वापस -ENOMEM;

	soc_dev = soc_device_रेजिस्टर(&soc_dev_attr);
	अगर (IS_ERR(soc_dev))
		वापस PTR_ERR(soc_dev);

	pr_info("Machine: %s\n", soc_dev_attr.machine);
	pr_info("SoC family: %s\n", soc_dev_attr.family);
	pr_info("SoC ID: %s, Revision: %s\n",
		soc_dev_attr.soc_id, soc_dev_attr.revision);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_guts_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	soc_device_unरेजिस्टर(soc_dev);
	of_node_put(root);
	वापस 0;
पूर्ण

/*
 * Table क्रम matching compatible strings, क्रम device tree
 * guts node, क्रम Freescale QorIQ SOCs.
 */
अटल स्थिर काष्ठा of_device_id fsl_guts_of_match[] = अणु
	अणु .compatible = "fsl,qoriq-device-config-1.0", पूर्ण,
	अणु .compatible = "fsl,qoriq-device-config-2.0", पूर्ण,
	अणु .compatible = "fsl,p1010-guts", पूर्ण,
	अणु .compatible = "fsl,p1020-guts", पूर्ण,
	अणु .compatible = "fsl,p1021-guts", पूर्ण,
	अणु .compatible = "fsl,p1022-guts", पूर्ण,
	अणु .compatible = "fsl,p1023-guts", पूर्ण,
	अणु .compatible = "fsl,p2020-guts", पूर्ण,
	अणु .compatible = "fsl,bsc9131-guts", पूर्ण,
	अणु .compatible = "fsl,bsc9132-guts", पूर्ण,
	अणु .compatible = "fsl,mpc8536-guts", पूर्ण,
	अणु .compatible = "fsl,mpc8544-guts", पूर्ण,
	अणु .compatible = "fsl,mpc8548-guts", पूर्ण,
	अणु .compatible = "fsl,mpc8568-guts", पूर्ण,
	अणु .compatible = "fsl,mpc8569-guts", पूर्ण,
	अणु .compatible = "fsl,mpc8572-guts", पूर्ण,
	अणु .compatible = "fsl,ls1021a-dcfg", पूर्ण,
	अणु .compatible = "fsl,ls1043a-dcfg", पूर्ण,
	अणु .compatible = "fsl,ls2080a-dcfg", पूर्ण,
	अणु .compatible = "fsl,ls1088a-dcfg", पूर्ण,
	अणु .compatible = "fsl,ls1012a-dcfg", पूर्ण,
	अणु .compatible = "fsl,ls1046a-dcfg", पूर्ण,
	अणु .compatible = "fsl,lx2160a-dcfg", पूर्ण,
	अणु .compatible = "fsl,ls1028a-dcfg", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_guts_of_match);

अटल काष्ठा platक्रमm_driver fsl_guts_driver = अणु
	.driver = अणु
		.name = "fsl-guts",
		.of_match_table = fsl_guts_of_match,
	पूर्ण,
	.probe = fsl_guts_probe,
	.हटाओ = fsl_guts_हटाओ,
पूर्ण;

अटल पूर्णांक __init fsl_guts_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fsl_guts_driver);
पूर्ण
core_initcall(fsl_guts_init);

अटल व्योम __निकास fsl_guts_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fsl_guts_driver);
पूर्ण
module_निकास(fsl_guts_निकास);
