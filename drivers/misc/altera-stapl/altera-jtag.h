<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * altera-jtag.h
 *
 * altera FPGA driver
 *
 * Copyright (C) Altera Corporation 1998-2001
 * Copyright (C) 2010 NetUP Inc.
 * Copyright (C) 2010 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित ALTERA_JTAG_H
#घोषणा ALTERA_JTAG_H

/* Function Prototypes */
क्रमागत altera_jtag_state अणु
	ILLEGAL_JTAG_STATE = -1,
	RESET = 0,
	IDLE = 1,
	DRSELECT = 2,
	DRCAPTURE = 3,
	DRSHIFT = 4,
	DREXIT1 = 5,
	DRPAUSE = 6,
	DREXIT2 = 7,
	DRUPDATE = 8,
	IRSELECT = 9,
	IRCAPTURE = 10,
	IRSHIFT = 11,
	IREXIT1 = 12,
	IRPAUSE = 13,
	IREXIT2 = 14,
	IRUPDATE = 15

पूर्ण;

काष्ठा altera_jtag अणु
	/* Global variable to store the current JTAG state */
	क्रमागत altera_jtag_state jtag_state;

	/* Store current stop-state क्रम DR and IR scan commands */
	क्रमागत altera_jtag_state drstop_state;
	क्रमागत altera_jtag_state irstop_state;

	/* Store current padding values */
	u32 dr_pre;
	u32 dr_post;
	u32 ir_pre;
	u32 ir_post;
	u32 dr_length;
	u32 ir_length;
	u8 *dr_pre_data;
	u8 *dr_post_data;
	u8 *ir_pre_data;
	u8 *ir_post_data;
	u8 *dr_buffer;
	u8 *ir_buffer;
पूर्ण;

#घोषणा ALTERA_STACK_SIZE 128
#घोषणा ALTERA_MESSAGE_LENGTH 1024

काष्ठा altera_state अणु
	काष्ठा altera_config	*config;
	काष्ठा altera_jtag	js;
	अक्षर			msg_buff[ALTERA_MESSAGE_LENGTH + 1];
	दीर्घ			stack[ALTERA_STACK_SIZE];
पूर्ण;

पूर्णांक altera_jinit(काष्ठा altera_state *astate);
पूर्णांक altera_set_drstop(काष्ठा altera_jtag *js, क्रमागत altera_jtag_state state);
पूर्णांक altera_set_irstop(काष्ठा altera_jtag *js, क्रमागत altera_jtag_state state);
पूर्णांक altera_set_dr_pre(काष्ठा altera_jtag *js, u32 count, u32 start_index,
				u8 *preamble_data);
पूर्णांक altera_set_ir_pre(काष्ठा altera_jtag *js, u32 count, u32 start_index,
				u8 *preamble_data);
पूर्णांक altera_set_dr_post(काष्ठा altera_jtag *js, u32 count, u32 start_index,
				u8 *postamble_data);
पूर्णांक altera_set_ir_post(काष्ठा altera_jtag *js, u32 count, u32 start_index,
				u8 *postamble_data);
पूर्णांक altera_जाओ_jstate(काष्ठा altera_state *astate,
				क्रमागत altera_jtag_state state);
पूर्णांक altera_रुको_cycles(काष्ठा altera_state *astate, s32 cycles,
				क्रमागत altera_jtag_state रुको_state);
पूर्णांक altera_रुको_msecs(काष्ठा altera_state *astate, s32 microseconds,
				क्रमागत altera_jtag_state रुको_state);
पूर्णांक altera_irscan(काष्ठा altera_state *astate, u32 count,
				u8 *tdi_data, u32 start_index);
पूर्णांक altera_swap_ir(काष्ठा altera_state *astate,
				u32 count, u8 *in_data,
				u32 in_index, u8 *out_data,
				u32 out_index);
पूर्णांक altera_drscan(काष्ठा altera_state *astate, u32 count,
				u8 *tdi_data, u32 start_index);
पूर्णांक altera_swap_dr(काष्ठा altera_state *astate, u32 count,
				u8 *in_data, u32 in_index,
				u8 *out_data, u32 out_index);
व्योम altera_मुक्त_buffers(काष्ठा altera_state *astate);
#पूर्ण_अगर /* ALTERA_JTAG_H */
