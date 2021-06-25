<शैली गुरु>
/* Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DC_MPCC_H__
#घोषणा __DC_MPCC_H__

#समावेश "dc_hw_types.h"
#समावेश "hw_shared.h"
#समावेश "transform.h"

#घोषणा MAX_MPCC 6
#घोषणा MAX_OPP 6

#घोषणा MAX_DWB		2

क्रमागत mpc_output_csc_mode अणु
	MPC_OUTPUT_CSC_DISABLE = 0,
	MPC_OUTPUT_CSC_COEF_A,
	MPC_OUTPUT_CSC_COEF_B
पूर्ण;


क्रमागत mpcc_blend_mode अणु
	MPCC_BLEND_MODE_BYPASS,
	MPCC_BLEND_MODE_TOP_LAYER_PASSTHROUGH,
	MPCC_BLEND_MODE_TOP_LAYER_ONLY,
	MPCC_BLEND_MODE_TOP_BOT_BLENDING
पूर्ण;

क्रमागत mpcc_alpha_blend_mode अणु
	MPCC_ALPHA_BLEND_MODE_PER_PIXEL_ALPHA,
	MPCC_ALPHA_BLEND_MODE_PER_PIXEL_ALPHA_COMBINED_GLOBAL_GAIN,
	MPCC_ALPHA_BLEND_MODE_GLOBAL_ALPHA
पूर्ण;

/*
 * MPCC blending configuration
 */
काष्ठा mpcc_blnd_cfg अणु
	काष्ठा tg_color black_color;	/* background color */
	क्रमागत mpcc_alpha_blend_mode alpha_mode;	/* alpha blend mode */
	bool pre_multiplied_alpha;	/* alpha pre-multiplied mode flag */
	पूर्णांक global_gain;
	पूर्णांक global_alpha;
	bool overlap_only;

	/* MPCC top/bottom gain settings */
	पूर्णांक bottom_gain_mode;
	पूर्णांक background_color_bpc;
	पूर्णांक top_gain;
	पूर्णांक bottom_inside_gain;
	पूर्णांक bottom_outside_gain;
पूर्ण;

काष्ठा mpc_grph_gamut_adjusपंचांगent अणु
	काष्ठा fixed31_32 temperature_matrix[CSC_TEMPERATURE_MATRIX_SIZE];
	क्रमागत graphics_gamut_adjust_type gamut_adjust_type;
पूर्ण;

काष्ठा mpcc_sm_cfg अणु
	bool enable;
	/* 0-single plane,2-row subsampling,4-column subsampling,6-checkboard subsampling */
	पूर्णांक sm_mode;
	/* 0- disable frame alternate, 1- enable frame alternate */
	bool frame_alt;
	/* 0- disable field alternate, 1- enable field alternate */
	bool field_alt;
	/* 0-no क्रमce,2-क्रमce frame polarity from top,3-क्रमce frame polarity from bottom */
	पूर्णांक क्रमce_next_frame_porlarity;
	/* 0-no क्रमce,2-क्रमce field polarity from top,3-क्रमce field polarity from bottom */
	पूर्णांक क्रमce_next_field_polarity;
पूर्ण;

काष्ठा mpc_denorm_clamp अणु
	पूर्णांक clamp_max_r_cr;
	पूर्णांक clamp_min_r_cr;
	पूर्णांक clamp_max_g_y;
	पूर्णांक clamp_min_g_y;
	पूर्णांक clamp_max_b_cb;
	पूर्णांक clamp_min_b_cb;
पूर्ण;

काष्ठा mpc_dwb_flow_control अणु
	पूर्णांक flow_ctrl_mode;
	पूर्णांक flow_ctrl_cnt0;
	पूर्णांक flow_ctrl_cnt1;
पूर्ण;

/*
 * MPCC connection and blending configuration क्रम a single MPCC instance.
 * This काष्ठा is used as a node in an MPC tree.
 */
काष्ठा mpcc अणु
	पूर्णांक mpcc_id;			/* MPCC physical instance */
	पूर्णांक dpp_id;			/* DPP input to this MPCC */
	काष्ठा mpcc *mpcc_bot;		/* poपूर्णांकer to bottom layer MPCC.  शून्य when not connected */
	काष्ठा mpcc_blnd_cfg blnd_cfg;	/* The blending configuration क्रम this MPCC */
	काष्ठा mpcc_sm_cfg sm_cfg;	/* stereo mix setting क्रम this MPCC */
	bool shared_bottom;		/* TRUE अगर MPCC output to both OPP and DWB endpoपूर्णांकs, अन्यथा FALSE */
पूर्ण;

/*
 * MPC tree represents all MPCC connections क्रम a pipe.
 */
काष्ठा mpc_tree अणु
	पूर्णांक opp_id;			/* The OPP instance that owns this MPC tree */
	काष्ठा mpcc *opp_list;		/* The top MPCC layer of the MPC tree that outमाला_दो to OPP endpoपूर्णांक */
पूर्ण;

काष्ठा mpc अणु
	स्थिर काष्ठा mpc_funcs *funcs;
	काष्ठा dc_context *ctx;

	काष्ठा mpcc mpcc_array[MAX_MPCC];
	काष्ठा pwl_params blender_params;
	bool cm_bypass_mode;
पूर्ण;

काष्ठा mpcc_state अणु
	uपूर्णांक32_t opp_id;
	uपूर्णांक32_t dpp_id;
	uपूर्णांक32_t bot_mpcc_id;
	uपूर्णांक32_t mode;
	uपूर्णांक32_t alpha_mode;
	uपूर्णांक32_t pre_multiplied_alpha;
	uपूर्णांक32_t overlap_only;
	uपूर्णांक32_t idle;
	uपूर्णांक32_t busy;
पूर्ण;

काष्ठा mpc_funcs अणु
	व्योम (*पढ़ो_mpcc_state)(
			काष्ठा mpc *mpc,
			पूर्णांक mpcc_inst,
			काष्ठा mpcc_state *s);

	/*
	 * Insert DPP पूर्णांकo MPC tree based on specअगरied blending position.
	 * Only used क्रम planes that are part of blending chain क्रम OPP output
	 *
	 * Parameters:
	 * [in/out] mpc		- MPC context.
	 * [in/out] tree	- MPC tree काष्ठाure that plane will be added to.
	 * [in]	blnd_cfg	- MPCC blending configuration क्रम the new blending layer.
	 * [in]	sm_cfg		- MPCC stereo mix configuration क्रम the new blending layer.
	 *			  stereo mix must disable क्रम the very bottom layer of the tree config.
	 * [in]	insert_above_mpcc - Insert new plane above this MPCC.  If शून्य, insert as bottom plane.
	 * [in]	dpp_id		 - DPP instance क्रम the plane to be added.
	 * [in]	mpcc_id		 - The MPCC physical instance to use क्रम blending.
	 *
	 * Return:  काष्ठा mpcc* - MPCC that was added.
	 */
	काष्ठा mpcc* (*insert_plane)(
			काष्ठा mpc *mpc,
			काष्ठा mpc_tree *tree,
			काष्ठा mpcc_blnd_cfg *blnd_cfg,
			काष्ठा mpcc_sm_cfg *sm_cfg,
			काष्ठा mpcc *insert_above_mpcc,
			पूर्णांक dpp_id,
			पूर्णांक mpcc_id);

	/*
	 * Remove a specअगरied MPCC from the MPC tree.
	 *
	 * Parameters:
	 * [in/out] mpc		- MPC context.
	 * [in/out] tree	- MPC tree काष्ठाure that plane will be हटाओd from.
	 * [in/out] mpcc	- MPCC to be हटाओd from tree.
	 *
	 * Return:  व्योम
	 */
	व्योम (*हटाओ_mpcc)(
			काष्ठा mpc *mpc,
			काष्ठा mpc_tree *tree,
			काष्ठा mpcc *mpcc);

	/*
	 * Reset the MPCC HW status by disconnecting all muxes.
	 *
	 * Parameters:
	 * [in/out] mpc		- MPC context.
	 *
	 * Return:  व्योम
	 */
	व्योम (*mpc_init)(काष्ठा mpc *mpc);
	व्योम (*mpc_init_single_inst)(
			काष्ठा mpc *mpc,
			अचिन्हित पूर्णांक mpcc_id);

	/*
	 * Update the blending configuration क्रम a specअगरied MPCC.
	 *
	 * Parameters:
	 * [in/out] mpc		- MPC context.
	 * [in]     blnd_cfg	- MPCC blending configuration.
	 * [in]     mpcc_id	- The MPCC physical instance.
	 *
	 * Return:  व्योम
	 */
	व्योम (*update_blending)(
		काष्ठा mpc *mpc,
		काष्ठा mpcc_blnd_cfg *blnd_cfg,
		पूर्णांक mpcc_id);

	/*
	 * Lock cursor updates क्रम the specअगरied OPP.
	 * OPP defines the set of MPCC that are locked together क्रम cursor.
	 *
	 * Parameters:
	 * [in] 	mpc		- MPC context.
	 * [in]     opp_id	- The OPP to lock cursor updates on
	 * [in]		lock	- lock/unlock the OPP
	 *
	 * Return:  व्योम
	 */
	व्योम (*cursor_lock)(
			काष्ठा mpc *mpc,
			पूर्णांक opp_id,
			bool lock);

	/*
	 * Add DPP पूर्णांकo 'secondary' MPC tree based on specअगरied blending position.
	 * Only used क्रम planes that are part of blending chain क्रम DWB output
	 *
	 * Parameters:
	 * [in/out] mpc		- MPC context.
	 * [in/out] tree		- MPC tree काष्ठाure that plane will be added to.
	 * [in]	blnd_cfg	- MPCC blending configuration क्रम the new blending layer.
	 * [in]	sm_cfg		- MPCC stereo mix configuration क्रम the new blending layer.
	 *			  stereo mix must disable क्रम the very bottom layer of the tree config.
	 * [in]	insert_above_mpcc - Insert new plane above this MPCC.  If शून्य, insert as bottom plane.
	 * [in]	dpp_id		- DPP instance क्रम the plane to be added.
	 * [in]	mpcc_id		- The MPCC physical instance to use क्रम blending.
	 *
	 * Return:  काष्ठा mpcc* - MPCC that was added.
	 */
	काष्ठा mpcc* (*insert_plane_to_secondary)(
			काष्ठा mpc *mpc,
			काष्ठा mpc_tree *tree,
			काष्ठा mpcc_blnd_cfg *blnd_cfg,
			काष्ठा mpcc_sm_cfg *sm_cfg,
			काष्ठा mpcc *insert_above_mpcc,
			पूर्णांक dpp_id,
			पूर्णांक mpcc_id);

	/*
	 * Remove a specअगरied DPP from the 'secondary' MPC tree.
	 *
	 * Parameters:
	 * [in/out] mpc		- MPC context.
	 * [in/out] tree	- MPC tree काष्ठाure that plane will be हटाओd from.
	 * [in]     mpcc	- MPCC to be हटाओd from tree.
	 * Return:  व्योम
	 */
	व्योम (*हटाओ_mpcc_from_secondary)(
			काष्ठा mpc *mpc,
			काष्ठा mpc_tree *tree,
			काष्ठा mpcc *mpcc);

	काष्ठा mpcc* (*get_mpcc_क्रम_dpp_from_secondary)(
			काष्ठा mpc_tree *tree,
			पूर्णांक dpp_id);
	काष्ठा mpcc* (*get_mpcc_क्रम_dpp)(
			काष्ठा mpc_tree *tree,
			पूर्णांक dpp_id);

	व्योम (*रुको_क्रम_idle)(काष्ठा mpc *mpc, पूर्णांक id);

	व्योम (*निश्चित_mpcc_idle_beक्रमe_connect)(काष्ठा mpc *mpc, पूर्णांक mpcc_id);

	व्योम (*init_mpcc_list_from_hw)(
		काष्ठा mpc *mpc,
		काष्ठा mpc_tree *tree);

	व्योम (*set_denorm)(काष्ठा mpc *mpc,
			पूर्णांक opp_id,
			क्रमागत dc_color_depth output_depth);

	व्योम (*set_denorm_clamp)(
			काष्ठा mpc *mpc,
			पूर्णांक opp_id,
			काष्ठा mpc_denorm_clamp denorm_clamp);

	व्योम (*set_output_csc)(काष्ठा mpc *mpc,
			पूर्णांक opp_id,
			स्थिर uपूर्णांक16_t *regval,
			क्रमागत mpc_output_csc_mode ocsc_mode);

	व्योम (*set_ocsc_शेष)(काष्ठा mpc *mpc,
			पूर्णांक opp_id,
			क्रमागत dc_color_space color_space,
			क्रमागत mpc_output_csc_mode ocsc_mode);

	व्योम (*set_output_gamma)(
			काष्ठा mpc *mpc,
			पूर्णांक mpcc_id,
			स्थिर काष्ठा pwl_params *params);
	व्योम (*घातer_on_mpc_mem_pwr)(
			काष्ठा mpc *mpc,
			पूर्णांक mpcc_id,
			bool घातer_on);
	व्योम (*set_dwb_mux)(
			काष्ठा mpc *mpc,
			पूर्णांक dwb_id,
			पूर्णांक mpcc_id);

	व्योम (*disable_dwb_mux)(
		काष्ठा mpc *mpc,
		पूर्णांक dwb_id);

	bool (*is_dwb_idle)(
		काष्ठा mpc *mpc,
		पूर्णांक dwb_id);

	व्योम (*set_out_rate_control)(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		bool enable,
		bool rate_2x_mode,
		काष्ठा mpc_dwb_flow_control *flow_control);

	व्योम (*set_gamut_remap)(
			काष्ठा mpc *mpc,
			पूर्णांक mpcc_id,
			स्थिर काष्ठा mpc_grph_gamut_adjusपंचांगent *adjust);

	bool (*program_shaper)(
			काष्ठा mpc *mpc,
			स्थिर काष्ठा pwl_params *params,
			uपूर्णांक32_t rmu_idx);

	uपूर्णांक32_t (*acquire_rmu)(काष्ठा mpc *mpc, पूर्णांक mpcc_id, पूर्णांक rmu_idx);

	bool (*program_3dlut)(
			काष्ठा mpc *mpc,
			स्थिर काष्ठा tetrahedral_params *params,
			पूर्णांक rmu_idx);

	पूर्णांक (*release_rmu)(काष्ठा mpc *mpc, पूर्णांक mpcc_id);

	अचिन्हित पूर्णांक (*get_mpc_out_mux)(
			काष्ठा mpc *mpc,
			पूर्णांक opp_id);

पूर्ण;

#पूर्ण_अगर
