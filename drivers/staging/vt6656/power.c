<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: घातer.c
 *
 * Purpose: Handles 802.11 घातer management functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: July 17, 2002
 *
 * Functions:
 *      vnt_enable_घातer_saving - Enable Power Saving Mode
 *      PSvDiasblePowerSaving - Disable Power Saving Mode
 *      vnt_next_tbtt_wakeup - Decide अगर we need to wake up at next Beacon
 *
 * Revision History:
 *
 */

#समावेश "mac.h"
#समावेश "device.h"
#समावेश "power.h"
#समावेश "wcmd.h"
#समावेश "rxtx.h"
#समावेश "card.h"
#समावेश "usbpipe.h"

/*
 *
 * Routine Description:
 * Enable hw घातer saving functions
 *
 * Return Value:
 *    None.
 *
 */

व्योम vnt_enable_घातer_saving(काष्ठा vnt_निजी *priv, u16 listen_पूर्णांकerval)
अणु
	u16 aid = priv->current_aid | BIT(14) | BIT(15);

	/* set period of घातer up beक्रमe TBTT */
	vnt_mac_ग_लिखो_word(priv, MAC_REG_PWBT, C_PWBT);

	अगर (priv->op_mode != NL80211_IFTYPE_ADHOC)
		/* set AID */
		vnt_mac_ग_लिखो_word(priv, MAC_REG_AIDATIM, aid);

	/* Warren:06-18-2004,the sequence must follow
	 * PSEN->AUTOSLEEP->GO2DOZE
	 */
	/* enable घातer saving hw function */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_PSEN);

	/* Set AutoSleep */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);

	/* Warren:MUST turn on this once beक्रमe turn on AUTOSLEEP ,or the
	 * AUTOSLEEP करोesn't work
	 */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_GO2DOZE);

	/* always listen beacon */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_ALBCN);

	dev_dbg(&priv->usb->dev,  "PS:Power Saving Mode Enable...\n");
पूर्ण

पूर्णांक vnt_disable_घातer_saving(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret;

	/* disable घातer saving hw function */
	ret = vnt_control_out(priv, MESSAGE_TYPE_DISABLE_PS, 0,
			      0, 0, शून्य);
	अगर (ret)
		वापस ret;

	/* clear AutoSleep */
	vnt_mac_reg_bits_off(priv, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);

	/* set always listen beacon */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_ALBCN);

	वापस 0;
पूर्ण

/*
 *
 * Routine Description:
 * Check अगर Next TBTT must wake up
 *
 * Return Value:
 *    None.
 *
 */

पूर्णांक vnt_next_tbtt_wakeup(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	पूर्णांक wake_up = false;

	अगर (conf->listen_पूर्णांकerval > 1) अणु
		/* Turn on wake up to listen next beacon */
		vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_LNBCN);
		wake_up = true;
	पूर्ण

	वापस wake_up;
पूर्ण
