<शैली गुरु>
/*
 * Copyright तऊ 2012-2016 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _INTEL_DPLL_MGR_H_
#घोषणा _INTEL_DPLL_MGR_H_

#समावेश <linux/types.h>

#समावेश "intel_display.h"
#समावेश "intel_wakeref.h"

/*FIXME: Move this to a more appropriate place. */
#घोषणा असल_dअगरf(a, b) (अणु			\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	(व्योम) (&__a == &__b);			\
	__a > __b ? (__a - __b) : (__b - __a); पूर्ण)

काष्ठा drm_device;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_shared_dpll;

/**
 * क्रमागत पूर्णांकel_dpll_id - possible DPLL ids
 *
 * Enumeration of possible IDs क्रम a DPLL. Real shared dpll ids must be >= 0.
 */
क्रमागत पूर्णांकel_dpll_id अणु
	/**
	 * @DPLL_ID_PRIVATE: non-shared dpll in use
	 */
	DPLL_ID_PRIVATE = -1,

	/**
	 * @DPLL_ID_PCH_PLL_A: DPLL A in ILK, SNB and IVB
	 */
	DPLL_ID_PCH_PLL_A = 0,
	/**
	 * @DPLL_ID_PCH_PLL_B: DPLL B in ILK, SNB and IVB
	 */
	DPLL_ID_PCH_PLL_B = 1,


	/**
	 * @DPLL_ID_WRPLL1: HSW and BDW WRPLL1
	 */
	DPLL_ID_WRPLL1 = 0,
	/**
	 * @DPLL_ID_WRPLL2: HSW and BDW WRPLL2
	 */
	DPLL_ID_WRPLL2 = 1,
	/**
	 * @DPLL_ID_SPLL: HSW and BDW SPLL
	 */
	DPLL_ID_SPLL = 2,
	/**
	 * @DPLL_ID_LCPLL_810: HSW and BDW 0.81 GHz LCPLL
	 */
	DPLL_ID_LCPLL_810 = 3,
	/**
	 * @DPLL_ID_LCPLL_1350: HSW and BDW 1.35 GHz LCPLL
	 */
	DPLL_ID_LCPLL_1350 = 4,
	/**
	 * @DPLL_ID_LCPLL_2700: HSW and BDW 2.7 GHz LCPLL
	 */
	DPLL_ID_LCPLL_2700 = 5,


	/**
	 * @DPLL_ID_SKL_DPLL0: SKL and later DPLL0
	 */
	DPLL_ID_SKL_DPLL0 = 0,
	/**
	 * @DPLL_ID_SKL_DPLL1: SKL and later DPLL1
	 */
	DPLL_ID_SKL_DPLL1 = 1,
	/**
	 * @DPLL_ID_SKL_DPLL2: SKL and later DPLL2
	 */
	DPLL_ID_SKL_DPLL2 = 2,
	/**
	 * @DPLL_ID_SKL_DPLL3: SKL and later DPLL3
	 */
	DPLL_ID_SKL_DPLL3 = 3,


	/**
	 * @DPLL_ID_ICL_DPLL0: ICL/TGL combo PHY DPLL0
	 */
	DPLL_ID_ICL_DPLL0 = 0,
	/**
	 * @DPLL_ID_ICL_DPLL1: ICL/TGL combo PHY DPLL1
	 */
	DPLL_ID_ICL_DPLL1 = 1,
	/**
	 * @DPLL_ID_EHL_DPLL4: EHL combo PHY DPLL4
	 */
	DPLL_ID_EHL_DPLL4 = 2,
	/**
	 * @DPLL_ID_ICL_TBTPLL: ICL/TGL TBT PLL
	 */
	DPLL_ID_ICL_TBTPLL = 2,
	/**
	 * @DPLL_ID_ICL_MGPLL1: ICL MG PLL 1 port 1 (C),
	 *                      TGL TC PLL 1 port 1 (TC1)
	 */
	DPLL_ID_ICL_MGPLL1 = 3,
	/**
	 * @DPLL_ID_ICL_MGPLL2: ICL MG PLL 1 port 2 (D)
	 *                      TGL TC PLL 1 port 2 (TC2)
	 */
	DPLL_ID_ICL_MGPLL2 = 4,
	/**
	 * @DPLL_ID_ICL_MGPLL3: ICL MG PLL 1 port 3 (E)
	 *                      TGL TC PLL 1 port 3 (TC3)
	 */
	DPLL_ID_ICL_MGPLL3 = 5,
	/**
	 * @DPLL_ID_ICL_MGPLL4: ICL MG PLL 1 port 4 (F)
	 *                      TGL TC PLL 1 port 4 (TC4)
	 */
	DPLL_ID_ICL_MGPLL4 = 6,
	/**
	 * @DPLL_ID_TGL_MGPLL5: TGL TC PLL port 5 (TC5)
	 */
	DPLL_ID_TGL_MGPLL5 = 7,
	/**
	 * @DPLL_ID_TGL_MGPLL6: TGL TC PLL port 6 (TC6)
	 */
	DPLL_ID_TGL_MGPLL6 = 8,

	/**
	 * @DPLL_ID_DG1_DPLL0: DG1 combo PHY DPLL0
	 */
	DPLL_ID_DG1_DPLL0 = 0,
	/**
	 * @DPLL_ID_DG1_DPLL1: DG1 combo PHY DPLL1
	 */
	DPLL_ID_DG1_DPLL1 = 1,
	/**
	 * @DPLL_ID_DG1_DPLL2: DG1 combo PHY DPLL2
	 */
	DPLL_ID_DG1_DPLL2 = 2,
	/**
	 * @DPLL_ID_DG1_DPLL3: DG1 combo PHY DPLL3
	 */
	DPLL_ID_DG1_DPLL3 = 3,
पूर्ण;

#घोषणा I915_NUM_PLLS 9

क्रमागत icl_port_dpll_id अणु
	ICL_PORT_DPLL_DEFAULT,
	ICL_PORT_DPLL_MG_PHY,

	ICL_PORT_DPLL_COUNT,
पूर्ण;

काष्ठा पूर्णांकel_dpll_hw_state अणु
	/* i9xx, pch plls */
	u32 dpll;
	u32 dpll_md;
	u32 fp0;
	u32 fp1;

	/* hsw, bdw */
	u32 wrpll;
	u32 spll;

	/* skl */
	/*
	 * DPLL_CTRL1 has 6 bits क्रम each each this DPLL. We store those in
	 * lower part of ctrl1 and they get shअगरted पूर्णांकo position when writing
	 * the रेजिस्टर.  This allows us to easily compare the state to share
	 * the DPLL.
	 */
	u32 ctrl1;
	/* HDMI only, 0 when used क्रम DP */
	u32 cfgcr1, cfgcr2;

	/* cnl */
	u32 cfgcr0;
	/* CNL also uses cfgcr1 */

	/* bxt */
	u32 ebb0, ebb4, pll0, pll1, pll2, pll3, pll6, pll8, pll9, pll10, pcsdw12;

	/*
	 * ICL uses the following, alपढ़ोy defined:
	 * u32 cfgcr0, cfgcr1;
	 */
	u32 mg_refclkin_ctl;
	u32 mg_clktop2_coreclkctl1;
	u32 mg_clktop2_hsclkctl;
	u32 mg_pll_भाग0;
	u32 mg_pll_भाग1;
	u32 mg_pll_lf;
	u32 mg_pll_frac_lock;
	u32 mg_pll_ssc;
	u32 mg_pll_bias;
	u32 mg_pll_tdc_coldst_bias;
	u32 mg_pll_bias_mask;
	u32 mg_pll_tdc_coldst_bias_mask;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_shared_dpll_state - hold the DPLL atomic state
 *
 * This काष्ठाure holds an atomic state क्रम the DPLL, that can represent
 * either its current state (in काष्ठा &पूर्णांकel_shared_dpll) or a desired
 * future state which would be applied by an atomic mode set (stored in
 * a काष्ठा &पूर्णांकel_atomic_state).
 *
 * See also पूर्णांकel_reserve_shared_dplls() and पूर्णांकel_release_shared_dplls().
 */
काष्ठा पूर्णांकel_shared_dpll_state अणु
	/**
	 * @pipe_mask: mask of pipes using this DPLL, active or not
	 */
	u8 pipe_mask;

	/**
	 * @hw_state: hardware configuration क्रम the DPLL stored in
	 * काष्ठा &पूर्णांकel_dpll_hw_state.
	 */
	काष्ठा पूर्णांकel_dpll_hw_state hw_state;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_shared_dpll_funcs - platक्रमm specअगरic hooks क्रम managing DPLLs
 */
काष्ठा पूर्णांकel_shared_dpll_funcs अणु
	/**
	 * @prepare:
	 *
	 * Optional hook to perक्रमm operations prior to enabling the PLL.
	 * Called from पूर्णांकel_prepare_shared_dpll() function unless the PLL
	 * is alपढ़ोy enabled.
	 */
	व्योम (*prepare)(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा पूर्णांकel_shared_dpll *pll);

	/**
	 * @enable:
	 *
	 * Hook क्रम enabling the pll, called from पूर्णांकel_enable_shared_dpll()
	 * अगर the pll is not alपढ़ोy enabled.
	 */
	व्योम (*enable)(काष्ठा drm_i915_निजी *dev_priv,
		       काष्ठा पूर्णांकel_shared_dpll *pll);

	/**
	 * @disable:
	 *
	 * Hook क्रम disabling the pll, called from पूर्णांकel_disable_shared_dpll()
	 * only when it is safe to disable the pll, i.e., there are no more
	 * tracked users क्रम it.
	 */
	व्योम (*disable)(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा पूर्णांकel_shared_dpll *pll);

	/**
	 * @get_hw_state:
	 *
	 * Hook क्रम पढ़ोing the values currently programmed to the DPLL
	 * रेजिस्टरs. This is used क्रम initial hw state पढ़ोout and state
	 * verअगरication after a mode set.
	 */
	bool (*get_hw_state)(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_shared_dpll *pll,
			     काष्ठा पूर्णांकel_dpll_hw_state *hw_state);

	/**
	 * @get_freq:
	 *
	 * Hook क्रम calculating the pll's output frequency based on its
	 * passed in state.
	 */
	पूर्णांक (*get_freq)(काष्ठा drm_i915_निजी *i915,
			स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
			स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state);
पूर्ण;

/**
 * काष्ठा dpll_info - display PLL platक्रमm specअगरic info
 */
काष्ठा dpll_info अणु
	/**
	 * @name: DPLL name; used क्रम logging
	 */
	स्थिर अक्षर *name;

	/**
	 * @funcs: platक्रमm specअगरic hooks
	 */
	स्थिर काष्ठा पूर्णांकel_shared_dpll_funcs *funcs;

	/**
	 * @id: unique indentअगरier क्रम this DPLL; should match the index in the
	 * dev_priv->shared_dplls array
	 */
	क्रमागत पूर्णांकel_dpll_id id;

#घोषणा INTEL_DPLL_ALWAYS_ON	(1 << 0)
	/**
	 * @flags:
	 *
	 * INTEL_DPLL_ALWAYS_ON
	 *     Inक्रमm the state checker that the DPLL is kept enabled even अगर
	 *     not in use by any CRTC.
	 */
	u32 flags;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_shared_dpll - display PLL with tracked state and users
 */
काष्ठा पूर्णांकel_shared_dpll अणु
	/**
	 * @state:
	 *
	 * Store the state क्रम the pll, including its hw state
	 * and CRTCs using it.
	 */
	काष्ठा पूर्णांकel_shared_dpll_state state;

	/**
	 * @active_mask: mask of active pipes (i.e. DPMS on) using this DPLL
	 */
	u8 active_mask;

	/**
	 * @on: is the PLL actually active? Disabled during modeset
	 */
	bool on;

	/**
	 * @info: platक्रमm specअगरic info
	 */
	स्थिर काष्ठा dpll_info *info;

	/**
	 * @wakeref: In some platक्रमms a device-level runसमय pm reference may
	 * need to be grabbed to disable DC states जबतक this DPLL is enabled
	 */
	पूर्णांकel_wakeref_t wakeref;
पूर्ण;

#घोषणा SKL_DPLL0 0
#घोषणा SKL_DPLL1 1
#घोषणा SKL_DPLL2 2
#घोषणा SKL_DPLL3 3

/* shared dpll functions */
काष्ठा पूर्णांकel_shared_dpll *
पूर्णांकel_get_shared_dpll_by_id(काष्ठा drm_i915_निजी *dev_priv,
			    क्रमागत पूर्णांकel_dpll_id id);
क्रमागत पूर्णांकel_dpll_id
पूर्णांकel_get_shared_dpll_id(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा पूर्णांकel_shared_dpll *pll);
व्योम निश्चित_shared_dpll(काष्ठा drm_i915_निजी *dev_priv,
			काष्ठा पूर्णांकel_shared_dpll *pll,
			bool state);
#घोषणा निश्चित_shared_dpll_enabled(d, p) निश्चित_shared_dpll(d, p, true)
#घोषणा निश्चित_shared_dpll_disabled(d, p) निश्चित_shared_dpll(d, p, false)
bool पूर्णांकel_reserve_shared_dplls(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा पूर्णांकel_encoder *encoder);
व्योम पूर्णांकel_release_shared_dplls(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_crtc *crtc);
व्योम icl_set_active_port_dpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      क्रमागत icl_port_dpll_id port_dpll_id);
व्योम पूर्णांकel_update_active_dpll(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_encoder *encoder);
पूर्णांक पूर्णांकel_dpll_get_freq(काष्ठा drm_i915_निजी *i915,
			स्थिर काष्ठा पूर्णांकel_shared_dpll *pll,
			स्थिर काष्ठा पूर्णांकel_dpll_hw_state *pll_state);
bool पूर्णांकel_dpll_get_hw_state(काष्ठा drm_i915_निजी *i915,
			     काष्ठा पूर्णांकel_shared_dpll *pll,
			     काष्ठा पूर्णांकel_dpll_hw_state *hw_state);
व्योम पूर्णांकel_prepare_shared_dpll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_enable_shared_dpll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_disable_shared_dpll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_shared_dpll_swap_state(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_shared_dpll_init(काष्ठा drm_device *dev);
व्योम पूर्णांकel_dpll_update_ref_clks(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_dpll_पढ़ोout_hw_state(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_dpll_sanitize_state(काष्ठा drm_i915_निजी *dev_priv);

व्योम पूर्णांकel_dpll_dump_hw_state(काष्ठा drm_i915_निजी *dev_priv,
			      स्थिर काष्ठा पूर्णांकel_dpll_hw_state *hw_state);
क्रमागत पूर्णांकel_dpll_id icl_tc_port_to_pll_id(क्रमागत tc_port tc_port);
bool पूर्णांकel_dpll_is_combophy(क्रमागत पूर्णांकel_dpll_id id);

#पूर्ण_अगर /* _INTEL_DPLL_MGR_H_ */
