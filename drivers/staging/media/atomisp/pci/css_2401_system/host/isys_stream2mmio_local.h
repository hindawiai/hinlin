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

#अगर_अघोषित __ISYS_STREAM2MMIO_LOCAL_H_INCLUDED__
#घोषणा __ISYS_STREAM2MMIO_LOCAL_H_INCLUDED__

#समावेश "isys_stream2mmio_global.h"

प्रकार काष्ठा stream2mmio_state_s		stream2mmio_state_t;
प्रकार काष्ठा stream2mmio_sid_state_s	stream2mmio_sid_state_t;

काष्ठा stream2mmio_sid_state_s अणु
	hrt_data rcv_ack;
	hrt_data pix_width_id;
	hrt_data start_addr;
	hrt_data end_addr;
	hrt_data strides;
	hrt_data num_items;
	hrt_data block_when_no_cmd;
पूर्ण;

काष्ठा stream2mmio_state_s अणु
	stream2mmio_sid_state_t	sid_state[N_STREAM2MMIO_SID_ID];
पूर्ण;
#पूर्ण_अगर /* __ISYS_STREAM2MMIO_LOCAL_H_INCLUDED__ */
