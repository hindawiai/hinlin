<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/media/platक्रमm/exynos3250-jpeg/jpeg-hw.h
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>

#समावेश "jpeg-core.h"
#समावेश "jpeg-regs.h"
#समावेश "jpeg-hw-exynos3250.h"

व्योम exynos3250_jpeg_reset(व्योम __iomem *regs)
अणु
	u32 reg = 1;
	पूर्णांक count = 1000;

	ग_लिखोl(1, regs + EXYNOS3250_SW_RESET);
	/* no other way but polling क्रम when JPEG IP becomes operational */
	जबतक (reg != 0 && --count > 0) अणु
		udelay(1);
		cpu_relax();
		reg = पढ़ोl(regs + EXYNOS3250_SW_RESET);
	पूर्ण

	reg = 0;
	count = 1000;

	जबतक (reg != 1 && --count > 0) अणु
		ग_लिखोl(1, regs + EXYNOS3250_JPGDRI);
		udelay(1);
		cpu_relax();
		reg = पढ़ोl(regs + EXYNOS3250_JPGDRI);
	पूर्ण

	ग_लिखोl(0, regs + EXYNOS3250_JPGDRI);
पूर्ण

व्योम exynos3250_jpeg_घातeron(व्योम __iomem *regs)
अणु
	ग_लिखोl(EXYNOS3250_POWER_ON, regs + EXYNOS3250_JPGCLKCON);
पूर्ण

व्योम exynos3250_jpeg_set_dma_num(व्योम __iomem *regs)
अणु
	ग_लिखोl(((EXYNOS3250_DMA_MO_COUNT << EXYNOS3250_WDMA_ISSUE_NUM_SHIFT) &
			EXYNOS3250_WDMA_ISSUE_NUM_MASK) |
	       ((EXYNOS3250_DMA_MO_COUNT << EXYNOS3250_RDMA_ISSUE_NUM_SHIFT) &
			EXYNOS3250_RDMA_ISSUE_NUM_MASK) |
	       ((EXYNOS3250_DMA_MO_COUNT << EXYNOS3250_ISSUE_GATHER_NUM_SHIFT) &
			EXYNOS3250_ISSUE_GATHER_NUM_MASK),
		regs + EXYNOS3250_DMA_ISSUE_NUM);
पूर्ण

व्योम exynos3250_jpeg_clk_set(व्योम __iomem *base)
अणु
	u32 reg;

	reg = पढ़ोl(base + EXYNOS3250_JPGCMOD) & ~EXYNOS3250_HALF_EN_MASK;

	ग_लिखोl(reg | EXYNOS3250_HALF_EN, base + EXYNOS3250_JPGCMOD);
पूर्ण

व्योम exynos3250_jpeg_input_raw_fmt(व्योम __iomem *regs, अचिन्हित पूर्णांक fmt)
अणु
	u32 reg;

	reg = पढ़ोl(regs + EXYNOS3250_JPGCMOD) &
			EXYNOS3250_MODE_Y16_MASK;

	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_RGB32:
		reg |= EXYNOS3250_MODE_SEL_ARGB8888;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		reg |= EXYNOS3250_MODE_SEL_ARGB8888 | EXYNOS3250_SRC_SWAP_RGB;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		reg |= EXYNOS3250_MODE_SEL_RGB565;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565X:
		reg |= EXYNOS3250_MODE_SEL_RGB565 | EXYNOS3250_SRC_SWAP_RGB;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		reg |= EXYNOS3250_MODE_SEL_422_1P_LUM_CHR;
		अवरोध;
	हाल V4L2_PIX_FMT_YVYU:
		reg |= EXYNOS3250_MODE_SEL_422_1P_LUM_CHR |
			EXYNOS3250_SRC_SWAP_UV;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		reg |= EXYNOS3250_MODE_SEL_422_1P_CHR_LUM;
		अवरोध;
	हाल V4L2_PIX_FMT_VYUY:
		reg |= EXYNOS3250_MODE_SEL_422_1P_CHR_LUM |
			EXYNOS3250_SRC_SWAP_UV;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		reg |= EXYNOS3250_MODE_SEL_420_2P | EXYNOS3250_SRC_NV12;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
		reg |= EXYNOS3250_MODE_SEL_420_2P | EXYNOS3250_SRC_NV21;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		reg |= EXYNOS3250_MODE_SEL_420_3P;
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण

	ग_लिखोl(reg, regs + EXYNOS3250_JPGCMOD);
पूर्ण

व्योम exynos3250_jpeg_set_y16(व्योम __iomem *regs, bool y16)
अणु
	u32 reg;

	reg = पढ़ोl(regs + EXYNOS3250_JPGCMOD);
	अगर (y16)
		reg |= EXYNOS3250_MODE_Y16;
	अन्यथा
		reg &= ~EXYNOS3250_MODE_Y16_MASK;
	ग_लिखोl(reg, regs + EXYNOS3250_JPGCMOD);
पूर्ण

व्योम exynos3250_jpeg_proc_mode(व्योम __iomem *regs, अचिन्हित पूर्णांक mode)
अणु
	u32 reg, m;

	अगर (mode == S5P_JPEG_ENCODE)
		m = EXYNOS3250_PROC_MODE_COMPR;
	अन्यथा
		m = EXYNOS3250_PROC_MODE_DECOMPR;
	reg = पढ़ोl(regs + EXYNOS3250_JPGMOD);
	reg &= ~EXYNOS3250_PROC_MODE_MASK;
	reg |= m;
	ग_लिखोl(reg, regs + EXYNOS3250_JPGMOD);
पूर्ण

व्योम exynos3250_jpeg_subsampling_mode(व्योम __iomem *regs, अचिन्हित पूर्णांक mode)
अणु
	u32 reg, m = 0;

	चयन (mode) अणु
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_444:
		m = EXYNOS3250_SUBSAMPLING_MODE_444;
		अवरोध;
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_422:
		m = EXYNOS3250_SUBSAMPLING_MODE_422;
		अवरोध;
	हाल V4L2_JPEG_CHROMA_SUBSAMPLING_420:
		m = EXYNOS3250_SUBSAMPLING_MODE_420;
		अवरोध;
	पूर्ण

	reg = पढ़ोl(regs + EXYNOS3250_JPGMOD);
	reg &= ~EXYNOS3250_SUBSAMPLING_MODE_MASK;
	reg |= m;
	ग_लिखोl(reg, regs + EXYNOS3250_JPGMOD);
पूर्ण

अचिन्हित पूर्णांक exynos3250_jpeg_get_subsampling_mode(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + EXYNOS3250_JPGMOD) &
				EXYNOS3250_SUBSAMPLING_MODE_MASK;
पूर्ण

व्योम exynos3250_jpeg_dri(व्योम __iomem *regs, अचिन्हित पूर्णांक dri)
अणु
	u32 reg;

	reg = dri & EXYNOS3250_JPGDRI_MASK;
	ग_लिखोl(reg, regs + EXYNOS3250_JPGDRI);
पूर्ण

व्योम exynos3250_jpeg_qtbl(व्योम __iomem *regs, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + EXYNOS3250_QHTBL);
	reg &= ~EXYNOS3250_QT_NUM_MASK(t);
	reg |= (n << EXYNOS3250_QT_NUM_SHIFT(t)) &
					EXYNOS3250_QT_NUM_MASK(t);
	ग_लिखोl(reg, regs + EXYNOS3250_QHTBL);
पूर्ण

व्योम exynos3250_jpeg_htbl_ac(व्योम __iomem *regs, अचिन्हित पूर्णांक t)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + EXYNOS3250_QHTBL);
	reg &= ~EXYNOS3250_HT_NUM_AC_MASK(t);
	/* this driver uses table 0 क्रम all color components */
	reg |= (0 << EXYNOS3250_HT_NUM_AC_SHIFT(t)) &
					EXYNOS3250_HT_NUM_AC_MASK(t);
	ग_लिखोl(reg, regs + EXYNOS3250_QHTBL);
पूर्ण

व्योम exynos3250_jpeg_htbl_dc(व्योम __iomem *regs, अचिन्हित पूर्णांक t)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + EXYNOS3250_QHTBL);
	reg &= ~EXYNOS3250_HT_NUM_DC_MASK(t);
	/* this driver uses table 0 क्रम all color components */
	reg |= (0 << EXYNOS3250_HT_NUM_DC_SHIFT(t)) &
					EXYNOS3250_HT_NUM_DC_MASK(t);
	ग_लिखोl(reg, regs + EXYNOS3250_QHTBL);
पूर्ण

व्योम exynos3250_jpeg_set_y(व्योम __iomem *regs, अचिन्हित पूर्णांक y)
अणु
	u32 reg;

	reg = y & EXYNOS3250_JPGY_MASK;
	ग_लिखोl(reg, regs + EXYNOS3250_JPGY);
पूर्ण

व्योम exynos3250_jpeg_set_x(व्योम __iomem *regs, अचिन्हित पूर्णांक x)
अणु
	u32 reg;

	reg = x & EXYNOS3250_JPGX_MASK;
	ग_लिखोl(reg, regs + EXYNOS3250_JPGX);
पूर्ण

#अगर 0	/* Currently unused */
अचिन्हित पूर्णांक exynos3250_jpeg_get_y(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + EXYNOS3250_JPGY);
पूर्ण

अचिन्हित पूर्णांक exynos3250_jpeg_get_x(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + EXYNOS3250_JPGX);
पूर्ण
#पूर्ण_अगर

व्योम exynos3250_jpeg_पूर्णांकerrupts_enable(व्योम __iomem *regs)
अणु
	u32 reg;

	reg = पढ़ोl(regs + EXYNOS3250_JPGINTSE);
	reg |= (EXYNOS3250_JPEG_DONE_EN |
		EXYNOS3250_WDMA_DONE_EN |
		EXYNOS3250_RDMA_DONE_EN |
		EXYNOS3250_ENC_STREAM_INT_EN |
		EXYNOS3250_CORE_DONE_EN |
		EXYNOS3250_ERR_INT_EN |
		EXYNOS3250_HEAD_INT_EN);
	ग_लिखोl(reg, regs + EXYNOS3250_JPGINTSE);
पूर्ण

व्योम exynos3250_jpeg_enc_stream_bound(व्योम __iomem *regs, अचिन्हित पूर्णांक size)
अणु
	u32 reg;

	reg = size & EXYNOS3250_ENC_STREAM_BOUND_MASK;
	ग_लिखोl(reg, regs + EXYNOS3250_ENC_STREAM_BOUND);
पूर्ण

व्योम exynos3250_jpeg_output_raw_fmt(व्योम __iomem *regs, अचिन्हित पूर्णांक fmt)
अणु
	u32 reg;

	चयन (fmt) अणु
	हाल V4L2_PIX_FMT_RGB32:
		reg = EXYNOS3250_OUT_FMT_ARGB8888;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		reg = EXYNOS3250_OUT_FMT_ARGB8888 | EXYNOS3250_OUT_SWAP_RGB;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		reg = EXYNOS3250_OUT_FMT_RGB565;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565X:
		reg = EXYNOS3250_OUT_FMT_RGB565 | EXYNOS3250_OUT_SWAP_RGB;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		reg = EXYNOS3250_OUT_FMT_422_1P_LUM_CHR;
		अवरोध;
	हाल V4L2_PIX_FMT_YVYU:
		reg = EXYNOS3250_OUT_FMT_422_1P_LUM_CHR |
			EXYNOS3250_OUT_SWAP_UV;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		reg = EXYNOS3250_OUT_FMT_422_1P_CHR_LUM;
		अवरोध;
	हाल V4L2_PIX_FMT_VYUY:
		reg = EXYNOS3250_OUT_FMT_422_1P_CHR_LUM |
			EXYNOS3250_OUT_SWAP_UV;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		reg = EXYNOS3250_OUT_FMT_420_2P | EXYNOS3250_OUT_NV12;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
		reg = EXYNOS3250_OUT_FMT_420_2P | EXYNOS3250_OUT_NV21;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		reg = EXYNOS3250_OUT_FMT_420_3P;
		अवरोध;
	शेष:
		reg = 0;
		अवरोध;
	पूर्ण

	ग_लिखोl(reg, regs + EXYNOS3250_OUTFORM);
पूर्ण

व्योम exynos3250_jpeg_jpgadr(व्योम __iomem *regs, अचिन्हित पूर्णांक addr)
अणु
	ग_लिखोl(addr, regs + EXYNOS3250_JPG_JPGADR);
पूर्ण

व्योम exynos3250_jpeg_imgadr(व्योम __iomem *regs, काष्ठा s5p_jpeg_addr *img_addr)
अणु
	ग_लिखोl(img_addr->y, regs + EXYNOS3250_LUMA_BASE);
	ग_लिखोl(img_addr->cb, regs + EXYNOS3250_CHROMA_BASE);
	ग_लिखोl(img_addr->cr, regs + EXYNOS3250_CHROMA_CR_BASE);
पूर्ण

व्योम exynos3250_jpeg_stride(व्योम __iomem *regs, अचिन्हित पूर्णांक img_fmt,
			    अचिन्हित पूर्णांक width)
अणु
	u32 reg_luma = 0, reg_cr = 0, reg_cb = 0;

	चयन (img_fmt) अणु
	हाल V4L2_PIX_FMT_RGB32:
		reg_luma = 4 * width;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
		reg_luma = 2 * width;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		reg_luma = width;
		reg_cb = reg_luma;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420:
		reg_luma = width;
		reg_cb = reg_cr = reg_luma / 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखोl(reg_luma, regs + EXYNOS3250_LUMA_STRIDE);
	ग_लिखोl(reg_cb, regs + EXYNOS3250_CHROMA_STRIDE);
	ग_लिखोl(reg_cr, regs + EXYNOS3250_CHROMA_CR_STRIDE);
पूर्ण

व्योम exynos3250_jpeg_offset(व्योम __iomem *regs, अचिन्हित पूर्णांक x_offset,
				अचिन्हित पूर्णांक y_offset)
अणु
	u32 reg;

	reg = (y_offset << EXYNOS3250_LUMA_YY_OFFSET_SHIFT) &
			EXYNOS3250_LUMA_YY_OFFSET_MASK;
	reg |= (x_offset << EXYNOS3250_LUMA_YX_OFFSET_SHIFT) &
			EXYNOS3250_LUMA_YX_OFFSET_MASK;

	ग_लिखोl(reg, regs + EXYNOS3250_LUMA_XY_OFFSET);

	reg = (y_offset << EXYNOS3250_CHROMA_YY_OFFSET_SHIFT) &
			EXYNOS3250_CHROMA_YY_OFFSET_MASK;
	reg |= (x_offset << EXYNOS3250_CHROMA_YX_OFFSET_SHIFT) &
			EXYNOS3250_CHROMA_YX_OFFSET_MASK;

	ग_लिखोl(reg, regs + EXYNOS3250_CHROMA_XY_OFFSET);

	reg = (y_offset << EXYNOS3250_CHROMA_CR_YY_OFFSET_SHIFT) &
			EXYNOS3250_CHROMA_CR_YY_OFFSET_MASK;
	reg |= (x_offset << EXYNOS3250_CHROMA_CR_YX_OFFSET_SHIFT) &
			EXYNOS3250_CHROMA_CR_YX_OFFSET_MASK;

	ग_लिखोl(reg, regs + EXYNOS3250_CHROMA_CR_XY_OFFSET);
पूर्ण

व्योम exynos3250_jpeg_coef(व्योम __iomem *base, अचिन्हित पूर्णांक mode)
अणु
	अगर (mode == S5P_JPEG_ENCODE) अणु
		ग_लिखोl(EXYNOS3250_JPEG_ENC_COEF1,
					base + EXYNOS3250_JPG_COEF(1));
		ग_लिखोl(EXYNOS3250_JPEG_ENC_COEF2,
					base + EXYNOS3250_JPG_COEF(2));
		ग_लिखोl(EXYNOS3250_JPEG_ENC_COEF3,
					base + EXYNOS3250_JPG_COEF(3));
	पूर्ण अन्यथा अणु
		ग_लिखोl(EXYNOS3250_JPEG_DEC_COEF1,
					base + EXYNOS3250_JPG_COEF(1));
		ग_लिखोl(EXYNOS3250_JPEG_DEC_COEF2,
					base + EXYNOS3250_JPG_COEF(2));
		ग_लिखोl(EXYNOS3250_JPEG_DEC_COEF3,
					base + EXYNOS3250_JPG_COEF(3));
	पूर्ण
पूर्ण

व्योम exynos3250_jpeg_start(व्योम __iomem *regs)
अणु
	ग_लिखोl(1, regs + EXYNOS3250_JSTART);
पूर्ण

व्योम exynos3250_jpeg_rstart(व्योम __iomem *regs)
अणु
	ग_लिखोl(1, regs + EXYNOS3250_JRSTART);
पूर्ण

अचिन्हित पूर्णांक exynos3250_jpeg_get_पूर्णांक_status(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + EXYNOS3250_JPGINTST);
पूर्ण

व्योम exynos3250_jpeg_clear_पूर्णांक_status(व्योम __iomem *regs,
				      अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl(value, regs + EXYNOS3250_JPGINTST);
पूर्ण

अचिन्हित पूर्णांक exynos3250_jpeg_operating(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + S5P_JPGOPR) & EXYNOS3250_JPGOPR_MASK;
पूर्ण

अचिन्हित पूर्णांक exynos3250_jpeg_compressed_size(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + EXYNOS3250_JPGCNT) & EXYNOS3250_JPGCNT_MASK;
पूर्ण

व्योम exynos3250_jpeg_dec_stream_size(व्योम __iomem *regs,
						अचिन्हित पूर्णांक size)
अणु
	ग_लिखोl(size & EXYNOS3250_DEC_STREAM_MASK,
				regs + EXYNOS3250_DEC_STREAM_SIZE);
पूर्ण

व्योम exynos3250_jpeg_dec_scaling_ratio(व्योम __iomem *regs,
						अचिन्हित पूर्णांक sratio)
अणु
	चयन (sratio) अणु
	हाल 1:
	शेष:
		sratio = EXYNOS3250_DEC_SCALE_FACTOR_8_8;
		अवरोध;
	हाल 2:
		sratio = EXYNOS3250_DEC_SCALE_FACTOR_4_8;
		अवरोध;
	हाल 4:
		sratio = EXYNOS3250_DEC_SCALE_FACTOR_2_8;
		अवरोध;
	हाल 8:
		sratio = EXYNOS3250_DEC_SCALE_FACTOR_1_8;
		अवरोध;
	पूर्ण

	ग_लिखोl(sratio & EXYNOS3250_DEC_SCALE_FACTOR_MASK,
				regs + EXYNOS3250_DEC_SCALING_RATIO);
पूर्ण

व्योम exynos3250_jpeg_set_समयr(व्योम __iomem *regs, अचिन्हित पूर्णांक समय_value)
अणु
	समय_value &= EXYNOS3250_TIMER_INIT_MASK;

	ग_लिखोl(EXYNOS3250_TIMER_INT_STAT | समय_value,
					regs + EXYNOS3250_TIMER_SE);
पूर्ण

अचिन्हित पूर्णांक exynos3250_jpeg_get_समयr_status(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + EXYNOS3250_TIMER_ST);
पूर्ण

व्योम exynos3250_jpeg_clear_समयr_status(व्योम __iomem *regs)
अणु
	ग_लिखोl(EXYNOS3250_TIMER_INT_STAT, regs + EXYNOS3250_TIMER_ST);
पूर्ण
