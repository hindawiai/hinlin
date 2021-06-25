<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/platक्रमm/s5p-mfc/s5p_mfc_opr_v6.h
 *
 * Header file क्रम Samsung MFC (Multi Function Codec - FIMV) driver
 * Contains declarations of hw related functions.
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अगर_अघोषित S5P_MFC_OPR_V6_H_
#घोषणा S5P_MFC_OPR_V6_H_

#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_opr.h"

#घोषणा MFC_CTRL_MODE_CUSTOM	MFC_CTRL_MODE_SFR

#घोषणा MB_WIDTH(x_size)		DIV_ROUND_UP(x_size, 16)
#घोषणा MB_HEIGHT(y_size)		DIV_ROUND_UP(y_size, 16)
#घोषणा S5P_MFC_DEC_MV_SIZE_V6(x, y)	(MB_WIDTH(x) * \
					(((MB_HEIGHT(y)+1)/2)*2) * 64 + 128)
#घोषणा S5P_MFC_DEC_MV_SIZE_V10(x, y)	(MB_WIDTH(x) * \
					(((MB_HEIGHT(y)+1)/2)*2) * 64 + 512)
#घोषणा S5P_MFC_LCU_WIDTH(x_size)	DIV_ROUND_UP(x_size, 32)
#घोषणा S5P_MFC_LCU_HEIGHT(y_size)	DIV_ROUND_UP(y_size, 32)

#घोषणा s5p_mfc_dec_hevc_mv_size(x, y) \
	(DIV_ROUND_UP(x, 64) * DIV_ROUND_UP(y, 64) * 256 + 512)

/* Definition */
#घोषणा ENC_MULTI_SLICE_MB_MAX		((1 << 30) - 1)
#घोषणा ENC_MULTI_SLICE_BIT_MIN		2800
#घोषणा ENC_INTRA_REFRESH_MB_MAX	((1 << 18) - 1)
#घोषणा ENC_VBV_BUF_SIZE_MAX		((1 << 30) - 1)
#घोषणा ENC_H264_LOOP_FILTER_AB_MIN	-12
#घोषणा ENC_H264_LOOP_FILTER_AB_MAX	12
#घोषणा ENC_H264_RC_FRAME_RATE_MAX	((1 << 16) - 1)
#घोषणा ENC_H263_RC_FRAME_RATE_MAX	((1 << 16) - 1)
#घोषणा ENC_H264_PROखाता_MAX		3
#घोषणा ENC_H264_LEVEL_MAX		42
#घोषणा ENC_MPEG4_VOP_TIME_RES_MAX	((1 << 16) - 1)
#घोषणा FRAME_DELTA_H264_H263		1
#घोषणा TIGHT_CBR_MAX			10
#घोषणा ENC_HEVC_RC_FRAME_RATE_MAX	((1 << 16) - 1)
#घोषणा ENC_HEVC_QP_INDEX_MIN		-12
#घोषणा ENC_HEVC_QP_INDEX_MAX		12
#घोषणा ENC_HEVC_LOOP_FILTER_MIN	-12
#घोषणा ENC_HEVC_LOOP_FILTER_MAX	12
#घोषणा ENC_HEVC_LEVEL_MAX		62

#घोषणा FRAME_DELTA_DEFAULT		1

काष्ठा s5p_mfc_hw_ops *s5p_mfc_init_hw_ops_v6(व्योम);
स्थिर काष्ठा s5p_mfc_regs *s5p_mfc_init_regs_v6_plus(काष्ठा s5p_mfc_dev *dev);
#पूर्ण_अगर /* S5P_MFC_OPR_V6_H_ */
