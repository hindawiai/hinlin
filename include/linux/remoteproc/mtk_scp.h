<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#अगर_अघोषित _MTK_SCP_H
#घोषणा _MTK_SCP_H

#समावेश <linux/platक्रमm_device.h>

प्रकार व्योम (*scp_ipi_handler_t) (व्योम *data,
				   अचिन्हित पूर्णांक len,
				   व्योम *priv);
काष्ठा mtk_scp;

/**
 * क्रमागत ipi_id - the id of पूर्णांकer-processor पूर्णांकerrupt
 *
 * @SCP_IPI_INIT:	 The पूर्णांकerrupt from scp is to notfiy kernel
 *			 SCP initialization completed.
 *			 IPI_SCP_INIT is sent from SCP when firmware is
 *			 loaded. AP करोesn't need to send IPI_SCP_INIT
 *			 command to SCP.
 *			 For other IPI below, AP should send the request
 *			 to SCP to trigger the पूर्णांकerrupt.
 * @SCP_IPI_MAX:	 The maximum IPI number
 */

क्रमागत scp_ipi_id अणु
	SCP_IPI_INIT = 0,
	SCP_IPI_VDEC_H264,
	SCP_IPI_VDEC_VP8,
	SCP_IPI_VDEC_VP9,
	SCP_IPI_VENC_H264,
	SCP_IPI_VENC_VP8,
	SCP_IPI_MDP_INIT,
	SCP_IPI_MDP_DEINIT,
	SCP_IPI_MDP_FRAME,
	SCP_IPI_DIP,
	SCP_IPI_ISP_CMD,
	SCP_IPI_ISP_FRAME,
	SCP_IPI_FD_CMD,
	SCP_IPI_CROS_HOST_CMD,
	SCP_IPI_NS_SERVICE = 0xFF,
	SCP_IPI_MAX = 0x100,
पूर्ण;

काष्ठा mtk_scp *scp_get(काष्ठा platक्रमm_device *pdev);
व्योम scp_put(काष्ठा mtk_scp *scp);

काष्ठा device *scp_get_device(काष्ठा mtk_scp *scp);
काष्ठा rproc *scp_get_rproc(काष्ठा mtk_scp *scp);

पूर्णांक scp_ipi_रेजिस्टर(काष्ठा mtk_scp *scp, u32 id, scp_ipi_handler_t handler,
		     व्योम *priv);
व्योम scp_ipi_unरेजिस्टर(काष्ठा mtk_scp *scp, u32 id);

पूर्णांक scp_ipi_send(काष्ठा mtk_scp *scp, u32 id, व्योम *buf, अचिन्हित पूर्णांक len,
		 अचिन्हित पूर्णांक रुको);

अचिन्हित पूर्णांक scp_get_vdec_hw_capa(काष्ठा mtk_scp *scp);
अचिन्हित पूर्णांक scp_get_venc_hw_capa(काष्ठा mtk_scp *scp);

व्योम *scp_mapping_dm_addr(काष्ठा mtk_scp *scp, u32 mem_addr);

#पूर्ण_अगर /* _MTK_SCP_H */
