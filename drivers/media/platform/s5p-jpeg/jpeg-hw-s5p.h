<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/drivers/media/platक्रमm/s5p-jpeg/jpeg-hw.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */
#अगर_अघोषित JPEG_HW_S5P_H_
#घोषणा JPEG_HW_S5P_H_

#समावेश <linux/पन.स>
#समावेश <linux/videodev2.h>

#समावेश "jpeg-regs.h"

#घोषणा S5P_JPEG_MIN_WIDTH		32
#घोषणा S5P_JPEG_MIN_HEIGHT		32
#घोषणा S5P_JPEG_MAX_WIDTH		8192
#घोषणा S5P_JPEG_MAX_HEIGHT		8192
#घोषणा S5P_JPEG_RAW_IN_565		0
#घोषणा S5P_JPEG_RAW_IN_422		1
#घोषणा S5P_JPEG_RAW_OUT_422		0
#घोषणा S5P_JPEG_RAW_OUT_420		1

व्योम s5p_jpeg_reset(व्योम __iomem *regs);
व्योम s5p_jpeg_घातeron(व्योम __iomem *regs);
व्योम s5p_jpeg_input_raw_mode(व्योम __iomem *regs, अचिन्हित दीर्घ mode);
व्योम s5p_jpeg_proc_mode(व्योम __iomem *regs, अचिन्हित दीर्घ mode);
व्योम s5p_jpeg_subsampling_mode(व्योम __iomem *regs, अचिन्हित पूर्णांक mode);
अचिन्हित पूर्णांक s5p_jpeg_get_subsampling_mode(व्योम __iomem *regs);
व्योम s5p_jpeg_dri(व्योम __iomem *regs, अचिन्हित पूर्णांक dri);
व्योम s5p_jpeg_qtbl(व्योम __iomem *regs, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक n);
व्योम s5p_jpeg_htbl_ac(व्योम __iomem *regs, अचिन्हित पूर्णांक t);
व्योम s5p_jpeg_htbl_dc(व्योम __iomem *regs, अचिन्हित पूर्णांक t);
व्योम s5p_jpeg_y(व्योम __iomem *regs, अचिन्हित पूर्णांक y);
व्योम s5p_jpeg_x(व्योम __iomem *regs, अचिन्हित पूर्णांक x);
व्योम s5p_jpeg_rst_पूर्णांक_enable(व्योम __iomem *regs, bool enable);
व्योम s5p_jpeg_data_num_पूर्णांक_enable(व्योम __iomem *regs, bool enable);
व्योम s5p_jpeg_final_mcu_num_पूर्णांक_enable(व्योम __iomem *regs, bool enbl);
पूर्णांक s5p_jpeg_समयr_stat(व्योम __iomem *regs);
व्योम s5p_jpeg_clear_समयr_stat(व्योम __iomem *regs);
व्योम s5p_jpeg_enc_stream_पूर्णांक(व्योम __iomem *regs, अचिन्हित दीर्घ size);
पूर्णांक s5p_jpeg_enc_stream_stat(व्योम __iomem *regs);
व्योम s5p_jpeg_clear_enc_stream_stat(व्योम __iomem *regs);
व्योम s5p_jpeg_outक्रमm_raw(व्योम __iomem *regs, अचिन्हित दीर्घ क्रमmat);
व्योम s5p_jpeg_jpgadr(व्योम __iomem *regs, अचिन्हित दीर्घ addr);
व्योम s5p_jpeg_imgadr(व्योम __iomem *regs, अचिन्हित दीर्घ addr);
व्योम s5p_jpeg_coef(व्योम __iomem *regs, अचिन्हित पूर्णांक i,
			     अचिन्हित पूर्णांक j, अचिन्हित पूर्णांक coef);
व्योम s5p_jpeg_start(व्योम __iomem *regs);
पूर्णांक s5p_jpeg_result_stat_ok(व्योम __iomem *regs);
पूर्णांक s5p_jpeg_stream_stat_ok(व्योम __iomem *regs);
व्योम s5p_jpeg_clear_पूर्णांक(व्योम __iomem *regs);
अचिन्हित पूर्णांक s5p_jpeg_compressed_size(व्योम __iomem *regs);

#पूर्ण_अगर /* JPEG_HW_S5P_H_ */
