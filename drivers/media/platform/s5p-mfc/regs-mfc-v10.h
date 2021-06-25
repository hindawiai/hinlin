<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 *     http://www.samsung.com/
 *
 * Register definition file क्रम Samsung MFC V10.x Interface (FIMV) driver
 *
 */

#अगर_अघोषित _REGS_MFC_V10_H
#घोषणा _REGS_MFC_V10_H

#समावेश <linux/sizes.h>
#समावेश "regs-mfc-v8.h"

/* MFCv10 रेजिस्टर definitions*/
#घोषणा S5P_FIMV_MFC_CLOCK_OFF_V10			0x7120
#घोषणा S5P_FIMV_MFC_STATE_V10				0x7124
#घोषणा S5P_FIMV_D_STATIC_BUFFER_ADDR_V10		0xF570
#घोषणा S5P_FIMV_D_STATIC_BUFFER_SIZE_V10		0xF574
#घोषणा S5P_FIMV_E_NUM_T_LAYER_V10			0xFBAC
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER0_V10		0xFBB0
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER1_V10		0xFBB4
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER2_V10		0xFBB8
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER3_V10		0xFBBC
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER4_V10		0xFBC0
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER5_V10		0xFBC4
#घोषणा S5P_FIMV_E_HIERARCHICAL_QP_LAYER6_V10		0xFBC8
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER0_V10	0xFD18
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER1_V10	0xFD1C
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER2_V10	0xFD20
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER3_V10	0xFD24
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER4_V10	0xFD28
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER5_V10	0xFD2C
#घोषणा S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER6_V10	0xFD30
#घोषणा S5P_FIMV_E_HEVC_OPTIONS_V10			0xFDD4
#घोषणा S5P_FIMV_E_HEVC_REFRESH_PERIOD_V10		0xFDD8
#घोषणा S5P_FIMV_E_HEVC_CHROMA_QP_OFFSET_V10		0xFDDC
#घोषणा S5P_FIMV_E_HEVC_LF_BETA_OFFSET_DIV2_V10		0xFDE0
#घोषणा S5P_FIMV_E_HEVC_LF_TC_OFFSET_DIV2_V10		0xFDE4
#घोषणा S5P_FIMV_E_HEVC_NAL_CONTROL_V10			0xFDE8

/* MFCv10 Context buffer sizes */
#घोषणा MFC_CTX_BUF_SIZE_V10		(30 * SZ_1K)
#घोषणा MFC_H264_DEC_CTX_BUF_SIZE_V10	(2 * SZ_1M)
#घोषणा MFC_OTHER_DEC_CTX_BUF_SIZE_V10	(20 * SZ_1K)
#घोषणा MFC_H264_ENC_CTX_BUF_SIZE_V10	(100 * SZ_1K)
#घोषणा MFC_HEVC_ENC_CTX_BUF_SIZE_V10	(30 * SZ_1K)
#घोषणा MFC_OTHER_ENC_CTX_BUF_SIZE_V10  (15 * SZ_1K)

/* MFCv10 variant defines */
#घोषणा MAX_FW_SIZE_V10		(SZ_1M)
#घोषणा MAX_CPB_SIZE_V10	(3 * SZ_1M)
#घोषणा MFC_VERSION_V10		0xA0
#घोषणा MFC_NUM_PORTS_V10	1

/* MFCv10 codec defines*/
#घोषणा S5P_FIMV_CODEC_HEVC_DEC		17
#घोषणा S5P_FIMV_CODEC_VP9_DEC		18
#घोषणा S5P_FIMV_CODEC_HEVC_ENC         26

/* Decoder buffer size क्रम MFC v10 */
#घोषणा DEC_VP9_STATIC_BUFFER_SIZE	20480

/* Encoder buffer size क्रम MFC v10.0 */
#घोषणा ENC_V100_BASE_SIZE(x, y) \
	(((x + 3) * (y + 3) * 8) \
	+  ((y * 64) + 1280) * DIV_ROUND_UP(x, 8))

#घोषणा ENC_V100_H264_ME_SIZE(x, y) \
	(ENC_V100_BASE_SIZE(x, y) \
	+ (DIV_ROUND_UP(x * y, 64) * 32))

#घोषणा ENC_V100_MPEG4_ME_SIZE(x, y) \
	(ENC_V100_BASE_SIZE(x, y) \
	+ (DIV_ROUND_UP(x * y, 128) * 16))

#घोषणा ENC_V100_VP8_ME_SIZE(x, y) \
	ENC_V100_BASE_SIZE(x, y)

#घोषणा ENC_V100_HEVC_ME_SIZE(x, y)	\
	(((x + 3) * (y + 3) * 32)	\
	 + ((y * 128) + 1280) * DIV_ROUND_UP(x, 4))

#पूर्ण_अगर /*_REGS_MFC_V10_H*/

