<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#अगर_अघोषित __MTK_MDP_COMP_H__
#घोषणा __MTK_MDP_COMP_H__

/**
 * क्रमागत mtk_mdp_comp_type - the MDP component
 * @MTK_MDP_RDMA:	Read DMA
 * @MTK_MDP_RSZ:	Riszer
 * @MTK_MDP_WDMA:	Write DMA
 * @MTK_MDP_WROT:	Write DMA with rotation
 */
क्रमागत mtk_mdp_comp_type अणु
	MTK_MDP_RDMA,
	MTK_MDP_RSZ,
	MTK_MDP_WDMA,
	MTK_MDP_WROT,
पूर्ण;

/**
 * काष्ठा mtk_mdp_comp - the MDP's function component data
 * @node:	list node to track sibing MDP components
 * @dev_node:	component device node
 * @clk:	घड़ीs required क्रम component
 * @larb_dev:	SMI device required क्रम component
 * @type:	component type
 */
काष्ठा mtk_mdp_comp अणु
	काष्ठा list_head	node;
	काष्ठा device_node	*dev_node;
	काष्ठा clk		*clk[2];
	काष्ठा device		*larb_dev;
	क्रमागत mtk_mdp_comp_type	type;
पूर्ण;

पूर्णांक mtk_mdp_comp_init(काष्ठा device *dev, काष्ठा device_node *node,
		      काष्ठा mtk_mdp_comp *comp,
		      क्रमागत mtk_mdp_comp_type comp_type);
व्योम mtk_mdp_comp_deinit(काष्ठा device *dev, काष्ठा mtk_mdp_comp *comp);
व्योम mtk_mdp_comp_घड़ी_on(काष्ठा device *dev, काष्ठा mtk_mdp_comp *comp);
व्योम mtk_mdp_comp_घड़ी_off(काष्ठा device *dev, काष्ठा mtk_mdp_comp *comp);


#पूर्ण_अगर /* __MTK_MDP_COMP_H__ */
