<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definition file क्रम Samsung MFC V7.x Interface (FIMV) driver
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अगर_अघोषित _REGS_MFC_V7_H
#घोषणा _REGS_MFC_V7_H

#समावेश "regs-mfc-v6.h"

/* Additional features of v7 */
#घोषणा S5P_FIMV_CODEC_VP8_ENC_V7	25

/* Additional रेजिस्टरs क्रम v7 */
#घोषणा S5P_FIMV_E_SOURCE_FIRST_ADDR_V7			0xf9e0
#घोषणा S5P_FIMV_E_SOURCE_SECOND_ADDR_V7		0xf9e4
#घोषणा S5P_FIMV_E_SOURCE_THIRD_ADDR_V7			0xf9e8
#घोषणा S5P_FIMV_E_SOURCE_FIRST_STRIDE_V7		0xf9ec
#घोषणा S5P_FIMV_E_SOURCE_SECOND_STRIDE_V7		0xf9f0
#घोषणा S5P_FIMV_E_SOURCE_THIRD_STRIDE_V7		0xf9f4

#घोषणा S5P_FIMV_E_ENCODED_SOURCE_FIRST_ADDR_V7		0xfa70
#घोषणा S5P_FIMV_E_ENCODED_SOURCE_SECOND_ADDR_V7	0xfa74

#घोषणा S5P_FIMV_E_VP8_OPTIONS_V7			0xfdb0
#घोषणा S5P_FIMV_E_VP8_FILTER_OPTIONS_V7		0xfdb4
#घोषणा S5P_FIMV_E_VP8_GOLDEN_FRAME_OPTION_V7		0xfdb8
#घोषणा S5P_FIMV_E_VP8_NUM_T_LAYER_V7			0xfdc4

/* MFCv7 variant defines */
#घोषणा MAX_FW_SIZE_V7			(SZ_512K)	/* 512KB */
#घोषणा MAX_CPB_SIZE_V7			(3 * SZ_1M)	/* 3MB */
#घोषणा MFC_VERSION_V7			0x72
#घोषणा MFC_NUM_PORTS_V7		1

#घोषणा MFC_LUMA_PAD_BYTES_V7		256
#घोषणा MFC_CHROMA_PAD_BYTES_V7		128

/* MFCv7 Context buffer sizes */
#घोषणा MFC_CTX_BUF_SIZE_V7		(30 * SZ_1K)	/*  30KB */
#घोषणा MFC_H264_DEC_CTX_BUF_SIZE_V7	(2 * SZ_1M)	/*  2MB */
#घोषणा MFC_OTHER_DEC_CTX_BUF_SIZE_V7	(20 * SZ_1K)	/*  20KB */
#घोषणा MFC_H264_ENC_CTX_BUF_SIZE_V7	(100 * SZ_1K)	/* 100KB */
#घोषणा MFC_OTHER_ENC_CTX_BUF_SIZE_V7	(10 * SZ_1K)	/*  10KB */

/* Buffer size defines */
#घोषणा S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V7(w, h) \
			(SZ_1M + ((w) * 144) + (8192 * (h)) + 49216)

#घोषणा S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V7(w, h) \
			(((w) * 48) + 8192 + ((((w) + 1) / 2) * 128) + 144 + \
			((((((w) * 16) * ((h) * 16)) * 3) / 2) * 4))

#पूर्ण_अगर /*_REGS_MFC_V7_H*/
