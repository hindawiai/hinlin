<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/export.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/dma-mapping.h>

#समावेश <lantiq_soc.h>

अटल अचिन्हित पूर्णांक *cp1_base;

अचिन्हित पूर्णांक *ltq_get_cp1_base(व्योम)
अणु
	अगर (!cp1_base)
		panic("no cp1 base was set\n");

	वापस cp1_base;
पूर्ण
EXPORT_SYMBOL(ltq_get_cp1_base);

अटल पूर्णांक vmmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
#घोषणा CP1_SIZE       (1 << 20)
	पूर्णांक gpio_count;
	dma_addr_t dma;

	cp1_base =
		(व्योम *) CPHYSADDR(dma_alloc_coherent(&pdev->dev, CP1_SIZE,
						    &dma, GFP_KERNEL));

	gpio_count = of_gpio_count(pdev->dev.of_node);
	जबतक (gpio_count > 0) अणु
		क्रमागत of_gpio_flags flags;
		पूर्णांक gpio = of_get_gpio_flags(pdev->dev.of_node,
					     --gpio_count, &flags);
		अगर (gpio_request(gpio, "vmmc-relay"))
			जारी;
		dev_info(&pdev->dev, "requested GPIO %d\n", gpio);
		gpio_direction_output(gpio,
				      (flags & OF_GPIO_ACTIVE_LOW) ? (0) : (1));
	पूर्ण

	dev_info(&pdev->dev, "reserved %dMB at 0x%p", CP1_SIZE >> 20, cp1_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vmmc_match[] = अणु
	अणु .compatible = "lantiq,vmmc-xway" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver vmmc_driver = अणु
	.probe = vmmc_probe,
	.driver = अणु
		.name = "lantiq,vmmc",
		.of_match_table = vmmc_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(vmmc_driver);
