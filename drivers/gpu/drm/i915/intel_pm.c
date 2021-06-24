<शैली गुरु>
/*
 * Copyright तऊ 2012 Intel Corporation
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
 * Authors:
 *    Eugeni Doकरोnov <eugeni.करोकरोnov@पूर्णांकel.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "display/intel_atomic.h"
#समावेश "display/intel_atomic_plane.h"
#समावेश "display/intel_bw.h"
#समावेश "display/intel_display_types.h"
#समावेश "display/intel_fbc.h"
#समावेश "display/intel_sprite.h"
#समावेश "display/skl_universal_plane.h"

#समावेश "gt/intel_llc.h"

#समावेश "i915_drv.h"
#समावेश "i915_fixed.h"
#समावेश "i915_irq.h"
#समावेश "i915_trace.h"
#समावेश "intel_pm.h"
#समावेश "intel_sideband.h"
#समावेश "../../../platform/x86/intel_ips.h"

/* Stores plane specअगरic WM parameters */
काष्ठा skl_wm_params अणु
	bool x_tiled, y_tiled;
	bool rc_surface;
	bool is_planar;
	u32 width;
	u8 cpp;
	u32 plane_pixel_rate;
	u32 y_min_scanlines;
	u32 plane_bytes_per_line;
	uपूर्णांक_fixed_16_16_t plane_blocks_per_line;
	uपूर्णांक_fixed_16_16_t y_tile_minimum;
	u32 lineसमय_us;
	u32 dbuf_block_size;
पूर्ण;

/* used in computing the new watermarks state */
काष्ठा पूर्णांकel_wm_config अणु
	अचिन्हित पूर्णांक num_pipes_active;
	bool sprites_enabled;
	bool sprites_scaled;
पूर्ण;

अटल व्योम gen9_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_LLC(dev_priv)) अणु
		/*
		 * WaCompressedResourceDisplayNewHashMode:skl,kbl
		 * Display WA #0390: skl,kbl
		 *
		 * Must match Sampler, Pixel Back End, and Media. See
		 * WaCompressedResourceSamplerPbeMediaNewHashMode.
		 */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PAR1_1,
			   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PAR1_1) |
			   SKL_DE_COMPRESSED_HASH_MODE);
	पूर्ण

	/* See Bspec note क्रम PSR2_CTL bit 31, Wa#828:skl,bxt,kbl,cfl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PAR1_1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PAR1_1) | SKL_EDP_PSR_FIX_RDWRAP);

	/* WaEnableChickenDCPR:skl,bxt,kbl,glk,cfl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_CHICKEN_DCPR_1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_CHICKEN_DCPR_1) | MASK_WAKEMEM);

	/*
	 * WaFbcWakeMemOn:skl,bxt,kbl,glk,cfl
	 * Display WA #0859: skl,bxt,kbl,glk,cfl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		   DISP_FBC_MEMORY_WAKE);
पूर्ण

अटल व्योम bxt_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen9_init_घड़ी_gating(dev_priv);

	/* WaDisableSDEUnitClockGating:bxt */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_UCGCTL6, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_UCGCTL6) |
		   GEN8_SDEUNIT_CLOCK_GATE_DISABLE);

	/*
	 * FIXME:
	 * GEN8_HDCUNIT_CLOCK_GATE_DISABLE_HDCREQ applies on 3x6 GT SKUs only.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_UCGCTL6, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_UCGCTL6) |
		   GEN8_HDCUNIT_CLOCK_GATE_DISABLE_HDCREQ);

	/*
	 * Wa: Backlight PWM may stop in the निश्चितed state, causing backlight
	 * to stay fully on.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN9_CLKGATE_DIS_0, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN9_CLKGATE_DIS_0) |
		   PWM1_GATING_DIS | PWM2_GATING_DIS);

	/*
	 * Lower the display पूर्णांकernal समयout.
	 * This is needed to aव्योम any hard hangs when DSI port PLL
	 * is off and a MMIO access is attempted by any privilege
	 * application, using batch buffers or any other means.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RM_TIMEOUT, MMIO_TIMEOUT_US(950));

	/*
	 * WaFbcTurnOffFbcWatermark:bxt
	 * Display WA #0562: bxt
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		   DISP_FBC_WM_DIS);

	/*
	 * WaFbcHighMemBwCorruptionAव्योमance:bxt
	 * Display WA #0883: bxt
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DPFC_CHICKEN) |
		   ILK_DPFC_DISABLE_DUMMY0);
पूर्ण

अटल व्योम glk_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen9_init_घड़ी_gating(dev_priv);

	/*
	 * WaDisablePWMClockGating:glk
	 * Backlight PWM may stop in the निश्चितed state, causing backlight
	 * to stay fully on.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN9_CLKGATE_DIS_0, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN9_CLKGATE_DIS_0) |
		   PWM1_GATING_DIS | PWM2_GATING_DIS);
पूर्ण

अटल व्योम pnv_get_mem_freq(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CLKCFG);

	चयन (पंचांगp & CLKCFG_FSB_MASK) अणु
	हाल CLKCFG_FSB_533:
		dev_priv->fsb_freq = 533; /* 133*4 */
		अवरोध;
	हाल CLKCFG_FSB_800:
		dev_priv->fsb_freq = 800; /* 200*4 */
		अवरोध;
	हाल CLKCFG_FSB_667:
		dev_priv->fsb_freq =  667; /* 167*4 */
		अवरोध;
	हाल CLKCFG_FSB_400:
		dev_priv->fsb_freq = 400; /* 100*4 */
		अवरोध;
	पूर्ण

	चयन (पंचांगp & CLKCFG_MEM_MASK) अणु
	हाल CLKCFG_MEM_533:
		dev_priv->mem_freq = 533;
		अवरोध;
	हाल CLKCFG_MEM_667:
		dev_priv->mem_freq = 667;
		अवरोध;
	हाल CLKCFG_MEM_800:
		dev_priv->mem_freq = 800;
		अवरोध;
	पूर्ण

	/* detect pineview DDR3 setting */
	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CSHRDDR3CTL);
	dev_priv->is_ddr3 = (पंचांगp & CSHRDDR3CTL_DDR3) ? 1 : 0;
पूर्ण

अटल व्योम ilk_get_mem_freq(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u16 ddrpll, csipll;

	ddrpll = पूर्णांकel_uncore_पढ़ो16(&dev_priv->uncore, DDRMPLL1);
	csipll = पूर्णांकel_uncore_पढ़ो16(&dev_priv->uncore, CSIPLL0);

	चयन (ddrpll & 0xff) अणु
	हाल 0xc:
		dev_priv->mem_freq = 800;
		अवरोध;
	हाल 0x10:
		dev_priv->mem_freq = 1066;
		अवरोध;
	हाल 0x14:
		dev_priv->mem_freq = 1333;
		अवरोध;
	हाल 0x18:
		dev_priv->mem_freq = 1600;
		अवरोध;
	शेष:
		drm_dbg(&dev_priv->drm, "unknown memory frequency 0x%02x\n",
			ddrpll & 0xff);
		dev_priv->mem_freq = 0;
		अवरोध;
	पूर्ण

	चयन (csipll & 0x3ff) अणु
	हाल 0x00c:
		dev_priv->fsb_freq = 3200;
		अवरोध;
	हाल 0x00e:
		dev_priv->fsb_freq = 3733;
		अवरोध;
	हाल 0x010:
		dev_priv->fsb_freq = 4266;
		अवरोध;
	हाल 0x012:
		dev_priv->fsb_freq = 4800;
		अवरोध;
	हाल 0x014:
		dev_priv->fsb_freq = 5333;
		अवरोध;
	हाल 0x016:
		dev_priv->fsb_freq = 5866;
		अवरोध;
	हाल 0x018:
		dev_priv->fsb_freq = 6400;
		अवरोध;
	शेष:
		drm_dbg(&dev_priv->drm, "unknown fsb frequency 0x%04x\n",
			csipll & 0x3ff);
		dev_priv->fsb_freq = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा cxsr_latency cxsr_latency_table[] = अणु
	अणु1, 0, 800, 400, 3382, 33382, 3983, 33983पूर्ण,    /* DDR2-400 SC */
	अणु1, 0, 800, 667, 3354, 33354, 3807, 33807पूर्ण,    /* DDR2-667 SC */
	अणु1, 0, 800, 800, 3347, 33347, 3763, 33763पूर्ण,    /* DDR2-800 SC */
	अणु1, 1, 800, 667, 6420, 36420, 6873, 36873पूर्ण,    /* DDR3-667 SC */
	अणु1, 1, 800, 800, 5902, 35902, 6318, 36318पूर्ण,    /* DDR3-800 SC */

	अणु1, 0, 667, 400, 3400, 33400, 4021, 34021पूर्ण,    /* DDR2-400 SC */
	अणु1, 0, 667, 667, 3372, 33372, 3845, 33845पूर्ण,    /* DDR2-667 SC */
	अणु1, 0, 667, 800, 3386, 33386, 3822, 33822पूर्ण,    /* DDR2-800 SC */
	अणु1, 1, 667, 667, 6438, 36438, 6911, 36911पूर्ण,    /* DDR3-667 SC */
	अणु1, 1, 667, 800, 5941, 35941, 6377, 36377पूर्ण,    /* DDR3-800 SC */

	अणु1, 0, 400, 400, 3472, 33472, 4173, 34173पूर्ण,    /* DDR2-400 SC */
	अणु1, 0, 400, 667, 3443, 33443, 3996, 33996पूर्ण,    /* DDR2-667 SC */
	अणु1, 0, 400, 800, 3430, 33430, 3946, 33946पूर्ण,    /* DDR2-800 SC */
	अणु1, 1, 400, 667, 6509, 36509, 7062, 37062पूर्ण,    /* DDR3-667 SC */
	अणु1, 1, 400, 800, 5985, 35985, 6501, 36501पूर्ण,    /* DDR3-800 SC */

	अणु0, 0, 800, 400, 3438, 33438, 4065, 34065पूर्ण,    /* DDR2-400 SC */
	अणु0, 0, 800, 667, 3410, 33410, 3889, 33889पूर्ण,    /* DDR2-667 SC */
	अणु0, 0, 800, 800, 3403, 33403, 3845, 33845पूर्ण,    /* DDR2-800 SC */
	अणु0, 1, 800, 667, 6476, 36476, 6955, 36955पूर्ण,    /* DDR3-667 SC */
	अणु0, 1, 800, 800, 5958, 35958, 6400, 36400पूर्ण,    /* DDR3-800 SC */

	अणु0, 0, 667, 400, 3456, 33456, 4103, 34106पूर्ण,    /* DDR2-400 SC */
	अणु0, 0, 667, 667, 3428, 33428, 3927, 33927पूर्ण,    /* DDR2-667 SC */
	अणु0, 0, 667, 800, 3443, 33443, 3905, 33905पूर्ण,    /* DDR2-800 SC */
	अणु0, 1, 667, 667, 6494, 36494, 6993, 36993पूर्ण,    /* DDR3-667 SC */
	अणु0, 1, 667, 800, 5998, 35998, 6460, 36460पूर्ण,    /* DDR3-800 SC */

	अणु0, 0, 400, 400, 3528, 33528, 4255, 34255पूर्ण,    /* DDR2-400 SC */
	अणु0, 0, 400, 667, 3500, 33500, 4079, 34079पूर्ण,    /* DDR2-667 SC */
	अणु0, 0, 400, 800, 3487, 33487, 4029, 34029पूर्ण,    /* DDR2-800 SC */
	अणु0, 1, 400, 667, 6566, 36566, 7145, 37145पूर्ण,    /* DDR3-667 SC */
	अणु0, 1, 400, 800, 6042, 36042, 6584, 36584पूर्ण,    /* DDR3-800 SC */
पूर्ण;

अटल स्थिर काष्ठा cxsr_latency *पूर्णांकel_get_cxsr_latency(bool is_desktop,
							 bool is_ddr3,
							 पूर्णांक fsb,
							 पूर्णांक mem)
अणु
	स्थिर काष्ठा cxsr_latency *latency;
	पूर्णांक i;

	अगर (fsb == 0 || mem == 0)
		वापस शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(cxsr_latency_table); i++) अणु
		latency = &cxsr_latency_table[i];
		अगर (is_desktop == latency->is_desktop &&
		    is_ddr3 == latency->is_ddr3 &&
		    fsb == latency->fsb_freq && mem == latency->mem_freq)
			वापस latency;
	पूर्ण

	DRM_DEBUG_KMS("Unknown FSB/MEM found, disable CxSR\n");

	वापस शून्य;
पूर्ण

अटल व्योम chv_set_memory_dvfs(काष्ठा drm_i915_निजी *dev_priv, bool enable)
अणु
	u32 val;

	vlv_punit_get(dev_priv);

	val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DDR_SETUP2);
	अगर (enable)
		val &= ~FORCE_DDR_HIGH_FREQ;
	अन्यथा
		val |= FORCE_DDR_HIGH_FREQ;
	val &= ~FORCE_DDR_LOW_FREQ;
	val |= FORCE_DDR_FREQ_REQ_ACK;
	vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_DDR_SETUP2, val);

	अगर (रुको_क्रम((vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DDR_SETUP2) &
		      FORCE_DDR_FREQ_REQ_ACK) == 0, 3))
		drm_err(&dev_priv->drm,
			"timed out waiting for Punit DDR DVFS request\n");

	vlv_punit_put(dev_priv);
पूर्ण

अटल व्योम chv_set_memory_pm5(काष्ठा drm_i915_निजी *dev_priv, bool enable)
अणु
	u32 val;

	vlv_punit_get(dev_priv);

	val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM);
	अगर (enable)
		val |= DSP_MAXFIFO_PM5_ENABLE;
	अन्यथा
		val &= ~DSP_MAXFIFO_PM5_ENABLE;
	vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_DSPSSPM, val);

	vlv_punit_put(dev_priv);
पूर्ण

#घोषणा FW_WM(value, plane) \
	(((value) << DSPFW_ ## plane ## _SHIFT) & DSPFW_ ## plane ## _MASK)

अटल bool _पूर्णांकel_set_memory_cxsr(काष्ठा drm_i915_निजी *dev_priv, bool enable)
अणु
	bool was_enabled;
	u32 val;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		was_enabled = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FW_BLC_SELF_VLV) & FW_CSPWRDWNEN;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC_SELF_VLV, enable ? FW_CSPWRDWNEN : 0);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, FW_BLC_SELF_VLV);
	पूर्ण अन्यथा अगर (IS_G4X(dev_priv) || IS_I965GM(dev_priv)) अणु
		was_enabled = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FW_BLC_SELF) & FW_BLC_SELF_EN;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC_SELF, enable ? FW_BLC_SELF_EN : 0);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, FW_BLC_SELF);
	पूर्ण अन्यथा अगर (IS_PINEVIEW(dev_priv)) अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW3);
		was_enabled = val & PINEVIEW_SELF_REFRESH_EN;
		अगर (enable)
			val |= PINEVIEW_SELF_REFRESH_EN;
		अन्यथा
			val &= ~PINEVIEW_SELF_REFRESH_EN;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3, val);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, DSPFW3);
	पूर्ण अन्यथा अगर (IS_I945G(dev_priv) || IS_I945GM(dev_priv)) अणु
		was_enabled = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FW_BLC_SELF) & FW_BLC_SELF_EN;
		val = enable ? _MASKED_BIT_ENABLE(FW_BLC_SELF_EN) :
			       _MASKED_BIT_DISABLE(FW_BLC_SELF_EN);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC_SELF, val);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, FW_BLC_SELF);
	पूर्ण अन्यथा अगर (IS_I915GM(dev_priv)) अणु
		/*
		 * FIXME can't find a bit like this क्रम 915G, and
		 * and yet it करोes have the related watermark in
		 * FW_BLC_SELF. What's going on?
		 */
		was_enabled = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, INSTPM) & INSTPM_SELF_EN;
		val = enable ? _MASKED_BIT_ENABLE(INSTPM_SELF_EN) :
			       _MASKED_BIT_DISABLE(INSTPM_SELF_EN);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, INSTPM, val);
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, INSTPM);
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	trace_पूर्णांकel_memory_cxsr(dev_priv, was_enabled, enable);

	drm_dbg_kms(&dev_priv->drm, "memory self-refresh is %s (was %s)\n",
		    enableddisabled(enable),
		    enableddisabled(was_enabled));

	वापस was_enabled;
पूर्ण

/**
 * पूर्णांकel_set_memory_cxsr - Configure CxSR state
 * @dev_priv: i915 device
 * @enable: Allow vs. disallow CxSR
 *
 * Allow or disallow the प्रणाली to enter a special CxSR
 * (C-state self refresh) state. What typically happens in CxSR mode
 * is that several display FIFOs may get combined पूर्णांकo a single larger
 * FIFO क्रम a particular plane (so called max FIFO mode) to allow the
 * प्रणाली to defer memory fetches दीर्घer, and the memory will enter
 * self refresh.
 *
 * Note that enabling CxSR करोes not guarantee that the प्रणाली enter
 * this special mode, nor करोes it guarantee that the प्रणाली stays
 * in that mode once entered. So this just allows/disallows the प्रणाली
 * to स्वतःnomously utilize the CxSR mode. Other factors such as core
 * C-states will affect when/अगर the प्रणाली actually enters/निकासs the
 * CxSR mode.
 *
 * Note that on VLV/CHV this actually only controls the max FIFO mode,
 * and the प्रणाली is मुक्त to enter/निकास memory self refresh at any समय
 * even when the use of CxSR has been disallowed.
 *
 * While the प्रणाली is actually in the CxSR/max FIFO mode, some plane
 * control रेजिस्टरs will not get latched on vblank. Thus in order to
 * guarantee the प्रणाली will respond to changes in the plane रेजिस्टरs
 * we must always disallow CxSR prior to making changes to those रेजिस्टरs.
 * Unक्रमtunately the प्रणाली will re-evaluate the CxSR conditions at
 * frame start which happens after vblank start (which is when the plane
 * रेजिस्टरs would get latched), so we can't proceed with the plane update
 * during the same frame where we disallowed CxSR.
 *
 * Certain platक्रमms also have a deeper HPLL SR mode. Fortunately the
 * HPLL SR mode depends on CxSR itself, so we करोn't have to hand hold
 * the hardware w.r.t. HPLL SR when writing to plane रेजिस्टरs.
 * Disallowing just CxSR is sufficient.
 */
bool पूर्णांकel_set_memory_cxsr(काष्ठा drm_i915_निजी *dev_priv, bool enable)
अणु
	bool ret;

	mutex_lock(&dev_priv->wm.wm_mutex);
	ret = _पूर्णांकel_set_memory_cxsr(dev_priv, enable);
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->wm.vlv.cxsr = enable;
	अन्यथा अगर (IS_G4X(dev_priv))
		dev_priv->wm.g4x.cxsr = enable;
	mutex_unlock(&dev_priv->wm.wm_mutex);

	वापस ret;
पूर्ण

/*
 * Latency क्रम FIFO fetches is dependent on several factors:
 *   - memory configuration (speed, channels)
 *   - chipset
 *   - current MCH state
 * It can be fairly high in some situations, so here we assume a fairly
 * pessimal value.  It's a tradeoff between extra memory fetches (अगर we
 * set this value too high, the FIFO will fetch frequently to stay full)
 * and घातer consumption (set it too low to save घातer and we might see
 * FIFO underruns and display "flicker").
 *
 * A value of 5us seems to be a good balance; safe क्रम very low end
 * platक्रमms but not overly aggressive on lower latency configs.
 */
अटल स्थिर पूर्णांक pessimal_latency_ns = 5000;

#घोषणा VLV_FIFO_START(dsparb, dsparb2, lo_shअगरt, hi_shअगरt) \
	((((dsparb) >> (lo_shअगरt)) & 0xff) | ((((dsparb2) >> (hi_shअगरt)) & 0x1) << 8))

अटल व्योम vlv_get_fअगरo_size(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा vlv_fअगरo_state *fअगरo_state = &crtc_state->wm.vlv.fअगरo_state;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक sprite0_start, sprite1_start;
	u32 dsparb, dsparb2, dsparb3;

	चयन (pipe) अणु
	हाल PIPE_A:
		dsparb = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB);
		dsparb2 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB2);
		sprite0_start = VLV_FIFO_START(dsparb, dsparb2, 0, 0);
		sprite1_start = VLV_FIFO_START(dsparb, dsparb2, 8, 4);
		अवरोध;
	हाल PIPE_B:
		dsparb = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB);
		dsparb2 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB2);
		sprite0_start = VLV_FIFO_START(dsparb, dsparb2, 16, 8);
		sprite1_start = VLV_FIFO_START(dsparb, dsparb2, 24, 12);
		अवरोध;
	हाल PIPE_C:
		dsparb2 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB2);
		dsparb3 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB3);
		sprite0_start = VLV_FIFO_START(dsparb3, dsparb2, 0, 16);
		sprite1_start = VLV_FIFO_START(dsparb3, dsparb2, 8, 20);
		अवरोध;
	शेष:
		MISSING_CASE(pipe);
		वापस;
	पूर्ण

	fअगरo_state->plane[PLANE_PRIMARY] = sprite0_start;
	fअगरo_state->plane[PLANE_SPRITE0] = sprite1_start - sprite0_start;
	fअगरo_state->plane[PLANE_SPRITE1] = 511 - sprite1_start;
	fअगरo_state->plane[PLANE_CURSOR] = 63;
पूर्ण

अटल पूर्णांक i9xx_get_fअगरo_size(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत i9xx_plane_id i9xx_plane)
अणु
	u32 dsparb = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB);
	पूर्णांक size;

	size = dsparb & 0x7f;
	अगर (i9xx_plane == PLANE_B)
		size = ((dsparb >> DSPARB_CSTART_SHIFT) & 0x7f) - size;

	drm_dbg_kms(&dev_priv->drm, "FIFO size - (0x%08x) %c: %d\n",
		    dsparb, plane_name(i9xx_plane), size);

	वापस size;
पूर्ण

अटल पूर्णांक i830_get_fअगरo_size(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत i9xx_plane_id i9xx_plane)
अणु
	u32 dsparb = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB);
	पूर्णांक size;

	size = dsparb & 0x1ff;
	अगर (i9xx_plane == PLANE_B)
		size = ((dsparb >> DSPARB_BEND_SHIFT) & 0x1ff) - size;
	size >>= 1; /* Convert to cachelines */

	drm_dbg_kms(&dev_priv->drm, "FIFO size - (0x%08x) %c: %d\n",
		    dsparb, plane_name(i9xx_plane), size);

	वापस size;
पूर्ण

अटल पूर्णांक i845_get_fअगरo_size(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत i9xx_plane_id i9xx_plane)
अणु
	u32 dsparb = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPARB);
	पूर्णांक size;

	size = dsparb & 0x7f;
	size >>= 2; /* Convert to cachelines */

	drm_dbg_kms(&dev_priv->drm, "FIFO size - (0x%08x) %c: %d\n",
		    dsparb, plane_name(i9xx_plane), size);

	वापस size;
पूर्ण

/* Pineview has dअगरferent values क्रम various configs */
अटल स्थिर काष्ठा पूर्णांकel_watermark_params pnv_display_wm = अणु
	.fअगरo_size = PINEVIEW_DISPLAY_FIFO,
	.max_wm = PINEVIEW_MAX_WM,
	.शेष_wm = PINEVIEW_DFT_WM,
	.guard_size = PINEVIEW_GUARD_WM,
	.cacheline_size = PINEVIEW_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params pnv_display_hplloff_wm = अणु
	.fअगरo_size = PINEVIEW_DISPLAY_FIFO,
	.max_wm = PINEVIEW_MAX_WM,
	.शेष_wm = PINEVIEW_DFT_HPLLOFF_WM,
	.guard_size = PINEVIEW_GUARD_WM,
	.cacheline_size = PINEVIEW_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params pnv_cursor_wm = अणु
	.fअगरo_size = PINEVIEW_CURSOR_FIFO,
	.max_wm = PINEVIEW_CURSOR_MAX_WM,
	.शेष_wm = PINEVIEW_CURSOR_DFT_WM,
	.guard_size = PINEVIEW_CURSOR_GUARD_WM,
	.cacheline_size = PINEVIEW_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params pnv_cursor_hplloff_wm = अणु
	.fअगरo_size = PINEVIEW_CURSOR_FIFO,
	.max_wm = PINEVIEW_CURSOR_MAX_WM,
	.शेष_wm = PINEVIEW_CURSOR_DFT_WM,
	.guard_size = PINEVIEW_CURSOR_GUARD_WM,
	.cacheline_size = PINEVIEW_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params i965_cursor_wm_info = अणु
	.fअगरo_size = I965_CURSOR_FIFO,
	.max_wm = I965_CURSOR_MAX_WM,
	.शेष_wm = I965_CURSOR_DFT_WM,
	.guard_size = 2,
	.cacheline_size = I915_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params i945_wm_info = अणु
	.fअगरo_size = I945_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.शेष_wm = 1,
	.guard_size = 2,
	.cacheline_size = I915_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params i915_wm_info = अणु
	.fअगरo_size = I915_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.शेष_wm = 1,
	.guard_size = 2,
	.cacheline_size = I915_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params i830_a_wm_info = अणु
	.fअगरo_size = I855GM_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.शेष_wm = 1,
	.guard_size = 2,
	.cacheline_size = I830_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params i830_bc_wm_info = अणु
	.fअगरo_size = I855GM_FIFO_SIZE,
	.max_wm = I915_MAX_WM/2,
	.शेष_wm = 1,
	.guard_size = 2,
	.cacheline_size = I830_FIFO_LINE_SIZE,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_watermark_params i845_wm_info = अणु
	.fअगरo_size = I830_FIFO_SIZE,
	.max_wm = I915_MAX_WM,
	.शेष_wm = 1,
	.guard_size = 2,
	.cacheline_size = I830_FIFO_LINE_SIZE,
पूर्ण;

/**
 * पूर्णांकel_wm_method1 - Method 1 / "small buffer" watermark क्रमmula
 * @pixel_rate: Pipe pixel rate in kHz
 * @cpp: Plane bytes per pixel
 * @latency: Memory wakeup latency in 0.1us units
 *
 * Compute the watermark using the method 1 or "small buffer"
 * क्रमmula. The caller may additonally add extra cachelines
 * to account क्रम TLB misses and घड़ी crossings.
 *
 * This method is concerned with the लघु term drain rate
 * of the FIFO, ie. it करोes not account क्रम blanking periods
 * which would effectively reduce the average drain rate across
 * a दीर्घer period. The name "small" refers to the fact the
 * FIFO is relatively small compared to the amount of data
 * fetched.
 *
 * The FIFO level vs. समय graph might look something like:
 *
 *   |\   |\
 *   | \  | \
 * __---__---__ (- plane active, _ blanking)
 * -> समय
 *
 * or perhaps like this:
 *
 *   |\|\  |\|\
 * __----__----__ (- plane active, _ blanking)
 * -> समय
 *
 * Returns:
 * The watermark in bytes
 */
अटल अचिन्हित पूर्णांक पूर्णांकel_wm_method1(अचिन्हित पूर्णांक pixel_rate,
				     अचिन्हित पूर्णांक cpp,
				     अचिन्हित पूर्णांक latency)
अणु
	u64 ret;

	ret = mul_u32_u32(pixel_rate, cpp * latency);
	ret = DIV_ROUND_UP_ULL(ret, 10000);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_wm_method2 - Method 2 / "large buffer" watermark क्रमmula
 * @pixel_rate: Pipe pixel rate in kHz
 * @htotal: Pipe horizontal total
 * @width: Plane width in pixels
 * @cpp: Plane bytes per pixel
 * @latency: Memory wakeup latency in 0.1us units
 *
 * Compute the watermark using the method 2 or "large buffer"
 * क्रमmula. The caller may additonally add extra cachelines
 * to account क्रम TLB misses and घड़ी crossings.
 *
 * This method is concerned with the दीर्घ term drain rate
 * of the FIFO, ie. it करोes account क्रम blanking periods
 * which effectively reduce the average drain rate across
 * a दीर्घer period. The name "large" refers to the fact the
 * FIFO is relatively large compared to the amount of data
 * fetched.
 *
 * The FIFO level vs. समय graph might look something like:
 *
 *    |\___       |\___
 *    |    \___   |    \___
 *    |        \  |        \
 * __ --__--__--__--__--__--__ (- plane active, _ blanking)
 * -> समय
 *
 * Returns:
 * The watermark in bytes
 */
अटल अचिन्हित पूर्णांक पूर्णांकel_wm_method2(अचिन्हित पूर्णांक pixel_rate,
				     अचिन्हित पूर्णांक htotal,
				     अचिन्हित पूर्णांक width,
				     अचिन्हित पूर्णांक cpp,
				     अचिन्हित पूर्णांक latency)
अणु
	अचिन्हित पूर्णांक ret;

	/*
	 * FIXME हटाओ once all users are computing
	 * watermarks in the correct place.
	 */
	अगर (WARN_ON_ONCE(htotal == 0))
		htotal = 1;

	ret = (latency * pixel_rate) / (htotal * 10000);
	ret = (ret + 1) * width * cpp;

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_calculate_wm - calculate watermark level
 * @pixel_rate: pixel घड़ी
 * @wm: chip FIFO params
 * @fअगरo_size: size of the FIFO buffer
 * @cpp: bytes per pixel
 * @latency_ns: memory latency क्रम the platक्रमm
 *
 * Calculate the watermark level (the level at which the display plane will
 * start fetching from memory again).  Each chip has a dअगरferent display
 * FIFO size and allocation, so the caller needs to figure that out and pass
 * in the correct पूर्णांकel_watermark_params काष्ठाure.
 *
 * As the pixel घड़ी runs, the FIFO will be drained at a rate that depends
 * on the pixel size.  When it reaches the watermark level, it'll start
 * fetching FIFO line sized based chunks from memory until the FIFO fills
 * past the watermark poपूर्णांक.  If the FIFO drains completely, a FIFO underrun
 * will occur, and a display engine hang could result.
 */
अटल अचिन्हित पूर्णांक पूर्णांकel_calculate_wm(पूर्णांक pixel_rate,
				       स्थिर काष्ठा पूर्णांकel_watermark_params *wm,
				       पूर्णांक fअगरo_size, पूर्णांक cpp,
				       अचिन्हित पूर्णांक latency_ns)
अणु
	पूर्णांक entries, wm_size;

	/*
	 * Note: we need to make sure we करोn't overflow क्रम various घड़ी &
	 * latency values.
	 * घड़ीs go from a few thousand to several hundred thousand.
	 * latency is usually a few thousand
	 */
	entries = पूर्णांकel_wm_method1(pixel_rate, cpp,
				   latency_ns / 100);
	entries = DIV_ROUND_UP(entries, wm->cacheline_size) +
		wm->guard_size;
	DRM_DEBUG_KMS("FIFO entries required for mode: %d\n", entries);

	wm_size = fअगरo_size - entries;
	DRM_DEBUG_KMS("FIFO watermark level: %d\n", wm_size);

	/* Don't promote wm_size to अचिन्हित... */
	अगर (wm_size > wm->max_wm)
		wm_size = wm->max_wm;
	अगर (wm_size <= 0)
		wm_size = wm->शेष_wm;

	/*
	 * Bspec seems to indicate that the value shouldn't be lower than
	 * 'burst size + 1'. Certainly 830 is quite unhappy with low values.
	 * Lets go क्रम 8 which is the burst size since certain platक्रमms
	 * alपढ़ोy use a hardcoded 8 (which is what the spec says should be
	 * करोne).
	 */
	अगर (wm_size <= 8)
		wm_size = 8;

	वापस wm_size;
पूर्ण

अटल bool is_disabling(पूर्णांक old, पूर्णांक new, पूर्णांक threshold)
अणु
	वापस old >= threshold && new < threshold;
पूर्ण

अटल bool is_enabling(पूर्णांक old, पूर्णांक new, पूर्णांक threshold)
अणु
	वापस old < threshold && new >= threshold;
पूर्ण

अटल पूर्णांक पूर्णांकel_wm_num_levels(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस dev_priv->wm.max_level + 1;
पूर्ण

अटल bool पूर्णांकel_wm_plane_visible(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);

	/* FIXME check the 'enable' instead */
	अगर (!crtc_state->hw.active)
		वापस false;

	/*
	 * Treat cursor with fb as always visible since cursor updates
	 * can happen faster than the vrefresh rate, and the current
	 * watermark code करोesn't handle that correctly. Cursor updates
	 * which set/clear the fb or change the cursor size are going
	 * to get throttled by पूर्णांकel_legacy_cursor_update() to work
	 * around this problem with the watermark code.
	 */
	अगर (plane->id == PLANE_CURSOR)
		वापस plane_state->hw.fb != शून्य;
	अन्यथा
		वापस plane_state->uapi.visible;
पूर्ण

अटल bool पूर्णांकel_crtc_active(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	/* Be paranoid as we can arrive here with only partial
	 * state retrieved from the hardware during setup.
	 *
	 * We can ditch the adjusted_mode.crtc_घड़ी check as soon
	 * as Haswell has gained घड़ी पढ़ोout/fastboot support.
	 *
	 * We can ditch the crtc->primary->state->fb check as soon as we can
	 * properly reस्थिरruct framebuffers.
	 *
	 * FIXME: The पूर्णांकel_crtc->active here should be चयनed to
	 * crtc->state->active once we have proper CRTC states wired up
	 * क्रम atomic.
	 */
	वापस crtc->active && crtc->base.primary->state->fb &&
		crtc->config->hw.adjusted_mode.crtc_घड़ी;
पूर्ण

अटल काष्ठा पूर्णांकel_crtc *single_enabled_crtc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_crtc *crtc, *enabled = शून्य;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		अगर (पूर्णांकel_crtc_active(crtc)) अणु
			अगर (enabled)
				वापस शून्य;
			enabled = crtc;
		पूर्ण
	पूर्ण

	वापस enabled;
पूर्ण

अटल व्योम pnv_update_wm(काष्ठा पूर्णांकel_crtc *unused_crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(unused_crtc->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	स्थिर काष्ठा cxsr_latency *latency;
	u32 reg;
	अचिन्हित पूर्णांक wm;

	latency = पूर्णांकel_get_cxsr_latency(!IS_MOBILE(dev_priv),
					 dev_priv->is_ddr3,
					 dev_priv->fsb_freq,
					 dev_priv->mem_freq);
	अगर (!latency) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Unknown FSB/MEM found, disable CxSR\n");
		पूर्णांकel_set_memory_cxsr(dev_priv, false);
		वापस;
	पूर्ण

	crtc = single_enabled_crtc(dev_priv);
	अगर (crtc) अणु
		स्थिर काष्ठा drm_display_mode *pipe_mode =
			&crtc->config->hw.pipe_mode;
		स्थिर काष्ठा drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		पूर्णांक cpp = fb->क्रमmat->cpp[0];
		पूर्णांक घड़ी = pipe_mode->crtc_घड़ी;

		/* Display SR */
		wm = पूर्णांकel_calculate_wm(घड़ी, &pnv_display_wm,
					pnv_display_wm.fअगरo_size,
					cpp, latency->display_sr);
		reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW1);
		reg &= ~DSPFW_SR_MASK;
		reg |= FW_WM(wm, SR);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW1, reg);
		drm_dbg_kms(&dev_priv->drm, "DSPFW1 register is %x\n", reg);

		/* cursor SR */
		wm = पूर्णांकel_calculate_wm(घड़ी, &pnv_cursor_wm,
					pnv_display_wm.fअगरo_size,
					4, latency->cursor_sr);
		reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW3);
		reg &= ~DSPFW_CURSOR_SR_MASK;
		reg |= FW_WM(wm, CURSOR_SR);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3, reg);

		/* Display HPLL off SR */
		wm = पूर्णांकel_calculate_wm(घड़ी, &pnv_display_hplloff_wm,
					pnv_display_hplloff_wm.fअगरo_size,
					cpp, latency->display_hpll_disable);
		reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW3);
		reg &= ~DSPFW_HPLL_SR_MASK;
		reg |= FW_WM(wm, HPLL_SR);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3, reg);

		/* cursor HPLL off SR */
		wm = पूर्णांकel_calculate_wm(घड़ी, &pnv_cursor_hplloff_wm,
					pnv_display_hplloff_wm.fअगरo_size,
					4, latency->cursor_hpll_disable);
		reg = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW3);
		reg &= ~DSPFW_HPLL_CURSOR_MASK;
		reg |= FW_WM(wm, HPLL_CURSOR);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3, reg);
		drm_dbg_kms(&dev_priv->drm, "DSPFW3 register is %x\n", reg);

		पूर्णांकel_set_memory_cxsr(dev_priv, true);
	पूर्ण अन्यथा अणु
		पूर्णांकel_set_memory_cxsr(dev_priv, false);
	पूर्ण
पूर्ण

/*
 * Documentation says:
 * "If the line size is small, the TLB fetches can get in the way of the
 *  data fetches, causing some lag in the pixel data वापस which is not
 *  accounted क्रम in the above क्रमmulas. The following adjusपंचांगent only
 *  needs to be applied अगर eight whole lines fit in the buffer at once.
 *  The WM is adjusted upwards by the dअगरference between the FIFO size
 *  and the size of 8 whole lines. This adjusपंचांगent is always perक्रमmed
 *  in the actual pixel depth regardless of whether FBC is enabled or not."
 */
अटल अचिन्हित पूर्णांक g4x_tlb_miss_wa(पूर्णांक fअगरo_size, पूर्णांक width, पूर्णांक cpp)
अणु
	पूर्णांक tlb_miss = fअगरo_size * 64 - width * cpp * 8;

	वापस max(0, tlb_miss);
पूर्ण

अटल व्योम g4x_ग_लिखो_wm_values(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर काष्ठा g4x_wm_values *wm)
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe)
		trace_g4x_wm(पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe), wm);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW1,
		   FW_WM(wm->sr.plane, SR) |
		   FW_WM(wm->pipe[PIPE_B].plane[PLANE_CURSOR], CURSORB) |
		   FW_WM(wm->pipe[PIPE_B].plane[PLANE_PRIMARY], PLANEB) |
		   FW_WM(wm->pipe[PIPE_A].plane[PLANE_PRIMARY], PLANEA));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW2,
		   (wm->fbc_en ? DSPFW_FBC_SR_EN : 0) |
		   FW_WM(wm->sr.fbc, FBC_SR) |
		   FW_WM(wm->hpll.fbc, FBC_HPLL_SR) |
		   FW_WM(wm->pipe[PIPE_B].plane[PLANE_SPRITE0], SPRITEB) |
		   FW_WM(wm->pipe[PIPE_A].plane[PLANE_CURSOR], CURSORA) |
		   FW_WM(wm->pipe[PIPE_A].plane[PLANE_SPRITE0], SPRITEA));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3,
		   (wm->hpll_en ? DSPFW_HPLL_SR_EN : 0) |
		   FW_WM(wm->sr.cursor, CURSOR_SR) |
		   FW_WM(wm->hpll.cursor, HPLL_CURSOR) |
		   FW_WM(wm->hpll.plane, HPLL_SR));

	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, DSPFW1);
पूर्ण

#घोषणा FW_WM_VLV(value, plane) \
	(((value) << DSPFW_ ## plane ## _SHIFT) & DSPFW_ ## plane ## _MASK_VLV)

अटल व्योम vlv_ग_लिखो_wm_values(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर काष्ठा vlv_wm_values *wm)
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		trace_vlv_wm(पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe), wm);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_DDL(pipe),
			   (wm->ddl[pipe].plane[PLANE_CURSOR] << DDL_CURSOR_SHIFT) |
			   (wm->ddl[pipe].plane[PLANE_SPRITE1] << DDL_SPRITE_SHIFT(1)) |
			   (wm->ddl[pipe].plane[PLANE_SPRITE0] << DDL_SPRITE_SHIFT(0)) |
			   (wm->ddl[pipe].plane[PLANE_PRIMARY] << DDL_PLANE_SHIFT));
	पूर्ण

	/*
	 * Zero the (unused) WM1 watermarks, and also clear all the
	 * high order bits so that there are no out of bounds values
	 * present in the रेजिस्टरs during the reprogramming.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPHOWM, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPHOWM1, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW4, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW5, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW6, 0);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW1,
		   FW_WM(wm->sr.plane, SR) |
		   FW_WM(wm->pipe[PIPE_B].plane[PLANE_CURSOR], CURSORB) |
		   FW_WM_VLV(wm->pipe[PIPE_B].plane[PLANE_PRIMARY], PLANEB) |
		   FW_WM_VLV(wm->pipe[PIPE_A].plane[PLANE_PRIMARY], PLANEA));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW2,
		   FW_WM_VLV(wm->pipe[PIPE_A].plane[PLANE_SPRITE1], SPRITEB) |
		   FW_WM(wm->pipe[PIPE_A].plane[PLANE_CURSOR], CURSORA) |
		   FW_WM_VLV(wm->pipe[PIPE_A].plane[PLANE_SPRITE0], SPRITEA));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3,
		   FW_WM(wm->sr.cursor, CURSOR_SR));

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW7_CHV,
			   FW_WM_VLV(wm->pipe[PIPE_B].plane[PLANE_SPRITE1], SPRITED) |
			   FW_WM_VLV(wm->pipe[PIPE_B].plane[PLANE_SPRITE0], SPRITEC));
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW8_CHV,
			   FW_WM_VLV(wm->pipe[PIPE_C].plane[PLANE_SPRITE1], SPRITEF) |
			   FW_WM_VLV(wm->pipe[PIPE_C].plane[PLANE_SPRITE0], SPRITEE));
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW9_CHV,
			   FW_WM_VLV(wm->pipe[PIPE_C].plane[PLANE_PRIMARY], PLANEC) |
			   FW_WM(wm->pipe[PIPE_C].plane[PLANE_CURSOR], CURSORC));
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPHOWM,
			   FW_WM(wm->sr.plane >> 9, SR_HI) |
			   FW_WM(wm->pipe[PIPE_C].plane[PLANE_SPRITE1] >> 8, SPRITEF_HI) |
			   FW_WM(wm->pipe[PIPE_C].plane[PLANE_SPRITE0] >> 8, SPRITEE_HI) |
			   FW_WM(wm->pipe[PIPE_C].plane[PLANE_PRIMARY] >> 8, PLANEC_HI) |
			   FW_WM(wm->pipe[PIPE_B].plane[PLANE_SPRITE1] >> 8, SPRITED_HI) |
			   FW_WM(wm->pipe[PIPE_B].plane[PLANE_SPRITE0] >> 8, SPRITEC_HI) |
			   FW_WM(wm->pipe[PIPE_B].plane[PLANE_PRIMARY] >> 8, PLANEB_HI) |
			   FW_WM(wm->pipe[PIPE_A].plane[PLANE_SPRITE1] >> 8, SPRITEB_HI) |
			   FW_WM(wm->pipe[PIPE_A].plane[PLANE_SPRITE0] >> 8, SPRITEA_HI) |
			   FW_WM(wm->pipe[PIPE_A].plane[PLANE_PRIMARY] >> 8, PLANEA_HI));
	पूर्ण अन्यथा अणु
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW7,
			   FW_WM_VLV(wm->pipe[PIPE_B].plane[PLANE_SPRITE1], SPRITED) |
			   FW_WM_VLV(wm->pipe[PIPE_B].plane[PLANE_SPRITE0], SPRITEC));
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPHOWM,
			   FW_WM(wm->sr.plane >> 9, SR_HI) |
			   FW_WM(wm->pipe[PIPE_B].plane[PLANE_SPRITE1] >> 8, SPRITED_HI) |
			   FW_WM(wm->pipe[PIPE_B].plane[PLANE_SPRITE0] >> 8, SPRITEC_HI) |
			   FW_WM(wm->pipe[PIPE_B].plane[PLANE_PRIMARY] >> 8, PLANEB_HI) |
			   FW_WM(wm->pipe[PIPE_A].plane[PLANE_SPRITE1] >> 8, SPRITEB_HI) |
			   FW_WM(wm->pipe[PIPE_A].plane[PLANE_SPRITE0] >> 8, SPRITEA_HI) |
			   FW_WM(wm->pipe[PIPE_A].plane[PLANE_PRIMARY] >> 8, PLANEA_HI));
	पूर्ण

	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, DSPFW1);
पूर्ण

#अघोषित FW_WM_VLV

अटल व्योम g4x_setup_wm_latency(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* all latencies in usec */
	dev_priv->wm.pri_latency[G4X_WM_LEVEL_NORMAL] = 5;
	dev_priv->wm.pri_latency[G4X_WM_LEVEL_SR] = 12;
	dev_priv->wm.pri_latency[G4X_WM_LEVEL_HPLL] = 35;

	dev_priv->wm.max_level = G4X_WM_LEVEL_HPLL;
पूर्ण

अटल पूर्णांक g4x_plane_fअगरo_size(क्रमागत plane_id plane_id, पूर्णांक level)
अणु
	/*
	 * DSPCNTR[13] supposedly controls whether the
	 * primary plane can use the FIFO space otherwise
	 * reserved क्रम the sprite plane. It's not 100% clear
	 * what the actual FIFO size is, but it looks like we
	 * can happily set both primary and sprite watermarks
	 * up to 127 cachelines. So that would seem to mean
	 * that either DSPCNTR[13] करोesn't करो anything, or that
	 * the total FIFO is >= 256 cachelines in size. Either
	 * way, we करोn't seem to have to worry about this
	 * repartitioning as the maximum watermark value the
	 * रेजिस्टर can hold क्रम each plane is lower than the
	 * minimum FIFO size.
	 */
	चयन (plane_id) अणु
	हाल PLANE_CURSOR:
		वापस 63;
	हाल PLANE_PRIMARY:
		वापस level == G4X_WM_LEVEL_NORMAL ? 127 : 511;
	हाल PLANE_SPRITE0:
		वापस level == G4X_WM_LEVEL_NORMAL ? 127 : 0;
	शेष:
		MISSING_CASE(plane_id);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक g4x_fbc_fअगरo_size(पूर्णांक level)
अणु
	चयन (level) अणु
	हाल G4X_WM_LEVEL_SR:
		वापस 7;
	हाल G4X_WM_LEVEL_HPLL:
		वापस 15;
	शेष:
		MISSING_CASE(level);
		वापस 0;
	पूर्ण
पूर्ण

अटल u16 g4x_compute_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			  पूर्णांक level)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_display_mode *pipe_mode =
		&crtc_state->hw.pipe_mode;
	अचिन्हित पूर्णांक latency = dev_priv->wm.pri_latency[level] * 10;
	अचिन्हित पूर्णांक घड़ी, htotal, cpp, width, wm;

	अगर (latency == 0)
		वापस अच_लघु_उच्च;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	cpp = plane_state->hw.fb->क्रमmat->cpp[0];

	/*
	 * Not 100% sure which way ELK should go here as the
	 * spec only says CL/CTG should assume 32bpp and BW
	 * करोesn't need to. But as these things followed the
	 * mobile vs. desktop lines on gen3 as well, let's
	 * assume ELK करोesn't need this.
	 *
	 * The spec also fails to list such a restriction क्रम
	 * the HPLL watermark, which seems a little strange.
	 * Let's use 32bpp क्रम the HPLL watermark as well.
	 */
	अगर (IS_GM45(dev_priv) && plane->id == PLANE_PRIMARY &&
	    level != G4X_WM_LEVEL_NORMAL)
		cpp = max(cpp, 4u);

	घड़ी = pipe_mode->crtc_घड़ी;
	htotal = pipe_mode->crtc_htotal;

	width = drm_rect_width(&plane_state->uapi.dst);

	अगर (plane->id == PLANE_CURSOR) अणु
		wm = पूर्णांकel_wm_method2(घड़ी, htotal, width, cpp, latency);
	पूर्ण अन्यथा अगर (plane->id == PLANE_PRIMARY &&
		   level == G4X_WM_LEVEL_NORMAL) अणु
		wm = पूर्णांकel_wm_method1(घड़ी, cpp, latency);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक small, large;

		small = पूर्णांकel_wm_method1(घड़ी, cpp, latency);
		large = पूर्णांकel_wm_method2(घड़ी, htotal, width, cpp, latency);

		wm = min(small, large);
	पूर्ण

	wm += g4x_tlb_miss_wa(g4x_plane_fअगरo_size(plane->id, level),
			      width, cpp);

	wm = DIV_ROUND_UP(wm, 64) + 2;

	वापस min_t(अचिन्हित पूर्णांक, wm, अच_लघु_उच्च);
पूर्ण

अटल bool g4x_raw_plane_wm_set(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 पूर्णांक level, क्रमागत plane_id plane_id, u16 value)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	bool dirty = false;

	क्रम (; level < पूर्णांकel_wm_num_levels(dev_priv); level++) अणु
		काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.g4x.raw[level];

		dirty |= raw->plane[plane_id] != value;
		raw->plane[plane_id] = value;
	पूर्ण

	वापस dirty;
पूर्ण

अटल bool g4x_raw_fbc_wm_set(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक level, u16 value)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	bool dirty = false;

	/* NORMAL level करोesn't have an FBC watermark */
	level = max(level, G4X_WM_LEVEL_SR);

	क्रम (; level < पूर्णांकel_wm_num_levels(dev_priv); level++) अणु
		काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.g4x.raw[level];

		dirty |= raw->fbc != value;
		raw->fbc = value;
	पूर्ण

	वापस dirty;
पूर्ण

अटल u32 ilk_compute_fbc_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			      u32 pri_val);

अटल bool g4x_raw_plane_wm_compute(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक num_levels = पूर्णांकel_wm_num_levels(to_i915(plane->base.dev));
	क्रमागत plane_id plane_id = plane->id;
	bool dirty = false;
	पूर्णांक level;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state)) अणु
		dirty |= g4x_raw_plane_wm_set(crtc_state, 0, plane_id, 0);
		अगर (plane_id == PLANE_PRIMARY)
			dirty |= g4x_raw_fbc_wm_set(crtc_state, 0, 0);
		जाओ out;
	पूर्ण

	क्रम (level = 0; level < num_levels; level++) अणु
		काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.g4x.raw[level];
		पूर्णांक wm, max_wm;

		wm = g4x_compute_wm(crtc_state, plane_state, level);
		max_wm = g4x_plane_fअगरo_size(plane_id, level);

		अगर (wm > max_wm)
			अवरोध;

		dirty |= raw->plane[plane_id] != wm;
		raw->plane[plane_id] = wm;

		अगर (plane_id != PLANE_PRIMARY ||
		    level == G4X_WM_LEVEL_NORMAL)
			जारी;

		wm = ilk_compute_fbc_wm(crtc_state, plane_state,
					raw->plane[plane_id]);
		max_wm = g4x_fbc_fअगरo_size(level);

		/*
		 * FBC wm is not mandatory as we
		 * can always just disable its use.
		 */
		अगर (wm > max_wm)
			wm = अच_लघु_उच्च;

		dirty |= raw->fbc != wm;
		raw->fbc = wm;
	पूर्ण

	/* mark watermarks as invalid */
	dirty |= g4x_raw_plane_wm_set(crtc_state, level, plane_id, अच_लघु_उच्च);

	अगर (plane_id == PLANE_PRIMARY)
		dirty |= g4x_raw_fbc_wm_set(crtc_state, level, अच_लघु_उच्च);

 out:
	अगर (dirty) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "%s watermarks: normal=%d, SR=%d, HPLL=%d\n",
			    plane->base.name,
			    crtc_state->wm.g4x.raw[G4X_WM_LEVEL_NORMAL].plane[plane_id],
			    crtc_state->wm.g4x.raw[G4X_WM_LEVEL_SR].plane[plane_id],
			    crtc_state->wm.g4x.raw[G4X_WM_LEVEL_HPLL].plane[plane_id]);

		अगर (plane_id == PLANE_PRIMARY)
			drm_dbg_kms(&dev_priv->drm,
				    "FBC watermarks: SR=%d, HPLL=%d\n",
				    crtc_state->wm.g4x.raw[G4X_WM_LEVEL_SR].fbc,
				    crtc_state->wm.g4x.raw[G4X_WM_LEVEL_HPLL].fbc);
	पूर्ण

	वापस dirty;
पूर्ण

अटल bool g4x_raw_plane_wm_is_valid(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      क्रमागत plane_id plane_id, पूर्णांक level)
अणु
	स्थिर काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.g4x.raw[level];

	वापस raw->plane[plane_id] <= g4x_plane_fअगरo_size(plane_id, level);
पूर्ण

अटल bool g4x_raw_crtc_wm_is_valid(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (level > dev_priv->wm.max_level)
		वापस false;

	वापस g4x_raw_plane_wm_is_valid(crtc_state, PLANE_PRIMARY, level) &&
		g4x_raw_plane_wm_is_valid(crtc_state, PLANE_SPRITE0, level) &&
		g4x_raw_plane_wm_is_valid(crtc_state, PLANE_CURSOR, level);
पूर्ण

/* mark all levels starting from 'level' as invalid */
अटल व्योम g4x_invalidate_wms(काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा g4x_wm_state *wm_state, पूर्णांक level)
अणु
	अगर (level <= G4X_WM_LEVEL_NORMAL) अणु
		क्रमागत plane_id plane_id;

		क्रम_each_plane_id_on_crtc(crtc, plane_id)
			wm_state->wm.plane[plane_id] = अच_लघु_उच्च;
	पूर्ण

	अगर (level <= G4X_WM_LEVEL_SR) अणु
		wm_state->cxsr = false;
		wm_state->sr.cursor = अच_लघु_उच्च;
		wm_state->sr.plane = अच_लघु_उच्च;
		wm_state->sr.fbc = अच_लघु_उच्च;
	पूर्ण

	अगर (level <= G4X_WM_LEVEL_HPLL) अणु
		wm_state->hpll_en = false;
		wm_state->hpll.cursor = अच_लघु_उच्च;
		wm_state->hpll.plane = अच_लघु_उच्च;
		wm_state->hpll.fbc = अच_लघु_उच्च;
	पूर्ण
पूर्ण

अटल bool g4x_compute_fbc_en(स्थिर काष्ठा g4x_wm_state *wm_state,
			       पूर्णांक level)
अणु
	अगर (level < G4X_WM_LEVEL_SR)
		वापस false;

	अगर (level >= G4X_WM_LEVEL_SR &&
	    wm_state->sr.fbc > g4x_fbc_fअगरo_size(G4X_WM_LEVEL_SR))
		वापस false;

	अगर (level >= G4X_WM_LEVEL_HPLL &&
	    wm_state->hpll.fbc > g4x_fbc_fअगरo_size(G4X_WM_LEVEL_HPLL))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक g4x_compute_pipe_wm(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(crtc_state->uapi.state);
	काष्ठा g4x_wm_state *wm_state = &crtc_state->wm.g4x.optimal;
	पूर्णांक num_active_planes = hweight8(crtc_state->active_planes &
					 ~BIT(PLANE_CURSOR));
	स्थिर काष्ठा g4x_pipe_wm *raw;
	स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state;
	स्थिर काष्ठा पूर्णांकel_plane_state *new_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	क्रमागत plane_id plane_id;
	पूर्णांक i, level;
	अचिन्हित पूर्णांक dirty = 0;

	क्रम_each_oldnew_पूर्णांकel_plane_in_state(state, plane,
					     old_plane_state,
					     new_plane_state, i) अणु
		अगर (new_plane_state->hw.crtc != &crtc->base &&
		    old_plane_state->hw.crtc != &crtc->base)
			जारी;

		अगर (g4x_raw_plane_wm_compute(crtc_state, new_plane_state))
			dirty |= BIT(plane->id);
	पूर्ण

	अगर (!dirty)
		वापस 0;

	level = G4X_WM_LEVEL_NORMAL;
	अगर (!g4x_raw_crtc_wm_is_valid(crtc_state, level))
		जाओ out;

	raw = &crtc_state->wm.g4x.raw[level];
	क्रम_each_plane_id_on_crtc(crtc, plane_id)
		wm_state->wm.plane[plane_id] = raw->plane[plane_id];

	level = G4X_WM_LEVEL_SR;
	अगर (!g4x_raw_crtc_wm_is_valid(crtc_state, level))
		जाओ out;

	raw = &crtc_state->wm.g4x.raw[level];
	wm_state->sr.plane = raw->plane[PLANE_PRIMARY];
	wm_state->sr.cursor = raw->plane[PLANE_CURSOR];
	wm_state->sr.fbc = raw->fbc;

	wm_state->cxsr = num_active_planes == BIT(PLANE_PRIMARY);

	level = G4X_WM_LEVEL_HPLL;
	अगर (!g4x_raw_crtc_wm_is_valid(crtc_state, level))
		जाओ out;

	raw = &crtc_state->wm.g4x.raw[level];
	wm_state->hpll.plane = raw->plane[PLANE_PRIMARY];
	wm_state->hpll.cursor = raw->plane[PLANE_CURSOR];
	wm_state->hpll.fbc = raw->fbc;

	wm_state->hpll_en = wm_state->cxsr;

	level++;

 out:
	अगर (level == G4X_WM_LEVEL_NORMAL)
		वापस -EINVAL;

	/* invalidate the higher levels */
	g4x_invalidate_wms(crtc, wm_state, level);

	/*
	 * Determine अगर the FBC watermark(s) can be used. IF
	 * this isn't the हाल we prefer to disable the FBC
	 * watermark(s) rather than disable the SR/HPLL
	 * level(s) entirely. 'level-1' is the highest valid
	 * level here.
	 */
	wm_state->fbc_en = g4x_compute_fbc_en(wm_state, level - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक g4x_compute_पूर्णांकermediate_wm(काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा g4x_wm_state *पूर्णांकermediate = &new_crtc_state->wm.g4x.पूर्णांकermediate;
	स्थिर काष्ठा g4x_wm_state *optimal = &new_crtc_state->wm.g4x.optimal;
	काष्ठा पूर्णांकel_atomic_state *पूर्णांकel_state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(पूर्णांकel_state, crtc);
	स्थिर काष्ठा g4x_wm_state *active = &old_crtc_state->wm.g4x.optimal;
	क्रमागत plane_id plane_id;

	अगर (!new_crtc_state->hw.active || drm_atomic_crtc_needs_modeset(&new_crtc_state->uapi)) अणु
		*पूर्णांकermediate = *optimal;

		पूर्णांकermediate->cxsr = false;
		पूर्णांकermediate->hpll_en = false;
		जाओ out;
	पूर्ण

	पूर्णांकermediate->cxsr = optimal->cxsr && active->cxsr &&
		!new_crtc_state->disable_cxsr;
	पूर्णांकermediate->hpll_en = optimal->hpll_en && active->hpll_en &&
		!new_crtc_state->disable_cxsr;
	पूर्णांकermediate->fbc_en = optimal->fbc_en && active->fbc_en;

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		पूर्णांकermediate->wm.plane[plane_id] =
			max(optimal->wm.plane[plane_id],
			    active->wm.plane[plane_id]);

		drm_WARN_ON(&dev_priv->drm, पूर्णांकermediate->wm.plane[plane_id] >
			    g4x_plane_fअगरo_size(plane_id, G4X_WM_LEVEL_NORMAL));
	पूर्ण

	पूर्णांकermediate->sr.plane = max(optimal->sr.plane,
				     active->sr.plane);
	पूर्णांकermediate->sr.cursor = max(optimal->sr.cursor,
				      active->sr.cursor);
	पूर्णांकermediate->sr.fbc = max(optimal->sr.fbc,
				   active->sr.fbc);

	पूर्णांकermediate->hpll.plane = max(optimal->hpll.plane,
				       active->hpll.plane);
	पूर्णांकermediate->hpll.cursor = max(optimal->hpll.cursor,
					active->hpll.cursor);
	पूर्णांकermediate->hpll.fbc = max(optimal->hpll.fbc,
				     active->hpll.fbc);

	drm_WARN_ON(&dev_priv->drm,
		    (पूर्णांकermediate->sr.plane >
		     g4x_plane_fअगरo_size(PLANE_PRIMARY, G4X_WM_LEVEL_SR) ||
		     पूर्णांकermediate->sr.cursor >
		     g4x_plane_fअगरo_size(PLANE_CURSOR, G4X_WM_LEVEL_SR)) &&
		    पूर्णांकermediate->cxsr);
	drm_WARN_ON(&dev_priv->drm,
		    (पूर्णांकermediate->sr.plane >
		     g4x_plane_fअगरo_size(PLANE_PRIMARY, G4X_WM_LEVEL_HPLL) ||
		     पूर्णांकermediate->sr.cursor >
		     g4x_plane_fअगरo_size(PLANE_CURSOR, G4X_WM_LEVEL_HPLL)) &&
		    पूर्णांकermediate->hpll_en);

	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकermediate->sr.fbc > g4x_fbc_fअगरo_size(1) &&
		    पूर्णांकermediate->fbc_en && पूर्णांकermediate->cxsr);
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकermediate->hpll.fbc > g4x_fbc_fअगरo_size(2) &&
		    पूर्णांकermediate->fbc_en && पूर्णांकermediate->hpll_en);

out:
	/*
	 * If our पूर्णांकermediate WM are identical to the final WM, then we can
	 * omit the post-vblank programming; only update अगर it's dअगरferent.
	 */
	अगर (स_भेद(पूर्णांकermediate, optimal, माप(*पूर्णांकermediate)) != 0)
		new_crtc_state->wm.need_postvbl_update = true;

	वापस 0;
पूर्ण

अटल व्योम g4x_merge_wm(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा g4x_wm_values *wm)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक num_active_pipes = 0;

	wm->cxsr = true;
	wm->hpll_en = true;
	wm->fbc_en = true;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		स्थिर काष्ठा g4x_wm_state *wm_state = &crtc->wm.active.g4x;

		अगर (!crtc->active)
			जारी;

		अगर (!wm_state->cxsr)
			wm->cxsr = false;
		अगर (!wm_state->hpll_en)
			wm->hpll_en = false;
		अगर (!wm_state->fbc_en)
			wm->fbc_en = false;

		num_active_pipes++;
	पूर्ण

	अगर (num_active_pipes != 1) अणु
		wm->cxsr = false;
		wm->hpll_en = false;
		wm->fbc_en = false;
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		स्थिर काष्ठा g4x_wm_state *wm_state = &crtc->wm.active.g4x;
		क्रमागत pipe pipe = crtc->pipe;

		wm->pipe[pipe] = wm_state->wm;
		अगर (crtc->active && wm->cxsr)
			wm->sr = wm_state->sr;
		अगर (crtc->active && wm->hpll_en)
			wm->hpll = wm_state->hpll;
	पूर्ण
पूर्ण

अटल व्योम g4x_program_watermarks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा g4x_wm_values *old_wm = &dev_priv->wm.g4x;
	काष्ठा g4x_wm_values new_wm = अणुपूर्ण;

	g4x_merge_wm(dev_priv, &new_wm);

	अगर (स_भेद(old_wm, &new_wm, माप(new_wm)) == 0)
		वापस;

	अगर (is_disabling(old_wm->cxsr, new_wm.cxsr, true))
		_पूर्णांकel_set_memory_cxsr(dev_priv, false);

	g4x_ग_लिखो_wm_values(dev_priv, &new_wm);

	अगर (is_enabling(old_wm->cxsr, new_wm.cxsr, true))
		_पूर्णांकel_set_memory_cxsr(dev_priv, true);

	*old_wm = new_wm;
पूर्ण

अटल व्योम g4x_initial_watermarks(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.g4x = crtc_state->wm.g4x.पूर्णांकermediate;
	g4x_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

अटल व्योम g4x_optimize_watermarks(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	अगर (!crtc_state->wm.need_postvbl_update)
		वापस;

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.g4x = crtc_state->wm.g4x.optimal;
	g4x_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

/* latency must be in 0.1us units. */
अटल अचिन्हित पूर्णांक vlv_wm_method2(अचिन्हित पूर्णांक pixel_rate,
				   अचिन्हित पूर्णांक htotal,
				   अचिन्हित पूर्णांक width,
				   अचिन्हित पूर्णांक cpp,
				   अचिन्हित पूर्णांक latency)
अणु
	अचिन्हित पूर्णांक ret;

	ret = पूर्णांकel_wm_method2(pixel_rate, htotal,
			       width, cpp, latency);
	ret = DIV_ROUND_UP(ret, 64);

	वापस ret;
पूर्ण

अटल व्योम vlv_setup_wm_latency(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* all latencies in usec */
	dev_priv->wm.pri_latency[VLV_WM_LEVEL_PM2] = 3;

	dev_priv->wm.max_level = VLV_WM_LEVEL_PM2;

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		dev_priv->wm.pri_latency[VLV_WM_LEVEL_PM5] = 12;
		dev_priv->wm.pri_latency[VLV_WM_LEVEL_DDR_DVFS] = 33;

		dev_priv->wm.max_level = VLV_WM_LEVEL_DDR_DVFS;
	पूर्ण
पूर्ण

अटल u16 vlv_compute_wm_level(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				पूर्णांक level)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_display_mode *pipe_mode =
		&crtc_state->hw.pipe_mode;
	अचिन्हित पूर्णांक घड़ी, htotal, cpp, width, wm;

	अगर (dev_priv->wm.pri_latency[level] == 0)
		वापस अच_लघु_उच्च;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	cpp = plane_state->hw.fb->क्रमmat->cpp[0];
	घड़ी = pipe_mode->crtc_घड़ी;
	htotal = pipe_mode->crtc_htotal;
	width = crtc_state->pipe_src_w;

	अगर (plane->id == PLANE_CURSOR) अणु
		/*
		 * FIXME the क्रमmula gives values that are
		 * too big क्रम the cursor FIFO, and hence we
		 * would never be able to use cursors. For
		 * now just hardcode the watermark.
		 */
		wm = 63;
	पूर्ण अन्यथा अणु
		wm = vlv_wm_method2(घड़ी, htotal, width, cpp,
				    dev_priv->wm.pri_latency[level] * 10);
	पूर्ण

	वापस min_t(अचिन्हित पूर्णांक, wm, अच_लघु_उच्च);
पूर्ण

अटल bool vlv_need_sprite0_fअगरo_workaround(अचिन्हित पूर्णांक active_planes)
अणु
	वापस (active_planes & (BIT(PLANE_SPRITE0) |
				 BIT(PLANE_SPRITE1))) == BIT(PLANE_SPRITE1);
पूर्ण

अटल पूर्णांक vlv_compute_fअगरo(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा g4x_pipe_wm *raw =
		&crtc_state->wm.vlv.raw[VLV_WM_LEVEL_PM2];
	काष्ठा vlv_fअगरo_state *fअगरo_state = &crtc_state->wm.vlv.fअगरo_state;
	अचिन्हित पूर्णांक active_planes = crtc_state->active_planes & ~BIT(PLANE_CURSOR);
	पूर्णांक num_active_planes = hweight8(active_planes);
	स्थिर पूर्णांक fअगरo_size = 511;
	पूर्णांक fअगरo_extra, fअगरo_left = fअगरo_size;
	पूर्णांक sprite0_fअगरo_extra = 0;
	अचिन्हित पूर्णांक total_rate;
	क्रमागत plane_id plane_id;

	/*
	 * When enabling sprite0 after sprite1 has alपढ़ोy been enabled
	 * we tend to get an underrun unless sprite0 alपढ़ोy has some
	 * FIFO space allcoated. Hence we always allocate at least one
	 * cacheline क्रम sprite0 whenever sprite1 is enabled.
	 *
	 * All other plane enable sequences appear immune to this problem.
	 */
	अगर (vlv_need_sprite0_fअगरo_workaround(active_planes))
		sprite0_fअगरo_extra = 1;

	total_rate = raw->plane[PLANE_PRIMARY] +
		raw->plane[PLANE_SPRITE0] +
		raw->plane[PLANE_SPRITE1] +
		sprite0_fअगरo_extra;

	अगर (total_rate > fअगरo_size)
		वापस -EINVAL;

	अगर (total_rate == 0)
		total_rate = 1;

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		अचिन्हित पूर्णांक rate;

		अगर ((active_planes & BIT(plane_id)) == 0) अणु
			fअगरo_state->plane[plane_id] = 0;
			जारी;
		पूर्ण

		rate = raw->plane[plane_id];
		fअगरo_state->plane[plane_id] = fअगरo_size * rate / total_rate;
		fअगरo_left -= fअगरo_state->plane[plane_id];
	पूर्ण

	fअगरo_state->plane[PLANE_SPRITE0] += sprite0_fअगरo_extra;
	fअगरo_left -= sprite0_fअगरo_extra;

	fअगरo_state->plane[PLANE_CURSOR] = 63;

	fअगरo_extra = DIV_ROUND_UP(fअगरo_left, num_active_planes ?: 1);

	/* spपढ़ो the reमुख्यder evenly */
	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		पूर्णांक plane_extra;

		अगर (fअगरo_left == 0)
			अवरोध;

		अगर ((active_planes & BIT(plane_id)) == 0)
			जारी;

		plane_extra = min(fअगरo_extra, fअगरo_left);
		fअगरo_state->plane[plane_id] += plane_extra;
		fअगरo_left -= plane_extra;
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, active_planes != 0 && fअगरo_left != 0);

	/* give it all to the first plane अगर none are active */
	अगर (active_planes == 0) अणु
		drm_WARN_ON(&dev_priv->drm, fअगरo_left != fअगरo_size);
		fअगरo_state->plane[PLANE_PRIMARY] = fअगरo_left;
	पूर्ण

	वापस 0;
पूर्ण

/* mark all levels starting from 'level' as invalid */
अटल व्योम vlv_invalidate_wms(काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा vlv_wm_state *wm_state, पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	क्रम (; level < पूर्णांकel_wm_num_levels(dev_priv); level++) अणु
		क्रमागत plane_id plane_id;

		क्रम_each_plane_id_on_crtc(crtc, plane_id)
			wm_state->wm[level].plane[plane_id] = अच_लघु_उच्च;

		wm_state->sr[level].cursor = अच_लघु_उच्च;
		wm_state->sr[level].plane = अच_लघु_उच्च;
	पूर्ण
पूर्ण

अटल u16 vlv_invert_wm_value(u16 wm, u16 fअगरo_size)
अणु
	अगर (wm > fअगरo_size)
		वापस अच_लघु_उच्च;
	अन्यथा
		वापस fअगरo_size - wm;
पूर्ण

/*
 * Starting from 'level' set all higher
 * levels to 'value' in the "raw" watermarks.
 */
अटल bool vlv_raw_plane_wm_set(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 पूर्णांक level, क्रमागत plane_id plane_id, u16 value)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक num_levels = पूर्णांकel_wm_num_levels(dev_priv);
	bool dirty = false;

	क्रम (; level < num_levels; level++) अणु
		काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.vlv.raw[level];

		dirty |= raw->plane[plane_id] != value;
		raw->plane[plane_id] = value;
	पूर्ण

	वापस dirty;
पूर्ण

अटल bool vlv_raw_plane_wm_compute(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	क्रमागत plane_id plane_id = plane->id;
	पूर्णांक num_levels = पूर्णांकel_wm_num_levels(to_i915(plane->base.dev));
	पूर्णांक level;
	bool dirty = false;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state)) अणु
		dirty |= vlv_raw_plane_wm_set(crtc_state, 0, plane_id, 0);
		जाओ out;
	पूर्ण

	क्रम (level = 0; level < num_levels; level++) अणु
		काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.vlv.raw[level];
		पूर्णांक wm = vlv_compute_wm_level(crtc_state, plane_state, level);
		पूर्णांक max_wm = plane_id == PLANE_CURSOR ? 63 : 511;

		अगर (wm > max_wm)
			अवरोध;

		dirty |= raw->plane[plane_id] != wm;
		raw->plane[plane_id] = wm;
	पूर्ण

	/* mark all higher levels as invalid */
	dirty |= vlv_raw_plane_wm_set(crtc_state, level, plane_id, अच_लघु_उच्च);

out:
	अगर (dirty)
		drm_dbg_kms(&dev_priv->drm,
			    "%s watermarks: PM2=%d, PM5=%d, DDR DVFS=%d\n",
			    plane->base.name,
			    crtc_state->wm.vlv.raw[VLV_WM_LEVEL_PM2].plane[plane_id],
			    crtc_state->wm.vlv.raw[VLV_WM_LEVEL_PM5].plane[plane_id],
			    crtc_state->wm.vlv.raw[VLV_WM_LEVEL_DDR_DVFS].plane[plane_id]);

	वापस dirty;
पूर्ण

अटल bool vlv_raw_plane_wm_is_valid(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      क्रमागत plane_id plane_id, पूर्णांक level)
अणु
	स्थिर काष्ठा g4x_pipe_wm *raw =
		&crtc_state->wm.vlv.raw[level];
	स्थिर काष्ठा vlv_fअगरo_state *fअगरo_state =
		&crtc_state->wm.vlv.fअगरo_state;

	वापस raw->plane[plane_id] <= fअगरo_state->plane[plane_id];
पूर्ण

अटल bool vlv_raw_crtc_wm_is_valid(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state, पूर्णांक level)
अणु
	वापस vlv_raw_plane_wm_is_valid(crtc_state, PLANE_PRIMARY, level) &&
		vlv_raw_plane_wm_is_valid(crtc_state, PLANE_SPRITE0, level) &&
		vlv_raw_plane_wm_is_valid(crtc_state, PLANE_SPRITE1, level) &&
		vlv_raw_plane_wm_is_valid(crtc_state, PLANE_CURSOR, level);
पूर्ण

अटल पूर्णांक vlv_compute_pipe_wm(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(crtc_state->uapi.state);
	काष्ठा vlv_wm_state *wm_state = &crtc_state->wm.vlv.optimal;
	स्थिर काष्ठा vlv_fअगरo_state *fअगरo_state =
		&crtc_state->wm.vlv.fअगरo_state;
	पूर्णांक num_active_planes = hweight8(crtc_state->active_planes &
					 ~BIT(PLANE_CURSOR));
	bool needs_modeset = drm_atomic_crtc_needs_modeset(&crtc_state->uapi);
	स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state;
	स्थिर काष्ठा पूर्णांकel_plane_state *new_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	क्रमागत plane_id plane_id;
	पूर्णांक level, ret, i;
	अचिन्हित पूर्णांक dirty = 0;

	क्रम_each_oldnew_पूर्णांकel_plane_in_state(state, plane,
					     old_plane_state,
					     new_plane_state, i) अणु
		अगर (new_plane_state->hw.crtc != &crtc->base &&
		    old_plane_state->hw.crtc != &crtc->base)
			जारी;

		अगर (vlv_raw_plane_wm_compute(crtc_state, new_plane_state))
			dirty |= BIT(plane->id);
	पूर्ण

	/*
	 * DSPARB रेजिस्टरs may have been reset due to the
	 * घातer well being turned off. Make sure we restore
	 * them to a consistent state even अगर no primary/sprite
	 * planes are initially active.
	 */
	अगर (needs_modeset)
		crtc_state->fअगरo_changed = true;

	अगर (!dirty)
		वापस 0;

	/* cursor changes करोn't warrant a FIFO recompute */
	अगर (dirty & ~BIT(PLANE_CURSOR)) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
			पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
		स्थिर काष्ठा vlv_fअगरo_state *old_fअगरo_state =
			&old_crtc_state->wm.vlv.fअगरo_state;

		ret = vlv_compute_fअगरo(crtc_state);
		अगर (ret)
			वापस ret;

		अगर (needs_modeset ||
		    स_भेद(old_fअगरo_state, fअगरo_state,
			   माप(*fअगरo_state)) != 0)
			crtc_state->fअगरo_changed = true;
	पूर्ण

	/* initially allow all levels */
	wm_state->num_levels = पूर्णांकel_wm_num_levels(dev_priv);
	/*
	 * Note that enabling cxsr with no primary/sprite planes
	 * enabled can wedge the pipe. Hence we only allow cxsr
	 * with exactly one enabled primary/sprite plane.
	 */
	wm_state->cxsr = crtc->pipe != PIPE_C && num_active_planes == 1;

	क्रम (level = 0; level < wm_state->num_levels; level++) अणु
		स्थिर काष्ठा g4x_pipe_wm *raw = &crtc_state->wm.vlv.raw[level];
		स्थिर पूर्णांक sr_fअगरo_size = INTEL_NUM_PIPES(dev_priv) * 512 - 1;

		अगर (!vlv_raw_crtc_wm_is_valid(crtc_state, level))
			अवरोध;

		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			wm_state->wm[level].plane[plane_id] =
				vlv_invert_wm_value(raw->plane[plane_id],
						    fअगरo_state->plane[plane_id]);
		पूर्ण

		wm_state->sr[level].plane =
			vlv_invert_wm_value(max3(raw->plane[PLANE_PRIMARY],
						 raw->plane[PLANE_SPRITE0],
						 raw->plane[PLANE_SPRITE1]),
					    sr_fअगरo_size);

		wm_state->sr[level].cursor =
			vlv_invert_wm_value(raw->plane[PLANE_CURSOR],
					    63);
	पूर्ण

	अगर (level == 0)
		वापस -EINVAL;

	/* limit to only levels we can actually handle */
	wm_state->num_levels = level;

	/* invalidate the higher levels */
	vlv_invalidate_wms(crtc, wm_state, level);

	वापस 0;
पूर्ण

#घोषणा VLV_FIFO(plane, value) \
	(((value) << DSPARB_ ## plane ## _SHIFT_VLV) & DSPARB_ ## plane ## _MASK_VLV)

अटल व्योम vlv_atomic_update_fअगरo(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा vlv_fअगरo_state *fअगरo_state =
		&crtc_state->wm.vlv.fअगरo_state;
	पूर्णांक sprite0_start, sprite1_start, fअगरo_size;
	u32 dsparb, dsparb2, dsparb3;

	अगर (!crtc_state->fअगरo_changed)
		वापस;

	sprite0_start = fअगरo_state->plane[PLANE_PRIMARY];
	sprite1_start = fअगरo_state->plane[PLANE_SPRITE0] + sprite0_start;
	fअगरo_size = fअगरo_state->plane[PLANE_SPRITE1] + sprite1_start;

	drm_WARN_ON(&dev_priv->drm, fअगरo_state->plane[PLANE_CURSOR] != 63);
	drm_WARN_ON(&dev_priv->drm, fअगरo_size != 511);

	trace_vlv_fअगरo_size(crtc, sprite0_start, sprite1_start, fअगरo_size);

	/*
	 * uncore.lock serves a द्विगुन purpose here. It allows us to
	 * use the less expensive I915_अणुREAD,WRITEपूर्ण_FW() functions, and
	 * it protects the DSPARB रेजिस्टरs from getting clobbered by
	 * parallel updates from multiple pipes.
	 *
	 * पूर्णांकel_pipe_update_start() has alपढ़ोy disabled पूर्णांकerrupts
	 * क्रम us, so a plain spin_lock() is sufficient here.
	 */
	spin_lock(&uncore->lock);

	चयन (crtc->pipe) अणु
	हाल PIPE_A:
		dsparb = पूर्णांकel_uncore_पढ़ो_fw(uncore, DSPARB);
		dsparb2 = पूर्णांकel_uncore_पढ़ो_fw(uncore, DSPARB2);

		dsparb &= ~(VLV_FIFO(SPRITEA, 0xff) |
			    VLV_FIFO(SPRITEB, 0xff));
		dsparb |= (VLV_FIFO(SPRITEA, sprite0_start) |
			   VLV_FIFO(SPRITEB, sprite1_start));

		dsparb2 &= ~(VLV_FIFO(SPRITEA_HI, 0x1) |
			     VLV_FIFO(SPRITEB_HI, 0x1));
		dsparb2 |= (VLV_FIFO(SPRITEA_HI, sprite0_start >> 8) |
			   VLV_FIFO(SPRITEB_HI, sprite1_start >> 8));

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, DSPARB, dsparb);
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, DSPARB2, dsparb2);
		अवरोध;
	हाल PIPE_B:
		dsparb = पूर्णांकel_uncore_पढ़ो_fw(uncore, DSPARB);
		dsparb2 = पूर्णांकel_uncore_पढ़ो_fw(uncore, DSPARB2);

		dsparb &= ~(VLV_FIFO(SPRITEC, 0xff) |
			    VLV_FIFO(SPRITED, 0xff));
		dsparb |= (VLV_FIFO(SPRITEC, sprite0_start) |
			   VLV_FIFO(SPRITED, sprite1_start));

		dsparb2 &= ~(VLV_FIFO(SPRITEC_HI, 0xff) |
			     VLV_FIFO(SPRITED_HI, 0xff));
		dsparb2 |= (VLV_FIFO(SPRITEC_HI, sprite0_start >> 8) |
			   VLV_FIFO(SPRITED_HI, sprite1_start >> 8));

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, DSPARB, dsparb);
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, DSPARB2, dsparb2);
		अवरोध;
	हाल PIPE_C:
		dsparb3 = पूर्णांकel_uncore_पढ़ो_fw(uncore, DSPARB3);
		dsparb2 = पूर्णांकel_uncore_पढ़ो_fw(uncore, DSPARB2);

		dsparb3 &= ~(VLV_FIFO(SPRITEE, 0xff) |
			     VLV_FIFO(SPRITEF, 0xff));
		dsparb3 |= (VLV_FIFO(SPRITEE, sprite0_start) |
			    VLV_FIFO(SPRITEF, sprite1_start));

		dsparb2 &= ~(VLV_FIFO(SPRITEE_HI, 0xff) |
			     VLV_FIFO(SPRITEF_HI, 0xff));
		dsparb2 |= (VLV_FIFO(SPRITEE_HI, sprite0_start >> 8) |
			   VLV_FIFO(SPRITEF_HI, sprite1_start >> 8));

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, DSPARB3, dsparb3);
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, DSPARB2, dsparb2);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, DSPARB);

	spin_unlock(&uncore->lock);
पूर्ण

#अघोषित VLV_FIFO

अटल पूर्णांक vlv_compute_पूर्णांकermediate_wm(काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा vlv_wm_state *पूर्णांकermediate = &new_crtc_state->wm.vlv.पूर्णांकermediate;
	स्थिर काष्ठा vlv_wm_state *optimal = &new_crtc_state->wm.vlv.optimal;
	काष्ठा पूर्णांकel_atomic_state *पूर्णांकel_state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(पूर्णांकel_state, crtc);
	स्थिर काष्ठा vlv_wm_state *active = &old_crtc_state->wm.vlv.optimal;
	पूर्णांक level;

	अगर (!new_crtc_state->hw.active || drm_atomic_crtc_needs_modeset(&new_crtc_state->uapi)) अणु
		*पूर्णांकermediate = *optimal;

		पूर्णांकermediate->cxsr = false;
		जाओ out;
	पूर्ण

	पूर्णांकermediate->num_levels = min(optimal->num_levels, active->num_levels);
	पूर्णांकermediate->cxsr = optimal->cxsr && active->cxsr &&
		!new_crtc_state->disable_cxsr;

	क्रम (level = 0; level < पूर्णांकermediate->num_levels; level++) अणु
		क्रमागत plane_id plane_id;

		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			पूर्णांकermediate->wm[level].plane[plane_id] =
				min(optimal->wm[level].plane[plane_id],
				    active->wm[level].plane[plane_id]);
		पूर्ण

		पूर्णांकermediate->sr[level].plane = min(optimal->sr[level].plane,
						    active->sr[level].plane);
		पूर्णांकermediate->sr[level].cursor = min(optimal->sr[level].cursor,
						     active->sr[level].cursor);
	पूर्ण

	vlv_invalidate_wms(crtc, पूर्णांकermediate, level);

out:
	/*
	 * If our पूर्णांकermediate WM are identical to the final WM, then we can
	 * omit the post-vblank programming; only update अगर it's dअगरferent.
	 */
	अगर (स_भेद(पूर्णांकermediate, optimal, माप(*पूर्णांकermediate)) != 0)
		new_crtc_state->wm.need_postvbl_update = true;

	वापस 0;
पूर्ण

अटल व्योम vlv_merge_wm(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा vlv_wm_values *wm)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक num_active_pipes = 0;

	wm->level = dev_priv->wm.max_level;
	wm->cxsr = true;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		स्थिर काष्ठा vlv_wm_state *wm_state = &crtc->wm.active.vlv;

		अगर (!crtc->active)
			जारी;

		अगर (!wm_state->cxsr)
			wm->cxsr = false;

		num_active_pipes++;
		wm->level = min_t(पूर्णांक, wm->level, wm_state->num_levels - 1);
	पूर्ण

	अगर (num_active_pipes != 1)
		wm->cxsr = false;

	अगर (num_active_pipes > 1)
		wm->level = VLV_WM_LEVEL_PM2;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		स्थिर काष्ठा vlv_wm_state *wm_state = &crtc->wm.active.vlv;
		क्रमागत pipe pipe = crtc->pipe;

		wm->pipe[pipe] = wm_state->wm[wm->level];
		अगर (crtc->active && wm->cxsr)
			wm->sr = wm_state->sr[wm->level];

		wm->ddl[pipe].plane[PLANE_PRIMARY] = DDL_PRECISION_HIGH | 2;
		wm->ddl[pipe].plane[PLANE_SPRITE0] = DDL_PRECISION_HIGH | 2;
		wm->ddl[pipe].plane[PLANE_SPRITE1] = DDL_PRECISION_HIGH | 2;
		wm->ddl[pipe].plane[PLANE_CURSOR] = DDL_PRECISION_HIGH | 2;
	पूर्ण
पूर्ण

अटल व्योम vlv_program_watermarks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा vlv_wm_values *old_wm = &dev_priv->wm.vlv;
	काष्ठा vlv_wm_values new_wm = अणुपूर्ण;

	vlv_merge_wm(dev_priv, &new_wm);

	अगर (स_भेद(old_wm, &new_wm, माप(new_wm)) == 0)
		वापस;

	अगर (is_disabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_DDR_DVFS))
		chv_set_memory_dvfs(dev_priv, false);

	अगर (is_disabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_PM5))
		chv_set_memory_pm5(dev_priv, false);

	अगर (is_disabling(old_wm->cxsr, new_wm.cxsr, true))
		_पूर्णांकel_set_memory_cxsr(dev_priv, false);

	vlv_ग_लिखो_wm_values(dev_priv, &new_wm);

	अगर (is_enabling(old_wm->cxsr, new_wm.cxsr, true))
		_पूर्णांकel_set_memory_cxsr(dev_priv, true);

	अगर (is_enabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_PM5))
		chv_set_memory_pm5(dev_priv, true);

	अगर (is_enabling(old_wm->level, new_wm.level, VLV_WM_LEVEL_DDR_DVFS))
		chv_set_memory_dvfs(dev_priv, true);

	*old_wm = new_wm;
पूर्ण

अटल व्योम vlv_initial_watermarks(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.vlv = crtc_state->wm.vlv.पूर्णांकermediate;
	vlv_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

अटल व्योम vlv_optimize_watermarks(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	अगर (!crtc_state->wm.need_postvbl_update)
		वापस;

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.vlv = crtc_state->wm.vlv.optimal;
	vlv_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

अटल व्योम i965_update_wm(काष्ठा पूर्णांकel_crtc *unused_crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(unused_crtc->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक srwm = 1;
	पूर्णांक cursor_sr = 16;
	bool cxsr_enabled;

	/* Calc sr entries क्रम one plane configs */
	crtc = single_enabled_crtc(dev_priv);
	अगर (crtc) अणु
		/* self-refresh has much higher latency */
		अटल स्थिर पूर्णांक sr_latency_ns = 12000;
		स्थिर काष्ठा drm_display_mode *pipe_mode =
			&crtc->config->hw.pipe_mode;
		स्थिर काष्ठा drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		पूर्णांक घड़ी = pipe_mode->crtc_घड़ी;
		पूर्णांक htotal = pipe_mode->crtc_htotal;
		पूर्णांक hdisplay = crtc->config->pipe_src_w;
		पूर्णांक cpp = fb->क्रमmat->cpp[0];
		पूर्णांक entries;

		entries = पूर्णांकel_wm_method2(घड़ी, htotal,
					   hdisplay, cpp, sr_latency_ns / 100);
		entries = DIV_ROUND_UP(entries, I915_FIFO_LINE_SIZE);
		srwm = I965_FIFO_SIZE - entries;
		अगर (srwm < 0)
			srwm = 1;
		srwm &= 0x1ff;
		drm_dbg_kms(&dev_priv->drm,
			    "self-refresh entries: %d, wm: %d\n",
			    entries, srwm);

		entries = पूर्णांकel_wm_method2(घड़ी, htotal,
					   crtc->base.cursor->state->crtc_w, 4,
					   sr_latency_ns / 100);
		entries = DIV_ROUND_UP(entries,
				       i965_cursor_wm_info.cacheline_size) +
			i965_cursor_wm_info.guard_size;

		cursor_sr = i965_cursor_wm_info.fअगरo_size - entries;
		अगर (cursor_sr > i965_cursor_wm_info.max_wm)
			cursor_sr = i965_cursor_wm_info.max_wm;

		drm_dbg_kms(&dev_priv->drm,
			    "self-refresh watermark: display plane %d "
			    "cursor %d\n", srwm, cursor_sr);

		cxsr_enabled = true;
	पूर्ण अन्यथा अणु
		cxsr_enabled = false;
		/* Turn off self refresh अगर both pipes are enabled */
		पूर्णांकel_set_memory_cxsr(dev_priv, false);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "Setting FIFO watermarks - A: 8, B: 8, C: 8, SR %d\n",
		    srwm);

	/* 965 has limitations... */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW1, FW_WM(srwm, SR) |
		   FW_WM(8, CURSORB) |
		   FW_WM(8, PLANEB) |
		   FW_WM(8, PLANEA));
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW2, FW_WM(8, CURSORA) |
		   FW_WM(8, PLANEC_OLD));
	/* update cursor SR watermark */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPFW3, FW_WM(cursor_sr, CURSOR_SR));

	अगर (cxsr_enabled)
		पूर्णांकel_set_memory_cxsr(dev_priv, true);
पूर्ण

#अघोषित FW_WM

अटल व्योम i9xx_update_wm(काष्ठा पूर्णांकel_crtc *unused_crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(unused_crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_watermark_params *wm_info;
	u32 fwater_lo;
	u32 fwater_hi;
	पूर्णांक cwm, srwm = 1;
	पूर्णांक fअगरo_size;
	पूर्णांक planea_wm, planeb_wm;
	काष्ठा पूर्णांकel_crtc *crtc, *enabled = शून्य;

	अगर (IS_I945GM(dev_priv))
		wm_info = &i945_wm_info;
	अन्यथा अगर (!IS_DISPLAY_VER(dev_priv, 2))
		wm_info = &i915_wm_info;
	अन्यथा
		wm_info = &i830_a_wm_info;

	fअगरo_size = dev_priv->display.get_fअगरo_size(dev_priv, PLANE_A);
	crtc = पूर्णांकel_get_crtc_क्रम_plane(dev_priv, PLANE_A);
	अगर (पूर्णांकel_crtc_active(crtc)) अणु
		स्थिर काष्ठा drm_display_mode *pipe_mode =
			&crtc->config->hw.pipe_mode;
		स्थिर काष्ठा drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		पूर्णांक cpp;

		अगर (IS_DISPLAY_VER(dev_priv, 2))
			cpp = 4;
		अन्यथा
			cpp = fb->क्रमmat->cpp[0];

		planea_wm = पूर्णांकel_calculate_wm(pipe_mode->crtc_घड़ी,
					       wm_info, fअगरo_size, cpp,
					       pessimal_latency_ns);
		enabled = crtc;
	पूर्ण अन्यथा अणु
		planea_wm = fअगरo_size - wm_info->guard_size;
		अगर (planea_wm > (दीर्घ)wm_info->max_wm)
			planea_wm = wm_info->max_wm;
	पूर्ण

	अगर (IS_DISPLAY_VER(dev_priv, 2))
		wm_info = &i830_bc_wm_info;

	fअगरo_size = dev_priv->display.get_fअगरo_size(dev_priv, PLANE_B);
	crtc = पूर्णांकel_get_crtc_क्रम_plane(dev_priv, PLANE_B);
	अगर (पूर्णांकel_crtc_active(crtc)) अणु
		स्थिर काष्ठा drm_display_mode *pipe_mode =
			&crtc->config->hw.pipe_mode;
		स्थिर काष्ठा drm_framebuffer *fb =
			crtc->base.primary->state->fb;
		पूर्णांक cpp;

		अगर (IS_DISPLAY_VER(dev_priv, 2))
			cpp = 4;
		अन्यथा
			cpp = fb->क्रमmat->cpp[0];

		planeb_wm = पूर्णांकel_calculate_wm(pipe_mode->crtc_घड़ी,
					       wm_info, fअगरo_size, cpp,
					       pessimal_latency_ns);
		अगर (enabled == शून्य)
			enabled = crtc;
		अन्यथा
			enabled = शून्य;
	पूर्ण अन्यथा अणु
		planeb_wm = fअगरo_size - wm_info->guard_size;
		अगर (planeb_wm > (दीर्घ)wm_info->max_wm)
			planeb_wm = wm_info->max_wm;
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "FIFO watermarks - A: %d, B: %d\n", planea_wm, planeb_wm);

	अगर (IS_I915GM(dev_priv) && enabled) अणु
		काष्ठा drm_i915_gem_object *obj;

		obj = पूर्णांकel_fb_obj(enabled->base.primary->state->fb);

		/* self-refresh seems busted with untiled */
		अगर (!i915_gem_object_is_tiled(obj))
			enabled = शून्य;
	पूर्ण

	/*
	 * Overlay माला_लो an aggressive शेष since video jitter is bad.
	 */
	cwm = 2;

	/* Play safe and disable self-refresh beक्रमe adjusting watermarks. */
	पूर्णांकel_set_memory_cxsr(dev_priv, false);

	/* Calc sr entries क्रम one plane configs */
	अगर (HAS_FW_BLC(dev_priv) && enabled) अणु
		/* self-refresh has much higher latency */
		अटल स्थिर पूर्णांक sr_latency_ns = 6000;
		स्थिर काष्ठा drm_display_mode *pipe_mode =
			&enabled->config->hw.pipe_mode;
		स्थिर काष्ठा drm_framebuffer *fb =
			enabled->base.primary->state->fb;
		पूर्णांक घड़ी = pipe_mode->crtc_घड़ी;
		पूर्णांक htotal = pipe_mode->crtc_htotal;
		पूर्णांक hdisplay = enabled->config->pipe_src_w;
		पूर्णांक cpp;
		पूर्णांक entries;

		अगर (IS_I915GM(dev_priv) || IS_I945GM(dev_priv))
			cpp = 4;
		अन्यथा
			cpp = fb->क्रमmat->cpp[0];

		entries = पूर्णांकel_wm_method2(घड़ी, htotal, hdisplay, cpp,
					   sr_latency_ns / 100);
		entries = DIV_ROUND_UP(entries, wm_info->cacheline_size);
		drm_dbg_kms(&dev_priv->drm,
			    "self-refresh entries: %d\n", entries);
		srwm = wm_info->fअगरo_size - entries;
		अगर (srwm < 0)
			srwm = 1;

		अगर (IS_I945G(dev_priv) || IS_I945GM(dev_priv))
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC_SELF,
				   FW_BLC_SELF_FIFO_MASK | (srwm & 0xff));
		अन्यथा
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC_SELF, srwm & 0x3f);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "Setting FIFO watermarks - A: %d, B: %d, C: %d, SR %d\n",
		     planea_wm, planeb_wm, cwm, srwm);

	fwater_lo = ((planeb_wm & 0x3f) << 16) | (planea_wm & 0x3f);
	fwater_hi = (cwm & 0x1f);

	/* Set request length to 8 cachelines per fetch */
	fwater_lo = fwater_lo | (1 << 24) | (1 << 8);
	fwater_hi = fwater_hi | (1 << 8);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC, fwater_lo);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC2, fwater_hi);

	अगर (enabled)
		पूर्णांकel_set_memory_cxsr(dev_priv, true);
पूर्ण

अटल व्योम i845_update_wm(काष्ठा पूर्णांकel_crtc *unused_crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(unused_crtc->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	स्थिर काष्ठा drm_display_mode *pipe_mode;
	u32 fwater_lo;
	पूर्णांक planea_wm;

	crtc = single_enabled_crtc(dev_priv);
	अगर (crtc == शून्य)
		वापस;

	pipe_mode = &crtc->config->hw.pipe_mode;
	planea_wm = पूर्णांकel_calculate_wm(pipe_mode->crtc_घड़ी,
				       &i845_wm_info,
				       dev_priv->display.get_fअगरo_size(dev_priv, PLANE_A),
				       4, pessimal_latency_ns);
	fwater_lo = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FW_BLC) & ~0xfff;
	fwater_lo |= (3<<8) | planea_wm;

	drm_dbg_kms(&dev_priv->drm,
		    "Setting FIFO watermarks - A: %d\n", planea_wm);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FW_BLC, fwater_lo);
पूर्ण

/* latency must be in 0.1us units. */
अटल अचिन्हित पूर्णांक ilk_wm_method1(अचिन्हित पूर्णांक pixel_rate,
				   अचिन्हित पूर्णांक cpp,
				   अचिन्हित पूर्णांक latency)
अणु
	अचिन्हित पूर्णांक ret;

	ret = पूर्णांकel_wm_method1(pixel_rate, cpp, latency);
	ret = DIV_ROUND_UP(ret, 64) + 2;

	वापस ret;
पूर्ण

/* latency must be in 0.1us units. */
अटल अचिन्हित पूर्णांक ilk_wm_method2(अचिन्हित पूर्णांक pixel_rate,
				   अचिन्हित पूर्णांक htotal,
				   अचिन्हित पूर्णांक width,
				   अचिन्हित पूर्णांक cpp,
				   अचिन्हित पूर्णांक latency)
अणु
	अचिन्हित पूर्णांक ret;

	ret = पूर्णांकel_wm_method2(pixel_rate, htotal,
			       width, cpp, latency);
	ret = DIV_ROUND_UP(ret, 64) + 2;

	वापस ret;
पूर्ण

अटल u32 ilk_wm_fbc(u32 pri_val, u32 horiz_pixels, u8 cpp)
अणु
	/*
	 * Neither of these should be possible since this function shouldn't be
	 * called अगर the CRTC is off or the plane is invisible.  But let's be
	 * extra paranoid to aव्योम a potential भागide-by-zero अगर we screw up
	 * अन्यथाwhere in the driver.
	 */
	अगर (WARN_ON(!cpp))
		वापस 0;
	अगर (WARN_ON(!horiz_pixels))
		वापस 0;

	वापस DIV_ROUND_UP(pri_val * 64, horiz_pixels * cpp) + 2;
पूर्ण

काष्ठा ilk_wm_maximums अणु
	u16 pri;
	u16 spr;
	u16 cur;
	u16 fbc;
पूर्ण;

/*
 * For both WM_PIPE and WM_LP.
 * mem_value must be in 0.1us units.
 */
अटल u32 ilk_compute_pri_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			      u32 mem_value, bool is_lp)
अणु
	u32 method1, method2;
	पूर्णांक cpp;

	अगर (mem_value == 0)
		वापस U32_MAX;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	cpp = plane_state->hw.fb->क्रमmat->cpp[0];

	method1 = ilk_wm_method1(crtc_state->pixel_rate, cpp, mem_value);

	अगर (!is_lp)
		वापस method1;

	method2 = ilk_wm_method2(crtc_state->pixel_rate,
				 crtc_state->hw.pipe_mode.crtc_htotal,
				 drm_rect_width(&plane_state->uapi.dst),
				 cpp, mem_value);

	वापस min(method1, method2);
पूर्ण

/*
 * For both WM_PIPE and WM_LP.
 * mem_value must be in 0.1us units.
 */
अटल u32 ilk_compute_spr_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			      u32 mem_value)
अणु
	u32 method1, method2;
	पूर्णांक cpp;

	अगर (mem_value == 0)
		वापस U32_MAX;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	cpp = plane_state->hw.fb->क्रमmat->cpp[0];

	method1 = ilk_wm_method1(crtc_state->pixel_rate, cpp, mem_value);
	method2 = ilk_wm_method2(crtc_state->pixel_rate,
				 crtc_state->hw.pipe_mode.crtc_htotal,
				 drm_rect_width(&plane_state->uapi.dst),
				 cpp, mem_value);
	वापस min(method1, method2);
पूर्ण

/*
 * For both WM_PIPE and WM_LP.
 * mem_value must be in 0.1us units.
 */
अटल u32 ilk_compute_cur_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			      u32 mem_value)
अणु
	पूर्णांक cpp;

	अगर (mem_value == 0)
		वापस U32_MAX;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	cpp = plane_state->hw.fb->क्रमmat->cpp[0];

	वापस ilk_wm_method2(crtc_state->pixel_rate,
			      crtc_state->hw.pipe_mode.crtc_htotal,
			      drm_rect_width(&plane_state->uapi.dst),
			      cpp, mem_value);
पूर्ण

/* Only क्रम WM_LP. */
अटल u32 ilk_compute_fbc_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			      u32 pri_val)
अणु
	पूर्णांक cpp;

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	cpp = plane_state->hw.fb->क्रमmat->cpp[0];

	वापस ilk_wm_fbc(pri_val, drm_rect_width(&plane_state->uapi.dst),
			  cpp);
पूर्ण

अटल अचिन्हित पूर्णांक
ilk_display_fअगरo_size(स्थिर काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 8)
		वापस 3072;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7)
		वापस 768;
	अन्यथा
		वापस 512;
पूर्ण

अटल अचिन्हित पूर्णांक
ilk_plane_wm_reg_max(स्थिर काष्ठा drm_i915_निजी *dev_priv,
		     पूर्णांक level, bool is_sprite)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 8)
		/* BDW primary/sprite plane watermarks */
		वापस level == 0 ? 255 : 2047;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7)
		/* IVB/HSW primary/sprite plane watermarks */
		वापस level == 0 ? 127 : 1023;
	अन्यथा अगर (!is_sprite)
		/* ILK/SNB primary plane watermarks */
		वापस level == 0 ? 127 : 511;
	अन्यथा
		/* ILK/SNB sprite plane watermarks */
		वापस level == 0 ? 63 : 255;
पूर्ण

अटल अचिन्हित पूर्णांक
ilk_cursor_wm_reg_max(स्थिर काष्ठा drm_i915_निजी *dev_priv, पूर्णांक level)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 7)
		वापस level == 0 ? 63 : 255;
	अन्यथा
		वापस level == 0 ? 31 : 63;
पूर्ण

अटल अचिन्हित पूर्णांक ilk_fbc_wm_reg_max(स्थिर काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 8)
		वापस 31;
	अन्यथा
		वापस 15;
पूर्ण

/* Calculate the maximum primary/sprite plane watermark */
अटल अचिन्हित पूर्णांक ilk_plane_wm_max(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				     पूर्णांक level,
				     स्थिर काष्ठा पूर्णांकel_wm_config *config,
				     क्रमागत पूर्णांकel_ddb_partitioning ddb_partitioning,
				     bool is_sprite)
अणु
	अचिन्हित पूर्णांक fअगरo_size = ilk_display_fअगरo_size(dev_priv);

	/* अगर sprites aren't enabled, sprites get nothing */
	अगर (is_sprite && !config->sprites_enabled)
		वापस 0;

	/* HSW allows LP1+ watermarks even with multiple pipes */
	अगर (level == 0 || config->num_pipes_active > 1) अणु
		fअगरo_size /= INTEL_NUM_PIPES(dev_priv);

		/*
		 * For some reason the non self refresh
		 * FIFO size is only half of the self
		 * refresh FIFO size on ILK/SNB.
		 */
		अगर (DISPLAY_VER(dev_priv) <= 6)
			fअगरo_size /= 2;
	पूर्ण

	अगर (config->sprites_enabled) अणु
		/* level 0 is always calculated with 1:1 split */
		अगर (level > 0 && ddb_partitioning == INTEL_DDB_PART_5_6) अणु
			अगर (is_sprite)
				fअगरo_size *= 5;
			fअगरo_size /= 6;
		पूर्ण अन्यथा अणु
			fअगरo_size /= 2;
		पूर्ण
	पूर्ण

	/* clamp to max that the रेजिस्टरs can hold */
	वापस min(fअगरo_size, ilk_plane_wm_reg_max(dev_priv, level, is_sprite));
पूर्ण

/* Calculate the maximum cursor plane watermark */
अटल अचिन्हित पूर्णांक ilk_cursor_wm_max(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				      पूर्णांक level,
				      स्थिर काष्ठा पूर्णांकel_wm_config *config)
अणु
	/* HSW LP1+ watermarks w/ multiple pipes */
	अगर (level > 0 && config->num_pipes_active > 1)
		वापस 64;

	/* otherwise just report max that रेजिस्टरs can hold */
	वापस ilk_cursor_wm_reg_max(dev_priv, level);
पूर्ण

अटल व्योम ilk_compute_wm_maximums(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				    पूर्णांक level,
				    स्थिर काष्ठा पूर्णांकel_wm_config *config,
				    क्रमागत पूर्णांकel_ddb_partitioning ddb_partitioning,
				    काष्ठा ilk_wm_maximums *max)
अणु
	max->pri = ilk_plane_wm_max(dev_priv, level, config, ddb_partitioning, false);
	max->spr = ilk_plane_wm_max(dev_priv, level, config, ddb_partitioning, true);
	max->cur = ilk_cursor_wm_max(dev_priv, level, config);
	max->fbc = ilk_fbc_wm_reg_max(dev_priv);
पूर्ण

अटल व्योम ilk_compute_wm_reg_maximums(स्थिर काष्ठा drm_i915_निजी *dev_priv,
					पूर्णांक level,
					काष्ठा ilk_wm_maximums *max)
अणु
	max->pri = ilk_plane_wm_reg_max(dev_priv, level, false);
	max->spr = ilk_plane_wm_reg_max(dev_priv, level, true);
	max->cur = ilk_cursor_wm_reg_max(dev_priv, level);
	max->fbc = ilk_fbc_wm_reg_max(dev_priv);
पूर्ण

अटल bool ilk_validate_wm_level(पूर्णांक level,
				  स्थिर काष्ठा ilk_wm_maximums *max,
				  काष्ठा पूर्णांकel_wm_level *result)
अणु
	bool ret;

	/* alपढ़ोy determined to be invalid? */
	अगर (!result->enable)
		वापस false;

	result->enable = result->pri_val <= max->pri &&
			 result->spr_val <= max->spr &&
			 result->cur_val <= max->cur;

	ret = result->enable;

	/*
	 * HACK until we can pre-compute everything,
	 * and thus fail gracefully अगर LP0 watermarks
	 * are exceeded...
	 */
	अगर (level == 0 && !result->enable) अणु
		अगर (result->pri_val > max->pri)
			DRM_DEBUG_KMS("Primary WM%d too large %u (max %u)\n",
				      level, result->pri_val, max->pri);
		अगर (result->spr_val > max->spr)
			DRM_DEBUG_KMS("Sprite WM%d too large %u (max %u)\n",
				      level, result->spr_val, max->spr);
		अगर (result->cur_val > max->cur)
			DRM_DEBUG_KMS("Cursor WM%d too large %u (max %u)\n",
				      level, result->cur_val, max->cur);

		result->pri_val = min_t(u32, result->pri_val, max->pri);
		result->spr_val = min_t(u32, result->spr_val, max->spr);
		result->cur_val = min_t(u32, result->cur_val, max->cur);
		result->enable = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ilk_compute_wm_level(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				 स्थिर काष्ठा पूर्णांकel_crtc *crtc,
				 पूर्णांक level,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा पूर्णांकel_plane_state *pristate,
				 स्थिर काष्ठा पूर्णांकel_plane_state *sprstate,
				 स्थिर काष्ठा पूर्णांकel_plane_state *curstate,
				 काष्ठा पूर्णांकel_wm_level *result)
अणु
	u16 pri_latency = dev_priv->wm.pri_latency[level];
	u16 spr_latency = dev_priv->wm.spr_latency[level];
	u16 cur_latency = dev_priv->wm.cur_latency[level];

	/* WM1+ latency values stored in 0.5us units */
	अगर (level > 0) अणु
		pri_latency *= 5;
		spr_latency *= 5;
		cur_latency *= 5;
	पूर्ण

	अगर (pristate) अणु
		result->pri_val = ilk_compute_pri_wm(crtc_state, pristate,
						     pri_latency, level);
		result->fbc_val = ilk_compute_fbc_wm(crtc_state, pristate, result->pri_val);
	पूर्ण

	अगर (sprstate)
		result->spr_val = ilk_compute_spr_wm(crtc_state, sprstate, spr_latency);

	अगर (curstate)
		result->cur_val = ilk_compute_cur_wm(crtc_state, curstate, cur_latency);

	result->enable = true;
पूर्ण

अटल व्योम पूर्णांकel_पढ़ो_wm_latency(काष्ठा drm_i915_निजी *dev_priv,
				  u16 wm[8])
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		u32 val;
		पूर्णांक ret, i;
		पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);

		/* पढ़ो the first set of memory latencies[0:3] */
		val = 0; /* data0 to be programmed to 0 क्रम first set */
		ret = sandybridge_pcode_पढ़ो(dev_priv,
					     GEN9_PCODE_READ_MEM_LATENCY,
					     &val, शून्य);

		अगर (ret) अणु
			drm_err(&dev_priv->drm,
				"SKL Mailbox read error = %d\n", ret);
			वापस;
		पूर्ण

		wm[0] = val & GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[1] = (val >> GEN9_MEM_LATENCY_LEVEL_1_5_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[2] = (val >> GEN9_MEM_LATENCY_LEVEL_2_6_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[3] = (val >> GEN9_MEM_LATENCY_LEVEL_3_7_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;

		/* पढ़ो the second set of memory latencies[4:7] */
		val = 1; /* data0 to be programmed to 1 क्रम second set */
		ret = sandybridge_pcode_पढ़ो(dev_priv,
					     GEN9_PCODE_READ_MEM_LATENCY,
					     &val, शून्य);
		अगर (ret) अणु
			drm_err(&dev_priv->drm,
				"SKL Mailbox read error = %d\n", ret);
			वापस;
		पूर्ण

		wm[4] = val & GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[5] = (val >> GEN9_MEM_LATENCY_LEVEL_1_5_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[6] = (val >> GEN9_MEM_LATENCY_LEVEL_2_6_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[7] = (val >> GEN9_MEM_LATENCY_LEVEL_3_7_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;

		/*
		 * If a level n (n > 1) has a 0us latency, all levels m (m >= n)
		 * need to be disabled. We make sure to sanitize the values out
		 * of the punit to satisfy this requirement.
		 */
		क्रम (level = 1; level <= max_level; level++) अणु
			अगर (wm[level] == 0) अणु
				क्रम (i = level + 1; i <= max_level; i++)
					wm[i] = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * WaWmMemoryReadLatency:skl+,glk
		 *
		 * punit करोesn't take पूर्णांकo account the पढ़ो latency so we need
		 * to add 2us to the various latency levels we retrieve from the
		 * punit when level 0 response data us 0us.
		 */
		अगर (wm[0] == 0) अणु
			wm[0] += 2;
			क्रम (level = 1; level <= max_level; level++) अणु
				अगर (wm[level] == 0)
					अवरोध;
				wm[level] += 2;
			पूर्ण
		पूर्ण

		/*
		 * WA Level-0 adjusपंचांगent क्रम 16GB DIMMs: SKL+
		 * If we could not get dimm info enable this WA to prevent from
		 * any underrun. If not able to get Dimm info assume 16GB dimm
		 * to aव्योम any underrun.
		 */
		अगर (dev_priv->dram_info.wm_lv_0_adjust_needed)
			wm[0] += 1;

	पूर्ण अन्यथा अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
		u64 sskpd = पूर्णांकel_uncore_पढ़ो64(uncore, MCH_SSKPD);

		wm[0] = (sskpd >> 56) & 0xFF;
		अगर (wm[0] == 0)
			wm[0] = sskpd & 0xF;
		wm[1] = (sskpd >> 4) & 0xFF;
		wm[2] = (sskpd >> 12) & 0xFF;
		wm[3] = (sskpd >> 20) & 0x1FF;
		wm[4] = (sskpd >> 32) & 0x1FF;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 6) अणु
		u32 sskpd = पूर्णांकel_uncore_पढ़ो(uncore, MCH_SSKPD);

		wm[0] = (sskpd >> SSKPD_WM0_SHIFT) & SSKPD_WM_MASK;
		wm[1] = (sskpd >> SSKPD_WM1_SHIFT) & SSKPD_WM_MASK;
		wm[2] = (sskpd >> SSKPD_WM2_SHIFT) & SSKPD_WM_MASK;
		wm[3] = (sskpd >> SSKPD_WM3_SHIFT) & SSKPD_WM_MASK;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5) अणु
		u32 mltr = पूर्णांकel_uncore_पढ़ो(uncore, MLTR_ILK);

		/* ILK primary LP0 latency is 700 ns */
		wm[0] = 7;
		wm[1] = (mltr >> MLTR_WM1_SHIFT) & ILK_SRLT_MASK;
		wm[2] = (mltr >> MLTR_WM2_SHIFT) & ILK_SRLT_MASK;
	पूर्ण अन्यथा अणु
		MISSING_CASE(INTEL_DEVID(dev_priv));
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_fixup_spr_wm_latency(काष्ठा drm_i915_निजी *dev_priv,
				       u16 wm[5])
अणु
	/* ILK sprite LP0 latency is 1300 ns */
	अगर (IS_DISPLAY_VER(dev_priv, 5))
		wm[0] = 13;
पूर्ण

अटल व्योम पूर्णांकel_fixup_cur_wm_latency(काष्ठा drm_i915_निजी *dev_priv,
				       u16 wm[5])
अणु
	/* ILK cursor LP0 latency is 1300 ns */
	अगर (IS_DISPLAY_VER(dev_priv, 5))
		wm[0] = 13;
पूर्ण

पूर्णांक ilk_wm_max_level(स्थिर काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* how many WM levels are we expecting */
	अगर (DISPLAY_VER(dev_priv) >= 9)
		वापस 7;
	अन्यथा अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		वापस 4;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 6)
		वापस 3;
	अन्यथा
		वापस 2;
पूर्ण

अटल व्योम पूर्णांकel_prपूर्णांक_wm_latency(काष्ठा drm_i915_निजी *dev_priv,
				   स्थिर अक्षर *name,
				   स्थिर u16 wm[])
अणु
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);

	क्रम (level = 0; level <= max_level; level++) अणु
		अचिन्हित पूर्णांक latency = wm[level];

		अगर (latency == 0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "%s WM%d latency not provided\n",
				    name, level);
			जारी;
		पूर्ण

		/*
		 * - latencies are in us on gen9.
		 * - beक्रमe then, WM1+ latency values are in 0.5us units
		 */
		अगर (DISPLAY_VER(dev_priv) >= 9)
			latency *= 10;
		अन्यथा अगर (level > 0)
			latency *= 5;

		drm_dbg_kms(&dev_priv->drm,
			    "%s WM%d latency %u (%u.%u usec)\n", name, level,
			    wm[level], latency / 10, latency % 10);
	पूर्ण
पूर्ण

अटल bool ilk_increase_wm_latency(काष्ठा drm_i915_निजी *dev_priv,
				    u16 wm[5], u16 min)
अणु
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);

	अगर (wm[0] >= min)
		वापस false;

	wm[0] = max(wm[0], min);
	क्रम (level = 1; level <= max_level; level++)
		wm[level] = max_t(u16, wm[level], DIV_ROUND_UP(min, 5));

	वापस true;
पूर्ण

अटल व्योम snb_wm_latency_quirk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	bool changed;

	/*
	 * The BIOS provided WM memory latency values are often
	 * inadequate क्रम high resolution displays. Adjust them.
	 */
	changed = ilk_increase_wm_latency(dev_priv, dev_priv->wm.pri_latency, 12) |
		ilk_increase_wm_latency(dev_priv, dev_priv->wm.spr_latency, 12) |
		ilk_increase_wm_latency(dev_priv, dev_priv->wm.cur_latency, 12);

	अगर (!changed)
		वापस;

	drm_dbg_kms(&dev_priv->drm,
		    "WM latency values increased to avoid potential underruns\n");
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Primary", dev_priv->wm.pri_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Sprite", dev_priv->wm.spr_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Cursor", dev_priv->wm.cur_latency);
पूर्ण

अटल व्योम snb_wm_lp3_irq_quirk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * On some SNB machines (Thinkpad X220 Tablet at least)
	 * LP3 usage can cause vblank पूर्णांकerrupts to be lost.
	 * The DEIIR bit will go high but it looks like the CPU
	 * never माला_लो पूर्णांकerrupted.
	 *
	 * It's not clear whether other पूर्णांकerrupt source could
	 * be affected or अगर this is somehow limited to vblank
	 * पूर्णांकerrupts only. To play it safe we disable LP3
	 * watermarks entirely.
	 */
	अगर (dev_priv->wm.pri_latency[3] == 0 &&
	    dev_priv->wm.spr_latency[3] == 0 &&
	    dev_priv->wm.cur_latency[3] == 0)
		वापस;

	dev_priv->wm.pri_latency[3] = 0;
	dev_priv->wm.spr_latency[3] = 0;
	dev_priv->wm.cur_latency[3] = 0;

	drm_dbg_kms(&dev_priv->drm,
		    "LP3 watermarks disabled due to potential for lost interrupts\n");
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Primary", dev_priv->wm.pri_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Sprite", dev_priv->wm.spr_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Cursor", dev_priv->wm.cur_latency);
पूर्ण

अटल व्योम ilk_setup_wm_latency(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_पढ़ो_wm_latency(dev_priv, dev_priv->wm.pri_latency);

	स_नकल(dev_priv->wm.spr_latency, dev_priv->wm.pri_latency,
	       माप(dev_priv->wm.pri_latency));
	स_नकल(dev_priv->wm.cur_latency, dev_priv->wm.pri_latency,
	       माप(dev_priv->wm.pri_latency));

	पूर्णांकel_fixup_spr_wm_latency(dev_priv, dev_priv->wm.spr_latency);
	पूर्णांकel_fixup_cur_wm_latency(dev_priv, dev_priv->wm.cur_latency);

	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Primary", dev_priv->wm.pri_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Sprite", dev_priv->wm.spr_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Cursor", dev_priv->wm.cur_latency);

	अगर (IS_DISPLAY_VER(dev_priv, 6)) अणु
		snb_wm_latency_quirk(dev_priv);
		snb_wm_lp3_irq_quirk(dev_priv);
	पूर्ण
पूर्ण

अटल व्योम skl_setup_wm_latency(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_पढ़ो_wm_latency(dev_priv, dev_priv->wm.skl_latency);
	पूर्णांकel_prपूर्णांक_wm_latency(dev_priv, "Gen9 Plane", dev_priv->wm.skl_latency);
पूर्ण

अटल bool ilk_validate_pipe_wm(स्थिर काष्ठा drm_i915_निजी *dev_priv,
				 काष्ठा पूर्णांकel_pipe_wm *pipe_wm)
अणु
	/* LP0 watermark maximums depend on this pipe alone */
	स्थिर काष्ठा पूर्णांकel_wm_config config = अणु
		.num_pipes_active = 1,
		.sprites_enabled = pipe_wm->sprites_enabled,
		.sprites_scaled = pipe_wm->sprites_scaled,
	पूर्ण;
	काष्ठा ilk_wm_maximums max;

	/* LP0 watermarks always use 1/2 DDB partitioning */
	ilk_compute_wm_maximums(dev_priv, 0, &config, INTEL_DDB_PART_1_2, &max);

	/* At least LP0 must be valid */
	अगर (!ilk_validate_wm_level(0, &max, &pipe_wm->wm[0])) अणु
		drm_dbg_kms(&dev_priv->drm, "LP0 watermark invalid\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Compute new watermarks क्रम the pipe */
अटल पूर्णांक ilk_compute_pipe_wm(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_pipe_wm *pipe_wm;
	काष्ठा पूर्णांकel_plane *plane;
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	स्थिर काष्ठा पूर्णांकel_plane_state *pristate = शून्य;
	स्थिर काष्ठा पूर्णांकel_plane_state *sprstate = शून्य;
	स्थिर काष्ठा पूर्णांकel_plane_state *curstate = शून्य;
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv), usable_level;
	काष्ठा ilk_wm_maximums max;

	pipe_wm = &crtc_state->wm.ilk.optimal;

	पूर्णांकel_atomic_crtc_state_क्रम_each_plane_state(plane, plane_state, crtc_state) अणु
		अगर (plane->base.type == DRM_PLANE_TYPE_PRIMARY)
			pristate = plane_state;
		अन्यथा अगर (plane->base.type == DRM_PLANE_TYPE_OVERLAY)
			sprstate = plane_state;
		अन्यथा अगर (plane->base.type == DRM_PLANE_TYPE_CURSOR)
			curstate = plane_state;
	पूर्ण

	pipe_wm->pipe_enabled = crtc_state->hw.active;
	अगर (sprstate) अणु
		pipe_wm->sprites_enabled = sprstate->uapi.visible;
		pipe_wm->sprites_scaled = sprstate->uapi.visible &&
			(drm_rect_width(&sprstate->uapi.dst) != drm_rect_width(&sprstate->uapi.src) >> 16 ||
			 drm_rect_height(&sprstate->uapi.dst) != drm_rect_height(&sprstate->uapi.src) >> 16);
	पूर्ण

	usable_level = max_level;

	/* ILK/SNB: LP2+ watermarks only w/o sprites */
	अगर (DISPLAY_VER(dev_priv) <= 6 && pipe_wm->sprites_enabled)
		usable_level = 1;

	/* ILK/SNB/IVB: LP1+ watermarks only w/o scaling */
	अगर (pipe_wm->sprites_scaled)
		usable_level = 0;

	स_रखो(&pipe_wm->wm, 0, माप(pipe_wm->wm));
	ilk_compute_wm_level(dev_priv, crtc, 0, crtc_state,
			     pristate, sprstate, curstate, &pipe_wm->wm[0]);

	अगर (!ilk_validate_pipe_wm(dev_priv, pipe_wm))
		वापस -EINVAL;

	ilk_compute_wm_reg_maximums(dev_priv, 1, &max);

	क्रम (level = 1; level <= usable_level; level++) अणु
		काष्ठा पूर्णांकel_wm_level *wm = &pipe_wm->wm[level];

		ilk_compute_wm_level(dev_priv, crtc, level, crtc_state,
				     pristate, sprstate, curstate, wm);

		/*
		 * Disable any watermark level that exceeds the
		 * रेजिस्टर maximums since such watermarks are
		 * always invalid.
		 */
		अगर (!ilk_validate_wm_level(level, &max, wm)) अणु
			स_रखो(wm, 0, माप(*wm));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Build a set of 'intermediate' watermark values that satisfy both the old
 * state and the new state.  These can be programmed to the hardware
 * immediately.
 */
अटल पूर्णांक ilk_compute_पूर्णांकermediate_wm(काष्ठा पूर्णांकel_crtc_state *newstate)
अणु
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(newstate->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_crtc->base.dev);
	काष्ठा पूर्णांकel_pipe_wm *a = &newstate->wm.ilk.पूर्णांकermediate;
	काष्ठा पूर्णांकel_atomic_state *पूर्णांकel_state =
		to_पूर्णांकel_atomic_state(newstate->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *oldstate =
		पूर्णांकel_atomic_get_old_crtc_state(पूर्णांकel_state, पूर्णांकel_crtc);
	स्थिर काष्ठा पूर्णांकel_pipe_wm *b = &oldstate->wm.ilk.optimal;
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);

	/*
	 * Start with the final, target watermarks, then combine with the
	 * currently active watermarks to get values that are safe both beक्रमe
	 * and after the vblank.
	 */
	*a = newstate->wm.ilk.optimal;
	अगर (!newstate->hw.active || drm_atomic_crtc_needs_modeset(&newstate->uapi) ||
	    पूर्णांकel_state->skip_पूर्णांकermediate_wm)
		वापस 0;

	a->pipe_enabled |= b->pipe_enabled;
	a->sprites_enabled |= b->sprites_enabled;
	a->sprites_scaled |= b->sprites_scaled;

	क्रम (level = 0; level <= max_level; level++) अणु
		काष्ठा पूर्णांकel_wm_level *a_wm = &a->wm[level];
		स्थिर काष्ठा पूर्णांकel_wm_level *b_wm = &b->wm[level];

		a_wm->enable &= b_wm->enable;
		a_wm->pri_val = max(a_wm->pri_val, b_wm->pri_val);
		a_wm->spr_val = max(a_wm->spr_val, b_wm->spr_val);
		a_wm->cur_val = max(a_wm->cur_val, b_wm->cur_val);
		a_wm->fbc_val = max(a_wm->fbc_val, b_wm->fbc_val);
	पूर्ण

	/*
	 * We need to make sure that these merged watermark values are
	 * actually a valid configuration themselves.  If they're not,
	 * there's no safe way to transition from the old state to
	 * the new state, so we need to fail the atomic transaction.
	 */
	अगर (!ilk_validate_pipe_wm(dev_priv, a))
		वापस -EINVAL;

	/*
	 * If our पूर्णांकermediate WM are identical to the final WM, then we can
	 * omit the post-vblank programming; only update अगर it's dअगरferent.
	 */
	अगर (स_भेद(a, &newstate->wm.ilk.optimal, माप(*a)) != 0)
		newstate->wm.need_postvbl_update = true;

	वापस 0;
पूर्ण

/*
 * Merge the watermarks from all active pipes क्रम a specअगरic level.
 */
अटल व्योम ilk_merge_wm_level(काष्ठा drm_i915_निजी *dev_priv,
			       पूर्णांक level,
			       काष्ठा पूर्णांकel_wm_level *ret_wm)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc;

	ret_wm->enable = true;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, पूर्णांकel_crtc) अणु
		स्थिर काष्ठा पूर्णांकel_pipe_wm *active = &पूर्णांकel_crtc->wm.active.ilk;
		स्थिर काष्ठा पूर्णांकel_wm_level *wm = &active->wm[level];

		अगर (!active->pipe_enabled)
			जारी;

		/*
		 * The watermark values may have been used in the past,
		 * so we must मुख्यtain them in the रेजिस्टरs क्रम some
		 * समय even अगर the level is now disabled.
		 */
		अगर (!wm->enable)
			ret_wm->enable = false;

		ret_wm->pri_val = max(ret_wm->pri_val, wm->pri_val);
		ret_wm->spr_val = max(ret_wm->spr_val, wm->spr_val);
		ret_wm->cur_val = max(ret_wm->cur_val, wm->cur_val);
		ret_wm->fbc_val = max(ret_wm->fbc_val, wm->fbc_val);
	पूर्ण
पूर्ण

/*
 * Merge all low घातer watermarks क्रम all active pipes.
 */
अटल व्योम ilk_wm_merge(काष्ठा drm_i915_निजी *dev_priv,
			 स्थिर काष्ठा पूर्णांकel_wm_config *config,
			 स्थिर काष्ठा ilk_wm_maximums *max,
			 काष्ठा पूर्णांकel_pipe_wm *merged)
अणु
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	पूर्णांक last_enabled_level = max_level;

	/* ILK/SNB/IVB: LP1+ watermarks only w/ single pipe */
	अगर ((DISPLAY_VER(dev_priv) <= 6 || IS_IVYBRIDGE(dev_priv)) &&
	    config->num_pipes_active > 1)
		last_enabled_level = 0;

	/* ILK: FBC WM must be disabled always */
	merged->fbc_wm_enabled = DISPLAY_VER(dev_priv) >= 6;

	/* merge each WM1+ level */
	क्रम (level = 1; level <= max_level; level++) अणु
		काष्ठा पूर्णांकel_wm_level *wm = &merged->wm[level];

		ilk_merge_wm_level(dev_priv, level, wm);

		अगर (level > last_enabled_level)
			wm->enable = false;
		अन्यथा अगर (!ilk_validate_wm_level(level, max, wm))
			/* make sure all following levels get disabled */
			last_enabled_level = level - 1;

		/*
		 * The spec says it is preferred to disable
		 * FBC WMs instead of disabling a WM level.
		 */
		अगर (wm->fbc_val > max->fbc) अणु
			अगर (wm->enable)
				merged->fbc_wm_enabled = false;
			wm->fbc_val = 0;
		पूर्ण
	पूर्ण

	/* ILK: LP2+ must be disabled when FBC WM is disabled but FBC enabled */
	/*
	 * FIXME this is racy. FBC might get enabled later.
	 * What we should check here is whether FBC can be
	 * enabled someसमय later.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 5) && !merged->fbc_wm_enabled &&
	    पूर्णांकel_fbc_is_active(dev_priv)) अणु
		क्रम (level = 2; level <= max_level; level++) अणु
			काष्ठा पूर्णांकel_wm_level *wm = &merged->wm[level];

			wm->enable = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ilk_wm_lp_to_level(पूर्णांक wm_lp, स्थिर काष्ठा पूर्णांकel_pipe_wm *pipe_wm)
अणु
	/* LP1,LP2,LP3 levels are either 1,2,3 or 1,3,4 */
	वापस wm_lp + (wm_lp >= 2 && pipe_wm->wm[4].enable);
पूर्ण

/* The value we need to program पूर्णांकo the WM_LPx latency field */
अटल अचिन्हित पूर्णांक ilk_wm_lp_latency(काष्ठा drm_i915_निजी *dev_priv,
				      पूर्णांक level)
अणु
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		वापस 2 * level;
	अन्यथा
		वापस dev_priv->wm.pri_latency[level];
पूर्ण

अटल व्योम ilk_compute_wm_results(काष्ठा drm_i915_निजी *dev_priv,
				   स्थिर काष्ठा पूर्णांकel_pipe_wm *merged,
				   क्रमागत पूर्णांकel_ddb_partitioning partitioning,
				   काष्ठा ilk_wm_values *results)
अणु
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc;
	पूर्णांक level, wm_lp;

	results->enable_fbc_wm = merged->fbc_wm_enabled;
	results->partitioning = partitioning;

	/* LP1+ रेजिस्टर values */
	क्रम (wm_lp = 1; wm_lp <= 3; wm_lp++) अणु
		स्थिर काष्ठा पूर्णांकel_wm_level *r;

		level = ilk_wm_lp_to_level(wm_lp, merged);

		r = &merged->wm[level];

		/*
		 * Maपूर्णांकain the watermark values even अगर the level is
		 * disabled. Doing otherwise could cause underruns.
		 */
		results->wm_lp[wm_lp - 1] =
			(ilk_wm_lp_latency(dev_priv, level) << WM1_LP_LATENCY_SHIFT) |
			(r->pri_val << WM1_LP_SR_SHIFT) |
			r->cur_val;

		अगर (r->enable)
			results->wm_lp[wm_lp - 1] |= WM1_LP_SR_EN;

		अगर (DISPLAY_VER(dev_priv) >= 8)
			results->wm_lp[wm_lp - 1] |=
				r->fbc_val << WM1_LP_FBC_SHIFT_BDW;
		अन्यथा
			results->wm_lp[wm_lp - 1] |=
				r->fbc_val << WM1_LP_FBC_SHIFT;

		/*
		 * Always set WM1S_LP_EN when spr_val != 0, even अगर the
		 * level is disabled. Doing otherwise could cause underruns.
		 */
		अगर (DISPLAY_VER(dev_priv) <= 6 && r->spr_val) अणु
			drm_WARN_ON(&dev_priv->drm, wm_lp != 1);
			results->wm_lp_spr[wm_lp - 1] = WM1S_LP_EN | r->spr_val;
		पूर्ण अन्यथा
			results->wm_lp_spr[wm_lp - 1] = r->spr_val;
	पूर्ण

	/* LP0 रेजिस्टर values */
	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, पूर्णांकel_crtc) अणु
		क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
		स्थिर काष्ठा पूर्णांकel_pipe_wm *pipe_wm = &पूर्णांकel_crtc->wm.active.ilk;
		स्थिर काष्ठा पूर्णांकel_wm_level *r = &pipe_wm->wm[0];

		अगर (drm_WARN_ON(&dev_priv->drm, !r->enable))
			जारी;

		results->wm_pipe[pipe] =
			(r->pri_val << WM0_PIPE_PLANE_SHIFT) |
			(r->spr_val << WM0_PIPE_SPRITE_SHIFT) |
			r->cur_val;
	पूर्ण
पूर्ण

/* Find the result with the highest level enabled. Check क्रम enable_fbc_wm in
 * हाल both are at the same level. Prefer r1 in हाल they're the same. */
अटल काष्ठा पूर्णांकel_pipe_wm *
ilk_find_best_result(काष्ठा drm_i915_निजी *dev_priv,
		     काष्ठा पूर्णांकel_pipe_wm *r1,
		     काष्ठा पूर्णांकel_pipe_wm *r2)
अणु
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	पूर्णांक level1 = 0, level2 = 0;

	क्रम (level = 1; level <= max_level; level++) अणु
		अगर (r1->wm[level].enable)
			level1 = level;
		अगर (r2->wm[level].enable)
			level2 = level;
	पूर्ण

	अगर (level1 == level2) अणु
		अगर (r2->fbc_wm_enabled && !r1->fbc_wm_enabled)
			वापस r2;
		अन्यथा
			वापस r1;
	पूर्ण अन्यथा अगर (level1 > level2) अणु
		वापस r1;
	पूर्ण अन्यथा अणु
		वापस r2;
	पूर्ण
पूर्ण

/* dirty bits used to track which watermarks need changes */
#घोषणा WM_सूचीTY_PIPE(pipe) (1 << (pipe))
#घोषणा WM_सूचीTY_LP(wm_lp) (1 << (15 + (wm_lp)))
#घोषणा WM_सूचीTY_LP_ALL (WM_सूचीTY_LP(1) | WM_सूचीTY_LP(2) | WM_सूचीTY_LP(3))
#घोषणा WM_सूचीTY_FBC (1 << 24)
#घोषणा WM_सूचीTY_DDB (1 << 25)

अटल अचिन्हित पूर्णांक ilk_compute_wm_dirty(काष्ठा drm_i915_निजी *dev_priv,
					 स्थिर काष्ठा ilk_wm_values *old,
					 स्थिर काष्ठा ilk_wm_values *new)
अणु
	अचिन्हित पूर्णांक dirty = 0;
	क्रमागत pipe pipe;
	पूर्णांक wm_lp;

	क्रम_each_pipe(dev_priv, pipe) अणु
		अगर (old->wm_pipe[pipe] != new->wm_pipe[pipe]) अणु
			dirty |= WM_सूचीTY_PIPE(pipe);
			/* Must disable LP1+ watermarks too */
			dirty |= WM_सूचीTY_LP_ALL;
		पूर्ण
	पूर्ण

	अगर (old->enable_fbc_wm != new->enable_fbc_wm) अणु
		dirty |= WM_सूचीTY_FBC;
		/* Must disable LP1+ watermarks too */
		dirty |= WM_सूचीTY_LP_ALL;
	पूर्ण

	अगर (old->partitioning != new->partitioning) अणु
		dirty |= WM_सूचीTY_DDB;
		/* Must disable LP1+ watermarks too */
		dirty |= WM_सूचीTY_LP_ALL;
	पूर्ण

	/* LP1+ watermarks alपढ़ोy deemed dirty, no need to जारी */
	अगर (dirty & WM_सूचीTY_LP_ALL)
		वापस dirty;

	/* Find the lowest numbered LP1+ watermark in need of an update... */
	क्रम (wm_lp = 1; wm_lp <= 3; wm_lp++) अणु
		अगर (old->wm_lp[wm_lp - 1] != new->wm_lp[wm_lp - 1] ||
		    old->wm_lp_spr[wm_lp - 1] != new->wm_lp_spr[wm_lp - 1])
			अवरोध;
	पूर्ण

	/* ...and mark it and all higher numbered LP1+ watermarks as dirty */
	क्रम (; wm_lp <= 3; wm_lp++)
		dirty |= WM_सूचीTY_LP(wm_lp);

	वापस dirty;
पूर्ण

अटल bool _ilk_disable_lp_wm(काष्ठा drm_i915_निजी *dev_priv,
			       अचिन्हित पूर्णांक dirty)
अणु
	काष्ठा ilk_wm_values *previous = &dev_priv->wm.hw;
	bool changed = false;

	अगर (dirty & WM_सूचीTY_LP(3) && previous->wm_lp[2] & WM1_LP_SR_EN) अणु
		previous->wm_lp[2] &= ~WM1_LP_SR_EN;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM3_LP_ILK, previous->wm_lp[2]);
		changed = true;
	पूर्ण
	अगर (dirty & WM_सूचीTY_LP(2) && previous->wm_lp[1] & WM1_LP_SR_EN) अणु
		previous->wm_lp[1] &= ~WM1_LP_SR_EN;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM2_LP_ILK, previous->wm_lp[1]);
		changed = true;
	पूर्ण
	अगर (dirty & WM_सूचीTY_LP(1) && previous->wm_lp[0] & WM1_LP_SR_EN) अणु
		previous->wm_lp[0] &= ~WM1_LP_SR_EN;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM1_LP_ILK, previous->wm_lp[0]);
		changed = true;
	पूर्ण

	/*
	 * Don't touch WM1S_LP_EN here.
	 * Doing so could cause underruns.
	 */

	वापस changed;
पूर्ण

/*
 * The spec says we shouldn't write when we don't need, because every ग_लिखो
 * causes WMs to be re-evaluated, expending some घातer.
 */
अटल व्योम ilk_ग_लिखो_wm_values(काष्ठा drm_i915_निजी *dev_priv,
				काष्ठा ilk_wm_values *results)
अणु
	काष्ठा ilk_wm_values *previous = &dev_priv->wm.hw;
	अचिन्हित पूर्णांक dirty;
	u32 val;

	dirty = ilk_compute_wm_dirty(dev_priv, previous, results);
	अगर (!dirty)
		वापस;

	_ilk_disable_lp_wm(dev_priv, dirty);

	अगर (dirty & WM_सूचीTY_PIPE(PIPE_A))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM0_PIPE_ILK(PIPE_A), results->wm_pipe[0]);
	अगर (dirty & WM_सूचीTY_PIPE(PIPE_B))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM0_PIPE_ILK(PIPE_B), results->wm_pipe[1]);
	अगर (dirty & WM_सूचीTY_PIPE(PIPE_C))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM0_PIPE_ILK(PIPE_C), results->wm_pipe[2]);

	अगर (dirty & WM_सूचीTY_DDB) अणु
		अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) अणु
			val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM_MISC);
			अगर (results->partitioning == INTEL_DDB_PART_1_2)
				val &= ~WM_MISC_DATA_PARTITION_5_6;
			अन्यथा
				val |= WM_MISC_DATA_PARTITION_5_6;
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM_MISC, val);
		पूर्ण अन्यथा अणु
			val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL2);
			अगर (results->partitioning == INTEL_DDB_PART_1_2)
				val &= ~DISP_DATA_PARTITION_5_6;
			अन्यथा
				val |= DISP_DATA_PARTITION_5_6;
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL2, val);
		पूर्ण
	पूर्ण

	अगर (dirty & WM_सूचीTY_FBC) अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL);
		अगर (results->enable_fbc_wm)
			val &= ~DISP_FBC_WM_DIS;
		अन्यथा
			val |= DISP_FBC_WM_DIS;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, val);
	पूर्ण

	अगर (dirty & WM_सूचीTY_LP(1) &&
	    previous->wm_lp_spr[0] != results->wm_lp_spr[0])
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM1S_LP_ILK, results->wm_lp_spr[0]);

	अगर (DISPLAY_VER(dev_priv) >= 7) अणु
		अगर (dirty & WM_सूचीTY_LP(2) && previous->wm_lp_spr[1] != results->wm_lp_spr[1])
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM2S_LP_IVB, results->wm_lp_spr[1]);
		अगर (dirty & WM_सूचीTY_LP(3) && previous->wm_lp_spr[2] != results->wm_lp_spr[2])
			पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM3S_LP_IVB, results->wm_lp_spr[2]);
	पूर्ण

	अगर (dirty & WM_सूचीTY_LP(1) && previous->wm_lp[0] != results->wm_lp[0])
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM1_LP_ILK, results->wm_lp[0]);
	अगर (dirty & WM_सूचीTY_LP(2) && previous->wm_lp[1] != results->wm_lp[1])
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM2_LP_ILK, results->wm_lp[1]);
	अगर (dirty & WM_सूचीTY_LP(3) && previous->wm_lp[2] != results->wm_lp[2])
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM3_LP_ILK, results->wm_lp[2]);

	dev_priv->wm.hw = *results;
पूर्ण

bool ilk_disable_lp_wm(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस _ilk_disable_lp_wm(dev_priv, WM_सूचीTY_LP_ALL);
पूर्ण

u8 पूर्णांकel_enabled_dbuf_slices_mask(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक i;
	पूर्णांक max_slices = INTEL_INFO(dev_priv)->num_supported_dbuf_slices;
	u8 enabled_slices_mask = 0;

	क्रम (i = 0; i < max_slices; i++) अणु
		अगर (पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DBUF_CTL_S(i)) & DBUF_POWER_STATE)
			enabled_slices_mask |= BIT(i);
	पूर्ण

	वापस enabled_slices_mask;
पूर्ण

/*
 * FIXME: We still करोn't have the proper code detect अगर we need to apply the WA,
 * so assume we'll always need it in order to aव्योम underruns.
 */
अटल bool skl_needs_memory_bw_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस IS_GEN9_BC(dev_priv) || IS_BROXTON(dev_priv);
पूर्ण

अटल bool
पूर्णांकel_has_sagv(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस (IS_GEN9_BC(dev_priv) || DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv)) &&
		dev_priv->sagv_status != I915_SAGV_NOT_CONTROLLED;
पूर्ण

अटल व्योम
skl_setup_sagv_block_समय(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		u32 val = 0;
		पूर्णांक ret;

		ret = sandybridge_pcode_पढ़ो(dev_priv,
					     GEN12_PCODE_READ_SAGV_BLOCK_TIME_US,
					     &val, शून्य);
		अगर (!ret) अणु
			dev_priv->sagv_block_समय_us = val;
			वापस;
		पूर्ण

		drm_dbg(&dev_priv->drm, "Couldn't read SAGV block time!\n");
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		dev_priv->sagv_block_समय_us = 10;
		वापस;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 10)) अणु
		dev_priv->sagv_block_समय_us = 20;
		वापस;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 9)) अणु
		dev_priv->sagv_block_समय_us = 30;
		वापस;
	पूर्ण अन्यथा अणु
		MISSING_CASE(DISPLAY_VER(dev_priv));
	पूर्ण

	/* Default to an unusable block समय */
	dev_priv->sagv_block_समय_us = -1;
पूर्ण

/*
 * SAGV dynamically adjusts the प्रणाली agent voltage and घड़ी frequencies
 * depending on घातer and perक्रमmance requirements. The display engine access
 * to प्रणाली memory is blocked during the adjusपंचांगent समय. Because of the
 * blocking समय, having this enabled can cause full प्रणाली hangs and/or pipe
 * underruns अगर we करोn't meet all of the following requirements:
 *
 *  - <= 1 pipe enabled
 *  - All planes can enable watermarks क्रम latencies >= SAGV engine block समय
 *  - We're not using an पूर्णांकerlaced display configuration
 */
अटल पूर्णांक
पूर्णांकel_enable_sagv(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (!पूर्णांकel_has_sagv(dev_priv))
		वापस 0;

	अगर (dev_priv->sagv_status == I915_SAGV_ENABLED)
		वापस 0;

	drm_dbg_kms(&dev_priv->drm, "Enabling SAGV\n");
	ret = sandybridge_pcode_ग_लिखो(dev_priv, GEN9_PCODE_SAGV_CONTROL,
				      GEN9_SAGV_ENABLE);

	/* We करोn't need to रुको क्रम SAGV when enabling */

	/*
	 * Some skl प्रणालीs, pre-release machines in particular,
	 * करोn't actually have SAGV.
	 */
	अगर (IS_SKYLAKE(dev_priv) && ret == -ENXIO) अणु
		drm_dbg(&dev_priv->drm, "No SAGV found on system, ignoring\n");
		dev_priv->sagv_status = I915_SAGV_NOT_CONTROLLED;
		वापस 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		drm_err(&dev_priv->drm, "Failed to enable SAGV\n");
		वापस ret;
	पूर्ण

	dev_priv->sagv_status = I915_SAGV_ENABLED;
	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_disable_sagv(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	अगर (!पूर्णांकel_has_sagv(dev_priv))
		वापस 0;

	अगर (dev_priv->sagv_status == I915_SAGV_DISABLED)
		वापस 0;

	drm_dbg_kms(&dev_priv->drm, "Disabling SAGV\n");
	/* bspec says to keep retrying क्रम at least 1 ms */
	ret = skl_pcode_request(dev_priv, GEN9_PCODE_SAGV_CONTROL,
				GEN9_SAGV_DISABLE,
				GEN9_SAGV_IS_DISABLED, GEN9_SAGV_IS_DISABLED,
				1);
	/*
	 * Some skl प्रणालीs, pre-release machines in particular,
	 * करोn't actually have SAGV.
	 */
	अगर (IS_SKYLAKE(dev_priv) && ret == -ENXIO) अणु
		drm_dbg(&dev_priv->drm, "No SAGV found on system, ignoring\n");
		dev_priv->sagv_status = I915_SAGV_NOT_CONTROLLED;
		वापस 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		drm_err(&dev_priv->drm, "Failed to disable SAGV (%d)\n", ret);
		वापस ret;
	पूर्ण

	dev_priv->sagv_status = I915_SAGV_DISABLED;
	वापस 0;
पूर्ण

व्योम पूर्णांकel_sagv_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_bw_state *new_bw_state;
	स्थिर काष्ठा पूर्णांकel_bw_state *old_bw_state;
	u32 new_mask = 0;

	/*
	 * Just वापस अगर we can't control SAGV or don't have it.
	 * This is dअगरferent from situation when we have SAGV but just can't
	 * afक्रमd it due to DBuf limitation - in हाल अगर SAGV is completely
	 * disabled in a BIOS, we are not even allowed to send a PCode request,
	 * as it will throw an error. So have to check it here.
	 */
	अगर (!पूर्णांकel_has_sagv(dev_priv))
		वापस;

	new_bw_state = पूर्णांकel_atomic_get_new_bw_state(state);
	अगर (!new_bw_state)
		वापस;

	अगर (DISPLAY_VER(dev_priv) < 11 && !पूर्णांकel_can_enable_sagv(dev_priv, new_bw_state)) अणु
		पूर्णांकel_disable_sagv(dev_priv);
		वापस;
	पूर्ण

	old_bw_state = पूर्णांकel_atomic_get_old_bw_state(state);
	/*
	 * Nothing to mask
	 */
	अगर (new_bw_state->qgv_poपूर्णांकs_mask == old_bw_state->qgv_poपूर्णांकs_mask)
		वापस;

	new_mask = old_bw_state->qgv_poपूर्णांकs_mask | new_bw_state->qgv_poपूर्णांकs_mask;

	/*
	 * If new mask is zero - means there is nothing to mask,
	 * we can only unmask, which should be करोne in unmask.
	 */
	अगर (!new_mask)
		वापस;

	/*
	 * Restrict required qgv poपूर्णांकs beक्रमe updating the configuration.
	 * According to BSpec we can't mask and unmask qgv poपूर्णांकs at the same
	 * समय. Also masking should be करोne beक्रमe updating the configuration
	 * and unmasking afterwards.
	 */
	icl_pcode_restrict_qgv_poपूर्णांकs(dev_priv, new_mask);
पूर्ण

व्योम पूर्णांकel_sagv_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_bw_state *new_bw_state;
	स्थिर काष्ठा पूर्णांकel_bw_state *old_bw_state;
	u32 new_mask = 0;

	/*
	 * Just वापस अगर we can't control SAGV or don't have it.
	 * This is dअगरferent from situation when we have SAGV but just can't
	 * afक्रमd it due to DBuf limitation - in हाल अगर SAGV is completely
	 * disabled in a BIOS, we are not even allowed to send a PCode request,
	 * as it will throw an error. So have to check it here.
	 */
	अगर (!पूर्णांकel_has_sagv(dev_priv))
		वापस;

	new_bw_state = पूर्णांकel_atomic_get_new_bw_state(state);
	अगर (!new_bw_state)
		वापस;

	अगर (DISPLAY_VER(dev_priv) < 11 && पूर्णांकel_can_enable_sagv(dev_priv, new_bw_state)) अणु
		पूर्णांकel_enable_sagv(dev_priv);
		वापस;
	पूर्ण

	old_bw_state = पूर्णांकel_atomic_get_old_bw_state(state);
	/*
	 * Nothing to unmask
	 */
	अगर (new_bw_state->qgv_poपूर्णांकs_mask == old_bw_state->qgv_poपूर्णांकs_mask)
		वापस;

	new_mask = new_bw_state->qgv_poपूर्णांकs_mask;

	/*
	 * Allow required qgv poपूर्णांकs after updating the configuration.
	 * According to BSpec we can't mask and unmask qgv poपूर्णांकs at the same
	 * समय. Also masking should be करोne beक्रमe updating the configuration
	 * and unmasking afterwards.
	 */
	icl_pcode_restrict_qgv_poपूर्णांकs(dev_priv, new_mask);
पूर्ण

अटल bool skl_crtc_can_enable_sagv(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत plane_id plane_id;
	पूर्णांक max_level = पूर्णांक_उच्च;

	अगर (!पूर्णांकel_has_sagv(dev_priv))
		वापस false;

	अगर (!crtc_state->hw.active)
		वापस true;

	अगर (crtc_state->hw.pipe_mode.flags & DRM_MODE_FLAG_INTERLACE)
		वापस false;

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		स्थिर काष्ठा skl_plane_wm *wm =
			&crtc_state->wm.skl.optimal.planes[plane_id];
		पूर्णांक level;

		/* Skip this plane अगर it's not enabled */
		अगर (!wm->wm[0].enable)
			जारी;

		/* Find the highest enabled wm level क्रम this plane */
		क्रम (level = ilk_wm_max_level(dev_priv);
		     !wm->wm[level].enable; --level)
		     अणु पूर्ण

		/* Highest common enabled wm level क्रम all planes */
		max_level = min(level, max_level);
	पूर्ण

	/* No enabled planes? */
	अगर (max_level == पूर्णांक_उच्च)
		वापस true;

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		स्थिर काष्ठा skl_plane_wm *wm =
			&crtc_state->wm.skl.optimal.planes[plane_id];

		/*
		 * All enabled planes must have enabled a common wm level that
		 * can tolerate memory latencies higher than sagv_block_समय_us
		 */
		अगर (wm->wm[0].enable && !wm->wm[max_level].can_sagv)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tgl_crtc_can_enable_sagv(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत plane_id plane_id;

	अगर (!crtc_state->hw.active)
		वापस true;

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		स्थिर काष्ठा skl_plane_wm *wm =
			&crtc_state->wm.skl.optimal.planes[plane_id];

		अगर (wm->wm[0].enable && !wm->sagv.wm0.enable)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool पूर्णांकel_crtc_can_enable_sagv(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस tgl_crtc_can_enable_sagv(crtc_state);
	अन्यथा
		वापस skl_crtc_can_enable_sagv(crtc_state);
पूर्ण

bool पूर्णांकel_can_enable_sagv(काष्ठा drm_i915_निजी *dev_priv,
			   स्थिर काष्ठा पूर्णांकel_bw_state *bw_state)
अणु
	अगर (DISPLAY_VER(dev_priv) < 11 &&
	    bw_state->active_pipes && !is_घातer_of_2(bw_state->active_pipes))
		वापस false;

	वापस bw_state->pipe_sagv_reject == 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_compute_sagv_mask(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	पूर्णांक ret;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	काष्ठा पूर्णांकel_bw_state *new_bw_state = शून्य;
	स्थिर काष्ठा पूर्णांकel_bw_state *old_bw_state = शून्य;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc,
					 new_crtc_state, i) अणु
		new_bw_state = पूर्णांकel_atomic_get_bw_state(state);
		अगर (IS_ERR(new_bw_state))
			वापस PTR_ERR(new_bw_state);

		old_bw_state = पूर्णांकel_atomic_get_old_bw_state(state);

		अगर (पूर्णांकel_crtc_can_enable_sagv(new_crtc_state))
			new_bw_state->pipe_sagv_reject &= ~BIT(crtc->pipe);
		अन्यथा
			new_bw_state->pipe_sagv_reject |= BIT(crtc->pipe);
	पूर्ण

	अगर (!new_bw_state)
		वापस 0;

	new_bw_state->active_pipes =
		पूर्णांकel_calc_active_pipes(state, old_bw_state->active_pipes);

	अगर (new_bw_state->active_pipes != old_bw_state->active_pipes) अणु
		ret = पूर्णांकel_atomic_lock_global_state(&new_bw_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc,
					 new_crtc_state, i) अणु
		काष्ठा skl_pipe_wm *pipe_wm = &new_crtc_state->wm.skl.optimal;

		/*
		 * We store use_sagv_wm in the crtc state rather than relying on
		 * that bw state since we have no convenient way to get at the
		 * latter from the plane commit hooks (especially in the legacy
		 * cursor हाल)
		 */
		pipe_wm->use_sagv_wm = DISPLAY_VER(dev_priv) >= 12 &&
				       पूर्णांकel_can_enable_sagv(dev_priv, new_bw_state);
	पूर्ण

	अगर (पूर्णांकel_can_enable_sagv(dev_priv, new_bw_state) !=
	    पूर्णांकel_can_enable_sagv(dev_priv, old_bw_state)) अणु
		ret = पूर्णांकel_atomic_serialize_global_state(&new_bw_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (new_bw_state->pipe_sagv_reject != old_bw_state->pipe_sagv_reject) अणु
		ret = पूर्णांकel_atomic_lock_global_state(&new_bw_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dbuf_size(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ddb_size = INTEL_INFO(dev_priv)->ddb_size;

	drm_WARN_ON(&dev_priv->drm, ddb_size == 0);

	अगर (DISPLAY_VER(dev_priv) < 11)
		वापस ddb_size - 4; /* 4 blocks क्रम bypass path allocation */

	वापस ddb_size;
पूर्ण

अटल पूर्णांक पूर्णांकel_dbuf_slice_size(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस पूर्णांकel_dbuf_size(dev_priv) /
		INTEL_INFO(dev_priv)->num_supported_dbuf_slices;
पूर्ण

अटल व्योम
skl_ddb_entry_क्रम_slices(काष्ठा drm_i915_निजी *dev_priv, u8 slice_mask,
			 काष्ठा skl_ddb_entry *ddb)
अणु
	पूर्णांक slice_size = पूर्णांकel_dbuf_slice_size(dev_priv);

	अगर (!slice_mask) अणु
		ddb->start = 0;
		ddb->end = 0;
		वापस;
	पूर्ण

	ddb->start = (ffs(slice_mask) - 1) * slice_size;
	ddb->end = fls(slice_mask) * slice_size;

	WARN_ON(ddb->start >= ddb->end);
	WARN_ON(ddb->end > पूर्णांकel_dbuf_size(dev_priv));
पूर्ण

u32 skl_ddb_dbuf_slice_mask(काष्ठा drm_i915_निजी *dev_priv,
			    स्थिर काष्ठा skl_ddb_entry *entry)
अणु
	u32 slice_mask = 0;
	u16 ddb_size = पूर्णांकel_dbuf_size(dev_priv);
	u16 num_supported_slices = INTEL_INFO(dev_priv)->num_supported_dbuf_slices;
	u16 slice_size = ddb_size / num_supported_slices;
	u16 start_slice;
	u16 end_slice;

	अगर (!skl_ddb_entry_size(entry))
		वापस 0;

	start_slice = entry->start / slice_size;
	end_slice = (entry->end - 1) / slice_size;

	/*
	 * Per plane DDB entry can in a really worst हाल be on multiple slices
	 * but single entry is anyway contigious.
	 */
	जबतक (start_slice <= end_slice) अणु
		slice_mask |= BIT(start_slice);
		start_slice++;
	पूर्ण

	वापस slice_mask;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_crtc_ddb_weight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_display_mode *pipe_mode = &crtc_state->hw.pipe_mode;
	पूर्णांक hdisplay, vdisplay;

	अगर (!crtc_state->hw.active)
		वापस 0;

	/*
	 * Watermark/ddb requirement highly depends upon width of the
	 * framebuffer, So instead of allocating DDB equally among pipes
	 * distribute DDB based on resolution/width of the display.
	 */
	drm_mode_get_hv_timing(pipe_mode, &hdisplay, &vdisplay);

	वापस hdisplay;
पूर्ण

अटल व्योम पूर्णांकel_crtc_dbuf_weights(स्थिर काष्ठा पूर्णांकel_dbuf_state *dbuf_state,
				    क्रमागत pipe क्रम_pipe,
				    अचिन्हित पूर्णांक *weight_start,
				    अचिन्हित पूर्णांक *weight_end,
				    अचिन्हित पूर्णांक *weight_total)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(dbuf_state->base.state->base.dev);
	क्रमागत pipe pipe;

	*weight_start = 0;
	*weight_end = 0;
	*weight_total = 0;

	क्रम_each_pipe(dev_priv, pipe) अणु
		पूर्णांक weight = dbuf_state->weight[pipe];

		/*
		 * Do not account pipes using other slice sets
		 * luckily as of current BSpec slice sets करो not partially
		 * पूर्णांकersect(pipes share either same one slice or same slice set
		 * i.e no partial पूर्णांकersection), so it is enough to check क्रम
		 * equality क्रम now.
		 */
		अगर (dbuf_state->slices[pipe] != dbuf_state->slices[क्रम_pipe])
			जारी;

		*weight_total += weight;
		अगर (pipe < क्रम_pipe) अणु
			*weight_start += weight;
			*weight_end += weight;
		पूर्ण अन्यथा अगर (pipe == क्रम_pipe) अणु
			*weight_end += weight;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
skl_crtc_allocate_ddb(काष्ठा पूर्णांकel_atomic_state *state, काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	अचिन्हित पूर्णांक weight_total, weight_start, weight_end;
	स्थिर काष्ठा पूर्णांकel_dbuf_state *old_dbuf_state =
		पूर्णांकel_atomic_get_old_dbuf_state(state);
	काष्ठा पूर्णांकel_dbuf_state *new_dbuf_state =
		पूर्णांकel_atomic_get_new_dbuf_state(state);
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा skl_ddb_entry ddb_slices;
	क्रमागत pipe pipe = crtc->pipe;
	u32 ddb_range_size;
	u32 dbuf_slice_mask;
	u32 start, end;
	पूर्णांक ret;

	अगर (new_dbuf_state->weight[pipe] == 0) अणु
		new_dbuf_state->ddb[pipe].start = 0;
		new_dbuf_state->ddb[pipe].end = 0;
		जाओ out;
	पूर्ण

	dbuf_slice_mask = new_dbuf_state->slices[pipe];

	skl_ddb_entry_क्रम_slices(dev_priv, dbuf_slice_mask, &ddb_slices);
	ddb_range_size = skl_ddb_entry_size(&ddb_slices);

	पूर्णांकel_crtc_dbuf_weights(new_dbuf_state, pipe,
				&weight_start, &weight_end, &weight_total);

	start = ddb_range_size * weight_start / weight_total;
	end = ddb_range_size * weight_end / weight_total;

	new_dbuf_state->ddb[pipe].start = ddb_slices.start + start;
	new_dbuf_state->ddb[pipe].end = ddb_slices.start + end;

out:
	अगर (skl_ddb_entry_equal(&old_dbuf_state->ddb[pipe],
				&new_dbuf_state->ddb[pipe]))
		वापस 0;

	ret = पूर्णांकel_atomic_lock_global_state(&new_dbuf_state->base);
	अगर (ret)
		वापस ret;

	crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	crtc_state->wm.skl.ddb = new_dbuf_state->ddb[pipe];

	drm_dbg_kms(&dev_priv->drm,
		    "[CRTC:%d:%s] dbuf slices 0x%x -> 0x%x, ddb (%d - %d) -> (%d - %d), active pipes 0x%x -> 0x%x\n",
		    crtc->base.base.id, crtc->base.name,
		    old_dbuf_state->slices[pipe], new_dbuf_state->slices[pipe],
		    old_dbuf_state->ddb[pipe].start, old_dbuf_state->ddb[pipe].end,
		    new_dbuf_state->ddb[pipe].start, new_dbuf_state->ddb[pipe].end,
		    old_dbuf_state->active_pipes, new_dbuf_state->active_pipes);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_compute_wm_params(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 पूर्णांक width, स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				 u64 modअगरier, अचिन्हित पूर्णांक rotation,
				 u32 plane_pixel_rate, काष्ठा skl_wm_params *wp,
				 पूर्णांक color_plane);
अटल व्योम skl_compute_plane_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 पूर्णांक level,
				 अचिन्हित पूर्णांक latency,
				 स्थिर काष्ठा skl_wm_params *wp,
				 स्थिर काष्ठा skl_wm_level *result_prev,
				 काष्ठा skl_wm_level *result /* out */);

अटल अचिन्हित पूर्णांक
skl_cursor_allocation(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      पूर्णांक num_active)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	काष्ठा skl_wm_level wm = अणुपूर्ण;
	पूर्णांक ret, min_ddb_alloc = 0;
	काष्ठा skl_wm_params wp;

	ret = skl_compute_wm_params(crtc_state, 256,
				    drm_क्रमmat_info(DRM_FORMAT_ARGB8888),
				    DRM_FORMAT_MOD_LINEAR,
				    DRM_MODE_ROTATE_0,
				    crtc_state->pixel_rate, &wp, 0);
	drm_WARN_ON(&dev_priv->drm, ret);

	क्रम (level = 0; level <= max_level; level++) अणु
		अचिन्हित पूर्णांक latency = dev_priv->wm.skl_latency[level];

		skl_compute_plane_wm(crtc_state, level, latency, &wp, &wm, &wm);
		अगर (wm.min_ddb_alloc == U16_MAX)
			अवरोध;

		min_ddb_alloc = wm.min_ddb_alloc;
	पूर्ण

	वापस max(num_active == 1 ? 32 : 8, min_ddb_alloc);
पूर्ण

अटल व्योम skl_ddb_entry_init_from_hw(काष्ठा drm_i915_निजी *dev_priv,
				       काष्ठा skl_ddb_entry *entry, u32 reg)
अणु

	entry->start = reg & DDB_ENTRY_MASK;
	entry->end = (reg >> DDB_ENTRY_END_SHIFT) & DDB_ENTRY_MASK;

	अगर (entry->end)
		entry->end += 1;
पूर्ण

अटल व्योम
skl_ddb_get_hw_plane_state(काष्ठा drm_i915_निजी *dev_priv,
			   स्थिर क्रमागत pipe pipe,
			   स्थिर क्रमागत plane_id plane_id,
			   काष्ठा skl_ddb_entry *ddb_y,
			   काष्ठा skl_ddb_entry *ddb_uv)
अणु
	u32 val, val2;
	u32 fourcc = 0;

	/* Cursor करोesn't support NV12/planar, so no extra calculation needed */
	अगर (plane_id == PLANE_CURSOR) अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CUR_BUF_CFG(pipe));
		skl_ddb_entry_init_from_hw(dev_priv, ddb_y, val);
		वापस;
	पूर्ण

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PLANE_CTL(pipe, plane_id));

	/* No DDB allocated क्रम disabled planes */
	अगर (val & PLANE_CTL_ENABLE)
		fourcc = skl_क्रमmat_to_fourcc(val & PLANE_CTL_FORMAT_MASK,
					      val & PLANE_CTL_ORDER_RGBX,
					      val & PLANE_CTL_ALPHA_MASK);

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PLANE_BUF_CFG(pipe, plane_id));
		skl_ddb_entry_init_from_hw(dev_priv, ddb_y, val);
	पूर्ण अन्यथा अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PLANE_BUF_CFG(pipe, plane_id));
		val2 = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PLANE_NV12_BUF_CFG(pipe, plane_id));

		अगर (fourcc &&
		    drm_क्रमmat_info_is_yuv_semiplanar(drm_क्रमmat_info(fourcc)))
			swap(val, val2);

		skl_ddb_entry_init_from_hw(dev_priv, ddb_y, val);
		skl_ddb_entry_init_from_hw(dev_priv, ddb_uv, val2);
	पूर्ण
पूर्ण

व्योम skl_pipe_ddb_get_hw_state(काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा skl_ddb_entry *ddb_y,
			       काष्ठा skl_ddb_entry *ddb_uv)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत plane_id plane_id;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस;

	क्रम_each_plane_id_on_crtc(crtc, plane_id)
		skl_ddb_get_hw_plane_state(dev_priv, pipe,
					   plane_id,
					   &ddb_y[plane_id],
					   &ddb_uv[plane_id]);

	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);
पूर्ण

/*
 * Determines the करोwnscale amount of a plane क्रम the purposes of watermark calculations.
 * The bspec defines करोwnscale amount as:
 *
 * """
 * Horizontal करोwn scale amount = maximum[1, Horizontal source size /
 *                                           Horizontal destination size]
 * Vertical करोwn scale amount = maximum[1, Vertical source size /
 *                                         Vertical destination size]
 * Total करोwn scale amount = Horizontal करोwn scale amount *
 *                           Vertical करोwn scale amount
 * """
 *
 * Return value is provided in 16.16 fixed poपूर्णांक क्रमm to retain fractional part.
 * Caller should take care of भागiding & rounding off the value.
 */
अटल uपूर्णांक_fixed_16_16_t
skl_plane_करोwnscale_amount(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	u32 src_w, src_h, dst_w, dst_h;
	uपूर्णांक_fixed_16_16_t fp_w_ratio, fp_h_ratio;
	uपूर्णांक_fixed_16_16_t करोwnscale_h, करोwnscale_w;

	अगर (drm_WARN_ON(&dev_priv->drm,
			!पूर्णांकel_wm_plane_visible(crtc_state, plane_state)))
		वापस u32_to_fixed16(0);

	/*
	 * Src coordinates are alपढ़ोy rotated by 270 degrees क्रम
	 * the 90/270 degree plane rotation हालs (to match the
	 * GTT mapping), hence no need to account क्रम rotation here.
	 *
	 * n.b., src is 16.16 fixed poपूर्णांक, dst is whole पूर्णांकeger.
	 */
	src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	src_h = drm_rect_height(&plane_state->uapi.src) >> 16;
	dst_w = drm_rect_width(&plane_state->uapi.dst);
	dst_h = drm_rect_height(&plane_state->uapi.dst);

	fp_w_ratio = भाग_fixed16(src_w, dst_w);
	fp_h_ratio = भाग_fixed16(src_h, dst_h);
	करोwnscale_w = max_fixed16(fp_w_ratio, u32_to_fixed16(1));
	करोwnscale_h = max_fixed16(fp_h_ratio, u32_to_fixed16(1));

	वापस mul_fixed16(करोwnscale_w, करोwnscale_h);
पूर्ण

काष्ठा dbuf_slice_conf_entry अणु
	u8 active_pipes;
	u8 dbuf_mask[I915_MAX_PIPES];
पूर्ण;

/*
 * Table taken from Bspec 12716
 * Pipes करो have some preferred DBuf slice affinity,
 * plus there are some hardcoded requirements on how
 * those should be distributed क्रम multipipe scenarios.
 * For more DBuf slices algorithm can get even more messy
 * and less पढ़ोable, so decided to use a table almost
 * as is from BSpec itself - that way it is at least easier
 * to compare, change and check.
 */
अटल स्थिर काष्ठा dbuf_slice_conf_entry icl_allowed_dbufs[] =
/* Autogenerated with igt/tools/पूर्णांकel_dbuf_map tool: */
अणु
	अणु
		.active_pipes = BIT(PIPE_A),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_B),
		.dbuf_mask = अणु
			[PIPE_B] = BIT(DBUF_S1),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_B),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_B] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_B) | BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Table taken from Bspec 49255
 * Pipes करो have some preferred DBuf slice affinity,
 * plus there are some hardcoded requirements on how
 * those should be distributed क्रम multipipe scenarios.
 * For more DBuf slices algorithm can get even more messy
 * and less पढ़ोable, so decided to use a table almost
 * as is from BSpec itself - that way it is at least easier
 * to compare, change and check.
 */
अटल स्थिर काष्ठा dbuf_slice_conf_entry tgl_allowed_dbufs[] =
/* Autogenerated with igt/tools/पूर्णांकel_dbuf_map tool: */
अणु
	अणु
		.active_pipes = BIT(PIPE_A),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1) | BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_B),
		.dbuf_mask = अणु
			[PIPE_B] = BIT(DBUF_S1) | BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_B),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S2),
			[PIPE_B] = BIT(DBUF_S1),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_C] = BIT(DBUF_S2) | BIT(DBUF_S1),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_B) | BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_D] = BIT(DBUF_S2) | BIT(DBUF_S1),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_B) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_C) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_C] = BIT(DBUF_S1),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_C) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणु
		.active_pipes = BIT(PIPE_A) | BIT(PIPE_B) | BIT(PIPE_C) | BIT(PIPE_D),
		.dbuf_mask = अणु
			[PIPE_A] = BIT(DBUF_S1),
			[PIPE_B] = BIT(DBUF_S1),
			[PIPE_C] = BIT(DBUF_S2),
			[PIPE_D] = BIT(DBUF_S2),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल u8 compute_dbuf_slices(क्रमागत pipe pipe, u8 active_pipes,
			      स्थिर काष्ठा dbuf_slice_conf_entry *dbuf_slices)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dbuf_slices[i].active_pipes; i++) अणु
		अगर (dbuf_slices[i].active_pipes == active_pipes)
			वापस dbuf_slices[i].dbuf_mask[pipe];
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function finds an entry with same enabled pipe configuration and
 * वापसs correspondent DBuf slice mask as stated in BSpec क्रम particular
 * platक्रमm.
 */
अटल u8 icl_compute_dbuf_slices(क्रमागत pipe pipe, u8 active_pipes)
अणु
	/*
	 * FIXME: For ICL this is still a bit unclear as prev BSpec revision
	 * required calculating "pipe ratio" in order to determine
	 * अगर one or two slices can be used क्रम single pipe configurations
	 * as additional स्थिरraपूर्णांक to the existing table.
	 * However based on recent info, it should be not "pipe ratio"
	 * but rather ratio between pixel_rate and cdclk with additional
	 * स्थिरants, so क्रम now we are using only table until this is
	 * clarअगरied. Also this is the reason why crtc_state param is
	 * still here - we will need it once those additional स्थिरraपूर्णांकs
	 * pop up.
	 */
	वापस compute_dbuf_slices(pipe, active_pipes, icl_allowed_dbufs);
पूर्ण

अटल u8 tgl_compute_dbuf_slices(क्रमागत pipe pipe, u8 active_pipes)
अणु
	वापस compute_dbuf_slices(pipe, active_pipes, tgl_allowed_dbufs);
पूर्ण

अटल u8 skl_compute_dbuf_slices(काष्ठा पूर्णांकel_crtc *crtc, u8 active_pipes)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	अगर (IS_DISPLAY_VER(dev_priv, 12))
		वापस tgl_compute_dbuf_slices(pipe, active_pipes);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11))
		वापस icl_compute_dbuf_slices(pipe, active_pipes);
	/*
	 * For anything अन्यथा just वापस one slice yet.
	 * Should be extended क्रम other platक्रमms.
	 */
	वापस active_pipes & BIT(pipe) ? BIT(DBUF_S1) : 0;
पूर्ण

अटल u64
skl_plane_relative_data_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			     पूर्णांक color_plane)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	u32 data_rate;
	u32 width = 0, height = 0;
	uपूर्णांक_fixed_16_16_t करोwn_scale_amount;
	u64 rate;

	अगर (!plane_state->uapi.visible)
		वापस 0;

	अगर (plane->id == PLANE_CURSOR)
		वापस 0;

	अगर (color_plane == 1 &&
	    !पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier))
		वापस 0;

	/*
	 * Src coordinates are alपढ़ोy rotated by 270 degrees क्रम
	 * the 90/270 degree plane rotation हालs (to match the
	 * GTT mapping), hence no need to account क्रम rotation here.
	 */
	width = drm_rect_width(&plane_state->uapi.src) >> 16;
	height = drm_rect_height(&plane_state->uapi.src) >> 16;

	/* UV plane करोes 1/2 pixel sub-sampling */
	अगर (color_plane == 1) अणु
		width /= 2;
		height /= 2;
	पूर्ण

	data_rate = width * height;

	करोwn_scale_amount = skl_plane_करोwnscale_amount(crtc_state, plane_state);

	rate = mul_round_up_u32_fixed16(data_rate, करोwn_scale_amount);

	rate *= fb->क्रमmat->cpp[color_plane];
	वापस rate;
पूर्ण

अटल u64
skl_get_total_relative_data_rate(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	u64 total_data_rate = 0;
	क्रमागत plane_id plane_id;
	पूर्णांक i;

	/* Calculate and cache data rate क्रम each plane */
	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->pipe != crtc->pipe)
			जारी;

		plane_id = plane->id;

		/* packed/y */
		crtc_state->plane_data_rate[plane_id] =
			skl_plane_relative_data_rate(crtc_state, plane_state, 0);

		/* uv-plane */
		crtc_state->uv_plane_data_rate[plane_id] =
			skl_plane_relative_data_rate(crtc_state, plane_state, 1);
	पूर्ण

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		total_data_rate += crtc_state->plane_data_rate[plane_id];
		total_data_rate += crtc_state->uv_plane_data_rate[plane_id];
	पूर्ण

	वापस total_data_rate;
पूर्ण

अटल u64
icl_get_total_relative_data_rate(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	u64 total_data_rate = 0;
	क्रमागत plane_id plane_id;
	पूर्णांक i;

	/* Calculate and cache data rate क्रम each plane */
	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->pipe != crtc->pipe)
			जारी;

		plane_id = plane->id;

		अगर (!plane_state->planar_linked_plane) अणु
			crtc_state->plane_data_rate[plane_id] =
				skl_plane_relative_data_rate(crtc_state, plane_state, 0);
		पूर्ण अन्यथा अणु
			क्रमागत plane_id y_plane_id;

			/*
			 * The slave plane might not iterate in
			 * पूर्णांकel_atomic_crtc_state_क्रम_each_plane_state(),
			 * and needs the master plane state which may be
			 * शून्य अगर we try get_new_plane_state(), so we
			 * always calculate from the master.
			 */
			अगर (plane_state->planar_slave)
				जारी;

			/* Y plane rate is calculated on the slave */
			y_plane_id = plane_state->planar_linked_plane->id;
			crtc_state->plane_data_rate[y_plane_id] =
				skl_plane_relative_data_rate(crtc_state, plane_state, 0);

			crtc_state->plane_data_rate[plane_id] =
				skl_plane_relative_data_rate(crtc_state, plane_state, 1);
		पूर्ण
	पूर्ण

	क्रम_each_plane_id_on_crtc(crtc, plane_id)
		total_data_rate += crtc_state->plane_data_rate[plane_id];

	वापस total_data_rate;
पूर्ण

स्थिर काष्ठा skl_wm_level *
skl_plane_wm_level(स्थिर काष्ठा skl_pipe_wm *pipe_wm,
		   क्रमागत plane_id plane_id,
		   पूर्णांक level)
अणु
	स्थिर काष्ठा skl_plane_wm *wm = &pipe_wm->planes[plane_id];

	अगर (level == 0 && pipe_wm->use_sagv_wm)
		वापस &wm->sagv.wm0;

	वापस &wm->wm[level];
पूर्ण

स्थिर काष्ठा skl_wm_level *
skl_plane_trans_wm(स्थिर काष्ठा skl_pipe_wm *pipe_wm,
		   क्रमागत plane_id plane_id)
अणु
	स्थिर काष्ठा skl_plane_wm *wm = &pipe_wm->planes[plane_id];

	अगर (pipe_wm->use_sagv_wm)
		वापस &wm->sagv.trans_wm;

	वापस &wm->trans_wm;
पूर्ण

/*
 * We only disable the watermarks क्रम each plane अगर
 * they exceed the ddb allocation of said plane. This
 * is करोne so that we करोn't end up touching cursor
 * watermarks needlessly when some other plane reduces
 * our max possible watermark level.
 *
 * Bspec has this to say about the PLANE_WM enable bit:
 * "All the watermarks at this level क्रम all enabled
 *  planes must be enabled beक्रमe the level will be used."
 * So this is actually safe to करो.
 */
अटल व्योम
skl_check_wm_level(काष्ठा skl_wm_level *wm, u64 total)
अणु
	अगर (wm->min_ddb_alloc > total)
		स_रखो(wm, 0, माप(*wm));
पूर्ण

अटल व्योम
skl_check_nv12_wm_level(काष्ठा skl_wm_level *wm, काष्ठा skl_wm_level *uv_wm,
			u64 total, u64 uv_total)
अणु
	अगर (wm->min_ddb_alloc > total ||
	    uv_wm->min_ddb_alloc > uv_total) अणु
		स_रखो(wm, 0, माप(*wm));
		स_रखो(uv_wm, 0, माप(*uv_wm));
	पूर्ण
पूर्ण

अटल पूर्णांक
skl_allocate_plane_ddb(काष्ठा पूर्णांकel_atomic_state *state,
		       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_dbuf_state *dbuf_state =
		पूर्णांकel_atomic_get_new_dbuf_state(state);
	स्थिर काष्ठा skl_ddb_entry *alloc = &dbuf_state->ddb[crtc->pipe];
	पूर्णांक num_active = hweight8(dbuf_state->active_pipes);
	u16 alloc_size, start = 0;
	u16 total[I915_MAX_PLANES] = अणुपूर्ण;
	u16 uv_total[I915_MAX_PLANES] = अणुपूर्ण;
	u64 total_data_rate;
	क्रमागत plane_id plane_id;
	u32 blocks;
	पूर्णांक level;

	/* Clear the partitioning क्रम disabled planes. */
	स_रखो(crtc_state->wm.skl.plane_ddb_y, 0, माप(crtc_state->wm.skl.plane_ddb_y));
	स_रखो(crtc_state->wm.skl.plane_ddb_uv, 0, माप(crtc_state->wm.skl.plane_ddb_uv));

	अगर (!crtc_state->hw.active)
		वापस 0;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		total_data_rate =
			icl_get_total_relative_data_rate(state, crtc);
	अन्यथा
		total_data_rate =
			skl_get_total_relative_data_rate(state, crtc);

	alloc_size = skl_ddb_entry_size(alloc);
	अगर (alloc_size == 0)
		वापस 0;

	/* Allocate fixed number of blocks क्रम cursor. */
	total[PLANE_CURSOR] = skl_cursor_allocation(crtc_state, num_active);
	alloc_size -= total[PLANE_CURSOR];
	crtc_state->wm.skl.plane_ddb_y[PLANE_CURSOR].start =
		alloc->end - total[PLANE_CURSOR];
	crtc_state->wm.skl.plane_ddb_y[PLANE_CURSOR].end = alloc->end;

	अगर (total_data_rate == 0)
		वापस 0;

	/*
	 * Find the highest watermark level क्रम which we can satisfy the block
	 * requirement of active planes.
	 */
	क्रम (level = ilk_wm_max_level(dev_priv); level >= 0; level--) अणु
		blocks = 0;
		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			स्थिर काष्ठा skl_plane_wm *wm =
				&crtc_state->wm.skl.optimal.planes[plane_id];

			अगर (plane_id == PLANE_CURSOR) अणु
				अगर (wm->wm[level].min_ddb_alloc > total[PLANE_CURSOR]) अणु
					drm_WARN_ON(&dev_priv->drm,
						    wm->wm[level].min_ddb_alloc != U16_MAX);
					blocks = U32_MAX;
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण

			blocks += wm->wm[level].min_ddb_alloc;
			blocks += wm->uv_wm[level].min_ddb_alloc;
		पूर्ण

		अगर (blocks <= alloc_size) अणु
			alloc_size -= blocks;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (level < 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Requested display configuration exceeds system DDB limitations");
		drm_dbg_kms(&dev_priv->drm, "minimum required %d/%d\n",
			    blocks, alloc_size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Grant each plane the blocks it requires at the highest achievable
	 * watermark level, plus an extra share of the leftover blocks
	 * proportional to its relative data rate.
	 */
	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		स्थिर काष्ठा skl_plane_wm *wm =
			&crtc_state->wm.skl.optimal.planes[plane_id];
		u64 rate;
		u16 extra;

		अगर (plane_id == PLANE_CURSOR)
			जारी;

		/*
		 * We've accounted क्रम all active planes; reमुख्यing planes are
		 * all disabled.
		 */
		अगर (total_data_rate == 0)
			अवरोध;

		rate = crtc_state->plane_data_rate[plane_id];
		extra = min_t(u16, alloc_size,
			      DIV64_U64_ROUND_UP(alloc_size * rate,
						 total_data_rate));
		total[plane_id] = wm->wm[level].min_ddb_alloc + extra;
		alloc_size -= extra;
		total_data_rate -= rate;

		अगर (total_data_rate == 0)
			अवरोध;

		rate = crtc_state->uv_plane_data_rate[plane_id];
		extra = min_t(u16, alloc_size,
			      DIV64_U64_ROUND_UP(alloc_size * rate,
						 total_data_rate));
		uv_total[plane_id] = wm->uv_wm[level].min_ddb_alloc + extra;
		alloc_size -= extra;
		total_data_rate -= rate;
	पूर्ण
	drm_WARN_ON(&dev_priv->drm, alloc_size != 0 || total_data_rate != 0);

	/* Set the actual DDB start/end poपूर्णांकs क्रम each plane */
	start = alloc->start;
	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		काष्ठा skl_ddb_entry *plane_alloc =
			&crtc_state->wm.skl.plane_ddb_y[plane_id];
		काष्ठा skl_ddb_entry *uv_plane_alloc =
			&crtc_state->wm.skl.plane_ddb_uv[plane_id];

		अगर (plane_id == PLANE_CURSOR)
			जारी;

		/* Gen11+ uses a separate plane क्रम UV watermarks */
		drm_WARN_ON(&dev_priv->drm,
			    DISPLAY_VER(dev_priv) >= 11 && uv_total[plane_id]);

		/* Leave disabled planes at (0,0) */
		अगर (total[plane_id]) अणु
			plane_alloc->start = start;
			start += total[plane_id];
			plane_alloc->end = start;
		पूर्ण

		अगर (uv_total[plane_id]) अणु
			uv_plane_alloc->start = start;
			start += uv_total[plane_id];
			uv_plane_alloc->end = start;
		पूर्ण
	पूर्ण

	/*
	 * When we calculated watermark values we didn't know how high
	 * of a level we'd actually be able to hit, so we just marked
	 * all levels as "enabled."  Go back now and disable the ones
	 * that aren't actually possible.
	 */
	क्रम (level++; level <= ilk_wm_max_level(dev_priv); level++) अणु
		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			काष्ठा skl_plane_wm *wm =
				&crtc_state->wm.skl.optimal.planes[plane_id];

			skl_check_nv12_wm_level(&wm->wm[level], &wm->uv_wm[level],
						total[plane_id], uv_total[plane_id]);

			/*
			 * Wa_1408961008:icl, ehl
			 * Underruns with WM1+ disabled
			 */
			अगर (IS_DISPLAY_VER(dev_priv, 11) &&
			    level == 1 && wm->wm[0].enable) अणु
				wm->wm[level].blocks = wm->wm[0].blocks;
				wm->wm[level].lines = wm->wm[0].lines;
				wm->wm[level].ignore_lines = wm->wm[0].ignore_lines;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Go back and disable the transition and SAGV watermarks
	 * अगर it turns out we करोn't have enough DDB blocks क्रम them.
	 */
	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		काष्ठा skl_plane_wm *wm =
			&crtc_state->wm.skl.optimal.planes[plane_id];

		skl_check_wm_level(&wm->trans_wm, total[plane_id]);
		skl_check_wm_level(&wm->sagv.wm0, total[plane_id]);
		skl_check_wm_level(&wm->sagv.trans_wm, total[plane_id]);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The max latency should be 257 (max the punit can code is 255 and we add 2us
 * क्रम the पढ़ो latency) and cpp should always be <= 8, so that
 * should allow pixel_rate up to ~2 GHz which seems sufficient since max
 * 2xcdclk is 1350 MHz and the pixel rate should never exceed that.
*/
अटल uपूर्णांक_fixed_16_16_t
skl_wm_method1(स्थिर काष्ठा drm_i915_निजी *dev_priv, u32 pixel_rate,
	       u8 cpp, u32 latency, u32 dbuf_block_size)
अणु
	u32 wm_पूर्णांकermediate_val;
	uपूर्णांक_fixed_16_16_t ret;

	अगर (latency == 0)
		वापस FP_16_16_MAX;

	wm_पूर्णांकermediate_val = latency * pixel_rate * cpp;
	ret = भाग_fixed16(wm_पूर्णांकermediate_val, 1000 * dbuf_block_size);

	अगर (DISPLAY_VER(dev_priv) >= 10)
		ret = add_fixed16_u32(ret, 1);

	वापस ret;
पूर्ण

अटल uपूर्णांक_fixed_16_16_t
skl_wm_method2(u32 pixel_rate, u32 pipe_htotal, u32 latency,
	       uपूर्णांक_fixed_16_16_t plane_blocks_per_line)
अणु
	u32 wm_पूर्णांकermediate_val;
	uपूर्णांक_fixed_16_16_t ret;

	अगर (latency == 0)
		वापस FP_16_16_MAX;

	wm_पूर्णांकermediate_val = latency * pixel_rate;
	wm_पूर्णांकermediate_val = DIV_ROUND_UP(wm_पूर्णांकermediate_val,
					   pipe_htotal * 1000);
	ret = mul_u32_fixed16(wm_पूर्णांकermediate_val, plane_blocks_per_line);
	वापस ret;
पूर्ण

अटल uपूर्णांक_fixed_16_16_t
पूर्णांकel_get_lineसमय_us(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	u32 pixel_rate;
	u32 crtc_htotal;
	uपूर्णांक_fixed_16_16_t lineसमय_us;

	अगर (!crtc_state->hw.active)
		वापस u32_to_fixed16(0);

	pixel_rate = crtc_state->pixel_rate;

	अगर (drm_WARN_ON(&dev_priv->drm, pixel_rate == 0))
		वापस u32_to_fixed16(0);

	crtc_htotal = crtc_state->hw.pipe_mode.crtc_htotal;
	lineसमय_us = भाग_fixed16(crtc_htotal * 1000, pixel_rate);

	वापस lineसमय_us;
पूर्ण

अटल पूर्णांक
skl_compute_wm_params(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      पूर्णांक width, स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
		      u64 modअगरier, अचिन्हित पूर्णांक rotation,
		      u32 plane_pixel_rate, काष्ठा skl_wm_params *wp,
		      पूर्णांक color_plane)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 पूर्णांकerm_pbpl;

	/* only planar क्रमmat has two planes */
	अगर (color_plane == 1 &&
	    !पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(क्रमmat, modअगरier)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Non planar format have single plane\n");
		वापस -EINVAL;
	पूर्ण

	wp->y_tiled = modअगरier == I915_FORMAT_MOD_Y_TILED ||
		      modअगरier == I915_FORMAT_MOD_Yf_TILED ||
		      modअगरier == I915_FORMAT_MOD_Y_TILED_CCS ||
		      modअगरier == I915_FORMAT_MOD_Yf_TILED_CCS;
	wp->x_tiled = modअगरier == I915_FORMAT_MOD_X_TILED;
	wp->rc_surface = modअगरier == I915_FORMAT_MOD_Y_TILED_CCS ||
			 modअगरier == I915_FORMAT_MOD_Yf_TILED_CCS;
	wp->is_planar = पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(क्रमmat, modअगरier);

	wp->width = width;
	अगर (color_plane == 1 && wp->is_planar)
		wp->width /= 2;

	wp->cpp = क्रमmat->cpp[color_plane];
	wp->plane_pixel_rate = plane_pixel_rate;

	अगर (DISPLAY_VER(dev_priv) >= 11 &&
	    modअगरier == I915_FORMAT_MOD_Yf_TILED  && wp->cpp == 1)
		wp->dbuf_block_size = 256;
	अन्यथा
		wp->dbuf_block_size = 512;

	अगर (drm_rotation_90_or_270(rotation)) अणु
		चयन (wp->cpp) अणु
		हाल 1:
			wp->y_min_scanlines = 16;
			अवरोध;
		हाल 2:
			wp->y_min_scanlines = 8;
			अवरोध;
		हाल 4:
			wp->y_min_scanlines = 4;
			अवरोध;
		शेष:
			MISSING_CASE(wp->cpp);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		wp->y_min_scanlines = 4;
	पूर्ण

	अगर (skl_needs_memory_bw_wa(dev_priv))
		wp->y_min_scanlines *= 2;

	wp->plane_bytes_per_line = wp->width * wp->cpp;
	अगर (wp->y_tiled) अणु
		पूर्णांकerm_pbpl = DIV_ROUND_UP(wp->plane_bytes_per_line *
					   wp->y_min_scanlines,
					   wp->dbuf_block_size);

		अगर (DISPLAY_VER(dev_priv) >= 10)
			पूर्णांकerm_pbpl++;

		wp->plane_blocks_per_line = भाग_fixed16(पूर्णांकerm_pbpl,
							wp->y_min_scanlines);
	पूर्ण अन्यथा अणु
		पूर्णांकerm_pbpl = DIV_ROUND_UP(wp->plane_bytes_per_line,
					   wp->dbuf_block_size);

		अगर (!wp->x_tiled || DISPLAY_VER(dev_priv) >= 10)
			पूर्णांकerm_pbpl++;

		wp->plane_blocks_per_line = u32_to_fixed16(पूर्णांकerm_pbpl);
	पूर्ण

	wp->y_tile_minimum = mul_u32_fixed16(wp->y_min_scanlines,
					     wp->plane_blocks_per_line);

	wp->lineसमय_us = fixed16_to_u32_round_up(
					पूर्णांकel_get_lineसमय_us(crtc_state));

	वापस 0;
पूर्ण

अटल पूर्णांक
skl_compute_plane_wm_params(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
			    काष्ठा skl_wm_params *wp, पूर्णांक color_plane)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक width;

	/*
	 * Src coordinates are alपढ़ोy rotated by 270 degrees क्रम
	 * the 90/270 degree plane rotation हालs (to match the
	 * GTT mapping), hence no need to account क्रम rotation here.
	 */
	width = drm_rect_width(&plane_state->uapi.src) >> 16;

	वापस skl_compute_wm_params(crtc_state, width,
				     fb->क्रमmat, fb->modअगरier,
				     plane_state->hw.rotation,
				     पूर्णांकel_plane_pixel_rate(crtc_state, plane_state),
				     wp, color_plane);
पूर्ण

अटल bool skl_wm_has_lines(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक level)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 10)
		वापस true;

	/* The number of lines are ignored क्रम the level 0 watermark. */
	वापस level > 0;
पूर्ण

अटल व्योम skl_compute_plane_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 पूर्णांक level,
				 अचिन्हित पूर्णांक latency,
				 स्थिर काष्ठा skl_wm_params *wp,
				 स्थिर काष्ठा skl_wm_level *result_prev,
				 काष्ठा skl_wm_level *result /* out */)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	uपूर्णांक_fixed_16_16_t method1, method2;
	uपूर्णांक_fixed_16_16_t selected_result;
	u32 blocks, lines, min_ddb_alloc = 0;

	अगर (latency == 0) अणु
		/* reject it */
		result->min_ddb_alloc = U16_MAX;
		वापस;
	पूर्ण

	/*
	 * WaIncreaseLatencyIPCEnabled: kbl,cfl
	 * Display WA #1141: kbl,cfl
	 */
	अगर ((IS_KABYLAKE(dev_priv) ||
	     IS_COFFEELAKE(dev_priv) ||
	     IS_COMETLAKE(dev_priv)) &&
	    dev_priv->ipc_enabled)
		latency += 4;

	अगर (skl_needs_memory_bw_wa(dev_priv) && wp->x_tiled)
		latency += 15;

	method1 = skl_wm_method1(dev_priv, wp->plane_pixel_rate,
				 wp->cpp, latency, wp->dbuf_block_size);
	method2 = skl_wm_method2(wp->plane_pixel_rate,
				 crtc_state->hw.pipe_mode.crtc_htotal,
				 latency,
				 wp->plane_blocks_per_line);

	अगर (wp->y_tiled) अणु
		selected_result = max_fixed16(method2, wp->y_tile_minimum);
	पूर्ण अन्यथा अणु
		अगर ((wp->cpp * crtc_state->hw.pipe_mode.crtc_htotal /
		     wp->dbuf_block_size < 1) &&
		     (wp->plane_bytes_per_line / wp->dbuf_block_size < 1)) अणु
			selected_result = method2;
		पूर्ण अन्यथा अगर (latency >= wp->lineसमय_us) अणु
			अगर (IS_DISPLAY_VER(dev_priv, 9))
				selected_result = min_fixed16(method1, method2);
			अन्यथा
				selected_result = method2;
		पूर्ण अन्यथा अणु
			selected_result = method1;
		पूर्ण
	पूर्ण

	blocks = fixed16_to_u32_round_up(selected_result) + 1;
	lines = भाग_round_up_fixed16(selected_result,
				     wp->plane_blocks_per_line);

	अगर (IS_GEN9_BC(dev_priv) || IS_BROXTON(dev_priv)) अणु
		/* Display WA #1125: skl,bxt,kbl */
		अगर (level == 0 && wp->rc_surface)
			blocks += fixed16_to_u32_round_up(wp->y_tile_minimum);

		/* Display WA #1126: skl,bxt,kbl */
		अगर (level >= 1 && level <= 7) अणु
			अगर (wp->y_tiled) अणु
				blocks += fixed16_to_u32_round_up(wp->y_tile_minimum);
				lines += wp->y_min_scanlines;
			पूर्ण अन्यथा अणु
				blocks++;
			पूर्ण

			/*
			 * Make sure result blocks क्रम higher latency levels are
			 * atleast as high as level below the current level.
			 * Assumption in DDB algorithm optimization क्रम special
			 * हालs. Also covers Display WA #1125 क्रम RC.
			 */
			अगर (result_prev->blocks > blocks)
				blocks = result_prev->blocks;
		पूर्ण
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		अगर (wp->y_tiled) अणु
			पूर्णांक extra_lines;

			अगर (lines % wp->y_min_scanlines == 0)
				extra_lines = wp->y_min_scanlines;
			अन्यथा
				extra_lines = wp->y_min_scanlines * 2 -
					lines % wp->y_min_scanlines;

			min_ddb_alloc = mul_round_up_u32_fixed16(lines + extra_lines,
								 wp->plane_blocks_per_line);
		पूर्ण अन्यथा अणु
			min_ddb_alloc = blocks + DIV_ROUND_UP(blocks, 10);
		पूर्ण
	पूर्ण

	अगर (!skl_wm_has_lines(dev_priv, level))
		lines = 0;

	अगर (lines > 31) अणु
		/* reject it */
		result->min_ddb_alloc = U16_MAX;
		वापस;
	पूर्ण

	/*
	 * If lines is valid, assume we can use this watermark level
	 * क्रम now.  We'll come back and disable it after we calculate the
	 * DDB allocation अगर it turns out we करोn't actually have enough
	 * blocks to satisfy it.
	 */
	result->blocks = blocks;
	result->lines = lines;
	/* Bspec says: value >= plane ddb allocation -> invalid, hence the +1 here */
	result->min_ddb_alloc = max(min_ddb_alloc, blocks) + 1;
	result->enable = true;

	अगर (DISPLAY_VER(dev_priv) < 12)
		result->can_sagv = latency >= dev_priv->sagv_block_समय_us;
पूर्ण

अटल व्योम
skl_compute_wm_levels(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		      स्थिर काष्ठा skl_wm_params *wm_params,
		      काष्ठा skl_wm_level *levels)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	काष्ठा skl_wm_level *result_prev = &levels[0];

	क्रम (level = 0; level <= max_level; level++) अणु
		काष्ठा skl_wm_level *result = &levels[level];
		अचिन्हित पूर्णांक latency = dev_priv->wm.skl_latency[level];

		skl_compute_plane_wm(crtc_state, level, latency,
				     wm_params, result_prev, result);

		result_prev = result;
	पूर्ण
पूर्ण

अटल व्योम tgl_compute_sagv_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				स्थिर काष्ठा skl_wm_params *wm_params,
				काष्ठा skl_plane_wm *plane_wm)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा skl_wm_level *sagv_wm = &plane_wm->sagv.wm0;
	काष्ठा skl_wm_level *levels = plane_wm->wm;
	अचिन्हित पूर्णांक latency = dev_priv->wm.skl_latency[0] + dev_priv->sagv_block_समय_us;

	skl_compute_plane_wm(crtc_state, 0, latency,
			     wm_params, &levels[0],
			     sagv_wm);
पूर्ण

अटल व्योम skl_compute_transition_wm(काष्ठा drm_i915_निजी *dev_priv,
				      काष्ठा skl_wm_level *trans_wm,
				      स्थिर काष्ठा skl_wm_level *wm0,
				      स्थिर काष्ठा skl_wm_params *wp)
अणु
	u16 trans_min, trans_amount, trans_y_tile_min;
	u16 wm0_blocks, trans_offset, blocks;

	/* Transition WM करोn't make any sense अगर ipc is disabled */
	अगर (!dev_priv->ipc_enabled)
		वापस;

	/*
	 * WaDisableTWM:skl,kbl,cfl,bxt
	 * Transition WM are not recommended by HW team क्रम GEN9
	 */
	अगर (IS_GEN9_BC(dev_priv) || IS_BROXTON(dev_priv))
		वापस;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		trans_min = 4;
	अन्यथा
		trans_min = 14;

	/* Display WA #1140: glk,cnl */
	अगर (IS_DISPLAY_VER(dev_priv, 10))
		trans_amount = 0;
	अन्यथा
		trans_amount = 10; /* This is configurable amount */

	trans_offset = trans_min + trans_amount;

	/*
	 * The spec asks क्रम Selected Result Blocks क्रम wm0 (the real value),
	 * not Result Blocks (the पूर्णांकeger value). Pay attention to the capital
	 * letters. The value wm_l0->blocks is actually Result Blocks, but
	 * since Result Blocks is the उच्चमानing of Selected Result Blocks plus 1,
	 * and since we later will have to get the उच्चमानing of the sum in the
	 * transition watermarks calculation, we can just pretend Selected
	 * Result Blocks is Result Blocks minus 1 and it should work क्रम the
	 * current platक्रमms.
	 */
	wm0_blocks = wm0->blocks - 1;

	अगर (wp->y_tiled) अणु
		trans_y_tile_min =
			(u16)mul_round_up_u32_fixed16(2, wp->y_tile_minimum);
		blocks = max(wm0_blocks, trans_y_tile_min) + trans_offset;
	पूर्ण अन्यथा अणु
		blocks = wm0_blocks + trans_offset;
	पूर्ण
	blocks++;

	/*
	 * Just assume we can enable the transition watermark.  After
	 * computing the DDB we'll come back and disable it अगर that
	 * assumption turns out to be false.
	 */
	trans_wm->blocks = blocks;
	trans_wm->min_ddb_alloc = max_t(u16, wm0->min_ddb_alloc, blocks + 1);
	trans_wm->enable = true;
पूर्ण

अटल पूर्णांक skl_build_plane_wm_single(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				     क्रमागत plane_id plane_id, पूर्णांक color_plane)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा skl_plane_wm *wm = &crtc_state->wm.skl.raw.planes[plane_id];
	काष्ठा skl_wm_params wm_params;
	पूर्णांक ret;

	ret = skl_compute_plane_wm_params(crtc_state, plane_state,
					  &wm_params, color_plane);
	अगर (ret)
		वापस ret;

	skl_compute_wm_levels(crtc_state, &wm_params, wm->wm);

	skl_compute_transition_wm(dev_priv, &wm->trans_wm,
				  &wm->wm[0], &wm_params);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		tgl_compute_sagv_wm(crtc_state, &wm_params, wm);

		skl_compute_transition_wm(dev_priv, &wm->sagv.trans_wm,
					  &wm->sagv.wm0, &wm_params);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_build_plane_wm_uv(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा पूर्णांकel_plane_state *plane_state,
				 क्रमागत plane_id plane_id)
अणु
	काष्ठा skl_plane_wm *wm = &crtc_state->wm.skl.raw.planes[plane_id];
	काष्ठा skl_wm_params wm_params;
	पूर्णांक ret;

	wm->is_planar = true;

	/* uv plane watermarks must also be validated क्रम NV12/Planar */
	ret = skl_compute_plane_wm_params(crtc_state, plane_state,
					  &wm_params, 1);
	अगर (ret)
		वापस ret;

	skl_compute_wm_levels(crtc_state, &wm_params, wm->uv_wm);

	वापस 0;
पूर्ण

अटल पूर्णांक skl_build_plane_wm(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	क्रमागत plane_id plane_id = plane->id;
	काष्ठा skl_plane_wm *wm = &crtc_state->wm.skl.raw.planes[plane_id];
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक ret;

	स_रखो(wm, 0, माप(*wm));

	अगर (!पूर्णांकel_wm_plane_visible(crtc_state, plane_state))
		वापस 0;

	ret = skl_build_plane_wm_single(crtc_state, plane_state,
					plane_id, 0);
	अगर (ret)
		वापस ret;

	अगर (fb->क्रमmat->is_yuv && fb->क्रमmat->num_planes > 1) अणु
		ret = skl_build_plane_wm_uv(crtc_state, plane_state,
					    plane_id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icl_build_plane_wm(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	क्रमागत plane_id plane_id = plane->id;
	काष्ठा skl_plane_wm *wm = &crtc_state->wm.skl.raw.planes[plane_id];
	पूर्णांक ret;

	/* Watermarks calculated in master */
	अगर (plane_state->planar_slave)
		वापस 0;

	स_रखो(wm, 0, माप(*wm));

	अगर (plane_state->planar_linked_plane) अणु
		स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
		क्रमागत plane_id y_plane_id = plane_state->planar_linked_plane->id;

		drm_WARN_ON(&dev_priv->drm,
			    !पूर्णांकel_wm_plane_visible(crtc_state, plane_state));
		drm_WARN_ON(&dev_priv->drm, !fb->क्रमmat->is_yuv ||
			    fb->क्रमmat->num_planes == 1);

		ret = skl_build_plane_wm_single(crtc_state, plane_state,
						y_plane_id, 0);
		अगर (ret)
			वापस ret;

		ret = skl_build_plane_wm_single(crtc_state, plane_state,
						plane_id, 1);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (पूर्णांकel_wm_plane_visible(crtc_state, plane_state)) अणु
		ret = skl_build_plane_wm_single(crtc_state, plane_state,
						plane_id, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_build_pipe_wm(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक ret, i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		/*
		 * FIXME should perhaps check अणुold,newपूर्ण_plane_crtc->hw.crtc
		 * instead but we करोn't populate that correctly क्रम NV12 Y
		 * planes so क्रम now hack this.
		 */
		अगर (plane->pipe != crtc->pipe)
			जारी;

		अगर (DISPLAY_VER(dev_priv) >= 11)
			ret = icl_build_plane_wm(crtc_state, plane_state);
		अन्यथा
			ret = skl_build_plane_wm(crtc_state, plane_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	crtc_state->wm.skl.optimal = crtc_state->wm.skl.raw;

	वापस 0;
पूर्ण

अटल व्योम skl_ddb_entry_ग_लिखो(काष्ठा drm_i915_निजी *dev_priv,
				i915_reg_t reg,
				स्थिर काष्ठा skl_ddb_entry *entry)
अणु
	अगर (entry->end)
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, reg,
				  (entry->end - 1) << 16 | entry->start);
	अन्यथा
		पूर्णांकel_de_ग_लिखो_fw(dev_priv, reg, 0);
पूर्ण

अटल व्योम skl_ग_लिखो_wm_level(काष्ठा drm_i915_निजी *dev_priv,
			       i915_reg_t reg,
			       स्थिर काष्ठा skl_wm_level *level)
अणु
	u32 val = 0;

	अगर (level->enable)
		val |= PLANE_WM_EN;
	अगर (level->ignore_lines)
		val |= PLANE_WM_IGNORE_LINES;
	val |= level->blocks;
	val |= level->lines << PLANE_WM_LINES_SHIFT;

	पूर्णांकel_de_ग_लिखो_fw(dev_priv, reg, val);
पूर्ण

व्योम skl_ग_लिखो_plane_wm(काष्ठा पूर्णांकel_plane *plane,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	क्रमागत plane_id plane_id = plane->id;
	क्रमागत pipe pipe = plane->pipe;
	स्थिर काष्ठा skl_pipe_wm *pipe_wm = &crtc_state->wm.skl.optimal;
	स्थिर काष्ठा skl_plane_wm *wm = &pipe_wm->planes[plane_id];
	स्थिर काष्ठा skl_ddb_entry *ddb_y =
		&crtc_state->wm.skl.plane_ddb_y[plane_id];
	स्थिर काष्ठा skl_ddb_entry *ddb_uv =
		&crtc_state->wm.skl.plane_ddb_uv[plane_id];

	क्रम (level = 0; level <= max_level; level++)
		skl_ग_लिखो_wm_level(dev_priv, PLANE_WM(pipe, plane_id, level),
				   skl_plane_wm_level(pipe_wm, plane_id, level));

	skl_ग_लिखो_wm_level(dev_priv, PLANE_WM_TRANS(pipe, plane_id),
			   skl_plane_trans_wm(pipe_wm, plane_id));

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		skl_ddb_entry_ग_लिखो(dev_priv,
				    PLANE_BUF_CFG(pipe, plane_id), ddb_y);
		वापस;
	पूर्ण

	अगर (wm->is_planar)
		swap(ddb_y, ddb_uv);

	skl_ddb_entry_ग_लिखो(dev_priv,
			    PLANE_BUF_CFG(pipe, plane_id), ddb_y);
	skl_ddb_entry_ग_लिखो(dev_priv,
			    PLANE_NV12_BUF_CFG(pipe, plane_id), ddb_uv);
पूर्ण

व्योम skl_ग_लिखो_cursor_wm(काष्ठा पूर्णांकel_plane *plane,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	क्रमागत plane_id plane_id = plane->id;
	क्रमागत pipe pipe = plane->pipe;
	स्थिर काष्ठा skl_pipe_wm *pipe_wm = &crtc_state->wm.skl.optimal;
	स्थिर काष्ठा skl_ddb_entry *ddb =
		&crtc_state->wm.skl.plane_ddb_y[plane_id];

	क्रम (level = 0; level <= max_level; level++)
		skl_ग_लिखो_wm_level(dev_priv, CUR_WM(pipe, level),
				   skl_plane_wm_level(pipe_wm, plane_id, level));

	skl_ग_लिखो_wm_level(dev_priv, CUR_WM_TRANS(pipe),
			   skl_plane_trans_wm(pipe_wm, plane_id));

	skl_ddb_entry_ग_लिखो(dev_priv, CUR_BUF_CFG(pipe), ddb);
पूर्ण

bool skl_wm_level_equals(स्थिर काष्ठा skl_wm_level *l1,
			 स्थिर काष्ठा skl_wm_level *l2)
अणु
	वापस l1->enable == l2->enable &&
		l1->ignore_lines == l2->ignore_lines &&
		l1->lines == l2->lines &&
		l1->blocks == l2->blocks;
पूर्ण

अटल bool skl_plane_wm_equals(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर काष्ठा skl_plane_wm *wm1,
				स्थिर काष्ठा skl_plane_wm *wm2)
अणु
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);

	क्रम (level = 0; level <= max_level; level++) अणु
		/*
		 * We करोn't check uv_wm as the hardware doesn't actually
		 * use it. It only माला_लो used क्रम calculating the required
		 * ddb allocation.
		 */
		अगर (!skl_wm_level_equals(&wm1->wm[level], &wm2->wm[level]))
			वापस false;
	पूर्ण

	वापस skl_wm_level_equals(&wm1->trans_wm, &wm2->trans_wm) &&
		skl_wm_level_equals(&wm1->sagv.wm0, &wm2->sagv.wm0) &&
		skl_wm_level_equals(&wm1->sagv.trans_wm, &wm2->sagv.trans_wm);
पूर्ण

अटल bool skl_ddb_entries_overlap(स्थिर काष्ठा skl_ddb_entry *a,
				    स्थिर काष्ठा skl_ddb_entry *b)
अणु
	वापस a->start < b->end && b->start < a->end;
पूर्ण

अटल व्योम skl_ddb_entry_जोड़(काष्ठा skl_ddb_entry *a,
				स्थिर काष्ठा skl_ddb_entry *b)
अणु
	अगर (a->end && b->end) अणु
		a->start = min(a->start, b->start);
		a->end = max(a->end, b->end);
	पूर्ण अन्यथा अगर (b->end) अणु
		a->start = b->start;
		a->end = b->end;
	पूर्ण
पूर्ण

bool skl_ddb_allocation_overlaps(स्थिर काष्ठा skl_ddb_entry *ddb,
				 स्थिर काष्ठा skl_ddb_entry *entries,
				 पूर्णांक num_entries, पूर्णांक ignore_idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (i != ignore_idx &&
		    skl_ddb_entries_overlap(ddb, &entries[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
skl_ddb_add_affected_planes(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			    काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		काष्ठा पूर्णांकel_plane_state *plane_state;
		क्रमागत plane_id plane_id = plane->id;

		अगर (skl_ddb_entry_equal(&old_crtc_state->wm.skl.plane_ddb_y[plane_id],
					&new_crtc_state->wm.skl.plane_ddb_y[plane_id]) &&
		    skl_ddb_entry_equal(&old_crtc_state->wm.skl.plane_ddb_uv[plane_id],
					&new_crtc_state->wm.skl.plane_ddb_uv[plane_id]))
			जारी;

		plane_state = पूर्णांकel_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);

		new_crtc_state->update_planes |= BIT(plane_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 पूर्णांकel_dbuf_enabled_slices(स्थिर काष्ठा पूर्णांकel_dbuf_state *dbuf_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dbuf_state->base.state->base.dev);
	u8 enabled_slices;
	क्रमागत pipe pipe;

	/*
	 * FIXME: For now we always enable slice S1 as per
	 * the Bspec display initialization sequence.
	 */
	enabled_slices = BIT(DBUF_S1);

	क्रम_each_pipe(dev_priv, pipe)
		enabled_slices |= dbuf_state->slices[pipe];

	वापस enabled_slices;
पूर्ण

अटल पूर्णांक
skl_compute_ddb(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_dbuf_state *old_dbuf_state;
	काष्ठा पूर्णांकel_dbuf_state *new_dbuf_state = शून्य;
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state;
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक ret, i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		new_dbuf_state = पूर्णांकel_atomic_get_dbuf_state(state);
		अगर (IS_ERR(new_dbuf_state))
			वापस PTR_ERR(new_dbuf_state);

		old_dbuf_state = पूर्णांकel_atomic_get_old_dbuf_state(state);
		अवरोध;
	पूर्ण

	अगर (!new_dbuf_state)
		वापस 0;

	new_dbuf_state->active_pipes =
		पूर्णांकel_calc_active_pipes(state, old_dbuf_state->active_pipes);

	अगर (old_dbuf_state->active_pipes != new_dbuf_state->active_pipes) अणु
		ret = पूर्णांकel_atomic_lock_global_state(&new_dbuf_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		क्रमागत pipe pipe = crtc->pipe;

		new_dbuf_state->slices[pipe] =
			skl_compute_dbuf_slices(crtc, new_dbuf_state->active_pipes);

		अगर (old_dbuf_state->slices[pipe] == new_dbuf_state->slices[pipe])
			जारी;

		ret = पूर्णांकel_atomic_lock_global_state(&new_dbuf_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	new_dbuf_state->enabled_slices = पूर्णांकel_dbuf_enabled_slices(new_dbuf_state);

	अगर (old_dbuf_state->enabled_slices != new_dbuf_state->enabled_slices) अणु
		ret = पूर्णांकel_atomic_serialize_global_state(&new_dbuf_state->base);
		अगर (ret)
			वापस ret;

		drm_dbg_kms(&dev_priv->drm,
			    "Enabled dbuf slices 0x%x -> 0x%x (out of %d dbuf slices)\n",
			    old_dbuf_state->enabled_slices,
			    new_dbuf_state->enabled_slices,
			    INTEL_INFO(dev_priv)->num_supported_dbuf_slices);
	पूर्ण

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		क्रमागत pipe pipe = crtc->pipe;

		new_dbuf_state->weight[pipe] = पूर्णांकel_crtc_ddb_weight(new_crtc_state);

		अगर (old_dbuf_state->weight[pipe] == new_dbuf_state->weight[pipe])
			जारी;

		ret = पूर्णांकel_atomic_lock_global_state(&new_dbuf_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		ret = skl_crtc_allocate_ddb(state, crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		ret = skl_allocate_plane_ddb(state, crtc);
		अगर (ret)
			वापस ret;

		ret = skl_ddb_add_affected_planes(old_crtc_state,
						  new_crtc_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर enast(bool enable)
अणु
	वापस enable ? '*' : ' ';
पूर्ण

अटल व्योम
skl_prपूर्णांक_wm_changes(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state;
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	अगर (!drm_debug_enabled(DRM_UT_KMS))
		वापस;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		स्थिर काष्ठा skl_pipe_wm *old_pipe_wm, *new_pipe_wm;

		old_pipe_wm = &old_crtc_state->wm.skl.optimal;
		new_pipe_wm = &new_crtc_state->wm.skl.optimal;

		क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
			क्रमागत plane_id plane_id = plane->id;
			स्थिर काष्ठा skl_ddb_entry *old, *new;

			old = &old_crtc_state->wm.skl.plane_ddb_y[plane_id];
			new = &new_crtc_state->wm.skl.plane_ddb_y[plane_id];

			अगर (skl_ddb_entry_equal(old, new))
				जारी;

			drm_dbg_kms(&dev_priv->drm,
				    "[PLANE:%d:%s] ddb (%4d - %4d) -> (%4d - %4d), size %4d -> %4d\n",
				    plane->base.base.id, plane->base.name,
				    old->start, old->end, new->start, new->end,
				    skl_ddb_entry_size(old), skl_ddb_entry_size(new));
		पूर्ण

		क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
			क्रमागत plane_id plane_id = plane->id;
			स्थिर काष्ठा skl_plane_wm *old_wm, *new_wm;

			old_wm = &old_pipe_wm->planes[plane_id];
			new_wm = &new_pipe_wm->planes[plane_id];

			अगर (skl_plane_wm_equals(dev_priv, old_wm, new_wm))
				जारी;

			drm_dbg_kms(&dev_priv->drm,
				    "[PLANE:%d:%s]   level %cwm0,%cwm1,%cwm2,%cwm3,%cwm4,%cwm5,%cwm6,%cwm7,%ctwm,%cswm,%cstwm"
				    " -> %cwm0,%cwm1,%cwm2,%cwm3,%cwm4,%cwm5,%cwm6,%cwm7,%ctwm,%cswm,%cstwm\n",
				    plane->base.base.id, plane->base.name,
				    enast(old_wm->wm[0].enable), enast(old_wm->wm[1].enable),
				    enast(old_wm->wm[2].enable), enast(old_wm->wm[3].enable),
				    enast(old_wm->wm[4].enable), enast(old_wm->wm[5].enable),
				    enast(old_wm->wm[6].enable), enast(old_wm->wm[7].enable),
				    enast(old_wm->trans_wm.enable),
				    enast(old_wm->sagv.wm0.enable),
				    enast(old_wm->sagv.trans_wm.enable),
				    enast(new_wm->wm[0].enable), enast(new_wm->wm[1].enable),
				    enast(new_wm->wm[2].enable), enast(new_wm->wm[3].enable),
				    enast(new_wm->wm[4].enable), enast(new_wm->wm[5].enable),
				    enast(new_wm->wm[6].enable), enast(new_wm->wm[7].enable),
				    enast(new_wm->trans_wm.enable),
				    enast(new_wm->sagv.wm0.enable),
				    enast(new_wm->sagv.trans_wm.enable));

			drm_dbg_kms(&dev_priv->drm,
				    "[PLANE:%d:%s]   lines %c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%4d"
				      " -> %c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%3d,%c%4d\n",
				    plane->base.base.id, plane->base.name,
				    enast(old_wm->wm[0].ignore_lines), old_wm->wm[0].lines,
				    enast(old_wm->wm[1].ignore_lines), old_wm->wm[1].lines,
				    enast(old_wm->wm[2].ignore_lines), old_wm->wm[2].lines,
				    enast(old_wm->wm[3].ignore_lines), old_wm->wm[3].lines,
				    enast(old_wm->wm[4].ignore_lines), old_wm->wm[4].lines,
				    enast(old_wm->wm[5].ignore_lines), old_wm->wm[5].lines,
				    enast(old_wm->wm[6].ignore_lines), old_wm->wm[6].lines,
				    enast(old_wm->wm[7].ignore_lines), old_wm->wm[7].lines,
				    enast(old_wm->trans_wm.ignore_lines), old_wm->trans_wm.lines,
				    enast(old_wm->sagv.wm0.ignore_lines), old_wm->sagv.wm0.lines,
				    enast(old_wm->sagv.trans_wm.ignore_lines), old_wm->sagv.trans_wm.lines,
				    enast(new_wm->wm[0].ignore_lines), new_wm->wm[0].lines,
				    enast(new_wm->wm[1].ignore_lines), new_wm->wm[1].lines,
				    enast(new_wm->wm[2].ignore_lines), new_wm->wm[2].lines,
				    enast(new_wm->wm[3].ignore_lines), new_wm->wm[3].lines,
				    enast(new_wm->wm[4].ignore_lines), new_wm->wm[4].lines,
				    enast(new_wm->wm[5].ignore_lines), new_wm->wm[5].lines,
				    enast(new_wm->wm[6].ignore_lines), new_wm->wm[6].lines,
				    enast(new_wm->wm[7].ignore_lines), new_wm->wm[7].lines,
				    enast(new_wm->trans_wm.ignore_lines), new_wm->trans_wm.lines,
				    enast(new_wm->sagv.wm0.ignore_lines), new_wm->sagv.wm0.lines,
				    enast(new_wm->sagv.trans_wm.ignore_lines), new_wm->sagv.trans_wm.lines);

			drm_dbg_kms(&dev_priv->drm,
				    "[PLANE:%d:%s]  blocks %4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%5d"
				    " -> %4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%5d\n",
				    plane->base.base.id, plane->base.name,
				    old_wm->wm[0].blocks, old_wm->wm[1].blocks,
				    old_wm->wm[2].blocks, old_wm->wm[3].blocks,
				    old_wm->wm[4].blocks, old_wm->wm[5].blocks,
				    old_wm->wm[6].blocks, old_wm->wm[7].blocks,
				    old_wm->trans_wm.blocks,
				    old_wm->sagv.wm0.blocks,
				    old_wm->sagv.trans_wm.blocks,
				    new_wm->wm[0].blocks, new_wm->wm[1].blocks,
				    new_wm->wm[2].blocks, new_wm->wm[3].blocks,
				    new_wm->wm[4].blocks, new_wm->wm[5].blocks,
				    new_wm->wm[6].blocks, new_wm->wm[7].blocks,
				    new_wm->trans_wm.blocks,
				    new_wm->sagv.wm0.blocks,
				    new_wm->sagv.trans_wm.blocks);

			drm_dbg_kms(&dev_priv->drm,
				    "[PLANE:%d:%s] min_ddb %4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%5d"
				    " -> %4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%5d\n",
				    plane->base.base.id, plane->base.name,
				    old_wm->wm[0].min_ddb_alloc, old_wm->wm[1].min_ddb_alloc,
				    old_wm->wm[2].min_ddb_alloc, old_wm->wm[3].min_ddb_alloc,
				    old_wm->wm[4].min_ddb_alloc, old_wm->wm[5].min_ddb_alloc,
				    old_wm->wm[6].min_ddb_alloc, old_wm->wm[7].min_ddb_alloc,
				    old_wm->trans_wm.min_ddb_alloc,
				    old_wm->sagv.wm0.min_ddb_alloc,
				    old_wm->sagv.trans_wm.min_ddb_alloc,
				    new_wm->wm[0].min_ddb_alloc, new_wm->wm[1].min_ddb_alloc,
				    new_wm->wm[2].min_ddb_alloc, new_wm->wm[3].min_ddb_alloc,
				    new_wm->wm[4].min_ddb_alloc, new_wm->wm[5].min_ddb_alloc,
				    new_wm->wm[6].min_ddb_alloc, new_wm->wm[7].min_ddb_alloc,
				    new_wm->trans_wm.min_ddb_alloc,
				    new_wm->sagv.wm0.min_ddb_alloc,
				    new_wm->sagv.trans_wm.min_ddb_alloc);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool skl_plane_selected_wm_equals(काष्ठा पूर्णांकel_plane *plane,
					 स्थिर काष्ठा skl_pipe_wm *old_pipe_wm,
					 स्थिर काष्ठा skl_pipe_wm *new_pipe_wm)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	पूर्णांक level, max_level = ilk_wm_max_level(i915);

	क्रम (level = 0; level <= max_level; level++) अणु
		/*
		 * We करोn't check uv_wm as the hardware doesn't actually
		 * use it. It only माला_लो used क्रम calculating the required
		 * ddb allocation.
		 */
		अगर (!skl_wm_level_equals(skl_plane_wm_level(old_pipe_wm, plane->id, level),
					 skl_plane_wm_level(new_pipe_wm, plane->id, level)))
			वापस false;
	पूर्ण

	वापस skl_wm_level_equals(skl_plane_trans_wm(old_pipe_wm, plane->id),
				   skl_plane_trans_wm(new_pipe_wm, plane->id));
पूर्ण

/*
 * To make sure the cursor watermark रेजिस्टरs are always consistent
 * with our computed state the following scenario needs special
 * treaपंचांगent:
 *
 * 1. enable cursor
 * 2. move cursor entirely offscreen
 * 3. disable cursor
 *
 * Step 2. करोes call .disable_plane() but करोes not zero the watermarks
 * (since we consider an offscreen cursor still active क्रम the purposes
 * of watermarks). Step 3. would not normally call .disable_plane()
 * because the actual plane visibility isn't changing, and we don't
 * deallocate the cursor ddb until the pipe माला_लो disabled. So we must
 * क्रमce step 3. to call .disable_plane() to update the watermark
 * रेजिस्टरs properly.
 *
 * Other planes करो not suffer from this issues as their watermarks are
 * calculated based on the actual plane visibility. The only समय this
 * can trigger क्रम the other planes is during the initial पढ़ोout as the
 * शेष value of the watermarks रेजिस्टरs is not zero.
 */
अटल पूर्णांक skl_wm_add_affected_planes(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		काष्ठा पूर्णांकel_plane_state *plane_state;
		क्रमागत plane_id plane_id = plane->id;

		/*
		 * Force a full wm update क्रम every plane on modeset.
		 * Required because the reset value of the wm रेजिस्टरs
		 * is non-zero, whereas we want all disabled planes to
		 * have zero watermarks. So अगर we turn off the relevant
		 * घातer well the hardware state will go out of sync
		 * with the software state.
		 */
		अगर (!drm_atomic_crtc_needs_modeset(&new_crtc_state->uapi) &&
		    skl_plane_selected_wm_equals(plane,
						 &old_crtc_state->wm.skl.optimal,
						 &new_crtc_state->wm.skl.optimal))
			जारी;

		plane_state = पूर्णांकel_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);

		new_crtc_state->update_planes |= BIT(plane_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
skl_compute_wm(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	पूर्णांक ret, i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		ret = skl_build_pipe_wm(state, crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = skl_compute_ddb(state);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_compute_sagv_mask(state);
	अगर (ret)
		वापस ret;

	/*
	 * skl_compute_ddb() will have adjusted the final watermarks
	 * based on how much ddb is available. Now we can actually
	 * check अगर the final watermarks changed.
	 */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		ret = skl_wm_add_affected_planes(state, crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	skl_prपूर्णांक_wm_changes(state);

	वापस 0;
पूर्ण

अटल व्योम ilk_compute_wm_config(काष्ठा drm_i915_निजी *dev_priv,
				  काष्ठा पूर्णांकel_wm_config *config)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;

	/* Compute the currently _active_ config */
	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		स्थिर काष्ठा पूर्णांकel_pipe_wm *wm = &crtc->wm.active.ilk;

		अगर (!wm->pipe_enabled)
			जारी;

		config->sprites_enabled |= wm->sprites_enabled;
		config->sprites_scaled |= wm->sprites_scaled;
		config->num_pipes_active++;
	पूर्ण
पूर्ण

अटल व्योम ilk_program_watermarks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_pipe_wm lp_wm_1_2 = अणुपूर्ण, lp_wm_5_6 = अणुपूर्ण, *best_lp_wm;
	काष्ठा ilk_wm_maximums max;
	काष्ठा पूर्णांकel_wm_config config = अणुपूर्ण;
	काष्ठा ilk_wm_values results = अणुपूर्ण;
	क्रमागत पूर्णांकel_ddb_partitioning partitioning;

	ilk_compute_wm_config(dev_priv, &config);

	ilk_compute_wm_maximums(dev_priv, 1, &config, INTEL_DDB_PART_1_2, &max);
	ilk_wm_merge(dev_priv, &config, &max, &lp_wm_1_2);

	/* 5/6 split only in single pipe config on IVB+ */
	अगर (DISPLAY_VER(dev_priv) >= 7 &&
	    config.num_pipes_active == 1 && config.sprites_enabled) अणु
		ilk_compute_wm_maximums(dev_priv, 1, &config, INTEL_DDB_PART_5_6, &max);
		ilk_wm_merge(dev_priv, &config, &max, &lp_wm_5_6);

		best_lp_wm = ilk_find_best_result(dev_priv, &lp_wm_1_2, &lp_wm_5_6);
	पूर्ण अन्यथा अणु
		best_lp_wm = &lp_wm_1_2;
	पूर्ण

	partitioning = (best_lp_wm == &lp_wm_1_2) ?
		       INTEL_DDB_PART_1_2 : INTEL_DDB_PART_5_6;

	ilk_compute_wm_results(dev_priv, best_lp_wm, partitioning, &results);

	ilk_ग_लिखो_wm_values(dev_priv, &results);
पूर्ण

अटल व्योम ilk_initial_watermarks(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.ilk = crtc_state->wm.ilk.पूर्णांकermediate;
	ilk_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

अटल व्योम ilk_optimize_watermarks(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	अगर (!crtc_state->wm.need_postvbl_update)
		वापस;

	mutex_lock(&dev_priv->wm.wm_mutex);
	crtc->wm.active.ilk = crtc_state->wm.ilk.optimal;
	ilk_program_watermarks(dev_priv);
	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

अटल व्योम skl_wm_level_from_reg_val(u32 val, काष्ठा skl_wm_level *level)
अणु
	level->enable = val & PLANE_WM_EN;
	level->ignore_lines = val & PLANE_WM_IGNORE_LINES;
	level->blocks = val & PLANE_WM_BLOCKS_MASK;
	level->lines = (val >> PLANE_WM_LINES_SHIFT) &
		PLANE_WM_LINES_MASK;
पूर्ण

व्योम skl_pipe_wm_get_hw_state(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा skl_pipe_wm *out)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक level, max_level;
	क्रमागत plane_id plane_id;
	u32 val;

	max_level = ilk_wm_max_level(dev_priv);

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		काष्ठा skl_plane_wm *wm = &out->planes[plane_id];

		क्रम (level = 0; level <= max_level; level++) अणु
			अगर (plane_id != PLANE_CURSOR)
				val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PLANE_WM(pipe, plane_id, level));
			अन्यथा
				val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CUR_WM(pipe, level));

			skl_wm_level_from_reg_val(val, &wm->wm[level]);
		पूर्ण

		अगर (plane_id != PLANE_CURSOR)
			val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, PLANE_WM_TRANS(pipe, plane_id));
		अन्यथा
			val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CUR_WM_TRANS(pipe));

		skl_wm_level_from_reg_val(val, &wm->trans_wm);

		अगर (DISPLAY_VER(dev_priv) >= 12) अणु
			wm->sagv.wm0 = wm->wm[0];
			wm->sagv.trans_wm = wm->trans_wm;
		पूर्ण
	पूर्ण
पूर्ण

व्योम skl_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_dbuf_state *dbuf_state =
		to_पूर्णांकel_dbuf_state(dev_priv->dbuf.obj.state);
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		क्रमागत pipe pipe = crtc->pipe;
		क्रमागत plane_id plane_id;

		skl_pipe_wm_get_hw_state(crtc, &crtc_state->wm.skl.optimal);
		crtc_state->wm.skl.raw = crtc_state->wm.skl.optimal;

		स_रखो(&dbuf_state->ddb[pipe], 0, माप(dbuf_state->ddb[pipe]));

		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			काष्ठा skl_ddb_entry *ddb_y =
				&crtc_state->wm.skl.plane_ddb_y[plane_id];
			काष्ठा skl_ddb_entry *ddb_uv =
				&crtc_state->wm.skl.plane_ddb_uv[plane_id];

			skl_ddb_get_hw_plane_state(dev_priv, crtc->pipe,
						   plane_id, ddb_y, ddb_uv);

			skl_ddb_entry_जोड़(&dbuf_state->ddb[pipe], ddb_y);
			skl_ddb_entry_जोड़(&dbuf_state->ddb[pipe], ddb_uv);
		पूर्ण

		dbuf_state->slices[pipe] =
			skl_compute_dbuf_slices(crtc, dbuf_state->active_pipes);

		dbuf_state->weight[pipe] = पूर्णांकel_crtc_ddb_weight(crtc_state);

		crtc_state->wm.skl.ddb = dbuf_state->ddb[pipe];

		drm_dbg_kms(&dev_priv->drm,
			    "[CRTC:%d:%s] dbuf slices 0x%x, ddb (%d - %d), active pipes 0x%x\n",
			    crtc->base.base.id, crtc->base.name,
			    dbuf_state->slices[pipe], dbuf_state->ddb[pipe].start,
			    dbuf_state->ddb[pipe].end, dbuf_state->active_pipes);
	पूर्ण

	dbuf_state->enabled_slices = dev_priv->dbuf.enabled_slices;
पूर्ण

अटल व्योम ilk_pipe_wm_get_hw_state(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा ilk_wm_values *hw = &dev_priv->wm.hw;
	काष्ठा पूर्णांकel_crtc_state *crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);
	काष्ठा पूर्णांकel_pipe_wm *active = &crtc_state->wm.ilk.optimal;
	क्रमागत pipe pipe = crtc->pipe;

	hw->wm_pipe[pipe] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM0_PIPE_ILK(pipe));

	स_रखो(active, 0, माप(*active));

	active->pipe_enabled = crtc->active;

	अगर (active->pipe_enabled) अणु
		u32 पंचांगp = hw->wm_pipe[pipe];

		/*
		 * For active pipes LP0 watermark is marked as
		 * enabled, and LP1+ watermaks as disabled since
		 * we can't really reverse compute them in हाल
		 * multiple pipes are active.
		 */
		active->wm[0].enable = true;
		active->wm[0].pri_val = (पंचांगp & WM0_PIPE_PLANE_MASK) >> WM0_PIPE_PLANE_SHIFT;
		active->wm[0].spr_val = (पंचांगp & WM0_PIPE_SPRITE_MASK) >> WM0_PIPE_SPRITE_SHIFT;
		active->wm[0].cur_val = पंचांगp & WM0_PIPE_CURSOR_MASK;
	पूर्ण अन्यथा अणु
		पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);

		/*
		 * For inactive pipes, all watermark levels
		 * should be marked as enabled but zeroed,
		 * which is what we'd compute them to.
		 */
		क्रम (level = 0; level <= max_level; level++)
			active->wm[level].enable = true;
	पूर्ण

	crtc->wm.active.ilk = *active;
पूर्ण

#घोषणा _FW_WM(value, plane) \
	(((value) & DSPFW_ ## plane ## _MASK) >> DSPFW_ ## plane ## _SHIFT)
#घोषणा _FW_WM_VLV(value, plane) \
	(((value) & DSPFW_ ## plane ## _MASK_VLV) >> DSPFW_ ## plane ## _SHIFT)

अटल व्योम g4x_पढ़ो_wm_values(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा g4x_wm_values *wm)
अणु
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW1);
	wm->sr.plane = _FW_WM(पंचांगp, SR);
	wm->pipe[PIPE_B].plane[PLANE_CURSOR] = _FW_WM(पंचांगp, CURSORB);
	wm->pipe[PIPE_B].plane[PLANE_PRIMARY] = _FW_WM(पंचांगp, PLANEB);
	wm->pipe[PIPE_A].plane[PLANE_PRIMARY] = _FW_WM(पंचांगp, PLANEA);

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW2);
	wm->fbc_en = पंचांगp & DSPFW_FBC_SR_EN;
	wm->sr.fbc = _FW_WM(पंचांगp, FBC_SR);
	wm->hpll.fbc = _FW_WM(पंचांगp, FBC_HPLL_SR);
	wm->pipe[PIPE_B].plane[PLANE_SPRITE0] = _FW_WM(पंचांगp, SPRITEB);
	wm->pipe[PIPE_A].plane[PLANE_CURSOR] = _FW_WM(पंचांगp, CURSORA);
	wm->pipe[PIPE_A].plane[PLANE_SPRITE0] = _FW_WM(पंचांगp, SPRITEA);

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW3);
	wm->hpll_en = पंचांगp & DSPFW_HPLL_SR_EN;
	wm->sr.cursor = _FW_WM(पंचांगp, CURSOR_SR);
	wm->hpll.cursor = _FW_WM(पंचांगp, HPLL_CURSOR);
	wm->hpll.plane = _FW_WM(पंचांगp, HPLL_SR);
पूर्ण

अटल व्योम vlv_पढ़ो_wm_values(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा vlv_wm_values *wm)
अणु
	क्रमागत pipe pipe;
	u32 पंचांगp;

	क्रम_each_pipe(dev_priv, pipe) अणु
		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, VLV_DDL(pipe));

		wm->ddl[pipe].plane[PLANE_PRIMARY] =
			(पंचांगp >> DDL_PLANE_SHIFT) & (DDL_PRECISION_HIGH | DRAIN_LATENCY_MASK);
		wm->ddl[pipe].plane[PLANE_CURSOR] =
			(पंचांगp >> DDL_CURSOR_SHIFT) & (DDL_PRECISION_HIGH | DRAIN_LATENCY_MASK);
		wm->ddl[pipe].plane[PLANE_SPRITE0] =
			(पंचांगp >> DDL_SPRITE_SHIFT(0)) & (DDL_PRECISION_HIGH | DRAIN_LATENCY_MASK);
		wm->ddl[pipe].plane[PLANE_SPRITE1] =
			(पंचांगp >> DDL_SPRITE_SHIFT(1)) & (DDL_PRECISION_HIGH | DRAIN_LATENCY_MASK);
	पूर्ण

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW1);
	wm->sr.plane = _FW_WM(पंचांगp, SR);
	wm->pipe[PIPE_B].plane[PLANE_CURSOR] = _FW_WM(पंचांगp, CURSORB);
	wm->pipe[PIPE_B].plane[PLANE_PRIMARY] = _FW_WM_VLV(पंचांगp, PLANEB);
	wm->pipe[PIPE_A].plane[PLANE_PRIMARY] = _FW_WM_VLV(पंचांगp, PLANEA);

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW2);
	wm->pipe[PIPE_A].plane[PLANE_SPRITE1] = _FW_WM_VLV(पंचांगp, SPRITEB);
	wm->pipe[PIPE_A].plane[PLANE_CURSOR] = _FW_WM(पंचांगp, CURSORA);
	wm->pipe[PIPE_A].plane[PLANE_SPRITE0] = _FW_WM_VLV(पंचांगp, SPRITEA);

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW3);
	wm->sr.cursor = _FW_WM(पंचांगp, CURSOR_SR);

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW7_CHV);
		wm->pipe[PIPE_B].plane[PLANE_SPRITE1] = _FW_WM_VLV(पंचांगp, SPRITED);
		wm->pipe[PIPE_B].plane[PLANE_SPRITE0] = _FW_WM_VLV(पंचांगp, SPRITEC);

		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW8_CHV);
		wm->pipe[PIPE_C].plane[PLANE_SPRITE1] = _FW_WM_VLV(पंचांगp, SPRITEF);
		wm->pipe[PIPE_C].plane[PLANE_SPRITE0] = _FW_WM_VLV(पंचांगp, SPRITEE);

		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW9_CHV);
		wm->pipe[PIPE_C].plane[PLANE_PRIMARY] = _FW_WM_VLV(पंचांगp, PLANEC);
		wm->pipe[PIPE_C].plane[PLANE_CURSOR] = _FW_WM(पंचांगp, CURSORC);

		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPHOWM);
		wm->sr.plane |= _FW_WM(पंचांगp, SR_HI) << 9;
		wm->pipe[PIPE_C].plane[PLANE_SPRITE1] |= _FW_WM(पंचांगp, SPRITEF_HI) << 8;
		wm->pipe[PIPE_C].plane[PLANE_SPRITE0] |= _FW_WM(पंचांगp, SPRITEE_HI) << 8;
		wm->pipe[PIPE_C].plane[PLANE_PRIMARY] |= _FW_WM(पंचांगp, PLANEC_HI) << 8;
		wm->pipe[PIPE_B].plane[PLANE_SPRITE1] |= _FW_WM(पंचांगp, SPRITED_HI) << 8;
		wm->pipe[PIPE_B].plane[PLANE_SPRITE0] |= _FW_WM(पंचांगp, SPRITEC_HI) << 8;
		wm->pipe[PIPE_B].plane[PLANE_PRIMARY] |= _FW_WM(पंचांगp, PLANEB_HI) << 8;
		wm->pipe[PIPE_A].plane[PLANE_SPRITE1] |= _FW_WM(पंचांगp, SPRITEB_HI) << 8;
		wm->pipe[PIPE_A].plane[PLANE_SPRITE0] |= _FW_WM(पंचांगp, SPRITEA_HI) << 8;
		wm->pipe[PIPE_A].plane[PLANE_PRIMARY] |= _FW_WM(पंचांगp, PLANEA_HI) << 8;
	पूर्ण अन्यथा अणु
		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPFW7);
		wm->pipe[PIPE_B].plane[PLANE_SPRITE1] = _FW_WM_VLV(पंचांगp, SPRITED);
		wm->pipe[PIPE_B].plane[PLANE_SPRITE0] = _FW_WM_VLV(पंचांगp, SPRITEC);

		पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPHOWM);
		wm->sr.plane |= _FW_WM(पंचांगp, SR_HI) << 9;
		wm->pipe[PIPE_B].plane[PLANE_SPRITE1] |= _FW_WM(पंचांगp, SPRITED_HI) << 8;
		wm->pipe[PIPE_B].plane[PLANE_SPRITE0] |= _FW_WM(पंचांगp, SPRITEC_HI) << 8;
		wm->pipe[PIPE_B].plane[PLANE_PRIMARY] |= _FW_WM(पंचांगp, PLANEB_HI) << 8;
		wm->pipe[PIPE_A].plane[PLANE_SPRITE1] |= _FW_WM(पंचांगp, SPRITEB_HI) << 8;
		wm->pipe[PIPE_A].plane[PLANE_SPRITE0] |= _FW_WM(पंचांगp, SPRITEA_HI) << 8;
		wm->pipe[PIPE_A].plane[PLANE_PRIMARY] |= _FW_WM(पंचांगp, PLANEA_HI) << 8;
	पूर्ण
पूर्ण

#अघोषित _FW_WM
#अघोषित _FW_WM_VLV

व्योम g4x_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा g4x_wm_values *wm = &dev_priv->wm.g4x;
	काष्ठा पूर्णांकel_crtc *crtc;

	g4x_पढ़ो_wm_values(dev_priv, wm);

	wm->cxsr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FW_BLC_SELF) & FW_BLC_SELF_EN;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		काष्ठा g4x_wm_state *active = &crtc->wm.active.g4x;
		काष्ठा g4x_pipe_wm *raw;
		क्रमागत pipe pipe = crtc->pipe;
		क्रमागत plane_id plane_id;
		पूर्णांक level, max_level;

		active->cxsr = wm->cxsr;
		active->hpll_en = wm->hpll_en;
		active->fbc_en = wm->fbc_en;

		active->sr = wm->sr;
		active->hpll = wm->hpll;

		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			active->wm.plane[plane_id] =
				wm->pipe[pipe].plane[plane_id];
		पूर्ण

		अगर (wm->cxsr && wm->hpll_en)
			max_level = G4X_WM_LEVEL_HPLL;
		अन्यथा अगर (wm->cxsr)
			max_level = G4X_WM_LEVEL_SR;
		अन्यथा
			max_level = G4X_WM_LEVEL_NORMAL;

		level = G4X_WM_LEVEL_NORMAL;
		raw = &crtc_state->wm.g4x.raw[level];
		क्रम_each_plane_id_on_crtc(crtc, plane_id)
			raw->plane[plane_id] = active->wm.plane[plane_id];

		अगर (++level > max_level)
			जाओ out;

		raw = &crtc_state->wm.g4x.raw[level];
		raw->plane[PLANE_PRIMARY] = active->sr.plane;
		raw->plane[PLANE_CURSOR] = active->sr.cursor;
		raw->plane[PLANE_SPRITE0] = 0;
		raw->fbc = active->sr.fbc;

		अगर (++level > max_level)
			जाओ out;

		raw = &crtc_state->wm.g4x.raw[level];
		raw->plane[PLANE_PRIMARY] = active->hpll.plane;
		raw->plane[PLANE_CURSOR] = active->hpll.cursor;
		raw->plane[PLANE_SPRITE0] = 0;
		raw->fbc = active->hpll.fbc;

	out:
		क्रम_each_plane_id_on_crtc(crtc, plane_id)
			g4x_raw_plane_wm_set(crtc_state, level,
					     plane_id, अच_लघु_उच्च);
		g4x_raw_fbc_wm_set(crtc_state, level, अच_लघु_उच्च);

		crtc_state->wm.g4x.optimal = *active;
		crtc_state->wm.g4x.पूर्णांकermediate = *active;

		drm_dbg_kms(&dev_priv->drm,
			    "Initial watermarks: pipe %c, plane=%d, cursor=%d, sprite=%d\n",
			    pipe_name(pipe),
			    wm->pipe[pipe].plane[PLANE_PRIMARY],
			    wm->pipe[pipe].plane[PLANE_CURSOR],
			    wm->pipe[pipe].plane[PLANE_SPRITE0]);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "Initial SR watermarks: plane=%d, cursor=%d fbc=%d\n",
		    wm->sr.plane, wm->sr.cursor, wm->sr.fbc);
	drm_dbg_kms(&dev_priv->drm,
		    "Initial HPLL watermarks: plane=%d, SR cursor=%d fbc=%d\n",
		    wm->hpll.plane, wm->hpll.cursor, wm->hpll.fbc);
	drm_dbg_kms(&dev_priv->drm, "Initial SR=%s HPLL=%s FBC=%s\n",
		    yesno(wm->cxsr), yesno(wm->hpll_en), yesno(wm->fbc_en));
पूर्ण

व्योम g4x_wm_sanitize(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_crtc *crtc;

	mutex_lock(&dev_priv->wm.wm_mutex);

	क्रम_each_पूर्णांकel_plane(&dev_priv->drm, plane) अणु
		काष्ठा पूर्णांकel_crtc *crtc =
			पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, plane->pipe);
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		काष्ठा पूर्णांकel_plane_state *plane_state =
			to_पूर्णांकel_plane_state(plane->base.state);
		काष्ठा g4x_wm_state *wm_state = &crtc_state->wm.g4x.optimal;
		क्रमागत plane_id plane_id = plane->id;
		पूर्णांक level;

		अगर (plane_state->uapi.visible)
			जारी;

		क्रम (level = 0; level < 3; level++) अणु
			काष्ठा g4x_pipe_wm *raw =
				&crtc_state->wm.g4x.raw[level];

			raw->plane[plane_id] = 0;
			wm_state->wm.plane[plane_id] = 0;
		पूर्ण

		अगर (plane_id == PLANE_PRIMARY) अणु
			क्रम (level = 0; level < 3; level++) अणु
				काष्ठा g4x_pipe_wm *raw =
					&crtc_state->wm.g4x.raw[level];
				raw->fbc = 0;
			पूर्ण

			wm_state->sr.fbc = 0;
			wm_state->hpll.fbc = 0;
			wm_state->fbc_en = false;
		पूर्ण
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		crtc_state->wm.g4x.पूर्णांकermediate =
			crtc_state->wm.g4x.optimal;
		crtc->wm.active.g4x = crtc_state->wm.g4x.optimal;
	पूर्ण

	g4x_program_watermarks(dev_priv);

	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

व्योम vlv_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा vlv_wm_values *wm = &dev_priv->wm.vlv;
	काष्ठा पूर्णांकel_crtc *crtc;
	u32 val;

	vlv_पढ़ो_wm_values(dev_priv, wm);

	wm->cxsr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FW_BLC_SELF_VLV) & FW_CSPWRDWNEN;
	wm->level = VLV_WM_LEVEL_PM2;

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		vlv_punit_get(dev_priv);

		val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM);
		अगर (val & DSP_MAXFIFO_PM5_ENABLE)
			wm->level = VLV_WM_LEVEL_PM5;

		/*
		 * If DDR DVFS is disabled in the BIOS, Punit
		 * will never ack the request. So अगर that happens
		 * assume we करोn't have to enable/disable DDR DVFS
		 * dynamically. To test that just set the REQ_ACK
		 * bit to poke the Punit, but करोn't change the
		 * HIGH/LOW bits so that we करोn't actually change
		 * the current state.
		 */
		val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DDR_SETUP2);
		val |= FORCE_DDR_FREQ_REQ_ACK;
		vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_DDR_SETUP2, val);

		अगर (रुको_क्रम((vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DDR_SETUP2) &
			      FORCE_DDR_FREQ_REQ_ACK) == 0, 3)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Punit not acking DDR DVFS request, "
				    "assuming DDR DVFS is disabled\n");
			dev_priv->wm.max_level = VLV_WM_LEVEL_PM5;
		पूर्ण अन्यथा अणु
			val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DDR_SETUP2);
			अगर ((val & FORCE_DDR_HIGH_FREQ) == 0)
				wm->level = VLV_WM_LEVEL_DDR_DVFS;
		पूर्ण

		vlv_punit_put(dev_priv);
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		काष्ठा vlv_wm_state *active = &crtc->wm.active.vlv;
		स्थिर काष्ठा vlv_fअगरo_state *fअगरo_state =
			&crtc_state->wm.vlv.fअगरo_state;
		क्रमागत pipe pipe = crtc->pipe;
		क्रमागत plane_id plane_id;
		पूर्णांक level;

		vlv_get_fअगरo_size(crtc_state);

		active->num_levels = wm->level + 1;
		active->cxsr = wm->cxsr;

		क्रम (level = 0; level < active->num_levels; level++) अणु
			काष्ठा g4x_pipe_wm *raw =
				&crtc_state->wm.vlv.raw[level];

			active->sr[level].plane = wm->sr.plane;
			active->sr[level].cursor = wm->sr.cursor;

			क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
				active->wm[level].plane[plane_id] =
					wm->pipe[pipe].plane[plane_id];

				raw->plane[plane_id] =
					vlv_invert_wm_value(active->wm[level].plane[plane_id],
							    fअगरo_state->plane[plane_id]);
			पूर्ण
		पूर्ण

		क्रम_each_plane_id_on_crtc(crtc, plane_id)
			vlv_raw_plane_wm_set(crtc_state, level,
					     plane_id, अच_लघु_उच्च);
		vlv_invalidate_wms(crtc, active, level);

		crtc_state->wm.vlv.optimal = *active;
		crtc_state->wm.vlv.पूर्णांकermediate = *active;

		drm_dbg_kms(&dev_priv->drm,
			    "Initial watermarks: pipe %c, plane=%d, cursor=%d, sprite0=%d, sprite1=%d\n",
			    pipe_name(pipe),
			    wm->pipe[pipe].plane[PLANE_PRIMARY],
			    wm->pipe[pipe].plane[PLANE_CURSOR],
			    wm->pipe[pipe].plane[PLANE_SPRITE0],
			    wm->pipe[pipe].plane[PLANE_SPRITE1]);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "Initial watermarks: SR plane=%d, SR cursor=%d level=%d cxsr=%d\n",
		    wm->sr.plane, wm->sr.cursor, wm->level, wm->cxsr);
पूर्ण

व्योम vlv_wm_sanitize(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_crtc *crtc;

	mutex_lock(&dev_priv->wm.wm_mutex);

	क्रम_each_पूर्णांकel_plane(&dev_priv->drm, plane) अणु
		काष्ठा पूर्णांकel_crtc *crtc =
			पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, plane->pipe);
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		काष्ठा पूर्णांकel_plane_state *plane_state =
			to_पूर्णांकel_plane_state(plane->base.state);
		काष्ठा vlv_wm_state *wm_state = &crtc_state->wm.vlv.optimal;
		स्थिर काष्ठा vlv_fअगरo_state *fअगरo_state =
			&crtc_state->wm.vlv.fअगरo_state;
		क्रमागत plane_id plane_id = plane->id;
		पूर्णांक level;

		अगर (plane_state->uapi.visible)
			जारी;

		क्रम (level = 0; level < wm_state->num_levels; level++) अणु
			काष्ठा g4x_pipe_wm *raw =
				&crtc_state->wm.vlv.raw[level];

			raw->plane[plane_id] = 0;

			wm_state->wm[level].plane[plane_id] =
				vlv_invert_wm_value(raw->plane[plane_id],
						    fअगरo_state->plane[plane_id]);
		पूर्ण
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		crtc_state->wm.vlv.पूर्णांकermediate =
			crtc_state->wm.vlv.optimal;
		crtc->wm.active.vlv = crtc_state->wm.vlv.optimal;
	पूर्ण

	vlv_program_watermarks(dev_priv);

	mutex_unlock(&dev_priv->wm.wm_mutex);
पूर्ण

/*
 * FIXME should probably समाप्त this and improve
 * the real watermark पढ़ोout/sanitation instead
 */
अटल व्योम ilk_init_lp_watermarks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM3_LP_ILK, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM3_LP_ILK) & ~WM1_LP_SR_EN);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM2_LP_ILK, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM2_LP_ILK) & ~WM1_LP_SR_EN);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, WM1_LP_ILK, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM1_LP_ILK) & ~WM1_LP_SR_EN);

	/*
	 * Don't touch WM1S_LP_EN here.
	 * Doing so could cause underruns.
	 */
पूर्ण

व्योम ilk_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा ilk_wm_values *hw = &dev_priv->wm.hw;
	काष्ठा पूर्णांकel_crtc *crtc;

	ilk_init_lp_watermarks(dev_priv);

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc)
		ilk_pipe_wm_get_hw_state(crtc);

	hw->wm_lp[0] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM1_LP_ILK);
	hw->wm_lp[1] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM2_LP_ILK);
	hw->wm_lp[2] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM3_LP_ILK);

	hw->wm_lp_spr[0] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM1S_LP_ILK);
	अगर (DISPLAY_VER(dev_priv) >= 7) अणु
		hw->wm_lp_spr[1] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM2S_LP_IVB);
		hw->wm_lp_spr[2] = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM3S_LP_IVB);
	पूर्ण

	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		hw->partitioning = (पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, WM_MISC) & WM_MISC_DATA_PARTITION_5_6) ?
			INTEL_DDB_PART_5_6 : INTEL_DDB_PART_1_2;
	अन्यथा अगर (IS_IVYBRIDGE(dev_priv))
		hw->partitioning = (पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL2) & DISP_DATA_PARTITION_5_6) ?
			INTEL_DDB_PART_5_6 : INTEL_DDB_PART_1_2;

	hw->enable_fbc_wm =
		!(पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) & DISP_FBC_WM_DIS);
पूर्ण

/**
 * पूर्णांकel_update_watermarks - update FIFO watermark values based on current modes
 * @crtc: the #पूर्णांकel_crtc on which to compute the WM
 *
 * Calculate watermark values क्रम the various WM regs based on current mode
 * and plane configuration.
 *
 * There are several हालs to deal with here:
 *   - normal (i.e. non-self-refresh)
 *   - self-refresh (SR) mode
 *   - lines are large relative to FIFO size (buffer can hold up to 2)
 *   - lines are small relative to FIFO size (buffer can hold more than 2
 *     lines), so need to account क्रम TLB latency
 *
 *   The normal calculation is:
 *     watermark = करोtघड़ी * bytes per pixel * latency
 *   where latency is platक्रमm & configuration dependent (we assume pessimal
 *   values here).
 *
 *   The SR calculation is:
 *     watermark = (trunc(latency/line समय)+1) * surface width *
 *       bytes per pixel
 *   where
 *     line समय = htotal / करोtघड़ी
 *     surface width = hdisplay क्रम normal plane and 64 क्रम cursor
 *   and latency is assumed to be high, as above.
 *
 * The final value programmed to the रेजिस्टर should always be rounded up,
 * and include an extra 2 entries to account क्रम घड़ी crossings.
 *
 * We करोn't use the sprite, so we can ignore that.  And on Crestline we have
 * to set the non-SR watermarks to 8.
 */
व्योम पूर्णांकel_update_watermarks(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (dev_priv->display.update_wm)
		dev_priv->display.update_wm(crtc);
पूर्ण

व्योम पूर्णांकel_enable_ipc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	अगर (!HAS_IPC(dev_priv))
		वापस;

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL2);

	अगर (dev_priv->ipc_enabled)
		val |= DISP_IPC_ENABLE;
	अन्यथा
		val &= ~DISP_IPC_ENABLE;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL2, val);
पूर्ण

अटल bool पूर्णांकel_can_enable_ipc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* Display WA #0477 WaDisableIPC: skl */
	अगर (IS_SKYLAKE(dev_priv))
		वापस false;

	/* Display WA #1141: SKL:all KBL:all CFL */
	अगर (IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_COMETLAKE(dev_priv))
		वापस dev_priv->dram_info.symmetric_memory;

	वापस true;
पूर्ण

व्योम पूर्णांकel_init_ipc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_IPC(dev_priv))
		वापस;

	dev_priv->ipc_enabled = पूर्णांकel_can_enable_ipc(dev_priv);

	पूर्णांकel_enable_ipc(dev_priv);
पूर्ण

अटल व्योम ibx_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * On Ibex Peak and Cougar Poपूर्णांक, we need to disable घड़ी
	 * gating क्रम the panel घातer sequencer or it will fail to
	 * start up when no ports are active.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D, PCH_DPLSUNIT_CLOCK_GATE_DISABLE);
पूर्ण

अटल व्योम g4x_disable_trickle_feed(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe) अणु
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPCNTR(pipe),
			   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPCNTR(pipe)) |
			   DISPPLANE_TRICKLE_FEED_DISABLE);

		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPSURF(pipe), पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DSPSURF(pipe)));
		पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, DSPSURF(pipe));
	पूर्ण
पूर्ण

अटल व्योम ilk_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 dspclk_gate = ILK_VRHUNIT_CLOCK_GATE_DISABLE;

	/*
	 * Required क्रम FBC
	 * WaFbcDisableDpfcClockGating:ilk
	 */
	dspclk_gate |= ILK_DPFCRUNIT_CLOCK_GATE_DISABLE |
		   ILK_DPFCUNIT_CLOCK_GATE_DISABLE |
		   ILK_DPFDUNIT_CLOCK_GATE_ENABLE;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_3DCGDIS0,
		   MARIUNIT_CLOCK_GATE_DISABLE |
		   SVSMUNIT_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, PCH_3DCGDIS1,
		   VFMUNIT_CLOCK_GATE_DISABLE);

	/*
	 * According to the spec the following bits should be set in
	 * order to enable memory self-refresh
	 * The bit 22/21 of 0x42004
	 * The bit 5 of 0x42020
	 * The bit 15 of 0x45000
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2,
		   (पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2) |
		    ILK_DPARB_GATE | ILK_VSDPFD_FULL));
	dspclk_gate |= ILK_DPARBUNIT_CLOCK_GATE_ENABLE;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL,
		   (पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		    DISP_FBC_WM_DIS));

	/*
	 * Based on the करोcument from hardware guys the following bits
	 * should be set unconditionally in order to enable FBC.
	 * The bit 22 of 0x42000
	 * The bit 22 of 0x42004
	 * The bit 7,8,9 of 0x42020.
	 */
	अगर (IS_IRONLAKE_M(dev_priv)) अणु
		/* WaFbcAsynchFlipDisableFbcQueue:ilk */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN1,
			   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN1) |
			   ILK_FBCQ_DIS);
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2,
			   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2) |
			   ILK_DPARB_GATE);
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DSPCLK_GATE_D, dspclk_gate);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2) |
		   ILK_ELPIN_409_SELECT);

	g4x_disable_trickle_feed(dev_priv);

	ibx_init_घड़ी_gating(dev_priv);
पूर्ण

अटल व्योम cpt_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत pipe pipe;
	u32 val;

	/*
	 * On Ibex Peak and Cougar Poपूर्णांक, we need to disable घड़ी
	 * gating क्रम the panel घातer sequencer or it will fail to
	 * start up when no ports are active.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D, PCH_DPLSUNIT_CLOCK_GATE_DISABLE |
		   PCH_DPLUNIT_CLOCK_GATE_DISABLE |
		   PCH_CPUNIT_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_CHICKEN2, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SOUTH_CHICKEN2) |
		   DPLS_EDP_PPS_FIX_DIS);
	/* The below fixes the weird display corruption, a few pixels shअगरted
	 * करोwnward, on (only) LVDS of some HP laptops with IVY.
	 */
	क्रम_each_pipe(dev_priv, pipe) अणु
		val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, TRANS_CHICKEN2(pipe));
		val |= TRANS_CHICKEN2_TIMING_OVERRIDE;
		val &= ~TRANS_CHICKEN2_FDI_POLARITY_REVERSED;
		अगर (dev_priv->vbt.fdi_rx_polarity_inverted)
			val |= TRANS_CHICKEN2_FDI_POLARITY_REVERSED;
		val &= ~TRANS_CHICKEN2_DISABLE_DEEP_COLOR_COUNTER;
		val &= ~TRANS_CHICKEN2_DISABLE_DEEP_COLOR_MODESWITCH;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, TRANS_CHICKEN2(pipe), val);
	पूर्ण
	/* WADP0ClockGatingDisable */
	क्रम_each_pipe(dev_priv, pipe) अणु
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, TRANS_CHICKEN1(pipe),
			   TRANS_CHICKEN1_DP0UNIT_GC_DISABLE);
	पूर्ण
पूर्ण

अटल व्योम gen6_check_mch_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, MCH_SSKPD);
	अगर ((पंचांगp & MCH_SSKPD_WM0_MASK) != MCH_SSKPD_WM0_VAL)
		drm_dbg_kms(&dev_priv->drm,
			    "Wrong MCH_SSKPD value: 0x%08x This can cause underruns.\n",
			    पंचांगp);
पूर्ण

अटल व्योम gen6_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 dspclk_gate = ILK_VRHUNIT_CLOCK_GATE_DISABLE;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DSPCLK_GATE_D, dspclk_gate);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2) |
		   ILK_ELPIN_409_SELECT);

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_UCGCTL1) |
		   GEN6_BLBUNIT_CLOCK_GATE_DISABLE |
		   GEN6_CSUNIT_CLOCK_GATE_DISABLE);

	/* According to the BSpec vol1g, bit 12 (RCPBUNIT) घड़ी
	 * gating disable must be set.  Failure to set it results in
	 * flickering pixels due to Z ग_लिखो ordering failures after
	 * some amount of runसमय in the Mesa "fire" demo, and Unigine
	 * Sanctuary and Tropics, and apparently anything अन्यथा with
	 * alpha test or pixel discard.
	 *
	 * According to the spec, bit 11 (RCCUNIT) must also be set,
	 * but we didn't debug actual testहालs to find it out.
	 *
	 * WaDisableRCCUnitClockGating:snb
	 * WaDisableRCPBUnitClockGating:snb
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL2,
		   GEN6_RCPBUNIT_CLOCK_GATE_DISABLE |
		   GEN6_RCCUNIT_CLOCK_GATE_DISABLE);

	/*
	 * According to the spec the following bits should be
	 * set in order to enable memory self-refresh and fbc:
	 * The bit21 and bit22 of 0x42000
	 * The bit21 and bit22 of 0x42004
	 * The bit5 and bit7 of 0x42020
	 * The bit14 of 0x70180
	 * The bit14 of 0x71180
	 *
	 * WaFbcAsynchFlipDisableFbcQueue:snb
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN1) |
		   ILK_FBCQ_DIS | ILK_PABSTRETCH_DIS);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN2) |
		   ILK_DPARB_GATE | ILK_VSDPFD_FULL);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DSPCLK_GATE_D,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DSPCLK_GATE_D) |
		   ILK_DPARBUNIT_CLOCK_GATE_ENABLE  |
		   ILK_DPFDUNIT_CLOCK_GATE_ENABLE);

	g4x_disable_trickle_feed(dev_priv);

	cpt_init_घड़ी_gating(dev_priv);

	gen6_check_mch_setup(dev_priv);
पूर्ण

अटल व्योम lpt_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * TODO: this bit should only be enabled when really needed, then
	 * disabled when not needed anymore in order to save घातer.
	 */
	अगर (HAS_PCH_LPT_LP(dev_priv))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D,
			   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D) |
			   PCH_LP_PARTITION_LEVEL_DISABLE);

	/* WADPOClockGatingDisable:hsw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, TRANS_CHICKEN1(PIPE_A),
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, TRANS_CHICKEN1(PIPE_A)) |
		   TRANS_CHICKEN1_DP0UNIT_GC_DISABLE);
पूर्ण

अटल व्योम lpt_suspend_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_PCH_LPT_LP(dev_priv)) अणु
		u32 val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D);

		val &= ~PCH_LP_PARTITION_LEVEL_DISABLE;
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D, val);
	पूर्ण
पूर्ण

अटल व्योम gen8_set_l3sqc_credits(काष्ठा drm_i915_निजी *dev_priv,
				   पूर्णांक general_prio_credits,
				   पूर्णांक high_prio_credits)
अणु
	u32 misccpctl;
	u32 val;

	/* WaTempDisableDOPClkGating:bdw */
	misccpctl = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_MISCCPCTL);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_MISCCPCTL, misccpctl & ~GEN7_DOP_CLOCK_GATE_ENABLE);

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_L3SQCREG1);
	val &= ~L3_PRIO_CREDITS_MASK;
	val |= L3_GENERAL_PRIO_CREDITS(general_prio_credits);
	val |= L3_HIGH_PRIO_CREDITS(high_prio_credits);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_L3SQCREG1, val);

	/*
	 * Wait at least 100 घड़ीs beक्रमe re-enabling घड़ी gating.
	 * See the definition of L3SQCREG1 in BSpec.
	 */
	पूर्णांकel_uncore_posting_पढ़ो(&dev_priv->uncore, GEN8_L3SQCREG1);
	udelay(1);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_MISCCPCTL, misccpctl);
पूर्ण

अटल व्योम icl_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* Wa_1409120013:icl,ehl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN,
		   ILK_DPFC_CHICKEN_COMP_DUMMY_PIXEL);

	/* This is not an Wa. Enable to reduce Sampler घातer */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN10_DFR_RATIO_EN_AND_CHICKEN,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN10_DFR_RATIO_EN_AND_CHICKEN) & ~DFR_DISABLE);

	/*Wa_14010594013:icl, ehl */
	पूर्णांकel_uncore_rmw(&dev_priv->uncore, GEN8_CHICKEN_DCPR_1,
			 0, CNL_DELAY_PMRSP);
पूर्ण

अटल व्योम gen12lp_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* Wa_1409120013:tgl,rkl,adl_s,dg1 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN,
			   ILK_DPFC_CHICKEN_COMP_DUMMY_PIXEL);

	/* Wa_1409825376:tgl (pre-prod)*/
	अगर (IS_TGL_DISPLAY_STEP(dev_priv, STEP_A0, STEP_B1))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN9_CLKGATE_DIS_3, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN9_CLKGATE_DIS_3) |
			   TGL_VRH_GATING_DIS);

	/* Wa_14011059788:tgl,rkl,adl_s,dg1 */
	पूर्णांकel_uncore_rmw(&dev_priv->uncore, GEN10_DFR_RATIO_EN_AND_CHICKEN,
			 0, DFR_DISABLE);
पूर्ण

अटल व्योम dg1_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen12lp_init_घड़ी_gating(dev_priv);

	/* Wa_1409836686:dg1[a0] */
	अगर (IS_DG1_REVID(dev_priv, DG1_REVID_A0, DG1_REVID_A0))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN9_CLKGATE_DIS_3, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN9_CLKGATE_DIS_3) |
			   DPT_GATING_DIS);
पूर्ण

अटल व्योम cnp_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_PCH_CNP(dev_priv))
		वापस;

	/* Display WA #1181 WaSouthDisplayDisablePWMCGEGating: cnp */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SOUTH_DSPCLK_GATE_D) |
		   CNP_PWM_CGE_GATING_DISABLE);
पूर्ण

अटल व्योम cnl_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;
	cnp_init_घड़ी_gating(dev_priv);

	/* This is not an Wa. Enable क्रम better image quality */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, _3D_CHICKEN3,
		   _MASKED_BIT_ENABLE(_3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE));

	/* WaEnableChickenDCPR:cnl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_CHICKEN_DCPR_1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_CHICKEN_DCPR_1) | MASK_WAKEMEM);

	/*
	 * WaFbcWakeMemOn:cnl
	 * Display WA #0859: cnl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		   DISP_FBC_MEMORY_WAKE);

	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SLICE_UNIT_LEVEL_CLKGATE);
	/* ReadHitWriteOnlyDisable:cnl */
	val |= RCCUNIT_CLKGATE_DIS;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SLICE_UNIT_LEVEL_CLKGATE, val);

	/* Wa_2201832410:cnl */
	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, SUBSLICE_UNIT_LEVEL_CLKGATE);
	val |= GWUNIT_CLKGATE_DIS;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SUBSLICE_UNIT_LEVEL_CLKGATE, val);

	/* WaDisableVFclkgate:cnl */
	/* WaVFUnitClockGatingDisable:cnl */
	val = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, UNSLICE_UNIT_LEVEL_CLKGATE);
	val |= VFUNIT_CLKGATE_DIS;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, UNSLICE_UNIT_LEVEL_CLKGATE, val);
पूर्ण

अटल व्योम cfl_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	cnp_init_घड़ी_gating(dev_priv);
	gen9_init_घड़ी_gating(dev_priv);

	/* WAC6entrylatency:cfl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FBC_LLC_READ_CTRL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FBC_LLC_READ_CTRL) |
		   FBC_LLC_FULLY_OPEN);

	/*
	 * WaFbcTurnOffFbcWatermark:cfl
	 * Display WA #0562: cfl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		   DISP_FBC_WM_DIS);

	/*
	 * WaFbcNukeOnHostModअगरy:cfl
	 * Display WA #0873: cfl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DPFC_CHICKEN) |
		   ILK_DPFC_NUKE_ON_ANY_MODIFICATION);
पूर्ण

अटल व्योम kbl_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen9_init_घड़ी_gating(dev_priv);

	/* WAC6entrylatency:kbl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FBC_LLC_READ_CTRL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FBC_LLC_READ_CTRL) |
		   FBC_LLC_FULLY_OPEN);

	/* WaDisableSDEUnitClockGating:kbl */
	अगर (IS_KBL_GT_STEP(dev_priv, 0, STEP_B0))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_UCGCTL6, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_UCGCTL6) |
			   GEN8_SDEUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableGamClockGating:kbl */
	अगर (IS_KBL_GT_STEP(dev_priv, 0, STEP_B0))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL1, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_UCGCTL1) |
			   GEN6_GAMUNIT_CLOCK_GATE_DISABLE);

	/*
	 * WaFbcTurnOffFbcWatermark:kbl
	 * Display WA #0562: kbl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		   DISP_FBC_WM_DIS);

	/*
	 * WaFbcNukeOnHostModअगरy:kbl
	 * Display WA #0873: kbl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DPFC_CHICKEN) |
		   ILK_DPFC_NUKE_ON_ANY_MODIFICATION);
पूर्ण

अटल व्योम skl_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	gen9_init_घड़ी_gating(dev_priv);

	/* WaDisableDopClockGating:skl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_MISCCPCTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_MISCCPCTL) &
		   ~GEN7_DOP_CLOCK_GATE_ENABLE);

	/* WAC6entrylatency:skl */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, FBC_LLC_READ_CTRL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, FBC_LLC_READ_CTRL) |
		   FBC_LLC_FULLY_OPEN);

	/*
	 * WaFbcTurnOffFbcWatermark:skl
	 * Display WA #0562: skl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DISP_ARB_CTL, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, DISP_ARB_CTL) |
		   DISP_FBC_WM_DIS);

	/*
	 * WaFbcNukeOnHostModअगरy:skl
	 * Display WA #0873: skl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DPFC_CHICKEN) |
		   ILK_DPFC_NUKE_ON_ANY_MODIFICATION);

	/*
	 * WaFbcHighMemBwCorruptionAव्योमance:skl
	 * Display WA #0883: skl
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DPFC_CHICKEN, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DPFC_CHICKEN) |
		   ILK_DPFC_DISABLE_DUMMY0);
पूर्ण

अटल व्योम bdw_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत pipe pipe;

	/* WaFbcAsynchFlipDisableFbcQueue:hsw,bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PIPESL_1(PIPE_A),
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PIPESL_1(PIPE_A)) |
		   HSW_FBCQ_DIS);

	/* WaSwitchSolVfFArbitrationPriority:bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GAM_ECOCHK, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GAM_ECOCHK) | HSW_ECOCHK_ARB_PRIO_SOL);

	/* WaPsrDPAMaskVBlankInSRD:bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PAR1_1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PAR1_1) | DPA_MASK_VBLANK_SRD);

	क्रम_each_pipe(dev_priv, pipe) अणु
		/* WaPsrDPRSUnmaskVBlankInSRD:bdw */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PIPESL_1(pipe),
			   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PIPESL_1(pipe)) |
			   BDW_DPRS_MASK_VBLANK_SRD);

		/* Unकरोcumented but fixes async flip + VT-d corruption */
		अगर (पूर्णांकel_vtd_active())
			पूर्णांकel_uncore_rmw(&dev_priv->uncore, CHICKEN_PIPESL_1(pipe),
					 HSW_PRI_STRETCH_MAX_MASK, HSW_PRI_STRETCH_MAX_X1);
	पूर्ण

	/* WaVSRefCountFullक्रमceMissDisable:bdw */
	/* WaDSRefCountFullक्रमceMissDisable:bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_FF_THREAD_MODE,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_FF_THREAD_MODE) &
		   ~(GEN8_FF_DS_REF_CNT_FFME | GEN7_FF_VS_REF_CNT_FFME));

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_RC_SLEEP_PSMI_CONTROL,
		   _MASKED_BIT_ENABLE(GEN8_RC_SEMA_IDLE_MSG_DISABLE));

	/* WaDisableSDEUnitClockGating:bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_UCGCTL6, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_UCGCTL6) |
		   GEN8_SDEUNIT_CLOCK_GATE_DISABLE);

	/* WaProgramL3SqcReg1Default:bdw */
	gen8_set_l3sqc_credits(dev_priv, 30, 2);

	/* WaKVMNotअगरicationOnConfigChange:bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PAR2_1, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PAR2_1)
		   | KVM_CONFIG_CHANGE_NOTIFICATION_SELECT);

	lpt_init_घड़ी_gating(dev_priv);

	/* WaDisableDopClockGating:bdw
	 *
	 * Also see the CHICKEN2 ग_लिखो in bdw_init_workarounds() to disable DOP
	 * घड़ी gating.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_UCGCTL1) | GEN6_EU_TCUNIT_CLOCK_GATE_DISABLE);
पूर्ण

अटल व्योम hsw_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत pipe pipe;

	/* WaFbcAsynchFlipDisableFbcQueue:hsw,bdw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, CHICKEN_PIPESL_1(PIPE_A),
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, CHICKEN_PIPESL_1(PIPE_A)) |
		   HSW_FBCQ_DIS);

	क्रम_each_pipe(dev_priv, pipe) अणु
		/* Unकरोcumented but fixes async flip + VT-d corruption */
		अगर (पूर्णांकel_vtd_active())
			पूर्णांकel_uncore_rmw(&dev_priv->uncore, CHICKEN_PIPESL_1(pipe),
					 HSW_PRI_STRETCH_MAX_MASK, HSW_PRI_STRETCH_MAX_X1);
	पूर्ण

	/* This is required by WaCatErrorRejectionIssue:hsw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_SQ_CHICKEN_MBCUNIT_CONFIG,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_SQ_CHICKEN_MBCUNIT_CONFIG) |
		   GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB);

	/* WaSwitchSolVfFArbitrationPriority:hsw */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GAM_ECOCHK, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GAM_ECOCHK) | HSW_ECOCHK_ARB_PRIO_SOL);

	lpt_init_घड़ी_gating(dev_priv);
पूर्ण

अटल व्योम ivb_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 snpcr;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DSPCLK_GATE_D, ILK_VRHUNIT_CLOCK_GATE_DISABLE);

	/* WaFbcAsynchFlipDisableFbcQueue:ivb */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN1,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, ILK_DISPLAY_CHICKEN1) |
		   ILK_FBCQ_DIS);

	/* WaDisableBackToBackFlipFix:ivb */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, IVB_CHICKEN3,
		   CHICKEN3_DGMG_REQ_OUT_FIX_DISABLE |
		   CHICKEN3_DGMG_DONE_FIX_DISABLE);

	अगर (IS_IVB_GT1(dev_priv))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_ROW_CHICKEN2,
			   _MASKED_BIT_ENABLE(DOP_CLOCK_GATING_DISABLE));
	अन्यथा अणु
		/* must ग_लिखो both रेजिस्टरs */
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_ROW_CHICKEN2,
			   _MASKED_BIT_ENABLE(DOP_CLOCK_GATING_DISABLE));
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_ROW_CHICKEN2_GT2,
			   _MASKED_BIT_ENABLE(DOP_CLOCK_GATING_DISABLE));
	पूर्ण

	/*
	 * According to the spec, bit 13 (RCZUNIT) must be set on IVB.
	 * This implements the WaDisableRCZUnitClockGating:ivb workaround.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL2,
		   GEN6_RCZUNIT_CLOCK_GATE_DISABLE);

	/* This is required by WaCatErrorRejectionIssue:ivb */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_SQ_CHICKEN_MBCUNIT_CONFIG,
			पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_SQ_CHICKEN_MBCUNIT_CONFIG) |
			GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB);

	g4x_disable_trickle_feed(dev_priv);

	snpcr = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_MBCUNIT_SNPCR);
	snpcr &= ~GEN6_MBC_SNPCR_MASK;
	snpcr |= GEN6_MBC_SNPCR_MED;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_MBCUNIT_SNPCR, snpcr);

	अगर (!HAS_PCH_NOP(dev_priv))
		cpt_init_घड़ी_gating(dev_priv);

	gen6_check_mch_setup(dev_priv);
पूर्ण

अटल व्योम vlv_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* WaDisableBackToBackFlipFix:vlv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, IVB_CHICKEN3,
		   CHICKEN3_DGMG_REQ_OUT_FIX_DISABLE |
		   CHICKEN3_DGMG_DONE_FIX_DISABLE);

	/* WaDisableDopClockGating:vlv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_ROW_CHICKEN2,
		   _MASKED_BIT_ENABLE(DOP_CLOCK_GATING_DISABLE));

	/* This is required by WaCatErrorRejectionIssue:vlv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_SQ_CHICKEN_MBCUNIT_CONFIG,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_SQ_CHICKEN_MBCUNIT_CONFIG) |
		   GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB);

	/*
	 * According to the spec, bit 13 (RCZUNIT) must be set on IVB.
	 * This implements the WaDisableRCZUnitClockGating:vlv workaround.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL2,
		   GEN6_RCZUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableL3Bank2xClockGate:vlv
	 * Disabling L3 घड़ी gating- MMIO 940c[25] = 1
	 * Set bit 25, to disable L3_BANK_2x_CLK_GATING */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_UCGCTL4,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_UCGCTL4) | GEN7_L3BANK2X_CLOCK_GATE_DISABLE);

	/*
	 * WaDisableVLVClockGating_VBIIssue:vlv
	 * Disable घड़ी gating on th GCFG unit to prevent a delay
	 * in the reporting of vblank events.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, VLV_GUNIT_CLOCK_GATE, GCFG_DIS);
पूर्ण

अटल व्योम chv_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* WaVSRefCountFullक्रमceMissDisable:chv */
	/* WaDSRefCountFullक्रमceMissDisable:chv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN7_FF_THREAD_MODE,
		   पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN7_FF_THREAD_MODE) &
		   ~(GEN8_FF_DS_REF_CNT_FFME | GEN7_FF_VS_REF_CNT_FFME));

	/* WaDisableSemaphoreAndSyncFlipWait:chv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_RC_SLEEP_PSMI_CONTROL,
		   _MASKED_BIT_ENABLE(GEN8_RC_SEMA_IDLE_MSG_DISABLE));

	/* WaDisableCSUnitClockGating:chv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN6_UCGCTL1, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN6_UCGCTL1) |
		   GEN6_CSUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableSDEUnitClockGating:chv */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, GEN8_UCGCTL6, पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, GEN8_UCGCTL6) |
		   GEN8_SDEUNIT_CLOCK_GATE_DISABLE);

	/*
	 * WaProgramL3SqcReg1Default:chv
	 * See gfxspecs/Related Documents/Perक्रमmance Guide/
	 * LSQC Setting Recommendations.
	 */
	gen8_set_l3sqc_credits(dev_priv, 38, 2);
पूर्ण

अटल व्योम g4x_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 dspclk_gate;

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RENCLK_GATE_D1, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RENCLK_GATE_D2, VF_UNIT_CLOCK_GATE_DISABLE |
		   GS_UNIT_CLOCK_GATE_DISABLE |
		   CL_UNIT_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RAMCLK_GATE_D, 0);
	dspclk_gate = VRHUNIT_CLOCK_GATE_DISABLE |
		OVRUNIT_CLOCK_GATE_DISABLE |
		OVCUNIT_CLOCK_GATE_DISABLE;
	अगर (IS_GM45(dev_priv))
		dspclk_gate |= DSSUNIT_CLOCK_GATE_DISABLE;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, DSPCLK_GATE_D, dspclk_gate);

	g4x_disable_trickle_feed(dev_priv);
पूर्ण

अटल व्योम i965gm_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;

	पूर्णांकel_uncore_ग_लिखो(uncore, RENCLK_GATE_D1, I965_RCC_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_ग_लिखो(uncore, RENCLK_GATE_D2, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, DSPCLK_GATE_D, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, RAMCLK_GATE_D, 0);
	पूर्णांकel_uncore_ग_लिखो16(uncore, DEUC, 0);
	पूर्णांकel_uncore_ग_लिखो(uncore,
			   MI_ARB_STATE,
			   _MASKED_BIT_ENABLE(MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE));
पूर्ण

अटल व्योम i965g_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RENCLK_GATE_D1, I965_RCZ_CLOCK_GATE_DISABLE |
		   I965_RCC_CLOCK_GATE_DISABLE |
		   I965_RCPB_CLOCK_GATE_DISABLE |
		   I965_ISC_CLOCK_GATE_DISABLE |
		   I965_FBC_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RENCLK_GATE_D2, 0);
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, MI_ARB_STATE,
		   _MASKED_BIT_ENABLE(MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE));
पूर्ण

अटल व्योम gen3_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 dstate = पूर्णांकel_uncore_पढ़ो(&dev_priv->uncore, D_STATE);

	dstate |= DSTATE_PLL_D3_OFF | DSTATE_GFX_CLOCK_GATING |
		DSTATE_DOT_CLOCK_GATING;
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, D_STATE, dstate);

	अगर (IS_PINEVIEW(dev_priv))
		पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ECOSKPD, _MASKED_BIT_ENABLE(ECO_GATING_CX_ONLY));

	/* IIR "flip pending" means करोne अगर this bit is set */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, ECOSKPD, _MASKED_BIT_DISABLE(ECO_FLIP_DONE));

	/* पूर्णांकerrupts should cause a wake up from C3 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, INSTPM, _MASKED_BIT_ENABLE(INSTPM_AGPBUSY_INT_EN));

	/* On GEN3 we really need to make sure the ARB C3 LP bit is set */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, MI_ARB_STATE, _MASKED_BIT_ENABLE(MI_ARB_C3_LP_WRITE_ENABLE));

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, MI_ARB_STATE,
		   _MASKED_BIT_ENABLE(MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE));
पूर्ण

अटल व्योम i85x_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, RENCLK_GATE_D1, SV_CLOCK_GATE_DISABLE);

	/* पूर्णांकerrupts should cause a wake up from C3 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, MI_STATE, _MASKED_BIT_ENABLE(MI_AGPBUSY_INT_EN) |
		   _MASKED_BIT_DISABLE(MI_AGPBUSY_830_MODE));

	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, MEM_MODE,
		   _MASKED_BIT_ENABLE(MEM_DISPLAY_TRICKLE_FEED_DISABLE));

	/*
	 * Have FBC ignore 3D activity since we use software
	 * render tracking, and otherwise a pure 3D workload
	 * (even अगर it just renders a single frame and then करोes
	 * abosultely nothing) would not allow FBC to recompress
	 * until a 2D blit occurs.
	 */
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, SCPD0,
		   _MASKED_BIT_ENABLE(SCPD_FBC_IGNORE_3D));
पूर्ण

अटल व्योम i830_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_uncore_ग_लिखो(&dev_priv->uncore, MEM_MODE,
		   _MASKED_BIT_ENABLE(MEM_DISPLAY_A_TRICKLE_FEED_DISABLE) |
		   _MASKED_BIT_ENABLE(MEM_DISPLAY_B_TRICKLE_FEED_DISABLE));
पूर्ण

व्योम पूर्णांकel_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	dev_priv->display.init_घड़ी_gating(dev_priv);
पूर्ण

व्योम पूर्णांकel_suspend_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_PCH_LPT(dev_priv))
		lpt_suspend_hw(dev_priv);
पूर्ण

अटल व्योम nop_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv)
अणु
	drm_dbg_kms(&dev_priv->drm,
		    "No clock gating settings or workarounds applied.\n");
पूर्ण

/**
 * पूर्णांकel_init_घड़ी_gating_hooks - setup the घड़ी gating hooks
 * @dev_priv: device निजी
 *
 * Setup the hooks that configure which घड़ीs of a given platक्रमm can be
 * gated and also apply various GT and display specअगरic workarounds क्रम these
 * platक्रमms. Note that some GT specअगरic workarounds are applied separately
 * when GPU contexts or batchbuffers start their execution.
 */
व्योम पूर्णांकel_init_घड़ी_gating_hooks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_DG1(dev_priv))
		dev_priv->display.init_घड़ी_gating = dg1_init_घड़ी_gating;
	अन्यथा अगर (IS_GEN(dev_priv, 12))
		dev_priv->display.init_घड़ी_gating = gen12lp_init_घड़ी_gating;
	अन्यथा अगर (IS_GEN(dev_priv, 11))
		dev_priv->display.init_घड़ी_gating = icl_init_घड़ी_gating;
	अन्यथा अगर (IS_CANNONLAKE(dev_priv))
		dev_priv->display.init_घड़ी_gating = cnl_init_घड़ी_gating;
	अन्यथा अगर (IS_COFFEELAKE(dev_priv) || IS_COMETLAKE(dev_priv))
		dev_priv->display.init_घड़ी_gating = cfl_init_घड़ी_gating;
	अन्यथा अगर (IS_SKYLAKE(dev_priv))
		dev_priv->display.init_घड़ी_gating = skl_init_घड़ी_gating;
	अन्यथा अगर (IS_KABYLAKE(dev_priv))
		dev_priv->display.init_घड़ी_gating = kbl_init_घड़ी_gating;
	अन्यथा अगर (IS_BROXTON(dev_priv))
		dev_priv->display.init_घड़ी_gating = bxt_init_घड़ी_gating;
	अन्यथा अगर (IS_GEMINILAKE(dev_priv))
		dev_priv->display.init_घड़ी_gating = glk_init_घड़ी_gating;
	अन्यथा अगर (IS_BROADWELL(dev_priv))
		dev_priv->display.init_घड़ी_gating = bdw_init_घड़ी_gating;
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		dev_priv->display.init_घड़ी_gating = chv_init_घड़ी_gating;
	अन्यथा अगर (IS_HASWELL(dev_priv))
		dev_priv->display.init_घड़ी_gating = hsw_init_घड़ी_gating;
	अन्यथा अगर (IS_IVYBRIDGE(dev_priv))
		dev_priv->display.init_घड़ी_gating = ivb_init_घड़ी_gating;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		dev_priv->display.init_घड़ी_gating = vlv_init_घड़ी_gating;
	अन्यथा अगर (IS_GEN(dev_priv, 6))
		dev_priv->display.init_घड़ी_gating = gen6_init_घड़ी_gating;
	अन्यथा अगर (IS_GEN(dev_priv, 5))
		dev_priv->display.init_घड़ी_gating = ilk_init_घड़ी_gating;
	अन्यथा अगर (IS_G4X(dev_priv))
		dev_priv->display.init_घड़ी_gating = g4x_init_घड़ी_gating;
	अन्यथा अगर (IS_I965GM(dev_priv))
		dev_priv->display.init_घड़ी_gating = i965gm_init_घड़ी_gating;
	अन्यथा अगर (IS_I965G(dev_priv))
		dev_priv->display.init_घड़ी_gating = i965g_init_घड़ी_gating;
	अन्यथा अगर (IS_GEN(dev_priv, 3))
		dev_priv->display.init_घड़ी_gating = gen3_init_घड़ी_gating;
	अन्यथा अगर (IS_I85X(dev_priv) || IS_I865G(dev_priv))
		dev_priv->display.init_घड़ी_gating = i85x_init_घड़ी_gating;
	अन्यथा अगर (IS_GEN(dev_priv, 2))
		dev_priv->display.init_घड़ी_gating = i830_init_घड़ी_gating;
	अन्यथा अणु
		MISSING_CASE(INTEL_DEVID(dev_priv));
		dev_priv->display.init_घड़ी_gating = nop_init_घड़ी_gating;
	पूर्ण
पूर्ण

/* Set up chip specअगरic घातer management-related functions */
व्योम पूर्णांकel_init_pm(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* For cxsr */
	अगर (IS_PINEVIEW(dev_priv))
		pnv_get_mem_freq(dev_priv);
	अन्यथा अगर (IS_GEN(dev_priv, 5))
		ilk_get_mem_freq(dev_priv);

	अगर (पूर्णांकel_has_sagv(dev_priv))
		skl_setup_sagv_block_समय(dev_priv);

	/* For FIFO watermark updates */
	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		skl_setup_wm_latency(dev_priv);
		dev_priv->display.compute_global_watermarks = skl_compute_wm;
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		ilk_setup_wm_latency(dev_priv);

		अगर ((IS_DISPLAY_VER(dev_priv, 5) && dev_priv->wm.pri_latency[1] &&
		     dev_priv->wm.spr_latency[1] && dev_priv->wm.cur_latency[1]) ||
		    (!IS_DISPLAY_VER(dev_priv, 5) && dev_priv->wm.pri_latency[0] &&
		     dev_priv->wm.spr_latency[0] && dev_priv->wm.cur_latency[0])) अणु
			dev_priv->display.compute_pipe_wm = ilk_compute_pipe_wm;
			dev_priv->display.compute_पूर्णांकermediate_wm =
				ilk_compute_पूर्णांकermediate_wm;
			dev_priv->display.initial_watermarks =
				ilk_initial_watermarks;
			dev_priv->display.optimize_watermarks =
				ilk_optimize_watermarks;
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Failed to read display plane latency. "
				    "Disable CxSR\n");
		पूर्ण
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		vlv_setup_wm_latency(dev_priv);
		dev_priv->display.compute_pipe_wm = vlv_compute_pipe_wm;
		dev_priv->display.compute_पूर्णांकermediate_wm = vlv_compute_पूर्णांकermediate_wm;
		dev_priv->display.initial_watermarks = vlv_initial_watermarks;
		dev_priv->display.optimize_watermarks = vlv_optimize_watermarks;
		dev_priv->display.atomic_update_watermarks = vlv_atomic_update_fअगरo;
	पूर्ण अन्यथा अगर (IS_G4X(dev_priv)) अणु
		g4x_setup_wm_latency(dev_priv);
		dev_priv->display.compute_pipe_wm = g4x_compute_pipe_wm;
		dev_priv->display.compute_पूर्णांकermediate_wm = g4x_compute_पूर्णांकermediate_wm;
		dev_priv->display.initial_watermarks = g4x_initial_watermarks;
		dev_priv->display.optimize_watermarks = g4x_optimize_watermarks;
	पूर्ण अन्यथा अगर (IS_PINEVIEW(dev_priv)) अणु
		अगर (!पूर्णांकel_get_cxsr_latency(!IS_MOBILE(dev_priv),
					    dev_priv->is_ddr3,
					    dev_priv->fsb_freq,
					    dev_priv->mem_freq)) अणु
			drm_info(&dev_priv->drm,
				 "failed to find known CxSR latency "
				 "(found ddr%s fsb freq %d, mem freq %d), "
				 "disabling CxSR\n",
				 (dev_priv->is_ddr3 == 1) ? "3" : "2",
				 dev_priv->fsb_freq, dev_priv->mem_freq);
			/* Disable CxSR and never update its watermark again */
			पूर्णांकel_set_memory_cxsr(dev_priv, false);
			dev_priv->display.update_wm = शून्य;
		पूर्ण अन्यथा
			dev_priv->display.update_wm = pnv_update_wm;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 4)) अणु
		dev_priv->display.update_wm = i965_update_wm;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 3)) अणु
		dev_priv->display.update_wm = i9xx_update_wm;
		dev_priv->display.get_fअगरo_size = i9xx_get_fअगरo_size;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 2)) अणु
		अगर (INTEL_NUM_PIPES(dev_priv) == 1) अणु
			dev_priv->display.update_wm = i845_update_wm;
			dev_priv->display.get_fअगरo_size = i845_get_fअगरo_size;
		पूर्ण अन्यथा अणु
			dev_priv->display.update_wm = i9xx_update_wm;
			dev_priv->display.get_fअगरo_size = i830_get_fअगरo_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		drm_err(&dev_priv->drm,
			"unexpected fall-through in %s\n", __func__);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pm_setup(काष्ठा drm_i915_निजी *dev_priv)
अणु
	dev_priv->runसमय_pm.suspended = false;
	atomic_set(&dev_priv->runसमय_pm.wakeref_count, 0);
पूर्ण

अटल काष्ठा पूर्णांकel_global_state *पूर्णांकel_dbuf_duplicate_state(काष्ठा पूर्णांकel_global_obj *obj)
अणु
	काष्ठा पूर्णांकel_dbuf_state *dbuf_state;

	dbuf_state = kmemdup(obj->state, माप(*dbuf_state), GFP_KERNEL);
	अगर (!dbuf_state)
		वापस शून्य;

	वापस &dbuf_state->base;
पूर्ण

अटल व्योम पूर्णांकel_dbuf_destroy_state(काष्ठा पूर्णांकel_global_obj *obj,
				     काष्ठा पूर्णांकel_global_state *state)
अणु
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_global_state_funcs पूर्णांकel_dbuf_funcs = अणु
	.atomic_duplicate_state = पूर्णांकel_dbuf_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_dbuf_destroy_state,
पूर्ण;

काष्ठा पूर्णांकel_dbuf_state *
पूर्णांकel_atomic_get_dbuf_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_global_state *dbuf_state;

	dbuf_state = पूर्णांकel_atomic_get_global_obj_state(state, &dev_priv->dbuf.obj);
	अगर (IS_ERR(dbuf_state))
		वापस ERR_CAST(dbuf_state);

	वापस to_पूर्णांकel_dbuf_state(dbuf_state);
पूर्ण

पूर्णांक पूर्णांकel_dbuf_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_dbuf_state *dbuf_state;

	dbuf_state = kzalloc(माप(*dbuf_state), GFP_KERNEL);
	अगर (!dbuf_state)
		वापस -ENOMEM;

	पूर्णांकel_atomic_global_obj_init(dev_priv, &dev_priv->dbuf.obj,
				     &dbuf_state->base, &पूर्णांकel_dbuf_funcs);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_dbuf_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_dbuf_state *new_dbuf_state =
		पूर्णांकel_atomic_get_new_dbuf_state(state);
	स्थिर काष्ठा पूर्णांकel_dbuf_state *old_dbuf_state =
		पूर्णांकel_atomic_get_old_dbuf_state(state);

	अगर (!new_dbuf_state ||
	    new_dbuf_state->enabled_slices == old_dbuf_state->enabled_slices)
		वापस;

	WARN_ON(!new_dbuf_state->base.changed);

	gen9_dbuf_slices_update(dev_priv,
				old_dbuf_state->enabled_slices |
				new_dbuf_state->enabled_slices);
पूर्ण

व्योम पूर्णांकel_dbuf_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_dbuf_state *new_dbuf_state =
		पूर्णांकel_atomic_get_new_dbuf_state(state);
	स्थिर काष्ठा पूर्णांकel_dbuf_state *old_dbuf_state =
		पूर्णांकel_atomic_get_old_dbuf_state(state);

	अगर (!new_dbuf_state ||
	    new_dbuf_state->enabled_slices == old_dbuf_state->enabled_slices)
		वापस;

	WARN_ON(!new_dbuf_state->base.changed);

	gen9_dbuf_slices_update(dev_priv,
				new_dbuf_state->enabled_slices);
पूर्ण
