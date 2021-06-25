<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PoChun Lin <pochun.lin@mediatek.com>
 */

#अगर_अघोषित _VENC_VPU_IF_H_
#घोषणा _VENC_VPU_IF_H_

#समावेश "mtk_vcodec_fw.h"
#समावेश "venc_drv_if.h"

/*
 * काष्ठा venc_vpu_inst - encoder VPU driver instance
 * @wq_hd: रुको queue used क्रम vpu cmd trigger then रुको vpu पूर्णांकerrupt करोne
 * @संकेतed: flag used क्रम checking vpu पूर्णांकerrupt करोne
 * @failure: flag to show vpu cmd succeeds or not
 * @state: क्रमागत venc_ipi_msg_enc_state
 * @bs_size: bitstream size क्रम skip frame हाल usage
 * @is_key_frm: key frame flag
 * @inst_addr: VPU instance addr
 * @vsi: driver काष्ठाure allocated by VPU side and shared to AP side क्रम
 *	 control and info share
 * @id: the id of पूर्णांकer-processor पूर्णांकerrupt
 * @ctx: context क्रम v4l2 layer पूर्णांकegration
 * @dev: device क्रम v4l2 layer पूर्णांकegration
 */
काष्ठा venc_vpu_inst अणु
	रुको_queue_head_t wq_hd;
	पूर्णांक संकेतed;
	पूर्णांक failure;
	पूर्णांक state;
	पूर्णांक bs_size;
	पूर्णांक is_key_frm;
	अचिन्हित पूर्णांक inst_addr;
	व्योम *vsi;
	पूर्णांक id;
	काष्ठा mtk_vcodec_ctx *ctx;
पूर्ण;

पूर्णांक vpu_enc_init(काष्ठा venc_vpu_inst *vpu);
पूर्णांक vpu_enc_set_param(काष्ठा venc_vpu_inst *vpu,
		      क्रमागत venc_set_param_type id,
		      काष्ठा venc_enc_param *param);
पूर्णांक vpu_enc_encode(काष्ठा venc_vpu_inst *vpu, अचिन्हित पूर्णांक bs_mode,
		   काष्ठा venc_frm_buf *frm_buf,
		   काष्ठा mtk_vcodec_mem *bs_buf,
		   अचिन्हित पूर्णांक *bs_size,
		   काष्ठा venc_frame_info *frame_info);
पूर्णांक vpu_enc_deinit(काष्ठा venc_vpu_inst *vpu);

#पूर्ण_अगर
