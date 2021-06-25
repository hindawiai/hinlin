<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register definition file क्रम Samsung MFC V8.x Interface (FIMV) driver
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अगर_अघोषित _REGS_MFC_V8_H
#घोषणा _REGS_MFC_V8_H

#समावेश <linux/sizes.h>
#समावेश "regs-mfc-v7.h"

/* Additional रेजिस्टरs क्रम v8 */
#घोषणा S5P_FIMV_D_MVC_NUM_VIEWS_V8		0xf104
#घोषणा S5P_FIMV_D_MIN_SCRATCH_BUFFER_SIZE_V8	0xf108
#घोषणा S5P_FIMV_D_FIRST_PLANE_DPB_SIZE_V8	0xf144
#घोषणा S5P_FIMV_D_SECOND_PLANE_DPB_SIZE_V8	0xf148
#घोषणा S5P_FIMV_D_MV_BUFFER_SIZE_V8		0xf150

#घोषणा S5P_FIMV_D_FIRST_PLANE_DPB_STRIDE_SIZE_V8	0xf138
#घोषणा S5P_FIMV_D_SECOND_PLANE_DPB_STRIDE_SIZE_V8	0xf13c

#घोषणा S5P_FIMV_D_FIRST_PLANE_DPB_V8		0xf160
#घोषणा S5P_FIMV_D_SECOND_PLANE_DPB_V8		0xf260
#घोषणा S5P_FIMV_D_MV_BUFFER_V8			0xf460

#घोषणा S5P_FIMV_D_NUM_MV_V8			0xf134
#घोषणा S5P_FIMV_D_INIT_BUFFER_OPTIONS_V8	0xf154

#घोषणा S5P_FIMV_D_SCRATCH_BUFFER_ADDR_V8	0xf560
#घोषणा S5P_FIMV_D_SCRATCH_BUFFER_SIZE_V8	0xf564

#घोषणा S5P_FIMV_D_CPB_BUFFER_ADDR_V8		0xf5b0
#घोषणा S5P_FIMV_D_CPB_BUFFER_SIZE_V8		0xf5b4
#घोषणा S5P_FIMV_D_AVAILABLE_DPB_FLAG_LOWER_V8	0xf5bc
#घोषणा S5P_FIMV_D_CPB_BUFFER_OFFSET_V8		0xf5c0
#घोषणा S5P_FIMV_D_SLICE_IF_ENABLE_V8		0xf5c4
#घोषणा S5P_FIMV_D_STREAM_DATA_SIZE_V8		0xf5d0

/* Display inक्रमmation रेजिस्टर */
#घोषणा S5P_FIMV_D_DISPLAY_FRAME_WIDTH_V8	0xf600
#घोषणा S5P_FIMV_D_DISPLAY_FRAME_HEIGHT_V8	0xf604

/* Display status */
#घोषणा S5P_FIMV_D_DISPLAY_STATUS_V8		0xf608

#घोषणा S5P_FIMV_D_DISPLAY_FIRST_PLANE_ADDR_V8	0xf60c
#घोषणा S5P_FIMV_D_DISPLAY_SECOND_PLANE_ADDR_V8	0xf610

#घोषणा S5P_FIMV_D_DISPLAY_FRAME_TYPE_V8	0xf618
#घोषणा S5P_FIMV_D_DISPLAY_CROP_INFO1_V8	0xf61c
#घोषणा S5P_FIMV_D_DISPLAY_CROP_INFO2_V8	0xf620
#घोषणा S5P_FIMV_D_DISPLAY_PICTURE_PROखाता_V8	0xf624

/* Decoded picture inक्रमmation रेजिस्टर */
#घोषणा S5P_FIMV_D_DECODED_STATUS_V8		0xf644
#घोषणा S5P_FIMV_D_DECODED_FIRST_PLANE_ADDR_V8	0xf648
#घोषणा S5P_FIMV_D_DECODED_SECOND_PLANE_ADDR_V8	0xf64c
#घोषणा S5P_FIMV_D_DECODED_THIRD_PLANE_ADDR_V8	0xf650
#घोषणा S5P_FIMV_D_DECODED_FRAME_TYPE_V8	0xf654
#घोषणा S5P_FIMV_D_DECODED_NAL_SIZE_V8          0xf664

/* Returned value रेजिस्टर क्रम specअगरic setting */
#घोषणा S5P_FIMV_D_RET_PICTURE_TAG_TOP_V8	0xf674
#घोषणा S5P_FIMV_D_RET_PICTURE_TAG_BOT_V8	0xf678
#घोषणा S5P_FIMV_D_MVC_VIEW_ID_V8		0xf6d8

/* SEI related inक्रमmation */
#घोषणा S5P_FIMV_D_FRAME_PACK_SEI_AVAIL_V8	0xf6dc

/* Encoder Registers */
#घोषणा S5P_FIMV_E_FIXED_PICTURE_QP_V8		0xf794
#घोषणा S5P_FIMV_E_RC_CONFIG_V8			0xf798
#घोषणा S5P_FIMV_E_RC_QP_BOUND_V8		0xf79c
#घोषणा S5P_FIMV_E_RC_RPARAM_V8			0xf7a4
#घोषणा S5P_FIMV_E_MB_RC_CONFIG_V8		0xf7a8
#घोषणा S5P_FIMV_E_PADDING_CTRL_V8		0xf7ac
#घोषणा S5P_FIMV_E_MV_HOR_RANGE_V8		0xf7b4
#घोषणा S5P_FIMV_E_MV_VER_RANGE_V8		0xf7b8

#घोषणा S5P_FIMV_E_VBV_BUFFER_SIZE_V8		0xf78c
#घोषणा S5P_FIMV_E_VBV_INIT_DELAY_V8		0xf790
#घोषणा S5P_FIMV_E_MIN_SCRATCH_BUFFER_SIZE_V8   0xf894

#घोषणा S5P_FIMV_E_ASPECT_RATIO_V8		0xfb4c
#घोषणा S5P_FIMV_E_EXTENDED_SAR_V8		0xfb50
#घोषणा S5P_FIMV_E_H264_OPTIONS_V8		0xfb54

/* MFCv8 Context buffer sizes */
#घोषणा MFC_CTX_BUF_SIZE_V8		(36 * SZ_1K)	/*  36KB */
#घोषणा MFC_H264_DEC_CTX_BUF_SIZE_V8	(2 * SZ_1M)	/*  2MB */
#घोषणा MFC_OTHER_DEC_CTX_BUF_SIZE_V8	(20 * SZ_1K)	/*  20KB */
#घोषणा MFC_H264_ENC_CTX_BUF_SIZE_V8	(100 * SZ_1K)	/* 100KB */
#घोषणा MFC_OTHER_ENC_CTX_BUF_SIZE_V8	(10 * SZ_1K)	/*  10KB */

/* Buffer size defines */
#घोषणा S5P_FIMV_TMV_BUFFER_SIZE_V8(w, h)	(((w) + 1) * ((h) + 1) * 8)

#घोषणा S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V8(w, h)	(((w) * 704) + 2176)
#घोषणा S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V8(w, h) \
		(((w) * 576 + (h) * 128)  + 4128)

#घोषणा S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V8(w, h) \
			(((w) * 592) + 2336)
#घोषणा S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V8(w, h) \
			(((w) * 576) + 10512 + \
			((((((w) * 16) * ((h) * 16)) * 3) / 2) * 4))
#घोषणा S5P_FIMV_ME_BUFFER_SIZE_V8(imw, imh, mbw, mbh) \
	((DIV_ROUND_UP((mbw * 16), 64) *  DIV_ROUND_UP((mbh * 16), 64) * 256) \
	 + (DIV_ROUND_UP((mbw) * (mbh), 32) * 16))

/* BUffer alignment defines */
#घोषणा S5P_FIMV_D_ALIGN_PLANE_SIZE_V8	64

/* MFCv8 variant defines */
#घोषणा MAX_FW_SIZE_V8			(SZ_512K)	/* 512KB */
#घोषणा MAX_CPB_SIZE_V8			(3 * SZ_1M)	/* 3MB */
#घोषणा MFC_VERSION_V8			0x80
#घोषणा MFC_NUM_PORTS_V8		1

#पूर्ण_अगर /*_REGS_MFC_V8_H*/
