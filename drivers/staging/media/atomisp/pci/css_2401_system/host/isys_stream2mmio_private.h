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

#अगर_अघोषित __ISYS_STREAM2MMIO_PRIVATE_H_INCLUDED__
#घोषणा __ISYS_STREAM2MMIO_PRIVATE_H_INCLUDED__

#समावेश "isys_stream2mmio_public.h"
#समावेश "device_access.h"	/* ia_css_device_load_uपूर्णांक32 */
#समावेश "assert_support.h"	/* निश्चित */
#समावेश "print_support.h"	/* prपूर्णांक */

#घोषणा STREAM2MMIO_COMMAND_REG_ID             0
#घोषणा STREAM2MMIO_ACKNOWLEDGE_REG_ID         1
#घोषणा STREAM2MMIO_PIX_WIDTH_ID_REG_ID        2
#घोषणा STREAM2MMIO_START_ADDR_REG_ID          3      /* master port address,NOT Byte */
#घोषणा STREAM2MMIO_END_ADDR_REG_ID            4      /* master port address,NOT Byte */
#घोषणा STREAM2MMIO_STRIDE_REG_ID              5      /* stride in master port words, increment is per packet क्रम दीर्घ sids, stride is not used क्रम लघु sid's*/
#घोषणा STREAM2MMIO_NUM_ITEMS_REG_ID           6      /* number of packets क्रम store packets cmd, number of words क्रम store_words cmd */
#घोषणा STREAM2MMIO_BLOCK_WHEN_NO_CMD_REG_ID   7      /* अगर this रेजिस्टर is 1, input will be stalled अगर there is no pending command क्रम this sid */
#घोषणा STREAM2MMIO_REGS_PER_SID               8

/*****************************************************
 *
 * Native command पूर्णांकerface (NCI).
 *
 *****************************************************/
/**
 * @brief Get the stream2mmio-controller state.
 * Refer to "stream2mmio_public.h" क्रम details.
 */
STORAGE_CLASS_STREAM2MMIO_C व्योम stream2mmio_get_state(
    स्थिर stream2mmio_ID_t ID,
    stream2mmio_state_t *state)
अणु
	stream2mmio_sid_ID_t i;

	/*
	 * Get the values of the रेजिस्टर-set per
	 * stream2mmio-controller sids.
	 */
	क्रम (i = STREAM2MMIO_SID0_ID; i < N_STREAM2MMIO_SID_PROCS[ID]; i++) अणु
		stream2mmio_get_sid_state(ID, i, &state->sid_state[i]);
	पूर्ण
पूर्ण

/**
 * @brief Get the state of the stream2mmio-controller sidess.
 * Refer to "stream2mmio_public.h" क्रम details.
 */
STORAGE_CLASS_STREAM2MMIO_C व्योम stream2mmio_get_sid_state(
    स्थिर stream2mmio_ID_t ID,
    स्थिर stream2mmio_sid_ID_t sid_id,
    stream2mmio_sid_state_t	*state)
अणु
	state->rcv_ack =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_ACKNOWLEDGE_REG_ID);

	state->pix_width_id =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_PIX_WIDTH_ID_REG_ID);

	state->start_addr =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_START_ADDR_REG_ID);

	state->end_addr =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_END_ADDR_REG_ID);

	state->strides =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_STRIDE_REG_ID);

	state->num_items =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_NUM_ITEMS_REG_ID);

	state->block_when_no_cmd =
	    stream2mmio_reg_load(ID, sid_id, STREAM2MMIO_BLOCK_WHEN_NO_CMD_REG_ID);
पूर्ण

/**
 * @brief Dump the state of the stream2mmio-controller sidess.
 * Refer to "stream2mmio_public.h" क्रम details.
 */
STORAGE_CLASS_STREAM2MMIO_C व्योम stream2mmio_prपूर्णांक_sid_state(
    stream2mmio_sid_state_t	*state)
अणु
	ia_css_prपूर्णांक("\t \t Receive acks 0x%x\n", state->rcv_ack);
	ia_css_prपूर्णांक("\t \t Pixel width 0x%x\n", state->pix_width_id);
	ia_css_prपूर्णांक("\t \t Startaddr 0x%x\n", state->start_addr);
	ia_css_prपूर्णांक("\t \t Endaddr 0x%x\n", state->end_addr);
	ia_css_prपूर्णांक("\t \t Strides 0x%x\n", state->strides);
	ia_css_prपूर्णांक("\t \t Num Items 0x%x\n", state->num_items);
	ia_css_prपूर्णांक("\t \t block when no cmd 0x%x\n", state->block_when_no_cmd);
पूर्ण

/**
 * @brief Dump the ibuf-controller state.
 * Refer to "stream2mmio_public.h" क्रम details.
 */
STORAGE_CLASS_STREAM2MMIO_C व्योम stream2mmio_dump_state(
    स्थिर stream2mmio_ID_t ID,
    stream2mmio_state_t *state)
अणु
	stream2mmio_sid_ID_t i;

	/*
	 * Get the values of the रेजिस्टर-set per
	 * stream2mmio-controller sids.
	 */
	क्रम (i = STREAM2MMIO_SID0_ID; i < N_STREAM2MMIO_SID_PROCS[ID]; i++) अणु
		ia_css_prपूर्णांक("StREAM2MMIO ID %d SID %d\n", ID, i);
		stream2mmio_prपूर्णांक_sid_state(&state->sid_state[i]);
	पूर्ण
पूर्ण

/* end of NCI */

/*****************************************************
 *
 * Device level पूर्णांकerface (DLI).
 *
 *****************************************************/
/**
 * @brief Load the रेजिस्टर value.
 * Refer to "stream2mmio_public.h" क्रम details.
 */
STORAGE_CLASS_STREAM2MMIO_C hrt_data stream2mmio_reg_load(
    स्थिर stream2mmio_ID_t ID,
    स्थिर stream2mmio_sid_ID_t sid_id,
    स्थिर uपूर्णांक32_t reg_idx)
अणु
	u32 reg_bank_offset;

	निश्चित(ID < N_STREAM2MMIO_ID);

	reg_bank_offset = STREAM2MMIO_REGS_PER_SID * sid_id;
	वापस ia_css_device_load_uपूर्णांक32(STREAM2MMIO_CTRL_BASE[ID] +
					 (reg_bank_offset + reg_idx) * माप(hrt_data));
पूर्ण

/**
 * @brief Store a value to the रेजिस्टर.
 * Refer to "stream2mmio_public.h" क्रम details.
 */
STORAGE_CLASS_STREAM2MMIO_C व्योम stream2mmio_reg_store(
    स्थिर stream2mmio_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value)
अणु
	निश्चित(ID < N_STREAM2MMIO_ID);
	निश्चित(STREAM2MMIO_CTRL_BASE[ID] != (hrt_address)-1);

	ia_css_device_store_uपूर्णांक32(STREAM2MMIO_CTRL_BASE[ID] +
				   reg * माप(hrt_data), value);
पूर्ण

/* end of DLI */

#पूर्ण_अगर /* __ISYS_STREAM2MMIO_PRIVATE_H_INCLUDED__ */
