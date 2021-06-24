<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 */

#अगर_अघोषित _VDEC_VPU_IF_H_
#घोषणा _VDEC_VPU_IF_H_

#समावेश "mtk_vcodec_fw.h"

काष्ठा mtk_vcodec_ctx;

/**
 * काष्ठा vdec_vpu_inst - VPU instance क्रम video codec
 * @id          : ipi msg id क्रम each decoder
 * @vsi         : driver काष्ठाure allocated by VPU side and shared to AP side
 *                क्रम control and info share
 * @failure     : VPU execution result status, 0: success, others: fail
 * @inst_addr	: VPU decoder instance address
 * @संकेतed    : 1 - Host has received ack message from VPU, 0 - not received
 * @ctx         : context क्रम v4l2 layer पूर्णांकegration
 * @dev		: platक्रमm device of VPU
 * @wq          : रुको queue to रुको VPU message ack
 * @handler     : ipi handler क्रम each decoder
 */
काष्ठा vdec_vpu_inst अणु
	पूर्णांक id;
	व्योम *vsi;
	पूर्णांक32_t failure;
	uपूर्णांक32_t inst_addr;
	अचिन्हित पूर्णांक संकेतed;
	काष्ठा mtk_vcodec_ctx *ctx;
	रुको_queue_head_t wq;
	mtk_vcodec_ipi_handler handler;
पूर्ण;

/**
 * vpu_dec_init - init decoder instance and allocate required resource in VPU.
 *
 * @vpu: instance क्रम vdec_vpu_inst
 */
पूर्णांक vpu_dec_init(काष्ठा vdec_vpu_inst *vpu);

/**
 * vpu_dec_start - start decoding, basically the function will be invoked once
 *                 every frame.
 *
 * @vpu : instance क्रम vdec_vpu_inst
 * @data: meta data to pass bitstream info to VPU decoder
 * @len : meta data length
 */
पूर्णांक vpu_dec_start(काष्ठा vdec_vpu_inst *vpu, uपूर्णांक32_t *data, अचिन्हित पूर्णांक len);

/**
 * vpu_dec_end - end decoding, basically the function will be invoked once
 *               when HW decoding करोne पूर्णांकerrupt received successfully. The
 *               decoder in VPU will जारी to करो reference frame management
 *               and check अगर there is a new decoded frame available to display.
 *
 * @vpu : instance क्रम vdec_vpu_inst
 */
पूर्णांक vpu_dec_end(काष्ठा vdec_vpu_inst *vpu);

/**
 * vpu_dec_deinit - deinit decoder instance and resource मुक्तd in VPU.
 *
 * @vpu: instance क्रम vdec_vpu_inst
 */
पूर्णांक vpu_dec_deinit(काष्ठा vdec_vpu_inst *vpu);

/**
 * vpu_dec_reset - reset decoder, use क्रम flush decoder when end of stream or
 *                 seek. Reमुख्यig non displayed frame will be pushed to display.
 *
 * @vpu: instance क्रम vdec_vpu_inst
 */
पूर्णांक vpu_dec_reset(काष्ठा vdec_vpu_inst *vpu);

#पूर्ण_अगर
