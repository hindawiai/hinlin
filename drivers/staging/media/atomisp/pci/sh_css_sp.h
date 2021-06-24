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

#अगर_अघोषित _SH_CSS_SP_H_
#घोषणा _SH_CSS_SP_H_

#समावेश <प्रणाली_global.h>
#समावेश <type_support.h>
#अगर !defined(ISP2401)
#समावेश "input_formatter.h"
#पूर्ण_अगर

#समावेश "ia_css_binary.h"
#समावेश "ia_css_types.h"
#समावेश "ia_css_pipeline.h"

/* Function to initialize the data and bss section descr of the binary */
व्योम
sh_css_sp_store_init_dmem(स्थिर काष्ठा ia_css_fw_info *fw);

व्योम
store_sp_stage_data(क्रमागत ia_css_pipe_id id, अचिन्हित पूर्णांक pipe_num,
		    अचिन्हित पूर्णांक stage);

व्योम
sh_css_stage_ग_लिखो_binary_info(काष्ठा ia_css_binary_info *info);

व्योम
store_sp_group_data(व्योम);

/* Start binary (jpeg) copy on the SP */
व्योम
sh_css_sp_start_binary_copy(अचिन्हित पूर्णांक pipe_num,
			    काष्ठा ia_css_frame *out_frame,
			    अचिन्हित पूर्णांक two_ppc);

अचिन्हित पूर्णांक
sh_css_sp_get_binary_copy_size(व्योम);

/* Return the value of a SW पूर्णांकerrupt */
अचिन्हित पूर्णांक
sh_css_sp_get_sw_पूर्णांकerrupt_value(अचिन्हित पूर्णांक irq);

व्योम
sh_css_sp_init_pipeline(काष्ठा ia_css_pipeline *me,
			क्रमागत ia_css_pipe_id id,
			u8 pipe_num,
			bool xnr,
			bool two_ppc,
			bool continuous,
			bool offline,
			अचिन्हित पूर्णांक required_bds_factor,
			क्रमागत sh_css_pipe_config_override copy_ovrd,
			क्रमागत ia_css_input_mode input_mode,
			स्थिर काष्ठा ia_css_metadata_config *md_config,
			स्थिर काष्ठा ia_css_metadata_info *md_info,
			स्थिर क्रमागत mipi_port_id port_id,
			स्थिर काष्ठा ia_css_coordinate
			*पूर्णांकernal_frame_origin_bqs_on_sctbl, /* Origin of पूर्णांकernal frame
							positioned on shading table at shading correction in ISP. */
			स्थिर काष्ठा ia_css_isp_parameters *params
		       );

व्योम
sh_css_sp_uninit_pipeline(अचिन्हित पूर्णांक pipe_num);

bool sh_css_ग_लिखो_host2sp_command(क्रमागत host2sp_commands host2sp_command);

क्रमागत host2sp_commands
sh_css_पढ़ो_host2sp_command(व्योम);

व्योम
sh_css_init_host2sp_frame_data(व्योम);

/**
 * @brief Update the offline frame inक्रमmation in host_sp_communication.
 *
 * @param[in] frame_num The offline frame number.
 * @param[in] frame The poपूर्णांकer to the offline frame.
 */
व्योम
sh_css_update_host2sp_offline_frame(
    अचिन्हित पूर्णांक frame_num,
    काष्ठा ia_css_frame *frame,
    काष्ठा ia_css_metadata *metadata);

/**
 * @brief Update the mipi frame inक्रमmation in host_sp_communication.
 *
 * @param[in] frame_num The mipi frame number.
 * @param[in] frame The poपूर्णांकer to the mipi frame.
 */
व्योम
sh_css_update_host2sp_mipi_frame(
    अचिन्हित पूर्णांक frame_num,
    काष्ठा ia_css_frame *frame);

/**
 * @brief Update the mipi metadata inक्रमmation in host_sp_communication.
 *
 * @param[in] frame_num The mipi frame number.
 * @param[in] metadata The poपूर्णांकer to the mipi metadata.
 */
व्योम
sh_css_update_host2sp_mipi_metadata(
    अचिन्हित पूर्णांक frame_num,
    काष्ठा ia_css_metadata *metadata);

/**
 * @brief Update the nr of mipi frames to use in host_sp_communication.
 *
 * @param[in] num_frames The number of mipi frames to use.
 */
व्योम
sh_css_update_host2sp_num_mipi_frames(अचिन्हित पूर्णांक num_frames);

/**
 * @brief Update the nr of offline frames to use in host_sp_communication.
 *
 * @param[in] num_frames The number of raw frames to use.
 */
व्योम
sh_css_update_host2sp_cont_num_raw_frames(अचिन्हित पूर्णांक num_frames,
	bool set_avail);

व्योम
sh_css_event_init_irq_mask(व्योम);

व्योम
sh_css_sp_start_isp(व्योम);

व्योम
sh_css_sp_set_sp_running(bool flag);

bool
sh_css_sp_is_running(व्योम);

#अगर SP_DEBUG != SP_DEBUG_NONE

व्योम
sh_css_sp_get_debug_state(काष्ठा sh_css_sp_debug_state *state);

#पूर्ण_अगर

#अगर !defined(ISP2401)
व्योम
sh_css_sp_set_अगर_configs(
    स्थिर input_क्रमmatter_cfg_t	*config_a,
    स्थिर input_क्रमmatter_cfg_t	*config_b,
    स्थिर uपूर्णांक8_t		अगर_config_index);
#पूर्ण_अगर

व्योम
sh_css_sp_program_input_circuit(पूर्णांक fmt_type,
				पूर्णांक ch_id,
				क्रमागत ia_css_input_mode input_mode);

व्योम
sh_css_sp_configure_sync_gen(पूर्णांक width,
			     पूर्णांक height,
			     पूर्णांक hblank_cycles,
			     पूर्णांक vblank_cycles);

व्योम
sh_css_sp_configure_tpg(पूर्णांक x_mask,
			पूर्णांक y_mask,
			पूर्णांक x_delta,
			पूर्णांक y_delta,
			पूर्णांक xy_mask);

व्योम
sh_css_sp_configure_prbs(पूर्णांक seed);

व्योम
sh_css_sp_configure_enable_raw_pool_locking(bool lock_all);

व्योम
sh_css_sp_enable_isys_event_queue(bool enable);

व्योम
sh_css_sp_set_disable_continuous_viewfinder(bool flag);

व्योम
sh_css_sp_reset_global_vars(व्योम);

/**
 * @brief Initialize the DMA software-mask in the debug mode.
 * This API should be ONLY called in the debugging mode.
 * And it should be always called beक्रमe the first call of
 * "sh_css_set_dma_sw_reg(...)".
 *
 * @param[in]	dma_id		The ID of the target DMA.
 *
 * @वापस
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool
sh_css_sp_init_dma_sw_reg(पूर्णांक dma_id);

/**
 * @brief Set the DMA software-mask in the debug mode.
 * This API should be ONLYL called in the debugging mode. Must
 * call "sh_css_set_dma_sw_reg(...)" beक्रमe this
 * API is called क्रम the first समय.
 *
 * @param[in]	dma_id		The ID of the target DMA.
 * @param[in]	channel_id	The ID of the target DMA channel.
 * @param[in]	request_type	The type of the DMA request.
 *				For example:
 *				- "0" indicates the writing request.
 *				- "1" indicates the पढ़ोing request.
 *
 * @param[in]	enable		If it is "true", the target DMA
 *				channel is enabled in the software.
 *				Otherwise, the target DMA channel
 *				is disabled in the software.
 *
 * @वापस
 *	- true, अगर it is successful.
 *	- false, otherwise.
 */
bool
sh_css_sp_set_dma_sw_reg(पूर्णांक dma_id,
			 पूर्णांक channel_id,
			 पूर्णांक request_type,
			 bool enable);

बाह्य काष्ठा sh_css_sp_group sh_css_sp_group;
बाह्य काष्ठा sh_css_sp_stage sh_css_sp_stage;
बाह्य काष्ठा sh_css_isp_stage sh_css_isp_stage;

#पूर्ण_अगर /* _SH_CSS_SP_H_ */
