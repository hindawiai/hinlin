<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_S3A_HOST_H
#घोषणा __IA_CSS_S3A_HOST_H

#समावेश "ia_css_s3a_types.h"
#समावेश "ia_css_s3a_param.h"
#समावेश "bh/bh_2/ia_css_bh.host.h"

बाह्य स्थिर काष्ठा ia_css_3a_config शेष_3a_config;

व्योम
ia_css_s3a_configure(
    अचिन्हित पूर्णांक raw_bit_depth);

व्योम
ia_css_s3a_encode(
    काष्ठा sh_css_isp_s3a_params *to,
    स्थिर काष्ठा ia_css_3a_config *from,
    अचिन्हित पूर्णांक size);

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_ae_dump(
    स्थिर काष्ठा sh_css_isp_ae_params *ae,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_awb_dump(
    स्थिर काष्ठा sh_css_isp_awb_params *awb,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_af_dump(
    स्थिर काष्ठा sh_css_isp_af_params *af,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_s3a_dump(
    स्थिर काष्ठा sh_css_isp_s3a_params *s3a,
    अचिन्हित पूर्णांक level);

व्योम
ia_css_s3a_debug_dtrace(
    स्थिर काष्ठा ia_css_3a_config *config,
    अचिन्हित पूर्णांक level);
#पूर्ण_अगर

व्योम
ia_css_s3a_hmem_decode(
    काष्ठा ia_css_3a_statistics *host_stats,
    स्थिर काष्ठा ia_css_bh_table *hmem_buf);

व्योम
ia_css_s3a_dmem_decode(
    काष्ठा ia_css_3a_statistics *host_stats,
    स्थिर काष्ठा ia_css_3a_output *isp_stats);

व्योम
ia_css_s3a_vmem_decode(
    काष्ठा ia_css_3a_statistics *host_stats,
    स्थिर u16 *isp_stats_hi,
    स्थिर uपूर्णांक16_t *isp_stats_lo);

#पूर्ण_अगर /* __IA_CSS_S3A_HOST_H */
