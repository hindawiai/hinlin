<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/media/platक्रमm/s5p-jpeg/jpeg-core.c
 *
 * Copyright (c) 2011-2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-rect.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "jpeg-core.h"
#समावेश "jpeg-hw-s5p.h"
#समावेश "jpeg-hw-exynos4.h"
#समावेश "jpeg-hw-exynos3250.h"
#समावेश "jpeg-regs.h"

अटल काष्ठा s5p_jpeg_fmt sjpeg_क्रमmats[] = अणु
	अणु
		.fourcc		= V4L2_PIX_FMT_JPEG,
		.flags		= SJPEG_FMT_FLAG_ENC_CAPTURE |
				  SJPEG_FMT_FLAG_DEC_OUTPUT |
				  SJPEG_FMT_FLAG_S5P |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_FLAG_EXYNOS4,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 4,
		.v_align	= 3,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_S5P |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 1,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUYV,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 1,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YVYU,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_UYVY,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_VYUY,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 0,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565X,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.depth		= 16,
		.colplanes	= 1,
		.h_align	= 0,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_S5P |
				  SJPEG_FMT_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB32,
		.depth		= 32,
		.colplanes	= 1,
		.h_align	= 0,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_RGB32,
		.depth		= 32,
		.colplanes	= 1,
		.h_align	= 2,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV24,
		.depth		= 24,
		.colplanes	= 2,
		.h_align	= 0,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV42,
		.depth		= 24,
		.colplanes	= 2,
		.h_align	= 0,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV61,
		.depth		= 16,
		.colplanes	= 2,
		.h_align	= 1,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV16,
		.depth		= 16,
		.colplanes	= 2,
		.h_align	= 1,
		.v_align	= 0,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12,
		.depth		= 12,
		.colplanes	= 2,
		.h_align	= 1,
		.v_align	= 1,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12,
		.depth		= 12,
		.colplanes	= 2,
		.h_align	= 3,
		.v_align	= 3,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV12,
		.depth		= 12,
		.colplanes	= 2,
		.h_align	= 4,
		.v_align	= 4,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_S5P |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV21,
		.depth		= 12,
		.colplanes	= 2,
		.h_align	= 3,
		.v_align	= 3,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_NV21,
		.depth		= 12,
		.colplanes	= 2,
		.h_align	= 1,
		.v_align	= 1,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV420,
		.depth		= 12,
		.colplanes	= 3,
		.h_align	= 1,
		.v_align	= 1,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_YUV420,
		.depth		= 12,
		.colplanes	= 3,
		.h_align	= 4,
		.v_align	= 4,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS3250 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	पूर्ण,
	अणु
		.fourcc		= V4L2_PIX_FMT_GREY,
		.depth		= 8,
		.colplanes	= 1,
		.flags		= SJPEG_FMT_FLAG_ENC_OUTPUT |
				  SJPEG_FMT_FLAG_DEC_CAPTURE |
				  SJPEG_FMT_FLAG_EXYNOS4 |
				  SJPEG_FMT_NON_RGB,
		.subsampling	= V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY,
	पूर्ण,
पूर्ण;
#घोषणा SJPEG_NUM_FORMATS ARRAY_SIZE(sjpeg_क्रमmats)

अटल स्थिर अचिन्हित अक्षर qtbl_luminance[4][64] = अणु
	अणु/*level 0 - high compression quality */
		20, 16, 25, 39, 50, 46, 62, 68,
		16, 18, 23, 38, 38, 53, 65, 68,
		25, 23, 31, 38, 53, 65, 68, 68,
		39, 38, 38, 53, 65, 68, 68, 68,
		50, 38, 53, 65, 68, 68, 68, 68,
		46, 53, 65, 68, 68, 68, 68, 68,
		62, 65, 68, 68, 68, 68, 68, 68,
		68, 68, 68, 68, 68, 68, 68, 68
	पूर्ण,
	अणु/* level 1 */
		16, 11, 11, 16, 23, 27, 31, 30,
		11, 12, 12, 15, 20, 23, 23, 30,
		11, 12, 13, 16, 23, 26, 35, 47,
		16, 15, 16, 23, 26, 37, 47, 64,
		23, 20, 23, 26, 39, 51, 64, 64,
		27, 23, 26, 37, 51, 64, 64, 64,
		31, 23, 35, 47, 64, 64, 64, 64,
		30, 30, 47, 64, 64, 64, 64, 64
	पूर्ण,
	अणु/* level 2 */
		12,  8,  8, 12, 17, 21, 24, 23,
		 8,  9,  9, 11, 15, 19, 18, 23,
		 8,  9, 10, 12, 19, 20, 27, 36,
		12, 11, 12, 21, 20, 28, 36, 53,
		17, 15, 19, 20, 30, 39, 51, 59,
		21, 19, 20, 28, 39, 51, 59, 59,
		24, 18, 27, 36, 51, 59, 59, 59,
		23, 23, 36, 53, 59, 59, 59, 59
	पूर्ण,
	अणु/* level 3 - low compression quality */
		 8,  6,  6,  8, 12, 14, 16, 17,
		 6,  6,  6,  8, 10, 13, 12, 15,
		 6,  6,  7,  8, 13, 14, 18, 24,
		 8,  8,  8, 14, 13, 19, 24, 35,
		12, 10, 13, 13, 20, 26, 34, 39,
		14, 13, 14, 19, 26, 34, 39, 39,
		16, 12, 18, 24, 34, 39, 39, 39,
		17, 15, 24, 35, 39, 39, 39, 39
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर qtbl_chrominance[4][64] = अणु
	अणु/*level 0 - high compression quality */
		21, 25, 32, 38, 54, 68, 68, 68,
		25, 28, 24, 38, 54, 68, 68, 68,
		32, 24, 32, 43, 66, 68, 68, 68,
		38, 38, 43, 53, 68, 68, 68, 68,
		54, 54, 66, 68, 68, 68, 68, 68,
		68, 68, 68, 68, 68, 68, 68, 68,
		68, 68, 68, 68, 68, 68, 68, 68,
		68, 68, 68, 68, 68, 68, 68, 68
	पूर्ण,
	अणु/* level 1 */
		17, 15, 17, 21, 20, 26, 38, 48,
		15, 19, 18, 17, 20, 26, 35, 43,
		17, 18, 20, 22, 26, 30, 46, 53,
		21, 17, 22, 28, 30, 39, 53, 64,
		20, 20, 26, 30, 39, 48, 64, 64,
		26, 26, 30, 39, 48, 63, 64, 64,
		38, 35, 46, 53, 64, 64, 64, 64,
		48, 43, 53, 64, 64, 64, 64, 64
	पूर्ण,
	अणु/* level 2 */
		13, 11, 13, 16, 20, 20, 29, 37,
		11, 14, 14, 14, 16, 20, 26, 32,
		13, 14, 15, 17, 20, 23, 35, 40,
		16, 14, 17, 21, 23, 30, 40, 50,
		20, 16, 20, 23, 30, 37, 50, 59,
		20, 20, 23, 30, 37, 48, 59, 59,
		29, 26, 35, 40, 50, 59, 59, 59,
		37, 32, 40, 50, 59, 59, 59, 59
	पूर्ण,
	अणु/* level 3 - low compression quality */
		 9,  8,  9, 11, 14, 17, 19, 24,
		 8, 10,  9, 11, 14, 13, 17, 22,
		 9,  9, 13, 14, 13, 15, 23, 26,
		11, 11, 14, 14, 15, 20, 26, 33,
		14, 14, 13, 15, 20, 24, 33, 39,
		17, 13, 15, 20, 24, 32, 39, 39,
		19, 17, 23, 26, 33, 39, 39, 39,
		24, 22, 26, 33, 39, 39, 39, 39
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर hdctbl0[16] = अणु
	0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल स्थिर अचिन्हित अक्षर hdctblg0[12] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb
पूर्ण;
अटल स्थिर अचिन्हित अक्षर hactbl0[16] = अणु
	0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d
पूर्ण;
अटल स्थिर अचिन्हित अक्षर hactblg0[162] = अणु
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
पूर्ण;

/*
 * Fourcc करोwngrade schema lookup tables क्रम 422 and 420
 * chroma subsampling - fourcc on each position maps on the
 * fourcc from the table fourcc_to_dwngrd_schema_id which allows
 * to get the most suitable fourcc counterpart क्रम the given
 * करोwngraded subsampling property.
 */
अटल स्थिर u32 subs422_fourcc_dwngrd_schema[] = अणु
	V4L2_PIX_FMT_NV16,
	V4L2_PIX_FMT_NV61,
पूर्ण;

अटल स्थिर u32 subs420_fourcc_dwngrd_schema[] = अणु
	V4L2_PIX_FMT_NV12,
	V4L2_PIX_FMT_NV21,
	V4L2_PIX_FMT_NV12,
	V4L2_PIX_FMT_NV21,
	V4L2_PIX_FMT_NV12,
	V4L2_PIX_FMT_NV21,
	V4L2_PIX_FMT_GREY,
	V4L2_PIX_FMT_GREY,
	V4L2_PIX_FMT_GREY,
	V4L2_PIX_FMT_GREY,
पूर्ण;

/*
 * Lookup table क्रम translation of a fourcc to the position
 * of its करोwngraded counterpart in the *fourcc_dwngrd_schema
 * tables.
 */
अटल स्थिर u32 fourcc_to_dwngrd_schema_id[] = अणु
	V4L2_PIX_FMT_NV24,
	V4L2_PIX_FMT_NV42,
	V4L2_PIX_FMT_NV16,
	V4L2_PIX_FMT_NV61,
	V4L2_PIX_FMT_YUYV,
	V4L2_PIX_FMT_YVYU,
	V4L2_PIX_FMT_NV12,
	V4L2_PIX_FMT_NV21,
	V4L2_PIX_FMT_YUV420,
	V4L2_PIX_FMT_GREY,
पूर्ण;

अटल पूर्णांक s5p_jpeg_get_dwngrd_sch_id_by_fourcc(u32 fourcc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fourcc_to_dwngrd_schema_id); ++i) अणु
		अगर (fourcc_to_dwngrd_schema_id[i] == fourcc)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s5p_jpeg_adjust_fourcc_to_subsampling(
					क्रमागत v4l2_jpeg_chroma_subsampling subs,
					u32 in_fourcc,
					u32 *out_fourcc,
					काष्ठा s5p_jpeg_ctx *ctx)
अणु
	पूर्णांक dwngrd_sch_id;

	अगर (ctx->subsampling != V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY) अणु
		dwngrd_sch_id =
			s5p_jpeg_get_dwngrd_sch_id_by_fourcc(in_fourcc);
		अगर (dwngrd_sch_id < 0)
			वापस -EINVAL;
	पूर्ण

	चयन (ctx->subsampling) अणु
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY:
		*out_fourcc = V4L2_PIX_FMT_GREY;
		अवरोध;
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_420:
		अगर (dwngrd_sch_id >
				ARRAY_SIZE(subs420_fourcc_dwngrd_schema) - 1)
			वापस -EINVAL;
		*out_fourcc = subs420_fourcc_dwngrd_schema[dwngrd_sch_id];
		अवरोध;
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_422:
		अगर (dwngrd_sch_id >
				ARRAY_SIZE(subs422_fourcc_dwngrd_schema) - 1)
			वापस -EINVAL;
		*out_fourcc = subs422_fourcc_dwngrd_schema[dwngrd_sch_id];
		अवरोध;
	शेष:
		*out_fourcc = V4L2_PIX_FMT_GREY;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos4x12_decoded_subsampling[] = अणु
	V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY,
	V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	V4L2_JPEG_CHROMA_SUBSAMPLING_420,
पूर्ण;

अटल पूर्णांक exynos3250_decoded_subsampling[] = अणु
	V4L2_JPEG_CHROMA_SUBSAMPLING_444,
	V4L2_JPEG_CHROMA_SUBSAMPLING_422,
	V4L2_JPEG_CHROMA_SUBSAMPLING_420,
	V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY,
	-1,
	-1,
	V4L2_JPEG_CHROMA_SUBSAMPLING_411,
पूर्ण;

अटल अंतरभूत काष्ठा s5p_jpeg_ctx *ctrl_to_ctx(काष्ठा v4l2_ctrl *c)
अणु
	वापस container_of(c->handler, काष्ठा s5p_jpeg_ctx, ctrl_handler);
पूर्ण

अटल अंतरभूत काष्ठा s5p_jpeg_ctx *fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा s5p_jpeg_ctx, fh);
पूर्ण

अटल पूर्णांक s5p_jpeg_to_user_subsampling(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	चयन (ctx->jpeg->variant->version) अणु
	हाल SJPEG_S5P:
		WARN_ON(ctx->subsampling > 3);
		अगर (ctx->subsampling > 2)
			वापस V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;
		वापस ctx->subsampling;
	हाल SJPEG_EXYNOS3250:
	हाल SJPEG_EXYNOS5420:
		WARN_ON(ctx->subsampling > 6);
		अगर (ctx->subsampling > 3)
			वापस V4L2_JPEG_CHROMA_SUBSAMPLING_411;
		वापस exynos3250_decoded_subsampling[ctx->subsampling];
	हाल SJPEG_EXYNOS4:
		WARN_ON(ctx->subsampling > 3);
		अगर (ctx->subsampling > 2)
			वापस V4L2_JPEG_CHROMA_SUBSAMPLING_420;
		वापस exynos4x12_decoded_subsampling[ctx->subsampling];
	हाल SJPEG_EXYNOS5433:
		वापस ctx->subsampling; /* parsed from header */
	शेष:
		WARN_ON(ctx->subsampling > 3);
		वापस V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_qtbl(व्योम __iomem *regs,
				     स्थिर अचिन्हित अक्षर *qtbl,
				     अचिन्हित दीर्घ tab, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोl((अचिन्हित पूर्णांक)qtbl[i], regs + tab + (i * 0x04));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_qtbl_lum(व्योम __iomem *regs, पूर्णांक quality)
अणु
	/* this driver fills quantisation table 0 with data क्रम luma */
	s5p_jpeg_set_qtbl(regs, qtbl_luminance[quality],
			  S5P_JPG_QTBL_CONTENT(0),
			  ARRAY_SIZE(qtbl_luminance[quality]));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_qtbl_chr(व्योम __iomem *regs, पूर्णांक quality)
अणु
	/* this driver fills quantisation table 1 with data क्रम chroma */
	s5p_jpeg_set_qtbl(regs, qtbl_chrominance[quality],
			  S5P_JPG_QTBL_CONTENT(1),
			  ARRAY_SIZE(qtbl_chrominance[quality]));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_htbl(व्योम __iomem *regs,
				     स्थिर अचिन्हित अक्षर *htbl,
				     अचिन्हित दीर्घ tab, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोl((अचिन्हित पूर्णांक)htbl[i], regs + tab + (i * 0x04));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_hdctbl(व्योम __iomem *regs)
अणु
	/* this driver fills table 0 क्रम this component */
	s5p_jpeg_set_htbl(regs, hdctbl0, S5P_JPG_HDCTBL(0),
						ARRAY_SIZE(hdctbl0));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_hdctblg(व्योम __iomem *regs)
अणु
	/* this driver fills table 0 क्रम this component */
	s5p_jpeg_set_htbl(regs, hdctblg0, S5P_JPG_HDCTBLG(0),
						ARRAY_SIZE(hdctblg0));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_hactbl(व्योम __iomem *regs)
अणु
	/* this driver fills table 0 क्रम this component */
	s5p_jpeg_set_htbl(regs, hactbl0, S5P_JPG_HACTBL(0),
						ARRAY_SIZE(hactbl0));
पूर्ण

अटल अंतरभूत व्योम s5p_jpeg_set_hactblg(व्योम __iomem *regs)
अणु
	/* this driver fills table 0 क्रम this component */
	s5p_jpeg_set_htbl(regs, hactblg0, S5P_JPG_HACTBLG(0),
						ARRAY_SIZE(hactblg0));
पूर्ण

अटल अंतरभूत व्योम exynos4_jpeg_set_tbl(व्योम __iomem *regs,
					स्थिर अचिन्हित अक्षर *tbl,
					अचिन्हित दीर्घ tab, पूर्णांक len)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक dword;

	क्रम (i = 0; i < len; i += 4) अणु
		dword = tbl[i] |
			(tbl[i + 1] << 8) |
			(tbl[i + 2] << 16) |
			(tbl[i + 3] << 24);
		ग_लिखोl(dword, regs + tab + i);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम exynos4_jpeg_set_qtbl_lum(व्योम __iomem *regs, पूर्णांक quality)
अणु
	/* this driver fills quantisation table 0 with data क्रम luma */
	exynos4_jpeg_set_tbl(regs, qtbl_luminance[quality],
			     EXYNOS4_QTBL_CONTENT(0),
			     ARRAY_SIZE(qtbl_luminance[quality]));
पूर्ण

अटल अंतरभूत व्योम exynos4_jpeg_set_qtbl_chr(व्योम __iomem *regs, पूर्णांक quality)
अणु
	/* this driver fills quantisation table 1 with data क्रम chroma */
	exynos4_jpeg_set_tbl(regs, qtbl_chrominance[quality],
			     EXYNOS4_QTBL_CONTENT(1),
			     ARRAY_SIZE(qtbl_chrominance[quality]));
पूर्ण

अटल व्योम exynos4_jpeg_set_huff_tbl(व्योम __iomem *base)
अणु
	exynos4_jpeg_set_tbl(base, hdctbl0, EXYNOS4_HUFF_TBL_HDCLL,
							ARRAY_SIZE(hdctbl0));
	exynos4_jpeg_set_tbl(base, hdctbl0, EXYNOS4_HUFF_TBL_HDCCL,
							ARRAY_SIZE(hdctbl0));
	exynos4_jpeg_set_tbl(base, hdctblg0, EXYNOS4_HUFF_TBL_HDCLV,
							ARRAY_SIZE(hdctblg0));
	exynos4_jpeg_set_tbl(base, hdctblg0, EXYNOS4_HUFF_TBL_HDCCV,
							ARRAY_SIZE(hdctblg0));
	exynos4_jpeg_set_tbl(base, hactbl0, EXYNOS4_HUFF_TBL_HACLL,
							ARRAY_SIZE(hactbl0));
	exynos4_jpeg_set_tbl(base, hactbl0, EXYNOS4_HUFF_TBL_HACCL,
							ARRAY_SIZE(hactbl0));
	exynos4_jpeg_set_tbl(base, hactblg0, EXYNOS4_HUFF_TBL_HACLV,
							ARRAY_SIZE(hactblg0));
	exynos4_jpeg_set_tbl(base, hactblg0, EXYNOS4_HUFF_TBL_HACCV,
							ARRAY_SIZE(hactblg0));
पूर्ण

अटल अंतरभूत पूर्णांक __exynos4_huff_tbl(पूर्णांक class, पूर्णांक id, bool lenval)
अणु
	/*
	 * class: 0 - DC, 1 - AC
	 * id: 0 - Y, 1 - Cb/Cr
	 */
	अगर (class) अणु
		अगर (id)
			वापस lenval ? EXYNOS4_HUFF_TBL_HACCL :
				EXYNOS4_HUFF_TBL_HACCV;
		वापस lenval ? EXYNOS4_HUFF_TBL_HACLL : EXYNOS4_HUFF_TBL_HACLV;

	पूर्ण
	/* class == 0 */
	अगर (id)
		वापस lenval ? EXYNOS4_HUFF_TBL_HDCCL : EXYNOS4_HUFF_TBL_HDCCV;

	वापस lenval ? EXYNOS4_HUFF_TBL_HDCLL : EXYNOS4_HUFF_TBL_HDCLV;
पूर्ण

अटल अंतरभूत पूर्णांक exynos4_huff_tbl_len(पूर्णांक class, पूर्णांक id)
अणु
	वापस __exynos4_huff_tbl(class, id, true);
पूर्ण

अटल अंतरभूत पूर्णांक exynos4_huff_tbl_val(पूर्णांक class, पूर्णांक id)
अणु
	वापस __exynos4_huff_tbl(class, id, false);
पूर्ण

अटल पूर्णांक get_byte(काष्ठा s5p_jpeg_buffer *buf);
अटल पूर्णांक get_word_be(काष्ठा s5p_jpeg_buffer *buf, अचिन्हित पूर्णांक *word);
अटल व्योम skip(काष्ठा s5p_jpeg_buffer *buf, दीर्घ len);

अटल व्योम exynos4_jpeg_parse_decode_h_tbl(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	काष्ठा s5p_jpeg_buffer jpeg_buffer;
	अचिन्हित पूर्णांक word;
	पूर्णांक c, x, components;

	jpeg_buffer.size = 2; /* Ls */
	jpeg_buffer.data =
		(अचिन्हित दीर्घ)vb2_plane_vaddr(&vb->vb2_buf, 0) + ctx->out_q.sos + 2;
	jpeg_buffer.curr = 0;

	word = 0;

	अगर (get_word_be(&jpeg_buffer, &word))
		वापस;
	jpeg_buffer.size = (दीर्घ)word - 2;
	jpeg_buffer.data += 2;
	jpeg_buffer.curr = 0;

	components = get_byte(&jpeg_buffer);
	अगर (components == -1)
		वापस;
	जबतक (components--) अणु
		c = get_byte(&jpeg_buffer);
		अगर (c == -1)
			वापस;
		x = get_byte(&jpeg_buffer);
		अगर (x == -1)
			वापस;
		exynos4_jpeg_select_dec_h_tbl(jpeg->regs, c,
					(((x >> 4) & 0x1) << 1) | (x & 0x1));
	पूर्ण

पूर्ण

अटल व्योम exynos4_jpeg_parse_huff_tbl(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	काष्ठा s5p_jpeg_buffer jpeg_buffer;
	अचिन्हित पूर्णांक word;
	पूर्णांक c, i, n, j;

	क्रम (j = 0; j < ctx->out_q.dht.n; ++j) अणु
		jpeg_buffer.size = ctx->out_q.dht.len[j];
		jpeg_buffer.data = (अचिन्हित दीर्घ)vb2_plane_vaddr(&vb->vb2_buf, 0) +
				   ctx->out_q.dht.marker[j];
		jpeg_buffer.curr = 0;

		word = 0;
		जबतक (jpeg_buffer.curr < jpeg_buffer.size) अणु
			अक्षर id, class;

			c = get_byte(&jpeg_buffer);
			अगर (c == -1)
				वापस;
			id = c & 0xf;
			class = (c >> 4) & 0xf;
			n = 0;
			क्रम (i = 0; i < 16; ++i) अणु
				c = get_byte(&jpeg_buffer);
				अगर (c == -1)
					वापस;
				word |= c << ((i % 4) * 8);
				अगर ((i + 1) % 4 == 0) अणु
					ग_लिखोl(word, jpeg->regs +
					exynos4_huff_tbl_len(class, id) +
					(i / 4) * 4);
					word = 0;
				पूर्ण
				n += c;
			पूर्ण
			word = 0;
			क्रम (i = 0; i < n; ++i) अणु
				c = get_byte(&jpeg_buffer);
				अगर (c == -1)
					वापस;
				word |= c << ((i % 4) * 8);
				अगर ((i + 1) % 4 == 0) अणु
					ग_लिखोl(word, jpeg->regs +
					exynos4_huff_tbl_val(class, id) +
					(i / 4) * 4);
					word = 0;
				पूर्ण
			पूर्ण
			अगर (i % 4) अणु
				ग_लिखोl(word, jpeg->regs +
				exynos4_huff_tbl_val(class, id) + (i / 4) * 4);
			पूर्ण
			word = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम exynos4_jpeg_parse_decode_q_tbl(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	काष्ठा s5p_jpeg_buffer jpeg_buffer;
	पूर्णांक c, x, components;

	jpeg_buffer.size = ctx->out_q.sof_len;
	jpeg_buffer.data =
		(अचिन्हित दीर्घ)vb2_plane_vaddr(&vb->vb2_buf, 0) + ctx->out_q.sof;
	jpeg_buffer.curr = 0;

	skip(&jpeg_buffer, 5); /* P, Y, X */
	components = get_byte(&jpeg_buffer);
	अगर (components == -1)
		वापस;

	exynos4_jpeg_set_dec_components(jpeg->regs, components);

	जबतक (components--) अणु
		c = get_byte(&jpeg_buffer);
		अगर (c == -1)
			वापस;
		skip(&jpeg_buffer, 1);
		x = get_byte(&jpeg_buffer);
		अगर (x == -1)
			वापस;
		exynos4_jpeg_select_dec_q_tbl(jpeg->regs, c, x);
	पूर्ण
पूर्ण

अटल व्योम exynos4_jpeg_parse_q_tbl(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	काष्ठा s5p_jpeg_buffer jpeg_buffer;
	अचिन्हित पूर्णांक word;
	पूर्णांक c, i, j;

	क्रम (j = 0; j < ctx->out_q.dqt.n; ++j) अणु
		jpeg_buffer.size = ctx->out_q.dqt.len[j];
		jpeg_buffer.data = (अचिन्हित दीर्घ)vb2_plane_vaddr(&vb->vb2_buf, 0) +
				   ctx->out_q.dqt.marker[j];
		jpeg_buffer.curr = 0;

		word = 0;
		जबतक (jpeg_buffer.size - jpeg_buffer.curr >= 65) अणु
			अक्षर id;

			c = get_byte(&jpeg_buffer);
			अगर (c == -1)
				वापस;
			id = c & 0xf;
			/* nonzero means extended mode - not supported */
			अगर ((c >> 4) & 0xf)
				वापस;
			क्रम (i = 0; i < 64; ++i) अणु
				c = get_byte(&jpeg_buffer);
				अगर (c == -1)
					वापस;
				word |= c << ((i % 4) * 8);
				अगर ((i + 1) % 4 == 0) अणु
					ग_लिखोl(word, jpeg->regs +
					EXYNOS4_QTBL_CONTENT(id) + (i / 4) * 4);
					word = 0;
				पूर्ण
			पूर्ण
			word = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ============================================================================
 * Device file operations
 * ============================================================================
 */

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq);
अटल काष्ठा s5p_jpeg_fmt *s5p_jpeg_find_क्रमmat(काष्ठा s5p_jpeg_ctx *ctx,
				__u32 pixelक्रमmat, अचिन्हित पूर्णांक fmt_type);
अटल पूर्णांक s5p_jpeg_controls_create(काष्ठा s5p_jpeg_ctx *ctx);

अटल पूर्णांक s5p_jpeg_खोलो(काष्ठा file *file)
अणु
	काष्ठा s5p_jpeg *jpeg = video_drvdata(file);
	काष्ठा video_device *vfd = video_devdata(file);
	काष्ठा s5p_jpeg_ctx *ctx;
	काष्ठा s5p_jpeg_fmt *out_fmt, *cap_fmt;
	पूर्णांक ret = 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (mutex_lock_पूर्णांकerruptible(&jpeg->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ मुक्त;
	पूर्ण

	v4l2_fh_init(&ctx->fh, vfd);
	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->निजी_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->jpeg = jpeg;
	अगर (vfd == jpeg->vfd_encoder) अणु
		ctx->mode = S5P_JPEG_ENCODE;
		out_fmt = s5p_jpeg_find_क्रमmat(ctx, V4L2_PIX_FMT_RGB565,
							FMT_TYPE_OUTPUT);
		cap_fmt = s5p_jpeg_find_क्रमmat(ctx, V4L2_PIX_FMT_JPEG,
							FMT_TYPE_CAPTURE);
	पूर्ण अन्यथा अणु
		ctx->mode = S5P_JPEG_DECODE;
		out_fmt = s5p_jpeg_find_क्रमmat(ctx, V4L2_PIX_FMT_JPEG,
							FMT_TYPE_OUTPUT);
		cap_fmt = s5p_jpeg_find_क्रमmat(ctx, V4L2_PIX_FMT_YUYV,
							FMT_TYPE_CAPTURE);
		ctx->scale_factor = EXYNOS3250_DEC_SCALE_FACTOR_8_8;
	पूर्ण

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(jpeg->m2m_dev, ctx, queue_init);
	अगर (IS_ERR(ctx->fh.m2m_ctx)) अणु
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		जाओ error;
	पूर्ण

	ctx->out_q.fmt = out_fmt;
	ctx->cap_q.fmt = cap_fmt;

	ret = s5p_jpeg_controls_create(ctx);
	अगर (ret < 0)
		जाओ error;

	mutex_unlock(&jpeg->lock);
	वापस 0;

error:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	mutex_unlock(&jpeg->lock);
मुक्त:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_jpeg_release(काष्ठा file *file)
अणु
	काष्ठा s5p_jpeg *jpeg = video_drvdata(file);
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(file->निजी_data);

	mutex_lock(&jpeg->lock);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_निकास(&ctx->fh);
	kमुक्त(ctx);
	mutex_unlock(&jpeg->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations s5p_jpeg_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= s5p_jpeg_खोलो,
	.release	= s5p_jpeg_release,
	.poll		= v4l2_m2m_fop_poll,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= v4l2_m2m_fop_mmap,
पूर्ण;

/*
 * ============================================================================
 * video ioctl operations
 * ============================================================================
 */

अटल पूर्णांक get_byte(काष्ठा s5p_jpeg_buffer *buf)
अणु
	अगर (buf->curr >= buf->size)
		वापस -1;

	वापस ((अचिन्हित अक्षर *)buf->data)[buf->curr++];
पूर्ण

अटल पूर्णांक get_word_be(काष्ठा s5p_jpeg_buffer *buf, अचिन्हित पूर्णांक *word)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक byte;

	byte = get_byte(buf);
	अगर (byte == -1)
		वापस -1;
	temp = byte << 8;
	byte = get_byte(buf);
	अगर (byte == -1)
		वापस -1;
	*word = (अचिन्हित पूर्णांक)byte | temp;
	वापस 0;
पूर्ण

अटल व्योम skip(काष्ठा s5p_jpeg_buffer *buf, दीर्घ len)
अणु
	अगर (len <= 0)
		वापस;

	जबतक (len--)
		get_byte(buf);
पूर्ण

अटल bool s5p_jpeg_subsampling_decode(काष्ठा s5p_jpeg_ctx *ctx,
					अचिन्हित पूर्णांक subsampling)
अणु
	अचिन्हित पूर्णांक version;

	चयन (subsampling) अणु
	हाल 0x11:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_444;
		अवरोध;
	हाल 0x21:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_422;
		अवरोध;
	हाल 0x22:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_420;
		अवरोध;
	हाल 0x33:
		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;
		अवरोध;
	हाल 0x41:
		/*
		 * 4:1:1 subsampling only supported by 3250, 5420, and 5433
		 * variants
		 */
		version = ctx->jpeg->variant->version;
		अगर (version != SJPEG_EXYNOS3250 &&
		    version != SJPEG_EXYNOS5420 &&
		    version != SJPEG_EXYNOS5433)
			वापस false;

		ctx->subsampling = V4L2_JPEG_CHROMA_SUBSAMPLING_411;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool s5p_jpeg_parse_hdr(काष्ठा s5p_jpeg_q_data *result,
			       अचिन्हित दीर्घ buffer, अचिन्हित दीर्घ size,
			       काष्ठा s5p_jpeg_ctx *ctx)
अणु
	पूर्णांक c, components = 0, notfound, n_dht = 0, n_dqt = 0;
	अचिन्हित पूर्णांक height = 0, width = 0, word, subsampling = 0;
	अचिन्हित पूर्णांक sos = 0, sof = 0, sof_len = 0;
	अचिन्हित पूर्णांक dht[S5P_JPEG_MAX_MARKER], dht_len[S5P_JPEG_MAX_MARKER];
	अचिन्हित पूर्णांक dqt[S5P_JPEG_MAX_MARKER], dqt_len[S5P_JPEG_MAX_MARKER];
	दीर्घ length;
	काष्ठा s5p_jpeg_buffer jpeg_buffer;

	jpeg_buffer.size = size;
	jpeg_buffer.data = buffer;
	jpeg_buffer.curr = 0;

	notfound = 1;
	जबतक (notfound || !sos) अणु
		c = get_byte(&jpeg_buffer);
		अगर (c == -1)
			वापस false;
		अगर (c != 0xff)
			जारी;
		करो
			c = get_byte(&jpeg_buffer);
		जबतक (c == 0xff);
		अगर (c == -1)
			वापस false;
		अगर (c == 0)
			जारी;
		length = 0;
		चयन (c) अणु
		/* SOF0: baseline JPEG */
		हाल SOF0:
			अगर (get_word_be(&jpeg_buffer, &word))
				अवरोध;
			length = (दीर्घ)word - 2;
			अगर (!length)
				वापस false;
			sof = jpeg_buffer.curr; /* after 0xffc0 */
			sof_len = length;
			अगर (get_byte(&jpeg_buffer) == -1)
				अवरोध;
			अगर (get_word_be(&jpeg_buffer, &height))
				अवरोध;
			अगर (get_word_be(&jpeg_buffer, &width))
				अवरोध;
			components = get_byte(&jpeg_buffer);
			अगर (components == -1)
				अवरोध;

			अगर (components == 1) अणु
				subsampling = 0x33;
			पूर्ण अन्यथा अणु
				skip(&jpeg_buffer, 1);
				subsampling = get_byte(&jpeg_buffer);
				skip(&jpeg_buffer, 1);
			पूर्ण
			अगर (components > 3)
				वापस false;
			skip(&jpeg_buffer, components * 2);
			notfound = 0;
			अवरोध;

		हाल DQT:
			अगर (get_word_be(&jpeg_buffer, &word))
				अवरोध;
			length = (दीर्घ)word - 2;
			अगर (!length)
				वापस false;
			अगर (n_dqt >= S5P_JPEG_MAX_MARKER)
				वापस false;
			dqt[n_dqt] = jpeg_buffer.curr; /* after 0xffdb */
			dqt_len[n_dqt++] = length;
			skip(&jpeg_buffer, length);
			अवरोध;

		हाल DHT:
			अगर (get_word_be(&jpeg_buffer, &word))
				अवरोध;
			length = (दीर्घ)word - 2;
			अगर (!length)
				वापस false;
			अगर (n_dht >= S5P_JPEG_MAX_MARKER)
				वापस false;
			dht[n_dht] = jpeg_buffer.curr; /* after 0xffc4 */
			dht_len[n_dht++] = length;
			skip(&jpeg_buffer, length);
			अवरोध;

		हाल SOS:
			sos = jpeg_buffer.curr - 2; /* 0xffda */
			अवरोध;

		/* skip payload-less markers */
		हाल RST ... RST + 7:
		हाल SOI:
		हाल EOI:
		हाल TEM:
			अवरोध;

		/* skip unपूर्णांकeresting payload markers */
		शेष:
			अगर (get_word_be(&jpeg_buffer, &word))
				अवरोध;
			length = (दीर्घ)word - 2;
			skip(&jpeg_buffer, length);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (notfound || !sos || !s5p_jpeg_subsampling_decode(ctx, subsampling))
		वापस false;

	result->w = width;
	result->h = height;
	result->sos = sos;
	result->dht.n = n_dht;
	जबतक (n_dht--) अणु
		result->dht.marker[n_dht] = dht[n_dht];
		result->dht.len[n_dht] = dht_len[n_dht];
	पूर्ण
	result->dqt.n = n_dqt;
	जबतक (n_dqt--) अणु
		result->dqt.marker[n_dqt] = dqt[n_dqt];
		result->dqt.len[n_dqt] = dqt_len[n_dqt];
	पूर्ण
	result->sof = sof;
	result->sof_len = sof_len;

	वापस true;
पूर्ण

अटल पूर्णांक s5p_jpeg_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		strscpy(cap->driver, S5P_JPEG_M2M_NAME,
			माप(cap->driver));
		strscpy(cap->card, S5P_JPEG_M2M_NAME " encoder",
			माप(cap->card));
	पूर्ण अन्यथा अणु
		strscpy(cap->driver, S5P_JPEG_M2M_NAME,
			माप(cap->driver));
		strscpy(cap->card, S5P_JPEG_M2M_NAME " decoder",
			माप(cap->card));
	पूर्ण
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(ctx->jpeg->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक क्रमागत_fmt(काष्ठा s5p_jpeg_ctx *ctx,
		    काष्ठा s5p_jpeg_fmt *sjpeg_क्रमmats, पूर्णांक n,
		    काष्ठा v4l2_fmtdesc *f, u32 type)
अणु
	पूर्णांक i, num = 0;
	अचिन्हित पूर्णांक fmt_ver_flag = ctx->jpeg->variant->fmt_ver_flag;

	क्रम (i = 0; i < n; ++i) अणु
		अगर (sjpeg_क्रमmats[i].flags & type &&
		    sjpeg_क्रमmats[i].flags & fmt_ver_flag) अणु
			/* index-th क्रमmat of type type found ? */
			अगर (num == f->index)
				अवरोध;
			/* Correct type but haven't reached our index yet,
			 * just increment per-type index
			 */
			++num;
		पूर्ण
	पूर्ण

	/* Format not found */
	अगर (i >= n)
		वापस -EINVAL;

	f->pixelक्रमmat = sjpeg_क्रमmats[i].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->mode == S5P_JPEG_ENCODE)
		वापस क्रमागत_fmt(ctx, sjpeg_क्रमmats, SJPEG_NUM_FORMATS, f,
				SJPEG_FMT_FLAG_ENC_CAPTURE);

	वापस क्रमागत_fmt(ctx, sjpeg_क्रमmats, SJPEG_NUM_FORMATS, f,
			SJPEG_FMT_FLAG_DEC_CAPTURE);
पूर्ण

अटल पूर्णांक s5p_jpeg_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	अगर (ctx->mode == S5P_JPEG_ENCODE)
		वापस क्रमागत_fmt(ctx, sjpeg_क्रमmats, SJPEG_NUM_FORMATS, f,
				SJPEG_FMT_FLAG_ENC_OUTPUT);

	वापस क्रमागत_fmt(ctx, sjpeg_क्रमmats, SJPEG_NUM_FORMATS, f,
			SJPEG_FMT_FLAG_DEC_OUTPUT);
पूर्ण

अटल काष्ठा s5p_jpeg_q_data *get_q_data(काष्ठा s5p_jpeg_ctx *ctx,
					  क्रमागत v4l2_buf_type type)
अणु
	अगर (type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस &ctx->out_q;
	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस &ctx->cap_q;

	वापस शून्य;
पूर्ण

अटल पूर्णांक s5p_jpeg_g_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा s5p_jpeg_q_data *q_data = शून्य;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा s5p_jpeg_ctx *ct = fh_to_ctx(priv);

	vq = v4l2_m2m_get_vq(ct->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	अगर (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    ct->mode == S5P_JPEG_DECODE && !ct->hdr_parsed)
		वापस -EINVAL;
	q_data = get_q_data(ct, f->type);
	BUG_ON(q_data == शून्य);

	pix->width = q_data->w;
	pix->height = q_data->h;
	pix->field = V4L2_FIELD_NONE;
	pix->pixelक्रमmat = q_data->fmt->fourcc;
	pix->bytesperline = 0;
	अगर (q_data->fmt->fourcc != V4L2_PIX_FMT_JPEG) अणु
		u32 bpl = q_data->w;

		अगर (q_data->fmt->colplanes == 1)
			bpl = (bpl * q_data->fmt->depth) >> 3;
		pix->bytesperline = bpl;
	पूर्ण
	pix->sizeimage = q_data->size;

	वापस 0;
पूर्ण

अटल काष्ठा s5p_jpeg_fmt *s5p_jpeg_find_क्रमmat(काष्ठा s5p_jpeg_ctx *ctx,
				u32 pixelक्रमmat, अचिन्हित पूर्णांक fmt_type)
अणु
	अचिन्हित पूर्णांक k, fmt_flag;

	अगर (ctx->mode == S5P_JPEG_ENCODE)
		fmt_flag = (fmt_type == FMT_TYPE_OUTPUT) ?
				SJPEG_FMT_FLAG_ENC_OUTPUT :
				SJPEG_FMT_FLAG_ENC_CAPTURE;
	अन्यथा
		fmt_flag = (fmt_type == FMT_TYPE_OUTPUT) ?
				SJPEG_FMT_FLAG_DEC_OUTPUT :
				SJPEG_FMT_FLAG_DEC_CAPTURE;

	क्रम (k = 0; k < ARRAY_SIZE(sjpeg_क्रमmats); k++) अणु
		काष्ठा s5p_jpeg_fmt *fmt = &sjpeg_क्रमmats[k];

		अगर (fmt->fourcc == pixelक्रमmat &&
		    fmt->flags & fmt_flag &&
		    fmt->flags & ctx->jpeg->variant->fmt_ver_flag) अणु
			वापस fmt;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम jpeg_bound_align_image(काष्ठा s5p_jpeg_ctx *ctx,
				   u32 *w, अचिन्हित पूर्णांक wmin, अचिन्हित पूर्णांक wmax,
				   अचिन्हित पूर्णांक walign,
				   u32 *h, अचिन्हित पूर्णांक hmin, अचिन्हित पूर्णांक hmax,
				   अचिन्हित पूर्णांक halign)
अणु
	पूर्णांक width, height, w_step, h_step;

	width = *w;
	height = *h;

	w_step = 1 << walign;
	h_step = 1 << halign;

	अगर (ctx->jpeg->variant->hw3250_compat) अणु
		/*
		 * Righपंचांगost and bottommost pixels are cropped by the
		 * Exynos3250/compatible JPEG IP क्रम RGB क्रमmats, क्रम the
		 * specअगरic width and height values respectively. This
		 * assignment will result in v4l_bound_align_image वापसing
		 * dimensions reduced by 1 क्रम the aक्रमementioned हालs.
		 */
		अगर (w_step == 4 && ((width & 3) == 1)) अणु
			wmax = width;
			hmax = height;
		पूर्ण
	पूर्ण

	v4l_bound_align_image(w, wmin, wmax, walign, h, hmin, hmax, halign, 0);

	अगर (*w < width && (*w + w_step) < wmax)
		*w += w_step;
	अगर (*h < height && (*h + h_step) < hmax)
		*h += h_step;
पूर्ण

अटल पूर्णांक vidioc_try_fmt(काष्ठा v4l2_क्रमmat *f, काष्ठा s5p_jpeg_fmt *fmt,
			  काष्ठा s5p_jpeg_ctx *ctx, पूर्णांक q_type)
अणु
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;

	अगर (pix->field == V4L2_FIELD_ANY)
		pix->field = V4L2_FIELD_NONE;
	अन्यथा अगर (pix->field != V4L2_FIELD_NONE)
		वापस -EINVAL;

	/* V4L2 specअगरication suggests the driver corrects the क्रमmat काष्ठा
	 * अगर any of the dimensions is unsupported
	 */
	अगर (q_type == FMT_TYPE_OUTPUT)
		jpeg_bound_align_image(ctx, &pix->width, S5P_JPEG_MIN_WIDTH,
				       S5P_JPEG_MAX_WIDTH, 0,
				       &pix->height, S5P_JPEG_MIN_HEIGHT,
				       S5P_JPEG_MAX_HEIGHT, 0);
	अन्यथा
		jpeg_bound_align_image(ctx, &pix->width, S5P_JPEG_MIN_WIDTH,
				       S5P_JPEG_MAX_WIDTH, fmt->h_align,
				       &pix->height, S5P_JPEG_MIN_HEIGHT,
				       S5P_JPEG_MAX_HEIGHT, fmt->v_align);

	अगर (fmt->fourcc == V4L2_PIX_FMT_JPEG) अणु
		अगर (pix->sizeimage <= 0)
			pix->sizeimage = PAGE_SIZE;
		pix->bytesperline = 0;
	पूर्ण अन्यथा अणु
		u32 bpl = pix->bytesperline;

		अगर (fmt->colplanes > 1 && bpl < pix->width)
			bpl = pix->width; /* planar */

		अगर (fmt->colplanes == 1 && /* packed */
		    (bpl << 3) / fmt->depth < pix->width)
			bpl = (pix->width * fmt->depth) >> 3;

		pix->bytesperline = bpl;
		pix->sizeimage = (pix->width * pix->height * fmt->depth) >> 3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(priv);
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा s5p_jpeg_fmt *fmt;
	पूर्णांक ret;

	fmt = s5p_jpeg_find_क्रमmat(ctx, f->fmt.pix.pixelक्रमmat,
						FMT_TYPE_CAPTURE);
	अगर (!fmt) अणु
		v4l2_err(&ctx->jpeg->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (!ctx->jpeg->variant->hw_ex4_compat || ctx->mode != S5P_JPEG_DECODE)
		जाओ निकास;

	/*
	 * The exynos4x12 device requires resulting YUV image
	 * subsampling not to be lower than the input jpeg subsampling.
	 * If this requirement is not met then करोwngrade the requested
	 * capture क्रमmat to the one with subsampling equal to the input jpeg.
	 */
	अगर ((fmt->flags & SJPEG_FMT_NON_RGB) &&
	    (fmt->subsampling < ctx->subsampling)) अणु
		ret = s5p_jpeg_adjust_fourcc_to_subsampling(ctx->subsampling,
							    fmt->fourcc,
							    &pix->pixelक्रमmat,
							    ctx);
		अगर (ret < 0)
			pix->pixelक्रमmat = V4L2_PIX_FMT_GREY;

		fmt = s5p_jpeg_find_क्रमmat(ctx, pix->pixelक्रमmat,
							FMT_TYPE_CAPTURE);
	पूर्ण

	/*
	 * Decompression of a JPEG file with 4:2:0 subsampling and odd
	 * width to the YUV 4:2:0 compliant क्रमmats produces a raw image
	 * with broken luma component. Adjust capture क्रमmat to RGB565
	 * in such a हाल.
	 */
	अगर (ctx->subsampling == V4L2_JPEG_CHROMA_SUBSAMPLING_420 &&
	    (ctx->out_q.w & 1) &&
	    (pix->pixelक्रमmat == V4L2_PIX_FMT_NV12 ||
	     pix->pixelक्रमmat == V4L2_PIX_FMT_NV21 ||
	     pix->pixelक्रमmat == V4L2_PIX_FMT_YUV420)) अणु
		pix->pixelक्रमmat = V4L2_PIX_FMT_RGB565;
		fmt = s5p_jpeg_find_क्रमmat(ctx, pix->pixelक्रमmat,
							FMT_TYPE_CAPTURE);
	पूर्ण

निकास:
	वापस vidioc_try_fmt(f, fmt, ctx, FMT_TYPE_CAPTURE);
पूर्ण

अटल पूर्णांक s5p_jpeg_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(priv);
	काष्ठा s5p_jpeg_fmt *fmt;

	fmt = s5p_jpeg_find_क्रमmat(ctx, f->fmt.pix.pixelक्रमmat,
						FMT_TYPE_OUTPUT);
	अगर (!fmt) अणु
		v4l2_err(&ctx->jpeg->v4l2_dev,
			 "Fourcc format (0x%08x) invalid.\n",
			 f->fmt.pix.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस vidioc_try_fmt(f, fmt, ctx, FMT_TYPE_OUTPUT);
पूर्ण

अटल पूर्णांक exynos4_jpeg_get_output_buffer_size(काष्ठा s5p_jpeg_ctx *ctx,
						काष्ठा v4l2_क्रमmat *f,
						पूर्णांक fmt_depth)
अणु
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	u32 pix_fmt = f->fmt.pix.pixelक्रमmat;
	पूर्णांक w = pix->width, h = pix->height, wh_align;
	पूर्णांक padding = 0;

	अगर (pix_fmt == V4L2_PIX_FMT_RGB32 ||
	    pix_fmt == V4L2_PIX_FMT_RGB565 ||
	    pix_fmt == V4L2_PIX_FMT_NV24 ||
	    pix_fmt == V4L2_PIX_FMT_NV42 ||
	    pix_fmt == V4L2_PIX_FMT_NV12 ||
	    pix_fmt == V4L2_PIX_FMT_NV21 ||
	    pix_fmt == V4L2_PIX_FMT_YUV420)
		wh_align = 4;
	अन्यथा
		wh_align = 1;

	jpeg_bound_align_image(ctx, &w, S5P_JPEG_MIN_WIDTH,
			       S5P_JPEG_MAX_WIDTH, wh_align,
			       &h, S5P_JPEG_MIN_HEIGHT,
			       S5P_JPEG_MAX_HEIGHT, wh_align);

	अगर (ctx->jpeg->variant->version == SJPEG_EXYNOS4)
		padding = PAGE_SIZE;

	वापस (w * h * fmt_depth >> 3) + padding;
पूर्ण

अटल पूर्णांक exynos3250_jpeg_try_करोwnscale(काष्ठा s5p_jpeg_ctx *ctx,
				   काष्ठा v4l2_rect *r);

अटल पूर्णांक s5p_jpeg_s_fmt(काष्ठा s5p_jpeg_ctx *ct, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vb2_queue *vq;
	काष्ठा s5p_jpeg_q_data *q_data = शून्य;
	काष्ठा v4l2_pix_क्रमmat *pix = &f->fmt.pix;
	काष्ठा v4l2_ctrl *ctrl_subs;
	काष्ठा v4l2_rect scale_rect;
	अचिन्हित पूर्णांक f_type;

	vq = v4l2_m2m_get_vq(ct->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;

	q_data = get_q_data(ct, f->type);
	BUG_ON(q_data == शून्य);

	अगर (vb2_is_busy(vq)) अणु
		v4l2_err(&ct->jpeg->v4l2_dev, "%s queue busy\n", __func__);
		वापस -EBUSY;
	पूर्ण

	f_type = V4L2_TYPE_IS_OUTPUT(f->type) ?
			FMT_TYPE_OUTPUT : FMT_TYPE_CAPTURE;

	q_data->fmt = s5p_jpeg_find_क्रमmat(ct, pix->pixelक्रमmat, f_type);
	अगर (ct->mode == S5P_JPEG_ENCODE ||
		(ct->mode == S5P_JPEG_DECODE &&
		q_data->fmt->fourcc != V4L2_PIX_FMT_JPEG)) अणु
		q_data->w = pix->width;
		q_data->h = pix->height;
	पूर्ण
	अगर (q_data->fmt->fourcc != V4L2_PIX_FMT_JPEG) अणु
		/*
		 * During encoding Exynos4x12 SoCs access wider memory area
		 * than it results from Image_x and Image_y values written to
		 * the JPEG_IMAGE_SIZE रेजिस्टर. In order to aव्योम sysmmu
		 * page fault calculate proper buffer size in such a हाल.
		 */
		अगर (ct->jpeg->variant->hw_ex4_compat &&
		    f_type == FMT_TYPE_OUTPUT && ct->mode == S5P_JPEG_ENCODE)
			q_data->size = exynos4_jpeg_get_output_buffer_size(ct,
							f,
							q_data->fmt->depth);
		अन्यथा
			q_data->size = q_data->w * q_data->h *
						q_data->fmt->depth >> 3;
	पूर्ण अन्यथा अणु
		q_data->size = pix->sizeimage;
	पूर्ण

	अगर (f_type == FMT_TYPE_OUTPUT) अणु
		ctrl_subs = v4l2_ctrl_find(&ct->ctrl_handler,
					V4L2_CID_JPEG_CHROMA_SUBSAMPLING);
		अगर (ctrl_subs)
			v4l2_ctrl_s_ctrl(ctrl_subs, q_data->fmt->subsampling);
		ct->crop_altered = false;
	पूर्ण

	/*
	 * For decoding init crop_rect with capture buffer dimmensions which
	 * contain aligned dimensions of the input JPEG image and करो it only
	 * अगर crop rectangle hasn't been altered by the user space e.g. with
	 * S_SELECTION ioctl. For encoding assign output buffer dimensions.
	 */
	अगर (!ct->crop_altered &&
	    ((ct->mode == S5P_JPEG_DECODE && f_type == FMT_TYPE_CAPTURE) ||
	     (ct->mode == S5P_JPEG_ENCODE && f_type == FMT_TYPE_OUTPUT))) अणु
		ct->crop_rect.width = pix->width;
		ct->crop_rect.height = pix->height;
	पूर्ण

	/*
	 * Prevent करोwnscaling to YUV420 क्रमmat by more than 2
	 * क्रम Exynos3250/compatible SoC as it produces broken raw image
	 * in such हालs.
	 */
	अगर (ct->mode == S5P_JPEG_DECODE &&
	    f_type == FMT_TYPE_CAPTURE &&
	    ct->jpeg->variant->hw3250_compat &&
	    pix->pixelक्रमmat == V4L2_PIX_FMT_YUV420 &&
	    ct->scale_factor > 2) अणु
		scale_rect.width = ct->out_q.w / 2;
		scale_rect.height = ct->out_q.h / 2;
		exynos3250_jpeg_try_करोwnscale(ct, &scale_rect);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = s5p_jpeg_try_fmt_vid_cap(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस s5p_jpeg_s_fmt(fh_to_ctx(priv), f);
पूर्ण

अटल पूर्णांक s5p_jpeg_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret;

	ret = s5p_jpeg_try_fmt_vid_out(file, priv, f);
	अगर (ret)
		वापस ret;

	वापस s5p_jpeg_s_fmt(fh_to_ctx(priv), f);
पूर्ण

अटल पूर्णांक s5p_jpeg_subscribe_event(काष्ठा v4l2_fh *fh,
				    स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type == V4L2_EVENT_SOURCE_CHANGE)
		वापस v4l2_src_change_event_subscribe(fh, sub);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक exynos3250_jpeg_try_करोwnscale(काष्ठा s5p_jpeg_ctx *ctx,
				   काष्ठा v4l2_rect *r)
अणु
	पूर्णांक w_ratio, h_ratio, scale_factor, cur_ratio, i;

	w_ratio = ctx->out_q.w / r->width;
	h_ratio = ctx->out_q.h / r->height;

	scale_factor = w_ratio > h_ratio ? w_ratio : h_ratio;
	scale_factor = clamp_val(scale_factor, 1, 8);

	/* Align scale ratio to the nearest घातer of 2 */
	क्रम (i = 0; i <= 3; ++i) अणु
		cur_ratio = 1 << i;
		अगर (scale_factor <= cur_ratio) अणु
			ctx->scale_factor = cur_ratio;
			अवरोध;
		पूर्ण
	पूर्ण

	r->width = round_करोwn(ctx->out_q.w / ctx->scale_factor, 2);
	r->height = round_करोwn(ctx->out_q.h / ctx->scale_factor, 2);

	ctx->crop_rect.width = r->width;
	ctx->crop_rect.height = r->height;
	ctx->crop_rect.left = 0;
	ctx->crop_rect.top = 0;

	ctx->crop_altered = true;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos3250_jpeg_try_crop(काष्ठा s5p_jpeg_ctx *ctx,
				   काष्ठा v4l2_rect *r)
अणु
	काष्ठा v4l2_rect base_rect;
	पूर्णांक w_step, h_step;

	चयन (ctx->cap_q.fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		w_step = 1;
		h_step = 2;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		w_step = 2;
		h_step = 2;
		अवरोध;
	शेष:
		w_step = 1;
		h_step = 1;
		अवरोध;
	पूर्ण

	base_rect.top = 0;
	base_rect.left = 0;
	base_rect.width = ctx->out_q.w;
	base_rect.height = ctx->out_q.h;

	r->width = round_करोwn(r->width, w_step);
	r->height = round_करोwn(r->height, h_step);
	r->left = round_करोwn(r->left, 2);
	r->top = round_करोwn(r->top, 2);

	अगर (!v4l2_rect_enबंदd(r, &base_rect))
		वापस -EINVAL;

	ctx->crop_rect.left = r->left;
	ctx->crop_rect.top = r->top;
	ctx->crop_rect.width = r->width;
	ctx->crop_rect.height = r->height;

	ctx->crop_altered = true;

	वापस 0;
पूर्ण

/*
 * V4L2 controls
 */

अटल पूर्णांक s5p_jpeg_g_selection(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_selection *s)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	/* For JPEG blob active == शेष == bounds */
	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_COMPOSE_DEFAULT:
		s->r.width = ctx->out_q.w;
		s->r.height = ctx->out_q.h;
		s->r.left = 0;
		s->r.top = 0;
		अवरोध;
	हाल V4L2_SEL_TGT_COMPOSE:
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
	हाल V4L2_SEL_TGT_COMPOSE_PADDED:
		s->r.width = ctx->crop_rect.width;
		s->r.height =  ctx->crop_rect.height;
		s->r.left = ctx->crop_rect.left;
		s->r.top = ctx->crop_rect.top;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * V4L2 controls
 */
अटल पूर्णांक s5p_jpeg_s_selection(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_selection *s)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = fh_to_ctx(file->निजी_data);
	काष्ठा v4l2_rect *rect = &s->r;
	पूर्णांक ret = -EINVAL;

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (s->target == V4L2_SEL_TGT_COMPOSE) अणु
		अगर (ctx->mode != S5P_JPEG_DECODE)
			वापस -EINVAL;
		अगर (ctx->jpeg->variant->hw3250_compat)
			ret = exynos3250_jpeg_try_करोwnscale(ctx, rect);
	पूर्ण अन्यथा अगर (s->target == V4L2_SEL_TGT_CROP) अणु
		अगर (ctx->mode != S5P_JPEG_ENCODE)
			वापस -EINVAL;
		अगर (ctx->jpeg->variant->hw3250_compat)
			ret = exynos3250_jpeg_try_crop(ctx, rect);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक s5p_jpeg_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	अचिन्हित दीर्घ flags;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		spin_lock_irqsave(&jpeg->slock, flags);
		ctrl->val = s5p_jpeg_to_user_subsampling(ctx);
		spin_unlock_irqrestore(&jpeg->slock, flags);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_adjust_subs_ctrl(काष्ठा s5p_jpeg_ctx *ctx, पूर्णांक *ctrl_val)
अणु
	चयन (ctx->jpeg->variant->version) अणु
	हाल SJPEG_S5P:
		वापस 0;
	हाल SJPEG_EXYNOS3250:
	हाल SJPEG_EXYNOS5420:
		/*
		 * The exynos3250/compatible device can produce JPEG image only
		 * of 4:4:4 subsampling when given RGB32 source image.
		 */
		अगर (ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB32)
			*ctrl_val = 0;
		अवरोध;
	हाल SJPEG_EXYNOS4:
		/*
		 * The exynos4x12 device requires input raw image fourcc
		 * to be V4L2_PIX_FMT_GREY अगर gray jpeg क्रमmat
		 * is to be set.
		 */
		अगर (ctx->out_q.fmt->fourcc != V4L2_PIX_FMT_GREY &&
		    *ctrl_val == V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	/*
	 * The exynos4x12 and exynos3250/compatible devices require resulting
	 * jpeg subsampling not to be lower than the input raw image
	 * subsampling.
	 */
	अगर (ctx->out_q.fmt->subsampling > *ctrl_val)
		*ctrl_val = ctx->out_q.fmt->subsampling;

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	अगर (ctrl->id == V4L2_CID_JPEG_CHROMA_SUBSAMPLING)
		ret = s5p_jpeg_adjust_subs_ctrl(ctx, &ctrl->val);

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_jpeg_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ctx->compr_quality = ctrl->val;
		अवरोध;
	हाल V4L2_CID_JPEG_RESTART_INTERVAL:
		ctx->restart_पूर्णांकerval = ctrl->val;
		अवरोध;
	हाल V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		ctx->subsampling = ctrl->val;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s5p_jpeg_ctrl_ops = अणु
	.g_अस्थिर_ctrl	= s5p_jpeg_g_अस्थिर_ctrl,
	.try_ctrl		= s5p_jpeg_try_ctrl,
	.s_ctrl			= s5p_jpeg_s_ctrl,
पूर्ण;

अटल पूर्णांक s5p_jpeg_controls_create(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	अचिन्हित पूर्णांक mask = ~0x27; /* 444, 422, 420, GRAY */
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 3);

	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		v4l2_ctrl_new_std(&ctx->ctrl_handler, &s5p_jpeg_ctrl_ops,
				  V4L2_CID_JPEG_COMPRESSION_QUALITY,
				  0, 3, 1, S5P_JPEG_COMPR_QUAL_WORST);

		v4l2_ctrl_new_std(&ctx->ctrl_handler, &s5p_jpeg_ctrl_ops,
				  V4L2_CID_JPEG_RESTART_INTERVAL,
				  0, 0xffff, 1, 0);
		अगर (ctx->jpeg->variant->version == SJPEG_S5P)
			mask = ~0x06; /* 422, 420 */
	पूर्ण

	ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrl_handler, &s5p_jpeg_ctrl_ops,
				      V4L2_CID_JPEG_CHROMA_SUBSAMPLING,
				      V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY, mask,
				      V4L2_JPEG_CHROMA_SUBSAMPLING_422);

	अगर (ctx->ctrl_handler.error) अणु
		ret = ctx->ctrl_handler.error;
		जाओ error_मुक्त;
	पूर्ण

	अगर (ctx->mode == S5P_JPEG_DECODE)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE |
			V4L2_CTRL_FLAG_READ_ONLY;

	ret = v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	अगर (ret < 0)
		जाओ error_मुक्त;

	वापस ret;

error_मुक्त:
	v4l2_ctrl_handler_मुक्त(&ctx->ctrl_handler);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops s5p_jpeg_ioctl_ops = अणु
	.vidioc_querycap		= s5p_jpeg_querycap,

	.vidioc_क्रमागत_fmt_vid_cap	= s5p_jpeg_क्रमागत_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_out	= s5p_jpeg_क्रमागत_fmt_vid_out,

	.vidioc_g_fmt_vid_cap		= s5p_jpeg_g_fmt,
	.vidioc_g_fmt_vid_out		= s5p_jpeg_g_fmt,

	.vidioc_try_fmt_vid_cap		= s5p_jpeg_try_fmt_vid_cap,
	.vidioc_try_fmt_vid_out		= s5p_jpeg_try_fmt_vid_out,

	.vidioc_s_fmt_vid_cap		= s5p_jpeg_s_fmt_vid_cap,
	.vidioc_s_fmt_vid_out		= s5p_jpeg_s_fmt_vid_out,

	.vidioc_reqbufs			= v4l2_m2m_ioctl_reqbufs,
	.vidioc_querybuf		= v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf			= v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf			= v4l2_m2m_ioctl_dqbuf,

	.vidioc_streamon		= v4l2_m2m_ioctl_streamon,
	.vidioc_streamoff		= v4l2_m2m_ioctl_streamoff,

	.vidioc_g_selection		= s5p_jpeg_g_selection,
	.vidioc_s_selection		= s5p_jpeg_s_selection,

	.vidioc_subscribe_event		= s5p_jpeg_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/*
 * ============================================================================
 * mem2mem callbacks
 * ============================================================================
 */

अटल व्योम s5p_jpeg_device_run(व्योम *priv)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = priv;
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित दीर्घ src_addr, dst_addr, flags;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	src_addr = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);

	s5p_jpeg_reset(jpeg->regs);
	s5p_jpeg_घातeron(jpeg->regs);
	s5p_jpeg_proc_mode(jpeg->regs, ctx->mode);
	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		अगर (ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB565)
			s5p_jpeg_input_raw_mode(jpeg->regs,
							S5P_JPEG_RAW_IN_565);
		अन्यथा
			s5p_jpeg_input_raw_mode(jpeg->regs,
							S5P_JPEG_RAW_IN_422);
		s5p_jpeg_subsampling_mode(jpeg->regs, ctx->subsampling);
		s5p_jpeg_dri(jpeg->regs, ctx->restart_पूर्णांकerval);
		s5p_jpeg_x(jpeg->regs, ctx->out_q.w);
		s5p_jpeg_y(jpeg->regs, ctx->out_q.h);
		s5p_jpeg_imgadr(jpeg->regs, src_addr);
		s5p_jpeg_jpgadr(jpeg->regs, dst_addr);

		/* ultimately comes from sizeimage from userspace */
		s5p_jpeg_enc_stream_पूर्णांक(jpeg->regs, ctx->cap_q.size);

		/* JPEG RGB to YCbCr conversion matrix */
		s5p_jpeg_coef(jpeg->regs, 1, 1, S5P_JPEG_COEF11);
		s5p_jpeg_coef(jpeg->regs, 1, 2, S5P_JPEG_COEF12);
		s5p_jpeg_coef(jpeg->regs, 1, 3, S5P_JPEG_COEF13);
		s5p_jpeg_coef(jpeg->regs, 2, 1, S5P_JPEG_COEF21);
		s5p_jpeg_coef(jpeg->regs, 2, 2, S5P_JPEG_COEF22);
		s5p_jpeg_coef(jpeg->regs, 2, 3, S5P_JPEG_COEF23);
		s5p_jpeg_coef(jpeg->regs, 3, 1, S5P_JPEG_COEF31);
		s5p_jpeg_coef(jpeg->regs, 3, 2, S5P_JPEG_COEF32);
		s5p_jpeg_coef(jpeg->regs, 3, 3, S5P_JPEG_COEF33);

		/*
		 * JPEG IP allows storing 4 quantization tables
		 * We fill table 0 क्रम luma and table 1 क्रम chroma
		 */
		s5p_jpeg_set_qtbl_lum(jpeg->regs, ctx->compr_quality);
		s5p_jpeg_set_qtbl_chr(jpeg->regs, ctx->compr_quality);
		/* use table 0 क्रम Y */
		s5p_jpeg_qtbl(jpeg->regs, 1, 0);
		/* use table 1 क्रम Cb and Cr*/
		s5p_jpeg_qtbl(jpeg->regs, 2, 1);
		s5p_jpeg_qtbl(jpeg->regs, 3, 1);

		/* Y, Cb, Cr use Huffman table 0 */
		s5p_jpeg_htbl_ac(jpeg->regs, 1);
		s5p_jpeg_htbl_dc(jpeg->regs, 1);
		s5p_jpeg_htbl_ac(jpeg->regs, 2);
		s5p_jpeg_htbl_dc(jpeg->regs, 2);
		s5p_jpeg_htbl_ac(jpeg->regs, 3);
		s5p_jpeg_htbl_dc(jpeg->regs, 3);
	पूर्ण अन्यथा अणु /* S5P_JPEG_DECODE */
		s5p_jpeg_rst_पूर्णांक_enable(jpeg->regs, true);
		s5p_jpeg_data_num_पूर्णांक_enable(jpeg->regs, true);
		s5p_jpeg_final_mcu_num_पूर्णांक_enable(jpeg->regs, true);
		अगर (ctx->cap_q.fmt->fourcc == V4L2_PIX_FMT_YUYV)
			s5p_jpeg_outक्रमm_raw(jpeg->regs, S5P_JPEG_RAW_OUT_422);
		अन्यथा
			s5p_jpeg_outक्रमm_raw(jpeg->regs, S5P_JPEG_RAW_OUT_420);
		s5p_jpeg_jpgadr(jpeg->regs, src_addr);
		s5p_jpeg_imgadr(jpeg->regs, dst_addr);
	पूर्ण

	s5p_jpeg_start(jpeg->regs);

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
पूर्ण

अटल व्योम exynos4_jpeg_set_img_addr(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा s5p_jpeg_fmt *fmt;
	काष्ठा vb2_v4l2_buffer *vb;
	काष्ठा s5p_jpeg_addr jpeg_addr = अणुपूर्ण;
	u32 pix_size, padding_bytes = 0;

	jpeg_addr.cb = 0;
	jpeg_addr.cr = 0;

	pix_size = ctx->cap_q.w * ctx->cap_q.h;

	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		fmt = ctx->out_q.fmt;
		अगर (ctx->out_q.w % 2 && fmt->h_align > 0)
			padding_bytes = ctx->out_q.h;
	पूर्ण अन्यथा अणु
		fmt = ctx->cap_q.fmt;
		vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	पूर्ण

	jpeg_addr.y = vb2_dma_contig_plane_dma_addr(&vb->vb2_buf, 0);

	अगर (fmt->colplanes == 2) अणु
		jpeg_addr.cb = jpeg_addr.y + pix_size - padding_bytes;
	पूर्ण अन्यथा अगर (fmt->colplanes == 3) अणु
		jpeg_addr.cb = jpeg_addr.y + pix_size;
		अगर (fmt->fourcc == V4L2_PIX_FMT_YUV420)
			jpeg_addr.cr = jpeg_addr.cb + pix_size / 4;
		अन्यथा
			jpeg_addr.cr = jpeg_addr.cb + pix_size / 2;
	पूर्ण

	exynos4_jpeg_set_frame_buf_address(jpeg->regs, &jpeg_addr);
पूर्ण

अटल व्योम exynos4_jpeg_set_jpeg_addr(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *vb;
	अचिन्हित पूर्णांक jpeg_addr = 0;

	अगर (ctx->mode == S5P_JPEG_ENCODE)
		vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	अन्यथा
		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);

	jpeg_addr = vb2_dma_contig_plane_dma_addr(&vb->vb2_buf, 0);
	अगर (jpeg->variant->version == SJPEG_EXYNOS5433 &&
	    ctx->mode == S5P_JPEG_DECODE)
		jpeg_addr += ctx->out_q.sos;
	exynos4_jpeg_set_stream_buf_address(jpeg->regs, jpeg_addr);
पूर्ण

अटल अंतरभूत व्योम exynos4_jpeg_set_img_fmt(व्योम __iomem *base,
					    अचिन्हित पूर्णांक img_fmt)
अणु
	__exynos4_jpeg_set_img_fmt(base, img_fmt, SJPEG_EXYNOS4);
पूर्ण

अटल अंतरभूत व्योम exynos5433_jpeg_set_img_fmt(व्योम __iomem *base,
					       अचिन्हित पूर्णांक img_fmt)
अणु
	__exynos4_jpeg_set_img_fmt(base, img_fmt, SJPEG_EXYNOS5433);
पूर्ण

अटल अंतरभूत व्योम exynos4_jpeg_set_enc_out_fmt(व्योम __iomem *base,
						अचिन्हित पूर्णांक out_fmt)
अणु
	__exynos4_jpeg_set_enc_out_fmt(base, out_fmt, SJPEG_EXYNOS4);
पूर्ण

अटल अंतरभूत व्योम exynos5433_jpeg_set_enc_out_fmt(व्योम __iomem *base,
						   अचिन्हित पूर्णांक out_fmt)
अणु
	__exynos4_jpeg_set_enc_out_fmt(base, out_fmt, SJPEG_EXYNOS5433);
पूर्ण

अटल व्योम exynos4_jpeg_device_run(व्योम *priv)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = priv;
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	अचिन्हित पूर्णांक bitstream_size;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&jpeg->slock, flags);

	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		exynos4_jpeg_sw_reset(jpeg->regs);
		exynos4_jpeg_set_पूर्णांकerrupt(jpeg->regs, jpeg->variant->version);
		exynos4_jpeg_set_huf_table_enable(jpeg->regs, 1);

		exynos4_jpeg_set_huff_tbl(jpeg->regs);

		/*
		 * JPEG IP allows storing 4 quantization tables
		 * We fill table 0 क्रम luma and table 1 क्रम chroma
		 */
		exynos4_jpeg_set_qtbl_lum(jpeg->regs, ctx->compr_quality);
		exynos4_jpeg_set_qtbl_chr(jpeg->regs, ctx->compr_quality);

		exynos4_jpeg_set_encode_tbl_select(jpeg->regs,
							ctx->compr_quality);
		exynos4_jpeg_set_stream_size(jpeg->regs, ctx->cap_q.w,
							ctx->cap_q.h);

		अगर (ctx->jpeg->variant->version == SJPEG_EXYNOS4) अणु
			exynos4_jpeg_set_enc_out_fmt(jpeg->regs,
						     ctx->subsampling);
			exynos4_jpeg_set_img_fmt(jpeg->regs,
						 ctx->out_q.fmt->fourcc);
		पूर्ण अन्यथा अणु
			exynos5433_jpeg_set_enc_out_fmt(jpeg->regs,
							ctx->subsampling);
			exynos5433_jpeg_set_img_fmt(jpeg->regs,
						    ctx->out_q.fmt->fourcc);
		पूर्ण
		exynos4_jpeg_set_img_addr(ctx);
		exynos4_jpeg_set_jpeg_addr(ctx);
		exynos4_jpeg_set_encode_hoff_cnt(jpeg->regs,
							ctx->out_q.fmt->fourcc);
	पूर्ण अन्यथा अणु
		exynos4_jpeg_sw_reset(jpeg->regs);
		exynos4_jpeg_set_पूर्णांकerrupt(jpeg->regs,
					   jpeg->variant->version);
		exynos4_jpeg_set_img_addr(ctx);
		exynos4_jpeg_set_jpeg_addr(ctx);

		अगर (jpeg->variant->version == SJPEG_EXYNOS5433) अणु
			exynos4_jpeg_parse_huff_tbl(ctx);
			exynos4_jpeg_parse_decode_h_tbl(ctx);

			exynos4_jpeg_parse_q_tbl(ctx);
			exynos4_jpeg_parse_decode_q_tbl(ctx);

			exynos4_jpeg_set_huf_table_enable(jpeg->regs, 1);

			exynos4_jpeg_set_stream_size(jpeg->regs, ctx->cap_q.w,
					ctx->cap_q.h);
			exynos5433_jpeg_set_enc_out_fmt(jpeg->regs,
							ctx->subsampling);
			exynos5433_jpeg_set_img_fmt(jpeg->regs,
						    ctx->cap_q.fmt->fourcc);
			bitstream_size = DIV_ROUND_UP(ctx->out_q.size, 16);
		पूर्ण अन्यथा अणु
			exynos4_jpeg_set_img_fmt(jpeg->regs,
						 ctx->cap_q.fmt->fourcc);
			bitstream_size = DIV_ROUND_UP(ctx->out_q.size, 32);
		पूर्ण

		exynos4_jpeg_set_dec_bitstream_size(jpeg->regs, bitstream_size);
	पूर्ण

	exynos4_jpeg_set_sys_पूर्णांक_enable(jpeg->regs, 1);
	exynos4_jpeg_set_enc_dec_mode(jpeg->regs, ctx->mode);

	spin_unlock_irqrestore(&jpeg->slock, flags);
पूर्ण

अटल व्योम exynos3250_jpeg_set_img_addr(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा s5p_jpeg_fmt *fmt;
	काष्ठा vb2_v4l2_buffer *vb;
	काष्ठा s5p_jpeg_addr jpeg_addr = अणुपूर्ण;
	u32 pix_size;

	pix_size = ctx->cap_q.w * ctx->cap_q.h;

	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
		fmt = ctx->out_q.fmt;
	पूर्ण अन्यथा अणु
		vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
		fmt = ctx->cap_q.fmt;
	पूर्ण

	jpeg_addr.y = vb2_dma_contig_plane_dma_addr(&vb->vb2_buf, 0);

	अगर (fmt->colplanes == 2) अणु
		jpeg_addr.cb = jpeg_addr.y + pix_size;
	पूर्ण अन्यथा अगर (fmt->colplanes == 3) अणु
		jpeg_addr.cb = jpeg_addr.y + pix_size;
		अगर (fmt->fourcc == V4L2_PIX_FMT_YUV420)
			jpeg_addr.cr = jpeg_addr.cb + pix_size / 4;
		अन्यथा
			jpeg_addr.cr = jpeg_addr.cb + pix_size / 2;
	पूर्ण

	exynos3250_jpeg_imgadr(jpeg->regs, &jpeg_addr);
पूर्ण

अटल व्योम exynos3250_jpeg_set_jpeg_addr(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	काष्ठा vb2_v4l2_buffer *vb;
	अचिन्हित पूर्णांक jpeg_addr = 0;

	अगर (ctx->mode == S5P_JPEG_ENCODE)
		vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	अन्यथा
		vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);

	jpeg_addr = vb2_dma_contig_plane_dma_addr(&vb->vb2_buf, 0);
	exynos3250_jpeg_jpgadr(jpeg->regs, jpeg_addr);
पूर्ण

अटल व्योम exynos3250_jpeg_device_run(व्योम *priv)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = priv;
	काष्ठा s5p_jpeg *jpeg = ctx->jpeg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	exynos3250_jpeg_reset(jpeg->regs);
	exynos3250_jpeg_set_dma_num(jpeg->regs);
	exynos3250_jpeg_घातeron(jpeg->regs);
	exynos3250_jpeg_clk_set(jpeg->regs);
	exynos3250_jpeg_proc_mode(jpeg->regs, ctx->mode);

	अगर (ctx->mode == S5P_JPEG_ENCODE) अणु
		exynos3250_jpeg_input_raw_fmt(jpeg->regs,
					      ctx->out_q.fmt->fourcc);
		exynos3250_jpeg_dri(jpeg->regs, ctx->restart_पूर्णांकerval);

		/*
		 * JPEG IP allows storing 4 quantization tables
		 * We fill table 0 क्रम luma and table 1 क्रम chroma
		 */
		s5p_jpeg_set_qtbl_lum(jpeg->regs, ctx->compr_quality);
		s5p_jpeg_set_qtbl_chr(jpeg->regs, ctx->compr_quality);
		/* use table 0 क्रम Y */
		exynos3250_jpeg_qtbl(jpeg->regs, 1, 0);
		/* use table 1 क्रम Cb and Cr*/
		exynos3250_jpeg_qtbl(jpeg->regs, 2, 1);
		exynos3250_jpeg_qtbl(jpeg->regs, 3, 1);

		/*
		 * Some SoCs require setting Huffman tables beक्रमe each run
		 */
		अगर (jpeg->variant->htbl_reinit) अणु
			s5p_jpeg_set_hdctbl(jpeg->regs);
			s5p_jpeg_set_hdctblg(jpeg->regs);
			s5p_jpeg_set_hactbl(jpeg->regs);
			s5p_jpeg_set_hactblg(jpeg->regs);
		पूर्ण

		/* Y, Cb, Cr use Huffman table 0 */
		exynos3250_jpeg_htbl_ac(jpeg->regs, 1);
		exynos3250_jpeg_htbl_dc(jpeg->regs, 1);
		exynos3250_jpeg_htbl_ac(jpeg->regs, 2);
		exynos3250_jpeg_htbl_dc(jpeg->regs, 2);
		exynos3250_jpeg_htbl_ac(jpeg->regs, 3);
		exynos3250_jpeg_htbl_dc(jpeg->regs, 3);

		exynos3250_jpeg_set_x(jpeg->regs, ctx->crop_rect.width);
		exynos3250_jpeg_set_y(jpeg->regs, ctx->crop_rect.height);
		exynos3250_jpeg_stride(jpeg->regs, ctx->out_q.fmt->fourcc,
								ctx->out_q.w);
		exynos3250_jpeg_offset(jpeg->regs, ctx->crop_rect.left,
							ctx->crop_rect.top);
		exynos3250_jpeg_set_img_addr(ctx);
		exynos3250_jpeg_set_jpeg_addr(ctx);
		exynos3250_jpeg_subsampling_mode(jpeg->regs, ctx->subsampling);

		/* ultimately comes from sizeimage from userspace */
		exynos3250_jpeg_enc_stream_bound(jpeg->regs, ctx->cap_q.size);

		अगर (ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB565 ||
		    ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB565X ||
		    ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB32)
			exynos3250_jpeg_set_y16(jpeg->regs, true);
	पूर्ण अन्यथा अणु
		exynos3250_jpeg_set_img_addr(ctx);
		exynos3250_jpeg_set_jpeg_addr(ctx);
		exynos3250_jpeg_stride(jpeg->regs, ctx->cap_q.fmt->fourcc,
								ctx->cap_q.w);
		exynos3250_jpeg_offset(jpeg->regs, 0, 0);
		exynos3250_jpeg_dec_scaling_ratio(jpeg->regs,
							ctx->scale_factor);
		exynos3250_jpeg_dec_stream_size(jpeg->regs, ctx->out_q.size);
		exynos3250_jpeg_output_raw_fmt(jpeg->regs,
						ctx->cap_q.fmt->fourcc);
	पूर्ण

	exynos3250_jpeg_पूर्णांकerrupts_enable(jpeg->regs);

	/* JPEG RGB to YCbCr conversion matrix */
	exynos3250_jpeg_coef(jpeg->regs, ctx->mode);

	exynos3250_jpeg_set_समयr(jpeg->regs, EXYNOS3250_IRQ_TIMEOUT);
	jpeg->irq_status = 0;
	exynos3250_jpeg_start(jpeg->regs);

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
पूर्ण

अटल पूर्णांक s5p_jpeg_job_पढ़ोy(व्योम *priv)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = priv;

	अगर (ctx->mode == S5P_JPEG_DECODE) अणु
		/*
		 * We have only one input buffer and one output buffer. If there
		 * is a resolution change event, no need to जारी decoding.
		 */
		अगर (ctx->state == JPEGCTX_RESOLUTION_CHANGE)
			वापस 0;

		वापस ctx->hdr_parsed;
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा v4l2_m2m_ops s5p_jpeg_m2m_ops = अणु
	.device_run	= s5p_jpeg_device_run,
	.job_पढ़ोy	= s5p_jpeg_job_पढ़ोy,
पूर्ण;

अटल काष्ठा v4l2_m2m_ops exynos3250_jpeg_m2m_ops = अणु
	.device_run	= exynos3250_jpeg_device_run,
	.job_पढ़ोy	= s5p_jpeg_job_पढ़ोy,
पूर्ण;

अटल काष्ठा v4l2_m2m_ops exynos4_jpeg_m2m_ops = अणु
	.device_run	= exynos4_jpeg_device_run,
	.job_पढ़ोy	= s5p_jpeg_job_पढ़ोy,
पूर्ण;

/*
 * ============================================================================
 * Queue operations
 * ============================================================================
 */

अटल पूर्णांक s5p_jpeg_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा s5p_jpeg_ctx *ctx = vb2_get_drv_priv(vq);
	काष्ठा s5p_jpeg_q_data *q_data = शून्य;
	अचिन्हित पूर्णांक size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);
	BUG_ON(q_data == शून्य);

	size = q_data->size;

	/*
	 * header is parsed during decoding and parsed inक्रमmation stored
	 * in the context so we करो not allow another buffer to overग_लिखो it
	 */
	अगर (ctx->mode == S5P_JPEG_DECODE)
		count = 1;

	*nbuffers = count;
	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा s5p_jpeg_q_data *q_data = शून्य;

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	BUG_ON(q_data == शून्य);

	अगर (vb2_plane_size(vb, 0) < q_data->size) अणु
		pr_err("%s data will not fit into plane (%lu < %lu)\n",
				__func__, vb2_plane_size(vb, 0),
				(दीर्घ)q_data->size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, q_data->size);

	वापस 0;
पूर्ण

अटल व्योम s5p_jpeg_set_capture_queue_data(काष्ठा s5p_jpeg_ctx *ctx)
अणु
	काष्ठा s5p_jpeg_q_data *q_data = &ctx->cap_q;

	q_data->w = ctx->out_q.w;
	q_data->h = ctx->out_q.h;

	/*
	 * This call to jpeg_bound_align_image() takes care of width and
	 * height values alignment when user space calls the QBUF of
	 * OUTPUT buffer after the S_FMT of CAPTURE buffer.
	 * Please note that on Exynos4x12 SoCs, resigning from executing
	 * S_FMT on capture buffer क्रम each JPEG image can result in a
	 * hardware hangup अगर subsampling is lower than the one of input
	 * JPEG.
	 */
	jpeg_bound_align_image(ctx, &q_data->w, S5P_JPEG_MIN_WIDTH,
			       S5P_JPEG_MAX_WIDTH, q_data->fmt->h_align,
			       &q_data->h, S5P_JPEG_MIN_HEIGHT,
			       S5P_JPEG_MAX_HEIGHT, q_data->fmt->v_align);

	q_data->size = q_data->w * q_data->h * q_data->fmt->depth >> 3;
पूर्ण

अटल व्योम s5p_jpeg_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा s5p_jpeg_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	अगर (ctx->mode == S5P_JPEG_DECODE &&
	    vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) अणु
		अटल स्थिर काष्ठा v4l2_event ev_src_ch = अणु
			.type = V4L2_EVENT_SOURCE_CHANGE,
			.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
		पूर्ण;
		काष्ठा vb2_queue *dst_vq;
		u32 ori_w;
		u32 ori_h;

		dst_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					 V4L2_BUF_TYPE_VIDEO_CAPTURE);
		ori_w = ctx->out_q.w;
		ori_h = ctx->out_q.h;

		ctx->hdr_parsed = s5p_jpeg_parse_hdr(&ctx->out_q,
		     (अचिन्हित दीर्घ)vb2_plane_vaddr(vb, 0),
		     min((अचिन्हित दीर्घ)ctx->out_q.size,
			 vb2_get_plane_payload(vb, 0)), ctx);
		अगर (!ctx->hdr_parsed) अणु
			vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
			वापस;
		पूर्ण

		/*
		 * If there is a resolution change event, only update capture
		 * queue when it is not streaming. Otherwise, update it in
		 * STREAMOFF. See s5p_jpeg_stop_streaming क्रम detail.
		 */
		अगर (ctx->out_q.w != ori_w || ctx->out_q.h != ori_h) अणु
			v4l2_event_queue_fh(&ctx->fh, &ev_src_ch);
			अगर (vb2_is_streaming(dst_vq))
				ctx->state = JPEGCTX_RESOLUTION_CHANGE;
			अन्यथा
				s5p_jpeg_set_capture_queue_data(ctx);
		पूर्ण
	पूर्ण

	v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक s5p_jpeg_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = vb2_get_drv_priv(q);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(ctx->jpeg->dev);

	वापस ret > 0 ? 0 : ret;
पूर्ण

अटल व्योम s5p_jpeg_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = vb2_get_drv_priv(q);

	/*
	 * STREAMOFF is an acknowledgment क्रम resolution change event.
	 * Beक्रमe STREAMOFF, we still have to वापस the old resolution and
	 * subsampling. Update capture queue when the stream is off.
	 */
	अगर (ctx->state == JPEGCTX_RESOLUTION_CHANGE &&
	    q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		s5p_jpeg_set_capture_queue_data(ctx);
		ctx->state = JPEGCTX_RUNNING;
	पूर्ण

	pm_runसमय_put(ctx->jpeg->dev);
पूर्ण

अटल स्थिर काष्ठा vb2_ops s5p_jpeg_qops = अणु
	.queue_setup		= s5p_jpeg_queue_setup,
	.buf_prepare		= s5p_jpeg_buf_prepare,
	.buf_queue		= s5p_jpeg_buf_queue,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.start_streaming	= s5p_jpeg_start_streaming,
	.stop_streaming		= s5p_jpeg_stop_streaming,
पूर्ण;

अटल पूर्णांक queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq)
अणु
	काष्ठा s5p_jpeg_ctx *ctx = priv;
	पूर्णांक ret;

	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_MMAP | VB2_USERPTR;
	src_vq->drv_priv = ctx;
	src_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	src_vq->ops = &s5p_jpeg_qops;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->lock = &ctx->jpeg->lock;
	src_vq->dev = ctx->jpeg->dev;

	ret = vb2_queue_init(src_vq);
	अगर (ret)
		वापस ret;

	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_MMAP | VB2_USERPTR;
	dst_vq->drv_priv = ctx;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा v4l2_m2m_buffer);
	dst_vq->ops = &s5p_jpeg_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->lock = &ctx->jpeg->lock;
	dst_vq->dev = ctx->jpeg->dev;

	वापस vb2_queue_init(dst_vq);
पूर्ण

/*
 * ============================================================================
 * ISR
 * ============================================================================
 */

अटल irqवापस_t s5p_jpeg_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s5p_jpeg *jpeg = dev_id;
	काष्ठा s5p_jpeg_ctx *curr_ctx;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित दीर्घ payload_size = 0;
	क्रमागत vb2_buffer_state state = VB2_BUF_STATE_DONE;
	bool enc_jpeg_too_large = false;
	bool समयr_elapsed = false;
	bool op_completed = false;

	spin_lock(&jpeg->slock);

	curr_ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);

	src_buf = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	अगर (curr_ctx->mode == S5P_JPEG_ENCODE)
		enc_jpeg_too_large = s5p_jpeg_enc_stream_stat(jpeg->regs);
	समयr_elapsed = s5p_jpeg_समयr_stat(jpeg->regs);
	op_completed = s5p_jpeg_result_stat_ok(jpeg->regs);
	अगर (curr_ctx->mode == S5P_JPEG_DECODE)
		op_completed = op_completed &&
					s5p_jpeg_stream_stat_ok(jpeg->regs);

	अगर (enc_jpeg_too_large) अणु
		state = VB2_BUF_STATE_ERROR;
		s5p_jpeg_clear_enc_stream_stat(jpeg->regs);
	पूर्ण अन्यथा अगर (समयr_elapsed) अणु
		state = VB2_BUF_STATE_ERROR;
		s5p_jpeg_clear_समयr_stat(jpeg->regs);
	पूर्ण अन्यथा अगर (!op_completed) अणु
		state = VB2_BUF_STATE_ERROR;
	पूर्ण अन्यथा अणु
		payload_size = s5p_jpeg_compressed_size(jpeg->regs);
	पूर्ण

	dst_buf->समयcode = src_buf->समयcode;
	dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;
	dst_buf->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	dst_buf->flags |=
		src_buf->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	v4l2_m2m_buf_करोne(src_buf, state);
	अगर (curr_ctx->mode == S5P_JPEG_ENCODE)
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, payload_size);
	v4l2_m2m_buf_करोne(dst_buf, state);

	curr_ctx->subsampling = s5p_jpeg_get_subsampling_mode(jpeg->regs);
	spin_unlock(&jpeg->slock);

	s5p_jpeg_clear_पूर्णांक(jpeg->regs);

	v4l2_m2m_job_finish(jpeg->m2m_dev, curr_ctx->fh.m2m_ctx);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t exynos4_jpeg_irq(पूर्णांक irq, व्योम *priv)
अणु
	अचिन्हित पूर्णांक पूर्णांक_status;
	काष्ठा vb2_v4l2_buffer *src_vb, *dst_vb;
	काष्ठा s5p_jpeg *jpeg = priv;
	काष्ठा s5p_jpeg_ctx *curr_ctx;
	अचिन्हित दीर्घ payload_size = 0;

	spin_lock(&jpeg->slock);

	exynos4_jpeg_set_sys_पूर्णांक_enable(jpeg->regs, 0);

	curr_ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);

	src_vb = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	पूर्णांक_status = exynos4_jpeg_get_पूर्णांक_status(jpeg->regs);

	अगर (पूर्णांक_status) अणु
		चयन (पूर्णांक_status & 0x1f) अणु
		हाल 0x1:
			jpeg->irq_ret = ERR_PROT;
			अवरोध;
		हाल 0x2:
			jpeg->irq_ret = OK_ENC_OR_DEC;
			अवरोध;
		हाल 0x4:
			jpeg->irq_ret = ERR_DEC_INVALID_FORMAT;
			अवरोध;
		हाल 0x8:
			jpeg->irq_ret = ERR_MULTI_SCAN;
			अवरोध;
		हाल 0x10:
			jpeg->irq_ret = ERR_FRAME;
			अवरोध;
		शेष:
			jpeg->irq_ret = ERR_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		jpeg->irq_ret = ERR_UNKNOWN;
	पूर्ण

	अगर (jpeg->irq_ret == OK_ENC_OR_DEC) अणु
		अगर (curr_ctx->mode == S5P_JPEG_ENCODE) अणु
			payload_size = exynos4_jpeg_get_stream_size(jpeg->regs);
			vb2_set_plane_payload(&dst_vb->vb2_buf,
					0, payload_size);
		पूर्ण
		v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_DONE);
	पूर्ण अन्यथा अणु
		v4l2_m2m_buf_करोne(src_vb, VB2_BUF_STATE_ERROR);
		v4l2_m2m_buf_करोne(dst_vb, VB2_BUF_STATE_ERROR);
	पूर्ण

	अगर (jpeg->variant->version == SJPEG_EXYNOS4)
		curr_ctx->subsampling = exynos4_jpeg_get_frame_fmt(jpeg->regs);

	exynos4_jpeg_set_enc_dec_mode(jpeg->regs, S5P_JPEG_DISABLE);

	spin_unlock(&jpeg->slock);

	v4l2_m2m_job_finish(jpeg->m2m_dev, curr_ctx->fh.m2m_ctx);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t exynos3250_jpeg_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा s5p_jpeg *jpeg = dev_id;
	काष्ठा s5p_jpeg_ctx *curr_ctx;
	काष्ठा vb2_v4l2_buffer *src_buf, *dst_buf;
	अचिन्हित दीर्घ payload_size = 0;
	क्रमागत vb2_buffer_state state = VB2_BUF_STATE_DONE;
	bool पूर्णांकerrupt_समयout = false;
	bool stream_error = false;
	u32 irq_status;

	spin_lock(&jpeg->slock);

	irq_status = exynos3250_jpeg_get_समयr_status(jpeg->regs);
	अगर (irq_status & EXYNOS3250_TIMER_INT_STAT) अणु
		exynos3250_jpeg_clear_समयr_status(jpeg->regs);
		पूर्णांकerrupt_समयout = true;
		dev_err(jpeg->dev, "Interrupt timeout occurred.\n");
	पूर्ण

	irq_status = exynos3250_jpeg_get_पूर्णांक_status(jpeg->regs);
	exynos3250_jpeg_clear_पूर्णांक_status(jpeg->regs, irq_status);

	jpeg->irq_status |= irq_status;

	अगर (jpeg->variant->version == SJPEG_EXYNOS5420 &&
	    irq_status & EXYNOS3250_STREAM_STAT) अणु
		stream_error = true;
		dev_err(jpeg->dev, "Syntax error or unrecoverable error occurred.\n");
	पूर्ण

	curr_ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);

	अगर (!curr_ctx)
		जाओ निकास_unlock;

	अगर ((irq_status & EXYNOS3250_HEADER_STAT) &&
	    (curr_ctx->mode == S5P_JPEG_DECODE)) अणु
		exynos3250_jpeg_rstart(jpeg->regs);
		जाओ निकास_unlock;
	पूर्ण

	अगर (jpeg->irq_status & (EXYNOS3250_JPEG_DONE |
				EXYNOS3250_WDMA_DONE |
				EXYNOS3250_RDMA_DONE |
				EXYNOS3250_RESULT_STAT))
		payload_size = exynos3250_jpeg_compressed_size(jpeg->regs);
	अन्यथा अगर (पूर्णांकerrupt_समयout || stream_error)
		state = VB2_BUF_STATE_ERROR;
	अन्यथा
		जाओ निकास_unlock;

	src_buf = v4l2_m2m_src_buf_हटाओ(curr_ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_हटाओ(curr_ctx->fh.m2m_ctx);

	dst_buf->समयcode = src_buf->समयcode;
	dst_buf->vb2_buf.बारtamp = src_buf->vb2_buf.बारtamp;

	v4l2_m2m_buf_करोne(src_buf, state);
	अगर (curr_ctx->mode == S5P_JPEG_ENCODE)
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, payload_size);
	v4l2_m2m_buf_करोne(dst_buf, state);

	curr_ctx->subsampling =
			exynos3250_jpeg_get_subsampling_mode(jpeg->regs);

	spin_unlock(&jpeg->slock);

	v4l2_m2m_job_finish(jpeg->m2m_dev, curr_ctx->fh.m2m_ctx);
	वापस IRQ_HANDLED;

निकास_unlock:
	spin_unlock(&jpeg->slock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम *jpeg_get_drv_data(काष्ठा device *dev);

/*
 * ============================================================================
 * Driver basic infraकाष्ठाure
 * ============================================================================
 */

अटल पूर्णांक s5p_jpeg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s5p_jpeg *jpeg;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	/* JPEG IP असलtraction काष्ठा */
	jpeg = devm_kzalloc(&pdev->dev, माप(काष्ठा s5p_jpeg), GFP_KERNEL);
	अगर (!jpeg)
		वापस -ENOMEM;

	jpeg->variant = jpeg_get_drv_data(&pdev->dev);
	अगर (!jpeg->variant)
		वापस -ENODEV;

	mutex_init(&jpeg->lock);
	spin_lock_init(&jpeg->slock);
	jpeg->dev = &pdev->dev;

	/* memory-mapped रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	jpeg->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(jpeg->regs))
		वापस PTR_ERR(jpeg->regs);

	/* पूर्णांकerrupt service routine registration */
	jpeg->irq = ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot find IRQ\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, jpeg->irq, jpeg->variant->jpeg_irq,
				0, dev_name(&pdev->dev), jpeg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", jpeg->irq);
		वापस ret;
	पूर्ण

	/* घड़ीs */
	क्रम (i = 0; i < jpeg->variant->num_घड़ीs; i++) अणु
		jpeg->घड़ीs[i] = devm_clk_get(&pdev->dev,
					      jpeg->variant->clk_names[i]);
		अगर (IS_ERR(jpeg->घड़ीs[i])) अणु
			dev_err(&pdev->dev, "failed to get clock: %s\n",
				jpeg->variant->clk_names[i]);
			वापस PTR_ERR(jpeg->घड़ीs[i]);
		पूर्ण
	पूर्ण

	/* v4l2 device */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &jpeg->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register v4l2 device\n");
		वापस ret;
	पूर्ण

	/* mem2mem device */
	jpeg->m2m_dev = v4l2_m2m_init(jpeg->variant->m2m_ops);
	अगर (IS_ERR(jpeg->m2m_dev)) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(jpeg->m2m_dev);
		जाओ device_रेजिस्टर_rollback;
	पूर्ण

	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	/* JPEG encoder /dev/videoX node */
	jpeg->vfd_encoder = video_device_alloc();
	अगर (!jpeg->vfd_encoder) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ m2m_init_rollback;
	पूर्ण
	snम_लिखो(jpeg->vfd_encoder->name, माप(jpeg->vfd_encoder->name),
				"%s-enc", S5P_JPEG_M2M_NAME);
	jpeg->vfd_encoder->fops		= &s5p_jpeg_fops;
	jpeg->vfd_encoder->ioctl_ops	= &s5p_jpeg_ioctl_ops;
	jpeg->vfd_encoder->minor	= -1;
	jpeg->vfd_encoder->release	= video_device_release;
	jpeg->vfd_encoder->lock		= &jpeg->lock;
	jpeg->vfd_encoder->v4l2_dev	= &jpeg->v4l2_dev;
	jpeg->vfd_encoder->vfl_dir	= VFL_सूची_M2M;
	jpeg->vfd_encoder->device_caps	= V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;

	ret = video_रेजिस्टर_device(jpeg->vfd_encoder, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to register video device\n");
		video_device_release(jpeg->vfd_encoder);
		जाओ m2m_init_rollback;
	पूर्ण

	video_set_drvdata(jpeg->vfd_encoder, jpeg);
	v4l2_info(&jpeg->v4l2_dev,
		  "encoder device registered as /dev/video%d\n",
		  jpeg->vfd_encoder->num);

	/* JPEG decoder /dev/videoX node */
	jpeg->vfd_decoder = video_device_alloc();
	अगर (!jpeg->vfd_decoder) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to allocate video device\n");
		ret = -ENOMEM;
		जाओ enc_vdev_रेजिस्टर_rollback;
	पूर्ण
	snम_लिखो(jpeg->vfd_decoder->name, माप(jpeg->vfd_decoder->name),
				"%s-dec", S5P_JPEG_M2M_NAME);
	jpeg->vfd_decoder->fops		= &s5p_jpeg_fops;
	jpeg->vfd_decoder->ioctl_ops	= &s5p_jpeg_ioctl_ops;
	jpeg->vfd_decoder->minor	= -1;
	jpeg->vfd_decoder->release	= video_device_release;
	jpeg->vfd_decoder->lock		= &jpeg->lock;
	jpeg->vfd_decoder->v4l2_dev	= &jpeg->v4l2_dev;
	jpeg->vfd_decoder->vfl_dir	= VFL_सूची_M2M;
	jpeg->vfd_decoder->device_caps	= V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M;

	ret = video_रेजिस्टर_device(jpeg->vfd_decoder, VFL_TYPE_VIDEO, -1);
	अगर (ret) अणु
		v4l2_err(&jpeg->v4l2_dev, "Failed to register video device\n");
		video_device_release(jpeg->vfd_decoder);
		जाओ enc_vdev_रेजिस्टर_rollback;
	पूर्ण

	video_set_drvdata(jpeg->vfd_decoder, jpeg);
	v4l2_info(&jpeg->v4l2_dev,
		  "decoder device registered as /dev/video%d\n",
		  jpeg->vfd_decoder->num);

	/* final statements & घातer management */
	platक्रमm_set_drvdata(pdev, jpeg);

	pm_runसमय_enable(&pdev->dev);

	v4l2_info(&jpeg->v4l2_dev, "Samsung S5P JPEG codec\n");

	वापस 0;

enc_vdev_रेजिस्टर_rollback:
	video_unरेजिस्टर_device(jpeg->vfd_encoder);

m2m_init_rollback:
	v4l2_m2m_release(jpeg->m2m_dev);

device_रेजिस्टर_rollback:
	v4l2_device_unरेजिस्टर(&jpeg->v4l2_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक s5p_jpeg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s5p_jpeg *jpeg = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	pm_runसमय_disable(jpeg->dev);

	video_unरेजिस्टर_device(jpeg->vfd_decoder);
	video_unरेजिस्टर_device(jpeg->vfd_encoder);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	v4l2_m2m_release(jpeg->m2m_dev);
	v4l2_device_unरेजिस्टर(&jpeg->v4l2_dev);

	अगर (!pm_runसमय_status_suspended(&pdev->dev)) अणु
		क्रम (i = jpeg->variant->num_घड़ीs - 1; i >= 0; i--)
			clk_disable_unprepare(jpeg->घड़ीs[i]);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s5p_jpeg_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा s5p_jpeg *jpeg = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = jpeg->variant->num_घड़ीs - 1; i >= 0; i--)
		clk_disable_unprepare(jpeg->घड़ीs[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_jpeg_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा s5p_jpeg *jpeg = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ret;

	क्रम (i = 0; i < jpeg->variant->num_घड़ीs; i++) अणु
		ret = clk_prepare_enable(jpeg->घड़ीs[i]);
		अगर (ret) अणु
			जबतक (--i >= 0)
				clk_disable_unprepare(jpeg->घड़ीs[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&jpeg->slock, flags);

	/*
	 * JPEG IP allows storing two Huffman tables क्रम each component.
	 * We fill table 0 क्रम each component and करो this here only
	 * क्रम S5PC210 and Exynos3250 SoCs. Exynos4x12 and Exynos542x SoC
	 * require programming their Huffman tables each समय the encoding
	 * process is initialized, and thus it is accomplished in the
	 * device_run callback of m2m_ops.
	 */
	अगर (!jpeg->variant->htbl_reinit) अणु
		s5p_jpeg_set_hdctbl(jpeg->regs);
		s5p_jpeg_set_hdctblg(jpeg->regs);
		s5p_jpeg_set_hactbl(jpeg->regs);
		s5p_jpeg_set_hactblg(jpeg->regs);
	पूर्ण

	spin_unlock_irqrestore(&jpeg->slock, flags);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops s5p_jpeg_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(s5p_jpeg_runसमय_suspend, s5p_jpeg_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा s5p_jpeg_variant s5p_jpeg_drvdata = अणु
	.version	= SJPEG_S5P,
	.jpeg_irq	= s5p_jpeg_irq,
	.m2m_ops	= &s5p_jpeg_m2m_ops,
	.fmt_ver_flag	= SJPEG_FMT_FLAG_S5P,
	.clk_names	= अणु"jpeg"पूर्ण,
	.num_घड़ीs	= 1,
पूर्ण;

अटल काष्ठा s5p_jpeg_variant exynos3250_jpeg_drvdata = अणु
	.version	= SJPEG_EXYNOS3250,
	.jpeg_irq	= exynos3250_jpeg_irq,
	.m2m_ops	= &exynos3250_jpeg_m2m_ops,
	.fmt_ver_flag	= SJPEG_FMT_FLAG_EXYNOS3250,
	.hw3250_compat	= 1,
	.clk_names	= अणु"jpeg", "sclk"पूर्ण,
	.num_घड़ीs	= 2,
पूर्ण;

अटल काष्ठा s5p_jpeg_variant exynos4_jpeg_drvdata = अणु
	.version	= SJPEG_EXYNOS4,
	.jpeg_irq	= exynos4_jpeg_irq,
	.m2m_ops	= &exynos4_jpeg_m2m_ops,
	.fmt_ver_flag	= SJPEG_FMT_FLAG_EXYNOS4,
	.htbl_reinit	= 1,
	.clk_names	= अणु"jpeg"पूर्ण,
	.num_घड़ीs	= 1,
	.hw_ex4_compat	= 1,
पूर्ण;

अटल काष्ठा s5p_jpeg_variant exynos5420_jpeg_drvdata = अणु
	.version	= SJPEG_EXYNOS5420,
	.jpeg_irq	= exynos3250_jpeg_irq,		/* पूर्णांकentionally 3250 */
	.m2m_ops	= &exynos3250_jpeg_m2m_ops,	/* पूर्णांकentionally 3250 */
	.fmt_ver_flag	= SJPEG_FMT_FLAG_EXYNOS3250,	/* पूर्णांकentionally 3250 */
	.hw3250_compat	= 1,
	.htbl_reinit	= 1,
	.clk_names	= अणु"jpeg"पूर्ण,
	.num_घड़ीs	= 1,
पूर्ण;

अटल काष्ठा s5p_jpeg_variant exynos5433_jpeg_drvdata = अणु
	.version	= SJPEG_EXYNOS5433,
	.jpeg_irq	= exynos4_jpeg_irq,
	.m2m_ops	= &exynos4_jpeg_m2m_ops,
	.fmt_ver_flag	= SJPEG_FMT_FLAG_EXYNOS4,
	.htbl_reinit	= 1,
	.clk_names	= अणु"pclk", "aclk", "aclk_xiu", "sclk"पूर्ण,
	.num_घड़ीs	= 4,
	.hw_ex4_compat	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id samsung_jpeg_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-jpeg",
		.data = &s5p_jpeg_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos3250-jpeg",
		.data = &exynos3250_jpeg_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-jpeg",
		.data = &exynos4_jpeg_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-jpeg",
		.data = &exynos4_jpeg_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-jpeg",
		.data = &exynos5420_jpeg_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-jpeg",
		.data = &exynos5433_jpeg_drvdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, samsung_jpeg_match);

अटल व्योम *jpeg_get_drv_data(काष्ठा device *dev)
अणु
	काष्ठा s5p_jpeg_variant *driver_data = शून्य;
	स्थिर काष्ठा of_device_id *match;

	अगर (!IS_ENABLED(CONFIG_OF) || !dev->of_node)
		वापस &s5p_jpeg_drvdata;

	match = of_match_node(samsung_jpeg_match, dev->of_node);

	अगर (match)
		driver_data = (काष्ठा s5p_jpeg_variant *)match->data;

	वापस driver_data;
पूर्ण

अटल काष्ठा platक्रमm_driver s5p_jpeg_driver = अणु
	.probe = s5p_jpeg_probe,
	.हटाओ = s5p_jpeg_हटाओ,
	.driver = अणु
		.of_match_table	= of_match_ptr(samsung_jpeg_match),
		.name		= S5P_JPEG_M2M_NAME,
		.pm		= &s5p_jpeg_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s5p_jpeg_driver);

MODULE_AUTHOR("Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>");
MODULE_AUTHOR("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODULE_DESCRIPTION("Samsung JPEG codec driver");
MODULE_LICENSE("GPL");
