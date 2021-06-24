<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/media/platक्रमm/s5p-jpeg/jpeg-hw.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/videodev2.h>

#समावेश "jpeg-core.h"
#समावेश "jpeg-regs.h"
#समावेश "jpeg-hw-s5p.h"

व्योम s5p_jpeg_reset(व्योम __iomem *regs)
अणु
	अचिन्हित दीर्घ reg;

	ग_लिखोl(1, regs + S5P_JPG_SW_RESET);
	reg = पढ़ोl(regs + S5P_JPG_SW_RESET);
	/* no other way but polling क्रम when JPEG IP becomes operational */
	जबतक (reg != 0) अणु
		cpu_relax();
		reg = पढ़ोl(regs + S5P_JPG_SW_RESET);
	पूर्ण
पूर्ण

व्योम s5p_jpeg_घातeron(व्योम __iomem *regs)
अणु
	ग_लिखोl(S5P_POWER_ON, regs + S5P_JPGCLKCON);
पूर्ण

व्योम s5p_jpeg_input_raw_mode(व्योम __iomem *regs, अचिन्हित दीर्घ mode)
अणु
	अचिन्हित दीर्घ reg, m;

	m = S5P_MOD_SEL_565;
	अगर (mode == S5P_JPEG_RAW_IN_565)
		m = S5P_MOD_SEL_565;
	अन्यथा अगर (mode == S5P_JPEG_RAW_IN_422)
		m = S5P_MOD_SEL_422;

	reg = पढ़ोl(regs + S5P_JPGCMOD);
	reg &= ~S5P_MOD_SEL_MASK;
	reg |= m;
	ग_लिखोl(reg, regs + S5P_JPGCMOD);
पूर्ण

व्योम s5p_jpeg_proc_mode(व्योम __iomem *regs, अचिन्हित दीर्घ mode)
अणु
	अचिन्हित दीर्घ reg, m;

	m = S5P_PROC_MODE_DECOMPR;
	अगर (mode == S5P_JPEG_ENCODE)
		m = S5P_PROC_MODE_COMPR;
	अन्यथा
		m = S5P_PROC_MODE_DECOMPR;
	reg = पढ़ोl(regs + S5P_JPGMOD);
	reg &= ~S5P_PROC_MODE_MASK;
	reg |= m;
	ग_लिखोl(reg, regs + S5P_JPGMOD);
पूर्ण

व्योम s5p_jpeg_subsampling_mode(व्योम __iomem *regs, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ reg, m;

	अगर (mode == V4L2_JPEG_CHROMA_SUBSAMPLING_420)
		m = S5P_SUBSAMPLING_MODE_420;
	अन्यथा
		m = S5P_SUBSAMPLING_MODE_422;

	reg = पढ़ोl(regs + S5P_JPGMOD);
	reg &= ~S5P_SUBSAMPLING_MODE_MASK;
	reg |= m;
	ग_लिखोl(reg, regs + S5P_JPGMOD);
पूर्ण

अचिन्हित पूर्णांक s5p_jpeg_get_subsampling_mode(व्योम __iomem *regs)
अणु
	वापस पढ़ोl(regs + S5P_JPGMOD) & S5P_SUBSAMPLING_MODE_MASK;
पूर्ण

व्योम s5p_jpeg_dri(व्योम __iomem *regs, अचिन्हित पूर्णांक dri)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPGDRI_U);
	reg &= ~0xff;
	reg |= (dri >> 8) & 0xff;
	ग_लिखोl(reg, regs + S5P_JPGDRI_U);

	reg = पढ़ोl(regs + S5P_JPGDRI_L);
	reg &= ~0xff;
	reg |= dri & 0xff;
	ग_लिखोl(reg, regs + S5P_JPGDRI_L);
पूर्ण

व्योम s5p_jpeg_qtbl(व्योम __iomem *regs, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_QTBL);
	reg &= ~S5P_QT_NUMt_MASK(t);
	reg |= (n << S5P_QT_NUMt_SHIFT(t)) & S5P_QT_NUMt_MASK(t);
	ग_लिखोl(reg, regs + S5P_JPG_QTBL);
पूर्ण

व्योम s5p_jpeg_htbl_ac(व्योम __iomem *regs, अचिन्हित पूर्णांक t)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_HTBL);
	reg &= ~S5P_HT_NUMt_AC_MASK(t);
	/* this driver uses table 0 क्रम all color components */
	reg |= (0 << S5P_HT_NUMt_AC_SHIFT(t)) & S5P_HT_NUMt_AC_MASK(t);
	ग_लिखोl(reg, regs + S5P_JPG_HTBL);
पूर्ण

व्योम s5p_jpeg_htbl_dc(व्योम __iomem *regs, अचिन्हित पूर्णांक t)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_HTBL);
	reg &= ~S5P_HT_NUMt_DC_MASK(t);
	/* this driver uses table 0 क्रम all color components */
	reg |= (0 << S5P_HT_NUMt_DC_SHIFT(t)) & S5P_HT_NUMt_DC_MASK(t);
	ग_लिखोl(reg, regs + S5P_JPG_HTBL);
पूर्ण

व्योम s5p_jpeg_y(व्योम __iomem *regs, अचिन्हित पूर्णांक y)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPGY_U);
	reg &= ~0xff;
	reg |= (y >> 8) & 0xff;
	ग_लिखोl(reg, regs + S5P_JPGY_U);

	reg = पढ़ोl(regs + S5P_JPGY_L);
	reg &= ~0xff;
	reg |= y & 0xff;
	ग_लिखोl(reg, regs + S5P_JPGY_L);
पूर्ण

व्योम s5p_jpeg_x(व्योम __iomem *regs, अचिन्हित पूर्णांक x)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPGX_U);
	reg &= ~0xff;
	reg |= (x >> 8) & 0xff;
	ग_लिखोl(reg, regs + S5P_JPGX_U);

	reg = पढ़ोl(regs + S5P_JPGX_L);
	reg &= ~0xff;
	reg |= x & 0xff;
	ग_लिखोl(reg, regs + S5P_JPGX_L);
पूर्ण

व्योम s5p_jpeg_rst_पूर्णांक_enable(व्योम __iomem *regs, bool enable)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPGINTSE);
	reg &= ~S5P_RSTm_INT_EN_MASK;
	अगर (enable)
		reg |= S5P_RSTm_INT_EN;
	ग_लिखोl(reg, regs + S5P_JPGINTSE);
पूर्ण

व्योम s5p_jpeg_data_num_पूर्णांक_enable(व्योम __iomem *regs, bool enable)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPGINTSE);
	reg &= ~S5P_DATA_NUM_INT_EN_MASK;
	अगर (enable)
		reg |= S5P_DATA_NUM_INT_EN;
	ग_लिखोl(reg, regs + S5P_JPGINTSE);
पूर्ण

व्योम s5p_jpeg_final_mcu_num_पूर्णांक_enable(व्योम __iomem *regs, bool enbl)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPGINTSE);
	reg &= ~S5P_FINAL_MCU_NUM_INT_EN_MASK;
	अगर (enbl)
		reg |= S5P_FINAL_MCU_NUM_INT_EN;
	ग_लिखोl(reg, regs + S5P_JPGINTSE);
पूर्ण

पूर्णांक s5p_jpeg_समयr_stat(व्योम __iomem *regs)
अणु
	वापस (पूर्णांक)((पढ़ोl(regs + S5P_JPG_TIMER_ST) & S5P_TIMER_INT_STAT_MASK)
		     >> S5P_TIMER_INT_STAT_SHIFT);
पूर्ण

व्योम s5p_jpeg_clear_समयr_stat(व्योम __iomem *regs)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_TIMER_SE);
	reg &= ~S5P_TIMER_INT_STAT_MASK;
	ग_लिखोl(reg, regs + S5P_JPG_TIMER_SE);
पूर्ण

व्योम s5p_jpeg_enc_stream_पूर्णांक(व्योम __iomem *regs, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_ENC_STREAM_INTSE);
	reg &= ~S5P_ENC_STREAM_BOUND_MASK;
	reg |= S5P_ENC_STREAM_INT_EN;
	reg |= size & S5P_ENC_STREAM_BOUND_MASK;
	ग_लिखोl(reg, regs + S5P_JPG_ENC_STREAM_INTSE);
पूर्ण

पूर्णांक s5p_jpeg_enc_stream_stat(व्योम __iomem *regs)
अणु
	वापस (पूर्णांक)(पढ़ोl(regs + S5P_JPG_ENC_STREAM_INTST) &
		     S5P_ENC_STREAM_INT_STAT_MASK);
पूर्ण

व्योम s5p_jpeg_clear_enc_stream_stat(व्योम __iomem *regs)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_ENC_STREAM_INTSE);
	reg &= ~S5P_ENC_STREAM_INT_MASK;
	ग_लिखोl(reg, regs + S5P_JPG_ENC_STREAM_INTSE);
पूर्ण

व्योम s5p_jpeg_outक्रमm_raw(व्योम __iomem *regs, अचिन्हित दीर्घ क्रमmat)
अणु
	अचिन्हित दीर्घ reg, f;

	f = S5P_DEC_OUT_FORMAT_422;
	अगर (क्रमmat == S5P_JPEG_RAW_OUT_422)
		f = S5P_DEC_OUT_FORMAT_422;
	अन्यथा अगर (क्रमmat == S5P_JPEG_RAW_OUT_420)
		f = S5P_DEC_OUT_FORMAT_420;
	reg = पढ़ोl(regs + S5P_JPG_OUTFORM);
	reg &= ~S5P_DEC_OUT_FORMAT_MASK;
	reg |= f;
	ग_लिखोl(reg, regs + S5P_JPG_OUTFORM);
पूर्ण

व्योम s5p_jpeg_jpgadr(व्योम __iomem *regs, अचिन्हित दीर्घ addr)
अणु
	ग_लिखोl(addr, regs + S5P_JPG_JPGADR);
पूर्ण

व्योम s5p_jpeg_imgadr(व्योम __iomem *regs, अचिन्हित दीर्घ addr)
अणु
	ग_लिखोl(addr, regs + S5P_JPG_IMGADR);
पूर्ण

व्योम s5p_jpeg_coef(व्योम __iomem *regs, अचिन्हित पूर्णांक i,
			     अचिन्हित पूर्णांक j, अचिन्हित पूर्णांक coef)
अणु
	अचिन्हित दीर्घ reg;

	reg = पढ़ोl(regs + S5P_JPG_COEF(i));
	reg &= ~S5P_COEFn_MASK(j);
	reg |= (coef << S5P_COEFn_SHIFT(j)) & S5P_COEFn_MASK(j);
	ग_लिखोl(reg, regs + S5P_JPG_COEF(i));
पूर्ण

व्योम s5p_jpeg_start(व्योम __iomem *regs)
अणु
	ग_लिखोl(1, regs + S5P_JSTART);
पूर्ण

पूर्णांक s5p_jpeg_result_stat_ok(व्योम __iomem *regs)
अणु
	वापस (पूर्णांक)((पढ़ोl(regs + S5P_JPGINTST) & S5P_RESULT_STAT_MASK)
		     >> S5P_RESULT_STAT_SHIFT);
पूर्ण

पूर्णांक s5p_jpeg_stream_stat_ok(व्योम __iomem *regs)
अणु
	वापस !(पूर्णांक)((पढ़ोl(regs + S5P_JPGINTST) & S5P_STREAM_STAT_MASK)
		      >> S5P_STREAM_STAT_SHIFT);
पूर्ण

व्योम s5p_jpeg_clear_पूर्णांक(व्योम __iomem *regs)
अणु
	पढ़ोl(regs + S5P_JPGINTST);
	ग_लिखोl(S5P_INT_RELEASE, regs + S5P_JPGCOM);
	पढ़ोl(regs + S5P_JPGOPR);
पूर्ण

अचिन्हित पूर्णांक s5p_jpeg_compressed_size(व्योम __iomem *regs)
अणु
	अचिन्हित दीर्घ jpeg_size = 0;

	jpeg_size |= (पढ़ोl(regs + S5P_JPGCNT_U) & 0xff) << 16;
	jpeg_size |= (पढ़ोl(regs + S5P_JPGCNT_M) & 0xff) << 8;
	jpeg_size |= (पढ़ोl(regs + S5P_JPGCNT_L) & 0xff);

	वापस (अचिन्हित पूर्णांक)jpeg_size;
पूर्ण
