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

#अगर_अघोषित __INPUT_SYSTEM_PUBLIC_H_INCLUDED__
#घोषणा __INPUT_SYSTEM_PUBLIC_H_INCLUDED__

#समावेश <type_support.h>
#अगर_घोषित ISP2401
#समावेश "isys_public.h"
#अन्यथा

प्रकार काष्ठा input_प्रणाली_state_s		input_प्रणाली_state_t;
प्रकार काष्ठा receiver_state_s			receiver_state_t;

/*! Read the state of INPUT_SYSTEM[ID]

 \param	ID[in]				INPUT_SYSTEM identअगरier
 \param	state[out]			input प्रणाली state काष्ठाure

 \लeturn none, state = INPUT_SYSTEM[ID].state
 */
व्योम input_प्रणाली_get_state(
    स्थिर input_प्रणाली_ID_t		ID,
    input_प्रणाली_state_t		*state);

/*! Read the state of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	state[out]			receiver state काष्ठाure

 \लeturn none, state = RECEIVER[ID].state
 */
व्योम receiver_get_state(
    स्थिर rx_ID_t				ID,
    receiver_state_t			*state);

/*! Flag whether a MIPI क्रमmat is YUV420

 \param	mipi_क्रमmat[in]		MIPI क्रमmat

 \लeturn mipi_क्रमmat == YUV420
 */
bool is_mipi_क्रमmat_yuv420(
    स्थिर mipi_क्रमmat_t			mipi_क्रमmat);

/*! Set compression parameters क्रम cfg[cfg_ID] of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	cfg_ID[in]			Configuration identअगरier
 \param	comp[in]			Compression method
 \param	pred[in]			Predictor method

 \NOTE: the storage of compression configuration is
	implementation specअगरic. The config can be
	carried either on MIPI ports or on MIPI channels

 \लeturn none, RECEIVER[ID].cfg[cfg_ID] = अणुcomp, predपूर्ण
 */
व्योम receiver_set_compression(
    स्थिर rx_ID_t				ID,
    स्थिर अचिन्हित पूर्णांक			cfg_ID,
    स्थिर mipi_compressor_t		comp,
    स्थिर mipi_predictor_t		pred);

/*! Enable PORT[port_ID] of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier
 \param	cnd[in]				irq predicate

 \लeturn None, enable(RECEIVER[ID].PORT[port_ID])
 */
व्योम receiver_port_enable(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id		port_ID,
    स्थिर bool					cnd);

/*! Flag अगर PORT[port_ID] of RECEIVER[ID] is enabled

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier

 \लeturn enable(RECEIVER[ID].PORT[port_ID]) == true
 */
bool is_receiver_port_enabled(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id		port_ID);

/*! Enable the IRQ channels of PORT[port_ID] of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier
 \param	irq_info[in]		irq channels

 \लeturn None, enable(RECEIVER[ID].PORT[port_ID].irq_info)
 */
व्योम receiver_irq_enable(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id		port_ID,
    स्थिर rx_irq_info_t			irq_info);

/*! Return the IRQ status of PORT[port_ID] of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier

 \लeturn RECEIVER[ID].PORT[port_ID].irq_info
 */
rx_irq_info_t receiver_get_irq_info(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id		port_ID);

/*! Clear the IRQ status of PORT[port_ID] of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier
 \param	irq_info[in]		irq status

 \लeturn None, clear(RECEIVER[ID].PORT[port_ID].irq_info)
 */
व्योम receiver_irq_clear(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id			port_ID,
    स्थिर rx_irq_info_t			irq_info);

/*! Write to a control रेजिस्टर of INPUT_SYSTEM[ID]

 \param	ID[in]				INPUT_SYSTEM identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, INPUT_SYSTEM[ID].ctrl[reg] = value
 */
STORAGE_CLASS_INPUT_SYSTEM_H व्योम input_प्रणाली_reg_store(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value);

/*! Read from a control रेजिस्टर of INPUT_SYSTEM[ID]

 \param	ID[in]				INPUT_SYSTEM identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn INPUT_SYSTEM[ID].ctrl[reg]
 */
STORAGE_CLASS_INPUT_SYSTEM_H hrt_data input_प्रणाली_reg_load(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर hrt_address			reg);

/*! Write to a control रेजिस्टर of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, RECEIVER[ID].ctrl[reg] = value
 */
STORAGE_CLASS_INPUT_SYSTEM_H व्योम receiver_reg_store(
    स्थिर rx_ID_t				ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value);

/*! Read from a control रेजिस्टर of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn RECEIVER[ID].ctrl[reg]
 */
STORAGE_CLASS_INPUT_SYSTEM_H hrt_data receiver_reg_load(
    स्थिर rx_ID_t				ID,
    स्थिर hrt_address			reg);

/*! Write to a control रेजिस्टर of PORT[port_ID] of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, RECEIVER[ID].PORT[port_ID].ctrl[reg] = value
 */
STORAGE_CLASS_INPUT_SYSTEM_H व्योम receiver_port_reg_store(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id			port_ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value);

/*! Read from a control रेजिस्टर PORT[port_ID] of of RECEIVER[ID]

 \param	ID[in]				RECEIVER identअगरier
 \param	port_ID[in]			mipi PORT identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn RECEIVER[ID].PORT[port_ID].ctrl[reg]
 */
STORAGE_CLASS_INPUT_SYSTEM_H hrt_data receiver_port_reg_load(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id		port_ID,
    स्थिर hrt_address			reg);

/*! Write to a control रेजिस्टर of SUB_SYSTEM[sub_ID] of INPUT_SYSTEM[ID]

 \param	ID[in]				INPUT_SYSTEM identअगरier
 \param	port_ID[in]			sub प्रणाली identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, INPUT_SYSTEM[ID].SUB_SYSTEM[sub_ID].ctrl[reg] = value
 */
STORAGE_CLASS_INPUT_SYSTEM_H व्योम input_प्रणाली_sub_प्रणाली_reg_store(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value);

/*! Read from a control रेजिस्टर SUB_SYSTEM[sub_ID] of INPUT_SYSTEM[ID]

 \param	ID[in]				INPUT_SYSTEM identअगरier
 \param	port_ID[in]			sub प्रणाली identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn INPUT_SYSTEM[ID].SUB_SYSTEM[sub_ID].ctrl[reg]
 */
STORAGE_CLASS_INPUT_SYSTEM_H hrt_data input_प्रणाली_sub_प्रणाली_reg_load(
    स्थिर input_प्रणाली_ID_t		ID,
    स्थिर sub_प्रणाली_ID_t		sub_ID,
    स्थिर hrt_address			reg);

///////////////////////////////////////////////////////////////////////////
//
//    Functions क्रम configuration phase on input प्रणाली.
//
///////////////////////////////////////////////////////////////////////////

// Function that resets current configuration.
// हटाओ the argument since it should be निजी.
input_प्रणाली_err_t input_प्रणाली_configuration_reset(व्योम);

// Function that commits current configuration.
// हटाओ the argument since it should be निजी.
input_प्रणाली_err_t input_प्रणाली_configuration_commit(व्योम);

///////////////////////////////////////////////////////////////////////////
//
// User functions:
//		(encoded generic function)
//    - no checking
//    - decoding name and agruments पूर्णांकo the generic (channel) configuration
//    function.
//
///////////////////////////////////////////////////////////////////////////

// FIFO channel config function user

input_प्रणाली_err_t	input_प्रणाली_csi_fअगरo_channel_cfg(
    u32				ch_id,
    input_प्रणाली_csi_port_t	port,
    backend_channel_cfg_t	backend_ch,
    target_cfg2400_t			target
);

input_प्रणाली_err_t	input_प्रणाली_csi_fअगरo_channel_with_counting_cfg(
    u32				ch_id,
    u32				nof_frame,
    input_प्रणाली_csi_port_t	port,
    backend_channel_cfg_t	backend_ch,
    u32				mem_region_size,
    u32				nof_mem_regions,
    target_cfg2400_t			target
);

// SRAM channel config function user

input_प्रणाली_err_t	input_प्रणाली_csi_sram_channel_cfg(
    u32				ch_id,
    input_प्रणाली_csi_port_t	port,
    backend_channel_cfg_t	backend_ch,
    u32				csi_mem_region_size,
    u32				csi_nof_mem_regions,
    target_cfg2400_t			target
);

//XMEM channel config function user

input_प्रणाली_err_t	input_प्रणाली_csi_xmem_channel_cfg(
    u32				ch_id,
    input_प्रणाली_csi_port_t port,
    backend_channel_cfg_t	backend_ch,
    u32				mem_region_size,
    u32				nof_mem_regions,
    u32				acq_mem_region_size,
    u32				acq_nof_mem_regions,
    target_cfg2400_t			target,
    uपूर्णांक32_t				nof_xmem_buffers
);

input_प्रणाली_err_t	input_प्रणाली_csi_xmem_capture_only_channel_cfg(
    u32				ch_id,
    u32				nof_frames,
    input_प्रणाली_csi_port_t port,
    u32				csi_mem_region_size,
    u32				csi_nof_mem_regions,
    u32				acq_mem_region_size,
    u32				acq_nof_mem_regions,
    target_cfg2400_t			target
);

input_प्रणाली_err_t	input_प्रणाली_csi_xmem_acquire_only_channel_cfg(
    u32				ch_id,
    u32				nof_frames,
    input_प्रणाली_csi_port_t port,
    backend_channel_cfg_t	backend_ch,
    u32				acq_mem_region_size,
    u32				acq_nof_mem_regions,
    target_cfg2400_t			target
);

// Non - CSI channel config function user

input_प्रणाली_err_t	input_प्रणाली_prbs_channel_cfg(
    u32		ch_id,
    u32		nof_frames,
    u32		seed,
    u32		sync_gen_width,
    u32		sync_gen_height,
    u32		sync_gen_hblank_cycles,
    u32		sync_gen_vblank_cycles,
    target_cfg2400_t	target
);

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
);

input_प्रणाली_err_t	input_प्रणाली_gpfअगरo_channel_cfg(
    u32		ch_id,
    u32		nof_frames,
    target_cfg2400_t	target
);
#पूर्ण_अगर /* #अगर_घोषित ISP2401 */

#पूर्ण_अगर /* __INPUT_SYSTEM_PUBLIC_H_INCLUDED__ */
