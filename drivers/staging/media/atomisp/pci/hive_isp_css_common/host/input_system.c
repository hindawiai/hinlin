<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-015, Intel Corporation.
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

#समावेश "system_global.h"

#अगर_अघोषित ISP2401

#समावेश "input_system.h"
#समावेश <type_support.h>
#समावेश "gp_device.h"

#समावेश "assert_support.h"

#अगर_अघोषित __INLINE_INPUT_SYSTEM__
#समावेश "input_system_private.h"
#पूर्ण_अगर /* __INLINE_INPUT_SYSTEM__ */

#घोषणा ZERO (0x0)
#घोषणा ONE  (1U)

अटल स्थिर isp2400_ib_buffer_t   IB_BUFFER_शून्य = अणु0, 0, 0 पूर्ण;

अटल input_प्रणाली_err_t input_प्रणाली_configure_channel(
    स्थिर channel_cfg_t		channel);

अटल input_प्रणाली_err_t input_प्रणाली_configure_channel_sensor(
    स्थिर channel_cfg_t		channel);

अटल input_प्रणाली_err_t input_buffer_configuration(व्योम);

अटल input_प्रणाली_err_t configuration_to_रेजिस्टरs(व्योम);

अटल व्योम receiver_rst(स्थिर rx_ID_t ID);
अटल व्योम input_प्रणाली_network_rst(स्थिर input_प्रणाली_ID_t ID);

अटल व्योम capture_unit_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    स्थिर isp2400_ib_buffer_t *स्थिर cfg);

अटल व्योम acquisition_unit_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    स्थिर isp2400_ib_buffer_t *स्थिर cfg);

अटल व्योम ctrl_unit_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    स्थिर ctrl_unit_cfg_t *स्थिर cfg);

अटल व्योम input_प्रणाली_network_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर input_प्रणाली_network_cfg_t *स्थिर cfg);

// MW: CSI is previously named as "rx" लघु क्रम "receiver"
अटल input_प्रणाली_err_t set_csi_cfg(
    csi_cfg_t *स्थिर lhs,
    स्थिर csi_cfg_t *स्थिर rhs,
    input_प्रणाली_config_flags_t *स्थिर flags);

अटल input_प्रणाली_err_t set_source_type(
    input_प्रणाली_source_t *स्थिर lhs,
    स्थिर input_प्रणाली_source_t				rhs,
    input_प्रणाली_config_flags_t *स्थिर flags);

अटल input_प्रणाली_err_t input_प्रणाली_multiplexer_cfg(
    input_प्रणाली_multiplex_t *स्थिर lhs,
    स्थिर input_प्रणाली_multiplex_t			rhs,
    input_प्रणाली_config_flags_t *स्थिर flags);

अटल अंतरभूत व्योम capture_unit_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    capture_unit_state_t			*state);

अटल अंतरभूत व्योम acquisition_unit_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    acquisition_unit_state_t		*state);

अटल अंतरभूत व्योम ctrl_unit_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    ctrl_unit_state_t				*state);

अटल अंतरभूत व्योम mipi_port_get_state(
    स्थिर rx_ID_t					ID,
    स्थिर क्रमागत mipi_port_id			port_ID,
    mipi_port_state_t				*state);

अटल अंतरभूत व्योम rx_channel_get_state(
    स्थिर rx_ID_t					ID,
    स्थिर अचिन्हित पूर्णांक				ch_id,
    rx_channel_state_t				*state);

अटल व्योम gp_device_rst(स्थिर gp_device_ID_t		ID);

अटल व्योम input_selector_cfg_क्रम_sensor(स्थिर gp_device_ID_t	ID);

अटल व्योम input_चयन_rst(स्थिर gp_device_ID_t	ID);

अटल व्योम input_चयन_cfg(
    स्थिर gp_device_ID_t				ID,
    स्थिर input_चयन_cfg_t *स्थिर cfg
);

व्योम input_प्रणाली_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    input_प्रणाली_state_t			*state)
अणु
	sub_प्रणाली_ID_t	sub_id;

	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(state);

	state->str_multicastA_sel = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				    GPREGS_UNIT0_ID,
				    HIVE_ISYS_GPREG_MULTICAST_A_IDX);
	state->str_multicastB_sel = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				    GPREGS_UNIT0_ID,
				    HIVE_ISYS_GPREG_MULTICAST_B_IDX);
	state->str_multicastC_sel = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				    GPREGS_UNIT0_ID,
				    HIVE_ISYS_GPREG_MULTICAST_C_IDX);
	state->str_mux_sel = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			     GPREGS_UNIT0_ID,
			     HIVE_ISYS_GPREG_MUX_IDX);
	state->str_mon_status = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				GPREGS_UNIT0_ID,
				HIVE_ISYS_GPREG_STRMON_STAT_IDX);
	state->str_mon_irq_cond = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  GPREGS_UNIT0_ID,
				  HIVE_ISYS_GPREG_STRMON_COND_IDX);
	state->str_mon_irq_en = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				GPREGS_UNIT0_ID,
				HIVE_ISYS_GPREG_STRMON_IRQ_EN_IDX);
	state->isys_srst = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			   GPREGS_UNIT0_ID,
			   HIVE_ISYS_GPREG_SRST_IDX);
	state->isys_slv_reg_srst = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				   GPREGS_UNIT0_ID,
				   HIVE_ISYS_GPREG_SLV_REG_SRST_IDX);
	state->str_deपूर्णांक_portA_cnt = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				     GPREGS_UNIT0_ID,
				     HIVE_ISYS_GPREG_REG_PORT_A_IDX);
	state->str_deपूर्णांक_portB_cnt = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				     GPREGS_UNIT0_ID,
				     HIVE_ISYS_GPREG_REG_PORT_B_IDX);

	क्रम (sub_id = CAPTURE_UNIT0_ID; sub_id < CAPTURE_UNIT0_ID + N_CAPTURE_UNIT_ID;
	     sub_id++) अणु
		capture_unit_get_state(ID, sub_id,
				       &state->capture_unit[sub_id - CAPTURE_UNIT0_ID]);
	पूर्ण
	क्रम (sub_id = ACQUISITION_UNIT0_ID;
	     sub_id < ACQUISITION_UNIT0_ID + N_ACQUISITION_UNIT_ID; sub_id++) अणु
		acquisition_unit_get_state(ID, sub_id,
					   &state->acquisition_unit[sub_id - ACQUISITION_UNIT0_ID]);
	पूर्ण
	क्रम (sub_id = CTRL_UNIT0_ID; sub_id < CTRL_UNIT0_ID + N_CTRL_UNIT_ID;
	     sub_id++) अणु
		ctrl_unit_get_state(ID, sub_id,
				    &state->ctrl_unit_state[sub_id - CTRL_UNIT0_ID]);
	पूर्ण

	वापस;
पूर्ण

व्योम receiver_get_state(
    स्थिर rx_ID_t				ID,
    receiver_state_t			*state)
अणु
	क्रमागत mipi_port_id	port_id;
	अचिन्हित पूर्णांक	ch_id;

	निश्चित(ID < N_RX_ID);
	निश्चित(state);

	state->fs_to_ls_delay = (uपूर्णांक8_t)receiver_reg_load(ID,
				_HRT_CSS_RECEIVER_FS_TO_LS_DELAY_REG_IDX);
	state->ls_to_data_delay = (uपूर्णांक8_t)receiver_reg_load(ID,
				  _HRT_CSS_RECEIVER_LS_TO_DATA_DELAY_REG_IDX);
	state->data_to_le_delay = (uपूर्णांक8_t)receiver_reg_load(ID,
				  _HRT_CSS_RECEIVER_DATA_TO_LE_DELAY_REG_IDX);
	state->le_to_fe_delay = (uपूर्णांक8_t)receiver_reg_load(ID,
				_HRT_CSS_RECEIVER_LE_TO_FE_DELAY_REG_IDX);
	state->fe_to_fs_delay = (uपूर्णांक8_t)receiver_reg_load(ID,
				_HRT_CSS_RECEIVER_FE_TO_FS_DELAY_REG_IDX);
	state->le_to_fs_delay = (uपूर्णांक8_t)receiver_reg_load(ID,
				_HRT_CSS_RECEIVER_LE_TO_LS_DELAY_REG_IDX);
	state->is_two_ppc = (bool)receiver_reg_load(ID,
			    _HRT_CSS_RECEIVER_TWO_PIXEL_EN_REG_IDX);
	state->backend_rst = receiver_reg_load(ID,
					       _HRT_CSS_RECEIVER_BACKEND_RST_REG_IDX);
	state->raw18 = (uपूर्णांक16_t)receiver_reg_load(ID,
		       _HRT_CSS_RECEIVER_RAW18_REG_IDX);
	state->क्रमce_raw8 = (bool)receiver_reg_load(ID,
			    _HRT_CSS_RECEIVER_FORCE_RAW8_REG_IDX);
	state->raw16 = (uपूर्णांक16_t)receiver_reg_load(ID,
		       _HRT_CSS_RECEIVER_RAW16_REG_IDX);

	क्रम (port_id = (क्रमागत mipi_port_id)0; port_id < N_MIPI_PORT_ID; port_id++) अणु
		mipi_port_get_state(ID, port_id,
				    &state->mipi_port_state[port_id]);
	पूर्ण
	क्रम (ch_id = 0U; ch_id < N_RX_CHANNEL_ID; ch_id++) अणु
		rx_channel_get_state(ID, ch_id,
				     &state->rx_channel_state[ch_id]);
	पूर्ण

	state->be_gsp_acc_ovl = receiver_reg_load(ID,
				_HRT_CSS_RECEIVER_BE_GSP_ACC_OVL_REG_IDX);
	state->be_srst = receiver_reg_load(ID,
					   _HRT_CSS_RECEIVER_BE_SRST_REG_IDX);
	state->be_is_two_ppc = receiver_reg_load(ID,
			       _HRT_CSS_RECEIVER_BE_TWO_PPC_REG_IDX);
	state->be_comp_क्रमmat0 = receiver_reg_load(ID,
				 _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG0_IDX);
	state->be_comp_क्रमmat1 = receiver_reg_load(ID,
				 _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG1_IDX);
	state->be_comp_क्रमmat2 = receiver_reg_load(ID,
				 _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG2_IDX);
	state->be_comp_क्रमmat3 = receiver_reg_load(ID,
				 _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG3_IDX);
	state->be_sel = receiver_reg_load(ID,
					  _HRT_CSS_RECEIVER_BE_SEL_REG_IDX);
	state->be_raw16_config = receiver_reg_load(ID,
				 _HRT_CSS_RECEIVER_BE_RAW16_CONFIG_REG_IDX);
	state->be_raw18_config = receiver_reg_load(ID,
				 _HRT_CSS_RECEIVER_BE_RAW18_CONFIG_REG_IDX);
	state->be_क्रमce_raw8 = receiver_reg_load(ID,
			       _HRT_CSS_RECEIVER_BE_FORCE_RAW8_REG_IDX);
	state->be_irq_status = receiver_reg_load(ID,
			       _HRT_CSS_RECEIVER_BE_IRQ_STATUS_REG_IDX);
	state->be_irq_clear = receiver_reg_load(ID,
						_HRT_CSS_RECEIVER_BE_IRQ_CLEAR_REG_IDX);

	वापस;
पूर्ण

bool is_mipi_क्रमmat_yuv420(
    स्थिर mipi_क्रमmat_t			mipi_क्रमmat)
अणु
	bool	is_yuv420 = (
				(mipi_क्रमmat == MIPI_FORMAT_YUV420_8) ||
				(mipi_क्रमmat == MIPI_FORMAT_YUV420_10) ||
				(mipi_क्रमmat == MIPI_FORMAT_YUV420_8_SHIFT) ||
				(mipi_क्रमmat == MIPI_FORMAT_YUV420_10_SHIFT));
	/* MIPI_FORMAT_YUV420_8_LEGACY is not YUV420 */

	वापस is_yuv420;
पूर्ण

व्योम receiver_set_compression(
    स्थिर rx_ID_t			ID,
    स्थिर अचिन्हित पूर्णांक		cfg_ID,
    स्थिर mipi_compressor_t		comp,
    स्थिर mipi_predictor_t		pred)
अणु
	स्थिर अचिन्हित पूर्णांक		field_id = cfg_ID % N_MIPI_FORMAT_CUSTOM;
	स्थिर अचिन्हित पूर्णांक		ch_id = cfg_ID / N_MIPI_FORMAT_CUSTOM;
	hrt_data			val;
	hrt_address			addr = 0;
	hrt_data			reg;

	निश्चित(ID < N_RX_ID);
	निश्चित(cfg_ID < N_MIPI_COMPRESSOR_CONTEXT);
	निश्चित(field_id < N_MIPI_FORMAT_CUSTOM);
	निश्चित(ch_id < N_RX_CHANNEL_ID);
	निश्चित(comp < N_MIPI_COMPRESSOR_METHODS);
	निश्चित(pred < N_MIPI_PREDICTOR_TYPES);

	val = (((uपूर्णांक8_t)pred) << 3) | comp;

	चयन (ch_id) अणु
	हाल 0:
		addr = ((field_id < 6) ? _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG0_IDX :
			_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG1_IDX);
		अवरोध;
	हाल 1:
		addr = ((field_id < 6) ? _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG0_IDX :
			_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG1_IDX);
		अवरोध;
	हाल 2:
		addr = ((field_id < 6) ? _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG0_IDX :
			_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG1_IDX);
		अवरोध;
	हाल 3:
		addr = ((field_id < 6) ? _HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG0_IDX :
			_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG1_IDX);
		अवरोध;
	शेष:
		/* should not happen */
		निश्चित(false);
		वापस;
	पूर्ण

	reg = ((field_id < 6) ? (val << (field_id * 5)) : (val << ((
		    field_id - 6) * 5)));
	receiver_reg_store(ID, addr, reg);

	वापस;
पूर्ण

व्योम receiver_port_enable(
    स्थिर rx_ID_t			ID,
    स्थिर क्रमागत mipi_port_id		port_ID,
    स्थिर bool			cnd)
अणु
	hrt_data	reg = receiver_port_reg_load(ID, port_ID,
			  _HRT_CSS_RECEIVER_DEVICE_READY_REG_IDX);

	अगर (cnd) अणु
		reg |= 0x01;
	पूर्ण अन्यथा अणु
		reg &= ~0x01;
	पूर्ण

	receiver_port_reg_store(ID, port_ID,
				_HRT_CSS_RECEIVER_DEVICE_READY_REG_IDX, reg);
	वापस;
पूर्ण

bool is_receiver_port_enabled(
    स्थिर rx_ID_t			ID,
    स्थिर क्रमागत mipi_port_id		port_ID)
अणु
	hrt_data	reg = receiver_port_reg_load(ID, port_ID,
			  _HRT_CSS_RECEIVER_DEVICE_READY_REG_IDX);
	वापस ((reg & 0x01) != 0);
पूर्ण

व्योम receiver_irq_enable(
    स्थिर rx_ID_t			ID,
    स्थिर क्रमागत mipi_port_id		port_ID,
    स्थिर rx_irq_info_t		irq_info)
अणु
	receiver_port_reg_store(ID,
				port_ID, _HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX, irq_info);
	वापस;
पूर्ण

rx_irq_info_t receiver_get_irq_info(
    स्थिर rx_ID_t			ID,
    स्थिर क्रमागत mipi_port_id		port_ID)
अणु
	वापस receiver_port_reg_load(ID,
				      port_ID, _HRT_CSS_RECEIVER_IRQ_STATUS_REG_IDX);
पूर्ण

व्योम receiver_irq_clear(
    स्थिर rx_ID_t			ID,
    स्थिर क्रमागत mipi_port_id		port_ID,
    स्थिर rx_irq_info_t		irq_info)
अणु
	receiver_port_reg_store(ID,
				port_ID, _HRT_CSS_RECEIVER_IRQ_STATUS_REG_IDX, irq_info);
	वापस;
पूर्ण

अटल अंतरभूत व्योम capture_unit_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    capture_unit_state_t			*state)
अणु
	निश्चित(/*(sub_id >= CAPTURE_UNIT0_ID) &&*/ (sub_id <= CAPTURE_UNIT2_ID));
	निश्चित(state);

	state->StartMode = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			   sub_id,
			   CAPT_START_MODE_REG_ID);
	state->Start_Addr = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			    sub_id,
			    CAPT_START_ADDR_REG_ID);
	state->Mem_Region_Size = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 CAPT_MEM_REGION_SIZE_REG_ID);
	state->Num_Mem_Regions = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 CAPT_NUM_MEM_REGIONS_REG_ID);
//	AM: Illegal पढ़ो from following रेजिस्टरs.
	/*	state->Init = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			sub_id,
			CAPT_INIT_REG_ID);
		state->Start = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			sub_id,
			CAPT_START_REG_ID);
		state->Stop = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			sub_id,
			CAPT_STOP_REG_ID);
	*/
	state->Packet_Length = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			       sub_id,
			       CAPT_PACKET_LENGTH_REG_ID);
	state->Received_Length = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 CAPT_RECEIVED_LENGTH_REG_ID);
	state->Received_Short_Packets = input_प्रणाली_sub_प्रणाली_reg_load(ID,
					sub_id,
					CAPT_RECEIVED_SHORT_PACKETS_REG_ID);
	state->Received_Long_Packets = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       CAPT_RECEIVED_LONG_PACKETS_REG_ID);
	state->Last_Command = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			      sub_id,
			      CAPT_LAST_COMMAND_REG_ID);
	state->Next_Command = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			      sub_id,
			      CAPT_NEXT_COMMAND_REG_ID);
	state->Last_Acknowledge = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  CAPT_LAST_ACKNOWLEDGE_REG_ID);
	state->Next_Acknowledge = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  CAPT_NEXT_ACKNOWLEDGE_REG_ID);
	state->FSM_State_Info = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				sub_id,
				CAPT_FSM_STATE_INFO_REG_ID);

	वापस;
पूर्ण

अटल अंतरभूत व्योम acquisition_unit_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    acquisition_unit_state_t		*state)
अणु
	निश्चित(sub_id == ACQUISITION_UNIT0_ID);
	निश्चित(state);

	state->Start_Addr = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			    sub_id,
			    ACQ_START_ADDR_REG_ID);
	state->Mem_Region_Size = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 ACQ_MEM_REGION_SIZE_REG_ID);
	state->Num_Mem_Regions = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 ACQ_NUM_MEM_REGIONS_REG_ID);
//	AM: Illegal पढ़ो from following रेजिस्टरs.
	/*	state->Init = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			sub_id,
			ACQ_INIT_REG_ID);
	*/
	state->Received_Short_Packets = input_प्रणाली_sub_प्रणाली_reg_load(ID,
					sub_id,
					ACQ_RECEIVED_SHORT_PACKETS_REG_ID);
	state->Received_Long_Packets = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ACQ_RECEIVED_LONG_PACKETS_REG_ID);
	state->Last_Command = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			      sub_id,
			      ACQ_LAST_COMMAND_REG_ID);
	state->Next_Command = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			      sub_id,
			      ACQ_NEXT_COMMAND_REG_ID);
	state->Last_Acknowledge = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  ACQ_LAST_ACKNOWLEDGE_REG_ID);
	state->Next_Acknowledge = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  ACQ_NEXT_ACKNOWLEDGE_REG_ID);
	state->FSM_State_Info = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				sub_id,
				ACQ_FSM_STATE_INFO_REG_ID);
	state->Int_Cntr_Info = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			       sub_id,
			       ACQ_INT_CNTR_INFO_REG_ID);

	वापस;
पूर्ण

अटल अंतरभूत व्योम ctrl_unit_get_state(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    ctrl_unit_state_t			*state)
अणु
	निश्चित(sub_id == CTRL_UNIT0_ID);
	निश्चित(state);

	state->captA_start_addr = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  ISYS_CTRL_CAPT_START_ADDR_A_REG_ID);
	state->captB_start_addr = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  ISYS_CTRL_CAPT_START_ADDR_B_REG_ID);
	state->captC_start_addr = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				  sub_id,
				  ISYS_CTRL_CAPT_START_ADDR_C_REG_ID);
	state->captA_mem_region_size = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ISYS_CTRL_CAPT_MEM_REGION_SIZE_A_REG_ID);
	state->captB_mem_region_size = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ISYS_CTRL_CAPT_MEM_REGION_SIZE_B_REG_ID);
	state->captC_mem_region_size = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ISYS_CTRL_CAPT_MEM_REGION_SIZE_C_REG_ID);
	state->captA_num_mem_regions = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ISYS_CTRL_CAPT_NUM_MEM_REGIONS_A_REG_ID);
	state->captB_num_mem_regions = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ISYS_CTRL_CAPT_NUM_MEM_REGIONS_B_REG_ID);
	state->captC_num_mem_regions = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				       sub_id,
				       ISYS_CTRL_CAPT_NUM_MEM_REGIONS_C_REG_ID);
	state->acq_start_addr = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				sub_id,
				ISYS_CTRL_ACQ_START_ADDR_REG_ID);
	state->acq_mem_region_size = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				     sub_id,
				     ISYS_CTRL_ACQ_MEM_REGION_SIZE_REG_ID);
	state->acq_num_mem_regions = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				     sub_id,
				     ISYS_CTRL_ACQ_NUM_MEM_REGIONS_REG_ID);
//	AM: Illegal पढ़ो from following रेजिस्टरs.
	/*	state->ctrl_init = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			sub_id,
			ISYS_CTRL_INIT_REG_ID);
	*/
	state->last_cmd = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			  sub_id,
			  ISYS_CTRL_LAST_COMMAND_REG_ID);
	state->next_cmd = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			  sub_id,
			  ISYS_CTRL_NEXT_COMMAND_REG_ID);
	state->last_ack = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			  sub_id,
			  ISYS_CTRL_LAST_ACKNOWLEDGE_REG_ID);
	state->next_ack = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			  sub_id,
			  ISYS_CTRL_NEXT_ACKNOWLEDGE_REG_ID);
	state->top_fsm_state = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			       sub_id,
			       ISYS_CTRL_FSM_STATE_INFO_REG_ID);
	state->captA_fsm_state = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 ISYS_CTRL_CAPT_A_FSM_STATE_INFO_REG_ID);
	state->captB_fsm_state = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 ISYS_CTRL_CAPT_B_FSM_STATE_INFO_REG_ID);
	state->captC_fsm_state = input_प्रणाली_sub_प्रणाली_reg_load(ID,
				 sub_id,
				 ISYS_CTRL_CAPT_C_FSM_STATE_INFO_REG_ID);
	state->acq_fsm_state = input_प्रणाली_sub_प्रणाली_reg_load(ID,
			       sub_id,
			       ISYS_CTRL_ACQ_FSM_STATE_INFO_REG_ID);
	state->capt_reserve_one_mem_region = input_प्रणाली_sub_प्रणाली_reg_load(ID,
					     sub_id,
					     ISYS_CTRL_CAPT_RESERVE_ONE_MEM_REGION_REG_ID);

	वापस;
पूर्ण

अटल अंतरभूत व्योम mipi_port_get_state(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id			port_ID,
    mipi_port_state_t			*state)
अणु
	पूर्णांक	i;

	निश्चित(ID < N_RX_ID);
	निश्चित(port_ID < N_MIPI_PORT_ID);
	निश्चित(state);

	state->device_पढ़ोy = receiver_port_reg_load(ID,
			      port_ID, _HRT_CSS_RECEIVER_DEVICE_READY_REG_IDX);
	state->irq_status = receiver_port_reg_load(ID,
			    port_ID, _HRT_CSS_RECEIVER_IRQ_STATUS_REG_IDX);
	state->irq_enable = receiver_port_reg_load(ID,
			    port_ID, _HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX);
	state->समयout_count = receiver_port_reg_load(ID,
			       port_ID, _HRT_CSS_RECEIVER_TIMEOUT_COUNT_REG_IDX);
	state->init_count = (uपूर्णांक16_t)receiver_port_reg_load(ID,
			    port_ID, _HRT_CSS_RECEIVER_INIT_COUNT_REG_IDX);
	state->raw16_18 = (uपूर्णांक16_t)receiver_port_reg_load(ID,
			  port_ID, _HRT_CSS_RECEIVER_RAW16_18_DATAID_REG_IDX);
	state->sync_count = receiver_port_reg_load(ID,
			    port_ID, _HRT_CSS_RECEIVER_SYNC_COUNT_REG_IDX);
	state->rx_count = receiver_port_reg_load(ID,
			  port_ID, _HRT_CSS_RECEIVER_RX_COUNT_REG_IDX);

	क्रम (i = 0; i < MIPI_4LANE_CFG ; i++) अणु
		state->lane_sync_count[i] = (uपूर्णांक8_t)((state->sync_count) >> (i * 8));
		state->lane_rx_count[i] = (uपूर्णांक8_t)((state->rx_count) >> (i * 8));
	पूर्ण

	वापस;
पूर्ण

अटल अंतरभूत व्योम rx_channel_get_state(
    स्थिर rx_ID_t					ID,
    स्थिर अचिन्हित पूर्णांक				ch_id,
    rx_channel_state_t				*state)
अणु
	पूर्णांक	i;

	निश्चित(ID < N_RX_ID);
	निश्चित(ch_id < N_RX_CHANNEL_ID);
	निश्चित(state);

	चयन (ch_id) अणु
	हाल 0:
		state->comp_scheme0 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG0_IDX);
		state->comp_scheme1 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG1_IDX);
		अवरोध;
	हाल 1:
		state->comp_scheme0 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG0_IDX);
		state->comp_scheme1 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG1_IDX);
		अवरोध;
	हाल 2:
		state->comp_scheme0 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG0_IDX);
		state->comp_scheme1 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG1_IDX);
		अवरोध;
	हाल 3:
		state->comp_scheme0 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG0_IDX);
		state->comp_scheme1 = receiver_reg_load(ID,
							_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG1_IDX);
		अवरोध;
	पूर्ण

	/* See Table 7.1.17,..., 7.1.24 */
	क्रम (i = 0; i < 6; i++) अणु
		u8	val = (uपूर्णांक8_t)((state->comp_scheme0) >> (i * 5)) & 0x1f;

		state->comp[i] = (mipi_compressor_t)(val & 0x07);
		state->pred[i] = (mipi_predictor_t)((val & 0x18) >> 3);
	पूर्ण
	क्रम (i = 6; i < N_MIPI_FORMAT_CUSTOM; i++) अणु
		u8	val = (uपूर्णांक8_t)((state->comp_scheme0) >> ((i - 6) * 5)) & 0x1f;

		state->comp[i] = (mipi_compressor_t)(val & 0x07);
		state->pred[i] = (mipi_predictor_t)((val & 0x18) >> 3);
	पूर्ण

	वापस;
पूर्ण

// MW: "2400" in the name is not good, but this is to aव्योम a naming conflict
अटल input_प्रणाली_cfg2400_t config;

अटल व्योम receiver_rst(
    स्थिर rx_ID_t				ID)
अणु
	क्रमागत mipi_port_id		port_id;

	निश्चित(ID < N_RX_ID);

// Disable all ports.
	क्रम (port_id = MIPI_PORT0_ID; port_id < N_MIPI_PORT_ID; port_id++) अणु
		receiver_port_enable(ID, port_id, false);
	पूर्ण

	// AM: Additional actions क्रम stopping receiver?

	वापस;
पूर्ण

//Single function to reset all the devices mapped via GP_DEVICE.
अटल व्योम gp_device_rst(स्थिर gp_device_ID_t		ID)
अणु
	निश्चित(ID < N_GP_DEVICE_ID);

	gp_device_reg_store(ID, _REG_GP_SYNCGEN_ENABLE_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNCGEN_FREE_RUNNING_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNCGEN_PAUSE_ADDR, ONE);
	// gp_device_reg_store(ID, _REG_GP_NR_FRAMES_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNGEN_NR_PIX_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNGEN_NR_PIX_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNGEN_NR_LINES_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNGEN_HBLANK_CYCLES_ADDR, ZERO);
	// gp_device_reg_store(ID, _REG_GP_SYNGEN_VBLANK_CYCLES_ADDR, ZERO);
// AM: Following calls cause strange warnings. Probably they should not be initialized.
//	gp_device_reg_store(ID, _REG_GP_ISEL_SOF_ADDR, ZERO);
//	gp_device_reg_store(ID, _REG_GP_ISEL_खातापूर्ण_ADDR, ZERO);
//	gp_device_reg_store(ID, _REG_GP_ISEL_SOL_ADDR, ZERO);
//	gp_device_reg_store(ID, _REG_GP_ISEL_EOL_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_LFSR_ENABLE_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_LFSR_ENABLE_B_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_LFSR_RESET_VALUE_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_ENABLE_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_ENABLE_B_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_HOR_CNT_MASK_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_VER_CNT_MASK_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_XY_CNT_MASK_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_HOR_CNT_DELTA_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_VER_CNT_DELTA_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_MODE_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_RED1_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_GREEN1_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_BLUE1_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_RED2_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_GREEN2_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_TPG_BLUE2_ADDR, ZERO);
	//gp_device_reg_store(ID, _REG_GP_ISEL_CH_ID_ADDR, ZERO);
	//gp_device_reg_store(ID, _REG_GP_ISEL_FMT_TYPE_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_DATA_SEL_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_SBAND_SEL_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_SYNC_SEL_ADDR, ZERO);
	//	gp_device_reg_store(ID, _REG_GP_SYNCGEN_HOR_CNT_ADDR, ZERO);
	//	gp_device_reg_store(ID, _REG_GP_SYNCGEN_VER_CNT_ADDR, ZERO);
	//	gp_device_reg_store(ID, _REG_GP_SYNCGEN_FRAME_CNT_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_SOFT_RESET_ADDR,
			    ZERO); // AM: Maybe this soft reset is not safe.

	वापस;
पूर्ण

अटल व्योम input_selector_cfg_क्रम_sensor(स्थिर gp_device_ID_t ID)
अणु
	निश्चित(ID < N_GP_DEVICE_ID);

	gp_device_reg_store(ID, _REG_GP_ISEL_SOF_ADDR, ONE);
	gp_device_reg_store(ID, _REG_GP_ISEL_खातापूर्ण_ADDR, ONE);
	gp_device_reg_store(ID, _REG_GP_ISEL_SOL_ADDR, ONE);
	gp_device_reg_store(ID, _REG_GP_ISEL_EOL_ADDR, ONE);
	gp_device_reg_store(ID, _REG_GP_ISEL_CH_ID_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_FMT_TYPE_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_DATA_SEL_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_SBAND_SEL_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_ISEL_SYNC_SEL_ADDR, ZERO);
	gp_device_reg_store(ID, _REG_GP_SOFT_RESET_ADDR, ZERO);

	वापस;
पूर्ण

अटल व्योम input_चयन_rst(स्थिर gp_device_ID_t ID)
अणु
	पूर्णांक addr;

	निश्चित(ID < N_GP_DEVICE_ID);

	// Initialize the data&hsync LUT.
	क्रम (addr = _REG_GP_IFMT_input_चयन_lut_reg0;
	     addr <= _REG_GP_IFMT_input_चयन_lut_reg7; addr += SIZखातापूर्ण_HRT_REG) अणु
		gp_device_reg_store(ID, addr, ZERO);
	पूर्ण

	// Initialize the vsync LUT.
	gp_device_reg_store(ID,
			    _REG_GP_IFMT_input_चयन_fsync_lut,
			    ZERO);

	वापस;
पूर्ण

अटल व्योम input_चयन_cfg(
    स्थिर gp_device_ID_t			ID,
    स्थिर input_चयन_cfg_t *स्थिर cfg)
अणु
	पूर्णांक addr_offset;

	निश्चित(ID < N_GP_DEVICE_ID);
	निश्चित(cfg);

	// Initialize the data&hsync LUT.
	क्रम (addr_offset = 0; addr_offset < N_RX_CHANNEL_ID * 2; addr_offset++) अणु
		निश्चित(addr_offset * SIZखातापूर्ण_HRT_REG + _REG_GP_IFMT_input_चयन_lut_reg0 <=
		       _REG_GP_IFMT_input_चयन_lut_reg7);
		gp_device_reg_store(ID,
				    _REG_GP_IFMT_input_चयन_lut_reg0 + addr_offset * SIZखातापूर्ण_HRT_REG,
				    cfg->hsync_data_reg[addr_offset]);
	पूर्ण

	// Initialize the vsync LUT.
	gp_device_reg_store(ID,
			    _REG_GP_IFMT_input_चयन_fsync_lut,
			    cfg->vsync_data_reg);

	वापस;
पूर्ण

अटल व्योम input_प्रणाली_network_rst(स्थिर input_प्रणाली_ID_t ID)
अणु
	अचिन्हित पूर्णांक sub_id;

	// Reset all 3 multicasts.
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MULTICAST_A_IDX,
					  INPUT_SYSTEM_DISCARD_ALL);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MULTICAST_B_IDX,
					  INPUT_SYSTEM_DISCARD_ALL);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MULTICAST_C_IDX,
					  INPUT_SYSTEM_DISCARD_ALL);

	// Reset stream mux.
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MUX_IDX,
					  N_INPUT_SYSTEM_MULTIPLEX);

	// Reset 3 capture units.
	क्रम (sub_id = CAPTURE_UNIT0_ID; sub_id < CAPTURE_UNIT0_ID + N_CAPTURE_UNIT_ID;
	     sub_id++) अणु
		input_प्रणाली_sub_प्रणाली_reg_store(ID,
						  sub_id,
						  CAPT_INIT_REG_ID,
						  1U << CAPT_INIT_RST_REG_BIT);
	पूर्ण

	// Reset acquisition unit.
	क्रम (sub_id = ACQUISITION_UNIT0_ID;
	     sub_id < ACQUISITION_UNIT0_ID + N_ACQUISITION_UNIT_ID; sub_id++) अणु
		input_प्रणाली_sub_प्रणाली_reg_store(ID,
						  sub_id,
						  ACQ_INIT_REG_ID,
						  1U << ACQ_INIT_RST_REG_BIT);
	पूर्ण

	// DMA unit reset is not needed.

	// Reset controller units.
	// NB: In future we need to keep part of ctrl_state क्रम split capture and
	क्रम (sub_id = CTRL_UNIT0_ID; sub_id < CTRL_UNIT0_ID + N_CTRL_UNIT_ID;
	     sub_id++) अणु
		input_प्रणाली_sub_प्रणाली_reg_store(ID,
						  sub_id,
						  ISYS_CTRL_INIT_REG_ID,
						  1U); //AM: Is there any named स्थिरant?
	पूर्ण

	वापस;
पूर्ण

// Function that resets current configuration.
input_प्रणाली_err_t input_प्रणाली_configuration_reset(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	receiver_rst(RX0_ID);

	input_प्रणाली_network_rst(INPUT_SYSTEM0_ID);

	gp_device_rst(GP_DEVICE0_ID);

	input_चयन_rst(GP_DEVICE0_ID);

	//target_rst();

	// Reset IRQ_CTRLs.

	// Reset configuration data काष्ठाures.
	क्रम (i = 0; i < N_CHANNELS; i++) अणु
		config.ch_flags[i] = INPUT_SYSTEM_CFG_FLAG_RESET;
		config.target_isp_flags[i] = INPUT_SYSTEM_CFG_FLAG_RESET;
		config.target_sp_flags[i] = INPUT_SYSTEM_CFG_FLAG_RESET;
		config.target_strm2mem_flags[i] = INPUT_SYSTEM_CFG_FLAG_RESET;
	पूर्ण

	क्रम (i = 0; i < N_CSI_PORTS; i++) अणु
		config.csi_buffer_flags[i]	 = INPUT_SYSTEM_CFG_FLAG_RESET;
		config.multicast[i]		 = INPUT_SYSTEM_DISCARD_ALL;
	पूर्ण

	config.source_type_flags				 = INPUT_SYSTEM_CFG_FLAG_RESET;
	config.acquisition_buffer_unique_flags	 = INPUT_SYSTEM_CFG_FLAG_RESET;
	config.unallocated_ib_mem_words			 = IB_CAPACITY_IN_WORDS;
	//config.acq_allocated_ib_mem_words		 = 0;

	// Set the start of the session cofiguration.
	config.session_flags = INPUT_SYSTEM_CFG_FLAG_REQUIRED;

	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// MW: Comments are good, but करोxygen is required, place it at the declaration
// Function that appends the channel to current configuration.
अटल input_प्रणाली_err_t input_प्रणाली_configure_channel(
    स्थिर channel_cfg_t		channel)
अणु
	input_प्रणाली_err_t error = INPUT_SYSTEM_ERR_NO_ERROR;
	// Check अगर channel is not alपढ़ोy configured.
	अगर (config.ch_flags[channel.ch_id] & INPUT_SYSTEM_CFG_FLAG_SET) अणु
		वापस INPUT_SYSTEM_ERR_CHANNEL_ALREADY_SET;
	पूर्ण अन्यथा अणु
		चयन (channel.source_type) अणु
		हाल INPUT_SYSTEM_SOURCE_SENSOR:
			error = input_प्रणाली_configure_channel_sensor(channel);
			अवरोध;
		हाल INPUT_SYSTEM_SOURCE_TPG:
			वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
			अवरोध;
		हाल INPUT_SYSTEM_SOURCE_PRBS:
			वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
			अवरोध;
		हाल INPUT_SYSTEM_SOURCE_FIFO:
			वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
			अवरोध;
		शेष:
			वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
			अवरोध;
		पूर्ण

		अगर (error != INPUT_SYSTEM_ERR_NO_ERROR) वापस error;
		// Input चयन channel configurations must be combined in united config.
		config.input_चयन_cfg.hsync_data_reg[channel.source_cfg.csi_cfg.csi_port * 2]
		    =
			channel.target_cfg.input_चयन_channel_cfg.hsync_data_reg[0];
		config.input_चयन_cfg.hsync_data_reg[channel.source_cfg.csi_cfg.csi_port * 2 +
											   1] =
							       channel.target_cfg.input_चयन_channel_cfg.hsync_data_reg[1];
		config.input_चयन_cfg.vsync_data_reg |=
		    (channel.target_cfg.input_चयन_channel_cfg.vsync_data_reg & 0x7) <<
		    (channel.source_cfg.csi_cfg.csi_port * 3);

		// Other tarमाला_लो are just copied and marked as set.
		config.target_isp[channel.source_cfg.csi_cfg.csi_port] =
		    channel.target_cfg.target_isp_cfg;
		config.target_sp[channel.source_cfg.csi_cfg.csi_port] =
		    channel.target_cfg.target_sp_cfg;
		config.target_strm2mem[channel.source_cfg.csi_cfg.csi_port] =
		    channel.target_cfg.target_strm2mem_cfg;
		config.target_isp_flags[channel.source_cfg.csi_cfg.csi_port] |=
		    INPUT_SYSTEM_CFG_FLAG_SET;
		config.target_sp_flags[channel.source_cfg.csi_cfg.csi_port] |=
		    INPUT_SYSTEM_CFG_FLAG_SET;
		config.target_strm2mem_flags[channel.source_cfg.csi_cfg.csi_port] |=
		    INPUT_SYSTEM_CFG_FLAG_SET;

		config.ch_flags[channel.ch_id] = INPUT_SYSTEM_CFG_FLAG_SET;
	पूर्ण
	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// Function that partitions input buffer space with determining addresses.
अटल input_प्रणाली_err_t input_buffer_configuration(व्योम)
अणु
	u32 current_address    = 0;
	u32 unallocated_memory = IB_CAPACITY_IN_WORDS;

	isp2400_ib_buffer_t	candidate_buffer_acq  = IB_BUFFER_शून्य;
	u32 size_requested;
	input_प्रणाली_config_flags_t	acq_alपढ़ोy_specअगरied = INPUT_SYSTEM_CFG_FLAG_RESET;
	input_प्रणाली_csi_port_t port;

	क्रम (port = INPUT_SYSTEM_PORT_A; port < N_INPUT_SYSTEM_PORTS; port++) अणु
		csi_cfg_t source = config.csi_value[port];//.csi_cfg;

		अगर (config.csi_flags[port] & INPUT_SYSTEM_CFG_FLAG_SET) अणु
			// Check and set csi buffer in input buffer.
			चयन (source.buffering_mode) अणु
			हाल INPUT_SYSTEM_FIFO_CAPTURE:
			हाल INPUT_SYSTEM_XMEM_ACQUIRE:
				config.csi_buffer_flags[port] =
				    INPUT_SYSTEM_CFG_FLAG_BLOCKED; // Well, not used.
				अवरोध;

			हाल INPUT_SYSTEM_FIFO_CAPTURE_WITH_COUNTING:
			हाल INPUT_SYSTEM_SRAM_BUFFERING:
			हाल INPUT_SYSTEM_XMEM_BUFFERING:
			हाल INPUT_SYSTEM_XMEM_CAPTURE:
				size_requested = source.csi_buffer.mem_reg_size *
						 source.csi_buffer.nof_mem_regs;
				अगर (source.csi_buffer.mem_reg_size > 0
				    && source.csi_buffer.nof_mem_regs > 0
				    && size_requested <= unallocated_memory
				   ) अणु
					config.csi_buffer[port].mem_reg_addr = current_address;
					config.csi_buffer[port].mem_reg_size = source.csi_buffer.mem_reg_size;
					config.csi_buffer[port].nof_mem_regs = source.csi_buffer.nof_mem_regs;
					current_address		+= size_requested;
					unallocated_memory	-= size_requested;
					config.csi_buffer_flags[port] = INPUT_SYSTEM_CFG_FLAG_SET;
				पूर्ण अन्यथा अणु
					config.csi_buffer_flags[port] |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
					वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
				पूर्ण
				अवरोध;

			शेष:
				config.csi_buffer_flags[port] |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
				वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
				अवरोध;
			पूर्ण

			// Check acquisition buffer specअगरied but set it later since it has to be unique.
			चयन (source.buffering_mode) अणु
			हाल INPUT_SYSTEM_FIFO_CAPTURE:
			हाल INPUT_SYSTEM_SRAM_BUFFERING:
			हाल INPUT_SYSTEM_XMEM_CAPTURE:
				// Nothing to करो.
				अवरोध;

			हाल INPUT_SYSTEM_FIFO_CAPTURE_WITH_COUNTING:
			हाल INPUT_SYSTEM_XMEM_BUFFERING:
			हाल INPUT_SYSTEM_XMEM_ACQUIRE:
				अगर (acq_alपढ़ोy_specअगरied == INPUT_SYSTEM_CFG_FLAG_RESET) अणु
					size_requested = source.acquisition_buffer.mem_reg_size
							 * source.acquisition_buffer.nof_mem_regs;
					अगर (source.acquisition_buffer.mem_reg_size > 0
					    && source.acquisition_buffer.nof_mem_regs > 0
					    && size_requested <= unallocated_memory
					   ) अणु
						candidate_buffer_acq = source.acquisition_buffer;
						acq_alपढ़ोy_specअगरied = INPUT_SYSTEM_CFG_FLAG_SET;
					पूर्ण
				पूर्ण अन्यथा अणु
					// Check अगर specअगरied acquisition buffer is the same as specअगरied beक्रमe.
					अगर (source.acquisition_buffer.mem_reg_size != candidate_buffer_acq.mem_reg_size
					    || source.acquisition_buffer.nof_mem_regs !=  candidate_buffer_acq.nof_mem_regs
					   ) अणु
						config.acquisition_buffer_unique_flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
						वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
					पूर्ण
				पूर्ण
				अवरोध;

			शेष:
				वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			config.csi_buffer_flags[port] = INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		पूर्ण
	पूर्ण // end of क्रम ( port )

	// Set the acquisition buffer at the end.
	size_requested = candidate_buffer_acq.mem_reg_size *
			 candidate_buffer_acq.nof_mem_regs;
	अगर (acq_alपढ़ोy_specअगरied == INPUT_SYSTEM_CFG_FLAG_SET
	    && size_requested <= unallocated_memory) अणु
		config.acquisition_buffer_unique.mem_reg_addr = current_address;
		config.acquisition_buffer_unique.mem_reg_size =
		    candidate_buffer_acq.mem_reg_size;
		config.acquisition_buffer_unique.nof_mem_regs =
		    candidate_buffer_acq.nof_mem_regs;
		current_address		+= size_requested;
		unallocated_memory	-= size_requested;
		config.acquisition_buffer_unique_flags = INPUT_SYSTEM_CFG_FLAG_SET;

		निश्चित(current_address <= IB_CAPACITY_IN_WORDS);
	पूर्ण

	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

अटल व्योम capture_unit_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    स्थिर isp2400_ib_buffer_t *स्थिर cfg)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(/*(sub_id >= CAPTURE_UNIT0_ID) &&*/ (sub_id <=
		CAPTURE_UNIT2_ID)); // Commented part is always true.
	निश्चित(cfg);

	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  CAPT_START_ADDR_REG_ID,
					  cfg->mem_reg_addr);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  CAPT_MEM_REGION_SIZE_REG_ID,
					  cfg->mem_reg_size);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  CAPT_NUM_MEM_REGIONS_REG_ID,
					  cfg->nof_mem_regs);

	वापस;
पूर्ण

अटल व्योम acquisition_unit_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    स्थिर isp2400_ib_buffer_t *स्थिर cfg)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(sub_id == ACQUISITION_UNIT0_ID);
	निश्चित(cfg);

	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ACQ_START_ADDR_REG_ID,
					  cfg->mem_reg_addr);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ACQ_NUM_MEM_REGIONS_REG_ID,
					  cfg->nof_mem_regs);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ACQ_MEM_REGION_SIZE_REG_ID,
					  cfg->mem_reg_size);

	वापस;
पूर्ण

अटल व्योम ctrl_unit_configure(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_id,
    स्थिर ctrl_unit_cfg_t *स्थिर cfg)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(sub_id == CTRL_UNIT0_ID);
	निश्चित(cfg);

	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_START_ADDR_A_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT0_ID].mem_reg_addr);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_MEM_REGION_SIZE_A_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT0_ID].mem_reg_size);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_NUM_MEM_REGIONS_A_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT0_ID].nof_mem_regs);

	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_START_ADDR_B_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT1_ID].mem_reg_addr);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_MEM_REGION_SIZE_B_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT1_ID].mem_reg_size);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_NUM_MEM_REGIONS_B_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT1_ID].nof_mem_regs);

	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_START_ADDR_C_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT2_ID].mem_reg_addr);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_MEM_REGION_SIZE_C_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT2_ID].mem_reg_size);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_NUM_MEM_REGIONS_C_REG_ID,
					  cfg->buffer_mipi[CAPTURE_UNIT2_ID].nof_mem_regs);

	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_ACQ_START_ADDR_REG_ID,
					  cfg->buffer_acquire[ACQUISITION_UNIT0_ID - ACQUISITION_UNIT0_ID].mem_reg_addr);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_ACQ_MEM_REGION_SIZE_REG_ID,
					  cfg->buffer_acquire[ACQUISITION_UNIT0_ID - ACQUISITION_UNIT0_ID].mem_reg_size);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_ACQ_NUM_MEM_REGIONS_REG_ID,
					  cfg->buffer_acquire[ACQUISITION_UNIT0_ID - ACQUISITION_UNIT0_ID].nof_mem_regs);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  sub_id,
					  ISYS_CTRL_CAPT_RESERVE_ONE_MEM_REGION_REG_ID,
					  0);
	वापस;
पूर्ण

अटल व्योम input_प्रणाली_network_configure(
    स्थिर input_प्रणाली_ID_t				ID,
    स्थिर input_प्रणाली_network_cfg_t *स्थिर cfg)
अणु
	u32 sub_id;

	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(cfg);

	// Set all 3 multicasts.
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MULTICAST_A_IDX,
					  cfg->multicast_cfg[CAPTURE_UNIT0_ID]);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MULTICAST_B_IDX,
					  cfg->multicast_cfg[CAPTURE_UNIT1_ID]);
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MULTICAST_C_IDX,
					  cfg->multicast_cfg[CAPTURE_UNIT2_ID]);

	// Set stream mux.
	input_प्रणाली_sub_प्रणाली_reg_store(ID,
					  GPREGS_UNIT0_ID,
					  HIVE_ISYS_GPREG_MUX_IDX,
					  cfg->mux_cfg);

	// Set capture units.
	क्रम (sub_id = CAPTURE_UNIT0_ID; sub_id < CAPTURE_UNIT0_ID + N_CAPTURE_UNIT_ID;
	     sub_id++) अणु
		capture_unit_configure(ID,
				       sub_id,
				       &cfg->ctrl_unit_cfg[ID].buffer_mipi[sub_id - CAPTURE_UNIT0_ID]);
	पूर्ण

	// Set acquisition units.
	क्रम (sub_id = ACQUISITION_UNIT0_ID;
	     sub_id < ACQUISITION_UNIT0_ID + N_ACQUISITION_UNIT_ID; sub_id++) अणु
		acquisition_unit_configure(ID,
					   sub_id,
					   &cfg->ctrl_unit_cfg[sub_id - ACQUISITION_UNIT0_ID].buffer_acquire[sub_id -
						   ACQUISITION_UNIT0_ID]);
	पूर्ण

	// No DMA configuration needed. Ctrl_unit will fully control it.

	// Set controller units.
	क्रम (sub_id = CTRL_UNIT0_ID; sub_id < CTRL_UNIT0_ID + N_CTRL_UNIT_ID;
	     sub_id++) अणु
		ctrl_unit_configure(ID,
				    sub_id,
				    &cfg->ctrl_unit_cfg[sub_id - CTRL_UNIT0_ID]);
	पूर्ण

	वापस;
पूर्ण

अटल input_प्रणाली_err_t configuration_to_रेजिस्टरs(व्योम)
अणु
	input_प्रणाली_network_cfg_t input_प्रणाली_network_cfg;
	पूर्णांक i;

	निश्चित(config.source_type_flags & INPUT_SYSTEM_CFG_FLAG_SET);

	चयन (config.source_type) अणु
	हाल INPUT_SYSTEM_SOURCE_SENSOR:

		// Determine stream multicasts setting based on the mode of csi_cfg_t.
		// AM: This should be moved towards earlier function call, e.g. in
		// the commit function.
		क्रम (i = MIPI_PORT0_ID; i < N_MIPI_PORT_ID; i++) अणु
			अगर (config.csi_flags[i] & INPUT_SYSTEM_CFG_FLAG_SET) अणु
				चयन (config.csi_value[i].buffering_mode) अणु
				हाल INPUT_SYSTEM_FIFO_CAPTURE:
					config.multicast[i] = INPUT_SYSTEM_CSI_BACKEND;
					अवरोध;

				हाल INPUT_SYSTEM_XMEM_CAPTURE:
				हाल INPUT_SYSTEM_SRAM_BUFFERING:
				हाल INPUT_SYSTEM_XMEM_BUFFERING:
					config.multicast[i] = INPUT_SYSTEM_INPUT_BUFFER;
					अवरोध;

				हाल INPUT_SYSTEM_FIFO_CAPTURE_WITH_COUNTING:
					config.multicast[i] = INPUT_SYSTEM_MULTICAST;
					अवरोध;

				हाल INPUT_SYSTEM_XMEM_ACQUIRE:
					config.multicast[i] = INPUT_SYSTEM_DISCARD_ALL;
					अवरोध;

				शेष:
					config.multicast[i] = INPUT_SYSTEM_DISCARD_ALL;
					वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
					//अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				config.multicast[i] = INPUT_SYSTEM_DISCARD_ALL;
			पूर्ण

			input_प्रणाली_network_cfg.multicast_cfg[i] = config.multicast[i];

		पूर्ण // क्रम

		input_प्रणाली_network_cfg.mux_cfg = config.multiplexer;

		input_प्रणाली_network_cfg.ctrl_unit_cfg[CTRL_UNIT0_ID -
						       CTRL_UNIT0_ID].buffer_mipi[CAPTURE_UNIT0_ID] =
							       config.csi_buffer[MIPI_PORT0_ID];
		input_प्रणाली_network_cfg.ctrl_unit_cfg[CTRL_UNIT0_ID -
						       CTRL_UNIT0_ID].buffer_mipi[CAPTURE_UNIT1_ID] =
							       config.csi_buffer[MIPI_PORT1_ID];
		input_प्रणाली_network_cfg.ctrl_unit_cfg[CTRL_UNIT0_ID -
						       CTRL_UNIT0_ID].buffer_mipi[CAPTURE_UNIT2_ID] =
							       config.csi_buffer[MIPI_PORT2_ID];
		input_प्रणाली_network_cfg.ctrl_unit_cfg[CTRL_UNIT0_ID -
						       CTRL_UNIT0_ID].buffer_acquire[ACQUISITION_UNIT0_ID -
							       ACQUISITION_UNIT0_ID] =
								       config.acquisition_buffer_unique;

		// First set input network around CSI receiver.
		input_प्रणाली_network_configure(INPUT_SYSTEM0_ID, &input_प्रणाली_network_cfg);

		// Set the CSI receiver.
		//...
		अवरोध;

	हाल INPUT_SYSTEM_SOURCE_TPG:

		अवरोध;

	हाल INPUT_SYSTEM_SOURCE_PRBS:

		अवरोध;

	हाल INPUT_SYSTEM_SOURCE_FIFO:
		अवरोध;

	शेष:
		वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
		अवरोध;

	पूर्ण // end of चयन (source_type)

	// Set input selector.
	input_selector_cfg_क्रम_sensor(GP_DEVICE0_ID);

	// Set input चयन.
	input_चयन_cfg(GP_DEVICE0_ID, &config.input_चयन_cfg);

	// Set input क्रमmatters.
	// AM: IF are set dynamically.
	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// Function that applies the whole configuration.
input_प्रणाली_err_t input_प्रणाली_configuration_commit(व्योम)
अणु
	// The last configuration step is to configure the input buffer.
	input_प्रणाली_err_t error = input_buffer_configuration();

	अगर (error != INPUT_SYSTEM_ERR_NO_ERROR) अणु
		वापस error;
	पूर्ण

	// Translate the whole configuration पूर्णांकo रेजिस्टरs.
	error = configuration_to_रेजिस्टरs();
	अगर (error != INPUT_SYSTEM_ERR_NO_ERROR) अणु
		वापस error;
	पूर्ण

	// Translate the whole configuration पूर्णांकo ctrl commands etc.

	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// FIFO

input_प्रणाली_err_t	input_प्रणाली_csi_fअगरo_channel_cfg(
    u32		ch_id,
    input_प्रणाली_csi_port_t	port,
    backend_channel_cfg_t	backend_ch,
    target_cfg2400_t	target
)
अणु
	channel_cfg_t channel;

	channel.ch_id	= ch_id;
	channel.backend_ch	= backend_ch;
	channel.source_type = INPUT_SYSTEM_SOURCE_SENSOR;
	//channel.source
	channel.source_cfg.csi_cfg.csi_port			= port;
	channel.source_cfg.csi_cfg.buffering_mode	= INPUT_SYSTEM_FIFO_CAPTURE;
	channel.source_cfg.csi_cfg.csi_buffer			= IB_BUFFER_शून्य;
	channel.source_cfg.csi_cfg.acquisition_buffer	= IB_BUFFER_शून्य;
	channel.source_cfg.csi_cfg.nof_xmem_buffers	= 0;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

input_प्रणाली_err_t	input_प्रणाली_csi_fअगरo_channel_with_counting_cfg(
    u32				ch_id,
    u32				nof_frames,
    input_प्रणाली_csi_port_t			port,
    backend_channel_cfg_t			backend_ch,
    u32				csi_mem_reg_size,
    u32				csi_nof_mem_regs,
    target_cfg2400_t			target
)
अणु
	channel_cfg_t channel;

	channel.ch_id	= ch_id;
	channel.backend_ch	= backend_ch;
	channel.source_type		= INPUT_SYSTEM_SOURCE_SENSOR;
	//channel.source
	channel.source_cfg.csi_cfg.csi_port			= port;
	channel.source_cfg.csi_cfg.buffering_mode	=
	    INPUT_SYSTEM_FIFO_CAPTURE_WITH_COUNTING;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_size		= csi_mem_reg_size;
	channel.source_cfg.csi_cfg.csi_buffer.nof_mem_regs		= csi_nof_mem_regs;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_addr		= 0;
	channel.source_cfg.csi_cfg.acquisition_buffer			= IB_BUFFER_शून्य;
	channel.source_cfg.csi_cfg.nof_xmem_buffers	= nof_frames;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

// SRAM

input_प्रणाली_err_t	input_प्रणाली_csi_sram_channel_cfg(
    u32				ch_id,
    input_प्रणाली_csi_port_t			port,
    backend_channel_cfg_t			backend_ch,
    u32				csi_mem_reg_size,
    u32				csi_nof_mem_regs,
    //	uपूर्णांक32_t				acq_mem_reg_size,
    //	uपूर्णांक32_t				acq_nof_mem_regs,
    target_cfg2400_t			target
)
अणु
	channel_cfg_t channel;

	channel.ch_id	= ch_id;
	channel.backend_ch	= backend_ch;
	channel.source_type		= INPUT_SYSTEM_SOURCE_SENSOR;
	//channel.source
	channel.source_cfg.csi_cfg.csi_port			= port;
	channel.source_cfg.csi_cfg.buffering_mode	= INPUT_SYSTEM_SRAM_BUFFERING;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_size		= csi_mem_reg_size;
	channel.source_cfg.csi_cfg.csi_buffer.nof_mem_regs		= csi_nof_mem_regs;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_addr		= 0;
	channel.source_cfg.csi_cfg.acquisition_buffer			= IB_BUFFER_शून्य;
	channel.source_cfg.csi_cfg.nof_xmem_buffers	= 0;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

//XMEM

// Collects all parameters and माला_दो them in channel_cfg_t.
input_प्रणाली_err_t	input_प्रणाली_csi_xmem_channel_cfg(
    u32				ch_id,
    input_प्रणाली_csi_port_t			port,
    backend_channel_cfg_t			backend_ch,
    u32				csi_mem_reg_size,
    u32				csi_nof_mem_regs,
    u32				acq_mem_reg_size,
    u32				acq_nof_mem_regs,
    target_cfg2400_t			target,
    uपूर्णांक32_t				nof_xmem_buffers
)
अणु
	channel_cfg_t channel;

	channel.ch_id	= ch_id;
	channel.backend_ch	= backend_ch;
	channel.source_type		= INPUT_SYSTEM_SOURCE_SENSOR;
	//channel.source
	channel.source_cfg.csi_cfg.csi_port			= port;
	channel.source_cfg.csi_cfg.buffering_mode	= INPUT_SYSTEM_XMEM_BUFFERING;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_size		= csi_mem_reg_size;
	channel.source_cfg.csi_cfg.csi_buffer.nof_mem_regs		= csi_nof_mem_regs;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_addr		= 0;
	channel.source_cfg.csi_cfg.acquisition_buffer.mem_reg_size	= acq_mem_reg_size;
	channel.source_cfg.csi_cfg.acquisition_buffer.nof_mem_regs	= acq_nof_mem_regs;
	channel.source_cfg.csi_cfg.acquisition_buffer.mem_reg_addr	= 0;
	channel.source_cfg.csi_cfg.nof_xmem_buffers	= nof_xmem_buffers;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

input_प्रणाली_err_t	input_प्रणाली_csi_xmem_acquire_only_channel_cfg(
    u32				ch_id,
    u32				nof_frames,
    input_प्रणाली_csi_port_t			port,
    backend_channel_cfg_t			backend_ch,
    u32				acq_mem_reg_size,
    u32				acq_nof_mem_regs,
    target_cfg2400_t			target)
अणु
	channel_cfg_t channel;

	channel.ch_id	= ch_id;
	channel.backend_ch	= backend_ch;
	channel.source_type		= INPUT_SYSTEM_SOURCE_SENSOR;
	//channel.source
	channel.source_cfg.csi_cfg.csi_port			= port;
	channel.source_cfg.csi_cfg.buffering_mode	= INPUT_SYSTEM_XMEM_ACQUIRE;
	channel.source_cfg.csi_cfg.csi_buffer		= IB_BUFFER_शून्य;
	channel.source_cfg.csi_cfg.acquisition_buffer.mem_reg_size	= acq_mem_reg_size;
	channel.source_cfg.csi_cfg.acquisition_buffer.nof_mem_regs	= acq_nof_mem_regs;
	channel.source_cfg.csi_cfg.acquisition_buffer.mem_reg_addr	= 0;
	channel.source_cfg.csi_cfg.nof_xmem_buffers	= nof_frames;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

input_प्रणाली_err_t	input_प्रणाली_csi_xmem_capture_only_channel_cfg(
    u32				ch_id,
    u32				nof_frames,
    input_प्रणाली_csi_port_t			port,
    u32				csi_mem_reg_size,
    u32				csi_nof_mem_regs,
    u32				acq_mem_reg_size,
    u32				acq_nof_mem_regs,
    target_cfg2400_t			target)
अणु
	channel_cfg_t channel;

	channel.ch_id	= ch_id;
	//channel.backend_ch	= backend_ch;
	channel.source_type		= INPUT_SYSTEM_SOURCE_SENSOR;
	//channel.source
	channel.source_cfg.csi_cfg.csi_port			= port;
	//channel.source_cfg.csi_cfg.backend_ch		= backend_ch;
	channel.source_cfg.csi_cfg.buffering_mode	= INPUT_SYSTEM_XMEM_CAPTURE;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_size		= csi_mem_reg_size;
	channel.source_cfg.csi_cfg.csi_buffer.nof_mem_regs		= csi_nof_mem_regs;
	channel.source_cfg.csi_cfg.csi_buffer.mem_reg_addr		= 0;
	channel.source_cfg.csi_cfg.acquisition_buffer.mem_reg_size	= acq_mem_reg_size;
	channel.source_cfg.csi_cfg.acquisition_buffer.nof_mem_regs	= acq_nof_mem_regs;
	channel.source_cfg.csi_cfg.acquisition_buffer.mem_reg_addr	= 0;
	channel.source_cfg.csi_cfg.nof_xmem_buffers	= nof_frames;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

// Non - CSI

input_प्रणाली_err_t	input_प्रणाली_prbs_channel_cfg(
    u32		ch_id,
    u32		nof_frames,//not used yet
    u32		seed,
    u32		sync_gen_width,
    u32		sync_gen_height,
    u32		sync_gen_hblank_cycles,
    u32		sync_gen_vblank_cycles,
    target_cfg2400_t	target
)
अणु
	channel_cfg_t channel;

	(व्योम)nof_frames;

	channel.ch_id	= ch_id;
	channel.source_type = INPUT_SYSTEM_SOURCE_PRBS;

	channel.source_cfg.prbs_cfg.seed = seed;
	channel.source_cfg.prbs_cfg.sync_gen_cfg.width		= sync_gen_width;
	channel.source_cfg.prbs_cfg.sync_gen_cfg.height		= sync_gen_height;
	channel.source_cfg.prbs_cfg.sync_gen_cfg.hblank_cycles	= sync_gen_hblank_cycles;
	channel.source_cfg.prbs_cfg.sync_gen_cfg.vblank_cycles	= sync_gen_vblank_cycles;

	channel.target_cfg	= target;

	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

input_प्रणाली_err_t	input_प्रणाली_tpg_channel_cfg(
    u32		ch_id,
    u32		nof_frames,//not used yet
    u32		x_mask,
    u32		y_mask,
    u32		x_delta,
    u32		y_delta,
    u32		xy_mask,
    u32		sync_gen_width,
    u32		sync_gen_height,
    u32		sync_gen_hblank_cycles,
    u32		sync_gen_vblank_cycles,
    target_cfg2400_t	target
)
अणु
	channel_cfg_t channel;

	(व्योम)nof_frames;

	channel.ch_id	= ch_id;
	channel.source_type		= INPUT_SYSTEM_SOURCE_TPG;

	channel.source_cfg.tpg_cfg.x_mask	= x_mask;
	channel.source_cfg.tpg_cfg.y_mask	= y_mask;
	channel.source_cfg.tpg_cfg.x_delta	= x_delta;
	channel.source_cfg.tpg_cfg.y_delta	= y_delta;
	channel.source_cfg.tpg_cfg.xy_mask	= xy_mask;
	channel.source_cfg.tpg_cfg.sync_gen_cfg.width		= sync_gen_width;
	channel.source_cfg.tpg_cfg.sync_gen_cfg.height		= sync_gen_height;
	channel.source_cfg.tpg_cfg.sync_gen_cfg.hblank_cycles	= sync_gen_hblank_cycles;
	channel.source_cfg.tpg_cfg.sync_gen_cfg.vblank_cycles	= sync_gen_vblank_cycles;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

// MW: Don't use प्रणाली specअगरic names, (even in प्रणाली specअगरic files) "cfg2400" -> cfg
input_प्रणाली_err_t	input_प्रणाली_gpfअगरo_channel_cfg(
    u32		ch_id,
    u32		nof_frames, //not used yet

    target_cfg2400_t	target)
अणु
	channel_cfg_t channel;

	(व्योम)nof_frames;

	channel.ch_id	= ch_id;
	channel.source_type	= INPUT_SYSTEM_SOURCE_FIFO;

	channel.target_cfg	= target;
	वापस input_प्रणाली_configure_channel(channel);
पूर्ण

///////////////////////////////////////////////////////////////////////////
//
// Private specialized functions क्रम channel setting.
//
///////////////////////////////////////////////////////////////////////////

// Fills the parameters to config.csi_value[port]
अटल input_प्रणाली_err_t input_प्रणाली_configure_channel_sensor(
    स्थिर channel_cfg_t channel)
अणु
	स्थिर u32 port = channel.source_cfg.csi_cfg.csi_port;
	input_प्रणाली_err_t status = INPUT_SYSTEM_ERR_NO_ERROR;

	input_प्रणाली_multiplex_t mux;

	अगर (port >= N_INPUT_SYSTEM_PORTS)
		वापस INPUT_SYSTEM_ERR_GENERIC;

	//check अगर port > N_INPUT_SYSTEM_MULTIPLEX

	status = set_source_type(&config.source_type, channel.source_type,
				 &config.source_type_flags);
	अगर (status != INPUT_SYSTEM_ERR_NO_ERROR) वापस status;

	// Check क्रम conflicts on source (implicitly on multicast, capture unit and input buffer).

	status = set_csi_cfg(&config.csi_value[port], &channel.source_cfg.csi_cfg,
			     &config.csi_flags[port]);
	अगर (status != INPUT_SYSTEM_ERR_NO_ERROR) वापस status;

	चयन (channel.source_cfg.csi_cfg.buffering_mode) अणु
	हाल INPUT_SYSTEM_FIFO_CAPTURE:

		// Check क्रम conflicts on mux.
		mux = INPUT_SYSTEM_MIPI_PORT0 + port;
		status = input_प्रणाली_multiplexer_cfg(&config.multiplexer, mux,
						      &config.multiplexer_flags);
		अगर (status != INPUT_SYSTEM_ERR_NO_ERROR) वापस status;
		config.multicast[port] = INPUT_SYSTEM_CSI_BACKEND;

		// Shared resource, so it should be blocked.
		//config.mux_flags |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		//config.csi_buffer_flags[port] |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		//config.acquisition_buffer_unique_flags |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;

		अवरोध;
	हाल INPUT_SYSTEM_SRAM_BUFFERING:

		// Check क्रम conflicts on mux.
		mux = INPUT_SYSTEM_ACQUISITION_UNIT;
		status = input_प्रणाली_multiplexer_cfg(&config.multiplexer, mux,
						      &config.multiplexer_flags);
		अगर (status != INPUT_SYSTEM_ERR_NO_ERROR) वापस status;
		config.multicast[port] = INPUT_SYSTEM_INPUT_BUFFER;

		// Shared resource, so it should be blocked.
		//config.mux_flags |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		//config.csi_buffer_flags[port] |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		//config.acquisition_buffer_unique_flags |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;

		अवरोध;
	हाल INPUT_SYSTEM_XMEM_BUFFERING:

		// Check क्रम conflicts on mux.
		mux = INPUT_SYSTEM_ACQUISITION_UNIT;
		status = input_प्रणाली_multiplexer_cfg(&config.multiplexer, mux,
						      &config.multiplexer_flags);
		अगर (status != INPUT_SYSTEM_ERR_NO_ERROR) वापस status;
		config.multicast[port] = INPUT_SYSTEM_INPUT_BUFFER;

		// Shared resource, so it should be blocked.
		//config.mux_flags |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		//config.csi_buffer_flags[port] |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;
		//config.acquisition_buffer_unique_flags |= INPUT_SYSTEM_CFG_FLAG_BLOCKED;

		अवरोध;
	हाल INPUT_SYSTEM_FIFO_CAPTURE_WITH_COUNTING:
		वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
		अवरोध;
	हाल INPUT_SYSTEM_XMEM_CAPTURE:
		वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
		अवरोध;
	हाल INPUT_SYSTEM_XMEM_ACQUIRE:
		वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
		अवरोध;
	शेष:
		वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
		अवरोध;
	पूर्ण
	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// Test flags and set काष्ठाure.
अटल input_प्रणाली_err_t set_source_type(
    input_प्रणाली_source_t *स्थिर lhs,
    स्थिर input_प्रणाली_source_t			rhs,
    input_प्रणाली_config_flags_t *स्थिर flags)
अणु
	// MW: Not enough निश्चितs
	निश्चित(lhs);
	निश्चित(flags);

	अगर ((*flags) & INPUT_SYSTEM_CFG_FLAG_BLOCKED) अणु
		*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
		वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
	पूर्ण

	अगर ((*flags) & INPUT_SYSTEM_CFG_FLAG_SET) अणु
		// Check क्रम consistency with alपढ़ोy set value.
		अगर ((*lhs) == (rhs)) अणु
			वापस INPUT_SYSTEM_ERR_NO_ERROR;
		पूर्ण अन्यथा अणु
			*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
			वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
		पूर्ण
	पूर्ण
	// Check the value (inभागidually).
	अगर (rhs >= N_INPUT_SYSTEM_SOURCE) अणु
		*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
		वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
	पूर्ण
	// Set the value.
	*lhs = rhs;

	*flags |= INPUT_SYSTEM_CFG_FLAG_SET;
	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// Test flags and set काष्ठाure.
अटल input_प्रणाली_err_t set_csi_cfg(
    csi_cfg_t *स्थिर lhs,
    स्थिर csi_cfg_t *स्थिर rhs,
    input_प्रणाली_config_flags_t *स्थिर flags)
अणु
	u32 memory_required;
	u32 acq_memory_required;

	निश्चित(lhs);
	निश्चित(flags);

	अगर ((*flags) & INPUT_SYSTEM_CFG_FLAG_BLOCKED) अणु
		*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
		वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
	पूर्ण

	अगर (*flags & INPUT_SYSTEM_CFG_FLAG_SET) अणु
		// check क्रम consistency with alपढ़ोy set value.
		अगर (/*lhs->backend_ch == rhs.backend_ch
			&&*/ lhs->buffering_mode == rhs->buffering_mode
		    && lhs->csi_buffer.mem_reg_size == rhs->csi_buffer.mem_reg_size
		    && lhs->csi_buffer.nof_mem_regs  == rhs->csi_buffer.nof_mem_regs
		    && lhs->acquisition_buffer.mem_reg_size == rhs->acquisition_buffer.mem_reg_size
		    && lhs->acquisition_buffer.nof_mem_regs  == rhs->acquisition_buffer.nof_mem_regs
		    && lhs->nof_xmem_buffers  == rhs->nof_xmem_buffers
		) अणु
			वापस INPUT_SYSTEM_ERR_NO_ERROR;
		पूर्ण अन्यथा अणु
			*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
			वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
		पूर्ण
	पूर्ण
	// Check the value (inभागidually).
	// no check क्रम backend_ch
	// no check क्रम nof_xmem_buffers
	memory_required = rhs->csi_buffer.mem_reg_size * rhs->csi_buffer.nof_mem_regs;
	acq_memory_required = rhs->acquisition_buffer.mem_reg_size *
			      rhs->acquisition_buffer.nof_mem_regs;
	अगर (rhs->buffering_mode >= N_INPUT_SYSTEM_BUFFERING_MODE
	    ||
	    // Check अगर required memory is available in input buffer (SRAM).
	    (memory_required + acq_memory_required) > config.unallocated_ib_mem_words

	   ) अणु
		*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
		वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
	पूर्ण
	// Set the value.
	//lhs[port]->backend_ch		= rhs.backend_ch;
	lhs->buffering_mode	= rhs->buffering_mode;
	lhs->nof_xmem_buffers = rhs->nof_xmem_buffers;

	lhs->csi_buffer.mem_reg_size = rhs->csi_buffer.mem_reg_size;
	lhs->csi_buffer.nof_mem_regs  = rhs->csi_buffer.nof_mem_regs;
	lhs->acquisition_buffer.mem_reg_size = rhs->acquisition_buffer.mem_reg_size;
	lhs->acquisition_buffer.nof_mem_regs  = rhs->acquisition_buffer.nof_mem_regs;
	// ALX: NB: Here we just set buffer parameters, but still not allocate it
	// (no addresses determined). That will be करोne during commit.

	//  FIXIT:	acq_memory_required is not deducted, since it can be allocated multiple बार.
	config.unallocated_ib_mem_words -= memory_required;
//निश्चित(config.unallocated_ib_mem_words >=0);
	*flags |= INPUT_SYSTEM_CFG_FLAG_SET;
	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण

// Test flags and set काष्ठाure.
अटल input_प्रणाली_err_t input_प्रणाली_multiplexer_cfg(
    input_प्रणाली_multiplex_t *स्थिर lhs,
    स्थिर input_प्रणाली_multiplex_t		rhs,
    input_प्रणाली_config_flags_t *स्थिर flags)
अणु
	निश्चित(lhs);
	निश्चित(flags);

	अगर ((*flags) & INPUT_SYSTEM_CFG_FLAG_BLOCKED) अणु
		*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
		वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
	पूर्ण

	अगर ((*flags) & INPUT_SYSTEM_CFG_FLAG_SET) अणु
		// Check क्रम consistency with alपढ़ोy set value.
		अगर ((*lhs) == (rhs)) अणु
			वापस INPUT_SYSTEM_ERR_NO_ERROR;
		पूर्ण अन्यथा अणु
			*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
			वापस INPUT_SYSTEM_ERR_CONFLICT_ON_RESOURCE;
		पूर्ण
	पूर्ण
	// Check the value (inभागidually).
	अगर (rhs >= N_INPUT_SYSTEM_MULTIPLEX) अणु
		*flags |= INPUT_SYSTEM_CFG_FLAG_CONFLICT;
		वापस INPUT_SYSTEM_ERR_PARAMETER_NOT_SUPPORTED;
	पूर्ण
	// Set the value.
	*lhs = rhs;

	*flags |= INPUT_SYSTEM_CFG_FLAG_SET;
	वापस INPUT_SYSTEM_ERR_NO_ERROR;
पूर्ण
#पूर्ण_अगर
