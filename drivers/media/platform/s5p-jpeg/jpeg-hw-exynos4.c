<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 *
 * Register पूर्णांकerface file क्रम JPEG driver on Exynos4x12.
 */
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश "jpeg-core.h"
#समावेश "jpeg-hw-exynos4.h"
#समावेश "jpeg-regs.h"

व्योम exynos4_jpeg_sw_reset(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(base + EXYNOS4_JPEG_CNTL_REG);
	ग_लिखोl(reg & ~(EXYNOS4_DEC_MODE | EXYNOS4_ENC_MODE),
				base + EXYNOS4_JPEG_CNTL_REG);

	reg = पढ़ोl(base + EXYNOS4_JPEG_CNTL_REG);
	ग_लिखोl(reg & ~EXYNOS4_SOFT_RESET_HI, base + EXYNOS4_JPEG_CNTL_REG);

	udelay(100);

	ग_लिखोl(reg | EXYNOS4_SOFT_RESET_HI, base + EXYNOS4_JPEG_CNTL_REG);
पूर्ण

व्योम exynos4_jpeg_set_enc_dec_mode(व्योम __iomem *base, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(base + EXYNOS4_JPEG_CNTL_REG);
	/* set exynos4_jpeg mod रेजिस्टर */
	अगर (mode == S5P_JPEG_DECODE) अणु
		ग_लिखोl((reg & EXYNOS4_ENC_DEC_MODE_MASK) |
					EXYNOS4_DEC_MODE,
			base + EXYNOS4_JPEG_CNTL_REG);
	पूर्ण अन्यथा अगर (mode == S5P_JPEG_ENCODE) अणु/* encode */
		ग_लिखोl((reg & EXYNOS4_ENC_DEC_MODE_MASK) |
					EXYNOS4_ENC_MODE,
			base + EXYNOS4_JPEG_CNTL_REG);
	पूर्ण अन्यथा अणु /* disable both */
		ग_लिखोl(reg & EXYNOS4_ENC_DEC_MODE_MASK,
			base + EXYNOS4_JPEG_CNTL_REG);
	पूर्ण
पूर्ण

व्योम __exynos4_jpeg_set_img_fmt(व्योम __iomem *base, अचिन्हित पूर्णांक img_fmt,
				अचिन्हित पूर्णांक version)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक exynos4_swap_chroma_cbcr;
	अचिन्हित पूर्णांक exynos4_swap_chroma_crcb;

	अगर (version == SJPEG_EXYNOS4) अणु
		exynos4_swap_chroma_cbcr = EXYNOS4_SWAP_CHROMA_CBCR;
		exynos4_swap_chroma_crcb = EXYNOS4_SWAP_CHROMA_CRCB;
	पूर्ण अन्यथा अणु
		exynos4_swap_chroma_cbcr = EXYNOS5433_SWAP_CHROMA_CBCR;
		exynos4_swap_chroma_crcb = EXYNOS5433_SWAP_CHROMA_CRCB;
	पूर्ण

	reg = पढ़ोl(base + EXYNOS4_IMG_FMT_REG) &
			EXYNOS4_ENC_IN_FMT_MASK; /* clear except enc क्रमmat */

	चयन (img_fmt) अणु
	हाल V4L2_PIX_FMT_GREY:
		reg = reg | EXYNOS4_ENC_GRAY_IMG | EXYNOS4_GRAY_IMG_IP;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB32:
		reg = reg | EXYNOS4_ENC_RGB_IMG |
				EXYNOS4_RGB_IP_RGB_32BIT_IMG;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		reg = reg | EXYNOS4_ENC_RGB_IMG |
				EXYNOS4_RGB_IP_RGB_16BIT_IMG;
		अवरोध;
	हाल V4L2_PIX_FMT_NV24:
		reg = reg | EXYNOS4_ENC_YUV_444_IMG |
				EXYNOS4_YUV_444_IP_YUV_444_2P_IMG |
				exynos4_swap_chroma_cbcr;
		अवरोध;
	हाल V4L2_PIX_FMT_NV42:
		reg = reg | EXYNOS4_ENC_YUV_444_IMG |
				EXYNOS4_YUV_444_IP_YUV_444_2P_IMG |
				exynos4_swap_chroma_crcb;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		reg = reg | EXYNOS4_DEC_YUV_422_IMG |
				EXYNOS4_YUV_422_IP_YUV_422_1P_IMG |
				exynos4_swap_chroma_cbcr;
		अवरोध;

	हाल V4L2_PIX_FMT_YVYU:
		reg = reg | EXYNOS4_DEC_YUV_422_IMG |
				EXYNOS4_YUV_422_IP_YUV_422_1P_IMG |
				exynos4_swap_chroma_crcb;
		अवरोध;
	हाल V4L2_PIX_FMT_NV16:
		reg = reg | EXYNOS4_DEC_YUV_422_IMG |
				EXYNOS4_YUV_422_IP_YUV_422_2P_IMG |
				exynos4_swap_chroma_cbcr;
		अवरोध;
	हाल V4L2_PIX_FMT_NV61:
		reg = reg | EXYNOS4_DEC_YUV_422_IMG |
				EXYNOS4_YUV_422_IP_YUV_422_2P_IMG |
				exynos4_swap_chroma_crcb;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		reg = reg | EXYNOS4_DEC_YUV_420_IMG |
				EXYNOS4_YUV_420_IP_YUV_420_2P_IMG |
				exynos4_swap_chroma_cbcr;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
		reg = reg | EXYNOS4_DEC_YUV_420_IMG |
				EXYNOS4_YUV_420_IP_YUV_420_2P_IMG |
				exynos4_swap_chroma_crcb;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		reg = reg | EXYNOS4_DEC_YUV_420_IMG |
				EXYNOS4_YUV_420_IP_YUV_420_3P_IMG |
				exynos4_swap_chroma_cbcr;
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण

	ग_लिखोl(reg, base + EXYNOS4_IMG_FMT_REG);
पूर्ण

व्योम __exynos4_jpeg_set_enc_out_fmt(व्योम __iomem *base, अचिन्हित पूर्णांक out_fmt,
				    अचिन्हित पूर्णांक version)
अणु
	अचिन्हित पूर्णांक reg;

	reg = पढ़ोl(base + EXYNOS4_IMG_FMT_REG) &
			~(version == SJPEG_EXYNOS4 ? EXYNOS4_ENC_FMT_MASK :
			  EXYNOS5433_ENC_FMT_MASK); /* clear enc क्रमmat */

	चयन (out_fmt) अणु
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY:
		reg = reg | EXYNOS4_ENC_FMT_GRAY;
		अवरोध;

	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_444:
		reg = reg | EXYNOS4_ENC_FMT_YUV_444;
		अवरोध;

	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_422:
		reg = reg | EXYNOS4_ENC_FMT_YUV_422;
		अवरोध;

	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_420:
		reg = reg | EXYNOS4_ENC_FMT_YUV_420;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(reg, base + EXYNOS4_IMG_FMT_REG);
पूर्ण

व्योम exynos4_jpeg_set_पूर्णांकerrupt(व्योम __iomem *base, अचिन्हित पूर्णांक version)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (version == SJPEG_EXYNOS4) अणु
		reg = पढ़ोl(base + EXYNOS4_INT_EN_REG) & ~EXYNOS4_INT_EN_MASK;
		ग_लिखोl(reg | EXYNOS4_INT_EN_ALL, base + EXYNOS4_INT_EN_REG);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl(base + EXYNOS4_INT_EN_REG) &
							~EXYNOS5433_INT_EN_MASK;
		ग_लिखोl(reg | EXYNOS5433_INT_EN_ALL, base + EXYNOS4_INT_EN_REG);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक exynos4_jpeg_get_पूर्णांक_status(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + EXYNOS4_INT_STATUS_REG);
पूर्ण

अचिन्हित पूर्णांक exynos4_jpeg_get_fअगरo_status(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + EXYNOS4_FIFO_STATUS_REG);
पूर्ण

व्योम exynos4_jpeg_set_huf_table_enable(व्योम __iomem *base, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक	reg;

	reg = पढ़ोl(base + EXYNOS4_JPEG_CNTL_REG) & ~EXYNOS4_HUF_TBL_EN;

	अगर (value == 1)
		ग_लिखोl(reg | EXYNOS4_HUF_TBL_EN,
					base + EXYNOS4_JPEG_CNTL_REG);
	अन्यथा
		ग_लिखोl(reg & ~EXYNOS4_HUF_TBL_EN,
					base + EXYNOS4_JPEG_CNTL_REG);
पूर्ण

व्योम exynos4_jpeg_set_sys_पूर्णांक_enable(व्योम __iomem *base, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक	reg;

	reg = पढ़ोl(base + EXYNOS4_JPEG_CNTL_REG) & ~(EXYNOS4_SYS_INT_EN);

	अगर (value == 1)
		ग_लिखोl(reg | EXYNOS4_SYS_INT_EN, base + EXYNOS4_JPEG_CNTL_REG);
	अन्यथा
		ग_लिखोl(reg & ~EXYNOS4_SYS_INT_EN, base + EXYNOS4_JPEG_CNTL_REG);
पूर्ण

व्योम exynos4_jpeg_set_stream_buf_address(व्योम __iomem *base,
					 अचिन्हित पूर्णांक address)
अणु
	ग_लिखोl(address, base + EXYNOS4_OUT_MEM_BASE_REG);
पूर्ण

व्योम exynos4_jpeg_set_stream_size(व्योम __iomem *base,
		अचिन्हित पूर्णांक x_value, अचिन्हित पूर्णांक y_value)
अणु
	ग_लिखोl(0x0, base + EXYNOS4_JPEG_IMG_SIZE_REG); /* clear */
	ग_लिखोl(EXYNOS4_X_SIZE(x_value) | EXYNOS4_Y_SIZE(y_value),
			base + EXYNOS4_JPEG_IMG_SIZE_REG);
पूर्ण

व्योम exynos4_jpeg_set_frame_buf_address(व्योम __iomem *base,
				काष्ठा s5p_jpeg_addr *exynos4_jpeg_addr)
अणु
	ग_लिखोl(exynos4_jpeg_addr->y, base + EXYNOS4_IMG_BA_PLANE_1_REG);
	ग_लिखोl(exynos4_jpeg_addr->cb, base + EXYNOS4_IMG_BA_PLANE_2_REG);
	ग_लिखोl(exynos4_jpeg_addr->cr, base + EXYNOS4_IMG_BA_PLANE_3_REG);
पूर्ण

व्योम exynos4_jpeg_set_encode_tbl_select(व्योम __iomem *base,
		क्रमागत exynos4_jpeg_img_quality_level level)
अणु
	अचिन्हित पूर्णांक	reg;

	reg = EXYNOS4_Q_TBL_COMP1_0 | EXYNOS4_Q_TBL_COMP2_1 |
		EXYNOS4_Q_TBL_COMP3_1 |
		EXYNOS4_HUFF_TBL_COMP1_AC_0_DC_1 |
		EXYNOS4_HUFF_TBL_COMP2_AC_0_DC_0 |
		EXYNOS4_HUFF_TBL_COMP3_AC_1_DC_1;

	ग_लिखोl(reg, base + EXYNOS4_TBL_SEL_REG);
पूर्ण

व्योम exynos4_jpeg_set_dec_components(व्योम __iomem *base, पूर्णांक n)
अणु
	अचिन्हित पूर्णांक	reg;

	reg = पढ़ोl(base + EXYNOS4_TBL_SEL_REG);

	reg |= EXYNOS4_NF(n);
	ग_लिखोl(reg, base + EXYNOS4_TBL_SEL_REG);
पूर्ण

व्योम exynos4_jpeg_select_dec_q_tbl(व्योम __iomem *base, अक्षर c, अक्षर x)
अणु
	अचिन्हित पूर्णांक	reg;

	reg = पढ़ोl(base + EXYNOS4_TBL_SEL_REG);

	reg |= EXYNOS4_Q_TBL_COMP(c, x);
	ग_लिखोl(reg, base + EXYNOS4_TBL_SEL_REG);
पूर्ण

व्योम exynos4_jpeg_select_dec_h_tbl(व्योम __iomem *base, अक्षर c, अक्षर x)
अणु
	अचिन्हित पूर्णांक	reg;

	reg = पढ़ोl(base + EXYNOS4_TBL_SEL_REG);

	reg |= EXYNOS4_HUFF_TBL_COMP(c, x);
	ग_लिखोl(reg, base + EXYNOS4_TBL_SEL_REG);
पूर्ण

व्योम exynos4_jpeg_set_encode_hoff_cnt(व्योम __iomem *base, अचिन्हित पूर्णांक fmt)
अणु
	अगर (fmt == V4L2_PIX_FMT_GREY)
		ग_लिखोl(0xd2, base + EXYNOS4_HUFF_CNT_REG);
	अन्यथा
		ग_लिखोl(0x1a2, base + EXYNOS4_HUFF_CNT_REG);
पूर्ण

अचिन्हित पूर्णांक exynos4_jpeg_get_stream_size(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + EXYNOS4_BITSTREAM_SIZE_REG);
पूर्ण

व्योम exynos4_jpeg_set_dec_bitstream_size(व्योम __iomem *base, अचिन्हित पूर्णांक size)
अणु
	ग_लिखोl(size, base + EXYNOS4_BITSTREAM_SIZE_REG);
पूर्ण

व्योम exynos4_jpeg_get_frame_size(व्योम __iomem *base,
			अचिन्हित पूर्णांक *width, अचिन्हित पूर्णांक *height)
अणु
	*width = (पढ़ोl(base + EXYNOS4_DECODE_XY_SIZE_REG) &
				EXYNOS4_DECODED_SIZE_MASK);
	*height = (पढ़ोl(base + EXYNOS4_DECODE_XY_SIZE_REG) >> 16) &
				EXYNOS4_DECODED_SIZE_MASK;
पूर्ण

अचिन्हित पूर्णांक exynos4_jpeg_get_frame_fmt(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + EXYNOS4_DECODE_IMG_FMT_REG) &
				EXYNOS4_JPEG_DECODED_IMG_FMT_MASK;
पूर्ण

व्योम exynos4_jpeg_set_समयr_count(व्योम __iomem *base, अचिन्हित पूर्णांक size)
अणु
	ग_लिखोl(size, base + EXYNOS4_INT_TIMER_COUNT_REG);
पूर्ण
