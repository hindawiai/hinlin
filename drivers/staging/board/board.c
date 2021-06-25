<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Magnus Damm
 * Copyright (C) 2015 Glider bvba
 */

#घोषणा pr_fmt(fmt)	"board_staging: "  fmt

#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>

#समावेश "board.h"

अटल काष्ठा device_node *irqc_node __initdata;
अटल अचिन्हित पूर्णांक irqc_base __initdata;

अटल bool find_by_address(u64 base_address)
अणु
	काष्ठा device_node *dn = of_find_all_nodes(शून्य);
	काष्ठा resource res;

	जबतक (dn) अणु
		अगर (!of_address_to_resource(dn, 0, &res)) अणु
			अगर (res.start == base_address) अणु
				of_node_put(dn);
				वापस true;
			पूर्ण
		पूर्ण
		dn = of_find_all_nodes(dn);
	पूर्ण

	वापस false;
पूर्ण

bool __init board_staging_dt_node_available(स्थिर काष्ठा resource *resource,
					    अचिन्हित पूर्णांक num_resources)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_resources; i++) अणु
		स्थिर काष्ठा resource *r = resource + i;

		अगर (resource_type(r) == IORESOURCE_MEM)
			अगर (find_by_address(r->start))
				वापस true; /* DT node available */
	पूर्ण

	वापस false; /* Nothing found */
पूर्ण

पूर्णांक __init board_staging_gic_setup_xlate(स्थिर अक्षर *gic_match,
					 अचिन्हित पूर्णांक base)
अणु
	WARN_ON(irqc_node);

	irqc_node = of_find_compatible_node(शून्य, शून्य, gic_match);

	WARN_ON(!irqc_node);
	अगर (!irqc_node)
		वापस -ENOENT;

	irqc_base = base;
	वापस 0;
पूर्ण

अटल व्योम __init gic_fixup_resource(काष्ठा resource *res)
अणु
	काष्ठा of_phandle_args irq_data;
	अचिन्हित पूर्णांक hwirq = res->start;
	अचिन्हित पूर्णांक virq;

	अगर (resource_type(res) != IORESOURCE_IRQ || !irqc_node)
		वापस;

	irq_data.np = irqc_node;
	irq_data.args_count = 3;
	irq_data.args[0] = 0;
	irq_data.args[1] = hwirq - irqc_base;
	चयन (res->flags &
		(IORESOURCE_IRQ_LOWEDGE | IORESOURCE_IRQ_HIGHEDGE |
		 IORESOURCE_IRQ_LOWLEVEL | IORESOURCE_IRQ_HIGHLEVEL)) अणु
	हाल IORESOURCE_IRQ_LOWEDGE:
		irq_data.args[2] = IRQ_TYPE_EDGE_FALLING;
		अवरोध;
	हाल IORESOURCE_IRQ_HIGHEDGE:
		irq_data.args[2] = IRQ_TYPE_EDGE_RISING;
		अवरोध;
	हाल IORESOURCE_IRQ_LOWLEVEL:
		irq_data.args[2] = IRQ_TYPE_LEVEL_LOW;
		अवरोध;
	हाल IORESOURCE_IRQ_HIGHLEVEL:
	शेष:
		irq_data.args[2] = IRQ_TYPE_LEVEL_HIGH;
		अवरोध;
	पूर्ण

	virq = irq_create_of_mapping(&irq_data);
	अगर (WARN_ON(!virq))
		वापस;

	pr_debug("hwirq %u -> virq %u\n", hwirq, virq);
	res->start = virq;
पूर्ण

व्योम __init board_staging_gic_fixup_resources(काष्ठा resource *res,
					      अचिन्हित पूर्णांक nres)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nres; i++)
		gic_fixup_resource(&res[i]);
पूर्ण

पूर्णांक __init board_staging_रेजिस्टर_घड़ी(स्थिर काष्ठा board_staging_clk *bsc)
अणु
	पूर्णांक error;

	pr_debug("Aliasing clock %s for con_id %s dev_id %s\n", bsc->clk,
		 bsc->con_id, bsc->dev_id);
	error = clk_add_alias(bsc->con_id, bsc->dev_id, bsc->clk, शून्य);
	अगर (error)
		pr_err("Failed to alias clock %s (%d)\n", bsc->clk, error);

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_PM_GENERIC_DOMAINS_OF
अटल पूर्णांक board_staging_add_dev_करोमुख्य(काष्ठा platक्रमm_device *pdev,
					स्थिर अक्षर *करोमुख्य)
अणु
	काष्ठा of_phandle_args pd_args;
	काष्ठा device_node *np;

	np = of_find_node_by_path(करोमुख्य);
	अगर (!np) अणु
		pr_err("Cannot find domain node %s\n", करोमुख्य);
		वापस -ENOENT;
	पूर्ण

	pd_args.np = np;
	pd_args.args_count = 0;

	वापस of_genpd_add_device(&pd_args, &pdev->dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक board_staging_add_dev_करोमुख्य(काष्ठा platक्रमm_device *pdev,
					       स्थिर अक्षर *करोमुख्य)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक __init board_staging_रेजिस्टर_device(स्थिर काष्ठा board_staging_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = dev->pdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	pr_debug("Trying to register device %s\n", pdev->name);
	अगर (board_staging_dt_node_available(pdev->resource,
					    pdev->num_resources)) अणु
		pr_warn("Skipping %s, already in DT\n", pdev->name);
		वापस -EEXIST;
	पूर्ण

	board_staging_gic_fixup_resources(pdev->resource, pdev->num_resources);

	क्रम (i = 0; i < dev->nघड़ीs; i++)
		board_staging_रेजिस्टर_घड़ी(&dev->घड़ीs[i]);

	अगर (dev->करोमुख्य)
		board_staging_add_dev_करोमुख्य(pdev, dev->करोमुख्य);

	error = platक्रमm_device_रेजिस्टर(pdev);
	अगर (error) अणु
		pr_err("Failed to register device %s (%d)\n", pdev->name,
		       error);
		वापस error;
	पूर्ण

	वापस error;
पूर्ण

व्योम __init board_staging_रेजिस्टर_devices(स्थिर काष्ठा board_staging_dev *devs,
					   अचिन्हित पूर्णांक ndevs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ndevs; i++)
		board_staging_रेजिस्टर_device(&devs[i]);
पूर्ण
