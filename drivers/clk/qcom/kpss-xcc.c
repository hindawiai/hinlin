<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>

अटल स्थिर अक्षर *aux_parents[] = अणु
	"pll8_vote",
	"pxo",
पूर्ण;

अटल अचिन्हित पूर्णांक aux_parent_map[] = अणु
	3,
	0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id kpss_xcc_match_table[] = अणु
	अणु .compatible = "qcom,kpss-acc-v1", .data = (व्योम *)1UL पूर्ण,
	अणु .compatible = "qcom,kpss-gcc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, kpss_xcc_match_table);

अटल पूर्णांक kpss_xcc_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	काष्ठा clk *clk;
	काष्ठा resource *res;
	व्योम __iomem *base;
	स्थिर अक्षर *name;

	id = of_match_device(kpss_xcc_match_table, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (id->data) अणु
		अगर (of_property_पढ़ो_string_index(pdev->dev.of_node,
						  "clock-output-names",
						  0, &name))
			वापस -ENODEV;
		base += 0x14;
	पूर्ण अन्यथा अणु
		name = "acpu_l2_aux";
		base += 0x28;
	पूर्ण

	clk = clk_रेजिस्टर_mux_table(&pdev->dev, name, aux_parents,
				     ARRAY_SIZE(aux_parents), 0, base, 0, 0x3,
				     0, aux_parent_map, शून्य);

	platक्रमm_set_drvdata(pdev, clk);

	वापस PTR_ERR_OR_ZERO(clk);
पूर्ण

अटल पूर्णांक kpss_xcc_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	clk_unरेजिस्टर_mux(platक्रमm_get_drvdata(pdev));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kpss_xcc_driver = अणु
	.probe = kpss_xcc_driver_probe,
	.हटाओ = kpss_xcc_driver_हटाओ,
	.driver = अणु
		.name = "kpss-xcc",
		.of_match_table = kpss_xcc_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(kpss_xcc_driver);

MODULE_DESCRIPTION("Krait Processor Sub System (KPSS) Clock Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:kpss-xcc");
