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

#अगर_अघोषित __CSI_RX_PRIVATE_H_INCLUDED__
#घोषणा __CSI_RX_PRIVATE_H_INCLUDED__

#समावेश "rx_csi_defs.h"
#समावेश "mipi_backend_defs.h"
#समावेश "csi_rx.h"

#समावेश "device_access.h"	/* ia_css_device_load_uपूर्णांक32 */

#समावेश "assert_support.h" /* निश्चित */
#समावेश "print_support.h" /* prपूर्णांक */

/*****************************************************
 *
 * Device level पूर्णांकerface (DLI).
 *
 *****************************************************/
/**
 * @brief Load the रेजिस्टर value.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत hrt_data csi_rx_fe_ctrl_reg_load(
    स्थिर csi_rx_frontend_ID_t ID,
    स्थिर hrt_address reg)
अणु
	निश्चित(ID < N_CSI_RX_FRONTEND_ID);
	निश्चित(CSI_RX_FE_CTRL_BASE[ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(CSI_RX_FE_CTRL_BASE[ID] + reg * माप(
					     hrt_data));
पूर्ण

/**
 * @brief Store a value to the रेजिस्टर.
 * Refer to "ibuf_ctrl_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_fe_ctrl_reg_store(
    स्थिर csi_rx_frontend_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value)
अणु
	निश्चित(ID < N_CSI_RX_FRONTEND_ID);
	निश्चित(CSI_RX_FE_CTRL_BASE[ID] != (hrt_address)-1);

	ia_css_device_store_uपूर्णांक32(CSI_RX_FE_CTRL_BASE[ID] + reg * माप(hrt_data),
				   value);
पूर्ण

/**
 * @brief Load the रेजिस्टर value.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत hrt_data csi_rx_be_ctrl_reg_load(
    स्थिर csi_rx_backend_ID_t ID,
    स्थिर hrt_address reg)
अणु
	निश्चित(ID < N_CSI_RX_BACKEND_ID);
	निश्चित(CSI_RX_BE_CTRL_BASE[ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(CSI_RX_BE_CTRL_BASE[ID] + reg * माप(
					     hrt_data));
पूर्ण

/**
 * @brief Store a value to the रेजिस्टर.
 * Refer to "ibuf_ctrl_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_be_ctrl_reg_store(
    स्थिर csi_rx_backend_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value)
अणु
	निश्चित(ID < N_CSI_RX_BACKEND_ID);
	निश्चित(CSI_RX_BE_CTRL_BASE[ID] != (hrt_address)-1);

	ia_css_device_store_uपूर्णांक32(CSI_RX_BE_CTRL_BASE[ID] + reg * माप(hrt_data),
				   value);
पूर्ण

/* end of DLI */

/*****************************************************
 *
 * Native command पूर्णांकerface (NCI).
 *
 *****************************************************/
/**
 * @brief Get the state of the csi rx fe dlane process.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_fe_ctrl_get_dlane_state(
    स्थिर csi_rx_frontend_ID_t ID,
    स्थिर u32 lane,
    csi_rx_fe_ctrl_lane_t *dlane_state)
अणु
	dlane_state->termen =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_DLY_CNT_TERMEN_DLANE_REG_IDX(lane));
	dlane_state->settle =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_DLY_CNT_SETTLE_DLANE_REG_IDX(lane));
पूर्ण

/**
 * @brief Get the csi rx fe state.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_fe_ctrl_get_state(
    स्थिर csi_rx_frontend_ID_t ID,
    csi_rx_fe_ctrl_state_t *state)
अणु
	u32 i;

	state->enable =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_ENABLE_REG_IDX);
	state->nof_enable_lanes =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_NOF_ENABLED_LANES_REG_IDX);
	state->error_handling =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_ERROR_HANDLING_REG_IDX);
	state->status =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_STATUS_REG_IDX);
	state->status_dlane_hs =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_STATUS_DLANE_HS_REG_IDX);
	state->status_dlane_lp =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_STATUS_DLANE_LP_REG_IDX);
	state->clane.termen =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_DLY_CNT_TERMEN_CLANE_REG_IDX);
	state->clane.settle =
	    csi_rx_fe_ctrl_reg_load(ID, _HRT_CSI_RX_DLY_CNT_SETTLE_CLANE_REG_IDX);

	/*
	 * Get the values of the रेजिस्टर-set per
	 * dlane.
	 */
	क्रम (i = 0; i < N_CSI_RX_FE_CTRL_DLANES[ID]; i++) अणु
		csi_rx_fe_ctrl_get_dlane_state(
		    ID,
		    i,
		    &state->dlane[i]);
	पूर्ण
पूर्ण

/**
 * @brief dump the csi rx fe state.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_fe_ctrl_dump_state(
    स्थिर csi_rx_frontend_ID_t ID,
    csi_rx_fe_ctrl_state_t *state)
अणु
	u32 i;

	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Enable state 0x%x\n", ID,
		     state->enable);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d No Of enable lanes 0x%x\n", ID,
		     state->nof_enable_lanes);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Error handling 0x%x\n", ID,
		     state->error_handling);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Status 0x%x\n", ID, state->status);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Status Dlane HS 0x%x\n", ID,
		     state->status_dlane_hs);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Status Dlane LP 0x%x\n", ID,
		     state->status_dlane_lp);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Status term enable LP 0x%x\n", ID,
		     state->clane.termen);
	ia_css_prपूर्णांक("CSI RX FE STATE Controller %d Status term settle LP 0x%x\n", ID,
		     state->clane.settle);

	/*
	 * Get the values of the रेजिस्टर-set per
	 * dlane.
	 */
	क्रम (i = 0; i < N_CSI_RX_FE_CTRL_DLANES[ID]; i++) अणु
		ia_css_prपूर्णांक("CSI RX FE STATE Controller %d DLANE ID %d termen 0x%x\n", ID, i,
			     state->dlane[i].termen);
		ia_css_prपूर्णांक("CSI RX FE STATE Controller %d DLANE ID %d settle 0x%x\n", ID, i,
			     state->dlane[i].settle);
	पूर्ण
पूर्ण

/**
 * @brief Get the csi rx be state.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_be_ctrl_get_state(
    स्थिर csi_rx_backend_ID_t ID,
    csi_rx_be_ctrl_state_t *state)
अणु
	u32 i;

	state->enable =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_ENABLE_REG_IDX);

	state->status =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_STATUS_REG_IDX);

	क्रम (i = 0; i < N_CSI_RX_BE_MIPI_COMP_FMT_REG ; i++) अणु
		state->comp_क्रमmat_reg[i] =
		    csi_rx_be_ctrl_reg_load(ID,
					    _HRT_MIPI_BACKEND_COMP_FORMAT_REG0_IDX + i);
	पूर्ण

	state->raw16 =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_RAW16_CONFIG_REG_IDX);

	state->raw18 =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_RAW18_CONFIG_REG_IDX);
	state->क्रमce_raw8 =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_FORCE_RAW8_REG_IDX);
	state->irq_status =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_IRQ_STATUS_REG_IDX);
#अगर 0 /* device access error क्रम these रेजिस्टरs */
	/* ToDo: rootcause this failure */
	state->custom_mode_enable =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_CUST_EN_REG_IDX);

	state->custom_mode_data_state =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_CUST_DATA_STATE_REG_IDX);
	क्रम (i = 0; i < N_CSI_RX_BE_MIPI_CUSTOM_PEC ; i++) अणु
		state->pec[i] =
		    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_CUST_PIX_EXT_S0P0_REG_IDX + i);
	पूर्ण
	state->custom_mode_valid_eop_config =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_CUST_PIX_VALID_EOP_REG_IDX);
#पूर्ण_अगर
	state->global_lut_disregard_reg =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_GLOBAL_LUT_DISREGARD_REG_IDX);
	state->packet_status_stall =
	    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_PKT_STALL_STATUS_REG_IDX);
	/*
	 * Get the values of the रेजिस्टर-set per
	 * lut.
	 */
	क्रम (i = 0; i < N_SHORT_PACKET_LUT_ENTRIES[ID]; i++) अणु
		state->लघु_packet_lut_entry[i] =
		    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_SP_LUT_ENTRY_0_REG_IDX + i);
	पूर्ण
	क्रम (i = 0; i < N_LONG_PACKET_LUT_ENTRIES[ID]; i++) अणु
		state->दीर्घ_packet_lut_entry[i] =
		    csi_rx_be_ctrl_reg_load(ID, _HRT_MIPI_BACKEND_LP_LUT_ENTRY_0_REG_IDX + i);
	पूर्ण
पूर्ण

/**
 * @brief Dump the csi rx be state.
 * Refer to "csi_rx_public.h" क्रम details.
 */
अटल अंतरभूत व्योम csi_rx_be_ctrl_dump_state(
    स्थिर csi_rx_backend_ID_t ID,
    csi_rx_be_ctrl_state_t *state)
अणु
	u32 i;

	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d Enable 0x%x\n", ID, state->enable);
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d Status 0x%x\n", ID, state->status);

	क्रम (i = 0; i < N_CSI_RX_BE_MIPI_COMP_FMT_REG ; i++) अणु
		ia_css_prपूर्णांक("CSI RX BE STATE Controller %d comp format reg vc%d value 0x%x\n",
			     ID, i, state->status);
	पूर्ण
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d RAW16 0x%x\n", ID, state->raw16);
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d RAW18 0x%x\n", ID, state->raw18);
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d Force RAW8 0x%x\n", ID,
		     state->क्रमce_raw8);
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d IRQ state 0x%x\n", ID,
		     state->irq_status);
#अगर 0   /* ToDo:Getting device access error क्रम this रेजिस्टर */
	क्रम (i = 0; i < N_CSI_RX_BE_MIPI_CUSTOM_PEC ; i++) अणु
		ia_css_prपूर्णांक("CSI RX BE STATE Controller %d PEC ID %d custom pec 0x%x\n", ID, i,
			     state->pec[i]);
	पूर्ण
#पूर्ण_अगर
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d Global LUT disregard reg 0x%x\n",
		     ID, state->global_lut_disregard_reg);
	ia_css_prपूर्णांक("CSI RX BE STATE Controller %d packet stall reg 0x%x\n", ID,
		     state->packet_status_stall);
	/*
	 * Get the values of the रेजिस्टर-set per
	 * lut.
	 */
	क्रम (i = 0; i < N_SHORT_PACKET_LUT_ENTRIES[ID]; i++) अणु
		ia_css_prपूर्णांक("CSI RX BE STATE Controller ID %d Short packet entry %d short packet lut id 0x%x\n",
			     ID, i,
			     state->लघु_packet_lut_entry[i]);
	पूर्ण
	क्रम (i = 0; i < N_LONG_PACKET_LUT_ENTRIES[ID]; i++) अणु
		ia_css_prपूर्णांक("CSI RX BE STATE Controller ID %d Long packet entry %d long packet lut id 0x%x\n",
			     ID, i,
			     state->दीर्घ_packet_lut_entry[i]);
	पूर्ण
पूर्ण

/* end of NCI */

#पूर्ण_अगर /* __CSI_RX_PRIVATE_H_INCLUDED__ */
