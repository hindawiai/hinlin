<शैली गुरु>
/*
 * Copyright (C) 2012 Thomas Petazzoni
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * This special of_device_id is the sentinel at the end of the
 * of_device_id[] array of all irqchips. It is स्वतःmatically placed at
 * the end of the array by the linker, thanks to being part of a
 * special section.
 */
अटल स्थिर काष्ठा of_device_id
irqchip_of_match_end __used __section("__irqchip_of_table_end");

बाह्य काष्ठा of_device_id __irqchip_of_table[];

व्योम __init irqchip_init(व्योम)
अणु
	of_irq_init(__irqchip_of_table);
	acpi_probe_device_table(irqchip);
पूर्ण

पूर्णांक platक्रमm_irqchip_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *par_np = of_irq_find_parent(np);
	of_irq_init_cb_t irq_init_cb = of_device_get_match_data(&pdev->dev);

	अगर (!irq_init_cb)
		वापस -EINVAL;

	अगर (par_np == np)
		par_np = शून्य;

	/*
	 * If there's a parent पूर्णांकerrupt controller and  none of the parent irq
	 * करोमुख्यs have been रेजिस्टरed, that means the parent पूर्णांकerrupt
	 * controller has not been initialized yet.  it's not समय क्रम this
	 * पूर्णांकerrupt controller to initialize. So, defer probe of this
	 * पूर्णांकerrupt controller. The actual initialization callback of this
	 * पूर्णांकerrupt controller can check क्रम specअगरic करोमुख्यs as necessary.
	 */
	अगर (par_np && !irq_find_matching_host(par_np, DOMAIN_BUS_ANY))
		वापस -EPROBE_DEFER;

	वापस irq_init_cb(np, par_np);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_irqchip_probe);
