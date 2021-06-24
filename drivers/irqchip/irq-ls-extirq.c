<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt) "irq-ls-extirq: " fmt

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा MAXIRQ 12
#घोषणा LS1021A_SCFGREVCR 0x200

काष्ठा ls_extirq_data अणु
	काष्ठा regmap		*syscon;
	u32			पूर्णांकpcr;
	bool			is_ls1021a_or_ls1043a;
	u32			nirq;
	काष्ठा irq_fwspec	map[MAXIRQ];
पूर्ण;

अटल पूर्णांक
ls_extirq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा ls_extirq_data *priv = data->chip_data;
	irq_hw_number_t hwirq = data->hwirq;
	u32 value, mask;

	अगर (priv->is_ls1021a_or_ls1043a)
		mask = 1U << (31 - hwirq);
	अन्यथा
		mask = 1U << hwirq;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_LOW:
		type = IRQ_TYPE_LEVEL_HIGH;
		value = mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		type = IRQ_TYPE_EDGE_RISING;
		value = mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_EDGE_RISING:
		value = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(priv->syscon, priv->पूर्णांकpcr, mask, value);

	वापस irq_chip_set_type_parent(data, type);
पूर्ण

अटल काष्ठा irq_chip ls_extirq_chip = अणु
	.name			= "ls-extirq",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_type		= ls_extirq_set_type,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.flags                  = IRQCHIP_SET_TYPE_MASKED | IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक
ls_extirq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
		       अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा ls_extirq_data *priv = करोमुख्य->host_data;
	काष्ठा irq_fwspec *fwspec = arg;
	irq_hw_number_t hwirq;

	अगर (fwspec->param_count != 2)
		वापस -EINVAL;

	hwirq = fwspec->param[0];
	अगर (hwirq >= priv->nirq)
		वापस -EINVAL;

	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq, &ls_extirq_chip,
				      priv);

	वापस irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &priv->map[hwirq]);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops extirq_करोमुख्य_ops = अणु
	.xlate		= irq_करोमुख्य_xlate_twocell,
	.alloc		= ls_extirq_करोमुख्य_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_common,
पूर्ण;

अटल पूर्णांक
ls_extirq_parse_map(काष्ठा ls_extirq_data *priv, काष्ठा device_node *node)
अणु
	स्थिर __be32 *map;
	u32 mapsize;
	पूर्णांक ret;

	map = of_get_property(node, "interrupt-map", &mapsize);
	अगर (!map)
		वापस -ENOENT;
	अगर (mapsize % माप(*map))
		वापस -EINVAL;
	mapsize /= माप(*map);

	जबतक (mapsize) अणु
		काष्ठा device_node *ipar;
		u32 hwirq, पूर्णांकsize, j;

		अगर (mapsize < 3)
			वापस -EINVAL;
		hwirq = be32_to_cpup(map);
		अगर (hwirq >= MAXIRQ)
			वापस -EINVAL;
		priv->nirq = max(priv->nirq, hwirq + 1);

		ipar = of_find_node_by_phandle(be32_to_cpup(map + 2));
		map += 3;
		mapsize -= 3;
		अगर (!ipar)
			वापस -EINVAL;
		priv->map[hwirq].fwnode = &ipar->fwnode;
		ret = of_property_पढ़ो_u32(ipar, "#interrupt-cells", &पूर्णांकsize);
		अगर (ret)
			वापस ret;

		अगर (पूर्णांकsize > mapsize)
			वापस -EINVAL;

		priv->map[hwirq].param_count = पूर्णांकsize;
		क्रम (j = 0; j < पूर्णांकsize; ++j)
			priv->map[hwirq].param[j] = be32_to_cpup(map++);
		mapsize -= पूर्णांकsize;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init
ls_extirq_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु

	काष्ठा irq_करोमुख्य *करोमुख्य, *parent_करोमुख्य;
	काष्ठा ls_extirq_data *priv;
	पूर्णांक ret;

	parent_करोमुख्य = irq_find_host(parent);
	अगर (!parent_करोमुख्य) अणु
		pr_err("Cannot find parent domain\n");
		वापस -ENODEV;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->syscon = syscon_node_to_regmap(node->parent);
	अगर (IS_ERR(priv->syscon)) अणु
		ret = PTR_ERR(priv->syscon);
		pr_err("Failed to lookup parent regmap\n");
		जाओ out;
	पूर्ण
	ret = of_property_पढ़ो_u32(node, "reg", &priv->पूर्णांकpcr);
	अगर (ret) अणु
		pr_err("Missing INTPCR offset value\n");
		जाओ out;
	पूर्ण

	ret = ls_extirq_parse_map(priv, node);
	अगर (ret)
		जाओ out;

	priv->is_ls1021a_or_ls1043a = of_device_is_compatible(node, "fsl,ls1021a-extirq") ||
				      of_device_is_compatible(node, "fsl,ls1043a-extirq");

	करोमुख्य = irq_करोमुख्य_add_hierarchy(parent_करोमुख्य, 0, priv->nirq, node,
					  &extirq_करोमुख्य_ops, priv);
	अगर (!करोमुख्य)
		ret = -ENOMEM;

out:
	अगर (ret)
		kमुक्त(priv);
	वापस ret;
पूर्ण

IRQCHIP_DECLARE(ls1021a_extirq, "fsl,ls1021a-extirq", ls_extirq_of_init);
IRQCHIP_DECLARE(ls1043a_extirq, "fsl,ls1043a-extirq", ls_extirq_of_init);
IRQCHIP_DECLARE(ls1088a_extirq, "fsl,ls1088a-extirq", ls_extirq_of_init);
