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

#अगर_अघोषित _SH_CSS_METRICS_H_
#घोषणा _SH_CSS_METRICS_H_

#समावेश <type_support.h>

काष्ठा sh_css_pc_histogram अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक *run;
	अचिन्हित पूर्णांक *stall;
	अचिन्हित पूर्णांक *msink;
पूर्ण;

काष्ठा sh_css_binary_metrics अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक id;
	काष्ठा sh_css_pc_histogram isp_histogram;
	काष्ठा sh_css_pc_histogram sp_histogram;
	काष्ठा sh_css_binary_metrics *next;
पूर्ण;

काष्ठा ia_css_frame_metrics अणु
	अचिन्हित पूर्णांक num_frames;
पूर्ण;

काष्ठा sh_css_metrics अणु
	काष्ठा sh_css_binary_metrics *binary_metrics;
	काष्ठा ia_css_frame_metrics   frame_metrics;
पूर्ण;

बाह्य काष्ठा sh_css_metrics sh_css_metrics;

/* includes ia_css_binary.h, which depends on sh_css_metrics.h */
#समावेश "ia_css_types.h"

/* Sample ISP and SP pc and add to histogram */
व्योम sh_css_metrics_enable_pc_histogram(bool enable);
व्योम sh_css_metrics_start_frame(व्योम);
व्योम sh_css_metrics_start_binary(काष्ठा sh_css_binary_metrics *metrics);
व्योम sh_css_metrics_sample_pcs(व्योम);

#पूर्ण_अगर /* _SH_CSS_METRICS_H_ */
