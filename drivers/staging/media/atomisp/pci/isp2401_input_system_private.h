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

#अगर_अघोषित __INPUT_SYSTEM_PRIVATE_H_INCLUDED__
#घोषणा __INPUT_SYSTEM_PRIVATE_H_INCLUDED__

#समावेश "input_system_public.h"

#समावेश "device_access.h"	/* ia_css_device_load_uपूर्णांक32 */

#समावेश "assert_support.h" /* निश्चित */
#समावेश "print_support.h" /* prपूर्णांक */

/* Load the रेजिस्टर value */
अटल अंतरभूत hrt_data ibuf_ctrl_reg_load(स्थिर ibuf_ctrl_ID_t ID,
					  स्थिर hrt_address reg)
अणु
	निश्चित(ID < N_IBUF_CTRL_ID);
	निश्चित(IBUF_CTRL_BASE[ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(IBUF_CTRL_BASE[ID] + reg * माप(hrt_data));
पूर्ण

/* Store a value to the रेजिस्टर */
अटल अंतरभूत व्योम ibuf_ctrl_reg_store(स्थिर ibuf_ctrl_ID_t ID,
				       स्थिर hrt_address reg,
				       स्थिर hrt_data value)
अणु
	निश्चित(ID < N_IBUF_CTRL_ID);
	निश्चित(IBUF_CTRL_BASE[ID] != (hrt_address)-1);

	ia_css_device_store_uपूर्णांक32(IBUF_CTRL_BASE[ID] + reg * माप(hrt_data), value);
पूर्ण

/* Get the state of the ibuf-controller process */
अटल अंतरभूत व्योम ibuf_ctrl_get_proc_state(स्थिर ibuf_ctrl_ID_t ID,
					    स्थिर u32 proc_id,
					    ibuf_ctrl_proc_state_t *state)
अणु
	hrt_address reg_bank_offset;

	reg_bank_offset =
	    _IBUF_CNTRL_PROC_REG_ALIGN * (1 + proc_id);

	state->num_items =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_NUM_ITEMS_PER_STORE);

	state->num_stores =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_NUM_STORES_PER_FRAME);

	state->dma_channel =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_DMA_CHANNEL);

	state->dma_command =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_DMA_CMD);

	state->ibuf_st_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_BUFFER_START_ADDRESS);

	state->ibuf_stride =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_BUFFER_STRIDE);

	state->ibuf_end_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_BUFFER_END_ADDRESS);

	state->dest_st_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_DEST_START_ADDRESS);

	state->dest_stride =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_DEST_STRIDE);

	state->dest_end_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_DEST_END_ADDRESS);

	state->sync_frame =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_SYNC_FRAME);

	state->sync_command =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_STR2MMIO_SYNC_CMD);

	state->store_command =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_STR2MMIO_STORE_CMD);

	state->shअगरt_वापसed_items =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_SHIFT_ITEMS);

	state->elems_ibuf =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_ELEMS_P_WORD_IBUF);

	state->elems_dest =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_ELEMS_P_WORD_DEST);

	state->cur_stores =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_STORES);

	state->cur_acks =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_ACKS);

	state->cur_s2m_ibuf_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_S2M_IBUF_ADDR);

	state->cur_dma_ibuf_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_DMA_IBUF_ADDR);

	state->cur_dma_dest_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_DMA_DEST_ADDR);

	state->cur_isp_dest_addr =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_ISP_DEST_ADDR);

	state->dma_cmds_send =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_CUR_NR_DMA_CMDS_SEND);

	state->मुख्य_cntrl_state =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_MAIN_CNTRL_STATE);

	state->dma_sync_state =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_DMA_SYNC_STATE);

	state->isp_sync_state =
	    ibuf_ctrl_reg_load(ID, reg_bank_offset + _IBUF_CNTRL_ISP_SYNC_STATE);
पूर्ण

/* Get the ibuf-controller state. */
अटल अंतरभूत व्योम ibuf_ctrl_get_state(स्थिर ibuf_ctrl_ID_t ID,
				       ibuf_ctrl_state_t *state)
अणु
	u32 i;

	state->recalc_words =
	    ibuf_ctrl_reg_load(ID, _IBUF_CNTRL_RECALC_WORDS_STATUS);
	state->arbiters =
	    ibuf_ctrl_reg_load(ID, _IBUF_CNTRL_ARBITERS_STATUS);

	/*
	 * Get the values of the रेजिस्टर-set per
	 * ibuf-controller process.
	 */
	क्रम (i = 0; i < N_IBUF_CTRL_PROCS[ID]; i++) अणु
		ibuf_ctrl_get_proc_state(
		    ID,
		    i,
		    &state->proc_state[i]);
	पूर्ण
पूर्ण

/* Dump the ibuf-controller state */
अटल अंतरभूत व्योम ibuf_ctrl_dump_state(स्थिर ibuf_ctrl_ID_t ID,
					ibuf_ctrl_state_t *state)
अणु
	u32 i;

	ia_css_prपूर्णांक("IBUF controller ID %d recalculate words 0x%x\n", ID,
		     state->recalc_words);
	ia_css_prपूर्णांक("IBUF controller ID %d arbiters 0x%x\n", ID, state->arbiters);

	/*
	 * Dump the values of the रेजिस्टर-set per
	 * ibuf-controller process.
	 */
	क्रम (i = 0; i < N_IBUF_CTRL_PROCS[ID]; i++) अणु
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d num_items 0x%x\n", ID, i,
			     state->proc_state[i].num_items);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d num_stores 0x%x\n", ID, i,
			     state->proc_state[i].num_stores);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dma_channel 0x%x\n", ID, i,
			     state->proc_state[i].dma_channel);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dma_command 0x%x\n", ID, i,
			     state->proc_state[i].dma_command);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d ibuf_st_addr 0x%x\n", ID, i,
			     state->proc_state[i].ibuf_st_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d ibuf_stride 0x%x\n", ID, i,
			     state->proc_state[i].ibuf_stride);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d ibuf_end_addr 0x%x\n", ID, i,
			     state->proc_state[i].ibuf_end_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dest_st_addr 0x%x\n", ID, i,
			     state->proc_state[i].dest_st_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dest_stride 0x%x\n", ID, i,
			     state->proc_state[i].dest_stride);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dest_end_addr 0x%x\n", ID, i,
			     state->proc_state[i].dest_end_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d sync_frame 0x%x\n", ID, i,
			     state->proc_state[i].sync_frame);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d sync_command 0x%x\n", ID, i,
			     state->proc_state[i].sync_command);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d store_command 0x%x\n", ID, i,
			     state->proc_state[i].store_command);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d shift_returned_items 0x%x\n",
			     ID, i,
			     state->proc_state[i].shअगरt_वापसed_items);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d elems_ibuf 0x%x\n", ID, i,
			     state->proc_state[i].elems_ibuf);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d elems_dest 0x%x\n", ID, i,
			     state->proc_state[i].elems_dest);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d cur_stores 0x%x\n", ID, i,
			     state->proc_state[i].cur_stores);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d cur_acks 0x%x\n", ID, i,
			     state->proc_state[i].cur_acks);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d cur_s2m_ibuf_addr 0x%x\n", ID,
			     i,
			     state->proc_state[i].cur_s2m_ibuf_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d cur_dma_ibuf_addr 0x%x\n", ID,
			     i,
			     state->proc_state[i].cur_dma_ibuf_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d cur_dma_dest_addr 0x%x\n", ID,
			     i,
			     state->proc_state[i].cur_dma_dest_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d cur_isp_dest_addr 0x%x\n", ID,
			     i,
			     state->proc_state[i].cur_isp_dest_addr);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dma_cmds_send 0x%x\n", ID, i,
			     state->proc_state[i].dma_cmds_send);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d main_cntrl_state 0x%x\n", ID,
			     i,
			     state->proc_state[i].मुख्य_cntrl_state);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d dma_sync_state 0x%x\n", ID, i,
			     state->proc_state[i].dma_sync_state);
		ia_css_prपूर्णांक("IBUF controller ID %d Process ID %d isp_sync_state 0x%x\n", ID, i,
			     state->proc_state[i].isp_sync_state);
	पूर्ण
पूर्ण

अटल अंतरभूत input_प्रणाली_err_t
input_प्रणाली_get_state(स्थिर input_प्रणाली_ID_t ID,
		       input_प्रणाली_state_t *state)
अणु
	u32 i;

	(व्योम)(ID);

	/*  get the states of all CSI RX frontend devices */
	क्रम (i = 0; i < N_CSI_RX_FRONTEND_ID; i++) अणु
		csi_rx_fe_ctrl_get_state(
		    (csi_rx_frontend_ID_t)i,
		    &state->csi_rx_fe_ctrl_state[i]);
	पूर्ण

	/*  get the states of all CIS RX backend devices */
	क्रम (i = 0; i < N_CSI_RX_BACKEND_ID; i++) अणु
		csi_rx_be_ctrl_get_state(
		    (csi_rx_backend_ID_t)i,
		    &state->csi_rx_be_ctrl_state[i]);
	पूर्ण

	/* get the states of all pixelgen devices */
	क्रम (i = 0; i < N_PIXELGEN_ID; i++) अणु
		pixelgen_ctrl_get_state(
		    (pixelgen_ID_t)i,
		    &state->pixelgen_ctrl_state[i]);
	पूर्ण

	/* get the states of all stream2mmio devices */
	क्रम (i = 0; i < N_STREAM2MMIO_ID; i++) अणु
		stream2mmio_get_state(
		    (stream2mmio_ID_t)i,
		    &state->stream2mmio_state[i]);
	पूर्ण

	/* get the states of all ibuf-controller devices */
	क्रम (i = 0; i < N_IBUF_CTRL_ID; i++) अणु
		ibuf_ctrl_get_state(
		    (ibuf_ctrl_ID_t)i,
		    &state->ibuf_ctrl_state[i]);
	पूर्ण

	/* get the states of all isys irq controllers */
	क्रम (i = 0; i < N_ISYS_IRQ_ID; i++) अणु
		isys_irqc_state_get((isys_irq_ID_t)i, &state->isys_irqc_state[i]);
	पूर्ण

	/* TODO: get the states of all ISYS2401 DMA devices  */
	क्रम (i = 0; i < N_ISYS2401_DMA_ID; i++) अणु
	पूर्ण

	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

अटल अंतरभूत व्योम input_प्रणाली_dump_state(स्थिर input_प्रणाली_ID_t ID,
					   input_प्रणाली_state_t *state)
अणु
	u32 i;

	(व्योम)(ID);

	/*  dump the states of all CSI RX frontend devices */
	क्रम (i = 0; i < N_CSI_RX_FRONTEND_ID; i++) अणु
		csi_rx_fe_ctrl_dump_state(
		    (csi_rx_frontend_ID_t)i,
		    &state->csi_rx_fe_ctrl_state[i]);
	पूर्ण

	/*  dump the states of all CIS RX backend devices */
	क्रम (i = 0; i < N_CSI_RX_BACKEND_ID; i++) अणु
		csi_rx_be_ctrl_dump_state(
		    (csi_rx_backend_ID_t)i,
		    &state->csi_rx_be_ctrl_state[i]);
	पूर्ण

	/* dump the states of all pixelgen devices */
	क्रम (i = 0; i < N_PIXELGEN_ID; i++) अणु
		pixelgen_ctrl_dump_state(
		    (pixelgen_ID_t)i,
		    &state->pixelgen_ctrl_state[i]);
	पूर्ण

	/* dump the states of all st2mmio devices */
	क्रम (i = 0; i < N_STREAM2MMIO_ID; i++) अणु
		stream2mmio_dump_state(
		    (stream2mmio_ID_t)i,
		    &state->stream2mmio_state[i]);
	पूर्ण

	/* dump the states of all ibuf-controller devices */
	क्रम (i = 0; i < N_IBUF_CTRL_ID; i++) अणु
		ibuf_ctrl_dump_state(
		    (ibuf_ctrl_ID_t)i,
		    &state->ibuf_ctrl_state[i]);
	पूर्ण

	/* dump the states of all isys irq controllers */
	क्रम (i = 0; i < N_ISYS_IRQ_ID; i++) अणु
		isys_irqc_state_dump((isys_irq_ID_t)i, &state->isys_irqc_state[i]);
	पूर्ण

	/* TODO: dump the states of all ISYS2401 DMA devices  */
	क्रम (i = 0; i < N_ISYS2401_DMA_ID; i++) अणु
	पूर्ण

	वापस;
पूर्ण
#पूर्ण_अगर /* __INPUT_SYSTEM_PRIVATE_H_INCLUDED__ */
