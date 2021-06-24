<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Jungchang Tsao <jungchang.tsao@mediatek.com>
 *	   Daniel Hsiao <daniel.hsiao@mediatek.com>
 *	   Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#अगर_अघोषित _VENC_IPI_MSG_H_
#घोषणा _VENC_IPI_MSG_H_

#घोषणा AP_IPIMSG_VENC_BASE 0xC000
#घोषणा VPU_IPIMSG_VENC_BASE 0xD000

/**
 * क्रमागत venc_ipi_msg_id - message id between AP and VPU
 * (ipi stands क्रम पूर्णांकer-processor पूर्णांकerrupt)
 * @AP_IPIMSG_ENC_XXX:		AP to VPU cmd message id
 * @VPU_IPIMSG_ENC_XXX_DONE:	VPU ack AP cmd message id
 */
क्रमागत venc_ipi_msg_id अणु
	AP_IPIMSG_ENC_INIT = AP_IPIMSG_VENC_BASE,
	AP_IPIMSG_ENC_SET_PARAM,
	AP_IPIMSG_ENC_ENCODE,
	AP_IPIMSG_ENC_DEINIT,

	VPU_IPIMSG_ENC_INIT_DONE = VPU_IPIMSG_VENC_BASE,
	VPU_IPIMSG_ENC_SET_PARAM_DONE,
	VPU_IPIMSG_ENC_ENCODE_DONE,
	VPU_IPIMSG_ENC_DEINIT_DONE,
पूर्ण;

/**
 * काष्ठा venc_ap_ipi_msg_init - AP to VPU init cmd काष्ठाure
 * @msg_id:	message id (AP_IPIMSG_XXX_ENC_INIT)
 * @reserved:	reserved क्रम future use. vpu is running in 32bit. Without
 *		this reserved field, अगर kernel run in 64bit. this काष्ठा size
 *		will be dअगरferent between kernel and vpu
 * @venc_inst:	AP encoder instance
 *		(काष्ठा venc_vp8_inst/venc_h264_inst *)
 */
काष्ठा venc_ap_ipi_msg_init अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t reserved;
	uपूर्णांक64_t venc_inst;
पूर्ण;

/**
 * काष्ठा venc_ap_ipi_msg_set_param - AP to VPU set_param cmd काष्ठाure
 * @msg_id:	message id (AP_IPIMSG_XXX_ENC_SET_PARAM)
 * @vpu_inst_addr:	VPU encoder instance addr
 *			(काष्ठा venc_vp8_vsi/venc_h264_vsi *)
 * @param_id:	parameter id (venc_set_param_type)
 * @data_item:	number of items in the data array
 * @data:	data array to store the set parameters
 */
काष्ठा venc_ap_ipi_msg_set_param अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t vpu_inst_addr;
	uपूर्णांक32_t param_id;
	uपूर्णांक32_t data_item;
	uपूर्णांक32_t data[8];
पूर्ण;

काष्ठा venc_ap_ipi_msg_set_param_ext अणु
	काष्ठा venc_ap_ipi_msg_set_param base;
	uपूर्णांक32_t data_ext[24];
पूर्ण;

/**
 * काष्ठा venc_ap_ipi_msg_enc - AP to VPU enc cmd काष्ठाure
 * @msg_id:	message id (AP_IPIMSG_XXX_ENC_ENCODE)
 * @vpu_inst_addr:	VPU encoder instance addr
 *			(काष्ठा venc_vp8_vsi/venc_h264_vsi *)
 * @bs_mode:	bitstream mode क्रम h264
 *		(H264_BS_MODE_SPS/H264_BS_MODE_PPS/H264_BS_MODE_FRAME)
 * @input_addr:	poपूर्णांकer to input image buffer plane
 * @bs_addr:	poपूर्णांकer to output bit stream buffer
 * @bs_size:	bit stream buffer size
 */
काष्ठा venc_ap_ipi_msg_enc अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t vpu_inst_addr;
	uपूर्णांक32_t bs_mode;
	uपूर्णांक32_t input_addr[3];
	uपूर्णांक32_t bs_addr;
	uपूर्णांक32_t bs_size;
पूर्ण;

/**
 * काष्ठा venc_ap_ipi_msg_enc_ext - AP to SCP extended enc cmd काष्ठाure
 *
 * @base:	base msg काष्ठाure
 * @data_item:	number of items in the data array
 * @data:	data array to store the set parameters
 */
काष्ठा venc_ap_ipi_msg_enc_ext अणु
	काष्ठा venc_ap_ipi_msg_enc base;
	uपूर्णांक32_t data_item;
	uपूर्णांक32_t data[32];
पूर्ण;

/**
 * काष्ठा venc_ap_ipi_msg_deinit - AP to VPU deinit cmd काष्ठाure
 * @msg_id:	message id (AP_IPIMSG_XXX_ENC_DEINIT)
 * @vpu_inst_addr:	VPU encoder instance addr
 *			(काष्ठा venc_vp8_vsi/venc_h264_vsi *)
 */
काष्ठा venc_ap_ipi_msg_deinit अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t vpu_inst_addr;
पूर्ण;

/**
 * क्रमागत venc_ipi_msg_status - VPU ack AP cmd status
 */
क्रमागत venc_ipi_msg_status अणु
	VENC_IPI_MSG_STATUS_OK,
	VENC_IPI_MSG_STATUS_FAIL,
पूर्ण;

/**
 * काष्ठा venc_vpu_ipi_msg_common - VPU ack AP cmd common काष्ठाure
 * @msg_id:	message id (VPU_IPIMSG_XXX_DONE)
 * @status:	cmd status (venc_ipi_msg_status)
 * @venc_inst:	AP encoder instance (काष्ठा venc_vp8_inst/venc_h264_inst *)
 */
काष्ठा venc_vpu_ipi_msg_common अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t status;
	uपूर्णांक64_t venc_inst;
पूर्ण;

/**
 * काष्ठा venc_vpu_ipi_msg_init - VPU ack AP init cmd काष्ठाure
 * @msg_id:	message id (VPU_IPIMSG_XXX_ENC_SET_PARAM_DONE)
 * @status:	cmd status (venc_ipi_msg_status)
 * @venc_inst:	AP encoder instance (काष्ठा venc_vp8_inst/venc_h264_inst *)
 * @vpu_inst_addr:	VPU encoder instance addr
 *			(काष्ठा venc_vp8_vsi/venc_h264_vsi *)
 * @venc_abi_version:	ABI version of the firmware. Kernel can use it to
 *			ensure that it is compatible with the firmware.
 *			For MT8173 the value of this field is undefined and
 *			should not be used.
 */
काष्ठा venc_vpu_ipi_msg_init अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t status;
	uपूर्णांक64_t venc_inst;
	uपूर्णांक32_t vpu_inst_addr;
	uपूर्णांक32_t venc_abi_version;
पूर्ण;

/**
 * काष्ठा venc_vpu_ipi_msg_set_param - VPU ack AP set_param cmd काष्ठाure
 * @msg_id:	message id (VPU_IPIMSG_XXX_ENC_SET_PARAM_DONE)
 * @status:	cmd status (venc_ipi_msg_status)
 * @venc_inst:	AP encoder instance (काष्ठा venc_vp8_inst/venc_h264_inst *)
 * @param_id:	parameter id (venc_set_param_type)
 * @data_item:	number of items in the data array
 * @data:	data array to store the वापस result
 */
काष्ठा venc_vpu_ipi_msg_set_param अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t status;
	uपूर्णांक64_t venc_inst;
	uपूर्णांक32_t param_id;
	uपूर्णांक32_t data_item;
	uपूर्णांक32_t data[6];
पूर्ण;

/**
 * क्रमागत venc_ipi_msg_enc_state - Type of encode state
 * @VEN_IPI_MSG_ENC_STATE_FRAME:	one frame being encoded
 * @VEN_IPI_MSG_ENC_STATE_PART:		bit stream buffer full
 * @VEN_IPI_MSG_ENC_STATE_SKIP:		encoded skip frame
 * @VEN_IPI_MSG_ENC_STATE_ERROR:	encounter error
 */
क्रमागत venc_ipi_msg_enc_state अणु
	VEN_IPI_MSG_ENC_STATE_FRAME,
	VEN_IPI_MSG_ENC_STATE_PART,
	VEN_IPI_MSG_ENC_STATE_SKIP,
	VEN_IPI_MSG_ENC_STATE_ERROR,
पूर्ण;

/**
 * काष्ठा venc_vpu_ipi_msg_enc - VPU ack AP enc cmd काष्ठाure
 * @msg_id:	message id (VPU_IPIMSG_XXX_ENC_ENCODE_DONE)
 * @status:	cmd status (venc_ipi_msg_status)
 * @venc_inst:	AP encoder instance (काष्ठा venc_vp8_inst/venc_h264_inst *)
 * @state:	encode state (venc_ipi_msg_enc_state)
 * @is_key_frm:	whether the encoded frame is key frame
 * @bs_size:	encoded bitstream size
 * @reserved:	reserved क्रम future use. vpu is running in 32bit. Without
 *		this reserved field, अगर kernel run in 64bit. this काष्ठा size
 *		will be dअगरferent between kernel and vpu
 */
काष्ठा venc_vpu_ipi_msg_enc अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t status;
	uपूर्णांक64_t venc_inst;
	uपूर्णांक32_t state;
	uपूर्णांक32_t is_key_frm;
	uपूर्णांक32_t bs_size;
	uपूर्णांक32_t reserved;
पूर्ण;

/**
 * काष्ठा venc_vpu_ipi_msg_deinit - VPU ack AP deinit cmd काष्ठाure
 * @msg_id:   message id (VPU_IPIMSG_XXX_ENC_DEINIT_DONE)
 * @status:   cmd status (venc_ipi_msg_status)
 * @venc_inst:	AP encoder instance (काष्ठा venc_vp8_inst/venc_h264_inst *)
 */
काष्ठा venc_vpu_ipi_msg_deinit अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t status;
	uपूर्णांक64_t venc_inst;
पूर्ण;

#पूर्ण_अगर /* _VENC_IPI_MSG_H_ */
