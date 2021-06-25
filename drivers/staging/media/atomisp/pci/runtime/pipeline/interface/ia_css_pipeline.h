<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
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

#अगर_अघोषित __IA_CSS_PIPELINE_H__
#घोषणा __IA_CSS_PIPELINE_H__

#समावेश "sh_css_internal.h"
#समावेश "ia_css_pipe_public.h"
#समावेश "ia_css_pipeline_common.h"

#घोषणा IA_CSS_PIPELINE_NUM_MAX		(20)

/* Pipeline stage to be executed on SP/ISP */
काष्ठा ia_css_pipeline_stage अणु
	अचिन्हित पूर्णांक stage_num;
	काष्ठा ia_css_binary *binary;	/* built-in binary */
	काष्ठा ia_css_binary_info *binary_info;
	स्थिर काष्ठा ia_css_fw_info *firmware;	/* acceleration binary */
	/* SP function क्रम SP stage */
	क्रमागत ia_css_pipeline_stage_sp_func sp_func;
	अचिन्हित पूर्णांक max_input_width;	/* For SP raw copy */
	काष्ठा sh_css_binary_args args;
	पूर्णांक mode;
	bool out_frame_allocated[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	bool vf_frame_allocated;
	काष्ठा ia_css_pipeline_stage *next;
	bool enable_zoom;
पूर्ण;

/* Pipeline of n stages to be executed on SP/ISP per stage */
काष्ठा ia_css_pipeline अणु
	क्रमागत ia_css_pipe_id pipe_id;
	u8 pipe_num;
	bool stop_requested;
	काष्ठा ia_css_pipeline_stage *stages;
	काष्ठा ia_css_pipeline_stage *current_stage;
	अचिन्हित पूर्णांक num_stages;
	काष्ठा ia_css_frame in_frame;
	काष्ठा ia_css_frame out_frame[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_frame vf_frame[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	अचिन्हित पूर्णांक dvs_frame_delay;
	अचिन्हित पूर्णांक inout_port_config;
	पूर्णांक num_execs;
	bool acquire_isp_each_stage;
	u32 pipe_qos_config;
पूर्ण;

#घोषणा DEFAULT_PIPELINE अणु \
	.pipe_id		= IA_CSS_PIPE_ID_PREVIEW, \
	.in_frame		= DEFAULT_FRAME, \
	.out_frame		= अणुDEFAULT_FRAMEपूर्ण, \
	.vf_frame		= अणुDEFAULT_FRAMEपूर्ण, \
	.dvs_frame_delay	= IA_CSS_FRAME_DELAY_1, \
	.num_execs		= -1, \
	.acquire_isp_each_stage	= true, \
	.pipe_qos_config	= QOS_INVALID \
पूर्ण

/* Stage descriptor used to create a new stage in the pipeline */
काष्ठा ia_css_pipeline_stage_desc अणु
	काष्ठा ia_css_binary *binary;
	स्थिर काष्ठा ia_css_fw_info *firmware;
	क्रमागत ia_css_pipeline_stage_sp_func sp_func;
	अचिन्हित पूर्णांक max_input_width;
	अचिन्हित पूर्णांक mode;
	काष्ठा ia_css_frame *in_frame;
	काष्ठा ia_css_frame *out_frame[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_frame *vf_frame;
पूर्ण;

/* @brief initialize the pipeline module
 *
 * @वापस    None
 *
 * Initializes the pipeline module. This API has to be called
 * beक्रमe any operation on the pipeline module is करोne
 */
व्योम ia_css_pipeline_init(व्योम);

/* @brief initialize the pipeline काष्ठाure with शेष values
 *
 * @param[out] pipeline  काष्ठाure to be initialized with शेषs
 * @param[in] pipe_id
 * @param[in] pipe_num Number that uniquely identअगरies a pipeline.
 * @वापस                     0 or error code upon error.
 *
 * Initializes the pipeline काष्ठाure with a set of शेष values.
 * This API is expected to be used when a pipeline काष्ठाure is allocated
 * बाह्यally and needs sane शेषs
 */
पूर्णांक ia_css_pipeline_create(
    काष्ठा ia_css_pipeline *pipeline,
    क्रमागत ia_css_pipe_id pipe_id,
    अचिन्हित पूर्णांक pipe_num,
    अचिन्हित पूर्णांक dvs_frame_delay);

/* @brief destroy a pipeline
 *
 * @param[in] pipeline
 * @वापस    None
 *
 */
व्योम ia_css_pipeline_destroy(काष्ठा ia_css_pipeline *pipeline);

/* @brief Starts a pipeline
 *
 * @param[in] pipe_id
 * @param[in] pipeline
 * @वापस    None
 *
 */
व्योम ia_css_pipeline_start(क्रमागत ia_css_pipe_id pipe_id,
			   काष्ठा ia_css_pipeline *pipeline);

/* @brief Request to stop a pipeline
 *
 * @param[in] pipeline
 * @वापस                     0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipeline_request_stop(काष्ठा ia_css_pipeline *pipeline);

/* @brief Check whether pipeline has stopped
 *
 * @param[in] pipeline
 * @वापस    true अगर the pipeline has stopped
 *
 */
bool ia_css_pipeline_has_stopped(काष्ठा ia_css_pipeline *pipe);

/* @brief clean all the stages pipeline and make it as new
 *
 * @param[in] pipeline
 * @वापस    None
 *
 */
व्योम ia_css_pipeline_clean(काष्ठा ia_css_pipeline *pipeline);

/* @brief Add a stage to pipeline.
 *
 * @param     pipeline               Poपूर्णांकer to the pipeline to be added to.
 * @param[in] stage_desc       The description of the stage
 * @param[out] stage            The successor of the stage.
 * @वापस                     0 or error code upon error.
 *
 * Add a new stage to a non-शून्य pipeline.
 * The stage consists of an ISP binary or firmware and input and output
 * arguments.
*/
पूर्णांक ia_css_pipeline_create_and_add_stage(
    काष्ठा ia_css_pipeline *pipeline,
    काष्ठा ia_css_pipeline_stage_desc *stage_desc,
    काष्ठा ia_css_pipeline_stage **stage);

/* @brief Finalize the stages in a pipeline
 *
 * @param     pipeline               Poपूर्णांकer to the pipeline to be added to.
 * @वापस                     None
 *
 * This API is expected to be called after adding all stages
*/
व्योम ia_css_pipeline_finalize_stages(काष्ठा ia_css_pipeline *pipeline,
				     bool continuous);

/* @brief माला_लो a stage from the pipeline
 *
 * @param[in] pipeline
 * @वापस                     0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipeline_get_stage(काष्ठा ia_css_pipeline *pipeline,
	पूर्णांक mode,
	काष्ठा ia_css_pipeline_stage **stage);

/* @brief Gets a pipeline stage corresponding Firmware handle from the pipeline
 *
 * @param[in] pipeline
 * @param[in] fw_handle
 * @param[out] stage Poपूर्णांकer to Stage
 *
 * @वापस   0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipeline_get_stage_from_fw(काष्ठा ia_css_pipeline
	*pipeline,
	u32 fw_handle,
	काष्ठा ia_css_pipeline_stage **stage);

/* @brief Gets the Firmware handle corresponding the stage num from the pipeline
 *
 * @param[in] pipeline
 * @param[in] stage_num
 * @param[out] fw_handle
 *
 * @वापस   0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipeline_get_fw_from_stage(काष्ठा ia_css_pipeline
	*pipeline,
	u32 stage_num,
	uपूर्णांक32_t *fw_handle);

/* @brief माला_लो the output stage from the pipeline
 *
 * @param[in] pipeline
 * @वापस                     0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipeline_get_output_stage(
    काष्ठा ia_css_pipeline *pipeline,
    पूर्णांक mode,
    काष्ठा ia_css_pipeline_stage **stage);

/* @brief Checks whether the pipeline uses params
 *
 * @param[in] pipeline
 * @वापस    true अगर the pipeline uses params
 *
 */
bool ia_css_pipeline_uses_params(काष्ठा ia_css_pipeline *pipeline);

/**
 * @brief get the SP thपढ़ो ID.
 *
 * @param[in]	key	The query key, typical use is pipe_num.
 * @param[out]	val	The query value.
 *
 * @वापस
 *	true, अगर the query succeeds;
 *	false, अगर the query fails.
 */
bool ia_css_pipeline_get_sp_thपढ़ो_id(अचिन्हित पूर्णांक key, अचिन्हित पूर्णांक *val);

#अगर defined(ISP2401)
/**
 * @brief Get the pipeline io status
 *
 * @param[in] None
 * @वापस
 *	Poपूर्णांकer to pipe_io_status
 */
काष्ठा sh_css_sp_pipeline_io_status *ia_css_pipeline_get_pipe_io_status(व्योम);
#पूर्ण_अगर

/**
 * @brief Map an SP thपढ़ो to this pipeline
 *
 * @param[in]	pipe_num
 * @param[in]	map true क्रम mapping and false क्रम unmapping sp thपढ़ोs.
 *
 */
व्योम ia_css_pipeline_map(अचिन्हित पूर्णांक pipe_num, bool map);

/**
 * @brief Checks whether the pipeline is mapped to SP thपढ़ोs
 *
 * @param[in]	Query key, typical use is pipe_num
 *
 * वापस
 *	true, pipeline is mapped to SP thपढ़ोs
 *	false, pipeline is not mapped to SP thपढ़ोs
 */
bool ia_css_pipeline_is_mapped(अचिन्हित पूर्णांक key);

/**
 * @brief Prपूर्णांक pipeline thपढ़ो mapping
 *
 * @param[in]	none
 *
 * वापस none
 */
व्योम ia_css_pipeline_dump_thपढ़ो_map_info(व्योम);

#पूर्ण_अगर /*__IA_CSS_PIPELINE_H__*/
