<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

#अगर_अघोषित __FIFO_MONITOR_LOCAL_H_INCLUDED__
#घोषणा __FIFO_MONITOR_LOCAL_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "fifo_monitor_global.h"

#समावेश "hive_isp_css_defs.h"	/* ISP_STR_MON_PORT_SND_SP, ... */

#घोषणा _hive_str_mon_valid_offset   0
#घोषणा _hive_str_mon_accept_offset  1

#घोषणा	FIFO_CHANNEL_SP_VALID_MASK		0x55555555
#घोषणा	FIFO_CHANNEL_SP_VALID_B_MASK	0x00000055
#घोषणा	FIFO_CHANNEL_ISP_VALID_MASK		0x15555555
#घोषणा	FIFO_CHANNEL_MOD_VALID_MASK		0x55555555

प्रकार क्रमागत fअगरo_चयन अणु
	FIFO_SWITCH_IF,
	FIFO_SWITCH_GDC0,
	FIFO_SWITCH_GDC1,
	N_FIFO_SWITCH
पूर्ण fअगरo_चयन_t;

प्रकार क्रमागत fअगरo_channel अणु
	FIFO_CHANNEL_ISP0_TO_SP0,
	FIFO_CHANNEL_SP0_TO_ISP0,
	FIFO_CHANNEL_ISP0_TO_IF0,
	FIFO_CHANNEL_IF0_TO_ISP0,
	FIFO_CHANNEL_ISP0_TO_IF1,
	FIFO_CHANNEL_IF1_TO_ISP0,
	FIFO_CHANNEL_ISP0_TO_DMA0,
	FIFO_CHANNEL_DMA0_TO_ISP0,
	FIFO_CHANNEL_ISP0_TO_GDC0,
	FIFO_CHANNEL_GDC0_TO_ISP0,
	FIFO_CHANNEL_ISP0_TO_GDC1,
	FIFO_CHANNEL_GDC1_TO_ISP0,
	FIFO_CHANNEL_ISP0_TO_HOST0,
	FIFO_CHANNEL_HOST0_TO_ISP0,
	FIFO_CHANNEL_SP0_TO_IF0,
	FIFO_CHANNEL_IF0_TO_SP0,
	FIFO_CHANNEL_SP0_TO_IF1,
	FIFO_CHANNEL_IF1_TO_SP0,
	FIFO_CHANNEL_SP0_TO_IF2,
	FIFO_CHANNEL_IF2_TO_SP0,
	FIFO_CHANNEL_SP0_TO_DMA0,
	FIFO_CHANNEL_DMA0_TO_SP0,
	FIFO_CHANNEL_SP0_TO_GDC0,
	FIFO_CHANNEL_GDC0_TO_SP0,
	FIFO_CHANNEL_SP0_TO_GDC1,
	FIFO_CHANNEL_GDC1_TO_SP0,
	FIFO_CHANNEL_SP0_TO_HOST0,
	FIFO_CHANNEL_HOST0_TO_SP0,
	FIFO_CHANNEL_SP0_TO_STREAM2MEM0,
	FIFO_CHANNEL_STREAM2MEM0_TO_SP0,
	FIFO_CHANNEL_SP0_TO_INPUT_SYSTEM0,
	FIFO_CHANNEL_INPUT_SYSTEM0_TO_SP0,
	/*
	 * No clue what this is
	 *
		FIFO_CHANNEL_SP0_TO_IRQ0,
		FIFO_CHANNEL_IRQ0_TO_SP0,
	 */
	N_FIFO_CHANNEL
पूर्ण fअगरo_channel_t;

काष्ठा fअगरo_channel_state_s अणु
	bool	src_valid;
	bool	fअगरo_accept;
	bool	fअगरo_valid;
	bool	sink_accept;
पूर्ण;

/* The चयन is tri-state */
काष्ठा fअगरo_चयन_state_s अणु
	bool	is_none;
	bool	is_isp;
	bool	is_sp;
पूर्ण;

काष्ठा fअगरo_monitor_state_s अणु
	काष्ठा fअगरo_channel_state_s	fअगरo_channels[N_FIFO_CHANNEL];
	काष्ठा fअगरo_चयन_state_s	fअगरo_चयनes[N_FIFO_SWITCH];
पूर्ण;

#पूर्ण_अगर /* __FIFO_MONITOR_LOCAL_H_INCLUDED__ */
