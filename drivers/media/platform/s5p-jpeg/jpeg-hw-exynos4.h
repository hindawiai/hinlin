<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 *
 * Header file of the रेजिस्टर पूर्णांकerface क्रम JPEG driver on Exynos4x12.
*/

#अगर_अघोषित JPEG_HW_EXYNOS4_H_
#घोषणा JPEG_HW_EXYNOS4_H_

व्योम exynos4_jpeg_sw_reset(व्योम __iomem *base);
व्योम exynos4_jpeg_set_enc_dec_mode(व्योम __iomem *base, अचिन्हित पूर्णांक mode);
व्योम __exynos4_jpeg_set_img_fmt(व्योम __iomem *base, अचिन्हित पूर्णांक img_fmt,
				अचिन्हित पूर्णांक version);
व्योम __exynos4_jpeg_set_enc_out_fmt(व्योम __iomem *base, अचिन्हित पूर्णांक out_fmt,
				    अचिन्हित पूर्णांक version);
व्योम exynos4_jpeg_set_enc_tbl(व्योम __iomem *base);
व्योम exynos4_jpeg_set_पूर्णांकerrupt(व्योम __iomem *base, अचिन्हित पूर्णांक version);
अचिन्हित पूर्णांक exynos4_jpeg_get_पूर्णांक_status(व्योम __iomem *base);
व्योम exynos4_jpeg_set_huf_table_enable(व्योम __iomem *base, पूर्णांक value);
व्योम exynos4_jpeg_set_sys_पूर्णांक_enable(व्योम __iomem *base, पूर्णांक value);
व्योम exynos4_jpeg_set_stream_buf_address(व्योम __iomem *base,
					 अचिन्हित पूर्णांक address);
व्योम exynos4_jpeg_set_stream_size(व्योम __iomem *base,
		अचिन्हित पूर्णांक x_value, अचिन्हित पूर्णांक y_value);
व्योम exynos4_jpeg_set_frame_buf_address(व्योम __iomem *base,
				काष्ठा s5p_jpeg_addr *jpeg_addr);
व्योम exynos4_jpeg_set_encode_tbl_select(व्योम __iomem *base,
		क्रमागत exynos4_jpeg_img_quality_level level);
व्योम exynos4_jpeg_set_dec_components(व्योम __iomem *base, पूर्णांक n);
व्योम exynos4_jpeg_select_dec_q_tbl(व्योम __iomem *base, अक्षर c, अक्षर x);
व्योम exynos4_jpeg_select_dec_h_tbl(व्योम __iomem *base, अक्षर c, अक्षर x);
व्योम exynos4_jpeg_set_encode_hoff_cnt(व्योम __iomem *base, अचिन्हित पूर्णांक fmt);
व्योम exynos4_jpeg_set_dec_bitstream_size(व्योम __iomem *base, अचिन्हित पूर्णांक size);
अचिन्हित पूर्णांक exynos4_jpeg_get_stream_size(व्योम __iomem *base);
व्योम exynos4_jpeg_get_frame_size(व्योम __iomem *base,
			अचिन्हित पूर्णांक *width, अचिन्हित पूर्णांक *height);
अचिन्हित पूर्णांक exynos4_jpeg_get_frame_fmt(व्योम __iomem *base);
अचिन्हित पूर्णांक exynos4_jpeg_get_fअगरo_status(व्योम __iomem *base);
व्योम exynos4_jpeg_set_समयr_count(व्योम __iomem *base, अचिन्हित पूर्णांक size);

#पूर्ण_अगर /* JPEG_HW_EXYNOS4_H_ */
