<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <soc/mediatek/smi.h>

#समावेश "mtk_mdp_comp.h"


व्योम mtk_mdp_comp_घड़ी_on(काष्ठा device *dev, काष्ठा mtk_mdp_comp *comp)
अणु
	पूर्णांक i, err;

	अगर (comp->larb_dev) अणु
		err = mtk_smi_larb_get(comp->larb_dev);
		अगर (err)
			dev_err(dev,
				"failed to get larb, err %d. type:%d\n",
				err, comp->type);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(comp->clk); i++) अणु
		अगर (IS_ERR(comp->clk[i]))
			जारी;
		err = clk_prepare_enable(comp->clk[i]);
		अगर (err)
			dev_err(dev,
			"failed to enable clock, err %d. type:%d i:%d\n",
				err, comp->type, i);
	पूर्ण
पूर्ण

व्योम mtk_mdp_comp_घड़ी_off(काष्ठा device *dev, काष्ठा mtk_mdp_comp *comp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(comp->clk); i++) अणु
		अगर (IS_ERR(comp->clk[i]))
			जारी;
		clk_disable_unprepare(comp->clk[i]);
	पूर्ण

	अगर (comp->larb_dev)
		mtk_smi_larb_put(comp->larb_dev);
पूर्ण

पूर्णांक mtk_mdp_comp_init(काष्ठा device *dev, काष्ठा device_node *node,
		      काष्ठा mtk_mdp_comp *comp,
		      क्रमागत mtk_mdp_comp_type comp_type)
अणु
	काष्ठा device_node *larb_node;
	काष्ठा platक्रमm_device *larb_pdev;
	पूर्णांक ret;
	पूर्णांक i;

	comp->dev_node = of_node_get(node);
	comp->type = comp_type;

	क्रम (i = 0; i < ARRAY_SIZE(comp->clk); i++) अणु
		comp->clk[i] = of_clk_get(node, i);
		अगर (IS_ERR(comp->clk[i])) अणु
			अगर (PTR_ERR(comp->clk[i]) != -EPROBE_DEFER)
				dev_err(dev, "Failed to get clock\n");
			ret = PTR_ERR(comp->clk[i]);
			जाओ put_dev;
		पूर्ण

		/* Only RDMA needs two घड़ीs */
		अगर (comp->type != MTK_MDP_RDMA)
			अवरोध;
	पूर्ण

	/* Only DMA capable components need the LARB property */
	comp->larb_dev = शून्य;
	अगर (comp->type != MTK_MDP_RDMA &&
	    comp->type != MTK_MDP_WDMA &&
	    comp->type != MTK_MDP_WROT)
		वापस 0;

	larb_node = of_parse_phandle(node, "mediatek,larb", 0);
	अगर (!larb_node) अणु
		dev_err(dev,
			"Missing mediadek,larb phandle in %pOF node\n", node);
		ret = -EINVAL;
		जाओ put_dev;
	पूर्ण

	larb_pdev = of_find_device_by_node(larb_node);
	अगर (!larb_pdev) अणु
		dev_warn(dev, "Waiting for larb device %pOF\n", larb_node);
		of_node_put(larb_node);
		ret = -EPROBE_DEFER;
		जाओ put_dev;
	पूर्ण
	of_node_put(larb_node);

	comp->larb_dev = &larb_pdev->dev;

	वापस 0;

put_dev:
	of_node_put(comp->dev_node);

	वापस ret;
पूर्ण

व्योम mtk_mdp_comp_deinit(काष्ठा device *dev, काष्ठा mtk_mdp_comp *comp)
अणु
	of_node_put(comp->dev_node);
पूर्ण
