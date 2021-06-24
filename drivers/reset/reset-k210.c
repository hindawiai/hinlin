<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <soc/canaan/k210-sysctl.h>

#समावेश <dt-bindings/reset/k210-rst.h>

#घोषणा K210_RST_MASK	0x27FFFFFF

काष्ठा k210_rst अणु
	काष्ठा regmap *map;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

अटल अंतरभूत काष्ठा k210_rst *
to_k210_rst(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा k210_rst, rcdev);
पूर्ण

अटल अंतरभूत पूर्णांक k210_rst_निश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा k210_rst *ksr = to_k210_rst(rcdev);

	वापस regmap_update_bits(ksr->map, K210_SYSCTL_PERI_RESET, BIT(id), 1);
पूर्ण

अटल अंतरभूत पूर्णांक k210_rst_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा k210_rst *ksr = to_k210_rst(rcdev);

	वापस regmap_update_bits(ksr->map, K210_SYSCTL_PERI_RESET, BIT(id), 0);
पूर्ण

अटल पूर्णांक k210_rst_reset(काष्ठा reset_controller_dev *rcdev,
			  अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;

	ret = k210_rst_निश्चित(rcdev, id);
	अगर (ret == 0) अणु
		udelay(10);
		ret = k210_rst_deनिश्चित(rcdev, id);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक k210_rst_status(काष्ठा reset_controller_dev *rcdev,
			   अचिन्हित दीर्घ id)
अणु
	काष्ठा k210_rst *ksr = to_k210_rst(rcdev);
	u32 reg, bit = BIT(id);
	पूर्णांक ret;

	ret = regmap_पढ़ो(ksr->map, K210_SYSCTL_PERI_RESET, &reg);
	अगर (ret)
		वापस ret;

	वापस reg & bit;
पूर्ण

अटल पूर्णांक k210_rst_xlate(काष्ठा reset_controller_dev *rcdev,
			  स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अचिन्हित दीर्घ id = reset_spec->args[0];

	अगर (!(BIT(id) & K210_RST_MASK))
		वापस -EINVAL;

	वापस id;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops k210_rst_ops = अणु
	.निश्चित		= k210_rst_निश्चित,
	.deनिश्चित	= k210_rst_deनिश्चित,
	.reset		= k210_rst_reset,
	.status		= k210_rst_status,
पूर्ण;

अटल पूर्णांक k210_rst_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent_np = of_get_parent(dev->of_node);
	काष्ठा k210_rst *ksr;

	dev_info(dev, "K210 reset controller\n");

	ksr = devm_kzalloc(dev, माप(*ksr), GFP_KERNEL);
	अगर (!ksr)
		वापस -ENOMEM;

	ksr->map = syscon_node_to_regmap(parent_np);
	of_node_put(parent_np);
	अगर (IS_ERR(ksr->map))
		वापस PTR_ERR(ksr->map);

	ksr->rcdev.owner = THIS_MODULE;
	ksr->rcdev.dev = dev;
	ksr->rcdev.of_node = dev->of_node;
	ksr->rcdev.ops = &k210_rst_ops;
	ksr->rcdev.nr_resets = fls(K210_RST_MASK);
	ksr->rcdev.of_reset_n_cells = 1;
	ksr->rcdev.of_xlate = k210_rst_xlate;

	वापस devm_reset_controller_रेजिस्टर(dev, &ksr->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id k210_rst_dt_ids[] = अणु
	अणु .compatible = "canaan,k210-rst" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver k210_rst_driver = अणु
	.probe	= k210_rst_probe,
	.driver = अणु
		.name		= "k210-rst",
		.of_match_table	= k210_rst_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(k210_rst_driver);
