<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/drivers/media/platक्रमm/s5p-jpeg/jpeg-regs.h
 *
 * Register definition file क्रम Samsung JPEG codec driver
 *
 * Copyright (c) 2011-2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#अगर_अघोषित JPEG_REGS_H_
#घोषणा JPEG_REGS_H_

/* Register and bit definitions क्रम S5PC210 */

/* JPEG mode रेजिस्टर */
#घोषणा S5P_JPGMOD			0x00
#घोषणा S5P_PROC_MODE_MASK		(0x1 << 3)
#घोषणा S5P_PROC_MODE_DECOMPR		(0x1 << 3)
#घोषणा S5P_PROC_MODE_COMPR		(0x0 << 3)
#घोषणा S5P_SUBSAMPLING_MODE_MASK	0x7
#घोषणा S5P_SUBSAMPLING_MODE_444	(0x0 << 0)
#घोषणा S5P_SUBSAMPLING_MODE_422	(0x1 << 0)
#घोषणा S5P_SUBSAMPLING_MODE_420	(0x2 << 0)
#घोषणा S5P_SUBSAMPLING_MODE_GRAY	(0x3 << 0)

/* JPEG operation status रेजिस्टर */
#घोषणा S5P_JPGOPR			0x04

/* Quantization tables*/
#घोषणा S5P_JPG_QTBL			0x08
#घोषणा S5P_QT_NUMt_SHIFT(t)		(((t) - 1) << 1)
#घोषणा S5P_QT_NUMt_MASK(t)		(0x3 << S5P_QT_NUMt_SHIFT(t))

/* Huffman tables */
#घोषणा S5P_JPG_HTBL			0x0c
#घोषणा S5P_HT_NUMt_AC_SHIFT(t)		(((t) << 1) - 1)
#घोषणा S5P_HT_NUMt_AC_MASK(t)		(0x1 << S5P_HT_NUMt_AC_SHIFT(t))

#घोषणा S5P_HT_NUMt_DC_SHIFT(t)		(((t) - 1) << 1)
#घोषणा S5P_HT_NUMt_DC_MASK(t)		(0x1 << S5P_HT_NUMt_DC_SHIFT(t))

/* JPEG restart पूर्णांकerval रेजिस्टर upper byte */
#घोषणा S5P_JPGDRI_U			0x10

/* JPEG restart पूर्णांकerval रेजिस्टर lower byte */
#घोषणा S5P_JPGDRI_L			0x14

/* JPEG vertical resolution रेजिस्टर upper byte */
#घोषणा S5P_JPGY_U			0x18

/* JPEG vertical resolution रेजिस्टर lower byte */
#घोषणा S5P_JPGY_L			0x1c

/* JPEG horizontal resolution रेजिस्टर upper byte */
#घोषणा S5P_JPGX_U			0x20

/* JPEG horizontal resolution रेजिस्टर lower byte */
#घोषणा S5P_JPGX_L			0x24

/* JPEG byte count रेजिस्टर upper byte */
#घोषणा S5P_JPGCNT_U			0x28

/* JPEG byte count रेजिस्टर middle byte */
#घोषणा S5P_JPGCNT_M			0x2c

/* JPEG byte count रेजिस्टर lower byte */
#घोषणा S5P_JPGCNT_L			0x30

/* JPEG पूर्णांकerrupt setting रेजिस्टर */
#घोषणा S5P_JPGINTSE			0x34
#घोषणा S5P_RSTm_INT_EN_MASK		(0x1 << 7)
#घोषणा S5P_RSTm_INT_EN			(0x1 << 7)
#घोषणा S5P_DATA_NUM_INT_EN_MASK	(0x1 << 6)
#घोषणा S5P_DATA_NUM_INT_EN		(0x1 << 6)
#घोषणा S5P_FINAL_MCU_NUM_INT_EN_MASK	(0x1 << 5)
#घोषणा S5P_FINAL_MCU_NUM_INT_EN	(0x1 << 5)

/* JPEG पूर्णांकerrupt status रेजिस्टर */
#घोषणा S5P_JPGINTST			0x38
#घोषणा S5P_RESULT_STAT_SHIFT		6
#घोषणा S5P_RESULT_STAT_MASK		(0x1 << S5P_RESULT_STAT_SHIFT)
#घोषणा S5P_STREAM_STAT_SHIFT		5
#घोषणा S5P_STREAM_STAT_MASK		(0x1 << S5P_STREAM_STAT_SHIFT)

/* JPEG command रेजिस्टर */
#घोषणा S5P_JPGCOM			0x4c
#घोषणा S5P_INT_RELEASE			(0x1 << 2)

/* Raw image data r/w address रेजिस्टर */
#घोषणा S5P_JPG_IMGADR			0x50

/* JPEG file r/w address रेजिस्टर */
#घोषणा S5P_JPG_JPGADR			0x58

/* Coefficient क्रम RGB-to-YCbCr converter रेजिस्टर */
#घोषणा S5P_JPG_COEF(n)			(0x5c + (((n) - 1) << 2))
#घोषणा S5P_COEFn_SHIFT(j)		((3 - (j)) << 3)
#घोषणा S5P_COEFn_MASK(j)		(0xff << S5P_COEFn_SHIFT(j))

/* JPEG color mode रेजिस्टर */
#घोषणा S5P_JPGCMOD			0x68
#घोषणा S5P_MOD_SEL_MASK		(0x7 << 5)
#घोषणा S5P_MOD_SEL_422			(0x1 << 5)
#घोषणा S5P_MOD_SEL_565			(0x2 << 5)
#घोषणा S5P_MODE_Y16_MASK		(0x1 << 1)
#घोषणा S5P_MODE_Y16			(0x1 << 1)

/* JPEG घड़ी control रेजिस्टर */
#घोषणा S5P_JPGCLKCON			0x6c
#घोषणा S5P_CLK_DOWN_READY		(0x1 << 1)
#घोषणा S5P_POWER_ON			(0x1 << 0)

/* JPEG start रेजिस्टर */
#घोषणा S5P_JSTART			0x70

/* JPEG SW reset रेजिस्टर */
#घोषणा S5P_JPG_SW_RESET		0x78

/* JPEG समयr setting रेजिस्टर */
#घोषणा S5P_JPG_TIMER_SE		0x7c
#घोषणा S5P_TIMER_INT_EN_MASK		(0x1UL << 31)
#घोषणा S5P_TIMER_INT_EN		(0x1UL << 31)
#घोषणा S5P_TIMER_INIT_MASK		0x7fffffff

/* JPEG समयr status रेजिस्टर */
#घोषणा S5P_JPG_TIMER_ST		0x80
#घोषणा S5P_TIMER_INT_STAT_SHIFT	31
#घोषणा S5P_TIMER_INT_STAT_MASK		(0x1UL << S5P_TIMER_INT_STAT_SHIFT)
#घोषणा S5P_TIMER_CNT_SHIFT		0
#घोषणा S5P_TIMER_CNT_MASK		0x7fffffff

/* JPEG decompression output क्रमmat रेजिस्टर */
#घोषणा S5P_JPG_OUTFORM			0x88
#घोषणा S5P_DEC_OUT_FORMAT_MASK		(0x1 << 0)
#घोषणा S5P_DEC_OUT_FORMAT_422		(0x0 << 0)
#घोषणा S5P_DEC_OUT_FORMAT_420		(0x1 << 0)

/* JPEG version रेजिस्टर */
#घोषणा S5P_JPG_VERSION			0x8c

/* JPEG compressed stream size पूर्णांकerrupt setting रेजिस्टर */
#घोषणा S5P_JPG_ENC_STREAM_INTSE	0x98
#घोषणा S5P_ENC_STREAM_INT_MASK		(0x1 << 24)
#घोषणा S5P_ENC_STREAM_INT_EN		(0x1 << 24)
#घोषणा S5P_ENC_STREAM_BOUND_MASK	0xffffff

/* JPEG compressed stream size पूर्णांकerrupt status रेजिस्टर */
#घोषणा S5P_JPG_ENC_STREAM_INTST	0x9c
#घोषणा S5P_ENC_STREAM_INT_STAT_MASK	0x1

/* JPEG quantizer table रेजिस्टर */
#घोषणा S5P_JPG_QTBL_CONTENT(n)		(0x400 + (n) * 0x100)

/* JPEG DC Huffman table रेजिस्टर */
#घोषणा S5P_JPG_HDCTBL(n)		(0x800 + (n) * 0x400)

/* JPEG DC Huffman table रेजिस्टर */
#घोषणा S5P_JPG_HDCTBLG(n)		(0x840 + (n) * 0x400)

/* JPEG AC Huffman table रेजिस्टर */
#घोषणा S5P_JPG_HACTBL(n)		(0x880 + (n) * 0x400)

/* JPEG AC Huffman table रेजिस्टर */
#घोषणा S5P_JPG_HACTBLG(n)		(0x8c0 + (n) * 0x400)


/* Register and bit definitions क्रम Exynos 4x12 */

/* JPEG Codec Control Registers */
#घोषणा EXYNOS4_JPEG_CNTL_REG		0x00
#घोषणा EXYNOS4_INT_EN_REG		0x04
#घोषणा EXYNOS4_INT_TIMER_COUNT_REG	0x08
#घोषणा EXYNOS4_INT_STATUS_REG		0x0c
#घोषणा EXYNOS4_OUT_MEM_BASE_REG		0x10
#घोषणा EXYNOS4_JPEG_IMG_SIZE_REG	0x14
#घोषणा EXYNOS4_IMG_BA_PLANE_1_REG	0x18
#घोषणा EXYNOS4_IMG_SO_PLANE_1_REG	0x1c
#घोषणा EXYNOS4_IMG_PO_PLANE_1_REG	0x20
#घोषणा EXYNOS4_IMG_BA_PLANE_2_REG	0x24
#घोषणा EXYNOS4_IMG_SO_PLANE_2_REG	0x28
#घोषणा EXYNOS4_IMG_PO_PLANE_2_REG	0x2c
#घोषणा EXYNOS4_IMG_BA_PLANE_3_REG	0x30
#घोषणा EXYNOS4_IMG_SO_PLANE_3_REG	0x34
#घोषणा EXYNOS4_IMG_PO_PLANE_3_REG	0x38

#घोषणा EXYNOS4_TBL_SEL_REG		0x3c

#घोषणा EXYNOS4_IMG_FMT_REG		0x40

#घोषणा EXYNOS4_BITSTREAM_SIZE_REG	0x44
#घोषणा EXYNOS4_PADDING_REG		0x48
#घोषणा EXYNOS4_HUFF_CNT_REG		0x4c
#घोषणा EXYNOS4_FIFO_STATUS_REG	0x50
#घोषणा EXYNOS4_DECODE_XY_SIZE_REG	0x54
#घोषणा EXYNOS4_DECODE_IMG_FMT_REG	0x58

#घोषणा EXYNOS4_QUAN_TBL_ENTRY_REG	0x100
#घोषणा EXYNOS4_HUFF_TBL_ENTRY_REG	0x200


/****************************************************************/
/* Bit definition part						*/
/****************************************************************/

/* JPEG CNTL Register bit */
#घोषणा EXYNOS4_ENC_DEC_MODE_MASK	(0xfffffffc << 0)
#घोषणा EXYNOS4_DEC_MODE		(1 << 0)
#घोषणा EXYNOS4_ENC_MODE		(1 << 1)
#घोषणा EXYNOS4_AUTO_RST_MARKER		(1 << 2)
#घोषणा EXYNOS4_RST_INTERVAL_SHIFT	3
#घोषणा EXYNOS4_RST_INTERVAL(x)		(((x) & 0xffff) \
						<< EXYNOS4_RST_INTERVAL_SHIFT)
#घोषणा EXYNOS4_HUF_TBL_EN		(1 << 19)
#घोषणा EXYNOS4_HOR_SCALING_SHIFT	20
#घोषणा EXYNOS4_HOR_SCALING_MASK	(3 << EXYNOS4_HOR_SCALING_SHIFT)
#घोषणा EXYNOS4_HOR_SCALING(x)		(((x) & 0x3) \
						<< EXYNOS4_HOR_SCALING_SHIFT)
#घोषणा EXYNOS4_VER_SCALING_SHIFT	22
#घोषणा EXYNOS4_VER_SCALING_MASK	(3 << EXYNOS4_VER_SCALING_SHIFT)
#घोषणा EXYNOS4_VER_SCALING(x)		(((x) & 0x3) \
						<< EXYNOS4_VER_SCALING_SHIFT)
#घोषणा EXYNOS4_PADDING			(1 << 27)
#घोषणा EXYNOS4_SYS_INT_EN		(1 << 28)
#घोषणा EXYNOS4_SOFT_RESET_HI		(1 << 29)

/* JPEG INT Register bit */
#घोषणा EXYNOS4_INT_EN_MASK		(0x1f << 0)
#घोषणा EXYNOS5433_INT_EN_MASK		(0x1ff << 0)
#घोषणा EXYNOS4_PROT_ERR_INT_EN		(1 << 0)
#घोषणा EXYNOS4_IMG_COMPLETION_INT_EN	(1 << 1)
#घोषणा EXYNOS4_DEC_INVALID_FORMAT_EN	(1 << 2)
#घोषणा EXYNOS4_MULTI_SCAN_ERROR_EN	(1 << 3)
#घोषणा EXYNOS4_FRAME_ERR_EN		(1 << 4)
#घोषणा EXYNOS4_INT_EN_ALL		(0x1f << 0)
#घोषणा EXYNOS5433_INT_EN_ALL		(0x1b6 << 0)

#घोषणा EXYNOS4_MOD_REG_PROC_ENC	(0 << 3)
#घोषणा EXYNOS4_MOD_REG_PROC_DEC	(1 << 3)

#घोषणा EXYNOS4_MOD_REG_SUBSAMPLE_444	(0 << 0)
#घोषणा EXYNOS4_MOD_REG_SUBSAMPLE_422	(1 << 0)
#घोषणा EXYNOS4_MOD_REG_SUBSAMPLE_420	(2 << 0)
#घोषणा EXYNOS4_MOD_REG_SUBSAMPLE_GRAY	(3 << 0)


/* JPEG IMAGE SIZE Register bit */
#घोषणा EXYNOS4_X_SIZE_SHIFT		0
#घोषणा EXYNOS4_X_SIZE_MASK		(0xffff << EXYNOS4_X_SIZE_SHIFT)
#घोषणा EXYNOS4_X_SIZE(x)		(((x) & 0xffff) << EXYNOS4_X_SIZE_SHIFT)
#घोषणा EXYNOS4_Y_SIZE_SHIFT		16
#घोषणा EXYNOS4_Y_SIZE_MASK		(0xffff << EXYNOS4_Y_SIZE_SHIFT)
#घोषणा EXYNOS4_Y_SIZE(x)		(((x) & 0xffff) << EXYNOS4_Y_SIZE_SHIFT)

/* JPEG IMAGE FORMAT Register bit */
#घोषणा EXYNOS4_ENC_IN_FMT_MASK		0xffff0000
#घोषणा EXYNOS4_ENC_GRAY_IMG		(0 << 0)
#घोषणा EXYNOS4_ENC_RGB_IMG		(1 << 0)
#घोषणा EXYNOS4_ENC_YUV_444_IMG		(2 << 0)
#घोषणा EXYNOS4_ENC_YUV_422_IMG		(3 << 0)
#घोषणा EXYNOS4_ENC_YUV_440_IMG		(4 << 0)

#घोषणा EXYNOS4_DEC_GRAY_IMG		(0 << 0)
#घोषणा EXYNOS4_DEC_RGB_IMG		(1 << 0)
#घोषणा EXYNOS4_DEC_YUV_444_IMG		(2 << 0)
#घोषणा EXYNOS4_DEC_YUV_422_IMG		(3 << 0)
#घोषणा EXYNOS4_DEC_YUV_420_IMG		(4 << 0)

#घोषणा EXYNOS4_GRAY_IMG_IP_SHIFT	3
#घोषणा EXYNOS4_GRAY_IMG_IP_MASK	(7 << EXYNOS4_GRAY_IMG_IP_SHIFT)
#घोषणा EXYNOS4_GRAY_IMG_IP		(4 << EXYNOS4_GRAY_IMG_IP_SHIFT)

#घोषणा EXYNOS4_RGB_IP_SHIFT		6
#घोषणा EXYNOS4_RGB_IP_MASK		(7 << EXYNOS4_RGB_IP_SHIFT)
#घोषणा EXYNOS4_RGB_IP_RGB_16BIT_IMG	(4 << EXYNOS4_RGB_IP_SHIFT)
#घोषणा EXYNOS4_RGB_IP_RGB_32BIT_IMG	(5 << EXYNOS4_RGB_IP_SHIFT)

#घोषणा EXYNOS4_YUV_444_IP_SHIFT		9
#घोषणा EXYNOS4_YUV_444_IP_MASK			(7 << EXYNOS4_YUV_444_IP_SHIFT)
#घोषणा EXYNOS4_YUV_444_IP_YUV_444_2P_IMG	(4 << EXYNOS4_YUV_444_IP_SHIFT)
#घोषणा EXYNOS4_YUV_444_IP_YUV_444_3P_IMG	(5 << EXYNOS4_YUV_444_IP_SHIFT)

#घोषणा EXYNOS4_YUV_422_IP_SHIFT		12
#घोषणा EXYNOS4_YUV_422_IP_MASK			(7 << EXYNOS4_YUV_422_IP_SHIFT)
#घोषणा EXYNOS4_YUV_422_IP_YUV_422_1P_IMG	(4 << EXYNOS4_YUV_422_IP_SHIFT)
#घोषणा EXYNOS4_YUV_422_IP_YUV_422_2P_IMG	(5 << EXYNOS4_YUV_422_IP_SHIFT)
#घोषणा EXYNOS4_YUV_422_IP_YUV_422_3P_IMG	(6 << EXYNOS4_YUV_422_IP_SHIFT)

#घोषणा EXYNOS4_YUV_420_IP_SHIFT		15
#घोषणा EXYNOS4_YUV_420_IP_MASK			(7 << EXYNOS4_YUV_420_IP_SHIFT)
#घोषणा EXYNOS4_YUV_420_IP_YUV_420_2P_IMG	(4 << EXYNOS4_YUV_420_IP_SHIFT)
#घोषणा EXYNOS4_YUV_420_IP_YUV_420_3P_IMG	(5 << EXYNOS4_YUV_420_IP_SHIFT)

#घोषणा EXYNOS4_ENC_FMT_SHIFT			24
#घोषणा EXYNOS4_ENC_FMT_MASK			(3 << EXYNOS4_ENC_FMT_SHIFT)
#घोषणा EXYNOS5433_ENC_FMT_MASK			(7 << EXYNOS4_ENC_FMT_SHIFT)

#घोषणा EXYNOS4_ENC_FMT_GRAY			(0 << EXYNOS4_ENC_FMT_SHIFT)
#घोषणा EXYNOS4_ENC_FMT_YUV_444			(1 << EXYNOS4_ENC_FMT_SHIFT)
#घोषणा EXYNOS4_ENC_FMT_YUV_422			(2 << EXYNOS4_ENC_FMT_SHIFT)
#घोषणा EXYNOS4_ENC_FMT_YUV_420			(3 << EXYNOS4_ENC_FMT_SHIFT)

#घोषणा EXYNOS4_JPEG_DECODED_IMG_FMT_MASK	0x03

#घोषणा EXYNOS4_SWAP_CHROMA_CRCB		(1 << 26)
#घोषणा EXYNOS4_SWAP_CHROMA_CBCR		(0 << 26)
#घोषणा EXYNOS5433_SWAP_CHROMA_CRCB		(1 << 27)
#घोषणा EXYNOS5433_SWAP_CHROMA_CBCR		(0 << 27)

/* JPEG HUFF count Register bit */
#घोषणा EXYNOS4_HUFF_COUNT_MASK			0xffff

/* JPEG Decoded_img_x_y_size Register bit */
#घोषणा EXYNOS4_DECODED_SIZE_MASK		0x0000ffff

/* JPEG Decoded image क्रमmat Register bit */
#घोषणा EXYNOS4_DECODED_IMG_FMT_MASK		0x3

/* JPEG TBL SEL Register bit */
#घोषणा EXYNOS4_Q_TBL_COMP(c, n)	((n) << (((c) - 1) << 1))

#घोषणा EXYNOS4_Q_TBL_COMP1_0		EXYNOS4_Q_TBL_COMP(1, 0)
#घोषणा EXYNOS4_Q_TBL_COMP1_1		EXYNOS4_Q_TBL_COMP(1, 1)
#घोषणा EXYNOS4_Q_TBL_COMP1_2		EXYNOS4_Q_TBL_COMP(1, 2)
#घोषणा EXYNOS4_Q_TBL_COMP1_3		EXYNOS4_Q_TBL_COMP(1, 3)

#घोषणा EXYNOS4_Q_TBL_COMP2_0		EXYNOS4_Q_TBL_COMP(2, 0)
#घोषणा EXYNOS4_Q_TBL_COMP2_1		EXYNOS4_Q_TBL_COMP(2, 1)
#घोषणा EXYNOS4_Q_TBL_COMP2_2		EXYNOS4_Q_TBL_COMP(2, 2)
#घोषणा EXYNOS4_Q_TBL_COMP2_3		EXYNOS4_Q_TBL_COMP(2, 3)

#घोषणा EXYNOS4_Q_TBL_COMP3_0		EXYNOS4_Q_TBL_COMP(3, 0)
#घोषणा EXYNOS4_Q_TBL_COMP3_1		EXYNOS4_Q_TBL_COMP(3, 1)
#घोषणा EXYNOS4_Q_TBL_COMP3_2		EXYNOS4_Q_TBL_COMP(3, 2)
#घोषणा EXYNOS4_Q_TBL_COMP3_3		EXYNOS4_Q_TBL_COMP(3, 3)

#घोषणा EXYNOS4_HUFF_TBL_COMP(c, n)	((n) << ((((c) - 1) << 1) + 6))

#घोषणा EXYNOS4_HUFF_TBL_COMP1_AC_0_DC_0	\
	EXYNOS4_HUFF_TBL_COMP(1, 0)
#घोषणा EXYNOS4_HUFF_TBL_COMP1_AC_0_DC_1	\
	EXYNOS4_HUFF_TBL_COMP(1, 1)
#घोषणा EXYNOS4_HUFF_TBL_COMP1_AC_1_DC_0	\
	EXYNOS4_HUFF_TBL_COMP(1, 2)
#घोषणा EXYNOS4_HUFF_TBL_COMP1_AC_1_DC_1	\
	EXYNOS4_HUFF_TBL_COMP(1, 3)

#घोषणा EXYNOS4_HUFF_TBL_COMP2_AC_0_DC_0	\
	EXYNOS4_HUFF_TBL_COMP(2, 0)
#घोषणा EXYNOS4_HUFF_TBL_COMP2_AC_0_DC_1	\
	EXYNOS4_HUFF_TBL_COMP(2, 1)
#घोषणा EXYNOS4_HUFF_TBL_COMP2_AC_1_DC_0	\
	EXYNOS4_HUFF_TBL_COMP(2, 2)
#घोषणा EXYNOS4_HUFF_TBL_COMP2_AC_1_DC_1	\
	EXYNOS4_HUFF_TBL_COMP(2, 3)

#घोषणा EXYNOS4_HUFF_TBL_COMP3_AC_0_DC_0	\
	EXYNOS4_HUFF_TBL_COMP(3, 0)
#घोषणा EXYNOS4_HUFF_TBL_COMP3_AC_0_DC_1	\
	EXYNOS4_HUFF_TBL_COMP(3, 1)
#घोषणा EXYNOS4_HUFF_TBL_COMP3_AC_1_DC_0	\
	EXYNOS4_HUFF_TBL_COMP(3, 2)
#घोषणा EXYNOS4_HUFF_TBL_COMP3_AC_1_DC_1	\
	EXYNOS4_HUFF_TBL_COMP(3, 3)

#घोषणा EXYNOS4_NF_SHIFT			16
#घोषणा EXYNOS4_NF_MASK				0xff
#घोषणा EXYNOS4_NF(x)				\
	(((x) & EXYNOS4_NF_MASK) << EXYNOS4_NF_SHIFT)

/* JPEG quantizer table रेजिस्टर */
#घोषणा EXYNOS4_QTBL_CONTENT(n)	(0x100 + (n) * 0x40)

/* JPEG DC luminance (code length) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HDCLL	0x200

/* JPEG DC luminance (values) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HDCLV	0x210

/* JPEG DC chrominance (code length) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HDCCL	0x220

/* JPEG DC chrominance (values) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HDCCV	0x230

/* JPEG AC luminance (code length) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HACLL	0x240

/* JPEG AC luminance (values) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HACLV	0x250

/* JPEG AC chrominance (code length) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HACCL	0x300

/* JPEG AC chrominance (values) Huffman table रेजिस्टर */
#घोषणा EXYNOS4_HUFF_TBL_HACCV	0x310

/* Register and bit definitions क्रम Exynos 3250 */

/* JPEG mode रेजिस्टर */
#घोषणा EXYNOS3250_JPGMOD			0x00
#घोषणा EXYNOS3250_PROC_MODE_MASK		(0x1 << 3)
#घोषणा EXYNOS3250_PROC_MODE_DECOMPR		(0x1 << 3)
#घोषणा EXYNOS3250_PROC_MODE_COMPR		(0x0 << 3)
#घोषणा EXYNOS3250_SUBSAMPLING_MODE_MASK	(0x7 << 0)
#घोषणा EXYNOS3250_SUBSAMPLING_MODE_444		(0x0 << 0)
#घोषणा EXYNOS3250_SUBSAMPLING_MODE_422		(0x1 << 0)
#घोषणा EXYNOS3250_SUBSAMPLING_MODE_420		(0x2 << 0)
#घोषणा EXYNOS3250_SUBSAMPLING_MODE_411		(0x6 << 0)
#घोषणा EXYNOS3250_SUBSAMPLING_MODE_GRAY	(0x3 << 0)

/* JPEG operation status रेजिस्टर */
#घोषणा EXYNOS3250_JPGOPR			0x04
#घोषणा EXYNOS3250_JPGOPR_MASK			0x01

/* Quantization and Huffman tables रेजिस्टर */
#घोषणा EXYNOS3250_QHTBL			0x08
#घोषणा EXYNOS3250_QT_NUM_SHIFT(t)		((((t) - 1) << 1) + 8)
#घोषणा EXYNOS3250_QT_NUM_MASK(t)		(0x3 << EXYNOS3250_QT_NUM_SHIFT(t))

/* Huffman tables */
#घोषणा EXYNOS3250_HT_NUM_AC_SHIFT(t)		(((t) << 1) - 1)
#घोषणा EXYNOS3250_HT_NUM_AC_MASK(t)		(0x1 << EXYNOS3250_HT_NUM_AC_SHIFT(t))

#घोषणा EXYNOS3250_HT_NUM_DC_SHIFT(t)		(((t) - 1) << 1)
#घोषणा EXYNOS3250_HT_NUM_DC_MASK(t)		(0x1 << EXYNOS3250_HT_NUM_DC_SHIFT(t))

/* JPEG restart पूर्णांकerval रेजिस्टर */
#घोषणा EXYNOS3250_JPGDRI			0x0c
#घोषणा EXYNOS3250_JPGDRI_MASK			0xffff

/* JPEG vertical resolution रेजिस्टर */
#घोषणा EXYNOS3250_JPGY				0x10
#घोषणा EXYNOS3250_JPGY_MASK			0xffff

/* JPEG horizontal resolution रेजिस्टर */
#घोषणा EXYNOS3250_JPGX				0x14
#घोषणा EXYNOS3250_JPGX_MASK			0xffff

/* JPEG byte count रेजिस्टर */
#घोषणा EXYNOS3250_JPGCNT			0x18
#घोषणा EXYNOS3250_JPGCNT_MASK			0xffffff

/* JPEG पूर्णांकerrupt mask रेजिस्टर */
#घोषणा EXYNOS3250_JPGINTSE			0x1c
#घोषणा EXYNOS3250_JPEG_DONE_EN			(1 << 11)
#घोषणा EXYNOS3250_WDMA_DONE_EN			(1 << 10)
#घोषणा EXYNOS3250_RDMA_DONE_EN			(1 << 9)
#घोषणा EXYNOS3250_ENC_STREAM_INT_EN		(1 << 8)
#घोषणा EXYNOS3250_CORE_DONE_EN			(1 << 5)
#घोषणा EXYNOS3250_ERR_INT_EN			(1 << 4)
#घोषणा EXYNOS3250_HEAD_INT_EN			(1 << 3)

/* JPEG पूर्णांकerrupt status रेजिस्टर */
#घोषणा EXYNOS3250_JPGINTST			0x20
#घोषणा EXYNOS3250_JPEG_DONE			(1 << 11)
#घोषणा EXYNOS3250_WDMA_DONE			(1 << 10)
#घोषणा EXYNOS3250_RDMA_DONE			(1 << 9)
#घोषणा EXYNOS3250_ENC_STREAM_STAT		(1 << 8)
#घोषणा EXYNOS3250_RESULT_STAT			(1 << 5)
#घोषणा EXYNOS3250_STREAM_STAT			(1 << 4)
#घोषणा EXYNOS3250_HEADER_STAT			(1 << 3)

/*
 * Base address of the luma component DMA buffer
 * of the raw input or output image.
 */
#घोषणा EXYNOS3250_LUMA_BASE			0x100
#घोषणा EXYNOS3250_SRC_TILE_EN_MASK		0x100

/* Stride of source or destination luma raw image buffer */
#घोषणा EXYNOS3250_LUMA_STRIDE			0x104

/* Horizontal/vertical offset of active region in luma raw image buffer */
#घोषणा EXYNOS3250_LUMA_XY_OFFSET		0x108
#घोषणा EXYNOS3250_LUMA_YY_OFFSET_SHIFT		18
#घोषणा EXYNOS3250_LUMA_YY_OFFSET_MASK		(0x1fff << EXYNOS3250_LUMA_YY_OFFSET_SHIFT)
#घोषणा EXYNOS3250_LUMA_YX_OFFSET_SHIFT		2
#घोषणा EXYNOS3250_LUMA_YX_OFFSET_MASK		(0x1fff << EXYNOS3250_LUMA_YX_OFFSET_SHIFT)

/*
 * Base address of the chroma(Cb) component DMA buffer
 * of the raw input or output image.
 */
#घोषणा EXYNOS3250_CHROMA_BASE			0x10c

/* Stride of source or destination chroma(Cb) raw image buffer */
#घोषणा EXYNOS3250_CHROMA_STRIDE		0x110

/* Horizontal/vertical offset of active region in chroma(Cb) raw image buffer */
#घोषणा EXYNOS3250_CHROMA_XY_OFFSET		0x114
#घोषणा EXYNOS3250_CHROMA_YY_OFFSET_SHIFT	18
#घोषणा EXYNOS3250_CHROMA_YY_OFFSET_MASK	(0x1fff << EXYNOS3250_CHROMA_YY_OFFSET_SHIFT)
#घोषणा EXYNOS3250_CHROMA_YX_OFFSET_SHIFT	2
#घोषणा EXYNOS3250_CHROMA_YX_OFFSET_MASK	(0x1fff << EXYNOS3250_CHROMA_YX_OFFSET_SHIFT)

/*
 * Base address of the chroma(Cr) component DMA buffer
 * of the raw input or output image.
 */
#घोषणा EXYNOS3250_CHROMA_CR_BASE		0x118

/* Stride of source or destination chroma(Cr) raw image buffer */
#घोषणा EXYNOS3250_CHROMA_CR_STRIDE		0x11c

/* Horizontal/vertical offset of active region in chroma(Cb) raw image buffer */
#घोषणा EXYNOS3250_CHROMA_CR_XY_OFFSET		0x120
#घोषणा EXYNOS3250_CHROMA_CR_YY_OFFSET_SHIFT	18
#घोषणा EXYNOS3250_CHROMA_CR_YY_OFFSET_MASK	(0x1fff << EXYNOS3250_CHROMA_CR_YY_OFFSET_SHIFT)
#घोषणा EXYNOS3250_CHROMA_CR_YX_OFFSET_SHIFT	2
#घोषणा EXYNOS3250_CHROMA_CR_YX_OFFSET_MASK	(0x1fff << EXYNOS3250_CHROMA_CR_YX_OFFSET_SHIFT)

/* Raw image data r/w address रेजिस्टर */
#घोषणा EXYNOS3250_JPG_IMGADR			0x50

/* Source or destination JPEG file DMA buffer address */
#घोषणा EXYNOS3250_JPG_JPGADR			0x124

/* Coefficients क्रम RGB-to-YCbCr converter रेजिस्टर */
#घोषणा EXYNOS3250_JPG_COEF(n)			(0x128 + (((n) - 1) << 2))
#घोषणा EXYNOS3250_COEF_SHIFT(j)		((3 - (j)) << 3)
#घोषणा EXYNOS3250_COEF_MASK(j)			(0xff << EXYNOS3250_COEF_SHIFT(j))

/* Raw input क्रमmat setting */
#घोषणा EXYNOS3250_JPGCMOD			0x134
#घोषणा EXYNOS3250_SRC_TILE_EN			(0x1 << 10)
#घोषणा EXYNOS3250_SRC_NV_MASK			(0x1 << 9)
#घोषणा EXYNOS3250_SRC_NV12			(0x0 << 9)
#घोषणा EXYNOS3250_SRC_NV21			(0x1 << 9)
#घोषणा EXYNOS3250_SRC_BIG_ENDIAN_MASK		(0x1 << 8)
#घोषणा EXYNOS3250_SRC_BIG_ENDIAN		(0x1 << 8)
#घोषणा EXYNOS3250_MODE_SEL_MASK		(0x7 << 5)
#घोषणा EXYNOS3250_MODE_SEL_420_2P		(0x0 << 5)
#घोषणा EXYNOS3250_MODE_SEL_422_1P_LUM_CHR	(0x1 << 5)
#घोषणा EXYNOS3250_MODE_SEL_RGB565		(0x2 << 5)
#घोषणा EXYNOS3250_MODE_SEL_422_1P_CHR_LUM	(0x3 << 5)
#घोषणा EXYNOS3250_MODE_SEL_ARGB8888		(0x4 << 5)
#घोषणा EXYNOS3250_MODE_SEL_420_3P		(0x5 << 5)
#घोषणा EXYNOS3250_SRC_SWAP_RGB			(0x1 << 3)
#घोषणा EXYNOS3250_SRC_SWAP_UV			(0x1 << 2)
#घोषणा EXYNOS3250_MODE_Y16_MASK		(0x1 << 1)
#घोषणा EXYNOS3250_MODE_Y16			(0x1 << 1)
#घोषणा EXYNOS3250_HALF_EN_MASK			(0x1 << 0)
#घोषणा EXYNOS3250_HALF_EN			(0x1 << 0)

/* Power on/off and घड़ी करोwn control */
#घोषणा EXYNOS3250_JPGCLKCON			0x138
#घोषणा EXYNOS3250_CLK_DOWN_READY		(0x1 << 1)
#घोषणा EXYNOS3250_POWER_ON			(0x1 << 0)

/* Start compression or decompression */
#घोषणा EXYNOS3250_JSTART			0x13c

/* Restart decompression after header analysis */
#घोषणा EXYNOS3250_JRSTART			0x140

/* JPEG SW reset रेजिस्टर */
#घोषणा EXYNOS3250_SW_RESET			0x144

/* JPEG समयr setting रेजिस्टर */
#घोषणा EXYNOS3250_TIMER_SE			0x148
#घोषणा EXYNOS3250_TIMER_INT_EN_SHIFT		31
#घोषणा EXYNOS3250_TIMER_INT_EN			(1UL << EXYNOS3250_TIMER_INT_EN_SHIFT)
#घोषणा EXYNOS3250_TIMER_INIT_MASK		0x7fffffff

/* JPEG समयr status रेजिस्टर */
#घोषणा EXYNOS3250_TIMER_ST			0x14c
#घोषणा EXYNOS3250_TIMER_INT_STAT_SHIFT		31
#घोषणा EXYNOS3250_TIMER_INT_STAT		(1UL << EXYNOS3250_TIMER_INT_STAT_SHIFT)
#घोषणा EXYNOS3250_TIMER_CNT_SHIFT		0
#घोषणा EXYNOS3250_TIMER_CNT_MASK		0x7fffffff

/* Command status रेजिस्टर */
#घोषणा EXYNOS3250_COMSTAT			0x150
#घोषणा EXYNOS3250_CUR_PROC_MODE		(0x1 << 1)
#घोषणा EXYNOS3250_CUR_COM_MODE			(0x1 << 0)

/* JPEG decompression output क्रमmat रेजिस्टर */
#घोषणा EXYNOS3250_OUTFORM			0x154
#घोषणा EXYNOS3250_OUT_ALPHA_MASK		(0xff << 24)
#घोषणा EXYNOS3250_OUT_TILE_EN			(0x1 << 10)
#घोषणा EXYNOS3250_OUT_NV_MASK			(0x1 << 9)
#घोषणा EXYNOS3250_OUT_NV12			(0x0 << 9)
#घोषणा EXYNOS3250_OUT_NV21			(0x1 << 9)
#घोषणा EXYNOS3250_OUT_BIG_ENDIAN_MASK		(0x1 << 8)
#घोषणा EXYNOS3250_OUT_BIG_ENDIAN		(0x1 << 8)
#घोषणा EXYNOS3250_OUT_SWAP_RGB			(0x1 << 7)
#घोषणा EXYNOS3250_OUT_SWAP_UV			(0x1 << 6)
#घोषणा EXYNOS3250_OUT_FMT_MASK			(0x7 << 0)
#घोषणा EXYNOS3250_OUT_FMT_420_2P		(0x0 << 0)
#घोषणा EXYNOS3250_OUT_FMT_422_1P_LUM_CHR	(0x1 << 0)
#घोषणा EXYNOS3250_OUT_FMT_422_1P_CHR_LUM	(0x3 << 0)
#घोषणा EXYNOS3250_OUT_FMT_420_3P		(0x4 << 0)
#घोषणा EXYNOS3250_OUT_FMT_RGB565		(0x5 << 0)
#घोषणा EXYNOS3250_OUT_FMT_ARGB8888		(0x6 << 0)

/* Input JPEG stream byte size क्रम decompression */
#घोषणा EXYNOS3250_DEC_STREAM_SIZE		0x158
#घोषणा EXYNOS3250_DEC_STREAM_MASK		0x1fffffff

/* The upper bound of the byte size of output compressed stream */
#घोषणा EXYNOS3250_ENC_STREAM_BOUND		0x15c
#घोषणा EXYNOS3250_ENC_STREAM_BOUND_MASK	0xffffc0

/* Scale-करोwn ratio when decoding */
#घोषणा EXYNOS3250_DEC_SCALING_RATIO		0x160
#घोषणा EXYNOS3250_DEC_SCALE_FACTOR_MASK	0x3
#घोषणा EXYNOS3250_DEC_SCALE_FACTOR_8_8		0x0
#घोषणा EXYNOS3250_DEC_SCALE_FACTOR_4_8		0x1
#घोषणा EXYNOS3250_DEC_SCALE_FACTOR_2_8		0x2
#घोषणा EXYNOS3250_DEC_SCALE_FACTOR_1_8		0x3

/* Error check */
#घोषणा EXYNOS3250_CRC_RESULT			0x164

/* RDMA and WDMA operation status रेजिस्टर */
#घोषणा EXYNOS3250_DMA_OPER_STATUS		0x168
#घोषणा EXYNOS3250_WDMA_OPER_STATUS		(0x1 << 1)
#घोषणा EXYNOS3250_RDMA_OPER_STATUS		(0x1 << 0)

/* DMA issue gathering number and issue number settings */
#घोषणा EXYNOS3250_DMA_ISSUE_NUM		0x16c
#घोषणा EXYNOS3250_WDMA_ISSUE_NUM_SHIFT		16
#घोषणा EXYNOS3250_WDMA_ISSUE_NUM_MASK		(0x7 << EXYNOS3250_WDMA_ISSUE_NUM_SHIFT)
#घोषणा EXYNOS3250_RDMA_ISSUE_NUM_SHIFT		8
#घोषणा EXYNOS3250_RDMA_ISSUE_NUM_MASK		(0x7 << EXYNOS3250_RDMA_ISSUE_NUM_SHIFT)
#घोषणा EXYNOS3250_ISSUE_GATHER_NUM_SHIFT	0
#घोषणा EXYNOS3250_ISSUE_GATHER_NUM_MASK	(0x7 << EXYNOS3250_ISSUE_GATHER_NUM_SHIFT)
#घोषणा EXYNOS3250_DMA_MO_COUNT			0x7

/* Version रेजिस्टर */
#घोषणा EXYNOS3250_VERSION			0x1fc

/* RGB <-> YUV conversion coefficients */
#घोषणा EXYNOS3250_JPEG_ENC_COEF1		0x01352e1e
#घोषणा EXYNOS3250_JPEG_ENC_COEF2		0x00b0ae83
#घोषणा EXYNOS3250_JPEG_ENC_COEF3		0x020cdc13

#घोषणा EXYNOS3250_JPEG_DEC_COEF1		0x04a80199
#घोषणा EXYNOS3250_JPEG_DEC_COEF2		0x04a9a064
#घोषणा EXYNOS3250_JPEG_DEC_COEF3		0x04a80102

#पूर्ण_अगर /* JPEG_REGS_H_ */

