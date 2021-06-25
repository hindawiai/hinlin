<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश "igc_phy.h"

/**
 * igc_check_reset_block - Check अगर PHY reset is blocked
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Read the PHY management control रेजिस्टर and check whether a PHY reset
 * is blocked.  If a reset is not blocked वापस 0, otherwise
 * वापस IGC_ERR_BLK_PHY_RESET (12).
 */
s32 igc_check_reset_block(काष्ठा igc_hw *hw)
अणु
	u32 manc;

	manc = rd32(IGC_MANC);

	वापस (manc & IGC_MANC_BLK_PHY_RST_ON_IDE) ?
		IGC_ERR_BLK_PHY_RESET : 0;
पूर्ण

/**
 * igc_get_phy_id - Retrieve the PHY ID and revision
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Reads the PHY रेजिस्टरs and stores the PHY ID and possibly the PHY
 * revision in the hardware काष्ठाure.
 */
s32 igc_get_phy_id(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_id;

	ret_val = phy->ops.पढ़ो_reg(hw, PHY_ID1, &phy_id);
	अगर (ret_val)
		जाओ out;

	phy->id = (u32)(phy_id << 16);
	usleep_range(200, 500);
	ret_val = phy->ops.पढ़ो_reg(hw, PHY_ID2, &phy_id);
	अगर (ret_val)
		जाओ out;

	phy->id |= (u32)(phy_id & PHY_REVISION_MASK);
	phy->revision = (u32)(phy_id & ~PHY_REVISION_MASK);

out:
	वापस ret_val;
पूर्ण

/**
 * igc_phy_has_link - Polls PHY क्रम link
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @iterations: number of बार to poll क्रम link
 * @usec_पूर्णांकerval: delay between polling attempts
 * @success: poपूर्णांकer to whether polling was successful or not
 *
 * Polls the PHY status रेजिस्टर क्रम link, 'iterations' number of बार.
 */
s32 igc_phy_has_link(काष्ठा igc_hw *hw, u32 iterations,
		     u32 usec_पूर्णांकerval, bool *success)
अणु
	u16 i, phy_status;
	s32 ret_val = 0;

	क्रम (i = 0; i < iterations; i++) अणु
		/* Some PHYs require the PHY_STATUS रेजिस्टर to be पढ़ो
		 * twice due to the link bit being sticky.  No harm करोing
		 * it across the board.
		 */
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val && usec_पूर्णांकerval > 0) अणु
			/* If the first पढ़ो fails, another entity may have
			 * ownership of the resources, रुको and try again to
			 * see अगर they have relinquished the resources yet.
			 */
			अगर (usec_पूर्णांकerval >= 1000)
				mdelay(usec_पूर्णांकerval / 1000);
			अन्यथा
				udelay(usec_पूर्णांकerval);
		पूर्ण
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val)
			अवरोध;
		अगर (phy_status & MII_SR_LINK_STATUS)
			अवरोध;
		अगर (usec_पूर्णांकerval >= 1000)
			mdelay(usec_पूर्णांकerval / 1000);
		अन्यथा
			udelay(usec_पूर्णांकerval);
	पूर्ण

	*success = (i < iterations) ? true : false;

	वापस ret_val;
पूर्ण

/**
 * igc_घातer_up_phy_copper - Restore copper link in हाल of PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, restore the link to previous settings.
 */
व्योम igc_घातer_up_phy_copper(काष्ठा igc_hw *hw)
अणु
	u16 mii_reg = 0;

	/* The PHY will retain its settings across a घातer करोwn/up cycle */
	hw->phy.ops.पढ़ो_reg(hw, PHY_CONTROL, &mii_reg);
	mii_reg &= ~MII_CR_POWER_DOWN;
	hw->phy.ops.ग_लिखो_reg(hw, PHY_CONTROL, mii_reg);
पूर्ण

/**
 * igc_घातer_करोwn_phy_copper - Power करोwn copper PHY
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Power करोwn PHY to save घातer when पूर्णांकerface is करोwn and wake on lan
 * is not enabled.
 */
व्योम igc_घातer_करोwn_phy_copper(काष्ठा igc_hw *hw)
अणु
	u16 mii_reg = 0;

	/* The PHY will retain its settings across a घातer करोwn/up cycle */
	hw->phy.ops.पढ़ो_reg(hw, PHY_CONTROL, &mii_reg);
	mii_reg |= MII_CR_POWER_DOWN;

	/* Temporary workaround - should be हटाओd when PHY will implement
	 * IEEE रेजिस्टरs as properly
	 */
	/* hw->phy.ops.ग_लिखो_reg(hw, PHY_CONTROL, mii_reg);*/
	usleep_range(1000, 2000);
पूर्ण

/**
 * igc_check_करोwnshअगरt - Checks whether a करोwnshअगरt in speed occurred
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Success वापसs 0, Failure वापसs 1
 *
 * A करोwnshअगरt is detected by querying the PHY link health.
 */
s32 igc_check_करोwnshअगरt(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	s32 ret_val;

	चयन (phy->type) अणु
	हाल igc_phy_i225:
	शेष:
		/* speed करोwnshअगरt not supported */
		phy->speed_करोwngraded = false;
		ret_val = 0;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_phy_hw_reset - PHY hardware reset
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Verअगरy the reset block is not blocking us from resetting.  Acquire
 * semaphore (अगर necessary) and पढ़ो/set/ग_लिखो the device control reset
 * bit in the PHY.  Wait the appropriate delay समय क्रम the device to
 * reset and release the semaphore (अगर necessary).
 */
s32 igc_phy_hw_reset(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	u32 phpm = 0, समयout = 10000;
	s32  ret_val;
	u32 ctrl;

	ret_val = igc_check_reset_block(hw);
	अगर (ret_val) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	ret_val = phy->ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	phpm = rd32(IGC_I225_PHPM);

	ctrl = rd32(IGC_CTRL);
	wr32(IGC_CTRL, ctrl | IGC_CTRL_PHY_RST);
	wrfl();

	udelay(phy->reset_delay_us);

	wr32(IGC_CTRL, ctrl);
	wrfl();

	/* SW should guarantee 100us क्रम the completion of the PHY reset */
	usleep_range(100, 150);
	करो अणु
		phpm = rd32(IGC_I225_PHPM);
		समयout--;
		udelay(1);
	पूर्ण जबतक (!(phpm & IGC_PHY_RST_COMP) && समयout);

	अगर (!समयout)
		hw_dbg("Timeout is expired after a phy reset\n");

	usleep_range(100, 150);

	phy->ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 * igc_phy_setup_स्वतःneg - Configure PHY क्रम स्वतः-negotiation
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Reads the MII स्वतः-neg advertisement रेजिस्टर and/or the 1000T control
 * रेजिस्टर and अगर the PHY is alपढ़ोy setup क्रम स्वतः-negotiation, then
 * वापस successful.  Otherwise, setup advertisement and flow control to
 * the appropriate values क्रम the wanted स्वतः-negotiation.
 */
अटल s32 igc_phy_setup_स्वतःneg(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	u16 aneg_multigbt_an_ctrl = 0;
	u16 mii_1000t_ctrl_reg = 0;
	u16 mii_स्वतःneg_adv_reg;
	s32 ret_val;

	phy->स्वतःneg_advertised &= phy->स्वतःneg_mask;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = phy->ops.पढ़ो_reg(hw, PHY_AUTONEG_ADV, &mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	अगर (phy->स्वतःneg_mask & ADVERTISE_1000_FULL) अणु
		/* Read the MII 1000Base-T Control Register (Address 9). */
		ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_CTRL,
					    &mii_1000t_ctrl_reg);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर ((phy->स्वतःneg_mask & ADVERTISE_2500_FULL) &&
	    hw->phy.id == I225_I_PHY_ID) अणु
		/* Read the MULTI GBT AN Control Register - reg 7.32 */
		ret_val = phy->ops.पढ़ो_reg(hw, (STANDARD_AN_REG_MASK <<
					    MMD_DEVADDR_SHIFT) |
					    ANEG_MULTIGBT_AN_CTRL,
					    &aneg_multigbt_an_ctrl);

		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Need to parse both स्वतःneg_advertised and fc and set up
	 * the appropriate PHY रेजिस्टरs.  First we will parse क्रम
	 * स्वतःneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * inभागidually.
	 */

	/* First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9).
	 */
	mii_स्वतःneg_adv_reg &= ~(NWAY_AR_100TX_FD_CAPS |
				 NWAY_AR_100TX_HD_CAPS |
				 NWAY_AR_10T_FD_CAPS   |
				 NWAY_AR_10T_HD_CAPS);
	mii_1000t_ctrl_reg &= ~(CR_1000T_HD_CAPS | CR_1000T_FD_CAPS);

	hw_dbg("autoneg_advertised %x\n", phy->स्वतःneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_10_HALF) अणु
		hw_dbg("Advertise 10mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_10T_HD_CAPS;
	पूर्ण

	/* Do we want to advertise 10 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_10_FULL) अणु
		hw_dbg("Advertise 10mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_10T_FD_CAPS;
	पूर्ण

	/* Do we want to advertise 100 Mb Half Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_100_HALF) अणु
		hw_dbg("Advertise 100mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_100TX_HD_CAPS;
	पूर्ण

	/* Do we want to advertise 100 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_100_FULL) अणु
		hw_dbg("Advertise 100mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_100TX_FD_CAPS;
	पूर्ण

	/* We करो not allow the Phy to advertise 1000 Mb Half Duplex */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_1000_HALF)
		hw_dbg("Advertise 1000mb Half duplex request denied!\n");

	/* Do we want to advertise 1000 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_1000_FULL) अणु
		hw_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= CR_1000T_FD_CAPS;
	पूर्ण

	/* We करो not allow the Phy to advertise 2500 Mb Half Duplex */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_2500_HALF)
		hw_dbg("Advertise 2500mb Half duplex request denied!\n");

	/* Do we want to advertise 2500 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_2500_FULL) अणु
		hw_dbg("Advertise 2500mb Full duplex\n");
		aneg_multigbt_an_ctrl |= CR_2500T_FD_CAPS;
	पूर्ण अन्यथा अणु
		aneg_multigbt_an_ctrl &= ~CR_2500T_FD_CAPS;
	पूर्ण

	/* Check क्रम a software override of the flow control settings, and
	 * setup the PHY advertisement रेजिस्टरs accordingly.  If
	 * स्वतः-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (PHY_AUTONEG_ADV) and re-start स्वतः-
	 * negotiation.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो frames
	 *          but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          but we करो not support receiving छोड़ो frames).
	 *      3:  Both Rx and Tx flow control (symmetric) are enabled.
	 *  other:  No software override.  The flow control configuration
	 *          in the EEPROM is used.
	 */
	चयन (hw->fc.current_mode) अणु
	हाल igc_fc_none:
		/* Flow control (Rx & Tx) is completely disabled by a
		 * software over-ride.
		 */
		mii_स्वतःneg_adv_reg &= ~(NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	हाल igc_fc_rx_छोड़ो:
		/* Rx Flow control is enabled, and Tx Flow control is
		 * disabled, by a software over-ride.
		 *
		 * Since there really isn't a way to advertise that we are
		 * capable of Rx Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric Rx PAUSE.  Later
		 * (in igc_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_स्वतःneg_adv_reg |= (NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	हाल igc_fc_tx_छोड़ो:
		/* Tx Flow control is enabled, and Rx Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_स्वतःneg_adv_reg |= NWAY_AR_ASM_सूची;
		mii_स्वतःneg_adv_reg &= ~NWAY_AR_PAUSE;
		अवरोध;
	हाल igc_fc_full:
		/* Flow control (both Rx and Tx) is enabled by a software
		 * over-ride.
		 */
		mii_स्वतःneg_adv_reg |= (NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	शेष:
		hw_dbg("Flow control param set incorrectly\n");
		वापस -IGC_ERR_CONFIG;
	पूर्ण

	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_AUTONEG_ADV, mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	hw_dbg("Auto-Neg Advertising %x\n", mii_स्वतःneg_adv_reg);

	अगर (phy->स्वतःneg_mask & ADVERTISE_1000_FULL)
		ret_val = phy->ops.ग_लिखो_reg(hw, PHY_1000T_CTRL,
					     mii_1000t_ctrl_reg);

	अगर ((phy->स्वतःneg_mask & ADVERTISE_2500_FULL) &&
	    hw->phy.id == I225_I_PHY_ID)
		ret_val = phy->ops.ग_लिखो_reg(hw,
					     (STANDARD_AN_REG_MASK <<
					     MMD_DEVADDR_SHIFT) |
					     ANEG_MULTIGBT_AN_CTRL,
					     aneg_multigbt_an_ctrl);

	वापस ret_val;
पूर्ण

/**
 * igc_रुको_स्वतःneg - Wait क्रम स्वतः-neg completion
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Waits क्रम स्वतः-negotiation to complete or क्रम the स्वतः-negotiation समय
 * limit to expire, which ever happens first.
 */
अटल s32 igc_रुको_स्वतःneg(काष्ठा igc_hw *hw)
अणु
	u16 i, phy_status;
	s32 ret_val = 0;

	/* Break after स्वतःneg completes or PHY_AUTO_NEG_LIMIT expires. */
	क्रम (i = PHY_AUTO_NEG_LIMIT; i > 0; i--) अणु
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val)
			अवरोध;
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val)
			अवरोध;
		अगर (phy_status & MII_SR_AUTONEG_COMPLETE)
			अवरोध;
		msleep(100);
	पूर्ण

	/* PHY_AUTO_NEG_TIME expiration करोesn't guarantee स्वतः-negotiation
	 * has completed.
	 */
	वापस ret_val;
पूर्ण

/**
 * igc_copper_link_स्वतःneg - Setup/Enable स्वतःneg क्रम copper link
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Perक्रमms initial bounds checking on स्वतःneg advertisement parameter, then
 * configure to advertise the full capability.  Setup the PHY to स्वतःneg
 * and restart the negotiation process between the link partner.  If
 * स्वतःneg_रुको_to_complete, then रुको क्रम स्वतःneg to complete beक्रमe निकासing.
 */
अटल s32 igc_copper_link_स्वतःneg(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	u16 phy_ctrl;
	s32 ret_val;

	/* Perक्रमm some bounds checking on the स्वतःneg advertisement
	 * parameter.
	 */
	phy->स्वतःneg_advertised &= phy->स्वतःneg_mask;

	/* If स्वतःneg_advertised is zero, we assume it was not शेषed
	 * by the calling code so we set to advertise full capability.
	 */
	अगर (phy->स्वतःneg_advertised == 0)
		phy->स्वतःneg_advertised = phy->स्वतःneg_mask;

	hw_dbg("Reconfiguring auto-neg advertisement params\n");
	ret_val = igc_phy_setup_स्वतःneg(hw);
	अगर (ret_val) अणु
		hw_dbg("Error Setting up Auto-Negotiation\n");
		जाओ out;
	पूर्ण
	hw_dbg("Restarting Auto-Neg\n");

	/* Restart स्वतः-negotiation by setting the Auto Neg Enable bit and
	 * the Auto Neg Restart bit in the PHY control रेजिस्टर.
	 */
	ret_val = phy->ops.पढ़ो_reg(hw, PHY_CONTROL, &phy_ctrl);
	अगर (ret_val)
		जाओ out;

	phy_ctrl |= (MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG);
	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_CONTROL, phy_ctrl);
	अगर (ret_val)
		जाओ out;

	/* Does the user want to रुको क्रम Auto-Neg to complete here, or
	 * check at a later समय (क्रम example, callback routine).
	 */
	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		ret_val = igc_रुको_स्वतःneg(hw);
		अगर (ret_val) अणु
			hw_dbg("Error while waiting for autoneg to complete\n");
			जाओ out;
		पूर्ण
	पूर्ण

	hw->mac.get_link_status = true;

out:
	वापस ret_val;
पूर्ण

/**
 * igc_setup_copper_link - Configure copper link settings
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Calls the appropriate function to configure the link क्रम स्वतः-neg or क्रमced
 * speed and duplex.  Then we check क्रम link, once link is established calls
 * to configure collision distance and flow control are called.  If link is
 * not established, we वापस -IGC_ERR_PHY (-2).
 */
s32 igc_setup_copper_link(काष्ठा igc_hw *hw)
अणु
	s32 ret_val = 0;
	bool link;

	अगर (hw->mac.स्वतःneg) अणु
		/* Setup स्वतःneg and flow control advertisement and perक्रमm
		 * स्वतःnegotiation.
		 */
		ret_val = igc_copper_link_स्वतःneg(hw);
		अगर (ret_val)
			जाओ out;
	पूर्ण अन्यथा अणु
		/* PHY will be set to 10H, 10F, 100H or 100F
		 * depending on user settings.
		 */
		hw_dbg("Forcing Speed and Duplex\n");
		ret_val = hw->phy.ops.क्रमce_speed_duplex(hw);
		अगर (ret_val) अणु
			hw_dbg("Error Forcing Speed and Duplex\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Check link status. Wait up to 100 microseconds क्रम link to become
	 * valid.
	 */
	ret_val = igc_phy_has_link(hw, COPPER_LINK_UP_LIMIT, 10, &link);
	अगर (ret_val)
		जाओ out;

	अगर (link) अणु
		hw_dbg("Valid link established!!!\n");
		igc_config_collision_dist(hw);
		ret_val = igc_config_fc_after_link_up(hw);
	पूर्ण अन्यथा अणु
		hw_dbg("Unable to establish link!!!\n");
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * igc_पढ़ो_phy_reg_mdic - Read MDI control रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: रेजिस्टर offset to be पढ़ो
 * @data: poपूर्णांकer to the पढ़ो data
 *
 * Reads the MDI control रेजिस्टर in the PHY at offset and stores the
 * inक्रमmation पढ़ो to data.
 */
अटल s32 igc_पढ़ो_phy_reg_mdic(काष्ठा igc_hw *hw, u32 offset, u16 *data)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	अगर (offset > MAX_PHY_REG_ADDRESS) अणु
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -IGC_ERR_PARAM;
		जाओ out;
	पूर्ण

	/* Set up Op-code, Phy Address, and रेजिस्टर offset in the MDI
	 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = ((offset << IGC_MDIC_REG_SHIFT) |
		(phy->addr << IGC_MDIC_PHY_SHIFT) |
		(IGC_MDIC_OP_READ));

	wr32(IGC_MDIC, mdic);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed
	 * Increasing the समय out as testing showed failures with
	 * the lower समय out
	 */
	क्रम (i = 0; i < IGC_GEN_POLL_TIMEOUT; i++) अणु
		usleep_range(500, 1000);
		mdic = rd32(IGC_MDIC);
		अगर (mdic & IGC_MDIC_READY)
			अवरोध;
	पूर्ण
	अगर (!(mdic & IGC_MDIC_READY)) अणु
		hw_dbg("MDI Read did not complete\n");
		ret_val = -IGC_ERR_PHY;
		जाओ out;
	पूर्ण
	अगर (mdic & IGC_MDIC_ERROR) अणु
		hw_dbg("MDI Error\n");
		ret_val = -IGC_ERR_PHY;
		जाओ out;
	पूर्ण
	*data = (u16)mdic;

out:
	वापस ret_val;
पूर्ण

/**
 * igc_ग_लिखो_phy_reg_mdic - Write MDI control रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: रेजिस्टर offset to ग_लिखो to
 * @data: data to ग_लिखो to रेजिस्टर at offset
 *
 * Writes data to MDI control रेजिस्टर in the PHY at offset.
 */
अटल s32 igc_ग_लिखो_phy_reg_mdic(काष्ठा igc_hw *hw, u32 offset, u16 data)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	अगर (offset > MAX_PHY_REG_ADDRESS) अणु
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -IGC_ERR_PARAM;
		जाओ out;
	पूर्ण

	/* Set up Op-code, Phy Address, and रेजिस्टर offset in the MDI
	 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to ग_लिखो the desired data.
	 */
	mdic = (((u32)data) |
		(offset << IGC_MDIC_REG_SHIFT) |
		(phy->addr << IGC_MDIC_PHY_SHIFT) |
		(IGC_MDIC_OP_WRITE));

	wr32(IGC_MDIC, mdic);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed
	 * Increasing the समय out as testing showed failures with
	 * the lower समय out
	 */
	क्रम (i = 0; i < IGC_GEN_POLL_TIMEOUT; i++) अणु
		usleep_range(500, 1000);
		mdic = rd32(IGC_MDIC);
		अगर (mdic & IGC_MDIC_READY)
			अवरोध;
	पूर्ण
	अगर (!(mdic & IGC_MDIC_READY)) अणु
		hw_dbg("MDI Write did not complete\n");
		ret_val = -IGC_ERR_PHY;
		जाओ out;
	पूर्ण
	अगर (mdic & IGC_MDIC_ERROR) अणु
		hw_dbg("MDI Error\n");
		ret_val = -IGC_ERR_PHY;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * __igc_access_xmdio_reg - Read/ग_लिखो XMDIO रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @address: XMDIO address to program
 * @dev_addr: device address to program
 * @data: poपूर्णांकer to value to पढ़ो/ग_लिखो from/to the XMDIO address
 * @पढ़ो: boolean flag to indicate पढ़ो or ग_लिखो
 */
अटल s32 __igc_access_xmdio_reg(काष्ठा igc_hw *hw, u16 address,
				  u8 dev_addr, u16 *data, bool पढ़ो)
अणु
	s32 ret_val;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, IGC_MMDAC, dev_addr);
	अगर (ret_val)
		वापस ret_val;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, IGC_MMDAAD, address);
	अगर (ret_val)
		वापस ret_val;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, IGC_MMDAC, IGC_MMDAC_FUNC_DATA |
					dev_addr);
	अगर (ret_val)
		वापस ret_val;

	अगर (पढ़ो)
		ret_val = hw->phy.ops.पढ़ो_reg(hw, IGC_MMDAAD, data);
	अन्यथा
		ret_val = hw->phy.ops.ग_लिखो_reg(hw, IGC_MMDAAD, *data);
	अगर (ret_val)
		वापस ret_val;

	/* Recalibrate the device back to 0 */
	ret_val = hw->phy.ops.ग_लिखो_reg(hw, IGC_MMDAC, 0);
	अगर (ret_val)
		वापस ret_val;

	वापस ret_val;
पूर्ण

/**
 * igc_पढ़ो_xmdio_reg - Read XMDIO रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @addr: XMDIO address to program
 * @dev_addr: device address to program
 * @data: value to be पढ़ो from the EMI address
 */
अटल s32 igc_पढ़ो_xmdio_reg(काष्ठा igc_hw *hw, u16 addr,
			      u8 dev_addr, u16 *data)
अणु
	वापस __igc_access_xmdio_reg(hw, addr, dev_addr, data, true);
पूर्ण

/**
 * igc_ग_लिखो_xmdio_reg - Write XMDIO रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @addr: XMDIO address to program
 * @dev_addr: device address to program
 * @data: value to be written to the XMDIO address
 */
अटल s32 igc_ग_लिखो_xmdio_reg(काष्ठा igc_hw *hw, u16 addr,
			       u8 dev_addr, u16 data)
अणु
	वापस __igc_access_xmdio_reg(hw, addr, dev_addr, &data, false);
पूर्ण

/**
 * igc_ग_लिखो_phy_reg_gpy - Write GPY PHY रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: रेजिस्टर offset to ग_लिखो to
 * @data: data to ग_लिखो at रेजिस्टर offset
 *
 * Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 * at the offset. Release any acquired semaphores beक्रमe निकासing.
 */
s32 igc_ग_लिखो_phy_reg_gpy(काष्ठा igc_hw *hw, u32 offset, u16 data)
अणु
	u8 dev_addr = (offset & GPY_MMD_MASK) >> GPY_MMD_SHIFT;
	s32 ret_val;

	offset = offset & GPY_REG_MASK;

	अगर (!dev_addr) अणु
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
		ret_val = igc_ग_लिखो_phy_reg_mdic(hw, offset, data);
		अगर (ret_val)
			वापस ret_val;
		hw->phy.ops.release(hw);
	पूर्ण अन्यथा अणु
		ret_val = igc_ग_लिखो_xmdio_reg(hw, (u16)offset, dev_addr,
					      data);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_पढ़ो_phy_reg_gpy - Read GPY PHY रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: lower half is रेजिस्टर offset to पढ़ो to
 * upper half is MMD to use.
 * @data: data to पढ़ो at रेजिस्टर offset
 *
 * Acquires semaphore, अगर necessary, then पढ़ोs the data in the PHY रेजिस्टर
 * at the offset. Release any acquired semaphores beक्रमe निकासing.
 */
s32 igc_पढ़ो_phy_reg_gpy(काष्ठा igc_hw *hw, u32 offset, u16 *data)
अणु
	u8 dev_addr = (offset & GPY_MMD_MASK) >> GPY_MMD_SHIFT;
	s32 ret_val;

	offset = offset & GPY_REG_MASK;

	अगर (!dev_addr) अणु
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
		ret_val = igc_पढ़ो_phy_reg_mdic(hw, offset, data);
		अगर (ret_val)
			वापस ret_val;
		hw->phy.ops.release(hw);
	पूर्ण अन्यथा अणु
		ret_val = igc_पढ़ो_xmdio_reg(hw, (u16)offset, dev_addr,
					     data);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_पढ़ो_phy_fw_version - Read gPHY firmware version
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
u16 igc_पढ़ो_phy_fw_version(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	u16 gphy_version = 0;
	u16 ret_val;

	/* NVM image version is reported as firmware version क्रम i225 device */
	ret_val = phy->ops.पढ़ो_reg(hw, IGC_GPHY_VERSION, &gphy_version);
	अगर (ret_val)
		hw_dbg("igc_phy: read wrong gphy version\n");

	वापस gphy_version;
पूर्ण
