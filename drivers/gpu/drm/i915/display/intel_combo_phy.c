<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "intel_combo_phy.h"
#समावेश "intel_display_types.h"

#घोषणा क्रम_each_combo_phy(__dev_priv, __phy) \
	क्रम ((__phy) = PHY_A; (__phy) < I915_MAX_PHYS; (__phy)++)	\
		क्रम_each_अगर(पूर्णांकel_phy_is_combo(__dev_priv, __phy))

#घोषणा क्रम_each_combo_phy_reverse(__dev_priv, __phy) \
	क्रम ((__phy) = I915_MAX_PHYS; (__phy)-- > PHY_A;) \
		क्रम_each_अगर(पूर्णांकel_phy_is_combo(__dev_priv, __phy))

क्रमागत अणु
	PROCMON_0_85V_DOT_0,
	PROCMON_0_95V_DOT_0,
	PROCMON_0_95V_DOT_1,
	PROCMON_1_05V_DOT_0,
	PROCMON_1_05V_DOT_1,
पूर्ण;

अटल स्थिर काष्ठा cnl_procmon अणु
	u32 dw1, dw9, dw10;
पूर्ण cnl_procmon_values[] = अणु
	[PROCMON_0_85V_DOT_0] =
		अणु .dw1 = 0x00000000, .dw9 = 0x62AB67BB, .dw10 = 0x51914F96, पूर्ण,
	[PROCMON_0_95V_DOT_0] =
		अणु .dw1 = 0x00000000, .dw9 = 0x86E172C7, .dw10 = 0x77CA5EAB, पूर्ण,
	[PROCMON_0_95V_DOT_1] =
		अणु .dw1 = 0x00000000, .dw9 = 0x93F87FE1, .dw10 = 0x8AE871C5, पूर्ण,
	[PROCMON_1_05V_DOT_0] =
		अणु .dw1 = 0x00000000, .dw9 = 0x98FA82DD, .dw10 = 0x89E46DC1, पूर्ण,
	[PROCMON_1_05V_DOT_1] =
		अणु .dw1 = 0x00440000, .dw9 = 0x9A00AB25, .dw10 = 0x8AE38FF1, पूर्ण,
पूर्ण;

/*
 * CNL has just one set of रेजिस्टरs, जबतक gen11 has a set क्रम each combo PHY.
 * The CNL रेजिस्टरs are equivalent to the gen11 PHY A रेजिस्टरs, that's why we
 * call the ICL macros even though the function has CNL on its name.
 */
अटल स्थिर काष्ठा cnl_procmon *
cnl_get_procmon_ref_values(काष्ठा drm_i915_निजी *dev_priv, क्रमागत phy phy)
अणु
	स्थिर काष्ठा cnl_procmon *procmon;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW3(phy));
	चयन (val & (PROCESS_INFO_MASK | VOLTAGE_INFO_MASK)) अणु
	शेष:
		MISSING_CASE(val);
		fallthrough;
	हाल VOLTAGE_INFO_0_85V | PROCESS_INFO_DOT_0:
		procmon = &cnl_procmon_values[PROCMON_0_85V_DOT_0];
		अवरोध;
	हाल VOLTAGE_INFO_0_95V | PROCESS_INFO_DOT_0:
		procmon = &cnl_procmon_values[PROCMON_0_95V_DOT_0];
		अवरोध;
	हाल VOLTAGE_INFO_0_95V | PROCESS_INFO_DOT_1:
		procmon = &cnl_procmon_values[PROCMON_0_95V_DOT_1];
		अवरोध;
	हाल VOLTAGE_INFO_1_05V | PROCESS_INFO_DOT_0:
		procmon = &cnl_procmon_values[PROCMON_1_05V_DOT_0];
		अवरोध;
	हाल VOLTAGE_INFO_1_05V | PROCESS_INFO_DOT_1:
		procmon = &cnl_procmon_values[PROCMON_1_05V_DOT_1];
		अवरोध;
	पूर्ण

	वापस procmon;
पूर्ण

अटल व्योम cnl_set_procmon_ref_values(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत phy phy)
अणु
	स्थिर काष्ठा cnl_procmon *procmon;
	u32 val;

	procmon = cnl_get_procmon_ref_values(dev_priv, phy);

	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW1(phy));
	val &= ~((0xff << 16) | 0xff);
	val |= procmon->dw1;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_COMP_DW1(phy), val);

	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_COMP_DW9(phy), procmon->dw9);
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_COMP_DW10(phy), procmon->dw10);
पूर्ण

अटल bool check_phy_reg(काष्ठा drm_i915_निजी *dev_priv,
			  क्रमागत phy phy, i915_reg_t reg, u32 mask,
			  u32 expected_val)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

	अगर ((val & mask) != expected_val) अणु
		drm_dbg(&dev_priv->drm,
			"Combo PHY %c reg %08x state mismatch: "
			"current %08x mask %08x expected %08x\n",
			phy_name(phy),
			reg.reg, val, mask, expected_val);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool cnl_verअगरy_procmon_ref_values(काष्ठा drm_i915_निजी *dev_priv,
					  क्रमागत phy phy)
अणु
	स्थिर काष्ठा cnl_procmon *procmon;
	bool ret;

	procmon = cnl_get_procmon_ref_values(dev_priv, phy);

	ret = check_phy_reg(dev_priv, phy, ICL_PORT_COMP_DW1(phy),
			    (0xff << 16) | 0xff, procmon->dw1);
	ret &= check_phy_reg(dev_priv, phy, ICL_PORT_COMP_DW9(phy),
			     -1U, procmon->dw9);
	ret &= check_phy_reg(dev_priv, phy, ICL_PORT_COMP_DW10(phy),
			     -1U, procmon->dw10);

	वापस ret;
पूर्ण

अटल bool cnl_combo_phy_enabled(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस !(पूर्णांकel_de_पढ़ो(dev_priv, CHICKEN_MISC_2) & CNL_COMP_PWR_DOWN) &&
		(पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_COMP_DW0) & COMP_INIT);
पूर्ण

अटल bool cnl_combo_phy_verअगरy_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत phy phy = PHY_A;
	bool ret;

	अगर (!cnl_combo_phy_enabled(dev_priv))
		वापस false;

	ret = cnl_verअगरy_procmon_ref_values(dev_priv, phy);

	ret &= check_phy_reg(dev_priv, phy, CNL_PORT_CL1CM_DW5,
			     CL_POWER_DOWN_ENABLE, CL_POWER_DOWN_ENABLE);

	वापस ret;
पूर्ण

अटल व्योम cnl_combo_phys_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, CHICKEN_MISC_2);
	val &= ~CNL_COMP_PWR_DOWN;
	पूर्णांकel_de_ग_लिखो(dev_priv, CHICKEN_MISC_2, val);

	/* Dummy PORT_A to get the correct CNL रेजिस्टर from the ICL macro */
	cnl_set_procmon_ref_values(dev_priv, PHY_A);

	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_COMP_DW0);
	val |= COMP_INIT;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_COMP_DW0, val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_CL1CM_DW5);
	val |= CL_POWER_DOWN_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_CL1CM_DW5, val);
पूर्ण

अटल व्योम cnl_combo_phys_uninit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	अगर (!cnl_combo_phy_verअगरy_state(dev_priv))
		drm_warn(&dev_priv->drm,
			 "Combo PHY HW state changed unexpectedly.\n");

	val = पूर्णांकel_de_पढ़ो(dev_priv, CHICKEN_MISC_2);
	val |= CNL_COMP_PWR_DOWN;
	पूर्णांकel_de_ग_लिखो(dev_priv, CHICKEN_MISC_2, val);
पूर्ण

अटल bool has_phy_misc(काष्ठा drm_i915_निजी *i915, क्रमागत phy phy)
अणु
	/*
	 * Some platक्रमms only expect PHY_MISC to be programmed क्रम PHY-A and
	 * PHY-B and may not even have instances of the रेजिस्टर क्रम the
	 * other combo PHY's.
	 *
	 * ADL-S technically has three instances of PHY_MISC, but only requires
	 * that we program it क्रम PHY A.
	 */

	अगर (IS_ALDERLAKE_S(i915))
		वापस phy == PHY_A;
	अन्यथा अगर (IS_JSL_EHL(i915) ||
		 IS_ROCKETLAKE(i915) ||
		 IS_DG1(i915))
		वापस phy < PHY_C;

	वापस true;
पूर्ण

अटल bool icl_combo_phy_enabled(काष्ठा drm_i915_निजी *dev_priv,
				  क्रमागत phy phy)
अणु
	/* The PHY C added by EHL has no PHY_MISC रेजिस्टर */
	अगर (!has_phy_misc(dev_priv, phy))
		वापस पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW0(phy)) & COMP_INIT;
	अन्यथा
		वापस !(पूर्णांकel_de_पढ़ो(dev_priv, ICL_PHY_MISC(phy)) &
			 ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN) &&
			(पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW0(phy)) & COMP_INIT);
पूर्ण

अटल bool ehl_vbt_ddi_d_present(काष्ठा drm_i915_निजी *i915)
अणु
	bool ddi_a_present = पूर्णांकel_bios_is_port_present(i915, PORT_A);
	bool ddi_d_present = पूर्णांकel_bios_is_port_present(i915, PORT_D);
	bool dsi_present = पूर्णांकel_bios_is_dsi_present(i915, शून्य);

	/*
	 * VBT's 'dvo port' field क्रम child devices references the DDI, not
	 * the PHY.  So अगर combo PHY A is wired up to drive an बाह्यal
	 * display, we should see a child device present on PORT_D and
	 * nothing on PORT_A and no DSI.
	 */
	अगर (ddi_d_present && !ddi_a_present && !dsi_present)
		वापस true;

	/*
	 * If we encounter a VBT that claims to have an बाह्यal display on
	 * DDI-D _and_ an पूर्णांकernal display on DDI-A/DSI leave an error message
	 * in the log and let the पूर्णांकernal display win.
	 */
	अगर (ddi_d_present)
		drm_err(&i915->drm,
			"VBT claims to have both internal and external displays on PHY A.  Configuring for internal.\n");

	वापस false;
पूर्ण

अटल bool phy_is_master(काष्ठा drm_i915_निजी *dev_priv, क्रमागत phy phy)
अणु
	/*
	 * Certain PHYs are connected to compensation resistors and act
	 * as masters to other PHYs.
	 *
	 * ICL,TGL:
	 *   A(master) -> B(slave), C(slave)
	 * RKL,DG1:
	 *   A(master) -> B(slave)
	 *   C(master) -> D(slave)
	 * ADL-S:
	 *   A(master) -> B(slave), C(slave)
	 *   D(master) -> E(slave)
	 *
	 * We must set the IREFGEN bit क्रम any PHY acting as a master
	 * to another PHY.
	 */
	अगर (phy == PHY_A)
		वापस true;
	अन्यथा अगर (IS_ALDERLAKE_S(dev_priv))
		वापस phy == PHY_D;
	अन्यथा अगर (IS_DG1(dev_priv) || IS_ROCKETLAKE(dev_priv))
		वापस phy == PHY_C;

	वापस false;
पूर्ण

अटल bool icl_combo_phy_verअगरy_state(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत phy phy)
अणु
	bool ret = true;
	u32 expected_val = 0;

	अगर (!icl_combo_phy_enabled(dev_priv, phy))
		वापस false;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		ret &= check_phy_reg(dev_priv, phy, ICL_PORT_TX_DW8_LN0(phy),
				     ICL_PORT_TX_DW8_ODCC_CLK_SEL |
				     ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_MASK,
				     ICL_PORT_TX_DW8_ODCC_CLK_SEL |
				     ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_DIV2);

		ret &= check_phy_reg(dev_priv, phy, ICL_PORT_PCS_DW1_LN0(phy),
				     DCC_MODE_SELECT_MASK,
				     DCC_MODE_SELECT_CONTINUOSLY);
	पूर्ण

	ret &= cnl_verअगरy_procmon_ref_values(dev_priv, phy);

	अगर (phy_is_master(dev_priv, phy)) अणु
		ret &= check_phy_reg(dev_priv, phy, ICL_PORT_COMP_DW8(phy),
				     IREFGEN, IREFGEN);

		अगर (IS_JSL_EHL(dev_priv)) अणु
			अगर (ehl_vbt_ddi_d_present(dev_priv))
				expected_val = ICL_PHY_MISC_MUX_DDID;

			ret &= check_phy_reg(dev_priv, phy, ICL_PHY_MISC(phy),
					     ICL_PHY_MISC_MUX_DDID,
					     expected_val);
		पूर्ण
	पूर्ण

	ret &= check_phy_reg(dev_priv, phy, ICL_PORT_CL_DW5(phy),
			     CL_POWER_DOWN_ENABLE, CL_POWER_DOWN_ENABLE);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_combo_phy_घातer_up_lanes(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत phy phy, bool is_dsi,
				    पूर्णांक lane_count, bool lane_reversal)
अणु
	u8 lane_mask;
	u32 val;

	अगर (is_dsi) अणु
		drm_WARN_ON(&dev_priv->drm, lane_reversal);

		चयन (lane_count) अणु
		हाल 1:
			lane_mask = PWR_DOWN_LN_3_1_0;
			अवरोध;
		हाल 2:
			lane_mask = PWR_DOWN_LN_3_1;
			अवरोध;
		हाल 3:
			lane_mask = PWR_DOWN_LN_3;
			अवरोध;
		शेष:
			MISSING_CASE(lane_count);
			fallthrough;
		हाल 4:
			lane_mask = PWR_UP_ALL_LANES;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (lane_count) अणु
		हाल 1:
			lane_mask = lane_reversal ? PWR_DOWN_LN_2_1_0 :
						    PWR_DOWN_LN_3_2_1;
			अवरोध;
		हाल 2:
			lane_mask = lane_reversal ? PWR_DOWN_LN_1_0 :
						    PWR_DOWN_LN_3_2;
			अवरोध;
		शेष:
			MISSING_CASE(lane_count);
			fallthrough;
		हाल 4:
			lane_mask = PWR_UP_ALL_LANES;
			अवरोध;
		पूर्ण
	पूर्ण

	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_CL_DW10(phy));
	val &= ~PWR_DOWN_LN_MASK;
	val |= lane_mask << PWR_DOWN_LN_SHIFT;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_CL_DW10(phy), val);
पूर्ण

अटल व्योम icl_combo_phys_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत phy phy;

	क्रम_each_combo_phy(dev_priv, phy) अणु
		u32 val;

		अगर (icl_combo_phy_verअगरy_state(dev_priv, phy)) अणु
			drm_dbg(&dev_priv->drm,
				"Combo PHY %c already enabled, won't reprogram it.\n",
				phy_name(phy));
			जारी;
		पूर्ण

		अगर (!has_phy_misc(dev_priv, phy))
			जाओ skip_phy_misc;

		/*
		 * EHL's combo PHY A can be hooked up to either an बाह्यal
		 * display (via DDI-D) or an पूर्णांकernal display (via DDI-A or
		 * the DSI DPHY).  This is a motherboard design decision that
		 * can't be changed on the fly, so initialize the PHY's mux
		 * based on whether our VBT indicates the presence of any
		 * "internal" child devices.
		 */
		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PHY_MISC(phy));
		अगर (IS_JSL_EHL(dev_priv) && phy == PHY_A) अणु
			val &= ~ICL_PHY_MISC_MUX_DDID;

			अगर (ehl_vbt_ddi_d_present(dev_priv))
				val |= ICL_PHY_MISC_MUX_DDID;
		पूर्ण

		val &= ~ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PHY_MISC(phy), val);

skip_phy_misc:
		अगर (DISPLAY_VER(dev_priv) >= 12) अणु
			val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW8_LN0(phy));
			val &= ~ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_MASK;
			val |= ICL_PORT_TX_DW8_ODCC_CLK_SEL;
			val |= ICL_PORT_TX_DW8_ODCC_CLK_DIV_SEL_DIV2;
			पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW8_GRP(phy), val);

			val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_PCS_DW1_LN0(phy));
			val &= ~DCC_MODE_SELECT_MASK;
			val |= DCC_MODE_SELECT_CONTINUOSLY;
			पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_PCS_DW1_GRP(phy), val);
		पूर्ण

		cnl_set_procmon_ref_values(dev_priv, phy);

		अगर (phy_is_master(dev_priv, phy)) अणु
			val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW8(phy));
			val |= IREFGEN;
			पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_COMP_DW8(phy), val);
		पूर्ण

		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW0(phy));
		val |= COMP_INIT;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_COMP_DW0(phy), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_CL_DW5(phy));
		val |= CL_POWER_DOWN_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_CL_DW5(phy), val);
	पूर्ण
पूर्ण

अटल व्योम icl_combo_phys_uninit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	क्रमागत phy phy;

	क्रम_each_combo_phy_reverse(dev_priv, phy) अणु
		u32 val;

		अगर (phy == PHY_A &&
		    !icl_combo_phy_verअगरy_state(dev_priv, phy)) अणु
			अगर (IS_TIGERLAKE(dev_priv) || IS_DG1(dev_priv)) अणु
				/*
				 * A known problem with old अगरwi:
				 * https://gitlab.मुक्तdesktop.org/drm/पूर्णांकel/-/issues/2411
				 * Suppress the warning क्रम CI. Remove ASAP!
				 */
				drm_dbg_kms(&dev_priv->drm,
					    "Combo PHY %c HW state changed unexpectedly\n",
					    phy_name(phy));
			पूर्ण अन्यथा अणु
				drm_warn(&dev_priv->drm,
					 "Combo PHY %c HW state changed unexpectedly\n",
					 phy_name(phy));
			पूर्ण
		पूर्ण

		अगर (!has_phy_misc(dev_priv, phy))
			जाओ skip_phy_misc;

		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PHY_MISC(phy));
		val |= ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PHY_MISC(phy), val);

skip_phy_misc:
		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_COMP_DW0(phy));
		val &= ~COMP_INIT;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_COMP_DW0(phy), val);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_combo_phy_init(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11)
		icl_combo_phys_init(i915);
	अन्यथा अगर (IS_CANNONLAKE(i915))
		cnl_combo_phys_init(i915);
पूर्ण

व्योम पूर्णांकel_combo_phy_uninit(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (DISPLAY_VER(i915) >= 11)
		icl_combo_phys_uninit(i915);
	अन्यथा अगर (IS_CANNONLAKE(i915))
		cnl_combo_phys_uninit(i915);
पूर्ण
