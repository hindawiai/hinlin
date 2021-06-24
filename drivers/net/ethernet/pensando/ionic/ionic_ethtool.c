<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sfp.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_ethtool.h"
#समावेश "ionic_stats.h"

अटल स्थिर अक्षर ionic_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
#घोषणा IONIC_PRIV_F_SW_DBG_STATS	BIT(0)
	"sw-dbg-stats",
पूर्ण;

#घोषणा IONIC_PRIV_FLAGS_COUNT ARRAY_SIZE(ionic_priv_flags_strings)

अटल व्योम ionic_get_stats_strings(काष्ठा ionic_lअगर *lअगर, u8 *buf)
अणु
	u32 i;

	क्रम (i = 0; i < ionic_num_stats_grps; i++)
		ionic_stats_groups[i].get_strings(lअगर, &buf);
पूर्ण

अटल व्योम ionic_get_stats(काष्ठा net_device *netdev,
			    काष्ठा ethtool_stats *stats, u64 *buf)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	u32 i;

	स_रखो(buf, 0, stats->n_stats * माप(*buf));
	क्रम (i = 0; i < ionic_num_stats_grps; i++)
		ionic_stats_groups[i].get_values(lअगर, &buf);
पूर्ण

अटल पूर्णांक ionic_get_stats_count(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक i, num_stats = 0;

	क्रम (i = 0; i < ionic_num_stats_grps; i++)
		num_stats += ionic_stats_groups[i].get_count(lअगर);

	वापस num_stats;
पूर्ण

अटल पूर्णांक ionic_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	पूर्णांक count = 0;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		count = ionic_get_stats_count(lअगर);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		count = IONIC_PRIV_FLAGS_COUNT;
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम ionic_get_strings(काष्ठा net_device *netdev,
			      u32 sset, u8 *buf)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		ionic_get_stats_strings(lअगर, buf);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(buf, ionic_priv_flags_strings,
		       IONIC_PRIV_FLAGS_COUNT * ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ionic_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;

	strlcpy(drvinfo->driver, IONIC_DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->fw_version, ionic->idev.dev_info.fw_version,
		माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, ionic_bus_info(ionic),
		माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक ionic_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस (IONIC_DEV_INFO_REG_COUNT + IONIC_DEV_CMD_REG_COUNT) * माप(u32);
पूर्ण

अटल व्योम ionic_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs,
			   व्योम *p)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;

	regs->version = IONIC_DEV_CMD_REG_VERSION;

	offset = 0;
	size = IONIC_DEV_INFO_REG_COUNT * माप(u32);
	स_नकल_fromio(p + offset, lअगर->ionic->idev.dev_info_regs->words, size);

	offset += size;
	size = IONIC_DEV_CMD_REG_COUNT * माप(u32);
	स_नकल_fromio(p + offset, lअगर->ionic->idev.dev_cmd_regs->words, size);
पूर्ण

अटल पूर्णांक ionic_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	पूर्णांक copper_seen = 0;

	ethtool_link_ksettings_zero_link_mode(ks, supported);

	अगर (!idev->port_info) अणु
		netdev_err(netdev, "port_info not initialized\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* The port_info data is found in a DMA space that the NIC keeps
	 * up-to-date, so there's no need to request the data from the
	 * NIC, we alपढ़ोy have it in our memory space.
	 */

	चयन (le16_to_cpu(idev->port_info->status.xcvr.pid)) अणु
		/* Copper */
	हाल IONIC_XCVR_PID_QSFP_100G_CR4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseCR4_Full);
		copper_seen++;
		अवरोध;
	हाल IONIC_XCVR_PID_QSFP_40GBASE_CR4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseCR4_Full);
		copper_seen++;
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_25GBASE_CR_S:
	हाल IONIC_XCVR_PID_SFP_25GBASE_CR_L:
	हाल IONIC_XCVR_PID_SFP_25GBASE_CR_N:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseCR_Full);
		copper_seen++;
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_10GBASE_AOC:
	हाल IONIC_XCVR_PID_SFP_10GBASE_CU:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseCR_Full);
		copper_seen++;
		अवरोध;

		/* Fibre */
	हाल IONIC_XCVR_PID_QSFP_100G_SR4:
	हाल IONIC_XCVR_PID_QSFP_100G_AOC:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseSR4_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_QSFP_100G_CWDM4:
	हाल IONIC_XCVR_PID_QSFP_100G_PSM4:
	हाल IONIC_XCVR_PID_QSFP_100G_LR4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseLR4_ER4_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_QSFP_100G_ER4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseLR4_ER4_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_QSFP_40GBASE_SR4:
	हाल IONIC_XCVR_PID_QSFP_40GBASE_AOC:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseSR4_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_QSFP_40GBASE_LR4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseLR4_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_25GBASE_SR:
	हाल IONIC_XCVR_PID_SFP_25GBASE_AOC:
	हाल IONIC_XCVR_PID_SFP_25GBASE_ACC:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseSR_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_10GBASE_SR:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseSR_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_10GBASE_LR:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseLR_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_10GBASE_LRM:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseLRM_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_10GBASE_ER:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseER_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_10GBASE_T:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_SFP_1000BASE_T:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		अवरोध;
	हाल IONIC_XCVR_PID_UNKNOWN:
		/* This means there's no module plugged in */
		अवरोध;
	शेष:
		dev_info(lअगर->ionic->dev, "unknown xcvr type pid=%d / 0x%x\n",
			 idev->port_info->status.xcvr.pid,
			 idev->port_info->status.xcvr.pid);
		अवरोध;
	पूर्ण

	biपंचांगap_copy(ks->link_modes.advertising, ks->link_modes.supported,
		    __ETHTOOL_LINK_MODE_MASK_NBITS);

	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_BASER);
	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_RS);
	अगर (idev->port_info->config.fec_type == IONIC_PORT_FEC_TYPE_FC)
		ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_BASER);
	अन्यथा अगर (idev->port_info->config.fec_type == IONIC_PORT_FEC_TYPE_RS)
		ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_RS);

	ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
	ethtool_link_ksettings_add_link_mode(ks, supported, Pause);

	अगर (idev->port_info->status.xcvr.phy == IONIC_PHY_TYPE_COPPER ||
	    copper_seen)
		ks->base.port = PORT_DA;
	अन्यथा अगर (idev->port_info->status.xcvr.phy == IONIC_PHY_TYPE_FIBER)
		ks->base.port = PORT_FIBRE;
	अन्यथा
		ks->base.port = PORT_NONE;

	अगर (ks->base.port != PORT_NONE) अणु
		ks->base.speed = le32_to_cpu(lअगर->info->status.link_speed);

		अगर (le16_to_cpu(lअगर->info->status.link_status))
			ks->base.duplex = DUPLEX_FULL;
		अन्यथा
			ks->base.duplex = DUPLEX_UNKNOWN;

		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);

		अगर (idev->port_info->config.an_enable) अणु
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     Autoneg);
			ks->base.स्वतःneg = AUTONEG_ENABLE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक err = 0;

	/* set स्वतःneg */
	अगर (ks->base.स्वतःneg != idev->port_info->config.an_enable) अणु
		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_port_स्वतःneg(idev, ks->base.स्वतःneg);
		err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);
		अगर (err)
			वापस err;
	पूर्ण

	/* set speed */
	अगर (ks->base.speed != le32_to_cpu(idev->port_info->config.speed)) अणु
		mutex_lock(&ionic->dev_cmd_lock);
		ionic_dev_cmd_port_speed(idev, ks->base.speed);
		err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&ionic->dev_cmd_lock);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ionic_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	u8 छोड़ो_type;

	छोड़ो->स्वतःneg = 0;

	छोड़ो_type = lअगर->ionic->idev.port_info->config.छोड़ो_type;
	अगर (छोड़ो_type) अणु
		छोड़ो->rx_छोड़ो = (छोड़ो_type & IONIC_PAUSE_F_RX) ? 1 : 0;
		छोड़ो->tx_छोड़ो = (छोड़ो_type & IONIC_PAUSE_F_TX) ? 1 : 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_set_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	u32 requested_छोड़ो;
	पूर्णांक err;

	अगर (छोड़ो->स्वतःneg)
		वापस -EOPNOTSUPP;

	/* change both at the same समय */
	requested_छोड़ो = IONIC_PORT_PAUSE_TYPE_LINK;
	अगर (छोड़ो->rx_छोड़ो)
		requested_छोड़ो |= IONIC_PAUSE_F_RX;
	अगर (छोड़ो->tx_छोड़ो)
		requested_छोड़ो |= IONIC_PAUSE_F_TX;

	अगर (requested_छोड़ो == lअगर->ionic->idev.port_info->config.छोड़ो_type)
		वापस 0;

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_port_छोड़ो(&lअगर->ionic->idev, requested_छोड़ो);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_get_fecparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	चयन (lअगर->ionic->idev.port_info->config.fec_type) अणु
	हाल IONIC_PORT_FEC_TYPE_NONE:
		fec->active_fec = ETHTOOL_FEC_OFF;
		अवरोध;
	हाल IONIC_PORT_FEC_TYPE_RS:
		fec->active_fec = ETHTOOL_FEC_RS;
		अवरोध;
	हाल IONIC_PORT_FEC_TYPE_FC:
		fec->active_fec = ETHTOOL_FEC_BASER;
		अवरोध;
	पूर्ण

	fec->fec = ETHTOOL_FEC_OFF | ETHTOOL_FEC_RS | ETHTOOL_FEC_BASER;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_set_fecparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	u8 fec_type;
	पूर्णांक ret = 0;

	अगर (lअगर->ionic->idev.port_info->config.an_enable) अणु
		netdev_err(netdev, "FEC request not allowed while autoneg is enabled\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fec->fec) अणु
	हाल ETHTOOL_FEC_NONE:
		fec_type = IONIC_PORT_FEC_TYPE_NONE;
		अवरोध;
	हाल ETHTOOL_FEC_OFF:
		fec_type = IONIC_PORT_FEC_TYPE_NONE;
		अवरोध;
	हाल ETHTOOL_FEC_RS:
		fec_type = IONIC_PORT_FEC_TYPE_RS;
		अवरोध;
	हाल ETHTOOL_FEC_BASER:
		fec_type = IONIC_PORT_FEC_TYPE_FC;
		अवरोध;
	हाल ETHTOOL_FEC_AUTO:
	शेष:
		netdev_err(netdev, "FEC request 0x%04x not supported\n",
			   fec->fec);
		वापस -EINVAL;
	पूर्ण

	अगर (fec_type != lअगर->ionic->idev.port_info->config.fec_type) अणु
		mutex_lock(&lअगर->ionic->dev_cmd_lock);
		ionic_dev_cmd_port_fec(&lअगर->ionic->idev, fec_type);
		ret = ionic_dev_cmd_रुको(lअगर->ionic, DEVCMD_TIMEOUT);
		mutex_unlock(&lअगर->ionic->dev_cmd_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ionic_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	coalesce->tx_coalesce_usecs = lअगर->tx_coalesce_usecs;
	coalesce->rx_coalesce_usecs = lअगर->rx_coalesce_usecs;

	अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
		coalesce->use_adaptive_tx_coalesce = test_bit(IONIC_LIF_F_TX_DIM_INTR, lअगर->state);
	अन्यथा
		coalesce->use_adaptive_tx_coalesce = 0;

	coalesce->use_adaptive_rx_coalesce = test_bit(IONIC_LIF_F_RX_DIM_INTR, lअगर->state);

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_identity *ident;
	u32 rx_coal, rx_dim;
	u32 tx_coal, tx_dim;
	अचिन्हित पूर्णांक i;

	ident = &lअगर->ionic->ident;
	अगर (ident->dev.पूर्णांकr_coal_भाग == 0) अणु
		netdev_warn(netdev, "bad HW value in dev.intr_coal_div = %d\n",
			    ident->dev.पूर्णांकr_coal_भाग);
		वापस -EIO;
	पूर्ण

	/* Tx normally shares Rx पूर्णांकerrupt, so only change Rx अगर not split */
	अगर (!test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state) &&
	    (coalesce->tx_coalesce_usecs != lअगर->rx_coalesce_usecs ||
	     coalesce->use_adaptive_tx_coalesce)) अणु
		netdev_warn(netdev, "only rx parameters can be changed\n");
		वापस -EINVAL;
	पूर्ण

	/* Convert the usec request to a HW usable value.  If they asked
	 * क्रम non-zero and it resolved to zero, bump it up
	 */
	rx_coal = ionic_coal_usec_to_hw(lअगर->ionic, coalesce->rx_coalesce_usecs);
	अगर (!rx_coal && coalesce->rx_coalesce_usecs)
		rx_coal = 1;
	tx_coal = ionic_coal_usec_to_hw(lअगर->ionic, coalesce->tx_coalesce_usecs);
	अगर (!tx_coal && coalesce->tx_coalesce_usecs)
		tx_coal = 1;

	अगर (rx_coal > IONIC_INTR_CTRL_COAL_MAX ||
	    tx_coal > IONIC_INTR_CTRL_COAL_MAX)
		वापस -दुस्फल;

	/* Save the new values */
	lअगर->rx_coalesce_usecs = coalesce->rx_coalesce_usecs;
	lअगर->rx_coalesce_hw = rx_coal;

	अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
		lअगर->tx_coalesce_usecs = coalesce->tx_coalesce_usecs;
	अन्यथा
		lअगर->tx_coalesce_usecs = coalesce->rx_coalesce_usecs;
	lअगर->tx_coalesce_hw = tx_coal;

	अगर (coalesce->use_adaptive_rx_coalesce) अणु
		set_bit(IONIC_LIF_F_RX_DIM_INTR, lअगर->state);
		rx_dim = rx_coal;
	पूर्ण अन्यथा अणु
		clear_bit(IONIC_LIF_F_RX_DIM_INTR, lअगर->state);
		rx_dim = 0;
	पूर्ण

	अगर (coalesce->use_adaptive_tx_coalesce) अणु
		set_bit(IONIC_LIF_F_TX_DIM_INTR, lअगर->state);
		tx_dim = tx_coal;
	पूर्ण अन्यथा अणु
		clear_bit(IONIC_LIF_F_TX_DIM_INTR, lअगर->state);
		tx_dim = 0;
	पूर्ण

	अगर (test_bit(IONIC_LIF_F_UP, lअगर->state)) अणु
		क्रम (i = 0; i < lअगर->nxqs; i++) अणु
			अगर (lअगर->rxqcqs[i]->flags & IONIC_QCQ_F_INTR) अणु
				ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
						     lअगर->rxqcqs[i]->पूर्णांकr.index,
						     lअगर->rx_coalesce_hw);
				lअगर->rxqcqs[i]->पूर्णांकr.dim_coal_hw = rx_dim;
			पूर्ण

			अगर (lअगर->txqcqs[i]->flags & IONIC_QCQ_F_INTR) अणु
				ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
						     lअगर->txqcqs[i]->पूर्णांकr.index,
						     lअगर->tx_coalesce_hw);
				lअगर->txqcqs[i]->पूर्णांकr.dim_coal_hw = tx_dim;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ionic_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	ring->tx_max_pending = IONIC_MAX_TX_DESC;
	ring->tx_pending = lअगर->ntxq_descs;
	ring->rx_max_pending = IONIC_MAX_RX_DESC;
	ring->rx_pending = lअगर->nrxq_descs;
पूर्ण

अटल पूर्णांक ionic_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_queue_params qparam;
	पूर्णांक err;

	ionic_init_queue_params(lअगर, &qparam);

	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending) अणु
		netdev_info(netdev, "Changing jumbo or mini descriptors not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(ring->tx_pending) ||
	    !is_घातer_of_2(ring->rx_pending)) अणु
		netdev_info(netdev, "Descriptor count must be a power of 2\n");
		वापस -EINVAL;
	पूर्ण

	/* अगर nothing to करो वापस success */
	अगर (ring->tx_pending == lअगर->ntxq_descs &&
	    ring->rx_pending == lअगर->nrxq_descs)
		वापस 0;

	अगर (ring->tx_pending != lअगर->ntxq_descs)
		netdev_info(netdev, "Changing Tx ring size from %d to %d\n",
			    lअगर->ntxq_descs, ring->tx_pending);

	अगर (ring->rx_pending != lअगर->nrxq_descs)
		netdev_info(netdev, "Changing Rx ring size from %d to %d\n",
			    lअगर->nrxq_descs, ring->rx_pending);

	/* अगर we're not running, just set the values and वापस */
	अगर (!netअगर_running(lअगर->netdev)) अणु
		lअगर->ntxq_descs = ring->tx_pending;
		lअगर->nrxq_descs = ring->rx_pending;
		वापस 0;
	पूर्ण

	qparam.ntxq_descs = ring->tx_pending;
	qparam.nrxq_descs = ring->rx_pending;
	err = ionic_reconfigure_queues(lअगर, &qparam);
	अगर (err)
		netdev_info(netdev, "Ring reconfiguration failed, changes canceled: %d\n", err);

	वापस err;
पूर्ण

अटल व्योम ionic_get_channels(काष्ठा net_device *netdev,
			       काष्ठा ethtool_channels *ch)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	/* report maximum channels */
	ch->max_combined = lअगर->ionic->ntxqs_per_lअगर;
	ch->max_rx = lअगर->ionic->ntxqs_per_lअगर / 2;
	ch->max_tx = lअगर->ionic->ntxqs_per_lअगर / 2;

	/* report current channels */
	अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state)) अणु
		ch->rx_count = lअगर->nxqs;
		ch->tx_count = lअगर->nxqs;
	पूर्ण अन्यथा अणु
		ch->combined_count = lअगर->nxqs;
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_set_channels(काष्ठा net_device *netdev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_queue_params qparam;
	पूर्णांक max_cnt;
	पूर्णांक err;

	ionic_init_queue_params(lअगर, &qparam);

	अगर (ch->rx_count != ch->tx_count) अणु
		netdev_info(netdev, "The rx and tx count must be equal\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ch->combined_count && ch->rx_count) अणु
		netdev_info(netdev, "Use either combined or rx and tx, not both\n");
		वापस -EINVAL;
	पूर्ण

	max_cnt = lअगर->ionic->ntxqs_per_lअगर;
	अगर (ch->combined_count) अणु
		अगर (ch->combined_count > max_cnt)
			वापस -EINVAL;

		अगर (test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
			netdev_info(lअगर->netdev, "Sharing queue interrupts\n");
		अन्यथा अगर (ch->combined_count == lअगर->nxqs)
			वापस 0;

		अगर (lअगर->nxqs != ch->combined_count)
			netdev_info(netdev, "Changing queue count from %d to %d\n",
				    lअगर->nxqs, ch->combined_count);

		qparam.nxqs = ch->combined_count;
		qparam.पूर्णांकr_split = 0;
	पूर्ण अन्यथा अणु
		max_cnt /= 2;
		अगर (ch->rx_count > max_cnt)
			वापस -EINVAL;

		अगर (!test_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state))
			netdev_info(lअगर->netdev, "Splitting queue interrupts\n");
		अन्यथा अगर (ch->rx_count == lअगर->nxqs)
			वापस 0;

		अगर (lअगर->nxqs != ch->rx_count)
			netdev_info(netdev, "Changing queue count from %d to %d\n",
				    lअगर->nxqs, ch->rx_count);

		qparam.nxqs = ch->rx_count;
		qparam.पूर्णांकr_split = 1;
	पूर्ण

	/* अगर we're not running, just set the values and वापस */
	अगर (!netअगर_running(lअगर->netdev)) अणु
		lअगर->nxqs = qparam.nxqs;

		अगर (qparam.पूर्णांकr_split) अणु
			set_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state);
		पूर्ण अन्यथा अणु
			clear_bit(IONIC_LIF_F_SPLIT_INTR, lअगर->state);
			lअगर->tx_coalesce_usecs = lअगर->rx_coalesce_usecs;
			lअगर->tx_coalesce_hw = lअगर->rx_coalesce_hw;
		पूर्ण
		वापस 0;
	पूर्ण

	err = ionic_reconfigure_queues(lअगर, &qparam);
	अगर (err)
		netdev_info(netdev, "Queue reconfiguration failed, changes canceled: %d\n", err);

	वापस err;
पूर्ण

अटल u32 ionic_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	u32 priv_flags = 0;

	अगर (test_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state))
		priv_flags |= IONIC_PRIV_F_SW_DBG_STATS;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक ionic_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	clear_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state);
	अगर (priv_flags & IONIC_PRIV_F_SW_DBG_STATS)
		set_bit(IONIC_LIF_F_SW_DEBUG_STATS, lअगर->state);

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_get_rxnfc(काष्ठा net_device *netdev,
			   काष्ठा ethtool_rxnfc *info, u32 *rules)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = lअगर->nxqs;
		अवरोध;
	शेष:
		netdev_err(netdev, "Command parameter %d is not supported\n",
			   info->cmd);
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल u32 ionic_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	वापस le16_to_cpu(lअगर->ionic->ident.lअगर.eth.rss_ind_tbl_sz);
पूर्ण

अटल u32 ionic_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस IONIC_RSS_HASH_KEY_SIZE;
पूर्ण

अटल पूर्णांक ionic_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			  u8 *hfunc)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	अचिन्हित पूर्णांक i, tbl_sz;

	अगर (indir) अणु
		tbl_sz = le16_to_cpu(lअगर->ionic->ident.lअगर.eth.rss_ind_tbl_sz);
		क्रम (i = 0; i < tbl_sz; i++)
			indir[i] = lअगर->rss_ind_tbl[i];
	पूर्ण

	अगर (key)
		स_नकल(key, lअगर->rss_hash_key, IONIC_RSS_HASH_KEY_SIZE);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	वापस ionic_lअगर_rss_config(lअगर, lअगर->rss_types, key, indir);
पूर्ण

अटल पूर्णांक ionic_set_tunable(काष्ठा net_device *dev,
			     स्थिर काष्ठा ethtool_tunable *tuna,
			     स्थिर व्योम *data)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(dev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		lअगर->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_get_tunable(काष्ठा net_device *netdev,
			     स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = lअगर->rx_copyअवरोध;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_get_module_info(काष्ठा net_device *netdev,
				 काष्ठा ethtool_modinfo *modinfo)

अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा ionic_xcvr_status *xcvr;
	काष्ठा sfp_eeprom_base *sfp;

	xcvr = &idev->port_info->status.xcvr;
	sfp = (काष्ठा sfp_eeprom_base *) xcvr->sprom;

	/* report the module data type and length */
	चयन (sfp->phys_id) अणु
	हाल SFF8024_ID_SFP:
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		अवरोध;
	हाल SFF8024_ID_QSFP_8436_8636:
	हाल SFF8024_ID_QSFP28_8636:
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		अवरोध;
	शेष:
		netdev_info(netdev, "unknown xcvr type 0x%02x\n",
			    xcvr->sprom[0]);
		modinfo->type = 0;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_get_module_eeprom(काष्ठा net_device *netdev,
				   काष्ठा ethtool_eeprom *ee,
				   u8 *data)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_dev *idev = &lअगर->ionic->idev;
	काष्ठा ionic_xcvr_status *xcvr;
	अक्षर tbuf[माप(xcvr->sprom)];
	पूर्णांक count = 10;
	u32 len;

	/* The NIC keeps the module prom up-to-date in the DMA space
	 * so we can simply copy the module bytes पूर्णांकo the data buffer.
	 */
	xcvr = &idev->port_info->status.xcvr;
	len = min_t(u32, माप(xcvr->sprom), ee->len);

	करो अणु
		स_नकल(data, xcvr->sprom, len);
		स_नकल(tbuf, xcvr->sprom, len);

		/* Let's make sure we got a consistent copy */
		अगर (!स_भेद(data, tbuf, len))
			अवरोध;

	पूर्ण जबतक (--count);

	अगर (!count)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_get_ts_info(काष्ठा net_device *netdev,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	__le64 mask;

	अगर (!lअगर->phc || !lअगर->phc->ptp)
		वापस ethtool_op_get_ts_info(netdev, info);

	info->phc_index = ptp_घड़ी_index(lअगर->phc->ptp);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	/* tx modes */

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	mask = cpu_to_le64(BIT_ULL(IONIC_TXSTAMP_ONESTEP_SYNC));
	अगर (ionic->ident.lअगर.eth.hwstamp_tx_modes & mask)
		info->tx_types |= BIT(HWTSTAMP_TX_ONESTEP_SYNC);

	mask = cpu_to_le64(BIT_ULL(IONIC_TXSTAMP_ONESTEP_P2P));
	अगर (ionic->ident.lअगर.eth.hwstamp_tx_modes & mask)
		info->tx_types |= BIT(HWTSTAMP_TX_ONESTEP_P2P);

	/* rx filters */

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_ALL);

	mask = cpu_to_le64(IONIC_PKT_CLS_NTP_ALL);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_NTP_ALL);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP1_SYNC);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V1_L4_SYNC);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP1_DREQ);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP1_ALL);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V1_L4_EVENT);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_L4_SYNC);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L4_SYNC);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_L4_DREQ);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_L4_ALL);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L4_EVENT);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_L2_SYNC);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L2_SYNC);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_L2_DREQ);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_L2_ALL);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L2_EVENT);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_SYNC);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_SYNC);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_DREQ);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_DELAY_REQ);

	mask = cpu_to_le64(IONIC_PKT_CLS_PTP2_ALL);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) == mask)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic *ionic = lअगर->ionic;
	पूर्णांक err = 0;

	/* flap the link to क्रमce स्वतः-negotiation */

	mutex_lock(&ionic->dev_cmd_lock);

	ionic_dev_cmd_port_state(&ionic->idev, IONIC_PORT_ADMIN_STATE_DOWN);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);

	अगर (!err) अणु
		ionic_dev_cmd_port_state(&ionic->idev, IONIC_PORT_ADMIN_STATE_UP);
		err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	पूर्ण

	mutex_unlock(&ionic->dev_cmd_lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ionic_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_TX,
	.get_drvinfo		= ionic_get_drvinfo,
	.get_regs_len		= ionic_get_regs_len,
	.get_regs		= ionic_get_regs,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= ionic_get_link_ksettings,
	.set_link_ksettings	= ionic_set_link_ksettings,
	.get_coalesce		= ionic_get_coalesce,
	.set_coalesce		= ionic_set_coalesce,
	.get_ringparam		= ionic_get_ringparam,
	.set_ringparam		= ionic_set_ringparam,
	.get_channels		= ionic_get_channels,
	.set_channels		= ionic_set_channels,
	.get_strings		= ionic_get_strings,
	.get_ethtool_stats	= ionic_get_stats,
	.get_sset_count		= ionic_get_sset_count,
	.get_priv_flags		= ionic_get_priv_flags,
	.set_priv_flags		= ionic_set_priv_flags,
	.get_rxnfc		= ionic_get_rxnfc,
	.get_rxfh_indir_size	= ionic_get_rxfh_indir_size,
	.get_rxfh_key_size	= ionic_get_rxfh_key_size,
	.get_rxfh		= ionic_get_rxfh,
	.set_rxfh		= ionic_set_rxfh,
	.get_tunable		= ionic_get_tunable,
	.set_tunable		= ionic_set_tunable,
	.get_module_info	= ionic_get_module_info,
	.get_module_eeprom	= ionic_get_module_eeprom,
	.get_छोड़ोparam		= ionic_get_छोड़ोparam,
	.set_छोड़ोparam		= ionic_set_छोड़ोparam,
	.get_fecparam		= ionic_get_fecparam,
	.set_fecparam		= ionic_set_fecparam,
	.get_ts_info		= ionic_get_ts_info,
	.nway_reset		= ionic_nway_reset,
पूर्ण;

व्योम ionic_ethtool_set_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ionic_ethtool_ops;
पूर्ण
