<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2006-2011 Solarflare Communications Inc.
 */
/*
 * Useful functions क्रम working with MDIO clause 45 PHYs
 */
#समावेश <linux/types.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>
#समावेश "net_driver.h"
#समावेश "mdio_10g.h"
#समावेश "workarounds.h"

अचिन्हित ef4_mdio_id_oui(u32 id)
अणु
	अचिन्हित oui = 0;
	पूर्णांक i;

	/* The bits of the OUI are designated a..x, with a=0 and b variable.
	 * In the id रेजिस्टर c is the MSB but the OUI is conventionally
	 * written as bytes h..a, p..i, x..q.  Reorder the bits accordingly. */
	क्रम (i = 0; i < 22; ++i)
		अगर (id & (1 << (i + 10)))
			oui |= 1 << (i ^ 7);

	वापस oui;
पूर्ण

पूर्णांक ef4_mdio_reset_mmd(काष्ठा ef4_nic *port, पूर्णांक mmd,
			    पूर्णांक spins, पूर्णांक spपूर्णांकime)
अणु
	u32 ctrl;

	/* Catch callers passing values in the wrong units (or just silly) */
	EF4_BUG_ON_PARANOID(spins * spपूर्णांकime >= 5000);

	ef4_mdio_ग_लिखो(port, mmd, MDIO_CTRL1, MDIO_CTRL1_RESET);
	/* Wait क्रम the reset bit to clear. */
	करो अणु
		msleep(spपूर्णांकime);
		ctrl = ef4_mdio_पढ़ो(port, mmd, MDIO_CTRL1);
		spins--;

	पूर्ण जबतक (spins && (ctrl & MDIO_CTRL1_RESET));

	वापस spins ? spins : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ef4_mdio_check_mmd(काष्ठा ef4_nic *efx, पूर्णांक mmd)
अणु
	पूर्णांक status;

	अगर (mmd != MDIO_MMD_AN) अणु
		/* Read MMD STATUS2 to check it is responding. */
		status = ef4_mdio_पढ़ो(efx, mmd, MDIO_STAT2);
		अगर ((status & MDIO_STAT2_DEVPRST) != MDIO_STAT2_DEVPRST_VAL) अणु
			netअगर_err(efx, hw, efx->net_dev,
				  "PHY MMD %d not responding.\n", mmd);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This ought to be ridiculous overसमाप्त. We expect it to fail rarely */
#घोषणा MDIO45_RESET_TIME	1000 /* ms */
#घोषणा MDIO45_RESET_ITERS	100

पूर्णांक ef4_mdio_रुको_reset_mmds(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक mmd_mask)
अणु
	स्थिर पूर्णांक spपूर्णांकime = MDIO45_RESET_TIME / MDIO45_RESET_ITERS;
	पूर्णांक tries = MDIO45_RESET_ITERS;
	पूर्णांक rc = 0;
	पूर्णांक in_reset;

	जबतक (tries) अणु
		पूर्णांक mask = mmd_mask;
		पूर्णांक mmd = 0;
		पूर्णांक stat;
		in_reset = 0;
		जबतक (mask) अणु
			अगर (mask & 1) अणु
				stat = ef4_mdio_पढ़ो(efx, mmd, MDIO_CTRL1);
				अगर (stat < 0) अणु
					netअगर_err(efx, hw, efx->net_dev,
						  "failed to read status of"
						  " MMD %d\n", mmd);
					वापस -EIO;
				पूर्ण
				अगर (stat & MDIO_CTRL1_RESET)
					in_reset |= (1 << mmd);
			पूर्ण
			mask = mask >> 1;
			mmd++;
		पूर्ण
		अगर (!in_reset)
			अवरोध;
		tries--;
		msleep(spपूर्णांकime);
	पूर्ण
	अगर (in_reset != 0) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "not all MMDs came out of reset in time."
			  " MMDs still in reset: %x\n", in_reset);
		rc = -ETIMEDOUT;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक ef4_mdio_check_mmds(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक mmd_mask)
अणु
	पूर्णांक mmd = 0, probe_mmd, devs1, devs2;
	u32 devices;

	/* Historically we have probed the PHYXS to find out what devices are
	 * present,but that करोesn't work so well if the PHYXS isn't expected
	 * to exist, अगर so just find the first item in the list supplied. */
	probe_mmd = (mmd_mask & MDIO_DEVS_PHYXS) ? MDIO_MMD_PHYXS :
	    __ffs(mmd_mask);

	/* Check all the expected MMDs are present */
	devs1 = ef4_mdio_पढ़ो(efx, probe_mmd, MDIO_DEVS1);
	devs2 = ef4_mdio_पढ़ो(efx, probe_mmd, MDIO_DEVS2);
	अगर (devs1 < 0 || devs2 < 0) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "failed to read devices present\n");
		वापस -EIO;
	पूर्ण
	devices = devs1 | (devs2 << 16);
	अगर ((devices & mmd_mask) != mmd_mask) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "required MMDs not present: got %x, wanted %x\n",
			  devices, mmd_mask);
		वापस -ENODEV;
	पूर्ण
	netअगर_vdbg(efx, hw, efx->net_dev, "Devices present: %x\n", devices);

	/* Check all required MMDs are responding and happy. */
	जबतक (mmd_mask) अणु
		अगर ((mmd_mask & 1) && ef4_mdio_check_mmd(efx, mmd))
			वापस -EIO;
		mmd_mask = mmd_mask >> 1;
		mmd++;
	पूर्ण

	वापस 0;
पूर्ण

bool ef4_mdio_links_ok(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक mmd_mask)
अणु
	/* If the port is in loopback, then we should only consider a subset
	 * of mmd's */
	अगर (LOOPBACK_INTERNAL(efx))
		वापस true;
	अन्यथा अगर (LOOPBACK_MASK(efx) & LOOPBACKS_WS)
		वापस false;
	अन्यथा अगर (ef4_phy_mode_disabled(efx->phy_mode))
		वापस false;
	अन्यथा अगर (efx->loopback_mode == LOOPBACK_PHYXS)
		mmd_mask &= ~(MDIO_DEVS_PHYXS |
			      MDIO_DEVS_PCS |
			      MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);
	अन्यथा अगर (efx->loopback_mode == LOOPBACK_PCS)
		mmd_mask &= ~(MDIO_DEVS_PCS |
			      MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);
	अन्यथा अगर (efx->loopback_mode == LOOPBACK_PMAPMD)
		mmd_mask &= ~(MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);

	वापस mdio45_links_ok(&efx->mdio, mmd_mask);
पूर्ण

व्योम ef4_mdio_transmit_disable(काष्ठा ef4_nic *efx)
अणु
	ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD,
			  MDIO_PMA_TXDIS, MDIO_PMD_TXDIS_GLOBAL,
			  efx->phy_mode & PHY_MODE_TX_DISABLED);
पूर्ण

व्योम ef4_mdio_phy_reconfigure(काष्ठा ef4_nic *efx)
अणु
	ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD,
			  MDIO_CTRL1, MDIO_PMA_CTRL1_LOOPBACK,
			  efx->loopback_mode == LOOPBACK_PMAPMD);
	ef4_mdio_set_flag(efx, MDIO_MMD_PCS,
			  MDIO_CTRL1, MDIO_PCS_CTRL1_LOOPBACK,
			  efx->loopback_mode == LOOPBACK_PCS);
	ef4_mdio_set_flag(efx, MDIO_MMD_PHYXS,
			  MDIO_CTRL1, MDIO_PHYXS_CTRL1_LOOPBACK,
			  efx->loopback_mode == LOOPBACK_PHYXS_WS);
पूर्ण

अटल व्योम ef4_mdio_set_mmd_lघातer(काष्ठा ef4_nic *efx,
				    पूर्णांक lघातer, पूर्णांक mmd)
अणु
	पूर्णांक stat = ef4_mdio_पढ़ो(efx, mmd, MDIO_STAT1);

	netअगर_vdbg(efx, drv, efx->net_dev, "Setting low power mode for MMD %d to %d\n",
		  mmd, lघातer);

	अगर (stat & MDIO_STAT1_LPOWERABLE) अणु
		ef4_mdio_set_flag(efx, mmd, MDIO_CTRL1,
				  MDIO_CTRL1_LPOWER, lघातer);
	पूर्ण
पूर्ण

व्योम ef4_mdio_set_mmds_lघातer(काष्ठा ef4_nic *efx,
			      पूर्णांक low_घातer, अचिन्हित पूर्णांक mmd_mask)
अणु
	पूर्णांक mmd = 0;
	mmd_mask &= ~MDIO_DEVS_AN;
	जबतक (mmd_mask) अणु
		अगर (mmd_mask & 1)
			ef4_mdio_set_mmd_lघातer(efx, low_घातer, mmd);
		mmd_mask = (mmd_mask >> 1);
		mmd++;
	पूर्ण
पूर्ण

/**
 * ef4_mdio_set_link_ksettings - Set (some of) the PHY settings over MDIO.
 * @efx:		Efx NIC
 * @cmd:		New settings
 */
पूर्णांक ef4_mdio_set_link_ksettings(काष्ठा ef4_nic *efx,
				स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ethtool_link_ksettings prev = अणु
		.base.cmd = ETHTOOL_GLINKSETTINGS
	पूर्ण;
	u32 prev_advertising, advertising;
	u32 prev_supported;

	efx->phy_op->get_link_ksettings(efx, &prev);

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);
	ethtool_convert_link_mode_to_legacy_u32(&prev_advertising,
						prev.link_modes.advertising);
	ethtool_convert_link_mode_to_legacy_u32(&prev_supported,
						prev.link_modes.supported);

	अगर (advertising == prev_advertising &&
	    cmd->base.speed == prev.base.speed &&
	    cmd->base.duplex == prev.base.duplex &&
	    cmd->base.port == prev.base.port &&
	    cmd->base.स्वतःneg == prev.base.स्वतःneg)
		वापस 0;

	/* We can only change these settings क्रम -T PHYs */
	अगर (prev.base.port != PORT_TP || cmd->base.port != PORT_TP)
		वापस -EINVAL;

	/* Check that PHY supports these settings */
	अगर (!cmd->base.स्वतःneg ||
	    (advertising | SUPPORTED_Autoneg) & ~prev_supported)
		वापस -EINVAL;

	ef4_link_set_advertising(efx, advertising | ADVERTISED_Autoneg);
	ef4_mdio_an_reconfigure(efx);
	वापस 0;
पूर्ण

/**
 * ef4_mdio_an_reconfigure - Push advertising flags and restart स्वतःnegotiation
 * @efx:		Efx NIC
 */
व्योम ef4_mdio_an_reconfigure(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक reg;

	WARN_ON(!(efx->mdio.mmds & MDIO_DEVS_AN));

	/* Set up the base page */
	reg = ADVERTISE_CSMA | ADVERTISE_RESV;
	अगर (efx->link_advertising & ADVERTISED_Pause)
		reg |= ADVERTISE_PAUSE_CAP;
	अगर (efx->link_advertising & ADVERTISED_Asym_Pause)
		reg |= ADVERTISE_PAUSE_ASYM;
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_AN, MDIO_AN_ADVERTISE, reg);

	/* Set up the (extended) next page */
	efx->phy_op->set_npage_adv(efx, efx->link_advertising);

	/* Enable and restart AN */
	reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_AN, MDIO_CTRL1);
	reg |= MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART | MDIO_AN_CTRL1_XNP;
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_AN, MDIO_CTRL1, reg);
पूर्ण

u8 ef4_mdio_get_छोड़ो(काष्ठा ef4_nic *efx)
अणु
	BUILD_BUG_ON(EF4_FC_AUTO & (EF4_FC_RX | EF4_FC_TX));

	अगर (!(efx->wanted_fc & EF4_FC_AUTO))
		वापस efx->wanted_fc;

	WARN_ON(!(efx->mdio.mmds & MDIO_DEVS_AN));

	वापस mii_resolve_flowctrl_fdx(
		mii_advertise_flowctrl(efx->wanted_fc),
		ef4_mdio_पढ़ो(efx, MDIO_MMD_AN, MDIO_AN_LPA));
पूर्ण

पूर्णांक ef4_mdio_test_alive(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;
	पूर्णांक devad = __ffs(efx->mdio.mmds);
	u16 physid1, physid2;

	mutex_lock(&efx->mac_lock);

	physid1 = ef4_mdio_पढ़ो(efx, devad, MDIO_DEVID1);
	physid2 = ef4_mdio_पढ़ो(efx, devad, MDIO_DEVID2);

	अगर ((physid1 == 0x0000) || (physid1 == 0xffff) ||
	    (physid2 == 0x0000) || (physid2 == 0xffff)) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "no MDIO PHY present with ID %d\n", efx->mdio.prtad);
		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		rc = ef4_mdio_check_mmds(efx, efx->mdio.mmds);
	पूर्ण

	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण
