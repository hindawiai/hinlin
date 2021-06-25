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

#अगर_अघोषित __IBUF_CTRL_GLOBAL_H_INCLUDED__
#घोषणा __IBUF_CTRL_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

#समावेश <ibuf_cntrl_defs.h>	/* _IBUF_CNTRL_RECALC_WORDS_STATUS,
				 * _IBUF_CNTRL_ARBITERS_STATUS,
				 * _IBUF_CNTRL_PROC_REG_ALIGN,
				 * etc.
				 */

/* Definition of contents of मुख्य controller state रेजिस्टर is lacking
 * in ibuf_cntrl_defs.h, so define these here:
 */
#घोषणा _IBUF_CNTRL_MAIN_CNTRL_FSM_MASK			0xf
#घोषणा _IBUF_CNTRL_MAIN_CNTRL_FSM_NEXT_COMMAND_CHECK	0x9
#घोषणा _IBUF_CNTRL_MAIN_CNTRL_MEM_INP_BUF_ALLOC	BIT(8)
#घोषणा _IBUF_CNTRL_DMA_SYNC_WAIT_FOR_SYNC		1
#घोषणा _IBUF_CNTRL_DMA_SYNC_FSM_WAIT_FOR_ACK		(0x3 << 1)

काष्ठा	isp2401_ib_buffer_s अणु
	u32	start_addr;	/* start address of the buffer in the
					 * "input-buffer hardware block"
					 */

	u32	stride;		/* stride per buffer line (in bytes) */
	u32	lines;		/* lines in the buffer */
पूर्ण;
प्रकार काष्ठा isp2401_ib_buffer_s	isp2401_ib_buffer_t;

प्रकार काष्ठा ibuf_ctrl_cfg_s ibuf_ctrl_cfg_t;
काष्ठा ibuf_ctrl_cfg_s अणु
	bool online;

	काष्ठा अणु
		/* DMA configuration */
		u32 channel;
		u32 cmd; /* must be _DMA_V2_MOVE_A2B_NO_SYNC_CHK_COMMAND */

		/* DMA reconfiguration */
		u32 shअगरt_वापसed_items;
		u32 elems_per_word_in_ibuf;
		u32 elems_per_word_in_dest;
	पूर्ण dma_cfg;

	isp2401_ib_buffer_t ib_buffer;

	काष्ठा अणु
		u32 stride;
		u32 start_addr;
		u32 lines;
	पूर्ण dest_buf_cfg;

	u32 items_per_store;
	u32 stores_per_frame;

	काष्ठा अणु
		u32 sync_cmd;	/* must be _STREAM2MMIO_CMD_TOKEN_SYNC_FRAME */
		u32 store_cmd;	/* must be _STREAM2MMIO_CMD_TOKEN_STORE_PACKETS */
	पूर्ण stream2mmio_cfg;
पूर्ण;

बाह्य स्थिर u32 N_IBUF_CTRL_PROCS[N_IBUF_CTRL_ID];

#पूर्ण_अगर /* __IBUF_CTRL_GLOBAL_H_INCLUDED__ */
