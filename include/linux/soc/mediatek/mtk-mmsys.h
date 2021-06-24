<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#अगर_अघोषित __MTK_MMSYS_H
#घोषणा __MTK_MMSYS_H

क्रमागत mtk_ddp_comp_id;
काष्ठा device;

क्रमागत mtk_ddp_comp_id अणु
	DDP_COMPONENT_AAL0,
	DDP_COMPONENT_AAL1,
	DDP_COMPONENT_BLS,
	DDP_COMPONENT_CCORR,
	DDP_COMPONENT_COLOR0,
	DDP_COMPONENT_COLOR1,
	DDP_COMPONENT_DITHER,
	DDP_COMPONENT_DPI0,
	DDP_COMPONENT_DPI1,
	DDP_COMPONENT_DSI0,
	DDP_COMPONENT_DSI1,
	DDP_COMPONENT_DSI2,
	DDP_COMPONENT_DSI3,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_OD0,
	DDP_COMPONENT_OD1,
	DDP_COMPONENT_OVL0,
	DDP_COMPONENT_OVL_2L0,
	DDP_COMPONENT_OVL_2L1,
	DDP_COMPONENT_OVL1,
	DDP_COMPONENT_PWM0,
	DDP_COMPONENT_PWM1,
	DDP_COMPONENT_PWM2,
	DDP_COMPONENT_RDMA0,
	DDP_COMPONENT_RDMA1,
	DDP_COMPONENT_RDMA2,
	DDP_COMPONENT_UFOE,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_ID_MAX,
पूर्ण;

व्योम mtk_mmsys_ddp_connect(काष्ठा device *dev,
			   क्रमागत mtk_ddp_comp_id cur,
			   क्रमागत mtk_ddp_comp_id next);

व्योम mtk_mmsys_ddp_disconnect(काष्ठा device *dev,
			      क्रमागत mtk_ddp_comp_id cur,
			      क्रमागत mtk_ddp_comp_id next);

#पूर्ण_अगर /* __MTK_MMSYS_H */
