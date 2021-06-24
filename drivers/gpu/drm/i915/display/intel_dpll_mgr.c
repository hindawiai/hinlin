<शैली गुरु>
/*
 * Copyright तऊ 2006-2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश "intel_display_types.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_dpll_mgr.h"

/**
 * DOC: Display PLLs
 *
 * Display PLLs used क्रम driving outमाला_दो vary by platक्रमm. While some have
 * per-pipe or per-encoder dedicated PLLs, others allow the use of any PLL
 * from a pool. In the latter scenario, it is possible that multiple pipes
 * share a PLL अगर their configurations match.
 *
 * This file provides an असलtraction over display PLLs. The function
 * पूर्णांकel_shared_dpll_init() initializes the PLLs क्रम the given platक्रमm.  The
 * users of a PLL are tracked and that tracking is पूर्णांकegrated with the atomic
 * modset पूर्णांकerface. During an atomic operation, required PLLs can be reserved
 * क्रम a given CRTC and encoder configuration by calling
 * पूर्णांकel_reserve_shared_dplls() and previously reserved PLLs can be released
 * with पूर्णांकel_release_shared_dplls().
 * Changes to the users are first staged in the atomic state, and then made
 * effective by calling पूर्णांकel_shared_dpll_swap_state() during the atomic
 * commit phase.
 */

काष्ठा पूर्णांकel_dpll_mgr अणु
	स्थिर काष्ठा dpll_info *dpll_info;

	bool (*get_dplls)(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc *crtc,
			  काष्ठा पूर्णांकel_encoder *encoder);
	व्योम (*put_dplls)(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc *crtc);
	व्योम (*update_active_dpll)(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_encoder *encoder);
	व्योम (*update_ref_clks)(काष्ठा drm_i915_निजी *i915);
	व्योम (*dump_hw_state)(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state);
पूर्ण;

अटल व्योम
पूर्णांकel_atomic_duplicate_dpll_state(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_shared_dpll_state *shared_dpll)
अणु
	क्रमागत पूर्णांकel_dpll_id i;

	/* Copy shared dpll state */
	क्रम (i = 0; i < dev_priv->dpll.num_shared_dpll; i++) अणु
		काष्ठा पूर्णांकel_shared_dpll *pll = &dev_priv->dpll.shared_dplls[i];

		shared_dpll[i] = pll->state;
	पूर्ण
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll_state *
पूर्णांकel_atomic_get_shared_dpll_state(काष्ठा drm_atomic_state *s)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(s);

	drm_WARN_ON(s->dev, !drm_modeset_is_locked(&s->dev->mode_config.connection_mutex));

	अगर (!state->dpll_set) अणु
		state->dpll_set = true;

		पूर्णांकel_atomic_duplicate_dpll_state(to_i915(s->dev),
						  state->shared_dpll);
	पूर्ण

	वापस state->shared_dpll;
पूर्ण

/**
 * पूर्णांकel_get_shared_dpll_by_id - get a DPLL given its id
 * @dev_priv: i915 device instance
 * @id: pll id
 *
 * Returns:
 * A poपूर्णांकer to the DPLL with @id
 */
काष्ठा पूर्णांकel_shared_dpll *
पूर्णांकel_get_shared_dpll_by_id(काष्ठा drm_i915_निजी *dev_priv,
			    क्रमागत पूर्णांकel_dpll_id id)
अणु
	वापस &dev_priv->dpll.shared_dplls[id];
पूर्ण

/**
 * पूर्णांकel_get_shared_dpll_id - get the id of a DPLL
 * @dev_priv: i915 device instance
 * @pll: the DPLL
 *
 * Returns:
 * The id of @pll
 */
क्रमागत पूर्णांकel_dpll_id
पूर्णांकel_get_shared_dpll_id(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	दीर्घ pll_idx = pll - dev_priv->dpll.shared_dplls;

	अगर (drm_WARN_ON(&dev_priv->drm,
			pll_idx < 0 ||
			pll_idx >= dev_priv->dpll.num_shared_dpll))
		वापस -1;

	वापस pll_idx;
पूर्ण

/* For ILK+ */
व्योम निश्चित_shared_dpll(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा पूर्णांकel_shared_dpll *pll,
			bool state)
अणु
	bool cur_state;
	काष्ठा पूर्णांकel_dpll_hw_state hw_state;

	अगर (drm_WARN(&dev_priv->drm, !pll,
		     "asserting DPLL %s with no DPLL\n", onoff(state)))
		वापस;

	cur_state = पूर्णांकel_dpll_get_hw_state(dev_priv, pll, &hw_state);
	I915_STATE_WARN(cur_state != state,
	     "%s assertion failure (expected %s, current %s)\n",
			pll->info->name, onoff(state), onoff(cur_state));
पूर्ण

अटल i915_reg_t
पूर्णांकel_combo_pll_enable_reg(काष्ठा drm_i915_निजी *i915,
			   काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	अगर (IS_DG1(i915))
		वापस DG1_DPLL_ENABLE(pll->info->id);
	अन्यथा अगर (IS_JSL_EHL(i915) && (pll->info->id == DPLL_ID_EHL_DPLL4))
		वापस MG_PLL_ENABLE(0);

	वापस CNL_DPLL_ENABLE(pll->info->id);
पूर्ण

/**
 * पूर्णांकel_prepare_shared_dpll - call a dpll's prepare hook
 * @crtc_state: CRTC, and its state, which has a shared dpll
 *
 * This calls the PLL's prepare hook अगर it has one and अगर the PLL is not
 * alपढ़ोy enabled. The prepare hook is platक्रमm specअगरic.
 */
व्योम पूर्णांकel_prepare_shared_dpll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;

	अगर (drm_WARN_ON(&dev_priv->drm, pll == शून्य))
		वापस;

	mutex_lock(&dev_priv->dpll.lock);
	drm_WARN_ON(&dev_priv->drm, !pll->state.pipe_mask);
	अगर (!pll->active_mask) अणु
		drm_dbg(&dev_priv->drm, "setting up %s\n", pll->info->name);
		drm_WARN_ON(&dev_priv->drm, pll->on);
		निश्चित_shared_dpll_disabled(dev_priv, pll);

		pll->info->funcs->prepare(dev_priv, pll);
	पूर्ण
	mutex_unlock(&dev_priv->dpll.lock);
पूर्ण

/**
 * पूर्णांकel_enable_shared_dpll - enable a CRTC's shared DPLL
 * @crtc_state: CRTC, and its state, which has a shared DPLL
 *
 * Enable the shared DPLL used by @crtc.
 */
व्योम पूर्णांकel_enable_shared_dpll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	अचिन्हित पूर्णांक pipe_mask = BIT(crtc->pipe);
	अचिन्हित पूर्णांक old_mask;

	अगर (drm_WARN_ON(&dev_priv->drm, pll == शून्य))
		वापस;

	mutex_lock(&dev_priv->dpll.lock);
	old_mask = pll->active_mask;

	अगर (drm_WARN_ON(&dev_priv->drm, !(pll->state.pipe_mask & pipe_mask)) ||
	    drm_WARN_ON(&dev_priv->drm, pll->active_mask & pipe_mask))
		जाओ out;

	pll->active_mask |= pipe_mask;

	drm_dbg_kms(&dev_priv->drm,
		    "enable %s (active 0x%x, on? %d) for [CRTC:%d:%s]\n",
		    pll->info->name, pll->active_mask, pll->on,
		    crtc->base.base.id, crtc->base.name);

	अगर (old_mask) अणु
		drm_WARN_ON(&dev_priv->drm, !pll->on);
		निश्चित_shared_dpll_enabled(dev_priv, pll);
		जाओ out;
	पूर्ण
	drm_WARN_ON(&dev_priv->drm, pll->on);

	drm_dbg_kms(&dev_priv->drm, "enabling %s\n", pll->info->name);
	pll->info->funcs->enable(dev_priv, pll);
	pll->on = true;

out:
	mutex_unlock(&dev_priv->dpll.lock);
पूर्ण

/**
 * पूर्णांकel_disable_shared_dpll - disable a CRTC's shared DPLL
 * @crtc_state: CRTC, and its state, which has a shared DPLL
 *
 * Disable the shared DPLL used by @crtc.
 */
व्योम पूर्णांकel_disable_shared_dpll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	अचिन्हित पूर्णांक pipe_mask = BIT(crtc->pipe);

	/* PCH only available on ILK+ */
	अगर (DISPLAY_VER(dev_priv) < 5)
		वापस;

	अगर (pll == शून्य)
		वापस;

	mutex_lock(&dev_priv->dpll.lock);
	अगर (drm_WARN(&dev_priv->drm, !(pll->active_mask & pipe_mask),
		     "%s not used by [CRTC:%d:%s]\n", pll->info->name,
		     crtc->base.base.id, crtc->base.name))
		जाओ out;

	drm_dbg_kms(&dev_priv->drm,
		    "disable %s (active 0x%x, on? %d) for [CRTC:%d:%s]\n",
		    pll->info->name, pll->active_mask, pll->on,
		    crtc->base.base.id, crtc->base.name);

	निश्चित_shared_dpll_enabled(dev_priv, pll);
	drm_WARN_ON(&dev_priv->drm, !pll->on);

	pll->active_mask &= ~pipe_mask;
	अगर (pll->active_mask)
		जाओ out;

	drm_dbg_kms(&dev_priv->drm, "disabling %s\n", pll->info->name);
	pll->info->funcs->disable(dev_priv, pll);
	pll->on = false;

out:
	mutex_unlock(&dev_priv->dpll.lock);
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *
पूर्णांकel_find_shared_dpll(काष्ठा पूर्णांकel_atomic_state *state,
		       स्थिर काष्ठा पूर्णांकel_crtc *crtc,
		       स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state,
		       अचिन्हित दीर्घ dpll_mask)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll, *unused_pll = शून्य;
	काष्ठा पूर्णांकel_shared_dpll_state *shared_dpll;
	क्रमागत पूर्णांकel_dpll_id i;

	shared_dpll = पूर्णांकel_atomic_get_shared_dpll_state(&state->base);

	drm_WARN_ON(&dev_priv->drm, dpll_mask & ~(BIT(I915_NUM_PLLS) - 1));

	क्रम_each_set_bit(i, &dpll_mask, I915_NUM_PLLS) अणु
		pll = &dev_priv->dpll.shared_dplls[i];

		/* Only want to check enabled timings first */
		अगर (shared_dpll[i].pipe_mask == 0) अणु
			अगर (!unused_pll)
				unused_pll = pll;
			जारी;
		पूर्ण

		अगर (स_भेद(pll_state,
			   &shared_dpll[i].hw_state,
			   माप(*pll_state)) == 0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "[CRTC:%d:%s] sharing existing %s (pipe mask 0x%x, active 0x%x)\n",
				    crtc->base.base.id, crtc->base.name,
				    pll->info->name,
				    shared_dpll[i].pipe_mask,
				    pll->active_mask);
			वापस pll;
		पूर्ण
	पूर्ण

	/* Ok no matching timings, maybe there's a मुक्त one? */
	अगर (unused_pll) अणु
		drm_dbg_kms(&dev_priv->drm, "[CRTC:%d:%s] allocated %s\n",
			    crtc->base.base.id, crtc->base.name,
			    unused_pll->info->name);
		वापस unused_pll;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
पूर्णांकel_reference_shared_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			    स्थिर काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
			    स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_shared_dpll_state *shared_dpll;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	shared_dpll = पूर्णांकel_atomic_get_shared_dpll_state(&state->base);

	अगर (shared_dpll[id].pipe_mask == 0)
		shared_dpll[id].hw_state = *pll_state;

	drm_dbg(&i915->drm, "using %s for pipe %c\n", pll->info->name,
		pipe_name(crtc->pipe));

	shared_dpll[id].pipe_mask |= BIT(crtc->pipe);
पूर्ण

अटल व्योम पूर्णांकel_unreference_shared_dpll(काष्ठा पूर्णांकel_atomic_state *state,
					  स्थिर काष्ठा पूर्णांकel_crtc *crtc,
					  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा पूर्णांकel_shared_dpll_state *shared_dpll;

	shared_dpll = पूर्णांकel_atomic_get_shared_dpll_state(&state->base);
	shared_dpll[pll->info->id].pipe_mask &= ~BIT(crtc->pipe);
पूर्ण

अटल व्योम पूर्णांकel_put_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	new_crtc_state->shared_dpll = शून्य;

	अगर (!old_crtc_state->shared_dpll)
		वापस;

	पूर्णांकel_unreference_shared_dpll(state, crtc, old_crtc_state->shared_dpll);
पूर्ण

/**
 * पूर्णांकel_shared_dpll_swap_state - make atomic DPLL configuration effective
 * @state: atomic state
 *
 * This is the dpll version of drm_atomic_helper_swap_state() since the
 * helper करोes not handle driver-specअगरic global state.
 *
 * For consistency with atomic helpers this function करोes a complete swap,
 * i.e. it also माला_दो the current state पूर्णांकo @state, even though there is no
 * need क्रम that at this moment.
 */
व्योम पूर्णांकel_shared_dpll_swap_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_shared_dpll_state *shared_dpll = state->shared_dpll;
	क्रमागत पूर्णांकel_dpll_id i;

	अगर (!state->dpll_set)
		वापस;

	क्रम (i = 0; i < dev_priv->dpll.num_shared_dpll; i++) अणु
		काष्ठा पूर्णांकel_shared_dpll *pll =
			&dev_priv->dpll.shared_dplls[i];

		swap(pll->state, shared_dpll[i]);
	पूर्ण
पूर्ण

अटल bool ibx_pch_dpll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				      काष्ठा पूर्णांकel_shared_dpll *pll,
				      काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	पूर्णांकel_wakeref_t wakeref;
	u32 val;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DPLL(id));
	hw_state->dpll = val;
	hw_state->fp0 = पूर्णांकel_de_पढ़ो(dev_priv, PCH_FP0(id));
	hw_state->fp1 = पूर्णांकel_de_पढ़ो(dev_priv, PCH_FP1(id));

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस val & DPLL_VCO_ENABLE;
पूर्ण

अटल व्योम ibx_pch_dpll_prepare(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_FP0(id), pll->state.hw_state.fp0);
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_FP1(id), pll->state.hw_state.fp1);
पूर्ण

अटल व्योम ibx_निश्चित_pch_refclk_enabled(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;
	bool enabled;

	I915_STATE_WARN_ON(!(HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv)));

	val = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DREF_CONTROL);
	enabled = !!(val & (DREF_SSC_SOURCE_MASK | DREF_NONSPREAD_SOURCE_MASK |
			    DREF_SUPERSPREAD_SOURCE_MASK));
	I915_STATE_WARN(!enabled, "PCH refclk assertion failure, should be active but is disabled\n");
पूर्ण

अटल व्योम ibx_pch_dpll_enable(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	/* PCH refघड़ी must be enabled first */
	ibx_निश्चित_pch_refclk_enabled(dev_priv);

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DPLL(id), pll->state.hw_state.dpll);

	/* Wait क्रम the घड़ीs to stabilize. */
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DPLL(id));
	udelay(150);

	/* The pixel multiplier can only be updated once the
	 * DPLL is enabled and the घड़ीs are stable.
	 *
	 * So ग_लिखो it again.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DPLL(id), pll->state.hw_state.dpll);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DPLL(id));
	udelay(200);
पूर्ण

अटल व्योम ibx_pch_dpll_disable(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DPLL(id), 0);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DPLL(id));
	udelay(200);
पूर्ण

अटल bool ibx_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll;
	क्रमागत पूर्णांकel_dpll_id i;

	अगर (HAS_PCH_IBX(dev_priv)) अणु
		/* Ironlake PCH has a fixed PLL->PCH pipe mapping. */
		i = (क्रमागत पूर्णांकel_dpll_id) crtc->pipe;
		pll = &dev_priv->dpll.shared_dplls[i];

		drm_dbg_kms(&dev_priv->drm,
			    "[CRTC:%d:%s] using pre-allocated %s\n",
			    crtc->base.base.id, crtc->base.name,
			    pll->info->name);
	पूर्ण अन्यथा अणु
		pll = पूर्णांकel_find_shared_dpll(state, crtc,
					     &crtc_state->dpll_hw_state,
					     BIT(DPLL_ID_PCH_PLL_B) |
					     BIT(DPLL_ID_PCH_PLL_A));
	पूर्ण

	अगर (!pll)
		वापस false;

	/* reference the pll */
	पूर्णांकel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	वापस true;
पूर्ण

अटल व्योम ibx_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	drm_dbg_kms(&dev_priv->drm,
		    "dpll_hw_state: dpll: 0x%x, dpll_md: 0x%x, "
		    "fp0: 0x%x, fp1: 0x%x\n",
		    hw_state->dpll,
		    hw_state->dpll_md,
		    hw_state->fp0,
		    hw_state->fp1);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs ibx_pch_dpll_funcs = अणु
	.prepare = ibx_pch_dpll_prepare,
	.enable = ibx_pch_dpll_enable,
	.disable = ibx_pch_dpll_disable,
	.get_hw_state = ibx_pch_dpll_get_hw_state,
पूर्ण;

अटल स्थिर काष्ठा dpll_info pch_plls[] = अणु
	अणु "PCH DPLL A", &ibx_pch_dpll_funcs, DPLL_ID_PCH_PLL_A, 0 पूर्ण,
	अणु "PCH DPLL B", &ibx_pch_dpll_funcs, DPLL_ID_PCH_PLL_B, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr pch_pll_mgr = अणु
	.dpll_info = pch_plls,
	.get_dplls = ibx_get_dpll,
	.put_dplls = पूर्णांकel_put_dpll,
	.dump_hw_state = ibx_dump_hw_state,
पूर्ण;

अटल व्योम hsw_ddi_wrpll_enable(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	पूर्णांकel_de_ग_लिखो(dev_priv, WRPLL_CTL(id), pll->state.hw_state.wrpll);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, WRPLL_CTL(id));
	udelay(20);
पूर्ण

अटल व्योम hsw_ddi_spll_enable(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, SPLL_CTL, pll->state.hw_state.spll);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, SPLL_CTL);
	udelay(20);
पूर्ण

अटल व्योम hsw_ddi_wrpll_disable(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, WRPLL_CTL(id));
	पूर्णांकel_de_ग_लिखो(dev_priv, WRPLL_CTL(id), val & ~WRPLL_PLL_ENABLE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, WRPLL_CTL(id));

	/*
	 * Try to set up the PCH reference घड़ी once all DPLLs
	 * that depend on it have been shut करोwn.
	 */
	अगर (dev_priv->pch_ssc_use & BIT(id))
		पूर्णांकel_init_pch_refclk(dev_priv);
पूर्ण

अटल व्योम hsw_ddi_spll_disable(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, SPLL_CTL);
	पूर्णांकel_de_ग_लिखो(dev_priv, SPLL_CTL, val & ~SPLL_PLL_ENABLE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, SPLL_CTL);

	/*
	 * Try to set up the PCH reference घड़ी once all DPLLs
	 * that depend on it have been shut करोwn.
	 */
	अगर (dev_priv->pch_ssc_use & BIT(id))
		पूर्णांकel_init_pch_refclk(dev_priv);
पूर्ण

अटल bool hsw_ddi_wrpll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				       काष्ठा पूर्णांकel_shared_dpll *pll,
				       काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	पूर्णांकel_wakeref_t wakeref;
	u32 val;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, WRPLL_CTL(id));
	hw_state->wrpll = val;

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस val & WRPLL_PLL_ENABLE;
पूर्ण

अटल bool hsw_ddi_spll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				      काष्ठा पूर्णांकel_shared_dpll *pll,
				      काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	पूर्णांकel_wakeref_t wakeref;
	u32 val;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, SPLL_CTL);
	hw_state->spll = val;

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस val & SPLL_PLL_ENABLE;
पूर्ण

#घोषणा LC_FREQ 2700
#घोषणा LC_FREQ_2K U64_C(LC_FREQ * 2000)

#घोषणा P_MIN 2
#घोषणा P_MAX 64
#घोषणा P_INC 2

/* Constraपूर्णांकs क्रम PLL good behavior */
#घोषणा REF_MIN 48
#घोषणा REF_MAX 400
#घोषणा VCO_MIN 2400
#घोषणा VCO_MAX 4800

काष्ठा hsw_wrpll_rnp अणु
	अचिन्हित p, n2, r2;
पूर्ण;

अटल अचिन्हित hsw_wrpll_get_budget_क्रम_freq(पूर्णांक घड़ी)
अणु
	अचिन्हित budget;

	चयन (घड़ी) अणु
	हाल 25175000:
	हाल 25200000:
	हाल 27000000:
	हाल 27027000:
	हाल 37762500:
	हाल 37800000:
	हाल 40500000:
	हाल 40541000:
	हाल 54000000:
	हाल 54054000:
	हाल 59341000:
	हाल 59400000:
	हाल 72000000:
	हाल 74176000:
	हाल 74250000:
	हाल 81000000:
	हाल 81081000:
	हाल 89012000:
	हाल 89100000:
	हाल 108000000:
	हाल 108108000:
	हाल 111264000:
	हाल 111375000:
	हाल 148352000:
	हाल 148500000:
	हाल 162000000:
	हाल 162162000:
	हाल 222525000:
	हाल 222750000:
	हाल 296703000:
	हाल 297000000:
		budget = 0;
		अवरोध;
	हाल 233500000:
	हाल 245250000:
	हाल 247750000:
	हाल 253250000:
	हाल 298000000:
		budget = 1500;
		अवरोध;
	हाल 169128000:
	हाल 169500000:
	हाल 179500000:
	हाल 202000000:
		budget = 2000;
		अवरोध;
	हाल 256250000:
	हाल 262500000:
	हाल 270000000:
	हाल 272500000:
	हाल 273750000:
	हाल 280750000:
	हाल 281250000:
	हाल 286000000:
	हाल 291750000:
		budget = 4000;
		अवरोध;
	हाल 267250000:
	हाल 268500000:
		budget = 5000;
		अवरोध;
	शेष:
		budget = 1000;
		अवरोध;
	पूर्ण

	वापस budget;
पूर्ण

अटल व्योम hsw_wrpll_update_rnp(u64 freq2k, अचिन्हित पूर्णांक budget,
				 अचिन्हित पूर्णांक r2, अचिन्हित पूर्णांक n2,
				 अचिन्हित पूर्णांक p,
				 काष्ठा hsw_wrpll_rnp *best)
अणु
	u64 a, b, c, d, dअगरf, dअगरf_best;

	/* No best (r,n,p) yet */
	अगर (best->p == 0) अणु
		best->p = p;
		best->n2 = n2;
		best->r2 = r2;
		वापस;
	पूर्ण

	/*
	 * Output घड़ी is (LC_FREQ_2K / 2000) * N / (P * R), which compares to
	 * freq2k.
	 *
	 * delta = 1e6 *
	 *	   असल(freq2k - (LC_FREQ_2K * n2/(p * r2))) /
	 *	   freq2k;
	 *
	 * and we would like delta <= budget.
	 *
	 * If the discrepancy is above the PPM-based budget, always prefer to
	 * improve upon the previous solution.  However, अगर you're within the
	 * budget, try to maximize Ref * VCO, that is N / (P * R^2).
	 */
	a = freq2k * budget * p * r2;
	b = freq2k * budget * best->p * best->r2;
	dअगरf = असल_dअगरf(freq2k * p * r2, LC_FREQ_2K * n2);
	dअगरf_best = असल_dअगरf(freq2k * best->p * best->r2,
			     LC_FREQ_2K * best->n2);
	c = 1000000 * dअगरf;
	d = 1000000 * dअगरf_best;

	अगर (a < c && b < d) अणु
		/* If both are above the budget, pick the बंदr */
		अगर (best->p * best->r2 * dअगरf < p * r2 * dअगरf_best) अणु
			best->p = p;
			best->n2 = n2;
			best->r2 = r2;
		पूर्ण
	पूर्ण अन्यथा अगर (a >= c && b < d) अणु
		/* If A is below the threshold but B is above it?  Update. */
		best->p = p;
		best->n2 = n2;
		best->r2 = r2;
	पूर्ण अन्यथा अगर (a >= c && b >= d) अणु
		/* Both are below the limit, so pick the higher n2/(r2*r2) */
		अगर (n2 * best->r2 * best->r2 > best->n2 * r2 * r2) अणु
			best->p = p;
			best->n2 = n2;
			best->r2 = r2;
		पूर्ण
	पूर्ण
	/* Otherwise a < c && b >= d, करो nothing */
पूर्ण

अटल व्योम
hsw_ddi_calculate_wrpll(पूर्णांक घड़ी /* in Hz */,
			अचिन्हित *r2_out, अचिन्हित *n2_out, अचिन्हित *p_out)
अणु
	u64 freq2k;
	अचिन्हित p, n2, r2;
	काष्ठा hsw_wrpll_rnp best = अणु 0, 0, 0 पूर्ण;
	अचिन्हित budget;

	freq2k = घड़ी / 100;

	budget = hsw_wrpll_get_budget_क्रम_freq(घड़ी);

	/* Special हाल handling क्रम 540 pixel घड़ी: bypass WR PLL entirely
	 * and directly pass the LC PLL to it. */
	अगर (freq2k == 5400000) अणु
		*n2_out = 2;
		*p_out = 1;
		*r2_out = 2;
		वापस;
	पूर्ण

	/*
	 * Ref = LC_FREQ / R, where Ref is the actual reference input seen by
	 * the WR PLL.
	 *
	 * We want R so that REF_MIN <= Ref <= REF_MAX.
	 * Injecting R2 = 2 * R gives:
	 *   REF_MAX * r2 > LC_FREQ * 2 and
	 *   REF_MIN * r2 < LC_FREQ * 2
	 *
	 * Which means the desired boundaries क्रम r2 are:
	 *  LC_FREQ * 2 / REF_MAX < r2 < LC_FREQ * 2 / REF_MIN
	 *
	 */
	क्रम (r2 = LC_FREQ * 2 / REF_MAX + 1;
	     r2 <= LC_FREQ * 2 / REF_MIN;
	     r2++) अणु

		/*
		 * VCO = N * Ref, that is: VCO = N * LC_FREQ / R
		 *
		 * Once again we want VCO_MIN <= VCO <= VCO_MAX.
		 * Injecting R2 = 2 * R and N2 = 2 * N, we get:
		 *   VCO_MAX * r2 > n2 * LC_FREQ and
		 *   VCO_MIN * r2 < n2 * LC_FREQ)
		 *
		 * Which means the desired boundaries क्रम n2 are:
		 * VCO_MIN * r2 / LC_FREQ < n2 < VCO_MAX * r2 / LC_FREQ
		 */
		क्रम (n2 = VCO_MIN * r2 / LC_FREQ + 1;
		     n2 <= VCO_MAX * r2 / LC_FREQ;
		     n2++) अणु

			क्रम (p = P_MIN; p <= P_MAX; p += P_INC)
				hsw_wrpll_update_rnp(freq2k, budget,
						     r2, n2, p, &best);
		पूर्ण
	पूर्ण

	*n2_out = best.n2;
	*p_out = best.p;
	*r2_out = best.r2;
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *
hsw_ddi_wrpll_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
		       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_shared_dpll *pll;
	u32 val;
	अचिन्हित पूर्णांक p, n2, r2;

	hsw_ddi_calculate_wrpll(crtc_state->port_घड़ी * 1000, &r2, &n2, &p);

	val = WRPLL_PLL_ENABLE | WRPLL_REF_LCPLL |
	      WRPLL_DIVIDER_REFERENCE(r2) | WRPLL_DIVIDER_FEEDBACK(n2) |
	      WRPLL_DIVIDER_POST(p);

	crtc_state->dpll_hw_state.wrpll = val;

	pll = पूर्णांकel_find_shared_dpll(state, crtc,
				     &crtc_state->dpll_hw_state,
				     BIT(DPLL_ID_WRPLL2) |
				     BIT(DPLL_ID_WRPLL1));

	अगर (!pll)
		वापस शून्य;

	वापस pll;
पूर्ण

अटल पूर्णांक hsw_ddi_wrpll_get_freq(काष्ठा drm_i915_निजी *dev_priv,
				  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				  स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	पूर्णांक refclk;
	पूर्णांक n, p, r;
	u32 wrpll = pll_state->wrpll;

	चयन (wrpll & WRPLL_REF_MASK) अणु
	हाल WRPLL_REF_SPECIAL_HSW:
		/* Muxed-SSC क्रम BDW, non-SSC क्रम non-ULT HSW. */
		अगर (IS_HASWELL(dev_priv) && !IS_HSW_ULT(dev_priv)) अणु
			refclk = dev_priv->dpll.ref_clks.nssc;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल WRPLL_REF_PCH_SSC:
		/*
		 * We could calculate spपढ़ो here, but our checking
		 * code only cares about 5% accuracy, and spपढ़ो is a max of
		 * 0.5% करोwnspपढ़ो.
		 */
		refclk = dev_priv->dpll.ref_clks.ssc;
		अवरोध;
	हाल WRPLL_REF_LCPLL:
		refclk = 2700000;
		अवरोध;
	शेष:
		MISSING_CASE(wrpll);
		वापस 0;
	पूर्ण

	r = wrpll & WRPLL_DIVIDER_REF_MASK;
	p = (wrpll & WRPLL_DIVIDER_POST_MASK) >> WRPLL_DIVIDER_POST_SHIFT;
	n = (wrpll & WRPLL_DIVIDER_FB_MASK) >> WRPLL_DIVIDER_FB_SHIFT;

	/* Convert to KHz, p & r have a fixed poपूर्णांक portion */
	वापस (refclk * n / 10) / (p * r) * 2;
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *
hsw_ddi_lcpll_get_dpll(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_shared_dpll *pll;
	क्रमागत पूर्णांकel_dpll_id pll_id;
	पूर्णांक घड़ी = crtc_state->port_घड़ी;

	चयन (घड़ी / 2) अणु
	हाल 81000:
		pll_id = DPLL_ID_LCPLL_810;
		अवरोध;
	हाल 135000:
		pll_id = DPLL_ID_LCPLL_1350;
		अवरोध;
	हाल 270000:
		pll_id = DPLL_ID_LCPLL_2700;
		अवरोध;
	शेष:
		drm_dbg_kms(&dev_priv->drm, "Invalid clock for DP: %d\n",
			    घड़ी);
		वापस शून्य;
	पूर्ण

	pll = पूर्णांकel_get_shared_dpll_by_id(dev_priv, pll_id);

	अगर (!pll)
		वापस शून्य;

	वापस pll;
पूर्ण

अटल पूर्णांक hsw_ddi_lcpll_get_freq(काष्ठा drm_i915_निजी *i915,
				  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				  स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	पूर्णांक link_घड़ी = 0;

	चयन (pll->info->id) अणु
	हाल DPLL_ID_LCPLL_810:
		link_घड़ी = 81000;
		अवरोध;
	हाल DPLL_ID_LCPLL_1350:
		link_घड़ी = 135000;
		अवरोध;
	हाल DPLL_ID_LCPLL_2700:
		link_घड़ी = 270000;
		अवरोध;
	शेष:
		drm_WARN(&i915->drm, 1, "bad port clock sel\n");
		अवरोध;
	पूर्ण

	वापस link_घड़ी * 2;
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *
hsw_ddi_spll_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
		      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	अगर (drm_WARN_ON(crtc->base.dev, crtc_state->port_घड़ी / 2 != 135000))
		वापस शून्य;

	crtc_state->dpll_hw_state.spll = SPLL_PLL_ENABLE | SPLL_FREQ_1350MHz |
					 SPLL_REF_MUXED_SSC;

	वापस पूर्णांकel_find_shared_dpll(state, crtc, &crtc_state->dpll_hw_state,
				      BIT(DPLL_ID_SPLL));
पूर्ण

अटल पूर्णांक hsw_ddi_spll_get_freq(काष्ठा drm_i915_निजी *i915,
				 स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				 स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	पूर्णांक link_घड़ी = 0;

	चयन (pll_state->spll & SPLL_FREQ_MASK) अणु
	हाल SPLL_FREQ_810MHz:
		link_घड़ी = 81000;
		अवरोध;
	हाल SPLL_FREQ_1350MHz:
		link_घड़ी = 135000;
		अवरोध;
	हाल SPLL_FREQ_2700MHz:
		link_घड़ी = 270000;
		अवरोध;
	शेष:
		drm_WARN(&i915->drm, 1, "bad spll freq\n");
		अवरोध;
	पूर्ण

	वापस link_घड़ी * 2;
पूर्ण

अटल bool hsw_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_shared_dpll *pll;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		pll = hsw_ddi_wrpll_get_dpll(state, crtc);
	अन्यथा अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		pll = hsw_ddi_lcpll_get_dpll(crtc_state);
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG))
		pll = hsw_ddi_spll_get_dpll(state, crtc);
	अन्यथा
		वापस false;

	अगर (!pll)
		वापस false;

	पूर्णांकel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	वापस true;
पूर्ण

अटल व्योम hsw_update_dpll_ref_clks(काष्ठा drm_i915_निजी *i915)
अणु
	i915->dpll.ref_clks.ssc = 135000;
	/* Non-SSC is only used on non-ULT HSW. */
	अगर (पूर्णांकel_de_पढ़ो(i915, FUSE_STRAP3) & HSW_REF_CLK_SELECT)
		i915->dpll.ref_clks.nssc = 24000;
	अन्यथा
		i915->dpll.ref_clks.nssc = 135000;
पूर्ण

अटल व्योम hsw_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	drm_dbg_kms(&dev_priv->drm, "dpll_hw_state: wrpll: 0x%x spll: 0x%x\n",
		    hw_state->wrpll, hw_state->spll);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs hsw_ddi_wrpll_funcs = अणु
	.enable = hsw_ddi_wrpll_enable,
	.disable = hsw_ddi_wrpll_disable,
	.get_hw_state = hsw_ddi_wrpll_get_hw_state,
	.get_freq = hsw_ddi_wrpll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs hsw_ddi_spll_funcs = अणु
	.enable = hsw_ddi_spll_enable,
	.disable = hsw_ddi_spll_disable,
	.get_hw_state = hsw_ddi_spll_get_hw_state,
	.get_freq = hsw_ddi_spll_get_freq,
पूर्ण;

अटल व्योम hsw_ddi_lcpll_enable(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
पूर्ण

अटल व्योम hsw_ddi_lcpll_disable(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
पूर्ण

अटल bool hsw_ddi_lcpll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				       काष्ठा पूर्णांकel_shared_dpll *pll,
				       काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	वापस true;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs hsw_ddi_lcpll_funcs = अणु
	.enable = hsw_ddi_lcpll_enable,
	.disable = hsw_ddi_lcpll_disable,
	.get_hw_state = hsw_ddi_lcpll_get_hw_state,
	.get_freq = hsw_ddi_lcpll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा dpll_info hsw_plls[] = अणु
	अणु "WRPLL 1",    &hsw_ddi_wrpll_funcs, DPLL_ID_WRPLL1,     0 पूर्ण,
	अणु "WRPLL 2",    &hsw_ddi_wrpll_funcs, DPLL_ID_WRPLL2,     0 पूर्ण,
	अणु "SPLL",       &hsw_ddi_spll_funcs,  DPLL_ID_SPLL,       0 पूर्ण,
	अणु "LCPLL 810",  &hsw_ddi_lcpll_funcs, DPLL_ID_LCPLL_810,  INTEL_DPLL_ALWAYS_ON पूर्ण,
	अणु "LCPLL 1350", &hsw_ddi_lcpll_funcs, DPLL_ID_LCPLL_1350, INTEL_DPLL_ALWAYS_ON पूर्ण,
	अणु "LCPLL 2700", &hsw_ddi_lcpll_funcs, DPLL_ID_LCPLL_2700, INTEL_DPLL_ALWAYS_ON पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr hsw_pll_mgr = अणु
	.dpll_info = hsw_plls,
	.get_dplls = hsw_get_dpll,
	.put_dplls = पूर्णांकel_put_dpll,
	.update_ref_clks = hsw_update_dpll_ref_clks,
	.dump_hw_state = hsw_dump_hw_state,
पूर्ण;

काष्ठा skl_dpll_regs अणु
	i915_reg_t ctl, cfgcr1, cfgcr2;
पूर्ण;

/* this array is indexed by the *shared* pll id */
अटल स्थिर काष्ठा skl_dpll_regs skl_dpll_regs[4] = अणु
	अणु
		/* DPLL 0 */
		.ctl = LCPLL1_CTL,
		/* DPLL 0 करोesn't support HDMI mode */
	पूर्ण,
	अणु
		/* DPLL 1 */
		.ctl = LCPLL2_CTL,
		.cfgcr1 = DPLL_CFGCR1(SKL_DPLL1),
		.cfgcr2 = DPLL_CFGCR2(SKL_DPLL1),
	पूर्ण,
	अणु
		/* DPLL 2 */
		.ctl = WRPLL_CTL(0),
		.cfgcr1 = DPLL_CFGCR1(SKL_DPLL2),
		.cfgcr2 = DPLL_CFGCR2(SKL_DPLL2),
	पूर्ण,
	अणु
		/* DPLL 3 */
		.ctl = WRPLL_CTL(1),
		.cfgcr1 = DPLL_CFGCR1(SKL_DPLL3),
		.cfgcr2 = DPLL_CFGCR2(SKL_DPLL3),
	पूर्ण,
पूर्ण;

अटल व्योम skl_ddi_pll_ग_लिखो_ctrl1(काष्ठा drm_i915_निजी *dev_priv,
				    काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL_CTRL1);

	val &= ~(DPLL_CTRL1_HDMI_MODE(id) |
		 DPLL_CTRL1_SSC(id) |
		 DPLL_CTRL1_LINK_RATE_MASK(id));
	val |= pll->state.hw_state.ctrl1 << (id * 6);

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL_CTRL1, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL_CTRL1);
पूर्ण

अटल व्योम skl_ddi_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर काष्ठा skl_dpll_regs *regs = skl_dpll_regs;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	skl_ddi_pll_ग_लिखो_ctrl1(dev_priv, pll);

	पूर्णांकel_de_ग_लिखो(dev_priv, regs[id].cfgcr1, pll->state.hw_state.cfgcr1);
	पूर्णांकel_de_ग_लिखो(dev_priv, regs[id].cfgcr2, pll->state.hw_state.cfgcr2);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, regs[id].cfgcr1);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, regs[id].cfgcr2);

	/* the enable bit is always bit 31 */
	पूर्णांकel_de_ग_लिखो(dev_priv, regs[id].ctl,
		       पूर्णांकel_de_पढ़ो(dev_priv, regs[id].ctl) | LCPLL_PLL_ENABLE);

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, DPLL_STATUS, DPLL_LOCK(id), 5))
		drm_err(&dev_priv->drm, "DPLL %d not locked\n", id);
पूर्ण

अटल व्योम skl_ddi_dpll0_enable(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	skl_ddi_pll_ग_लिखो_ctrl1(dev_priv, pll);
पूर्ण

अटल व्योम skl_ddi_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर काष्ठा skl_dpll_regs *regs = skl_dpll_regs;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	/* the enable bit is always bit 31 */
	पूर्णांकel_de_ग_लिखो(dev_priv, regs[id].ctl,
		       पूर्णांकel_de_पढ़ो(dev_priv, regs[id].ctl) & ~LCPLL_PLL_ENABLE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, regs[id].ctl);
पूर्ण

अटल व्योम skl_ddi_dpll0_disable(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
पूर्ण

अटल bool skl_ddi_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				     काष्ठा पूर्णांकel_shared_dpll *pll,
				     काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	u32 val;
	स्थिर काष्ठा skl_dpll_regs *regs = skl_dpll_regs;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	ret = false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, regs[id].ctl);
	अगर (!(val & LCPLL_PLL_ENABLE))
		जाओ out;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL_CTRL1);
	hw_state->ctrl1 = (val >> (id * 6)) & 0x3f;

	/* aव्योम पढ़ोing back stale values अगर HDMI mode is not enabled */
	अगर (val & DPLL_CTRL1_HDMI_MODE(id)) अणु
		hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv, regs[id].cfgcr1);
		hw_state->cfgcr2 = पूर्णांकel_de_पढ़ो(dev_priv, regs[id].cfgcr2);
	पूर्ण
	ret = true;

out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस ret;
पूर्ण

अटल bool skl_ddi_dpll0_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				       काष्ठा पूर्णांकel_shared_dpll *pll,
				       काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	स्थिर काष्ठा skl_dpll_regs *regs = skl_dpll_regs;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	पूर्णांकel_wakeref_t wakeref;
	u32 val;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	ret = false;

	/* DPLL0 is always enabled since it drives CDCLK */
	val = पूर्णांकel_de_पढ़ो(dev_priv, regs[id].ctl);
	अगर (drm_WARN_ON(&dev_priv->drm, !(val & LCPLL_PLL_ENABLE)))
		जाओ out;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL_CTRL1);
	hw_state->ctrl1 = (val >> (id * 6)) & 0x3f;

	ret = true;

out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस ret;
पूर्ण

काष्ठा skl_wrpll_context अणु
	u64 min_deviation;		/* current minimal deviation */
	u64 central_freq;		/* chosen central freq */
	u64 dco_freq;			/* chosen dco freq */
	अचिन्हित पूर्णांक p;			/* chosen भागider */
पूर्ण;

अटल व्योम skl_wrpll_context_init(काष्ठा skl_wrpll_context *ctx)
अणु
	स_रखो(ctx, 0, माप(*ctx));

	ctx->min_deviation = U64_MAX;
पूर्ण

/* DCO freq must be within +1%/-6%  of the DCO central freq */
#घोषणा SKL_DCO_MAX_PDEVIATION	100
#घोषणा SKL_DCO_MAX_NDEVIATION	600

अटल व्योम skl_wrpll_try_भागider(काष्ठा skl_wrpll_context *ctx,
				  u64 central_freq,
				  u64 dco_freq,
				  अचिन्हित पूर्णांक भागider)
अणु
	u64 deviation;

	deviation = भाग64_u64(10000 * असल_dअगरf(dco_freq, central_freq),
			      central_freq);

	/* positive deviation */
	अगर (dco_freq >= central_freq) अणु
		अगर (deviation < SKL_DCO_MAX_PDEVIATION &&
		    deviation < ctx->min_deviation) अणु
			ctx->min_deviation = deviation;
			ctx->central_freq = central_freq;
			ctx->dco_freq = dco_freq;
			ctx->p = भागider;
		पूर्ण
	/* negative deviation */
	पूर्ण अन्यथा अगर (deviation < SKL_DCO_MAX_NDEVIATION &&
		   deviation < ctx->min_deviation) अणु
		ctx->min_deviation = deviation;
		ctx->central_freq = central_freq;
		ctx->dco_freq = dco_freq;
		ctx->p = भागider;
	पूर्ण
पूर्ण

अटल व्योम skl_wrpll_get_multipliers(अचिन्हित पूर्णांक p,
				      अचिन्हित पूर्णांक *p0 /* out */,
				      अचिन्हित पूर्णांक *p1 /* out */,
				      अचिन्हित पूर्णांक *p2 /* out */)
अणु
	/* even भागiders */
	अगर (p % 2 == 0) अणु
		अचिन्हित पूर्णांक half = p / 2;

		अगर (half == 1 || half == 2 || half == 3 || half == 5) अणु
			*p0 = 2;
			*p1 = 1;
			*p2 = half;
		पूर्ण अन्यथा अगर (half % 2 == 0) अणु
			*p0 = 2;
			*p1 = half / 2;
			*p2 = 2;
		पूर्ण अन्यथा अगर (half % 3 == 0) अणु
			*p0 = 3;
			*p1 = half / 3;
			*p2 = 2;
		पूर्ण अन्यथा अगर (half % 7 == 0) अणु
			*p0 = 7;
			*p1 = half / 7;
			*p2 = 2;
		पूर्ण
	पूर्ण अन्यथा अगर (p == 3 || p == 9) अणु  /* 3, 5, 7, 9, 15, 21, 35 */
		*p0 = 3;
		*p1 = 1;
		*p2 = p / 3;
	पूर्ण अन्यथा अगर (p == 5 || p == 7) अणु
		*p0 = p;
		*p1 = 1;
		*p2 = 1;
	पूर्ण अन्यथा अगर (p == 15) अणु
		*p0 = 3;
		*p1 = 1;
		*p2 = 5;
	पूर्ण अन्यथा अगर (p == 21) अणु
		*p0 = 7;
		*p1 = 1;
		*p2 = 3;
	पूर्ण अन्यथा अगर (p == 35) अणु
		*p0 = 7;
		*p1 = 1;
		*p2 = 5;
	पूर्ण
पूर्ण

काष्ठा skl_wrpll_params अणु
	u32 dco_fraction;
	u32 dco_पूर्णांकeger;
	u32 qभाग_ratio;
	u32 qभाग_mode;
	u32 kभाग;
	u32 pभाग;
	u32 central_freq;
पूर्ण;

अटल व्योम skl_wrpll_params_populate(काष्ठा skl_wrpll_params *params,
				      u64 afe_घड़ी,
				      पूर्णांक ref_घड़ी,
				      u64 central_freq,
				      u32 p0, u32 p1, u32 p2)
अणु
	u64 dco_freq;

	चयन (central_freq) अणु
	हाल 9600000000ULL:
		params->central_freq = 0;
		अवरोध;
	हाल 9000000000ULL:
		params->central_freq = 1;
		अवरोध;
	हाल 8400000000ULL:
		params->central_freq = 3;
	पूर्ण

	चयन (p0) अणु
	हाल 1:
		params->pभाग = 0;
		अवरोध;
	हाल 2:
		params->pभाग = 1;
		अवरोध;
	हाल 3:
		params->pभाग = 2;
		अवरोध;
	हाल 7:
		params->pभाग = 4;
		अवरोध;
	शेष:
		WARN(1, "Incorrect PDiv\n");
	पूर्ण

	चयन (p2) अणु
	हाल 5:
		params->kभाग = 0;
		अवरोध;
	हाल 2:
		params->kभाग = 1;
		अवरोध;
	हाल 3:
		params->kभाग = 2;
		अवरोध;
	हाल 1:
		params->kभाग = 3;
		अवरोध;
	शेष:
		WARN(1, "Incorrect KDiv\n");
	पूर्ण

	params->qभाग_ratio = p1;
	params->qभाग_mode = (params->qभाग_ratio == 1) ? 0 : 1;

	dco_freq = p0 * p1 * p2 * afe_घड़ी;

	/*
	 * Intermediate values are in Hz.
	 * Divide by MHz to match bsepc
	 */
	params->dco_पूर्णांकeger = भाग_u64(dco_freq, ref_घड़ी * KHz(1));
	params->dco_fraction =
		भाग_u64((भाग_u64(dco_freq, ref_घड़ी / KHz(1)) -
			 params->dco_पूर्णांकeger * MHz(1)) * 0x8000, MHz(1));
पूर्ण

अटल bool
skl_ddi_calculate_wrpll(पूर्णांक घड़ी /* in Hz */,
			पूर्णांक ref_घड़ी,
			काष्ठा skl_wrpll_params *wrpll_params)
अणु
	u64 afe_घड़ी = घड़ी * 5; /* AFE Clock is 5x Pixel घड़ी */
	u64 dco_central_freq[3] = अणु 8400000000ULL,
				    9000000000ULL,
				    9600000000ULL पूर्ण;
	अटल स्थिर पूर्णांक even_भागiders[] = अणु  4,  6,  8, 10, 12, 14, 16, 18, 20,
					     24, 28, 30, 32, 36, 40, 42, 44,
					     48, 52, 54, 56, 60, 64, 66, 68,
					     70, 72, 76, 78, 80, 84, 88, 90,
					     92, 96, 98 पूर्ण;
	अटल स्थिर पूर्णांक odd_भागiders[] = अणु 3, 5, 7, 9, 15, 21, 35 पूर्ण;
	अटल स्थिर काष्ठा अणु
		स्थिर पूर्णांक *list;
		पूर्णांक n_भागiders;
	पूर्ण भागiders[] = अणु
		अणु even_भागiders, ARRAY_SIZE(even_भागiders) पूर्ण,
		अणु odd_भागiders, ARRAY_SIZE(odd_भागiders) पूर्ण,
	पूर्ण;
	काष्ठा skl_wrpll_context ctx;
	अचिन्हित पूर्णांक dco, d, i;
	अचिन्हित पूर्णांक p0, p1, p2;

	skl_wrpll_context_init(&ctx);

	क्रम (d = 0; d < ARRAY_SIZE(भागiders); d++) अणु
		क्रम (dco = 0; dco < ARRAY_SIZE(dco_central_freq); dco++) अणु
			क्रम (i = 0; i < भागiders[d].n_भागiders; i++) अणु
				अचिन्हित पूर्णांक p = भागiders[d].list[i];
				u64 dco_freq = p * afe_घड़ी;

				skl_wrpll_try_भागider(&ctx,
						      dco_central_freq[dco],
						      dco_freq,
						      p);
				/*
				 * Skip the reमुख्यing भागiders अगर we're sure to
				 * have found the definitive भागider, we can't
				 * improve a 0 deviation.
				 */
				अगर (ctx.min_deviation == 0)
					जाओ skip_reमुख्यing_भागiders;
			पूर्ण
		पूर्ण

skip_reमुख्यing_भागiders:
		/*
		 * If a solution is found with an even भागider, prefer
		 * this one.
		 */
		अगर (d == 0 && ctx.p)
			अवरोध;
	पूर्ण

	अगर (!ctx.p) अणु
		DRM_DEBUG_DRIVER("No valid divider found for %dHz\n", घड़ी);
		वापस false;
	पूर्ण

	/*
	 * gcc incorrectly analyses that these can be used without being
	 * initialized. To be fair, it's hard to guess.
	 */
	p0 = p1 = p2 = 0;
	skl_wrpll_get_multipliers(ctx.p, &p0, &p1, &p2);
	skl_wrpll_params_populate(wrpll_params, afe_घड़ी, ref_घड़ी,
				  ctx.central_freq, p0, p1, p2);

	वापस true;
पूर्ण

अटल bool skl_ddi_hdmi_pll_भागiders(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);
	u32 ctrl1, cfgcr1, cfgcr2;
	काष्ठा skl_wrpll_params wrpll_params = अणु 0, पूर्ण;

	/*
	 * See comment in पूर्णांकel_dpll_hw_state to understand why we always use 0
	 * as the DPLL id in this function.
	 */
	ctrl1 = DPLL_CTRL1_OVERRIDE(0);

	ctrl1 |= DPLL_CTRL1_HDMI_MODE(0);

	अगर (!skl_ddi_calculate_wrpll(crtc_state->port_घड़ी * 1000,
				     i915->dpll.ref_clks.nssc,
				     &wrpll_params))
		वापस false;

	cfgcr1 = DPLL_CFGCR1_FREQ_ENABLE |
		DPLL_CFGCR1_DCO_FRACTION(wrpll_params.dco_fraction) |
		wrpll_params.dco_पूर्णांकeger;

	cfgcr2 = DPLL_CFGCR2_QDIV_RATIO(wrpll_params.qभाग_ratio) |
		DPLL_CFGCR2_QDIV_MODE(wrpll_params.qभाग_mode) |
		DPLL_CFGCR2_KDIV(wrpll_params.kभाग) |
		DPLL_CFGCR2_PDIV(wrpll_params.pभाग) |
		wrpll_params.central_freq;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	crtc_state->dpll_hw_state.ctrl1 = ctrl1;
	crtc_state->dpll_hw_state.cfgcr1 = cfgcr1;
	crtc_state->dpll_hw_state.cfgcr2 = cfgcr2;
	वापस true;
पूर्ण

अटल पूर्णांक skl_ddi_wrpll_get_freq(काष्ठा drm_i915_निजी *i915,
				  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				  स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	पूर्णांक ref_घड़ी = i915->dpll.ref_clks.nssc;
	u32 p0, p1, p2, dco_freq;

	p0 = pll_state->cfgcr2 & DPLL_CFGCR2_PDIV_MASK;
	p2 = pll_state->cfgcr2 & DPLL_CFGCR2_KDIV_MASK;

	अगर (pll_state->cfgcr2 &  DPLL_CFGCR2_QDIV_MODE(1))
		p1 = (pll_state->cfgcr2 & DPLL_CFGCR2_QDIV_RATIO_MASK) >> 8;
	अन्यथा
		p1 = 1;


	चयन (p0) अणु
	हाल DPLL_CFGCR2_PDIV_1:
		p0 = 1;
		अवरोध;
	हाल DPLL_CFGCR2_PDIV_2:
		p0 = 2;
		अवरोध;
	हाल DPLL_CFGCR2_PDIV_3:
		p0 = 3;
		अवरोध;
	हाल DPLL_CFGCR2_PDIV_7_INVALID:
		/*
		 * Incorrect ASUS-Z170M BIOS setting, the HW seems to ignore bit#0,
		 * handling it the same way as PDIV_7.
		 */
		drm_dbg_kms(&i915->drm, "Invalid WRPLL PDIV divider value, fixing it.\n");
		fallthrough;
	हाल DPLL_CFGCR2_PDIV_7:
		p0 = 7;
		अवरोध;
	शेष:
		MISSING_CASE(p0);
		वापस 0;
	पूर्ण

	चयन (p2) अणु
	हाल DPLL_CFGCR2_KDIV_5:
		p2 = 5;
		अवरोध;
	हाल DPLL_CFGCR2_KDIV_2:
		p2 = 2;
		अवरोध;
	हाल DPLL_CFGCR2_KDIV_3:
		p2 = 3;
		अवरोध;
	हाल DPLL_CFGCR2_KDIV_1:
		p2 = 1;
		अवरोध;
	शेष:
		MISSING_CASE(p2);
		वापस 0;
	पूर्ण

	dco_freq = (pll_state->cfgcr1 & DPLL_CFGCR1_DCO_INTEGER_MASK) *
		   ref_घड़ी;

	dco_freq += ((pll_state->cfgcr1 & DPLL_CFGCR1_DCO_FRACTION_MASK) >> 9) *
		    ref_घड़ी / 0x8000;

	अगर (drm_WARN_ON(&i915->drm, p0 == 0 || p1 == 0 || p2 == 0))
		वापस 0;

	वापस dco_freq / (p0 * p1 * p2 * 5);
पूर्ण

अटल bool
skl_ddi_dp_set_dpll_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 ctrl1;

	/*
	 * See comment in पूर्णांकel_dpll_hw_state to understand why we always use 0
	 * as the DPLL id in this function.
	 */
	ctrl1 = DPLL_CTRL1_OVERRIDE(0);
	चयन (crtc_state->port_घड़ी / 2) अणु
	हाल 81000:
		ctrl1 |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_810, 0);
		अवरोध;
	हाल 135000:
		ctrl1 |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1350, 0);
		अवरोध;
	हाल 270000:
		ctrl1 |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_2700, 0);
		अवरोध;
		/* eDP 1.4 rates */
	हाल 162000:
		ctrl1 |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1620, 0);
		अवरोध;
	हाल 108000:
		ctrl1 |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1080, 0);
		अवरोध;
	हाल 216000:
		ctrl1 |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_2160, 0);
		अवरोध;
	पूर्ण

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	crtc_state->dpll_hw_state.ctrl1 = ctrl1;

	वापस true;
पूर्ण

अटल पूर्णांक skl_ddi_lcpll_get_freq(काष्ठा drm_i915_निजी *i915,
				  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				  स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	पूर्णांक link_घड़ी = 0;

	चयन ((pll_state->ctrl1 & DPLL_CTRL1_LINK_RATE_MASK(0)) >>
		DPLL_CTRL1_LINK_RATE_SHIFT(0)) अणु
	हाल DPLL_CTRL1_LINK_RATE_810:
		link_घड़ी = 81000;
		अवरोध;
	हाल DPLL_CTRL1_LINK_RATE_1080:
		link_घड़ी = 108000;
		अवरोध;
	हाल DPLL_CTRL1_LINK_RATE_1350:
		link_घड़ी = 135000;
		अवरोध;
	हाल DPLL_CTRL1_LINK_RATE_1620:
		link_घड़ी = 162000;
		अवरोध;
	हाल DPLL_CTRL1_LINK_RATE_2160:
		link_घड़ी = 216000;
		अवरोध;
	हाल DPLL_CTRL1_LINK_RATE_2700:
		link_घड़ी = 270000;
		अवरोध;
	शेष:
		drm_WARN(&i915->drm, 1, "Unsupported link rate\n");
		अवरोध;
	पूर्ण

	वापस link_घड़ी * 2;
पूर्ण

अटल bool skl_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll;
	bool bret;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) अणु
		bret = skl_ddi_hdmi_pll_भागiders(crtc_state);
		अगर (!bret) अणु
			drm_dbg_kms(&i915->drm,
				    "Could not get HDMI pll dividers.\n");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state)) अणु
		bret = skl_ddi_dp_set_dpll_hw_state(crtc_state);
		अगर (!bret) अणु
			drm_dbg_kms(&i915->drm,
				    "Could not set DP dpll HW state.\n");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		pll = पूर्णांकel_find_shared_dpll(state, crtc,
					     &crtc_state->dpll_hw_state,
					     BIT(DPLL_ID_SKL_DPLL0));
	अन्यथा
		pll = पूर्णांकel_find_shared_dpll(state, crtc,
					     &crtc_state->dpll_hw_state,
					     BIT(DPLL_ID_SKL_DPLL3) |
					     BIT(DPLL_ID_SKL_DPLL2) |
					     BIT(DPLL_ID_SKL_DPLL1));
	अगर (!pll)
		वापस false;

	पूर्णांकel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	वापस true;
पूर्ण

अटल पूर्णांक skl_ddi_pll_get_freq(काष्ठा drm_i915_निजी *i915,
				स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	/*
	 * ctrl1 रेजिस्टर is alपढ़ोy shअगरted क्रम each pll, just use 0 to get
	 * the पूर्णांकernal shअगरt क्रम each field
	 */
	अगर (pll_state->ctrl1 & DPLL_CTRL1_HDMI_MODE(0))
		वापस skl_ddi_wrpll_get_freq(i915, pll, pll_state);
	अन्यथा
		वापस skl_ddi_lcpll_get_freq(i915, pll, pll_state);
पूर्ण

अटल व्योम skl_update_dpll_ref_clks(काष्ठा drm_i915_निजी *i915)
अणु
	/* No SSC ref */
	i915->dpll.ref_clks.nssc = i915->cdclk.hw.ref;
पूर्ण

अटल व्योम skl_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	drm_dbg_kms(&dev_priv->drm, "dpll_hw_state: "
		      "ctrl1: 0x%x, cfgcr1: 0x%x, cfgcr2: 0x%x\n",
		      hw_state->ctrl1,
		      hw_state->cfgcr1,
		      hw_state->cfgcr2);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs skl_ddi_pll_funcs = अणु
	.enable = skl_ddi_pll_enable,
	.disable = skl_ddi_pll_disable,
	.get_hw_state = skl_ddi_pll_get_hw_state,
	.get_freq = skl_ddi_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs skl_ddi_dpll0_funcs = अणु
	.enable = skl_ddi_dpll0_enable,
	.disable = skl_ddi_dpll0_disable,
	.get_hw_state = skl_ddi_dpll0_get_hw_state,
	.get_freq = skl_ddi_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा dpll_info skl_plls[] = अणु
	अणु "DPLL 0", &skl_ddi_dpll0_funcs, DPLL_ID_SKL_DPLL0, INTEL_DPLL_ALWAYS_ON पूर्ण,
	अणु "DPLL 1", &skl_ddi_pll_funcs,   DPLL_ID_SKL_DPLL1, 0 पूर्ण,
	अणु "DPLL 2", &skl_ddi_pll_funcs,   DPLL_ID_SKL_DPLL2, 0 पूर्ण,
	अणु "DPLL 3", &skl_ddi_pll_funcs,   DPLL_ID_SKL_DPLL3, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr skl_pll_mgr = अणु
	.dpll_info = skl_plls,
	.get_dplls = skl_get_dpll,
	.put_dplls = पूर्णांकel_put_dpll,
	.update_ref_clks = skl_update_dpll_ref_clks,
	.dump_hw_state = skl_dump_hw_state,
पूर्ण;

अटल व्योम bxt_ddi_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	u32 temp;
	क्रमागत port port = (क्रमागत port)pll->info->id; /* 1:1 port->PLL mapping */
	क्रमागत dpio_phy phy;
	क्रमागत dpio_channel ch;

	bxt_port_to_phy_channel(dev_priv, port, &phy, &ch);

	/* Non-SSC reference */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));
	temp |= PORT_PLL_REF_SEL;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_ENABLE(port), temp);

	अगर (IS_GEMINILAKE(dev_priv)) अणु
		temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));
		temp |= PORT_PLL_POWER_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_ENABLE(port), temp);

		अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port)) &
				 PORT_PLL_POWER_STATE), 200))
			drm_err(&dev_priv->drm,
				"Power state not set for PLL:%d\n", port);
	पूर्ण

	/* Disable 10 bit घड़ी */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_EBB_4(phy, ch));
	temp &= ~PORT_PLL_10BIT_CLK_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_EBB_4(phy, ch), temp);

	/* Write P1 & P2 */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_EBB_0(phy, ch));
	temp &= ~(PORT_PLL_P1_MASK | PORT_PLL_P2_MASK);
	temp |= pll->state.hw_state.ebb0;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_EBB_0(phy, ch), temp);

	/* Write M2 पूर्णांकeger */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 0));
	temp &= ~PORT_PLL_M2_MASK;
	temp |= pll->state.hw_state.pll0;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 0), temp);

	/* Write N */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 1));
	temp &= ~PORT_PLL_N_MASK;
	temp |= pll->state.hw_state.pll1;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 1), temp);

	/* Write M2 fraction */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 2));
	temp &= ~PORT_PLL_M2_FRAC_MASK;
	temp |= pll->state.hw_state.pll2;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 2), temp);

	/* Write M2 fraction enable */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 3));
	temp &= ~PORT_PLL_M2_FRAC_ENABLE;
	temp |= pll->state.hw_state.pll3;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 3), temp);

	/* Write coeff */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 6));
	temp &= ~PORT_PLL_PROP_COEFF_MASK;
	temp &= ~PORT_PLL_INT_COEFF_MASK;
	temp &= ~PORT_PLL_GAIN_CTL_MASK;
	temp |= pll->state.hw_state.pll6;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 6), temp);

	/* Write calibration val */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 8));
	temp &= ~PORT_PLL_TARGET_CNT_MASK;
	temp |= pll->state.hw_state.pll8;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 8), temp);

	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 9));
	temp &= ~PORT_PLL_LOCK_THRESHOLD_MASK;
	temp |= pll->state.hw_state.pll9;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 9), temp);

	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 10));
	temp &= ~PORT_PLL_DCO_AMP_OVR_EN_H;
	temp &= ~PORT_PLL_DCO_AMP_MASK;
	temp |= pll->state.hw_state.pll10;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL(phy, ch, 10), temp);

	/* Recalibrate with new settings */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_EBB_4(phy, ch));
	temp |= PORT_PLL_RECALIBRATE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_EBB_4(phy, ch), temp);
	temp &= ~PORT_PLL_10BIT_CLK_ENABLE;
	temp |= pll->state.hw_state.ebb4;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_EBB_4(phy, ch), temp);

	/* Enable PLL */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));
	temp |= PORT_PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_ENABLE(port), temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));

	अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port)) & PORT_PLL_LOCK),
			200))
		drm_err(&dev_priv->drm, "PLL %d not locked\n", port);

	अगर (IS_GEMINILAKE(dev_priv)) अणु
		temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_TX_DW5_LN0(phy, ch));
		temp |= DCC_DELAY_RANGE_2;
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_TX_DW5_GRP(phy, ch), temp);
	पूर्ण

	/*
	 * While we ग_लिखो to the group रेजिस्टर to program all lanes at once we
	 * can पढ़ो only lane रेजिस्टरs and we pick lanes 0/1 क्रम that.
	 */
	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PCS_DW12_LN01(phy, ch));
	temp &= ~LANE_STAGGER_MASK;
	temp &= ~LANESTAGGER_STRAP_OVRD;
	temp |= pll->state.hw_state.pcsdw12;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PCS_DW12_GRP(phy, ch), temp);
पूर्ण

अटल व्योम bxt_ddi_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	क्रमागत port port = (क्रमागत port)pll->info->id; /* 1:1 port->PLL mapping */
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));
	temp &= ~PORT_PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_ENABLE(port), temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));

	अगर (IS_GEMINILAKE(dev_priv)) अणु
		temp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));
		temp &= ~PORT_PLL_POWER_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PLL_ENABLE(port), temp);

		अगर (रुको_क्रम_us(!(पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port)) &
				  PORT_PLL_POWER_STATE), 200))
			drm_err(&dev_priv->drm,
				"Power state not reset for PLL:%d\n", port);
	पूर्ण
पूर्ण

अटल bool bxt_ddi_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा पूर्णांकel_shared_dpll *pll,
					काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	क्रमागत port port = (क्रमागत port)pll->info->id; /* 1:1 port->PLL mapping */
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत dpio_phy phy;
	क्रमागत dpio_channel ch;
	u32 val;
	bool ret;

	bxt_port_to_phy_channel(dev_priv, port, &phy, &ch);

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	ret = false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_ENABLE(port));
	अगर (!(val & PORT_PLL_ENABLE))
		जाओ out;

	hw_state->ebb0 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_EBB_0(phy, ch));
	hw_state->ebb0 &= PORT_PLL_P1_MASK | PORT_PLL_P2_MASK;

	hw_state->ebb4 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL_EBB_4(phy, ch));
	hw_state->ebb4 &= PORT_PLL_10BIT_CLK_ENABLE;

	hw_state->pll0 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 0));
	hw_state->pll0 &= PORT_PLL_M2_MASK;

	hw_state->pll1 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 1));
	hw_state->pll1 &= PORT_PLL_N_MASK;

	hw_state->pll2 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 2));
	hw_state->pll2 &= PORT_PLL_M2_FRAC_MASK;

	hw_state->pll3 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 3));
	hw_state->pll3 &= PORT_PLL_M2_FRAC_ENABLE;

	hw_state->pll6 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 6));
	hw_state->pll6 &= PORT_PLL_PROP_COEFF_MASK |
			  PORT_PLL_INT_COEFF_MASK |
			  PORT_PLL_GAIN_CTL_MASK;

	hw_state->pll8 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 8));
	hw_state->pll8 &= PORT_PLL_TARGET_CNT_MASK;

	hw_state->pll9 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 9));
	hw_state->pll9 &= PORT_PLL_LOCK_THRESHOLD_MASK;

	hw_state->pll10 = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PLL(phy, ch, 10));
	hw_state->pll10 &= PORT_PLL_DCO_AMP_OVR_EN_H |
			   PORT_PLL_DCO_AMP_MASK;

	/*
	 * While we ग_लिखो to the group रेजिस्टर to program all lanes at once we
	 * can पढ़ो only lane रेजिस्टरs. We configure all lanes the same way, so
	 * here just पढ़ो out lanes 0/1 and output a note अगर lanes 2/3 dअगरfer.
	 */
	hw_state->pcsdw12 = पूर्णांकel_de_पढ़ो(dev_priv,
					  BXT_PORT_PCS_DW12_LN01(phy, ch));
	अगर (पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PCS_DW12_LN23(phy, ch)) != hw_state->pcsdw12)
		drm_dbg(&dev_priv->drm,
			"lane stagger config different for lane 01 (%08x) and 23 (%08x)\n",
			hw_state->pcsdw12,
			पूर्णांकel_de_पढ़ो(dev_priv,
				      BXT_PORT_PCS_DW12_LN23(phy, ch)));
	hw_state->pcsdw12 &= LANE_STAGGER_MASK | LANESTAGGER_STRAP_OVRD;

	ret = true;

out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस ret;
पूर्ण

/* bxt घड़ी parameters */
काष्ठा bxt_clk_भाग अणु
	पूर्णांक घड़ी;
	u32 p1;
	u32 p2;
	u32 m2_पूर्णांक;
	u32 m2_frac;
	bool m2_frac_en;
	u32 n;

	पूर्णांक vco;
पूर्ण;

/* pre-calculated values क्रम DP linkrates */
अटल स्थिर काष्ठा bxt_clk_भाग bxt_dp_clk_val[] = अणु
	अणु162000, 4, 2, 32, 1677722, 1, 1पूर्ण,
	अणु270000, 4, 1, 27,       0, 0, 1पूर्ण,
	अणु540000, 2, 1, 27,       0, 0, 1पूर्ण,
	अणु216000, 3, 2, 32, 1677722, 1, 1पूर्ण,
	अणु243000, 4, 1, 24, 1258291, 1, 1पूर्ण,
	अणु324000, 4, 1, 32, 1677722, 1, 1पूर्ण,
	अणु432000, 3, 1, 32, 1677722, 1, 1पूर्ण
पूर्ण;

अटल bool
bxt_ddi_hdmi_pll_भागiders(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  काष्ठा bxt_clk_भाग *clk_भाग)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा dpll best_घड़ी;

	/* Calculate HDMI भाग */
	/*
	 * FIXME: tie the following calculation पूर्णांकo
	 * i9xx_crtc_compute_घड़ी
	 */
	अगर (!bxt_find_best_dpll(crtc_state, &best_घड़ी)) अणु
		drm_dbg(&i915->drm, "no PLL dividers found for clock %d pipe %c\n",
			crtc_state->port_घड़ी,
			pipe_name(crtc->pipe));
		वापस false;
	पूर्ण

	clk_भाग->p1 = best_घड़ी.p1;
	clk_भाग->p2 = best_घड़ी.p2;
	drm_WARN_ON(&i915->drm, best_घड़ी.m1 != 2);
	clk_भाग->n = best_घड़ी.n;
	clk_भाग->m2_पूर्णांक = best_घड़ी.m2 >> 22;
	clk_भाग->m2_frac = best_घड़ी.m2 & ((1 << 22) - 1);
	clk_भाग->m2_frac_en = clk_भाग->m2_frac != 0;

	clk_भाग->vco = best_घड़ी.vco;

	वापस true;
पूर्ण

अटल व्योम bxt_ddi_dp_pll_भागiders(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    काष्ठा bxt_clk_भाग *clk_भाग)
अणु
	पूर्णांक घड़ी = crtc_state->port_घड़ी;
	पूर्णांक i;

	*clk_भाग = bxt_dp_clk_val[0];
	क्रम (i = 0; i < ARRAY_SIZE(bxt_dp_clk_val); ++i) अणु
		अगर (bxt_dp_clk_val[i].घड़ी == घड़ी) अणु
			*clk_भाग = bxt_dp_clk_val[i];
			अवरोध;
		पूर्ण
	पूर्ण

	clk_भाग->vco = घड़ी * 10 / 2 * clk_भाग->p1 * clk_भाग->p2;
पूर्ण

अटल bool bxt_ddi_set_dpll_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      स्थिर काष्ठा bxt_clk_भाग *clk_भाग)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_dpll_hw_state *dpll_hw_state = &crtc_state->dpll_hw_state;
	पूर्णांक घड़ी = crtc_state->port_घड़ी;
	पूर्णांक vco = clk_भाग->vco;
	u32 prop_coef, पूर्णांक_coef, gain_ctl, targ_cnt;
	u32 lanestagger;

	स_रखो(dpll_hw_state, 0, माप(*dpll_hw_state));

	अगर (vco >= 6200000 && vco <= 6700000) अणु
		prop_coef = 4;
		पूर्णांक_coef = 9;
		gain_ctl = 3;
		targ_cnt = 8;
	पूर्ण अन्यथा अगर ((vco > 5400000 && vco < 6200000) ||
			(vco >= 4800000 && vco < 5400000)) अणु
		prop_coef = 5;
		पूर्णांक_coef = 11;
		gain_ctl = 3;
		targ_cnt = 9;
	पूर्ण अन्यथा अगर (vco == 5400000) अणु
		prop_coef = 3;
		पूर्णांक_coef = 8;
		gain_ctl = 1;
		targ_cnt = 9;
	पूर्ण अन्यथा अणु
		drm_err(&i915->drm, "Invalid VCO\n");
		वापस false;
	पूर्ण

	अगर (घड़ी > 270000)
		lanestagger = 0x18;
	अन्यथा अगर (घड़ी > 135000)
		lanestagger = 0x0d;
	अन्यथा अगर (घड़ी > 67000)
		lanestagger = 0x07;
	अन्यथा अगर (घड़ी > 33000)
		lanestagger = 0x04;
	अन्यथा
		lanestagger = 0x02;

	dpll_hw_state->ebb0 = PORT_PLL_P1(clk_भाग->p1) | PORT_PLL_P2(clk_भाग->p2);
	dpll_hw_state->pll0 = clk_भाग->m2_पूर्णांक;
	dpll_hw_state->pll1 = PORT_PLL_N(clk_भाग->n);
	dpll_hw_state->pll2 = clk_भाग->m2_frac;

	अगर (clk_भाग->m2_frac_en)
		dpll_hw_state->pll3 = PORT_PLL_M2_FRAC_ENABLE;

	dpll_hw_state->pll6 = prop_coef | PORT_PLL_INT_COEFF(पूर्णांक_coef);
	dpll_hw_state->pll6 |= PORT_PLL_GAIN_CTL(gain_ctl);

	dpll_hw_state->pll8 = targ_cnt;

	dpll_hw_state->pll9 = 5 << PORT_PLL_LOCK_THRESHOLD_SHIFT;

	dpll_hw_state->pll10 =
		PORT_PLL_DCO_AMP(PORT_PLL_DCO_AMP_DEFAULT)
		| PORT_PLL_DCO_AMP_OVR_EN_H;

	dpll_hw_state->ebb4 = PORT_PLL_10BIT_CLK_ENABLE;

	dpll_hw_state->pcsdw12 = LANESTAGGER_STRAP_OVRD | lanestagger;

	वापस true;
पूर्ण

अटल bool
bxt_ddi_dp_set_dpll_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा bxt_clk_भाग clk_भाग = अणुपूर्ण;

	bxt_ddi_dp_pll_भागiders(crtc_state, &clk_भाग);

	वापस bxt_ddi_set_dpll_hw_state(crtc_state, &clk_भाग);
पूर्ण

अटल bool
bxt_ddi_hdmi_set_dpll_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा bxt_clk_भाग clk_भाग = अणुपूर्ण;

	bxt_ddi_hdmi_pll_भागiders(crtc_state, &clk_भाग);

	वापस bxt_ddi_set_dpll_hw_state(crtc_state, &clk_भाग);
पूर्ण

अटल पूर्णांक bxt_ddi_pll_get_freq(काष्ठा drm_i915_निजी *i915,
				स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	काष्ठा dpll घड़ी;

	घड़ी.m1 = 2;
	घड़ी.m2 = (pll_state->pll0 & PORT_PLL_M2_MASK) << 22;
	अगर (pll_state->pll3 & PORT_PLL_M2_FRAC_ENABLE)
		घड़ी.m2 |= pll_state->pll2 & PORT_PLL_M2_FRAC_MASK;
	घड़ी.n = (pll_state->pll1 & PORT_PLL_N_MASK) >> PORT_PLL_N_SHIFT;
	घड़ी.p1 = (pll_state->ebb0 & PORT_PLL_P1_MASK) >> PORT_PLL_P1_SHIFT;
	घड़ी.p2 = (pll_state->ebb0 & PORT_PLL_P2_MASK) >> PORT_PLL_P2_SHIFT;

	वापस chv_calc_dpll_params(i915->dpll.ref_clks.nssc, &घड़ी);
पूर्ण

अटल bool bxt_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_shared_dpll *pll;
	क्रमागत पूर्णांकel_dpll_id id;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI) &&
	    !bxt_ddi_hdmi_set_dpll_hw_state(crtc_state))
		वापस false;

	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state) &&
	    !bxt_ddi_dp_set_dpll_hw_state(crtc_state))
		वापस false;

	/* 1:1 mapping between ports and PLLs */
	id = (क्रमागत पूर्णांकel_dpll_id) encoder->port;
	pll = पूर्णांकel_get_shared_dpll_by_id(dev_priv, id);

	drm_dbg_kms(&dev_priv->drm, "[CRTC:%d:%s] using pre-allocated %s\n",
		    crtc->base.base.id, crtc->base.name, pll->info->name);

	पूर्णांकel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	वापस true;
पूर्ण

अटल व्योम bxt_update_dpll_ref_clks(काष्ठा drm_i915_निजी *i915)
अणु
	i915->dpll.ref_clks.ssc = 100000;
	i915->dpll.ref_clks.nssc = 100000;
	/* DSI non-SSC ref 19.2MHz */
पूर्ण

अटल व्योम bxt_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	drm_dbg_kms(&dev_priv->drm, "dpll_hw_state: ebb0: 0x%x, ebb4: 0x%x,"
		    "pll0: 0x%x, pll1: 0x%x, pll2: 0x%x, pll3: 0x%x, "
		    "pll6: 0x%x, pll8: 0x%x, pll9: 0x%x, pll10: 0x%x, pcsdw12: 0x%x\n",
		    hw_state->ebb0,
		    hw_state->ebb4,
		    hw_state->pll0,
		    hw_state->pll1,
		    hw_state->pll2,
		    hw_state->pll3,
		    hw_state->pll6,
		    hw_state->pll8,
		    hw_state->pll9,
		    hw_state->pll10,
		    hw_state->pcsdw12);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs bxt_ddi_pll_funcs = अणु
	.enable = bxt_ddi_pll_enable,
	.disable = bxt_ddi_pll_disable,
	.get_hw_state = bxt_ddi_pll_get_hw_state,
	.get_freq = bxt_ddi_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा dpll_info bxt_plls[] = अणु
	अणु "PORT PLL A", &bxt_ddi_pll_funcs, DPLL_ID_SKL_DPLL0, 0 पूर्ण,
	अणु "PORT PLL B", &bxt_ddi_pll_funcs, DPLL_ID_SKL_DPLL1, 0 पूर्ण,
	अणु "PORT PLL C", &bxt_ddi_pll_funcs, DPLL_ID_SKL_DPLL2, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr bxt_pll_mgr = अणु
	.dpll_info = bxt_plls,
	.get_dplls = bxt_get_dpll,
	.put_dplls = पूर्णांकel_put_dpll,
	.update_ref_clks = bxt_update_dpll_ref_clks,
	.dump_hw_state = bxt_dump_hw_state,
पूर्ण;

अटल व्योम cnl_ddi_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	u32 val;

	/* 1. Enable DPLL घातer in DPLL_ENABLE. */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_DPLL_ENABLE(id));
	val |= PLL_POWER_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_DPLL_ENABLE(id), val);

	/* 2. Wait क्रम DPLL घातer state enabled in DPLL_ENABLE. */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, CNL_DPLL_ENABLE(id),
				  PLL_POWER_STATE, 5))
		drm_err(&dev_priv->drm, "PLL %d Power not enabled\n", id);

	/*
	 * 3. Configure DPLL_CFGCR0 to set SSC enable/disable,
	 * select DP mode, and set DP link rate.
	 */
	val = pll->state.hw_state.cfgcr0;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_DPLL_CFGCR0(id), val);

	/* 4. Reab back to ensure ग_लिखोs completed */
	पूर्णांकel_de_posting_पढ़ो(dev_priv, CNL_DPLL_CFGCR0(id));

	/* 3. Configure DPLL_CFGCR0 */
	/* Aव्योम touch CFGCR1 अगर HDMI mode is not enabled */
	अगर (pll->state.hw_state.cfgcr0 & DPLL_CFGCR0_HDMI_MODE) अणु
		val = pll->state.hw_state.cfgcr1;
		पूर्णांकel_de_ग_लिखो(dev_priv, CNL_DPLL_CFGCR1(id), val);
		/* 4. Reab back to ensure ग_लिखोs completed */
		पूर्णांकel_de_posting_पढ़ो(dev_priv, CNL_DPLL_CFGCR1(id));
	पूर्ण

	/*
	 * 5. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence Beक्रमe Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we करो nothing here.
	 */

	/* 6. Enable DPLL in DPLL_ENABLE. */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_DPLL_ENABLE(id));
	val |= PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_DPLL_ENABLE(id), val);

	/* 7. Wait क्रम PLL lock status in DPLL_ENABLE. */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, CNL_DPLL_ENABLE(id), PLL_LOCK, 5))
		drm_err(&dev_priv->drm, "PLL %d not locked\n", id);

	/*
	 * 8. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence After Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we करो nothing here.
	 */

	/*
	 * 9. turn on the घड़ी क्रम the DDI and map the DPLL to the DDI
	 * Done at पूर्णांकel_ddi_clk_select
	 */
पूर्ण

अटल व्योम cnl_ddi_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	u32 val;

	/*
	 * 1. Configure DPCLKA_CFGCR0 to turn off the घड़ी क्रम the DDI.
	 * Done at पूर्णांकel_ddi_post_disable
	 */

	/*
	 * 2. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence Beक्रमe Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we करो nothing here.
	 */

	/* 3. Disable DPLL through DPLL_ENABLE. */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_DPLL_ENABLE(id));
	val &= ~PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_DPLL_ENABLE(id), val);

	/* 4. Wait क्रम PLL not locked status in DPLL_ENABLE. */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, CNL_DPLL_ENABLE(id), PLL_LOCK, 5))
		drm_err(&dev_priv->drm, "PLL %d locked\n", id);

	/*
	 * 5. If the frequency will result in a change to the voltage
	 * requirement, follow the Display Voltage Frequency Switching
	 * Sequence After Frequency Change
	 *
	 * Note: DVFS is actually handled via the cdclk code paths,
	 * hence we करो nothing here.
	 */

	/* 6. Disable DPLL घातer in DPLL_ENABLE. */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_DPLL_ENABLE(id));
	val &= ~PLL_POWER_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_DPLL_ENABLE(id), val);

	/* 7. Wait क्रम DPLL घातer state disabled in DPLL_ENABLE. */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, CNL_DPLL_ENABLE(id),
				    PLL_POWER_STATE, 5))
		drm_err(&dev_priv->drm, "PLL %d Power not disabled\n", id);
पूर्ण

अटल bool cnl_ddi_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				     काष्ठा पूर्णांकel_shared_dpll *pll,
				     काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	पूर्णांकel_wakeref_t wakeref;
	u32 val;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	ret = false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_DPLL_ENABLE(id));
	अगर (!(val & PLL_ENABLE))
		जाओ out;

	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_DPLL_CFGCR0(id));
	hw_state->cfgcr0 = val;

	/* aव्योम पढ़ोing back stale values अगर HDMI mode is not enabled */
	अगर (val & DPLL_CFGCR0_HDMI_MODE) अणु
		hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv,
						 CNL_DPLL_CFGCR1(id));
	पूर्ण
	ret = true;

out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);

	वापस ret;
पूर्ण

अटल व्योम cnl_wrpll_get_multipliers(पूर्णांक bestभाग, पूर्णांक *pभाग,
				      पूर्णांक *qभाग, पूर्णांक *kभाग)
अणु
	/* even भागiders */
	अगर (bestभाग % 2 == 0) अणु
		अगर (bestभाग == 2) अणु
			*pभाग = 2;
			*qभाग = 1;
			*kभाग = 1;
		पूर्ण अन्यथा अगर (bestभाग % 4 == 0) अणु
			*pभाग = 2;
			*qभाग = bestभाग / 4;
			*kभाग = 2;
		पूर्ण अन्यथा अगर (bestभाग % 6 == 0) अणु
			*pभाग = 3;
			*qभाग = bestभाग / 6;
			*kभाग = 2;
		पूर्ण अन्यथा अगर (bestभाग % 5 == 0) अणु
			*pभाग = 5;
			*qभाग = bestभाग / 10;
			*kभाग = 2;
		पूर्ण अन्यथा अगर (bestभाग % 14 == 0) अणु
			*pभाग = 7;
			*qभाग = bestभाग / 14;
			*kभाग = 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bestभाग == 3 || bestभाग == 5 || bestभाग == 7) अणु
			*pभाग = bestभाग;
			*qभाग = 1;
			*kभाग = 1;
		पूर्ण अन्यथा अणु /* 9, 15, 21 */
			*pभाग = bestभाग / 3;
			*qभाग = 1;
			*kभाग = 3;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cnl_wrpll_params_populate(काष्ठा skl_wrpll_params *params,
				      u32 dco_freq, u32 ref_freq,
				      पूर्णांक pभाग, पूर्णांक qभाग, पूर्णांक kभाग)
अणु
	u32 dco;

	चयन (kभाग) अणु
	हाल 1:
		params->kभाग = 1;
		अवरोध;
	हाल 2:
		params->kभाग = 2;
		अवरोध;
	हाल 3:
		params->kभाग = 4;
		अवरोध;
	शेष:
		WARN(1, "Incorrect KDiv\n");
	पूर्ण

	चयन (pभाग) अणु
	हाल 2:
		params->pभाग = 1;
		अवरोध;
	हाल 3:
		params->pभाग = 2;
		अवरोध;
	हाल 5:
		params->pभाग = 4;
		अवरोध;
	हाल 7:
		params->pभाग = 8;
		अवरोध;
	शेष:
		WARN(1, "Incorrect PDiv\n");
	पूर्ण

	WARN_ON(kभाग != 2 && qभाग != 1);

	params->qभाग_ratio = qभाग;
	params->qभाग_mode = (qभाग == 1) ? 0 : 1;

	dco = भाग_u64((u64)dco_freq << 15, ref_freq);

	params->dco_पूर्णांकeger = dco >> 15;
	params->dco_fraction = dco & 0x7fff;
पूर्ण

अटल bool
__cnl_ddi_calculate_wrpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  काष्ठा skl_wrpll_params *wrpll_params,
			  पूर्णांक ref_घड़ी)
अणु
	u32 afe_घड़ी = crtc_state->port_घड़ी * 5;
	u32 dco_min = 7998000;
	u32 dco_max = 10000000;
	u32 dco_mid = (dco_min + dco_max) / 2;
	अटल स्थिर पूर्णांक भागiders[] = अणु  2,  4,  6,  8, 10, 12,  14,  16,
					 18, 20, 24, 28, 30, 32,  36,  40,
					 42, 44, 48, 50, 52, 54,  56,  60,
					 64, 66, 68, 70, 72, 76,  78,  80,
					 84, 88, 90, 92, 96, 98, 100, 102,
					  3,  5,  7,  9, 15, 21 पूर्ण;
	u32 dco, best_dco = 0, dco_centrality = 0;
	u32 best_dco_centrality = U32_MAX; /* Spec meaning of 999999 MHz */
	पूर्णांक d, best_भाग = 0, pभाग = 0, qभाग = 0, kभाग = 0;

	क्रम (d = 0; d < ARRAY_SIZE(भागiders); d++) अणु
		dco = afe_घड़ी * भागiders[d];

		अगर ((dco <= dco_max) && (dco >= dco_min)) अणु
			dco_centrality = असल(dco - dco_mid);

			अगर (dco_centrality < best_dco_centrality) अणु
				best_dco_centrality = dco_centrality;
				best_भाग = भागiders[d];
				best_dco = dco;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (best_भाग == 0)
		वापस false;

	cnl_wrpll_get_multipliers(best_भाग, &pभाग, &qभाग, &kभाग);
	cnl_wrpll_params_populate(wrpll_params, best_dco, ref_घड़ी,
				  pभाग, qभाग, kभाग);

	वापस true;
पूर्ण

अटल bool
cnl_ddi_calculate_wrpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			काष्ठा skl_wrpll_params *wrpll_params)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);

	वापस __cnl_ddi_calculate_wrpll(crtc_state, wrpll_params,
					 i915->dpll.ref_clks.nssc);
पूर्ण

अटल bool cnl_ddi_hdmi_pll_भागiders(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 cfgcr0, cfgcr1;
	काष्ठा skl_wrpll_params wrpll_params = अणु 0, पूर्ण;

	cfgcr0 = DPLL_CFGCR0_HDMI_MODE;

	अगर (!cnl_ddi_calculate_wrpll(crtc_state, &wrpll_params))
		वापस false;

	cfgcr0 |= DPLL_CFGCR0_DCO_FRACTION(wrpll_params.dco_fraction) |
		wrpll_params.dco_पूर्णांकeger;

	cfgcr1 = DPLL_CFGCR1_QDIV_RATIO(wrpll_params.qभाग_ratio) |
		DPLL_CFGCR1_QDIV_MODE(wrpll_params.qभाग_mode) |
		DPLL_CFGCR1_KDIV(wrpll_params.kभाग) |
		DPLL_CFGCR1_PDIV(wrpll_params.pभाग) |
		DPLL_CFGCR1_CENTRAL_FREQ;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	crtc_state->dpll_hw_state.cfgcr0 = cfgcr0;
	crtc_state->dpll_hw_state.cfgcr1 = cfgcr1;
	वापस true;
पूर्ण

/*
 * Display WA #22010492432: ehl, tgl
 * Program half of the nominal DCO भागider fraction value.
 */
अटल bool
ehl_combo_pll_भाग_frac_wa_needed(काष्ठा drm_i915_निजी *i915)
अणु
	वापस ((IS_PLATFORM(i915, INTEL_ELKHARTLAKE) &&
		 IS_JSL_EHL_REVID(i915, EHL_REVID_B0, REVID_FOREVER)) ||
		 IS_TIGERLAKE(i915)) &&
		 i915->dpll.ref_clks.nssc == 38400;
पूर्ण

अटल पूर्णांक __cnl_ddi_wrpll_get_freq(काष्ठा drm_i915_निजी *dev_priv,
				    स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				    स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state,
				    पूर्णांक ref_घड़ी)
अणु
	u32 dco_fraction;
	u32 p0, p1, p2, dco_freq;

	p0 = pll_state->cfgcr1 & DPLL_CFGCR1_PDIV_MASK;
	p2 = pll_state->cfgcr1 & DPLL_CFGCR1_KDIV_MASK;

	अगर (pll_state->cfgcr1 & DPLL_CFGCR1_QDIV_MODE(1))
		p1 = (pll_state->cfgcr1 & DPLL_CFGCR1_QDIV_RATIO_MASK) >>
			DPLL_CFGCR1_QDIV_RATIO_SHIFT;
	अन्यथा
		p1 = 1;


	चयन (p0) अणु
	हाल DPLL_CFGCR1_PDIV_2:
		p0 = 2;
		अवरोध;
	हाल DPLL_CFGCR1_PDIV_3:
		p0 = 3;
		अवरोध;
	हाल DPLL_CFGCR1_PDIV_5:
		p0 = 5;
		अवरोध;
	हाल DPLL_CFGCR1_PDIV_7:
		p0 = 7;
		अवरोध;
	पूर्ण

	चयन (p2) अणु
	हाल DPLL_CFGCR1_KDIV_1:
		p2 = 1;
		अवरोध;
	हाल DPLL_CFGCR1_KDIV_2:
		p2 = 2;
		अवरोध;
	हाल DPLL_CFGCR1_KDIV_3:
		p2 = 3;
		अवरोध;
	पूर्ण

	dco_freq = (pll_state->cfgcr0 & DPLL_CFGCR0_DCO_INTEGER_MASK) *
		   ref_घड़ी;

	dco_fraction = (pll_state->cfgcr0 & DPLL_CFGCR0_DCO_FRACTION_MASK) >>
		       DPLL_CFGCR0_DCO_FRACTION_SHIFT;

	अगर (ehl_combo_pll_भाग_frac_wa_needed(dev_priv))
		dco_fraction *= 2;

	dco_freq += (dco_fraction * ref_घड़ी) / 0x8000;

	अगर (drm_WARN_ON(&dev_priv->drm, p0 == 0 || p1 == 0 || p2 == 0))
		वापस 0;

	वापस dco_freq / (p0 * p1 * p2 * 5);
पूर्ण

अटल पूर्णांक cnl_ddi_wrpll_get_freq(काष्ठा drm_i915_निजी *i915,
				  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				  स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	वापस __cnl_ddi_wrpll_get_freq(i915, pll, pll_state,
					i915->dpll.ref_clks.nssc);
पूर्ण

अटल bool
cnl_ddi_dp_set_dpll_hw_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 cfgcr0;

	cfgcr0 = DPLL_CFGCR0_SSC_ENABLE;

	चयन (crtc_state->port_घड़ी / 2) अणु
	हाल 81000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_810;
		अवरोध;
	हाल 135000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_1350;
		अवरोध;
	हाल 270000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_2700;
		अवरोध;
		/* eDP 1.4 rates */
	हाल 162000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_1620;
		अवरोध;
	हाल 108000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_1080;
		अवरोध;
	हाल 216000:
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_2160;
		अवरोध;
	हाल 324000:
		/* Some SKUs may require elevated I/O voltage to support this */
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_3240;
		अवरोध;
	हाल 405000:
		/* Some SKUs may require elevated I/O voltage to support this */
		cfgcr0 |= DPLL_CFGCR0_LINK_RATE_4050;
		अवरोध;
	पूर्ण

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	crtc_state->dpll_hw_state.cfgcr0 = cfgcr0;

	वापस true;
पूर्ण

अटल पूर्णांक cnl_ddi_lcpll_get_freq(काष्ठा drm_i915_निजी *i915,
				  स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				  स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	पूर्णांक link_घड़ी = 0;

	चयन (pll_state->cfgcr0 & DPLL_CFGCR0_LINK_RATE_MASK) अणु
	हाल DPLL_CFGCR0_LINK_RATE_810:
		link_घड़ी = 81000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_1080:
		link_घड़ी = 108000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_1350:
		link_घड़ी = 135000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_1620:
		link_घड़ी = 162000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_2160:
		link_घड़ी = 216000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_2700:
		link_घड़ी = 270000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_3240:
		link_घड़ी = 324000;
		अवरोध;
	हाल DPLL_CFGCR0_LINK_RATE_4050:
		link_घड़ी = 405000;
		अवरोध;
	शेष:
		drm_WARN(&i915->drm, 1, "Unsupported link rate\n");
		अवरोध;
	पूर्ण

	वापस link_घड़ी * 2;
पूर्ण

अटल bool cnl_get_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_shared_dpll *pll;
	bool bret;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) अणु
		bret = cnl_ddi_hdmi_pll_भागiders(crtc_state);
		अगर (!bret) अणु
			drm_dbg_kms(&i915->drm,
				    "Could not get HDMI pll dividers.\n");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state)) अणु
		bret = cnl_ddi_dp_set_dpll_hw_state(crtc_state);
		अगर (!bret) अणु
			drm_dbg_kms(&i915->drm,
				    "Could not set DP dpll HW state.\n");
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&i915->drm,
			    "Skip DPLL setup for output_types 0x%x\n",
			    crtc_state->output_types);
		वापस false;
	पूर्ण

	pll = पूर्णांकel_find_shared_dpll(state, crtc,
				     &crtc_state->dpll_hw_state,
				     BIT(DPLL_ID_SKL_DPLL2) |
				     BIT(DPLL_ID_SKL_DPLL1) |
				     BIT(DPLL_ID_SKL_DPLL0));
	अगर (!pll) अणु
		drm_dbg_kms(&i915->drm, "No PLL selected\n");
		वापस false;
	पूर्ण

	पूर्णांकel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	वापस true;
पूर्ण

अटल पूर्णांक cnl_ddi_pll_get_freq(काष्ठा drm_i915_निजी *i915,
				स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	अगर (pll_state->cfgcr0 & DPLL_CFGCR0_HDMI_MODE)
		वापस cnl_ddi_wrpll_get_freq(i915, pll, pll_state);
	अन्यथा
		वापस cnl_ddi_lcpll_get_freq(i915, pll, pll_state);
पूर्ण

अटल व्योम cnl_update_dpll_ref_clks(काष्ठा drm_i915_निजी *i915)
अणु
	/* No SSC reference */
	i915->dpll.ref_clks.nssc = i915->cdclk.hw.ref;
पूर्ण

अटल व्योम cnl_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	drm_dbg_kms(&dev_priv->drm, "dpll_hw_state: "
		    "cfgcr0: 0x%x, cfgcr1: 0x%x\n",
		    hw_state->cfgcr0,
		    hw_state->cfgcr1);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs cnl_ddi_pll_funcs = अणु
	.enable = cnl_ddi_pll_enable,
	.disable = cnl_ddi_pll_disable,
	.get_hw_state = cnl_ddi_pll_get_hw_state,
	.get_freq = cnl_ddi_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा dpll_info cnl_plls[] = अणु
	अणु "DPLL 0", &cnl_ddi_pll_funcs, DPLL_ID_SKL_DPLL0, 0 पूर्ण,
	अणु "DPLL 1", &cnl_ddi_pll_funcs, DPLL_ID_SKL_DPLL1, 0 पूर्ण,
	अणु "DPLL 2", &cnl_ddi_pll_funcs, DPLL_ID_SKL_DPLL2, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr cnl_pll_mgr = अणु
	.dpll_info = cnl_plls,
	.get_dplls = cnl_get_dpll,
	.put_dplls = पूर्णांकel_put_dpll,
	.update_ref_clks = cnl_update_dpll_ref_clks,
	.dump_hw_state = cnl_dump_hw_state,
पूर्ण;

काष्ठा icl_combo_pll_params अणु
	पूर्णांक घड़ी;
	काष्ठा skl_wrpll_params wrpll;
पूर्ण;

/*
 * These values alrea alपढ़ोy adjusted: they're the bits we ग_लिखो to the
 * रेजिस्टरs, not the logical values.
 */
अटल स्थिर काष्ठा icl_combo_pll_params icl_dp_combo_pll_24MHz_values[] = अणु
	अणु 540000,
	  अणु .dco_पूर्णांकeger = 0x151, .dco_fraction = 0x4000,		/* [0]: 5.4 */
	    .pभाग = 0x2 /* 3 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 270000,
	  अणु .dco_पूर्णांकeger = 0x151, .dco_fraction = 0x4000,		/* [1]: 2.7 */
	    .pभाग = 0x2 /* 3 */, .kभाग = 2, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 162000,
	  अणु .dco_पूर्णांकeger = 0x151, .dco_fraction = 0x4000,		/* [2]: 1.62 */
	    .pभाग = 0x4 /* 5 */, .kभाग = 2, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 324000,
	  अणु .dco_पूर्णांकeger = 0x151, .dco_fraction = 0x4000,		/* [3]: 3.24 */
	    .pभाग = 0x4 /* 5 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 216000,
	  अणु .dco_पूर्णांकeger = 0x168, .dco_fraction = 0x0000,		/* [4]: 2.16 */
	    .pभाग = 0x1 /* 2 */, .kभाग = 2, .qभाग_mode = 1, .qभाग_ratio = 2, पूर्ण, पूर्ण,
	अणु 432000,
	  अणु .dco_पूर्णांकeger = 0x168, .dco_fraction = 0x0000,		/* [5]: 4.32 */
	    .pभाग = 0x1 /* 2 */, .kभाग = 2, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 648000,
	  अणु .dco_पूर्णांकeger = 0x195, .dco_fraction = 0x0000,		/* [6]: 6.48 */
	    .pभाग = 0x2 /* 3 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 810000,
	  अणु .dco_पूर्णांकeger = 0x151, .dco_fraction = 0x4000,		/* [7]: 8.1 */
	    .pभाग = 0x1 /* 2 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
पूर्ण;


/* Also used क्रम 38.4 MHz values. */
अटल स्थिर काष्ठा icl_combo_pll_params icl_dp_combo_pll_19_2MHz_values[] = अणु
	अणु 540000,
	  अणु .dco_पूर्णांकeger = 0x1A5, .dco_fraction = 0x7000,		/* [0]: 5.4 */
	    .pभाग = 0x2 /* 3 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 270000,
	  अणु .dco_पूर्णांकeger = 0x1A5, .dco_fraction = 0x7000,		/* [1]: 2.7 */
	    .pभाग = 0x2 /* 3 */, .kभाग = 2, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 162000,
	  अणु .dco_पूर्णांकeger = 0x1A5, .dco_fraction = 0x7000,		/* [2]: 1.62 */
	    .pभाग = 0x4 /* 5 */, .kभाग = 2, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 324000,
	  अणु .dco_पूर्णांकeger = 0x1A5, .dco_fraction = 0x7000,		/* [3]: 3.24 */
	    .pभाग = 0x4 /* 5 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 216000,
	  अणु .dco_पूर्णांकeger = 0x1C2, .dco_fraction = 0x0000,		/* [4]: 2.16 */
	    .pभाग = 0x1 /* 2 */, .kभाग = 2, .qभाग_mode = 1, .qभाग_ratio = 2, पूर्ण, पूर्ण,
	अणु 432000,
	  अणु .dco_पूर्णांकeger = 0x1C2, .dco_fraction = 0x0000,		/* [5]: 4.32 */
	    .pभाग = 0x1 /* 2 */, .kभाग = 2, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 648000,
	  अणु .dco_पूर्णांकeger = 0x1FA, .dco_fraction = 0x2000,		/* [6]: 6.48 */
	    .pभाग = 0x2 /* 3 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
	अणु 810000,
	  अणु .dco_पूर्णांकeger = 0x1A5, .dco_fraction = 0x7000,		/* [7]: 8.1 */
	    .pभाग = 0x1 /* 2 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0, पूर्ण, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा skl_wrpll_params icl_tbt_pll_24MHz_values = अणु
	.dco_पूर्णांकeger = 0x151, .dco_fraction = 0x4000,
	.pभाग = 0x4 /* 5 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0,
पूर्ण;

अटल स्थिर काष्ठा skl_wrpll_params icl_tbt_pll_19_2MHz_values = अणु
	.dco_पूर्णांकeger = 0x1A5, .dco_fraction = 0x7000,
	.pभाग = 0x4 /* 5 */, .kभाग = 1, .qभाग_mode = 0, .qभाग_ratio = 0,
पूर्ण;

अटल स्थिर काष्ठा skl_wrpll_params tgl_tbt_pll_19_2MHz_values = अणु
	.dco_पूर्णांकeger = 0x54, .dco_fraction = 0x3000,
	/* the following params are unused */
	.pभाग = 0, .kभाग = 0, .qभाग_mode = 0, .qभाग_ratio = 0,
पूर्ण;

अटल स्थिर काष्ठा skl_wrpll_params tgl_tbt_pll_24MHz_values = अणु
	.dco_पूर्णांकeger = 0x43, .dco_fraction = 0x4000,
	/* the following params are unused */
पूर्ण;

अटल bool icl_calc_dp_combo_pll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  काष्ठा skl_wrpll_params *pll_params)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	स्थिर काष्ठा icl_combo_pll_params *params =
		dev_priv->dpll.ref_clks.nssc == 24000 ?
		icl_dp_combo_pll_24MHz_values :
		icl_dp_combo_pll_19_2MHz_values;
	पूर्णांक घड़ी = crtc_state->port_घड़ी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(icl_dp_combo_pll_24MHz_values); i++) अणु
		अगर (घड़ी == params[i].घड़ी) अणु
			*pll_params = params[i].wrpll;
			वापस true;
		पूर्ण
	पूर्ण

	MISSING_CASE(घड़ी);
	वापस false;
पूर्ण

अटल bool icl_calc_tbt_pll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     काष्ठा skl_wrpll_params *pll_params)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		चयन (dev_priv->dpll.ref_clks.nssc) अणु
		शेष:
			MISSING_CASE(dev_priv->dpll.ref_clks.nssc);
			fallthrough;
		हाल 19200:
		हाल 38400:
			*pll_params = tgl_tbt_pll_19_2MHz_values;
			अवरोध;
		हाल 24000:
			*pll_params = tgl_tbt_pll_24MHz_values;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (dev_priv->dpll.ref_clks.nssc) अणु
		शेष:
			MISSING_CASE(dev_priv->dpll.ref_clks.nssc);
			fallthrough;
		हाल 19200:
		हाल 38400:
			*pll_params = icl_tbt_pll_19_2MHz_values;
			अवरोध;
		हाल 24000:
			*pll_params = icl_tbt_pll_24MHz_values;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक icl_ddi_tbt_pll_get_freq(काष्ठा drm_i915_निजी *i915,
				    स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				    स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	/*
	 * The PLL outमाला_दो multiple frequencies at the same समय, selection is
	 * made at DDI घड़ी mux level.
	 */
	drm_WARN_ON(&i915->drm, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक icl_wrpll_ref_घड़ी(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ref_घड़ी = i915->dpll.ref_clks.nssc;

	/*
	 * For ICL+, the spec states: अगर reference frequency is 38.4,
	 * use 19.2 because the DPLL स्वतःmatically भागides that by 2.
	 */
	अगर (ref_घड़ी == 38400)
		ref_घड़ी = 19200;

	वापस ref_घड़ी;
पूर्ण

अटल bool
icl_calc_wrpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
	       काष्ठा skl_wrpll_params *wrpll_params)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);

	वापस __cnl_ddi_calculate_wrpll(crtc_state, wrpll_params,
					 icl_wrpll_ref_घड़ी(i915));
पूर्ण

अटल पूर्णांक icl_ddi_combo_pll_get_freq(काष्ठा drm_i915_निजी *i915,
				      स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	वापस __cnl_ddi_wrpll_get_freq(i915, pll, pll_state,
					icl_wrpll_ref_घड़ी(i915));
पूर्ण

अटल व्योम icl_calc_dpll_state(काष्ठा drm_i915_निजी *i915,
				स्थिर काष्ठा skl_wrpll_params *pll_params,
				काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	u32 dco_fraction = pll_params->dco_fraction;

	स_रखो(pll_state, 0, माप(*pll_state));

	अगर (ehl_combo_pll_भाग_frac_wa_needed(i915))
		dco_fraction = DIV_ROUND_CLOSEST(dco_fraction, 2);

	pll_state->cfgcr0 = DPLL_CFGCR0_DCO_FRACTION(dco_fraction) |
			    pll_params->dco_पूर्णांकeger;

	pll_state->cfgcr1 = DPLL_CFGCR1_QDIV_RATIO(pll_params->qभाग_ratio) |
			    DPLL_CFGCR1_QDIV_MODE(pll_params->qभाग_mode) |
			    DPLL_CFGCR1_KDIV(pll_params->kभाग) |
			    DPLL_CFGCR1_PDIV(pll_params->pभाग);

	अगर (DISPLAY_VER(i915) >= 12)
		pll_state->cfgcr1 |= TGL_DPLL_CFGCR1_CFSELOVRD_NORMAL_XTAL;
	अन्यथा
		pll_state->cfgcr1 |= DPLL_CFGCR1_CENTRAL_FREQ_8400;
पूर्ण

अटल क्रमागत tc_port icl_pll_id_to_tc_port(क्रमागत पूर्णांकel_dpll_id id)
अणु
	वापस id - DPLL_ID_ICL_MGPLL1;
पूर्ण

क्रमागत पूर्णांकel_dpll_id icl_tc_port_to_pll_id(क्रमागत tc_port tc_port)
अणु
	वापस tc_port + DPLL_ID_ICL_MGPLL1;
पूर्ण

अटल bool icl_mg_pll_find_भागisors(पूर्णांक घड़ी_khz, bool is_dp, bool use_ssc,
				     u32 *target_dco_khz,
				     काष्ठा पूर्णांकel_dpll_hw_state *state,
				     bool is_dkl)
अणु
	u32 dco_min_freq, dco_max_freq;
	पूर्णांक भाग1_vals[] = अणु7, 5, 3, 2पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक भाग2;

	dco_min_freq = is_dp ? 8100000 : use_ssc ? 8000000 : 7992000;
	dco_max_freq = is_dp ? 8100000 : 10000000;

	क्रम (i = 0; i < ARRAY_SIZE(भाग1_vals); i++) अणु
		पूर्णांक भाग1 = भाग1_vals[i];

		क्रम (भाग2 = 10; भाग2 > 0; भाग2--) अणु
			पूर्णांक dco = भाग1 * भाग2 * घड़ी_khz * 5;
			पूर्णांक a_भागratio, tlinedrv, inमाला_दोel;
			u32 hsभाग;

			अगर (dco < dco_min_freq || dco > dco_max_freq)
				जारी;

			अगर (भाग2 >= 2) अणु
				/*
				 * Note: a_भागratio not matching TGL BSpec
				 * algorithm but matching hardcoded values and
				 * working on HW क्रम DP alt-mode at least
				 */
				a_भागratio = is_dp ? 10 : 5;
				tlinedrv = is_dkl ? 1 : 2;
			पूर्ण अन्यथा अणु
				a_भागratio = 5;
				tlinedrv = 0;
			पूर्ण
			inमाला_दोel = is_dp ? 0 : 1;

			चयन (भाग1) अणु
			शेष:
				MISSING_CASE(भाग1);
				fallthrough;
			हाल 2:
				hsभाग = MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_2;
				अवरोध;
			हाल 3:
				hsभाग = MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_3;
				अवरोध;
			हाल 5:
				hsभाग = MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_5;
				अवरोध;
			हाल 7:
				hsभाग = MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_7;
				अवरोध;
			पूर्ण

			*target_dco_khz = dco;

			state->mg_refclkin_ctl = MG_REFCLKIN_CTL_OD_2_MUX(1);

			state->mg_clktop2_coreclkctl1 =
				MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO(a_भागratio);

			state->mg_clktop2_hsclkctl =
				MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL(tlinedrv) |
				MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL(inमाला_दोel) |
				hsभाग |
				MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO(भाग2);

			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/*
 * The specअगरication क्रम this function uses real numbers, so the math had to be
 * adapted to पूर्णांकeger-only calculation, that's why it looks so dअगरferent.
 */
अटल bool icl_calc_mg_pll_state(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक refclk_khz = dev_priv->dpll.ref_clks.nssc;
	पूर्णांक घड़ी = crtc_state->port_घड़ी;
	u32 dco_khz, m1भाग, m2भाग_पूर्णांक, m2भाग_rem, m2भाग_frac;
	u32 iref_nभाग, iref_trim, iref_pulse_w;
	u32 prop_coeff, पूर्णांक_coeff;
	u32 tdc_tarअ_लोnt, feedfwgain;
	u64 ssc_stepsize, ssc_steplen, ssc_steplog;
	u64 पंचांगp;
	bool use_ssc = false;
	bool is_dp = !पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI);
	bool is_dkl = DISPLAY_VER(dev_priv) >= 12;

	स_रखो(pll_state, 0, माप(*pll_state));

	अगर (!icl_mg_pll_find_भागisors(घड़ी, is_dp, use_ssc, &dco_khz,
				      pll_state, is_dkl)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Failed to find divisors for clock %d\n", घड़ी);
		वापस false;
	पूर्ण

	m1भाग = 2;
	m2भाग_पूर्णांक = dco_khz / (refclk_khz * m1भाग);
	अगर (m2भाग_पूर्णांक > 255) अणु
		अगर (!is_dkl) अणु
			m1भाग = 4;
			m2भाग_पूर्णांक = dco_khz / (refclk_khz * m1भाग);
		पूर्ण

		अगर (m2भाग_पूर्णांक > 255) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Failed to find mdiv for clock %d\n",
				    घड़ी);
			वापस false;
		पूर्ण
	पूर्ण
	m2भाग_rem = dco_khz % (refclk_khz * m1भाग);

	पंचांगp = (u64)m2भाग_rem * (1 << 22);
	करो_भाग(पंचांगp, refclk_khz * m1भाग);
	m2भाग_frac = पंचांगp;

	चयन (refclk_khz) अणु
	हाल 19200:
		iref_nभाग = 1;
		iref_trim = 28;
		iref_pulse_w = 1;
		अवरोध;
	हाल 24000:
		iref_nभाग = 1;
		iref_trim = 25;
		iref_pulse_w = 2;
		अवरोध;
	हाल 38400:
		iref_nभाग = 2;
		iref_trim = 28;
		iref_pulse_w = 1;
		अवरोध;
	शेष:
		MISSING_CASE(refclk_khz);
		वापस false;
	पूर्ण

	/*
	 * tdc_res = 0.000003
	 * tdc_tarअ_लोnt = पूर्णांक(2 / (tdc_res * 8 * 50 * 1.1) / refclk_mhz + 0.5)
	 *
	 * The multiplication by 1000 is due to refclk MHz to KHz conversion. It
	 * was supposed to be a भागision, but we rearranged the operations of
	 * the क्रमmula to aव्योम early भागisions so we करोn't multiply the
	 * rounding errors.
	 *
	 * 0.000003 * 8 * 50 * 1.1 = 0.00132, also known as 132 / 100000, which
	 * we also rearrange to work with पूर्णांकegers.
	 *
	 * The 0.5 transक्रमmed to 5 results in a multiplication by 10 and the
	 * last भागision by 10.
	 */
	tdc_tarअ_लोnt = (2 * 1000 * 100000 * 10 / (132 * refclk_khz) + 5) / 10;

	/*
	 * Here we भागide dco_khz by 10 in order to allow the भागidend to fit in
	 * 32 bits. That's not a problem since we round the भागision करोwn
	 * anyway.
	 */
	feedfwgain = (use_ssc || m2भाग_rem > 0) ?
		m1भाग * 1000000 * 100 / (dco_khz * 3 / 10) : 0;

	अगर (dco_khz >= 9000000) अणु
		prop_coeff = 5;
		पूर्णांक_coeff = 10;
	पूर्ण अन्यथा अणु
		prop_coeff = 4;
		पूर्णांक_coeff = 8;
	पूर्ण

	अगर (use_ssc) अणु
		पंचांगp = mul_u32_u32(dco_khz, 47 * 32);
		करो_भाग(पंचांगp, refclk_khz * m1भाग * 10000);
		ssc_stepsize = पंचांगp;

		पंचांगp = mul_u32_u32(dco_khz, 1000);
		ssc_steplen = DIV_ROUND_UP_ULL(पंचांगp, 32 * 2 * 32);
	पूर्ण अन्यथा अणु
		ssc_stepsize = 0;
		ssc_steplen = 0;
	पूर्ण
	ssc_steplog = 4;

	/* ग_लिखो pll_state calculations */
	अगर (is_dkl) अणु
		pll_state->mg_pll_भाग0 = DKL_PLL_DIV0_INTEG_COEFF(पूर्णांक_coeff) |
					 DKL_PLL_DIV0_PROP_COEFF(prop_coeff) |
					 DKL_PLL_DIV0_FBPREDIV(m1भाग) |
					 DKL_PLL_DIV0_FBDIV_INT(m2भाग_पूर्णांक);

		pll_state->mg_pll_भाग1 = DKL_PLL_DIV1_IREF_TRIM(iref_trim) |
					 DKL_PLL_DIV1_TDC_TARGET_CNT(tdc_tarअ_लोnt);

		pll_state->mg_pll_ssc = DKL_PLL_SSC_IREF_NDIV_RATIO(iref_nभाग) |
					DKL_PLL_SSC_STEP_LEN(ssc_steplen) |
					DKL_PLL_SSC_STEP_NUM(ssc_steplog) |
					(use_ssc ? DKL_PLL_SSC_EN : 0);

		pll_state->mg_pll_bias = (m2भाग_frac ? DKL_PLL_BIAS_FRAC_EN_H : 0) |
					  DKL_PLL_BIAS_FBDIV_FRAC(m2भाग_frac);

		pll_state->mg_pll_tdc_coldst_bias =
				DKL_PLL_TDC_SSC_STEP_SIZE(ssc_stepsize) |
				DKL_PLL_TDC_FEED_FWD_GAIN(feedfwgain);

	पूर्ण अन्यथा अणु
		pll_state->mg_pll_भाग0 =
			(m2भाग_rem > 0 ? MG_PLL_DIV0_FRACNEN_H : 0) |
			MG_PLL_DIV0_FBDIV_FRAC(m2भाग_frac) |
			MG_PLL_DIV0_FBDIV_INT(m2भाग_पूर्णांक);

		pll_state->mg_pll_भाग1 =
			MG_PLL_DIV1_IREF_NDIVRATIO(iref_nभाग) |
			MG_PLL_DIV1_DITHER_DIV_2 |
			MG_PLL_DIV1_NDIVRATIO(1) |
			MG_PLL_DIV1_FBPREDIV(m1भाग);

		pll_state->mg_pll_lf =
			MG_PLL_LF_TDCTARGETCNT(tdc_tarअ_लोnt) |
			MG_PLL_LF_AFCCNTSEL_512 |
			MG_PLL_LF_GAINCTRL(1) |
			MG_PLL_LF_INT_COEFF(पूर्णांक_coeff) |
			MG_PLL_LF_PROP_COEFF(prop_coeff);

		pll_state->mg_pll_frac_lock =
			MG_PLL_FRAC_LOCK_TRUELOCK_CRIT_32 |
			MG_PLL_FRAC_LOCK_EARLYLOCK_CRIT_32 |
			MG_PLL_FRAC_LOCK_LOCKTHRESH(10) |
			MG_PLL_FRAC_LOCK_DCODITHEREN |
			MG_PLL_FRAC_LOCK_FEEDFWRDGAIN(feedfwgain);
		अगर (use_ssc || m2भाग_rem > 0)
			pll_state->mg_pll_frac_lock |=
				MG_PLL_FRAC_LOCK_FEEDFWRDCAL_EN;

		pll_state->mg_pll_ssc =
			(use_ssc ? MG_PLL_SSC_EN : 0) |
			MG_PLL_SSC_TYPE(2) |
			MG_PLL_SSC_STEPLENGTH(ssc_steplen) |
			MG_PLL_SSC_STEPNUM(ssc_steplog) |
			MG_PLL_SSC_FLLEN |
			MG_PLL_SSC_STEPSIZE(ssc_stepsize);

		pll_state->mg_pll_tdc_coldst_bias =
			MG_PLL_TDC_COLDST_COLDSTART |
			MG_PLL_TDC_COLDST_IREFINT_EN |
			MG_PLL_TDC_COLDST_REFBIAS_START_PULSE_W(iref_pulse_w) |
			MG_PLL_TDC_TDCOVCCORR_EN |
			MG_PLL_TDC_TDCSEL(3);

		pll_state->mg_pll_bias =
			MG_PLL_BIAS_BIAS_GB_SEL(3) |
			MG_PLL_BIAS_INIT_DCOAMP(0x3F) |
			MG_PLL_BIAS_BIAS_BONUS(10) |
			MG_PLL_BIAS_BIASCAL_EN |
			MG_PLL_BIAS_CTRIM(12) |
			MG_PLL_BIAS_VREF_RDAC(4) |
			MG_PLL_BIAS_IREFTRIM(iref_trim);

		अगर (refclk_khz == 38400) अणु
			pll_state->mg_pll_tdc_coldst_bias_mask =
				MG_PLL_TDC_COLDST_COLDSTART;
			pll_state->mg_pll_bias_mask = 0;
		पूर्ण अन्यथा अणु
			pll_state->mg_pll_tdc_coldst_bias_mask = -1U;
			pll_state->mg_pll_bias_mask = -1U;
		पूर्ण

		pll_state->mg_pll_tdc_coldst_bias &=
			pll_state->mg_pll_tdc_coldst_bias_mask;
		pll_state->mg_pll_bias &= pll_state->mg_pll_bias_mask;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक icl_ddi_mg_pll_get_freq(काष्ठा drm_i915_निजी *dev_priv,
				   स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
				   स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	u32 m1, m2_पूर्णांक, m2_frac, भाग1, भाग2, ref_घड़ी;
	u64 पंचांगp;

	ref_घड़ी = dev_priv->dpll.ref_clks.nssc;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		m1 = pll_state->mg_pll_भाग0 & DKL_PLL_DIV0_FBPREDIV_MASK;
		m1 = m1 >> DKL_PLL_DIV0_FBPREDIV_SHIFT;
		m2_पूर्णांक = pll_state->mg_pll_भाग0 & DKL_PLL_DIV0_FBDIV_INT_MASK;

		अगर (pll_state->mg_pll_bias & DKL_PLL_BIAS_FRAC_EN_H) अणु
			m2_frac = pll_state->mg_pll_bias &
				  DKL_PLL_BIAS_FBDIV_FRAC_MASK;
			m2_frac = m2_frac >> DKL_PLL_BIAS_FBDIV_SHIFT;
		पूर्ण अन्यथा अणु
			m2_frac = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		m1 = pll_state->mg_pll_भाग1 & MG_PLL_DIV1_FBPREDIV_MASK;
		m2_पूर्णांक = pll_state->mg_pll_भाग0 & MG_PLL_DIV0_FBDIV_INT_MASK;

		अगर (pll_state->mg_pll_भाग0 & MG_PLL_DIV0_FRACNEN_H) अणु
			m2_frac = pll_state->mg_pll_भाग0 &
				  MG_PLL_DIV0_FBDIV_FRAC_MASK;
			m2_frac = m2_frac >> MG_PLL_DIV0_FBDIV_FRAC_SHIFT;
		पूर्ण अन्यथा अणु
			m2_frac = 0;
		पूर्ण
	पूर्ण

	चयन (pll_state->mg_clktop2_hsclkctl &
		MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK) अणु
	हाल MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_2:
		भाग1 = 2;
		अवरोध;
	हाल MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_3:
		भाग1 = 3;
		अवरोध;
	हाल MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_5:
		भाग1 = 5;
		अवरोध;
	हाल MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_7:
		भाग1 = 7;
		अवरोध;
	शेष:
		MISSING_CASE(pll_state->mg_clktop2_hsclkctl);
		वापस 0;
	पूर्ण

	भाग2 = (pll_state->mg_clktop2_hsclkctl &
		MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK) >>
		MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_SHIFT;

	/* भाग2 value of 0 is same as 1 means no भाग */
	अगर (भाग2 == 0)
		भाग2 = 1;

	/*
	 * Adjust the original क्रमmula to delay the भागision by 2^22 in order to
	 * minimize possible rounding errors.
	 */
	पंचांगp = (u64)m1 * m2_पूर्णांक * ref_घड़ी +
	      (((u64)m1 * m2_frac * ref_घड़ी) >> 22);
	पंचांगp = भाग_u64(पंचांगp, 5 * भाग1 * भाग2);

	वापस पंचांगp;
पूर्ण

/**
 * icl_set_active_port_dpll - select the active port DPLL क्रम a given CRTC
 * @crtc_state: state क्रम the CRTC to select the DPLL क्रम
 * @port_dpll_id: the active @port_dpll_id to select
 *
 * Select the given @port_dpll_id instance from the DPLLs reserved क्रम the
 * CRTC.
 */
व्योम icl_set_active_port_dpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      क्रमागत icl_port_dpll_id port_dpll_id)
अणु
	काष्ठा icl_port_dpll *port_dpll =
		&crtc_state->icl_port_dplls[port_dpll_id];

	crtc_state->shared_dpll = port_dpll->pll;
	crtc_state->dpll_hw_state = port_dpll->hw_state;
पूर्ण

अटल व्योम icl_update_active_dpll(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_digital_port *primary_port;
	क्रमागत icl_port_dpll_id port_dpll_id = ICL_PORT_DPLL_DEFAULT;

	primary_port = encoder->type == INTEL_OUTPUT_DP_MST ?
		enc_to_mst(encoder)->primary :
		enc_to_dig_port(encoder);

	अगर (primary_port &&
	    (primary_port->tc_mode == TC_PORT_DP_ALT ||
	     primary_port->tc_mode == TC_PORT_LEGACY))
		port_dpll_id = ICL_PORT_DPLL_MG_PHY;

	icl_set_active_port_dpll(crtc_state, port_dpll_id);
पूर्ण

अटल u32 पूर्णांकel_get_hti_plls(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!(i915->hti_state & HDPORT_ENABLED))
		वापस 0;

	वापस REG_FIELD_GET(HDPORT_DPLL_USED_MASK, i915->hti_state);
पूर्ण

अटल bool icl_get_combo_phy_dpll(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा skl_wrpll_params pll_params = अणु पूर्ण;
	काष्ठा icl_port_dpll *port_dpll =
		&crtc_state->icl_port_dplls[ICL_PORT_DPLL_DEFAULT];
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत port port = encoder->port;
	अचिन्हित दीर्घ dpll_mask;
	पूर्णांक ret;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI) ||
	    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI))
		ret = icl_calc_wrpll(crtc_state, &pll_params);
	अन्यथा
		ret = icl_calc_dp_combo_pll(crtc_state, &pll_params);

	अगर (!ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Could not calculate combo PHY PLL state.\n");

		वापस false;
	पूर्ण

	icl_calc_dpll_state(dev_priv, &pll_params, &port_dpll->hw_state);

	अगर (IS_ALDERLAKE_S(dev_priv)) अणु
		dpll_mask =
			BIT(DPLL_ID_DG1_DPLL3) |
			BIT(DPLL_ID_DG1_DPLL2) |
			BIT(DPLL_ID_ICL_DPLL1) |
			BIT(DPLL_ID_ICL_DPLL0);
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv)) अणु
		अगर (port == PORT_D || port == PORT_E) अणु
			dpll_mask =
				BIT(DPLL_ID_DG1_DPLL2) |
				BIT(DPLL_ID_DG1_DPLL3);
		पूर्ण अन्यथा अणु
			dpll_mask =
				BIT(DPLL_ID_DG1_DPLL0) |
				BIT(DPLL_ID_DG1_DPLL1);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(dev_priv)) अणु
		dpll_mask =
			BIT(DPLL_ID_EHL_DPLL4) |
			BIT(DPLL_ID_ICL_DPLL1) |
			BIT(DPLL_ID_ICL_DPLL0);
	पूर्ण अन्यथा अगर (IS_JSL_EHL(dev_priv) && port != PORT_A) अणु
		dpll_mask =
			BIT(DPLL_ID_EHL_DPLL4) |
			BIT(DPLL_ID_ICL_DPLL1) |
			BIT(DPLL_ID_ICL_DPLL0);
	पूर्ण अन्यथा अणु
		dpll_mask = BIT(DPLL_ID_ICL_DPLL1) | BIT(DPLL_ID_ICL_DPLL0);
	पूर्ण

	/* Eliminate DPLLs from consideration अगर reserved by HTI */
	dpll_mask &= ~पूर्णांकel_get_hti_plls(dev_priv);

	port_dpll->pll = पूर्णांकel_find_shared_dpll(state, crtc,
						&port_dpll->hw_state,
						dpll_mask);
	अगर (!port_dpll->pll) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "No combo PHY PLL found for [ENCODER:%d:%s]\n",
			    encoder->base.base.id, encoder->base.name);
		वापस false;
	पूर्ण

	पूर्णांकel_reference_shared_dpll(state, crtc,
				    port_dpll->pll, &port_dpll->hw_state);

	icl_update_active_dpll(state, crtc, encoder);

	वापस true;
पूर्ण

अटल bool icl_get_tc_phy_dplls(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_crtc *crtc,
				 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा skl_wrpll_params pll_params = अणु पूर्ण;
	काष्ठा icl_port_dpll *port_dpll;
	क्रमागत पूर्णांकel_dpll_id dpll_id;

	port_dpll = &crtc_state->icl_port_dplls[ICL_PORT_DPLL_DEFAULT];
	अगर (!icl_calc_tbt_pll(crtc_state, &pll_params)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Could not calculate TBT PLL state.\n");
		वापस false;
	पूर्ण

	icl_calc_dpll_state(dev_priv, &pll_params, &port_dpll->hw_state);

	port_dpll->pll = पूर्णांकel_find_shared_dpll(state, crtc,
						&port_dpll->hw_state,
						BIT(DPLL_ID_ICL_TBTPLL));
	अगर (!port_dpll->pll) अणु
		drm_dbg_kms(&dev_priv->drm, "No TBT-ALT PLL found\n");
		वापस false;
	पूर्ण
	पूर्णांकel_reference_shared_dpll(state, crtc,
				    port_dpll->pll, &port_dpll->hw_state);


	port_dpll = &crtc_state->icl_port_dplls[ICL_PORT_DPLL_MG_PHY];
	अगर (!icl_calc_mg_pll_state(crtc_state, &port_dpll->hw_state)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Could not calculate MG PHY PLL state.\n");
		जाओ err_unreference_tbt_pll;
	पूर्ण

	dpll_id = icl_tc_port_to_pll_id(पूर्णांकel_port_to_tc(dev_priv,
							 encoder->port));
	port_dpll->pll = पूर्णांकel_find_shared_dpll(state, crtc,
						&port_dpll->hw_state,
						BIT(dpll_id));
	अगर (!port_dpll->pll) अणु
		drm_dbg_kms(&dev_priv->drm, "No MG PHY PLL found\n");
		जाओ err_unreference_tbt_pll;
	पूर्ण
	पूर्णांकel_reference_shared_dpll(state, crtc,
				    port_dpll->pll, &port_dpll->hw_state);

	icl_update_active_dpll(state, crtc, encoder);

	वापस true;

err_unreference_tbt_pll:
	port_dpll = &crtc_state->icl_port_dplls[ICL_PORT_DPLL_DEFAULT];
	पूर्णांकel_unreference_shared_dpll(state, crtc, port_dpll->pll);

	वापस false;
पूर्ण

अटल bool icl_get_dplls(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc *crtc,
			  काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);

	अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
		वापस icl_get_combo_phy_dpll(state, crtc, encoder);
	अन्यथा अगर (पूर्णांकel_phy_is_tc(dev_priv, phy))
		वापस icl_get_tc_phy_dplls(state, crtc, encoder);

	MISSING_CASE(phy);

	वापस false;
पूर्ण

अटल व्योम icl_put_dplls(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	क्रमागत icl_port_dpll_id id;

	new_crtc_state->shared_dpll = शून्य;

	क्रम (id = ICL_PORT_DPLL_DEFAULT; id < ICL_PORT_DPLL_COUNT; id++) अणु
		स्थिर काष्ठा icl_port_dpll *old_port_dpll =
			&old_crtc_state->icl_port_dplls[id];
		काष्ठा icl_port_dpll *new_port_dpll =
			&new_crtc_state->icl_port_dplls[id];

		new_port_dpll->pll = शून्य;

		अगर (!old_port_dpll->pll)
			जारी;

		पूर्णांकel_unreference_shared_dpll(state, crtc, old_port_dpll->pll);
	पूर्ण
पूर्ण

अटल bool mg_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा पूर्णांकel_shared_dpll *pll,
				काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	क्रमागत tc_port tc_port = icl_pll_id_to_tc_port(id);
	पूर्णांकel_wakeref_t wakeref;
	bool ret = false;
	u32 val;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_ENABLE(tc_port));
	अगर (!(val & PLL_ENABLE))
		जाओ out;

	hw_state->mg_refclkin_ctl = पूर्णांकel_de_पढ़ो(dev_priv,
						  MG_REFCLKIN_CTL(tc_port));
	hw_state->mg_refclkin_ctl &= MG_REFCLKIN_CTL_OD_2_MUX_MASK;

	hw_state->mg_clktop2_coreclkctl1 =
		पूर्णांकel_de_पढ़ो(dev_priv, MG_CLKTOP2_CORECLKCTL1(tc_port));
	hw_state->mg_clktop2_coreclkctl1 &=
		MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO_MASK;

	hw_state->mg_clktop2_hsclkctl =
		पूर्णांकel_de_पढ़ो(dev_priv, MG_CLKTOP2_HSCLKCTL(tc_port));
	hw_state->mg_clktop2_hsclkctl &=
		MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL_MASK |
		MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL_MASK |
		MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK |
		MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK;

	hw_state->mg_pll_भाग0 = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_DIV0(tc_port));
	hw_state->mg_pll_भाग1 = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_DIV1(tc_port));
	hw_state->mg_pll_lf = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_LF(tc_port));
	hw_state->mg_pll_frac_lock = पूर्णांकel_de_पढ़ो(dev_priv,
						   MG_PLL_FRAC_LOCK(tc_port));
	hw_state->mg_pll_ssc = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_SSC(tc_port));

	hw_state->mg_pll_bias = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_BIAS(tc_port));
	hw_state->mg_pll_tdc_coldst_bias =
		पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_TDC_COLDST_BIAS(tc_port));

	अगर (dev_priv->dpll.ref_clks.nssc == 38400) अणु
		hw_state->mg_pll_tdc_coldst_bias_mask = MG_PLL_TDC_COLDST_COLDSTART;
		hw_state->mg_pll_bias_mask = 0;
	पूर्ण अन्यथा अणु
		hw_state->mg_pll_tdc_coldst_bias_mask = -1U;
		hw_state->mg_pll_bias_mask = -1U;
	पूर्ण

	hw_state->mg_pll_tdc_coldst_bias &= hw_state->mg_pll_tdc_coldst_bias_mask;
	hw_state->mg_pll_bias &= hw_state->mg_pll_bias_mask;

	ret = true;
out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
	वापस ret;
पूर्ण

अटल bool dkl_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll,
				 काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	क्रमागत tc_port tc_port = icl_pll_id_to_tc_port(id);
	पूर्णांकel_wakeref_t wakeref;
	bool ret = false;
	u32 val;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_ENABLE(tc_port));
	अगर (!(val & PLL_ENABLE))
		जाओ out;

	/*
	 * All रेजिस्टरs पढ़ो here have the same HIP_INDEX_REG even though
	 * they are on dअगरferent building blocks
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
		       HIP_INDEX_VAL(tc_port, 0x2));

	hw_state->mg_refclkin_ctl = पूर्णांकel_de_पढ़ो(dev_priv,
						  DKL_REFCLKIN_CTL(tc_port));
	hw_state->mg_refclkin_ctl &= MG_REFCLKIN_CTL_OD_2_MUX_MASK;

	hw_state->mg_clktop2_hsclkctl =
		पूर्णांकel_de_पढ़ो(dev_priv, DKL_CLKTOP2_HSCLKCTL(tc_port));
	hw_state->mg_clktop2_hsclkctl &=
		MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL_MASK |
		MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL_MASK |
		MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK |
		MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK;

	hw_state->mg_clktop2_coreclkctl1 =
		पूर्णांकel_de_पढ़ो(dev_priv, DKL_CLKTOP2_CORECLKCTL1(tc_port));
	hw_state->mg_clktop2_coreclkctl1 &=
		MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO_MASK;

	hw_state->mg_pll_भाग0 = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_DIV0(tc_port));
	hw_state->mg_pll_भाग0 &= (DKL_PLL_DIV0_INTEG_COEFF_MASK |
				  DKL_PLL_DIV0_PROP_COEFF_MASK |
				  DKL_PLL_DIV0_FBPREDIV_MASK |
				  DKL_PLL_DIV0_FBDIV_INT_MASK);

	hw_state->mg_pll_भाग1 = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_DIV1(tc_port));
	hw_state->mg_pll_भाग1 &= (DKL_PLL_DIV1_IREF_TRIM_MASK |
				  DKL_PLL_DIV1_TDC_TARGET_CNT_MASK);

	hw_state->mg_pll_ssc = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_SSC(tc_port));
	hw_state->mg_pll_ssc &= (DKL_PLL_SSC_IREF_NDIV_RATIO_MASK |
				 DKL_PLL_SSC_STEP_LEN_MASK |
				 DKL_PLL_SSC_STEP_NUM_MASK |
				 DKL_PLL_SSC_EN);

	hw_state->mg_pll_bias = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_BIAS(tc_port));
	hw_state->mg_pll_bias &= (DKL_PLL_BIAS_FRAC_EN_H |
				  DKL_PLL_BIAS_FBDIV_FRAC_MASK);

	hw_state->mg_pll_tdc_coldst_bias =
		पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_TDC_COLDST_BIAS(tc_port));
	hw_state->mg_pll_tdc_coldst_bias &= (DKL_PLL_TDC_SSC_STEP_SIZE_MASK |
					     DKL_PLL_TDC_FEED_FWD_GAIN_MASK);

	ret = true;
out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
	वापस ret;
पूर्ण

अटल bool icl_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll,
				 काष्ठा पूर्णांकel_dpll_hw_state *hw_state,
				 i915_reg_t enable_reg)
अणु
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	पूर्णांकel_wakeref_t wakeref;
	bool ret = false;
	u32 val;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     POWER_DOMAIN_DISPLAY_CORE);
	अगर (!wakeref)
		वापस false;

	val = पूर्णांकel_de_पढ़ो(dev_priv, enable_reg);
	अगर (!(val & PLL_ENABLE))
		जाओ out;

	अगर (IS_ALDERLAKE_S(dev_priv)) अणु
		hw_state->cfgcr0 = पूर्णांकel_de_पढ़ो(dev_priv, ADLS_DPLL_CFGCR0(id));
		hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv, ADLS_DPLL_CFGCR1(id));
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv)) अणु
		hw_state->cfgcr0 = पूर्णांकel_de_पढ़ो(dev_priv, DG1_DPLL_CFGCR0(id));
		hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv, DG1_DPLL_CFGCR1(id));
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(dev_priv)) अणु
		hw_state->cfgcr0 = पूर्णांकel_de_पढ़ो(dev_priv,
						 RKL_DPLL_CFGCR0(id));
		hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv,
						 RKL_DPLL_CFGCR1(id));
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		hw_state->cfgcr0 = पूर्णांकel_de_पढ़ो(dev_priv,
						 TGL_DPLL_CFGCR0(id));
		hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv,
						 TGL_DPLL_CFGCR1(id));
	पूर्ण अन्यथा अणु
		अगर (IS_JSL_EHL(dev_priv) && id == DPLL_ID_EHL_DPLL4) अणु
			hw_state->cfgcr0 = पूर्णांकel_de_पढ़ो(dev_priv,
							 ICL_DPLL_CFGCR0(4));
			hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv,
							 ICL_DPLL_CFGCR1(4));
		पूर्ण अन्यथा अणु
			hw_state->cfgcr0 = पूर्णांकel_de_पढ़ो(dev_priv,
							 ICL_DPLL_CFGCR0(id));
			hw_state->cfgcr1 = पूर्णांकel_de_पढ़ो(dev_priv,
							 ICL_DPLL_CFGCR1(id));
		पूर्ण
	पूर्ण

	ret = true;
out:
	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
	वापस ret;
पूर्ण

अटल bool combo_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_shared_dpll *pll,
				   काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	i915_reg_t enable_reg = पूर्णांकel_combo_pll_enable_reg(dev_priv, pll);

	वापस icl_pll_get_hw_state(dev_priv, pll, hw_state, enable_reg);
पूर्ण

अटल bool tbt_pll_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll,
				 काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	वापस icl_pll_get_hw_state(dev_priv, pll, hw_state, TBT_PLL_ENABLE);
पूर्ण

अटल व्योम icl_dpll_ग_लिखो(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा पूर्णांकel_dpll_hw_state *hw_state = &pll->state.hw_state;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;
	i915_reg_t cfgcr0_reg, cfgcr1_reg;

	अगर (IS_ALDERLAKE_S(dev_priv)) अणु
		cfgcr0_reg = ADLS_DPLL_CFGCR0(id);
		cfgcr1_reg = ADLS_DPLL_CFGCR1(id);
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv)) अणु
		cfgcr0_reg = DG1_DPLL_CFGCR0(id);
		cfgcr1_reg = DG1_DPLL_CFGCR1(id);
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(dev_priv)) अणु
		cfgcr0_reg = RKL_DPLL_CFGCR0(id);
		cfgcr1_reg = RKL_DPLL_CFGCR1(id);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		cfgcr0_reg = TGL_DPLL_CFGCR0(id);
		cfgcr1_reg = TGL_DPLL_CFGCR1(id);
	पूर्ण अन्यथा अणु
		अगर (IS_JSL_EHL(dev_priv) && id == DPLL_ID_EHL_DPLL4) अणु
			cfgcr0_reg = ICL_DPLL_CFGCR0(4);
			cfgcr1_reg = ICL_DPLL_CFGCR1(4);
		पूर्ण अन्यथा अणु
			cfgcr0_reg = ICL_DPLL_CFGCR0(id);
			cfgcr1_reg = ICL_DPLL_CFGCR1(id);
		पूर्ण
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, cfgcr0_reg, hw_state->cfgcr0);
	पूर्णांकel_de_ग_लिखो(dev_priv, cfgcr1_reg, hw_state->cfgcr1);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, cfgcr1_reg);
पूर्ण

अटल व्योम icl_mg_pll_ग_लिखो(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा पूर्णांकel_dpll_hw_state *hw_state = &pll->state.hw_state;
	क्रमागत tc_port tc_port = icl_pll_id_to_tc_port(pll->info->id);
	u32 val;

	/*
	 * Some of the following रेजिस्टरs have reserved fields, so program
	 * these with RMW based on a mask. The mask can be fixed or generated
	 * during the calc/पढ़ोout phase अगर the mask depends on some other HW
	 * state like refclk, see icl_calc_mg_pll_state().
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_REFCLKIN_CTL(tc_port));
	val &= ~MG_REFCLKIN_CTL_OD_2_MUX_MASK;
	val |= hw_state->mg_refclkin_ctl;
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_REFCLKIN_CTL(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_CLKTOP2_CORECLKCTL1(tc_port));
	val &= ~MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO_MASK;
	val |= hw_state->mg_clktop2_coreclkctl1;
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_CLKTOP2_CORECLKCTL1(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_CLKTOP2_HSCLKCTL(tc_port));
	val &= ~(MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL_MASK |
		 MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL_MASK |
		 MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK |
		 MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK);
	val |= hw_state->mg_clktop2_hsclkctl;
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_CLKTOP2_HSCLKCTL(tc_port), val);

	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_DIV0(tc_port), hw_state->mg_pll_भाग0);
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_DIV1(tc_port), hw_state->mg_pll_भाग1);
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_LF(tc_port), hw_state->mg_pll_lf);
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_FRAC_LOCK(tc_port),
		       hw_state->mg_pll_frac_lock);
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_SSC(tc_port), hw_state->mg_pll_ssc);

	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_BIAS(tc_port));
	val &= ~hw_state->mg_pll_bias_mask;
	val |= hw_state->mg_pll_bias;
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_BIAS(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, MG_PLL_TDC_COLDST_BIAS(tc_port));
	val &= ~hw_state->mg_pll_tdc_coldst_bias_mask;
	val |= hw_state->mg_pll_tdc_coldst_bias;
	पूर्णांकel_de_ग_लिखो(dev_priv, MG_PLL_TDC_COLDST_BIAS(tc_port), val);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, MG_PLL_TDC_COLDST_BIAS(tc_port));
पूर्ण

अटल व्योम dkl_pll_ग_लिखो(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा पूर्णांकel_dpll_hw_state *hw_state = &pll->state.hw_state;
	क्रमागत tc_port tc_port = icl_pll_id_to_tc_port(pll->info->id);
	u32 val;

	/*
	 * All रेजिस्टरs programmed here have the same HIP_INDEX_REG even
	 * though on dअगरferent building block
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
		       HIP_INDEX_VAL(tc_port, 0x2));

	/* All the रेजिस्टरs are RMW */
	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_REFCLKIN_CTL(tc_port));
	val &= ~MG_REFCLKIN_CTL_OD_2_MUX_MASK;
	val |= hw_state->mg_refclkin_ctl;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_REFCLKIN_CTL(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_CLKTOP2_CORECLKCTL1(tc_port));
	val &= ~MG_CLKTOP2_CORECLKCTL1_A_DIVRATIO_MASK;
	val |= hw_state->mg_clktop2_coreclkctl1;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_CLKTOP2_CORECLKCTL1(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_CLKTOP2_HSCLKCTL(tc_port));
	val &= ~(MG_CLKTOP2_HSCLKCTL_TLINEDRV_CLKSEL_MASK |
		 MG_CLKTOP2_HSCLKCTL_CORE_INPUTSEL_MASK |
		 MG_CLKTOP2_HSCLKCTL_HSDIV_RATIO_MASK |
		 MG_CLKTOP2_HSCLKCTL_DSDIV_RATIO_MASK);
	val |= hw_state->mg_clktop2_hsclkctl;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_CLKTOP2_HSCLKCTL(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_DIV0(tc_port));
	val &= ~(DKL_PLL_DIV0_INTEG_COEFF_MASK |
		 DKL_PLL_DIV0_PROP_COEFF_MASK |
		 DKL_PLL_DIV0_FBPREDIV_MASK |
		 DKL_PLL_DIV0_FBDIV_INT_MASK);
	val |= hw_state->mg_pll_भाग0;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_PLL_DIV0(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_DIV1(tc_port));
	val &= ~(DKL_PLL_DIV1_IREF_TRIM_MASK |
		 DKL_PLL_DIV1_TDC_TARGET_CNT_MASK);
	val |= hw_state->mg_pll_भाग1;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_PLL_DIV1(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_SSC(tc_port));
	val &= ~(DKL_PLL_SSC_IREF_NDIV_RATIO_MASK |
		 DKL_PLL_SSC_STEP_LEN_MASK |
		 DKL_PLL_SSC_STEP_NUM_MASK |
		 DKL_PLL_SSC_EN);
	val |= hw_state->mg_pll_ssc;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_PLL_SSC(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_BIAS(tc_port));
	val &= ~(DKL_PLL_BIAS_FRAC_EN_H |
		 DKL_PLL_BIAS_FBDIV_FRAC_MASK);
	val |= hw_state->mg_pll_bias;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_PLL_BIAS(tc_port), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_PLL_TDC_COLDST_BIAS(tc_port));
	val &= ~(DKL_PLL_TDC_SSC_STEP_SIZE_MASK |
		 DKL_PLL_TDC_FEED_FWD_GAIN_MASK);
	val |= hw_state->mg_pll_tdc_coldst_bias;
	पूर्णांकel_de_ग_लिखो(dev_priv, DKL_PLL_TDC_COLDST_BIAS(tc_port), val);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, DKL_PLL_TDC_COLDST_BIAS(tc_port));
पूर्ण

अटल व्योम icl_pll_घातer_enable(काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_shared_dpll *pll,
				 i915_reg_t enable_reg)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, enable_reg);
	val |= PLL_POWER_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, enable_reg, val);

	/*
	 * The spec says we need to "wait" but it also says it should be
	 * immediate.
	 */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, enable_reg, PLL_POWER_STATE, 1))
		drm_err(&dev_priv->drm, "PLL %d Power not enabled\n",
			pll->info->id);
पूर्ण

अटल व्योम icl_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_shared_dpll *pll,
			   i915_reg_t enable_reg)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, enable_reg);
	val |= PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, enable_reg, val);

	/* Timeout is actually 600us. */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, enable_reg, PLL_LOCK, 1))
		drm_err(&dev_priv->drm, "PLL %d not locked\n", pll->info->id);
पूर्ण

अटल व्योम combo_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	i915_reg_t enable_reg = पूर्णांकel_combo_pll_enable_reg(dev_priv, pll);

	अगर (IS_JSL_EHL(dev_priv) &&
	    pll->info->id == DPLL_ID_EHL_DPLL4) अणु

		/*
		 * We need to disable DC states when this DPLL is enabled.
		 * This can be करोne by taking a reference on DPLL4 घातer
		 * करोमुख्य.
		 */
		pll->wakeref = पूर्णांकel_display_घातer_get(dev_priv,
						       POWER_DOMAIN_DPLL_DC_OFF);
	पूर्ण

	icl_pll_घातer_enable(dev_priv, pll, enable_reg);

	icl_dpll_ग_लिखो(dev_priv, pll);

	/*
	 * DVFS pre sequence would be here, but in our driver the cdclk code
	 * paths should alपढ़ोy be setting the appropriate voltage, hence we करो
	 * nothing here.
	 */

	icl_pll_enable(dev_priv, pll, enable_reg);

	/* DVFS post sequence would be here. See the comment above. */
पूर्ण

अटल व्योम tbt_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	icl_pll_घातer_enable(dev_priv, pll, TBT_PLL_ENABLE);

	icl_dpll_ग_लिखो(dev_priv, pll);

	/*
	 * DVFS pre sequence would be here, but in our driver the cdclk code
	 * paths should alपढ़ोy be setting the appropriate voltage, hence we करो
	 * nothing here.
	 */

	icl_pll_enable(dev_priv, pll, TBT_PLL_ENABLE);

	/* DVFS post sequence would be here. See the comment above. */
पूर्ण

अटल व्योम mg_pll_enable(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	i915_reg_t enable_reg =
		MG_PLL_ENABLE(icl_pll_id_to_tc_port(pll->info->id));

	icl_pll_घातer_enable(dev_priv, pll, enable_reg);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		dkl_pll_ग_लिखो(dev_priv, pll);
	अन्यथा
		icl_mg_pll_ग_लिखो(dev_priv, pll);

	/*
	 * DVFS pre sequence would be here, but in our driver the cdclk code
	 * paths should alपढ़ोy be setting the appropriate voltage, hence we करो
	 * nothing here.
	 */

	icl_pll_enable(dev_priv, pll, enable_reg);

	/* DVFS post sequence would be here. See the comment above. */
पूर्ण

अटल व्योम icl_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
			    काष्ठा पूर्णांकel_shared_dpll *pll,
			    i915_reg_t enable_reg)
अणु
	u32 val;

	/* The first steps are करोne by पूर्णांकel_ddi_post_disable(). */

	/*
	 * DVFS pre sequence would be here, but in our driver the cdclk code
	 * paths should alपढ़ोy be setting the appropriate voltage, hence we करो
	 * nothing here.
	 */

	val = पूर्णांकel_de_पढ़ो(dev_priv, enable_reg);
	val &= ~PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, enable_reg, val);

	/* Timeout is actually 1us. */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, enable_reg, PLL_LOCK, 1))
		drm_err(&dev_priv->drm, "PLL %d locked\n", pll->info->id);

	/* DVFS post sequence would be here. See the comment above. */

	val = पूर्णांकel_de_पढ़ो(dev_priv, enable_reg);
	val &= ~PLL_POWER_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, enable_reg, val);

	/*
	 * The spec says we need to "wait" but it also says it should be
	 * immediate.
	 */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, enable_reg, PLL_POWER_STATE, 1))
		drm_err(&dev_priv->drm, "PLL %d Power not disabled\n",
			pll->info->id);
पूर्ण

अटल व्योम combo_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
			      काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	i915_reg_t enable_reg = पूर्णांकel_combo_pll_enable_reg(dev_priv, pll);

	icl_pll_disable(dev_priv, pll, enable_reg);

	अगर (IS_JSL_EHL(dev_priv) &&
	    pll->info->id == DPLL_ID_EHL_DPLL4)
		पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DPLL_DC_OFF,
					pll->wakeref);
पूर्ण

अटल व्योम tbt_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
			    काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	icl_pll_disable(dev_priv, pll, TBT_PLL_ENABLE);
पूर्ण

अटल व्योम mg_pll_disable(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	i915_reg_t enable_reg =
		MG_PLL_ENABLE(icl_pll_id_to_tc_port(pll->info->id));

	icl_pll_disable(dev_priv, pll, enable_reg);
पूर्ण

अटल व्योम icl_update_dpll_ref_clks(काष्ठा drm_i915_निजी *i915)
अणु
	/* No SSC ref */
	i915->dpll.ref_clks.nssc = i915->cdclk.hw.ref;
पूर्ण

अटल व्योम icl_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	drm_dbg_kms(&dev_priv->drm,
		    "dpll_hw_state: cfgcr0: 0x%x, cfgcr1: 0x%x, "
		    "mg_refclkin_ctl: 0x%x, hg_clktop2_coreclkctl1: 0x%x, "
		    "mg_clktop2_hsclkctl: 0x%x, mg_pll_div0: 0x%x, "
		    "mg_pll_div2: 0x%x, mg_pll_lf: 0x%x, "
		    "mg_pll_frac_lock: 0x%x, mg_pll_ssc: 0x%x, "
		    "mg_pll_bias: 0x%x, mg_pll_tdc_coldst_bias: 0x%x\n",
		    hw_state->cfgcr0, hw_state->cfgcr1,
		    hw_state->mg_refclkin_ctl,
		    hw_state->mg_clktop2_coreclkctl1,
		    hw_state->mg_clktop2_hsclkctl,
		    hw_state->mg_pll_भाग0,
		    hw_state->mg_pll_भाग1,
		    hw_state->mg_pll_lf,
		    hw_state->mg_pll_frac_lock,
		    hw_state->mg_pll_ssc,
		    hw_state->mg_pll_bias,
		    hw_state->mg_pll_tdc_coldst_bias);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs combo_pll_funcs = अणु
	.enable = combo_pll_enable,
	.disable = combo_pll_disable,
	.get_hw_state = combo_pll_get_hw_state,
	.get_freq = icl_ddi_combo_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs tbt_pll_funcs = अणु
	.enable = tbt_pll_enable,
	.disable = tbt_pll_disable,
	.get_hw_state = tbt_pll_get_hw_state,
	.get_freq = icl_ddi_tbt_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs mg_pll_funcs = अणु
	.enable = mg_pll_enable,
	.disable = mg_pll_disable,
	.get_hw_state = mg_pll_get_hw_state,
	.get_freq = icl_ddi_mg_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा dpll_info icl_plls[] = अणु
	अणु "DPLL 0",   &combo_pll_funcs, DPLL_ID_ICL_DPLL0,  0 पूर्ण,
	अणु "DPLL 1",   &combo_pll_funcs, DPLL_ID_ICL_DPLL1,  0 पूर्ण,
	अणु "TBT PLL",  &tbt_pll_funcs, DPLL_ID_ICL_TBTPLL, 0 पूर्ण,
	अणु "MG PLL 1", &mg_pll_funcs, DPLL_ID_ICL_MGPLL1, 0 पूर्ण,
	अणु "MG PLL 2", &mg_pll_funcs, DPLL_ID_ICL_MGPLL2, 0 पूर्ण,
	अणु "MG PLL 3", &mg_pll_funcs, DPLL_ID_ICL_MGPLL3, 0 पूर्ण,
	अणु "MG PLL 4", &mg_pll_funcs, DPLL_ID_ICL_MGPLL4, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr icl_pll_mgr = अणु
	.dpll_info = icl_plls,
	.get_dplls = icl_get_dplls,
	.put_dplls = icl_put_dplls,
	.update_active_dpll = icl_update_active_dpll,
	.update_ref_clks = icl_update_dpll_ref_clks,
	.dump_hw_state = icl_dump_hw_state,
पूर्ण;

अटल स्थिर काष्ठा dpll_info ehl_plls[] = अणु
	अणु "DPLL 0", &combo_pll_funcs, DPLL_ID_ICL_DPLL0, 0 पूर्ण,
	अणु "DPLL 1", &combo_pll_funcs, DPLL_ID_ICL_DPLL1, 0 पूर्ण,
	अणु "DPLL 4", &combo_pll_funcs, DPLL_ID_EHL_DPLL4, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr ehl_pll_mgr = अणु
	.dpll_info = ehl_plls,
	.get_dplls = icl_get_dplls,
	.put_dplls = icl_put_dplls,
	.update_ref_clks = icl_update_dpll_ref_clks,
	.dump_hw_state = icl_dump_hw_state,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs dkl_pll_funcs = अणु
	.enable = mg_pll_enable,
	.disable = mg_pll_disable,
	.get_hw_state = dkl_pll_get_hw_state,
	.get_freq = icl_ddi_mg_pll_get_freq,
पूर्ण;

अटल स्थिर काष्ठा dpll_info tgl_plls[] = अणु
	अणु "DPLL 0", &combo_pll_funcs, DPLL_ID_ICL_DPLL0,  0 पूर्ण,
	अणु "DPLL 1", &combo_pll_funcs, DPLL_ID_ICL_DPLL1,  0 पूर्ण,
	अणु "TBT PLL",  &tbt_pll_funcs, DPLL_ID_ICL_TBTPLL, 0 पूर्ण,
	अणु "TC PLL 1", &dkl_pll_funcs, DPLL_ID_ICL_MGPLL1, 0 पूर्ण,
	अणु "TC PLL 2", &dkl_pll_funcs, DPLL_ID_ICL_MGPLL2, 0 पूर्ण,
	अणु "TC PLL 3", &dkl_pll_funcs, DPLL_ID_ICL_MGPLL3, 0 पूर्ण,
	अणु "TC PLL 4", &dkl_pll_funcs, DPLL_ID_ICL_MGPLL4, 0 पूर्ण,
	अणु "TC PLL 5", &dkl_pll_funcs, DPLL_ID_TGL_MGPLL5, 0 पूर्ण,
	अणु "TC PLL 6", &dkl_pll_funcs, DPLL_ID_TGL_MGPLL6, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr tgl_pll_mgr = अणु
	.dpll_info = tgl_plls,
	.get_dplls = icl_get_dplls,
	.put_dplls = icl_put_dplls,
	.update_active_dpll = icl_update_active_dpll,
	.update_ref_clks = icl_update_dpll_ref_clks,
	.dump_hw_state = icl_dump_hw_state,
पूर्ण;

अटल स्थिर काष्ठा dpll_info rkl_plls[] = अणु
	अणु "DPLL 0", &combo_pll_funcs, DPLL_ID_ICL_DPLL0, 0 पूर्ण,
	अणु "DPLL 1", &combo_pll_funcs, DPLL_ID_ICL_DPLL1, 0 पूर्ण,
	अणु "DPLL 4", &combo_pll_funcs, DPLL_ID_EHL_DPLL4, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr rkl_pll_mgr = अणु
	.dpll_info = rkl_plls,
	.get_dplls = icl_get_dplls,
	.put_dplls = icl_put_dplls,
	.update_ref_clks = icl_update_dpll_ref_clks,
	.dump_hw_state = icl_dump_hw_state,
पूर्ण;

अटल स्थिर काष्ठा dpll_info dg1_plls[] = अणु
	अणु "DPLL 0", &combo_pll_funcs, DPLL_ID_DG1_DPLL0, 0 पूर्ण,
	अणु "DPLL 1", &combo_pll_funcs, DPLL_ID_DG1_DPLL1, 0 पूर्ण,
	अणु "DPLL 2", &combo_pll_funcs, DPLL_ID_DG1_DPLL2, 0 पूर्ण,
	अणु "DPLL 3", &combo_pll_funcs, DPLL_ID_DG1_DPLL3, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr dg1_pll_mgr = अणु
	.dpll_info = dg1_plls,
	.get_dplls = icl_get_dplls,
	.put_dplls = icl_put_dplls,
	.update_ref_clks = icl_update_dpll_ref_clks,
	.dump_hw_state = icl_dump_hw_state,
पूर्ण;

अटल स्थिर काष्ठा dpll_info adls_plls[] = अणु
	अणु "DPLL 0", &combo_pll_funcs, DPLL_ID_ICL_DPLL0, 0 पूर्ण,
	अणु "DPLL 1", &combo_pll_funcs, DPLL_ID_ICL_DPLL1, 0 पूर्ण,
	अणु "DPLL 2", &combo_pll_funcs, DPLL_ID_DG1_DPLL2, 0 पूर्ण,
	अणु "DPLL 3", &combo_pll_funcs, DPLL_ID_DG1_DPLL3, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_dpll_mgr adls_pll_mgr = अणु
	.dpll_info = adls_plls,
	.get_dplls = icl_get_dplls,
	.put_dplls = icl_put_dplls,
	.update_ref_clks = icl_update_dpll_ref_clks,
	.dump_hw_state = icl_dump_hw_state,
पूर्ण;

/**
 * पूर्णांकel_shared_dpll_init - Initialize shared DPLLs
 * @dev: drm device
 *
 * Initialize shared DPLLs क्रम @dev.
 */
व्योम पूर्णांकel_shared_dpll_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	स्थिर काष्ठा पूर्णांकel_dpll_mgr *dpll_mgr = शून्य;
	स्थिर काष्ठा dpll_info *dpll_info;
	पूर्णांक i;

	अगर (IS_ALDERLAKE_S(dev_priv))
		dpll_mgr = &adls_pll_mgr;
	अन्यथा अगर (IS_DG1(dev_priv))
		dpll_mgr = &dg1_pll_mgr;
	अन्यथा अगर (IS_ROCKETLAKE(dev_priv))
		dpll_mgr = &rkl_pll_mgr;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12)
		dpll_mgr = &tgl_pll_mgr;
	अन्यथा अगर (IS_JSL_EHL(dev_priv))
		dpll_mgr = &ehl_pll_mgr;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11)
		dpll_mgr = &icl_pll_mgr;
	अन्यथा अगर (IS_CANNONLAKE(dev_priv))
		dpll_mgr = &cnl_pll_mgr;
	अन्यथा अगर (IS_GEN9_BC(dev_priv))
		dpll_mgr = &skl_pll_mgr;
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		dpll_mgr = &bxt_pll_mgr;
	अन्यथा अगर (HAS_DDI(dev_priv))
		dpll_mgr = &hsw_pll_mgr;
	अन्यथा अगर (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv))
		dpll_mgr = &pch_pll_mgr;

	अगर (!dpll_mgr) अणु
		dev_priv->dpll.num_shared_dpll = 0;
		वापस;
	पूर्ण

	dpll_info = dpll_mgr->dpll_info;

	क्रम (i = 0; dpll_info[i].name; i++) अणु
		drm_WARN_ON(dev, i != dpll_info[i].id);
		dev_priv->dpll.shared_dplls[i].info = &dpll_info[i];
	पूर्ण

	dev_priv->dpll.mgr = dpll_mgr;
	dev_priv->dpll.num_shared_dpll = i;
	mutex_init(&dev_priv->dpll.lock);

	BUG_ON(dev_priv->dpll.num_shared_dpll > I915_NUM_PLLS);
पूर्ण

/**
 * पूर्णांकel_reserve_shared_dplls - reserve DPLLs क्रम CRTC and encoder combination
 * @state: atomic state
 * @crtc: CRTC to reserve DPLLs क्रम
 * @encoder: encoder
 *
 * This function reserves all required DPLLs क्रम the given CRTC and encoder
 * combination in the current atomic commit @state and the new @crtc atomic
 * state.
 *
 * The new configuration in the atomic commit @state is made effective by
 * calling पूर्णांकel_shared_dpll_swap_state().
 *
 * The reserved DPLLs should be released by calling
 * पूर्णांकel_release_shared_dplls().
 *
 * Returns:
 * True अगर all required DPLLs were successfully reserved.
 */
bool पूर्णांकel_reserve_shared_dplls(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_dpll_mgr *dpll_mgr = dev_priv->dpll.mgr;

	अगर (drm_WARN_ON(&dev_priv->drm, !dpll_mgr))
		वापस false;

	वापस dpll_mgr->get_dplls(state, crtc, encoder);
पूर्ण

/**
 * पूर्णांकel_release_shared_dplls - end use of DPLLs by CRTC in atomic state
 * @state: atomic state
 * @crtc: crtc from which the DPLLs are to be released
 *
 * This function releases all DPLLs reserved by पूर्णांकel_reserve_shared_dplls()
 * from the current atomic commit @state and the old @crtc atomic state.
 *
 * The new configuration in the atomic commit @state is made effective by
 * calling पूर्णांकel_shared_dpll_swap_state().
 */
व्योम पूर्णांकel_release_shared_dplls(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_dpll_mgr *dpll_mgr = dev_priv->dpll.mgr;

	/*
	 * FIXME: this function is called क्रम every platक्रमm having a
	 * compute_घड़ी hook, even though the platक्रमm करोesn't yet support
	 * the shared DPLL framework and पूर्णांकel_reserve_shared_dplls() is not
	 * called on those.
	 */
	अगर (!dpll_mgr)
		वापस;

	dpll_mgr->put_dplls(state, crtc);
पूर्ण

/**
 * पूर्णांकel_update_active_dpll - update the active DPLL क्रम a CRTC/encoder
 * @state: atomic state
 * @crtc: the CRTC क्रम which to update the active DPLL
 * @encoder: encoder determining the type of port DPLL
 *
 * Update the active DPLL क्रम the given @crtc/@encoder in @crtc's atomic state,
 * from the port DPLLs reserved previously by पूर्णांकel_reserve_shared_dplls(). The
 * DPLL selected will be based on the current mode of the encoder's port.
 */
व्योम पूर्णांकel_update_active_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_dpll_mgr *dpll_mgr = dev_priv->dpll.mgr;

	अगर (drm_WARN_ON(&dev_priv->drm, !dpll_mgr))
		वापस;

	dpll_mgr->update_active_dpll(state, crtc, encoder);
पूर्ण

/**
 * पूर्णांकel_dpll_get_freq - calculate the DPLL's output frequency
 * @i915: i915 device
 * @pll: DPLL क्रम which to calculate the output frequency
 * @pll_state: DPLL state from which to calculate the output frequency
 *
 * Return the output frequency corresponding to @pll's passed in @pll_state.
 */
पूर्णांक पूर्णांकel_dpll_get_freq(काष्ठा drm_i915_निजी *i915,
			स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
			स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state)
अणु
	अगर (drm_WARN_ON(&i915->drm, !pll->info->funcs->get_freq))
		वापस 0;

	वापस pll->info->funcs->get_freq(i915, pll, pll_state);
पूर्ण

/**
 * पूर्णांकel_dpll_get_hw_state - पढ़ोout the DPLL's hardware state
 * @i915: i915 device
 * @pll: DPLL क्रम which to calculate the output frequency
 * @hw_state: DPLL's hardware state
 *
 * Read out @pll's hardware state पूर्णांकo @hw_state.
 */
bool पूर्णांकel_dpll_get_hw_state(काष्ठा drm_i915_निजी *i915,
			     काष्ठा पूर्णांकel_shared_dpll *pll,
			     काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	वापस pll->info->funcs->get_hw_state(i915, pll, hw_state);
पूर्ण

अटल व्योम पढ़ोout_dpll_hw_state(काष्ठा drm_i915_निजी *i915,
				  काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;

	pll->on = पूर्णांकel_dpll_get_hw_state(i915, pll, &pll->state.hw_state);

	अगर (IS_JSL_EHL(i915) && pll->on &&
	    pll->info->id == DPLL_ID_EHL_DPLL4) अणु
		pll->wakeref = पूर्णांकel_display_घातer_get(i915,
						       POWER_DOMAIN_DPLL_DC_OFF);
	पूर्ण

	pll->state.pipe_mask = 0;
	क्रम_each_पूर्णांकel_crtc(&i915->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		अगर (crtc_state->hw.active && crtc_state->shared_dpll == pll)
			pll->state.pipe_mask |= BIT(crtc->pipe);
	पूर्ण
	pll->active_mask = pll->state.pipe_mask;

	drm_dbg_kms(&i915->drm,
		    "%s hw state readout: pipe_mask 0x%x, on %i\n",
		    pll->info->name, pll->state.pipe_mask, pll->on);
पूर्ण

व्योम पूर्णांकel_dpll_update_ref_clks(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (i915->dpll.mgr && i915->dpll.mgr->update_ref_clks)
		i915->dpll.mgr->update_ref_clks(i915);
पूर्ण

व्योम पूर्णांकel_dpll_पढ़ोout_hw_state(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < i915->dpll.num_shared_dpll; i++)
		पढ़ोout_dpll_hw_state(i915, &i915->dpll.shared_dplls[i]);
पूर्ण

अटल व्योम sanitize_dpll_state(काष्ठा drm_i915_निजी *i915,
				काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	अगर (!pll->on || pll->active_mask)
		वापस;

	drm_dbg_kms(&i915->drm,
		    "%s enabled but not in use, disabling\n",
		    pll->info->name);

	pll->info->funcs->disable(i915, pll);
	pll->on = false;
पूर्ण

व्योम पूर्णांकel_dpll_sanitize_state(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < i915->dpll.num_shared_dpll; i++)
		sanitize_dpll_state(i915, &i915->dpll.shared_dplls[i]);
पूर्ण

/**
 * पूर्णांकel_dpll_dump_hw_state - ग_लिखो hw_state to dmesg
 * @dev_priv: i915 drm device
 * @hw_state: hw state to be written to the log
 *
 * Write the relevant values in @hw_state to dmesg using drm_dbg_kms.
 */
व्योम पूर्णांकel_dpll_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state)
अणु
	अगर (dev_priv->dpll.mgr) अणु
		dev_priv->dpll.mgr->dump_hw_state(dev_priv, hw_state);
	पूर्ण अन्यथा अणु
		/* fallback क्रम platक्रमms that करोn't use the shared dpll
		 * infraकाष्ठाure
		 */
		drm_dbg_kms(&dev_priv->drm,
			    "dpll_hw_state: dpll: 0x%x, dpll_md: 0x%x, "
			    "fp0: 0x%x, fp1: 0x%x\n",
			    hw_state->dpll,
			    hw_state->dpll_md,
			    hw_state->fp0,
			    hw_state->fp1);
	पूर्ण
पूर्ण
