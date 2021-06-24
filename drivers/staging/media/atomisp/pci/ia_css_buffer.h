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

#अगर_अघोषित __IA_CSS_BUFFER_H
#घोषणा __IA_CSS_BUFFER_H

/* @file
 * This file contains dataकाष्ठाures and types क्रम buffers used in CSS
 */

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_timer.h"

/* Enumeration of buffer types. Buffers can be queued and de-queued
 *  to hand them over between IA and ISP.
 */
क्रमागत ia_css_buffer_type अणु
	IA_CSS_BUFFER_TYPE_INVALID = -1,
	IA_CSS_BUFFER_TYPE_3A_STATISTICS = 0,
	IA_CSS_BUFFER_TYPE_DIS_STATISTICS,
	IA_CSS_BUFFER_TYPE_LACE_STATISTICS,
	IA_CSS_BUFFER_TYPE_INPUT_FRAME,
	IA_CSS_BUFFER_TYPE_OUTPUT_FRAME,
	IA_CSS_BUFFER_TYPE_SEC_OUTPUT_FRAME,
	IA_CSS_BUFFER_TYPE_VF_OUTPUT_FRAME,
	IA_CSS_BUFFER_TYPE_SEC_VF_OUTPUT_FRAME,
	IA_CSS_BUFFER_TYPE_RAW_OUTPUT_FRAME,
	IA_CSS_BUFFER_TYPE_CUSTOM_INPUT,
	IA_CSS_BUFFER_TYPE_CUSTOM_OUTPUT,
	IA_CSS_BUFFER_TYPE_METADATA,
	IA_CSS_BUFFER_TYPE_PARAMETER_SET,
	IA_CSS_BUFFER_TYPE_PER_FRAME_PARAMETER_SET,
	IA_CSS_NUM_DYNAMIC_BUFFER_TYPE,
	IA_CSS_NUM_BUFFER_TYPE
पूर्ण;

/* Driver API is not SP/ISP visible, 64 bit types not supported on hivecc */

/* Buffer काष्ठाure. This is a container काष्ठाure that enables content
 *  independent buffer queues and access functions.
 */
काष्ठा ia_css_buffer अणु
	क्रमागत ia_css_buffer_type type; /** Buffer type. */
	अचिन्हित पूर्णांक exp_id;
	/** exposure id क्रम this buffer; 0 = not available
	     see ia_css_event_खुला.h क्रम more detail. */
	जोड़ अणु
		काष्ठा ia_css_isp_3a_statistics
			*stats_3a;    /** 3A statistics & optionally RGBY statistics. */
		काष्ठा ia_css_isp_dvs_statistics *stats_dvs;   /** DVS statistics. */
		काष्ठा ia_css_isp_skc_dvs_statistics *stats_skc_dvs;  /** SKC DVS statistics. */
		काष्ठा ia_css_frame              *frame;       /** Frame buffer. */
		काष्ठा ia_css_acc_param          *custom_data; /** Custom buffer. */
		काष्ठा ia_css_metadata           *metadata;    /** Sensor metadata. */
	पूर्ण data; /** Buffer data poपूर्णांकer. */
	u64 driver_cookie; /** cookie क्रम the driver */
	काष्ठा ia_css_समय_meas
		timing_data; /** timing data (पढ़ोings from the समयr) */
	काष्ठा ia_css_घड़ी_प्रकारick
		isys_eof_घड़ी_प्रकारick; /** ISYS's end of frame समयr tick*/
पूर्ण;

/* @brief Dequeue param buffers from sp2host_queue
 *
 * @वापस                                       None
 *
 * This function must be called at every driver पूर्णांकerrupt handler to prevent
 * overflow of sp2host_queue.
 */
व्योम
ia_css_dequeue_param_buffers(व्योम);

#पूर्ण_अगर /* __IA_CSS_BUFFER_H */
