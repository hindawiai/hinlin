<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#समावेश "reg_helper.h"
#समावेश "dcn10_mpc.h"

#घोषणा REG(reg)\
	mpc10->mpc_regs->reg

#घोषणा CTX \
	mpc10->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	mpc10->mpc_shअगरt->field_name, mpc10->mpc_mask->field_name


व्योम mpc1_set_bg_color(काष्ठा mpc *mpc,
		काष्ठा tg_color *bg_color,
		पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	काष्ठा mpcc *bottommost_mpcc = mpc1_get_mpcc(mpc, mpcc_id);
	uपूर्णांक32_t bg_r_cr, bg_g_y, bg_b_cb;

	/* find bottommost mpcc. */
	जबतक (bottommost_mpcc->mpcc_bot) अणु
		bottommost_mpcc = bottommost_mpcc->mpcc_bot;
	पूर्ण

	/* mpc color is 12 bit.  tg_color is 10 bit */
	/* toकरो: might want to use 16 bit to represent color and have each
	 * hw block translate to correct color depth.
	 */
	bg_r_cr = bg_color->color_r_cr << 2;
	bg_g_y = bg_color->color_g_y << 2;
	bg_b_cb = bg_color->color_b_cb << 2;

	REG_SET(MPCC_BG_R_CR[bottommost_mpcc->mpcc_id], 0,
			MPCC_BG_R_CR, bg_r_cr);
	REG_SET(MPCC_BG_G_Y[bottommost_mpcc->mpcc_id], 0,
			MPCC_BG_G_Y, bg_g_y);
	REG_SET(MPCC_BG_B_CB[bottommost_mpcc->mpcc_id], 0,
			MPCC_BG_B_CB, bg_b_cb);
पूर्ण

अटल व्योम mpc1_update_blending(
	काष्ठा mpc *mpc,
	काष्ठा mpcc_blnd_cfg *blnd_cfg,
	पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	काष्ठा mpcc *mpcc = mpc1_get_mpcc(mpc, mpcc_id);

	REG_UPDATE_5(MPCC_CONTROL[mpcc_id],
			MPCC_ALPHA_BLND_MODE,		blnd_cfg->alpha_mode,
			MPCC_ALPHA_MULTIPLIED_MODE,	blnd_cfg->pre_multiplied_alpha,
			MPCC_BLND_ACTIVE_OVERLAP_ONLY,	blnd_cfg->overlap_only,
			MPCC_GLOBAL_ALPHA,		blnd_cfg->global_alpha,
			MPCC_GLOBAL_GAIN,		blnd_cfg->global_gain);

	mpc1_set_bg_color(mpc, &blnd_cfg->black_color, mpcc_id);
	mpcc->blnd_cfg = *blnd_cfg;
पूर्ण

व्योम mpc1_update_stereo_mix(
	काष्ठा mpc *mpc,
	काष्ठा mpcc_sm_cfg *sm_cfg,
	पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	REG_UPDATE_6(MPCC_SM_CONTROL[mpcc_id],
			MPCC_SM_EN,			sm_cfg->enable,
			MPCC_SM_MODE,			sm_cfg->sm_mode,
			MPCC_SM_FRAME_ALT,		sm_cfg->frame_alt,
			MPCC_SM_FIELD_ALT,		sm_cfg->field_alt,
			MPCC_SM_FORCE_NEXT_FRAME_POL,	sm_cfg->क्रमce_next_frame_porlarity,
			MPCC_SM_FORCE_NEXT_TOP_POL,	sm_cfg->क्रमce_next_field_polarity);
पूर्ण
व्योम mpc1_निश्चित_idle_mpcc(काष्ठा mpc *mpc, पूर्णांक id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	ASSERT(!(mpc10->mpcc_in_use_mask & 1 << id));
	REG_WAIT(MPCC_STATUS[id],
			MPCC_IDLE, 1,
			1, 100000);
पूर्ण

काष्ठा mpcc *mpc1_get_mpcc(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	ASSERT(mpcc_id < mpc10->num_mpcc);
	वापस &(mpc->mpcc_array[mpcc_id]);
पूर्ण

काष्ठा mpcc *mpc1_get_mpcc_क्रम_dpp(काष्ठा mpc_tree *tree, पूर्णांक dpp_id)
अणु
	काष्ठा mpcc *पंचांगp_mpcc = tree->opp_list;

	जबतक (पंचांगp_mpcc != शून्य) अणु
		अगर (पंचांगp_mpcc->dpp_id == dpp_id)
			वापस पंचांगp_mpcc;
		पंचांगp_mpcc = पंचांगp_mpcc->mpcc_bot;
	पूर्ण
	वापस शून्य;
पूर्ण

bool mpc1_is_mpcc_idle(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	अचिन्हित पूर्णांक top_sel;
	अचिन्हित पूर्णांक opp_id;
	अचिन्हित पूर्णांक idle;

	REG_GET(MPCC_TOP_SEL[mpcc_id], MPCC_TOP_SEL, &top_sel);
	REG_GET(MPCC_OPP_ID[mpcc_id],  MPCC_OPP_ID, &opp_id);
	REG_GET(MPCC_STATUS[mpcc_id],  MPCC_IDLE,   &idle);
	अगर (top_sel == 0xf && opp_id == 0xf && idle)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम mpc1_निश्चित_mpcc_idle_beक्रमe_connect(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	अचिन्हित पूर्णांक top_sel, mpc_busy, mpc_idle;

	REG_GET(MPCC_TOP_SEL[mpcc_id],
			MPCC_TOP_SEL, &top_sel);

	अगर (top_sel == 0xf) अणु
		REG_GET_2(MPCC_STATUS[mpcc_id],
				MPCC_BUSY, &mpc_busy,
				MPCC_IDLE, &mpc_idle);

		ASSERT(mpc_busy == 0);
		ASSERT(mpc_idle == 1);
	पूर्ण
पूर्ण

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
 * [in]	dpp_id		- DPP instance क्रम the plane to be added.
 * [in]	mpcc_id		- The MPCC physical instance to use क्रम blending.
 *
 * Return:  काष्ठा mpcc* - MPCC that was added.
 */
काष्ठा mpcc *mpc1_insert_plane(
	काष्ठा mpc *mpc,
	काष्ठा mpc_tree *tree,
	काष्ठा mpcc_blnd_cfg *blnd_cfg,
	काष्ठा mpcc_sm_cfg *sm_cfg,
	काष्ठा mpcc *insert_above_mpcc,
	पूर्णांक dpp_id,
	पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	काष्ठा mpcc *new_mpcc = शून्य;

	/* sanity check parameters */
	ASSERT(mpcc_id < mpc10->num_mpcc);
	ASSERT(!(mpc10->mpcc_in_use_mask & 1 << mpcc_id));

	अगर (insert_above_mpcc) अणु
		/* check insert_above_mpcc exist in tree->opp_list */
		काष्ठा mpcc *temp_mpcc = tree->opp_list;

		जबतक (temp_mpcc && temp_mpcc->mpcc_bot != insert_above_mpcc)
			temp_mpcc = temp_mpcc->mpcc_bot;
		अगर (temp_mpcc == शून्य)
			वापस शून्य;
	पूर्ण

	/* Get and update MPCC काष्ठा parameters */
	new_mpcc = mpc1_get_mpcc(mpc, mpcc_id);
	new_mpcc->dpp_id = dpp_id;

	/* program mux and MPCC_MODE */
	अगर (insert_above_mpcc) अणु
		new_mpcc->mpcc_bot = insert_above_mpcc;
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, insert_above_mpcc->mpcc_id);
		REG_UPDATE(MPCC_CONTROL[mpcc_id], MPCC_MODE, MPCC_BLEND_MODE_TOP_BOT_BLENDING);
	पूर्ण अन्यथा अणु
		new_mpcc->mpcc_bot = शून्य;
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
		REG_UPDATE(MPCC_CONTROL[mpcc_id], MPCC_MODE, MPCC_BLEND_MODE_TOP_LAYER_ONLY);
	पूर्ण
	REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, dpp_id);
	REG_SET(MPCC_OPP_ID[mpcc_id], 0, MPCC_OPP_ID, tree->opp_id);

	/* Configure VUPDATE lock set क्रम this MPCC to map to the OPP */
	REG_SET(MPCC_UPDATE_LOCK_SEL[mpcc_id], 0, MPCC_UPDATE_LOCK_SEL, tree->opp_id);

	/* update mpc tree mux setting */
	अगर (tree->opp_list == insert_above_mpcc) अणु
		/* insert the toppest mpcc */
		tree->opp_list = new_mpcc;
		REG_UPDATE(MUX[tree->opp_id], MPC_OUT_MUX, mpcc_id);
	पूर्ण अन्यथा अणु
		/* find insert position */
		काष्ठा mpcc *temp_mpcc = tree->opp_list;

		जबतक (temp_mpcc && temp_mpcc->mpcc_bot != insert_above_mpcc)
			temp_mpcc = temp_mpcc->mpcc_bot;
		अगर (temp_mpcc && temp_mpcc->mpcc_bot == insert_above_mpcc) अणु
			REG_SET(MPCC_BOT_SEL[temp_mpcc->mpcc_id], 0, MPCC_BOT_SEL, mpcc_id);
			temp_mpcc->mpcc_bot = new_mpcc;
			अगर (!insert_above_mpcc)
				REG_UPDATE(MPCC_CONTROL[temp_mpcc->mpcc_id],
						MPCC_MODE, MPCC_BLEND_MODE_TOP_BOT_BLENDING);
		पूर्ण
	पूर्ण

	/* update the blending configuration */
	mpc->funcs->update_blending(mpc, blnd_cfg, mpcc_id);

	/* update the stereo mix settings, अगर provided */
	अगर (sm_cfg != शून्य) अणु
		new_mpcc->sm_cfg = *sm_cfg;
		mpc1_update_stereo_mix(mpc, sm_cfg, mpcc_id);
	पूर्ण

	/* mark this mpcc as in use */
	mpc10->mpcc_in_use_mask |= 1 << mpcc_id;

	वापस new_mpcc;
पूर्ण

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
व्योम mpc1_हटाओ_mpcc(
	काष्ठा mpc *mpc,
	काष्ठा mpc_tree *tree,
	काष्ठा mpcc *mpcc_to_हटाओ)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	bool found = false;
	पूर्णांक mpcc_id = mpcc_to_हटाओ->mpcc_id;

	अगर (tree->opp_list == mpcc_to_हटाओ) अणु
		found = true;
		/* हटाओ MPCC from top of tree */
		अगर (mpcc_to_हटाओ->mpcc_bot) अणु
			/* set the next MPCC in list to be the top MPCC */
			tree->opp_list = mpcc_to_हटाओ->mpcc_bot;
			REG_UPDATE(MUX[tree->opp_id], MPC_OUT_MUX, tree->opp_list->mpcc_id);
		पूर्ण अन्यथा अणु
			/* there are no other MPCC is list */
			tree->opp_list = शून्य;
			REG_UPDATE(MUX[tree->opp_id], MPC_OUT_MUX, 0xf);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* find mpcc to हटाओ MPCC list */
		काष्ठा mpcc *temp_mpcc = tree->opp_list;

		जबतक (temp_mpcc && temp_mpcc->mpcc_bot != mpcc_to_हटाओ)
			temp_mpcc = temp_mpcc->mpcc_bot;

		अगर (temp_mpcc && temp_mpcc->mpcc_bot == mpcc_to_हटाओ) अणु
			found = true;
			temp_mpcc->mpcc_bot = mpcc_to_हटाओ->mpcc_bot;
			अगर (mpcc_to_हटाओ->mpcc_bot) अणु
				/* हटाओ MPCC in middle of list */
				REG_SET(MPCC_BOT_SEL[temp_mpcc->mpcc_id], 0,
						MPCC_BOT_SEL, mpcc_to_हटाओ->mpcc_bot->mpcc_id);
			पूर्ण अन्यथा अणु
				/* हटाओ MPCC from bottom of list */
				REG_SET(MPCC_BOT_SEL[temp_mpcc->mpcc_id], 0,
						MPCC_BOT_SEL, 0xf);
				REG_UPDATE(MPCC_CONTROL[temp_mpcc->mpcc_id],
						MPCC_MODE, MPCC_BLEND_MODE_TOP_LAYER_PASSTHROUGH);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (found) अणु
		/* turn off MPCC mux रेजिस्टरs */
		REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, 0xf);
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
		REG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
		REG_SET(MPCC_UPDATE_LOCK_SEL[mpcc_id], 0, MPCC_UPDATE_LOCK_SEL, 0xf);

		/* mark this mpcc as not in use */
		mpc10->mpcc_in_use_mask &= ~(1 << mpcc_id);
		mpcc_to_हटाओ->dpp_id = 0xf;
		mpcc_to_हटाओ->mpcc_bot = शून्य;
	पूर्ण अन्यथा अणु
		/* In हाल of resume from S3/S4, हटाओ mpcc from bios left over */
		REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, 0xf);
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
		REG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
		REG_SET(MPCC_UPDATE_LOCK_SEL[mpcc_id], 0, MPCC_UPDATE_LOCK_SEL, 0xf);
	पूर्ण
पूर्ण

अटल व्योम mpc1_init_mpcc(काष्ठा mpcc *mpcc, पूर्णांक mpcc_inst)
अणु
	mpcc->mpcc_id = mpcc_inst;
	mpcc->dpp_id = 0xf;
	mpcc->mpcc_bot = शून्य;
	mpcc->blnd_cfg.overlap_only = false;
	mpcc->blnd_cfg.global_alpha = 0xff;
	mpcc->blnd_cfg.global_gain = 0xff;
	mpcc->sm_cfg.enable = false;
पूर्ण

/*
 * Reset the MPCC HW status by disconnecting all muxes.
 *
 * Parameters:
 * [in/out] mpc		- MPC context.
 *
 * Return:  व्योम
 */
व्योम mpc1_mpc_init(काष्ठा mpc *mpc)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	पूर्णांक mpcc_id;
	पूर्णांक opp_id;

	mpc10->mpcc_in_use_mask = 0;
	क्रम (mpcc_id = 0; mpcc_id < mpc10->num_mpcc; mpcc_id++) अणु
		REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, 0xf);
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
		REG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
		REG_SET(MPCC_UPDATE_LOCK_SEL[mpcc_id], 0, MPCC_UPDATE_LOCK_SEL, 0xf);

		mpc1_init_mpcc(&(mpc->mpcc_array[mpcc_id]), mpcc_id);
	पूर्ण

	क्रम (opp_id = 0; opp_id < MAX_OPP; opp_id++) अणु
		अगर (REG(MUX[opp_id]))
			REG_UPDATE(MUX[opp_id], MPC_OUT_MUX, 0xf);
	पूर्ण
पूर्ण

व्योम mpc1_mpc_init_single_inst(काष्ठा mpc *mpc, अचिन्हित पूर्णांक mpcc_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	पूर्णांक opp_id;

	REG_GET(MPCC_OPP_ID[mpcc_id], MPCC_OPP_ID, &opp_id);

	REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, 0xf);
	REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
	REG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
	REG_SET(MPCC_UPDATE_LOCK_SEL[mpcc_id], 0, MPCC_UPDATE_LOCK_SEL, 0xf);

	mpc1_init_mpcc(&(mpc->mpcc_array[mpcc_id]), mpcc_id);

	अगर (opp_id < MAX_OPP && REG(MUX[opp_id]))
		REG_UPDATE(MUX[opp_id], MPC_OUT_MUX, 0xf);
पूर्ण


व्योम mpc1_init_mpcc_list_from_hw(
	काष्ठा mpc *mpc,
	काष्ठा mpc_tree *tree)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	अचिन्हित पूर्णांक opp_id;
	अचिन्हित पूर्णांक top_sel;
	अचिन्हित पूर्णांक bot_sel;
	अचिन्हित पूर्णांक out_mux;
	काष्ठा mpcc *mpcc;
	पूर्णांक mpcc_id;
	पूर्णांक bot_mpcc_id;

	REG_GET(MUX[tree->opp_id], MPC_OUT_MUX, &out_mux);

	अगर (out_mux != 0xf) अणु
		क्रम (mpcc_id = 0; mpcc_id < mpc10->num_mpcc; mpcc_id++) अणु
			REG_GET(MPCC_OPP_ID[mpcc_id],  MPCC_OPP_ID,  &opp_id);
			REG_GET(MPCC_TOP_SEL[mpcc_id], MPCC_TOP_SEL, &top_sel);
			REG_GET(MPCC_BOT_SEL[mpcc_id],  MPCC_BOT_SEL, &bot_sel);

			अगर (bot_sel == mpcc_id)
				bot_sel = 0xf;

			अगर ((opp_id == tree->opp_id) && (top_sel != 0xf)) अणु
				mpcc = mpc1_get_mpcc(mpc, mpcc_id);
				mpcc->dpp_id = top_sel;
				mpc10->mpcc_in_use_mask |= 1 << mpcc_id;

				अगर (out_mux == mpcc_id)
					tree->opp_list = mpcc;
				अगर (bot_sel != 0xf && bot_sel < mpc10->num_mpcc) अणु
					bot_mpcc_id = bot_sel;
					REG_GET(MPCC_OPP_ID[bot_mpcc_id],  MPCC_OPP_ID,  &opp_id);
					REG_GET(MPCC_TOP_SEL[bot_mpcc_id], MPCC_TOP_SEL, &top_sel);
					अगर ((opp_id == tree->opp_id) && (top_sel != 0xf)) अणु
						काष्ठा mpcc *mpcc_bottom = mpc1_get_mpcc(mpc, bot_mpcc_id);

						mpcc->mpcc_bot = mpcc_bottom;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम mpc1_पढ़ो_mpcc_state(
		काष्ठा mpc *mpc,
		पूर्णांक mpcc_inst,
		काष्ठा mpcc_state *s)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	REG_GET(MPCC_OPP_ID[mpcc_inst], MPCC_OPP_ID, &s->opp_id);
	REG_GET(MPCC_TOP_SEL[mpcc_inst], MPCC_TOP_SEL, &s->dpp_id);
	REG_GET(MPCC_BOT_SEL[mpcc_inst], MPCC_BOT_SEL, &s->bot_mpcc_id);
	REG_GET_4(MPCC_CONTROL[mpcc_inst], MPCC_MODE, &s->mode,
			MPCC_ALPHA_BLND_MODE, &s->alpha_mode,
			MPCC_ALPHA_MULTIPLIED_MODE, &s->pre_multiplied_alpha,
			MPCC_BLND_ACTIVE_OVERLAP_ONLY, &s->overlap_only);
	REG_GET_2(MPCC_STATUS[mpcc_inst], MPCC_IDLE, &s->idle,
			MPCC_BUSY, &s->busy);
पूर्ण

व्योम mpc1_cursor_lock(काष्ठा mpc *mpc, पूर्णांक opp_id, bool lock)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	REG_SET(CUR[opp_id], 0, CUR_VUPDATE_LOCK_SET, lock ? 1 : 0);
पूर्ण

अचिन्हित पूर्णांक mpc1_get_mpc_out_mux(काष्ठा mpc *mpc, पूर्णांक opp_id)
अणु
	काष्ठा dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	uपूर्णांक32_t val = 0xf;

	अगर (opp_id < MAX_OPP && REG(MUX[opp_id]))
		REG_GET(MUX[opp_id], MPC_OUT_MUX, &val);

	वापस val;
पूर्ण

अटल स्थिर काष्ठा mpc_funcs dcn10_mpc_funcs = अणु
	.पढ़ो_mpcc_state = mpc1_पढ़ो_mpcc_state,
	.insert_plane = mpc1_insert_plane,
	.हटाओ_mpcc = mpc1_हटाओ_mpcc,
	.mpc_init = mpc1_mpc_init,
	.mpc_init_single_inst = mpc1_mpc_init_single_inst,
	.get_mpcc_क्रम_dpp = mpc1_get_mpcc_क्रम_dpp,
	.रुको_क्रम_idle = mpc1_निश्चित_idle_mpcc,
	.निश्चित_mpcc_idle_beक्रमe_connect = mpc1_निश्चित_mpcc_idle_beक्रमe_connect,
	.init_mpcc_list_from_hw = mpc1_init_mpcc_list_from_hw,
	.update_blending = mpc1_update_blending,
	.cursor_lock = mpc1_cursor_lock,
	.set_denorm = शून्य,
	.set_denorm_clamp = शून्य,
	.set_output_csc = शून्य,
	.set_output_gamma = शून्य,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
पूर्ण;

व्योम dcn10_mpc_स्थिरruct(काष्ठा dcn10_mpc *mpc10,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_mpc_रेजिस्टरs *mpc_regs,
	स्थिर काष्ठा dcn_mpc_shअगरt *mpc_shअगरt,
	स्थिर काष्ठा dcn_mpc_mask *mpc_mask,
	पूर्णांक num_mpcc)
अणु
	पूर्णांक i;

	mpc10->base.ctx = ctx;

	mpc10->base.funcs = &dcn10_mpc_funcs;

	mpc10->mpc_regs = mpc_regs;
	mpc10->mpc_shअगरt = mpc_shअगरt;
	mpc10->mpc_mask = mpc_mask;

	mpc10->mpcc_in_use_mask = 0;
	mpc10->num_mpcc = num_mpcc;

	क्रम (i = 0; i < MAX_MPCC; i++)
		mpc1_init_mpcc(&mpc10->base.mpcc_array[i], i);
पूर्ण

