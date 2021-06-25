<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "mcdi_port_common.h"
#समावेश "efx_common.h"
#समावेश "nic.h"

पूर्णांक efx_mcdi_get_phy_cfg(काष्ठा efx_nic *efx, काष्ठा efx_mcdi_phy_data *cfg)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_PHY_CFG_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_PHY_CFG_IN_LEN != 0);
	BUILD_BUG_ON(MC_CMD_GET_PHY_CFG_OUT_NAME_LEN != माप(cfg->name));

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_PHY_CFG, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;

	अगर (outlen < MC_CMD_GET_PHY_CFG_OUT_LEN) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	cfg->flags = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_FLAGS);
	cfg->type = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_TYPE);
	cfg->supported_cap =
		MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_SUPPORTED_CAP);
	cfg->channel = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_CHANNEL);
	cfg->port = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_PRT);
	cfg->stats_mask = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_STATS_MASK);
	स_नकल(cfg->name, MCDI_PTR(outbuf, GET_PHY_CFG_OUT_NAME),
	       माप(cfg->name));
	cfg->media = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_MEDIA_TYPE);
	cfg->mmd_mask = MCDI_DWORD(outbuf, GET_PHY_CFG_OUT_MMD_MASK);
	स_नकल(cfg->revision, MCDI_PTR(outbuf, GET_PHY_CFG_OUT_REVISION),
	       माप(cfg->revision));

	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

व्योम efx_link_set_advertising(काष्ठा efx_nic *efx,
			      स्थिर अचिन्हित दीर्घ *advertising)
अणु
	स_नकल(efx->link_advertising, advertising,
	       माप(__ETHTOOL_DECLARE_LINK_MODE_MASK()));

	efx->link_advertising[0] |= ADVERTISED_Autoneg;
	अगर (advertising[0] & ADVERTISED_Pause)
		efx->wanted_fc |= (EFX_FC_TX | EFX_FC_RX);
	अन्यथा
		efx->wanted_fc &= ~(EFX_FC_TX | EFX_FC_RX);
	अगर (advertising[0] & ADVERTISED_Asym_Pause)
		efx->wanted_fc ^= EFX_FC_TX;
पूर्ण

पूर्णांक efx_mcdi_set_link(काष्ठा efx_nic *efx, u32 capabilities,
		      u32 flags, u32 loopback_mode, u32 loopback_speed)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SET_LINK_IN_LEN);
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_SET_LINK_OUT_LEN != 0);

	MCDI_SET_DWORD(inbuf, SET_LINK_IN_CAP, capabilities);
	MCDI_SET_DWORD(inbuf, SET_LINK_IN_FLAGS, flags);
	MCDI_SET_DWORD(inbuf, SET_LINK_IN_LOOPBACK_MODE, loopback_mode);
	MCDI_SET_DWORD(inbuf, SET_LINK_IN_LOOPBACK_SPEED, loopback_speed);

	rc = efx_mcdi_rpc(efx, MC_CMD_SET_LINK, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_loopback_modes(काष्ठा efx_nic *efx, u64 *loopback_modes)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_LOOPBACK_MODES_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_LOOPBACK_MODES, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		जाओ fail;

	अगर (outlen < (MC_CMD_GET_LOOPBACK_MODES_OUT_SUGGESTED_OFST +
		      MC_CMD_GET_LOOPBACK_MODES_OUT_SUGGESTED_LEN)) अणु
		rc = -EIO;
		जाओ fail;
	पूर्ण

	*loopback_modes = MCDI_QWORD(outbuf, GET_LOOPBACK_MODES_OUT_SUGGESTED);

	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

व्योम mcdi_to_ethtool_linkset(u32 media, u32 cap, अचिन्हित दीर्घ *linkset)
अणु
	#घोषणा SET_BIT(name)	__set_bit(ETHTOOL_LINK_MODE_ ## name ## _BIT, \
					  linkset)

	biपंचांगap_zero(linkset, __ETHTOOL_LINK_MODE_MASK_NBITS);
	चयन (media) अणु
	हाल MC_CMD_MEDIA_KX4:
		SET_BIT(Backplane);
		अगर (cap & (1 << MC_CMD_PHY_CAP_1000FDX_LBN))
			SET_BIT(1000baseKX_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_10000FDX_LBN))
			SET_BIT(10000baseKX4_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_40000FDX_LBN))
			SET_BIT(40000baseKR4_Full);
		अवरोध;

	हाल MC_CMD_MEDIA_XFP:
	हाल MC_CMD_MEDIA_SFP_PLUS:
	हाल MC_CMD_MEDIA_QSFP_PLUS:
		SET_BIT(FIBRE);
		अगर (cap & (1 << MC_CMD_PHY_CAP_1000FDX_LBN))
			SET_BIT(1000baseT_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_10000FDX_LBN))
			SET_BIT(10000baseT_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_40000FDX_LBN))
			SET_BIT(40000baseCR4_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_100000FDX_LBN))
			SET_BIT(100000baseCR4_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_25000FDX_LBN))
			SET_BIT(25000baseCR_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_50000FDX_LBN))
			SET_BIT(50000baseCR2_Full);
		अवरोध;

	हाल MC_CMD_MEDIA_BASE_T:
		SET_BIT(TP);
		अगर (cap & (1 << MC_CMD_PHY_CAP_10HDX_LBN))
			SET_BIT(10baseT_Half);
		अगर (cap & (1 << MC_CMD_PHY_CAP_10FDX_LBN))
			SET_BIT(10baseT_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_100HDX_LBN))
			SET_BIT(100baseT_Half);
		अगर (cap & (1 << MC_CMD_PHY_CAP_100FDX_LBN))
			SET_BIT(100baseT_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_1000HDX_LBN))
			SET_BIT(1000baseT_Half);
		अगर (cap & (1 << MC_CMD_PHY_CAP_1000FDX_LBN))
			SET_BIT(1000baseT_Full);
		अगर (cap & (1 << MC_CMD_PHY_CAP_10000FDX_LBN))
			SET_BIT(10000baseT_Full);
		अवरोध;
	पूर्ण

	अगर (cap & (1 << MC_CMD_PHY_CAP_PAUSE_LBN))
		SET_BIT(Pause);
	अगर (cap & (1 << MC_CMD_PHY_CAP_ASYM_LBN))
		SET_BIT(Asym_Pause);
	अगर (cap & (1 << MC_CMD_PHY_CAP_AN_LBN))
		SET_BIT(Autoneg);

	#अघोषित SET_BIT
पूर्ण

u32 ethtool_linkset_to_mcdi_cap(स्थिर अचिन्हित दीर्घ *linkset)
अणु
	u32 result = 0;

	#घोषणा TEST_BIT(name)	test_bit(ETHTOOL_LINK_MODE_ ## name ## _BIT, \
					 linkset)

	अगर (TEST_BIT(10baseT_Half))
		result |= (1 << MC_CMD_PHY_CAP_10HDX_LBN);
	अगर (TEST_BIT(10baseT_Full))
		result |= (1 << MC_CMD_PHY_CAP_10FDX_LBN);
	अगर (TEST_BIT(100baseT_Half))
		result |= (1 << MC_CMD_PHY_CAP_100HDX_LBN);
	अगर (TEST_BIT(100baseT_Full))
		result |= (1 << MC_CMD_PHY_CAP_100FDX_LBN);
	अगर (TEST_BIT(1000baseT_Half))
		result |= (1 << MC_CMD_PHY_CAP_1000HDX_LBN);
	अगर (TEST_BIT(1000baseT_Full) || TEST_BIT(1000baseKX_Full))
		result |= (1 << MC_CMD_PHY_CAP_1000FDX_LBN);
	अगर (TEST_BIT(10000baseT_Full) || TEST_BIT(10000baseKX4_Full))
		result |= (1 << MC_CMD_PHY_CAP_10000FDX_LBN);
	अगर (TEST_BIT(40000baseCR4_Full) || TEST_BIT(40000baseKR4_Full))
		result |= (1 << MC_CMD_PHY_CAP_40000FDX_LBN);
	अगर (TEST_BIT(100000baseCR4_Full))
		result |= (1 << MC_CMD_PHY_CAP_100000FDX_LBN);
	अगर (TEST_BIT(25000baseCR_Full))
		result |= (1 << MC_CMD_PHY_CAP_25000FDX_LBN);
	अगर (TEST_BIT(50000baseCR2_Full))
		result |= (1 << MC_CMD_PHY_CAP_50000FDX_LBN);
	अगर (TEST_BIT(Pause))
		result |= (1 << MC_CMD_PHY_CAP_PAUSE_LBN);
	अगर (TEST_BIT(Asym_Pause))
		result |= (1 << MC_CMD_PHY_CAP_ASYM_LBN);
	अगर (TEST_BIT(Autoneg))
		result |= (1 << MC_CMD_PHY_CAP_AN_LBN);

	#अघोषित TEST_BIT

	वापस result;
पूर्ण

u32 efx_get_mcdi_phy_flags(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	क्रमागत efx_phy_mode mode, supported;
	u32 flags;

	/* TODO: Advertise the capabilities supported by this PHY */
	supported = 0;
	अगर (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_TXDIS_LBN))
		supported |= PHY_MODE_TX_DISABLED;
	अगर (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_LOWPOWER_LBN))
		supported |= PHY_MODE_LOW_POWER;
	अगर (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_POWEROFF_LBN))
		supported |= PHY_MODE_OFF;

	mode = efx->phy_mode & supported;

	flags = 0;
	अगर (mode & PHY_MODE_TX_DISABLED)
		flags |= (1 << MC_CMD_SET_LINK_IN_TXDIS_LBN);
	अगर (mode & PHY_MODE_LOW_POWER)
		flags |= (1 << MC_CMD_SET_LINK_IN_LOWPOWER_LBN);
	अगर (mode & PHY_MODE_OFF)
		flags |= (1 << MC_CMD_SET_LINK_IN_POWEROFF_LBN);

	वापस flags;
पूर्ण

u8 mcdi_to_ethtool_media(u32 media)
अणु
	चयन (media) अणु
	हाल MC_CMD_MEDIA_XAUI:
	हाल MC_CMD_MEDIA_CX4:
	हाल MC_CMD_MEDIA_KX4:
		वापस PORT_OTHER;

	हाल MC_CMD_MEDIA_XFP:
	हाल MC_CMD_MEDIA_SFP_PLUS:
	हाल MC_CMD_MEDIA_QSFP_PLUS:
		वापस PORT_FIBRE;

	हाल MC_CMD_MEDIA_BASE_T:
		वापस PORT_TP;

	शेष:
		वापस PORT_OTHER;
	पूर्ण
पूर्ण

व्योम efx_mcdi_phy_decode_link(काष्ठा efx_nic *efx,
			      काष्ठा efx_link_state *link_state,
			      u32 speed, u32 flags, u32 fcntl)
अणु
	चयन (fcntl) अणु
	हाल MC_CMD_FCNTL_AUTO:
		WARN_ON(1);	/* This is not a link mode */
		link_state->fc = EFX_FC_AUTO | EFX_FC_TX | EFX_FC_RX;
		अवरोध;
	हाल MC_CMD_FCNTL_BIसूची:
		link_state->fc = EFX_FC_TX | EFX_FC_RX;
		अवरोध;
	हाल MC_CMD_FCNTL_RESPOND:
		link_state->fc = EFX_FC_RX;
		अवरोध;
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल MC_CMD_FCNTL_OFF:
		link_state->fc = 0;
		अवरोध;
	पूर्ण

	link_state->up = !!(flags & (1 << MC_CMD_GET_LINK_OUT_LINK_UP_LBN));
	link_state->fd = !!(flags & (1 << MC_CMD_GET_LINK_OUT_FULL_DUPLEX_LBN));
	link_state->speed = speed;
पूर्ण

/* The semantics of the ethtool FEC mode biपंचांगask are not well defined,
 * particularly the meaning of combinations of bits.  Which means we get to
 * define our own semantics, as follows:
 * OFF overrides any other bits, and means "disable all FEC" (with the
 * exception of 25G KR4/CR4, where it is not possible to reject it अगर AN
 * partner requests it).
 * AUTO on its own means use cable requirements and link partner स्वतःneg with
 * fw-शेष preferences क्रम the cable type.
 * AUTO and either RS or BASER means use the specअगरied FEC type अगर cable and
 * link partner support it, otherwise स्वतःneg/fw-शेष.
 * RS or BASER alone means use the specअगरied FEC type अगर cable and link partner
 * support it and either requests it, otherwise no FEC.
 * Both RS and BASER (whether AUTO or not) means use FEC अगर cable and link
 * partner support it, preferring RS to BASER.
 */
u32 ethtool_fec_caps_to_mcdi(u32 supported_cap, u32 ethtool_cap)
अणु
	u32 ret = 0;

	अगर (ethtool_cap & ETHTOOL_FEC_OFF)
		वापस 0;

	अगर (ethtool_cap & ETHTOOL_FEC_AUTO)
		ret |= ((1 << MC_CMD_PHY_CAP_BASER_FEC_LBN) |
			(1 << MC_CMD_PHY_CAP_25G_BASER_FEC_LBN) |
			(1 << MC_CMD_PHY_CAP_RS_FEC_LBN)) & supported_cap;
	अगर (ethtool_cap & ETHTOOL_FEC_RS &&
	    supported_cap & (1 << MC_CMD_PHY_CAP_RS_FEC_LBN))
		ret |= (1 << MC_CMD_PHY_CAP_RS_FEC_LBN) |
		       (1 << MC_CMD_PHY_CAP_RS_FEC_REQUESTED_LBN);
	अगर (ethtool_cap & ETHTOOL_FEC_BASER) अणु
		अगर (supported_cap & (1 << MC_CMD_PHY_CAP_BASER_FEC_LBN))
			ret |= (1 << MC_CMD_PHY_CAP_BASER_FEC_LBN) |
			       (1 << MC_CMD_PHY_CAP_BASER_FEC_REQUESTED_LBN);
		अगर (supported_cap & (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_LBN))
			ret |= (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_LBN) |
			       (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_REQUESTED_LBN);
	पूर्ण
	वापस ret;
पूर्ण

/* Invert ethtool_fec_caps_to_mcdi.  There are two combinations that function
 * can never produce, (baser xor rs) and neither req; the implementation below
 * maps both of those to AUTO.  This should never matter, and it's not clear
 * what a better mapping would be anyway.
 */
u32 mcdi_fec_caps_to_ethtool(u32 caps, bool is_25g)
अणु
	bool rs = caps & (1 << MC_CMD_PHY_CAP_RS_FEC_LBN),
	     rs_req = caps & (1 << MC_CMD_PHY_CAP_RS_FEC_REQUESTED_LBN),
	     baser = is_25g ? caps & (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_LBN)
			    : caps & (1 << MC_CMD_PHY_CAP_BASER_FEC_LBN),
	     baser_req = is_25g ? caps & (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_REQUESTED_LBN)
				: caps & (1 << MC_CMD_PHY_CAP_BASER_FEC_REQUESTED_LBN);

	अगर (!baser && !rs)
		वापस ETHTOOL_FEC_OFF;
	वापस (rs_req ? ETHTOOL_FEC_RS : 0) |
	       (baser_req ? ETHTOOL_FEC_BASER : 0) |
	       (baser == baser_req && rs == rs_req ? 0 : ETHTOOL_FEC_AUTO);
पूर्ण

/* Verअगरy that the क्रमced flow control settings (!EFX_FC_AUTO) are
 * supported by the link partner. Warn the user अगर this isn't the हाल
 */
व्योम efx_mcdi_phy_check_fcntl(काष्ठा efx_nic *efx, u32 lpa)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 rmtadv;

	/* The link partner capabilities are only relevant अगर the
	 * link supports flow control स्वतःnegotiation
	 */
	अगर (~phy_cfg->supported_cap & (1 << MC_CMD_PHY_CAP_AN_LBN))
		वापस;

	/* If flow control स्वतःneg is supported and enabled, then fine */
	अगर (efx->wanted_fc & EFX_FC_AUTO)
		वापस;

	rmtadv = 0;
	अगर (lpa & (1 << MC_CMD_PHY_CAP_PAUSE_LBN))
		rmtadv |= ADVERTISED_Pause;
	अगर (lpa & (1 << MC_CMD_PHY_CAP_ASYM_LBN))
		rmtadv |=  ADVERTISED_Asym_Pause;

	अगर ((efx->wanted_fc & EFX_FC_TX) && rmtadv == ADVERTISED_Asym_Pause)
		netअगर_err(efx, link, efx->net_dev,
			  "warning: link partner doesn't support pause frames");
पूर्ण

bool efx_mcdi_phy_poll(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_link_state old_state = efx->link_state;
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_LINK_OUT_LEN);
	पूर्णांक rc;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	BUILD_BUG_ON(MC_CMD_GET_LINK_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_LINK, शून्य, 0,
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		efx->link_state.up = false;
	अन्यथा
		efx_mcdi_phy_decode_link(
			efx, &efx->link_state,
			MCDI_DWORD(outbuf, GET_LINK_OUT_LINK_SPEED),
			MCDI_DWORD(outbuf, GET_LINK_OUT_FLAGS),
			MCDI_DWORD(outbuf, GET_LINK_OUT_FCNTL));

	वापस !efx_link_state_equal(&efx->link_state, &old_state);
पूर्ण

पूर्णांक efx_mcdi_phy_probe(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_data;
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_LINK_OUT_LEN);
	u32 caps;
	पूर्णांक rc;

	/* Initialise and populate phy_data */
	phy_data = kzalloc(माप(*phy_data), GFP_KERNEL);
	अगर (phy_data == शून्य)
		वापस -ENOMEM;

	rc = efx_mcdi_get_phy_cfg(efx, phy_data);
	अगर (rc != 0)
		जाओ fail;

	/* Read initial link advertisement */
	BUILD_BUG_ON(MC_CMD_GET_LINK_IN_LEN != 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_GET_LINK, शून्य, 0,
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		जाओ fail;

	/* Fill out nic state */
	efx->phy_data = phy_data;
	efx->phy_type = phy_data->type;

	efx->mdio_bus = phy_data->channel;
	efx->mdio.prtad = phy_data->port;
	efx->mdio.mmds = phy_data->mmd_mask & ~(1 << MC_CMD_MMD_CLAUSE22);
	efx->mdio.mode_support = 0;
	अगर (phy_data->mmd_mask & (1 << MC_CMD_MMD_CLAUSE22))
		efx->mdio.mode_support |= MDIO_SUPPORTS_C22;
	अगर (phy_data->mmd_mask & ~(1 << MC_CMD_MMD_CLAUSE22))
		efx->mdio.mode_support |= MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;

	caps = MCDI_DWORD(outbuf, GET_LINK_OUT_CAP);
	अगर (caps & (1 << MC_CMD_PHY_CAP_AN_LBN))
		mcdi_to_ethtool_linkset(phy_data->media, caps,
					efx->link_advertising);
	अन्यथा
		phy_data->क्रमced_cap = caps;

	/* Assert that we can map efx -> mcdi loopback modes */
	BUILD_BUG_ON(LOOPBACK_NONE != MC_CMD_LOOPBACK_NONE);
	BUILD_BUG_ON(LOOPBACK_DATA != MC_CMD_LOOPBACK_DATA);
	BUILD_BUG_ON(LOOPBACK_GMAC != MC_CMD_LOOPBACK_GMAC);
	BUILD_BUG_ON(LOOPBACK_XGMII != MC_CMD_LOOPBACK_XGMII);
	BUILD_BUG_ON(LOOPBACK_XGXS != MC_CMD_LOOPBACK_XGXS);
	BUILD_BUG_ON(LOOPBACK_XAUI != MC_CMD_LOOPBACK_XAUI);
	BUILD_BUG_ON(LOOPBACK_GMII != MC_CMD_LOOPBACK_GMII);
	BUILD_BUG_ON(LOOPBACK_SGMII != MC_CMD_LOOPBACK_SGMII);
	BUILD_BUG_ON(LOOPBACK_XGBR != MC_CMD_LOOPBACK_XGBR);
	BUILD_BUG_ON(LOOPBACK_XFI != MC_CMD_LOOPBACK_XFI);
	BUILD_BUG_ON(LOOPBACK_XAUI_FAR != MC_CMD_LOOPBACK_XAUI_FAR);
	BUILD_BUG_ON(LOOPBACK_GMII_FAR != MC_CMD_LOOPBACK_GMII_FAR);
	BUILD_BUG_ON(LOOPBACK_SGMII_FAR != MC_CMD_LOOPBACK_SGMII_FAR);
	BUILD_BUG_ON(LOOPBACK_XFI_FAR != MC_CMD_LOOPBACK_XFI_FAR);
	BUILD_BUG_ON(LOOPBACK_GPHY != MC_CMD_LOOPBACK_GPHY);
	BUILD_BUG_ON(LOOPBACK_PHYXS != MC_CMD_LOOPBACK_PHYXS);
	BUILD_BUG_ON(LOOPBACK_PCS != MC_CMD_LOOPBACK_PCS);
	BUILD_BUG_ON(LOOPBACK_PMAPMD != MC_CMD_LOOPBACK_PMAPMD);
	BUILD_BUG_ON(LOOPBACK_XPORT != MC_CMD_LOOPBACK_XPORT);
	BUILD_BUG_ON(LOOPBACK_XGMII_WS != MC_CMD_LOOPBACK_XGMII_WS);
	BUILD_BUG_ON(LOOPBACK_XAUI_WS != MC_CMD_LOOPBACK_XAUI_WS);
	BUILD_BUG_ON(LOOPBACK_XAUI_WS_FAR != MC_CMD_LOOPBACK_XAUI_WS_FAR);
	BUILD_BUG_ON(LOOPBACK_XAUI_WS_NEAR != MC_CMD_LOOPBACK_XAUI_WS_NEAR);
	BUILD_BUG_ON(LOOPBACK_GMII_WS != MC_CMD_LOOPBACK_GMII_WS);
	BUILD_BUG_ON(LOOPBACK_XFI_WS != MC_CMD_LOOPBACK_XFI_WS);
	BUILD_BUG_ON(LOOPBACK_XFI_WS_FAR != MC_CMD_LOOPBACK_XFI_WS_FAR);
	BUILD_BUG_ON(LOOPBACK_PHYXS_WS != MC_CMD_LOOPBACK_PHYXS_WS);

	rc = efx_mcdi_loopback_modes(efx, &efx->loopback_modes);
	अगर (rc != 0)
		जाओ fail;
	/* The MC indicates that LOOPBACK_NONE is a valid loopback mode,
	 * but by convention we करोn't
	 */
	efx->loopback_modes &= ~(1 << LOOPBACK_NONE);

	/* Set the initial link mode */
	efx_mcdi_phy_decode_link(efx, &efx->link_state,
				 MCDI_DWORD(outbuf, GET_LINK_OUT_LINK_SPEED),
				 MCDI_DWORD(outbuf, GET_LINK_OUT_FLAGS),
				 MCDI_DWORD(outbuf, GET_LINK_OUT_FCNTL));

	/* Record the initial FEC configuration (or nearest approximation
	 * representable in the ethtool configuration space)
	 */
	efx->fec_config = mcdi_fec_caps_to_ethtool(caps,
						   efx->link_state.speed == 25000 ||
						   efx->link_state.speed == 50000);

	/* Default to Autonegotiated flow control अगर the PHY supports it */
	efx->wanted_fc = EFX_FC_RX | EFX_FC_TX;
	अगर (phy_data->supported_cap & (1 << MC_CMD_PHY_CAP_AN_LBN))
		efx->wanted_fc |= EFX_FC_AUTO;
	efx_link_set_wanted_fc(efx, efx->wanted_fc);

	वापस 0;

fail:
	kमुक्त(phy_data);
	वापस rc;
पूर्ण

व्योम efx_mcdi_phy_हटाओ(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_data = efx->phy_data;

	efx->phy_data = शून्य;
	kमुक्त(phy_data);
पूर्ण

व्योम efx_mcdi_phy_get_link_ksettings(काष्ठा efx_nic *efx, काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_LINK_OUT_LEN);
	पूर्णांक rc;

	cmd->base.speed = efx->link_state.speed;
	cmd->base.duplex = efx->link_state.fd;
	cmd->base.port = mcdi_to_ethtool_media(phy_cfg->media);
	cmd->base.phy_address = phy_cfg->port;
	cmd->base.स्वतःneg = !!(efx->link_advertising[0] & ADVERTISED_Autoneg);
	cmd->base.mdio_support = (efx->mdio.mode_support &
			      (MDIO_SUPPORTS_C45 | MDIO_SUPPORTS_C22));

	mcdi_to_ethtool_linkset(phy_cfg->media, phy_cfg->supported_cap,
				cmd->link_modes.supported);
	स_नकल(cmd->link_modes.advertising, efx->link_advertising,
	       माप(__ETHTOOL_DECLARE_LINK_MODE_MASK()));

	BUILD_BUG_ON(MC_CMD_GET_LINK_IN_LEN != 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_GET_LINK, शून्य, 0,
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		वापस;
	mcdi_to_ethtool_linkset(phy_cfg->media,
				MCDI_DWORD(outbuf, GET_LINK_OUT_LP_CAP),
				cmd->link_modes.lp_advertising);
पूर्ण

पूर्णांक efx_mcdi_phy_set_link_ksettings(काष्ठा efx_nic *efx, स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps;
	पूर्णांक rc;

	अगर (cmd->base.स्वतःneg) अणु
		caps = (ethtool_linkset_to_mcdi_cap(cmd->link_modes.advertising) |
			1 << MC_CMD_PHY_CAP_AN_LBN);
	पूर्ण अन्यथा अगर (cmd->base.duplex) अणु
		चयन (cmd->base.speed) अणु
		हाल 10:     caps = 1 << MC_CMD_PHY_CAP_10FDX_LBN;     अवरोध;
		हाल 100:    caps = 1 << MC_CMD_PHY_CAP_100FDX_LBN;    अवरोध;
		हाल 1000:   caps = 1 << MC_CMD_PHY_CAP_1000FDX_LBN;   अवरोध;
		हाल 10000:  caps = 1 << MC_CMD_PHY_CAP_10000FDX_LBN;  अवरोध;
		हाल 40000:  caps = 1 << MC_CMD_PHY_CAP_40000FDX_LBN;  अवरोध;
		हाल 100000: caps = 1 << MC_CMD_PHY_CAP_100000FDX_LBN; अवरोध;
		हाल 25000:  caps = 1 << MC_CMD_PHY_CAP_25000FDX_LBN;  अवरोध;
		हाल 50000:  caps = 1 << MC_CMD_PHY_CAP_50000FDX_LBN;  अवरोध;
		शेष:     वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cmd->base.speed) अणु
		हाल 10:     caps = 1 << MC_CMD_PHY_CAP_10HDX_LBN;     अवरोध;
		हाल 100:    caps = 1 << MC_CMD_PHY_CAP_100HDX_LBN;    अवरोध;
		हाल 1000:   caps = 1 << MC_CMD_PHY_CAP_1000HDX_LBN;   अवरोध;
		शेष:     वापस -EINVAL;
		पूर्ण
	पूर्ण

	caps |= ethtool_fec_caps_to_mcdi(phy_cfg->supported_cap, efx->fec_config);

	rc = efx_mcdi_set_link(efx, caps, efx_get_mcdi_phy_flags(efx),
			       efx->loopback_mode, 0);
	अगर (rc)
		वापस rc;

	अगर (cmd->base.स्वतःneg) अणु
		efx_link_set_advertising(efx, cmd->link_modes.advertising);
		phy_cfg->क्रमced_cap = 0;
	पूर्ण अन्यथा अणु
		efx_link_clear_advertising(efx);
		phy_cfg->क्रमced_cap = caps;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_phy_get_fecparam(काष्ठा efx_nic *efx, काष्ठा ethtool_fecparam *fec)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_LINK_OUT_V2_LEN);
	u32 caps, active, speed; /* MCDI क्रमmat */
	bool is_25g = false;
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_LINK_IN_LEN != 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_GET_LINK, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_GET_LINK_OUT_V2_LEN)
		वापस -EOPNOTSUPP;

	/* behaviour क्रम 25G/50G links depends on 25G BASER bit */
	speed = MCDI_DWORD(outbuf, GET_LINK_OUT_V2_LINK_SPEED);
	is_25g = speed == 25000 || speed == 50000;

	caps = MCDI_DWORD(outbuf, GET_LINK_OUT_V2_CAP);
	fec->fec = mcdi_fec_caps_to_ethtool(caps, is_25g);
	/* BASER is never supported on 100G */
	अगर (speed == 100000)
		fec->fec &= ~ETHTOOL_FEC_BASER;

	active = MCDI_DWORD(outbuf, GET_LINK_OUT_V2_FEC_TYPE);
	चयन (active) अणु
	हाल MC_CMD_FEC_NONE:
		fec->active_fec = ETHTOOL_FEC_OFF;
		अवरोध;
	हाल MC_CMD_FEC_BASER:
		fec->active_fec = ETHTOOL_FEC_BASER;
		अवरोध;
	हाल MC_CMD_FEC_RS:
		fec->active_fec = ETHTOOL_FEC_RS;
		अवरोध;
	शेष:
		netअगर_warn(efx, hw, efx->net_dev,
			   "Firmware reports unrecognised FEC_TYPE %u\n",
			   active);
		/* We करोn't know what firmware has picked.  AUTO is as good a
		 * "can't happen" value as any other.
		 */
		fec->active_fec = ETHTOOL_FEC_AUTO;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Basic validation to ensure that the caps we are going to attempt to set are
 * in fact supported by the adapter.  Note that 'no FEC' is always supported.
 */
अटल पूर्णांक ethtool_fec_supported(u32 supported_cap, u32 ethtool_cap)
अणु
	अगर (ethtool_cap & ETHTOOL_FEC_OFF)
		वापस 0;

	अगर (ethtool_cap &&
	    !ethtool_fec_caps_to_mcdi(supported_cap, ethtool_cap))
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_phy_set_fecparam(काष्ठा efx_nic *efx, स्थिर काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps;
	पूर्णांक rc;

	rc = ethtool_fec_supported(phy_cfg->supported_cap, fec->fec);
	अगर (rc)
		वापस rc;

	/* Work out what efx_mcdi_phy_set_link_ksettings() would produce from
	 * saved advertising bits
	 */
	अगर (test_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, efx->link_advertising))
		caps = (ethtool_linkset_to_mcdi_cap(efx->link_advertising) |
			1 << MC_CMD_PHY_CAP_AN_LBN);
	अन्यथा
		caps = phy_cfg->क्रमced_cap;

	caps |= ethtool_fec_caps_to_mcdi(phy_cfg->supported_cap, fec->fec);
	rc = efx_mcdi_set_link(efx, caps, efx_get_mcdi_phy_flags(efx),
			       efx->loopback_mode, 0);
	अगर (rc)
		वापस rc;

	/* Record the new FEC setting क्रम subsequent set_link calls */
	efx->fec_config = fec->fec;
	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_phy_test_alive(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_PHY_STATE_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_PHY_STATE_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_PHY_STATE, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;

	अगर (outlen < MC_CMD_GET_PHY_STATE_OUT_LEN)
		वापस -EIO;
	अगर (MCDI_DWORD(outbuf, GET_PHY_STATE_OUT_STATE) != MC_CMD_PHY_STATE_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_port_reconfigure(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps = (efx->link_advertising[0] ?
		    ethtool_linkset_to_mcdi_cap(efx->link_advertising) :
		    phy_cfg->क्रमced_cap);

	caps |= ethtool_fec_caps_to_mcdi(phy_cfg->supported_cap, efx->fec_config);

	वापस efx_mcdi_set_link(efx, caps, efx_get_mcdi_phy_flags(efx),
				 efx->loopback_mode, 0);
पूर्ण

अटल स्थिर अक्षर *स्थिर mcdi_sft9001_cable_diag_names[] = अणु
	"cable.pairA.length",
	"cable.pairB.length",
	"cable.pairC.length",
	"cable.pairD.length",
	"cable.pairA.status",
	"cable.pairB.status",
	"cable.pairC.status",
	"cable.pairD.status",
पूर्ण;

अटल पूर्णांक efx_mcdi_bist(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक bist_mode,
			 पूर्णांक *results)
अणु
	अचिन्हित पूर्णांक retry, i, count = 0;
	माप_प्रकार outlen;
	u32 status;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_START_BIST_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_POLL_BIST_OUT_SFT9001_LEN);
	u8 *ptr;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_START_BIST_OUT_LEN != 0);
	MCDI_SET_DWORD(inbuf, START_BIST_IN_TYPE, bist_mode);
	rc = efx_mcdi_rpc(efx, MC_CMD_START_BIST,
			  inbuf, MC_CMD_START_BIST_IN_LEN, शून्य, 0, शून्य);
	अगर (rc)
		जाओ out;

	/* Wait up to 10s क्रम BIST to finish */
	क्रम (retry = 0; retry < 100; ++retry) अणु
		BUILD_BUG_ON(MC_CMD_POLL_BIST_IN_LEN != 0);
		rc = efx_mcdi_rpc(efx, MC_CMD_POLL_BIST, शून्य, 0,
				  outbuf, माप(outbuf), &outlen);
		अगर (rc)
			जाओ out;

		status = MCDI_DWORD(outbuf, POLL_BIST_OUT_RESULT);
		अगर (status != MC_CMD_POLL_BIST_RUNNING)
			जाओ finished;

		msleep(100);
	पूर्ण

	rc = -ETIMEDOUT;
	जाओ out;

finished:
	results[count++] = (status == MC_CMD_POLL_BIST_PASSED) ? 1 : -1;

	/* SFT9001 specअगरic cable diagnostics output */
	अगर (efx->phy_type == PHY_TYPE_SFT9001B &&
	    (bist_mode == MC_CMD_PHY_BIST_CABLE_SHORT ||
	     bist_mode == MC_CMD_PHY_BIST_CABLE_LONG)) अणु
		ptr = MCDI_PTR(outbuf, POLL_BIST_OUT_SFT9001_CABLE_LENGTH_A);
		अगर (status == MC_CMD_POLL_BIST_PASSED &&
		    outlen >= MC_CMD_POLL_BIST_OUT_SFT9001_LEN) अणु
			क्रम (i = 0; i < 8; i++) अणु
				results[count + i] =
					EFX_DWORD_FIELD(((efx_dword_t *)ptr)[i],
							EFX_DWORD_0);
			पूर्ण
		पूर्ण
		count += 8;
	पूर्ण
	rc = count;

out:
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_phy_run_tests(काष्ठा efx_nic *efx, पूर्णांक *results, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 mode;
	पूर्णांक rc;

	अगर (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_LBN)) अणु
		rc = efx_mcdi_bist(efx, MC_CMD_PHY_BIST, results);
		अगर (rc < 0)
			वापस rc;

		results += rc;
	पूर्ण

	/* If we support both LONG and SHORT, then run each in response to
	 * अवरोध or not. Otherwise, run the one we support
	 */
	mode = 0;
	अगर (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_SHORT_LBN)) अणु
		अगर ((flags & ETH_TEST_FL_OFFLINE) &&
		    (phy_cfg->flags &
		     (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_LONG_LBN)))
			mode = MC_CMD_PHY_BIST_CABLE_LONG;
		अन्यथा
			mode = MC_CMD_PHY_BIST_CABLE_SHORT;
	पूर्ण अन्यथा अगर (phy_cfg->flags &
		   (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_LONG_LBN))
		mode = MC_CMD_PHY_BIST_CABLE_LONG;

	अगर (mode != 0) अणु
		rc = efx_mcdi_bist(efx, mode, results);
		अगर (rc < 0)
			वापस rc;
		results += rc;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर अक्षर *efx_mcdi_phy_test_name(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक index)
अणु
	काष्ठा efx_mcdi_phy_data *phy_cfg = efx->phy_data;

	अगर (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_LBN)) अणु
		अगर (index == 0)
			वापस "bist";
		--index;
	पूर्ण

	अगर (phy_cfg->flags & ((1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_SHORT_LBN) |
			      (1 << MC_CMD_GET_PHY_CFG_OUT_BIST_CABLE_LONG_LBN))) अणु
		अगर (index == 0)
			वापस "cable";
		--index;

		अगर (efx->phy_type == PHY_TYPE_SFT9001B) अणु
			अगर (index < ARRAY_SIZE(mcdi_sft9001_cable_diag_names))
				वापस mcdi_sft9001_cable_diag_names[index];
			index -= ARRAY_SIZE(mcdi_sft9001_cable_diag_names);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा SFP_PAGE_SIZE		128
#घोषणा SFF_DIAG_TYPE_OFFSET	92
#घोषणा SFF_DIAG_ADDR_CHANGE	BIT(2)
#घोषणा SFF_8079_NUM_PAGES	2
#घोषणा SFF_8472_NUM_PAGES	4
#घोषणा SFF_8436_NUM_PAGES	5
#घोषणा SFF_DMT_LEVEL_OFFSET	94

/** efx_mcdi_phy_get_module_eeprom_page() - Get a single page of module eeprom
 * @efx:	NIC context
 * @page:	EEPROM page number
 * @data:	Destination data poपूर्णांकer
 * @offset:	Offset in page to copy from in to data
 * @space:	Space available in data
 *
 * Return:
 *   >=0 - amount of data copied
 *   <0  - error
 */
अटल पूर्णांक efx_mcdi_phy_get_module_eeprom_page(काष्ठा efx_nic *efx,
					       अचिन्हित पूर्णांक page,
					       u8 *data, sमाप_प्रकार offset,
					       sमाप_प्रकार space)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_PHY_MEDIA_INFO_OUT_LENMAX);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_GET_PHY_MEDIA_INFO_IN_LEN);
	अचिन्हित पूर्णांक payload_len;
	अचिन्हित पूर्णांक to_copy;
	माप_प्रकार outlen;
	पूर्णांक rc;

	अगर (offset > SFP_PAGE_SIZE)
		वापस -EINVAL;

	to_copy = min(space, SFP_PAGE_SIZE - offset);

	MCDI_SET_DWORD(inbuf, GET_PHY_MEDIA_INFO_IN_PAGE, page);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_GET_PHY_MEDIA_INFO,
				inbuf, माप(inbuf),
				outbuf, माप(outbuf),
				&outlen);

	अगर (rc)
		वापस rc;

	अगर (outlen < (MC_CMD_GET_PHY_MEDIA_INFO_OUT_DATA_OFST +
			SFP_PAGE_SIZE))
		वापस -EIO;

	payload_len = MCDI_DWORD(outbuf, GET_PHY_MEDIA_INFO_OUT_DATALEN);
	अगर (payload_len != SFP_PAGE_SIZE)
		वापस -EIO;

	स_नकल(data, MCDI_PTR(outbuf, GET_PHY_MEDIA_INFO_OUT_DATA) + offset,
	       to_copy);

	वापस to_copy;
पूर्ण

अटल पूर्णांक efx_mcdi_phy_get_module_eeprom_byte(काष्ठा efx_nic *efx,
					       अचिन्हित पूर्णांक page,
					       u8 byte)
अणु
	u8 data;
	पूर्णांक rc;

	rc = efx_mcdi_phy_get_module_eeprom_page(efx, page, &data, byte, 1);
	अगर (rc == 1)
		वापस data;

	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_phy_diag_type(काष्ठा efx_nic *efx)
अणु
	/* Page zero of the EEPROM includes the diagnostic type at byte 92. */
	वापस efx_mcdi_phy_get_module_eeprom_byte(efx, 0,
						   SFF_DIAG_TYPE_OFFSET);
पूर्ण

अटल पूर्णांक efx_mcdi_phy_sff_8472_level(काष्ठा efx_nic *efx)
अणु
	/* Page zero of the EEPROM includes the DMT level at byte 94. */
	वापस efx_mcdi_phy_get_module_eeprom_byte(efx, 0,
						   SFF_DMT_LEVEL_OFFSET);
पूर्ण

अटल u32 efx_mcdi_phy_module_type(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_phy_data *phy_data = efx->phy_data;

	अगर (phy_data->media != MC_CMD_MEDIA_QSFP_PLUS)
		वापस phy_data->media;

	/* A QSFP+ NIC may actually have an SFP+ module attached.
	 * The ID is page 0, byte 0.
	 */
	चयन (efx_mcdi_phy_get_module_eeprom_byte(efx, 0, 0)) अणु
	हाल 0x3:
		वापस MC_CMD_MEDIA_SFP_PLUS;
	हाल 0xc:
	हाल 0xd:
		वापस MC_CMD_MEDIA_QSFP_PLUS;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक efx_mcdi_phy_get_module_eeprom(काष्ठा efx_nic *efx, काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	पूर्णांक rc;
	sमाप_प्रकार space_reमुख्यing = ee->len;
	अचिन्हित पूर्णांक page_off;
	bool ignore_missing;
	पूर्णांक num_pages;
	पूर्णांक page;

	चयन (efx_mcdi_phy_module_type(efx)) अणु
	हाल MC_CMD_MEDIA_SFP_PLUS:
		num_pages = efx_mcdi_phy_sff_8472_level(efx) > 0 ?
				SFF_8472_NUM_PAGES : SFF_8079_NUM_PAGES;
		page = 0;
		ignore_missing = false;
		अवरोध;
	हाल MC_CMD_MEDIA_QSFP_PLUS:
		num_pages = SFF_8436_NUM_PAGES;
		page = -1; /* We obtain the lower page by asking क्रम -1. */
		ignore_missing = true; /* Ignore missing pages after page 0. */
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	page_off = ee->offset % SFP_PAGE_SIZE;
	page += ee->offset / SFP_PAGE_SIZE;

	जबतक (space_reमुख्यing && (page < num_pages)) अणु
		rc = efx_mcdi_phy_get_module_eeprom_page(efx, page,
							 data, page_off,
							 space_reमुख्यing);

		अगर (rc > 0) अणु
			space_reमुख्यing -= rc;
			data += rc;
			page_off = 0;
			page++;
		पूर्ण अन्यथा अगर (rc == 0) अणु
			space_reमुख्यing = 0;
		पूर्ण अन्यथा अगर (ignore_missing && (page > 0)) अणु
			पूर्णांक पूर्णांकended_size = SFP_PAGE_SIZE - page_off;

			space_reमुख्यing -= पूर्णांकended_size;
			अगर (space_reमुख्यing < 0) अणु
				space_reमुख्यing = 0;
			पूर्ण अन्यथा अणु
				स_रखो(data, 0, पूर्णांकended_size);
				data += पूर्णांकended_size;
				page_off = 0;
				page++;
				rc = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_phy_get_module_info(काष्ठा efx_nic *efx, काष्ठा ethtool_modinfo *modinfo)
अणु
	पूर्णांक sff_8472_level;
	पूर्णांक diag_type;

	चयन (efx_mcdi_phy_module_type(efx)) अणु
	हाल MC_CMD_MEDIA_SFP_PLUS:
		sff_8472_level = efx_mcdi_phy_sff_8472_level(efx);

		/* If we can't पढ़ो the diagnostics level we have none. */
		अगर (sff_8472_level < 0)
			वापस -EOPNOTSUPP;

		/* Check अगर this module requires the (unsupported) address
		 * change operation.
		 */
		diag_type = efx_mcdi_phy_diag_type(efx);

		अगर (sff_8472_level == 0 ||
		    (diag_type & SFF_DIAG_ADDR_CHANGE)) अणु
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		पूर्ण
		अवरोध;

	हाल MC_CMD_MEDIA_QSFP_PLUS:
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक efx_calc_mac_mtu(काष्ठा efx_nic *efx)
अणु
	वापस EFX_MAX_FRAME_LEN(efx->net_dev->mtu);
पूर्ण

पूर्णांक efx_mcdi_set_mac(काष्ठा efx_nic *efx)
अणु
	u32 fcntl;
	MCDI_DECLARE_BUF(cmdbytes, MC_CMD_SET_MAC_IN_LEN);

	BUILD_BUG_ON(MC_CMD_SET_MAC_OUT_LEN != 0);

	/* This has no effect on EF10 */
	ether_addr_copy(MCDI_PTR(cmdbytes, SET_MAC_IN_ADDR),
			efx->net_dev->dev_addr);

	MCDI_SET_DWORD(cmdbytes, SET_MAC_IN_MTU, efx_calc_mac_mtu(efx));
	MCDI_SET_DWORD(cmdbytes, SET_MAC_IN_DRAIN, 0);

	/* Set simple MAC filter क्रम Siena */
	MCDI_POPULATE_DWORD_1(cmdbytes, SET_MAC_IN_REJECT,
			      SET_MAC_IN_REJECT_UNCST, efx->unicast_filter);

	MCDI_POPULATE_DWORD_1(cmdbytes, SET_MAC_IN_FLAGS,
			      SET_MAC_IN_FLAG_INCLUDE_FCS,
			      !!(efx->net_dev->features & NETIF_F_RXFCS));

	चयन (efx->wanted_fc) अणु
	हाल EFX_FC_RX | EFX_FC_TX:
		fcntl = MC_CMD_FCNTL_BIसूची;
		अवरोध;
	हाल EFX_FC_RX:
		fcntl = MC_CMD_FCNTL_RESPOND;
		अवरोध;
	शेष:
		fcntl = MC_CMD_FCNTL_OFF;
		अवरोध;
	पूर्ण
	अगर (efx->wanted_fc & EFX_FC_AUTO)
		fcntl = MC_CMD_FCNTL_AUTO;
	अगर (efx->fc_disable)
		fcntl = MC_CMD_FCNTL_OFF;

	MCDI_SET_DWORD(cmdbytes, SET_MAC_IN_FCNTL, fcntl);

	वापस efx_mcdi_rpc(efx, MC_CMD_SET_MAC, cmdbytes, माप(cmdbytes),
			    शून्य, 0, शून्य);
पूर्ण

पूर्णांक efx_mcdi_set_mtu(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SET_MAC_EXT_IN_LEN);

	BUILD_BUG_ON(MC_CMD_SET_MAC_OUT_LEN != 0);

	MCDI_SET_DWORD(inbuf, SET_MAC_EXT_IN_MTU, efx_calc_mac_mtu(efx));

	MCDI_POPULATE_DWORD_1(inbuf, SET_MAC_EXT_IN_CONTROL,
			      SET_MAC_EXT_IN_CFG_MTU, 1);

	वापस efx_mcdi_rpc(efx, MC_CMD_SET_MAC, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

क्रमागत efx_stats_action अणु
	EFX_STATS_ENABLE,
	EFX_STATS_DISABLE,
	EFX_STATS_PULL,
पूर्ण;

अटल पूर्णांक efx_mcdi_mac_stats(काष्ठा efx_nic *efx,
			      क्रमागत efx_stats_action action, पूर्णांक clear)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_MAC_STATS_IN_LEN);
	पूर्णांक rc;
	पूर्णांक change = action == EFX_STATS_PULL ? 0 : 1;
	पूर्णांक enable = action == EFX_STATS_ENABLE ? 1 : 0;
	पूर्णांक period = action == EFX_STATS_ENABLE ? 1000 : 0;
	dma_addr_t dma_addr = efx->stats_buffer.dma_addr;
	u32 dma_len = action != EFX_STATS_DISABLE ?
		efx->num_mac_stats * माप(u64) : 0;

	BUILD_BUG_ON(MC_CMD_MAC_STATS_OUT_DMA_LEN != 0);

	MCDI_SET_QWORD(inbuf, MAC_STATS_IN_DMA_ADDR, dma_addr);
	MCDI_POPULATE_DWORD_7(inbuf, MAC_STATS_IN_CMD,
			      MAC_STATS_IN_DMA, !!enable,
			      MAC_STATS_IN_CLEAR, clear,
			      MAC_STATS_IN_PERIODIC_CHANGE, change,
			      MAC_STATS_IN_PERIODIC_ENABLE, enable,
			      MAC_STATS_IN_PERIODIC_CLEAR, 0,
			      MAC_STATS_IN_PERIODIC_NOEVENT, 1,
			      MAC_STATS_IN_PERIOD_MS, period);
	MCDI_SET_DWORD(inbuf, MAC_STATS_IN_DMA_LEN, dma_len);

	अगर (efx_nic_rev(efx) >= EFX_REV_HUNT_A0)
		MCDI_SET_DWORD(inbuf, MAC_STATS_IN_PORT_ID, efx->vport_id);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_MAC_STATS, inbuf, माप(inbuf),
				शून्य, 0, शून्य);
	/* Expect ENOENT अगर DMA queues have not been set up */
	अगर (rc && (rc != -ENOENT || atomic_पढ़ो(&efx->active_queues)))
		efx_mcdi_display_error(efx, MC_CMD_MAC_STATS, माप(inbuf),
				       शून्य, 0, rc);
	वापस rc;
पूर्ण

व्योम efx_mcdi_mac_start_stats(काष्ठा efx_nic *efx)
अणु
	__le64 *dma_stats = efx->stats_buffer.addr;

	dma_stats[efx->num_mac_stats - 1] = EFX_MC_STATS_GENERATION_INVALID;

	efx_mcdi_mac_stats(efx, EFX_STATS_ENABLE, 0);
पूर्ण

व्योम efx_mcdi_mac_stop_stats(काष्ठा efx_nic *efx)
अणु
	efx_mcdi_mac_stats(efx, EFX_STATS_DISABLE, 0);
पूर्ण

#घोषणा EFX_MAC_STATS_WAIT_US 100
#घोषणा EFX_MAC_STATS_WAIT_ATTEMPTS 10

व्योम efx_mcdi_mac_pull_stats(काष्ठा efx_nic *efx)
अणु
	__le64 *dma_stats = efx->stats_buffer.addr;
	पूर्णांक attempts = EFX_MAC_STATS_WAIT_ATTEMPTS;

	dma_stats[efx->num_mac_stats - 1] = EFX_MC_STATS_GENERATION_INVALID;
	efx_mcdi_mac_stats(efx, EFX_STATS_PULL, 0);

	जबतक (dma_stats[efx->num_mac_stats - 1] ==
				EFX_MC_STATS_GENERATION_INVALID &&
			attempts-- != 0)
		udelay(EFX_MAC_STATS_WAIT_US);
पूर्ण

पूर्णांक efx_mcdi_mac_init_stats(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	अगर (!efx->num_mac_stats)
		वापस 0;

	/* Allocate buffer क्रम stats */
	rc = efx_nic_alloc_buffer(efx, &efx->stats_buffer,
				  efx->num_mac_stats * माप(u64), GFP_KERNEL);
	अगर (rc) अणु
		netअगर_warn(efx, probe, efx->net_dev,
			   "failed to allocate DMA buffer: %d\n", rc);
		वापस rc;
	पूर्ण

	netअगर_dbg(efx, probe, efx->net_dev,
		  "stats buffer at %llx (virt %p phys %llx)\n",
		  (u64) efx->stats_buffer.dma_addr,
		  efx->stats_buffer.addr,
		  (u64) virt_to_phys(efx->stats_buffer.addr));

	वापस 0;
पूर्ण

व्योम efx_mcdi_mac_fini_stats(काष्ठा efx_nic *efx)
अणु
	efx_nic_मुक्त_buffer(efx, &efx->stats_buffer);
पूर्ण

/* Get physical port number (EF10 only; on Siena it is same as PF number) */
पूर्णांक efx_mcdi_port_get_number(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_PORT_ASSIGNMENT_OUT_LEN);
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_PORT_ASSIGNMENT, शून्य, 0,
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		वापस rc;

	वापस MCDI_DWORD(outbuf, GET_PORT_ASSIGNMENT_OUT_PORT);
पूर्ण

अटल अचिन्हित पूर्णांक efx_mcdi_event_link_speed[] = अणु
	[MCDI_EVENT_LINKCHANGE_SPEED_100M] = 100,
	[MCDI_EVENT_LINKCHANGE_SPEED_1G] = 1000,
	[MCDI_EVENT_LINKCHANGE_SPEED_10G] = 10000,
	[MCDI_EVENT_LINKCHANGE_SPEED_40G] = 40000,
	[MCDI_EVENT_LINKCHANGE_SPEED_25G] = 25000,
	[MCDI_EVENT_LINKCHANGE_SPEED_50G] = 50000,
	[MCDI_EVENT_LINKCHANGE_SPEED_100G] = 100000,
पूर्ण;

व्योम efx_mcdi_process_link_change(काष्ठा efx_nic *efx, efx_qword_t *ev)
अणु
	u32 flags, fcntl, speed, lpa;

	speed = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_SPEED);
	EFX_WARN_ON_PARANOID(speed >= ARRAY_SIZE(efx_mcdi_event_link_speed));
	speed = efx_mcdi_event_link_speed[speed];

	flags = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_LINK_FLAGS);
	fcntl = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_FCNTL);
	lpa = EFX_QWORD_FIELD(*ev, MCDI_EVENT_LINKCHANGE_LP_CAP);

	/* efx->link_state is only modअगरied by efx_mcdi_phy_get_link(),
	 * which is only run after flushing the event queues. Thereक्रमe, it
	 * is safe to modअगरy the link state outside of the mac_lock here.
	 */
	efx_mcdi_phy_decode_link(efx, &efx->link_state, speed, flags, fcntl);

	efx_mcdi_phy_check_fcntl(efx, lpa);

	efx_link_status_changed(efx);
पूर्ण
