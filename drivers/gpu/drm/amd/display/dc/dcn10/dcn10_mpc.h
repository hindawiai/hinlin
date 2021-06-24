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

#अगर_अघोषित __DC_MPCC_DCN10_H__
#घोषणा __DC_MPCC_DCN10_H__

#समावेश "mpc.h"

#घोषणा TO_DCN10_MPC(mpc_base) \
	container_of(mpc_base, काष्ठा dcn10_mpc, base)

#घोषणा MPC_COMMON_REG_LIST_DCN1_0(inst) \
	SRII(MPCC_TOP_SEL, MPCC, inst),\
	SRII(MPCC_BOT_SEL, MPCC, inst),\
	SRII(MPCC_CONTROL, MPCC, inst),\
	SRII(MPCC_STATUS, MPCC, inst),\
	SRII(MPCC_OPP_ID, MPCC, inst),\
	SRII(MPCC_BG_G_Y, MPCC, inst),\
	SRII(MPCC_BG_R_CR, MPCC, inst),\
	SRII(MPCC_BG_B_CB, MPCC, inst),\
	SRII(MPCC_SM_CONTROL, MPCC, inst),\
	SRII(MPCC_UPDATE_LOCK_SEL, MPCC, inst)

#घोषणा MPC_OUT_MUX_COMMON_REG_LIST_DCN1_0(inst) \
	SRII(MUX, MPC_OUT, inst),\
	VUPDATE_SRII(CUR, VUPDATE_LOCK_SET, inst)

#घोषणा MPC_COMMON_REG_VARIABLE_LIST \
	uपूर्णांक32_t MPCC_TOP_SEL[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_BOT_SEL[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_CONTROL[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_STATUS[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OPP_ID[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_BG_G_Y[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_BG_R_CR[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_BG_B_CB[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_SM_CONTROL[MAX_MPCC]; \
	uपूर्णांक32_t MUX[MAX_OPP]; \
	uपूर्णांक32_t MPCC_UPDATE_LOCK_SEL[MAX_MPCC]; \
	uपूर्णांक32_t CUR[MAX_OPP];

#घोषणा MPC_COMMON_MASK_SH_LIST_DCN1_0(mask_sh)\
	SF(MPCC0_MPCC_TOP_SEL, MPCC_TOP_SEL, mask_sh),\
	SF(MPCC0_MPCC_BOT_SEL, MPCC_BOT_SEL, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_MODE, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_ALPHA_BLND_MODE, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_ALPHA_MULTIPLIED_MODE, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_BLND_ACTIVE_OVERLAP_ONLY, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_GLOBAL_ALPHA, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_GLOBAL_GAIN, mask_sh),\
	SF(MPCC0_MPCC_STATUS, MPCC_IDLE, mask_sh),\
	SF(MPCC0_MPCC_STATUS, MPCC_BUSY, mask_sh),\
	SF(MPCC0_MPCC_OPP_ID, MPCC_OPP_ID, mask_sh),\
	SF(MPCC0_MPCC_BG_G_Y, MPCC_BG_G_Y, mask_sh),\
	SF(MPCC0_MPCC_BG_R_CR, MPCC_BG_R_CR, mask_sh),\
	SF(MPCC0_MPCC_BG_B_CB, MPCC_BG_B_CB, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTROL, MPCC_SM_EN, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTROL, MPCC_SM_MODE, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTROL, MPCC_SM_FRAME_ALT, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTROL, MPCC_SM_FIELD_ALT, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTROL, MPCC_SM_FORCE_NEXT_FRAME_POL, mask_sh),\
	SF(MPCC0_MPCC_SM_CONTROL, MPCC_SM_FORCE_NEXT_TOP_POL, mask_sh),\
	SF(MPC_OUT0_MUX, MPC_OUT_MUX, mask_sh),\
	SF(MPCC0_MPCC_UPDATE_LOCK_SEL, MPCC_UPDATE_LOCK_SEL, mask_sh)

#घोषणा MPC_REG_FIELD_LIST(type) \
	type MPCC_TOP_SEL;\
	type MPCC_BOT_SEL;\
	type MPCC_MODE;\
	type MPCC_ALPHA_BLND_MODE;\
	type MPCC_ALPHA_MULTIPLIED_MODE;\
	type MPCC_BLND_ACTIVE_OVERLAP_ONLY;\
	type MPCC_GLOBAL_ALPHA;\
	type MPCC_GLOBAL_GAIN;\
	type MPCC_IDLE;\
	type MPCC_BUSY;\
	type MPCC_OPP_ID;\
	type MPCC_BG_G_Y;\
	type MPCC_BG_R_CR;\
	type MPCC_BG_B_CB;\
	type MPCC_SM_EN;\
	type MPCC_SM_MODE;\
	type MPCC_SM_FRAME_ALT;\
	type MPCC_SM_FIELD_ALT;\
	type MPCC_SM_FORCE_NEXT_FRAME_POL;\
	type MPCC_SM_FORCE_NEXT_TOP_POL;\
	type MPC_OUT_MUX;\
	type MPCC_UPDATE_LOCK_SEL;\
	type CUR_VUPDATE_LOCK_SET;

काष्ठा dcn_mpc_रेजिस्टरs अणु
	MPC_COMMON_REG_VARIABLE_LIST
पूर्ण;

काष्ठा dcn_mpc_shअगरt अणु
	MPC_REG_FIELD_LIST(uपूर्णांक8_t)
पूर्ण;

काष्ठा dcn_mpc_mask अणु
	MPC_REG_FIELD_LIST(uपूर्णांक32_t)
पूर्ण;

काष्ठा dcn10_mpc अणु
	काष्ठा mpc base;

	पूर्णांक mpcc_in_use_mask;
	पूर्णांक num_mpcc;
	स्थिर काष्ठा dcn_mpc_रेजिस्टरs *mpc_regs;
	स्थिर काष्ठा dcn_mpc_shअगरt *mpc_shअगरt;
	स्थिर काष्ठा dcn_mpc_mask *mpc_mask;
पूर्ण;

व्योम dcn10_mpc_स्थिरruct(काष्ठा dcn10_mpc *mpcc10,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn_mpc_रेजिस्टरs *mpc_regs,
	स्थिर काष्ठा dcn_mpc_shअगरt *mpc_shअगरt,
	स्थिर काष्ठा dcn_mpc_mask *mpc_mask,
	पूर्णांक num_mpcc);

काष्ठा mpcc *mpc1_insert_plane(
	काष्ठा mpc *mpc,
	काष्ठा mpc_tree *tree,
	काष्ठा mpcc_blnd_cfg *blnd_cfg,
	काष्ठा mpcc_sm_cfg *sm_cfg,
	काष्ठा mpcc *insert_above_mpcc,
	पूर्णांक dpp_id,
	पूर्णांक mpcc_id);

व्योम mpc1_हटाओ_mpcc(
	काष्ठा mpc *mpc,
	काष्ठा mpc_tree *tree,
	काष्ठा mpcc *mpcc);

व्योम mpc1_mpc_init(
	काष्ठा mpc *mpc);

व्योम mpc1_mpc_init_single_inst(
	काष्ठा mpc *mpc,
	अचिन्हित पूर्णांक mpcc_id);

व्योम mpc1_निश्चित_idle_mpcc(
	काष्ठा mpc *mpc,
	पूर्णांक id);

व्योम mpc1_set_bg_color(
	काष्ठा mpc *mpc,
	काष्ठा tg_color *bg_color,
	पूर्णांक id);

व्योम mpc1_update_stereo_mix(
	काष्ठा mpc *mpc,
	काष्ठा mpcc_sm_cfg *sm_cfg,
	पूर्णांक mpcc_id);

bool mpc1_is_mpcc_idle(
	काष्ठा mpc *mpc,
	पूर्णांक mpcc_id);

व्योम mpc1_निश्चित_mpcc_idle_beक्रमe_connect(
	काष्ठा mpc *mpc,
	पूर्णांक mpcc_id);

व्योम mpc1_init_mpcc_list_from_hw(
	काष्ठा mpc *mpc,
	काष्ठा mpc_tree *tree);

काष्ठा mpcc *mpc1_get_mpcc(
	काष्ठा mpc *mpc,
	पूर्णांक mpcc_id);

काष्ठा mpcc *mpc1_get_mpcc_क्रम_dpp(
	काष्ठा mpc_tree *tree,
	पूर्णांक dpp_id);

व्योम mpc1_पढ़ो_mpcc_state(
		काष्ठा mpc *mpc,
		पूर्णांक mpcc_inst,
		काष्ठा mpcc_state *s);

व्योम mpc1_cursor_lock(काष्ठा mpc *mpc, पूर्णांक opp_id, bool lock);

अचिन्हित पूर्णांक mpc1_get_mpc_out_mux(काष्ठा mpc *mpc, पूर्णांक opp_id);
#पूर्ण_अगर
