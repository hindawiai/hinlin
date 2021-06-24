<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Maxime Jourdan <mjourdan@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 */

#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "dos_regs.h"
#समावेश "hevc_regs.h"
#समावेश "codec_vp9.h"
#समावेश "vdec_helpers.h"
#समावेश "codec_hevc_common.h"

/* HEVC reg mapping */
#घोषणा VP9_DEC_STATUS_REG	HEVC_ASSIST_SCRATCH_0
	#घोषणा VP9_10B_DECODE_SLICE	5
	#घोषणा VP9_HEAD_PARSER_DONE	0xf0
#घोषणा VP9_RPM_BUFFER		HEVC_ASSIST_SCRATCH_1
#घोषणा VP9_SHORT_TERM_RPS	HEVC_ASSIST_SCRATCH_2
#घोषणा VP9_ADAPT_PROB_REG	HEVC_ASSIST_SCRATCH_3
#घोषणा VP9_MMU_MAP_BUFFER	HEVC_ASSIST_SCRATCH_4
#घोषणा VP9_PPS_BUFFER		HEVC_ASSIST_SCRATCH_5
#घोषणा VP9_SAO_UP		HEVC_ASSIST_SCRATCH_6
#घोषणा VP9_STREAM_SWAP_BUFFER	HEVC_ASSIST_SCRATCH_7
#घोषणा VP9_STREAM_SWAP_BUFFER2 HEVC_ASSIST_SCRATCH_8
#घोषणा VP9_PROB_SWAP_BUFFER	HEVC_ASSIST_SCRATCH_9
#घोषणा VP9_COUNT_SWAP_BUFFER	HEVC_ASSIST_SCRATCH_A
#घोषणा VP9_SEG_MAP_BUFFER	HEVC_ASSIST_SCRATCH_B
#घोषणा VP9_SCALELUT		HEVC_ASSIST_SCRATCH_D
#घोषणा VP9_WAIT_FLAG		HEVC_ASSIST_SCRATCH_E
#घोषणा LMEM_DUMP_ADR		HEVC_ASSIST_SCRATCH_F
#घोषणा NAL_SEARCH_CTL		HEVC_ASSIST_SCRATCH_I
#घोषणा VP9_DECODE_MODE		HEVC_ASSIST_SCRATCH_J
	#घोषणा DECODE_MODE_SINGLE 0
#घोषणा DECODE_STOP_POS		HEVC_ASSIST_SCRATCH_K
#घोषणा HEVC_DECODE_COUNT	HEVC_ASSIST_SCRATCH_M
#घोषणा HEVC_DECODE_SIZE	HEVC_ASSIST_SCRATCH_N

/* VP9 Constants */
#घोषणा LCU_SIZE		64
#घोषणा MAX_REF_PIC_NUM		24
#घोषणा REFS_PER_FRAME		3
#घोषणा REF_FRAMES		8
#घोषणा MV_MEM_UNIT		0x240
#घोषणा ADAPT_PROB_SIZE		0xf80

क्रमागत FRAME_TYPE अणु
	KEY_FRAME = 0,
	INTER_FRAME = 1,
	FRAME_TYPES,
पूर्ण;

/* VP9 Workspace layout */
#घोषणा MPRED_MV_BUF_SIZE 0x120000

#घोषणा IPP_SIZE	0x4000
#घोषणा SAO_ABV_SIZE	0x30000
#घोषणा SAO_VB_SIZE	0x30000
#घोषणा SH_TM_RPS_SIZE	0x800
#घोषणा VPS_SIZE	0x800
#घोषणा SPS_SIZE	0x800
#घोषणा PPS_SIZE	0x2000
#घोषणा SAO_UP_SIZE	0x2800
#घोषणा SWAP_BUF_SIZE	0x800
#घोषणा SWAP_BUF2_SIZE	0x800
#घोषणा SCALELUT_SIZE	0x8000
#घोषणा DBLK_PARA_SIZE	0x80000
#घोषणा DBLK_DATA_SIZE	0x80000
#घोषणा SEG_MAP_SIZE	0xd800
#घोषणा PROB_SIZE	0x5000
#घोषणा COUNT_SIZE	0x3000
#घोषणा MMU_VBH_SIZE	0x5000
#घोषणा MPRED_ABV_SIZE	0x10000
#घोषणा MPRED_MV_SIZE	(MPRED_MV_BUF_SIZE * MAX_REF_PIC_NUM)
#घोषणा RPM_BUF_SIZE	0x100
#घोषणा LMEM_SIZE	0x800

#घोषणा IPP_OFFSET       0x00
#घोषणा SAO_ABV_OFFSET   (IPP_OFFSET + IPP_SIZE)
#घोषणा SAO_VB_OFFSET    (SAO_ABV_OFFSET + SAO_ABV_SIZE)
#घोषणा SH_TM_RPS_OFFSET (SAO_VB_OFFSET + SAO_VB_SIZE)
#घोषणा VPS_OFFSET       (SH_TM_RPS_OFFSET + SH_TM_RPS_SIZE)
#घोषणा SPS_OFFSET       (VPS_OFFSET + VPS_SIZE)
#घोषणा PPS_OFFSET       (SPS_OFFSET + SPS_SIZE)
#घोषणा SAO_UP_OFFSET    (PPS_OFFSET + PPS_SIZE)
#घोषणा SWAP_BUF_OFFSET  (SAO_UP_OFFSET + SAO_UP_SIZE)
#घोषणा SWAP_BUF2_OFFSET (SWAP_BUF_OFFSET + SWAP_BUF_SIZE)
#घोषणा SCALELUT_OFFSET  (SWAP_BUF2_OFFSET + SWAP_BUF2_SIZE)
#घोषणा DBLK_PARA_OFFSET (SCALELUT_OFFSET + SCALELUT_SIZE)
#घोषणा DBLK_DATA_OFFSET (DBLK_PARA_OFFSET + DBLK_PARA_SIZE)
#घोषणा SEG_MAP_OFFSET   (DBLK_DATA_OFFSET + DBLK_DATA_SIZE)
#घोषणा PROB_OFFSET      (SEG_MAP_OFFSET + SEG_MAP_SIZE)
#घोषणा COUNT_OFFSET     (PROB_OFFSET + PROB_SIZE)
#घोषणा MMU_VBH_OFFSET   (COUNT_OFFSET + COUNT_SIZE)
#घोषणा MPRED_ABV_OFFSET (MMU_VBH_OFFSET + MMU_VBH_SIZE)
#घोषणा MPRED_MV_OFFSET  (MPRED_ABV_OFFSET + MPRED_ABV_SIZE)
#घोषणा RPM_OFFSET       (MPRED_MV_OFFSET + MPRED_MV_SIZE)
#घोषणा LMEM_OFFSET      (RPM_OFFSET + RPM_BUF_SIZE)

#घोषणा SIZE_WORKSPACE	ALIGN(LMEM_OFFSET + LMEM_SIZE, 64 * SZ_1K)

#घोषणा NONE           -1
#घोषणा INTRA_FRAME     0
#घोषणा LAST_FRAME      1
#घोषणा GOLDEN_FRAME    2
#घोषणा ALTREF_FRAME    3
#घोषणा MAX_REF_FRAMES  4

/*
 * Defines, declarations, sub-functions क्रम vp9 de-block loop
	filter Thr/Lvl table update
 * - काष्ठा segmentation is क्रम loop filter only (हटाओd something)
 * - function "vp9_loop_filter_init" and "vp9_loop_filter_frame_init" will
	be instantiated in C_Entry
 * - vp9_loop_filter_init run once beक्रमe decoding start
 * - vp9_loop_filter_frame_init run beक्रमe every frame decoding start
 * - set video क्रमmat to VP9 is in vp9_loop_filter_init
 */
#घोषणा MAX_LOOP_FILTER		63
#घोषणा MAX_REF_LF_DELTAS	4
#घोषणा MAX_MODE_LF_DELTAS	2
#घोषणा SEGMENT_DELTADATA	0
#घोषणा SEGMENT_ABSDATA		1
#घोषणा MAX_SEGMENTS		8

/* VP9 PROB processing defines */
#घोषणा VP9_PARTITION_START      0
#घोषणा VP9_PARTITION_SIZE_STEP  (3 * 4)
#घोषणा VP9_PARTITION_ONE_SIZE   (4 * VP9_PARTITION_SIZE_STEP)
#घोषणा VP9_PARTITION_KEY_START  0
#घोषणा VP9_PARTITION_P_START    VP9_PARTITION_ONE_SIZE
#घोषणा VP9_PARTITION_SIZE       (2 * VP9_PARTITION_ONE_SIZE)
#घोषणा VP9_SKIP_START           (VP9_PARTITION_START + VP9_PARTITION_SIZE)
#घोषणा VP9_SKIP_SIZE            4 /* only use 3*/
#घोषणा VP9_TX_MODE_START        (VP9_SKIP_START + VP9_SKIP_SIZE)
#घोषणा VP9_TX_MODE_8_0_OFFSET   0
#घोषणा VP9_TX_MODE_8_1_OFFSET   1
#घोषणा VP9_TX_MODE_16_0_OFFSET  2
#घोषणा VP9_TX_MODE_16_1_OFFSET  4
#घोषणा VP9_TX_MODE_32_0_OFFSET  6
#घोषणा VP9_TX_MODE_32_1_OFFSET  9
#घोषणा VP9_TX_MODE_SIZE         12
#घोषणा VP9_COEF_START           (VP9_TX_MODE_START + VP9_TX_MODE_SIZE)
#घोषणा VP9_COEF_BAND_0_OFFSET   0
#घोषणा VP9_COEF_BAND_1_OFFSET   (VP9_COEF_BAND_0_OFFSET + 3 * 3 + 1)
#घोषणा VP9_COEF_BAND_2_OFFSET   (VP9_COEF_BAND_1_OFFSET + 6 * 3)
#घोषणा VP9_COEF_BAND_3_OFFSET   (VP9_COEF_BAND_2_OFFSET + 6 * 3)
#घोषणा VP9_COEF_BAND_4_OFFSET   (VP9_COEF_BAND_3_OFFSET + 6 * 3)
#घोषणा VP9_COEF_BAND_5_OFFSET   (VP9_COEF_BAND_4_OFFSET + 6 * 3)
#घोषणा VP9_COEF_SIZE_ONE_SET    100 /* ((3 + 5 * 6) * 3 + 1 padding)*/
#घोषणा VP9_COEF_4X4_START       (VP9_COEF_START + 0 * VP9_COEF_SIZE_ONE_SET)
#घोषणा VP9_COEF_8X8_START       (VP9_COEF_START + 4 * VP9_COEF_SIZE_ONE_SET)
#घोषणा VP9_COEF_16X16_START     (VP9_COEF_START + 8 * VP9_COEF_SIZE_ONE_SET)
#घोषणा VP9_COEF_32X32_START     (VP9_COEF_START + 12 * VP9_COEF_SIZE_ONE_SET)
#घोषणा VP9_COEF_SIZE_PLANE      (2 * VP9_COEF_SIZE_ONE_SET)
#घोषणा VP9_COEF_SIZE            (4 * 2 * 2 * VP9_COEF_SIZE_ONE_SET)
#घोषणा VP9_INTER_MODE_START     (VP9_COEF_START + VP9_COEF_SIZE)
#घोषणा VP9_INTER_MODE_SIZE      24 /* only use 21 (# * 7)*/
#घोषणा VP9_INTERP_START         (VP9_INTER_MODE_START + VP9_INTER_MODE_SIZE)
#घोषणा VP9_INTERP_SIZE          8
#घोषणा VP9_INTRA_INTER_START    (VP9_INTERP_START + VP9_INTERP_SIZE)
#घोषणा VP9_INTRA_INTER_SIZE     4
#घोषणा VP9_INTERP_INTRA_INTER_START  VP9_INTERP_START
#घोषणा VP9_INTERP_INTRA_INTER_SIZE   (VP9_INTERP_SIZE + VP9_INTRA_INTER_SIZE)
#घोषणा VP9_COMP_INTER_START     \
		(VP9_INTERP_INTRA_INTER_START + VP9_INTERP_INTRA_INTER_SIZE)
#घोषणा VP9_COMP_INTER_SIZE      5
#घोषणा VP9_COMP_REF_START       (VP9_COMP_INTER_START + VP9_COMP_INTER_SIZE)
#घोषणा VP9_COMP_REF_SIZE        5
#घोषणा VP9_SINGLE_REF_START     (VP9_COMP_REF_START + VP9_COMP_REF_SIZE)
#घोषणा VP9_SINGLE_REF_SIZE      10
#घोषणा VP9_REF_MODE_START       VP9_COMP_INTER_START
#घोषणा VP9_REF_MODE_SIZE        \
		(VP9_COMP_INTER_SIZE + VP9_COMP_REF_SIZE + VP9_SINGLE_REF_SIZE)
#घोषणा VP9_IF_Y_MODE_START      (VP9_REF_MODE_START + VP9_REF_MODE_SIZE)
#घोषणा VP9_IF_Y_MODE_SIZE       36
#घोषणा VP9_IF_UV_MODE_START     (VP9_IF_Y_MODE_START + VP9_IF_Y_MODE_SIZE)
#घोषणा VP9_IF_UV_MODE_SIZE      92 /* only use 90*/
#घोषणा VP9_MV_JOINTS_START      (VP9_IF_UV_MODE_START + VP9_IF_UV_MODE_SIZE)
#घोषणा VP9_MV_JOINTS_SIZE       3
#घोषणा VP9_MV_SIGN_0_START      (VP9_MV_JOINTS_START + VP9_MV_JOINTS_SIZE)
#घोषणा VP9_MV_SIGN_0_SIZE       1
#घोषणा VP9_MV_CLASSES_0_START   (VP9_MV_SIGN_0_START + VP9_MV_SIGN_0_SIZE)
#घोषणा VP9_MV_CLASSES_0_SIZE    10
#घोषणा VP9_MV_CLASS0_0_START    \
		(VP9_MV_CLASSES_0_START + VP9_MV_CLASSES_0_SIZE)
#घोषणा VP9_MV_CLASS0_0_SIZE     1
#घोषणा VP9_MV_BITS_0_START      (VP9_MV_CLASS0_0_START + VP9_MV_CLASS0_0_SIZE)
#घोषणा VP9_MV_BITS_0_SIZE       10
#घोषणा VP9_MV_SIGN_1_START      (VP9_MV_BITS_0_START + VP9_MV_BITS_0_SIZE)
#घोषणा VP9_MV_SIGN_1_SIZE       1
#घोषणा VP9_MV_CLASSES_1_START   \
			(VP9_MV_SIGN_1_START + VP9_MV_SIGN_1_SIZE)
#घोषणा VP9_MV_CLASSES_1_SIZE    10
#घोषणा VP9_MV_CLASS0_1_START    \
			(VP9_MV_CLASSES_1_START + VP9_MV_CLASSES_1_SIZE)
#घोषणा VP9_MV_CLASS0_1_SIZE     1
#घोषणा VP9_MV_BITS_1_START      \
			(VP9_MV_CLASS0_1_START + VP9_MV_CLASS0_1_SIZE)
#घोषणा VP9_MV_BITS_1_SIZE       10
#घोषणा VP9_MV_CLASS0_FP_0_START \
			(VP9_MV_BITS_1_START + VP9_MV_BITS_1_SIZE)
#घोषणा VP9_MV_CLASS0_FP_0_SIZE  9
#घोषणा VP9_MV_CLASS0_FP_1_START \
			(VP9_MV_CLASS0_FP_0_START + VP9_MV_CLASS0_FP_0_SIZE)
#घोषणा VP9_MV_CLASS0_FP_1_SIZE  9
#घोषणा VP9_MV_CLASS0_HP_0_START \
			(VP9_MV_CLASS0_FP_1_START + VP9_MV_CLASS0_FP_1_SIZE)
#घोषणा VP9_MV_CLASS0_HP_0_SIZE  2
#घोषणा VP9_MV_CLASS0_HP_1_START \
			(VP9_MV_CLASS0_HP_0_START + VP9_MV_CLASS0_HP_0_SIZE)
#घोषणा VP9_MV_CLASS0_HP_1_SIZE  2
#घोषणा VP9_MV_START             VP9_MV_JOINTS_START
#घोषणा VP9_MV_SIZE              72 /*only use 69*/

#घोषणा VP9_TOTAL_SIZE           (VP9_MV_START + VP9_MV_SIZE)

/* VP9 COUNT mem processing defines */
#घोषणा VP9_COEF_COUNT_START           0
#घोषणा VP9_COEF_COUNT_BAND_0_OFFSET   0
#घोषणा VP9_COEF_COUNT_BAND_1_OFFSET   \
			(VP9_COEF_COUNT_BAND_0_OFFSET + 3 * 5)
#घोषणा VP9_COEF_COUNT_BAND_2_OFFSET   \
			(VP9_COEF_COUNT_BAND_1_OFFSET + 6 * 5)
#घोषणा VP9_COEF_COUNT_BAND_3_OFFSET   \
			(VP9_COEF_COUNT_BAND_2_OFFSET + 6 * 5)
#घोषणा VP9_COEF_COUNT_BAND_4_OFFSET   \
			(VP9_COEF_COUNT_BAND_3_OFFSET + 6 * 5)
#घोषणा VP9_COEF_COUNT_BAND_5_OFFSET   \
			(VP9_COEF_COUNT_BAND_4_OFFSET + 6 * 5)
#घोषणा VP9_COEF_COUNT_SIZE_ONE_SET    165 /* ((3 + 5 * 6) * 5 */
#घोषणा VP9_COEF_COUNT_4X4_START       \
		(VP9_COEF_COUNT_START + 0 * VP9_COEF_COUNT_SIZE_ONE_SET)
#घोषणा VP9_COEF_COUNT_8X8_START       \
		(VP9_COEF_COUNT_START + 4 * VP9_COEF_COUNT_SIZE_ONE_SET)
#घोषणा VP9_COEF_COUNT_16X16_START     \
		(VP9_COEF_COUNT_START + 8 * VP9_COEF_COUNT_SIZE_ONE_SET)
#घोषणा VP9_COEF_COUNT_32X32_START     \
		(VP9_COEF_COUNT_START + 12 * VP9_COEF_COUNT_SIZE_ONE_SET)
#घोषणा VP9_COEF_COUNT_SIZE_PLANE      (2 * VP9_COEF_COUNT_SIZE_ONE_SET)
#घोषणा VP9_COEF_COUNT_SIZE            (4 * 2 * 2 * VP9_COEF_COUNT_SIZE_ONE_SET)

#घोषणा VP9_INTRA_INTER_COUNT_START    \
		(VP9_COEF_COUNT_START + VP9_COEF_COUNT_SIZE)
#घोषणा VP9_INTRA_INTER_COUNT_SIZE     (4 * 2)
#घोषणा VP9_COMP_INTER_COUNT_START     \
		(VP9_INTRA_INTER_COUNT_START + VP9_INTRA_INTER_COUNT_SIZE)
#घोषणा VP9_COMP_INTER_COUNT_SIZE      (5 * 2)
#घोषणा VP9_COMP_REF_COUNT_START       \
		(VP9_COMP_INTER_COUNT_START + VP9_COMP_INTER_COUNT_SIZE)
#घोषणा VP9_COMP_REF_COUNT_SIZE        (5 * 2)
#घोषणा VP9_SINGLE_REF_COUNT_START     \
		(VP9_COMP_REF_COUNT_START + VP9_COMP_REF_COUNT_SIZE)
#घोषणा VP9_SINGLE_REF_COUNT_SIZE      (10 * 2)
#घोषणा VP9_TX_MODE_COUNT_START        \
		(VP9_SINGLE_REF_COUNT_START + VP9_SINGLE_REF_COUNT_SIZE)
#घोषणा VP9_TX_MODE_COUNT_SIZE         (12 * 2)
#घोषणा VP9_SKIP_COUNT_START           \
		(VP9_TX_MODE_COUNT_START + VP9_TX_MODE_COUNT_SIZE)
#घोषणा VP9_SKIP_COUNT_SIZE            (3 * 2)
#घोषणा VP9_MV_SIGN_0_COUNT_START      \
		(VP9_SKIP_COUNT_START + VP9_SKIP_COUNT_SIZE)
#घोषणा VP9_MV_SIGN_0_COUNT_SIZE       (1 * 2)
#घोषणा VP9_MV_SIGN_1_COUNT_START      \
		(VP9_MV_SIGN_0_COUNT_START + VP9_MV_SIGN_0_COUNT_SIZE)
#घोषणा VP9_MV_SIGN_1_COUNT_SIZE       (1 * 2)
#घोषणा VP9_MV_BITS_0_COUNT_START      \
		(VP9_MV_SIGN_1_COUNT_START + VP9_MV_SIGN_1_COUNT_SIZE)
#घोषणा VP9_MV_BITS_0_COUNT_SIZE       (10 * 2)
#घोषणा VP9_MV_BITS_1_COUNT_START      \
		(VP9_MV_BITS_0_COUNT_START + VP9_MV_BITS_0_COUNT_SIZE)
#घोषणा VP9_MV_BITS_1_COUNT_SIZE       (10 * 2)
#घोषणा VP9_MV_CLASS0_HP_0_COUNT_START \
		(VP9_MV_BITS_1_COUNT_START + VP9_MV_BITS_1_COUNT_SIZE)
#घोषणा VP9_MV_CLASS0_HP_0_COUNT_SIZE  (2 * 2)
#घोषणा VP9_MV_CLASS0_HP_1_COUNT_START \
		(VP9_MV_CLASS0_HP_0_COUNT_START + VP9_MV_CLASS0_HP_0_COUNT_SIZE)
#घोषणा VP9_MV_CLASS0_HP_1_COUNT_SIZE  (2 * 2)

/* Start merge_tree */
#घोषणा VP9_INTER_MODE_COUNT_START     \
		(VP9_MV_CLASS0_HP_1_COUNT_START + VP9_MV_CLASS0_HP_1_COUNT_SIZE)
#घोषणा VP9_INTER_MODE_COUNT_SIZE      (7 * 4)
#घोषणा VP9_IF_Y_MODE_COUNT_START      \
		(VP9_INTER_MODE_COUNT_START + VP9_INTER_MODE_COUNT_SIZE)
#घोषणा VP9_IF_Y_MODE_COUNT_SIZE       (10 * 4)
#घोषणा VP9_IF_UV_MODE_COUNT_START     \
		(VP9_IF_Y_MODE_COUNT_START + VP9_IF_Y_MODE_COUNT_SIZE)
#घोषणा VP9_IF_UV_MODE_COUNT_SIZE      (10 * 10)
#घोषणा VP9_PARTITION_P_COUNT_START    \
		(VP9_IF_UV_MODE_COUNT_START + VP9_IF_UV_MODE_COUNT_SIZE)
#घोषणा VP9_PARTITION_P_COUNT_SIZE     (4 * 4 * 4)
#घोषणा VP9_INTERP_COUNT_START         \
		(VP9_PARTITION_P_COUNT_START + VP9_PARTITION_P_COUNT_SIZE)
#घोषणा VP9_INTERP_COUNT_SIZE          (4 * 3)
#घोषणा VP9_MV_JOINTS_COUNT_START      \
		(VP9_INTERP_COUNT_START + VP9_INTERP_COUNT_SIZE)
#घोषणा VP9_MV_JOINTS_COUNT_SIZE       (1 * 4)
#घोषणा VP9_MV_CLASSES_0_COUNT_START   \
		(VP9_MV_JOINTS_COUNT_START + VP9_MV_JOINTS_COUNT_SIZE)
#घोषणा VP9_MV_CLASSES_0_COUNT_SIZE    (1 * 11)
#घोषणा VP9_MV_CLASS0_0_COUNT_START    \
		(VP9_MV_CLASSES_0_COUNT_START + VP9_MV_CLASSES_0_COUNT_SIZE)
#घोषणा VP9_MV_CLASS0_0_COUNT_SIZE     (1 * 2)
#घोषणा VP9_MV_CLASSES_1_COUNT_START   \
		(VP9_MV_CLASS0_0_COUNT_START + VP9_MV_CLASS0_0_COUNT_SIZE)
#घोषणा VP9_MV_CLASSES_1_COUNT_SIZE    (1 * 11)
#घोषणा VP9_MV_CLASS0_1_COUNT_START    \
		(VP9_MV_CLASSES_1_COUNT_START + VP9_MV_CLASSES_1_COUNT_SIZE)
#घोषणा VP9_MV_CLASS0_1_COUNT_SIZE     (1 * 2)
#घोषणा VP9_MV_CLASS0_FP_0_COUNT_START \
		(VP9_MV_CLASS0_1_COUNT_START + VP9_MV_CLASS0_1_COUNT_SIZE)
#घोषणा VP9_MV_CLASS0_FP_0_COUNT_SIZE  (3 * 4)
#घोषणा VP9_MV_CLASS0_FP_1_COUNT_START \
		(VP9_MV_CLASS0_FP_0_COUNT_START + VP9_MV_CLASS0_FP_0_COUNT_SIZE)
#घोषणा VP9_MV_CLASS0_FP_1_COUNT_SIZE  (3 * 4)

#घोषणा DC_PRED    0	/* Average of above and left pixels */
#घोषणा V_PRED     1	/* Vertical */
#घोषणा H_PRED     2	/* Horizontal */
#घोषणा D45_PRED   3	/* Directional 45 deg = round(arctan(1/1) * 180/pi) */
#घोषणा D135_PRED  4	/* Directional 135 deg = 180 - 45 */
#घोषणा D117_PRED  5	/* Directional 117 deg = 180 - 63 */
#घोषणा D153_PRED  6	/* Directional 153 deg = 180 - 27 */
#घोषणा D207_PRED  7	/* Directional 207 deg = 180 + 27 */
#घोषणा D63_PRED   8	/* Directional 63 deg = round(arctan(2/1) * 180/pi) */
#घोषणा TM_PRED    9	/* True-motion */

/* Use a अटल अंतरभूत to aव्योम possible side effect from num being reused */
अटल अंतरभूत पूर्णांक round_घातer_of_two(पूर्णांक value, पूर्णांक num)
अणु
	वापस (value + (1 << (num - 1))) >> num;
पूर्ण

#घोषणा MODE_MV_COUNT_SAT 20
अटल स्थिर पूर्णांक count_to_update_factor[MODE_MV_COUNT_SAT + 1] = अणु
	0, 6, 12, 19, 25, 32, 38, 44, 51, 57, 64,
	70, 76, 83, 89, 96, 102, 108, 115, 121, 128
पूर्ण;

जोड़ rpm_param अणु
	काष्ठा अणु
		u16 data[RPM_BUF_SIZE];
	पूर्ण l;
	काष्ठा अणु
		u16 profile;
		u16 show_existing_frame;
		u16 frame_to_show_idx;
		u16 frame_type; /*1 bit*/
		u16 show_frame; /*1 bit*/
		u16 error_resilient_mode; /*1 bit*/
		u16 पूर्णांकra_only; /*1 bit*/
		u16 display_size_present; /*1 bit*/
		u16 reset_frame_context;
		u16 refresh_frame_flags;
		u16 width;
		u16 height;
		u16 display_width;
		u16 display_height;
		u16 ref_info;
		u16 same_frame_size;
		u16 mode_ref_delta_enabled;
		u16 ref_deltas[4];
		u16 mode_deltas[2];
		u16 filter_level;
		u16 sharpness_level;
		u16 bit_depth;
		u16 seg_quant_info[8];
		u16 seg_enabled;
		u16 seg_असल_delta;
		/* bit 15: feature enabled; bit 8, sign; bit[5:0], data */
		u16 seg_lf_info[8];
	पूर्ण p;
पूर्ण;

क्रमागत SEG_LVL_FEATURES अणु
	SEG_LVL_ALT_Q = 0,	/* Use alternate Quantizer */
	SEG_LVL_ALT_LF = 1,	/* Use alternate loop filter value */
	SEG_LVL_REF_FRAME = 2,	/* Optional Segment reference frame */
	SEG_LVL_SKIP = 3,	/* Optional Segment (0,0) + skip mode */
	SEG_LVL_MAX = 4		/* Number of features supported */
पूर्ण;

काष्ठा segmentation अणु
	u8 enabled;
	u8 update_map;
	u8 update_data;
	u8 असल_delta;
	u8 temporal_update;
	s16 feature_data[MAX_SEGMENTS][SEG_LVL_MAX];
	अचिन्हित पूर्णांक feature_mask[MAX_SEGMENTS];
पूर्ण;

काष्ठा loop_filter_thresh अणु
	u8 mblim;
	u8 lim;
	u8 hev_thr;
पूर्ण;

काष्ठा loop_filter_info_n अणु
	काष्ठा loop_filter_thresh lfthr[MAX_LOOP_FILTER + 1];
	u8 lvl[MAX_SEGMENTS][MAX_REF_FRAMES][MAX_MODE_LF_DELTAS];
पूर्ण;

काष्ठा loopfilter अणु
	पूर्णांक filter_level;

	पूर्णांक sharpness_level;
	पूर्णांक last_sharpness_level;

	u8 mode_ref_delta_enabled;
	u8 mode_ref_delta_update;

	/*0 = Intra, Last, GF, ARF*/
	चिन्हित अक्षर ref_deltas[MAX_REF_LF_DELTAS];
	चिन्हित अक्षर last_ref_deltas[MAX_REF_LF_DELTAS];

	/*0 = ZERO_MV, MV*/
	चिन्हित अक्षर mode_deltas[MAX_MODE_LF_DELTAS];
	चिन्हित अक्षर last_mode_deltas[MAX_MODE_LF_DELTAS];
पूर्ण;

काष्ठा vp9_frame अणु
	काष्ठा list_head list;
	काष्ठा vb2_v4l2_buffer *vbuf;
	पूर्णांक index;
	पूर्णांक पूर्णांकra_only;
	पूर्णांक show;
	पूर्णांक type;
	पूर्णांक करोne;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
पूर्ण;

काष्ठा codec_vp9 अणु
	/* VP9 context lock */
	काष्ठा mutex lock;

	/* Common part with the HEVC decoder */
	काष्ठा codec_hevc_common common;

	/* Buffer क्रम the VP9 Workspace */
	व्योम      *workspace_vaddr;
	dma_addr_t workspace_paddr;

	/* Contains many inक्रमmation parsed from the bitstream */
	जोड़ rpm_param rpm_param;

	/* Whether we detected the bitstream as 10-bit */
	पूर्णांक is_10bit;

	/* Coded resolution reported by the hardware */
	u32 width, height;

	/* All ref frames used by the HW at a given समय */
	काष्ठा list_head ref_frames_list;
	u32 frames_num;

	/* In हाल of करोwnsampling (decoding with FBC but outputting in NV12M),
	 * we need to allocate additional buffers क्रम FBC.
	 */
	व्योम      *fbc_buffer_vaddr[MAX_REF_PIC_NUM];
	dma_addr_t fbc_buffer_paddr[MAX_REF_PIC_NUM];

	पूर्णांक ref_frame_map[REF_FRAMES];
	पूर्णांक next_ref_frame_map[REF_FRAMES];
	काष्ठा vp9_frame *frame_refs[REFS_PER_FRAME];

	u32 lcu_total;

	/* loop filter */
	पूर्णांक शेष_filt_lvl;
	काष्ठा loop_filter_info_n lfi;
	काष्ठा loopfilter lf;
	काष्ठा segmentation seg_4lf;

	काष्ठा vp9_frame *cur_frame;
	काष्ठा vp9_frame *prev_frame;
पूर्ण;

अटल पूर्णांक भाग_r32(s64 m, पूर्णांक n)
अणु
	s64 qu = भाग_s64(m, n);

	वापस (पूर्णांक)qu;
पूर्ण

अटल पूर्णांक clip_prob(पूर्णांक p)
अणु
	वापस clamp_val(p, 1, 255);
पूर्ण

अटल पूर्णांक segfeature_active(काष्ठा segmentation *seg, पूर्णांक segment_id,
			     क्रमागत SEG_LVL_FEATURES feature_id)
अणु
	वापस seg->enabled &&
		(seg->feature_mask[segment_id] & (1 << feature_id));
पूर्ण

अटल पूर्णांक get_segdata(काष्ठा segmentation *seg, पूर्णांक segment_id,
		       क्रमागत SEG_LVL_FEATURES feature_id)
अणु
	वापस seg->feature_data[segment_id][feature_id];
पूर्ण

अटल व्योम vp9_update_sharpness(काष्ठा loop_filter_info_n *lfi,
				 पूर्णांक sharpness_lvl)
अणु
	पूर्णांक lvl;

	/* For each possible value क्रम the loop filter fill out limits*/
	क्रम (lvl = 0; lvl <= MAX_LOOP_FILTER; lvl++) अणु
		/* Set loop filter parameters that control sharpness.*/
		पूर्णांक block_inside_limit = lvl >> ((sharpness_lvl > 0) +
					(sharpness_lvl > 4));

		अगर (sharpness_lvl > 0) अणु
			अगर (block_inside_limit > (9 - sharpness_lvl))
				block_inside_limit = (9 - sharpness_lvl);
		पूर्ण

		अगर (block_inside_limit < 1)
			block_inside_limit = 1;

		lfi->lfthr[lvl].lim = (u8)block_inside_limit;
		lfi->lfthr[lvl].mblim = (u8)(2 * (lvl + 2) +
				block_inside_limit);
	पूर्ण
पूर्ण

/* Instantiate this function once when decode is started */
अटल व्योम
vp9_loop_filter_init(काष्ठा amvdec_core *core, काष्ठा codec_vp9 *vp9)
अणु
	काष्ठा loop_filter_info_n *lfi = &vp9->lfi;
	काष्ठा loopfilter *lf = &vp9->lf;
	काष्ठा segmentation *seg_4lf = &vp9->seg_4lf;
	पूर्णांक i;

	स_रखो(lfi, 0, माप(काष्ठा loop_filter_info_n));
	स_रखो(lf, 0, माप(काष्ठा loopfilter));
	स_रखो(seg_4lf, 0, माप(काष्ठा segmentation));
	lf->sharpness_level = 0;
	vp9_update_sharpness(lfi, lf->sharpness_level);
	lf->last_sharpness_level = lf->sharpness_level;

	क्रम (i = 0; i < 32; i++) अणु
		अचिन्हित पूर्णांक thr;

		thr = ((lfi->lfthr[i * 2 + 1].lim & 0x3f) << 8) |
			(lfi->lfthr[i * 2 + 1].mblim & 0xff);
		thr = (thr << 16) | ((lfi->lfthr[i * 2].lim & 0x3f) << 8) |
			(lfi->lfthr[i * 2].mblim & 0xff);

		amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFG9, thr);
	पूर्ण

	अगर (core->platक्रमm->revision >= VDEC_REVISION_SM1)
		amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFGB,
				 (0x3 << 14) | /* dw fअगरo thres r and b */
				 (0x3 << 12) | /* dw fअगरo thres r or b */
				 (0x3 << 10) | /* dw fअगरo thres not r/b */
				 BIT(0)); /* VP9 video क्रमmat */
	अन्यथा अगर (core->platक्रमm->revision >= VDEC_REVISION_G12A)
		/* VP9 video क्रमmat */
		amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFGB, (0x54 << 8) | BIT(0));
	अन्यथा
		amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFGB, 0x40400001);
पूर्ण

अटल व्योम
vp9_loop_filter_frame_init(काष्ठा amvdec_core *core, काष्ठा segmentation *seg,
			   काष्ठा loop_filter_info_n *lfi,
			   काष्ठा loopfilter *lf, पूर्णांक शेष_filt_lvl)
अणु
	पूर्णांक i;
	पूर्णांक seg_id;

	/*
	 * n_shअगरt is the multiplier क्रम lf_deltas
	 * the multiplier is:
	 * - 1 क्रम when filter_lvl is between 0 and 31
	 * - 2 when filter_lvl is between 32 and 63
	 */
	स्थिर पूर्णांक scale = 1 << (शेष_filt_lvl >> 5);

	/* update limits अगर sharpness has changed */
	अगर (lf->last_sharpness_level != lf->sharpness_level) अणु
		vp9_update_sharpness(lfi, lf->sharpness_level);
		lf->last_sharpness_level = lf->sharpness_level;

		/* Write to रेजिस्टर */
		क्रम (i = 0; i < 32; i++) अणु
			अचिन्हित पूर्णांक thr;

			thr = ((lfi->lfthr[i * 2 + 1].lim & 0x3f) << 8) |
			      (lfi->lfthr[i * 2 + 1].mblim & 0xff);
			thr = (thr << 16) |
			      ((lfi->lfthr[i * 2].lim & 0x3f) << 8) |
			      (lfi->lfthr[i * 2].mblim & 0xff);

			amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFG9, thr);
		पूर्ण
	पूर्ण

	क्रम (seg_id = 0; seg_id < MAX_SEGMENTS; seg_id++) अणु
		पूर्णांक lvl_seg = शेष_filt_lvl;

		अगर (segfeature_active(seg, seg_id, SEG_LVL_ALT_LF)) अणु
			स्थिर पूर्णांक data = get_segdata(seg, seg_id,
						SEG_LVL_ALT_LF);
			lvl_seg = clamp_t(पूर्णांक,
					  seg->असल_delta == SEGMENT_ABSDATA ?
						data : शेष_filt_lvl + data,
					  0, MAX_LOOP_FILTER);
		पूर्ण

		अगर (!lf->mode_ref_delta_enabled) अणु
			/*
			 * We could get rid of this अगर we assume that deltas
			 * are set to zero when not in use.
			 * encoder always uses deltas
			 */
			स_रखो(lfi->lvl[seg_id], lvl_seg,
			       माप(lfi->lvl[seg_id]));
		पूर्ण अन्यथा अणु
			पूर्णांक ref, mode;
			स्थिर पूर्णांक पूर्णांकra_lvl =
				lvl_seg + lf->ref_deltas[INTRA_FRAME] * scale;
			lfi->lvl[seg_id][INTRA_FRAME][0] =
				clamp_val(पूर्णांकra_lvl, 0, MAX_LOOP_FILTER);

			क्रम (ref = LAST_FRAME; ref < MAX_REF_FRAMES; ++ref) अणु
				क्रम (mode = 0; mode < MAX_MODE_LF_DELTAS;
				     ++mode) अणु
					स्थिर पूर्णांक पूर्णांकer_lvl =
						lvl_seg +
						lf->ref_deltas[ref] * scale +
						lf->mode_deltas[mode] * scale;
					lfi->lvl[seg_id][ref][mode] =
						clamp_val(पूर्णांकer_lvl, 0,
							  MAX_LOOP_FILTER);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		अचिन्हित पूर्णांक level;

		level = ((lfi->lvl[i >> 1][3][i & 1] & 0x3f) << 24) |
			((lfi->lvl[i >> 1][2][i & 1] & 0x3f) << 16) |
			((lfi->lvl[i >> 1][1][i & 1] & 0x3f) << 8) |
			(lfi->lvl[i >> 1][0][i & 1] & 0x3f);
		अगर (!शेष_filt_lvl)
			level = 0;

		amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFGA, level);
	पूर्ण
पूर्ण

अटल व्योम codec_vp9_flush_output(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;
	काष्ठा vp9_frame *पंचांगp, *n;

	mutex_lock(&vp9->lock);
	list_क्रम_each_entry_safe(पंचांगp, n, &vp9->ref_frames_list, list) अणु
		अगर (!पंचांगp->करोne) अणु
			अगर (पंचांगp->show)
				amvdec_dst_buf_करोne(sess, पंचांगp->vbuf,
						    V4L2_FIELD_NONE);
			अन्यथा
				v4l2_m2m_buf_queue(sess->m2m_ctx, पंचांगp->vbuf);

			vp9->frames_num--;
		पूर्ण

		list_del(&पंचांगp->list);
		kमुक्त(पंचांगp);
	पूर्ण
	mutex_unlock(&vp9->lock);
पूर्ण

अटल u32 codec_vp9_num_pending_bufs(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;

	अगर (!vp9)
		वापस 0;

	वापस vp9->frames_num;
पूर्ण

अटल पूर्णांक codec_vp9_alloc_workspace(काष्ठा amvdec_core *core,
				     काष्ठा codec_vp9 *vp9)
अणु
	/* Allocate some memory क्रम the VP9 decoder's state */
	vp9->workspace_vaddr = dma_alloc_coherent(core->dev, SIZE_WORKSPACE,
						  &vp9->workspace_paddr,
						  GFP_KERNEL);
	अगर (!vp9->workspace_vaddr) अणु
		dev_err(core->dev, "Failed to allocate VP9 Workspace\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम codec_vp9_setup_workspace(काष्ठा amvdec_session *sess,
				      काष्ठा codec_vp9 *vp9)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 revision = core->platक्रमm->revision;
	dma_addr_t wkaddr = vp9->workspace_paddr;

	amvdec_ग_लिखो_करोs(core, HEVCD_IPP_LINEBUFF_BASE, wkaddr + IPP_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_RPM_BUFFER, wkaddr + RPM_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_SHORT_TERM_RPS, wkaddr + SH_TM_RPS_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_PPS_BUFFER, wkaddr + PPS_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_SAO_UP, wkaddr + SAO_UP_OFFSET);

	amvdec_ग_लिखो_करोs(core, VP9_STREAM_SWAP_BUFFER,
			 wkaddr + SWAP_BUF_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_STREAM_SWAP_BUFFER2,
			 wkaddr + SWAP_BUF2_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_SCALELUT, wkaddr + SCALELUT_OFFSET);

	अगर (core->platक्रमm->revision >= VDEC_REVISION_G12A)
		amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFGE,
				 wkaddr + DBLK_PARA_OFFSET);

	amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFG4, wkaddr + DBLK_PARA_OFFSET);
	amvdec_ग_लिखो_करोs(core, HEVC_DBLK_CFG5, wkaddr + DBLK_DATA_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_SEG_MAP_BUFFER, wkaddr + SEG_MAP_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_PROB_SWAP_BUFFER, wkaddr + PROB_OFFSET);
	amvdec_ग_लिखो_करोs(core, VP9_COUNT_SWAP_BUFFER, wkaddr + COUNT_OFFSET);
	amvdec_ग_लिखो_करोs(core, LMEM_DUMP_ADR, wkaddr + LMEM_OFFSET);

	अगर (codec_hevc_use_mmu(revision, sess->pixfmt_cap, vp9->is_10bit)) अणु
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_MMU_VH0_ADDR,
				 wkaddr + MMU_VBH_OFFSET);
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_MMU_VH1_ADDR,
				 wkaddr + MMU_VBH_OFFSET + (MMU_VBH_SIZE / 2));

		अगर (revision >= VDEC_REVISION_G12A)
			amvdec_ग_लिखो_करोs(core, HEVC_ASSIST_MMU_MAP_ADDR,
					 vp9->common.mmu_map_paddr);
		अन्यथा
			amvdec_ग_लिखो_करोs(core, VP9_MMU_MAP_BUFFER,
					 vp9->common.mmu_map_paddr);
	पूर्ण
पूर्ण

अटल पूर्णांक codec_vp9_start(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_vp9 *vp9;
	u32 val;
	पूर्णांक i;
	पूर्णांक ret;

	vp9 = kzalloc(माप(*vp9), GFP_KERNEL);
	अगर (!vp9)
		वापस -ENOMEM;

	ret = codec_vp9_alloc_workspace(core, vp9);
	अगर (ret)
		जाओ मुक्त_vp9;

	codec_vp9_setup_workspace(sess, vp9);
	amvdec_ग_लिखो_करोs_bits(core, HEVC_STREAM_CONTROL, BIT(0));
	/* stream_fअगरo_hole */
	अगर (core->platक्रमm->revision >= VDEC_REVISION_G12A)
		amvdec_ग_लिखो_करोs_bits(core, HEVC_STREAM_FIFO_CTL, BIT(29));

	val = amvdec_पढ़ो_करोs(core, HEVC_PARSER_INT_CONTROL) & 0x7fffffff;
	val |= (3 << 29) | BIT(24) | BIT(22) | BIT(7) | BIT(4) | BIT(0);
	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_INT_CONTROL, val);
	amvdec_ग_लिखो_करोs_bits(core, HEVC_SHIFT_STATUS, BIT(0));
	amvdec_ग_लिखो_करोs(core, HEVC_SHIFT_CONTROL, BIT(10) | BIT(9) |
			 (3 << 6) | BIT(5) | BIT(2) | BIT(1) | BIT(0));
	amvdec_ग_लिखो_करोs(core, HEVC_CABAC_CONTROL, BIT(0));
	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_CORE_CONTROL, BIT(0));
	amvdec_ग_लिखो_करोs(core, HEVC_SHIFT_STARTCODE, 0x00000001);

	amvdec_ग_लिखो_करोs(core, VP9_DEC_STATUS_REG, 0);

	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_CMD_WRITE, BIT(16));
	क्रम (i = 0; i < ARRAY_SIZE(vdec_hevc_parser_cmd); ++i)
		amvdec_ग_लिखो_करोs(core, HEVC_PARSER_CMD_WRITE,
				 vdec_hevc_parser_cmd[i]);

	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_CMD_SKIP_0, PARSER_CMD_SKIP_CFG_0);
	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_CMD_SKIP_1, PARSER_CMD_SKIP_CFG_1);
	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_CMD_SKIP_2, PARSER_CMD_SKIP_CFG_2);
	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_IF_CONTROL,
			 BIT(5) | BIT(2) | BIT(0));

	amvdec_ग_लिखो_करोs(core, HEVCD_IPP_TOP_CNTL, BIT(0));
	amvdec_ग_लिखो_करोs(core, HEVCD_IPP_TOP_CNTL, BIT(1));

	amvdec_ग_लिखो_करोs(core, VP9_WAIT_FLAG, 1);

	/* clear mailbox पूर्णांकerrupt */
	amvdec_ग_लिखो_करोs(core, HEVC_ASSIST_MBOX1_CLR_REG, 1);
	/* enable mailbox पूर्णांकerrupt */
	amvdec_ग_लिखो_करोs(core, HEVC_ASSIST_MBOX1_MASK, 1);
	/* disable PSCALE क्रम hardware sharing */
	amvdec_ग_लिखो_करोs(core, HEVC_PSCALE_CTRL, 0);
	/* Let the uCode करो all the parsing */
	amvdec_ग_लिखो_करोs(core, NAL_SEARCH_CTL, 0x8);

	amvdec_ग_लिखो_करोs(core, DECODE_STOP_POS, 0);
	amvdec_ग_लिखो_करोs(core, VP9_DECODE_MODE, DECODE_MODE_SINGLE);

	pr_debug("decode_count: %u; decode_size: %u\n",
		 amvdec_पढ़ो_करोs(core, HEVC_DECODE_COUNT),
		 amvdec_पढ़ो_करोs(core, HEVC_DECODE_SIZE));

	vp9_loop_filter_init(core, vp9);

	INIT_LIST_HEAD(&vp9->ref_frames_list);
	mutex_init(&vp9->lock);
	स_रखो(&vp9->ref_frame_map, -1, माप(vp9->ref_frame_map));
	स_रखो(&vp9->next_ref_frame_map, -1, माप(vp9->next_ref_frame_map));
	क्रम (i = 0; i < REFS_PER_FRAME; ++i)
		vp9->frame_refs[i] = शून्य;
	sess->priv = vp9;

	वापस 0;

मुक्त_vp9:
	kमुक्त(vp9);
	वापस ret;
पूर्ण

अटल पूर्णांक codec_vp9_stop(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_vp9 *vp9 = sess->priv;

	mutex_lock(&vp9->lock);
	अगर (vp9->workspace_vaddr)
		dma_मुक्त_coherent(core->dev, SIZE_WORKSPACE,
				  vp9->workspace_vaddr,
				  vp9->workspace_paddr);

	codec_hevc_मुक्त_fbc_buffers(sess, &vp9->common);
	mutex_unlock(&vp9->lock);

	वापस 0;
पूर्ण

/*
 * Program LAST & GOLDEN frames पूर्णांकo the motion compensation reference cache
 * controller
 */
अटल व्योम codec_vp9_set_mcrcc(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_vp9 *vp9 = sess->priv;
	u32 val;

	/* Reset mcrcc */
	amvdec_ग_लिखो_करोs(core, HEVCD_MCRCC_CTL1, 0x2);
	/* Disable on I-frame */
	अगर (vp9->cur_frame->type == KEY_FRAME || vp9->cur_frame->पूर्णांकra_only) अणु
		amvdec_ग_लिखो_करोs(core, HEVCD_MCRCC_CTL1, 0x0);
		वापस;
	पूर्ण

	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDR, BIT(1));
	val = amvdec_पढ़ो_करोs(core, HEVCD_MPP_ANC_CANVAS_DATA_ADDR) & 0xffff;
	val |= (val << 16);
	amvdec_ग_लिखो_करोs(core, HEVCD_MCRCC_CTL2, val);
	val = amvdec_पढ़ो_करोs(core, HEVCD_MPP_ANC_CANVAS_DATA_ADDR) & 0xffff;
	val |= (val << 16);
	amvdec_ग_लिखो_करोs(core, HEVCD_MCRCC_CTL3, val);

	/* Enable mcrcc progressive-mode */
	amvdec_ग_लिखो_करोs(core, HEVCD_MCRCC_CTL1, 0xff0);
पूर्ण

अटल व्योम codec_vp9_set_sao(काष्ठा amvdec_session *sess,
			      काष्ठा vb2_buffer *vb)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_vp9 *vp9 = sess->priv;

	dma_addr_t buf_y_paddr;
	dma_addr_t buf_u_v_paddr;
	u32 val;

	अगर (codec_hevc_use_करोwnsample(sess->pixfmt_cap, vp9->is_10bit))
		buf_y_paddr =
			vp9->common.fbc_buffer_paddr[vb->index];
	अन्यथा
		buf_y_paddr =
		       vb2_dma_contig_plane_dma_addr(vb, 0);

	अगर (codec_hevc_use_fbc(sess->pixfmt_cap, vp9->is_10bit)) अणु
		val = amvdec_पढ़ो_करोs(core, HEVC_SAO_CTRL5) & ~0xff0200;
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_CTRL5, val);
		amvdec_ग_लिखो_करोs(core, HEVC_CM_BODY_START_ADDR, buf_y_paddr);
	पूर्ण

	अगर (sess->pixfmt_cap == V4L2_PIX_FMT_NV12M) अणु
		buf_y_paddr =
		       vb2_dma_contig_plane_dma_addr(vb, 0);
		buf_u_v_paddr =
		       vb2_dma_contig_plane_dma_addr(vb, 1);
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_Y_START_ADDR, buf_y_paddr);
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_C_START_ADDR, buf_u_v_paddr);
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_Y_WPTR, buf_y_paddr);
		amvdec_ग_लिखो_करोs(core, HEVC_SAO_C_WPTR, buf_u_v_paddr);
	पूर्ण

	अगर (codec_hevc_use_mmu(core->platक्रमm->revision, sess->pixfmt_cap,
			       vp9->is_10bit)) अणु
		amvdec_ग_लिखो_करोs(core, HEVC_CM_HEADER_START_ADDR,
				 vp9->common.mmu_header_paddr[vb->index]);
		/* use HEVC_CM_HEADER_START_ADDR */
		amvdec_ग_लिखो_करोs_bits(core, HEVC_SAO_CTRL5, BIT(10));
	पूर्ण

	amvdec_ग_लिखो_करोs(core, HEVC_SAO_Y_LENGTH,
			 amvdec_get_output_size(sess));
	amvdec_ग_लिखो_करोs(core, HEVC_SAO_C_LENGTH,
			 (amvdec_get_output_size(sess) / 2));

	अगर (core->platक्रमm->revision >= VDEC_REVISION_G12A) अणु
		amvdec_clear_करोs_bits(core, HEVC_DBLK_CFGB,
				      BIT(4) | BIT(5) | BIT(8) | BIT(9));
		/* enable first, compressed ग_लिखो */
		अगर (codec_hevc_use_fbc(sess->pixfmt_cap, vp9->is_10bit))
			amvdec_ग_लिखो_करोs_bits(core, HEVC_DBLK_CFGB, BIT(8));

		/* enable second, uncompressed ग_लिखो */
		अगर (sess->pixfmt_cap == V4L2_PIX_FMT_NV12M)
			amvdec_ग_लिखो_करोs_bits(core, HEVC_DBLK_CFGB, BIT(9));

		/* dblk pipeline mode=1 क्रम perक्रमmance */
		अगर (sess->width >= 1280)
			amvdec_ग_लिखो_करोs_bits(core, HEVC_DBLK_CFGB, BIT(4));

		pr_debug("HEVC_DBLK_CFGB: %08X\n",
			 amvdec_पढ़ो_करोs(core, HEVC_DBLK_CFGB));
	पूर्ण

	val = amvdec_पढ़ो_करोs(core, HEVC_SAO_CTRL1) & ~0x3ff0;
	val |= 0xff0; /* Set endianness क्रम 2-bytes swaps (nv12) */
	अगर (core->platक्रमm->revision < VDEC_REVISION_G12A) अणु
		val &= ~0x3;
		अगर (!codec_hevc_use_fbc(sess->pixfmt_cap, vp9->is_10bit))
			val |= BIT(0); /* disable cm compression */
		/* TOFIX: Handle Amlogic Framebuffer compression */
	पूर्ण

	amvdec_ग_लिखो_करोs(core, HEVC_SAO_CTRL1, val);
	pr_debug("HEVC_SAO_CTRL1: %08X\n", val);

	/* no करोwnscale क्रम NV12 */
	val = amvdec_पढ़ो_करोs(core, HEVC_SAO_CTRL5) & ~0xff0000;
	amvdec_ग_लिखो_करोs(core, HEVC_SAO_CTRL5, val);

	val = amvdec_पढ़ो_करोs(core, HEVCD_IPP_AXIIF_CONFIG) & ~0x30;
	val |= 0xf;
	val &= ~BIT(12); /* NV12 */
	amvdec_ग_लिखो_करोs(core, HEVCD_IPP_AXIIF_CONFIG, val);
पूर्ण

अटल dma_addr_t codec_vp9_get_frame_mv_paddr(काष्ठा codec_vp9 *vp9,
					       काष्ठा vp9_frame *frame)
अणु
	वापस vp9->workspace_paddr + MPRED_MV_OFFSET +
	       (frame->index * MPRED_MV_BUF_SIZE);
पूर्ण

अटल व्योम codec_vp9_set_mpred_mv(काष्ठा amvdec_core *core,
				   काष्ठा codec_vp9 *vp9)
अणु
	पूर्णांक mpred_mv_rd_end_addr;
	पूर्णांक use_prev_frame_mvs = vp9->prev_frame->width ==
					vp9->cur_frame->width &&
				 vp9->prev_frame->height ==
					vp9->cur_frame->height &&
				 !vp9->prev_frame->पूर्णांकra_only &&
				 vp9->prev_frame->show &&
				 vp9->prev_frame->type != KEY_FRAME;

	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_CTRL3, 0x24122412);
	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_ABV_START_ADDR,
			 vp9->workspace_paddr + MPRED_ABV_OFFSET);

	amvdec_clear_करोs_bits(core, HEVC_MPRED_CTRL4, BIT(6));
	अगर (use_prev_frame_mvs)
		amvdec_ग_लिखो_करोs_bits(core, HEVC_MPRED_CTRL4, BIT(6));

	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_MV_WR_START_ADDR,
			 codec_vp9_get_frame_mv_paddr(vp9, vp9->cur_frame));
	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_MV_WPTR,
			 codec_vp9_get_frame_mv_paddr(vp9, vp9->cur_frame));

	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_MV_RD_START_ADDR,
			 codec_vp9_get_frame_mv_paddr(vp9, vp9->prev_frame));
	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_MV_RPTR,
			 codec_vp9_get_frame_mv_paddr(vp9, vp9->prev_frame));

	mpred_mv_rd_end_addr =
			codec_vp9_get_frame_mv_paddr(vp9, vp9->prev_frame) +
			(vp9->lcu_total * MV_MEM_UNIT);
	amvdec_ग_लिखो_करोs(core, HEVC_MPRED_MV_RD_END_ADDR, mpred_mv_rd_end_addr);
पूर्ण

अटल व्योम codec_vp9_update_next_ref(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;
	u32 buf_idx = vp9->cur_frame->index;
	पूर्णांक ref_index = 0;
	पूर्णांक refresh_frame_flags;
	पूर्णांक mask;

	refresh_frame_flags = vp9->cur_frame->type == KEY_FRAME ?
				0xff : param->p.refresh_frame_flags;

	क्रम (mask = refresh_frame_flags; mask; mask >>= 1) अणु
		pr_debug("mask=%08X; ref_index=%d\n", mask, ref_index);
		अगर (mask & 1)
			vp9->next_ref_frame_map[ref_index] = buf_idx;
		अन्यथा
			vp9->next_ref_frame_map[ref_index] =
				vp9->ref_frame_map[ref_index];

		++ref_index;
	पूर्ण

	क्रम (; ref_index < REF_FRAMES; ++ref_index)
		vp9->next_ref_frame_map[ref_index] =
			vp9->ref_frame_map[ref_index];
पूर्ण

अटल व्योम codec_vp9_save_refs(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;
	पूर्णांक i;

	क्रम (i = 0; i < REFS_PER_FRAME; ++i) अणु
		स्थिर पूर्णांक ref = (param->p.ref_info >>
				 (((REFS_PER_FRAME - i - 1) * 4) + 1)) & 0x7;

		अगर (vp9->ref_frame_map[ref] < 0)
			जारी;

		pr_warn("%s: FIXME, would need to save ref %d\n",
			__func__, vp9->ref_frame_map[ref]);
	पूर्ण
पूर्ण

अटल व्योम codec_vp9_update_ref(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;
	पूर्णांक ref_index = 0;
	पूर्णांक mask;
	पूर्णांक refresh_frame_flags;

	अगर (!vp9->cur_frame)
		वापस;

	refresh_frame_flags = vp9->cur_frame->type == KEY_FRAME ?
				0xff : param->p.refresh_frame_flags;

	क्रम (mask = refresh_frame_flags; mask; mask >>= 1) अणु
		vp9->ref_frame_map[ref_index] =
			vp9->next_ref_frame_map[ref_index];
		++ref_index;
	पूर्ण

	अगर (param->p.show_existing_frame)
		वापस;

	क्रम (; ref_index < REF_FRAMES; ++ref_index)
		vp9->ref_frame_map[ref_index] =
			vp9->next_ref_frame_map[ref_index];
पूर्ण

अटल काष्ठा vp9_frame *codec_vp9_get_frame_by_idx(काष्ठा codec_vp9 *vp9,
						    पूर्णांक idx)
अणु
	काष्ठा vp9_frame *frame;

	list_क्रम_each_entry(frame, &vp9->ref_frames_list, list) अणु
		अगर (frame->index == idx)
			वापस frame;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम codec_vp9_sync_ref(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;
	पूर्णांक i;

	क्रम (i = 0; i < REFS_PER_FRAME; ++i) अणु
		स्थिर पूर्णांक ref = (param->p.ref_info >>
				 (((REFS_PER_FRAME - i - 1) * 4) + 1)) & 0x7;
		स्थिर पूर्णांक idx = vp9->ref_frame_map[ref];

		vp9->frame_refs[i] = codec_vp9_get_frame_by_idx(vp9, idx);
		अगर (!vp9->frame_refs[i])
			pr_warn("%s: couldn't find VP9 ref %d\n", __func__,
				idx);
	पूर्ण
पूर्ण

अटल व्योम codec_vp9_set_refs(काष्ठा amvdec_session *sess,
			       काष्ठा codec_vp9 *vp9)
अणु
	काष्ठा amvdec_core *core = sess->core;
	पूर्णांक i;

	क्रम (i = 0; i < REFS_PER_FRAME; ++i) अणु
		काष्ठा vp9_frame *frame = vp9->frame_refs[i];
		पूर्णांक id_y;
		पूर्णांक id_u_v;

		अगर (!frame)
			जारी;

		अगर (codec_hevc_use_fbc(sess->pixfmt_cap, vp9->is_10bit)) अणु
			id_y = frame->index;
			id_u_v = id_y;
		पूर्ण अन्यथा अणु
			id_y = frame->index * 2;
			id_u_v = id_y + 1;
		पूर्ण

		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_DATA_ADDR,
				 (id_u_v << 16) | (id_u_v << 8) | id_y);
	पूर्ण
पूर्ण

अटल व्योम codec_vp9_set_mc(काष्ठा amvdec_session *sess,
			     काष्ठा codec_vp9 *vp9)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 scale = 0;
	u32 sz;
	पूर्णांक i;

	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDR, 1);
	codec_vp9_set_refs(sess, vp9);
	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDR,
			 (16 << 8) | 1);
	codec_vp9_set_refs(sess, vp9);

	amvdec_ग_लिखो_करोs(core, VP9D_MPP_REFINFO_TBL_ACCCONFIG, BIT(2));
	क्रम (i = 0; i < REFS_PER_FRAME; ++i) अणु
		अगर (!vp9->frame_refs[i])
			जारी;

		अगर (vp9->frame_refs[i]->width != vp9->width ||
		    vp9->frame_refs[i]->height != vp9->height)
			scale = 1;

		sz = amvdec_am21c_body_size(vp9->frame_refs[i]->width,
					    vp9->frame_refs[i]->height);

		amvdec_ग_लिखो_करोs(core, VP9D_MPP_REFINFO_DATA,
				 vp9->frame_refs[i]->width);
		amvdec_ग_लिखो_करोs(core, VP9D_MPP_REFINFO_DATA,
				 vp9->frame_refs[i]->height);
		amvdec_ग_लिखो_करोs(core, VP9D_MPP_REFINFO_DATA,
				 (vp9->frame_refs[i]->width << 14) /
				 vp9->width);
		amvdec_ग_लिखो_करोs(core, VP9D_MPP_REFINFO_DATA,
				 (vp9->frame_refs[i]->height << 14) /
				 vp9->height);
		amvdec_ग_लिखो_करोs(core, VP9D_MPP_REFINFO_DATA, sz >> 5);
	पूर्ण

	amvdec_ग_लिखो_करोs(core, VP9D_MPP_REF_SCALE_ENBL, scale);
पूर्ण

अटल काष्ठा vp9_frame *codec_vp9_get_new_frame(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;
	जोड़ rpm_param *param = &vp9->rpm_param;
	काष्ठा vb2_v4l2_buffer *vbuf;
	काष्ठा vp9_frame *new_frame;

	new_frame = kzalloc(माप(*new_frame), GFP_KERNEL);
	अगर (!new_frame)
		वापस शून्य;

	vbuf = v4l2_m2m_dst_buf_हटाओ(sess->m2m_ctx);
	अगर (!vbuf) अणु
		dev_err(sess->core->dev, "No dst buffer available\n");
		kमुक्त(new_frame);
		वापस शून्य;
	पूर्ण

	जबतक (codec_vp9_get_frame_by_idx(vp9, vbuf->vb2_buf.index)) अणु
		काष्ठा vb2_v4l2_buffer *old_vbuf = vbuf;

		vbuf = v4l2_m2m_dst_buf_हटाओ(sess->m2m_ctx);
		v4l2_m2m_buf_queue(sess->m2m_ctx, old_vbuf);
		अगर (!vbuf) अणु
			dev_err(sess->core->dev, "No dst buffer available\n");
			kमुक्त(new_frame);
			वापस शून्य;
		पूर्ण
	पूर्ण

	new_frame->vbuf = vbuf;
	new_frame->index = vbuf->vb2_buf.index;
	new_frame->पूर्णांकra_only = param->p.पूर्णांकra_only;
	new_frame->show = param->p.show_frame;
	new_frame->type = param->p.frame_type;
	new_frame->width = vp9->width;
	new_frame->height = vp9->height;
	list_add_tail(&new_frame->list, &vp9->ref_frames_list);
	vp9->frames_num++;

	वापस new_frame;
पूर्ण

अटल व्योम codec_vp9_show_existing_frame(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;

	अगर (!param->p.show_existing_frame)
		वापस;

	pr_debug("showing frame %u\n", param->p.frame_to_show_idx);
पूर्ण

अटल व्योम codec_vp9_rm_noshow_frame(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;
	काष्ठा vp9_frame *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &vp9->ref_frames_list, list) अणु
		अगर (पंचांगp->show)
			जारी;

		pr_debug("rm noshow: %u\n", पंचांगp->index);
		v4l2_m2m_buf_queue(sess->m2m_ctx, पंचांगp->vbuf);
		list_del(&पंचांगp->list);
		kमुक्त(पंचांगp);
		vp9->frames_num--;
		वापस;
	पूर्ण
पूर्ण

अटल व्योम codec_vp9_process_frame(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_vp9 *vp9 = sess->priv;
	जोड़ rpm_param *param = &vp9->rpm_param;
	पूर्णांक पूर्णांकra_only;

	अगर (!param->p.show_frame)
		codec_vp9_rm_noshow_frame(sess);

	vp9->cur_frame = codec_vp9_get_new_frame(sess);
	अगर (!vp9->cur_frame)
		वापस;

	pr_debug("frame %d: type: %08X; show_exist: %u; show: %u, intra_only: %u\n",
		 vp9->cur_frame->index,
		 param->p.frame_type, param->p.show_existing_frame,
		 param->p.show_frame, param->p.पूर्णांकra_only);

	अगर (param->p.frame_type != KEY_FRAME)
		codec_vp9_sync_ref(vp9);
	codec_vp9_update_next_ref(vp9);
	codec_vp9_show_existing_frame(vp9);

	अगर (codec_hevc_use_mmu(core->platक्रमm->revision, sess->pixfmt_cap,
			       vp9->is_10bit))
		codec_hevc_fill_mmu_map(sess, &vp9->common,
					&vp9->cur_frame->vbuf->vb2_buf);

	पूर्णांकra_only = param->p.show_frame ? 0 : param->p.पूर्णांकra_only;

	/* clear mpred (क्रम keyframe only) */
	अगर (param->p.frame_type != KEY_FRAME && !पूर्णांकra_only) अणु
		codec_vp9_set_mc(sess, vp9);
		codec_vp9_set_mpred_mv(core, vp9);
	पूर्ण अन्यथा अणु
		amvdec_clear_करोs_bits(core, HEVC_MPRED_CTRL4, BIT(6));
	पूर्ण

	amvdec_ग_लिखो_करोs(core, HEVC_PARSER_PICTURE_SIZE,
			 (vp9->height << 16) | vp9->width);
	codec_vp9_set_mcrcc(sess);
	codec_vp9_set_sao(sess, &vp9->cur_frame->vbuf->vb2_buf);

	vp9_loop_filter_frame_init(core, &vp9->seg_4lf,
				   &vp9->lfi, &vp9->lf,
				   vp9->शेष_filt_lvl);

	/* ask uCode to start decoding */
	amvdec_ग_लिखो_करोs(core, VP9_DEC_STATUS_REG, VP9_10B_DECODE_SLICE);
पूर्ण

अटल व्योम codec_vp9_process_lf(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;
	पूर्णांक i;

	vp9->lf.mode_ref_delta_enabled = param->p.mode_ref_delta_enabled;
	vp9->lf.sharpness_level = param->p.sharpness_level;
	vp9->शेष_filt_lvl = param->p.filter_level;
	vp9->seg_4lf.enabled = param->p.seg_enabled;
	vp9->seg_4lf.असल_delta = param->p.seg_असल_delta;

	क्रम (i = 0; i < 4; i++)
		vp9->lf.ref_deltas[i] = param->p.ref_deltas[i];

	क्रम (i = 0; i < 2; i++)
		vp9->lf.mode_deltas[i] = param->p.mode_deltas[i];

	क्रम (i = 0; i < MAX_SEGMENTS; i++)
		vp9->seg_4lf.feature_mask[i] =
			(param->p.seg_lf_info[i] & 0x8000) ?
				(1 << SEG_LVL_ALT_LF) : 0;

	क्रम (i = 0; i < MAX_SEGMENTS; i++)
		vp9->seg_4lf.feature_data[i][SEG_LVL_ALT_LF] =
			(param->p.seg_lf_info[i] & 0x100) ?
				-(param->p.seg_lf_info[i] & 0x3f)
				: (param->p.seg_lf_info[i] & 0x3f);
पूर्ण

अटल व्योम codec_vp9_resume(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;

	mutex_lock(&vp9->lock);
	अगर (codec_hevc_setup_buffers(sess, &vp9->common, vp9->is_10bit)) अणु
		mutex_unlock(&vp9->lock);
		amvdec_पात(sess);
		वापस;
	पूर्ण

	codec_vp9_setup_workspace(sess, vp9);
	codec_hevc_setup_decode_head(sess, vp9->is_10bit);
	codec_vp9_process_lf(vp9);
	codec_vp9_process_frame(sess);

	mutex_unlock(&vp9->lock);
पूर्ण

/*
 * The RPM section within the workspace contains
 * many inक्रमmation regarding the parsed bitstream
 */
अटल व्योम codec_vp9_fetch_rpm(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;
	u16 *rpm_vaddr = vp9->workspace_vaddr + RPM_OFFSET;
	पूर्णांक i, j;

	क्रम (i = 0; i < RPM_BUF_SIZE; i += 4)
		क्रम (j = 0; j < 4; j++)
			vp9->rpm_param.l.data[i + j] = rpm_vaddr[i + 3 - j];
पूर्ण

अटल पूर्णांक codec_vp9_process_rpm(काष्ठा codec_vp9 *vp9)
अणु
	जोड़ rpm_param *param = &vp9->rpm_param;
	पूर्णांक src_changed = 0;
	पूर्णांक is_10bit = 0;
	पूर्णांक pic_width_64 = ALIGN(param->p.width, 64);
	पूर्णांक pic_height_32 = ALIGN(param->p.height, 32);
	पूर्णांक pic_width_lcu  = (pic_width_64 % LCU_SIZE) ?
				pic_width_64 / LCU_SIZE  + 1
				: pic_width_64 / LCU_SIZE;
	पूर्णांक pic_height_lcu = (pic_height_32 % LCU_SIZE) ?
				pic_height_32 / LCU_SIZE + 1
				: pic_height_32 / LCU_SIZE;
	vp9->lcu_total = pic_width_lcu * pic_height_lcu;

	अगर (param->p.bit_depth == 10)
		is_10bit = 1;

	अगर (vp9->width != param->p.width || vp9->height != param->p.height ||
	    vp9->is_10bit != is_10bit)
		src_changed = 1;

	vp9->width = param->p.width;
	vp9->height = param->p.height;
	vp9->is_10bit = is_10bit;

	pr_debug("width: %u; height: %u; is_10bit: %d; src_changed: %d\n",
		 vp9->width, vp9->height, is_10bit, src_changed);

	वापस src_changed;
पूर्ण

अटल bool codec_vp9_is_ref(काष्ठा codec_vp9 *vp9, काष्ठा vp9_frame *frame)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < REF_FRAMES; ++i)
		अगर (vp9->ref_frame_map[i] == frame->index)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम codec_vp9_show_frame(काष्ठा amvdec_session *sess)
अणु
	काष्ठा codec_vp9 *vp9 = sess->priv;
	काष्ठा vp9_frame *पंचांगp, *n;

	list_क्रम_each_entry_safe(पंचांगp, n, &vp9->ref_frames_list, list) अणु
		अगर (!पंचांगp->show || पंचांगp == vp9->cur_frame)
			जारी;

		अगर (!पंचांगp->करोne) अणु
			pr_debug("Doning %u\n", पंचांगp->index);
			amvdec_dst_buf_करोne(sess, पंचांगp->vbuf, V4L2_FIELD_NONE);
			पंचांगp->करोne = 1;
			vp9->frames_num--;
		पूर्ण

		अगर (codec_vp9_is_ref(vp9, पंचांगp) || पंचांगp == vp9->prev_frame)
			जारी;

		pr_debug("deleting %d\n", पंचांगp->index);
		list_del(&पंचांगp->list);
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम vp9_tree_merge_probs(अचिन्हित पूर्णांक *prev_prob,
				 अचिन्हित पूर्णांक *cur_prob,
				 पूर्णांक coef_node_start, पूर्णांक tree_left,
				 पूर्णांक tree_right,
				 पूर्णांक tree_i, पूर्णांक node)
अणु
	पूर्णांक prob_32, prob_res, prob_shअगरt;
	पूर्णांक pre_prob, new_prob;
	पूर्णांक den, m_count, get_prob, factor;

	prob_32 = prev_prob[coef_node_start / 4 * 2];
	prob_res = coef_node_start & 3;
	prob_shअगरt = prob_res * 8;
	pre_prob = (prob_32 >> prob_shअगरt) & 0xff;

	den = tree_left + tree_right;

	अगर (den == 0) अणु
		new_prob = pre_prob;
	पूर्ण अन्यथा अणु
		m_count = den < MODE_MV_COUNT_SAT ? den : MODE_MV_COUNT_SAT;
		get_prob =
			clip_prob(भाग_r32(((पूर्णांक64_t)tree_left * 256 +
					   (den >> 1)),
					  den));

		/* weighted_prob */
		factor = count_to_update_factor[m_count];
		new_prob = round_घातer_of_two(pre_prob * (256 - factor) +
					      get_prob * factor, 8);
	पूर्ण

	cur_prob[coef_node_start / 4 * 2] =
		(cur_prob[coef_node_start / 4 * 2] & (~(0xff << prob_shअगरt))) |
		(new_prob << prob_shअगरt);
पूर्ण

अटल व्योम adapt_coef_probs_cxt(अचिन्हित पूर्णांक *prev_prob,
				 अचिन्हित पूर्णांक *cur_prob,
				 अचिन्हित पूर्णांक *count,
				 पूर्णांक update_factor,
				 पूर्णांक cxt_num,
				 पूर्णांक coef_cxt_start,
				 पूर्णांक coef_count_cxt_start)
अणु
	पूर्णांक prob_32, prob_res, prob_shअगरt;
	पूर्णांक pre_prob, new_prob;
	पूर्णांक num, den, m_count, get_prob, factor;
	पूर्णांक node, coef_node_start;
	पूर्णांक count_sat = 24;
	पूर्णांक cxt;

	क्रम (cxt = 0; cxt < cxt_num; cxt++) अणु
		स्थिर पूर्णांक n0 = count[coef_count_cxt_start];
		स्थिर पूर्णांक n1 = count[coef_count_cxt_start + 1];
		स्थिर पूर्णांक n2 = count[coef_count_cxt_start + 2];
		स्थिर पूर्णांक neob = count[coef_count_cxt_start + 3];
		स्थिर पूर्णांक nneob = count[coef_count_cxt_start + 4];
		स्थिर अचिन्हित पूर्णांक branch_ct[3][2] = अणु
			अणु neob, nneob पूर्ण,
			अणु n0, n1 + n2 पूर्ण,
			अणु n1, n2 पूर्ण
		पूर्ण;

		coef_node_start = coef_cxt_start;
		क्रम (node = 0 ; node < 3 ; node++) अणु
			prob_32 = prev_prob[coef_node_start / 4 * 2];
			prob_res = coef_node_start & 3;
			prob_shअगरt = prob_res * 8;
			pre_prob = (prob_32 >> prob_shअगरt) & 0xff;

			/* get binary prob */
			num = branch_ct[node][0];
			den = branch_ct[node][0] + branch_ct[node][1];
			m_count = den < count_sat ? den : count_sat;

			get_prob = (den == 0) ?
					128u :
					clip_prob(भाग_r32(((पूर्णांक64_t)num * 256 +
							  (den >> 1)), den));

			factor = update_factor * m_count / count_sat;
			new_prob =
				round_घातer_of_two(pre_prob * (256 - factor) +
						   get_prob * factor, 8);

			cur_prob[coef_node_start / 4 * 2] =
				(cur_prob[coef_node_start / 4 * 2] &
				 (~(0xff << prob_shअगरt))) |
				(new_prob << prob_shअगरt);

			coef_node_start += 1;
		पूर्ण

		coef_cxt_start = coef_cxt_start + 3;
		coef_count_cxt_start = coef_count_cxt_start + 5;
	पूर्ण
पूर्ण

अटल व्योम adapt_coef_probs(पूर्णांक prev_kf, पूर्णांक cur_kf, पूर्णांक pre_fc,
			     अचिन्हित पूर्णांक *prev_prob, अचिन्हित पूर्णांक *cur_prob,
			     अचिन्हित पूर्णांक *count)
अणु
	पूर्णांक tx_size, coef_tx_size_start, coef_count_tx_size_start;
	पूर्णांक plane, coef_plane_start, coef_count_plane_start;
	पूर्णांक type, coef_type_start, coef_count_type_start;
	पूर्णांक band, coef_band_start, coef_count_band_start;
	पूर्णांक cxt_num;
	पूर्णांक coef_cxt_start, coef_count_cxt_start;
	पूर्णांक node, coef_node_start, coef_count_node_start;

	पूर्णांक tree_i, tree_left, tree_right;
	पूर्णांक mvd_i;

	पूर्णांक update_factor = cur_kf ? 112 : (prev_kf ? 128 : 112);

	पूर्णांक prob_32;
	पूर्णांक prob_res;
	पूर्णांक prob_shअगरt;
	पूर्णांक pre_prob;

	पूर्णांक den;
	पूर्णांक get_prob;
	पूर्णांक m_count;
	पूर्णांक factor;

	पूर्णांक new_prob;

	क्रम (tx_size = 0 ; tx_size < 4 ; tx_size++) अणु
		coef_tx_size_start = VP9_COEF_START +
				tx_size * 4 * VP9_COEF_SIZE_ONE_SET;
		coef_count_tx_size_start = VP9_COEF_COUNT_START +
				tx_size * 4 * VP9_COEF_COUNT_SIZE_ONE_SET;
		coef_plane_start = coef_tx_size_start;
		coef_count_plane_start = coef_count_tx_size_start;

		क्रम (plane = 0 ; plane < 2 ; plane++) अणु
			coef_type_start = coef_plane_start;
			coef_count_type_start = coef_count_plane_start;

			क्रम (type = 0 ; type < 2 ; type++) अणु
				coef_band_start = coef_type_start;
				coef_count_band_start = coef_count_type_start;

				क्रम (band = 0 ; band < 6 ; band++) अणु
					अगर (band == 0)
						cxt_num = 3;
					अन्यथा
						cxt_num = 6;
					coef_cxt_start = coef_band_start;
					coef_count_cxt_start =
						coef_count_band_start;

					adapt_coef_probs_cxt(prev_prob,
							     cur_prob,
							     count,
							     update_factor,
							     cxt_num,
							     coef_cxt_start,
							coef_count_cxt_start);

					अगर (band == 0) अणु
						coef_band_start += 10;
						coef_count_band_start += 15;
					पूर्ण अन्यथा अणु
						coef_band_start += 18;
						coef_count_band_start += 30;
					पूर्ण
				पूर्ण
				coef_type_start += VP9_COEF_SIZE_ONE_SET;
				coef_count_type_start +=
					VP9_COEF_COUNT_SIZE_ONE_SET;
			पूर्ण

			coef_plane_start += 2 * VP9_COEF_SIZE_ONE_SET;
			coef_count_plane_start +=
				2 * VP9_COEF_COUNT_SIZE_ONE_SET;
		पूर्ण
	पूर्ण

	अगर (cur_kf == 0) अणु
		/* mode_mv_merge_probs - merge_पूर्णांकra_पूर्णांकer_prob */
		क्रम (coef_count_node_start = VP9_INTRA_INTER_COUNT_START;
		     coef_count_node_start < (VP9_MV_CLASS0_HP_1_COUNT_START +
					      VP9_MV_CLASS0_HP_1_COUNT_SIZE);
		     coef_count_node_start += 2) अणु
			अगर (coef_count_node_start ==
					VP9_INTRA_INTER_COUNT_START)
				coef_node_start = VP9_INTRA_INTER_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_COMP_INTER_COUNT_START)
				coef_node_start = VP9_COMP_INTER_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_TX_MODE_COUNT_START)
				coef_node_start = VP9_TX_MODE_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_SKIP_COUNT_START)
				coef_node_start = VP9_SKIP_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_MV_SIGN_0_COUNT_START)
				coef_node_start = VP9_MV_SIGN_0_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_MV_SIGN_1_COUNT_START)
				coef_node_start = VP9_MV_SIGN_1_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_MV_BITS_0_COUNT_START)
				coef_node_start = VP9_MV_BITS_0_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_MV_BITS_1_COUNT_START)
				coef_node_start = VP9_MV_BITS_1_START;
			अन्यथा अगर (coef_count_node_start ==
					VP9_MV_CLASS0_HP_0_COUNT_START)
				coef_node_start = VP9_MV_CLASS0_HP_0_START;

			den = count[coef_count_node_start] +
			      count[coef_count_node_start + 1];

			prob_32 = prev_prob[coef_node_start / 4 * 2];
			prob_res = coef_node_start & 3;
			prob_shअगरt = prob_res * 8;
			pre_prob = (prob_32 >> prob_shअगरt) & 0xff;

			अगर (den == 0) अणु
				new_prob = pre_prob;
			पूर्ण अन्यथा अणु
				m_count = den < MODE_MV_COUNT_SAT ?
						den : MODE_MV_COUNT_SAT;
				get_prob =
				clip_prob(भाग_r32(((पूर्णांक64_t)
					count[coef_count_node_start] * 256 +
					(den >> 1)),
					den));

				/* weighted prob */
				factor = count_to_update_factor[m_count];
				new_prob =
					round_घातer_of_two(pre_prob *
							   (256 - factor) +
							   get_prob * factor,
							   8);
			पूर्ण

			cur_prob[coef_node_start / 4 * 2] =
				(cur_prob[coef_node_start / 4 * 2] &
				 (~(0xff << prob_shअगरt))) |
				(new_prob << prob_shअगरt);

			coef_node_start = coef_node_start + 1;
		पूर्ण

		coef_node_start = VP9_INTER_MODE_START;
		coef_count_node_start = VP9_INTER_MODE_COUNT_START;
		क्रम (tree_i = 0 ; tree_i < 7 ; tree_i++) अणु
			क्रम (node = 0 ; node < 3 ; node++) अणु
				अचिन्हित पूर्णांक start = coef_count_node_start;

				चयन (node) अणु
				हाल 2:
					tree_left = count[start + 1];
					tree_right = count[start + 3];
					अवरोध;
				हाल 1:
					tree_left = count[start + 0];
					tree_right = count[start + 1] +
						     count[start + 3];
					अवरोध;
				शेष:
					tree_left = count[start + 2];
					tree_right = count[start + 0] +
						     count[start + 1] +
						     count[start + 3];
					अवरोध;
				पूर्ण

				vp9_tree_merge_probs(prev_prob, cur_prob,
						     coef_node_start,
						     tree_left, tree_right,
						     tree_i, node);

				coef_node_start = coef_node_start + 1;
			पूर्ण

			coef_count_node_start = coef_count_node_start + 4;
		पूर्ण

		coef_node_start = VP9_IF_Y_MODE_START;
		coef_count_node_start = VP9_IF_Y_MODE_COUNT_START;
		क्रम (tree_i = 0 ; tree_i < 14 ; tree_i++) अणु
			क्रम (node = 0 ; node < 9 ; node++) अणु
				अचिन्हित पूर्णांक start = coef_count_node_start;

				चयन (node) अणु
				हाल 8:
					tree_left =
						count[start + D153_PRED];
					tree_right =
						count[start + D207_PRED];
					अवरोध;
				हाल 7:
					tree_left =
						count[start + D63_PRED];
					tree_right =
						count[start + D207_PRED] +
						count[start + D153_PRED];
					अवरोध;
				हाल 6:
					tree_left =
						count[start + D45_PRED];
					tree_right =
						count[start + D207_PRED] +
						count[start + D153_PRED] +
						count[start + D63_PRED];
					अवरोध;
				हाल 5:
					tree_left =
						count[start + D135_PRED];
					tree_right =
						count[start + D117_PRED];
					अवरोध;
				हाल 4:
					tree_left =
						count[start + H_PRED];
					tree_right =
						count[start + D117_PRED] +
						count[start + D135_PRED];
					अवरोध;
				हाल 3:
					tree_left =
						count[start + H_PRED] +
						count[start + D117_PRED] +
						count[start + D135_PRED];
					tree_right =
						count[start + D45_PRED] +
						count[start + D207_PRED] +
						count[start + D153_PRED] +
						count[start + D63_PRED];
					अवरोध;
				हाल 2:
					tree_left =
						count[start + V_PRED];
					tree_right =
						count[start + H_PRED] +
						count[start + D117_PRED] +
						count[start + D135_PRED] +
						count[start + D45_PRED] +
						count[start + D207_PRED] +
						count[start + D153_PRED] +
						count[start + D63_PRED];
					अवरोध;
				हाल 1:
					tree_left =
						count[start + TM_PRED];
					tree_right =
						count[start + V_PRED] +
						count[start + H_PRED] +
						count[start + D117_PRED] +
						count[start + D135_PRED] +
						count[start + D45_PRED] +
						count[start + D207_PRED] +
						count[start + D153_PRED] +
						count[start + D63_PRED];
					अवरोध;
				शेष:
					tree_left =
						count[start + DC_PRED];
					tree_right =
						count[start + TM_PRED] +
						count[start + V_PRED] +
						count[start + H_PRED] +
						count[start + D117_PRED] +
						count[start + D135_PRED] +
						count[start + D45_PRED] +
						count[start + D207_PRED] +
						count[start + D153_PRED] +
						count[start + D63_PRED];
					अवरोध;
				पूर्ण

				vp9_tree_merge_probs(prev_prob, cur_prob,
						     coef_node_start,
						     tree_left, tree_right,
						     tree_i, node);

				coef_node_start = coef_node_start + 1;
			पूर्ण
			coef_count_node_start = coef_count_node_start + 10;
		पूर्ण

		coef_node_start = VP9_PARTITION_P_START;
		coef_count_node_start = VP9_PARTITION_P_COUNT_START;
		क्रम (tree_i = 0 ; tree_i < 16 ; tree_i++) अणु
			क्रम (node = 0 ; node < 3 ; node++) अणु
				अचिन्हित पूर्णांक start = coef_count_node_start;

				चयन (node) अणु
				हाल 2:
					tree_left = count[start + 2];
					tree_right = count[start + 3];
					अवरोध;
				हाल 1:
					tree_left = count[start + 1];
					tree_right = count[start + 2] +
						     count[start + 3];
					अवरोध;
				शेष:
					tree_left = count[start + 0];
					tree_right = count[start + 1] +
						     count[start + 2] +
						     count[start + 3];
					अवरोध;
				पूर्ण

				vp9_tree_merge_probs(prev_prob, cur_prob,
						     coef_node_start,
						     tree_left, tree_right,
						     tree_i, node);

				coef_node_start = coef_node_start + 1;
			पूर्ण

			coef_count_node_start = coef_count_node_start + 4;
		पूर्ण

		coef_node_start = VP9_INTERP_START;
		coef_count_node_start = VP9_INTERP_COUNT_START;
		क्रम (tree_i = 0 ; tree_i < 4 ; tree_i++) अणु
			क्रम (node = 0 ; node < 2 ; node++) अणु
				अचिन्हित पूर्णांक start = coef_count_node_start;

				चयन (node) अणु
				हाल 1:
					tree_left = count[start + 1];
					tree_right = count[start + 2];
					अवरोध;
				शेष:
					tree_left = count[start + 0];
					tree_right = count[start + 1] +
						     count[start + 2];
					अवरोध;
				पूर्ण

				vp9_tree_merge_probs(prev_prob, cur_prob,
						     coef_node_start,
						     tree_left, tree_right,
						     tree_i, node);

				coef_node_start = coef_node_start + 1;
			पूर्ण
			coef_count_node_start = coef_count_node_start + 3;
		पूर्ण

		coef_node_start = VP9_MV_JOINTS_START;
		coef_count_node_start = VP9_MV_JOINTS_COUNT_START;
		क्रम (tree_i = 0 ; tree_i < 1 ; tree_i++) अणु
			क्रम (node = 0 ; node < 3 ; node++) अणु
				अचिन्हित पूर्णांक start = coef_count_node_start;

				चयन (node) अणु
				हाल 2:
					tree_left = count[start + 2];
					tree_right = count[start + 3];
					अवरोध;
				हाल 1:
					tree_left = count[start + 1];
					tree_right = count[start + 2] +
						     count[start + 3];
					अवरोध;
				शेष:
					tree_left = count[start + 0];
					tree_right = count[start + 1] +
						     count[start + 2] +
						     count[start + 3];
					अवरोध;
				पूर्ण

				vp9_tree_merge_probs(prev_prob, cur_prob,
						     coef_node_start,
						     tree_left, tree_right,
						     tree_i, node);

				coef_node_start = coef_node_start + 1;
			पूर्ण
			coef_count_node_start = coef_count_node_start + 4;
		पूर्ण

		क्रम (mvd_i = 0 ; mvd_i < 2 ; mvd_i++) अणु
			coef_node_start = mvd_i ? VP9_MV_CLASSES_1_START :
						  VP9_MV_CLASSES_0_START;
			coef_count_node_start = mvd_i ?
					VP9_MV_CLASSES_1_COUNT_START :
					VP9_MV_CLASSES_0_COUNT_START;
			tree_i = 0;
			क्रम (node = 0; node < 10; node++) अणु
				अचिन्हित पूर्णांक start = coef_count_node_start;

				चयन (node) अणु
				हाल 9:
					tree_left = count[start + 9];
					tree_right = count[start + 10];
					अवरोध;
				हाल 8:
					tree_left = count[start + 7];
					tree_right = count[start + 8];
					अवरोध;
				हाल 7:
					tree_left = count[start + 7] +
						     count[start + 8];
					tree_right = count[start + 9] +
						     count[start + 10];
					अवरोध;
				हाल 6:
					tree_left = count[start + 6];
					tree_right = count[start + 7] +
						     count[start + 8] +
						     count[start + 9] +
						     count[start + 10];
					अवरोध;
				हाल 5:
					tree_left = count[start + 4];
					tree_right = count[start + 5];
					अवरोध;
				हाल 4:
					tree_left = count[start + 4] +
						    count[start + 5];
					tree_right = count[start + 6] +
						     count[start + 7] +
						     count[start + 8] +
						     count[start + 9] +
						     count[start + 10];
					अवरोध;
				हाल 3:
					tree_left = count[start + 2];
					tree_right = count[start + 3];
					अवरोध;
				हाल 2:
					tree_left = count[start + 2] +
						    count[start + 3];
					tree_right = count[start + 4] +
						     count[start + 5] +
						     count[start + 6] +
						     count[start + 7] +
						     count[start + 8] +
						     count[start + 9] +
						     count[start + 10];
					अवरोध;
				हाल 1:
					tree_left = count[start + 1];
					tree_right = count[start + 2] +
						     count[start + 3] +
						     count[start + 4] +
						     count[start + 5] +
						     count[start + 6] +
						     count[start + 7] +
						     count[start + 8] +
						     count[start + 9] +
						     count[start + 10];
					अवरोध;
				शेष:
					tree_left = count[start + 0];
					tree_right = count[start + 1] +
						     count[start + 2] +
						     count[start + 3] +
						     count[start + 4] +
						     count[start + 5] +
						     count[start + 6] +
						     count[start + 7] +
						     count[start + 8] +
						     count[start + 9] +
						     count[start + 10];
					अवरोध;
				पूर्ण

				vp9_tree_merge_probs(prev_prob, cur_prob,
						     coef_node_start,
						     tree_left, tree_right,
						     tree_i, node);

				coef_node_start = coef_node_start + 1;
			पूर्ण

			coef_node_start = mvd_i ? VP9_MV_CLASS0_1_START :
						  VP9_MV_CLASS0_0_START;
			coef_count_node_start =	mvd_i ?
						VP9_MV_CLASS0_1_COUNT_START :
						VP9_MV_CLASS0_0_COUNT_START;
			tree_i = 0;
			node = 0;
			tree_left = count[coef_count_node_start + 0];
			tree_right = count[coef_count_node_start + 1];

			vp9_tree_merge_probs(prev_prob, cur_prob,
					     coef_node_start,
					     tree_left, tree_right,
					     tree_i, node);
			coef_node_start = mvd_i ? VP9_MV_CLASS0_FP_1_START :
						  VP9_MV_CLASS0_FP_0_START;
			coef_count_node_start =	mvd_i ?
					VP9_MV_CLASS0_FP_1_COUNT_START :
					VP9_MV_CLASS0_FP_0_COUNT_START;

			क्रम (tree_i = 0; tree_i < 3; tree_i++) अणु
				क्रम (node = 0; node < 3; node++) अणु
					अचिन्हित पूर्णांक start =
						coef_count_node_start;
					चयन (node) अणु
					हाल 2:
						tree_left = count[start + 2];
						tree_right = count[start + 3];
						अवरोध;
					हाल 1:
						tree_left = count[start + 1];
						tree_right = count[start + 2] +
							     count[start + 3];
						अवरोध;
					शेष:
						tree_left = count[start + 0];
						tree_right = count[start + 1] +
							     count[start + 2] +
							     count[start + 3];
						अवरोध;
					पूर्ण

					vp9_tree_merge_probs(prev_prob,
							     cur_prob,
							     coef_node_start,
							     tree_left,
							     tree_right,
							     tree_i, node);

					coef_node_start = coef_node_start + 1;
				पूर्ण
				coef_count_node_start =
					coef_count_node_start + 4;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t codec_vp9_thपढ़ोed_isr(काष्ठा amvdec_session *sess)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा codec_vp9 *vp9 = sess->priv;
	u32 dec_status = amvdec_पढ़ो_करोs(core, VP9_DEC_STATUS_REG);
	u32 prob_status = amvdec_पढ़ो_करोs(core, VP9_ADAPT_PROB_REG);
	पूर्णांक i;

	अगर (!vp9)
		वापस IRQ_HANDLED;

	mutex_lock(&vp9->lock);
	अगर (dec_status != VP9_HEAD_PARSER_DONE) अणु
		dev_err(core->dev_dec, "Unrecognized dec_status: %08X\n",
			dec_status);
		amvdec_पात(sess);
		जाओ unlock;
	पूर्ण

	pr_debug("ISR: %08X;%08X\n", dec_status, prob_status);
	sess->keyframe_found = 1;

	अगर ((prob_status & 0xff) == 0xfd && vp9->cur_frame) अणु
		/* VP9_REQ_ADAPT_PROB */
		u8 *prev_prob_b = ((u8 *)vp9->workspace_vaddr +
					 PROB_OFFSET) +
					((prob_status >> 8) * 0x1000);
		u8 *cur_prob_b = ((u8 *)vp9->workspace_vaddr +
					 PROB_OFFSET) + 0x4000;
		u8 *count_b = (u8 *)vp9->workspace_vaddr +
				   COUNT_OFFSET;
		पूर्णांक last_frame_type = vp9->prev_frame ?
						vp9->prev_frame->type :
						KEY_FRAME;

		adapt_coef_probs(last_frame_type == KEY_FRAME,
				 vp9->cur_frame->type == KEY_FRAME ? 1 : 0,
				 prob_status >> 8,
				 (अचिन्हित पूर्णांक *)prev_prob_b,
				 (अचिन्हित पूर्णांक *)cur_prob_b,
				 (अचिन्हित पूर्णांक *)count_b);

		स_नकल(prev_prob_b, cur_prob_b, ADAPT_PROB_SIZE);
		amvdec_ग_लिखो_करोs(core, VP9_ADAPT_PROB_REG, 0);
	पूर्ण

	/* Invalidate first 3 refs */
	क्रम (i = 0; i < REFS_PER_FRAME ; ++i)
		vp9->frame_refs[i] = शून्य;

	vp9->prev_frame = vp9->cur_frame;
	codec_vp9_update_ref(vp9);

	codec_vp9_fetch_rpm(sess);
	अगर (codec_vp9_process_rpm(vp9)) अणु
		amvdec_src_change(sess, vp9->width, vp9->height, 16);

		/* No frame is actually processed */
		vp9->cur_frame = शून्य;

		/* Show the reमुख्यing frame */
		codec_vp9_show_frame(sess);

		/* FIXME: Save refs क्रम resized frame */
		अगर (vp9->frames_num)
			codec_vp9_save_refs(vp9);

		जाओ unlock;
	पूर्ण

	codec_vp9_process_lf(vp9);
	codec_vp9_process_frame(sess);
	codec_vp9_show_frame(sess);

unlock:
	mutex_unlock(&vp9->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t codec_vp9_isr(काष्ठा amvdec_session *sess)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

काष्ठा amvdec_codec_ops codec_vp9_ops = अणु
	.start = codec_vp9_start,
	.stop = codec_vp9_stop,
	.isr = codec_vp9_isr,
	.thपढ़ोed_isr = codec_vp9_thपढ़ोed_isr,
	.num_pending_bufs = codec_vp9_num_pending_bufs,
	.drain = codec_vp9_flush_output,
	.resume = codec_vp9_resume,
पूर्ण;
