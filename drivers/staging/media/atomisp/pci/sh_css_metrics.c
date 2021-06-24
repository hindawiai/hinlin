<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "assert_support.h"
#समावेश "sh_css_metrics.h"

#समावेश "sp.h"
#समावेश "isp.h"

#समावेश "sh_css_internal.h"

#घोषणा MULTIPLE_PCS 0
#घोषणा SUSPEND      0
#घोषणा NOF_PCS      1
#घोषणा RESUME_MASK  0x8
#घोषणा STOP_MASK    0x0

अटल bool pc_histogram_enabled;
अटल काष्ठा sh_css_pc_histogram *isp_histogram;
अटल काष्ठा sh_css_pc_histogram *sp_histogram;

काष्ठा sh_css_metrics sh_css_metrics;

व्योम
sh_css_metrics_start_frame(व्योम)
अणु
	sh_css_metrics.frame_metrics.num_frames++;
पूर्ण

अटल व्योम
clear_histogram(काष्ठा sh_css_pc_histogram *histogram)
अणु
	अचिन्हित पूर्णांक i;

	निश्चित(histogram);

	क्रम (i = 0; i < histogram->length; i++) अणु
		histogram->run[i] = 0;
		histogram->stall[i] = 0;
		histogram->msink[i] = 0xFFFF;
	पूर्ण
पूर्ण

व्योम
sh_css_metrics_enable_pc_histogram(bool enable)
अणु
	pc_histogram_enabled = enable;
पूर्ण

अटल व्योम
make_histogram(काष्ठा sh_css_pc_histogram *histogram, अचिन्हित पूर्णांक length)
अणु
	निश्चित(histogram);

	अगर (histogram->length)
		वापस;
	अगर (histogram->run)
		वापस;
	histogram->run = kvदो_स्मृति(length * माप(*histogram->run),
				  GFP_KERNEL);
	अगर (!histogram->run)
		वापस;
	histogram->stall = kvदो_स्मृति(length * माप(*histogram->stall),
				    GFP_KERNEL);
	अगर (!histogram->stall)
		वापस;
	histogram->msink = kvदो_स्मृति(length * माप(*histogram->msink),
				    GFP_KERNEL);
	अगर (!histogram->msink)
		वापस;

	histogram->length = length;
	clear_histogram(histogram);
पूर्ण

अटल व्योम
insert_binary_metrics(काष्ठा sh_css_binary_metrics **l,
		      काष्ठा sh_css_binary_metrics *metrics)
अणु
	निश्चित(l);
	निश्चित(*l);
	निश्चित(metrics);

	क्रम (; *l; l = &(*l)->next)
		अगर (*l == metrics)
			वापस;

	*l = metrics;
	metrics->next = शून्य;
पूर्ण

व्योम
sh_css_metrics_start_binary(काष्ठा sh_css_binary_metrics *metrics)
अणु
	निश्चित(metrics);

	अगर (!pc_histogram_enabled)
		वापस;

	isp_histogram = &metrics->isp_histogram;
	sp_histogram = &metrics->sp_histogram;
	make_histogram(isp_histogram, ISP_PMEM_DEPTH);
	make_histogram(sp_histogram, SP_PMEM_DEPTH);
	insert_binary_metrics(&sh_css_metrics.binary_metrics, metrics);
पूर्ण

व्योम
sh_css_metrics_sample_pcs(व्योम)
अणु
	bool stall;
	अचिन्हित पूर्णांक pc;
	अचिन्हित पूर्णांक msink;

#अगर SUSPEND
	अचिन्हित पूर्णांक sc = 0;
	अचिन्हित पूर्णांक stopped_sc = 0;
	अचिन्हित पूर्णांक resume_sc = 0;
#पूर्ण_अगर

#अगर MULTIPLE_PCS
	पूर्णांक i;
	अचिन्हित पूर्णांक pc_tab[NOF_PCS];

	क्रम (i = 0; i < NOF_PCS; i++)
		pc_tab[i] = 0;
#पूर्ण_अगर

	अगर (!pc_histogram_enabled)
		वापस;

	अगर (isp_histogram) अणु
#अगर SUSPEND
		/* STOP the ISP */
		isp_ctrl_store(ISP0_ID, ISP_SC_REG, STOP_MASK);
#पूर्ण_अगर
		msink = isp_ctrl_load(ISP0_ID, ISP_CTRL_SINK_REG);
#अगर MULTIPLE_PCS
		क्रम (i = 0; i < NOF_PCS; i++)
			pc_tab[i] = isp_ctrl_load(ISP0_ID, ISP_PC_REG);
#अन्यथा
		pc = isp_ctrl_load(ISP0_ID, ISP_PC_REG);
#पूर्ण_अगर

#अगर SUSPEND
		/* RESUME the ISP */
		isp_ctrl_store(ISP0_ID, ISP_SC_REG, RESUME_MASK);
#पूर्ण_अगर
		isp_histogram->msink[pc] &= msink;
		stall = (msink != 0x7FF);

		अगर (stall)
			isp_histogram->stall[pc]++;
		अन्यथा
			isp_histogram->run[pc]++;
	पूर्ण

	अगर (sp_histogram && 0) अणु
		msink = sp_ctrl_load(SP0_ID, SP_CTRL_SINK_REG);
		pc = sp_ctrl_load(SP0_ID, SP_PC_REG);
		sp_histogram->msink[pc] &= msink;
		stall = (msink != 0x7FF);
		अगर (stall)
			sp_histogram->stall[pc]++;
		अन्यथा
			sp_histogram->run[pc]++;
	पूर्ण
पूर्ण
