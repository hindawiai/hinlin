<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#अगर_अघोषित __MTK_MDP_IPI_H__
#घोषणा __MTK_MDP_IPI_H__

#घोषणा MTK_MDP_MAX_NUM_PLANE		3

क्रमागत mdp_ipi_msgid अणु
	AP_MDP_INIT		= 0xd000,
	AP_MDP_DEINIT		= 0xd001,
	AP_MDP_PROCESS		= 0xd002,

	VPU_MDP_INIT_ACK	= 0xe000,
	VPU_MDP_DEINIT_ACK	= 0xe001,
	VPU_MDP_PROCESS_ACK	= 0xe002
पूर्ण;

#आशय pack(push, 4)

/**
 * काष्ठा mdp_ipi_init - क्रम AP_MDP_INIT
 * @msg_id   : AP_MDP_INIT
 * @ipi_id   : IPI_MDP
 * @ap_inst  : AP mtk_mdp_vpu address
 */
काष्ठा mdp_ipi_init अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t ipi_id;
	uपूर्णांक64_t ap_inst;
पूर्ण;

/**
 * काष्ठा mdp_ipi_comm - क्रम AP_MDP_PROCESS, AP_MDP_DEINIT
 * @msg_id        : AP_MDP_PROCESS, AP_MDP_DEINIT
 * @ipi_id        : IPI_MDP
 * @ap_inst       : AP mtk_mdp_vpu address
 * @vpu_inst_addr : VPU MDP instance address
 */
काष्ठा mdp_ipi_comm अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t ipi_id;
	uपूर्णांक64_t ap_inst;
	uपूर्णांक32_t vpu_inst_addr;
पूर्ण;

/**
 * काष्ठा mdp_ipi_comm_ack - क्रम VPU_MDP_DEINIT_ACK, VPU_MDP_PROCESS_ACK
 * @msg_id        : VPU_MDP_DEINIT_ACK, VPU_MDP_PROCESS_ACK
 * @ipi_id        : IPI_MDP
 * @ap_inst       : AP mtk_mdp_vpu address
 * @vpu_inst_addr : VPU MDP instance address
 * @status        : VPU exeuction result
 */
काष्ठा mdp_ipi_comm_ack अणु
	uपूर्णांक32_t msg_id;
	uपूर्णांक32_t ipi_id;
	uपूर्णांक64_t ap_inst;
	uपूर्णांक32_t vpu_inst_addr;
	पूर्णांक32_t status;
पूर्ण;

/**
 * काष्ठा mdp_config - configured क्रम source/destination image
 * @x        : left
 * @y        : top
 * @w        : width
 * @h        : height
 * @w_stride : bytes in horizontal
 * @h_stride : bytes in vertical
 * @crop_x   : cropped left
 * @crop_y   : cropped top
 * @crop_w   : cropped width
 * @crop_h   : cropped height
 * @क्रमmat   : color क्रमmat
 */
काष्ठा mdp_config अणु
	पूर्णांक32_t x;
	पूर्णांक32_t y;
	पूर्णांक32_t w;
	पूर्णांक32_t h;
	पूर्णांक32_t w_stride;
	पूर्णांक32_t h_stride;
	पूर्णांक32_t crop_x;
	पूर्णांक32_t crop_y;
	पूर्णांक32_t crop_w;
	पूर्णांक32_t crop_h;
	पूर्णांक32_t क्रमmat;
पूर्ण;

काष्ठा mdp_buffer अणु
	uपूर्णांक64_t addr_mva[MTK_MDP_MAX_NUM_PLANE];
	पूर्णांक32_t plane_size[MTK_MDP_MAX_NUM_PLANE];
	पूर्णांक32_t plane_num;
पूर्ण;

काष्ठा mdp_config_misc अणु
	पूर्णांक32_t orientation; /* 0, 90, 180, 270 */
	पूर्णांक32_t hflip; /* 1 will enable the flip */
	पूर्णांक32_t vflip; /* 1 will enable the flip */
	पूर्णांक32_t alpha; /* global alpha */
पूर्ण;

काष्ठा mdp_process_vsi अणु
	काष्ठा mdp_config src_config;
	काष्ठा mdp_buffer src_buffer;
	काष्ठा mdp_config dst_config;
	काष्ठा mdp_buffer dst_buffer;
	काष्ठा mdp_config_misc misc;
पूर्ण;

#आशय pack(pop)

#पूर्ण_अगर /* __MTK_MDP_IPI_H__ */
