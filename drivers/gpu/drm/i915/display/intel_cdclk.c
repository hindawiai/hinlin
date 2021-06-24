<शैली गुरु>
/*
 * Copyright तऊ 2006-2017 Intel Corporation
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

#समावेश <linux/समय.स>

#समावेश "intel_atomic.h"
#समावेश "intel_bw.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_display_types.h"
#समावेश "intel_sideband.h"

/**
 * DOC: CDCLK / RAWCLK
 *
 * The display engine uses several dअगरferent घड़ीs to करो its work. There
 * are two मुख्य घड़ीs involved that aren't directly related to the actual
 * pixel घड़ी or any symbol/bit घड़ी of the actual output port. These
 * are the core display घड़ी (CDCLK) and RAWCLK.
 *
 * CDCLK घड़ीs most of the display pipe logic, and thus its frequency
 * must be high enough to support the rate at which pixels are flowing
 * through the pipes. Downscaling must also be accounted as that increases
 * the effective pixel rate.
 *
 * On several platक्रमms the CDCLK frequency can be changed dynamically
 * to minimize घातer consumption क्रम a given display configuration.
 * Typically changes to the CDCLK frequency require all the display pipes
 * to be shut करोwn जबतक the frequency is being changed.
 *
 * On SKL+ the DMC will toggle the CDCLK off/on during DC5/6 entry/निकास.
 * DMC will not change the active CDCLK frequency however, so that part
 * will still be perक्रमmed by the driver directly.
 *
 * RAWCLK is a fixed frequency घड़ी, often used by various auxiliary
 * blocks such as AUX CH or backlight PWM. Hence the only thing we
 * really need to know about RAWCLK is its frequency so that various
 * भागiders can be programmed correctly.
 */

अटल व्योम fixed_133mhz_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	cdclk_config->cdclk = 133333;
पूर्ण

अटल व्योम fixed_200mhz_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	cdclk_config->cdclk = 200000;
पूर्ण

अटल व्योम fixed_266mhz_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	cdclk_config->cdclk = 266667;
पूर्ण

अटल व्योम fixed_333mhz_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	cdclk_config->cdclk = 333333;
पूर्ण

अटल व्योम fixed_400mhz_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	cdclk_config->cdclk = 400000;
पूर्ण

अटल व्योम fixed_450mhz_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	cdclk_config->cdclk = 450000;
पूर्ण

अटल व्योम i85x_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u16 hpllcc = 0;

	/*
	 * 852GM/852GMV only supports 133 MHz and the HPLLCC
	 * encoding is dअगरferent :(
	 * FIXME is this the right way to detect 852GM/852GMV?
	 */
	अगर (pdev->revision == 0x1) अणु
		cdclk_config->cdclk = 133333;
		वापस;
	पूर्ण

	pci_bus_पढ़ो_config_word(pdev->bus,
				 PCI_DEVFN(0, 3), HPLLCC, &hpllcc);

	/* Assume that the hardware is in the high speed state.  This
	 * should be the शेष.
	 */
	चयन (hpllcc & GC_CLOCK_CONTROL_MASK) अणु
	हाल GC_CLOCK_133_200:
	हाल GC_CLOCK_133_200_2:
	हाल GC_CLOCK_100_200:
		cdclk_config->cdclk = 200000;
		अवरोध;
	हाल GC_CLOCK_166_250:
		cdclk_config->cdclk = 250000;
		अवरोध;
	हाल GC_CLOCK_100_133:
		cdclk_config->cdclk = 133333;
		अवरोध;
	हाल GC_CLOCK_133_266:
	हाल GC_CLOCK_133_266_2:
	हाल GC_CLOCK_166_266:
		cdclk_config->cdclk = 266667;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम i915gm_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u16 gcfgc = 0;

	pci_पढ़ो_config_word(pdev, GCFGC, &gcfgc);

	अगर (gcfgc & GC_LOW_FREQUENCY_ENABLE) अणु
		cdclk_config->cdclk = 133333;
		वापस;
	पूर्ण

	चयन (gcfgc & GC_DISPLAY_CLOCK_MASK) अणु
	हाल GC_DISPLAY_CLOCK_333_320_MHZ:
		cdclk_config->cdclk = 333333;
		अवरोध;
	शेष:
	हाल GC_DISPLAY_CLOCK_190_200_MHZ:
		cdclk_config->cdclk = 190000;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम i945gm_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u16 gcfgc = 0;

	pci_पढ़ो_config_word(pdev, GCFGC, &gcfgc);

	अगर (gcfgc & GC_LOW_FREQUENCY_ENABLE) अणु
		cdclk_config->cdclk = 133333;
		वापस;
	पूर्ण

	चयन (gcfgc & GC_DISPLAY_CLOCK_MASK) अणु
	हाल GC_DISPLAY_CLOCK_333_320_MHZ:
		cdclk_config->cdclk = 320000;
		अवरोध;
	शेष:
	हाल GC_DISPLAY_CLOCK_190_200_MHZ:
		cdclk_config->cdclk = 200000;
		अवरोध;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_hpll_vco(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अटल स्थिर अचिन्हित पूर्णांक blb_vco[8] = अणु
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 4800000,
		[4] = 6400000,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक pnv_vco[8] = अणु
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 4800000,
		[4] = 2666667,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक cl_vco[8] = अणु
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 6400000,
		[4] = 3333333,
		[5] = 3566667,
		[6] = 4266667,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक elk_vco[8] = अणु
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 4800000,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक ctg_vco[8] = अणु
		[0] = 3200000,
		[1] = 4000000,
		[2] = 5333333,
		[3] = 6400000,
		[4] = 2666667,
		[5] = 4266667,
	पूर्ण;
	स्थिर अचिन्हित पूर्णांक *vco_table;
	अचिन्हित पूर्णांक vco;
	u8 पंचांगp = 0;

	/* FIXME other chipsets? */
	अगर (IS_GM45(dev_priv))
		vco_table = ctg_vco;
	अन्यथा अगर (IS_G45(dev_priv))
		vco_table = elk_vco;
	अन्यथा अगर (IS_I965GM(dev_priv))
		vco_table = cl_vco;
	अन्यथा अगर (IS_PINEVIEW(dev_priv))
		vco_table = pnv_vco;
	अन्यथा अगर (IS_G33(dev_priv))
		vco_table = blb_vco;
	अन्यथा
		वापस 0;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
			    IS_PINEVIEW(dev_priv) || IS_MOBILE(dev_priv) ? HPLLVCO_MOBILE : HPLLVCO);

	vco = vco_table[पंचांगp & 0x7];
	अगर (vco == 0)
		drm_err(&dev_priv->drm, "Bad HPLL VCO (HPLLVCO=0x%02x)\n",
			पंचांगp);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm, "HPLL VCO %u kHz\n", vco);

	वापस vco;
पूर्ण

अटल व्योम g33_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	अटल स्थिर u8 भाग_3200[] = अणु 12, 10,  8,  7, 5, 16 पूर्ण;
	अटल स्थिर u8 भाग_4000[] = अणु 14, 12, 10,  8, 6, 20 पूर्ण;
	अटल स्थिर u8 भाग_4800[] = अणु 20, 14, 12, 10, 8, 24 पूर्ण;
	अटल स्थिर u8 भाग_5333[] = अणु 20, 16, 12, 12, 8, 28 पूर्ण;
	स्थिर u8 *भाग_प्रकारable;
	अचिन्हित पूर्णांक cdclk_sel;
	u16 पंचांगp = 0;

	cdclk_config->vco = पूर्णांकel_hpll_vco(dev_priv);

	pci_पढ़ो_config_word(pdev, GCFGC, &पंचांगp);

	cdclk_sel = (पंचांगp >> 4) & 0x7;

	अगर (cdclk_sel >= ARRAY_SIZE(भाग_3200))
		जाओ fail;

	चयन (cdclk_config->vco) अणु
	हाल 3200000:
		भाग_प्रकारable = भाग_3200;
		अवरोध;
	हाल 4000000:
		भाग_प्रकारable = भाग_4000;
		अवरोध;
	हाल 4800000:
		भाग_प्रकारable = भाग_4800;
		अवरोध;
	हाल 5333333:
		भाग_प्रकारable = भाग_5333;
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण

	cdclk_config->cdclk = DIV_ROUND_CLOSEST(cdclk_config->vco,
						भाग_प्रकारable[cdclk_sel]);
	वापस;

fail:
	drm_err(&dev_priv->drm,
		"Unable to determine CDCLK. HPLL VCO=%u kHz, CFGC=0x%08x\n",
		cdclk_config->vco, पंचांगp);
	cdclk_config->cdclk = 190476;
पूर्ण

अटल व्योम pnv_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	u16 gcfgc = 0;

	pci_पढ़ो_config_word(pdev, GCFGC, &gcfgc);

	चयन (gcfgc & GC_DISPLAY_CLOCK_MASK) अणु
	हाल GC_DISPLAY_CLOCK_267_MHZ_PNV:
		cdclk_config->cdclk = 266667;
		अवरोध;
	हाल GC_DISPLAY_CLOCK_333_MHZ_PNV:
		cdclk_config->cdclk = 333333;
		अवरोध;
	हाल GC_DISPLAY_CLOCK_444_MHZ_PNV:
		cdclk_config->cdclk = 444444;
		अवरोध;
	हाल GC_DISPLAY_CLOCK_200_MHZ_PNV:
		cdclk_config->cdclk = 200000;
		अवरोध;
	शेष:
		drm_err(&dev_priv->drm,
			"Unknown pnv display core clock 0x%04x\n", gcfgc);
		fallthrough;
	हाल GC_DISPLAY_CLOCK_133_MHZ_PNV:
		cdclk_config->cdclk = 133333;
		अवरोध;
	हाल GC_DISPLAY_CLOCK_167_MHZ_PNV:
		cdclk_config->cdclk = 166667;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम i965gm_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	अटल स्थिर u8 भाग_3200[] = अणु 16, 10,  8 पूर्ण;
	अटल स्थिर u8 भाग_4000[] = अणु 20, 12, 10 पूर्ण;
	अटल स्थिर u8 भाग_5333[] = अणु 24, 16, 14 पूर्ण;
	स्थिर u8 *भाग_प्रकारable;
	अचिन्हित पूर्णांक cdclk_sel;
	u16 पंचांगp = 0;

	cdclk_config->vco = पूर्णांकel_hpll_vco(dev_priv);

	pci_पढ़ो_config_word(pdev, GCFGC, &पंचांगp);

	cdclk_sel = ((पंचांगp >> 8) & 0x1f) - 1;

	अगर (cdclk_sel >= ARRAY_SIZE(भाग_3200))
		जाओ fail;

	चयन (cdclk_config->vco) अणु
	हाल 3200000:
		भाग_प्रकारable = भाग_3200;
		अवरोध;
	हाल 4000000:
		भाग_प्रकारable = भाग_4000;
		अवरोध;
	हाल 5333333:
		भाग_प्रकारable = भाग_5333;
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण

	cdclk_config->cdclk = DIV_ROUND_CLOSEST(cdclk_config->vco,
						भाग_प्रकारable[cdclk_sel]);
	वापस;

fail:
	drm_err(&dev_priv->drm,
		"Unable to determine CDCLK. HPLL VCO=%u kHz, CFGC=0x%04x\n",
		cdclk_config->vco, पंचांगp);
	cdclk_config->cdclk = 200000;
पूर्ण

अटल व्योम gm45_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			   काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_priv->drm.dev);
	अचिन्हित पूर्णांक cdclk_sel;
	u16 पंचांगp = 0;

	cdclk_config->vco = पूर्णांकel_hpll_vco(dev_priv);

	pci_पढ़ो_config_word(pdev, GCFGC, &पंचांगp);

	cdclk_sel = (पंचांगp >> 12) & 0x1;

	चयन (cdclk_config->vco) अणु
	हाल 2666667:
	हाल 4000000:
	हाल 5333333:
		cdclk_config->cdclk = cdclk_sel ? 333333 : 222222;
		अवरोध;
	हाल 3200000:
		cdclk_config->cdclk = cdclk_sel ? 320000 : 228571;
		अवरोध;
	शेष:
		drm_err(&dev_priv->drm,
			"Unable to determine CDCLK. HPLL VCO=%u, CFGC=0x%04x\n",
			cdclk_config->vco, पंचांगp);
		cdclk_config->cdclk = 222222;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hsw_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 lcpll = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	u32 freq = lcpll & LCPLL_CLK_FREQ_MASK;

	अगर (lcpll & LCPLL_CD_SOURCE_FCLK)
		cdclk_config->cdclk = 800000;
	अन्यथा अगर (पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP) & HSW_CDCLK_LIMIT)
		cdclk_config->cdclk = 450000;
	अन्यथा अगर (freq == LCPLL_CLK_FREQ_450)
		cdclk_config->cdclk = 450000;
	अन्यथा अगर (IS_HSW_ULT(dev_priv))
		cdclk_config->cdclk = 337500;
	अन्यथा
		cdclk_config->cdclk = 540000;
पूर्ण

अटल पूर्णांक vlv_calc_cdclk(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक min_cdclk)
अणु
	पूर्णांक freq_320 = (dev_priv->hpll_freq <<  1) % 320000 != 0 ?
		333333 : 320000;

	/*
	 * We seem to get an unstable or solid color picture at 200MHz.
	 * Not sure what's wrong. For now use 200MHz only when all pipes
	 * are off.
	 */
	अगर (IS_VALLEYVIEW(dev_priv) && min_cdclk > freq_320)
		वापस 400000;
	अन्यथा अगर (min_cdclk > 266667)
		वापस freq_320;
	अन्यथा अगर (min_cdclk > 0)
		वापस 266667;
	अन्यथा
		वापस 200000;
पूर्ण

अटल u8 vlv_calc_voltage_level(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक cdclk)
अणु
	अगर (IS_VALLEYVIEW(dev_priv)) अणु
		अगर (cdclk >= 320000) /* jump to highest voltage क्रम 400MHz too */
			वापस 2;
		अन्यथा अगर (cdclk >= 266667)
			वापस 1;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * Specs are full of misinक्रमmation, but testing on actual
		 * hardware has shown that we just need to ग_लिखो the desired
		 * CCK भागider पूर्णांकo the Punit रेजिस्टर.
		 */
		वापस DIV_ROUND_CLOSEST(dev_priv->hpll_freq << 1, cdclk) - 1;
	पूर्ण
पूर्ण

अटल व्योम vlv_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 val;

	vlv_iosf_sb_get(dev_priv,
			BIT(VLV_IOSF_SB_CCK) | BIT(VLV_IOSF_SB_PUNIT));

	cdclk_config->vco = vlv_get_hpll_vco(dev_priv);
	cdclk_config->cdclk = vlv_get_cck_घड़ी(dev_priv, "cdclk",
						CCK_DISPLAY_CLOCK_CONTROL,
						cdclk_config->vco);

	val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM);

	vlv_iosf_sb_put(dev_priv,
			BIT(VLV_IOSF_SB_CCK) | BIT(VLV_IOSF_SB_PUNIT));

	अगर (IS_VALLEYVIEW(dev_priv))
		cdclk_config->voltage_level = (val & DSPFREQGUAR_MASK) >>
			DSPFREQGUAR_SHIFT;
	अन्यथा
		cdclk_config->voltage_level = (val & DSPFREQGUAR_MASK_CHV) >>
			DSPFREQGUAR_SHIFT_CHV;
पूर्ण

अटल व्योम vlv_program_pfi_credits(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अचिन्हित पूर्णांक credits, शेष_credits;

	अगर (IS_CHERRYVIEW(dev_priv))
		शेष_credits = PFI_CREDIT(12);
	अन्यथा
		शेष_credits = PFI_CREDIT(8);

	अगर (dev_priv->cdclk.hw.cdclk >= dev_priv->czclk_freq) अणु
		/* CHV suggested value is 31 or 63 */
		अगर (IS_CHERRYVIEW(dev_priv))
			credits = PFI_CREDIT_63;
		अन्यथा
			credits = PFI_CREDIT(15);
	पूर्ण अन्यथा अणु
		credits = शेष_credits;
	पूर्ण

	/*
	 * WA - ग_लिखो शेष credits beक्रमe re-programming
	 * FIXME: should we also set the resend bit here?
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, GCI_CONTROL,
		       VGA_FAST_MODE_DISABLE | शेष_credits);

	पूर्णांकel_de_ग_लिखो(dev_priv, GCI_CONTROL,
		       VGA_FAST_MODE_DISABLE | credits | PFI_CREDIT_RESEND);

	/*
	 * FIXME is this guaranteed to clear
	 * immediately or should we poll क्रम it?
	 */
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, GCI_CONTROL) & PFI_CREDIT_RESEND);
पूर्ण

अटल व्योम vlv_set_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			  क्रमागत pipe pipe)
अणु
	पूर्णांक cdclk = cdclk_config->cdclk;
	u32 val, cmd = cdclk_config->voltage_level;
	पूर्णांकel_wakeref_t wakeref;

	चयन (cdclk) अणु
	हाल 400000:
	हाल 333333:
	हाल 320000:
	हाल 266667:
	हाल 200000:
		अवरोध;
	शेष:
		MISSING_CASE(cdclk);
		वापस;
	पूर्ण

	/* There are हालs where we can end up here with घातer करोमुख्यs
	 * off and a CDCLK frequency other than the minimum, like when
	 * issuing a modeset without actually changing any display after
	 * a प्रणाली suspend.  So grab the display core करोमुख्य, which covers
	 * the HW blocks needed क्रम the following programming.
	 */
	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_DISPLAY_CORE);

	vlv_iosf_sb_get(dev_priv,
			BIT(VLV_IOSF_SB_CCK) |
			BIT(VLV_IOSF_SB_BUNIT) |
			BIT(VLV_IOSF_SB_PUNIT));

	val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM);
	val &= ~DSPFREQGUAR_MASK;
	val |= (cmd << DSPFREQGUAR_SHIFT);
	vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_DSPSSPM, val);
	अगर (रुको_क्रम((vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM) &
		      DSPFREQSTAT_MASK) == (cmd << DSPFREQSTAT_SHIFT),
		     50)) अणु
		drm_err(&dev_priv->drm,
			"timed out waiting for CDclk change\n");
	पूर्ण

	अगर (cdclk == 400000) अणु
		u32 भागider;

		भागider = DIV_ROUND_CLOSEST(dev_priv->hpll_freq << 1,
					    cdclk) - 1;

		/* adjust cdclk भागider */
		val = vlv_cck_पढ़ो(dev_priv, CCK_DISPLAY_CLOCK_CONTROL);
		val &= ~CCK_FREQUENCY_VALUES;
		val |= भागider;
		vlv_cck_ग_लिखो(dev_priv, CCK_DISPLAY_CLOCK_CONTROL, val);

		अगर (रुको_क्रम((vlv_cck_पढ़ो(dev_priv, CCK_DISPLAY_CLOCK_CONTROL) &
			      CCK_FREQUENCY_STATUS) == (भागider << CCK_FREQUENCY_STATUS_SHIFT),
			     50))
			drm_err(&dev_priv->drm,
				"timed out waiting for CDclk change\n");
	पूर्ण

	/* adjust self-refresh निकास latency value */
	val = vlv_bunit_पढ़ो(dev_priv, BUNIT_REG_BISOC);
	val &= ~0x7f;

	/*
	 * For high bandwidth configs, we set a higher latency in the bunit
	 * so that the core display fetch happens in समय to aव्योम underruns.
	 */
	अगर (cdclk == 400000)
		val |= 4500 / 250; /* 4.5 usec */
	अन्यथा
		val |= 3000 / 250; /* 3.0 usec */
	vlv_bunit_ग_लिखो(dev_priv, BUNIT_REG_BISOC, val);

	vlv_iosf_sb_put(dev_priv,
			BIT(VLV_IOSF_SB_CCK) |
			BIT(VLV_IOSF_SB_BUNIT) |
			BIT(VLV_IOSF_SB_PUNIT));

	पूर्णांकel_update_cdclk(dev_priv);

	vlv_program_pfi_credits(dev_priv);

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
पूर्ण

अटल व्योम chv_set_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			  क्रमागत pipe pipe)
अणु
	पूर्णांक cdclk = cdclk_config->cdclk;
	u32 val, cmd = cdclk_config->voltage_level;
	पूर्णांकel_wakeref_t wakeref;

	चयन (cdclk) अणु
	हाल 333333:
	हाल 320000:
	हाल 266667:
	हाल 200000:
		अवरोध;
	शेष:
		MISSING_CASE(cdclk);
		वापस;
	पूर्ण

	/* There are हालs where we can end up here with घातer करोमुख्यs
	 * off and a CDCLK frequency other than the minimum, like when
	 * issuing a modeset without actually changing any display after
	 * a प्रणाली suspend.  So grab the display core करोमुख्य, which covers
	 * the HW blocks needed क्रम the following programming.
	 */
	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_DISPLAY_CORE);

	vlv_punit_get(dev_priv);
	val = vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM);
	val &= ~DSPFREQGUAR_MASK_CHV;
	val |= (cmd << DSPFREQGUAR_SHIFT_CHV);
	vlv_punit_ग_लिखो(dev_priv, PUNIT_REG_DSPSSPM, val);
	अगर (रुको_क्रम((vlv_punit_पढ़ो(dev_priv, PUNIT_REG_DSPSSPM) &
		      DSPFREQSTAT_MASK_CHV) == (cmd << DSPFREQSTAT_SHIFT_CHV),
		     50)) अणु
		drm_err(&dev_priv->drm,
			"timed out waiting for CDclk change\n");
	पूर्ण

	vlv_punit_put(dev_priv);

	पूर्णांकel_update_cdclk(dev_priv);

	vlv_program_pfi_credits(dev_priv);

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_DISPLAY_CORE, wakeref);
पूर्ण

अटल पूर्णांक bdw_calc_cdclk(पूर्णांक min_cdclk)
अणु
	अगर (min_cdclk > 540000)
		वापस 675000;
	अन्यथा अगर (min_cdclk > 450000)
		वापस 540000;
	अन्यथा अगर (min_cdclk > 337500)
		वापस 450000;
	अन्यथा
		वापस 337500;
पूर्ण

अटल u8 bdw_calc_voltage_level(पूर्णांक cdclk)
अणु
	चयन (cdclk) अणु
	शेष:
	हाल 337500:
		वापस 2;
	हाल 450000:
		वापस 0;
	हाल 540000:
		वापस 1;
	हाल 675000:
		वापस 3;
	पूर्ण
पूर्ण

अटल व्योम bdw_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 lcpll = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	u32 freq = lcpll & LCPLL_CLK_FREQ_MASK;

	अगर (lcpll & LCPLL_CD_SOURCE_FCLK)
		cdclk_config->cdclk = 800000;
	अन्यथा अगर (पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP) & HSW_CDCLK_LIMIT)
		cdclk_config->cdclk = 450000;
	अन्यथा अगर (freq == LCPLL_CLK_FREQ_450)
		cdclk_config->cdclk = 450000;
	अन्यथा अगर (freq == LCPLL_CLK_FREQ_54O_BDW)
		cdclk_config->cdclk = 540000;
	अन्यथा अगर (freq == LCPLL_CLK_FREQ_337_5_BDW)
		cdclk_config->cdclk = 337500;
	अन्यथा
		cdclk_config->cdclk = 675000;

	/*
	 * Can't read this out :( Let's assume it's
	 * at least what the CDCLK frequency requires.
	 */
	cdclk_config->voltage_level =
		bdw_calc_voltage_level(cdclk_config->cdclk);
पूर्ण

अटल व्योम bdw_set_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			  क्रमागत pipe pipe)
अणु
	पूर्णांक cdclk = cdclk_config->cdclk;
	u32 val;
	पूर्णांक ret;

	अगर (drm_WARN(&dev_priv->drm,
		     (पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL) &
		      (LCPLL_PLL_DISABLE | LCPLL_PLL_LOCK |
		       LCPLL_CD_CLOCK_DISABLE | LCPLL_ROOT_CD_CLOCK_DISABLE |
		       LCPLL_CD2X_CLOCK_DISABLE | LCPLL_POWER_DOWN_ALLOW |
		       LCPLL_CD_SOURCE_FCLK)) != LCPLL_PLL_LOCK,
		     "trying to change cdclk frequency with cdclk not enabled\n"))
		वापस;

	ret = sandybridge_pcode_ग_लिखो(dev_priv,
				      BDW_PCODE_DISPLAY_FREQ_CHANGE_REQ, 0x0);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"failed to inform pcode about cdclk change\n");
		वापस;
	पूर्ण

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	val |= LCPLL_CD_SOURCE_FCLK;
	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);

	/*
	 * According to the spec, it should be enough to poll क्रम this 1 us.
	 * However, extensive testing shows that this can take दीर्घer.
	 */
	अगर (रुको_क्रम_us(पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL) &
			LCPLL_CD_SOURCE_FCLK_DONE, 100))
		drm_err(&dev_priv->drm, "Switching to FCLK failed\n");

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	val &= ~LCPLL_CLK_FREQ_MASK;

	चयन (cdclk) अणु
	शेष:
		MISSING_CASE(cdclk);
		fallthrough;
	हाल 337500:
		val |= LCPLL_CLK_FREQ_337_5_BDW;
		अवरोध;
	हाल 450000:
		val |= LCPLL_CLK_FREQ_450;
		अवरोध;
	हाल 540000:
		val |= LCPLL_CLK_FREQ_54O_BDW;
		अवरोध;
	हाल 675000:
		val |= LCPLL_CLK_FREQ_675_BDW;
		अवरोध;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL);
	val &= ~LCPLL_CD_SOURCE_FCLK;
	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL_CTL, val);

	अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, LCPLL_CTL) &
			 LCPLL_CD_SOURCE_FCLK_DONE) == 0, 1))
		drm_err(&dev_priv->drm, "Switching back to LCPLL failed\n");

	sandybridge_pcode_ग_लिखो(dev_priv, HSW_PCODE_DE_WRITE_FREQ_REQ,
				cdclk_config->voltage_level);

	पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_FREQ,
		       DIV_ROUND_CLOSEST(cdclk, 1000) - 1);

	पूर्णांकel_update_cdclk(dev_priv);
पूर्ण

अटल पूर्णांक skl_calc_cdclk(पूर्णांक min_cdclk, पूर्णांक vco)
अणु
	अगर (vco == 8640000) अणु
		अगर (min_cdclk > 540000)
			वापस 617143;
		अन्यथा अगर (min_cdclk > 432000)
			वापस 540000;
		अन्यथा अगर (min_cdclk > 308571)
			वापस 432000;
		अन्यथा
			वापस 308571;
	पूर्ण अन्यथा अणु
		अगर (min_cdclk > 540000)
			वापस 675000;
		अन्यथा अगर (min_cdclk > 450000)
			वापस 540000;
		अन्यथा अगर (min_cdclk > 337500)
			वापस 450000;
		अन्यथा
			वापस 337500;
	पूर्ण
पूर्ण

अटल u8 skl_calc_voltage_level(पूर्णांक cdclk)
अणु
	अगर (cdclk > 540000)
		वापस 3;
	अन्यथा अगर (cdclk > 450000)
		वापस 2;
	अन्यथा अगर (cdclk > 337500)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम skl_dpll0_update(काष्ठा drm_i915_निजी *dev_priv,
			     काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 val;

	cdclk_config->ref = 24000;
	cdclk_config->vco = 0;

	val = पूर्णांकel_de_पढ़ो(dev_priv, LCPLL1_CTL);
	अगर ((val & LCPLL_PLL_ENABLE) == 0)
		वापस;

	अगर (drm_WARN_ON(&dev_priv->drm, (val & LCPLL_PLL_LOCK) == 0))
		वापस;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL_CTRL1);

	अगर (drm_WARN_ON(&dev_priv->drm,
			(val & (DPLL_CTRL1_HDMI_MODE(SKL_DPLL0) |
				DPLL_CTRL1_SSC(SKL_DPLL0) |
				DPLL_CTRL1_OVERRIDE(SKL_DPLL0))) !=
			DPLL_CTRL1_OVERRIDE(SKL_DPLL0)))
		वापस;

	चयन (val & DPLL_CTRL1_LINK_RATE_MASK(SKL_DPLL0)) अणु
	हाल DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_810, SKL_DPLL0):
	हाल DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1350, SKL_DPLL0):
	हाल DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1620, SKL_DPLL0):
	हाल DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_2700, SKL_DPLL0):
		cdclk_config->vco = 8100000;
		अवरोध;
	हाल DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1080, SKL_DPLL0):
	हाल DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_2160, SKL_DPLL0):
		cdclk_config->vco = 8640000;
		अवरोध;
	शेष:
		MISSING_CASE(val & DPLL_CTRL1_LINK_RATE_MASK(SKL_DPLL0));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम skl_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 cdctl;

	skl_dpll0_update(dev_priv, cdclk_config);

	cdclk_config->cdclk = cdclk_config->bypass = cdclk_config->ref;

	अगर (cdclk_config->vco == 0)
		जाओ out;

	cdctl = पूर्णांकel_de_पढ़ो(dev_priv, CDCLK_CTL);

	अगर (cdclk_config->vco == 8640000) अणु
		चयन (cdctl & CDCLK_FREQ_SEL_MASK) अणु
		हाल CDCLK_FREQ_450_432:
			cdclk_config->cdclk = 432000;
			अवरोध;
		हाल CDCLK_FREQ_337_308:
			cdclk_config->cdclk = 308571;
			अवरोध;
		हाल CDCLK_FREQ_540:
			cdclk_config->cdclk = 540000;
			अवरोध;
		हाल CDCLK_FREQ_675_617:
			cdclk_config->cdclk = 617143;
			अवरोध;
		शेष:
			MISSING_CASE(cdctl & CDCLK_FREQ_SEL_MASK);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cdctl & CDCLK_FREQ_SEL_MASK) अणु
		हाल CDCLK_FREQ_450_432:
			cdclk_config->cdclk = 450000;
			अवरोध;
		हाल CDCLK_FREQ_337_308:
			cdclk_config->cdclk = 337500;
			अवरोध;
		हाल CDCLK_FREQ_540:
			cdclk_config->cdclk = 540000;
			अवरोध;
		हाल CDCLK_FREQ_675_617:
			cdclk_config->cdclk = 675000;
			अवरोध;
		शेष:
			MISSING_CASE(cdctl & CDCLK_FREQ_SEL_MASK);
			अवरोध;
		पूर्ण
	पूर्ण

 out:
	/*
	 * Can't read this out :( Let's assume it's
	 * at least what the CDCLK frequency requires.
	 */
	cdclk_config->voltage_level =
		skl_calc_voltage_level(cdclk_config->cdclk);
पूर्ण

/* convert from kHz to .1 fixpoपूर्णांक MHz with -1MHz offset */
अटल पूर्णांक skl_cdclk_decimal(पूर्णांक cdclk)
अणु
	वापस DIV_ROUND_CLOSEST(cdclk - 1000, 500);
पूर्ण

अटल व्योम skl_set_preferred_cdclk_vco(काष्ठा drm_i915_निजी *dev_priv,
					पूर्णांक vco)
अणु
	bool changed = dev_priv->skl_preferred_vco_freq != vco;

	dev_priv->skl_preferred_vco_freq = vco;

	अगर (changed)
		पूर्णांकel_update_max_cdclk(dev_priv);
पूर्ण

अटल व्योम skl_dpll0_enable(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक vco)
अणु
	u32 val;

	drm_WARN_ON(&dev_priv->drm, vco != 8100000 && vco != 8640000);

	/*
	 * We always enable DPLL0 with the lowest link rate possible, but still
	 * taking पूर्णांकo account the VCO required to operate the eDP panel at the
	 * desired frequency. The usual DP link rates operate with a VCO of
	 * 8100 जबतक the eDP 1.4 alternate link rates need a VCO of 8640.
	 * The modeset code is responsible क्रम the selection of the exact link
	 * rate later on, with the स्थिरraपूर्णांक of choosing a frequency that
	 * works with vco.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL_CTRL1);

	val &= ~(DPLL_CTRL1_HDMI_MODE(SKL_DPLL0) | DPLL_CTRL1_SSC(SKL_DPLL0) |
		 DPLL_CTRL1_LINK_RATE_MASK(SKL_DPLL0));
	val |= DPLL_CTRL1_OVERRIDE(SKL_DPLL0);
	अगर (vco == 8640000)
		val |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_1080,
					    SKL_DPLL0);
	अन्यथा
		val |= DPLL_CTRL1_LINK_RATE(DPLL_CTRL1_LINK_RATE_810,
					    SKL_DPLL0);

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL_CTRL1, val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL_CTRL1);

	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL1_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, LCPLL1_CTL) | LCPLL_PLL_ENABLE);

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, LCPLL1_CTL, LCPLL_PLL_LOCK, 5))
		drm_err(&dev_priv->drm, "DPLL0 not locked\n");

	dev_priv->cdclk.hw.vco = vco;

	/* We'll want to keep using the current vco from now on. */
	skl_set_preferred_cdclk_vco(dev_priv, vco);
पूर्ण

अटल व्योम skl_dpll0_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, LCPLL1_CTL,
		       पूर्णांकel_de_पढ़ो(dev_priv, LCPLL1_CTL) & ~LCPLL_PLL_ENABLE);
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, LCPLL1_CTL, LCPLL_PLL_LOCK, 1))
		drm_err(&dev_priv->drm, "Couldn't disable DPLL0\n");

	dev_priv->cdclk.hw.vco = 0;
पूर्ण

अटल व्योम skl_set_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			  क्रमागत pipe pipe)
अणु
	पूर्णांक cdclk = cdclk_config->cdclk;
	पूर्णांक vco = cdclk_config->vco;
	u32 freq_select, cdclk_ctl;
	पूर्णांक ret;

	/*
	 * Based on WA#1183 CDCLK rates 308 and 617MHz CDCLK rates are
	 * unsupported on SKL. In theory this should never happen since only
	 * the eDP1.4 2.16 and 4.32Gbps rates require it, but eDP1.4 is not
	 * supported on SKL either, see the above WA. WARN whenever trying to
	 * use the corresponding VCO freq as that always leads to using the
	 * minimum 308MHz CDCLK.
	 */
	drm_WARN_ON_ONCE(&dev_priv->drm,
			 IS_SKYLAKE(dev_priv) && vco == 8640000);

	ret = skl_pcode_request(dev_priv, SKL_PCODE_CDCLK_CONTROL,
				SKL_CDCLK_PREPARE_FOR_CHANGE,
				SKL_CDCLK_READY_FOR_CHANGE,
				SKL_CDCLK_READY_FOR_CHANGE, 3);
	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Failed to inform PCU about cdclk change (%d)\n", ret);
		वापस;
	पूर्ण

	/* Choose frequency क्रम this cdclk */
	चयन (cdclk) अणु
	शेष:
		drm_WARN_ON(&dev_priv->drm,
			    cdclk != dev_priv->cdclk.hw.bypass);
		drm_WARN_ON(&dev_priv->drm, vco != 0);
		fallthrough;
	हाल 308571:
	हाल 337500:
		freq_select = CDCLK_FREQ_337_308;
		अवरोध;
	हाल 450000:
	हाल 432000:
		freq_select = CDCLK_FREQ_450_432;
		अवरोध;
	हाल 540000:
		freq_select = CDCLK_FREQ_540;
		अवरोध;
	हाल 617143:
	हाल 675000:
		freq_select = CDCLK_FREQ_675_617;
		अवरोध;
	पूर्ण

	अगर (dev_priv->cdclk.hw.vco != 0 &&
	    dev_priv->cdclk.hw.vco != vco)
		skl_dpll0_disable(dev_priv);

	cdclk_ctl = पूर्णांकel_de_पढ़ो(dev_priv, CDCLK_CTL);

	अगर (dev_priv->cdclk.hw.vco != vco) अणु
		/* Wa Display #1183: skl,kbl,cfl */
		cdclk_ctl &= ~(CDCLK_FREQ_SEL_MASK | CDCLK_FREQ_DECIMAL_MASK);
		cdclk_ctl |= freq_select | skl_cdclk_decimal(cdclk);
		पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_CTL, cdclk_ctl);
	पूर्ण

	/* Wa Display #1183: skl,kbl,cfl */
	cdclk_ctl |= CDCLK_DIVMUX_CD_OVERRIDE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_CTL, cdclk_ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, CDCLK_CTL);

	अगर (dev_priv->cdclk.hw.vco != vco)
		skl_dpll0_enable(dev_priv, vco);

	/* Wa Display #1183: skl,kbl,cfl */
	cdclk_ctl &= ~(CDCLK_FREQ_SEL_MASK | CDCLK_FREQ_DECIMAL_MASK);
	पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_CTL, cdclk_ctl);

	cdclk_ctl |= freq_select | skl_cdclk_decimal(cdclk);
	पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_CTL, cdclk_ctl);

	/* Wa Display #1183: skl,kbl,cfl */
	cdclk_ctl &= ~CDCLK_DIVMUX_CD_OVERRIDE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_CTL, cdclk_ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, CDCLK_CTL);

	/* inक्रमm PCU of the change */
	sandybridge_pcode_ग_लिखो(dev_priv, SKL_PCODE_CDCLK_CONTROL,
				cdclk_config->voltage_level);

	पूर्णांकel_update_cdclk(dev_priv);
पूर्ण

अटल व्योम skl_sanitize_cdclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 cdctl, expected;

	/*
	 * check अगर the pre-os initialized the display
	 * There is SWF18 scratchpad रेजिस्टर defined which is set by the
	 * pre-os which can be used by the OS drivers to check the status
	 */
	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, SWF_ILK(0x18)) & 0x00FFFFFF) == 0)
		जाओ sanitize;

	पूर्णांकel_update_cdclk(dev_priv);
	पूर्णांकel_dump_cdclk_config(&dev_priv->cdclk.hw, "Current CDCLK");

	/* Is PLL enabled and locked ? */
	अगर (dev_priv->cdclk.hw.vco == 0 ||
	    dev_priv->cdclk.hw.cdclk == dev_priv->cdclk.hw.bypass)
		जाओ sanitize;

	/* DPLL okay; verअगरy the cdघड़ी
	 *
	 * Noticed in some instances that the freq selection is correct but
	 * decimal part is programmed wrong from BIOS where pre-os करोes not
	 * enable display. Verअगरy the same as well.
	 */
	cdctl = पूर्णांकel_de_पढ़ो(dev_priv, CDCLK_CTL);
	expected = (cdctl & CDCLK_FREQ_SEL_MASK) |
		skl_cdclk_decimal(dev_priv->cdclk.hw.cdclk);
	अगर (cdctl == expected)
		/* All well; nothing to sanitize */
		वापस;

sanitize:
	drm_dbg_kms(&dev_priv->drm, "Sanitizing cdclk programmed by pre-os\n");

	/* क्रमce cdclk programming */
	dev_priv->cdclk.hw.cdclk = 0;
	/* क्रमce full PLL disable + enable */
	dev_priv->cdclk.hw.vco = -1;
पूर्ण

अटल व्योम skl_cdclk_init_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_cdclk_config cdclk_config;

	skl_sanitize_cdclk(dev_priv);

	अगर (dev_priv->cdclk.hw.cdclk != 0 &&
	    dev_priv->cdclk.hw.vco != 0) अणु
		/*
		 * Use the current vco as our initial
		 * guess as to what the preferred vco is.
		 */
		अगर (dev_priv->skl_preferred_vco_freq == 0)
			skl_set_preferred_cdclk_vco(dev_priv,
						    dev_priv->cdclk.hw.vco);
		वापस;
	पूर्ण

	cdclk_config = dev_priv->cdclk.hw;

	cdclk_config.vco = dev_priv->skl_preferred_vco_freq;
	अगर (cdclk_config.vco == 0)
		cdclk_config.vco = 8100000;
	cdclk_config.cdclk = skl_calc_cdclk(0, cdclk_config.vco);
	cdclk_config.voltage_level = skl_calc_voltage_level(cdclk_config.cdclk);

	skl_set_cdclk(dev_priv, &cdclk_config, INVALID_PIPE);
पूर्ण

अटल व्योम skl_cdclk_uninit_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_cdclk_config cdclk_config = dev_priv->cdclk.hw;

	cdclk_config.cdclk = cdclk_config.bypass;
	cdclk_config.vco = 0;
	cdclk_config.voltage_level = skl_calc_voltage_level(cdclk_config.cdclk);

	skl_set_cdclk(dev_priv, &cdclk_config, INVALID_PIPE);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_cdclk_vals bxt_cdclk_table[] = अणु
	अणु .refclk = 19200, .cdclk = 144000, .भागider = 8, .ratio = 60 पूर्ण,
	अणु .refclk = 19200, .cdclk = 288000, .भागider = 4, .ratio = 60 पूर्ण,
	अणु .refclk = 19200, .cdclk = 384000, .भागider = 3, .ratio = 60 पूर्ण,
	अणु .refclk = 19200, .cdclk = 576000, .भागider = 2, .ratio = 60 पूर्ण,
	अणु .refclk = 19200, .cdclk = 624000, .भागider = 2, .ratio = 65 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_cdclk_vals glk_cdclk_table[] = अणु
	अणु .refclk = 19200, .cdclk =  79200, .भागider = 8, .ratio = 33 पूर्ण,
	अणु .refclk = 19200, .cdclk = 158400, .भागider = 4, .ratio = 33 पूर्ण,
	अणु .refclk = 19200, .cdclk = 316800, .भागider = 2, .ratio = 33 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_cdclk_vals cnl_cdclk_table[] = अणु
	अणु .refclk = 19200, .cdclk = 168000, .भागider = 4, .ratio = 35 पूर्ण,
	अणु .refclk = 19200, .cdclk = 336000, .भागider = 2, .ratio = 35 पूर्ण,
	अणु .refclk = 19200, .cdclk = 528000, .भागider = 2, .ratio = 55 पूर्ण,

	अणु .refclk = 24000, .cdclk = 168000, .भागider = 4, .ratio = 28 पूर्ण,
	अणु .refclk = 24000, .cdclk = 336000, .भागider = 2, .ratio = 28 पूर्ण,
	अणु .refclk = 24000, .cdclk = 528000, .भागider = 2, .ratio = 44 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_cdclk_vals icl_cdclk_table[] = अणु
	अणु .refclk = 19200, .cdclk = 172800, .भागider = 2, .ratio = 18 पूर्ण,
	अणु .refclk = 19200, .cdclk = 192000, .भागider = 2, .ratio = 20 पूर्ण,
	अणु .refclk = 19200, .cdclk = 307200, .भागider = 2, .ratio = 32 पूर्ण,
	अणु .refclk = 19200, .cdclk = 326400, .भागider = 4, .ratio = 68 पूर्ण,
	अणु .refclk = 19200, .cdclk = 556800, .भागider = 2, .ratio = 58 पूर्ण,
	अणु .refclk = 19200, .cdclk = 652800, .भागider = 2, .ratio = 68 पूर्ण,

	अणु .refclk = 24000, .cdclk = 180000, .भागider = 2, .ratio = 15 पूर्ण,
	अणु .refclk = 24000, .cdclk = 192000, .भागider = 2, .ratio = 16 पूर्ण,
	अणु .refclk = 24000, .cdclk = 312000, .भागider = 2, .ratio = 26 पूर्ण,
	अणु .refclk = 24000, .cdclk = 324000, .भागider = 4, .ratio = 54 पूर्ण,
	अणु .refclk = 24000, .cdclk = 552000, .भागider = 2, .ratio = 46 पूर्ण,
	अणु .refclk = 24000, .cdclk = 648000, .भागider = 2, .ratio = 54 पूर्ण,

	अणु .refclk = 38400, .cdclk = 172800, .भागider = 2, .ratio =  9 पूर्ण,
	अणु .refclk = 38400, .cdclk = 192000, .भागider = 2, .ratio = 10 पूर्ण,
	अणु .refclk = 38400, .cdclk = 307200, .भागider = 2, .ratio = 16 पूर्ण,
	अणु .refclk = 38400, .cdclk = 326400, .भागider = 4, .ratio = 34 पूर्ण,
	अणु .refclk = 38400, .cdclk = 556800, .भागider = 2, .ratio = 29 पूर्ण,
	अणु .refclk = 38400, .cdclk = 652800, .भागider = 2, .ratio = 34 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_cdclk_vals rkl_cdclk_table[] = अणु
	अणु .refclk = 19200, .cdclk = 172800, .भागider = 4, .ratio =  36 पूर्ण,
	अणु .refclk = 19200, .cdclk = 192000, .भागider = 4, .ratio =  40 पूर्ण,
	अणु .refclk = 19200, .cdclk = 307200, .भागider = 4, .ratio =  64 पूर्ण,
	अणु .refclk = 19200, .cdclk = 326400, .भागider = 8, .ratio = 136 पूर्ण,
	अणु .refclk = 19200, .cdclk = 556800, .भागider = 4, .ratio = 116 पूर्ण,
	अणु .refclk = 19200, .cdclk = 652800, .भागider = 4, .ratio = 136 पूर्ण,

	अणु .refclk = 24000, .cdclk = 180000, .भागider = 4, .ratio =  30 पूर्ण,
	अणु .refclk = 24000, .cdclk = 192000, .भागider = 4, .ratio =  32 पूर्ण,
	अणु .refclk = 24000, .cdclk = 312000, .भागider = 4, .ratio =  52 पूर्ण,
	अणु .refclk = 24000, .cdclk = 324000, .भागider = 8, .ratio = 108 पूर्ण,
	अणु .refclk = 24000, .cdclk = 552000, .भागider = 4, .ratio =  92 पूर्ण,
	अणु .refclk = 24000, .cdclk = 648000, .भागider = 4, .ratio = 108 पूर्ण,

	अणु .refclk = 38400, .cdclk = 172800, .भागider = 4, .ratio = 18 पूर्ण,
	अणु .refclk = 38400, .cdclk = 192000, .भागider = 4, .ratio = 20 पूर्ण,
	अणु .refclk = 38400, .cdclk = 307200, .भागider = 4, .ratio = 32 पूर्ण,
	अणु .refclk = 38400, .cdclk = 326400, .भागider = 8, .ratio = 68 पूर्ण,
	अणु .refclk = 38400, .cdclk = 556800, .भागider = 4, .ratio = 58 पूर्ण,
	अणु .refclk = 38400, .cdclk = 652800, .भागider = 4, .ratio = 68 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक bxt_calc_cdclk(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक min_cdclk)
अणु
	स्थिर काष्ठा पूर्णांकel_cdclk_vals *table = dev_priv->cdclk.table;
	पूर्णांक i;

	क्रम (i = 0; table[i].refclk; i++)
		अगर (table[i].refclk == dev_priv->cdclk.hw.ref &&
		    table[i].cdclk >= min_cdclk)
			वापस table[i].cdclk;

	drm_WARN(&dev_priv->drm, 1,
		 "Cannot satisfy minimum cdclk %d with refclk %u\n",
		 min_cdclk, dev_priv->cdclk.hw.ref);
	वापस 0;
पूर्ण

अटल पूर्णांक bxt_calc_cdclk_pll_vco(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक cdclk)
अणु
	स्थिर काष्ठा पूर्णांकel_cdclk_vals *table = dev_priv->cdclk.table;
	पूर्णांक i;

	अगर (cdclk == dev_priv->cdclk.hw.bypass)
		वापस 0;

	क्रम (i = 0; table[i].refclk; i++)
		अगर (table[i].refclk == dev_priv->cdclk.hw.ref &&
		    table[i].cdclk == cdclk)
			वापस dev_priv->cdclk.hw.ref * table[i].ratio;

	drm_WARN(&dev_priv->drm, 1, "cdclk %d not valid for refclk %u\n",
		 cdclk, dev_priv->cdclk.hw.ref);
	वापस 0;
पूर्ण

अटल u8 bxt_calc_voltage_level(पूर्णांक cdclk)
अणु
	वापस DIV_ROUND_UP(cdclk, 25000);
पूर्ण

अटल u8 cnl_calc_voltage_level(पूर्णांक cdclk)
अणु
	अगर (cdclk > 336000)
		वापस 2;
	अन्यथा अगर (cdclk > 168000)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल u8 icl_calc_voltage_level(पूर्णांक cdclk)
अणु
	अगर (cdclk > 556800)
		वापस 2;
	अन्यथा अगर (cdclk > 312000)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल u8 ehl_calc_voltage_level(पूर्णांक cdclk)
अणु
	अगर (cdclk > 326400)
		वापस 3;
	अन्यथा अगर (cdclk > 312000)
		वापस 2;
	अन्यथा अगर (cdclk > 180000)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल u8 tgl_calc_voltage_level(पूर्णांक cdclk)
अणु
	अगर (cdclk > 556800)
		वापस 3;
	अन्यथा अगर (cdclk > 326400)
		वापस 2;
	अन्यथा अगर (cdclk > 312000)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम cnl_पढ़ोout_refclk(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	अगर (पूर्णांकel_de_पढ़ो(dev_priv, SKL_DSSM) & CNL_DSSM_CDCLK_PLL_REFCLK_24MHz)
		cdclk_config->ref = 24000;
	अन्यथा
		cdclk_config->ref = 19200;
पूर्ण

अटल व्योम icl_पढ़ोout_refclk(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 dssm = पूर्णांकel_de_पढ़ो(dev_priv, SKL_DSSM) & ICL_DSSM_CDCLK_PLL_REFCLK_MASK;

	चयन (dssm) अणु
	शेष:
		MISSING_CASE(dssm);
		fallthrough;
	हाल ICL_DSSM_CDCLK_PLL_REFCLK_24MHz:
		cdclk_config->ref = 24000;
		अवरोध;
	हाल ICL_DSSM_CDCLK_PLL_REFCLK_19_2MHz:
		cdclk_config->ref = 19200;
		अवरोध;
	हाल ICL_DSSM_CDCLK_PLL_REFCLK_38_4MHz:
		cdclk_config->ref = 38400;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bxt_de_pll_पढ़ोout(काष्ठा drm_i915_निजी *dev_priv,
			       काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 val, ratio;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_पढ़ोout_refclk(dev_priv, cdclk_config);
	अन्यथा अगर (IS_CANNONLAKE(dev_priv))
		cnl_पढ़ोout_refclk(dev_priv, cdclk_config);
	अन्यथा
		cdclk_config->ref = 19200;

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DE_PLL_ENABLE);
	अगर ((val & BXT_DE_PLL_PLL_ENABLE) == 0 ||
	    (val & BXT_DE_PLL_LOCK) == 0) अणु
		/*
		 * CDCLK PLL is disabled, the VCO/ratio करोesn't matter, but
		 * setting it to zero is a way to संकेत that.
		 */
		cdclk_config->vco = 0;
		वापस;
	पूर्ण

	/*
	 * CNL+ have the ratio directly in the PLL enable रेजिस्टर, gen9lp had
	 * it in a separate PLL control रेजिस्टर.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		ratio = val & CNL_CDCLK_PLL_RATIO_MASK;
	अन्यथा
		ratio = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DE_PLL_CTL) & BXT_DE_PLL_RATIO_MASK;

	cdclk_config->vco = ratio * cdclk_config->ref;
पूर्ण

अटल व्योम bxt_get_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config)
अणु
	u32 भागider;
	पूर्णांक भाग;

	bxt_de_pll_पढ़ोout(dev_priv, cdclk_config);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		cdclk_config->bypass = cdclk_config->ref / 2;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11)
		cdclk_config->bypass = 50000;
	अन्यथा
		cdclk_config->bypass = cdclk_config->ref;

	अगर (cdclk_config->vco == 0) अणु
		cdclk_config->cdclk = cdclk_config->bypass;
		जाओ out;
	पूर्ण

	भागider = पूर्णांकel_de_पढ़ो(dev_priv, CDCLK_CTL) & BXT_CDCLK_CD2X_DIV_SEL_MASK;

	चयन (भागider) अणु
	हाल BXT_CDCLK_CD2X_DIV_SEL_1:
		भाग = 2;
		अवरोध;
	हाल BXT_CDCLK_CD2X_DIV_SEL_1_5:
		drm_WARN(&dev_priv->drm,
			 DISPLAY_VER(dev_priv) >= 10,
			 "Unsupported divider\n");
		भाग = 3;
		अवरोध;
	हाल BXT_CDCLK_CD2X_DIV_SEL_2:
		भाग = 4;
		अवरोध;
	हाल BXT_CDCLK_CD2X_DIV_SEL_4:
		drm_WARN(&dev_priv->drm,
			 DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv),
			 "Unsupported divider\n");
		भाग = 8;
		अवरोध;
	शेष:
		MISSING_CASE(भागider);
		वापस;
	पूर्ण

	cdclk_config->cdclk = DIV_ROUND_CLOSEST(cdclk_config->vco, भाग);

 out:
	/*
	 * Can't read this out :( Let's assume it's
	 * at least what the CDCLK frequency requires.
	 */
	cdclk_config->voltage_level =
		dev_priv->display.calc_voltage_level(cdclk_config->cdclk);
पूर्ण

अटल व्योम bxt_de_pll_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DE_PLL_ENABLE, 0);

	/* Timeout 200us */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv,
				    BXT_DE_PLL_ENABLE, BXT_DE_PLL_LOCK, 1))
		drm_err(&dev_priv->drm, "timeout waiting for DE PLL unlock\n");

	dev_priv->cdclk.hw.vco = 0;
पूर्ण

अटल व्योम bxt_de_pll_enable(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक vco)
अणु
	पूर्णांक ratio = DIV_ROUND_CLOSEST(vco, dev_priv->cdclk.hw.ref);
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DE_PLL_CTL);
	val &= ~BXT_DE_PLL_RATIO_MASK;
	val |= BXT_DE_PLL_RATIO(ratio);
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DE_PLL_CTL, val);

	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DE_PLL_ENABLE, BXT_DE_PLL_PLL_ENABLE);

	/* Timeout 200us */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv,
				  BXT_DE_PLL_ENABLE, BXT_DE_PLL_LOCK, 1))
		drm_err(&dev_priv->drm, "timeout waiting for DE PLL lock\n");

	dev_priv->cdclk.hw.vco = vco;
पूर्ण

अटल व्योम cnl_cdclk_pll_disable(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_DE_PLL_ENABLE);
	val &= ~BXT_DE_PLL_PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DE_PLL_ENABLE, val);

	/* Timeout 200us */
	अगर (रुको_क्रम((पूर्णांकel_de_पढ़ो(dev_priv, BXT_DE_PLL_ENABLE) & BXT_DE_PLL_LOCK) == 0, 1))
		drm_err(&dev_priv->drm,
			"timeout waiting for CDCLK PLL unlock\n");

	dev_priv->cdclk.hw.vco = 0;
पूर्ण

अटल व्योम cnl_cdclk_pll_enable(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक vco)
अणु
	पूर्णांक ratio = DIV_ROUND_CLOSEST(vco, dev_priv->cdclk.hw.ref);
	u32 val;

	val = CNL_CDCLK_PLL_RATIO(ratio);
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DE_PLL_ENABLE, val);

	val |= BXT_DE_PLL_PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_DE_PLL_ENABLE, val);

	/* Timeout 200us */
	अगर (रुको_क्रम((पूर्णांकel_de_पढ़ो(dev_priv, BXT_DE_PLL_ENABLE) & BXT_DE_PLL_LOCK) != 0, 1))
		drm_err(&dev_priv->drm,
			"timeout waiting for CDCLK PLL lock\n");

	dev_priv->cdclk.hw.vco = vco;
पूर्ण

अटल u32 bxt_cdclk_cd2x_pipe(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		अगर (pipe == INVALID_PIPE)
			वापस TGL_CDCLK_CD2X_PIPE_NONE;
		अन्यथा
			वापस TGL_CDCLK_CD2X_PIPE(pipe);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		अगर (pipe == INVALID_PIPE)
			वापस ICL_CDCLK_CD2X_PIPE_NONE;
		अन्यथा
			वापस ICL_CDCLK_CD2X_PIPE(pipe);
	पूर्ण अन्यथा अणु
		अगर (pipe == INVALID_PIPE)
			वापस BXT_CDCLK_CD2X_PIPE_NONE;
		अन्यथा
			वापस BXT_CDCLK_CD2X_PIPE(pipe);
	पूर्ण
पूर्ण

अटल व्योम bxt_set_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			  क्रमागत pipe pipe)
अणु
	पूर्णांक cdclk = cdclk_config->cdclk;
	पूर्णांक vco = cdclk_config->vco;
	u32 val, भागider;
	पूर्णांक ret;

	/* Inक्रमm घातer controller of upcoming frequency change. */
	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		ret = skl_pcode_request(dev_priv, SKL_PCODE_CDCLK_CONTROL,
					SKL_CDCLK_PREPARE_FOR_CHANGE,
					SKL_CDCLK_READY_FOR_CHANGE,
					SKL_CDCLK_READY_FOR_CHANGE, 3);
	अन्यथा
		/*
		 * BSpec requires us to रुको up to 150usec, but that leads to
		 * समयouts; the 2ms used here is based on experiment.
		 */
		ret = sandybridge_pcode_ग_लिखो_समयout(dev_priv,
						      HSW_PCODE_DE_WRITE_FREQ_REQ,
						      0x80000000, 150, 2);

	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"Failed to inform PCU about cdclk change (err %d, freq %d)\n",
			ret, cdclk);
		वापस;
	पूर्ण

	/* cdclk = vco / 2 / भागअणु1,1.5,2,4पूर्ण */
	चयन (DIV_ROUND_CLOSEST(vco, cdclk)) अणु
	शेष:
		drm_WARN_ON(&dev_priv->drm,
			    cdclk != dev_priv->cdclk.hw.bypass);
		drm_WARN_ON(&dev_priv->drm, vco != 0);
		fallthrough;
	हाल 2:
		भागider = BXT_CDCLK_CD2X_DIV_SEL_1;
		अवरोध;
	हाल 3:
		drm_WARN(&dev_priv->drm,
			 DISPLAY_VER(dev_priv) >= 10,
			 "Unsupported divider\n");
		भागider = BXT_CDCLK_CD2X_DIV_SEL_1_5;
		अवरोध;
	हाल 4:
		भागider = BXT_CDCLK_CD2X_DIV_SEL_2;
		अवरोध;
	हाल 8:
		drm_WARN(&dev_priv->drm,
			 DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv),
			 "Unsupported divider\n");
		भागider = BXT_CDCLK_CD2X_DIV_SEL_4;
		अवरोध;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv)) अणु
		अगर (dev_priv->cdclk.hw.vco != 0 &&
		    dev_priv->cdclk.hw.vco != vco)
			cnl_cdclk_pll_disable(dev_priv);

		अगर (dev_priv->cdclk.hw.vco != vco)
			cnl_cdclk_pll_enable(dev_priv, vco);

	पूर्ण अन्यथा अणु
		अगर (dev_priv->cdclk.hw.vco != 0 &&
		    dev_priv->cdclk.hw.vco != vco)
			bxt_de_pll_disable(dev_priv);

		अगर (dev_priv->cdclk.hw.vco != vco)
			bxt_de_pll_enable(dev_priv, vco);
	पूर्ण

	val = भागider | skl_cdclk_decimal(cdclk) |
		bxt_cdclk_cd2x_pipe(dev_priv, pipe);

	/*
	 * Disable SSA Preअक्षरge when CD घड़ी frequency < 500 MHz,
	 * enable otherwise.
	 */
	अगर (IS_GEN9_LP(dev_priv) && cdclk >= 500000)
		val |= BXT_CDCLK_SSA_PRECHARGE_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CDCLK_CTL, val);

	अगर (pipe != INVALID_PIPE)
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv)) अणु
		ret = sandybridge_pcode_ग_लिखो(dev_priv, SKL_PCODE_CDCLK_CONTROL,
					      cdclk_config->voltage_level);
	पूर्ण अन्यथा अणु
		/*
		 * The समयout isn't specअगरied, the 2ms used here is based on
		 * experiment.
		 * FIXME: Waiting क्रम the request completion could be delayed
		 * until the next PCODE request based on BSpec.
		 */
		ret = sandybridge_pcode_ग_लिखो_समयout(dev_priv,
						      HSW_PCODE_DE_WRITE_FREQ_REQ,
						      cdclk_config->voltage_level,
						      150, 2);
	पूर्ण

	अगर (ret) अणु
		drm_err(&dev_priv->drm,
			"PCode CDCLK freq set failed, (err %d, freq %d)\n",
			ret, cdclk);
		वापस;
	पूर्ण

	पूर्णांकel_update_cdclk(dev_priv);

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		/*
		 * Can't पढ़ो out the voltage level :(
		 * Let's just assume everything is as expected.
		 */
		dev_priv->cdclk.hw.voltage_level = cdclk_config->voltage_level;
पूर्ण

अटल व्योम bxt_sanitize_cdclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 cdctl, expected;
	पूर्णांक cdclk, vco;

	पूर्णांकel_update_cdclk(dev_priv);
	पूर्णांकel_dump_cdclk_config(&dev_priv->cdclk.hw, "Current CDCLK");

	अगर (dev_priv->cdclk.hw.vco == 0 ||
	    dev_priv->cdclk.hw.cdclk == dev_priv->cdclk.hw.bypass)
		जाओ sanitize;

	/* DPLL okay; verअगरy the cdघड़ी
	 *
	 * Some BIOS versions leave an incorrect decimal frequency value and
	 * set reserved MBZ bits in CDCLK_CTL at least during निकासing from S4,
	 * so sanitize this रेजिस्टर.
	 */
	cdctl = पूर्णांकel_de_पढ़ो(dev_priv, CDCLK_CTL);
	/*
	 * Let's ignore the pipe field, since BIOS could have configured the
	 * भागiders both synching to an active pipe, or asynchronously
	 * (PIPE_NONE).
	 */
	cdctl &= ~bxt_cdclk_cd2x_pipe(dev_priv, INVALID_PIPE);

	/* Make sure this is a legal cdclk value क्रम the platक्रमm */
	cdclk = bxt_calc_cdclk(dev_priv, dev_priv->cdclk.hw.cdclk);
	अगर (cdclk != dev_priv->cdclk.hw.cdclk)
		जाओ sanitize;

	/* Make sure the VCO is correct क्रम the cdclk */
	vco = bxt_calc_cdclk_pll_vco(dev_priv, cdclk);
	अगर (vco != dev_priv->cdclk.hw.vco)
		जाओ sanitize;

	expected = skl_cdclk_decimal(cdclk);

	/* Figure out what CD2X भागider we should be using क्रम this cdclk */
	चयन (DIV_ROUND_CLOSEST(dev_priv->cdclk.hw.vco,
				  dev_priv->cdclk.hw.cdclk)) अणु
	हाल 2:
		expected |= BXT_CDCLK_CD2X_DIV_SEL_1;
		अवरोध;
	हाल 3:
		expected |= BXT_CDCLK_CD2X_DIV_SEL_1_5;
		अवरोध;
	हाल 4:
		expected |= BXT_CDCLK_CD2X_DIV_SEL_2;
		अवरोध;
	हाल 8:
		expected |= BXT_CDCLK_CD2X_DIV_SEL_4;
		अवरोध;
	शेष:
		जाओ sanitize;
	पूर्ण

	/*
	 * Disable SSA Preअक्षरge when CD घड़ी frequency < 500 MHz,
	 * enable otherwise.
	 */
	अगर (IS_GEN9_LP(dev_priv) && dev_priv->cdclk.hw.cdclk >= 500000)
		expected |= BXT_CDCLK_SSA_PRECHARGE_ENABLE;

	अगर (cdctl == expected)
		/* All well; nothing to sanitize */
		वापस;

sanitize:
	drm_dbg_kms(&dev_priv->drm, "Sanitizing cdclk programmed by pre-os\n");

	/* क्रमce cdclk programming */
	dev_priv->cdclk.hw.cdclk = 0;

	/* क्रमce full PLL disable + enable */
	dev_priv->cdclk.hw.vco = -1;
पूर्ण

अटल व्योम bxt_cdclk_init_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_cdclk_config cdclk_config;

	bxt_sanitize_cdclk(dev_priv);

	अगर (dev_priv->cdclk.hw.cdclk != 0 &&
	    dev_priv->cdclk.hw.vco != 0)
		वापस;

	cdclk_config = dev_priv->cdclk.hw;

	/*
	 * FIXME:
	 * - The initial CDCLK needs to be पढ़ो from VBT.
	 *   Need to make this change after VBT has changes क्रम BXT.
	 */
	cdclk_config.cdclk = bxt_calc_cdclk(dev_priv, 0);
	cdclk_config.vco = bxt_calc_cdclk_pll_vco(dev_priv, cdclk_config.cdclk);
	cdclk_config.voltage_level =
		dev_priv->display.calc_voltage_level(cdclk_config.cdclk);

	bxt_set_cdclk(dev_priv, &cdclk_config, INVALID_PIPE);
पूर्ण

अटल व्योम bxt_cdclk_uninit_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_cdclk_config cdclk_config = dev_priv->cdclk.hw;

	cdclk_config.cdclk = cdclk_config.bypass;
	cdclk_config.vco = 0;
	cdclk_config.voltage_level =
		dev_priv->display.calc_voltage_level(cdclk_config.cdclk);

	bxt_set_cdclk(dev_priv, &cdclk_config, INVALID_PIPE);
पूर्ण

/**
 * पूर्णांकel_cdclk_init_hw - Initialize CDCLK hardware
 * @i915: i915 device
 *
 * Initialize CDCLK. This consists मुख्यly of initializing dev_priv->cdclk.hw and
 * sanitizing the state of the hardware अगर needed. This is generally करोne only
 * during the display core initialization sequence, after which the DMC will
 * take care of turning CDCLK off/on as needed.
 */
व्योम पूर्णांकel_cdclk_init_hw(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (IS_GEN9_LP(i915) || DISPLAY_VER(i915) >= 10)
		bxt_cdclk_init_hw(i915);
	अन्यथा अगर (IS_GEN9_BC(i915))
		skl_cdclk_init_hw(i915);
पूर्ण

/**
 * पूर्णांकel_cdclk_uninit_hw - Uninitialize CDCLK hardware
 * @i915: i915 device
 *
 * Uninitialize CDCLK. This is करोne only during the display core
 * uninitialization sequence.
 */
व्योम पूर्णांकel_cdclk_uninit_hw(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 10 || IS_GEN9_LP(i915))
		bxt_cdclk_uninit_hw(i915);
	अन्यथा अगर (IS_GEN9_BC(i915))
		skl_cdclk_uninit_hw(i915);
पूर्ण

/**
 * पूर्णांकel_cdclk_needs_modeset - Determine अगर changong between the CDCLK
 *                             configurations requires a modeset on all pipes
 * @a: first CDCLK configuration
 * @b: second CDCLK configuration
 *
 * Returns:
 * True अगर changing between the two CDCLK configurations
 * requires all pipes to be off, false अगर not.
 */
bool पूर्णांकel_cdclk_needs_modeset(स्थिर काष्ठा पूर्णांकel_cdclk_config *a,
			       स्थिर काष्ठा पूर्णांकel_cdclk_config *b)
अणु
	वापस a->cdclk != b->cdclk ||
		a->vco != b->vco ||
		a->ref != b->ref;
पूर्ण

/**
 * पूर्णांकel_cdclk_can_cd2x_update - Determine अगर changing between the two CDCLK
 *                               configurations requires only a cd2x भागider update
 * @dev_priv: i915 device
 * @a: first CDCLK configuration
 * @b: second CDCLK configuration
 *
 * Returns:
 * True अगर changing between the two CDCLK configurations
 * can be करोne with just a cd2x भागider update, false अगर not.
 */
अटल bool पूर्णांकel_cdclk_can_cd2x_update(काष्ठा drm_i915_निजी *dev_priv,
					स्थिर काष्ठा पूर्णांकel_cdclk_config *a,
					स्थिर काष्ठा पूर्णांकel_cdclk_config *b)
अणु
	/* Older hw करोesn't have the capability */
	अगर (DISPLAY_VER(dev_priv) < 10 && !IS_GEN9_LP(dev_priv))
		वापस false;

	वापस a->cdclk != b->cdclk &&
		a->vco == b->vco &&
		a->ref == b->ref;
पूर्ण

/**
 * पूर्णांकel_cdclk_changed - Determine अगर two CDCLK configurations are dअगरferent
 * @a: first CDCLK configuration
 * @b: second CDCLK configuration
 *
 * Returns:
 * True अगर the CDCLK configurations करोn't match, false अगर they करो.
 */
अटल bool पूर्णांकel_cdclk_changed(स्थिर काष्ठा पूर्णांकel_cdclk_config *a,
				स्थिर काष्ठा पूर्णांकel_cdclk_config *b)
अणु
	वापस पूर्णांकel_cdclk_needs_modeset(a, b) ||
		a->voltage_level != b->voltage_level;
पूर्ण

व्योम पूर्णांकel_dump_cdclk_config(स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			     स्थिर अक्षर *context)
अणु
	DRM_DEBUG_DRIVER("%s %d kHz, VCO %d kHz, ref %d kHz, bypass %d kHz, voltage level %d\n",
			 context, cdclk_config->cdclk, cdclk_config->vco,
			 cdclk_config->ref, cdclk_config->bypass,
			 cdclk_config->voltage_level);
पूर्ण

/**
 * पूर्णांकel_set_cdclk - Push the CDCLK configuration to the hardware
 * @dev_priv: i915 device
 * @cdclk_config: new CDCLK configuration
 * @pipe: pipe with which to synchronize the update
 *
 * Program the hardware based on the passed in CDCLK state,
 * अगर necessary.
 */
अटल व्योम पूर्णांकel_set_cdclk(काष्ठा drm_i915_निजी *dev_priv,
			    स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			    क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (!पूर्णांकel_cdclk_changed(&dev_priv->cdclk.hw, cdclk_config))
		वापस;

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !dev_priv->display.set_cdclk))
		वापस;

	पूर्णांकel_dump_cdclk_config(cdclk_config, "Changing CDCLK to");

	/*
	 * Lock aux/gmbus जबतक we change cdclk in हाल those
	 * functions use cdclk. Not all platक्रमms/ports करो,
	 * but we'll lock them all क्रम simplicity.
	 */
	mutex_lock(&dev_priv->gmbus_mutex);
	क्रम_each_पूर्णांकel_dp(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		mutex_lock_nest_lock(&पूर्णांकel_dp->aux.hw_mutex,
				     &dev_priv->gmbus_mutex);
	पूर्ण

	dev_priv->display.set_cdclk(dev_priv, cdclk_config, pipe);

	क्रम_each_पूर्णांकel_dp(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		mutex_unlock(&पूर्णांकel_dp->aux.hw_mutex);
	पूर्ण
	mutex_unlock(&dev_priv->gmbus_mutex);

	अगर (drm_WARN(&dev_priv->drm,
		     पूर्णांकel_cdclk_changed(&dev_priv->cdclk.hw, cdclk_config),
		     "cdclk state doesn't match!\n")) अणु
		पूर्णांकel_dump_cdclk_config(&dev_priv->cdclk.hw, "[hw state]");
		पूर्णांकel_dump_cdclk_config(cdclk_config, "[sw state]");
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_set_cdclk_pre_plane_update - Push the CDCLK state to the hardware
 * @state: पूर्णांकel atomic state
 *
 * Program the hardware beक्रमe updating the HW plane state based on the
 * new CDCLK state, अगर necessary.
 */
व्योम
पूर्णांकel_set_cdclk_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *old_cdclk_state =
		पूर्णांकel_atomic_get_old_cdclk_state(state);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *new_cdclk_state =
		पूर्णांकel_atomic_get_new_cdclk_state(state);
	क्रमागत pipe pipe = new_cdclk_state->pipe;

	अगर (!पूर्णांकel_cdclk_changed(&old_cdclk_state->actual,
				 &new_cdclk_state->actual))
		वापस;

	अगर (pipe == INVALID_PIPE ||
	    old_cdclk_state->actual.cdclk <= new_cdclk_state->actual.cdclk) अणु
		drm_WARN_ON(&dev_priv->drm, !new_cdclk_state->base.changed);

		पूर्णांकel_set_cdclk(dev_priv, &new_cdclk_state->actual, pipe);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_set_cdclk_post_plane_update - Push the CDCLK state to the hardware
 * @state: पूर्णांकel atomic state
 *
 * Program the hardware after updating the HW plane state based on the
 * new CDCLK state, अगर necessary.
 */
व्योम
पूर्णांकel_set_cdclk_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *old_cdclk_state =
		पूर्णांकel_atomic_get_old_cdclk_state(state);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *new_cdclk_state =
		पूर्णांकel_atomic_get_new_cdclk_state(state);
	क्रमागत pipe pipe = new_cdclk_state->pipe;

	अगर (!पूर्णांकel_cdclk_changed(&old_cdclk_state->actual,
				 &new_cdclk_state->actual))
		वापस;

	अगर (pipe != INVALID_PIPE &&
	    old_cdclk_state->actual.cdclk > new_cdclk_state->actual.cdclk) अणु
		drm_WARN_ON(&dev_priv->drm, !new_cdclk_state->base.changed);

		पूर्णांकel_set_cdclk(dev_priv, &new_cdclk_state->actual, pipe);
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pixel_rate_to_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक pixel_rate = crtc_state->pixel_rate;

	अगर (DISPLAY_VER(dev_priv) >= 10)
		वापस DIV_ROUND_UP(pixel_rate, 2);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 9) ||
		 IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		वापस pixel_rate;
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		वापस DIV_ROUND_UP(pixel_rate * 100, 95);
	अन्यथा अगर (crtc_state->द्विगुन_wide)
		वापस DIV_ROUND_UP(pixel_rate * 100, 90 * 2);
	अन्यथा
		वापस DIV_ROUND_UP(pixel_rate * 100, 90);
पूर्ण

अटल पूर्णांक पूर्णांकel_planes_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक min_cdclk = 0;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane)
		min_cdclk = max(crtc_state->min_cdclk[plane->id], min_cdclk);

	वापस min_cdclk;
पूर्ण

पूर्णांक पूर्णांकel_crtc_compute_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक min_cdclk;

	अगर (!crtc_state->hw.enable)
		वापस 0;

	min_cdclk = पूर्णांकel_pixel_rate_to_cdclk(crtc_state);

	/* pixel rate mustn't exceed 95% of cdclk with IPS on BDW */
	अगर (IS_BROADWELL(dev_priv) && hsw_crtc_state_ips_capable(crtc_state))
		min_cdclk = DIV_ROUND_UP(min_cdclk * 100, 95);

	/* BSpec says "Do not use DisplayPort with CDCLK less than 432 MHz,
	 * audio enabled, port width x4, and link rate HBR2 (5.4 GHz), or अन्यथा
	 * there may be audio corruption or screen corruption." This cdclk
	 * restriction क्रम GLK is 316.8 MHz.
	 */
	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state) &&
	    crtc_state->has_audio &&
	    crtc_state->port_घड़ी >= 540000 &&
	    crtc_state->lane_count == 4) अणु
		अगर (IS_DISPLAY_VER(dev_priv, 10)) अणु
			/* Display WA #1145: glk,cnl */
			min_cdclk = max(316800, min_cdclk);
		पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 9) || IS_BROADWELL(dev_priv)) अणु
			/* Display WA #1144: skl,bxt */
			min_cdclk = max(432000, min_cdclk);
		पूर्ण
	पूर्ण

	/*
	 * According to BSpec, "The CD घड़ी frequency must be at least twice
	 * the frequency of the Azalia BCLK." and BCLK is 96 MHz by शेष.
	 */
	अगर (crtc_state->has_audio && DISPLAY_VER(dev_priv) >= 9)
		min_cdclk = max(2 * 96000, min_cdclk);

	/*
	 * "For DP audio configuration, cdclk frequency shall be set to
	 *  meet the following requirements:
	 *  DP Link Frequency(MHz) | Cdclk frequency(MHz)
	 *  270                    | 320 or higher
	 *  162                    | 200 or higher"
	 */
	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    पूर्णांकel_crtc_has_dp_encoder(crtc_state) && crtc_state->has_audio)
		min_cdclk = max(crtc_state->port_घड़ी, min_cdclk);

	/*
	 * On Valleyview some DSI panels lose (v|h)sync when the घड़ी is lower
	 * than 320000KHz.
	 */
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI) &&
	    IS_VALLEYVIEW(dev_priv))
		min_cdclk = max(320000, min_cdclk);

	/*
	 * On Geminilake once the CDCLK माला_लो as low as 79200
	 * picture माला_लो unstable, despite that values are
	 * correct क्रम DSI PLL and DE PLL.
	 */
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI) &&
	    IS_GEMINILAKE(dev_priv))
		min_cdclk = max(158400, min_cdclk);

	/* Account क्रम additional needs from the planes */
	min_cdclk = max(पूर्णांकel_planes_min_cdclk(crtc_state), min_cdclk);

	/*
	 * HACK. Currently क्रम TGL platक्रमms we calculate
	 * min_cdclk initially based on pixel_rate भागided
	 * by 2, accounting क्रम also plane requirements,
	 * however in some हालs the lowest possible CDCLK
	 * करोesn't work and causing the underruns.
	 * Explicitly stating here that this seems to be currently
	 * rather a Hack, than final solution.
	 */
	अगर (IS_TIGERLAKE(dev_priv)) अणु
		/*
		 * Clamp to max_cdclk_freq in हाल pixel rate is higher,
		 * in order not to अवरोध an 8K, but still leave W/A at place.
		 */
		min_cdclk = max_t(पूर्णांक, min_cdclk,
				  min_t(पूर्णांक, crtc_state->pixel_rate,
					dev_priv->max_cdclk_freq));
	पूर्ण

	अगर (min_cdclk > dev_priv->max_cdclk_freq) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "required cdclk (%d kHz) exceeds max (%d kHz)\n",
			    min_cdclk, dev_priv->max_cdclk_freq);
		वापस -EINVAL;
	पूर्ण

	वापस min_cdclk;
पूर्ण

अटल पूर्णांक पूर्णांकel_compute_min_cdclk(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = cdclk_state->base.state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_bw_state *bw_state = शून्य;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	पूर्णांक min_cdclk, i;
	क्रमागत pipe pipe;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		पूर्णांक ret;

		min_cdclk = पूर्णांकel_crtc_compute_min_cdclk(crtc_state);
		अगर (min_cdclk < 0)
			वापस min_cdclk;

		bw_state = पूर्णांकel_atomic_get_bw_state(state);
		अगर (IS_ERR(bw_state))
			वापस PTR_ERR(bw_state);

		अगर (cdclk_state->min_cdclk[crtc->pipe] == min_cdclk)
			जारी;

		cdclk_state->min_cdclk[crtc->pipe] = min_cdclk;

		ret = पूर्णांकel_atomic_lock_global_state(&cdclk_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	min_cdclk = cdclk_state->क्रमce_min_cdclk;
	क्रम_each_pipe(dev_priv, pipe) अणु
		min_cdclk = max(cdclk_state->min_cdclk[pipe], min_cdclk);

		अगर (!bw_state)
			जारी;

		min_cdclk = max(bw_state->min_cdclk, min_cdclk);
	पूर्ण

	वापस min_cdclk;
पूर्ण

/*
 * Account क्रम port घड़ी min voltage level requirements.
 * This only really करोes something on CNL+ but can be
 * called on earlier platक्रमms as well.
 *
 * Note that this functions assumes that 0 is
 * the lowest voltage value, and higher values
 * correspond to increasingly higher voltages.
 *
 * Should that relationship no दीर्घer hold on
 * future platक्रमms this code will need to be
 * adjusted.
 */
अटल पूर्णांक bxt_compute_min_voltage_level(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = cdclk_state->base.state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	u8 min_voltage_level;
	पूर्णांक i;
	क्रमागत pipe pipe;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		पूर्णांक ret;

		अगर (crtc_state->hw.enable)
			min_voltage_level = crtc_state->min_voltage_level;
		अन्यथा
			min_voltage_level = 0;

		अगर (cdclk_state->min_voltage_level[crtc->pipe] == min_voltage_level)
			जारी;

		cdclk_state->min_voltage_level[crtc->pipe] = min_voltage_level;

		ret = पूर्णांकel_atomic_lock_global_state(&cdclk_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	min_voltage_level = 0;
	क्रम_each_pipe(dev_priv, pipe)
		min_voltage_level = max(cdclk_state->min_voltage_level[pipe],
					min_voltage_level);

	वापस min_voltage_level;
पूर्ण

अटल पूर्णांक vlv_modeset_calc_cdclk(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = cdclk_state->base.state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	पूर्णांक min_cdclk, cdclk;

	min_cdclk = पूर्णांकel_compute_min_cdclk(cdclk_state);
	अगर (min_cdclk < 0)
		वापस min_cdclk;

	cdclk = vlv_calc_cdclk(dev_priv, min_cdclk);

	cdclk_state->logical.cdclk = cdclk;
	cdclk_state->logical.voltage_level =
		vlv_calc_voltage_level(dev_priv, cdclk);

	अगर (!cdclk_state->active_pipes) अणु
		cdclk = vlv_calc_cdclk(dev_priv, cdclk_state->क्रमce_min_cdclk);

		cdclk_state->actual.cdclk = cdclk;
		cdclk_state->actual.voltage_level =
			vlv_calc_voltage_level(dev_priv, cdclk);
	पूर्ण अन्यथा अणु
		cdclk_state->actual = cdclk_state->logical;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bdw_modeset_calc_cdclk(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	पूर्णांक min_cdclk, cdclk;

	min_cdclk = पूर्णांकel_compute_min_cdclk(cdclk_state);
	अगर (min_cdclk < 0)
		वापस min_cdclk;

	/*
	 * FIXME should also account क्रम plane ratio
	 * once 64bpp pixel क्रमmats are supported.
	 */
	cdclk = bdw_calc_cdclk(min_cdclk);

	cdclk_state->logical.cdclk = cdclk;
	cdclk_state->logical.voltage_level =
		bdw_calc_voltage_level(cdclk);

	अगर (!cdclk_state->active_pipes) अणु
		cdclk = bdw_calc_cdclk(cdclk_state->क्रमce_min_cdclk);

		cdclk_state->actual.cdclk = cdclk;
		cdclk_state->actual.voltage_level =
			bdw_calc_voltage_level(cdclk);
	पूर्ण अन्यथा अणु
		cdclk_state->actual = cdclk_state->logical;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skl_dpll0_vco(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = cdclk_state->base.state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	पूर्णांक vco, i;

	vco = cdclk_state->logical.vco;
	अगर (!vco)
		vco = dev_priv->skl_preferred_vco_freq;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (!crtc_state->hw.enable)
			जारी;

		अगर (!पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
			जारी;

		/*
		 * DPLL0 VCO may need to be adjusted to get the correct
		 * घड़ी क्रम eDP. This will affect cdclk as well.
		 */
		चयन (crtc_state->port_घड़ी / 2) अणु
		हाल 108000:
		हाल 216000:
			vco = 8640000;
			अवरोध;
		शेष:
			vco = 8100000;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस vco;
पूर्ण

अटल पूर्णांक skl_modeset_calc_cdclk(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	पूर्णांक min_cdclk, cdclk, vco;

	min_cdclk = पूर्णांकel_compute_min_cdclk(cdclk_state);
	अगर (min_cdclk < 0)
		वापस min_cdclk;

	vco = skl_dpll0_vco(cdclk_state);

	/*
	 * FIXME should also account क्रम plane ratio
	 * once 64bpp pixel क्रमmats are supported.
	 */
	cdclk = skl_calc_cdclk(min_cdclk, vco);

	cdclk_state->logical.vco = vco;
	cdclk_state->logical.cdclk = cdclk;
	cdclk_state->logical.voltage_level =
		skl_calc_voltage_level(cdclk);

	अगर (!cdclk_state->active_pipes) अणु
		cdclk = skl_calc_cdclk(cdclk_state->क्रमce_min_cdclk, vco);

		cdclk_state->actual.vco = vco;
		cdclk_state->actual.cdclk = cdclk;
		cdclk_state->actual.voltage_level =
			skl_calc_voltage_level(cdclk);
	पूर्ण अन्यथा अणु
		cdclk_state->actual = cdclk_state->logical;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_modeset_calc_cdclk(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = cdclk_state->base.state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	पूर्णांक min_cdclk, min_voltage_level, cdclk, vco;

	min_cdclk = पूर्णांकel_compute_min_cdclk(cdclk_state);
	अगर (min_cdclk < 0)
		वापस min_cdclk;

	min_voltage_level = bxt_compute_min_voltage_level(cdclk_state);
	अगर (min_voltage_level < 0)
		वापस min_voltage_level;

	cdclk = bxt_calc_cdclk(dev_priv, min_cdclk);
	vco = bxt_calc_cdclk_pll_vco(dev_priv, cdclk);

	cdclk_state->logical.vco = vco;
	cdclk_state->logical.cdclk = cdclk;
	cdclk_state->logical.voltage_level =
		max_t(पूर्णांक, min_voltage_level,
		      dev_priv->display.calc_voltage_level(cdclk));

	अगर (!cdclk_state->active_pipes) अणु
		cdclk = bxt_calc_cdclk(dev_priv, cdclk_state->क्रमce_min_cdclk);
		vco = bxt_calc_cdclk_pll_vco(dev_priv, cdclk);

		cdclk_state->actual.vco = vco;
		cdclk_state->actual.cdclk = cdclk;
		cdclk_state->actual.voltage_level =
			dev_priv->display.calc_voltage_level(cdclk);
	पूर्ण अन्यथा अणु
		cdclk_state->actual = cdclk_state->logical;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_modeset_all_pipes(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;

	/*
	 * Add all pipes to the state, and क्रमce
	 * a modeset on all the active ones.
	 */
	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		पूर्णांक ret;

		crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		अगर (!crtc_state->hw.active ||
		    drm_atomic_crtc_needs_modeset(&crtc_state->uapi))
			जारी;

		crtc_state->uapi.mode_changed = true;

		ret = drm_atomic_add_affected_connectors(&state->base,
							 &crtc->base);
		अगर (ret)
			वापस ret;

		ret = पूर्णांकel_atomic_add_affected_planes(state, crtc);
		अगर (ret)
			वापस ret;

		crtc_state->update_planes |= crtc_state->active_planes;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fixed_modeset_calc_cdclk(काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	पूर्णांक min_cdclk;

	/*
	 * We can't change the cdclk frequency, but we still want to
	 * check that the required minimum frequency करोesn't exceed
	 * the actual cdclk frequency.
	 */
	min_cdclk = पूर्णांकel_compute_min_cdclk(cdclk_state);
	अगर (min_cdclk < 0)
		वापस min_cdclk;

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_global_state *पूर्णांकel_cdclk_duplicate_state(काष्ठा पूर्णांकel_global_obj *obj)
अणु
	काष्ठा पूर्णांकel_cdclk_state *cdclk_state;

	cdclk_state = kmemdup(obj->state, माप(*cdclk_state), GFP_KERNEL);
	अगर (!cdclk_state)
		वापस शून्य;

	cdclk_state->pipe = INVALID_PIPE;

	वापस &cdclk_state->base;
पूर्ण

अटल व्योम पूर्णांकel_cdclk_destroy_state(काष्ठा पूर्णांकel_global_obj *obj,
				      काष्ठा पूर्णांकel_global_state *state)
अणु
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_global_state_funcs पूर्णांकel_cdclk_funcs = अणु
	.atomic_duplicate_state = पूर्णांकel_cdclk_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_cdclk_destroy_state,
पूर्ण;

काष्ठा पूर्णांकel_cdclk_state *
पूर्णांकel_atomic_get_cdclk_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_global_state *cdclk_state;

	cdclk_state = पूर्णांकel_atomic_get_global_obj_state(state, &dev_priv->cdclk.obj);
	अगर (IS_ERR(cdclk_state))
		वापस ERR_CAST(cdclk_state);

	वापस to_पूर्णांकel_cdclk_state(cdclk_state);
पूर्ण

पूर्णांक पूर्णांकel_cdclk_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_cdclk_state *cdclk_state;

	cdclk_state = kzalloc(माप(*cdclk_state), GFP_KERNEL);
	अगर (!cdclk_state)
		वापस -ENOMEM;

	पूर्णांकel_atomic_global_obj_init(dev_priv, &dev_priv->cdclk.obj,
				     &cdclk_state->base, &पूर्णांकel_cdclk_funcs);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_modeset_calc_cdclk(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *old_cdclk_state;
	काष्ठा पूर्णांकel_cdclk_state *new_cdclk_state;
	क्रमागत pipe pipe;
	पूर्णांक ret;

	new_cdclk_state = पूर्णांकel_atomic_get_cdclk_state(state);
	अगर (IS_ERR(new_cdclk_state))
		वापस PTR_ERR(new_cdclk_state);

	old_cdclk_state = पूर्णांकel_atomic_get_old_cdclk_state(state);

	new_cdclk_state->active_pipes =
		पूर्णांकel_calc_active_pipes(state, old_cdclk_state->active_pipes);

	ret = dev_priv->display.modeset_calc_cdclk(new_cdclk_state);
	अगर (ret)
		वापस ret;

	अगर (पूर्णांकel_cdclk_changed(&old_cdclk_state->actual,
				&new_cdclk_state->actual)) अणु
		/*
		 * Also serialize commits across all crtcs
		 * अगर the actual hw needs to be poked.
		 */
		ret = पूर्णांकel_atomic_serialize_global_state(&new_cdclk_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (old_cdclk_state->active_pipes != new_cdclk_state->active_pipes ||
		   old_cdclk_state->क्रमce_min_cdclk != new_cdclk_state->क्रमce_min_cdclk ||
		   पूर्णांकel_cdclk_changed(&old_cdclk_state->logical,
				       &new_cdclk_state->logical)) अणु
		ret = पूर्णांकel_atomic_lock_global_state(&new_cdclk_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (is_घातer_of_2(new_cdclk_state->active_pipes) &&
	    पूर्णांकel_cdclk_can_cd2x_update(dev_priv,
					&old_cdclk_state->actual,
					&new_cdclk_state->actual)) अणु
		काष्ठा पूर्णांकel_crtc *crtc;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;

		pipe = ilog2(new_cdclk_state->active_pipes);
		crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

		crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		अगर (drm_atomic_crtc_needs_modeset(&crtc_state->uapi))
			pipe = INVALID_PIPE;
	पूर्ण अन्यथा अणु
		pipe = INVALID_PIPE;
	पूर्ण

	अगर (pipe != INVALID_PIPE) अणु
		new_cdclk_state->pipe = pipe;

		drm_dbg_kms(&dev_priv->drm,
			    "Can change cdclk with pipe %c active\n",
			    pipe_name(pipe));
	पूर्ण अन्यथा अगर (पूर्णांकel_cdclk_needs_modeset(&old_cdclk_state->actual,
					     &new_cdclk_state->actual)) अणु
		/* All pipes must be चयनed off जबतक we change the cdclk. */
		ret = पूर्णांकel_modeset_all_pipes(state);
		अगर (ret)
			वापस ret;

		new_cdclk_state->pipe = INVALID_PIPE;

		drm_dbg_kms(&dev_priv->drm,
			    "Modeset required for cdclk change\n");
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "New cdclk calculated to be logical %u kHz, actual %u kHz\n",
		    new_cdclk_state->logical.cdclk,
		    new_cdclk_state->actual.cdclk);
	drm_dbg_kms(&dev_priv->drm,
		    "New voltage level calculated to be logical %u, actual %u\n",
		    new_cdclk_state->logical.voltage_level,
		    new_cdclk_state->actual.voltage_level);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_compute_max_करोtclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक max_cdclk_freq = dev_priv->max_cdclk_freq;

	अगर (DISPLAY_VER(dev_priv) >= 10)
		वापस 2 * max_cdclk_freq;
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 9) ||
		 IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		वापस max_cdclk_freq;
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		वापस max_cdclk_freq*95/100;
	अन्यथा अगर (DISPLAY_VER(dev_priv) < 4)
		वापस 2*max_cdclk_freq*90/100;
	अन्यथा
		वापस max_cdclk_freq*90/100;
पूर्ण

/**
 * पूर्णांकel_update_max_cdclk - Determine the maximum support CDCLK frequency
 * @dev_priv: i915 device
 *
 * Determine the maximum CDCLK frequency the platक्रमm supports, and also
 * derive the maximum करोt घड़ी frequency the maximum CDCLK frequency
 * allows.
 */
व्योम पूर्णांकel_update_max_cdclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_JSL_EHL(dev_priv)) अणु
		अगर (dev_priv->cdclk.hw.ref == 24000)
			dev_priv->max_cdclk_freq = 552000;
		अन्यथा
			dev_priv->max_cdclk_freq = 556800;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		अगर (dev_priv->cdclk.hw.ref == 24000)
			dev_priv->max_cdclk_freq = 648000;
		अन्यथा
			dev_priv->max_cdclk_freq = 652800;
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		dev_priv->max_cdclk_freq = 528000;
	पूर्ण अन्यथा अगर (IS_GEN9_BC(dev_priv)) अणु
		u32 limit = पूर्णांकel_de_पढ़ो(dev_priv, SKL_DFSM) & SKL_DFSM_CDCLK_LIMIT_MASK;
		पूर्णांक max_cdclk, vco;

		vco = dev_priv->skl_preferred_vco_freq;
		drm_WARN_ON(&dev_priv->drm, vco != 8100000 && vco != 8640000);

		/*
		 * Use the lower (vco 8640) cdclk values as a
		 * first guess. skl_calc_cdclk() will correct it
		 * अगर the preferred vco is 8100 instead.
		 */
		अगर (limit == SKL_DFSM_CDCLK_LIMIT_675)
			max_cdclk = 617143;
		अन्यथा अगर (limit == SKL_DFSM_CDCLK_LIMIT_540)
			max_cdclk = 540000;
		अन्यथा अगर (limit == SKL_DFSM_CDCLK_LIMIT_450)
			max_cdclk = 432000;
		अन्यथा
			max_cdclk = 308571;

		dev_priv->max_cdclk_freq = skl_calc_cdclk(max_cdclk, vco);
	पूर्ण अन्यथा अगर (IS_GEMINILAKE(dev_priv)) अणु
		dev_priv->max_cdclk_freq = 316800;
	पूर्ण अन्यथा अगर (IS_BROXTON(dev_priv)) अणु
		dev_priv->max_cdclk_freq = 624000;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv))  अणु
		/*
		 * FIXME with extra cooling we can allow
		 * 540 MHz क्रम ULX and 675 Mhz क्रम ULT.
		 * How can we know अगर extra cooling is
		 * available? PCI ID, VTB, something अन्यथा?
		 */
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP) & HSW_CDCLK_LIMIT)
			dev_priv->max_cdclk_freq = 450000;
		अन्यथा अगर (IS_BDW_ULX(dev_priv))
			dev_priv->max_cdclk_freq = 450000;
		अन्यथा अगर (IS_BDW_ULT(dev_priv))
			dev_priv->max_cdclk_freq = 540000;
		अन्यथा
			dev_priv->max_cdclk_freq = 675000;
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(dev_priv)) अणु
		dev_priv->max_cdclk_freq = 320000;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv)) अणु
		dev_priv->max_cdclk_freq = 400000;
	पूर्ण अन्यथा अणु
		/* otherwise assume cdclk is fixed */
		dev_priv->max_cdclk_freq = dev_priv->cdclk.hw.cdclk;
	पूर्ण

	dev_priv->max_करोtclk_freq = पूर्णांकel_compute_max_करोtclk(dev_priv);

	drm_dbg(&dev_priv->drm, "Max CD clock rate: %d kHz\n",
		dev_priv->max_cdclk_freq);

	drm_dbg(&dev_priv->drm, "Max dotclock rate: %d kHz\n",
		dev_priv->max_करोtclk_freq);
पूर्ण

/**
 * पूर्णांकel_update_cdclk - Determine the current CDCLK frequency
 * @dev_priv: i915 device
 *
 * Determine the current CDCLK frequency.
 */
व्योम पूर्णांकel_update_cdclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	dev_priv->display.get_cdclk(dev_priv, &dev_priv->cdclk.hw);

	/*
	 * 9:0 CMBUS [sic] CDCLK frequency (cdfreq):
	 * Programmng [sic] note: bit[9:2] should be programmed to the number
	 * of cdclk that generates 4MHz reference घड़ी freq which is used to
	 * generate GMBus घड़ी. This will vary with the cdclk freq.
	 */
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, GMBUSFREQ_VLV,
			       DIV_ROUND_UP(dev_priv->cdclk.hw.cdclk, 1000));
पूर्ण

अटल पूर्णांक dg1_rawclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * DG1 always uses a 38.4 MHz rawclk.  The bspec tells us
	 * "Program Numerator=2, Denominator=4, Divider=37 decimal."
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_RAWCLK_FREQ,
		       CNP_RAWCLK_DEN(4) | CNP_RAWCLK_DIV(37) | ICP_RAWCLK_NUM(2));

	वापस 38400;
पूर्ण

अटल पूर्णांक cnp_rawclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 rawclk;
	पूर्णांक भागider, fraction;

	अगर (पूर्णांकel_de_पढ़ो(dev_priv, SFUSE_STRAP) & SFUSE_STRAP_RAW_FREQUENCY) अणु
		/* 24 MHz */
		भागider = 24000;
		fraction = 0;
	पूर्ण अन्यथा अणु
		/* 19.2 MHz */
		भागider = 19000;
		fraction = 200;
	पूर्ण

	rawclk = CNP_RAWCLK_DIV(भागider / 1000);
	अगर (fraction) अणु
		पूर्णांक numerator = 1;

		rawclk |= CNP_RAWCLK_DEN(DIV_ROUND_CLOSEST(numerator * 1000,
							   fraction) - 1);
		अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_ICP)
			rawclk |= ICP_RAWCLK_NUM(numerator);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_RAWCLK_FREQ, rawclk);
	वापस भागider + fraction;
पूर्ण

अटल पूर्णांक pch_rawclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस (पूर्णांकel_de_पढ़ो(dev_priv, PCH_RAWCLK_FREQ) & RAWCLK_FREQ_MASK) * 1000;
पूर्ण

अटल पूर्णांक vlv_hrawclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* RAWCLK_FREQ_VLV रेजिस्टर updated from घातer well code */
	वापस vlv_get_cck_घड़ी_hpll(dev_priv, "hrawclk",
				      CCK_DISPLAY_REF_CLOCK_CONTROL);
पूर्ण

अटल पूर्णांक i9xx_hrawclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 clkcfg;

	/*
	 * hrawघड़ी is 1/4 the FSB frequency
	 *
	 * Note that this only पढ़ोs the state of the FSB
	 * straps, not the actual FSB frequency. Some BIOSen
	 * let you configure each independently. Ideally we'd
	 * पढ़ो out the actual FSB frequency but sadly we
	 * करोn't know which रेजिस्टरs have that inक्रमmation,
	 * and all the relevant करोcs have gone to bit heaven :(
	 */
	clkcfg = पूर्णांकel_de_पढ़ो(dev_priv, CLKCFG) & CLKCFG_FSB_MASK;

	अगर (IS_MOBILE(dev_priv)) अणु
		चयन (clkcfg) अणु
		हाल CLKCFG_FSB_400:
			वापस 100000;
		हाल CLKCFG_FSB_533:
			वापस 133333;
		हाल CLKCFG_FSB_667:
			वापस 166667;
		हाल CLKCFG_FSB_800:
			वापस 200000;
		हाल CLKCFG_FSB_1067:
			वापस 266667;
		हाल CLKCFG_FSB_1333:
			वापस 333333;
		शेष:
			MISSING_CASE(clkcfg);
			वापस 133333;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (clkcfg) अणु
		हाल CLKCFG_FSB_400_ALT:
			वापस 100000;
		हाल CLKCFG_FSB_533:
			वापस 133333;
		हाल CLKCFG_FSB_667:
			वापस 166667;
		हाल CLKCFG_FSB_800:
			वापस 200000;
		हाल CLKCFG_FSB_1067_ALT:
			वापस 266667;
		हाल CLKCFG_FSB_1333_ALT:
			वापस 333333;
		हाल CLKCFG_FSB_1600_ALT:
			वापस 400000;
		शेष:
			वापस 133333;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_पढ़ो_rawclk - Determine the current RAWCLK frequency
 * @dev_priv: i915 device
 *
 * Determine the current RAWCLK frequency. RAWCLK is a fixed
 * frequency घड़ी so this needs to करोne only once.
 */
u32 पूर्णांकel_पढ़ो_rawclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 freq;

	अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_DG1)
		freq = dg1_rawclk(dev_priv);
	अन्यथा अगर (INTEL_PCH_TYPE(dev_priv) >= PCH_CNP)
		freq = cnp_rawclk(dev_priv);
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		freq = pch_rawclk(dev_priv);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		freq = vlv_hrawclk(dev_priv);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 3)
		freq = i9xx_hrawclk(dev_priv);
	अन्यथा
		/* no rawclk on other platक्रमms, or no need to know it */
		वापस 0;

	वापस freq;
पूर्ण

/**
 * पूर्णांकel_init_cdclk_hooks - Initialize CDCLK related modesetting hooks
 * @dev_priv: i915 device
 */
व्योम पूर्णांकel_init_cdclk_hooks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_ROCKETLAKE(dev_priv)) अणु
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
		dev_priv->display.calc_voltage_level = tgl_calc_voltage_level;
		dev_priv->cdclk.table = rkl_cdclk_table;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
		dev_priv->display.calc_voltage_level = tgl_calc_voltage_level;
		dev_priv->cdclk.table = icl_cdclk_table;
	पूर्ण अन्यथा अगर (IS_JSL_EHL(dev_priv)) अणु
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
		dev_priv->display.calc_voltage_level = ehl_calc_voltage_level;
		dev_priv->cdclk.table = icl_cdclk_table;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
		dev_priv->display.calc_voltage_level = icl_calc_voltage_level;
		dev_priv->cdclk.table = icl_cdclk_table;
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
		dev_priv->display.calc_voltage_level = cnl_calc_voltage_level;
		dev_priv->cdclk.table = cnl_cdclk_table;
	पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.set_cdclk = bxt_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = bxt_modeset_calc_cdclk;
		dev_priv->display.calc_voltage_level = bxt_calc_voltage_level;
		अगर (IS_GEMINILAKE(dev_priv))
			dev_priv->cdclk.table = glk_cdclk_table;
		अन्यथा
			dev_priv->cdclk.table = bxt_cdclk_table;
	पूर्ण अन्यथा अगर (IS_GEN9_BC(dev_priv)) अणु
		dev_priv->display.bw_calc_min_cdclk = skl_bw_calc_min_cdclk;
		dev_priv->display.set_cdclk = skl_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = skl_modeset_calc_cdclk;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv)) अणु
		dev_priv->display.bw_calc_min_cdclk = पूर्णांकel_bw_calc_min_cdclk;
		dev_priv->display.set_cdclk = bdw_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = bdw_modeset_calc_cdclk;
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(dev_priv)) अणु
		dev_priv->display.bw_calc_min_cdclk = पूर्णांकel_bw_calc_min_cdclk;
		dev_priv->display.set_cdclk = chv_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = vlv_modeset_calc_cdclk;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv)) अणु
		dev_priv->display.bw_calc_min_cdclk = पूर्णांकel_bw_calc_min_cdclk;
		dev_priv->display.set_cdclk = vlv_set_cdclk;
		dev_priv->display.modeset_calc_cdclk = vlv_modeset_calc_cdclk;
	पूर्ण अन्यथा अणु
		dev_priv->display.bw_calc_min_cdclk = पूर्णांकel_bw_calc_min_cdclk;
		dev_priv->display.modeset_calc_cdclk = fixed_modeset_calc_cdclk;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 10 || IS_GEN9_LP(dev_priv))
		dev_priv->display.get_cdclk = bxt_get_cdclk;
	अन्यथा अगर (IS_GEN9_BC(dev_priv))
		dev_priv->display.get_cdclk = skl_get_cdclk;
	अन्यथा अगर (IS_BROADWELL(dev_priv))
		dev_priv->display.get_cdclk = bdw_get_cdclk;
	अन्यथा अगर (IS_HASWELL(dev_priv))
		dev_priv->display.get_cdclk = hsw_get_cdclk;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		dev_priv->display.get_cdclk = vlv_get_cdclk;
	अन्यथा अगर (IS_SANDYBRIDGE(dev_priv) || IS_IVYBRIDGE(dev_priv))
		dev_priv->display.get_cdclk = fixed_400mhz_get_cdclk;
	अन्यथा अगर (IS_IRONLAKE(dev_priv))
		dev_priv->display.get_cdclk = fixed_450mhz_get_cdclk;
	अन्यथा अगर (IS_GM45(dev_priv))
		dev_priv->display.get_cdclk = gm45_get_cdclk;
	अन्यथा अगर (IS_G45(dev_priv))
		dev_priv->display.get_cdclk = g33_get_cdclk;
	अन्यथा अगर (IS_I965GM(dev_priv))
		dev_priv->display.get_cdclk = i965gm_get_cdclk;
	अन्यथा अगर (IS_I965G(dev_priv))
		dev_priv->display.get_cdclk = fixed_400mhz_get_cdclk;
	अन्यथा अगर (IS_PINEVIEW(dev_priv))
		dev_priv->display.get_cdclk = pnv_get_cdclk;
	अन्यथा अगर (IS_G33(dev_priv))
		dev_priv->display.get_cdclk = g33_get_cdclk;
	अन्यथा अगर (IS_I945GM(dev_priv))
		dev_priv->display.get_cdclk = i945gm_get_cdclk;
	अन्यथा अगर (IS_I945G(dev_priv))
		dev_priv->display.get_cdclk = fixed_400mhz_get_cdclk;
	अन्यथा अगर (IS_I915GM(dev_priv))
		dev_priv->display.get_cdclk = i915gm_get_cdclk;
	अन्यथा अगर (IS_I915G(dev_priv))
		dev_priv->display.get_cdclk = fixed_333mhz_get_cdclk;
	अन्यथा अगर (IS_I865G(dev_priv))
		dev_priv->display.get_cdclk = fixed_266mhz_get_cdclk;
	अन्यथा अगर (IS_I85X(dev_priv))
		dev_priv->display.get_cdclk = i85x_get_cdclk;
	अन्यथा अगर (IS_I845G(dev_priv))
		dev_priv->display.get_cdclk = fixed_200mhz_get_cdclk;
	अन्यथा अगर (IS_I830(dev_priv))
		dev_priv->display.get_cdclk = fixed_133mhz_get_cdclk;

	अगर (drm_WARN(&dev_priv->drm, !dev_priv->display.get_cdclk,
		     "Unknown platform. Assuming 133 MHz CDCLK\n"))
		dev_priv->display.get_cdclk = fixed_133mhz_get_cdclk;
पूर्ण
