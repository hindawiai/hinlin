<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश "fm10k.h"

/**
 * fm10k_dcbnl_ieee_getets - get the ETS configuration क्रम the device
 * @dev: netdev पूर्णांकerface क्रम the device
 * @ets: ETS काष्ठाure to push configuration to
 **/
अटल पूर्णांक fm10k_dcbnl_ieee_getets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	पूर्णांक i;

	/* we support 8 TCs in all modes */
	ets->ets_cap = IEEE_8021QAZ_MAX_TCS;
	ets->cbs = 0;

	/* we only support strict priority and cannot करो traffic shaping */
	स_रखो(ets->tc_tx_bw, 0, माप(ets->tc_tx_bw));
	स_रखो(ets->tc_rx_bw, 0, माप(ets->tc_rx_bw));
	स_रखो(ets->tc_tsa, IEEE_8021QAZ_TSA_STRICT, माप(ets->tc_tsa));

	/* populate the prio map based on the netdev */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		ets->prio_tc[i] = netdev_get_prio_tc_map(dev, i);

	वापस 0;
पूर्ण

/**
 * fm10k_dcbnl_ieee_setets - set the ETS configuration क्रम the device
 * @dev: netdev पूर्णांकerface क्रम the device
 * @ets: ETS काष्ठाure to pull configuration from
 **/
अटल पूर्णांक fm10k_dcbnl_ieee_setets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	u8 num_tc = 0;
	पूर्णांक i;

	/* verअगरy type and determine num_tcs needed */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (ets->tc_tx_bw[i] || ets->tc_rx_bw[i])
			वापस -EINVAL;
		अगर (ets->tc_tsa[i] != IEEE_8021QAZ_TSA_STRICT)
			वापस -EINVAL;
		अगर (ets->prio_tc[i] > num_tc)
			num_tc = ets->prio_tc[i];
	पूर्ण

	/* अगर requested TC is greater than 0 then num_tcs is max + 1 */
	अगर (num_tc)
		num_tc++;

	अगर (num_tc > IEEE_8021QAZ_MAX_TCS)
		वापस -EINVAL;

	/* update TC hardware mapping अगर necessary */
	अगर (num_tc != netdev_get_num_tc(dev)) अणु
		पूर्णांक err = fm10k_setup_tc(dev, num_tc);
		अगर (err)
			वापस err;
	पूर्ण

	/* update priority mapping */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		netdev_set_prio_tc_map(dev, i, ets->prio_tc[i]);

	वापस 0;
पूर्ण

/**
 * fm10k_dcbnl_ieee_getpfc - get the PFC configuration क्रम the device
 * @dev: netdev पूर्णांकerface क्रम the device
 * @pfc: PFC काष्ठाure to push configuration to
 **/
अटल पूर्णांक fm10k_dcbnl_ieee_getpfc(काष्ठा net_device *dev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);

	/* record flow control max count and state of TCs */
	pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;
	pfc->pfc_en = पूर्णांकerface->pfc_en;

	वापस 0;
पूर्ण

/**
 * fm10k_dcbnl_ieee_setpfc - set the PFC configuration क्रम the device
 * @dev: netdev पूर्णांकerface क्रम the device
 * @pfc: PFC काष्ठाure to pull configuration from
 **/
अटल पूर्णांक fm10k_dcbnl_ieee_setpfc(काष्ठा net_device *dev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);

	/* record PFC configuration to पूर्णांकerface */
	पूर्णांकerface->pfc_en = pfc->pfc_en;

	/* अगर we are running update the drop_en state क्रम all queues */
	अगर (netअगर_running(dev))
		fm10k_update_rx_drop_en(पूर्णांकerface);

	वापस 0;
पूर्ण

/**
 * fm10k_dcbnl_getdcbx - get the DCBX configuration क्रम the device
 * @dev: netdev पूर्णांकerface क्रम the device
 *
 * Returns that we support only IEEE DCB क्रम this पूर्णांकerface
 **/
अटल u8 fm10k_dcbnl_getdcbx(काष्ठा net_device __always_unused *dev)
अणु
	वापस DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_IEEE;
पूर्ण

/**
 * fm10k_dcbnl_setdcbx - get the DCBX configuration क्रम the device
 * @dev: netdev पूर्णांकerface क्रम the device
 * @mode: new mode क्रम this device
 *
 * Returns error on attempt to enable anything but IEEE DCB क्रम this पूर्णांकerface
 **/
अटल u8 fm10k_dcbnl_setdcbx(काष्ठा net_device __always_unused *dev, u8 mode)
अणु
	वापस (mode != (DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_IEEE)) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops fm10k_dcbnl_ops = अणु
	.ieee_getets	= fm10k_dcbnl_ieee_getets,
	.ieee_setets	= fm10k_dcbnl_ieee_setets,
	.ieee_getpfc	= fm10k_dcbnl_ieee_getpfc,
	.ieee_setpfc	= fm10k_dcbnl_ieee_setpfc,

	.getdcbx	= fm10k_dcbnl_getdcbx,
	.setdcbx	= fm10k_dcbnl_setdcbx,
पूर्ण;

/**
 * fm10k_dcbnl_set_ops - Configures dcbnl ops poपूर्णांकer क्रम netdev
 * @dev: netdev पूर्णांकerface क्रम the device
 *
 * Enables PF क्रम DCB by assigning DCBNL ops poपूर्णांकer.
 **/
व्योम fm10k_dcbnl_set_ops(काष्ठा net_device *dev)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(dev);
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

	अगर (hw->mac.type == fm10k_mac_pf)
		dev->dcbnl_ops = &fm10k_dcbnl_ops;
पूर्ण
