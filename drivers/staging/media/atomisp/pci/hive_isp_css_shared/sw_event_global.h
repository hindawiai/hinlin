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

#अगर_अघोषित __SW_EVENT_GLOBAL_H_INCLUDED__
#घोषणा __SW_EVENT_GLOBAL_H_INCLUDED__

#घोषणा MAX_NR_OF_PAYLOADS_PER_SW_EVENT 4

क्रमागत ia_css_psys_sw_event अणु
	IA_CSS_PSYS_SW_EVENT_BUFFER_ENQUEUED, /* from host to SP */
	IA_CSS_PSYS_SW_EVENT_BUFFER_DEQUEUED, /* from SP to host */
	IA_CSS_PSYS_SW_EVENT_EVENT_DEQUEUED, /* from SP to host, one way only */
	IA_CSS_PSYS_SW_EVENT_START_STREAM,
	IA_CSS_PSYS_SW_EVENT_STOP_STREAM,
	IA_CSS_PSYS_SW_EVENT_MIPI_BUFFERS_READY,
	IA_CSS_PSYS_SW_EVENT_UNLOCK_RAW_BUFFER,
	IA_CSS_PSYS_SW_EVENT_STAGE_ENABLE_DISABLE /* क्रम extension state change enable/disable */
पूर्ण;

क्रमागत ia_css_isys_sw_event अणु
	IA_CSS_ISYS_SW_EVENT_EVENT_DEQUEUED
पूर्ण;

#पूर्ण_अगर /* __SW_EVENT_GLOBAL_H_INCLUDED__ */
