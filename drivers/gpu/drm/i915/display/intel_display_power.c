<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "display/intel_crt.h"

#समावेश "i915_drv.h"
#समावेश "i915_irq.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_combo_phy.h"
#समावेश "intel_csr.h"
#समावेश "intel_display_power.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_pm.h"
#समावेश "intel_pps.h"
#समावेश "intel_sideband.h"
#समावेश "intel_tc.h"
#समावेश "intel_vga.h"

bool पूर्णांकel_display_घातer_well_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत i915_घातer_well_id घातer_well_id);

स्थिर अक्षर *
पूर्णांकel_display_घातer_करोमुख्य_str(क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	चयन (करोमुख्य) अणु
	हाल POWER_DOMAIN_DISPLAY_CORE:
		वापस "DISPLAY_CORE";
	हाल POWER_DOMAIN_PIPE_A:
		वापस "PIPE_A";
	हाल POWER_DOMAIN_PIPE_B:
		वापस "PIPE_B";
	हाल POWER_DOMAIN_PIPE_C:
		वापस "PIPE_C";
	हाल POWER_DOMAIN_PIPE_D:
		वापस "PIPE_D";
	हाल POWER_DOMAIN_PIPE_A_PANEL_FITTER:
		वापस "PIPE_A_PANEL_FITTER";
	हाल POWER_DOMAIN_PIPE_B_PANEL_FITTER:
		वापस "PIPE_B_PANEL_FITTER";
	हाल POWER_DOMAIN_PIPE_C_PANEL_FITTER:
		वापस "PIPE_C_PANEL_FITTER";
	हाल POWER_DOMAIN_PIPE_D_PANEL_FITTER:
		वापस "PIPE_D_PANEL_FITTER";
	हाल POWER_DOMAIN_TRANSCODER_A:
		वापस "TRANSCODER_A";
	हाल POWER_DOMAIN_TRANSCODER_B:
		वापस "TRANSCODER_B";
	हाल POWER_DOMAIN_TRANSCODER_C:
		वापस "TRANSCODER_C";
	हाल POWER_DOMAIN_TRANSCODER_D:
		वापस "TRANSCODER_D";
	हाल POWER_DOMAIN_TRANSCODER_EDP:
		वापस "TRANSCODER_EDP";
	हाल POWER_DOMAIN_TRANSCODER_VDSC_PW2:
		वापस "TRANSCODER_VDSC_PW2";
	हाल POWER_DOMAIN_TRANSCODER_DSI_A:
		वापस "TRANSCODER_DSI_A";
	हाल POWER_DOMAIN_TRANSCODER_DSI_C:
		वापस "TRANSCODER_DSI_C";
	हाल POWER_DOMAIN_PORT_DDI_A_LANES:
		वापस "PORT_DDI_A_LANES";
	हाल POWER_DOMAIN_PORT_DDI_B_LANES:
		वापस "PORT_DDI_B_LANES";
	हाल POWER_DOMAIN_PORT_DDI_C_LANES:
		वापस "PORT_DDI_C_LANES";
	हाल POWER_DOMAIN_PORT_DDI_D_LANES:
		वापस "PORT_DDI_D_LANES";
	हाल POWER_DOMAIN_PORT_DDI_E_LANES:
		वापस "PORT_DDI_E_LANES";
	हाल POWER_DOMAIN_PORT_DDI_F_LANES:
		वापस "PORT_DDI_F_LANES";
	हाल POWER_DOMAIN_PORT_DDI_G_LANES:
		वापस "PORT_DDI_G_LANES";
	हाल POWER_DOMAIN_PORT_DDI_H_LANES:
		वापस "PORT_DDI_H_LANES";
	हाल POWER_DOMAIN_PORT_DDI_I_LANES:
		वापस "PORT_DDI_I_LANES";
	हाल POWER_DOMAIN_PORT_DDI_A_IO:
		वापस "PORT_DDI_A_IO";
	हाल POWER_DOMAIN_PORT_DDI_B_IO:
		वापस "PORT_DDI_B_IO";
	हाल POWER_DOMAIN_PORT_DDI_C_IO:
		वापस "PORT_DDI_C_IO";
	हाल POWER_DOMAIN_PORT_DDI_D_IO:
		वापस "PORT_DDI_D_IO";
	हाल POWER_DOMAIN_PORT_DDI_E_IO:
		वापस "PORT_DDI_E_IO";
	हाल POWER_DOMAIN_PORT_DDI_F_IO:
		वापस "PORT_DDI_F_IO";
	हाल POWER_DOMAIN_PORT_DDI_G_IO:
		वापस "PORT_DDI_G_IO";
	हाल POWER_DOMAIN_PORT_DDI_H_IO:
		वापस "PORT_DDI_H_IO";
	हाल POWER_DOMAIN_PORT_DDI_I_IO:
		वापस "PORT_DDI_I_IO";
	हाल POWER_DOMAIN_PORT_DSI:
		वापस "PORT_DSI";
	हाल POWER_DOMAIN_PORT_CRT:
		वापस "PORT_CRT";
	हाल POWER_DOMAIN_PORT_OTHER:
		वापस "PORT_OTHER";
	हाल POWER_DOMAIN_VGA:
		वापस "VGA";
	हाल POWER_DOMAIN_AUDIO:
		वापस "AUDIO";
	हाल POWER_DOMAIN_AUX_A:
		वापस "AUX_A";
	हाल POWER_DOMAIN_AUX_B:
		वापस "AUX_B";
	हाल POWER_DOMAIN_AUX_C:
		वापस "AUX_C";
	हाल POWER_DOMAIN_AUX_D:
		वापस "AUX_D";
	हाल POWER_DOMAIN_AUX_E:
		वापस "AUX_E";
	हाल POWER_DOMAIN_AUX_F:
		वापस "AUX_F";
	हाल POWER_DOMAIN_AUX_G:
		वापस "AUX_G";
	हाल POWER_DOMAIN_AUX_H:
		वापस "AUX_H";
	हाल POWER_DOMAIN_AUX_I:
		वापस "AUX_I";
	हाल POWER_DOMAIN_AUX_IO_A:
		वापस "AUX_IO_A";
	हाल POWER_DOMAIN_AUX_C_TBT:
		वापस "AUX_C_TBT";
	हाल POWER_DOMAIN_AUX_D_TBT:
		वापस "AUX_D_TBT";
	हाल POWER_DOMAIN_AUX_E_TBT:
		वापस "AUX_E_TBT";
	हाल POWER_DOMAIN_AUX_F_TBT:
		वापस "AUX_F_TBT";
	हाल POWER_DOMAIN_AUX_G_TBT:
		वापस "AUX_G_TBT";
	हाल POWER_DOMAIN_AUX_H_TBT:
		वापस "AUX_H_TBT";
	हाल POWER_DOMAIN_AUX_I_TBT:
		वापस "AUX_I_TBT";
	हाल POWER_DOMAIN_GMBUS:
		वापस "GMBUS";
	हाल POWER_DOMAIN_INIT:
		वापस "INIT";
	हाल POWER_DOMAIN_MODESET:
		वापस "MODESET";
	हाल POWER_DOMAIN_GT_IRQ:
		वापस "GT_IRQ";
	हाल POWER_DOMAIN_DPLL_DC_OFF:
		वापस "DPLL_DC_OFF";
	हाल POWER_DOMAIN_TC_COLD_OFF:
		वापस "TC_COLD_OFF";
	शेष:
		MISSING_CASE(करोमुख्य);
		वापस "?";
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
				    काष्ठा i915_घातer_well *घातer_well)
अणु
	drm_dbg_kms(&dev_priv->drm, "enabling %s\n", घातer_well->desc->name);
	घातer_well->desc->ops->enable(dev_priv, घातer_well);
	घातer_well->hw_enabled = true;
पूर्ण

अटल व्योम पूर्णांकel_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
				     काष्ठा i915_घातer_well *घातer_well)
अणु
	drm_dbg_kms(&dev_priv->drm, "disabling %s\n", घातer_well->desc->name);
	घातer_well->hw_enabled = false;
	घातer_well->desc->ops->disable(dev_priv, घातer_well);
पूर्ण

अटल व्योम पूर्णांकel_घातer_well_get(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा i915_घातer_well *घातer_well)
अणु
	अगर (!घातer_well->count++)
		पूर्णांकel_घातer_well_enable(dev_priv, घातer_well);
पूर्ण

अटल व्योम पूर्णांकel_घातer_well_put(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा i915_घातer_well *घातer_well)
अणु
	drm_WARN(&dev_priv->drm, !घातer_well->count,
		 "Use count on power well %s is already zero",
		 घातer_well->desc->name);

	अगर (!--घातer_well->count)
		पूर्णांकel_घातer_well_disable(dev_priv, घातer_well);
पूर्ण

/**
 * __पूर्णांकel_display_घातer_is_enabled - unlocked check क्रम a घातer करोमुख्य
 * @dev_priv: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to check
 *
 * This is the unlocked version of पूर्णांकel_display_घातer_is_enabled() and should
 * only be used from error capture and recovery code where deadlocks are
 * possible.
 *
 * Returns:
 * True when the घातer करोमुख्य is enabled, false otherwise.
 */
bool __पूर्णांकel_display_घातer_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_well *घातer_well;
	bool is_enabled;

	अगर (dev_priv->runसमय_pm.suspended)
		वापस false;

	is_enabled = true;

	क्रम_each_घातer_करोमुख्य_well_reverse(dev_priv, घातer_well, BIT_ULL(करोमुख्य)) अणु
		अगर (घातer_well->desc->always_on)
			जारी;

		अगर (!घातer_well->hw_enabled) अणु
			is_enabled = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस is_enabled;
पूर्ण

/**
 * पूर्णांकel_display_घातer_is_enabled - check क्रम a घातer करोमुख्य
 * @dev_priv: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to check
 *
 * This function can be used to check the hw घातer करोमुख्य state. It is mostly
 * used in hardware state पढ़ोout functions. Everywhere अन्यथा code should rely
 * upon explicit घातer करोमुख्य reference counting to ensure that the hardware
 * block is घातered up beक्रमe accessing it.
 *
 * Callers must hold the relevant modesetting locks to ensure that concurrent
 * thपढ़ोs can't disable the घातer well जबतक the caller tries to पढ़ो a few
 * रेजिस्टरs.
 *
 * Returns:
 * True when the घातer करोमुख्य is enabled, false otherwise.
 */
bool पूर्णांकel_display_घातer_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs;
	bool ret;

	घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;

	mutex_lock(&घातer_करोमुख्यs->lock);
	ret = __पूर्णांकel_display_घातer_is_enabled(dev_priv, करोमुख्य);
	mutex_unlock(&घातer_करोमुख्यs->lock);

	वापस ret;
पूर्ण

/*
 * Starting with Haswell, we have a "Power Down Well" that can be turned off
 * when not needed anymore. We have 4 रेजिस्टरs that can request the घातer well
 * to be enabled, and it will only be disabled अगर none of the रेजिस्टरs is
 * requesting it to be enabled.
 */
अटल व्योम hsw_घातer_well_post_enable(काष्ठा drm_i915_निजी *dev_priv,
				       u8 irq_pipe_mask, bool has_vga)
अणु
	अगर (has_vga)
		पूर्णांकel_vga_reset_io_mem(dev_priv);

	अगर (irq_pipe_mask)
		gen8_irq_घातer_well_post_enable(dev_priv, irq_pipe_mask);
पूर्ण

अटल व्योम hsw_घातer_well_pre_disable(काष्ठा drm_i915_निजी *dev_priv,
				       u8 irq_pipe_mask)
अणु
	अगर (irq_pipe_mask)
		gen8_irq_घातer_well_pre_disable(dev_priv, irq_pipe_mask);
पूर्ण

#घोषणा ICL_AUX_PW_TO_CH(pw_idx)	\
	((pw_idx) - ICL_PW_CTL_IDX_AUX_A + AUX_CH_A)

#घोषणा ICL_TBT_AUX_PW_TO_CH(pw_idx)	\
	((pw_idx) - ICL_PW_CTL_IDX_AUX_TBT1 + AUX_CH_C)

अटल क्रमागत aux_ch icl_tc_phy_aux_ch(काष्ठा drm_i915_निजी *dev_priv,
				     काष्ठा i915_घातer_well *घातer_well)
अणु
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;

	वापस घातer_well->desc->hsw.is_tc_tbt ? ICL_TBT_AUX_PW_TO_CH(pw_idx) :
						 ICL_AUX_PW_TO_CH(pw_idx);
पूर्ण

अटल काष्ठा पूर्णांकel_digital_port *
aux_ch_to_digital_port(काष्ठा drm_i915_निजी *dev_priv,
		       क्रमागत aux_ch aux_ch)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = शून्य;
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		/* We'll check the MST primary port */
		अगर (encoder->type == INTEL_OUTPUT_DP_MST)
			जारी;

		dig_port = enc_to_dig_port(encoder);
		अगर (!dig_port)
			जारी;

		अगर (dig_port->aux_ch != aux_ch) अणु
			dig_port = शून्य;
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस dig_port;
पूर्ण

अटल व्योम hsw_रुको_क्रम_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well,
					   bool समयout_expected)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;

	/* Timeout क्रम PW1:10 us, AUX:not specअगरied, other PWs:20 us. */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, regs->driver,
				  HSW_PWR_WELL_CTL_STATE(pw_idx), 1)) अणु
		drm_dbg_kms(&dev_priv->drm, "%s power well enable timeout\n",
			    घातer_well->desc->name);

		drm_WARN_ON(&dev_priv->drm, !समयout_expected);

	पूर्ण
पूर्ण

अटल u32 hsw_घातer_well_requesters(काष्ठा drm_i915_निजी *dev_priv,
				     स्थिर काष्ठा i915_घातer_well_regs *regs,
				     पूर्णांक pw_idx)
अणु
	u32 req_mask = HSW_PWR_WELL_CTL_REQ(pw_idx);
	u32 ret;

	ret = पूर्णांकel_de_पढ़ो(dev_priv, regs->bios) & req_mask ? 1 : 0;
	ret |= पूर्णांकel_de_पढ़ो(dev_priv, regs->driver) & req_mask ? 2 : 0;
	अगर (regs->kvmr.reg)
		ret |= पूर्णांकel_de_पढ़ो(dev_priv, regs->kvmr) & req_mask ? 4 : 0;
	ret |= पूर्णांकel_de_पढ़ो(dev_priv, regs->debug) & req_mask ? 8 : 0;

	वापस ret;
पूर्ण

अटल व्योम hsw_रुको_क्रम_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					    काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	bool disabled;
	u32 reqs;

	/*
	 * Bspec करोesn't require रुकोing क्रम PWs to get disabled, but still करो
	 * this क्रम paranoia. The known हालs where a PW will be क्रमced on:
	 * - a KVMR request on any घातer well via the KVMR request रेजिस्टर
	 * - a DMC request on PW1 and MISC_IO घातer wells via the BIOS and
	 *   DEBUG request रेजिस्टरs
	 * Skip the रुको in हाल any of the request bits are set and prपूर्णांक a
	 * diagnostic message.
	 */
	रुको_क्रम((disabled = !(पूर्णांकel_de_पढ़ो(dev_priv, regs->driver) &
			       HSW_PWR_WELL_CTL_STATE(pw_idx))) ||
		 (reqs = hsw_घातer_well_requesters(dev_priv, regs, pw_idx)), 1);
	अगर (disabled)
		वापस;

	drm_dbg_kms(&dev_priv->drm,
		    "%s forced on (bios:%d driver:%d kvmr:%d debug:%d)\n",
		    घातer_well->desc->name,
		    !!(reqs & 1), !!(reqs & 2), !!(reqs & 4), !!(reqs & 8));
पूर्ण

अटल व्योम gen9_रुको_क्रम_घातer_well_fuses(काष्ठा drm_i915_निजी *dev_priv,
					   क्रमागत skl_घातer_gate pg)
अणु
	/* Timeout 5us क्रम PG#0, क्रम other PGs 1us */
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_रुको_क्रम_set(dev_priv, SKL_FUSE_STATUS,
					  SKL_FUSE_PG_DIST_STATUS(pg), 1));
पूर्ण

अटल व्योम hsw_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	u32 val;

	अगर (घातer_well->desc->hsw.has_fuses) अणु
		क्रमागत skl_घातer_gate pg;

		pg = DISPLAY_VER(dev_priv) >= 11 ? ICL_PW_CTL_IDX_TO_PG(pw_idx) :
						 SKL_PW_CTL_IDX_TO_PG(pw_idx);
		/*
		 * For PW1 we have to रुको both क्रम the PW0/PG0 fuse state
		 * beक्रमe enabling the घातer well and PW1/PG1's own fuse
		 * state after the enabling. For all other घातer wells with
		 * fuses we only have to रुको क्रम that PW/PG's fuse state
		 * after the enabling.
		 */
		अगर (pg == SKL_PG1)
			gen9_रुको_क्रम_घातer_well_fuses(dev_priv, SKL_PG0);
	पूर्ण

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs->driver,
		       val | HSW_PWR_WELL_CTL_REQ(pw_idx));

	hsw_रुको_क्रम_घातer_well_enable(dev_priv, घातer_well, false);

	/* Display WA #1178: cnl */
	अगर (IS_CANNONLAKE(dev_priv) &&
	    pw_idx >= GLK_PW_CTL_IDX_AUX_B &&
	    pw_idx <= CNL_PW_CTL_IDX_AUX_F) अणु
		u32 val;

		val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_AUX_ANAOVRD1(pw_idx));
		val |= CNL_AUX_ANAOVRD1_ENABLE | CNL_AUX_ANAOVRD1_LDO_BYPASS;
		पूर्णांकel_de_ग_लिखो(dev_priv, CNL_AUX_ANAOVRD1(pw_idx), val);
	पूर्ण

	अगर (घातer_well->desc->hsw.has_fuses) अणु
		क्रमागत skl_घातer_gate pg;

		pg = DISPLAY_VER(dev_priv) >= 11 ? ICL_PW_CTL_IDX_TO_PG(pw_idx) :
						 SKL_PW_CTL_IDX_TO_PG(pw_idx);
		gen9_रुको_क्रम_घातer_well_fuses(dev_priv, pg);
	पूर्ण

	hsw_घातer_well_post_enable(dev_priv,
				   घातer_well->desc->hsw.irq_pipe_mask,
				   घातer_well->desc->hsw.has_vga);
पूर्ण

अटल व्योम hsw_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	u32 val;

	hsw_घातer_well_pre_disable(dev_priv,
				   घातer_well->desc->hsw.irq_pipe_mask);

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs->driver,
		       val & ~HSW_PWR_WELL_CTL_REQ(pw_idx));
	hsw_रुको_क्रम_घातer_well_disable(dev_priv, घातer_well);
पूर्ण

#घोषणा ICL_AUX_PW_TO_PHY(pw_idx)	((pw_idx) - ICL_PW_CTL_IDX_AUX_A)

अटल व्योम
icl_combo_phy_aux_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
				    काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	क्रमागत phy phy = ICL_AUX_PW_TO_PHY(pw_idx);
	u32 val;

	drm_WARN_ON(&dev_priv->drm, !IS_ICELAKE(dev_priv));

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs->driver,
		       val | HSW_PWR_WELL_CTL_REQ(pw_idx));

	अगर (DISPLAY_VER(dev_priv) < 12) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_CL_DW12(phy));
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_CL_DW12(phy),
			       val | ICL_LANE_ENABLE_AUX);
	पूर्ण

	hsw_रुको_क्रम_घातer_well_enable(dev_priv, घातer_well, false);

	/* Display WA #1178: icl */
	अगर (pw_idx >= ICL_PW_CTL_IDX_AUX_A && pw_idx <= ICL_PW_CTL_IDX_AUX_B &&
	    !पूर्णांकel_bios_is_port_edp(dev_priv, (क्रमागत port)phy)) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_AUX_ANAOVRD1(pw_idx));
		val |= ICL_AUX_ANAOVRD1_ENABLE | ICL_AUX_ANAOVRD1_LDO_BYPASS;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_AUX_ANAOVRD1(pw_idx), val);
	पूर्ण
पूर्ण

अटल व्योम
icl_combo_phy_aux_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
				     काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	क्रमागत phy phy = ICL_AUX_PW_TO_PHY(pw_idx);
	u32 val;

	drm_WARN_ON(&dev_priv->drm, !IS_ICELAKE(dev_priv));

	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_CL_DW12(phy));
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_CL_DW12(phy),
		       val & ~ICL_LANE_ENABLE_AUX);

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs->driver,
		       val & ~HSW_PWR_WELL_CTL_REQ(pw_idx));

	hsw_रुको_क्रम_घातer_well_disable(dev_priv, घातer_well);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)

अटल u64 async_put_करोमुख्यs_mask(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs);

अटल पूर्णांक घातer_well_async_ref_count(काष्ठा drm_i915_निजी *dev_priv,
				      काष्ठा i915_घातer_well *घातer_well)
अणु
	पूर्णांक refs = hweight64(घातer_well->desc->करोमुख्यs &
			     async_put_करोमुख्यs_mask(&dev_priv->घातer_करोमुख्यs));

	drm_WARN_ON(&dev_priv->drm, refs > घातer_well->count);

	वापस refs;
पूर्ण

अटल व्योम icl_tc_port_निश्चित_ref_held(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा i915_घातer_well *घातer_well,
					काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	/* Bypass the check अगर all references are released asynchronously */
	अगर (घातer_well_async_ref_count(dev_priv, घातer_well) ==
	    घातer_well->count)
		वापस;

	अगर (drm_WARN_ON(&dev_priv->drm, !dig_port))
		वापस;

	अगर (IS_DISPLAY_VER(dev_priv, 11) && dig_port->tc_legacy_port)
		वापस;

	drm_WARN_ON(&dev_priv->drm, !पूर्णांकel_tc_port_ref_held(dig_port));
पूर्ण

#अन्यथा

अटल व्योम icl_tc_port_निश्चित_ref_held(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा i915_घातer_well *घातer_well,
					काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
पूर्ण

#पूर्ण_अगर

#घोषणा TGL_AUX_PW_TO_TC_PORT(pw_idx)	((pw_idx) - TGL_PW_CTL_IDX_AUX_TC1)

अटल व्योम icl_tc_cold_निकास(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret, tries = 0;

	जबतक (1) अणु
		ret = sandybridge_pcode_ग_लिखो_समयout(i915,
						      ICL_PCODE_EXIT_TCCOLD,
						      0, 250, 1);
		अगर (ret != -EAGAIN || ++tries == 3)
			अवरोध;
		msleep(1);
	पूर्ण

	/* Spec states that TC cold निकास can take up to 1ms to complete */
	अगर (!ret)
		msleep(1);

	/* TODO: turn failure पूर्णांकo a error as soon i915 CI updates ICL IFWI */
	drm_dbg_kms(&i915->drm, "TC cold block %s\n", ret ? "failed" :
		    "succeeded");
पूर्ण

अटल व्योम
icl_tc_phy_aux_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा i915_घातer_well *घातer_well)
अणु
	क्रमागत aux_ch aux_ch = icl_tc_phy_aux_ch(dev_priv, घातer_well);
	काष्ठा पूर्णांकel_digital_port *dig_port = aux_ch_to_digital_port(dev_priv, aux_ch);
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	bool is_tbt = घातer_well->desc->hsw.is_tc_tbt;
	bool समयout_expected;
	u32 val;

	icl_tc_port_निश्चित_ref_held(dev_priv, घातer_well, dig_port);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DP_AUX_CH_CTL(aux_ch));
	val &= ~DP_AUX_CH_CTL_TBT_IO;
	अगर (is_tbt)
		val |= DP_AUX_CH_CTL_TBT_IO;
	पूर्णांकel_de_ग_लिखो(dev_priv, DP_AUX_CH_CTL(aux_ch), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs->driver,
		       val | HSW_PWR_WELL_CTL_REQ(घातer_well->desc->hsw.idx));

	/*
	 * An AUX समयout is expected अगर the TBT DP tunnel is करोwn,
	 * or need to enable AUX on a legacy TypeC port as part of the TC-cold
	 * निकास sequence.
	 */
	समयout_expected = is_tbt;
	अगर (IS_DISPLAY_VER(dev_priv, 11) && dig_port->tc_legacy_port) अणु
		icl_tc_cold_निकास(dev_priv);
		समयout_expected = true;
	पूर्ण

	hsw_रुको_क्रम_घातer_well_enable(dev_priv, घातer_well, समयout_expected);

	अगर (DISPLAY_VER(dev_priv) >= 12 && !is_tbt) अणु
		क्रमागत tc_port tc_port;

		tc_port = TGL_AUX_PW_TO_TC_PORT(घातer_well->desc->hsw.idx);
		पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
			       HIP_INDEX_VAL(tc_port, 0x2));

		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, DKL_CMN_UC_DW_27(tc_port),
					  DKL_CMN_UC_DW27_UC_HEALTH, 1))
			drm_warn(&dev_priv->drm,
				 "Timeout waiting TC uC health\n");
	पूर्ण
पूर्ण

अटल व्योम
icl_tc_phy_aux_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा i915_घातer_well *घातer_well)
अणु
	क्रमागत aux_ch aux_ch = icl_tc_phy_aux_ch(dev_priv, घातer_well);
	काष्ठा पूर्णांकel_digital_port *dig_port = aux_ch_to_digital_port(dev_priv, aux_ch);

	icl_tc_port_निश्चित_ref_held(dev_priv, घातer_well, dig_port);

	hsw_घातer_well_disable(dev_priv, घातer_well);
पूर्ण

अटल व्योम
icl_aux_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा i915_घातer_well *घातer_well)
अणु
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	क्रमागत phy phy = ICL_AUX_PW_TO_PHY(pw_idx);  /* non-TBT only */
	bool is_tbt = घातer_well->desc->hsw.is_tc_tbt;

	अगर (is_tbt || पूर्णांकel_phy_is_tc(dev_priv, phy))
		वापस icl_tc_phy_aux_घातer_well_enable(dev_priv, घातer_well);
	अन्यथा अगर (IS_ICELAKE(dev_priv))
		वापस icl_combo_phy_aux_घातer_well_enable(dev_priv,
							   घातer_well);
	अन्यथा
		वापस hsw_घातer_well_enable(dev_priv, घातer_well);
पूर्ण

अटल व्योम
icl_aux_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा i915_घातer_well *घातer_well)
अणु
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	क्रमागत phy phy = ICL_AUX_PW_TO_PHY(pw_idx);  /* non-TBT only */
	bool is_tbt = घातer_well->desc->hsw.is_tc_tbt;

	अगर (is_tbt || पूर्णांकel_phy_is_tc(dev_priv, phy))
		वापस icl_tc_phy_aux_घातer_well_disable(dev_priv, घातer_well);
	अन्यथा अगर (IS_ICELAKE(dev_priv))
		वापस icl_combo_phy_aux_घातer_well_disable(dev_priv,
							    घातer_well);
	अन्यथा
		वापस hsw_घातer_well_disable(dev_priv, घातer_well);
पूर्ण

/*
 * We should only use the घातer well अगर we explicitly asked the hardware to
 * enable it, so check अगर it's enabled and also check if we've requested it to
 * be enabled.
 */
अटल bool hsw_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	क्रमागत i915_घातer_well_id id = घातer_well->desc->id;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	u32 mask = HSW_PWR_WELL_CTL_REQ(pw_idx) |
		   HSW_PWR_WELL_CTL_STATE(pw_idx);
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);

	/*
	 * On GEN9 big core due to a DMC bug the driver's request bits क्रम PW1
	 * and the MISC_IO PW will be not restored, so check instead क्रम the
	 * BIOS's own request bits, which are क्रमced-on क्रम these घातer wells
	 * when निकासing DC5/6.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 9) && !IS_GEN9_LP(dev_priv) &&
	    (id == SKL_DISP_PW_1 || id == SKL_DISP_PW_MISC_IO))
		val |= पूर्णांकel_de_पढ़ो(dev_priv, regs->bios);

	वापस (val & mask) == mask;
पूर्ण

अटल व्योम निश्चित_can_enable_dc9(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_WARN_ONCE(&dev_priv->drm,
		      (पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) & DC_STATE_EN_DC9),
		      "DC9 already programmed to be enabled.\n");
	drm_WARN_ONCE(&dev_priv->drm,
		      पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) &
		      DC_STATE_EN_UPTO_DC5,
		      "DC5 still not disabled to enable DC9.\n");
	drm_WARN_ONCE(&dev_priv->drm,
		      पूर्णांकel_de_पढ़ो(dev_priv, HSW_PWR_WELL_CTL2) &
		      HSW_PWR_WELL_CTL_REQ(SKL_PW_CTL_IDX_PW_2),
		      "Power well 2 on.\n");
	drm_WARN_ONCE(&dev_priv->drm, पूर्णांकel_irqs_enabled(dev_priv),
		      "Interrupts not disabled yet.\n");

	 /*
	  * TODO: check क्रम the following to verअगरy the conditions to enter DC9
	  * state are satisfied:
	  * 1] Check relevant display engine रेजिस्टरs to verअगरy अगर mode set
	  * disable sequence was followed.
	  * 2] Check अगर display uninitialize sequence is initialized.
	  */
पूर्ण

अटल व्योम निश्चित_can_disable_dc9(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_WARN_ONCE(&dev_priv->drm, पूर्णांकel_irqs_enabled(dev_priv),
		      "Interrupts not disabled yet.\n");
	drm_WARN_ONCE(&dev_priv->drm,
		      पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) &
		      DC_STATE_EN_UPTO_DC5,
		      "DC5 still not disabled.\n");

	 /*
	  * TODO: check क्रम the following to verअगरy DC9 state was indeed
	  * entered beक्रमe programming to disable it:
	  * 1] Check relevant display engine रेजिस्टरs to verअगरy अगर mode
	  *  set disable sequence was followed.
	  * 2] Check अगर display uninitialize sequence is initialized.
	  */
पूर्ण

अटल व्योम gen9_ग_लिखो_dc_state(काष्ठा drm_i915_निजी *dev_priv,
				u32 state)
अणु
	पूर्णांक reग_लिखोs = 0;
	पूर्णांक reपढ़ोs = 0;
	u32 v;

	पूर्णांकel_de_ग_लिखो(dev_priv, DC_STATE_EN, state);

	/* It has been observed that disabling the dc6 state someबार
	 * करोesn't stick and dmc keeps वापसing old value. Make sure
	 * the ग_लिखो really sticks enough बार and also क्रमce reग_लिखो until
	 * we are confident that state is exactly what we want.
	 */
	करो  अणु
		v = पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN);

		अगर (v != state) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, DC_STATE_EN, state);
			reग_लिखोs++;
			reपढ़ोs = 0;
		पूर्ण अन्यथा अगर (reपढ़ोs++ > 5) अणु
			अवरोध;
		पूर्ण

	पूर्ण जबतक (reग_लिखोs < 100);

	अगर (v != state)
		drm_err(&dev_priv->drm,
			"Writing dc state to 0x%x failed, now 0x%x\n",
			state, v);

	/* Most of the बार we need one retry, aव्योम spam */
	अगर (reग_लिखोs > 1)
		drm_dbg_kms(&dev_priv->drm,
			    "Rewrote dc state to 0x%x %d times\n",
			    state, reग_लिखोs);
पूर्ण

अटल u32 gen9_dc_mask(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 mask;

	mask = DC_STATE_EN_UPTO_DC5;

	अगर (DISPLAY_VER(dev_priv) >= 12)
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC6
					  | DC_STATE_EN_DC9;
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11))
		mask |= DC_STATE_EN_UPTO_DC6 | DC_STATE_EN_DC9;
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		mask |= DC_STATE_EN_DC9;
	अन्यथा
		mask |= DC_STATE_EN_UPTO_DC6;

	वापस mask;
पूर्ण

अटल व्योम gen9_sanitize_dc_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) & gen9_dc_mask(dev_priv);

	drm_dbg_kms(&dev_priv->drm,
		    "Resetting DC state tracking from %02x to %02x\n",
		    dev_priv->csr.dc_state, val);
	dev_priv->csr.dc_state = val;
पूर्ण

/**
 * gen9_set_dc_state - set target display C घातer state
 * @dev_priv: i915 device instance
 * @state: target DC घातer state
 * - DC_STATE_DISABLE
 * - DC_STATE_EN_UPTO_DC5
 * - DC_STATE_EN_UPTO_DC6
 * - DC_STATE_EN_DC9
 *
 * Signal to DMC firmware/HW the target DC घातer state passed in @state.
 * DMC/HW can turn off inभागidual display घड़ीs and घातer rails when entering
 * a deeper DC घातer state (higher in number) and turns these back when निकासing
 * that state to a shallower घातer state (lower in number). The HW will decide
 * when to actually enter a given state on an on-demand basis, क्रम instance
 * depending on the active state of display pipes. The state of display
 * रेजिस्टरs backed by affected घातer rails are saved/restored as needed.
 *
 * Based on the above enabling a deeper DC घातer state is asynchronous wrt.
 * enabling it. Disabling a deeper घातer state is synchronous: क्रम instance
 * setting %DC_STATE_DISABLE won't complete until all HW resources are turned
 * back on and रेजिस्टर state is restored. This is guaranteed by the MMIO ग_लिखो
 * to DC_STATE_EN blocking until the state is restored.
 */
अटल व्योम gen9_set_dc_state(काष्ठा drm_i915_निजी *dev_priv, u32 state)
अणु
	u32 val;
	u32 mask;

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm,
			     state & ~dev_priv->csr.allowed_dc_mask))
		state &= dev_priv->csr.allowed_dc_mask;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN);
	mask = gen9_dc_mask(dev_priv);
	drm_dbg_kms(&dev_priv->drm, "Setting DC state from %02x to %02x\n",
		    val & mask, state);

	/* Check अगर DMC is ignoring our DC state requests */
	अगर ((val & mask) != dev_priv->csr.dc_state)
		drm_err(&dev_priv->drm, "DC state mismatch (0x%x -> 0x%x)\n",
			dev_priv->csr.dc_state, val & mask);

	val &= ~mask;
	val |= state;

	gen9_ग_लिखो_dc_state(dev_priv, val);

	dev_priv->csr.dc_state = val & mask;
पूर्ण

अटल u32
sanitize_target_dc_state(काष्ठा drm_i915_निजी *dev_priv,
			 u32 target_dc_state)
अणु
	u32 states[] = अणु
		DC_STATE_EN_UPTO_DC6,
		DC_STATE_EN_UPTO_DC5,
		DC_STATE_EN_DC3CO,
		DC_STATE_DISABLE,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(states) - 1; i++) अणु
		अगर (target_dc_state != states[i])
			जारी;

		अगर (dev_priv->csr.allowed_dc_mask & target_dc_state)
			अवरोध;

		target_dc_state = states[i + 1];
	पूर्ण

	वापस target_dc_state;
पूर्ण

अटल व्योम tgl_enable_dc3co(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_dbg_kms(&dev_priv->drm, "Enabling DC3CO\n");
	gen9_set_dc_state(dev_priv, DC_STATE_EN_DC3CO);
पूर्ण

अटल व्योम tgl_disable_dc3co(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "Disabling DC3CO\n");
	val = पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN);
	val &= ~DC_STATE_DC3CO_STATUS;
	पूर्णांकel_de_ग_लिखो(dev_priv, DC_STATE_EN, val);
	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);
	/*
	 * Delay of 200us DC3CO Exit समय B.Spec 49196
	 */
	usleep_range(200, 210);
पूर्ण

अटल व्योम bxt_enable_dc9(काष्ठा drm_i915_निजी *dev_priv)
अणु
	निश्चित_can_enable_dc9(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "Enabling DC9\n");
	/*
	 * Power sequencer reset is not needed on
	 * platक्रमms with South Display Engine on PCH,
	 * because PPS रेजिस्टरs are always on.
	 */
	अगर (!HAS_PCH_SPLIT(dev_priv))
		पूर्णांकel_pps_reset_all(dev_priv);
	gen9_set_dc_state(dev_priv, DC_STATE_EN_DC9);
पूर्ण

अटल व्योम bxt_disable_dc9(काष्ठा drm_i915_निजी *dev_priv)
अणु
	निश्चित_can_disable_dc9(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "Disabling DC9\n");

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	पूर्णांकel_pps_unlock_regs_wa(dev_priv);
पूर्ण

अटल व्योम निश्चित_csr_loaded(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_WARN_ONCE(&dev_priv->drm,
		      !पूर्णांकel_de_पढ़ो(dev_priv, CSR_PROGRAM(0)),
		      "CSR program storage start is NULL\n");
	drm_WARN_ONCE(&dev_priv->drm, !पूर्णांकel_de_पढ़ो(dev_priv, CSR_SSP_BASE),
		      "CSR SSP Base Not fine\n");
	drm_WARN_ONCE(&dev_priv->drm, !पूर्णांकel_de_पढ़ो(dev_priv, CSR_HTP_SKL),
		      "CSR HTP Not fine\n");
पूर्ण

अटल काष्ठा i915_घातer_well *
lookup_घातer_well(काष्ठा drm_i915_निजी *dev_priv,
		  क्रमागत i915_घातer_well_id घातer_well_id)
अणु
	काष्ठा i915_घातer_well *घातer_well;

	क्रम_each_घातer_well(dev_priv, घातer_well)
		अगर (घातer_well->desc->id == घातer_well_id)
			वापस घातer_well;

	/*
	 * It's not feasible to add error checking code to the callers since
	 * this condition really shouldn't happen and it doesn't even make sense
	 * to पात things like display initialization sequences. Just वापस
	 * the first घातer well and hope the WARN माला_लो reported so we can fix
	 * our driver.
	 */
	drm_WARN(&dev_priv->drm, 1,
		 "Power well %d not defined for this platform\n",
		 घातer_well_id);
	वापस &dev_priv->घातer_करोमुख्यs.घातer_wells[0];
पूर्ण

/**
 * पूर्णांकel_display_घातer_set_target_dc_state - Set target dc state.
 * @dev_priv: i915 device
 * @state: state which needs to be set as target_dc_state.
 *
 * This function set the "DC off" घातer well target_dc_state,
 * based upon this target_dc_stste, "DC off" घातer well will
 * enable desired DC state.
 */
व्योम पूर्णांकel_display_घातer_set_target_dc_state(काष्ठा drm_i915_निजी *dev_priv,
					     u32 state)
अणु
	काष्ठा i915_घातer_well *घातer_well;
	bool dc_off_enabled;
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;

	mutex_lock(&घातer_करोमुख्यs->lock);
	घातer_well = lookup_घातer_well(dev_priv, SKL_DISP_DC_OFF);

	अगर (drm_WARN_ON(&dev_priv->drm, !घातer_well))
		जाओ unlock;

	state = sanitize_target_dc_state(dev_priv, state);

	अगर (state == dev_priv->csr.target_dc_state)
		जाओ unlock;

	dc_off_enabled = घातer_well->desc->ops->is_enabled(dev_priv,
							   घातer_well);
	/*
	 * If DC off घातer well is disabled, need to enable and disable the
	 * DC off घातer well to effect target DC state.
	 */
	अगर (!dc_off_enabled)
		घातer_well->desc->ops->enable(dev_priv, घातer_well);

	dev_priv->csr.target_dc_state = state;

	अगर (!dc_off_enabled)
		घातer_well->desc->ops->disable(dev_priv, घातer_well);

unlock:
	mutex_unlock(&घातer_करोमुख्यs->lock);
पूर्ण

अटल व्योम निश्चित_can_enable_dc5(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत i915_घातer_well_id high_pg;

	/* Power wells at this level and above must be disabled क्रम DC5 entry */
	अगर (DISPLAY_VER(dev_priv) >= 12)
		high_pg = ICL_DISP_PW_3;
	अन्यथा
		high_pg = SKL_DISP_PW_2;

	drm_WARN_ONCE(&dev_priv->drm,
		      पूर्णांकel_display_घातer_well_is_enabled(dev_priv, high_pg),
		      "Power wells above platform's DC5 limit still enabled.\n");

	drm_WARN_ONCE(&dev_priv->drm,
		      (पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) &
		       DC_STATE_EN_UPTO_DC5),
		      "DC5 already programmed to be enabled.\n");
	निश्चित_rpm_wakelock_held(&dev_priv->runसमय_pm);

	निश्चित_csr_loaded(dev_priv);
पूर्ण

अटल व्योम gen9_enable_dc5(काष्ठा drm_i915_निजी *dev_priv)
अणु
	निश्चित_can_enable_dc5(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "Enabling DC5\n");

	/* Wa Display #1183: skl,kbl,cfl */
	अगर (IS_GEN9_BC(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, GEN8_CHICKEN_DCPR_1,
			       पूर्णांकel_de_पढ़ो(dev_priv, GEN8_CHICKEN_DCPR_1) | SKL_SELECT_ALTERNATE_DC_EXIT);

	gen9_set_dc_state(dev_priv, DC_STATE_EN_UPTO_DC5);
पूर्ण

अटल व्योम निश्चित_can_enable_dc6(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_WARN_ONCE(&dev_priv->drm,
		      पूर्णांकel_de_पढ़ो(dev_priv, UTIL_PIN_CTL) & UTIL_PIN_ENABLE,
		      "Backlight is not disabled.\n");
	drm_WARN_ONCE(&dev_priv->drm,
		      (पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) &
		       DC_STATE_EN_UPTO_DC6),
		      "DC6 already programmed to be enabled.\n");

	निश्चित_csr_loaded(dev_priv);
पूर्ण

अटल व्योम skl_enable_dc6(काष्ठा drm_i915_निजी *dev_priv)
अणु
	निश्चित_can_enable_dc6(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "Enabling DC6\n");

	/* Wa Display #1183: skl,kbl,cfl */
	अगर (IS_GEN9_BC(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, GEN8_CHICKEN_DCPR_1,
			       पूर्णांकel_de_पढ़ो(dev_priv, GEN8_CHICKEN_DCPR_1) | SKL_SELECT_ALTERNATE_DC_EXIT);

	gen9_set_dc_state(dev_priv, DC_STATE_EN_UPTO_DC6);
पूर्ण

अटल व्योम hsw_घातer_well_sync_hw(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	स्थिर काष्ठा i915_घातer_well_regs *regs = घातer_well->desc->hsw.regs;
	पूर्णांक pw_idx = घातer_well->desc->hsw.idx;
	u32 mask = HSW_PWR_WELL_CTL_REQ(pw_idx);
	u32 bios_req = पूर्णांकel_de_पढ़ो(dev_priv, regs->bios);

	/* Take over the request bit अगर set by BIOS. */
	अगर (bios_req & mask) अणु
		u32 drv_req = पूर्णांकel_de_पढ़ो(dev_priv, regs->driver);

		अगर (!(drv_req & mask))
			पूर्णांकel_de_ग_लिखो(dev_priv, regs->driver, drv_req | mask);
		पूर्णांकel_de_ग_लिखो(dev_priv, regs->bios, bios_req & ~mask);
	पूर्ण
पूर्ण

अटल व्योम bxt_dpio_cmn_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
	bxt_ddi_phy_init(dev_priv, घातer_well->desc->bxt.phy);
पूर्ण

अटल व्योम bxt_dpio_cmn_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					    काष्ठा i915_घातer_well *घातer_well)
अणु
	bxt_ddi_phy_uninit(dev_priv, घातer_well->desc->bxt.phy);
पूर्ण

अटल bool bxt_dpio_cmn_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
					    काष्ठा i915_घातer_well *घातer_well)
अणु
	वापस bxt_ddi_phy_is_enabled(dev_priv, घातer_well->desc->bxt.phy);
पूर्ण

अटल व्योम bxt_verअगरy_ddi_phy_घातer_wells(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_well *घातer_well;

	घातer_well = lookup_घातer_well(dev_priv, BXT_DISP_PW_DPIO_CMN_A);
	अगर (घातer_well->count > 0)
		bxt_ddi_phy_verअगरy_state(dev_priv, घातer_well->desc->bxt.phy);

	घातer_well = lookup_घातer_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	अगर (घातer_well->count > 0)
		bxt_ddi_phy_verअगरy_state(dev_priv, घातer_well->desc->bxt.phy);

	अगर (IS_GEMINILAKE(dev_priv)) अणु
		घातer_well = lookup_घातer_well(dev_priv,
					       GLK_DISP_PW_DPIO_CMN_C);
		अगर (घातer_well->count > 0)
			bxt_ddi_phy_verअगरy_state(dev_priv,
						 घातer_well->desc->bxt.phy);
	पूर्ण
पूर्ण

अटल bool gen9_dc_off_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
	वापस ((पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) & DC_STATE_EN_DC3CO) == 0 &&
		(पूर्णांकel_de_पढ़ो(dev_priv, DC_STATE_EN) & DC_STATE_EN_UPTO_DC5_DC6_MASK) == 0);
पूर्ण

अटल व्योम gen9_निश्चित_dbuf_enabled(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u8 hw_enabled_dbuf_slices = पूर्णांकel_enabled_dbuf_slices_mask(dev_priv);
	u8 enabled_dbuf_slices = dev_priv->dbuf.enabled_slices;

	drm_WARN(&dev_priv->drm,
		 hw_enabled_dbuf_slices != enabled_dbuf_slices,
		 "Unexpected DBuf power power state (0x%08x, expected 0x%08x)\n",
		 hw_enabled_dbuf_slices,
		 enabled_dbuf_slices);
पूर्ण

अटल व्योम gen9_disable_dc_states(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_cdclk_config cdclk_config = अणुपूर्ण;

	अगर (dev_priv->csr.target_dc_state == DC_STATE_EN_DC3CO) अणु
		tgl_disable_dc3co(dev_priv);
		वापस;
	पूर्ण

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	dev_priv->display.get_cdclk(dev_priv, &cdclk_config);
	/* Can't read out voltage_level so can't use पूर्णांकel_cdclk_changed() */
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_cdclk_needs_modeset(&dev_priv->cdclk.hw,
					      &cdclk_config));

	gen9_निश्चित_dbuf_enabled(dev_priv);

	अगर (IS_GEN9_LP(dev_priv))
		bxt_verअगरy_ddi_phy_घातer_wells(dev_priv);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		/*
		 * DMC retains HW context only क्रम port A, the other combo
		 * PHY's HW context क्रम port B is lost after DC transitions,
		 * so we need to restore it manually.
		 */
		पूर्णांकel_combo_phy_init(dev_priv);
पूर्ण

अटल व्योम gen9_dc_off_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					  काष्ठा i915_घातer_well *घातer_well)
अणु
	gen9_disable_dc_states(dev_priv);
पूर्ण

अटल व्योम gen9_dc_off_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
	अगर (!dev_priv->csr.dmc_payload)
		वापस;

	चयन (dev_priv->csr.target_dc_state) अणु
	हाल DC_STATE_EN_DC3CO:
		tgl_enable_dc3co(dev_priv);
		अवरोध;
	हाल DC_STATE_EN_UPTO_DC6:
		skl_enable_dc6(dev_priv);
		अवरोध;
	हाल DC_STATE_EN_UPTO_DC5:
		gen9_enable_dc5(dev_priv);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम i9xx_घातer_well_sync_hw_noop(काष्ठा drm_i915_निजी *dev_priv,
					 काष्ठा i915_घातer_well *घातer_well)
अणु
पूर्ण

अटल व्योम i9xx_always_on_घातer_well_noop(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
पूर्ण

अटल bool i9xx_always_on_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
					     काष्ठा i915_घातer_well *घातer_well)
अणु
	वापस true;
पूर्ण

अटल व्योम i830_pipes_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					 काष्ठा i915_घातer_well *घातer_well)
अणु
	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(PIPE_A)) & PIPECONF_ENABLE) == 0)
		i830_enable_pipe(dev_priv, PIPE_A);
	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(PIPE_B)) & PIPECONF_ENABLE) == 0)
		i830_enable_pipe(dev_priv, PIPE_B);
पूर्ण

अटल व्योम i830_pipes_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					  काष्ठा i915_घातer_well *घातer_well)
अणु
	i830_disable_pipe(dev_priv, PIPE_B);
	i830_disable_pipe(dev_priv, PIPE_A);
पूर्ण

अटल bool i830_pipes_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
					  काष्ठा i915_घातer_well *घातer_well)
अणु
	वापस पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(PIPE_A)) & PIPECONF_ENABLE &&
		पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(PIPE_B)) & PIPECONF_ENABLE;
पूर्ण

अटल व्योम i830_pipes_घातer_well_sync_hw(काष्ठा drm_i915_निजी *dev_priv,
					  काष्ठा i915_घातer_well *घातer_well)
अणु
	अगर (घातer_well->count > 0)
		i830_pipes_घातer_well_enable(dev_priv, घातer_well);
	अन्यथा
		i830_pipes_घातer_well_disable(dev_priv, घातer_well);
पूर्ण

अटल व्योम vlv_set_घातer_well(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा i915_घातer_well *घातer_well, bool enable)
अणु
	पूर्णांक pw_idx = घातer_well->desc->vlv.idx;
	u32 mask;
	u32 state;
	u32 ctrl;

	mask = PUNIT_PWRGT_MASK(pw_idx);
	state = enable ? PUNIT_PWRGT_PWR_ON(pw_idx) :
			 PUNIT_PWRGT_PWR_GATE(pw_idx);

	vlv_punit_get(dev_priv);

#घोषणा COND \
	((vlv_punit_पढ़ो(dev_priv, PUNIT_REG_PWRGT_STATUS) & mask) == state)

	अगर (COND)
		जाओ out;

	ctrl = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_PWRGT_CTRL);
	ctrl &= ~mask;
	ctrl |= state;
	vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_PWRGT_CTRL, ctrl);

	अगर (रुको_क्रम(COND, 100))
		drm_err(&dev_priv->drm,
			"timeout setting power well state %08x (%08x)\n",
			state,
			vlv_punit_पढ़ो(dev_priv, PUNIT_REG_PWRGT_CTRL));

#अघोषित COND

out:
	vlv_punit_put(dev_priv);
पूर्ण

अटल व्योम vlv_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा i915_घातer_well *घातer_well)
अणु
	vlv_set_घातer_well(dev_priv, घातer_well, true);
पूर्ण

अटल व्योम vlv_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	vlv_set_घातer_well(dev_priv, घातer_well, false);
पूर्ण

अटल bool vlv_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	पूर्णांक pw_idx = घातer_well->desc->vlv.idx;
	bool enabled = false;
	u32 mask;
	u32 state;
	u32 ctrl;

	mask = PUNIT_PWRGT_MASK(pw_idx);
	ctrl = PUNIT_PWRGT_PWR_ON(pw_idx);

	vlv_punit_get(dev_priv);

	state = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_PWRGT_STATUS) & mask;
	/*
	 * We only ever set the घातer-on and घातer-gate states, anything
	 * अन्यथा is unexpected.
	 */
	drm_WARN_ON(&dev_priv->drm, state != PUNIT_PWRGT_PWR_ON(pw_idx) &&
		    state != PUNIT_PWRGT_PWR_GATE(pw_idx));
	अगर (state == ctrl)
		enabled = true;

	/*
	 * A transient state at this poपूर्णांक would mean some unexpected party
	 * is poking at the घातer controls too.
	 */
	ctrl = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_PWRGT_CTRL) & mask;
	drm_WARN_ON(&dev_priv->drm, ctrl != state);

	vlv_punit_put(dev_priv);

	वापस enabled;
पूर्ण

अटल व्योम vlv_init_display_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	/*
	 * On driver load, a pipe may be active and driving a DSI display.
	 * Preserve DPOUNIT_CLOCK_GATE_DISABLE to aव्योम the pipe getting stuck
	 * (and never recovering) in this हाल. पूर्णांकel_dsi_post_disable() will
	 * clear it when we turn off the display.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, DSPCLK_GATE_D);
	val &= DPOUNIT_CLOCK_GATE_DISABLE;
	val |= VRHUNIT_CLOCK_GATE_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, DSPCLK_GATE_D, val);

	/*
	 * Disable trickle feed and enable pnd deadline calculation
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, MI_ARB_VLV,
		       MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE);
	पूर्णांकel_de_ग_लिखो(dev_priv, CBR1_VLV, 0);

	drm_WARN_ON(&dev_priv->drm, RUNTIME_INFO(dev_priv)->rawclk_freq == 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, RAWCLK_FREQ_VLV,
		       DIV_ROUND_CLOSEST(RUNTIME_INFO(dev_priv)->rawclk_freq,
					 1000));
पूर्ण

अटल व्योम vlv_display_घातer_well_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	क्रमागत pipe pipe;

	/*
	 * Enable the CRI घड़ी source so we can get at the
	 * display and the reference घड़ी क्रम VGA
	 * hotplug / manual detection. Supposedly DSI also
	 * needs the ref घड़ी up and running.
	 *
	 * CHV DPLL B/C have some issues अगर VGA mode is enabled.
	 */
	क्रम_each_pipe(dev_priv, pipe) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL(pipe));

		val |= DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
		अगर (pipe != PIPE_A)
			val |= DPLL_INTEGRATED_CRI_CLK_VLV;

		पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), val);
	पूर्ण

	vlv_init_display_घड़ी_gating(dev_priv);

	spin_lock_irq(&dev_priv->irq_lock);
	valleyview_enable_display_irqs(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	/*
	 * During driver initialization/resume we can aव्योम restoring the
	 * part of the HW/SW state that will be inited anyway explicitly.
	 */
	अगर (dev_priv->घातer_करोमुख्यs.initializing)
		वापस;

	पूर्णांकel_hpd_init(dev_priv);
	पूर्णांकel_hpd_poll_disable(dev_priv);

	/* Re-enable the ADPA, अगर we have one */
	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		अगर (encoder->type == INTEL_OUTPUT_ANALOG)
			पूर्णांकel_crt_reset(&encoder->base);
	पूर्ण

	पूर्णांकel_vga_redisable_घातer_on(dev_priv);

	पूर्णांकel_pps_unlock_regs_wa(dev_priv);
पूर्ण

अटल व्योम vlv_display_घातer_well_deinit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	spin_lock_irq(&dev_priv->irq_lock);
	valleyview_disable_display_irqs(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	/* make sure we're करोne processing display irqs */
	पूर्णांकel_synchronize_irq(dev_priv);

	पूर्णांकel_pps_reset_all(dev_priv);

	/* Prevent us from re-enabling polling on accident in late suspend */
	अगर (!dev_priv->drm.dev->घातer.is_suspended)
		पूर्णांकel_hpd_poll_enable(dev_priv);
पूर्ण

अटल व्योम vlv_display_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					  काष्ठा i915_घातer_well *घातer_well)
अणु
	vlv_set_घातer_well(dev_priv, घातer_well, true);

	vlv_display_घातer_well_init(dev_priv);
पूर्ण

अटल व्योम vlv_display_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
	vlv_display_घातer_well_deinit(dev_priv);

	vlv_set_घातer_well(dev_priv, घातer_well, false);
पूर्ण

अटल व्योम vlv_dpio_cmn_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
	/* since ref/cri घड़ी was enabled */
	udelay(1); /* >10ns क्रम cmnreset, >0ns क्रम sidereset */

	vlv_set_घातer_well(dev_priv, घातer_well, true);

	/*
	 * From VLV2A0_DP_eDP_DPIO_driver_vbios_notes_10.करोcx -
	 *  6.	De-निश्चित cmn_reset/side_reset. Same as VLV X0.
	 *   a.	GUnit 0x2110 bit[0] set to 1 (def 0)
	 *   b.	The other bits such as sfr settings / modesel may all
	 *	be set to 0.
	 *
	 * This should only be करोne on init and resume from S3 with
	 * both PLLs disabled, or we risk losing DPIO and PLL
	 * synchronization.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPIO_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, DPIO_CTL) | DPIO_CMNRST);
पूर्ण

अटल व्योम vlv_dpio_cmn_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					    काष्ठा i915_घातer_well *घातer_well)
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe)
		निश्चित_pll_disabled(dev_priv, pipe);

	/* Assert common reset */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPIO_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, DPIO_CTL) & ~DPIO_CMNRST);

	vlv_set_घातer_well(dev_priv, घातer_well, false);
पूर्ण

#घोषणा POWER_DOMAIN_MASK (GENMASK_ULL(POWER_DOMAIN_NUM - 1, 0))

#घोषणा BITS_SET(val, bits) (((val) & (bits)) == (bits))

अटल व्योम निश्चित_chv_phy_status(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_well *cmn_bc =
		lookup_घातer_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	काष्ठा i915_घातer_well *cmn_d =
		lookup_घातer_well(dev_priv, CHV_DISP_PW_DPIO_CMN_D);
	u32 phy_control = dev_priv->chv_phy_control;
	u32 phy_status = 0;
	u32 phy_status_mask = 0xffffffff;

	/*
	 * The BIOS can leave the PHY is some weird state
	 * where it करोesn't fully घातer करोwn some parts.
	 * Disable the निश्चितs until the PHY has been fully
	 * reset (ie. the घातer well has been disabled at
	 * least once).
	 */
	अगर (!dev_priv->chv_phy_निश्चित[DPIO_PHY0])
		phy_status_mask &= ~(PHY_STATUS_CMN_LDO(DPIO_PHY0, DPIO_CH0) |
				     PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH0, 0) |
				     PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH0, 1) |
				     PHY_STATUS_CMN_LDO(DPIO_PHY0, DPIO_CH1) |
				     PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH1, 0) |
				     PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH1, 1));

	अगर (!dev_priv->chv_phy_निश्चित[DPIO_PHY1])
		phy_status_mask &= ~(PHY_STATUS_CMN_LDO(DPIO_PHY1, DPIO_CH0) |
				     PHY_STATUS_SPLINE_LDO(DPIO_PHY1, DPIO_CH0, 0) |
				     PHY_STATUS_SPLINE_LDO(DPIO_PHY1, DPIO_CH0, 1));

	अगर (cmn_bc->desc->ops->is_enabled(dev_priv, cmn_bc)) अणु
		phy_status |= PHY_POWERGOOD(DPIO_PHY0);

		/* this assumes override is only used to enable lanes */
		अगर ((phy_control & PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH0)) == 0)
			phy_control |= PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY0, DPIO_CH0);

		अगर ((phy_control & PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH1)) == 0)
			phy_control |= PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY0, DPIO_CH1);

		/* CL1 is on whenever anything is on in either channel */
		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY0, DPIO_CH0) |
			     PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY0, DPIO_CH1)))
			phy_status |= PHY_STATUS_CMN_LDO(DPIO_PHY0, DPIO_CH0);

		/*
		 * The DPLLB check accounts क्रम the pipe B + port A usage
		 * with CL2 घातered up but all the lanes in the second channel
		 * घातered करोwn.
		 */
		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY0, DPIO_CH1)) &&
		    (पूर्णांकel_de_पढ़ो(dev_priv, DPLL(PIPE_B)) & DPLL_VCO_ENABLE) == 0)
			phy_status |= PHY_STATUS_CMN_LDO(DPIO_PHY0, DPIO_CH1);

		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0x3, DPIO_PHY0, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH0, 0);
		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0xc, DPIO_PHY0, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH0, 1);

		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0x3, DPIO_PHY0, DPIO_CH1)))
			phy_status |= PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH1, 0);
		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0xc, DPIO_PHY0, DPIO_CH1)))
			phy_status |= PHY_STATUS_SPLINE_LDO(DPIO_PHY0, DPIO_CH1, 1);
	पूर्ण

	अगर (cmn_d->desc->ops->is_enabled(dev_priv, cmn_d)) अणु
		phy_status |= PHY_POWERGOOD(DPIO_PHY1);

		/* this assumes override is only used to enable lanes */
		अगर ((phy_control & PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY1, DPIO_CH0)) == 0)
			phy_control |= PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY1, DPIO_CH0);

		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0xf, DPIO_PHY1, DPIO_CH0)))
			phy_status |= PHY_STATUS_CMN_LDO(DPIO_PHY1, DPIO_CH0);

		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0x3, DPIO_PHY1, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPLINE_LDO(DPIO_PHY1, DPIO_CH0, 0);
		अगर (BITS_SET(phy_control,
			     PHY_CH_POWER_DOWN_OVRD(0xc, DPIO_PHY1, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPLINE_LDO(DPIO_PHY1, DPIO_CH0, 1);
	पूर्ण

	phy_status &= phy_status_mask;

	/*
	 * The PHY may be busy with some initial calibration and whatnot,
	 * so the घातer state can take a जबतक to actually change.
	 */
	अगर (पूर्णांकel_de_रुको_क्रम_रेजिस्टर(dev_priv, DISPLAY_PHY_STATUS,
				       phy_status_mask, phy_status, 10))
		drm_err(&dev_priv->drm,
			"Unexpected PHY_STATUS 0x%08x, expected 0x%08x (PHY_CONTROL=0x%08x)\n",
			पूर्णांकel_de_पढ़ो(dev_priv, DISPLAY_PHY_STATUS) & phy_status_mask,
			phy_status, dev_priv->chv_phy_control);
पूर्ण

#अघोषित BITS_SET

अटल व्योम chv_dpio_cmn_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
					   काष्ठा i915_घातer_well *घातer_well)
अणु
	क्रमागत dpio_phy phy;
	क्रमागत pipe pipe;
	u32 पंचांगp;

	drm_WARN_ON_ONCE(&dev_priv->drm,
			 घातer_well->desc->id != VLV_DISP_PW_DPIO_CMN_BC &&
			 घातer_well->desc->id != CHV_DISP_PW_DPIO_CMN_D);

	अगर (घातer_well->desc->id == VLV_DISP_PW_DPIO_CMN_BC) अणु
		pipe = PIPE_A;
		phy = DPIO_PHY0;
	पूर्ण अन्यथा अणु
		pipe = PIPE_C;
		phy = DPIO_PHY1;
	पूर्ण

	/* since ref/cri घड़ी was enabled */
	udelay(1); /* >10ns क्रम cmnreset, >0ns क्रम sidereset */
	vlv_set_घातer_well(dev_priv, घातer_well, true);

	/* Poll क्रम phypwrgood संकेत */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, DISPLAY_PHY_STATUS,
				  PHY_POWERGOOD(phy), 1))
		drm_err(&dev_priv->drm, "Display PHY %d is not power up\n",
			phy);

	vlv_dpio_get(dev_priv);

	/* Enable dynamic घातer करोwn */
	पंचांगp = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW28);
	पंचांगp |= DPIO_DYNPWRDOWNEN_CH0 | DPIO_CL1POWERDOWNEN |
		DPIO_SUS_CLK_CONFIG_GATE_CLKREQ;
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW28, पंचांगp);

	अगर (घातer_well->desc->id == VLV_DISP_PW_DPIO_CMN_BC) अणु
		पंचांगp = vlv_dpio_पढ़ो(dev_priv, pipe, _CHV_CMN_DW6_CH1);
		पंचांगp |= DPIO_DYNPWRDOWNEN_CH1;
		vlv_dpio_ग_लिखो(dev_priv, pipe, _CHV_CMN_DW6_CH1, पंचांगp);
	पूर्ण अन्यथा अणु
		/*
		 * Force the non-existing CL2 off. BXT करोes this
		 * too, so maybe it saves some घातer even though
		 * CL2 करोesn't exist?
		 */
		पंचांगp = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW30);
		पंचांगp |= DPIO_CL2_LDOFUSE_PWRENB;
		vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW30, पंचांगp);
	पूर्ण

	vlv_dpio_put(dev_priv);

	dev_priv->chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(phy);
	पूर्णांकel_de_ग_लिखो(dev_priv, DISPLAY_PHY_CONTROL,
		       dev_priv->chv_phy_control);

	drm_dbg_kms(&dev_priv->drm,
		    "Enabled DPIO PHY%d (PHY_CONTROL=0x%08x)\n",
		    phy, dev_priv->chv_phy_control);

	निश्चित_chv_phy_status(dev_priv);
पूर्ण

अटल व्योम chv_dpio_cmn_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					    काष्ठा i915_घातer_well *घातer_well)
अणु
	क्रमागत dpio_phy phy;

	drm_WARN_ON_ONCE(&dev_priv->drm,
			 घातer_well->desc->id != VLV_DISP_PW_DPIO_CMN_BC &&
			 घातer_well->desc->id != CHV_DISP_PW_DPIO_CMN_D);

	अगर (घातer_well->desc->id == VLV_DISP_PW_DPIO_CMN_BC) अणु
		phy = DPIO_PHY0;
		निश्चित_pll_disabled(dev_priv, PIPE_A);
		निश्चित_pll_disabled(dev_priv, PIPE_B);
	पूर्ण अन्यथा अणु
		phy = DPIO_PHY1;
		निश्चित_pll_disabled(dev_priv, PIPE_C);
	पूर्ण

	dev_priv->chv_phy_control &= ~PHY_COM_LANE_RESET_DEASSERT(phy);
	पूर्णांकel_de_ग_लिखो(dev_priv, DISPLAY_PHY_CONTROL,
		       dev_priv->chv_phy_control);

	vlv_set_घातer_well(dev_priv, घातer_well, false);

	drm_dbg_kms(&dev_priv->drm,
		    "Disabled DPIO PHY%d (PHY_CONTROL=0x%08x)\n",
		    phy, dev_priv->chv_phy_control);

	/* PHY is fully reset now, so we can enable the PHY state निश्चितs */
	dev_priv->chv_phy_निश्चित[phy] = true;

	निश्चित_chv_phy_status(dev_priv);
पूर्ण

अटल व्योम निश्चित_chv_phy_घातergate(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy,
				     क्रमागत dpio_channel ch, bool override, अचिन्हित पूर्णांक mask)
अणु
	क्रमागत pipe pipe = phy == DPIO_PHY0 ? PIPE_A : PIPE_C;
	u32 reg, val, expected, actual;

	/*
	 * The BIOS can leave the PHY is some weird state
	 * where it करोesn't fully घातer करोwn some parts.
	 * Disable the निश्चितs until the PHY has been fully
	 * reset (ie. the घातer well has been disabled at
	 * least once).
	 */
	अगर (!dev_priv->chv_phy_निश्चित[phy])
		वापस;

	अगर (ch == DPIO_CH0)
		reg = _CHV_CMN_DW0_CH0;
	अन्यथा
		reg = _CHV_CMN_DW6_CH1;

	vlv_dpio_get(dev_priv);
	val = vlv_dpio_पढ़ो(dev_priv, pipe, reg);
	vlv_dpio_put(dev_priv);

	/*
	 * This assumes !override is only used when the port is disabled.
	 * All lanes should घातer करोwn even without the override when
	 * the port is disabled.
	 */
	अगर (!override || mask == 0xf) अणु
		expected = DPIO_ALLDL_POWERDOWN | DPIO_ANYDL_POWERDOWN;
		/*
		 * If CH1 common lane is not active anymore
		 * (eg. क्रम pipe B DPLL) the entire channel will
		 * shut करोwn, which causes the common lane रेजिस्टरs
		 * to पढ़ो as 0. That means we can't actually check
		 * the lane घातer करोwn status bits, but as the entire
		 * रेजिस्टर पढ़ोs as 0 it's a good indication that the
		 * channel is indeed entirely घातered करोwn.
		 */
		अगर (ch == DPIO_CH1 && val == 0)
			expected = 0;
	पूर्ण अन्यथा अगर (mask != 0x0) अणु
		expected = DPIO_ANYDL_POWERDOWN;
	पूर्ण अन्यथा अणु
		expected = 0;
	पूर्ण

	अगर (ch == DPIO_CH0)
		actual = val >> DPIO_ANYDL_POWERDOWN_SHIFT_CH0;
	अन्यथा
		actual = val >> DPIO_ANYDL_POWERDOWN_SHIFT_CH1;
	actual &= DPIO_ALLDL_POWERDOWN | DPIO_ANYDL_POWERDOWN;

	drm_WARN(&dev_priv->drm, actual != expected,
		 "Unexpected DPIO lane power down: all %d, any %d. Expected: all %d, any %d. (0x%x = 0x%08x)\n",
		 !!(actual & DPIO_ALLDL_POWERDOWN),
		 !!(actual & DPIO_ANYDL_POWERDOWN),
		 !!(expected & DPIO_ALLDL_POWERDOWN),
		 !!(expected & DPIO_ANYDL_POWERDOWN),
		 reg, val);
पूर्ण

bool chv_phy_घातergate_ch(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy,
			  क्रमागत dpio_channel ch, bool override)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	bool was_override;

	mutex_lock(&घातer_करोमुख्यs->lock);

	was_override = dev_priv->chv_phy_control & PHY_CH_POWER_DOWN_OVRD_EN(phy, ch);

	अगर (override == was_override)
		जाओ out;

	अगर (override)
		dev_priv->chv_phy_control |= PHY_CH_POWER_DOWN_OVRD_EN(phy, ch);
	अन्यथा
		dev_priv->chv_phy_control &= ~PHY_CH_POWER_DOWN_OVRD_EN(phy, ch);

	पूर्णांकel_de_ग_लिखो(dev_priv, DISPLAY_PHY_CONTROL,
		       dev_priv->chv_phy_control);

	drm_dbg_kms(&dev_priv->drm,
		    "Power gating DPIO PHY%d CH%d (DPIO_PHY_CONTROL=0x%08x)\n",
		    phy, ch, dev_priv->chv_phy_control);

	निश्चित_chv_phy_status(dev_priv);

out:
	mutex_unlock(&घातer_करोमुख्यs->lock);

	वापस was_override;
पूर्ण

व्योम chv_phy_घातergate_lanes(काष्ठा पूर्णांकel_encoder *encoder,
			     bool override, अचिन्हित पूर्णांक mask)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	क्रमागत dpio_phy phy = vlv_dig_port_to_phy(enc_to_dig_port(encoder));
	क्रमागत dpio_channel ch = vlv_dig_port_to_channel(enc_to_dig_port(encoder));

	mutex_lock(&घातer_करोमुख्यs->lock);

	dev_priv->chv_phy_control &= ~PHY_CH_POWER_DOWN_OVRD(0xf, phy, ch);
	dev_priv->chv_phy_control |= PHY_CH_POWER_DOWN_OVRD(mask, phy, ch);

	अगर (override)
		dev_priv->chv_phy_control |= PHY_CH_POWER_DOWN_OVRD_EN(phy, ch);
	अन्यथा
		dev_priv->chv_phy_control &= ~PHY_CH_POWER_DOWN_OVRD_EN(phy, ch);

	पूर्णांकel_de_ग_लिखो(dev_priv, DISPLAY_PHY_CONTROL,
		       dev_priv->chv_phy_control);

	drm_dbg_kms(&dev_priv->drm,
		    "Power gating DPIO PHY%d CH%d lanes 0x%x (PHY_CONTROL=0x%08x)\n",
		    phy, ch, mask, dev_priv->chv_phy_control);

	निश्चित_chv_phy_status(dev_priv);

	निश्चित_chv_phy_घातergate(dev_priv, phy, ch, override, mask);

	mutex_unlock(&घातer_करोमुख्यs->lock);
पूर्ण

अटल bool chv_pipe_घातer_well_enabled(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा i915_घातer_well *घातer_well)
अणु
	क्रमागत pipe pipe = PIPE_A;
	bool enabled;
	u32 state, ctrl;

	vlv_punit_get(dev_priv);

	state = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM) & DP_SSS_MASK(pipe);
	/*
	 * We only ever set the घातer-on and घातer-gate states, anything
	 * अन्यथा is unexpected.
	 */
	drm_WARN_ON(&dev_priv->drm, state != DP_SSS_PWR_ON(pipe) &&
		    state != DP_SSS_PWR_GATE(pipe));
	enabled = state == DP_SSS_PWR_ON(pipe);

	/*
	 * A transient state at this poपूर्णांक would mean some unexpected party
	 * is poking at the घातer controls too.
	 */
	ctrl = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM) & DP_SSC_MASK(pipe);
	drm_WARN_ON(&dev_priv->drm, ctrl << 16 != state);

	vlv_punit_put(dev_priv);

	वापस enabled;
पूर्ण

अटल व्योम chv_set_pipe_घातer_well(काष्ठा drm_i915_निजी *dev_priv,
				    काष्ठा i915_घातer_well *घातer_well,
				    bool enable)
अणु
	क्रमागत pipe pipe = PIPE_A;
	u32 state;
	u32 ctrl;

	state = enable ? DP_SSS_PWR_ON(pipe) : DP_SSS_PWR_GATE(pipe);

	vlv_punit_get(dev_priv);

#घोषणा COND \
	((vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM) & DP_SSS_MASK(pipe)) == state)

	अगर (COND)
		जाओ out;

	ctrl = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM);
	ctrl &= ~DP_SSC_MASK(pipe);
	ctrl |= enable ? DP_SSC_PWR_ON(pipe) : DP_SSC_PWR_GATE(pipe);
	vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_DSPSSPM, ctrl);

	अगर (रुको_क्रम(COND, 100))
		drm_err(&dev_priv->drm,
			"timeout setting power well state %08x (%08x)\n",
			state,
			vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM));

#अघोषित COND

out:
	vlv_punit_put(dev_priv);
पूर्ण

अटल व्योम chv_pipe_घातer_well_sync_hw(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा i915_घातer_well *घातer_well)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, DISPLAY_PHY_CONTROL,
		       dev_priv->chv_phy_control);
पूर्ण

अटल व्योम chv_pipe_घातer_well_enable(काष्ठा drm_i915_निजी *dev_priv,
				       काष्ठा i915_घातer_well *घातer_well)
अणु
	chv_set_pipe_घातer_well(dev_priv, घातer_well, true);

	vlv_display_घातer_well_init(dev_priv);
पूर्ण

अटल व्योम chv_pipe_घातer_well_disable(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा i915_घातer_well *घातer_well)
अणु
	vlv_display_घातer_well_deinit(dev_priv);

	chv_set_pipe_घातer_well(dev_priv, घातer_well, false);
पूर्ण

अटल u64 __async_put_करोमुख्यs_mask(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
	वापस घातer_करोमुख्यs->async_put_करोमुख्यs[0] |
	       घातer_करोमुख्यs->async_put_करोमुख्यs[1];
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)

अटल bool
निश्चित_async_put_करोमुख्य_masks_disjoपूर्णांक(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(घातer_करोमुख्यs,
						     काष्ठा drm_i915_निजी,
						     घातer_करोमुख्यs);
	वापस !drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->async_put_करोमुख्यs[0] &
			    घातer_करोमुख्यs->async_put_करोमुख्यs[1]);
पूर्ण

अटल bool
__async_put_करोमुख्यs_state_ok(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(घातer_करोमुख्यs,
						     काष्ठा drm_i915_निजी,
						     घातer_करोमुख्यs);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;
	bool err = false;

	err |= !निश्चित_async_put_करोमुख्य_masks_disjoपूर्णांक(घातer_करोमुख्यs);
	err |= drm_WARN_ON(&i915->drm, !!घातer_करोमुख्यs->async_put_wakeref !=
			   !!__async_put_करोमुख्यs_mask(घातer_करोमुख्यs));

	क्रम_each_घातer_करोमुख्य(करोमुख्य, __async_put_करोमुख्यs_mask(घातer_करोमुख्यs))
		err |= drm_WARN_ON(&i915->drm,
				   घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य] != 1);

	वापस !err;
पूर्ण

अटल व्योम prपूर्णांक_घातer_करोमुख्यs(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs,
				स्थिर अक्षर *prefix, u64 mask)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(घातer_करोमुख्यs,
						     काष्ठा drm_i915_निजी,
						     घातer_करोमुख्यs);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

	drm_dbg(&i915->drm, "%s (%lu):\n", prefix, hweight64(mask));
	क्रम_each_घातer_करोमुख्य(करोमुख्य, mask)
		drm_dbg(&i915->drm, "%s use_count %d\n",
			पूर्णांकel_display_घातer_करोमुख्य_str(करोमुख्य),
			घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य]);
पूर्ण

अटल व्योम
prपूर्णांक_async_put_करोमुख्यs_state(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(घातer_करोमुख्यs,
						     काष्ठा drm_i915_निजी,
						     घातer_करोमुख्यs);

	drm_dbg(&i915->drm, "async_put_wakeref %u\n",
		घातer_करोमुख्यs->async_put_wakeref);

	prपूर्णांक_घातer_करोमुख्यs(घातer_करोमुख्यs, "async_put_domains[0]",
			    घातer_करोमुख्यs->async_put_करोमुख्यs[0]);
	prपूर्णांक_घातer_करोमुख्यs(घातer_करोमुख्यs, "async_put_domains[1]",
			    घातer_करोमुख्यs->async_put_करोमुख्यs[1]);
पूर्ण

अटल व्योम
verअगरy_async_put_करोमुख्यs_state(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
	अगर (!__async_put_करोमुख्यs_state_ok(घातer_करोमुख्यs))
		prपूर्णांक_async_put_करोमुख्यs_state(घातer_करोमुख्यs);
पूर्ण

#अन्यथा

अटल व्योम
निश्चित_async_put_करोमुख्य_masks_disjoपूर्णांक(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
पूर्ण

अटल व्योम
verअगरy_async_put_करोमुख्यs_state(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_DRM_I915_DEBUG_RUNTIME_PM */

अटल u64 async_put_करोमुख्यs_mask(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs)
अणु
	निश्चित_async_put_करोमुख्य_masks_disjoपूर्णांक(घातer_करोमुख्यs);

	वापस __async_put_करोमुख्यs_mask(घातer_करोमुख्यs);
पूर्ण

अटल व्योम
async_put_करोमुख्यs_clear_करोमुख्य(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs,
			       क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	निश्चित_async_put_करोमुख्य_masks_disjoपूर्णांक(घातer_करोमुख्यs);

	घातer_करोमुख्यs->async_put_करोमुख्यs[0] &= ~BIT_ULL(करोमुख्य);
	घातer_करोमुख्यs->async_put_करोमुख्यs[1] &= ~BIT_ULL(करोमुख्य);
पूर्ण

अटल bool
पूर्णांकel_display_घातer_grab_async_put_ref(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	bool ret = false;

	अगर (!(async_put_करोमुख्यs_mask(घातer_करोमुख्यs) & BIT_ULL(करोमुख्य)))
		जाओ out_verअगरy;

	async_put_करोमुख्यs_clear_करोमुख्य(घातer_करोमुख्यs, करोमुख्य);

	ret = true;

	अगर (async_put_करोमुख्यs_mask(घातer_करोमुख्यs))
		जाओ out_verअगरy;

	cancel_delayed_work(&घातer_करोमुख्यs->async_put_work);
	पूर्णांकel_runसमय_pm_put_raw(&dev_priv->runसमय_pm,
				 fetch_and_zero(&घातer_करोमुख्यs->async_put_wakeref));
out_verअगरy:
	verअगरy_async_put_करोमुख्यs_state(घातer_करोमुख्यs);

	वापस ret;
पूर्ण

अटल व्योम
__पूर्णांकel_display_घातer_get_करोमुख्य(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *घातer_well;

	अगर (पूर्णांकel_display_घातer_grab_async_put_ref(dev_priv, करोमुख्य))
		वापस;

	क्रम_each_घातer_करोमुख्य_well(dev_priv, घातer_well, BIT_ULL(करोमुख्य))
		पूर्णांकel_घातer_well_get(dev_priv, घातer_well);

	घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य]++;
पूर्ण

/**
 * पूर्णांकel_display_घातer_get - grab a घातer करोमुख्य reference
 * @dev_priv: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to reference
 *
 * This function grअसल a घातer करोमुख्य reference क्रम @करोमुख्य and ensures that the
 * घातer करोमुख्य and all its parents are घातered up. Thereक्रमe users should only
 * grab a reference to the innermost घातer करोमुख्य they need.
 *
 * Any घातer करोमुख्य reference obtained by this function must have a symmetric
 * call to पूर्णांकel_display_घातer_put() to release the reference again.
 */
पूर्णांकel_wakeref_t पूर्णांकel_display_घातer_get(काष्ठा drm_i915_निजी *dev_priv,
					क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	पूर्णांकel_wakeref_t wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	mutex_lock(&घातer_करोमुख्यs->lock);
	__पूर्णांकel_display_घातer_get_करोमुख्य(dev_priv, करोमुख्य);
	mutex_unlock(&घातer_करोमुख्यs->lock);

	वापस wakeref;
पूर्ण

/**
 * पूर्णांकel_display_घातer_get_अगर_enabled - grab a reference क्रम an enabled display घातer करोमुख्य
 * @dev_priv: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to reference
 *
 * This function grअसल a घातer करोमुख्य reference क्रम @करोमुख्य and ensures that the
 * घातer करोमुख्य and all its parents are घातered up. Thereक्रमe users should only
 * grab a reference to the innermost घातer करोमुख्य they need.
 *
 * Any घातer करोमुख्य reference obtained by this function must have a symmetric
 * call to पूर्णांकel_display_घातer_put() to release the reference again.
 */
पूर्णांकel_wakeref_t
पूर्णांकel_display_घातer_get_अगर_enabled(काष्ठा drm_i915_निजी *dev_priv,
				   क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	पूर्णांकel_wakeref_t wakeref;
	bool is_enabled;

	wakeref = पूर्णांकel_runसमय_pm_get_अगर_in_use(&dev_priv->runसमय_pm);
	अगर (!wakeref)
		वापस false;

	mutex_lock(&घातer_करोमुख्यs->lock);

	अगर (__पूर्णांकel_display_घातer_is_enabled(dev_priv, करोमुख्य)) अणु
		__पूर्णांकel_display_घातer_get_करोमुख्य(dev_priv, करोमुख्य);
		is_enabled = true;
	पूर्ण अन्यथा अणु
		is_enabled = false;
	पूर्ण

	mutex_unlock(&घातer_करोमुख्यs->lock);

	अगर (!is_enabled) अणु
		पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
		wakeref = 0;
	पूर्ण

	वापस wakeref;
पूर्ण

अटल व्योम
__पूर्णांकel_display_घातer_put_करोमुख्य(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *घातer_well;
	स्थिर अक्षर *name = पूर्णांकel_display_घातer_करोमुख्य_str(करोमुख्य);

	घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;

	drm_WARN(&dev_priv->drm, !घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य],
		 "Use count on domain %s is already zero\n",
		 name);
	drm_WARN(&dev_priv->drm,
		 async_put_करोमुख्यs_mask(घातer_करोमुख्यs) & BIT_ULL(करोमुख्य),
		 "Async disabling of domain %s is pending\n",
		 name);

	घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य]--;

	क्रम_each_घातer_करोमुख्य_well_reverse(dev_priv, घातer_well, BIT_ULL(करोमुख्य))
		पूर्णांकel_घातer_well_put(dev_priv, घातer_well);
पूर्ण

अटल व्योम __पूर्णांकel_display_घातer_put(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;

	mutex_lock(&घातer_करोमुख्यs->lock);
	__पूर्णांकel_display_घातer_put_करोमुख्य(dev_priv, करोमुख्य);
	mutex_unlock(&घातer_करोमुख्यs->lock);
पूर्ण

अटल व्योम
queue_async_put_करोमुख्यs_work(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs,
			     पूर्णांकel_wakeref_t wakeref)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(घातer_करोमुख्यs,
						     काष्ठा drm_i915_निजी,
						     घातer_करोमुख्यs);
	drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->async_put_wakeref);
	घातer_करोमुख्यs->async_put_wakeref = wakeref;
	drm_WARN_ON(&i915->drm, !queue_delayed_work(प्रणाली_unbound_wq,
						    &घातer_करोमुख्यs->async_put_work,
						    msecs_to_jअगरfies(100)));
पूर्ण

अटल व्योम
release_async_put_करोमुख्यs(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs, u64 mask)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(घातer_करोमुख्यs, काष्ठा drm_i915_निजी,
			     घातer_करोमुख्यs);
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &dev_priv->runसमय_pm;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * The caller must hold alपढ़ोy raw wakeref, upgrade that to a proper
	 * wakeref to make the state checker happy about the HW access during
	 * घातer well disabling.
	 */
	निश्चित_rpm_raw_wakeref_held(rpm);
	wakeref = पूर्णांकel_runसमय_pm_get(rpm);

	क्रम_each_घातer_करोमुख्य(करोमुख्य, mask) अणु
		/* Clear beक्रमe put, so put's sanity check is happy. */
		async_put_करोमुख्यs_clear_करोमुख्य(घातer_करोमुख्यs, करोमुख्य);
		__पूर्णांकel_display_घातer_put_करोमुख्य(dev_priv, करोमुख्य);
	पूर्ण

	पूर्णांकel_runसमय_pm_put(rpm, wakeref);
पूर्ण

अटल व्योम
पूर्णांकel_display_घातer_put_async_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, काष्ठा drm_i915_निजी,
			     घातer_करोमुख्यs.async_put_work.work);
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &dev_priv->runसमय_pm;
	पूर्णांकel_wakeref_t new_work_wakeref = पूर्णांकel_runसमय_pm_get_raw(rpm);
	पूर्णांकel_wakeref_t old_work_wakeref = 0;

	mutex_lock(&घातer_करोमुख्यs->lock);

	/*
	 * Bail out अगर all the करोमुख्य refs pending to be released were grabbed
	 * by subsequent माला_लो or a flush_work.
	 */
	old_work_wakeref = fetch_and_zero(&घातer_करोमुख्यs->async_put_wakeref);
	अगर (!old_work_wakeref)
		जाओ out_verअगरy;

	release_async_put_करोमुख्यs(घातer_करोमुख्यs,
				  घातer_करोमुख्यs->async_put_करोमुख्यs[0]);

	/* Requeue the work अगर more करोमुख्यs were async put meanजबतक. */
	अगर (घातer_करोमुख्यs->async_put_करोमुख्यs[1]) अणु
		घातer_करोमुख्यs->async_put_करोमुख्यs[0] =
			fetch_and_zero(&घातer_करोमुख्यs->async_put_करोमुख्यs[1]);
		queue_async_put_करोमुख्यs_work(घातer_करोमुख्यs,
					     fetch_and_zero(&new_work_wakeref));
	पूर्ण

out_verअगरy:
	verअगरy_async_put_करोमुख्यs_state(घातer_करोमुख्यs);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	अगर (old_work_wakeref)
		पूर्णांकel_runसमय_pm_put_raw(rpm, old_work_wakeref);
	अगर (new_work_wakeref)
		पूर्णांकel_runसमय_pm_put_raw(rpm, new_work_wakeref);
पूर्ण

/**
 * पूर्णांकel_display_घातer_put_async - release a घातer करोमुख्य reference asynchronously
 * @i915: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to reference
 * @wakeref: wakeref acquired क्रम the reference that is being released
 *
 * This function drops the घातer करोमुख्य reference obtained by
 * पूर्णांकel_display_घातer_get*() and schedules a work to घातer करोwn the
 * corresponding hardware block अगर this is the last reference.
 */
व्योम __पूर्णांकel_display_घातer_put_async(काष्ठा drm_i915_निजी *i915,
				     क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
				     पूर्णांकel_wakeref_t wakeref)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &i915->runसमय_pm;
	पूर्णांकel_wakeref_t work_wakeref = पूर्णांकel_runसमय_pm_get_raw(rpm);

	mutex_lock(&घातer_करोमुख्यs->lock);

	अगर (घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य] > 1) अणु
		__पूर्णांकel_display_घातer_put_करोमुख्य(i915, करोमुख्य);

		जाओ out_verअगरy;
	पूर्ण

	drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य] != 1);

	/* Let a pending work requeue itself or queue a new one. */
	अगर (घातer_करोमुख्यs->async_put_wakeref) अणु
		घातer_करोमुख्यs->async_put_करोमुख्यs[1] |= BIT_ULL(करोमुख्य);
	पूर्ण अन्यथा अणु
		घातer_करोमुख्यs->async_put_करोमुख्यs[0] |= BIT_ULL(करोमुख्य);
		queue_async_put_करोमुख्यs_work(घातer_करोमुख्यs,
					     fetch_and_zero(&work_wakeref));
	पूर्ण

out_verअगरy:
	verअगरy_async_put_करोमुख्यs_state(घातer_करोमुख्यs);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	अगर (work_wakeref)
		पूर्णांकel_runसमय_pm_put_raw(rpm, work_wakeref);

	पूर्णांकel_runसमय_pm_put(rpm, wakeref);
पूर्ण

/**
 * पूर्णांकel_display_घातer_flush_work - flushes the async display घातer disabling work
 * @i915: i915 device instance
 *
 * Flushes any pending work that was scheduled by a preceding
 * पूर्णांकel_display_घातer_put_async() call, completing the disabling of the
 * corresponding घातer करोमुख्यs.
 *
 * Note that the work handler function may still be running after this
 * function वापसs; to ensure that the work handler isn't running use
 * पूर्णांकel_display_घातer_flush_work_sync() instead.
 */
व्योम पूर्णांकel_display_घातer_flush_work(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;
	पूर्णांकel_wakeref_t work_wakeref;

	mutex_lock(&घातer_करोमुख्यs->lock);

	work_wakeref = fetch_and_zero(&घातer_करोमुख्यs->async_put_wakeref);
	अगर (!work_wakeref)
		जाओ out_verअगरy;

	release_async_put_करोमुख्यs(घातer_करोमुख्यs,
				  async_put_करोमुख्यs_mask(घातer_करोमुख्यs));
	cancel_delayed_work(&घातer_करोमुख्यs->async_put_work);

out_verअगरy:
	verअगरy_async_put_करोमुख्यs_state(घातer_करोमुख्यs);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	अगर (work_wakeref)
		पूर्णांकel_runसमय_pm_put_raw(&i915->runसमय_pm, work_wakeref);
पूर्ण

/**
 * पूर्णांकel_display_घातer_flush_work_sync - flushes and syncs the async display घातer disabling work
 * @i915: i915 device instance
 *
 * Like पूर्णांकel_display_घातer_flush_work(), but also ensure that the work
 * handler function is not running any more when this function वापसs.
 */
अटल व्योम
पूर्णांकel_display_घातer_flush_work_sync(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;

	पूर्णांकel_display_घातer_flush_work(i915);
	cancel_delayed_work_sync(&घातer_करोमुख्यs->async_put_work);

	verअगरy_async_put_करोमुख्यs_state(घातer_करोमुख्यs);

	drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->async_put_wakeref);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
/**
 * पूर्णांकel_display_घातer_put - release a घातer करोमुख्य reference
 * @dev_priv: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to reference
 * @wakeref: wakeref acquired क्रम the reference that is being released
 *
 * This function drops the घातer करोमुख्य reference obtained by
 * पूर्णांकel_display_घातer_get() and might घातer करोwn the corresponding hardware
 * block right away अगर this is the last reference.
 */
व्योम पूर्णांकel_display_घातer_put(काष्ठा drm_i915_निजी *dev_priv,
			     क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य,
			     पूर्णांकel_wakeref_t wakeref)
अणु
	__पूर्णांकel_display_घातer_put(dev_priv, करोमुख्य);
	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
पूर्ण
#अन्यथा
/**
 * पूर्णांकel_display_घातer_put_unchecked - release an unchecked घातer करोमुख्य reference
 * @dev_priv: i915 device instance
 * @करोमुख्य: घातer करोमुख्य to reference
 *
 * This function drops the घातer करोमुख्य reference obtained by
 * पूर्णांकel_display_घातer_get() and might घातer करोwn the corresponding hardware
 * block right away अगर this is the last reference.
 *
 * This function is only क्रम the घातer करोमुख्य code's पूर्णांकernal use to suppress wakeref
 * tracking when the correspondig debug kconfig option is disabled, should not
 * be used otherwise.
 */
व्योम पूर्णांकel_display_घातer_put_unchecked(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	__पूर्णांकel_display_घातer_put(dev_priv, करोमुख्य);
	पूर्णांकel_runसमय_pm_put_unchecked(&dev_priv->runसमय_pm);
पूर्ण
#पूर्ण_अगर

व्योम
पूर्णांकel_display_घातer_get_in_set(काष्ठा drm_i915_निजी *i915,
			       काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set,
			       क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	पूर्णांकel_wakeref_t __maybe_unused wf;

	drm_WARN_ON(&i915->drm, घातer_करोमुख्य_set->mask & BIT_ULL(करोमुख्य));

	wf = पूर्णांकel_display_घातer_get(i915, करोमुख्य);
#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
	घातer_करोमुख्य_set->wakerefs[करोमुख्य] = wf;
#पूर्ण_अगर
	घातer_करोमुख्य_set->mask |= BIT_ULL(करोमुख्य);
पूर्ण

bool
पूर्णांकel_display_घातer_get_in_set_अगर_enabled(काष्ठा drm_i915_निजी *i915,
					  काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set,
					  क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य)
अणु
	पूर्णांकel_wakeref_t wf;

	drm_WARN_ON(&i915->drm, घातer_करोमुख्य_set->mask & BIT_ULL(करोमुख्य));

	wf = पूर्णांकel_display_घातer_get_अगर_enabled(i915, करोमुख्य);
	अगर (!wf)
		वापस false;

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
	घातer_करोमुख्य_set->wakerefs[करोमुख्य] = wf;
#पूर्ण_अगर
	घातer_करोमुख्य_set->mask |= BIT_ULL(करोमुख्य);

	वापस true;
पूर्ण

व्योम
पूर्णांकel_display_घातer_put_mask_in_set(काष्ठा drm_i915_निजी *i915,
				    काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set,
				    u64 mask)
अणु
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

	drm_WARN_ON(&i915->drm, mask & ~घातer_करोमुख्य_set->mask);

	क्रम_each_घातer_करोमुख्य(करोमुख्य, mask) अणु
		पूर्णांकel_wakeref_t __maybe_unused wf = -1;

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
		wf = fetch_and_zero(&घातer_करोमुख्य_set->wakerefs[करोमुख्य]);
#पूर्ण_अगर
		पूर्णांकel_display_घातer_put(i915, करोमुख्य, wf);
		घातer_करोमुख्य_set->mask &= ~BIT_ULL(करोमुख्य);
	पूर्ण
पूर्ण

#घोषणा I830_PIPES_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PIPE_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_A_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |	\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा VLV_DISPLAY_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_DISPLAY_CORE) |	\
	BIT_ULL(POWER_DOMAIN_PIPE_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_A_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DSI) |		\
	BIT_ULL(POWER_DOMAIN_PORT_CRT) |		\
	BIT_ULL(POWER_DOMAIN_VGA) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_GMBUS) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा VLV_DPIO_CMN_BC_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_CRT) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा VLV_DPIO_TX_B_LANES_01_POWER_DOMAINS (	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा VLV_DPIO_TX_B_LANES_23_POWER_DOMAINS (	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा VLV_DPIO_TX_C_LANES_01_POWER_DOMAINS (	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा VLV_DPIO_TX_C_LANES_23_POWER_DOMAINS (	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा CHV_DISPLAY_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_DISPLAY_CORE) |	\
	BIT_ULL(POWER_DOMAIN_PIPE_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_A_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DSI) |		\
	BIT_ULL(POWER_DOMAIN_VGA) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_AUX_D) |		\
	BIT_ULL(POWER_DOMAIN_GMBUS) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा CHV_DPIO_CMN_BC_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा CHV_DPIO_CMN_D_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_D) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा HSW_DISPLAY_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_A_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_CRT) | /* DDI E */	\
	BIT_ULL(POWER_DOMAIN_VGA) |				\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा BDW_DISPLAY_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_CRT) | /* DDI E */	\
	BIT_ULL(POWER_DOMAIN_VGA) |				\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा SKL_DISPLAY_POWERWELL_2_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_E_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |                       \
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_AUX_D) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_VGA) |				\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा SKL_DISPLAY_DDI_IO_A_E_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_A_IO) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_E_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा SKL_DISPLAY_DDI_IO_B_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा SKL_DISPLAY_DDI_IO_C_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा SKL_DISPLAY_DDI_IO_D_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा SKL_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	SKL_DISPLAY_POWERWELL_2_POWER_DOMAINS |		\
	BIT_ULL(POWER_DOMAIN_GT_IRQ) |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा BXT_DISPLAY_POWERWELL_2_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_VGA) |				\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा BXT_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	BXT_DISPLAY_POWERWELL_2_POWER_DOMAINS |		\
	BIT_ULL(POWER_DOMAIN_GT_IRQ) |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_GMBUS) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा BXT_DPIO_CMN_A_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_A_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा BXT_DPIO_CMN_BC_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा GLK_DISPLAY_POWERWELL_2_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |                       \
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_VGA) |				\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DISPLAY_DDI_IO_A_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_A_IO))
#घोषणा GLK_DISPLAY_DDI_IO_B_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_IO))
#घोषणा GLK_DISPLAY_DDI_IO_C_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_IO))
#घोषणा GLK_DPIO_CMN_A_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_A_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DPIO_CMN_B_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DPIO_CMN_C_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DISPLAY_AUX_A_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_A) |		\
	BIT_ULL(POWER_DOMAIN_AUX_IO_A) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DISPLAY_AUX_B_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DISPLAY_AUX_C_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा GLK_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	GLK_DISPLAY_POWERWELL_2_POWER_DOMAINS |		\
	BIT_ULL(POWER_DOMAIN_GT_IRQ) |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_GMBUS) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा CNL_DISPLAY_POWERWELL_2_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_F_LANES) |		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |                       \
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_AUX_D) |			\
	BIT_ULL(POWER_DOMAIN_AUX_F) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_VGA) |				\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_DDI_A_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_A_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_DDI_B_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_DDI_C_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_DDI_D_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_AUX_A_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_AUX_IO_A) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_AUX_B_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_AUX_C_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_AUX_D_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_D) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_AUX_F_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_F) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_DDI_F_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_F_IO) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
#घोषणा CNL_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	CNL_DISPLAY_POWERWELL_2_POWER_DOMAINS |		\
	BIT_ULL(POWER_DOMAIN_GT_IRQ) |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

/*
 * ICL PW_0/PG_0 करोमुख्यs (HW/DMC control):
 * - PCI
 * - घड़ीs except port PLL
 * - central घातer except FBC
 * - shared functions except pipe पूर्णांकerrupts, pipe MBUS, DBUF रेजिस्टरs
 * ICL PW_1/PG_1 करोमुख्यs (HW/DMC control):
 * - DBUF function
 * - PIPE_A and its planes, except VGA
 * - transcoder EDP + PSR
 * - transcoder DSI
 * - DDI_A
 * - FBC
 */
#घोषणा ICL_PW_4_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_INIT))
	/* VDSC/joining */
#घोषणा ICL_PW_3_POWER_DOMAINS (			\
	ICL_PW_4_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_A) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_E_LANES) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_F_LANES) |	\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_AUX_D) |			\
	BIT_ULL(POWER_DOMAIN_AUX_E) |			\
	BIT_ULL(POWER_DOMAIN_AUX_F) |			\
	BIT_ULL(POWER_DOMAIN_AUX_C_TBT) |		\
	BIT_ULL(POWER_DOMAIN_AUX_D_TBT) |		\
	BIT_ULL(POWER_DOMAIN_AUX_E_TBT) |		\
	BIT_ULL(POWER_DOMAIN_AUX_F_TBT) |		\
	BIT_ULL(POWER_DOMAIN_VGA) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_INIT))
	/*
	 * - transcoder WD
	 * - KVMR (HW control)
	 */
#घोषणा ICL_PW_2_POWER_DOMAINS (			\
	ICL_PW_3_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_VDSC_PW2) |		\
	BIT_ULL(POWER_DOMAIN_INIT))
	/*
	 * - KVMR (HW control)
	 */
#घोषणा ICL_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	ICL_PW_2_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_DPLL_DC_OFF) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा ICL_DDI_IO_A_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_A_IO))
#घोषणा ICL_DDI_IO_B_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_B_IO))
#घोषणा ICL_DDI_IO_C_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_C_IO))
#घोषणा ICL_DDI_IO_D_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_D_IO))
#घोषणा ICL_DDI_IO_E_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_E_IO))
#घोषणा ICL_DDI_IO_F_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_F_IO))

#घोषणा ICL_AUX_A_IO_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_AUX_IO_A) |		\
	BIT_ULL(POWER_DOMAIN_AUX_A))
#घोषणा ICL_AUX_B_IO_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_AUX_B))
#घोषणा ICL_AUX_C_TC1_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_C))
#घोषणा ICL_AUX_D_TC2_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_D))
#घोषणा ICL_AUX_E_TC3_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_E))
#घोषणा ICL_AUX_F_TC4_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_F))
#घोषणा ICL_AUX_C_TBT1_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_C_TBT))
#घोषणा ICL_AUX_D_TBT2_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_D_TBT))
#घोषणा ICL_AUX_E_TBT3_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_E_TBT))
#घोषणा ICL_AUX_F_TBT4_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_F_TBT))

#घोषणा TGL_PW_5_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PIPE_D) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_D) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_D_PANEL_FITTER) |     \
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा TGL_PW_4_POWER_DOMAINS (			\
	TGL_PW_5_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा TGL_PW_3_POWER_DOMAINS (			\
	TGL_PW_4_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC1) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC2) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC3) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC4) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC5) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC6) |	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC1) |		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC2) |		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC3) |		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC4) |		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC5) |		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC6) |		\
	BIT_ULL(POWER_DOMAIN_AUX_TBT1) |		\
	BIT_ULL(POWER_DOMAIN_AUX_TBT2) |		\
	BIT_ULL(POWER_DOMAIN_AUX_TBT3) |		\
	BIT_ULL(POWER_DOMAIN_AUX_TBT4) |		\
	BIT_ULL(POWER_DOMAIN_AUX_TBT5) |		\
	BIT_ULL(POWER_DOMAIN_AUX_TBT6) |		\
	BIT_ULL(POWER_DOMAIN_VGA) |			\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा TGL_PW_2_POWER_DOMAINS (			\
	TGL_PW_3_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_VDSC_PW2) |	\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा TGL_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	TGL_PW_3_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_AUX_C) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा TGL_DDI_IO_TC1_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_PORT_DDI_IO_TC1)
#घोषणा TGL_DDI_IO_TC2_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_PORT_DDI_IO_TC2)
#घोषणा TGL_DDI_IO_TC3_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_PORT_DDI_IO_TC3)
#घोषणा TGL_DDI_IO_TC4_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_PORT_DDI_IO_TC4)
#घोषणा TGL_DDI_IO_TC5_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_PORT_DDI_IO_TC5)
#घोषणा TGL_DDI_IO_TC6_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_PORT_DDI_IO_TC6)

#घोषणा TGL_AUX_A_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_IO_A) |	\
	BIT_ULL(POWER_DOMAIN_AUX_A))
#घोषणा TGL_AUX_B_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_B))
#घोषणा TGL_AUX_C_IO_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_C))

#घोषणा TGL_AUX_IO_USBC1_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_USBC1)
#घोषणा TGL_AUX_IO_USBC2_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_USBC2)
#घोषणा TGL_AUX_IO_USBC3_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_USBC3)
#घोषणा TGL_AUX_IO_USBC4_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_USBC4)
#घोषणा TGL_AUX_IO_USBC5_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_USBC5)
#घोषणा TGL_AUX_IO_USBC6_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_USBC6)

#घोषणा TGL_AUX_IO_TBT1_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_TBT1)
#घोषणा TGL_AUX_IO_TBT2_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_TBT2)
#घोषणा TGL_AUX_IO_TBT3_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_TBT3)
#घोषणा TGL_AUX_IO_TBT4_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_TBT4)
#घोषणा TGL_AUX_IO_TBT5_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_TBT5)
#घोषणा TGL_AUX_IO_TBT6_POWER_DOMAINS	BIT_ULL(POWER_DOMAIN_AUX_TBT6)

#घोषणा TGL_TC_COLD_OFF_POWER_DOMAINS (		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC1)	|	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC2)	|	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC3)	|	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC4)	|	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC5)	|	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC6)	|	\
	BIT_ULL(POWER_DOMAIN_AUX_TBT1) |	\
	BIT_ULL(POWER_DOMAIN_AUX_TBT2) |	\
	BIT_ULL(POWER_DOMAIN_AUX_TBT3) |	\
	BIT_ULL(POWER_DOMAIN_AUX_TBT4) |	\
	BIT_ULL(POWER_DOMAIN_AUX_TBT5) |	\
	BIT_ULL(POWER_DOMAIN_AUX_TBT6) |	\
	BIT_ULL(POWER_DOMAIN_TC_COLD_OFF))

#घोषणा RKL_PW_4_POWER_DOMAINS (			\
	BIT_ULL(POWER_DOMAIN_PIPE_C) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_C_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_C) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

#घोषणा RKL_PW_3_POWER_DOMAINS (			\
	RKL_PW_4_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_PIPE_B) |			\
	BIT_ULL(POWER_DOMAIN_PIPE_B_PANEL_FITTER) |	\
	BIT_ULL(POWER_DOMAIN_AUDIO) |			\
	BIT_ULL(POWER_DOMAIN_VGA) |			\
	BIT_ULL(POWER_DOMAIN_TRANSCODER_B) |		\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC1) |	\
	BIT_ULL(POWER_DOMAIN_PORT_DDI_LANES_TC2) |	\
	BIT_ULL(POWER_DOMAIN_AUX_USBC1) |		\
	BIT_ULL(POWER_DOMAIN_AUX_USBC2) |		\
	BIT_ULL(POWER_DOMAIN_INIT))

/*
 * There is no PW_2/PG_2 on RKL.
 *
 * RKL PW_1/PG_1 करोमुख्यs (under HW/DMC control):
 * - DBUF function (note: रेजिस्टरs are in PW0)
 * - PIPE_A and its planes and VDSC/joining, except VGA
 * - transcoder A
 * - DDI_A and DDI_B
 * - FBC
 *
 * RKL PW_0/PG_0 करोमुख्यs (under HW/DMC control):
 * - PCI
 * - घड़ीs except port PLL
 * - shared functions:
 *     * पूर्णांकerrupts except pipe पूर्णांकerrupts
 *     * MBus except PIPE_MBUS_DBOX_CTL
 *     * DBUF रेजिस्टरs
 * - central घातer except FBC
 * - top-level GTC (DDI-level GTC is in the well associated with the DDI)
 */

#घोषणा RKL_DISPLAY_DC_OFF_POWER_DOMAINS (		\
	RKL_PW_3_POWER_DOMAINS |			\
	BIT_ULL(POWER_DOMAIN_MODESET) |			\
	BIT_ULL(POWER_DOMAIN_AUX_A) |			\
	BIT_ULL(POWER_DOMAIN_AUX_B) |			\
	BIT_ULL(POWER_DOMAIN_INIT))

अटल स्थिर काष्ठा i915_घातer_well_ops i9xx_always_on_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = i9xx_always_on_घातer_well_noop,
	.disable = i9xx_always_on_घातer_well_noop,
	.is_enabled = i9xx_always_on_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops chv_pipe_घातer_well_ops = अणु
	.sync_hw = chv_pipe_घातer_well_sync_hw,
	.enable = chv_pipe_घातer_well_enable,
	.disable = chv_pipe_घातer_well_disable,
	.is_enabled = chv_pipe_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops chv_dpio_cmn_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = chv_dpio_cmn_घातer_well_enable,
	.disable = chv_dpio_cmn_घातer_well_disable,
	.is_enabled = vlv_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc i9xx_always_on_घातer_well[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops i830_pipes_घातer_well_ops = अणु
	.sync_hw = i830_pipes_घातer_well_sync_hw,
	.enable = i830_pipes_घातer_well_enable,
	.disable = i830_pipes_घातer_well_disable,
	.is_enabled = i830_pipes_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc i830_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "pipes",
		.करोमुख्यs = I830_PIPES_POWER_DOMAINS,
		.ops = &i830_pipes_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops hsw_घातer_well_ops = अणु
	.sync_hw = hsw_घातer_well_sync_hw,
	.enable = hsw_घातer_well_enable,
	.disable = hsw_घातer_well_disable,
	.is_enabled = hsw_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops gen9_dc_off_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = gen9_dc_off_घातer_well_enable,
	.disable = gen9_dc_off_घातer_well_disable,
	.is_enabled = gen9_dc_off_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops bxt_dpio_cmn_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = bxt_dpio_cmn_घातer_well_enable,
	.disable = bxt_dpio_cmn_घातer_well_disable,
	.is_enabled = bxt_dpio_cmn_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_regs hsw_घातer_well_regs = अणु
	.bios	= HSW_PWR_WELL_CTL1,
	.driver	= HSW_PWR_WELL_CTL2,
	.kvmr	= HSW_PWR_WELL_CTL3,
	.debug	= HSW_PWR_WELL_CTL4,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc hsw_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "display",
		.करोमुख्यs = HSW_DISPLAY_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = HSW_DISP_PW_GLOBAL,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = HSW_PW_CTL_IDX_GLOBAL,
			.hsw.has_vga = true,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc bdw_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "display",
		.करोमुख्यs = BDW_DISPLAY_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = HSW_DISP_PW_GLOBAL,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = HSW_PW_CTL_IDX_GLOBAL,
			.hsw.irq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
			.hsw.has_vga = true,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops vlv_display_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = vlv_display_घातer_well_enable,
	.disable = vlv_display_घातer_well_disable,
	.is_enabled = vlv_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops vlv_dpio_cmn_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = vlv_dpio_cmn_घातer_well_enable,
	.disable = vlv_dpio_cmn_घातer_well_disable,
	.is_enabled = vlv_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops vlv_dpio_घातer_well_ops = अणु
	.sync_hw = i9xx_घातer_well_sync_hw_noop,
	.enable = vlv_घातer_well_enable,
	.disable = vlv_घातer_well_disable,
	.is_enabled = vlv_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc vlv_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "display",
		.करोमुख्यs = VLV_DISPLAY_POWER_DOMAINS,
		.ops = &vlv_display_घातer_well_ops,
		.id = VLV_DISP_PW_DISP2D,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DISP2D,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-tx-b-01",
		.करोमुख्यs = VLV_DPIO_TX_B_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_B_LANES_23_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_23_POWER_DOMAINS,
		.ops = &vlv_dpio_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_TX_B_LANES_01,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-tx-b-23",
		.करोमुख्यs = VLV_DPIO_TX_B_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_B_LANES_23_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_23_POWER_DOMAINS,
		.ops = &vlv_dpio_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_TX_B_LANES_23,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-tx-c-01",
		.करोमुख्यs = VLV_DPIO_TX_B_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_B_LANES_23_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_23_POWER_DOMAINS,
		.ops = &vlv_dpio_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_TX_C_LANES_01,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-tx-c-23",
		.करोमुख्यs = VLV_DPIO_TX_B_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_B_LANES_23_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_01_POWER_DOMAINS |
			   VLV_DPIO_TX_C_LANES_23_POWER_DOMAINS,
		.ops = &vlv_dpio_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_TX_C_LANES_23,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common",
		.करोमुख्यs = VLV_DPIO_CMN_BC_POWER_DOMAINS,
		.ops = &vlv_dpio_cmn_घातer_well_ops,
		.id = VLV_DISP_PW_DPIO_CMN_BC,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_CMN_BC,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc chv_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "display",
		/*
		 * Pipe A घातer well is the new disp2d well. Pipe B and C
		 * घातer wells करोn't actually exist. Pipe A घातer well is
		 * required क्रम any pipe to work.
		 */
		.करोमुख्यs = CHV_DISPLAY_POWER_DOMAINS,
		.ops = &chv_pipe_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "dpio-common-bc",
		.करोमुख्यs = CHV_DPIO_CMN_BC_POWER_DOMAINS,
		.ops = &chv_dpio_cmn_घातer_well_ops,
		.id = VLV_DISP_PW_DPIO_CMN_BC,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_CMN_BC,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common-d",
		.करोमुख्यs = CHV_DPIO_CMN_D_POWER_DOMAINS,
		.ops = &chv_dpio_cmn_घातer_well_ops,
		.id = CHV_DISP_PW_DPIO_CMN_D,
		अणु
			.vlv.idx = PUNIT_PWGT_IDX_DPIO_CMN_D,
		पूर्ण,
	पूर्ण,
पूर्ण;

bool पूर्णांकel_display_घातer_well_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत i915_घातer_well_id घातer_well_id)
अणु
	काष्ठा i915_घातer_well *घातer_well;
	bool ret;

	घातer_well = lookup_घातer_well(dev_priv, घातer_well_id);
	ret = घातer_well->desc->ops->is_enabled(dev_priv, घातer_well);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i915_घातer_well_desc skl_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "MISC IO power well",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_MISC_IO,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_MISC_IO,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = SKL_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 2",
		.करोमुख्यs = SKL_DISPLAY_POWERWELL_2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_2,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_2,
			.hsw.irq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI A/E IO power well",
		.करोमुख्यs = SKL_DISPLAY_DDI_IO_A_E_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_A_E,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI B IO power well",
		.करोमुख्यs = SKL_DISPLAY_DDI_IO_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI C IO power well",
		.करोमुख्यs = SKL_DISPLAY_DDI_IO_C_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_C,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI D IO power well",
		.करोमुख्यs = SKL_DISPLAY_DDI_IO_D_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_D,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc bxt_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = BXT_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 2",
		.करोमुख्यs = BXT_DISPLAY_POWERWELL_2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_2,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_2,
			.hsw.irq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common-a",
		.करोमुख्यs = BXT_DPIO_CMN_A_POWER_DOMAINS,
		.ops = &bxt_dpio_cmn_घातer_well_ops,
		.id = BXT_DISP_PW_DPIO_CMN_A,
		अणु
			.bxt.phy = DPIO_PHY1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common-bc",
		.करोमुख्यs = BXT_DPIO_CMN_BC_POWER_DOMAINS,
		.ops = &bxt_dpio_cmn_घातer_well_ops,
		.id = VLV_DISP_PW_DPIO_CMN_BC,
		अणु
			.bxt.phy = DPIO_PHY0,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc glk_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = GLK_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 2",
		.करोमुख्यs = GLK_DISPLAY_POWERWELL_2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_2,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_2,
			.hsw.irq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common-a",
		.करोमुख्यs = GLK_DPIO_CMN_A_POWER_DOMAINS,
		.ops = &bxt_dpio_cmn_घातer_well_ops,
		.id = BXT_DISP_PW_DPIO_CMN_A,
		अणु
			.bxt.phy = DPIO_PHY1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common-b",
		.करोमुख्यs = GLK_DPIO_CMN_B_POWER_DOMAINS,
		.ops = &bxt_dpio_cmn_घातer_well_ops,
		.id = VLV_DISP_PW_DPIO_CMN_BC,
		अणु
			.bxt.phy = DPIO_PHY0,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "dpio-common-c",
		.करोमुख्यs = GLK_DPIO_CMN_C_POWER_DOMAINS,
		.ops = &bxt_dpio_cmn_घातer_well_ops,
		.id = GLK_DISP_PW_DPIO_CMN_C,
		अणु
			.bxt.phy = DPIO_PHY2,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX A",
		.करोमुख्यs = GLK_DISPLAY_AUX_A_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_AUX_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX B",
		.करोमुख्यs = GLK_DISPLAY_AUX_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_AUX_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX C",
		.करोमुख्यs = GLK_DISPLAY_AUX_C_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_AUX_C,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI A IO power well",
		.करोमुख्यs = GLK_DISPLAY_DDI_IO_A_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_DDI_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI B IO power well",
		.करोमुख्यs = GLK_DISPLAY_DDI_IO_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI C IO power well",
		.करोमुख्यs = GLK_DISPLAY_DDI_IO_C_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_C,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc cnl_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX A",
		.करोमुख्यs = CNL_DISPLAY_AUX_A_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_AUX_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX B",
		.करोमुख्यs = CNL_DISPLAY_AUX_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_AUX_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX C",
		.करोमुख्यs = CNL_DISPLAY_AUX_C_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_AUX_C,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX D",
		.करोमुख्यs = CNL_DISPLAY_AUX_D_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = CNL_PW_CTL_IDX_AUX_D,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = CNL_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 2",
		.करोमुख्यs = CNL_DISPLAY_POWERWELL_2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_2,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_PW_2,
			.hsw.irq_pipe_mask = BIT(PIPE_B) | BIT(PIPE_C),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI A IO power well",
		.करोमुख्यs = CNL_DISPLAY_DDI_A_IO_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = GLK_PW_CTL_IDX_DDI_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI B IO power well",
		.करोमुख्यs = CNL_DISPLAY_DDI_B_IO_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI C IO power well",
		.करोमुख्यs = CNL_DISPLAY_DDI_C_IO_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_C,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI D IO power well",
		.करोमुख्यs = CNL_DISPLAY_DDI_D_IO_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = SKL_PW_CTL_IDX_DDI_D,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI F IO power well",
		.करोमुख्यs = CNL_DISPLAY_DDI_F_IO_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = CNL_DISP_PW_DDI_F_IO,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = CNL_PW_CTL_IDX_DDI_F,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX F",
		.करोमुख्यs = CNL_DISPLAY_AUX_F_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = CNL_DISP_PW_DDI_F_AUX,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = CNL_PW_CTL_IDX_AUX_F,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_ops icl_aux_घातer_well_ops = अणु
	.sync_hw = hsw_घातer_well_sync_hw,
	.enable = icl_aux_घातer_well_enable,
	.disable = icl_aux_घातer_well_disable,
	.is_enabled = hsw_घातer_well_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_regs icl_aux_घातer_well_regs = अणु
	.bios	= ICL_PWR_WELL_CTL_AUX1,
	.driver	= ICL_PWR_WELL_CTL_AUX2,
	.debug	= ICL_PWR_WELL_CTL_AUX4,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_regs icl_ddi_घातer_well_regs = अणु
	.bios	= ICL_PWR_WELL_CTL_DDI1,
	.driver	= ICL_PWR_WELL_CTL_DDI2,
	.debug	= ICL_PWR_WELL_CTL_DDI4,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc icl_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = ICL_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 2",
		.करोमुख्यs = ICL_PW_2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_2,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_2,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "power well 3",
		.करोमुख्यs = ICL_PW_3_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = ICL_DISP_PW_3,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_3,
			.hsw.irq_pipe_mask = BIT(PIPE_B),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI A IO",
		.करोमुख्यs = ICL_DDI_IO_A_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI B IO",
		.करोमुख्यs = ICL_DDI_IO_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI C IO",
		.करोमुख्यs = ICL_DDI_IO_C_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_C,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI D IO",
		.करोमुख्यs = ICL_DDI_IO_D_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_D,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI E IO",
		.करोमुख्यs = ICL_DDI_IO_E_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_E,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI F IO",
		.करोमुख्यs = ICL_DDI_IO_F_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_F,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX A",
		.करोमुख्यs = ICL_AUX_A_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX B",
		.करोमुख्यs = ICL_AUX_B_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX C TC1",
		.करोमुख्यs = ICL_AUX_C_TC1_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_C,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX D TC2",
		.करोमुख्यs = ICL_AUX_D_TC2_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_D,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX E TC3",
		.करोमुख्यs = ICL_AUX_E_TC3_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_E,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX F TC4",
		.करोमुख्यs = ICL_AUX_F_TC4_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_F,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX C TBT1",
		.करोमुख्यs = ICL_AUX_C_TBT1_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_TBT1,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX D TBT2",
		.करोमुख्यs = ICL_AUX_D_TBT2_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_TBT2,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX E TBT3",
		.करोमुख्यs = ICL_AUX_E_TBT3_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_TBT3,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX F TBT4",
		.करोमुख्यs = ICL_AUX_F_TBT4_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_TBT4,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "power well 4",
		.करोमुख्यs = ICL_PW_4_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_4,
			.hsw.has_fuses = true,
			.hsw.irq_pipe_mask = BIT(PIPE_C),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम
tgl_tc_cold_request(काष्ठा drm_i915_निजी *i915, bool block)
अणु
	u8 tries = 0;
	पूर्णांक ret;

	जबतक (1) अणु
		u32 low_val;
		u32 high_val = 0;

		अगर (block)
			low_val = TGL_PCODE_EXIT_TCCOLD_DATA_L_BLOCK_REQ;
		अन्यथा
			low_val = TGL_PCODE_EXIT_TCCOLD_DATA_L_UNBLOCK_REQ;

		/*
		 * Spec states that we should समयout the request after 200us
		 * but the function below will समयout after 500us
		 */
		ret = sandybridge_pcode_पढ़ो(i915, TGL_PCODE_TCCOLD, &low_val,
					     &high_val);
		अगर (ret == 0) अणु
			अगर (block &&
			    (low_val & TGL_PCODE_EXIT_TCCOLD_DATA_L_EXIT_FAILED))
				ret = -EIO;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (++tries == 3)
			अवरोध;

		msleep(1);
	पूर्ण

	अगर (ret)
		drm_err(&i915->drm, "TC cold %sblock failed\n",
			block ? "" : "un");
	अन्यथा
		drm_dbg_kms(&i915->drm, "TC cold %sblock succeeded\n",
			    block ? "" : "un");
पूर्ण

अटल व्योम
tgl_tc_cold_off_घातer_well_enable(काष्ठा drm_i915_निजी *i915,
				  काष्ठा i915_घातer_well *घातer_well)
अणु
	tgl_tc_cold_request(i915, true);
पूर्ण

अटल व्योम
tgl_tc_cold_off_घातer_well_disable(काष्ठा drm_i915_निजी *i915,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	tgl_tc_cold_request(i915, false);
पूर्ण

अटल व्योम
tgl_tc_cold_off_घातer_well_sync_hw(काष्ठा drm_i915_निजी *i915,
				   काष्ठा i915_घातer_well *घातer_well)
अणु
	अगर (घातer_well->count > 0)
		tgl_tc_cold_off_घातer_well_enable(i915, घातer_well);
	अन्यथा
		tgl_tc_cold_off_घातer_well_disable(i915, घातer_well);
पूर्ण

अटल bool
tgl_tc_cold_off_घातer_well_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
				      काष्ठा i915_घातer_well *घातer_well)
अणु
	/*
	 * Not the correctly implementation but there is no way to just पढ़ो it
	 * from PCODE, so वापसing count to aव्योम state mismatch errors
	 */
	वापस घातer_well->count;
पूर्ण

अटल स्थिर काष्ठा i915_घातer_well_ops tgl_tc_cold_off_ops = अणु
	.sync_hw = tgl_tc_cold_off_घातer_well_sync_hw,
	.enable = tgl_tc_cold_off_घातer_well_enable,
	.disable = tgl_tc_cold_off_घातer_well_disable,
	.is_enabled = tgl_tc_cold_off_घातer_well_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc tgl_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = TGL_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 2",
		.करोमुख्यs = TGL_PW_2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_2,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_2,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "power well 3",
		.करोमुख्यs = TGL_PW_3_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = ICL_DISP_PW_3,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_3,
			.hsw.irq_pipe_mask = BIT(PIPE_B),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI A IO",
		.करोमुख्यs = ICL_DDI_IO_A_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_A,
		पूर्ण
	पूर्ण,
	अणु
		.name = "DDI B IO",
		.करोमुख्यs = ICL_DDI_IO_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_B,
		पूर्ण
	पूर्ण,
	अणु
		.name = "DDI C IO",
		.करोमुख्यs = ICL_DDI_IO_C_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_C,
		पूर्ण
	पूर्ण,
	अणु
		.name = "DDI IO TC1",
		.करोमुख्यs = TGL_DDI_IO_TC1_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI IO TC2",
		.करोमुख्यs = TGL_DDI_IO_TC2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC2,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI IO TC3",
		.करोमुख्यs = TGL_DDI_IO_TC3_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC3,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI IO TC4",
		.करोमुख्यs = TGL_DDI_IO_TC4_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC4,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI IO TC5",
		.करोमुख्यs = TGL_DDI_IO_TC5_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC5,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI IO TC6",
		.करोमुख्यs = TGL_DDI_IO_TC6_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC6,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "TC cold off",
		.करोमुख्यs = TGL_TC_COLD_OFF_POWER_DOMAINS,
		.ops = &tgl_tc_cold_off_ops,
		.id = TGL_DISP_PW_TC_COLD_OFF,
	पूर्ण,
	अणु
		.name = "AUX A",
		.करोमुख्यs = TGL_AUX_A_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX B",
		.करोमुख्यs = TGL_AUX_B_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX C",
		.करोमुख्यs = TGL_AUX_C_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_C,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC1",
		.करोमुख्यs = TGL_AUX_IO_USBC1_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC1,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC2",
		.करोमुख्यs = TGL_AUX_IO_USBC2_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC2,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC3",
		.करोमुख्यs = TGL_AUX_IO_USBC3_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC3,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC4",
		.करोमुख्यs = TGL_AUX_IO_USBC4_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC4,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC5",
		.करोमुख्यs = TGL_AUX_IO_USBC5_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC5,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC6",
		.करोमुख्यs = TGL_AUX_IO_USBC6_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC6,
			.hsw.is_tc_tbt = false,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX TBT1",
		.करोमुख्यs = TGL_AUX_IO_TBT1_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TBT1,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX TBT2",
		.करोमुख्यs = TGL_AUX_IO_TBT2_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TBT2,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX TBT3",
		.करोमुख्यs = TGL_AUX_IO_TBT3_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TBT3,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX TBT4",
		.करोमुख्यs = TGL_AUX_IO_TBT4_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TBT4,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX TBT5",
		.करोमुख्यs = TGL_AUX_IO_TBT5_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TBT5,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX TBT6",
		.करोमुख्यs = TGL_AUX_IO_TBT6_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TBT6,
			.hsw.is_tc_tbt = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "power well 4",
		.करोमुख्यs = TGL_PW_4_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_4,
			.hsw.has_fuses = true,
			.hsw.irq_pipe_mask = BIT(PIPE_C),
		पूर्ण
	पूर्ण,
	अणु
		.name = "power well 5",
		.करोमुख्यs = TGL_PW_5_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_PW_5,
			.hsw.has_fuses = true,
			.hsw.irq_pipe_mask = BIT(PIPE_D),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i915_घातer_well_desc rkl_घातer_wells[] = अणु
	अणु
		.name = "always-on",
		.always_on = true,
		.करोमुख्यs = POWER_DOMAIN_MASK,
		.ops = &i9xx_always_on_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
	पूर्ण,
	अणु
		.name = "power well 1",
		/* Handled by the DMC firmware */
		.always_on = true,
		.करोमुख्यs = 0,
		.ops = &hsw_घातer_well_ops,
		.id = SKL_DISP_PW_1,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_1,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DC off",
		.करोमुख्यs = RKL_DISPLAY_DC_OFF_POWER_DOMAINS,
		.ops = &gen9_dc_off_घातer_well_ops,
		.id = SKL_DISP_DC_OFF,
	पूर्ण,
	अणु
		.name = "power well 3",
		.करोमुख्यs = RKL_PW_3_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = ICL_DISP_PW_3,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_3,
			.hsw.irq_pipe_mask = BIT(PIPE_B),
			.hsw.has_vga = true,
			.hsw.has_fuses = true,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "power well 4",
		.करोमुख्यs = RKL_PW_4_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &hsw_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_PW_4,
			.hsw.has_fuses = true,
			.hsw.irq_pipe_mask = BIT(PIPE_C),
		पूर्ण
	पूर्ण,
	अणु
		.name = "DDI A IO",
		.करोमुख्यs = ICL_DDI_IO_A_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_A,
		पूर्ण
	पूर्ण,
	अणु
		.name = "DDI B IO",
		.करोमुख्यs = ICL_DDI_IO_B_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_DDI_B,
		पूर्ण
	पूर्ण,
	अणु
		.name = "DDI IO TC1",
		.करोमुख्यs = TGL_DDI_IO_TC1_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DDI IO TC2",
		.करोमुख्यs = TGL_DDI_IO_TC2_POWER_DOMAINS,
		.ops = &hsw_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_ddi_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_DDI_TC2,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX A",
		.करोमुख्यs = ICL_AUX_A_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_A,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX B",
		.करोमुख्यs = ICL_AUX_B_IO_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = ICL_PW_CTL_IDX_AUX_B,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC1",
		.करोमुख्यs = TGL_AUX_IO_USBC1_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC1,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "AUX USBC2",
		.करोमुख्यs = TGL_AUX_IO_USBC2_POWER_DOMAINS,
		.ops = &icl_aux_घातer_well_ops,
		.id = DISP_PW_ID_NONE,
		अणु
			.hsw.regs = &icl_aux_घातer_well_regs,
			.hsw.idx = TGL_PW_CTL_IDX_AUX_TC2,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
sanitize_disable_घातer_well_option(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				   पूर्णांक disable_घातer_well)
अणु
	अगर (disable_घातer_well >= 0)
		वापस !!disable_घातer_well;

	वापस 1;
पूर्ण

अटल u32 get_allowed_dc_mask(स्थिर काष्ठा drm_i915_निजी *dev_priv,
			       पूर्णांक enable_dc)
अणु
	u32 mask;
	पूर्णांक requested_dc;
	पूर्णांक max_dc;

	अगर (IS_DG1(dev_priv))
		max_dc = 3;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12)
		max_dc = 4;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv) || IS_GEN9_BC(dev_priv))
		max_dc = 2;
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		max_dc = 1;
	अन्यथा
		max_dc = 0;

	/*
	 * DC9 has a separate HW flow from the rest of the DC states,
	 * not depending on the DMC firmware. It's needed by प्रणाली
	 * suspend/resume, so allow it unconditionally.
	 */
	mask = IS_GEN9_LP(dev_priv) || DISPLAY_VER(dev_priv) >= 11 ?
	       DC_STATE_EN_DC9 : 0;

	अगर (!dev_priv->params.disable_घातer_well)
		max_dc = 0;

	अगर (enable_dc >= 0 && enable_dc <= max_dc) अणु
		requested_dc = enable_dc;
	पूर्ण अन्यथा अगर (enable_dc == -1) अणु
		requested_dc = max_dc;
	पूर्ण अन्यथा अगर (enable_dc > max_dc && enable_dc <= 4) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Adjusting requested max DC state (%d->%d)\n",
			    enable_dc, max_dc);
		requested_dc = max_dc;
	पूर्ण अन्यथा अणु
		drm_err(&dev_priv->drm,
			"Unexpected value for enable_dc (%d)\n", enable_dc);
		requested_dc = max_dc;
	पूर्ण

	चयन (requested_dc) अणु
	हाल 4:
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC6;
		अवरोध;
	हाल 3:
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC5;
		अवरोध;
	हाल 2:
		mask |= DC_STATE_EN_UPTO_DC6;
		अवरोध;
	हाल 1:
		mask |= DC_STATE_EN_UPTO_DC5;
		अवरोध;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "Allowed DC state mask %02x\n", mask);

	वापस mask;
पूर्ण

अटल पूर्णांक
__set_घातer_wells(काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs,
		  स्थिर काष्ठा i915_घातer_well_desc *घातer_well_descs,
		  पूर्णांक घातer_well_descs_sz, u64 skip_mask)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(घातer_करोमुख्यs,
						     काष्ठा drm_i915_निजी,
						     घातer_करोमुख्यs);
	u64 घातer_well_ids = 0;
	पूर्णांक घातer_well_count = 0;
	पूर्णांक i, plt_idx = 0;

	क्रम (i = 0; i < घातer_well_descs_sz; i++)
		अगर (!(BIT_ULL(घातer_well_descs[i].id) & skip_mask))
			घातer_well_count++;

	घातer_करोमुख्यs->घातer_well_count = घातer_well_count;
	घातer_करोमुख्यs->घातer_wells =
				kसुस्मृति(घातer_well_count,
					माप(*घातer_करोमुख्यs->घातer_wells),
					GFP_KERNEL);
	अगर (!घातer_करोमुख्यs->घातer_wells)
		वापस -ENOMEM;

	क्रम (i = 0; i < घातer_well_descs_sz; i++) अणु
		क्रमागत i915_घातer_well_id id = घातer_well_descs[i].id;

		अगर (BIT_ULL(id) & skip_mask)
			जारी;

		घातer_करोमुख्यs->घातer_wells[plt_idx++].desc =
			&घातer_well_descs[i];

		अगर (id == DISP_PW_ID_NONE)
			जारी;

		drm_WARN_ON(&i915->drm, id >= माप(घातer_well_ids) * 8);
		drm_WARN_ON(&i915->drm, घातer_well_ids & BIT_ULL(id));
		घातer_well_ids |= BIT_ULL(id);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा set_घातer_wells_mask(घातer_करोमुख्यs, __घातer_well_descs, skip_mask) \
	__set_घातer_wells(घातer_करोमुख्यs, __घातer_well_descs, \
			  ARRAY_SIZE(__घातer_well_descs), skip_mask)

#घोषणा set_घातer_wells(घातer_करोमुख्यs, __घातer_well_descs) \
	set_घातer_wells_mask(घातer_करोमुख्यs, __घातer_well_descs, 0)

/**
 * पूर्णांकel_घातer_करोमुख्यs_init - initializes the घातer करोमुख्य काष्ठाures
 * @dev_priv: i915 device instance
 *
 * Initializes the घातer करोमुख्य काष्ठाures क्रम @dev_priv depending upon the
 * supported platक्रमm.
 */
पूर्णांक पूर्णांकel_घातer_करोमुख्यs_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	पूर्णांक err;

	dev_priv->params.disable_घातer_well =
		sanitize_disable_घातer_well_option(dev_priv,
						   dev_priv->params.disable_घातer_well);
	dev_priv->csr.allowed_dc_mask =
		get_allowed_dc_mask(dev_priv, dev_priv->params.enable_dc);

	dev_priv->csr.target_dc_state =
		sanitize_target_dc_state(dev_priv, DC_STATE_EN_UPTO_DC6);

	BUILD_BUG_ON(POWER_DOMAIN_NUM > 64);

	mutex_init(&घातer_करोमुख्यs->lock);

	INIT_DELAYED_WORK(&घातer_करोमुख्यs->async_put_work,
			  पूर्णांकel_display_घातer_put_async_work);

	/*
	 * The enabling order will be from lower to higher indexed wells,
	 * the disabling order is reversed.
	 */
	अगर (IS_ALDERLAKE_S(dev_priv) || IS_DG1(dev_priv)) अणु
		err = set_घातer_wells_mask(घातer_करोमुख्यs, tgl_घातer_wells,
					   BIT_ULL(TGL_DISP_PW_TC_COLD_OFF));
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, rkl_घातer_wells);
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 12)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, tgl_घातer_wells);
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, icl_घातer_wells);
	पूर्ण अन्यथा अगर (IS_CNL_WITH_PORT_F(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, cnl_घातer_wells);
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		err = set_घातer_wells_mask(घातer_करोमुख्यs, cnl_घातer_wells,
					   BIT_ULL(CNL_DISP_PW_DDI_F_IO) |
					   BIT_ULL(CNL_DISP_PW_DDI_F_AUX));
	पूर्ण अन्यथा अगर (IS_GEMINILAKE(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, glk_घातer_wells);
	पूर्ण अन्यथा अगर (IS_BROXTON(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, bxt_घातer_wells);
	पूर्ण अन्यथा अगर (IS_GEN9_BC(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, skl_घातer_wells);
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, chv_घातer_wells);
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, bdw_घातer_wells);
	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, hsw_घातer_wells);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, vlv_घातer_wells);
	पूर्ण अन्यथा अगर (IS_I830(dev_priv)) अणु
		err = set_घातer_wells(घातer_करोमुख्यs, i830_घातer_wells);
	पूर्ण अन्यथा अणु
		err = set_घातer_wells(घातer_करोमुख्यs, i9xx_always_on_घातer_well);
	पूर्ण

	वापस err;
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_cleanup - clean up घातer करोमुख्यs resources
 * @dev_priv: i915 device instance
 *
 * Release any resources acquired by पूर्णांकel_घातer_करोमुख्यs_init()
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_cleanup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	kमुक्त(dev_priv->घातer_करोमुख्यs.घातer_wells);
पूर्ण

अटल व्योम पूर्णांकel_घातer_करोमुख्यs_sync_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *घातer_well;

	mutex_lock(&घातer_करोमुख्यs->lock);
	क्रम_each_घातer_well(dev_priv, घातer_well) अणु
		घातer_well->desc->ops->sync_hw(dev_priv, घातer_well);
		घातer_well->hw_enabled =
			घातer_well->desc->ops->is_enabled(dev_priv, घातer_well);
	पूर्ण
	mutex_unlock(&घातer_करोमुख्यs->lock);
पूर्ण

अटल व्योम gen9_dbuf_slice_set(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत dbuf_slice slice, bool enable)
अणु
	i915_reg_t reg = DBUF_CTL_S(slice);
	bool state;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (enable)
		val |= DBUF_POWER_REQUEST;
	अन्यथा
		val &= ~DBUF_POWER_REQUEST;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(10);

	state = पूर्णांकel_de_पढ़ो(dev_priv, reg) & DBUF_POWER_STATE;
	drm_WARN(&dev_priv->drm, enable != state,
		 "DBuf slice %d power %s timeout!\n",
		 slice, enable ? "enable" : "disable");
पूर्ण

व्योम gen9_dbuf_slices_update(काष्ठा drm_i915_निजी *dev_priv,
			     u8 req_slices)
अणु
	पूर्णांक num_slices = INTEL_INFO(dev_priv)->num_supported_dbuf_slices;
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	क्रमागत dbuf_slice slice;

	drm_WARN(&dev_priv->drm, req_slices & ~(BIT(num_slices) - 1),
		 "Invalid set of dbuf slices (0x%x) requested (num dbuf slices %d)\n",
		 req_slices, num_slices);

	drm_dbg_kms(&dev_priv->drm, "Updating dbuf slices to 0x%x\n",
		    req_slices);

	/*
	 * Might be running this in parallel to gen9_dc_off_घातer_well_enable
	 * being called from पूर्णांकel_dp_detect क्रम instance,
	 * which causes निश्चितion triggered by race condition,
	 * as gen9_निश्चित_dbuf_enabled might preempt this when रेजिस्टरs
	 * were alपढ़ोy updated, जबतक dev_priv was not.
	 */
	mutex_lock(&घातer_करोमुख्यs->lock);

	क्रम (slice = DBUF_S1; slice < num_slices; slice++)
		gen9_dbuf_slice_set(dev_priv, slice, req_slices & BIT(slice));

	dev_priv->dbuf.enabled_slices = req_slices;

	mutex_unlock(&घातer_करोमुख्यs->lock);
पूर्ण

अटल व्योम gen9_dbuf_enable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	dev_priv->dbuf.enabled_slices =
		पूर्णांकel_enabled_dbuf_slices_mask(dev_priv);

	/*
	 * Just घातer up at least 1 slice, we will
	 * figure out later which slices we have and what we need.
	 */
	gen9_dbuf_slices_update(dev_priv, BIT(DBUF_S1) |
				dev_priv->dbuf.enabled_slices);
पूर्ण

अटल व्योम gen9_dbuf_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen9_dbuf_slices_update(dev_priv, 0);
पूर्ण

अटल व्योम gen12_dbuf_slices_config(काष्ठा drm_i915_निजी *dev_priv)
अणु
	स्थिर पूर्णांक num_slices = INTEL_INFO(dev_priv)->num_supported_dbuf_slices;
	क्रमागत dbuf_slice slice;

	क्रम (slice = DBUF_S1; slice < (DBUF_S1 + num_slices); slice++)
		पूर्णांकel_de_rmw(dev_priv, DBUF_CTL_S(slice),
			     DBUF_TRACKER_STATE_SERVICE_MASK,
			     DBUF_TRACKER_STATE_SERVICE(8));
पूर्ण

अटल व्योम icl_mbus_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अचिन्हित दीर्घ abox_regs = INTEL_INFO(dev_priv)->abox_mask;
	u32 mask, val, i;

	mask = MBUS_ABOX_BT_CREDIT_POOL1_MASK |
		MBUS_ABOX_BT_CREDIT_POOL2_MASK |
		MBUS_ABOX_B_CREDIT_MASK |
		MBUS_ABOX_BW_CREDIT_MASK;
	val = MBUS_ABOX_BT_CREDIT_POOL1(16) |
		MBUS_ABOX_BT_CREDIT_POOL2(16) |
		MBUS_ABOX_B_CREDIT(1) |
		MBUS_ABOX_BW_CREDIT(1);

	/*
	 * gen12 platक्रमms that use abox1 and abox2 क्रम pixel data पढ़ोs still
	 * expect us to program the abox_ctl0 रेजिस्टर as well, even though
	 * we करोn't have to program other instance-0 रेजिस्टरs like BW_BUDDY.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 12))
		abox_regs |= BIT(0);

	क्रम_each_set_bit(i, &abox_regs, माप(abox_regs))
		पूर्णांकel_de_rmw(dev_priv, MBUS_ABOX_CTL(i), mask, val);
पूर्ण

अटल व्योम hsw_निश्चित_cdclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);

	/*
	 * The LCPLL रेजिस्टर should be turned on by the BIOS. For now
	 * let's just check its state and prपूर्णांक errors in हाल
	 * something is wrong.  Don't even try to turn it on.
	 */

	अगर (val & LCPLL_CD_SOURCE_FCLK)
		drm_err(&dev_priv->drm, "CDCLK source is not LCPLL\n");

	अगर (val & LCPLL_PLL_DISABLE)
		drm_err(&dev_priv->drm, "LCPLL is disabled\n");

	अगर ((val & LCPLL_REF_MASK) != LCPLL_REF_NON_SSC)
		drm_err(&dev_priv->drm, "LCPLL not using non-SSC reference\n");
पूर्ण

अटल व्योम निश्चित_can_disable_lcpll(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(dev, crtc)
		I915_STATE_WARN(crtc->active, "CRTC for pipe %c enabled\n",
				pipe_name(crtc->pipe));

	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, HSW_PWR_WELL_CTL2),
			"Display power well on\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, SPLL_CTL) & SPLL_PLL_ENABLE,
			"SPLL enabled\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, WRPLL_CTL(0)) & WRPLL_PLL_ENABLE,
			"WRPLL1 enabled\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, WRPLL_CTL(1)) & WRPLL_PLL_ENABLE,
			"WRPLL2 enabled\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, PP_STATUS(0)) & PP_ON,
			"Panel power on\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_CPU_CTL2) & BLM_PWM_ENABLE,
			"CPU PWM1 enabled\n");
	अगर (IS_HASWELL(dev_priv))
		I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, HSW_BLC_PWM2_CTL) & BLM_PWM_ENABLE,
				"CPU PWM2 enabled\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, BLC_PWM_PCH_CTL1) & BLM_PCH_PWM_ENABLE,
			"PCH PWM1 enabled\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, UTIL_PIN_CTL) & UTIL_PIN_ENABLE,
			"Utility pin enabled\n");
	I915_STATE_WARN(पूर्णांकel_de_पढ़ो(dev_priv, PCH_GTC_CTL) & PCH_GTC_ENABLE,
			"PCH GTC enabled\n");

	/*
	 * In theory we can still leave IRQs enabled, as दीर्घ as only the HPD
	 * पूर्णांकerrupts reमुख्य enabled. We used to check क्रम that, but since it's
	 * gen-specअगरic and since we only disable LCPLL after we fully disable
	 * the पूर्णांकerrupts, the check below should be enough.
	 */
	I915_STATE_WARN(पूर्णांकel_irqs_enabled(dev_priv), "IRQs enabled\n");
पूर्ण

अटल u32 hsw_पढ़ो_dcomp(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_HASWELL(dev_priv))
		वापस पूर्णांकel_de_पढ़ो(dev_priv, D_COMP_HSW);
	अन्यथा
		वापस पूर्णांकel_de_पढ़ो(dev_priv, D_COMP_BDW);
पूर्ण

अटल व्योम hsw_ग_लिखो_dcomp(काष्ठा drm_i915_निजी *dev_priv, u32 val)
अणु
	अगर (IS_HASWELL(dev_priv)) अणु
		अगर (sandybridge_pcode_ग_लिखो(dev_priv,
					    GEN6_PCODE_WRITE_D_COMP, val))
			drm_dbg_kms(&dev_priv->drm,
				    "Failed to write to D_COMP\n");
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, D_COMP_BDW, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, D_COMP_BDW);
	पूर्ण
पूर्ण

/*
 * This function implements pieces of two sequences from BSpec:
 * - Sequence क्रम display software to disable LCPLL
 * - Sequence क्रम display software to allow package C8+
 * The steps implemented here are just the steps that actually touch the LCPLL
 * रेजिस्टर. Callers should take care of disabling all the display engine
 * functions, करोing the mode unset, fixing पूर्णांकerrupts, etc.
 */
अटल व्योम hsw_disable_lcpll(काष्ठा drm_i915_निजी *dev_priv,
			      bool चयन_to_fclk, bool allow_घातer_करोwn)
अणु
	u32 val;

	निश्चित_can_disable_lcpll(dev_priv);

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);

	अगर (चयन_to_fclk) अणु
		val |= LCPLL_CD_SOURCE_FCLK;
		पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);

		अगर (रुको_क्रम_us(पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL) &
				LCPLL_CD_SOURCE_FCLK_DONE, 1))
			drm_err(&dev_priv->drm, "Switching to FCLK failed\n");

		val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	पूर्ण

	val |= LCPLL_PLL_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, LCPLL_CTL);

	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, LCPLL_CTL, LCPLL_PLL_LOCK, 1))
		drm_err(&dev_priv->drm, "LCPLL still locked\n");

	val = hsw_पढ़ो_dcomp(dev_priv);
	val |= D_COMP_COMP_DISABLE;
	hsw_ग_लिखो_dcomp(dev_priv, val);
	ndelay(100);

	अगर (रुको_क्रम((hsw_पढ़ो_dcomp(dev_priv) &
		      D_COMP_RCOMP_IN_PROGRESS) == 0, 1))
		drm_err(&dev_priv->drm, "D_COMP RCOMP still in progress\n");

	अगर (allow_घातer_करोwn) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
		val |= LCPLL_POWER_DOWN_ALLOW;
		पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, LCPLL_CTL);
	पूर्ण
पूर्ण

/*
 * Fully restores LCPLL, disallowing घातer करोwn and चयनing back to LCPLL
 * source.
 */
अटल व्योम hsw_restore_lcpll(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);

	अगर ((val & (LCPLL_PLL_LOCK | LCPLL_PLL_DISABLE | LCPLL_CD_SOURCE_FCLK |
		    LCPLL_POWER_DOWN_ALLOW)) == LCPLL_PLL_LOCK)
		वापस;

	/*
	 * Make sure we're not on PC8 state beक्रमe disabling PC8, otherwise
	 * we'll hang the machine. To prevent PC8 state, just enable क्रमce_wake.
	 */
	पूर्णांकel_uncore_क्रमcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	अगर (val & LCPLL_POWER_DOWN_ALLOW) अणु
		val &= ~LCPLL_POWER_DOWN_ALLOW;
		पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, LCPLL_CTL);
	पूर्ण

	val = hsw_पढ़ो_dcomp(dev_priv);
	val |= D_COMP_COMP_FORCE;
	val &= ~D_COMP_COMP_DISABLE;
	hsw_ग_लिखो_dcomp(dev_priv, val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	val &= ~LCPLL_PLL_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, LCPLL_CTL, LCPLL_PLL_LOCK, 5))
		drm_err(&dev_priv->drm, "LCPLL not locked yet\n");

	अगर (val & LCPLL_CD_SOURCE_FCLK) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
		val &= ~LCPLL_CD_SOURCE_FCLK;
		पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);

		अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL) &
				 LCPLL_CD_SOURCE_FCLK_DONE) == 0, 1))
			drm_err(&dev_priv->drm,
				"Switching back to LCPLL failed\n");
	पूर्ण

	पूर्णांकel_uncore_क्रमcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);

	पूर्णांकel_update_cdclk(dev_priv);
	पूर्णांकel_dump_cdclk_config(&dev_priv->cdclk.hw, "Current CDCLK");
पूर्ण

/*
 * Package states C8 and deeper are really deep PC states that can only be
 * reached when all the devices on the प्रणाली allow it, so even अगर the graphics
 * device allows PC8+, it करोesn't mean the प्रणाली will actually get to these
 * states. Our driver only allows PC8+ when going पूर्णांकo runसमय PM.
 *
 * The requirements क्रम PC8+ are that all the outमाला_दो are disabled, the घातer
 * well is disabled and most पूर्णांकerrupts are disabled, and these are also
 * requirements क्रम runसमय PM. When these conditions are met, we manually करो
 * the other conditions: disable the पूर्णांकerrupts, घड़ीs and चयन LCPLL refclk
 * to Fclk. If we're in PC8+ and we get an non-hotplug पूर्णांकerrupt, we can hard
 * hang the machine.
 *
 * When we really reach PC8 or deeper states (not just when we allow it) we lose
 * the state of some रेजिस्टरs, so when we come back from PC8+ we need to
 * restore this state. We करोn't get into PC8+ if we're not in RC6, so we don't
 * need to take care of the रेजिस्टरs kept by RC6. Notice that this happens even
 * अगर we करोn't put the device in PCI D3 state (which is what currently happens
 * because of the runसमय PM support).
 *
 * For more, पढ़ो "Display Sequences for Package C8" on the hardware
 * करोcumentation.
 */
अटल व्योम hsw_enable_pc8(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "Enabling package C8+\n");

	अगर (HAS_PCH_LPT_LP(dev_priv)) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_DSPCLK_GATE_D);
		val &= ~PCH_LP_PARTITION_LEVEL_DISABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_DSPCLK_GATE_D, val);
	पूर्ण

	lpt_disable_clkout_dp(dev_priv);
	hsw_disable_lcpll(dev_priv, true, true);
पूर्ण

अटल व्योम hsw_disable_pc8(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "Disabling package C8+\n");

	hsw_restore_lcpll(dev_priv);
	पूर्णांकel_init_pch_refclk(dev_priv);

	अगर (HAS_PCH_LPT_LP(dev_priv)) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_DSPCLK_GATE_D);
		val |= PCH_LP_PARTITION_LEVEL_DISABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_DSPCLK_GATE_D, val);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pch_reset_handshake(काष्ठा drm_i915_निजी *dev_priv,
				      bool enable)
अणु
	i915_reg_t reg;
	u32 reset_bits, val;

	अगर (IS_IVYBRIDGE(dev_priv)) अणु
		reg = GEN7_MSG_CTL;
		reset_bits = WAIT_FOR_PCH_FLR_ACK | WAIT_FOR_PCH_RESET_ACK;
	पूर्ण अन्यथा अणु
		reg = HSW_NDE_RSTWRN_OPT;
		reset_bits = RESET_PCH_HANDSHAKE_ENABLE;
	पूर्ण

	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

	अगर (enable)
		val |= reset_bits;
	अन्यथा
		val &= ~reset_bits;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
पूर्ण

अटल व्योम skl_display_core_init(काष्ठा drm_i915_निजी *dev_priv,
				  bool resume)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* enable PCH reset handshake */
	पूर्णांकel_pch_reset_handshake(dev_priv, !HAS_PCH_NOP(dev_priv));

	/* enable PG1 and Misc I/O */
	mutex_lock(&घातer_करोमुख्यs->lock);

	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_enable(dev_priv, well);

	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_MISC_IO);
	पूर्णांकel_घातer_well_enable(dev_priv, well);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	पूर्णांकel_cdclk_init_hw(dev_priv);

	gen9_dbuf_enable(dev_priv);

	अगर (resume && dev_priv->csr.dmc_payload)
		पूर्णांकel_csr_load_program(dev_priv);
पूर्ण

अटल व्योम skl_display_core_uninit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_disable_dc_states(dev_priv);

	gen9_dbuf_disable(dev_priv);

	पूर्णांकel_cdclk_uninit_hw(dev_priv);

	/* The spec करोesn't call क्रम removing the reset handshake flag */
	/* disable PG1 and Misc I/O */

	mutex_lock(&घातer_करोमुख्यs->lock);

	/*
	 * BSpec says to keep the MISC IO घातer well enabled here, only
	 * हटाओ our request क्रम घातer well 1.
	 * Note that even though the driver's request is हटाओd घातer well 1
	 * may stay enabled after this due to DMC's own request on it.
	 */
	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_disable(dev_priv, well);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	usleep_range(10, 30);		/* 10 us delay per Bspec */
पूर्ण

अटल व्योम bxt_display_core_init(काष्ठा drm_i915_निजी *dev_priv, bool resume)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/*
	 * NDE_RSTWRN_OPT RST PCH Handshake En must always be 0b on BXT
	 * or अन्यथा the reset will hang because there is no PCH to respond.
	 * Move the handshake programming to initialization sequence.
	 * Previously was left up to BIOS.
	 */
	पूर्णांकel_pch_reset_handshake(dev_priv, false);

	/* Enable PG1 */
	mutex_lock(&घातer_करोमुख्यs->lock);

	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_enable(dev_priv, well);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	पूर्णांकel_cdclk_init_hw(dev_priv);

	gen9_dbuf_enable(dev_priv);

	अगर (resume && dev_priv->csr.dmc_payload)
		पूर्णांकel_csr_load_program(dev_priv);
पूर्ण

अटल व्योम bxt_display_core_uninit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_disable_dc_states(dev_priv);

	gen9_dbuf_disable(dev_priv);

	पूर्णांकel_cdclk_uninit_hw(dev_priv);

	/* The spec करोesn't call क्रम removing the reset handshake flag */

	/*
	 * Disable PW1 (PG1).
	 * Note that even though the driver's request is हटाओd घातer well 1
	 * may stay enabled after this due to DMC's own request on it.
	 */
	mutex_lock(&घातer_करोमुख्यs->lock);

	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_disable(dev_priv, well);

	mutex_unlock(&घातer_करोमुख्यs->lock);

	usleep_range(10, 30);		/* 10 us delay per Bspec */
पूर्ण

अटल व्योम cnl_display_core_init(काष्ठा drm_i915_निजी *dev_priv, bool resume)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* 1. Enable PCH Reset Handshake */
	पूर्णांकel_pch_reset_handshake(dev_priv, !HAS_PCH_NOP(dev_priv));

	/* 2-3. */
	पूर्णांकel_combo_phy_init(dev_priv);

	/*
	 * 4. Enable Power Well 1 (PG1).
	 *    The AUX IO घातer wells will be enabled on demand.
	 */
	mutex_lock(&घातer_करोमुख्यs->lock);
	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_enable(dev_priv, well);
	mutex_unlock(&घातer_करोमुख्यs->lock);

	/* 5. Enable CD घड़ी */
	पूर्णांकel_cdclk_init_hw(dev_priv);

	/* 6. Enable DBUF */
	gen9_dbuf_enable(dev_priv);

	अगर (resume && dev_priv->csr.dmc_payload)
		पूर्णांकel_csr_load_program(dev_priv);
पूर्ण

अटल व्योम cnl_display_core_uninit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_disable_dc_states(dev_priv);

	/* 1. Disable all display engine functions -> aपढ़ोy करोne */

	/* 2. Disable DBUF */
	gen9_dbuf_disable(dev_priv);

	/* 3. Disable CD घड़ी */
	पूर्णांकel_cdclk_uninit_hw(dev_priv);

	/*
	 * 4. Disable Power Well 1 (PG1).
	 *    The AUX IO घातer wells are toggled on demand, so they are alपढ़ोy
	 *    disabled at this poपूर्णांक.
	 */
	mutex_lock(&घातer_करोमुख्यs->lock);
	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_disable(dev_priv, well);
	mutex_unlock(&घातer_करोमुख्यs->lock);

	usleep_range(10, 30);		/* 10 us delay per Bspec */

	/* 5. */
	पूर्णांकel_combo_phy_uninit(dev_priv);
पूर्ण

काष्ठा buddy_page_mask अणु
	u32 page_mask;
	u8 type;
	u8 num_channels;
पूर्ण;

अटल स्थिर काष्ठा buddy_page_mask tgl_buddy_page_masks[] = अणु
	अणु .num_channels = 1, .type = INTEL_DRAM_DDR4,   .page_mask = 0xF पूर्ण,
	अणु .num_channels = 1, .type = INTEL_DRAM_DDR5,	.page_mask = 0xF पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x1C पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x1C पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_DDR4,   .page_mask = 0x1F पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_DDR5,   .page_mask = 0x1E पूर्ण,
	अणु .num_channels = 4, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x38 पूर्ण,
	अणु .num_channels = 4, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x38 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा buddy_page_mask wa_1409767108_buddy_page_masks[] = अणु
	अणु .num_channels = 1, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x1 पूर्ण,
	अणु .num_channels = 1, .type = INTEL_DRAM_DDR4,   .page_mask = 0x1 पूर्ण,
	अणु .num_channels = 1, .type = INTEL_DRAM_DDR5,   .page_mask = 0x1 पूर्ण,
	अणु .num_channels = 1, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x1 पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x3 पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_DDR4,   .page_mask = 0x3 पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_DDR5,   .page_mask = 0x3 पूर्ण,
	अणु .num_channels = 2, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x3 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम tgl_bw_buddy_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत पूर्णांकel_dram_type type = dev_priv->dram_info.type;
	u8 num_channels = dev_priv->dram_info.num_channels;
	स्थिर काष्ठा buddy_page_mask *table;
	अचिन्हित दीर्घ abox_mask = INTEL_INFO(dev_priv)->abox_mask;
	पूर्णांक config, i;

	अगर (IS_ALDERLAKE_S(dev_priv) ||
	    IS_DG1_REVID(dev_priv, DG1_REVID_A0, DG1_REVID_A0) ||
	    IS_TGL_DISPLAY_STEP(dev_priv, STEP_A0, STEP_B0))
		/* Wa_1409767108:tgl,dg1,adl-s */
		table = wa_1409767108_buddy_page_masks;
	अन्यथा
		table = tgl_buddy_page_masks;

	क्रम (config = 0; table[config].page_mask != 0; config++)
		अगर (table[config].num_channels == num_channels &&
		    table[config].type == type)
			अवरोध;

	अगर (table[config].page_mask == 0) अणु
		drm_dbg(&dev_priv->drm,
			"Unknown memory configuration; disabling address buddy logic.\n");
		क्रम_each_set_bit(i, &abox_mask, माप(abox_mask))
			पूर्णांकel_de_ग_लिखो(dev_priv, BW_BUDDY_CTL(i),
				       BW_BUDDY_DISABLE);
	पूर्ण अन्यथा अणु
		क्रम_each_set_bit(i, &abox_mask, माप(abox_mask)) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, BW_BUDDY_PAGE_MASK(i),
				       table[config].page_mask);

			/* Wa_22010178259:tgl,rkl */
			पूर्णांकel_de_rmw(dev_priv, BW_BUDDY_CTL(i),
				     BW_BUDDY_TLB_REQ_TIMER_MASK,
				     BW_BUDDY_TLB_REQ_TIMER(0x8));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम icl_display_core_init(काष्ठा drm_i915_निजी *dev_priv,
				  bool resume)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;
	u32 val;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* Wa_14011294188:ehl,jsl,tgl,rkl,adl-s */
	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_JSP &&
	    INTEL_PCH_TYPE(dev_priv) < PCH_DG1)
		पूर्णांकel_de_rmw(dev_priv, SOUTH_DSPCLK_GATE_D, 0,
			     PCH_DPMGUNIT_CLOCK_GATE_DISABLE);

	/* 1. Enable PCH reset handshake. */
	पूर्णांकel_pch_reset_handshake(dev_priv, !HAS_PCH_NOP(dev_priv));

	/* 2. Initialize all combo phys */
	पूर्णांकel_combo_phy_init(dev_priv);

	/*
	 * 3. Enable Power Well 1 (PG1).
	 *    The AUX IO घातer wells will be enabled on demand.
	 */
	mutex_lock(&घातer_करोमुख्यs->lock);
	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_enable(dev_priv, well);
	mutex_unlock(&घातer_करोमुख्यs->lock);

	/* 4. Enable CDCLK. */
	पूर्णांकel_cdclk_init_hw(dev_priv);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		gen12_dbuf_slices_config(dev_priv);

	/* 5. Enable DBUF. */
	gen9_dbuf_enable(dev_priv);

	/* 6. Setup MBUS. */
	icl_mbus_init(dev_priv);

	/* 7. Program arbiter BW_BUDDY रेजिस्टरs */
	अगर (DISPLAY_VER(dev_priv) >= 12)
		tgl_bw_buddy_init(dev_priv);

	अगर (resume && dev_priv->csr.dmc_payload)
		पूर्णांकel_csr_load_program(dev_priv);

	/* Wa_14011508470 */
	अगर (IS_DISPLAY_VER(dev_priv, 12)) अणु
		val = DCPR_CLEAR_MEMSTAT_DIS | DCPR_SEND_RESP_IMM |
		      DCPR_MASK_LPMODE | DCPR_MASK_MAXLATENCY_MEMUP_CLR;
		पूर्णांकel_uncore_rmw(&dev_priv->uncore, GEN11_CHICKEN_DCPR_2, 0, val);
	पूर्ण
पूर्ण

अटल व्योम icl_display_core_uninit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &dev_priv->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *well;

	gen9_disable_dc_states(dev_priv);

	/* 1. Disable all display engine functions -> aपढ़ोy करोne */

	/* 2. Disable DBUF */
	gen9_dbuf_disable(dev_priv);

	/* 3. Disable CD घड़ी */
	पूर्णांकel_cdclk_uninit_hw(dev_priv);

	/*
	 * 4. Disable Power Well 1 (PG1).
	 *    The AUX IO घातer wells are toggled on demand, so they are alपढ़ोy
	 *    disabled at this poपूर्णांक.
	 */
	mutex_lock(&घातer_करोमुख्यs->lock);
	well = lookup_घातer_well(dev_priv, SKL_DISP_PW_1);
	पूर्णांकel_घातer_well_disable(dev_priv, well);
	mutex_unlock(&घातer_करोमुख्यs->lock);

	/* 5. */
	पूर्णांकel_combo_phy_uninit(dev_priv);
पूर्ण

अटल व्योम chv_phy_control_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_well *cmn_bc =
		lookup_घातer_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	काष्ठा i915_घातer_well *cmn_d =
		lookup_घातer_well(dev_priv, CHV_DISP_PW_DPIO_CMN_D);

	/*
	 * DISPLAY_PHY_CONTROL can get corrupted अगर पढ़ो. As a
	 * workaround never ever पढ़ो DISPLAY_PHY_CONTROL, and
	 * instead मुख्यtain a shaकरोw copy ourselves. Use the actual
	 * घातer well state and lane status to reस्थिरruct the
	 * expected initial value.
	 */
	dev_priv->chv_phy_control =
		PHY_LDO_SEQ_DELAY(PHY_LDO_DELAY_600NS, DPIO_PHY0) |
		PHY_LDO_SEQ_DELAY(PHY_LDO_DELAY_600NS, DPIO_PHY1) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY0, DPIO_CH0) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY0, DPIO_CH1) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY1, DPIO_CH0);

	/*
	 * If all lanes are disabled we leave the override disabled
	 * with all घातer करोwn bits cleared to match the state we
	 * would use after disabling the port. Otherwise enable the
	 * override and set the lane घातerकरोwn bits accding to the
	 * current lane status.
	 */
	अगर (cmn_bc->desc->ops->is_enabled(dev_priv, cmn_bc)) अणु
		u32 status = पूर्णांकel_de_पढ़ो(dev_priv, DPLL(PIPE_A));
		अचिन्हित पूर्णांक mask;

		mask = status & DPLL_PORTB_READY_MASK;
		अगर (mask == 0xf)
			mask = 0x0;
		अन्यथा
			dev_priv->chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH0);

		dev_priv->chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY0, DPIO_CH0);

		mask = (status & DPLL_PORTC_READY_MASK) >> 4;
		अगर (mask == 0xf)
			mask = 0x0;
		अन्यथा
			dev_priv->chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH1);

		dev_priv->chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY0, DPIO_CH1);

		dev_priv->chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(DPIO_PHY0);

		dev_priv->chv_phy_निश्चित[DPIO_PHY0] = false;
	पूर्ण अन्यथा अणु
		dev_priv->chv_phy_निश्चित[DPIO_PHY0] = true;
	पूर्ण

	अगर (cmn_d->desc->ops->is_enabled(dev_priv, cmn_d)) अणु
		u32 status = पूर्णांकel_de_पढ़ो(dev_priv, DPIO_PHY_STATUS);
		अचिन्हित पूर्णांक mask;

		mask = status & DPLL_PORTD_READY_MASK;

		अगर (mask == 0xf)
			mask = 0x0;
		अन्यथा
			dev_priv->chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY1, DPIO_CH0);

		dev_priv->chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY1, DPIO_CH0);

		dev_priv->chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(DPIO_PHY1);

		dev_priv->chv_phy_निश्चित[DPIO_PHY1] = false;
	पूर्ण अन्यथा अणु
		dev_priv->chv_phy_निश्चित[DPIO_PHY1] = true;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "Initial PHY_CONTROL=0x%08x\n",
		    dev_priv->chv_phy_control);

	/* Defer application of initial phy_control to enabling the घातerwell */
पूर्ण

अटल व्योम vlv_cmnlane_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा i915_घातer_well *cmn =
		lookup_घातer_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	काष्ठा i915_घातer_well *disp2d =
		lookup_घातer_well(dev_priv, VLV_DISP_PW_DISP2D);

	/* If the display might be alपढ़ोy active skip this */
	अगर (cmn->desc->ops->is_enabled(dev_priv, cmn) &&
	    disp2d->desc->ops->is_enabled(dev_priv, disp2d) &&
	    पूर्णांकel_de_पढ़ो(dev_priv, DPIO_CTL) & DPIO_CMNRST)
		वापस;

	drm_dbg_kms(&dev_priv->drm, "toggling display PHY side reset\n");

	/* cmnlane needs DPLL रेजिस्टरs */
	disp2d->desc->ops->enable(dev_priv, disp2d);

	/*
	 * From VLV2A0_DP_eDP_HDMI_DPIO_driver_vbios_notes_11.करोcx:
	 * Need to निश्चित and de-निश्चित PHY SB reset by gating the
	 * common lane घातer, then un-gating it.
	 * Simply ungating isn't enough to reset the PHY enough to get
	 * ports and lanes running.
	 */
	cmn->desc->ops->disable(dev_priv, cmn);
पूर्ण

अटल bool vlv_punit_is_घातer_gated(काष्ठा drm_i915_निजी *dev_priv, u32 reg0)
अणु
	bool ret;

	vlv_punit_get(dev_priv);
	ret = (vlv_punit_पढ़ो(dev_priv, reg0) & SSPM0_SSC_MASK) == SSPM0_SSC_PWR_GATE;
	vlv_punit_put(dev_priv);

	वापस ret;
पूर्ण

अटल व्योम निश्चित_ved_घातer_gated(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_WARN(&dev_priv->drm,
		 !vlv_punit_is_घातer_gated(dev_priv, PUNIT_REG_VEDSSPM0),
		 "VED not power gated\n");
पूर्ण

अटल व्योम निश्चित_isp_घातer_gated(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अटल स्थिर काष्ठा pci_device_id isp_ids[] = अणु
		अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x0f38)पूर्ण,
		अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x22b8)पूर्ण,
		अणुपूर्ण
	पूर्ण;

	drm_WARN(&dev_priv->drm, !pci_dev_present(isp_ids) &&
		 !vlv_punit_is_घातer_gated(dev_priv, PUNIT_REG_ISPSSPM0),
		 "ISP not power gated\n");
पूर्ण

अटल व्योम पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(काष्ठा drm_i915_निजी *dev_priv);

/**
 * पूर्णांकel_घातer_करोमुख्यs_init_hw - initialize hardware घातer करोमुख्य state
 * @i915: i915 device instance
 * @resume: Called from resume code paths or not
 *
 * This function initializes the hardware घातer करोमुख्य state and enables all
 * घातer wells beदीर्घing to the INIT घातer करोमुख्य. Power wells in other
 * करोमुख्यs (and not in the INIT करोमुख्य) are referenced or disabled by
 * पूर्णांकel_modeset_पढ़ोout_hw_state(). After that the reference count of each
 * घातer well must match its HW enabled state, see
 * पूर्णांकel_घातer_करोमुख्यs_verअगरy_state().
 *
 * It will वापस with घातer करोमुख्यs disabled (to be enabled later by
 * पूर्णांकel_घातer_करोमुख्यs_enable()) and must be paired with
 * पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ().
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_init_hw(काष्ठा drm_i915_निजी *i915, bool resume)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;

	घातer_करोमुख्यs->initializing = true;

	अगर (DISPLAY_VER(i915) >= 11) अणु
		icl_display_core_init(i915, resume);
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(i915)) अणु
		cnl_display_core_init(i915, resume);
	पूर्ण अन्यथा अगर (IS_GEN9_BC(i915)) अणु
		skl_display_core_init(i915, resume);
	पूर्ण अन्यथा अगर (IS_GEN9_LP(i915)) अणु
		bxt_display_core_init(i915, resume);
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(i915)) अणु
		mutex_lock(&घातer_करोमुख्यs->lock);
		chv_phy_control_init(i915);
		mutex_unlock(&घातer_करोमुख्यs->lock);
		निश्चित_isp_घातer_gated(i915);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(i915)) अणु
		mutex_lock(&घातer_करोमुख्यs->lock);
		vlv_cmnlane_wa(i915);
		mutex_unlock(&घातer_करोमुख्यs->lock);
		निश्चित_ved_घातer_gated(i915);
		निश्चित_isp_घातer_gated(i915);
	पूर्ण अन्यथा अगर (IS_BROADWELL(i915) || IS_HASWELL(i915)) अणु
		hsw_निश्चित_cdclk(i915);
		पूर्णांकel_pch_reset_handshake(i915, !HAS_PCH_NOP(i915));
	पूर्ण अन्यथा अगर (IS_IVYBRIDGE(i915)) अणु
		पूर्णांकel_pch_reset_handshake(i915, !HAS_PCH_NOP(i915));
	पूर्ण

	/*
	 * Keep all घातer wells enabled क्रम any dependent HW access during
	 * initialization and to make sure we keep BIOS enabled display HW
	 * resources घातered until display HW पढ़ोout is complete. We drop
	 * this reference in पूर्णांकel_घातer_करोमुख्यs_enable().
	 */
	drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->init_wakeref);
	घातer_करोमुख्यs->init_wakeref =
		पूर्णांकel_display_घातer_get(i915, POWER_DOMAIN_INIT);

	/* Disable घातer support अगर the user asked so. */
	अगर (!i915->params.disable_घातer_well) अणु
		drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->disable_wakeref);
		i915->घातer_करोमुख्यs.disable_wakeref = पूर्णांकel_display_घातer_get(i915,
									      POWER_DOMAIN_INIT);
	पूर्ण
	पूर्णांकel_घातer_करोमुख्यs_sync_hw(i915);

	घातer_करोमुख्यs->initializing = false;
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ - deinitialize hw घातer करोमुख्य state
 * @i915: i915 device instance
 *
 * De-initializes the display घातer करोमुख्य HW state. It also ensures that the
 * device stays घातered up so that the driver can be reloaded.
 *
 * It must be called with घातer करोमुख्यs alपढ़ोy disabled (after a call to
 * पूर्णांकel_घातer_करोमुख्यs_disable()) and must be paired with
 * पूर्णांकel_घातer_करोमुख्यs_init_hw().
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&i915->घातer_करोमुख्यs.init_wakeref);

	/* Remove the refcount we took to keep घातer well support disabled. */
	अगर (!i915->params.disable_घातer_well)
		पूर्णांकel_display_घातer_put(i915, POWER_DOMAIN_INIT,
					fetch_and_zero(&i915->घातer_करोमुख्यs.disable_wakeref));

	पूर्णांकel_display_घातer_flush_work_sync(i915);

	पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(i915);

	/* Keep the घातer well enabled, but cancel its rpm wakeref. */
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_enable - enable toggling of display घातer wells
 * @i915: i915 device instance
 *
 * Enable the ondemand enabling/disabling of the display घातer wells. Note that
 * घातer wells not beदीर्घing to POWER_DOMAIN_INIT are allowed to be toggled
 * only at specअगरic poपूर्णांकs of the display modeset sequence, thus they are not
 * affected by the पूर्णांकel_घातer_करोमुख्यs_enable()/disable() calls. The purpose
 * of these function is to keep the rest of घातer wells enabled until the end
 * of display HW पढ़ोout (which will acquire the घातer references reflecting
 * the current HW state).
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_enable(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&i915->घातer_करोमुख्यs.init_wakeref);

	पूर्णांकel_display_घातer_put(i915, POWER_DOMAIN_INIT, wakeref);
	पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(i915);
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_disable - disable toggling of display घातer wells
 * @i915: i915 device instance
 *
 * Disable the ondemand enabling/disabling of the display घातer wells. See
 * पूर्णांकel_घातer_करोमुख्यs_enable() क्रम which घातer wells this call controls.
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_disable(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;

	drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->init_wakeref);
	घातer_करोमुख्यs->init_wakeref =
		पूर्णांकel_display_घातer_get(i915, POWER_DOMAIN_INIT);

	पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(i915);
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_suspend - suspend घातer करोमुख्य state
 * @i915: i915 device instance
 * @suspend_mode: specअगरies the target suspend state (idle, mem, hibernation)
 *
 * This function prepares the hardware घातer करोमुख्य state beक्रमe entering
 * प्रणाली suspend.
 *
 * It must be called with घातer करोमुख्यs alपढ़ोy disabled (after a call to
 * पूर्णांकel_घातer_करोमुख्यs_disable()) and paired with पूर्णांकel_घातer_करोमुख्यs_resume().
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_suspend(काष्ठा drm_i915_निजी *i915,
				 क्रमागत i915_drm_suspend_mode suspend_mode)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;
	पूर्णांकel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&घातer_करोमुख्यs->init_wakeref);

	पूर्णांकel_display_घातer_put(i915, POWER_DOMAIN_INIT, wakeref);

	/*
	 * In हाल of suspend-to-idle (aka S0ix) on a DMC platक्रमm without DC9
	 * support करोn't manually deinit the घातer करोमुख्यs. This also means the
	 * CSR/DMC firmware will stay active, it will घातer करोwn any HW
	 * resources as required and also enable deeper प्रणाली घातer states
	 * that would be blocked अगर the firmware was inactive.
	 */
	अगर (!(i915->csr.allowed_dc_mask & DC_STATE_EN_DC9) &&
	    suspend_mode == I915_DRM_SUSPEND_IDLE &&
	    i915->csr.dmc_payload) अणु
		पूर्णांकel_display_घातer_flush_work(i915);
		पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(i915);
		वापस;
	पूर्ण

	/*
	 * Even अगर घातer well support was disabled we still want to disable
	 * घातer wells अगर घातer करोमुख्यs must be deinitialized क्रम suspend.
	 */
	अगर (!i915->params.disable_घातer_well)
		पूर्णांकel_display_घातer_put(i915, POWER_DOMAIN_INIT,
					fetch_and_zero(&i915->घातer_करोमुख्यs.disable_wakeref));

	पूर्णांकel_display_घातer_flush_work(i915);
	पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(i915);

	अगर (DISPLAY_VER(i915) >= 11)
		icl_display_core_uninit(i915);
	अन्यथा अगर (IS_CANNONLAKE(i915))
		cnl_display_core_uninit(i915);
	अन्यथा अगर (IS_GEN9_BC(i915))
		skl_display_core_uninit(i915);
	अन्यथा अगर (IS_GEN9_LP(i915))
		bxt_display_core_uninit(i915);

	घातer_करोमुख्यs->display_core_suspended = true;
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_resume - resume घातer करोमुख्य state
 * @i915: i915 device instance
 *
 * This function resume the hardware घातer करोमुख्य state during प्रणाली resume.
 *
 * It will वापस with घातer करोमुख्य support disabled (to be enabled later by
 * पूर्णांकel_घातer_करोमुख्यs_enable()) and must be paired with
 * पूर्णांकel_घातer_करोमुख्यs_suspend().
 */
व्योम पूर्णांकel_घातer_करोमुख्यs_resume(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;

	अगर (घातer_करोमुख्यs->display_core_suspended) अणु
		पूर्णांकel_घातer_करोमुख्यs_init_hw(i915, true);
		घातer_करोमुख्यs->display_core_suspended = false;
	पूर्ण अन्यथा अणु
		drm_WARN_ON(&i915->drm, घातer_करोमुख्यs->init_wakeref);
		घातer_करोमुख्यs->init_wakeref =
			पूर्णांकel_display_घातer_get(i915, POWER_DOMAIN_INIT);
	पूर्ण

	पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(i915);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)

अटल व्योम पूर्णांकel_घातer_करोमुख्यs_dump_info(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *घातer_well;

	क्रम_each_घातer_well(i915, घातer_well) अणु
		क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

		drm_dbg(&i915->drm, "%-25s %d\n",
			घातer_well->desc->name, घातer_well->count);

		क्रम_each_घातer_करोमुख्य(करोमुख्य, घातer_well->desc->करोमुख्यs)
			drm_dbg(&i915->drm, "  %-23s %d\n",
				पूर्णांकel_display_घातer_करोमुख्य_str(करोमुख्य),
				घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य]);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_घातer_करोमुख्यs_verअगरy_state - verअगरy the HW/SW state क्रम all घातer wells
 * @i915: i915 device instance
 *
 * Verअगरy अगर the reference count of each घातer well matches its HW enabled
 * state and the total refcount of the करोमुख्यs it beदीर्घs to. This must be
 * called after modeset HW state sanitization, which is responsible क्रम
 * acquiring reference counts क्रम any घातer wells in use and disabling the
 * ones left on by BIOS but not required by any active output.
 */
अटल व्योम पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_घातer_करोमुख्यs *घातer_करोमुख्यs = &i915->घातer_करोमुख्यs;
	काष्ठा i915_घातer_well *घातer_well;
	bool dump_करोमुख्य_info;

	mutex_lock(&घातer_करोमुख्यs->lock);

	verअगरy_async_put_करोमुख्यs_state(घातer_करोमुख्यs);

	dump_करोमुख्य_info = false;
	क्रम_each_घातer_well(i915, घातer_well) अणु
		क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;
		पूर्णांक करोमुख्यs_count;
		bool enabled;

		enabled = घातer_well->desc->ops->is_enabled(i915, घातer_well);
		अगर ((घातer_well->count || घातer_well->desc->always_on) !=
		    enabled)
			drm_err(&i915->drm,
				"power well %s state mismatch (refcount %d/enabled %d)",
				घातer_well->desc->name,
				घातer_well->count, enabled);

		करोमुख्यs_count = 0;
		क्रम_each_घातer_करोमुख्य(करोमुख्य, घातer_well->desc->करोमुख्यs)
			करोमुख्यs_count += घातer_करोमुख्यs->करोमुख्य_use_count[करोमुख्य];

		अगर (घातer_well->count != करोमुख्यs_count) अणु
			drm_err(&i915->drm,
				"power well %s refcount/domain refcount mismatch "
				"(refcount %d/domains refcount %d)\n",
				घातer_well->desc->name, घातer_well->count,
				करोमुख्यs_count);
			dump_करोमुख्य_info = true;
		पूर्ण
	पूर्ण

	अगर (dump_करोमुख्य_info) अणु
		अटल bool dumped;

		अगर (!dumped) अणु
			पूर्णांकel_घातer_करोमुख्यs_dump_info(i915);
			dumped = true;
		पूर्ण
	पूर्ण

	mutex_unlock(&घातer_करोमुख्यs->lock);
पूर्ण

#अन्यथा

अटल व्योम पूर्णांकel_घातer_करोमुख्यs_verअगरy_state(काष्ठा drm_i915_निजी *i915)
अणु
पूर्ण

#पूर्ण_अगर

व्योम पूर्णांकel_display_घातer_suspend_late(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11 || IS_GEN9_LP(i915)) अणु
		bxt_enable_dc9(i915);
		/* Tweaked Wa_14010685332:icp,jsp,mcc */
		अगर (INTEL_PCH_TYPE(i915) >= PCH_ICP && INTEL_PCH_TYPE(i915) <= PCH_MCC)
			पूर्णांकel_de_rmw(i915, SOUTH_CHICKEN1,
				     SBCLK_RUN_REFCLK_DIS, SBCLK_RUN_REFCLK_DIS);
	पूर्ण अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915)) अणु
		hsw_enable_pc8(i915);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_display_घातer_resume_early(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11 || IS_GEN9_LP(i915)) अणु
		gen9_sanitize_dc_state(i915);
		bxt_disable_dc9(i915);
		/* Tweaked Wa_14010685332:icp,jsp,mcc */
		अगर (INTEL_PCH_TYPE(i915) >= PCH_ICP && INTEL_PCH_TYPE(i915) <= PCH_MCC)
			पूर्णांकel_de_rmw(i915, SOUTH_CHICKEN1, SBCLK_RUN_REFCLK_DIS, 0);

	पूर्ण अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915)) अणु
		hsw_disable_pc8(i915);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_display_घातer_suspend(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11) अणु
		icl_display_core_uninit(i915);
		bxt_enable_dc9(i915);
	पूर्ण अन्यथा अगर (IS_GEN9_LP(i915)) अणु
		bxt_display_core_uninit(i915);
		bxt_enable_dc9(i915);
	पूर्ण अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915)) अणु
		hsw_enable_pc8(i915);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_display_घातer_resume(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11) अणु
		bxt_disable_dc9(i915);
		icl_display_core_init(i915, true);
		अगर (i915->csr.dmc_payload) अणु
			अगर (i915->csr.allowed_dc_mask &
			    DC_STATE_EN_UPTO_DC6)
				skl_enable_dc6(i915);
			अन्यथा अगर (i915->csr.allowed_dc_mask &
				 DC_STATE_EN_UPTO_DC5)
				gen9_enable_dc5(i915);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_GEN9_LP(i915)) अणु
		bxt_disable_dc9(i915);
		bxt_display_core_init(i915, true);
		अगर (i915->csr.dmc_payload &&
		    (i915->csr.allowed_dc_mask & DC_STATE_EN_UPTO_DC5))
			gen9_enable_dc5(i915);
	पूर्ण अन्यथा अगर (IS_HASWELL(i915) || IS_BROADWELL(i915)) अणु
		hsw_disable_pc8(i915);
	पूर्ण
पूर्ण
