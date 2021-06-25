<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 */

#अगर_अघोषित _VDEC_IPI_MSG_H_
#घोषणा _VDEC_IPI_MSG_H_

/**
 * क्रमागत vdec_ipi_msgid - message id between AP and VPU
 * @AP_IPIMSG_XXX	: AP to VPU cmd message id
 * @VPU_IPIMSG_XXX_ACK	: VPU ack AP cmd message id
 */
क्रमागत vdec_ipi_msgid अणु
	AP_IPIMSG_DEC_INIT = 0xA000,
	AP_IPIMSG_DEC_START = 0xA001,
	AP_IPIMSG_DEC_END = 0xA002,
	AP_IPIMSG_DEC_DEINIT = 0xA003,
	AP_IPIMSG_DEC_RESET = 0xA004,

	VPU_IPIMSG_DEC_INIT_ACK = 0xB000,
	VPU_IPIMSG_DEC_START_ACK = 0xB001,
	VPU_IPIMSG_DEC_END_ACK = 0xB002,
	VPU_IPIMSG_DEC_DEINIT_ACK = 0xB003,
	VPU_IPIMSG_DEC_RESET_ACK = 0xB004,
पूर्ण;

/**
 * काष्ठा vdec_ap_ipi_cmd - generic AP to VPU ipi command क्रमmat
 * @msg_id	: vdec_ipi_msgid
 * @vpu_inst_addr	: VPU decoder instance address
 */
काष्ठा vdec_ap_ipi_cmd अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t vpu_inst_addr;
पूर्ण;

/**
 * काष्ठा vdec_vpu_ipi_ack - generic VPU to AP ipi command क्रमmat
 * @msg_id	: vdec_ipi_msgid
 * @status	: VPU exeuction result
 * @ap_inst_addr	: AP video decoder instance address
 */
काष्ठा vdec_vpu_ipi_ack अणु
	uपूर्णांक32_t msg_id;
	पूर्णांक32_t status;
	uपूर्णांक64_t ap_inst_addr;
पूर्ण;

/**
 * काष्ठा vdec_ap_ipi_init - क्रम AP_IPIMSG_DEC_INIT
 * @msg_id	: AP_IPIMSG_DEC_INIT
 * @reserved	: Reserved field
 * @ap_inst_addr	: AP video decoder instance address
 */
काष्ठा vdec_ap_ipi_init अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t reserved;
	uपूर्णांक64_t ap_inst_addr;
पूर्ण;

/**
 * काष्ठा vdec_ap_ipi_dec_start - क्रम AP_IPIMSG_DEC_START
 * @msg_id	: AP_IPIMSG_DEC_START
 * @vpu_inst_addr	: VPU decoder instance address
 * @data	: Header info
 *	H264 decoder [0]:buf_sz [1]:nal_start
 *	VP8 decoder  [0]:width/height
 *	VP9 decoder  [0]:profile, [1][2] width/height
 * @reserved	: Reserved field
 */
काष्ठा vdec_ap_ipi_dec_start अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t vpu_inst_addr;
	uपूर्णांक32_t data[3];
	uपूर्णांक32_t reserved;
पूर्ण;

/**
 * काष्ठा vdec_vpu_ipi_init_ack - क्रम VPU_IPIMSG_DEC_INIT_ACK
 * @msg_id	: VPU_IPIMSG_DEC_INIT_ACK
 * @status	: VPU exeuction result
 * @ap_inst_addr	: AP vcodec_vpu_inst instance address
 * @vpu_inst_addr	: VPU decoder instance address
 */
काष्ठा vdec_vpu_ipi_init_ack अणु
	uपूर्णांक32_t msg_id;
	पूर्णांक32_t status;
	uपूर्णांक64_t ap_inst_addr;
	uपूर्णांक32_t vpu_inst_addr;
पूर्ण;

#पूर्ण_अगर
