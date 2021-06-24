<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: घातer.c
 *
 * Purpose: Handles 802.11 घातer management  functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: July 17, 2002
 *
 * Functions:
 *      PSvEnablePowerSaving - Enable Power Saving Mode
 *      PSvDiasblePowerSaving - Disable Power Saving Mode
 *      PSbConsiderPowerDown - Decide अगर we can Power Down
 *      PSvSendPSPOLL - Send PS-POLL packet
 *      PSbSendNullPacket - Send Null packet
 *      PSbIsNextTBTTWakeUp - Decide अगर we need to wake up at next Beacon
 *
 * Revision History:
 *
 */

#समावेश "mac.h"
#समावेश "device.h"
#समावेश "power.h"
#समावेश "card.h"

/*---------------------  Static Definitions -------------------------*/

/*---------------------  Static Classes  ----------------------------*/

/*---------------------  Static Functions  --------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

/*
 *
 * Routine Description:
 * Enable hw घातer saving functions
 *
 * Return Value:
 *    None.
 *
 */

व्योम PSvEnablePowerSaving(काष्ठा vnt_निजी *priv,
			  अचिन्हित लघु wListenInterval)
अणु
	u16 wAID = priv->current_aid | BIT(14) | BIT(15);

	/* set period of घातer up beक्रमe TBTT */
	VNSvOutPortW(priv->PortOffset + MAC_REG_PWBT, C_PWBT);
	अगर (priv->op_mode != NL80211_IFTYPE_ADHOC) अणु
		/* set AID */
		VNSvOutPortW(priv->PortOffset + MAC_REG_AIDATIM, wAID);
	पूर्ण

	/* Set AutoSleep */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);

	/* Set HWUTSF */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_TFTCTL, TFTCTL_HWUTSF);

	अगर (wListenInterval >= 2) अणु
		/* clear always listen beacon */
		MACvRegBitsOff(priv->PortOffset, MAC_REG_PSCTL, PSCTL_ALBCN);
		/* first समय set listen next beacon */
		MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_LNBCN);
	पूर्ण अन्यथा अणु
		/* always listen beacon */
		MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_ALBCN);
	पूर्ण

	/* enable घातer saving hw function */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_PSEN);
	priv->bEnablePSMode = true;

	priv->bPWBitOn = true;
	pr_debug("PS:Power Saving Mode Enable...\n");
पूर्ण

/*
 *
 * Routine Description:
 * Disable hw घातer saving functions
 *
 * Return Value:
 *    None.
 *
 */

व्योम PSvDisablePowerSaving(काष्ठा vnt_निजी *priv)
अणु
	/* disable घातer saving hw function */
	MACbPSWakeup(priv);

	/* clear AutoSleep */
	MACvRegBitsOff(priv->PortOffset, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);

	/* clear HWUTSF */
	MACvRegBitsOff(priv->PortOffset, MAC_REG_TFTCTL, TFTCTL_HWUTSF);

	/* set always listen beacon */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_PSCTL, PSCTL_ALBCN);

	priv->bEnablePSMode = false;

	priv->bPWBitOn = false;
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

bool PSbIsNextTBTTWakeUp(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	bool wake_up = false;

	अगर (conf->listen_पूर्णांकerval > 1) अणु
		अगर (!priv->wake_up_count)
			priv->wake_up_count = conf->listen_पूर्णांकerval;

		--priv->wake_up_count;

		अगर (priv->wake_up_count == 1) अणु
			/* Turn on wake up to listen next beacon */
			MACvRegBitsOn(priv->PortOffset,
				      MAC_REG_PSCTL, PSCTL_LNBCN);
			wake_up = true;
		पूर्ण
	पूर्ण

	वापस wake_up;
पूर्ण
