<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>

#समावेश "clk-mtk.h"

काष्ठा mtk_reset अणु
	काष्ठा regmap *regmap;
	पूर्णांक regofs;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

अटल पूर्णांक mtk_reset_निश्चित_set_clr(काष्ठा reset_controller_dev *rcdev,
	अचिन्हित दीर्घ id)
अणु
	काष्ठा mtk_reset *data = container_of(rcdev, काष्ठा mtk_reset, rcdev);
	अचिन्हित पूर्णांक reg = data->regofs + ((id / 32) << 4);

	वापस regmap_ग_लिखो(data->regmap, reg, 1);
पूर्ण

अटल पूर्णांक mtk_reset_deनिश्चित_set_clr(काष्ठा reset_controller_dev *rcdev,
	अचिन्हित दीर्घ id)
अणु
	काष्ठा mtk_reset *data = container_of(rcdev, काष्ठा mtk_reset, rcdev);
	अचिन्हित पूर्णांक reg = data->regofs + ((id / 32) << 4) + 0x4;

	वापस regmap_ग_लिखो(data->regmap, reg, 1);
पूर्ण

अटल पूर्णांक mtk_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा mtk_reset *data = container_of(rcdev, काष्ठा mtk_reset, rcdev);

	वापस regmap_update_bits(data->regmap, data->regofs + ((id / 32) << 2),
			BIT(id % 32), ~0);
पूर्ण

अटल पूर्णांक mtk_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा mtk_reset *data = container_of(rcdev, काष्ठा mtk_reset, rcdev);

	वापस regmap_update_bits(data->regmap, data->regofs + ((id / 32) << 2),
			BIT(id % 32), 0);
पूर्ण

अटल पूर्णांक mtk_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;

	ret = mtk_reset_निश्चित(rcdev, id);
	अगर (ret)
		वापस ret;

	वापस mtk_reset_deनिश्चित(rcdev, id);
पूर्ण

अटल पूर्णांक mtk_reset_set_clr(काष्ठा reset_controller_dev *rcdev,
	अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;

	ret = mtk_reset_निश्चित_set_clr(rcdev, id);
	अगर (ret)
		वापस ret;
	वापस mtk_reset_deनिश्चित_set_clr(rcdev, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops mtk_reset_ops = अणु
	.निश्चित = mtk_reset_निश्चित,
	.deनिश्चित = mtk_reset_deनिश्चित,
	.reset = mtk_reset,
पूर्ण;

अटल स्थिर काष्ठा reset_control_ops mtk_reset_ops_set_clr = अणु
	.निश्चित = mtk_reset_निश्चित_set_clr,
	.deनिश्चित = mtk_reset_deनिश्चित_set_clr,
	.reset = mtk_reset_set_clr,
पूर्ण;

अटल व्योम mtk_रेजिस्टर_reset_controller_common(काष्ठा device_node *np,
			अचिन्हित पूर्णांक num_regs, पूर्णांक regofs,
			स्थिर काष्ठा reset_control_ops *reset_ops)
अणु
	काष्ठा mtk_reset *data;
	पूर्णांक ret;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(regmap)) अणु
		pr_err("Cannot find regmap for %pOF: %ld\n", np,
				PTR_ERR(regmap));
		वापस;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस;

	data->regmap = regmap;
	data->regofs = regofs;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = num_regs * 32;
	data->rcdev.ops = reset_ops;
	data->rcdev.of_node = np;

	ret = reset_controller_रेजिस्टर(&data->rcdev);
	अगर (ret) अणु
		pr_err("could not register reset controller: %d\n", ret);
		kमुक्त(data);
		वापस;
	पूर्ण
पूर्ण

व्योम mtk_रेजिस्टर_reset_controller(काष्ठा device_node *np,
	अचिन्हित पूर्णांक num_regs, पूर्णांक regofs)
अणु
	mtk_रेजिस्टर_reset_controller_common(np, num_regs, regofs,
		&mtk_reset_ops);
पूर्ण

व्योम mtk_रेजिस्टर_reset_controller_set_clr(काष्ठा device_node *np,
	अचिन्हित पूर्णांक num_regs, पूर्णांक regofs)
अणु
	mtk_रेजिस्टर_reset_controller_common(np, num_regs, regofs,
		&mtk_reset_ops_set_clr);
पूर्ण
