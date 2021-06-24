<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2006-2011 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_MDIO_10G_H
#घोषणा EF4_MDIO_10G_H

#समावेश <linux/mdपन.स>

/*
 * Helper functions क्रम करोing 10G MDIO as specअगरied in IEEE 802.3 clause 45.
 */

#समावेश "efx.h"

अटल अंतरभूत अचिन्हित ef4_mdio_id_rev(u32 id) अणु वापस id & 0xf; पूर्ण
अटल अंतरभूत अचिन्हित ef4_mdio_id_model(u32 id) अणु वापस (id >> 4) & 0x3f; पूर्ण
अचिन्हित ef4_mdio_id_oui(u32 id);

अटल अंतरभूत पूर्णांक ef4_mdio_पढ़ो(काष्ठा ef4_nic *efx, पूर्णांक devad, पूर्णांक addr)
अणु
	वापस efx->mdio.mdio_पढ़ो(efx->net_dev, efx->mdio.prtad, devad, addr);
पूर्ण

अटल अंतरभूत व्योम
ef4_mdio_ग_लिखो(काष्ठा ef4_nic *efx, पूर्णांक devad, पूर्णांक addr, पूर्णांक value)
अणु
	efx->mdio.mdio_ग_लिखो(efx->net_dev, efx->mdio.prtad, devad, addr, value);
पूर्ण

अटल अंतरभूत u32 ef4_mdio_पढ़ो_id(काष्ठा ef4_nic *efx, पूर्णांक mmd)
अणु
	u16 id_low = ef4_mdio_पढ़ो(efx, mmd, MDIO_DEVID2);
	u16 id_hi = ef4_mdio_पढ़ो(efx, mmd, MDIO_DEVID1);
	वापस (id_hi << 16) | (id_low);
पूर्ण

अटल अंतरभूत bool ef4_mdio_phyxgxs_lane_sync(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक i, lane_status;
	bool sync;

	क्रम (i = 0; i < 2; ++i)
		lane_status = ef4_mdio_पढ़ो(efx, MDIO_MMD_PHYXS,
					    MDIO_PHYXS_LNSTAT);

	sync = !!(lane_status & MDIO_PHYXS_LNSTAT_ALIGN);
	अगर (!sync)
		netअगर_dbg(efx, hw, efx->net_dev, "XGXS lane status: %x\n",
			  lane_status);
	वापस sync;
पूर्ण

स्थिर अक्षर *ef4_mdio_mmd_name(पूर्णांक mmd);

/*
 * Reset a specअगरic MMD and रुको क्रम reset to clear.
 * Return number of spins left (>0) on success, -%ETIMEDOUT on failure.
 *
 * This function will sleep
 */
पूर्णांक ef4_mdio_reset_mmd(काष्ठा ef4_nic *efx, पूर्णांक mmd, पूर्णांक spins, पूर्णांक spपूर्णांकime);

/* As ef4_mdio_check_mmd but क्रम multiple MMDs */
पूर्णांक ef4_mdio_check_mmds(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक mmd_mask);

/* Check the link status of specअगरied mmds in bit mask */
bool ef4_mdio_links_ok(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक mmd_mask);

/* Generic transmit disable support though PMAPMD */
व्योम ef4_mdio_transmit_disable(काष्ठा ef4_nic *efx);

/* Generic part of reconfigure: set/clear loopback bits */
व्योम ef4_mdio_phy_reconfigure(काष्ठा ef4_nic *efx);

/* Set the घातer state of the specअगरied MMDs */
व्योम ef4_mdio_set_mmds_lघातer(काष्ठा ef4_nic *efx, पूर्णांक low_घातer,
			      अचिन्हित पूर्णांक mmd_mask);

/* Set (some of) the PHY settings over MDIO */
पूर्णांक ef4_mdio_set_link_ksettings(काष्ठा ef4_nic *efx,
				स्थिर काष्ठा ethtool_link_ksettings *cmd);

/* Push advertising flags and restart स्वतःnegotiation */
व्योम ef4_mdio_an_reconfigure(काष्ठा ef4_nic *efx);

/* Get छोड़ो parameters from AN अगर available (otherwise वापस
 * requested छोड़ो parameters)
 */
u8 ef4_mdio_get_छोड़ो(काष्ठा ef4_nic *efx);

/* Wait क्रम specअगरied MMDs to निकास reset within a समयout */
पूर्णांक ef4_mdio_रुको_reset_mmds(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक mmd_mask);

/* Set or clear flag, debouncing */
अटल अंतरभूत व्योम
ef4_mdio_set_flag(काष्ठा ef4_nic *efx, पूर्णांक devad, पूर्णांक addr,
		  पूर्णांक mask, bool state)
अणु
	mdio_set_flag(&efx->mdio, efx->mdio.prtad, devad, addr, mask, state);
पूर्ण

/* Liveness self-test क्रम MDIO PHYs */
पूर्णांक ef4_mdio_test_alive(काष्ठा ef4_nic *efx);

#पूर्ण_अगर /* EF4_MDIO_10G_H */
