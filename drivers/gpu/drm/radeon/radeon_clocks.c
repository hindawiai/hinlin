<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_reg.h"

/* 10 khz */
uपूर्णांक32_t radeon_legacy_get_engine_घड़ी(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_pll *spll = &rdev->घड़ी.spll;
	uपूर्णांक32_t fb_भाग, ref_भाग, post_भाग, sclk;

	fb_भाग = RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV);
	fb_भाग = (fb_भाग >> RADEON_SPLL_FB_DIV_SHIFT) & RADEON_SPLL_FB_DIV_MASK;
	fb_भाग <<= 1;
	fb_भाग *= spll->reference_freq;

	ref_भाग =
	    RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) & RADEON_M_SPLL_REF_DIV_MASK;

	अगर (ref_भाग == 0)
		वापस 0;

	sclk = fb_भाग / ref_भाग;

	post_भाग = RREG32_PLL(RADEON_SCLK_CNTL) & RADEON_SCLK_SRC_SEL_MASK;
	अगर (post_भाग == 2)
		sclk >>= 1;
	अन्यथा अगर (post_भाग == 3)
		sclk >>= 2;
	अन्यथा अगर (post_भाग == 4)
		sclk >>= 3;

	वापस sclk;
पूर्ण

/* 10 khz */
uपूर्णांक32_t radeon_legacy_get_memory_घड़ी(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_pll *mpll = &rdev->घड़ी.mpll;
	uपूर्णांक32_t fb_भाग, ref_भाग, post_भाग, mclk;

	fb_भाग = RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV);
	fb_भाग = (fb_भाग >> RADEON_MPLL_FB_DIV_SHIFT) & RADEON_MPLL_FB_DIV_MASK;
	fb_भाग <<= 1;
	fb_भाग *= mpll->reference_freq;

	ref_भाग =
	    RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) & RADEON_M_SPLL_REF_DIV_MASK;

	अगर (ref_भाग == 0)
		वापस 0;

	mclk = fb_भाग / ref_भाग;

	post_भाग = RREG32_PLL(RADEON_MCLK_CNTL) & 0x7;
	अगर (post_भाग == 2)
		mclk >>= 1;
	अन्यथा अगर (post_भाग == 3)
		mclk >>= 2;
	अन्यथा अगर (post_भाग == 4)
		mclk >>= 3;

	वापस mclk;
पूर्ण

#अगर_घोषित CONFIG_OF
/*
 * Read XTAL (ref घड़ी), SCLK and MCLK from Open Firmware device
 * tree. Hopefully, ATI OF driver is kind enough to fill these
 */
अटल bool radeon_पढ़ो_घड़ीs_OF(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा device_node *dp = rdev->pdev->dev.of_node;
	स्थिर u32 *val;
	काष्ठा radeon_pll *p1pll = &rdev->घड़ी.p1pll;
	काष्ठा radeon_pll *p2pll = &rdev->घड़ी.p2pll;
	काष्ठा radeon_pll *spll = &rdev->घड़ी.spll;
	काष्ठा radeon_pll *mpll = &rdev->घड़ी.mpll;

	अगर (dp == शून्य)
		वापस false;
	val = of_get_property(dp, "ATY,RefCLK", शून्य);
	अगर (!val || !*val) अणु
		pr_warn("radeonfb: No ATY,RefCLK property !\n");
		वापस false;
	पूर्ण
	p1pll->reference_freq = p2pll->reference_freq = (*val) / 10;
	p1pll->reference_भाग = RREG32_PLL(RADEON_PPLL_REF_DIV) & 0x3ff;
	अगर (p1pll->reference_भाग < 2)
		p1pll->reference_भाग = 12;
	p2pll->reference_भाग = p1pll->reference_भाग;

	/* These aren't in the device-tree */
	अगर (rdev->family >= CHIP_R420) अणु
		p1pll->pll_in_min = 100;
		p1pll->pll_in_max = 1350;
		p1pll->pll_out_min = 20000;
		p1pll->pll_out_max = 50000;
		p2pll->pll_in_min = 100;
		p2pll->pll_in_max = 1350;
		p2pll->pll_out_min = 20000;
		p2pll->pll_out_max = 50000;
	पूर्ण अन्यथा अणु
		p1pll->pll_in_min = 40;
		p1pll->pll_in_max = 500;
		p1pll->pll_out_min = 12500;
		p1pll->pll_out_max = 35000;
		p2pll->pll_in_min = 40;
		p2pll->pll_in_max = 500;
		p2pll->pll_out_min = 12500;
		p2pll->pll_out_max = 35000;
	पूर्ण
	/* not sure what the max should be in all हालs */
	rdev->घड़ी.max_pixel_घड़ी = 35000;

	spll->reference_freq = mpll->reference_freq = p1pll->reference_freq;
	spll->reference_भाग = mpll->reference_भाग =
		RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) &
			    RADEON_M_SPLL_REF_DIV_MASK;

	val = of_get_property(dp, "ATY,SCLK", शून्य);
	अगर (val && *val)
		rdev->घड़ी.शेष_sclk = (*val) / 10;
	अन्यथा
		rdev->घड़ी.शेष_sclk =
			radeon_legacy_get_engine_घड़ी(rdev);

	val = of_get_property(dp, "ATY,MCLK", शून्य);
	अगर (val && *val)
		rdev->घड़ी.शेष_mclk = (*val) / 10;
	अन्यथा
		rdev->घड़ी.शेष_mclk =
			radeon_legacy_get_memory_घड़ी(rdev);

	DRM_INFO("Using device-tree clock info\n");

	वापस true;
पूर्ण
#अन्यथा
अटल bool radeon_पढ़ो_घड़ीs_OF(काष्ठा drm_device *dev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

व्योम radeon_get_घड़ी_info(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_pll *p1pll = &rdev->घड़ी.p1pll;
	काष्ठा radeon_pll *p2pll = &rdev->घड़ी.p2pll;
	काष्ठा radeon_pll *dcpll = &rdev->घड़ी.dcpll;
	काष्ठा radeon_pll *spll = &rdev->घड़ी.spll;
	काष्ठा radeon_pll *mpll = &rdev->घड़ी.mpll;
	पूर्णांक ret;

	अगर (rdev->is_atom_bios)
		ret = radeon_atom_get_घड़ी_info(dev);
	अन्यथा
		ret = radeon_combios_get_घड़ी_info(dev);
	अगर (!ret)
		ret = radeon_पढ़ो_घड़ीs_OF(dev);

	अगर (ret) अणु
		अगर (p1pll->reference_भाग < 2) अणु
			अगर (!ASIC_IS_AVIVO(rdev)) अणु
				u32 पंचांगp = RREG32_PLL(RADEON_PPLL_REF_DIV);
				अगर (ASIC_IS_R300(rdev))
					p1pll->reference_भाग =
						(पंचांगp & R300_PPLL_REF_DIV_ACC_MASK) >> R300_PPLL_REF_DIV_ACC_SHIFT;
				अन्यथा
					p1pll->reference_भाग = पंचांगp & RADEON_PPLL_REF_DIV_MASK;
				अगर (p1pll->reference_भाग < 2)
					p1pll->reference_भाग = 12;
			पूर्ण अन्यथा
				p1pll->reference_भाग = 12;
		पूर्ण
		अगर (p2pll->reference_भाग < 2)
			p2pll->reference_भाग = 12;
		अगर (rdev->family < CHIP_RS600) अणु
			अगर (spll->reference_भाग < 2)
				spll->reference_भाग =
					RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) &
					RADEON_M_SPLL_REF_DIV_MASK;
		पूर्ण
		अगर (mpll->reference_भाग < 2)
			mpll->reference_भाग = spll->reference_भाग;
	पूर्ण अन्यथा अणु
		अगर (ASIC_IS_AVIVO(rdev)) अणु
			/* TODO FALLBACK */
		पूर्ण अन्यथा अणु
			DRM_INFO("Using generic clock info\n");

			/* may need to be per card */
			rdev->घड़ी.max_pixel_घड़ी = 35000;

			अगर (rdev->flags & RADEON_IS_IGP) अणु
				p1pll->reference_freq = 1432;
				p2pll->reference_freq = 1432;
				spll->reference_freq = 1432;
				mpll->reference_freq = 1432;
			पूर्ण अन्यथा अणु
				p1pll->reference_freq = 2700;
				p2pll->reference_freq = 2700;
				spll->reference_freq = 2700;
				mpll->reference_freq = 2700;
			पूर्ण
			p1pll->reference_भाग =
			    RREG32_PLL(RADEON_PPLL_REF_DIV) & 0x3ff;
			अगर (p1pll->reference_भाग < 2)
				p1pll->reference_भाग = 12;
			p2pll->reference_भाग = p1pll->reference_भाग;

			अगर (rdev->family >= CHIP_R420) अणु
				p1pll->pll_in_min = 100;
				p1pll->pll_in_max = 1350;
				p1pll->pll_out_min = 20000;
				p1pll->pll_out_max = 50000;
				p2pll->pll_in_min = 100;
				p2pll->pll_in_max = 1350;
				p2pll->pll_out_min = 20000;
				p2pll->pll_out_max = 50000;
			पूर्ण अन्यथा अणु
				p1pll->pll_in_min = 40;
				p1pll->pll_in_max = 500;
				p1pll->pll_out_min = 12500;
				p1pll->pll_out_max = 35000;
				p2pll->pll_in_min = 40;
				p2pll->pll_in_max = 500;
				p2pll->pll_out_min = 12500;
				p2pll->pll_out_max = 35000;
			पूर्ण

			spll->reference_भाग =
			    RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) &
			    RADEON_M_SPLL_REF_DIV_MASK;
			mpll->reference_भाग = spll->reference_भाग;
			rdev->घड़ी.शेष_sclk =
			    radeon_legacy_get_engine_घड़ी(rdev);
			rdev->घड़ी.शेष_mclk =
			    radeon_legacy_get_memory_घड़ी(rdev);
		पूर्ण
	पूर्ण

	/* pixel घड़ीs */
	अगर (ASIC_IS_AVIVO(rdev)) अणु
		p1pll->min_post_भाग = 2;
		p1pll->max_post_भाग = 0x7f;
		p1pll->min_frac_feedback_भाग = 0;
		p1pll->max_frac_feedback_भाग = 9;
		p2pll->min_post_भाग = 2;
		p2pll->max_post_भाग = 0x7f;
		p2pll->min_frac_feedback_भाग = 0;
		p2pll->max_frac_feedback_भाग = 9;
	पूर्ण अन्यथा अणु
		p1pll->min_post_भाग = 1;
		p1pll->max_post_भाग = 16;
		p1pll->min_frac_feedback_भाग = 0;
		p1pll->max_frac_feedback_भाग = 0;
		p2pll->min_post_भाग = 1;
		p2pll->max_post_भाग = 12;
		p2pll->min_frac_feedback_भाग = 0;
		p2pll->max_frac_feedback_भाग = 0;
	पूर्ण

	/* dcpll is DCE4 only */
	dcpll->min_post_भाग = 2;
	dcpll->max_post_भाग = 0x7f;
	dcpll->min_frac_feedback_भाग = 0;
	dcpll->max_frac_feedback_भाग = 9;
	dcpll->min_ref_भाग = 2;
	dcpll->max_ref_भाग = 0x3ff;
	dcpll->min_feedback_भाग = 4;
	dcpll->max_feedback_भाग = 0xfff;
	dcpll->best_vco = 0;

	p1pll->min_ref_भाग = 2;
	p1pll->max_ref_भाग = 0x3ff;
	p1pll->min_feedback_भाग = 4;
	p1pll->max_feedback_भाग = 0x7ff;
	p1pll->best_vco = 0;

	p2pll->min_ref_भाग = 2;
	p2pll->max_ref_भाग = 0x3ff;
	p2pll->min_feedback_भाग = 4;
	p2pll->max_feedback_भाग = 0x7ff;
	p2pll->best_vco = 0;

	/* प्रणाली घड़ी */
	spll->min_post_भाग = 1;
	spll->max_post_भाग = 1;
	spll->min_ref_भाग = 2;
	spll->max_ref_भाग = 0xff;
	spll->min_feedback_भाग = 4;
	spll->max_feedback_भाग = 0xff;
	spll->best_vco = 0;

	/* memory घड़ी */
	mpll->min_post_भाग = 1;
	mpll->max_post_भाग = 1;
	mpll->min_ref_भाग = 2;
	mpll->max_ref_भाग = 0xff;
	mpll->min_feedback_भाग = 4;
	mpll->max_feedback_भाग = 0xff;
	mpll->best_vco = 0;

	अगर (!rdev->घड़ी.शेष_sclk)
		rdev->घड़ी.शेष_sclk = radeon_get_engine_घड़ी(rdev);
	अगर ((!rdev->घड़ी.शेष_mclk) && rdev->asic->pm.get_memory_घड़ी)
		rdev->घड़ी.शेष_mclk = radeon_get_memory_घड़ी(rdev);

	rdev->pm.current_sclk = rdev->घड़ी.शेष_sclk;
	rdev->pm.current_mclk = rdev->घड़ी.शेष_mclk;

पूर्ण

/* 10 khz */
अटल uपूर्णांक32_t calc_eng_mem_घड़ी(काष्ठा radeon_device *rdev,
				   uपूर्णांक32_t req_घड़ी,
				   पूर्णांक *fb_भाग, पूर्णांक *post_भाग)
अणु
	काष्ठा radeon_pll *spll = &rdev->घड़ी.spll;
	पूर्णांक ref_भाग = spll->reference_भाग;

	अगर (!ref_भाग)
		ref_भाग =
		    RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV) &
		    RADEON_M_SPLL_REF_DIV_MASK;

	अगर (req_घड़ी < 15000) अणु
		*post_भाग = 8;
		req_घड़ी *= 8;
	पूर्ण अन्यथा अगर (req_घड़ी < 30000) अणु
		*post_भाग = 4;
		req_घड़ी *= 4;
	पूर्ण अन्यथा अगर (req_घड़ी < 60000) अणु
		*post_भाग = 2;
		req_घड़ी *= 2;
	पूर्ण अन्यथा
		*post_भाग = 1;

	req_घड़ी *= ref_भाग;
	req_घड़ी += spll->reference_freq;
	req_घड़ी /= (2 * spll->reference_freq);

	*fb_भाग = req_घड़ी & 0xff;

	req_घड़ी = (req_घड़ी & 0xffff) << 1;
	req_घड़ी *= spll->reference_freq;
	req_घड़ी /= ref_भाग;
	req_घड़ी /= *post_भाग;

	वापस req_घड़ी;
पूर्ण

/* 10 khz */
व्योम radeon_legacy_set_engine_घड़ी(काष्ठा radeon_device *rdev,
				    uपूर्णांक32_t eng_घड़ी)
अणु
	uपूर्णांक32_t पंचांगp;
	पूर्णांक fb_भाग, post_भाग;

	/* XXX: रुको क्रम idle */

	eng_घड़ी = calc_eng_mem_घड़ी(rdev, eng_घड़ी, &fb_भाग, &post_भाग);

	पंचांगp = RREG32_PLL(RADEON_CLK_PIN_CNTL);
	पंचांगp &= ~RADEON_DONT_USE_XTALIN;
	WREG32_PLL(RADEON_CLK_PIN_CNTL, पंचांगp);

	पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
	पंचांगp &= ~RADEON_SCLK_SRC_SEL_MASK;
	WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

	udelay(10);

	पंचांगp = RREG32_PLL(RADEON_SPLL_CNTL);
	पंचांगp |= RADEON_SPLL_SLEEP;
	WREG32_PLL(RADEON_SPLL_CNTL, पंचांगp);

	udelay(2);

	पंचांगp = RREG32_PLL(RADEON_SPLL_CNTL);
	पंचांगp |= RADEON_SPLL_RESET;
	WREG32_PLL(RADEON_SPLL_CNTL, पंचांगp);

	udelay(200);

	पंचांगp = RREG32_PLL(RADEON_M_SPLL_REF_FB_DIV);
	पंचांगp &= ~(RADEON_SPLL_FB_DIV_MASK << RADEON_SPLL_FB_DIV_SHIFT);
	पंचांगp |= (fb_भाग & RADEON_SPLL_FB_DIV_MASK) << RADEON_SPLL_FB_DIV_SHIFT;
	WREG32_PLL(RADEON_M_SPLL_REF_FB_DIV, पंचांगp);

	/* XXX: verअगरy on dअगरferent asics */
	पंचांगp = RREG32_PLL(RADEON_SPLL_CNTL);
	पंचांगp &= ~RADEON_SPLL_PVG_MASK;
	अगर ((eng_घड़ी * post_भाग) >= 90000)
		पंचांगp |= (0x7 << RADEON_SPLL_PVG_SHIFT);
	अन्यथा
		पंचांगp |= (0x4 << RADEON_SPLL_PVG_SHIFT);
	WREG32_PLL(RADEON_SPLL_CNTL, पंचांगp);

	पंचांगp = RREG32_PLL(RADEON_SPLL_CNTL);
	पंचांगp &= ~RADEON_SPLL_SLEEP;
	WREG32_PLL(RADEON_SPLL_CNTL, पंचांगp);

	udelay(2);

	पंचांगp = RREG32_PLL(RADEON_SPLL_CNTL);
	पंचांगp &= ~RADEON_SPLL_RESET;
	WREG32_PLL(RADEON_SPLL_CNTL, पंचांगp);

	udelay(200);

	पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
	पंचांगp &= ~RADEON_SCLK_SRC_SEL_MASK;
	चयन (post_भाग) अणु
	हाल 1:
	शेष:
		पंचांगp |= 1;
		अवरोध;
	हाल 2:
		पंचांगp |= 2;
		अवरोध;
	हाल 4:
		पंचांगp |= 3;
		अवरोध;
	हाल 8:
		पंचांगp |= 4;
		अवरोध;
	पूर्ण
	WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

	udelay(20);

	पंचांगp = RREG32_PLL(RADEON_CLK_PIN_CNTL);
	पंचांगp |= RADEON_DONT_USE_XTALIN;
	WREG32_PLL(RADEON_CLK_PIN_CNTL, पंचांगp);

	udelay(10);
पूर्ण

व्योम radeon_legacy_set_घड़ी_gating(काष्ठा radeon_device *rdev, पूर्णांक enable)
अणु
	uपूर्णांक32_t पंचांगp;

	अगर (enable) अणु
		अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
			पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
			अगर ((RREG32(RADEON_CONFIG_CNTL) &
			     RADEON_CFG_ATI_REV_ID_MASK) >
			    RADEON_CFG_ATI_REV_A13) अणु
				पंचांगp &=
				    ~(RADEON_SCLK_FORCE_CP |
				      RADEON_SCLK_FORCE_RB);
			पूर्ण
			पंचांगp &=
			    ~(RADEON_SCLK_FORCE_HDP | RADEON_SCLK_FORCE_DISP1 |
			      RADEON_SCLK_FORCE_TOP | RADEON_SCLK_FORCE_SE |
			      RADEON_SCLK_FORCE_IDCT | RADEON_SCLK_FORCE_RE |
			      RADEON_SCLK_FORCE_PB | RADEON_SCLK_FORCE_TAM |
			      RADEON_SCLK_FORCE_TDM);
			WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);
		पूर्ण अन्यथा अगर (ASIC_IS_R300(rdev)) अणु
			अगर ((rdev->family == CHIP_RS400) ||
			    (rdev->family == CHIP_RS480)) अणु
				पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
				पंचांगp &=
				    ~(RADEON_SCLK_FORCE_DISP2 |
				      RADEON_SCLK_FORCE_CP |
				      RADEON_SCLK_FORCE_HDP |
				      RADEON_SCLK_FORCE_DISP1 |
				      RADEON_SCLK_FORCE_TOP |
				      RADEON_SCLK_FORCE_E2 | R300_SCLK_FORCE_VAP
				      | RADEON_SCLK_FORCE_IDCT |
				      RADEON_SCLK_FORCE_VIP | R300_SCLK_FORCE_SR
				      | R300_SCLK_FORCE_PX | R300_SCLK_FORCE_TX
				      | R300_SCLK_FORCE_US |
				      RADEON_SCLK_FORCE_TV_SCLK |
				      R300_SCLK_FORCE_SU |
				      RADEON_SCLK_FORCE_OV0);
				पंचांगp |= RADEON_DYN_STOP_LAT_MASK;
				पंचांगp |=
				    RADEON_SCLK_FORCE_TOP |
				    RADEON_SCLK_FORCE_VIP;
				WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_SCLK_MORE_CNTL);
				पंचांगp &= ~RADEON_SCLK_MORE_FORCEON;
				पंचांगp |= RADEON_SCLK_MORE_MAX_DYN_STOP_LAT;
				WREG32_PLL(RADEON_SCLK_MORE_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
				पंचांगp |= (RADEON_PIXCLK_ALWAYS_ONb |
					RADEON_PIXCLK_DAC_ALWAYS_ONb);
				WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_PIXCLKS_CNTL);
				पंचांगp |= (RADEON_PIX2CLK_ALWAYS_ONb |
					RADEON_PIX2CLK_DAC_ALWAYS_ONb |
					RADEON_DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb |
					R300_DVOCLK_ALWAYS_ONb |
					RADEON_PIXCLK_BLEND_ALWAYS_ONb |
					RADEON_PIXCLK_GV_ALWAYS_ONb |
					R300_PIXCLK_DVO_ALWAYS_ONb |
					RADEON_PIXCLK_LVDS_ALWAYS_ONb |
					RADEON_PIXCLK_TMDS_ALWAYS_ONb |
					R300_PIXCLK_TRANS_ALWAYS_ONb |
					R300_PIXCLK_TVO_ALWAYS_ONb |
					R300_P2G2CLK_ALWAYS_ONb |
					R300_P2G2CLK_DAC_ALWAYS_ONb);
				WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);
			पूर्ण अन्यथा अगर (rdev->family >= CHIP_RV350) अणु
				पंचांगp = RREG32_PLL(R300_SCLK_CNTL2);
				पंचांगp &= ~(R300_SCLK_FORCE_TCL |
					 R300_SCLK_FORCE_GA |
					 R300_SCLK_FORCE_CBA);
				पंचांगp |= (R300_SCLK_TCL_MAX_DYN_STOP_LAT |
					R300_SCLK_GA_MAX_DYN_STOP_LAT |
					R300_SCLK_CBA_MAX_DYN_STOP_LAT);
				WREG32_PLL(R300_SCLK_CNTL2, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
				पंचांगp &=
				    ~(RADEON_SCLK_FORCE_DISP2 |
				      RADEON_SCLK_FORCE_CP |
				      RADEON_SCLK_FORCE_HDP |
				      RADEON_SCLK_FORCE_DISP1 |
				      RADEON_SCLK_FORCE_TOP |
				      RADEON_SCLK_FORCE_E2 | R300_SCLK_FORCE_VAP
				      | RADEON_SCLK_FORCE_IDCT |
				      RADEON_SCLK_FORCE_VIP | R300_SCLK_FORCE_SR
				      | R300_SCLK_FORCE_PX | R300_SCLK_FORCE_TX
				      | R300_SCLK_FORCE_US |
				      RADEON_SCLK_FORCE_TV_SCLK |
				      R300_SCLK_FORCE_SU |
				      RADEON_SCLK_FORCE_OV0);
				पंचांगp |= RADEON_DYN_STOP_LAT_MASK;
				WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_SCLK_MORE_CNTL);
				पंचांगp &= ~RADEON_SCLK_MORE_FORCEON;
				पंचांगp |= RADEON_SCLK_MORE_MAX_DYN_STOP_LAT;
				WREG32_PLL(RADEON_SCLK_MORE_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
				पंचांगp |= (RADEON_PIXCLK_ALWAYS_ONb |
					RADEON_PIXCLK_DAC_ALWAYS_ONb);
				WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_PIXCLKS_CNTL);
				पंचांगp |= (RADEON_PIX2CLK_ALWAYS_ONb |
					RADEON_PIX2CLK_DAC_ALWAYS_ONb |
					RADEON_DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb |
					R300_DVOCLK_ALWAYS_ONb |
					RADEON_PIXCLK_BLEND_ALWAYS_ONb |
					RADEON_PIXCLK_GV_ALWAYS_ONb |
					R300_PIXCLK_DVO_ALWAYS_ONb |
					RADEON_PIXCLK_LVDS_ALWAYS_ONb |
					RADEON_PIXCLK_TMDS_ALWAYS_ONb |
					R300_PIXCLK_TRANS_ALWAYS_ONb |
					R300_PIXCLK_TVO_ALWAYS_ONb |
					R300_P2G2CLK_ALWAYS_ONb |
					R300_P2G2CLK_DAC_ALWAYS_ONb);
				WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_MCLK_MISC);
				पंचांगp |= (RADEON_MC_MCLK_DYN_ENABLE |
					RADEON_IO_MCLK_DYN_ENABLE);
				WREG32_PLL(RADEON_MCLK_MISC, पंचांगp);

				पंचांगp = RREG32_PLL(RADEON_MCLK_CNTL);
				पंचांगp |= (RADEON_FORCEON_MCLKA |
					RADEON_FORCEON_MCLKB);

				पंचांगp &= ~(RADEON_FORCEON_YCLKA |
					 RADEON_FORCEON_YCLKB |
					 RADEON_FORCEON_MC);

				/* Some releases of vbios have set DISABLE_MC_MCLKA
				   and DISABLE_MC_MCLKB bits in the vbios table.  Setting these
				   bits will cause H/W hang when पढ़ोing video memory with dynamic घड़ीing
				   enabled. */
				अगर ((पंचांगp & R300_DISABLE_MC_MCLKA) &&
				    (पंचांगp & R300_DISABLE_MC_MCLKB)) अणु
					/* If both bits are set, then check the active channels */
					पंचांगp = RREG32_PLL(RADEON_MCLK_CNTL);
					अगर (rdev->mc.vram_width == 64) अणु
						अगर (RREG32(RADEON_MEM_CNTL) &
						    R300_MEM_USE_CD_CH_ONLY)
							पंचांगp &=
							    ~R300_DISABLE_MC_MCLKB;
						अन्यथा
							पंचांगp &=
							    ~R300_DISABLE_MC_MCLKA;
					पूर्ण अन्यथा अणु
						पंचांगp &= ~(R300_DISABLE_MC_MCLKA |
							 R300_DISABLE_MC_MCLKB);
					पूर्ण
				पूर्ण

				WREG32_PLL(RADEON_MCLK_CNTL, पंचांगp);
			पूर्ण अन्यथा अणु
				पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
				पंचांगp &= ~(R300_SCLK_FORCE_VAP);
				पंचांगp |= RADEON_SCLK_FORCE_CP;
				WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);
				mdelay(15);

				पंचांगp = RREG32_PLL(R300_SCLK_CNTL2);
				पंचांगp &= ~(R300_SCLK_FORCE_TCL |
					 R300_SCLK_FORCE_GA |
					 R300_SCLK_FORCE_CBA);
				WREG32_PLL(R300_SCLK_CNTL2, पंचांगp);
			पूर्ण
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32_PLL(RADEON_CLK_PWRMGT_CNTL);

			पंचांगp &= ~(RADEON_ACTIVE_HILO_LAT_MASK |
				 RADEON_DISP_DYN_STOP_LAT_MASK |
				 RADEON_DYN_STOP_MODE_MASK);

			पंचांगp |= (RADEON_ENGIN_DYNCLK_MODE |
				(0x01 << RADEON_ACTIVE_HILO_LAT_SHIFT));
			WREG32_PLL(RADEON_CLK_PWRMGT_CNTL, पंचांगp);
			mdelay(15);

			पंचांगp = RREG32_PLL(RADEON_CLK_PIN_CNTL);
			पंचांगp |= RADEON_SCLK_DYN_START_CNTL;
			WREG32_PLL(RADEON_CLK_PIN_CNTL, पंचांगp);
			mdelay(15);

			/* When DRI is enabled, setting DYN_STOP_LAT to zero can cause some R200
			   to lockup अक्रमomly, leave them as set by BIOS.
			 */
			पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
			/*पंचांगp &= RADEON_SCLK_SRC_SEL_MASK; */
			पंचांगp &= ~RADEON_SCLK_FORCEON_MASK;

			/*RAGE_6::A11 A12 A12N1 A13, RV250::A11 A12, R300 */
			अगर (((rdev->family == CHIP_RV250) &&
			     ((RREG32(RADEON_CONFIG_CNTL) &
			       RADEON_CFG_ATI_REV_ID_MASK) <
			      RADEON_CFG_ATI_REV_A13))
			    || ((rdev->family == CHIP_RV100)
				&&
				((RREG32(RADEON_CONFIG_CNTL) &
				  RADEON_CFG_ATI_REV_ID_MASK) <=
				 RADEON_CFG_ATI_REV_A13))) अणु
				पंचांगp |= RADEON_SCLK_FORCE_CP;
				पंचांगp |= RADEON_SCLK_FORCE_VIP;
			पूर्ण

			WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

			अगर ((rdev->family == CHIP_RV200) ||
			    (rdev->family == CHIP_RV250) ||
			    (rdev->family == CHIP_RV280)) अणु
				पंचांगp = RREG32_PLL(RADEON_SCLK_MORE_CNTL);
				पंचांगp &= ~RADEON_SCLK_MORE_FORCEON;

				/* RV200::A11 A12 RV250::A11 A12 */
				अगर (((rdev->family == CHIP_RV200) ||
				     (rdev->family == CHIP_RV250)) &&
				    ((RREG32(RADEON_CONFIG_CNTL) &
				      RADEON_CFG_ATI_REV_ID_MASK) <
				     RADEON_CFG_ATI_REV_A13)) अणु
					पंचांगp |= RADEON_SCLK_MORE_FORCEON;
				पूर्ण
				WREG32_PLL(RADEON_SCLK_MORE_CNTL, पंचांगp);
				mdelay(15);
			पूर्ण

			/* RV200::A11 A12, RV250::A11 A12 */
			अगर (((rdev->family == CHIP_RV200) ||
			     (rdev->family == CHIP_RV250)) &&
			    ((RREG32(RADEON_CONFIG_CNTL) &
			      RADEON_CFG_ATI_REV_ID_MASK) <
			     RADEON_CFG_ATI_REV_A13)) अणु
				पंचांगp = RREG32_PLL(RADEON_PLL_PWRMGT_CNTL);
				पंचांगp |= RADEON_TCL_BYPASS_DISABLE;
				WREG32_PLL(RADEON_PLL_PWRMGT_CNTL, पंचांगp);
			पूर्ण
			mdelay(15);

			/*enable dynamic mode क्रम display घड़ीs (PIXCLK and PIX2CLK) */
			पंचांगp = RREG32_PLL(RADEON_PIXCLKS_CNTL);
			पंचांगp |= (RADEON_PIX2CLK_ALWAYS_ONb |
				RADEON_PIX2CLK_DAC_ALWAYS_ONb |
				RADEON_PIXCLK_BLEND_ALWAYS_ONb |
				RADEON_PIXCLK_GV_ALWAYS_ONb |
				RADEON_PIXCLK_DIG_TMDS_ALWAYS_ONb |
				RADEON_PIXCLK_LVDS_ALWAYS_ONb |
				RADEON_PIXCLK_TMDS_ALWAYS_ONb);

			WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);
			mdelay(15);

			पंचांगp = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
			पंचांगp |= (RADEON_PIXCLK_ALWAYS_ONb |
				RADEON_PIXCLK_DAC_ALWAYS_ONb);

			WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);
			mdelay(15);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Turn everything OFF (ForceON to everything) */
		अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
			पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
			पंचांगp |= (RADEON_SCLK_FORCE_CP | RADEON_SCLK_FORCE_HDP |
				RADEON_SCLK_FORCE_DISP1 | RADEON_SCLK_FORCE_TOP
				| RADEON_SCLK_FORCE_E2 | RADEON_SCLK_FORCE_SE |
				RADEON_SCLK_FORCE_IDCT | RADEON_SCLK_FORCE_VIP |
				RADEON_SCLK_FORCE_RE | RADEON_SCLK_FORCE_PB |
				RADEON_SCLK_FORCE_TAM | RADEON_SCLK_FORCE_TDM |
				RADEON_SCLK_FORCE_RB);
			WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);
		पूर्ण अन्यथा अगर ((rdev->family == CHIP_RS400) ||
			   (rdev->family == CHIP_RS480)) अणु
			पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
			पंचांगp |= (RADEON_SCLK_FORCE_DISP2 | RADEON_SCLK_FORCE_CP |
				RADEON_SCLK_FORCE_HDP | RADEON_SCLK_FORCE_DISP1
				| RADEON_SCLK_FORCE_TOP | RADEON_SCLK_FORCE_E2 |
				R300_SCLK_FORCE_VAP | RADEON_SCLK_FORCE_IDCT |
				RADEON_SCLK_FORCE_VIP | R300_SCLK_FORCE_SR |
				R300_SCLK_FORCE_PX | R300_SCLK_FORCE_TX |
				R300_SCLK_FORCE_US | RADEON_SCLK_FORCE_TV_SCLK |
				R300_SCLK_FORCE_SU | RADEON_SCLK_FORCE_OV0);
			WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_SCLK_MORE_CNTL);
			पंचांगp |= RADEON_SCLK_MORE_FORCEON;
			WREG32_PLL(RADEON_SCLK_MORE_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
			पंचांगp &= ~(RADEON_PIXCLK_ALWAYS_ONb |
				 RADEON_PIXCLK_DAC_ALWAYS_ONb |
				 R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF);
			WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_PIXCLKS_CNTL);
			पंचांगp &= ~(RADEON_PIX2CLK_ALWAYS_ONb |
				 RADEON_PIX2CLK_DAC_ALWAYS_ONb |
				 RADEON_DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb |
				 R300_DVOCLK_ALWAYS_ONb |
				 RADEON_PIXCLK_BLEND_ALWAYS_ONb |
				 RADEON_PIXCLK_GV_ALWAYS_ONb |
				 R300_PIXCLK_DVO_ALWAYS_ONb |
				 RADEON_PIXCLK_LVDS_ALWAYS_ONb |
				 RADEON_PIXCLK_TMDS_ALWAYS_ONb |
				 R300_PIXCLK_TRANS_ALWAYS_ONb |
				 R300_PIXCLK_TVO_ALWAYS_ONb |
				 R300_P2G2CLK_ALWAYS_ONb |
				 R300_P2G2CLK_DAC_ALWAYS_ONb |
				 R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF);
			WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);
		पूर्ण अन्यथा अगर (rdev->family >= CHIP_RV350) अणु
			/* क्रम RV350/M10, no delays are required. */
			पंचांगp = RREG32_PLL(R300_SCLK_CNTL2);
			पंचांगp |= (R300_SCLK_FORCE_TCL |
				R300_SCLK_FORCE_GA | R300_SCLK_FORCE_CBA);
			WREG32_PLL(R300_SCLK_CNTL2, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
			पंचांगp |= (RADEON_SCLK_FORCE_DISP2 | RADEON_SCLK_FORCE_CP |
				RADEON_SCLK_FORCE_HDP | RADEON_SCLK_FORCE_DISP1
				| RADEON_SCLK_FORCE_TOP | RADEON_SCLK_FORCE_E2 |
				R300_SCLK_FORCE_VAP | RADEON_SCLK_FORCE_IDCT |
				RADEON_SCLK_FORCE_VIP | R300_SCLK_FORCE_SR |
				R300_SCLK_FORCE_PX | R300_SCLK_FORCE_TX |
				R300_SCLK_FORCE_US | RADEON_SCLK_FORCE_TV_SCLK |
				R300_SCLK_FORCE_SU | RADEON_SCLK_FORCE_OV0);
			WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_SCLK_MORE_CNTL);
			पंचांगp |= RADEON_SCLK_MORE_FORCEON;
			WREG32_PLL(RADEON_SCLK_MORE_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_MCLK_CNTL);
			पंचांगp |= (RADEON_FORCEON_MCLKA |
				RADEON_FORCEON_MCLKB |
				RADEON_FORCEON_YCLKA |
				RADEON_FORCEON_YCLKB | RADEON_FORCEON_MC);
			WREG32_PLL(RADEON_MCLK_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
			पंचांगp &= ~(RADEON_PIXCLK_ALWAYS_ONb |
				 RADEON_PIXCLK_DAC_ALWAYS_ONb |
				 R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF);
			WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);

			पंचांगp = RREG32_PLL(RADEON_PIXCLKS_CNTL);
			पंचांगp &= ~(RADEON_PIX2CLK_ALWAYS_ONb |
				 RADEON_PIX2CLK_DAC_ALWAYS_ONb |
				 RADEON_DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb |
				 R300_DVOCLK_ALWAYS_ONb |
				 RADEON_PIXCLK_BLEND_ALWAYS_ONb |
				 RADEON_PIXCLK_GV_ALWAYS_ONb |
				 R300_PIXCLK_DVO_ALWAYS_ONb |
				 RADEON_PIXCLK_LVDS_ALWAYS_ONb |
				 RADEON_PIXCLK_TMDS_ALWAYS_ONb |
				 R300_PIXCLK_TRANS_ALWAYS_ONb |
				 R300_PIXCLK_TVO_ALWAYS_ONb |
				 R300_P2G2CLK_ALWAYS_ONb |
				 R300_P2G2CLK_DAC_ALWAYS_ONb |
				 R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF);
			WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = RREG32_PLL(RADEON_SCLK_CNTL);
			पंचांगp |= (RADEON_SCLK_FORCE_CP | RADEON_SCLK_FORCE_E2);
			पंचांगp |= RADEON_SCLK_FORCE_SE;

			अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
				पंचांगp |= (RADEON_SCLK_FORCE_RB |
					RADEON_SCLK_FORCE_TDM |
					RADEON_SCLK_FORCE_TAM |
					RADEON_SCLK_FORCE_PB |
					RADEON_SCLK_FORCE_RE |
					RADEON_SCLK_FORCE_VIP |
					RADEON_SCLK_FORCE_IDCT |
					RADEON_SCLK_FORCE_TOP |
					RADEON_SCLK_FORCE_DISP1 |
					RADEON_SCLK_FORCE_DISP2 |
					RADEON_SCLK_FORCE_HDP);
			पूर्ण अन्यथा अगर ((rdev->family == CHIP_R300) ||
				   (rdev->family == CHIP_R350)) अणु
				पंचांगp |= (RADEON_SCLK_FORCE_HDP |
					RADEON_SCLK_FORCE_DISP1 |
					RADEON_SCLK_FORCE_DISP2 |
					RADEON_SCLK_FORCE_TOP |
					RADEON_SCLK_FORCE_IDCT |
					RADEON_SCLK_FORCE_VIP);
			पूर्ण
			WREG32_PLL(RADEON_SCLK_CNTL, पंचांगp);

			mdelay(16);

			अगर ((rdev->family == CHIP_R300) ||
			    (rdev->family == CHIP_R350)) अणु
				पंचांगp = RREG32_PLL(R300_SCLK_CNTL2);
				पंचांगp |= (R300_SCLK_FORCE_TCL |
					R300_SCLK_FORCE_GA |
					R300_SCLK_FORCE_CBA);
				WREG32_PLL(R300_SCLK_CNTL2, पंचांगp);
				mdelay(16);
			पूर्ण

			अगर (rdev->flags & RADEON_IS_IGP) अणु
				पंचांगp = RREG32_PLL(RADEON_MCLK_CNTL);
				पंचांगp &= ~(RADEON_FORCEON_MCLKA |
					 RADEON_FORCEON_YCLKA);
				WREG32_PLL(RADEON_MCLK_CNTL, पंचांगp);
				mdelay(16);
			पूर्ण

			अगर ((rdev->family == CHIP_RV200) ||
			    (rdev->family == CHIP_RV250) ||
			    (rdev->family == CHIP_RV280)) अणु
				पंचांगp = RREG32_PLL(RADEON_SCLK_MORE_CNTL);
				पंचांगp |= RADEON_SCLK_MORE_FORCEON;
				WREG32_PLL(RADEON_SCLK_MORE_CNTL, पंचांगp);
				mdelay(16);
			पूर्ण

			पंचांगp = RREG32_PLL(RADEON_PIXCLKS_CNTL);
			पंचांगp &= ~(RADEON_PIX2CLK_ALWAYS_ONb |
				 RADEON_PIX2CLK_DAC_ALWAYS_ONb |
				 RADEON_PIXCLK_BLEND_ALWAYS_ONb |
				 RADEON_PIXCLK_GV_ALWAYS_ONb |
				 RADEON_PIXCLK_DIG_TMDS_ALWAYS_ONb |
				 RADEON_PIXCLK_LVDS_ALWAYS_ONb |
				 RADEON_PIXCLK_TMDS_ALWAYS_ONb);

			WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);
			mdelay(16);

			पंचांगp = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
			पंचांगp &= ~(RADEON_PIXCLK_ALWAYS_ONb |
				 RADEON_PIXCLK_DAC_ALWAYS_ONb);
			WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

