<शैली गुरु>
/*
 * Copyright तऊ 2014-2016 Intel Corporation
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

#समावेश "display/intel_dp.h"

#समावेश "intel_display_types.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_sideband.h"

/**
 * DOC: DPIO
 *
 * VLV, CHV and BXT have slightly peculiar display PHYs क्रम driving DP/HDMI
 * ports. DPIO is the name given to such a display PHY. These PHYs
 * करोn't follow the standard programming model using direct MMIO
 * रेजिस्टरs, and instead their रेजिस्टरs must be accessed trough IOSF
 * sideband. VLV has one such PHY क्रम driving ports B and C, and CHV
 * adds another PHY क्रम driving port D. Each PHY responds to specअगरic
 * IOSF-SB port.
 *
 * Each display PHY is made up of one or two channels. Each channel
 * houses a common lane part which contains the PLL and other common
 * logic. CH0 common lane also contains the IOSF-SB logic क्रम the
 * Common Register Interface (CRI) ie. the DPIO रेजिस्टरs. CRI घड़ी
 * must be running when any DPIO रेजिस्टरs are accessed.
 *
 * In addition to having their own रेजिस्टरs, the PHYs are also
 * controlled through some dedicated संकेतs from the display
 * controller. These include PLL reference घड़ी enable, PLL enable,
 * and CRI घड़ी selection, क्रम example.
 *
 * Eeach channel also has two splines (also called data lanes), and
 * each spline is made up of one Physical Access Coding Sub-Layer
 * (PCS) block and two TX lanes. So each channel has two PCS blocks
 * and four TX lanes. The TX lanes are used as DP lanes or TMDS
 * data/घड़ी pairs depending on the output type.
 *
 * Additionally the PHY also contains an AUX lane with AUX blocks
 * क्रम each channel. This is used क्रम DP AUX communication, but
 * this fact isn't really relevant क्रम the driver since AUX is
 * controlled from the display controller side. No DPIO रेजिस्टरs
 * need to be accessed during AUX communication,
 *
 * Generally on VLV/CHV the common lane corresponds to the pipe and
 * the spline (PCS/TX) corresponds to the port.
 *
 * For dual channel PHY (VLV/CHV):
 *
 *  pipe A == CMN/PLL/REF CH0
 *
 *  pipe B == CMN/PLL/REF CH1
 *
 *  port B == PCS/TX CH0
 *
 *  port C == PCS/TX CH1
 *
 * This is especially important when we cross the streams
 * ie. drive port B with pipe B, or port C with pipe A.
 *
 * For single channel PHY (CHV):
 *
 *  pipe C == CMN/PLL/REF CH0
 *
 *  port D == PCS/TX CH0
 *
 * On BXT the entire PHY channel corresponds to the port. That means
 * the PLL is also now associated with the port rather than the pipe,
 * and so the घड़ी needs to be routed to the appropriate transcoder.
 * Port A PLL is directly connected to transcoder EDP and port B/C
 * PLLs can be routed to any transcoder A/B/C.
 *
 * Note: DDI0 is digital port B, DD1 is digital port C, and DDI2 is
 * digital port D (CHV) or port A (BXT). ::
 *
 *
 *     Dual channel PHY (VLV/CHV/BXT)
 *     ---------------------------------
 *     |      CH0      |      CH1      |
 *     |  CMN/PLL/REF  |  CMN/PLL/REF  |
 *     |---------------|---------------| Display PHY
 *     | PCS01 | PCS23 | PCS01 | PCS23 |
 *     |-------|-------|-------|-------|
 *     |TX0|TX1|TX2|TX3|TX0|TX1|TX2|TX3|
 *     ---------------------------------
 *     |     DDI0      |     DDI1      | DP/HDMI ports
 *     ---------------------------------
 *
 *     Single channel PHY (CHV/BXT)
 *     -----------------
 *     |      CH0      |
 *     |  CMN/PLL/REF  |
 *     |---------------| Display PHY
 *     | PCS01 | PCS23 |
 *     |-------|-------|
 *     |TX0|TX1|TX2|TX3|
 *     -----------------
 *     |     DDI2      | DP/HDMI port
 *     -----------------
 */

/**
 * काष्ठा bxt_ddi_phy_info - Hold info क्रम a broxton DDI phy
 */
काष्ठा bxt_ddi_phy_info अणु
	/**
	 * @dual_channel: true अगर this phy has a second channel.
	 */
	bool dual_channel;

	/**
	 * @rcomp_phy: If -1, indicates this phy has its own rcomp resistor.
	 * Otherwise the GRC value will be copied from the phy indicated by
	 * this field.
	 */
	क्रमागत dpio_phy rcomp_phy;

	/**
	 * @reset_delay: delay in us to रुको beक्रमe setting the common reset
	 * bit in BXT_PHY_CTL_FAMILY, which effectively enables the phy.
	 */
	पूर्णांक reset_delay;

	/**
	 * @pwron_mask: Mask with the appropriate bit set that would cause the
	 * punit to घातer this phy अगर written to BXT_P_CR_GT_DISP_PWRON.
	 */
	u32 pwron_mask;

	/**
	 * @channel: काष्ठा containing per channel inक्रमmation.
	 */
	काष्ठा अणु
		/**
		 * @channel.port: which port maps to this channel.
		 */
		क्रमागत port port;
	पूर्ण channel[2];
पूर्ण;

अटल स्थिर काष्ठा bxt_ddi_phy_info bxt_ddi_phy_info[] = अणु
	[DPIO_PHY0] = अणु
		.dual_channel = true,
		.rcomp_phy = DPIO_PHY1,
		.pwron_mask = BIT(0),

		.channel = अणु
			[DPIO_CH0] = अणु .port = PORT_B पूर्ण,
			[DPIO_CH1] = अणु .port = PORT_C पूर्ण,
		पूर्ण
	पूर्ण,
	[DPIO_PHY1] = अणु
		.dual_channel = false,
		.rcomp_phy = -1,
		.pwron_mask = BIT(1),

		.channel = अणु
			[DPIO_CH0] = अणु .port = PORT_A पूर्ण,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bxt_ddi_phy_info glk_ddi_phy_info[] = अणु
	[DPIO_PHY0] = अणु
		.dual_channel = false,
		.rcomp_phy = DPIO_PHY1,
		.pwron_mask = BIT(0),
		.reset_delay = 20,

		.channel = अणु
			[DPIO_CH0] = अणु .port = PORT_B पूर्ण,
		पूर्ण
	पूर्ण,
	[DPIO_PHY1] = अणु
		.dual_channel = false,
		.rcomp_phy = -1,
		.pwron_mask = BIT(3),
		.reset_delay = 20,

		.channel = अणु
			[DPIO_CH0] = अणु .port = PORT_A पूर्ण,
		पूर्ण
	पूर्ण,
	[DPIO_PHY2] = अणु
		.dual_channel = false,
		.rcomp_phy = DPIO_PHY1,
		.pwron_mask = BIT(1),
		.reset_delay = 20,

		.channel = अणु
			[DPIO_CH0] = अणु .port = PORT_C पूर्ण,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bxt_ddi_phy_info *
bxt_get_phy_list(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक *count)
अणु
	अगर (IS_GEMINILAKE(dev_priv)) अणु
		*count =  ARRAY_SIZE(glk_ddi_phy_info);
		वापस glk_ddi_phy_info;
	पूर्ण अन्यथा अणु
		*count =  ARRAY_SIZE(bxt_ddi_phy_info);
		वापस bxt_ddi_phy_info;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bxt_ddi_phy_info *
bxt_get_phy_info(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy)
अणु
	पूर्णांक count;
	स्थिर काष्ठा bxt_ddi_phy_info *phy_list =
		bxt_get_phy_list(dev_priv, &count);

	वापस &phy_list[phy];
पूर्ण

व्योम bxt_port_to_phy_channel(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port,
			     क्रमागत dpio_phy *phy, क्रमागत dpio_channel *ch)
अणु
	स्थिर काष्ठा bxt_ddi_phy_info *phy_info, *phys;
	पूर्णांक i, count;

	phys = bxt_get_phy_list(dev_priv, &count);

	क्रम (i = 0; i < count; i++) अणु
		phy_info = &phys[i];

		अगर (port == phy_info->channel[DPIO_CH0].port) अणु
			*phy = i;
			*ch = DPIO_CH0;
			वापस;
		पूर्ण

		अगर (phy_info->dual_channel &&
		    port == phy_info->channel[DPIO_CH1].port) अणु
			*phy = i;
			*ch = DPIO_CH1;
			वापस;
		पूर्ण
	पूर्ण

	drm_WARN(&dev_priv->drm, 1, "PHY not found for PORT %c",
		 port_name(port));
	*phy = DPIO_PHY0;
	*ch = DPIO_CH0;
पूर्ण

व्योम bxt_ddi_phy_set_संकेत_level(काष्ठा drm_i915_निजी *dev_priv,
				  क्रमागत port port, u32 margin, u32 scale,
				  u32 enable, u32 deemphasis)
अणु
	u32 val;
	क्रमागत dpio_phy phy;
	क्रमागत dpio_channel ch;

	bxt_port_to_phy_channel(dev_priv, port, &phy, &ch);

	/*
	 * While we ग_लिखो to the group रेजिस्टर to program all lanes at once we
	 * can पढ़ो only lane रेजिस्टरs and we pick lanes 0/1 क्रम that.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PCS_DW10_LN01(phy, ch));
	val &= ~(TX2_SWING_CALC_INIT | TX1_SWING_CALC_INIT);
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PCS_DW10_GRP(phy, ch), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_TX_DW2_LN0(phy, ch));
	val &= ~(MARGIN_000 | UNIQ_TRANS_SCALE);
	val |= margin << MARGIN_000_SHIFT | scale << UNIQ_TRANS_SCALE_SHIFT;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_TX_DW2_GRP(phy, ch), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_TX_DW3_LN0(phy, ch));
	val &= ~SCALE_DCOMP_METHOD;
	अगर (enable)
		val |= SCALE_DCOMP_METHOD;

	अगर ((val & UNIQUE_TRANGE_EN_METHOD) && !(val & SCALE_DCOMP_METHOD))
		drm_err(&dev_priv->drm,
			"Disabled scaling while ouniqetrangenmethod was set");

	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_TX_DW3_GRP(phy, ch), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_TX_DW4_LN0(phy, ch));
	val &= ~DE_EMPHASIS;
	val |= deemphasis << DEEMPH_SHIFT;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_TX_DW4_GRP(phy, ch), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_PCS_DW10_LN01(phy, ch));
	val |= TX2_SWING_CALC_INIT | TX1_SWING_CALC_INIT;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_PCS_DW10_GRP(phy, ch), val);
पूर्ण

bool bxt_ddi_phy_is_enabled(काष्ठा drm_i915_निजी *dev_priv,
			    क्रमागत dpio_phy phy)
अणु
	स्थिर काष्ठा bxt_ddi_phy_info *phy_info;

	phy_info = bxt_get_phy_info(dev_priv, phy);

	अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, BXT_P_CR_GT_DISP_PWRON) & phy_info->pwron_mask))
		वापस false;

	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_CL1CM_DW0(phy)) &
	     (PHY_POWER_GOOD | PHY_RESERVED)) != PHY_POWER_GOOD) अणु
		drm_dbg(&dev_priv->drm,
			"DDI PHY %d powered, but power hasn't settled\n", phy);

		वापस false;
	पूर्ण

	अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, BXT_PHY_CTL_FAMILY(phy)) & COMMON_RESET_DIS)) अणु
		drm_dbg(&dev_priv->drm,
			"DDI PHY %d powered, but still in reset\n", phy);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल u32 bxt_get_grc(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_REF_DW6(phy));

	वापस (val & GRC_CODE_MASK) >> GRC_CODE_SHIFT;
पूर्ण

अटल व्योम bxt_phy_रुको_grc_करोne(काष्ठा drm_i915_निजी *dev_priv,
				  क्रमागत dpio_phy phy)
अणु
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, BXT_PORT_REF_DW3(phy),
				  GRC_DONE, 10))
		drm_err(&dev_priv->drm, "timeout waiting for PHY%d GRC\n",
			phy);
पूर्ण

अटल व्योम _bxt_ddi_phy_init(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत dpio_phy phy)
अणु
	स्थिर काष्ठा bxt_ddi_phy_info *phy_info;
	u32 val;

	phy_info = bxt_get_phy_info(dev_priv, phy);

	अगर (bxt_ddi_phy_is_enabled(dev_priv, phy)) अणु
		/* Still पढ़ो out the GRC value क्रम state verअगरication */
		अगर (phy_info->rcomp_phy != -1)
			dev_priv->bxt_phy_grc = bxt_get_grc(dev_priv, phy);

		अगर (bxt_ddi_phy_verअगरy_state(dev_priv, phy)) अणु
			drm_dbg(&dev_priv->drm, "DDI PHY %d already enabled, "
				"won't reprogram it\n", phy);
			वापस;
		पूर्ण

		drm_dbg(&dev_priv->drm,
			"DDI PHY %d enabled with invalid state, "
			"force reprogramming it\n", phy);
	पूर्ण

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_P_CR_GT_DISP_PWRON);
	val |= phy_info->pwron_mask;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_CR_GT_DISP_PWRON, val);

	/*
	 * The PHY रेजिस्टरs start out inaccessible and respond to पढ़ोs with
	 * all 1s.  Eventually they become accessible as they घातer up, then
	 * the reserved bit will give the शेष 0.  Poll on the reserved bit
	 * becoming 0 to find when the PHY is accessible.
	 * The flag should get set in 100us according to the HW team, but
	 * use 1ms due to occasional समयouts observed with that.
	 */
	अगर (पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(&dev_priv->uncore,
				       BXT_PORT_CL1CM_DW0(phy),
				       PHY_RESERVED | PHY_POWER_GOOD,
				       PHY_POWER_GOOD,
				       1))
		drm_err(&dev_priv->drm, "timeout during PHY%d power on\n",
			phy);

	/* Program PLL Rcomp code offset */
	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_CL1CM_DW9(phy));
	val &= ~IREF0RC_OFFSET_MASK;
	val |= 0xE4 << IREF0RC_OFFSET_SHIFT;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_CL1CM_DW9(phy), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_CL1CM_DW10(phy));
	val &= ~IREF1RC_OFFSET_MASK;
	val |= 0xE4 << IREF1RC_OFFSET_SHIFT;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_CL1CM_DW10(phy), val);

	/* Program घातer gating */
	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_CL1CM_DW28(phy));
	val |= OCL1_POWER_DOWN_EN | DW28_OLDO_DYN_PWR_DOWN_EN |
		SUS_CLK_CONFIG;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_CL1CM_DW28(phy), val);

	अगर (phy_info->dual_channel) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_CL2CM_DW6(phy));
		val |= DW6_OLDO_DYN_PWR_DOWN_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_CL2CM_DW6(phy), val);
	पूर्ण

	अगर (phy_info->rcomp_phy != -1) अणु
		u32 grc_code;

		bxt_phy_रुको_grc_करोne(dev_priv, phy_info->rcomp_phy);

		/*
		 * PHY0 isn't connected to an RCOMP resistor so copy over
		 * the corresponding calibrated value from PHY1, and disable
		 * the स्वतःmatic calibration on PHY0.
		 */
		val = dev_priv->bxt_phy_grc = bxt_get_grc(dev_priv,
							  phy_info->rcomp_phy);
		grc_code = val << GRC_CODE_FAST_SHIFT |
			   val << GRC_CODE_SLOW_SHIFT |
			   val;
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_REF_DW6(phy), grc_code);

		val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PORT_REF_DW8(phy));
		val |= GRC_DIS | GRC_RDY_OVRD;
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_REF_DW8(phy), val);
	पूर्ण

	अगर (phy_info->reset_delay)
		udelay(phy_info->reset_delay);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PHY_CTL_FAMILY(phy));
	val |= COMMON_RESET_DIS;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PHY_CTL_FAMILY(phy), val);
पूर्ण

व्योम bxt_ddi_phy_uninit(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy)
अणु
	स्थिर काष्ठा bxt_ddi_phy_info *phy_info;
	u32 val;

	phy_info = bxt_get_phy_info(dev_priv, phy);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PHY_CTL_FAMILY(phy));
	val &= ~COMMON_RESET_DIS;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PHY_CTL_FAMILY(phy), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_P_CR_GT_DISP_PWRON);
	val &= ~phy_info->pwron_mask;
	पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_CR_GT_DISP_PWRON, val);
पूर्ण

व्योम bxt_ddi_phy_init(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy)
अणु
	स्थिर काष्ठा bxt_ddi_phy_info *phy_info =
		bxt_get_phy_info(dev_priv, phy);
	क्रमागत dpio_phy rcomp_phy = phy_info->rcomp_phy;
	bool was_enabled;

	lockdep_निश्चित_held(&dev_priv->घातer_करोमुख्यs.lock);

	was_enabled = true;
	अगर (rcomp_phy != -1)
		was_enabled = bxt_ddi_phy_is_enabled(dev_priv, rcomp_phy);

	/*
	 * We need to copy the GRC calibration value from rcomp_phy,
	 * so make sure it's घातered up.
	 */
	अगर (!was_enabled)
		_bxt_ddi_phy_init(dev_priv, rcomp_phy);

	_bxt_ddi_phy_init(dev_priv, phy);

	अगर (!was_enabled)
		bxt_ddi_phy_uninit(dev_priv, rcomp_phy);
पूर्ण

अटल bool __म_लिखो(6, 7)
__phy_reg_verअगरy_state(काष्ठा drm_i915_निजी *dev_priv, क्रमागत dpio_phy phy,
		       i915_reg_t reg, u32 mask, u32 expected,
		       स्थिर अक्षर *reg_fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर ((val & mask) == expected)
		वापस true;

	बहु_शुरू(args, reg_fmt);
	vaf.fmt = reg_fmt;
	vaf.va = &args;

	drm_dbg(&dev_priv->drm, "DDI PHY %d reg %pV [%08x] state mismatch: "
			 "current %08x, expected %08x (mask %08x)\n",
			 phy, &vaf, reg.reg, val, (val & ~mask) | expected,
			 mask);

	बहु_पूर्ण(args);

	वापस false;
पूर्ण

bool bxt_ddi_phy_verअगरy_state(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत dpio_phy phy)
अणु
	स्थिर काष्ठा bxt_ddi_phy_info *phy_info;
	u32 mask;
	bool ok;

	phy_info = bxt_get_phy_info(dev_priv, phy);

#घोषणा _CHK(reg, mask, exp, fmt, ...)					\
	__phy_reg_verअगरy_state(dev_priv, phy, reg, mask, exp, fmt,	\
			       ## __VA_ARGS__)

	अगर (!bxt_ddi_phy_is_enabled(dev_priv, phy))
		वापस false;

	ok = true;

	/* PLL Rcomp code offset */
	ok &= _CHK(BXT_PORT_CL1CM_DW9(phy),
		    IREF0RC_OFFSET_MASK, 0xe4 << IREF0RC_OFFSET_SHIFT,
		    "BXT_PORT_CL1CM_DW9(%d)", phy);
	ok &= _CHK(BXT_PORT_CL1CM_DW10(phy),
		    IREF1RC_OFFSET_MASK, 0xe4 << IREF1RC_OFFSET_SHIFT,
		    "BXT_PORT_CL1CM_DW10(%d)", phy);

	/* Power gating */
	mask = OCL1_POWER_DOWN_EN | DW28_OLDO_DYN_PWR_DOWN_EN | SUS_CLK_CONFIG;
	ok &= _CHK(BXT_PORT_CL1CM_DW28(phy), mask, mask,
		    "BXT_PORT_CL1CM_DW28(%d)", phy);

	अगर (phy_info->dual_channel)
		ok &= _CHK(BXT_PORT_CL2CM_DW6(phy),
			   DW6_OLDO_DYN_PWR_DOWN_EN, DW6_OLDO_DYN_PWR_DOWN_EN,
			   "BXT_PORT_CL2CM_DW6(%d)", phy);

	अगर (phy_info->rcomp_phy != -1) अणु
		u32 grc_code = dev_priv->bxt_phy_grc;

		grc_code = grc_code << GRC_CODE_FAST_SHIFT |
			   grc_code << GRC_CODE_SLOW_SHIFT |
			   grc_code;
		mask = GRC_CODE_FAST_MASK | GRC_CODE_SLOW_MASK |
		       GRC_CODE_NOM_MASK;
		ok &= _CHK(BXT_PORT_REF_DW6(phy), mask, grc_code,
			   "BXT_PORT_REF_DW6(%d)", phy);

		mask = GRC_DIS | GRC_RDY_OVRD;
		ok &= _CHK(BXT_PORT_REF_DW8(phy), mask, mask,
			    "BXT_PORT_REF_DW8(%d)", phy);
	पूर्ण

	वापस ok;
#अघोषित _CHK
पूर्ण

u8
bxt_ddi_phy_calc_lane_lat_optim_mask(u8 lane_count)
अणु
	चयन (lane_count) अणु
	हाल 1:
		वापस 0;
	हाल 2:
		वापस BIT(2) | BIT(0);
	हाल 4:
		वापस BIT(3) | BIT(2) | BIT(0);
	शेष:
		MISSING_CASE(lane_count);

		वापस 0;
	पूर्ण
पूर्ण

व्योम bxt_ddi_phy_set_lane_optim_mask(काष्ठा पूर्णांकel_encoder *encoder,
				     u8 lane_lat_optim_mask)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत dpio_phy phy;
	क्रमागत dpio_channel ch;
	पूर्णांक lane;

	bxt_port_to_phy_channel(dev_priv, port, &phy, &ch);

	क्रम (lane = 0; lane < 4; lane++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv,
					BXT_PORT_TX_DW14_LN(phy, ch, lane));

		/*
		 * Note that on CHV this flag is called UPAR, but has
		 * the same function.
		 */
		val &= ~LATENCY_OPTIM;
		अगर (lane_lat_optim_mask & BIT(lane))
			val |= LATENCY_OPTIM;

		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_PORT_TX_DW14_LN(phy, ch, lane),
			       val);
	पूर्ण
पूर्ण

u8
bxt_ddi_phy_get_lane_lat_optim_mask(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत dpio_phy phy;
	क्रमागत dpio_channel ch;
	पूर्णांक lane;
	u8 mask;

	bxt_port_to_phy_channel(dev_priv, port, &phy, &ch);

	mask = 0;
	क्रम (lane = 0; lane < 4; lane++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv,
					BXT_PORT_TX_DW14_LN(phy, ch, lane));

		अगर (val & LATENCY_OPTIM)
			mask |= BIT(lane);
	पूर्ण

	वापस mask;
पूर्ण

व्योम chv_set_phy_संकेत_level(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      u32 deemph_reg_value, u32 margin_reg_value,
			      bool uniq_trans_scale)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत dpio_channel ch = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;
	पूर्णांक i;

	vlv_dpio_get(dev_priv);

	/* Clear calc init */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW10(ch));
	val &= ~(DPIO_PCS_SWING_CALC_TX0_TX2 | DPIO_PCS_SWING_CALC_TX1_TX3);
	val &= ~(DPIO_PCS_TX1DEEMP_MASK | DPIO_PCS_TX2DEEMP_MASK);
	val |= DPIO_PCS_TX1DEEMP_9P5 | DPIO_PCS_TX2DEEMP_9P5;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW10(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW10(ch));
		val &= ~(DPIO_PCS_SWING_CALC_TX0_TX2 | DPIO_PCS_SWING_CALC_TX1_TX3);
		val &= ~(DPIO_PCS_TX1DEEMP_MASK | DPIO_PCS_TX2DEEMP_MASK);
		val |= DPIO_PCS_TX1DEEMP_9P5 | DPIO_PCS_TX2DEEMP_9P5;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW10(ch), val);
	पूर्ण

	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW9(ch));
	val &= ~(DPIO_PCS_TX1MARGIN_MASK | DPIO_PCS_TX2MARGIN_MASK);
	val |= DPIO_PCS_TX1MARGIN_000 | DPIO_PCS_TX2MARGIN_000;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW9(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW9(ch));
		val &= ~(DPIO_PCS_TX1MARGIN_MASK | DPIO_PCS_TX2MARGIN_MASK);
		val |= DPIO_PCS_TX1MARGIN_000 | DPIO_PCS_TX2MARGIN_000;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW9(ch), val);
	पूर्ण

	/* Program swing deemph */
	क्रम (i = 0; i < crtc_state->lane_count; i++) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_TX_DW4(ch, i));
		val &= ~DPIO_SWING_DEEMPH9P5_MASK;
		val |= deemph_reg_value << DPIO_SWING_DEEMPH9P5_SHIFT;
		vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_TX_DW4(ch, i), val);
	पूर्ण

	/* Program swing margin */
	क्रम (i = 0; i < crtc_state->lane_count; i++) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_TX_DW2(ch, i));

		val &= ~DPIO_SWING_MARGIN000_MASK;
		val |= margin_reg_value << DPIO_SWING_MARGIN000_SHIFT;

		/*
		 * Supposedly this value shouldn't matter when unique transition
		 * scale is disabled, but in fact it करोes matter. Let's just
		 * always program the same value and hope it's OK.
		 */
		val &= ~(0xff << DPIO_UNIQ_TRANS_SCALE_SHIFT);
		val |= 0x9a << DPIO_UNIQ_TRANS_SCALE_SHIFT;

		vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_TX_DW2(ch, i), val);
	पूर्ण

	/*
	 * The करोcument said it needs to set bit 27 क्रम ch0 and bit 26
	 * क्रम ch1. Might be a typo in the करोc.
	 * For now, क्रम this unique transition scale selection, set bit
	 * 27 क्रम ch0 and ch1.
	 */
	क्रम (i = 0; i < crtc_state->lane_count; i++) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_TX_DW3(ch, i));
		अगर (uniq_trans_scale)
			val |= DPIO_TX_UNIQ_TRANS_SCALE_EN;
		अन्यथा
			val &= ~DPIO_TX_UNIQ_TRANS_SCALE_EN;
		vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_TX_DW3(ch, i), val);
	पूर्ण

	/* Start swing calculation */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW10(ch));
	val |= DPIO_PCS_SWING_CALC_TX0_TX2 | DPIO_PCS_SWING_CALC_TX1_TX3;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW10(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW10(ch));
		val |= DPIO_PCS_SWING_CALC_TX0_TX2 | DPIO_PCS_SWING_CALC_TX1_TX3;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW10(ch), val);
	पूर्ण

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम chv_data_lane_soft_reset(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      bool reset)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत dpio_channel ch = vlv_dig_port_to_channel(enc_to_dig_port(encoder));
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;

	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW0(ch));
	अगर (reset)
		val &= ~(DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET);
	अन्यथा
		val |= DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW0(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW0(ch));
		अगर (reset)
			val &= ~(DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET);
		अन्यथा
			val |= DPIO_PCS_TX_LANE2_RESET | DPIO_PCS_TX_LANE1_RESET;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW0(ch), val);
	पूर्ण

	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW1(ch));
	val |= CHV_PCS_REQ_SOFTRESET_EN;
	अगर (reset)
		val &= ~DPIO_PCS_CLK_SOFT_RESET;
	अन्यथा
		val |= DPIO_PCS_CLK_SOFT_RESET;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW1(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW1(ch));
		val |= CHV_PCS_REQ_SOFTRESET_EN;
		अगर (reset)
			val &= ~DPIO_PCS_CLK_SOFT_RESET;
		अन्यथा
			val |= DPIO_PCS_CLK_SOFT_RESET;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW1(ch), val);
	पूर्ण
पूर्ण

व्योम chv_phy_pre_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत dpio_channel ch = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;
	अचिन्हित पूर्णांक lane_mask =
		पूर्णांकel_dp_unused_lane_mask(crtc_state->lane_count);
	u32 val;

	/*
	 * Must trick the second common lane पूर्णांकo lअगरe.
	 * Otherwise we can't even access the PLL.
	 */
	अगर (ch == DPIO_CH0 && pipe == PIPE_B)
		dig_port->release_cl2_override =
			!chv_phy_घातergate_ch(dev_priv, DPIO_PHY0, DPIO_CH1, true);

	chv_phy_घातergate_lanes(encoder, true, lane_mask);

	vlv_dpio_get(dev_priv);

	/* Assert data lane reset */
	chv_data_lane_soft_reset(encoder, crtc_state, true);

	/* program left/right घड़ी distribution */
	अगर (pipe != PIPE_B) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, _CHV_CMN_DW5_CH0);
		val &= ~(CHV_BUFLEFTENA1_MASK | CHV_BUFRIGHTENA1_MASK);
		अगर (ch == DPIO_CH0)
			val |= CHV_BUFLEFTENA1_FORCE;
		अगर (ch == DPIO_CH1)
			val |= CHV_BUFRIGHTENA1_FORCE;
		vlv_dpio_ग_लिखो(dev_priv, pipe, _CHV_CMN_DW5_CH0, val);
	पूर्ण अन्यथा अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, _CHV_CMN_DW1_CH1);
		val &= ~(CHV_BUFLEFTENA2_MASK | CHV_BUFRIGHTENA2_MASK);
		अगर (ch == DPIO_CH0)
			val |= CHV_BUFLEFTENA2_FORCE;
		अगर (ch == DPIO_CH1)
			val |= CHV_BUFRIGHTENA2_FORCE;
		vlv_dpio_ग_लिखो(dev_priv, pipe, _CHV_CMN_DW1_CH1, val);
	पूर्ण

	/* program घड़ी channel usage */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW8(ch));
	val |= CHV_PCS_USEDCLKCHANNEL_OVRRIDE;
	अगर (pipe != PIPE_B)
		val &= ~CHV_PCS_USEDCLKCHANNEL;
	अन्यथा
		val |= CHV_PCS_USEDCLKCHANNEL;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW8(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW8(ch));
		val |= CHV_PCS_USEDCLKCHANNEL_OVRRIDE;
		अगर (pipe != PIPE_B)
			val &= ~CHV_PCS_USEDCLKCHANNEL;
		अन्यथा
			val |= CHV_PCS_USEDCLKCHANNEL;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW8(ch), val);
	पूर्ण

	/*
	 * This a a bit weird since generally CL
	 * matches the pipe, but here we need to
	 * pick the CL based on the port.
	 */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW19(ch));
	अगर (pipe != PIPE_B)
		val &= ~CHV_CMN_USEDCLKCHANNEL;
	अन्यथा
		val |= CHV_CMN_USEDCLKCHANNEL;
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW19(ch), val);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम chv_phy_pre_encoder_enable(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत dpio_channel ch = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक data, i, stagger;
	u32 val;

	vlv_dpio_get(dev_priv);

	/* allow hardware to manage TX FIFO reset source */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW11(ch));
	val &= ~DPIO_LANEDESKEW_STRAP_OVRD;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW11(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW11(ch));
		val &= ~DPIO_LANEDESKEW_STRAP_OVRD;
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW11(ch), val);
	पूर्ण

	/* Program Tx lane latency optimal setting*/
	क्रम (i = 0; i < crtc_state->lane_count; i++) अणु
		/* Set the upar bit */
		अगर (crtc_state->lane_count == 1)
			data = 0x0;
		अन्यथा
			data = (i == 1) ? 0x0 : 0x1;
		vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_TX_DW14(ch, i),
				data << DPIO_UPAR_SHIFT);
	पूर्ण

	/* Data lane stagger programming */
	अगर (crtc_state->port_घड़ी > 270000)
		stagger = 0x18;
	अन्यथा अगर (crtc_state->port_घड़ी > 135000)
		stagger = 0xd;
	अन्यथा अगर (crtc_state->port_घड़ी > 67500)
		stagger = 0x7;
	अन्यथा अगर (crtc_state->port_घड़ी > 33750)
		stagger = 0x4;
	अन्यथा
		stagger = 0x2;

	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW11(ch));
	val |= DPIO_TX2_STAGGER_MASK(0x1f);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW11(ch), val);

	अगर (crtc_state->lane_count > 2) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS23_DW11(ch));
		val |= DPIO_TX2_STAGGER_MASK(0x1f);
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW11(ch), val);
	पूर्ण

	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS01_DW12(ch),
		       DPIO_LANESTAGGER_STRAP(stagger) |
		       DPIO_LANESTAGGER_STRAP_OVRD |
		       DPIO_TX1_STAGGER_MASK(0x1f) |
		       DPIO_TX1_STAGGER_MULT(6) |
		       DPIO_TX2_STAGGER_MULT(0));

	अगर (crtc_state->lane_count > 2) अणु
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS23_DW12(ch),
			       DPIO_LANESTAGGER_STRAP(stagger) |
			       DPIO_LANESTAGGER_STRAP_OVRD |
			       DPIO_TX1_STAGGER_MASK(0x1f) |
			       DPIO_TX1_STAGGER_MULT(7) |
			       DPIO_TX2_STAGGER_MULT(5));
	पूर्ण

	/* Deनिश्चित data lane reset */
	chv_data_lane_soft_reset(encoder, crtc_state, false);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम chv_phy_release_cl2_override(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (dig_port->release_cl2_override) अणु
		chv_phy_घातergate_ch(dev_priv, DPIO_PHY0, DPIO_CH1, false);
		dig_port->release_cl2_override = false;
	पूर्ण
पूर्ण

व्योम chv_phy_post_pll_disable(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc)->pipe;
	u32 val;

	vlv_dpio_get(dev_priv);

	/* disable left/right घड़ी distribution */
	अगर (pipe != PIPE_B) अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, _CHV_CMN_DW5_CH0);
		val &= ~(CHV_BUFLEFTENA1_MASK | CHV_BUFRIGHTENA1_MASK);
		vlv_dpio_ग_लिखो(dev_priv, pipe, _CHV_CMN_DW5_CH0, val);
	पूर्ण अन्यथा अणु
		val = vlv_dpio_पढ़ो(dev_priv, pipe, _CHV_CMN_DW1_CH1);
		val &= ~(CHV_BUFLEFTENA2_MASK | CHV_BUFRIGHTENA2_MASK);
		vlv_dpio_ग_लिखो(dev_priv, pipe, _CHV_CMN_DW1_CH1, val);
	पूर्ण

	vlv_dpio_put(dev_priv);

	/*
	 * Leave the घातer करोwn bit cleared क्रम at least one
	 * lane so that chv_घातergate_phy_ch() will घातer
	 * on something when the channel is otherwise unused.
	 * When the port is off and the override is हटाओd
	 * the lanes घातer करोwn anyway, so otherwise it करोesn't
	 * really matter what the state of घातer करोwn bits is
	 * after this.
	 */
	chv_phy_घातergate_lanes(encoder, false, 0x0);
पूर्ण

व्योम vlv_set_phy_संकेत_level(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      u32 demph_reg_value, u32 preemph_reg_value,
			      u32 uniqtranscale_reg_value, u32 tx3_demph)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत dpio_channel port = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;

	vlv_dpio_get(dev_priv);

	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW5(port), 0x00000000);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW4(port), demph_reg_value);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW2(port),
			 uniqtranscale_reg_value);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW3(port), 0x0C782040);

	अगर (tx3_demph)
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX3_DW4(port), tx3_demph);

	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW11(port), 0x00030000);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW9(port), preemph_reg_value);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW5(port), DPIO_TX_OCALINIT_EN);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम vlv_phy_pre_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत dpio_channel port = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;

	/* Program Tx lane resets to शेष */
	vlv_dpio_get(dev_priv);

	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW0(port),
			 DPIO_PCS_TX_LANE2_RESET |
			 DPIO_PCS_TX_LANE1_RESET);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW1(port),
			 DPIO_PCS_CLK_CRI_RXEB_EIOS_EN |
			 DPIO_PCS_CLK_CRI_RXDIGFILTSG_EN |
			 (1<<DPIO_PCS_CLK_DATAWIDTH_SHIFT) |
				 DPIO_PCS_CLK_SOFT_RESET);

	/* Fix up पूर्णांकer-pair skew failure */
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW12(port), 0x00750f00);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW11(port), 0x00001500);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_TX_DW14(port), 0x40400000);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम vlv_phy_pre_encoder_enable(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत dpio_channel port = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;

	vlv_dpio_get(dev_priv);

	/* Enable घड़ी channels क्रम this port */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PCS01_DW8(port));
	val = 0;
	अगर (pipe)
		val |= (1<<21);
	अन्यथा
		val &= ~(1<<21);
	val |= 0x001000c4;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW8(port), val);

	/* Program lane घड़ी */
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW14(port), 0x00760018);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW23(port), 0x00400888);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम vlv_phy_reset_lanes(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	क्रमागत dpio_channel port = vlv_dig_port_to_channel(dig_port);
	क्रमागत pipe pipe = crtc->pipe;

	vlv_dpio_get(dev_priv);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW0(port), 0x00000000);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PCS_DW1(port), 0x00e00060);
	vlv_dpio_put(dev_priv);
पूर्ण
