<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/drivers/media/platक्रमm/s5p-jpeg/jpeg-hw-exynos3250.h
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 */
#अगर_अघोषित JPEG_HW_EXYNOS3250_H_
#घोषणा JPEG_HW_EXYNOS3250_H_

#समावेश <linux/पन.स>
#समावेश <linux/videodev2.h>

#समावेश "jpeg-regs.h"

व्योम exynos3250_jpeg_reset(व्योम __iomem *regs);
व्योम exynos3250_jpeg_घातeron(व्योम __iomem *regs);
व्योम exynos3250_jpeg_set_dma_num(व्योम __iomem *regs);
व्योम exynos3250_jpeg_clk_set(व्योम __iomem *base);
व्योम exynos3250_jpeg_input_raw_fmt(व्योम __iomem *regs, अचिन्हित पूर्णांक fmt);
व्योम exynos3250_jpeg_output_raw_fmt(व्योम __iomem *regs, अचिन्हित पूर्णांक fmt);
व्योम exynos3250_jpeg_set_y16(व्योम __iomem *regs, bool y16);
व्योम exynos3250_jpeg_proc_mode(व्योम __iomem *regs, अचिन्हित पूर्णांक mode);
व्योम exynos3250_jpeg_subsampling_mode(व्योम __iomem *regs, अचिन्हित पूर्णांक mode);
अचिन्हित पूर्णांक exynos3250_jpeg_get_subsampling_mode(व्योम __iomem *regs);
व्योम exynos3250_jpeg_dri(व्योम __iomem *regs, अचिन्हित पूर्णांक dri);
व्योम exynos3250_jpeg_qtbl(व्योम __iomem *regs, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक n);
व्योम exynos3250_jpeg_htbl_ac(व्योम __iomem *regs, अचिन्हित पूर्णांक t);
व्योम exynos3250_jpeg_htbl_dc(व्योम __iomem *regs, अचिन्हित पूर्णांक t);
व्योम exynos3250_jpeg_set_y(व्योम __iomem *regs, अचिन्हित पूर्णांक y);
व्योम exynos3250_jpeg_set_x(व्योम __iomem *regs, अचिन्हित पूर्णांक x);
व्योम exynos3250_jpeg_पूर्णांकerrupts_enable(व्योम __iomem *regs);
व्योम exynos3250_jpeg_enc_stream_bound(व्योम __iomem *regs, अचिन्हित पूर्णांक size);
व्योम exynos3250_jpeg_outक्रमm_raw(व्योम __iomem *regs, अचिन्हित दीर्घ क्रमmat);
व्योम exynos3250_jpeg_jpgadr(व्योम __iomem *regs, अचिन्हित पूर्णांक addr);
व्योम exynos3250_jpeg_imgadr(व्योम __iomem *regs, काष्ठा s5p_jpeg_addr *img_addr);
व्योम exynos3250_jpeg_stride(व्योम __iomem *regs, अचिन्हित पूर्णांक img_fmt,
			    अचिन्हित पूर्णांक width);
व्योम exynos3250_jpeg_offset(व्योम __iomem *regs, अचिन्हित पूर्णांक x_offset,
				अचिन्हित पूर्णांक y_offset);
व्योम exynos3250_jpeg_coef(व्योम __iomem *base, अचिन्हित पूर्णांक mode);
व्योम exynos3250_jpeg_start(व्योम __iomem *regs);
व्योम exynos3250_jpeg_rstart(व्योम __iomem *regs);
अचिन्हित पूर्णांक exynos3250_jpeg_get_पूर्णांक_status(व्योम __iomem *regs);
व्योम exynos3250_jpeg_clear_पूर्णांक_status(व्योम __iomem *regs,
						अचिन्हित पूर्णांक value);
अचिन्हित पूर्णांक exynos3250_jpeg_operating(व्योम __iomem *regs);
अचिन्हित पूर्णांक exynos3250_jpeg_compressed_size(व्योम __iomem *regs);
व्योम exynos3250_jpeg_dec_stream_size(व्योम __iomem *regs, अचिन्हित पूर्णांक size);
व्योम exynos3250_jpeg_dec_scaling_ratio(व्योम __iomem *regs, अचिन्हित पूर्णांक sratio);
व्योम exynos3250_jpeg_set_समयr(व्योम __iomem *regs, अचिन्हित पूर्णांक समय_value);
अचिन्हित पूर्णांक exynos3250_jpeg_get_समयr_status(व्योम __iomem *regs);
व्योम exynos3250_jpeg_set_समयr_status(व्योम __iomem *regs);
व्योम exynos3250_jpeg_clear_समयr_status(व्योम __iomem *regs);

#पूर्ण_अगर /* JPEG_HW_EXYNOS3250_H_ */
