<शैली गुरु>
/*
 * Allwinner SoCs SRAM Controller Driver
 *
 * Copyright (C) 2015 Maxime Ripard
 *
 * Author: Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/soc/sunxi/sunxi_sram.h>

काष्ठा sunxi_sram_func अणु
	अक्षर	*func;
	u8	val;
	u32	reg_val;
पूर्ण;

काष्ठा sunxi_sram_data अणु
	अक्षर			*name;
	u8			reg;
	u8			offset;
	u8			width;
	काष्ठा sunxi_sram_func	*func;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा sunxi_sram_desc अणु
	काष्ठा sunxi_sram_data	data;
	bool			claimed;
पूर्ण;

#घोषणा SUNXI_SRAM_MAP(_reg_val, _val, _func)			\
	अणु							\
		.func = _func,					\
		.val = _val,					\
		.reg_val = _reg_val,				\
	पूर्ण

#घोषणा SUNXI_SRAM_DATA(_name, _reg, _off, _width, ...)		\
	अणु							\
		.name = _name,					\
		.reg = _reg,					\
		.offset = _off,					\
		.width = _width,				\
		.func = (काष्ठा sunxi_sram_func[])अणु		\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण

अटल काष्ठा sunxi_sram_desc sun4i_a10_sram_a3_a4 = अणु
	.data	= SUNXI_SRAM_DATA("A3-A4", 0x4, 0x4, 2,
				  SUNXI_SRAM_MAP(0, 0, "cpu"),
				  SUNXI_SRAM_MAP(1, 1, "emac")),
पूर्ण;

अटल काष्ठा sunxi_sram_desc sun4i_a10_sram_c1 = अणु
	.data	= SUNXI_SRAM_DATA("C1", 0x0, 0x0, 31,
				  SUNXI_SRAM_MAP(0, 0, "cpu"),
				  SUNXI_SRAM_MAP(0x7fffffff, 1, "ve")),
पूर्ण;

अटल काष्ठा sunxi_sram_desc sun4i_a10_sram_d = अणु
	.data	= SUNXI_SRAM_DATA("D", 0x4, 0x0, 1,
				  SUNXI_SRAM_MAP(0, 0, "cpu"),
				  SUNXI_SRAM_MAP(1, 1, "usb-otg")),
पूर्ण;

अटल काष्ठा sunxi_sram_desc sun50i_a64_sram_c = अणु
	.data	= SUNXI_SRAM_DATA("C", 0x4, 24, 1,
				  SUNXI_SRAM_MAP(0, 1, "cpu"),
				  SUNXI_SRAM_MAP(1, 0, "de2")),
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_sram_dt_ids[] = अणु
	अणु
		.compatible	= "allwinner,sun4i-a10-sram-a3-a4",
		.data		= &sun4i_a10_sram_a3_a4.data,
	पूर्ण,
	अणु
		.compatible	= "allwinner,sun4i-a10-sram-c1",
		.data		= &sun4i_a10_sram_c1.data,
	पूर्ण,
	अणु
		.compatible	= "allwinner,sun4i-a10-sram-d",
		.data		= &sun4i_a10_sram_d.data,
	पूर्ण,
	अणु
		.compatible	= "allwinner,sun50i-a64-sram-c",
		.data		= &sun50i_a64_sram_c.data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा device *sram_dev;
अटल LIST_HEAD(claimed_sram);
अटल DEFINE_SPINLOCK(sram_lock);
अटल व्योम __iomem *base;

अटल पूर्णांक sunxi_sram_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा device_node *sram_node, *section_node;
	स्थिर काष्ठा sunxi_sram_data *sram_data;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा sunxi_sram_func *func;
	स्थिर __be32 *sram_addr_p, *section_addr_p;
	u32 val;

	seq_माला_दो(s, "Allwinner sunXi SRAM\n");
	seq_माला_दो(s, "--------------------\n\n");

	क्रम_each_child_of_node(sram_dev->of_node, sram_node) अणु
		sram_addr_p = of_get_address(sram_node, 0, शून्य, शून्य);

		seq_म_लिखो(s, "sram@%08x\n",
			   be32_to_cpu(*sram_addr_p));

		क्रम_each_child_of_node(sram_node, section_node) अणु
			match = of_match_node(sunxi_sram_dt_ids, section_node);
			अगर (!match)
				जारी;
			sram_data = match->data;

			section_addr_p = of_get_address(section_node, 0,
							शून्य, शून्य);

			seq_म_लिखो(s, "\tsection@%04x\t(%s)\n",
				   be32_to_cpu(*section_addr_p),
				   sram_data->name);

			val = पढ़ोl(base + sram_data->reg);
			val >>= sram_data->offset;
			val &= GENMASK(sram_data->width - 1, 0);

			क्रम (func = sram_data->func; func->func; func++) अणु
				seq_म_लिखो(s, "\t\t%s%c\n", func->func,
					   func->reg_val == val ?
					   '*' : ' ');
			पूर्ण
		पूर्ण

		seq_माला_दो(s, "\n");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(sunxi_sram);

अटल अंतरभूत काष्ठा sunxi_sram_desc *to_sram_desc(स्थिर काष्ठा sunxi_sram_data *data)
अणु
	वापस container_of(data, काष्ठा sunxi_sram_desc, data);
पूर्ण

अटल स्थिर काष्ठा sunxi_sram_data *sunxi_sram_of_parse(काष्ठा device_node *node,
							 अचिन्हित पूर्णांक *reg_value)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा sunxi_sram_data *data;
	काष्ठा sunxi_sram_func *func;
	काष्ठा of_phandle_args args;
	u8 val;
	पूर्णांक ret;

	ret = of_parse_phandle_with_fixed_args(node, "allwinner,sram", 1, 0,
					       &args);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (!of_device_is_available(args.np)) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	val = args.args[0];

	match = of_match_node(sunxi_sram_dt_ids, args.np);
	अगर (!match) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	data = match->data;
	अगर (!data) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (func = data->func; func->func; func++) अणु
		अगर (val == func->val) अणु
			अगर (reg_value)
				*reg_value = func->reg_val;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!func->func) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	of_node_put(args.np);
	वापस match->data;

err:
	of_node_put(args.np);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक sunxi_sram_claim(काष्ठा device *dev)
अणु
	स्थिर काष्ठा sunxi_sram_data *sram_data;
	काष्ठा sunxi_sram_desc *sram_desc;
	अचिन्हित पूर्णांक device;
	u32 val, mask;

	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (!base)
		वापस -EPROBE_DEFER;

	अगर (!dev || !dev->of_node)
		वापस -EINVAL;

	sram_data = sunxi_sram_of_parse(dev->of_node, &device);
	अगर (IS_ERR(sram_data))
		वापस PTR_ERR(sram_data);

	sram_desc = to_sram_desc(sram_data);

	spin_lock(&sram_lock);

	अगर (sram_desc->claimed) अणु
		spin_unlock(&sram_lock);
		वापस -EBUSY;
	पूर्ण

	mask = GENMASK(sram_data->offset + sram_data->width - 1,
		       sram_data->offset);
	val = पढ़ोl(base + sram_data->reg);
	val &= ~mask;
	ग_लिखोl(val | ((device << sram_data->offset) & mask),
	       base + sram_data->reg);

	spin_unlock(&sram_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sunxi_sram_claim);

पूर्णांक sunxi_sram_release(काष्ठा device *dev)
अणु
	स्थिर काष्ठा sunxi_sram_data *sram_data;
	काष्ठा sunxi_sram_desc *sram_desc;

	अगर (!dev || !dev->of_node)
		वापस -EINVAL;

	sram_data = sunxi_sram_of_parse(dev->of_node, शून्य);
	अगर (IS_ERR(sram_data))
		वापस -EINVAL;

	sram_desc = to_sram_desc(sram_data);

	spin_lock(&sram_lock);
	sram_desc->claimed = false;
	spin_unlock(&sram_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sunxi_sram_release);

काष्ठा sunxi_sramc_variant अणु
	पूर्णांक num_emac_घड़ीs;
पूर्ण;

अटल स्थिर काष्ठा sunxi_sramc_variant sun4i_a10_sramc_variant = अणु
	/* Nothing special */
पूर्ण;

अटल स्थिर काष्ठा sunxi_sramc_variant sun8i_h3_sramc_variant = अणु
	.num_emac_घड़ीs = 1,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sramc_variant sun50i_a64_sramc_variant = अणु
	.num_emac_घड़ीs = 1,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sramc_variant sun50i_h616_sramc_variant = अणु
	.num_emac_घड़ीs = 2,
पूर्ण;

#घोषणा SUNXI_SRAM_EMAC_CLOCK_REG	0x30
अटल bool sunxi_sram_regmap_accessible_reg(काष्ठा device *dev,
					     अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा sunxi_sramc_variant *variant;

	variant = of_device_get_match_data(dev);

	अगर (reg < SUNXI_SRAM_EMAC_CLOCK_REG)
		वापस false;
	अगर (reg > SUNXI_SRAM_EMAC_CLOCK_REG + variant->num_emac_घड़ीs * 4)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा regmap_config sunxi_sram_emac_घड़ी_regmap = अणु
	.reg_bits       = 32,
	.val_bits       = 32,
	.reg_stride     = 4,
	/* last defined रेजिस्टर */
	.max_रेजिस्टर   = SUNXI_SRAM_EMAC_CLOCK_REG + 4,
	/* other devices have no business accessing other रेजिस्टरs */
	.पढ़ोable_reg	= sunxi_sram_regmap_accessible_reg,
	.ग_लिखोable_reg	= sunxi_sram_regmap_accessible_reg,
पूर्ण;

अटल पूर्णांक sunxi_sram_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा dentry *d;
	काष्ठा regmap *emac_घड़ी;
	स्थिर काष्ठा sunxi_sramc_variant *variant;

	sram_dev = &pdev->dev;

	variant = of_device_get_match_data(&pdev->dev);
	अगर (!variant)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);

	d = debugfs_create_file("sram", S_IRUGO, शून्य, शून्य,
				&sunxi_sram_fops);
	अगर (!d)
		वापस -ENOMEM;

	अगर (variant->num_emac_घड़ीs > 0) अणु
		emac_घड़ी = devm_regmap_init_mmio(&pdev->dev, base,
						   &sunxi_sram_emac_घड़ी_regmap);

		अगर (IS_ERR(emac_घड़ी))
			वापस PTR_ERR(emac_घड़ी);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sunxi_sram_dt_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-sram-controller",
		.data = &sun4i_a10_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun4i-a10-system-control",
		.data = &sun4i_a10_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun5i-a13-system-control",
		.data = &sun4i_a10_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-a23-system-control",
		.data = &sun4i_a10_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-system-control",
		.data = &sun8i_h3_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-sram-controller",
		.data = &sun50i_a64_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-system-control",
		.data = &sun50i_a64_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h5-system-control",
		.data = &sun50i_a64_sramc_variant,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h616-system-control",
		.data = &sun50i_h616_sramc_variant,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_sram_dt_match);

अटल काष्ठा platक्रमm_driver sunxi_sram_driver = अणु
	.driver = अणु
		.name		= "sunxi-sram",
		.of_match_table	= sunxi_sram_dt_match,
	पूर्ण,
	.probe	= sunxi_sram_probe,
पूर्ण;
module_platक्रमm_driver(sunxi_sram_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner sunXi SRAM Controller Driver");
MODULE_LICENSE("GPL");
