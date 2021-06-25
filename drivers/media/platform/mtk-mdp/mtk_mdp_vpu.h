<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#अगर_अघोषित __MTK_MDP_VPU_H__
#घोषणा __MTK_MDP_VPU_H__

#समावेश "mtk_mdp_ipi.h"


/**
 * काष्ठा mtk_mdp_vpu - VPU instance क्रम MDP
 * @pdev	: poपूर्णांकer to the VPU platक्रमm device
 * @inst_addr	: VPU MDP instance address
 * @failure	: VPU execution result status
 * @vsi		: VPU shared inक्रमmation
 */
काष्ठा mtk_mdp_vpu अणु
	काष्ठा platक्रमm_device	*pdev;
	uपूर्णांक32_t		inst_addr;
	पूर्णांक32_t			failure;
	काष्ठा mdp_process_vsi	*vsi;
पूर्ण;

पूर्णांक mtk_mdp_vpu_रेजिस्टर(काष्ठा platक्रमm_device *pdev);
पूर्णांक mtk_mdp_vpu_init(काष्ठा mtk_mdp_vpu *vpu);
पूर्णांक mtk_mdp_vpu_deinit(काष्ठा mtk_mdp_vpu *vpu);
पूर्णांक mtk_mdp_vpu_process(काष्ठा mtk_mdp_vpu *vpu);

#पूर्ण_अगर /* __MTK_MDP_VPU_H__ */
