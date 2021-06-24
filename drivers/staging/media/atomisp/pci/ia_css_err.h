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

#अगर_अघोषित __IA_CSS_ERR_H
#घोषणा __IA_CSS_ERR_H

/* @file
 * This file contains possible वापस values क्रम most
 * functions in the CSS-API.
 */

/* FW warnings. This क्रमागत contains a value क्रम each warning that
 * the SP FW could indicate potential perक्रमmance issue
 */
क्रमागत ia_css_fw_warning अणु
	IA_CSS_FW_WARNING_NONE,
	IA_CSS_FW_WARNING_ISYS_QUEUE_FULL, /* < CSS प्रणाली delayed because of insufficient space in the ISys queue.
		This warning can be aव्योमed by de-queuing ISYS buffers more समयly. */
	IA_CSS_FW_WARNING_PSYS_QUEUE_FULL, /* < CSS प्रणाली delayed because of insufficient space in the PSys queue.
		This warning can be aव्योमed by de-queuing PSYS buffers more समयly. */
	IA_CSS_FW_WARNING_CIRCBUF_ALL_LOCKED, /* < CSS प्रणाली delayed because of insufficient available buffers.
		This warning can be aव्योमed by unlocking locked frame-buffers more समयly. */
	IA_CSS_FW_WARNING_EXP_ID_LOCKED, /* < Exposure ID skipped because the frame associated to it was still locked.
		This warning can be aव्योमed by unlocking locked frame-buffers more समयly. */
	IA_CSS_FW_WARNING_TAG_EXP_ID_FAILED, /* < Exposure ID cannot be found on the circular buffer.
		This warning can be aव्योमed by unlocking locked frame-buffers more समयly. */
	IA_CSS_FW_WARNING_FRAME_PARAM_MISMATCH, /* < Frame and param pair mismatched in tagger.
		This warning can be aव्योमed by providing a param set क्रम each frame. */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_ERR_H */
