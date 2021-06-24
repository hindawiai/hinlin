<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2011 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>

#समावेश <drm/drm_crtc.h>

#समावेश "cdv_device.h"
#समावेश "framebuffer.h"
#समावेश "gma_display.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

अटल bool cdv_पूर्णांकel_find_dp_pll(स्थिर काष्ठा gma_limit_t *limit,
				  काष्ठा drm_crtc *crtc, पूर्णांक target,
				  पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *best_घड़ी);


#घोषणा CDV_LIMIT_SINGLE_LVDS_96	0
#घोषणा CDV_LIMIT_SINGLE_LVDS_100	1
#घोषणा CDV_LIMIT_DAC_HDMI_27		2
#घोषणा CDV_LIMIT_DAC_HDMI_96		3
#घोषणा CDV_LIMIT_DP_27			4
#घोषणा CDV_LIMIT_DP_100		5

अटल स्थिर काष्ठा gma_limit_t cdv_पूर्णांकel_limits[] = अणु
	अणु			/* CDV_SINGLE_LVDS_96MHz */
	 .करोt = अणु.min = 20000, .max = 115500पूर्ण,
	 .vco = अणु.min = 1800000, .max = 3600000पूर्ण,
	 .n = अणु.min = 2, .max = 6पूर्ण,
	 .m = अणु.min = 60, .max = 160पूर्ण,
	 .m1 = अणु.min = 0, .max = 0पूर्ण,
	 .m2 = अणु.min = 58, .max = 158पूर्ण,
	 .p = अणु.min = 28, .max = 140पूर्ण,
	 .p1 = अणु.min = 2, .max = 10पूर्ण,
	 .p2 = अणु.करोt_limit = 200000, .p2_slow = 14, .p2_fast = 14पूर्ण,
	 .find_pll = gma_find_best_pll,
	 पूर्ण,
	अणु			/* CDV_SINGLE_LVDS_100MHz */
	 .करोt = अणु.min = 20000, .max = 115500पूर्ण,
	 .vco = अणु.min = 1800000, .max = 3600000पूर्ण,
	 .n = अणु.min = 2, .max = 6पूर्ण,
	 .m = अणु.min = 60, .max = 160पूर्ण,
	 .m1 = अणु.min = 0, .max = 0पूर्ण,
	 .m2 = अणु.min = 58, .max = 158पूर्ण,
	 .p = अणु.min = 28, .max = 140पूर्ण,
	 .p1 = अणु.min = 2, .max = 10पूर्ण,
	 /* The single-channel range is 25-112Mhz, and dual-channel
	  * is 80-224Mhz.  Prefer single channel as much as possible.
	  */
	 .p2 = अणु.करोt_limit = 200000, .p2_slow = 14, .p2_fast = 14पूर्ण,
	 .find_pll = gma_find_best_pll,
	 पूर्ण,
	अणु			/* CDV_DAC_HDMI_27MHz */
	 .करोt = अणु.min = 20000, .max = 400000पूर्ण,
	 .vco = अणु.min = 1809000, .max = 3564000पूर्ण,
	 .n = अणु.min = 1, .max = 1पूर्ण,
	 .m = अणु.min = 67, .max = 132पूर्ण,
	 .m1 = अणु.min = 0, .max = 0पूर्ण,
	 .m2 = अणु.min = 65, .max = 130पूर्ण,
	 .p = अणु.min = 5, .max = 90पूर्ण,
	 .p1 = अणु.min = 1, .max = 9पूर्ण,
	 .p2 = अणु.करोt_limit = 225000, .p2_slow = 10, .p2_fast = 5पूर्ण,
	 .find_pll = gma_find_best_pll,
	 पूर्ण,
	अणु			/* CDV_DAC_HDMI_96MHz */
	 .करोt = अणु.min = 20000, .max = 400000पूर्ण,
	 .vco = अणु.min = 1800000, .max = 3600000पूर्ण,
	 .n = अणु.min = 2, .max = 6पूर्ण,
	 .m = अणु.min = 60, .max = 160पूर्ण,
	 .m1 = अणु.min = 0, .max = 0पूर्ण,
	 .m2 = अणु.min = 58, .max = 158पूर्ण,
	 .p = अणु.min = 5, .max = 100पूर्ण,
	 .p1 = अणु.min = 1, .max = 10पूर्ण,
	 .p2 = अणु.करोt_limit = 225000, .p2_slow = 10, .p2_fast = 5पूर्ण,
	 .find_pll = gma_find_best_pll,
	 पूर्ण,
	अणु			/* CDV_DP_27MHz */
	 .करोt = अणु.min = 160000, .max = 272000पूर्ण,
	 .vco = अणु.min = 1809000, .max = 3564000पूर्ण,
	 .n = अणु.min = 1, .max = 1पूर्ण,
	 .m = अणु.min = 67, .max = 132पूर्ण,
	 .m1 = अणु.min = 0, .max = 0पूर्ण,
	 .m2 = अणु.min = 65, .max = 130पूर्ण,
	 .p = अणु.min = 5, .max = 90पूर्ण,
	 .p1 = अणु.min = 1, .max = 9पूर्ण,
	 .p2 = अणु.करोt_limit = 225000, .p2_slow = 10, .p2_fast = 10पूर्ण,
	 .find_pll = cdv_पूर्णांकel_find_dp_pll,
	 पूर्ण,
	अणु			/* CDV_DP_100MHz */
	 .करोt = अणु.min = 160000, .max = 272000पूर्ण,
	 .vco = अणु.min = 1800000, .max = 3600000पूर्ण,
	 .n = अणु.min = 2, .max = 6पूर्ण,
	 .m = अणु.min = 60, .max = 164पूर्ण,
	 .m1 = अणु.min = 0, .max = 0पूर्ण,
	 .m2 = अणु.min = 58, .max = 162पूर्ण,
	 .p = अणु.min = 5, .max = 100पूर्ण,
	 .p1 = अणु.min = 1, .max = 10पूर्ण,
	 .p2 = अणु.करोt_limit = 225000, .p2_slow = 10, .p2_fast = 10पूर्ण,
	 .find_pll = cdv_पूर्णांकel_find_dp_pll,
	पूर्ण
पूर्ण;

#घोषणा _रुको_क्रम(COND, MS, W) (अणु \
	अचिन्हित दीर्घ समयout__ = jअगरfies + msecs_to_jअगरfies(MS);	\
	पूर्णांक ret__ = 0;							\
	जबतक (!(COND)) अणु						\
		अगर (समय_after(jअगरfies, समयout__)) अणु			\
			ret__ = -ETIMEDOUT;				\
			अवरोध;						\
		पूर्ण							\
		अगर (W && !in_dbg_master())				\
			msleep(W);					\
	पूर्ण								\
	ret__;								\
पूर्ण)

#घोषणा रुको_क्रम(COND, MS) _रुको_क्रम(COND, MS, 1)


पूर्णांक cdv_sb_पढ़ो(काष्ठा drm_device *dev, u32 reg, u32 *val)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम((REG_READ(SB_PCKT) & SB_BUSY) == 0, 1000);
	अगर (ret) अणु
		DRM_ERROR("timeout waiting for SB to idle before read\n");
		वापस ret;
	पूर्ण

	REG_WRITE(SB_ADDR, reg);
	REG_WRITE(SB_PCKT,
		   SET_FIELD(SB_OPCODE_READ, SB_OPCODE) |
		   SET_FIELD(SB_DEST_DPLL, SB_DEST) |
		   SET_FIELD(0xf, SB_BYTE_ENABLE));

	ret = रुको_क्रम((REG_READ(SB_PCKT) & SB_BUSY) == 0, 1000);
	अगर (ret) अणु
		DRM_ERROR("timeout waiting for SB to idle after read\n");
		वापस ret;
	पूर्ण

	*val = REG_READ(SB_DATA);

	वापस 0;
पूर्ण

पूर्णांक cdv_sb_ग_लिखो(काष्ठा drm_device *dev, u32 reg, u32 val)
अणु
	पूर्णांक ret;
	अटल bool dpio_debug = true;
	u32 temp;

	अगर (dpio_debug) अणु
		अगर (cdv_sb_पढ़ो(dev, reg, &temp) == 0)
			DRM_DEBUG_KMS("0x%08x: 0x%08x (before)\n", reg, temp);
		DRM_DEBUG_KMS("0x%08x: 0x%08x\n", reg, val);
	पूर्ण

	ret = रुको_क्रम((REG_READ(SB_PCKT) & SB_BUSY) == 0, 1000);
	अगर (ret) अणु
		DRM_ERROR("timeout waiting for SB to idle before write\n");
		वापस ret;
	पूर्ण

	REG_WRITE(SB_ADDR, reg);
	REG_WRITE(SB_DATA, val);
	REG_WRITE(SB_PCKT,
		   SET_FIELD(SB_OPCODE_WRITE, SB_OPCODE) |
		   SET_FIELD(SB_DEST_DPLL, SB_DEST) |
		   SET_FIELD(0xf, SB_BYTE_ENABLE));

	ret = रुको_क्रम((REG_READ(SB_PCKT) & SB_BUSY) == 0, 1000);
	अगर (ret) अणु
		DRM_ERROR("timeout waiting for SB to idle after write\n");
		वापस ret;
	पूर्ण

	अगर (dpio_debug) अणु
		अगर (cdv_sb_पढ़ो(dev, reg, &temp) == 0)
			DRM_DEBUG_KMS("0x%08x: 0x%08x (after)\n", reg, temp);
	पूर्ण

	वापस 0;
पूर्ण

/* Reset the DPIO configuration रेजिस्टर.  The BIOS करोes this at every
 * mode set.
 */
व्योम cdv_sb_reset(काष्ठा drm_device *dev)
अणु

	REG_WRITE(DPIO_CFG, 0);
	REG_READ(DPIO_CFG);
	REG_WRITE(DPIO_CFG, DPIO_MODE_SELECT_0 | DPIO_CMN_RESET_N);
पूर्ण

/* Unlike most Intel display engines, on Cedarview the DPLL रेजिस्टरs
 * are behind this sideband bus.  They must be programmed जबतक the
 * DPLL reference घड़ी is on in the DPLL control रेजिस्टर, but beक्रमe
 * the DPLL is enabled in the DPLL control रेजिस्टर.
 */
अटल पूर्णांक
cdv_dpll_set_घड़ी_cdv(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
		       काष्ठा gma_घड़ी_प्रकार *घड़ी, bool is_lvds, u32 ddi_select)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	u32 m, n_vco, p;
	पूर्णांक ret = 0;
	पूर्णांक dpll_reg = (pipe == 0) ? DPLL_A : DPLL_B;
	पूर्णांक ref_sfr = (pipe == 0) ? SB_REF_DPLLA : SB_REF_DPLLB;
	u32 ref_value;
	u32 lane_reg, lane_value;

	cdv_sb_reset(dev);

	REG_WRITE(dpll_reg, DPLL_SYNCLOCK_ENABLE | DPLL_VGA_MODE_DIS);

	udelay(100);

	/* Follow the BIOS and ग_लिखो the REF/SFR Register. Hardcoded value */
	ref_value = 0x68A701;

	cdv_sb_ग_लिखो(dev, SB_REF_SFR(pipe), ref_value);

	/* We करोn't know what the other fields of these regs are, so
	 * leave them in place.
	 */
	/*
	 * The BIT 14:13 of 0x8010/0x8030 is used to select the ref clk
	 * क्रम the pipe A/B. Display spec 1.06 has wrong definition.
	 * Correct definition is like below:
	 *
	 * refclka mean use घड़ी from same PLL
	 *
	 * अगर DPLLA sets 01 and DPLLB sets 01, they use घड़ी from their pll
	 *
	 * अगर DPLLA sets 01 and DPLLB sets 02, both use clk from DPLLA
	 *
	 */
	ret = cdv_sb_पढ़ो(dev, ref_sfr, &ref_value);
	अगर (ret)
		वापस ret;
	ref_value &= ~(REF_CLK_MASK);

	/* use DPLL_A क्रम pipeB on CRT/HDMI */
	अगर (pipe == 1 && !is_lvds && !(ddi_select & DP_MASK)) अणु
		DRM_DEBUG_KMS("use DPLLA for pipe B\n");
		ref_value |= REF_CLK_DPLLA;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("use their DPLL for pipe A/B\n");
		ref_value |= REF_CLK_DPLL;
	पूर्ण
	ret = cdv_sb_ग_लिखो(dev, ref_sfr, ref_value);
	अगर (ret)
		वापस ret;

	ret = cdv_sb_पढ़ो(dev, SB_M(pipe), &m);
	अगर (ret)
		वापस ret;
	m &= ~SB_M_DIVIDER_MASK;
	m |= ((घड़ी->m2) << SB_M_DIVIDER_SHIFT);
	ret = cdv_sb_ग_लिखो(dev, SB_M(pipe), m);
	अगर (ret)
		वापस ret;

	ret = cdv_sb_पढ़ो(dev, SB_N_VCO(pipe), &n_vco);
	अगर (ret)
		वापस ret;

	/* Follow the BIOS to program the N_DIVIDER REG */
	n_vco &= 0xFFFF;
	n_vco |= 0x107;
	n_vco &= ~(SB_N_VCO_SEL_MASK |
		   SB_N_DIVIDER_MASK |
		   SB_N_CB_TUNE_MASK);

	n_vco |= ((घड़ी->n) << SB_N_DIVIDER_SHIFT);

	अगर (घड़ी->vco < 2250000) अणु
		n_vco |= (2 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (0 << SB_N_VCO_SEL_SHIFT);
	पूर्ण अन्यथा अगर (घड़ी->vco < 2750000) अणु
		n_vco |= (1 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (1 << SB_N_VCO_SEL_SHIFT);
	पूर्ण अन्यथा अगर (घड़ी->vco < 3300000) अणु
		n_vco |= (0 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (2 << SB_N_VCO_SEL_SHIFT);
	पूर्ण अन्यथा अणु
		n_vco |= (0 << SB_N_CB_TUNE_SHIFT);
		n_vco |= (3 << SB_N_VCO_SEL_SHIFT);
	पूर्ण

	ret = cdv_sb_ग_लिखो(dev, SB_N_VCO(pipe), n_vco);
	अगर (ret)
		वापस ret;

	ret = cdv_sb_पढ़ो(dev, SB_P(pipe), &p);
	अगर (ret)
		वापस ret;
	p &= ~(SB_P2_DIVIDER_MASK | SB_P1_DIVIDER_MASK);
	p |= SET_FIELD(घड़ी->p1, SB_P1_DIVIDER);
	चयन (घड़ी->p2) अणु
	हाल 5:
		p |= SET_FIELD(SB_P2_5, SB_P2_DIVIDER);
		अवरोध;
	हाल 10:
		p |= SET_FIELD(SB_P2_10, SB_P2_DIVIDER);
		अवरोध;
	हाल 14:
		p |= SET_FIELD(SB_P2_14, SB_P2_DIVIDER);
		अवरोध;
	हाल 7:
		p |= SET_FIELD(SB_P2_7, SB_P2_DIVIDER);
		अवरोध;
	शेष:
		DRM_ERROR("Bad P2 clock: %d\n", घड़ी->p2);
		वापस -EINVAL;
	पूर्ण
	ret = cdv_sb_ग_लिखो(dev, SB_P(pipe), p);
	अगर (ret)
		वापस ret;

	अगर (ddi_select) अणु
		अगर ((ddi_select & DDI_MASK) == DDI0_SELECT) अणु
			lane_reg = PSB_LANE0;
			cdv_sb_पढ़ो(dev, lane_reg, &lane_value);
			lane_value &= ~(LANE_PLL_MASK);
			lane_value |= LANE_PLL_ENABLE | LANE_PLL_PIPE(pipe);
			cdv_sb_ग_लिखो(dev, lane_reg, lane_value);

			lane_reg = PSB_LANE1;
			cdv_sb_पढ़ो(dev, lane_reg, &lane_value);
			lane_value &= ~(LANE_PLL_MASK);
			lane_value |= LANE_PLL_ENABLE | LANE_PLL_PIPE(pipe);
			cdv_sb_ग_लिखो(dev, lane_reg, lane_value);
		पूर्ण अन्यथा अणु
			lane_reg = PSB_LANE2;
			cdv_sb_पढ़ो(dev, lane_reg, &lane_value);
			lane_value &= ~(LANE_PLL_MASK);
			lane_value |= LANE_PLL_ENABLE | LANE_PLL_PIPE(pipe);
			cdv_sb_ग_लिखो(dev, lane_reg, lane_value);

			lane_reg = PSB_LANE3;
			cdv_sb_पढ़ो(dev, lane_reg, &lane_value);
			lane_value &= ~(LANE_PLL_MASK);
			lane_value |= LANE_PLL_ENABLE | LANE_PLL_PIPE(pipe);
			cdv_sb_ग_लिखो(dev, lane_reg, lane_value);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gma_limit_t *cdv_पूर्णांकel_limit(काष्ठा drm_crtc *crtc,
						 पूर्णांक refclk)
अणु
	स्थिर काष्ठा gma_limit_t *limit;
	अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) अणु
		/*
		 * Now only single-channel LVDS is supported on CDV. If it is
		 * incorrect, please add the dual-channel LVDS.
		 */
		अगर (refclk == 96000)
			limit = &cdv_पूर्णांकel_limits[CDV_LIMIT_SINGLE_LVDS_96];
		अन्यथा
			limit = &cdv_पूर्णांकel_limits[CDV_LIMIT_SINGLE_LVDS_100];
	पूर्ण अन्यथा अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_DISPLAYPORT) ||
			gma_pipe_has_type(crtc, INTEL_OUTPUT_EDP)) अणु
		अगर (refclk == 27000)
			limit = &cdv_पूर्णांकel_limits[CDV_LIMIT_DP_27];
		अन्यथा
			limit = &cdv_पूर्णांकel_limits[CDV_LIMIT_DP_100];
	पूर्ण अन्यथा अणु
		अगर (refclk == 27000)
			limit = &cdv_पूर्णांकel_limits[CDV_LIMIT_DAC_HDMI_27];
		अन्यथा
			limit = &cdv_पूर्णांकel_limits[CDV_LIMIT_DAC_HDMI_96];
	पूर्ण
	वापस limit;
पूर्ण

/* m1 is reserved as 0 in CDV, n is a ring counter */
अटल व्योम cdv_पूर्णांकel_घड़ी(पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *घड़ी)
अणु
	घड़ी->m = घड़ी->m2 + 2;
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	घड़ी->vco = (refclk * घड़ी->m) / घड़ी->n;
	घड़ी->करोt = घड़ी->vco / घड़ी->p;
पूर्ण

अटल bool cdv_पूर्णांकel_find_dp_pll(स्थिर काष्ठा gma_limit_t *limit,
				  काष्ठा drm_crtc *crtc, पूर्णांक target,
				  पूर्णांक refclk,
				  काष्ठा gma_घड़ी_प्रकार *best_घड़ी)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा gma_घड़ी_प्रकार घड़ी;

	स_रखो(&घड़ी, 0, माप(घड़ी));

	चयन (refclk) अणु
	हाल 27000:
		अगर (target < 200000) अणु
			घड़ी.p1 = 2;
			घड़ी.p2 = 10;
			घड़ी.n = 1;
			घड़ी.m1 = 0;
			घड़ी.m2 = 118;
		पूर्ण अन्यथा अणु
			घड़ी.p1 = 1;
			घड़ी.p2 = 10;
			घड़ी.n = 1;
			घड़ी.m1 = 0;
			घड़ी.m2 = 98;
		पूर्ण
		अवरोध;

	हाल 100000:
		अगर (target < 200000) अणु
			घड़ी.p1 = 2;
			घड़ी.p2 = 10;
			घड़ी.n = 5;
			घड़ी.m1 = 0;
			घड़ी.m2 = 160;
		पूर्ण अन्यथा अणु
			घड़ी.p1 = 1;
			घड़ी.p2 = 10;
			घड़ी.n = 5;
			घड़ी.m1 = 0;
			घड़ी.m2 = 133;
		पूर्ण
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	gma_crtc->घड़ी_funcs->घड़ी(refclk, &घड़ी);
	स_नकल(best_घड़ी, &घड़ी, माप(काष्ठा gma_घड़ी_प्रकार));
	वापस true;
पूर्ण

#घोषणा		FIFO_PIPEA		(1 << 0)
#घोषणा		FIFO_PIPEB		(1 << 1)

अटल bool cdv_पूर्णांकel_pipe_enabled(काष्ठा drm_device *dev, पूर्णांक pipe)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = शून्य;

	crtc = dev_priv->pipe_to_crtc_mapping[pipe];
	gma_crtc = to_gma_crtc(crtc);

	अगर (crtc->primary->fb == शून्य || !gma_crtc->active)
		वापस false;
	वापस true;
पूर्ण

व्योम cdv_disable_sr(काष्ठा drm_device *dev)
अणु
	अगर (REG_READ(FW_BLC_SELF) & FW_BLC_SELF_EN) अणु

		/* Disable self-refresh beक्रमe adjust WM */
		REG_WRITE(FW_BLC_SELF, (REG_READ(FW_BLC_SELF) & ~FW_BLC_SELF_EN));
		REG_READ(FW_BLC_SELF);

		gma_रुको_क्रम_vblank(dev);

		/* Cedarview workaround to ग_लिखो ovelay plane, which क्रमce to leave
		 * MAX_FIFO state.
		 */
		REG_WRITE(OV_OVADD, 0/*dev_priv->ovl_offset*/);
		REG_READ(OV_OVADD);

		gma_रुको_क्रम_vblank(dev);
	पूर्ण

पूर्ण

व्योम cdv_update_wm(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);

	/* Is only one pipe enabled? */
	अगर (cdv_पूर्णांकel_pipe_enabled(dev, 0) ^ cdv_पूर्णांकel_pipe_enabled(dev, 1)) अणु
		u32 fw;

		fw = REG_READ(DSPFW1);
		fw &= ~DSP_FIFO_SR_WM_MASK;
		fw |= (0x7e << DSP_FIFO_SR_WM_SHIFT);
		fw &= ~CURSOR_B_FIFO_WM_MASK;
		fw |= (0x4 << CURSOR_B_FIFO_WM_SHIFT);
		REG_WRITE(DSPFW1, fw);

		fw = REG_READ(DSPFW2);
		fw &= ~CURSOR_A_FIFO_WM_MASK;
		fw |= (0x6 << CURSOR_A_FIFO_WM_SHIFT);
		fw &= ~DSP_PLANE_C_FIFO_WM_MASK;
		fw |= (0x8 << DSP_PLANE_C_FIFO_WM_SHIFT);
		REG_WRITE(DSPFW2, fw);

		REG_WRITE(DSPFW3, 0x36000000);

		/* ignore FW4 */

		/* Is pipe b lvds ? */
		अगर (gma_crtc->pipe == 1 &&
		    gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) अणु
			REG_WRITE(DSPFW5, 0x00040330);
		पूर्ण अन्यथा अणु
			fw = (3 << DSP_PLANE_B_FIFO_WM1_SHIFT) |
			     (4 << DSP_PLANE_A_FIFO_WM1_SHIFT) |
			     (3 << CURSOR_B_FIFO_WM1_SHIFT) |
			     (4 << CURSOR_FIFO_SR_WM1_SHIFT);
			REG_WRITE(DSPFW5, fw);
		पूर्ण

		REG_WRITE(DSPFW6, 0x10);

		gma_रुको_क्रम_vblank(dev);

		/* enable self-refresh क्रम single pipe active */
		REG_WRITE(FW_BLC_SELF, FW_BLC_SELF_EN);
		REG_READ(FW_BLC_SELF);
		gma_रुको_क्रम_vblank(dev);

	पूर्ण अन्यथा अणु

		/* HW team suggested values... */
		REG_WRITE(DSPFW1, 0x3f880808);
		REG_WRITE(DSPFW2, 0x0b020202);
		REG_WRITE(DSPFW3, 0x24000000);
		REG_WRITE(DSPFW4, 0x08030202);
		REG_WRITE(DSPFW5, 0x01010101);
		REG_WRITE(DSPFW6, 0x1d0);

		gma_रुको_क्रम_vblank(dev);

		dev_priv->ops->disable_sr(dev);
	पूर्ण
पूर्ण

/*
 * Return the pipe currently connected to the panel fitter,
 * or -1 अगर the panel fitter is not present or not in use
 */
अटल पूर्णांक cdv_पूर्णांकel_panel_fitter_pipe(काष्ठा drm_device *dev)
अणु
	u32 pfit_control;

	pfit_control = REG_READ(PFIT_CONTROL);

	/* See अगर the panel fitter is in use */
	अगर ((pfit_control & PFIT_ENABLE) == 0)
		वापस -1;
	वापस (pfit_control >> 29) & 0x3;
पूर्ण

अटल पूर्णांक cdv_पूर्णांकel_crtc_mode_set(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode,
			       पूर्णांक x, पूर्णांक y,
			       काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	पूर्णांक refclk;
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	u32 dpll = 0, dspcntr, pipeconf;
	bool ok;
	bool is_lvds = false;
	bool is_dp = false;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *connector;
	स्थिर काष्ठा gma_limit_t *limit;
	u32 ddi_select = 0;
	bool is_edp = false;

	list_क्रम_each_entry(connector, &mode_config->connector_list, head) अणु
		काष्ठा gma_encoder *gma_encoder =
					gma_attached_encoder(connector);

		अगर (!connector->encoder
		    || connector->encoder->crtc != crtc)
			जारी;

		ddi_select = gma_encoder->ddi_select;
		चयन (gma_encoder->type) अणु
		हाल INTEL_OUTPUT_LVDS:
			is_lvds = true;
			अवरोध;
		हाल INTEL_OUTPUT_ANALOG:
		हाल INTEL_OUTPUT_HDMI:
			अवरोध;
		हाल INTEL_OUTPUT_DISPLAYPORT:
			is_dp = true;
			अवरोध;
		हाल INTEL_OUTPUT_EDP:
			is_edp = true;
			अवरोध;
		शेष:
			DRM_ERROR("invalid output type.\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (dev_priv->dplla_96mhz)
		/* low-end sku, 96/100 mhz */
		refclk = 96000;
	अन्यथा
		/* high-end sku, 27/100 mhz */
		refclk = 27000;
	अगर (is_dp || is_edp) अणु
		/*
		 * Based on the spec the low-end SKU has only CRT/LVDS. So it is
		 * unnecessary to consider it क्रम DP/eDP.
		 * On the high-end SKU, it will use the 27/100M reference clk
		 * क्रम DP/eDP. When using SSC घड़ी, the ref clk is 100MHz.Otherwise
		 * it will be 27MHz. From the VBIOS code it seems that the pipe A choose
		 * 27MHz क्रम DP/eDP जबतक the Pipe B chooses the 100MHz.
		 */
		अगर (pipe == 0)
			refclk = 27000;
		अन्यथा
			refclk = 100000;
	पूर्ण

	अगर (is_lvds && dev_priv->lvds_use_ssc) अणु
		refclk = dev_priv->lvds_ssc_freq * 1000;
		DRM_DEBUG_KMS("Use SSC reference clock %d Mhz\n", dev_priv->lvds_ssc_freq);
	पूर्ण

	drm_mode_debug_prपूर्णांकmodeline(adjusted_mode);

	limit = gma_crtc->घड़ी_funcs->limit(crtc, refclk);

	ok = limit->find_pll(limit, crtc, adjusted_mode->घड़ी, refclk,
				 &घड़ी);
	अगर (!ok) अणु
		DRM_ERROR("Couldn't find PLL settings for mode! target: %d, actual: %d",
			  adjusted_mode->घड़ी, घड़ी.करोt);
		वापस 0;
	पूर्ण

	dpll = DPLL_VGA_MODE_DIS;

	अगर (is_dp || is_edp) अणु
		cdv_पूर्णांकel_dp_set_m_n(crtc, mode, adjusted_mode);
	पूर्ण अन्यथा अणु
		REG_WRITE(PIPE_GMCH_DATA_M(pipe), 0);
		REG_WRITE(PIPE_GMCH_DATA_N(pipe), 0);
		REG_WRITE(PIPE_DP_LINK_M(pipe), 0);
		REG_WRITE(PIPE_DP_LINK_N(pipe), 0);
	पूर्ण

	dpll |= DPLL_SYNCLOCK_ENABLE;
/*	अगर (is_lvds)
		dpll |= DPLLB_MODE_LVDS;
	अन्यथा
		dpll |= DPLLB_MODE_DAC_SERIAL; */
	/* dpll |= (2 << 11); */

	/* setup pipeconf */
	pipeconf = REG_READ(map->conf);

	pipeconf &= ~(PIPE_BPC_MASK);
	अगर (is_edp) अणु
		चयन (dev_priv->edp.bpp) अणु
		हाल 24:
			pipeconf |= PIPE_8BPC;
			अवरोध;
		हाल 18:
			pipeconf |= PIPE_6BPC;
			अवरोध;
		हाल 30:
			pipeconf |= PIPE_10BPC;
			अवरोध;
		शेष:
			pipeconf |= PIPE_8BPC;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (is_lvds) अणु
		/* the BPC will be 6 अगर it is 18-bit LVDS panel */
		अगर ((REG_READ(LVDS) & LVDS_A3_POWER_MASK) == LVDS_A3_POWER_UP)
			pipeconf |= PIPE_8BPC;
		अन्यथा
			pipeconf |= PIPE_6BPC;
	पूर्ण अन्यथा
		pipeconf |= PIPE_8BPC;

	/* Set up the display plane रेजिस्टर */
	dspcntr = DISPPLANE_GAMMA_ENABLE;

	अगर (pipe == 0)
		dspcntr |= DISPPLANE_SEL_PIPE_A;
	अन्यथा
		dspcntr |= DISPPLANE_SEL_PIPE_B;

	dspcntr |= DISPLAY_PLANE_ENABLE;
	pipeconf |= PIPEACONF_ENABLE;

	REG_WRITE(map->dpll, dpll | DPLL_VGA_MODE_DIS | DPLL_SYNCLOCK_ENABLE);
	REG_READ(map->dpll);

	cdv_dpll_set_घड़ी_cdv(dev, crtc, &घड़ी, is_lvds, ddi_select);

	udelay(150);


	/* The LVDS pin pair needs to be on beक्रमe the DPLLs are enabled.
	 * This is an exception to the general rule that mode_set करोesn't turn
	 * things on.
	 */
	अगर (is_lvds) अणु
		u32 lvds = REG_READ(LVDS);

		lvds |=
		    LVDS_PORT_EN | LVDS_A0A2_CLKA_POWER_UP |
		    LVDS_PIPEB_SELECT;
		/* Set the B0-B3 data pairs corresponding to
		 * whether we're going to
		 * set the DPLLs क्रम dual-channel mode or not.
		 */
		अगर (घड़ी.p2 == 7)
			lvds |= LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP;
		अन्यथा
			lvds &= ~(LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP);

		/* It would be nice to set 24 vs 18-bit mode (LVDS_A3_POWER_UP)
		 * appropriately here, but we need to look more
		 * thoroughly पूर्णांकo how panels behave in the two modes.
		 */

		REG_WRITE(LVDS, lvds);
		REG_READ(LVDS);
	पूर्ण

	dpll |= DPLL_VCO_ENABLE;

	/* Disable the panel fitter अगर it was on our pipe */
	अगर (cdv_पूर्णांकel_panel_fitter_pipe(dev) == pipe)
		REG_WRITE(PFIT_CONTROL, 0);

	DRM_DEBUG_KMS("Mode for pipe %c:\n", pipe == 0 ? 'A' : 'B');
	drm_mode_debug_prपूर्णांकmodeline(mode);

	REG_WRITE(map->dpll,
		(REG_READ(map->dpll) & ~DPLL_LOCK) | DPLL_VCO_ENABLE);
	REG_READ(map->dpll);
	/* Wait क्रम the घड़ीs to stabilize. */
	udelay(150); /* 42 usec w/o calibration, 110 with.  rounded up. */

	अगर (!(REG_READ(map->dpll) & DPLL_LOCK)) अणु
		dev_err(dev->dev, "Failed to get DPLL lock\n");
		वापस -EBUSY;
	पूर्ण

	अणु
		पूर्णांक sdvo_pixel_multiply = adjusted_mode->घड़ी / mode->घड़ी;
		REG_WRITE(map->dpll_md, (0 << DPLL_MD_UDI_DIVIDER_SHIFT) | ((sdvo_pixel_multiply - 1) << DPLL_MD_UDI_MULTIPLIER_SHIFT));
	पूर्ण

	REG_WRITE(map->htotal, (adjusted_mode->crtc_hdisplay - 1) |
		  ((adjusted_mode->crtc_htotal - 1) << 16));
	REG_WRITE(map->hblank, (adjusted_mode->crtc_hblank_start - 1) |
		  ((adjusted_mode->crtc_hblank_end - 1) << 16));
	REG_WRITE(map->hsync, (adjusted_mode->crtc_hsync_start - 1) |
		  ((adjusted_mode->crtc_hsync_end - 1) << 16));
	REG_WRITE(map->vtotal, (adjusted_mode->crtc_vdisplay - 1) |
		  ((adjusted_mode->crtc_vtotal - 1) << 16));
	REG_WRITE(map->vblank, (adjusted_mode->crtc_vblank_start - 1) |
		  ((adjusted_mode->crtc_vblank_end - 1) << 16));
	REG_WRITE(map->vsync, (adjusted_mode->crtc_vsync_start - 1) |
		  ((adjusted_mode->crtc_vsync_end - 1) << 16));
	/* pipesrc and dspsize control the size that is scaled from,
	 * which should always be the user's requested size.
	 */
	REG_WRITE(map->size,
		  ((mode->vdisplay - 1) << 16) | (mode->hdisplay - 1));
	REG_WRITE(map->pos, 0);
	REG_WRITE(map->src,
		  ((mode->hdisplay - 1) << 16) | (mode->vdisplay - 1));
	REG_WRITE(map->conf, pipeconf);
	REG_READ(map->conf);

	gma_रुको_क्रम_vblank(dev);

	REG_WRITE(map->cntr, dspcntr);

	/* Flush the plane changes */
	अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs =
		    crtc->helper_निजी;
		crtc_funcs->mode_set_base(crtc, x, y, old_fb);
	पूर्ण

	gma_रुको_क्रम_vblank(dev);

	वापस 0;
पूर्ण

/** Derive the pixel घड़ी क्रम the given refclk and भागisors क्रम 8xx chips. */

/* FIXME: why are we using this, should it be cdv_ in this tree ? */

अटल व्योम i8xx_घड़ी(पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *घड़ी)
अणु
	घड़ी->m = 5 * (घड़ी->m1 + 2) + (घड़ी->m2 + 2);
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	घड़ी->vco = refclk * घड़ी->m / (घड़ी->n + 2);
	घड़ी->करोt = घड़ी->vco / घड़ी->p;
पूर्ण

/* Returns the घड़ी of the currently programmed mode of the given pipe. */
अटल पूर्णांक cdv_पूर्णांकel_crtc_घड़ी_get(काष्ठा drm_device *dev,
				काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	u32 dpll;
	u32 fp;
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	bool is_lvds;
	काष्ठा psb_pipe *p = &dev_priv->regs.pipe[pipe];

	अगर (gma_घातer_begin(dev, false)) अणु
		dpll = REG_READ(map->dpll);
		अगर ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
			fp = REG_READ(map->fp0);
		अन्यथा
			fp = REG_READ(map->fp1);
		is_lvds = (pipe == 1) && (REG_READ(LVDS) & LVDS_PORT_EN);
		gma_घातer_end(dev);
	पूर्ण अन्यथा अणु
		dpll = p->dpll;
		अगर ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
			fp = p->fp0;
		अन्यथा
			fp = p->fp1;

		is_lvds = (pipe == 1) &&
				(dev_priv->regs.psb.saveLVDS & LVDS_PORT_EN);
	पूर्ण

	घड़ी.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	घड़ी.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	घड़ी.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;

	अगर (is_lvds) अणु
		घड़ी.p1 =
		    ffs((dpll &
			 DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS) >>
			DPLL_FPA01_P1_POST_DIV_SHIFT);
		अगर (घड़ी.p1 == 0) अणु
			घड़ी.p1 = 4;
			dev_err(dev->dev, "PLL %d\n", dpll);
		पूर्ण
		घड़ी.p2 = 14;

		अगर ((dpll & PLL_REF_INPUT_MASK) ==
		    PLLB_REF_INPUT_SPREADSPECTRUMIN) अणु
			/* XXX: might not be 66MHz */
			i8xx_घड़ी(66000, &घड़ी);
		पूर्ण अन्यथा
			i8xx_घड़ी(48000, &घड़ी);
	पूर्ण अन्यथा अणु
		अगर (dpll & PLL_P1_DIVIDE_BY_TWO)
			घड़ी.p1 = 2;
		अन्यथा अणु
			घड़ी.p1 =
			    ((dpll &
			      DPLL_FPA01_P1_POST_DIV_MASK_I830) >>
			     DPLL_FPA01_P1_POST_DIV_SHIFT) + 2;
		पूर्ण
		अगर (dpll & PLL_P2_DIVIDE_BY_4)
			घड़ी.p2 = 4;
		अन्यथा
			घड़ी.p2 = 2;

		i8xx_घड़ी(48000, &घड़ी);
	पूर्ण

	/* XXX: It would be nice to validate the घड़ीs, but we can't reuse
	 * i830PllIsValid() because it relies on the xf86_config connector
	 * configuration being accurate, which it isn't necessarily.
	 */

	वापस घड़ी.करोt;
पूर्ण

/** Returns the currently programmed mode of the given pipe. */
काष्ठा drm_display_mode *cdv_पूर्णांकel_crtc_mode_get(काष्ठा drm_device *dev,
					     काष्ठा drm_crtc *crtc)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_pipe *p = &dev_priv->regs.pipe[pipe];
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	काष्ठा drm_display_mode *mode;
	पूर्णांक htot;
	पूर्णांक hsync;
	पूर्णांक vtot;
	पूर्णांक vsync;

	अगर (gma_घातer_begin(dev, false)) अणु
		htot = REG_READ(map->htotal);
		hsync = REG_READ(map->hsync);
		vtot = REG_READ(map->vtotal);
		vsync = REG_READ(map->vsync);
		gma_घातer_end(dev);
	पूर्ण अन्यथा अणु
		htot = p->htotal;
		hsync = p->hsync;
		vtot = p->vtotal;
		vsync = p->vsync;
	पूर्ण

	mode = kzalloc(माप(*mode), GFP_KERNEL);
	अगर (!mode)
		वापस शून्य;

	mode->घड़ी = cdv_पूर्णांकel_crtc_घड़ी_get(dev, crtc);
	mode->hdisplay = (htot & 0xffff) + 1;
	mode->htotal = ((htot & 0xffff0000) >> 16) + 1;
	mode->hsync_start = (hsync & 0xffff) + 1;
	mode->hsync_end = ((hsync & 0xffff0000) >> 16) + 1;
	mode->vdisplay = (vtot & 0xffff) + 1;
	mode->vtotal = ((vtot & 0xffff0000) >> 16) + 1;
	mode->vsync_start = (vsync & 0xffff) + 1;
	mode->vsync_end = ((vsync & 0xffff0000) >> 16) + 1;

	drm_mode_set_name(mode);
	drm_mode_set_crtcinfo(mode, 0);

	वापस mode;
पूर्ण

स्थिर काष्ठा drm_crtc_helper_funcs cdv_पूर्णांकel_helper_funcs = अणु
	.dpms = gma_crtc_dpms,
	.mode_set = cdv_पूर्णांकel_crtc_mode_set,
	.mode_set_base = gma_pipe_set_base,
	.prepare = gma_crtc_prepare,
	.commit = gma_crtc_commit,
	.disable = gma_crtc_disable,
पूर्ण;

स्थिर काष्ठा gma_घड़ी_funcs cdv_घड़ी_funcs = अणु
	.घड़ी = cdv_पूर्णांकel_घड़ी,
	.limit = cdv_पूर्णांकel_limit,
	.pll_is_valid = gma_pll_is_valid,
पूर्ण;
