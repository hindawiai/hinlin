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

#अगर_अघोषित _IA_CSS_BUFQ_COMM_H
#घोषणा _IA_CSS_BUFQ_COMM_H

#समावेश "system_global.h"

क्रमागत sh_css_queue_id अणु
	SH_CSS_INVALID_QUEUE_ID     = -1,
	SH_CSS_QUEUE_A_ID = 0,
	SH_CSS_QUEUE_B_ID,
	SH_CSS_QUEUE_C_ID,
	SH_CSS_QUEUE_D_ID,
	SH_CSS_QUEUE_E_ID,
	SH_CSS_QUEUE_F_ID,
	SH_CSS_QUEUE_G_ID,
	SH_CSS_QUEUE_H_ID, /* क्रम metadata */

#घोषणा SH_CSS_MAX_NUM_QUEUES (SH_CSS_QUEUE_H_ID + 1)

पूर्ण;

#घोषणा SH_CSS_MAX_DYNAMIC_BUFFERS_PER_THREAD SH_CSS_MAX_NUM_QUEUES
/* क्रम now we अटलaly assign queue 0 & 1 to parameter sets */
#घोषणा IA_CSS_PARAMETER_SET_QUEUE_ID SH_CSS_QUEUE_A_ID
#घोषणा IA_CSS_PER_FRAME_PARAMETER_SET_QUEUE_ID SH_CSS_QUEUE_B_ID

#पूर्ण_अगर
