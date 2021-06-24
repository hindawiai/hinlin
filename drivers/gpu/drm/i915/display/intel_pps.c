<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "g4x_dp.h"
#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_dpll.h"
#समावेश "intel_pps.h"

अटल व्योम vlv_steal_घातer_sequencer(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत pipe pipe);

अटल व्योम pps_init_delays(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);
अटल व्योम pps_init_रेजिस्टरs(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool क्रमce_disable_vdd);

पूर्णांकel_wakeref_t पूर्णांकel_pps_lock(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * See पूर्णांकel_pps_reset_all() why we need a घातer करोमुख्य reference here.
	 */
	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_DISPLAY_CORE);
	mutex_lock(&dev_priv->pps_mutex);

	वापस wakeref;
पूर्ण

पूर्णांकel_wakeref_t पूर्णांकel_pps_unlock(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				 पूर्णांकel_wakeref_t wakeref)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	mutex_unlock(&dev_priv->pps_mutex);
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस 0;
पूर्ण

अटल व्योम
vlv_घातer_sequencer_kick(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत pipe pipe = पूर्णांकel_dp->pps.pps_pipe;
	bool pll_enabled, release_cl_override = false;
	क्रमागत dpio_phy phy = DPIO_PHY(pipe);
	क्रमागत dpio_channel ch = vlv_pipe_to_channel(pipe);
	u32 DP;

	अगर (drm_WARN(&dev_priv->drm,
		     पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg) & DP_PORT_EN,
		     "skipping pipe %c power sequencer kick due to [ENCODER:%d:%s] being active\n",
		     pipe_name(pipe), dig_port->base.base.base.id,
		     dig_port->base.base.name))
		वापस;

	drm_dbg_kms(&dev_priv->drm,
		    "kicking pipe %c power sequencer for [ENCODER:%d:%s]\n",
		    pipe_name(pipe), dig_port->base.base.base.id,
		    dig_port->base.base.name);

	/* Preserve the BIOS-computed detected bit. This is
	 * supposed to be पढ़ो-only.
	 */
	DP = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg) & DP_DETECTED;
	DP |= DP_VOLTAGE_0_4 | DP_PRE_EMPHASIS_0;
	DP |= DP_PORT_WIDTH(1);
	DP |= DP_LINK_TRAIN_PAT_1;

	अगर (IS_CHERRYVIEW(dev_priv))
		DP |= DP_PIPE_SEL_CHV(pipe);
	अन्यथा
		DP |= DP_PIPE_SEL(pipe);

	pll_enabled = पूर्णांकel_de_पढ़ो(dev_priv, DPLL(pipe)) & DPLL_VCO_ENABLE;

	/*
	 * The DPLL क्रम the pipe must be enabled क्रम this to work.
	 * So enable temporarily it अगर it's not alपढ़ोy enabled.
	 */
	अगर (!pll_enabled) अणु
		release_cl_override = IS_CHERRYVIEW(dev_priv) &&
			!chv_phy_घातergate_ch(dev_priv, phy, ch, true);

		अगर (vlv_क्रमce_pll_on(dev_priv, pipe, vlv_get_dpll(dev_priv))) अणु
			drm_err(&dev_priv->drm,
				"Failed to force on pll for pipe %c!\n",
				pipe_name(pipe));
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Similar magic as in पूर्णांकel_dp_enable_port().
	 * We _must_ करो this port enable + disable trick
	 * to make this घातer sequencer lock onto the port.
	 * Otherwise even VDD क्रमce bit won't work.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP | DP_PORT_EN);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP & ~DP_PORT_EN);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	अगर (!pll_enabled) अणु
		vlv_क्रमce_pll_off(dev_priv, pipe);

		अगर (release_cl_override)
			chv_phy_घातergate_ch(dev_priv, phy, ch, false);
	पूर्ण
पूर्ण

अटल क्रमागत pipe vlv_find_मुक्त_pps(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	अचिन्हित पूर्णांक pipes = (1 << PIPE_A) | (1 << PIPE_B);

	/*
	 * We करोn't have घातer sequencer currently.
	 * Pick one that's not used by other ports.
	 */
	क्रम_each_पूर्णांकel_dp(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		अगर (encoder->type == INTEL_OUTPUT_EDP) अणु
			drm_WARN_ON(&dev_priv->drm,
				    पूर्णांकel_dp->pps.active_pipe != INVALID_PIPE &&
				    पूर्णांकel_dp->pps.active_pipe !=
				    पूर्णांकel_dp->pps.pps_pipe);

			अगर (पूर्णांकel_dp->pps.pps_pipe != INVALID_PIPE)
				pipes &= ~(1 << पूर्णांकel_dp->pps.pps_pipe);
		पूर्ण अन्यथा अणु
			drm_WARN_ON(&dev_priv->drm,
				    पूर्णांकel_dp->pps.pps_pipe != INVALID_PIPE);

			अगर (पूर्णांकel_dp->pps.active_pipe != INVALID_PIPE)
				pipes &= ~(1 << पूर्णांकel_dp->pps.active_pipe);
		पूर्ण
	पूर्ण

	अगर (pipes == 0)
		वापस INVALID_PIPE;

	वापस ffs(pipes) - 1;
पूर्ण

अटल क्रमागत pipe
vlv_घातer_sequencer_pipe(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत pipe pipe;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	/* We should never land here with regular DP ports */
	drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_dp_is_edp(पूर्णांकel_dp));

	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->pps.active_pipe != INVALID_PIPE &&
		    पूर्णांकel_dp->pps.active_pipe != पूर्णांकel_dp->pps.pps_pipe);

	अगर (पूर्णांकel_dp->pps.pps_pipe != INVALID_PIPE)
		वापस पूर्णांकel_dp->pps.pps_pipe;

	pipe = vlv_find_मुक्त_pps(dev_priv);

	/*
	 * Didn't find one. This should not happen since there
	 * are two घातer sequencers and up to two eDP ports.
	 */
	अगर (drm_WARN_ON(&dev_priv->drm, pipe == INVALID_PIPE))
		pipe = PIPE_A;

	vlv_steal_घातer_sequencer(dev_priv, pipe);
	पूर्णांकel_dp->pps.pps_pipe = pipe;

	drm_dbg_kms(&dev_priv->drm,
		    "picked pipe %c power sequencer for [ENCODER:%d:%s]\n",
		    pipe_name(पूर्णांकel_dp->pps.pps_pipe),
		    dig_port->base.base.base.id,
		    dig_port->base.base.name);

	/* init घातer sequencer on this pipe and port */
	pps_init_delays(पूर्णांकel_dp);
	pps_init_रेजिस्टरs(पूर्णांकel_dp, true);

	/*
	 * Even vdd क्रमce करोesn't work until we've made
	 * the घातer sequencer lock in on the port.
	 */
	vlv_घातer_sequencer_kick(पूर्णांकel_dp);

	वापस पूर्णांकel_dp->pps.pps_pipe;
पूर्ण

अटल पूर्णांक
bxt_घातer_sequencer_idx(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक backlight_controller = dev_priv->vbt.backlight.controller;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	/* We should never land here with regular DP ports */
	drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_dp_is_edp(पूर्णांकel_dp));

	अगर (!पूर्णांकel_dp->pps.pps_reset)
		वापस backlight_controller;

	पूर्णांकel_dp->pps.pps_reset = false;

	/*
	 * Only the HW needs to be reprogrammed, the SW state is fixed and
	 * has been setup during connector init.
	 */
	pps_init_रेजिस्टरs(पूर्णांकel_dp, false);

	वापस backlight_controller;
पूर्ण

प्रकार bool (*vlv_pipe_check)(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत pipe pipe);

अटल bool vlv_pipe_has_pp_on(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत pipe pipe)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv, PP_STATUS(pipe)) & PP_ON;
पूर्ण

अटल bool vlv_pipe_has_vdd_on(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत pipe pipe)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv, PP_CONTROL(pipe)) & EDP_FORCE_VDD;
पूर्ण

अटल bool vlv_pipe_any(काष्ठा drm_i915_निजी *dev_priv,
			 क्रमागत pipe pipe)
अणु
	वापस true;
पूर्ण

अटल क्रमागत pipe
vlv_initial_pps_pipe(काष्ठा drm_i915_निजी *dev_priv,
		     क्रमागत port port,
		     vlv_pipe_check pipe_check)
अणु
	क्रमागत pipe pipe;

	क्रम (pipe = PIPE_A; pipe <= PIPE_B; pipe++) अणु
		u32 port_sel = पूर्णांकel_de_पढ़ो(dev_priv, PP_ON_DELAYS(pipe)) &
			PANEL_PORT_SELECT_MASK;

		अगर (port_sel != PANEL_PORT_SELECT_VLV(port))
			जारी;

		अगर (!pipe_check(dev_priv, pipe))
			जारी;

		वापस pipe;
	पूर्ण

	वापस INVALID_PIPE;
पूर्ण

अटल व्योम
vlv_initial_घातer_sequencer_setup(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	क्रमागत port port = dig_port->base.port;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	/* try to find a pipe with this port selected */
	/* first pick one where the panel is on */
	पूर्णांकel_dp->pps.pps_pipe = vlv_initial_pps_pipe(dev_priv, port,
						      vlv_pipe_has_pp_on);
	/* didn't find one? pick one where vdd is on */
	अगर (पूर्णांकel_dp->pps.pps_pipe == INVALID_PIPE)
		पूर्णांकel_dp->pps.pps_pipe = vlv_initial_pps_pipe(dev_priv, port,
							      vlv_pipe_has_vdd_on);
	/* didn't find one? pick one with just the correct port */
	अगर (पूर्णांकel_dp->pps.pps_pipe == INVALID_PIPE)
		पूर्णांकel_dp->pps.pps_pipe = vlv_initial_pps_pipe(dev_priv, port,
							      vlv_pipe_any);

	/* didn't find one? just let vlv_घातer_sequencer_pipe() pick one when needed */
	अगर (पूर्णांकel_dp->pps.pps_pipe == INVALID_PIPE) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "no initial power sequencer for [ENCODER:%d:%s]\n",
			    dig_port->base.base.base.id,
			    dig_port->base.base.name);
		वापस;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "initial power sequencer for [ENCODER:%d:%s]: pipe %c\n",
		    dig_port->base.base.base.id,
		    dig_port->base.base.name,
		    pipe_name(पूर्णांकel_dp->pps.pps_pipe));
पूर्ण

व्योम पूर्णांकel_pps_reset_all(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (drm_WARN_ON(&dev_priv->drm,
			!(IS_VALLEYVIEW(dev_priv) ||
			  IS_CHERRYVIEW(dev_priv) ||
			  IS_GEN9_LP(dev_priv))))
		वापस;

	/*
	 * We can't grab pps_mutex here due to deadlock with घातer_करोमुख्य
	 * mutex when घातer_करोमुख्य functions are called जबतक holding pps_mutex.
	 * That also means that in order to use pps_pipe the code needs to
	 * hold both a घातer करोमुख्य reference and pps_mutex, and the घातer करोमुख्य
	 * reference get/put must be करोne जबतक _not_ holding pps_mutex.
	 * pps_अणुlock,unlockपूर्ण() करो these steps in the correct order, so one
	 * should use them always.
	 */

	क्रम_each_पूर्णांकel_dp(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		drm_WARN_ON(&dev_priv->drm,
			    पूर्णांकel_dp->pps.active_pipe != INVALID_PIPE);

		अगर (encoder->type != INTEL_OUTPUT_EDP)
			जारी;

		अगर (IS_GEN9_LP(dev_priv))
			पूर्णांकel_dp->pps.pps_reset = true;
		अन्यथा
			पूर्णांकel_dp->pps.pps_pipe = INVALID_PIPE;
	पूर्ण
पूर्ण

काष्ठा pps_रेजिस्टरs अणु
	i915_reg_t pp_ctrl;
	i915_reg_t pp_stat;
	i915_reg_t pp_on;
	i915_reg_t pp_off;
	i915_reg_t pp_भाग;
पूर्ण;

अटल व्योम पूर्णांकel_pps_get_रेजिस्टरs(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				    काष्ठा pps_रेजिस्टरs *regs)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक pps_idx = 0;

	स_रखो(regs, 0, माप(*regs));

	अगर (IS_GEN9_LP(dev_priv))
		pps_idx = bxt_घातer_sequencer_idx(पूर्णांकel_dp);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		pps_idx = vlv_घातer_sequencer_pipe(पूर्णांकel_dp);

	regs->pp_ctrl = PP_CONTROL(pps_idx);
	regs->pp_stat = PP_STATUS(pps_idx);
	regs->pp_on = PP_ON_DELAYS(pps_idx);
	regs->pp_off = PP_OFF_DELAYS(pps_idx);

	/* Cycle delay moved from PP_DIVISOR to PP_CONTROL */
	अगर (IS_GEN9_LP(dev_priv) || INTEL_PCH_TYPE(dev_priv) >= PCH_CNP)
		regs->pp_भाग = INVALID_MMIO_REG;
	अन्यथा
		regs->pp_भाग = PP_DIVISOR(pps_idx);
पूर्ण

अटल i915_reg_t
_pp_ctrl_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा pps_रेजिस्टरs regs;

	पूर्णांकel_pps_get_रेजिस्टरs(पूर्णांकel_dp, &regs);

	वापस regs.pp_ctrl;
पूर्ण

अटल i915_reg_t
_pp_stat_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा pps_रेजिस्टरs regs;

	पूर्णांकel_pps_get_रेजिस्टरs(पूर्णांकel_dp, &regs);

	वापस regs.pp_stat;
पूर्ण

अटल bool edp_have_panel_घातer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    पूर्णांकel_dp->pps.pps_pipe == INVALID_PIPE)
		वापस false;

	वापस (पूर्णांकel_de_पढ़ो(dev_priv, _pp_stat_reg(पूर्णांकel_dp)) & PP_ON) != 0;
पूर्ण

अटल bool edp_have_panel_vdd(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    पूर्णांकel_dp->pps.pps_pipe == INVALID_PIPE)
		वापस false;

	वापस पूर्णांकel_de_पढ़ो(dev_priv, _pp_ctrl_reg(पूर्णांकel_dp)) & EDP_FORCE_VDD;
पूर्ण

व्योम पूर्णांकel_pps_check_घातer_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	अगर (!edp_have_panel_घातer(पूर्णांकel_dp) && !edp_have_panel_vdd(पूर्णांकel_dp)) अणु
		drm_WARN(&dev_priv->drm, 1,
			 "eDP powered off while attempting aux channel communication.\n");
		drm_dbg_kms(&dev_priv->drm, "Status 0x%08x Control 0x%08x\n",
			    पूर्णांकel_de_पढ़ो(dev_priv, _pp_stat_reg(पूर्णांकel_dp)),
			    पूर्णांकel_de_पढ़ो(dev_priv, _pp_ctrl_reg(पूर्णांकel_dp)));
	पूर्ण
पूर्ण

#घोषणा IDLE_ON_MASK		(PP_ON | PP_SEQUENCE_MASK | 0                     | PP_SEQUENCE_STATE_MASK)
#घोषणा IDLE_ON_VALUE   	(PP_ON | PP_SEQUENCE_NONE | 0                     | PP_SEQUENCE_STATE_ON_IDLE)

#घोषणा IDLE_OFF_MASK		(PP_ON | PP_SEQUENCE_MASK | 0                     | 0)
#घोषणा IDLE_OFF_VALUE		(0     | PP_SEQUENCE_NONE | 0                     | 0)

#घोषणा IDLE_CYCLE_MASK		(PP_ON | PP_SEQUENCE_MASK | PP_CYCLE_DELAY_ACTIVE | PP_SEQUENCE_STATE_MASK)
#घोषणा IDLE_CYCLE_VALUE	(0     | PP_SEQUENCE_NONE | 0                     | PP_SEQUENCE_STATE_OFF_IDLE)

अटल व्योम पूर्णांकel_pps_verअगरy_state(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp);

अटल व्योम रुको_panel_status(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				       u32 mask,
				       u32 value)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	i915_reg_t pp_stat_reg, pp_ctrl_reg;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	पूर्णांकel_pps_verअगरy_state(पूर्णांकel_dp);

	pp_stat_reg = _pp_stat_reg(पूर्णांकel_dp);
	pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);

	drm_dbg_kms(&dev_priv->drm,
		    "mask %08x value %08x status %08x control %08x\n",
		    mask, value,
		    पूर्णांकel_de_पढ़ो(dev_priv, pp_stat_reg),
		    पूर्णांकel_de_पढ़ो(dev_priv, pp_ctrl_reg));

	अगर (पूर्णांकel_de_रुको_क्रम_रेजिस्टर(dev_priv, pp_stat_reg,
				       mask, value, 5000))
		drm_err(&dev_priv->drm,
			"Panel status timeout: status %08x control %08x\n",
			पूर्णांकel_de_पढ़ो(dev_priv, pp_stat_reg),
			पूर्णांकel_de_पढ़ो(dev_priv, pp_ctrl_reg));

	drm_dbg_kms(&dev_priv->drm, "Wait complete\n");
पूर्ण

अटल व्योम रुको_panel_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	drm_dbg_kms(&i915->drm, "Wait for panel power on\n");
	रुको_panel_status(पूर्णांकel_dp, IDLE_ON_MASK, IDLE_ON_VALUE);
पूर्ण

अटल व्योम रुको_panel_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	drm_dbg_kms(&i915->drm, "Wait for panel power off time\n");
	रुको_panel_status(पूर्णांकel_dp, IDLE_OFF_MASK, IDLE_OFF_VALUE);
पूर्ण

अटल व्योम रुको_panel_घातer_cycle(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	kसमय_प्रकार panel_घातer_on_समय;
	s64 panel_घातer_off_duration;

	drm_dbg_kms(&i915->drm, "Wait for panel power cycle\n");

	/* take the dअगरference of currrent समय and panel घातer off समय
	 * and then make panel रुको क्रम t11_t12 अगर needed. */
	panel_घातer_on_समय = kसमय_get_bootसमय();
	panel_घातer_off_duration = kसमय_ms_delta(panel_घातer_on_समय, पूर्णांकel_dp->pps.panel_घातer_off_समय);

	/* When we disable the VDD override bit last we have to करो the manual
	 * रुको. */
	अगर (panel_घातer_off_duration < (s64)पूर्णांकel_dp->pps.panel_घातer_cycle_delay)
		रुको_reमुख्यing_ms_from_jअगरfies(jअगरfies,
				       पूर्णांकel_dp->pps.panel_घातer_cycle_delay - panel_घातer_off_duration);

	रुको_panel_status(पूर्णांकel_dp, IDLE_CYCLE_MASK, IDLE_CYCLE_VALUE);
पूर्ण

व्योम पूर्णांकel_pps_रुको_घातer_cycle(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
		रुको_panel_घातer_cycle(पूर्णांकel_dp);
पूर्ण

अटल व्योम रुको_backlight_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	रुको_reमुख्यing_ms_from_jअगरfies(पूर्णांकel_dp->pps.last_घातer_on,
				       पूर्णांकel_dp->pps.backlight_on_delay);
पूर्ण

अटल व्योम edp_रुको_backlight_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	रुको_reमुख्यing_ms_from_jअगरfies(पूर्णांकel_dp->pps.last_backlight_off,
				       पूर्णांकel_dp->pps.backlight_off_delay);
पूर्ण

/* Read the current pp_control value, unlocking the रेजिस्टर अगर it
 * is locked
 */

अटल  u32 ilk_get_pp_control(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 control;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	control = पूर्णांकel_de_पढ़ो(dev_priv, _pp_ctrl_reg(पूर्णांकel_dp));
	अगर (drm_WARN_ON(&dev_priv->drm, !HAS_DDI(dev_priv) &&
			(control & PANEL_UNLOCK_MASK) != PANEL_UNLOCK_REGS)) अणु
		control &= ~PANEL_UNLOCK_MASK;
		control |= PANEL_UNLOCK_REGS;
	पूर्ण
	वापस control;
पूर्ण

/*
 * Must be paired with पूर्णांकel_pps_vdd_off_unlocked().
 * Must hold pps_mutex around the whole on/off sequence.
 * Can be nested with पूर्णांकel_pps_vdd_अणुon,offपूर्ण() calls.
 */
bool पूर्णांकel_pps_vdd_on_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	u32 pp;
	i915_reg_t pp_stat_reg, pp_ctrl_reg;
	bool need_to_disable = !पूर्णांकel_dp->pps.want_panel_vdd;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस false;

	cancel_delayed_work(&पूर्णांकel_dp->pps.panel_vdd_work);
	पूर्णांकel_dp->pps.want_panel_vdd = true;

	अगर (edp_have_panel_vdd(पूर्णांकel_dp))
		वापस need_to_disable;

	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->pps.vdd_wakeref);
	पूर्णांकel_dp->pps.vdd_wakeref = पूर्णांकel_display_घातer_get(dev_priv,
							    पूर्णांकel_aux_घातer_करोमुख्य(dig_port));

	drm_dbg_kms(&dev_priv->drm, "Turning [ENCODER:%d:%s] VDD on\n",
		    dig_port->base.base.base.id,
		    dig_port->base.base.name);

	अगर (!edp_have_panel_घातer(पूर्णांकel_dp))
		रुको_panel_घातer_cycle(पूर्णांकel_dp);

	pp = ilk_get_pp_control(पूर्णांकel_dp);
	pp |= EDP_FORCE_VDD;

	pp_stat_reg = _pp_stat_reg(पूर्णांकel_dp);
	pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);

	पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);
	drm_dbg_kms(&dev_priv->drm, "PP_STATUS: 0x%08x PP_CONTROL: 0x%08x\n",
		    पूर्णांकel_de_पढ़ो(dev_priv, pp_stat_reg),
		    पूर्णांकel_de_पढ़ो(dev_priv, pp_ctrl_reg));
	/*
	 * If the panel wasn't on, delay beक्रमe accessing aux channel
	 */
	अगर (!edp_have_panel_घातer(पूर्णांकel_dp)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "[ENCODER:%d:%s] panel power wasn't enabled\n",
			    dig_port->base.base.base.id,
			    dig_port->base.base.name);
		msleep(पूर्णांकel_dp->pps.panel_घातer_up_delay);
	पूर्ण

	वापस need_to_disable;
पूर्ण

/*
 * Must be paired with पूर्णांकel_pps_off().
 * Nested calls to these functions are not allowed since
 * we drop the lock. Caller must use some higher level
 * locking to prevent nested calls from other thपढ़ोs.
 */
व्योम पूर्णांकel_pps_vdd_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_wakeref_t wakeref;
	bool vdd;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	vdd = false;
	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
		vdd = पूर्णांकel_pps_vdd_on_unlocked(पूर्णांकel_dp);
	I915_STATE_WARN(!vdd, "[ENCODER:%d:%s] VDD already requested on\n",
			dp_to_dig_port(पूर्णांकel_dp)->base.base.base.id,
			dp_to_dig_port(पूर्णांकel_dp)->base.base.name);
पूर्ण

अटल व्योम पूर्णांकel_pps_vdd_off_sync_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port =
		dp_to_dig_port(पूर्णांकel_dp);
	u32 pp;
	i915_reg_t pp_stat_reg, pp_ctrl_reg;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->pps.want_panel_vdd);

	अगर (!edp_have_panel_vdd(पूर्णांकel_dp))
		वापस;

	drm_dbg_kms(&dev_priv->drm, "Turning [ENCODER:%d:%s] VDD off\n",
		    dig_port->base.base.base.id,
		    dig_port->base.base.name);

	pp = ilk_get_pp_control(पूर्णांकel_dp);
	pp &= ~EDP_FORCE_VDD;

	pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);
	pp_stat_reg = _pp_stat_reg(पूर्णांकel_dp);

	पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);

	/* Make sure sequencer is idle beक्रमe allowing subsequent activity */
	drm_dbg_kms(&dev_priv->drm, "PP_STATUS: 0x%08x PP_CONTROL: 0x%08x\n",
		    पूर्णांकel_de_पढ़ो(dev_priv, pp_stat_reg),
		    पूर्णांकel_de_पढ़ो(dev_priv, pp_ctrl_reg));

	अगर ((pp & PANEL_POWER_ON) == 0)
		पूर्णांकel_dp->pps.panel_घातer_off_समय = kसमय_get_bootसमय();

	पूर्णांकel_display_घातer_put(dev_priv,
				पूर्णांकel_aux_घातer_करोमुख्य(dig_port),
				fetch_and_zero(&पूर्णांकel_dp->pps.vdd_wakeref));
पूर्ण

व्योम पूर्णांकel_pps_vdd_off_sync(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	cancel_delayed_work_sync(&पूर्णांकel_dp->pps.panel_vdd_work);
	/*
	 * vdd might still be enabled due to the delayed vdd off.
	 * Make sure vdd is actually turned off here.
	 */
	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
		पूर्णांकel_pps_vdd_off_sync_unlocked(पूर्णांकel_dp);
पूर्ण

अटल व्योम edp_panel_vdd_work(काष्ठा work_काष्ठा *__work)
अणु
	काष्ठा पूर्णांकel_pps *pps = container_of(to_delayed_work(__work),
					     काष्ठा पूर्णांकel_pps, panel_vdd_work);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = container_of(pps, काष्ठा पूर्णांकel_dp, pps);
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref) अणु
		अगर (!पूर्णांकel_dp->pps.want_panel_vdd)
			पूर्णांकel_pps_vdd_off_sync_unlocked(पूर्णांकel_dp);
	पूर्ण
पूर्ण

अटल व्योम edp_panel_vdd_schedule_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	अचिन्हित दीर्घ delay;

	/*
	 * Queue the समयr to fire a दीर्घ समय from now (relative to the घातer
	 * करोwn delay) to keep the panel घातer up across a sequence of
	 * operations.
	 */
	delay = msecs_to_jअगरfies(पूर्णांकel_dp->pps.panel_घातer_cycle_delay * 5);
	schedule_delayed_work(&पूर्णांकel_dp->pps.panel_vdd_work, delay);
पूर्ण

/*
 * Must be paired with edp_panel_vdd_on().
 * Must hold pps_mutex around the whole on/off sequence.
 * Can be nested with पूर्णांकel_pps_vdd_अणुon,offपूर्ण() calls.
 */
व्योम पूर्णांकel_pps_vdd_off_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool sync)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	I915_STATE_WARN(!पूर्णांकel_dp->pps.want_panel_vdd, "[ENCODER:%d:%s] VDD not forced on",
			dp_to_dig_port(पूर्णांकel_dp)->base.base.base.id,
			dp_to_dig_port(पूर्णांकel_dp)->base.base.name);

	पूर्णांकel_dp->pps.want_panel_vdd = false;

	अगर (sync)
		पूर्णांकel_pps_vdd_off_sync_unlocked(पूर्णांकel_dp);
	अन्यथा
		edp_panel_vdd_schedule_off(पूर्णांकel_dp);
पूर्ण

व्योम पूर्णांकel_pps_on_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 pp;
	i915_reg_t pp_ctrl_reg;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	drm_dbg_kms(&dev_priv->drm, "Turn [ENCODER:%d:%s] panel power on\n",
		    dp_to_dig_port(पूर्णांकel_dp)->base.base.base.id,
		    dp_to_dig_port(पूर्णांकel_dp)->base.base.name);

	अगर (drm_WARN(&dev_priv->drm, edp_have_panel_घातer(पूर्णांकel_dp),
		     "[ENCODER:%d:%s] panel power already on\n",
		     dp_to_dig_port(पूर्णांकel_dp)->base.base.base.id,
		     dp_to_dig_port(पूर्णांकel_dp)->base.base.name))
		वापस;

	रुको_panel_घातer_cycle(पूर्णांकel_dp);

	pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);
	pp = ilk_get_pp_control(पूर्णांकel_dp);
	अगर (IS_IRONLAKE(dev_priv)) अणु
		/* ILK workaround: disable reset around घातer sequence */
		pp &= ~PANEL_POWER_RESET;
		पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);
	पूर्ण

	pp |= PANEL_POWER_ON;
	अगर (!IS_IRONLAKE(dev_priv))
		pp |= PANEL_POWER_RESET;

	पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);

	रुको_panel_on(पूर्णांकel_dp);
	पूर्णांकel_dp->pps.last_घातer_on = jअगरfies;

	अगर (IS_IRONLAKE(dev_priv)) अणु
		pp |= PANEL_POWER_RESET; /* restore panel reset bit */
		पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pps_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
		पूर्णांकel_pps_on_unlocked(पूर्णांकel_dp);
पूर्ण

व्योम पूर्णांकel_pps_off_unlocked(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	u32 pp;
	i915_reg_t pp_ctrl_reg;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	drm_dbg_kms(&dev_priv->drm, "Turn [ENCODER:%d:%s] panel power off\n",
		    dig_port->base.base.base.id, dig_port->base.base.name);

	drm_WARN(&dev_priv->drm, !पूर्णांकel_dp->pps.want_panel_vdd,
		 "Need [ENCODER:%d:%s] VDD to turn off panel\n",
		 dig_port->base.base.base.id, dig_port->base.base.name);

	pp = ilk_get_pp_control(पूर्णांकel_dp);
	/* We need to चयन off panel घातer _and_ क्रमce vdd, क्रम otherwise some
	 * panels get very unhappy and cease to work. */
	pp &= ~(PANEL_POWER_ON | PANEL_POWER_RESET | EDP_FORCE_VDD |
		EDP_BLC_ENABLE);

	pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);

	पूर्णांकel_dp->pps.want_panel_vdd = false;

	पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);

	रुको_panel_off(पूर्णांकel_dp);
	पूर्णांकel_dp->pps.panel_घातer_off_समय = kसमय_get_bootसमय();

	/* We got a reference when we enabled the VDD. */
	पूर्णांकel_display_घातer_put(dev_priv,
				पूर्णांकel_aux_घातer_करोमुख्य(dig_port),
				fetch_and_zero(&पूर्णांकel_dp->pps.vdd_wakeref));
पूर्ण

व्योम पूर्णांकel_pps_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
		पूर्णांकel_pps_off_unlocked(पूर्णांकel_dp);
पूर्ण

/* Enable backlight in the panel घातer control. */
व्योम पूर्णांकel_pps_backlight_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * If we enable the backlight right away following a panel घातer
	 * on, we may see slight flicker as the panel syncs with the eDP
	 * link.  So delay a bit to make sure the image is solid beक्रमe
	 * allowing it to appear.
	 */
	रुको_backlight_on(पूर्णांकel_dp);

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref) अणु
		i915_reg_t pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);
		u32 pp;

		pp = ilk_get_pp_control(पूर्णांकel_dp);
		pp |= EDP_BLC_ENABLE;

		पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);
	पूर्ण
पूर्ण

/* Disable backlight in the panel घातer control. */
व्योम पूर्णांकel_pps_backlight_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref) अणु
		i915_reg_t pp_ctrl_reg = _pp_ctrl_reg(पूर्णांकel_dp);
		u32 pp;

		pp = ilk_get_pp_control(पूर्णांकel_dp);
		pp &= ~EDP_BLC_ENABLE;

		पूर्णांकel_de_ग_लिखो(dev_priv, pp_ctrl_reg, pp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_ctrl_reg);
	पूर्ण

	पूर्णांकel_dp->pps.last_backlight_off = jअगरfies;
	edp_रुको_backlight_off(पूर्णांकel_dp);
पूर्ण

/*
 * Hook क्रम controlling the panel घातer control backlight through the bl_घातer
 * sysfs attribute. Take care to handle multiple calls.
 */
व्योम पूर्णांकel_pps_backlight_घातer(काष्ठा पूर्णांकel_connector *connector, bool enable)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_attached_dp(connector);
	पूर्णांकel_wakeref_t wakeref;
	bool is_enabled;

	is_enabled = false;
	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
		is_enabled = ilk_get_pp_control(पूर्णांकel_dp) & EDP_BLC_ENABLE;
	अगर (is_enabled == enable)
		वापस;

	drm_dbg_kms(&i915->drm, "panel power control backlight %s\n",
		    enable ? "enable" : "disable");

	अगर (enable)
		पूर्णांकel_pps_backlight_on(पूर्णांकel_dp);
	अन्यथा
		पूर्णांकel_pps_backlight_off(पूर्णांकel_dp);
पूर्ण

अटल व्योम vlv_detach_घातer_sequencer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत pipe pipe = पूर्णांकel_dp->pps.pps_pipe;
	i915_reg_t pp_on_reg = PP_ON_DELAYS(pipe);

	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->pps.active_pipe != INVALID_PIPE);

	अगर (drm_WARN_ON(&dev_priv->drm, pipe != PIPE_A && pipe != PIPE_B))
		वापस;

	पूर्णांकel_pps_vdd_off_sync_unlocked(पूर्णांकel_dp);

	/*
	 * VLV seems to get confused when multiple घातer sequencers
	 * have the same port selected (even अगर only one has घातer/vdd
	 * enabled). The failure manअगरests as vlv_रुको_port_पढ़ोy() failing
	 * CHV on the other hand करोesn't seem to mind having the same port
	 * selected in multiple घातer sequencers, but let's clear the
	 * port select always when logically disconnecting a घातer sequencer
	 * from a port.
	 */
	drm_dbg_kms(&dev_priv->drm,
		    "detaching pipe %c power sequencer from [ENCODER:%d:%s]\n",
		    pipe_name(pipe), dig_port->base.base.base.id,
		    dig_port->base.base.name);
	पूर्णांकel_de_ग_लिखो(dev_priv, pp_on_reg, 0);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, pp_on_reg);

	पूर्णांकel_dp->pps.pps_pipe = INVALID_PIPE;
पूर्ण

अटल व्योम vlv_steal_घातer_sequencer(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	क्रम_each_पूर्णांकel_dp(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		drm_WARN(&dev_priv->drm, पूर्णांकel_dp->pps.active_pipe == pipe,
			 "stealing pipe %c power sequencer from active [ENCODER:%d:%s]\n",
			 pipe_name(pipe), encoder->base.base.id,
			 encoder->base.name);

		अगर (पूर्णांकel_dp->pps.pps_pipe != pipe)
			जारी;

		drm_dbg_kms(&dev_priv->drm,
			    "stealing pipe %c power sequencer from [ENCODER:%d:%s]\n",
			    pipe_name(pipe), encoder->base.base.id,
			    encoder->base.name);

		/* make sure vdd is off beक्रमe we steal it */
		vlv_detach_घातer_sequencer(पूर्णांकel_dp);
	पूर्ण
पूर्ण

व्योम vlv_pps_init(काष्ठा पूर्णांकel_encoder *encoder,
		  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->pps.active_pipe != INVALID_PIPE);

	अगर (पूर्णांकel_dp->pps.pps_pipe != INVALID_PIPE &&
	    पूर्णांकel_dp->pps.pps_pipe != crtc->pipe) अणु
		/*
		 * If another घातer sequencer was being used on this
		 * port previously make sure to turn off vdd there जबतक
		 * we still have control of it.
		 */
		vlv_detach_घातer_sequencer(पूर्णांकel_dp);
	पूर्ण

	/*
	 * We may be stealing the घातer
	 * sequencer from another port.
	 */
	vlv_steal_घातer_sequencer(dev_priv, crtc->pipe);

	पूर्णांकel_dp->pps.active_pipe = crtc->pipe;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	/* now it's all ours */
	पूर्णांकel_dp->pps.pps_pipe = crtc->pipe;

	drm_dbg_kms(&dev_priv->drm,
		    "initializing pipe %c power sequencer for [ENCODER:%d:%s]\n",
		    pipe_name(पूर्णांकel_dp->pps.pps_pipe), encoder->base.base.id,
		    encoder->base.name);

	/* init घातer sequencer on this pipe and port */
	pps_init_delays(पूर्णांकel_dp);
	pps_init_रेजिस्टरs(पूर्णांकel_dp, true);
पूर्ण

अटल व्योम पूर्णांकel_pps_vdd_sanitize(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	अगर (!edp_have_panel_vdd(पूर्णांकel_dp))
		वापस;

	/*
	 * The VDD bit needs a घातer करोमुख्य reference, so अगर the bit is
	 * alपढ़ोy enabled when we boot or resume, grab this reference and
	 * schedule a vdd off, so we करोn't hold on to the reference
	 * indefinitely.
	 */
	drm_dbg_kms(&dev_priv->drm,
		    "VDD left on by BIOS, adjusting state tracking\n");
	drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dp->pps.vdd_wakeref);
	पूर्णांकel_dp->pps.vdd_wakeref = पूर्णांकel_display_घातer_get(dev_priv,
							    पूर्णांकel_aux_घातer_करोमुख्य(dig_port));

	edp_panel_vdd_schedule_off(पूर्णांकel_dp);
पूर्ण

bool पूर्णांकel_pps_have_घातer(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_wakeref_t wakeref;
	bool have_घातer = false;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref) अणु
		have_घातer = edp_have_panel_घातer(पूर्णांकel_dp) &&
						  edp_have_panel_vdd(पूर्णांकel_dp);
	पूर्ण

	वापस have_घातer;
पूर्ण

अटल व्योम pps_init_बारtamps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_dp->pps.panel_घातer_off_समय = kसमय_get_bootसमय();
	पूर्णांकel_dp->pps.last_घातer_on = jअगरfies;
	पूर्णांकel_dp->pps.last_backlight_off = jअगरfies;
पूर्ण

अटल व्योम
पूर्णांकel_pps_पढ़ोout_hw_state(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, काष्ठा edp_घातer_seq *seq)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 pp_on, pp_off, pp_ctl;
	काष्ठा pps_रेजिस्टरs regs;

	पूर्णांकel_pps_get_रेजिस्टरs(पूर्णांकel_dp, &regs);

	pp_ctl = ilk_get_pp_control(पूर्णांकel_dp);

	/* Ensure PPS is unlocked */
	अगर (!HAS_DDI(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, regs.pp_ctrl, pp_ctl);

	pp_on = पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_on);
	pp_off = पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_off);

	/* Pull timing values out of रेजिस्टरs */
	seq->t1_t3 = REG_FIELD_GET(PANEL_POWER_UP_DELAY_MASK, pp_on);
	seq->t8 = REG_FIELD_GET(PANEL_LIGHT_ON_DELAY_MASK, pp_on);
	seq->t9 = REG_FIELD_GET(PANEL_LIGHT_OFF_DELAY_MASK, pp_off);
	seq->t10 = REG_FIELD_GET(PANEL_POWER_DOWN_DELAY_MASK, pp_off);

	अगर (i915_mmio_reg_valid(regs.pp_भाग)) अणु
		u32 pp_भाग;

		pp_भाग = पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_भाग);

		seq->t11_t12 = REG_FIELD_GET(PANEL_POWER_CYCLE_DELAY_MASK, pp_भाग) * 1000;
	पूर्ण अन्यथा अणु
		seq->t11_t12 = REG_FIELD_GET(BXT_POWER_CYCLE_DELAY_MASK, pp_ctl) * 1000;
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_pps_dump_state(स्थिर अक्षर *state_name, स्थिर काष्ठा edp_घातer_seq *seq)
अणु
	DRM_DEBUG_KMS("%s t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
		      state_name,
		      seq->t1_t3, seq->t8, seq->t9, seq->t10, seq->t11_t12);
पूर्ण

अटल व्योम
पूर्णांकel_pps_verअगरy_state(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा edp_घातer_seq hw;
	काष्ठा edp_घातer_seq *sw = &पूर्णांकel_dp->pps.pps_delays;

	पूर्णांकel_pps_पढ़ोout_hw_state(पूर्णांकel_dp, &hw);

	अगर (hw.t1_t3 != sw->t1_t3 || hw.t8 != sw->t8 || hw.t9 != sw->t9 ||
	    hw.t10 != sw->t10 || hw.t11_t12 != sw->t11_t12) अणु
		DRM_ERROR("PPS state mismatch\n");
		पूर्णांकel_pps_dump_state("sw", sw);
		पूर्णांकel_pps_dump_state("hw", &hw);
	पूर्ण
पूर्ण

अटल व्योम pps_init_delays(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा edp_घातer_seq cur, vbt, spec,
		*final = &पूर्णांकel_dp->pps.pps_delays;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	/* alपढ़ोy initialized? */
	अगर (final->t11_t12 != 0)
		वापस;

	पूर्णांकel_pps_पढ़ोout_hw_state(पूर्णांकel_dp, &cur);

	पूर्णांकel_pps_dump_state("cur", &cur);

	vbt = dev_priv->vbt.edp.pps;
	/* On Toshiba Satellite P50-C-18C प्रणाली the VBT T12 delay
	 * of 500ms appears to be too लघु. Ocassionally the panel
	 * just fails to घातer back on. Increasing the delay to 800ms
	 * seems sufficient to aव्योम this problem.
	 */
	अगर (dev_priv->quirks & QUIRK_INCREASE_T12_DELAY) अणु
		vbt.t11_t12 = max_t(u16, vbt.t11_t12, 1300 * 10);
		drm_dbg_kms(&dev_priv->drm,
			    "Increasing T12 panel delay as per the quirk to %d\n",
			    vbt.t11_t12);
	पूर्ण
	/* T11_T12 delay is special and actually in units of 100ms, but zero
	 * based in the hw (so we need to add 100 ms). But the sw vbt
	 * table multiplies it with 1000 to make it in units of 100usec,
	 * too. */
	vbt.t11_t12 += 100 * 10;

	/* Upper limits from eDP 1.3 spec. Note that we use the clunky units of
	 * our hw here, which are all in 100usec. */
	spec.t1_t3 = 210 * 10;
	spec.t8 = 50 * 10; /* no limit क्रम t8, use t7 instead */
	spec.t9 = 50 * 10; /* no limit क्रम t9, make it symmetric with t8 */
	spec.t10 = 500 * 10;
	/* This one is special and actually in units of 100ms, but zero
	 * based in the hw (so we need to add 100 ms). But the sw vbt
	 * table multiplies it with 1000 to make it in units of 100usec,
	 * too. */
	spec.t11_t12 = (510 + 100) * 10;

	पूर्णांकel_pps_dump_state("vbt", &vbt);

	/* Use the max of the रेजिस्टर settings and vbt. If both are
	 * unset, fall back to the spec limits. */
#घोषणा assign_final(field)	final->field = (max(cur.field, vbt.field) == 0 ? \
				       spec.field : \
				       max(cur.field, vbt.field))
	assign_final(t1_t3);
	assign_final(t8);
	assign_final(t9);
	assign_final(t10);
	assign_final(t11_t12);
#अघोषित assign_final

#घोषणा get_delay(field)	(DIV_ROUND_UP(final->field, 10))
	पूर्णांकel_dp->pps.panel_घातer_up_delay = get_delay(t1_t3);
	पूर्णांकel_dp->pps.backlight_on_delay = get_delay(t8);
	पूर्णांकel_dp->pps.backlight_off_delay = get_delay(t9);
	पूर्णांकel_dp->pps.panel_घातer_करोwn_delay = get_delay(t10);
	पूर्णांकel_dp->pps.panel_घातer_cycle_delay = get_delay(t11_t12);
#अघोषित get_delay

	drm_dbg_kms(&dev_priv->drm,
		    "panel power up delay %d, power down delay %d, power cycle delay %d\n",
		    पूर्णांकel_dp->pps.panel_घातer_up_delay,
		    पूर्णांकel_dp->pps.panel_घातer_करोwn_delay,
		    पूर्णांकel_dp->pps.panel_घातer_cycle_delay);

	drm_dbg_kms(&dev_priv->drm, "backlight on delay %d, off delay %d\n",
		    पूर्णांकel_dp->pps.backlight_on_delay,
		    पूर्णांकel_dp->pps.backlight_off_delay);

	/*
	 * We override the HW backlight delays to 1 because we करो manual रुकोs
	 * on them. For T8, even BSpec recommends करोing it. For T9, अगर we
	 * करोn't do this, we'll end up रुकोing क्रम the backlight off delay
	 * twice: once when we करो the manual sleep, and once when we disable
	 * the panel and रुको क्रम the PP_STATUS bit to become zero.
	 */
	final->t8 = 1;
	final->t9 = 1;

	/*
	 * HW has only a 100msec granularity क्रम t11_t12 so round it up
	 * accordingly.
	 */
	final->t11_t12 = roundup(final->t11_t12, 100 * 10);
पूर्ण

अटल व्योम pps_init_रेजिस्टरs(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool क्रमce_disable_vdd)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 pp_on, pp_off, port_sel = 0;
	पूर्णांक भाग = RUNTIME_INFO(dev_priv)->rawclk_freq / 1000;
	काष्ठा pps_रेजिस्टरs regs;
	क्रमागत port port = dp_to_dig_port(पूर्णांकel_dp)->base.port;
	स्थिर काष्ठा edp_घातer_seq *seq = &पूर्णांकel_dp->pps.pps_delays;

	lockdep_निश्चित_held(&dev_priv->pps_mutex);

	पूर्णांकel_pps_get_रेजिस्टरs(पूर्णांकel_dp, &regs);

	/*
	 * On some VLV machines the BIOS can leave the VDD
	 * enabled even on घातer sequencers which aren't
	 * hooked up to any port. This would mess up the
	 * घातer करोमुख्य tracking the first समय we pick
	 * one of these घातer sequencers क्रम use since
	 * पूर्णांकel_pps_vdd_on_unlocked() would notice that the VDD was
	 * alपढ़ोy on and thereक्रमe wouldn't grab the घातer
	 * करोमुख्य reference. Disable VDD first to aव्योम this.
	 * This also aव्योमs spuriously turning the VDD on as
	 * soon as the new घातer sequencer माला_लो initialized.
	 */
	अगर (क्रमce_disable_vdd) अणु
		u32 pp = ilk_get_pp_control(पूर्णांकel_dp);

		drm_WARN(&dev_priv->drm, pp & PANEL_POWER_ON,
			 "Panel power already on\n");

		अगर (pp & EDP_FORCE_VDD)
			drm_dbg_kms(&dev_priv->drm,
				    "VDD already on, disabling first\n");

		pp &= ~EDP_FORCE_VDD;

		पूर्णांकel_de_ग_लिखो(dev_priv, regs.pp_ctrl, pp);
	पूर्ण

	pp_on = REG_FIELD_PREP(PANEL_POWER_UP_DELAY_MASK, seq->t1_t3) |
		REG_FIELD_PREP(PANEL_LIGHT_ON_DELAY_MASK, seq->t8);
	pp_off = REG_FIELD_PREP(PANEL_LIGHT_OFF_DELAY_MASK, seq->t9) |
		REG_FIELD_PREP(PANEL_POWER_DOWN_DELAY_MASK, seq->t10);

	/* Haswell करोesn't have any port selection bits क्रम the panel
	 * घातer sequencer any more. */
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		port_sel = PANEL_PORT_SELECT_VLV(port);
	पूर्ण अन्यथा अगर (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv)) अणु
		चयन (port) अणु
		हाल PORT_A:
			port_sel = PANEL_PORT_SELECT_DPA;
			अवरोध;
		हाल PORT_C:
			port_sel = PANEL_PORT_SELECT_DPC;
			अवरोध;
		हाल PORT_D:
			port_sel = PANEL_PORT_SELECT_DPD;
			अवरोध;
		शेष:
			MISSING_CASE(port);
			अवरोध;
		पूर्ण
	पूर्ण

	pp_on |= port_sel;

	पूर्णांकel_de_ग_लिखो(dev_priv, regs.pp_on, pp_on);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs.pp_off, pp_off);

	/*
	 * Compute the भागisor क्रम the pp घड़ी, simply match the Bspec क्रमmula.
	 */
	अगर (i915_mmio_reg_valid(regs.pp_भाग)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, regs.pp_भाग,
			       REG_FIELD_PREP(PP_REFERENCE_DIVIDER_MASK, (100 * भाग) / 2 - 1) | REG_FIELD_PREP(PANEL_POWER_CYCLE_DELAY_MASK, DIV_ROUND_UP(seq->t11_t12, 1000)));
	पूर्ण अन्यथा अणु
		u32 pp_ctl;

		pp_ctl = पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_ctrl);
		pp_ctl &= ~BXT_POWER_CYCLE_DELAY_MASK;
		pp_ctl |= REG_FIELD_PREP(BXT_POWER_CYCLE_DELAY_MASK, DIV_ROUND_UP(seq->t11_t12, 1000));
		पूर्णांकel_de_ग_लिखो(dev_priv, regs.pp_ctrl, pp_ctl);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "panel power sequencer register settings: PP_ON %#x, PP_OFF %#x, PP_DIV %#x\n",
		    पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_on),
		    पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_off),
		    i915_mmio_reg_valid(regs.pp_भाग) ?
		    पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_भाग) :
		    (पूर्णांकel_de_पढ़ो(dev_priv, regs.pp_ctrl) & BXT_POWER_CYCLE_DELAY_MASK));
पूर्ण

व्योम पूर्णांकel_pps_encoder_reset(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref) अणु
		/*
		 * Reinit the घातer sequencer also on the resume path, in हाल
		 * BIOS did something nasty with it.
		 */
		अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
			vlv_initial_घातer_sequencer_setup(पूर्णांकel_dp);

		pps_init_delays(पूर्णांकel_dp);
		pps_init_रेजिस्टरs(पूर्णांकel_dp, false);

		पूर्णांकel_pps_vdd_sanitize(पूर्णांकel_dp);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pps_init(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	INIT_DELAYED_WORK(&पूर्णांकel_dp->pps.panel_vdd_work, edp_panel_vdd_work);

	pps_init_बारtamps(पूर्णांकel_dp);

	पूर्णांकel_pps_encoder_reset(पूर्णांकel_dp);
पूर्ण

व्योम पूर्णांकel_pps_unlock_regs_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक pps_num;
	पूर्णांक pps_idx;

	अगर (HAS_DDI(dev_priv))
		वापस;
	/*
	 * This w/a is needed at least on CPT/PPT, but to be sure apply it
	 * everywhere where रेजिस्टरs can be ग_लिखो रक्षित.
	 */
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		pps_num = 2;
	अन्यथा
		pps_num = 1;

	क्रम (pps_idx = 0; pps_idx < pps_num; pps_idx++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, PP_CONTROL(pps_idx));

		val = (val & ~PANEL_UNLOCK_MASK) | PANEL_UNLOCK_REGS;
		पूर्णांकel_de_ग_लिखो(dev_priv, PP_CONTROL(pps_idx), val);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pps_setup(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (HAS_PCH_SPLIT(i915) || IS_GEN9_LP(i915))
		i915->pps_mmio_base = PCH_PPS_BASE;
	अन्यथा अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915))
		i915->pps_mmio_base = VLV_PPS_BASE;
	अन्यथा
		i915->pps_mmio_base = PPS_BASE;
पूर्ण
