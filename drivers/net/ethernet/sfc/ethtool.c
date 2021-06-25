<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/in.h>
#समावेश "net_driver.h"
#समावेश "workarounds.h"
#समावेश "selftest.h"
#समावेश "efx.h"
#समावेश "efx_channels.h"
#समावेश "rx_common.h"
#समावेश "tx_common.h"
#समावेश "ethtool_common.h"
#समावेश "filter.h"
#समावेश "nic.h"

#घोषणा EFX_ETHTOOL_EEPROM_MAGIC 0xEFAB

/**************************************************************************
 *
 * Ethtool operations
 *
 **************************************************************************
 */

/* Identअगरy device by flashing LEDs */
अटल पूर्णांक efx_ethtool_phys_id(काष्ठा net_device *net_dev,
			       क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	क्रमागत efx_led_mode mode = EFX_LED_DEFAULT;

	चयन (state) अणु
	हाल ETHTOOL_ID_ON:
		mode = EFX_LED_ON;
		अवरोध;
	हाल ETHTOOL_ID_OFF:
		mode = EFX_LED_OFF;
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		mode = EFX_LED_DEFAULT;
		अवरोध;
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */
	पूर्ण

	वापस efx_mcdi_set_id_led(efx, mode);
पूर्ण

अटल पूर्णांक efx_ethtool_get_regs_len(काष्ठा net_device *net_dev)
अणु
	वापस efx_nic_get_regs_len(netdev_priv(net_dev));
पूर्ण

अटल व्योम efx_ethtool_get_regs(काष्ठा net_device *net_dev,
				 काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	regs->version = efx->type->revision;
	efx_nic_get_regs(efx, buf);
पूर्ण

/*
 * Each channel has a single IRQ and moderation समयr, started by any
 * completion (or other event).  Unless the module parameter
 * separate_tx_channels is set, IRQs and moderation are thereक्रमe
 * shared between RX and TX completions.  In this हाल, when RX IRQ
 * moderation is explicitly changed then TX IRQ moderation is
 * स्वतःmatically changed too, but otherwise we fail अगर the two values
 * are requested to be dअगरferent.
 *
 * The hardware करोes not support a limit on the number of completions
 * beक्रमe an IRQ, so we करो not use the max_frames fields.  We should
 * report and require that max_frames == (usecs != 0), but this would
 * invalidate existing user करोcumentation.
 *
 * The hardware करोes not have distinct settings क्रम पूर्णांकerrupt
 * moderation जबतक the previous IRQ is being handled, so we should
 * not use the 'irq' fields.  However, an earlier developer
 * misunderstood the meaning of the 'irq' fields and the driver did
 * not support the standard fields.  To aव्योम invalidating existing
 * user करोcumentation, we report and accept changes through either the
 * standard or 'irq' fields.  If both are changed at the same समय, we
 * prefer the standard field.
 *
 * We implement adaptive IRQ moderation, but use a dअगरferent algorithm
 * from that assumed in the definition of काष्ठा ethtool_coalesce.
 * Thereक्रमe we करो not use any of the adaptive moderation parameters
 * in it.
 */

अटल पूर्णांक efx_ethtool_get_coalesce(काष्ठा net_device *net_dev,
				    काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	अचिन्हित पूर्णांक tx_usecs, rx_usecs;
	bool rx_adaptive;

	efx_get_irq_moderation(efx, &tx_usecs, &rx_usecs, &rx_adaptive);

	coalesce->tx_coalesce_usecs = tx_usecs;
	coalesce->tx_coalesce_usecs_irq = tx_usecs;
	coalesce->rx_coalesce_usecs = rx_usecs;
	coalesce->rx_coalesce_usecs_irq = rx_usecs;
	coalesce->use_adaptive_rx_coalesce = rx_adaptive;

	वापस 0;
पूर्ण

अटल पूर्णांक efx_ethtool_set_coalesce(काष्ठा net_device *net_dev,
				    काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक tx_usecs, rx_usecs;
	bool adaptive, rx_may_override_tx;
	पूर्णांक rc;

	efx_get_irq_moderation(efx, &tx_usecs, &rx_usecs, &adaptive);

	अगर (coalesce->rx_coalesce_usecs != rx_usecs)
		rx_usecs = coalesce->rx_coalesce_usecs;
	अन्यथा
		rx_usecs = coalesce->rx_coalesce_usecs_irq;

	adaptive = coalesce->use_adaptive_rx_coalesce;

	/* If channels are shared, TX IRQ moderation can be quietly
	 * overridden unless it is changed from its old value.
	 */
	rx_may_override_tx = (coalesce->tx_coalesce_usecs == tx_usecs &&
			      coalesce->tx_coalesce_usecs_irq == tx_usecs);
	अगर (coalesce->tx_coalesce_usecs != tx_usecs)
		tx_usecs = coalesce->tx_coalesce_usecs;
	अन्यथा
		tx_usecs = coalesce->tx_coalesce_usecs_irq;

	rc = efx_init_irq_moderation(efx, tx_usecs, rx_usecs, adaptive,
				     rx_may_override_tx);
	अगर (rc != 0)
		वापस rc;

	efx_क्रम_each_channel(channel, efx)
		efx->type->push_irq_moderation(channel);

	वापस 0;
पूर्ण

अटल व्योम efx_ethtool_get_ringparam(काष्ठा net_device *net_dev,
				      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	ring->rx_max_pending = EFX_MAX_DMAQ_SIZE;
	ring->tx_max_pending = EFX_TXQ_MAX_ENT(efx);
	ring->rx_pending = efx->rxq_entries;
	ring->tx_pending = efx->txq_entries;
पूर्ण

अटल पूर्णांक efx_ethtool_set_ringparam(काष्ठा net_device *net_dev,
				     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	u32 txq_entries;

	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending ||
	    ring->rx_pending > EFX_MAX_DMAQ_SIZE ||
	    ring->tx_pending > EFX_TXQ_MAX_ENT(efx))
		वापस -EINVAL;

	अगर (ring->rx_pending < EFX_RXQ_MIN_ENT) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "RX queues cannot be smaller than %u\n",
			  EFX_RXQ_MIN_ENT);
		वापस -EINVAL;
	पूर्ण

	txq_entries = max(ring->tx_pending, EFX_TXQ_MIN_ENT(efx));
	अगर (txq_entries != ring->tx_pending)
		netअगर_warn(efx, drv, efx->net_dev,
			   "increasing TX queue size to minimum of %u\n",
			   txq_entries);

	वापस efx_पुनः_स्मृति_channels(efx, ring->rx_pending, txq_entries);
पूर्ण

अटल व्योम efx_ethtool_get_wol(काष्ठा net_device *net_dev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	वापस efx->type->get_wol(efx, wol);
पूर्ण


अटल पूर्णांक efx_ethtool_set_wol(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	वापस efx->type->set_wol(efx, wol->wolopts);
पूर्ण

अटल व्योम efx_ethtool_get_fec_stats(काष्ठा net_device *net_dev,
				      काष्ठा ethtool_fec_stats *fec_stats)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->get_fec_stats)
		efx->type->get_fec_stats(efx, fec_stats);
पूर्ण

अटल पूर्णांक efx_ethtool_get_ts_info(काष्ठा net_device *net_dev,
				   काष्ठा ethtool_ts_info *ts_info)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	/* Software capabilities */
	ts_info->so_बारtamping = (SOF_TIMESTAMPING_RX_SOFTWARE |
				    SOF_TIMESTAMPING_SOFTWARE);
	ts_info->phc_index = -1;

	efx_ptp_get_ts_info(efx, ts_info);
	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops efx_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USECS_IRQ |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_drvinfo		= efx_ethtool_get_drvinfo,
	.get_regs_len		= efx_ethtool_get_regs_len,
	.get_regs		= efx_ethtool_get_regs,
	.get_msglevel		= efx_ethtool_get_msglevel,
	.set_msglevel		= efx_ethtool_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= efx_ethtool_get_coalesce,
	.set_coalesce		= efx_ethtool_set_coalesce,
	.get_ringparam		= efx_ethtool_get_ringparam,
	.set_ringparam		= efx_ethtool_set_ringparam,
	.get_छोड़ोparam         = efx_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam         = efx_ethtool_set_छोड़ोparam,
	.get_sset_count		= efx_ethtool_get_sset_count,
	.self_test		= efx_ethtool_self_test,
	.get_strings		= efx_ethtool_get_strings,
	.set_phys_id		= efx_ethtool_phys_id,
	.get_ethtool_stats	= efx_ethtool_get_stats,
	.get_wol                = efx_ethtool_get_wol,
	.set_wol                = efx_ethtool_set_wol,
	.reset			= efx_ethtool_reset,
	.get_rxnfc		= efx_ethtool_get_rxnfc,
	.set_rxnfc		= efx_ethtool_set_rxnfc,
	.get_rxfh_indir_size	= efx_ethtool_get_rxfh_indir_size,
	.get_rxfh_key_size	= efx_ethtool_get_rxfh_key_size,
	.get_rxfh		= efx_ethtool_get_rxfh,
	.set_rxfh		= efx_ethtool_set_rxfh,
	.get_rxfh_context	= efx_ethtool_get_rxfh_context,
	.set_rxfh_context	= efx_ethtool_set_rxfh_context,
	.get_ts_info		= efx_ethtool_get_ts_info,
	.get_module_info	= efx_ethtool_get_module_info,
	.get_module_eeprom	= efx_ethtool_get_module_eeprom,
	.get_link_ksettings	= efx_ethtool_get_link_ksettings,
	.set_link_ksettings	= efx_ethtool_set_link_ksettings,
	.get_fec_stats		= efx_ethtool_get_fec_stats,
	.get_fecparam		= efx_ethtool_get_fecparam,
	.set_fecparam		= efx_ethtool_set_fecparam,
पूर्ण;
