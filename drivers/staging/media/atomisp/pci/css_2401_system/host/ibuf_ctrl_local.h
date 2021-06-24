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

#अगर_अघोषित __IBUF_CTRL_LOCAL_H_INCLUDED__
#घोषणा __IBUF_CTRL_LOCAL_H_INCLUDED__

#समावेश "ibuf_ctrl_global.h"
#समावेश "ibuf_ctrl_local.h"

प्रकार काष्ठा ibuf_ctrl_proc_state_s	ibuf_ctrl_proc_state_t;
प्रकार काष्ठा ibuf_ctrl_state_s		ibuf_ctrl_state_t;

काष्ठा ibuf_ctrl_proc_state_s अणु
	hrt_data num_items;
	hrt_data num_stores;
	hrt_data dma_channel;
	hrt_data dma_command;
	hrt_data ibuf_st_addr;
	hrt_data ibuf_stride;
	hrt_data ibuf_end_addr;
	hrt_data dest_st_addr;
	hrt_data dest_stride;
	hrt_data dest_end_addr;
	hrt_data sync_frame;
	hrt_data sync_command;
	hrt_data store_command;
	hrt_data shअगरt_वापसed_items;
	hrt_data elems_ibuf;
	hrt_data elems_dest;
	hrt_data cur_stores;
	hrt_data cur_acks;
	hrt_data cur_s2m_ibuf_addr;
	hrt_data cur_dma_ibuf_addr;
	hrt_data cur_dma_dest_addr;
	hrt_data cur_isp_dest_addr;
	hrt_data dma_cmds_send;
	hrt_data मुख्य_cntrl_state;
	hrt_data dma_sync_state;
	hrt_data isp_sync_state;
पूर्ण;

काष्ठा ibuf_ctrl_state_s अणु
	hrt_data	recalc_words;
	hrt_data	arbiters;
	ibuf_ctrl_proc_state_t	proc_state[N_STREAM2MMIO_SID_ID];
पूर्ण;

#पूर्ण_अगर /* __IBUF_CTRL_LOCAL_H_INCLUDED__ */
