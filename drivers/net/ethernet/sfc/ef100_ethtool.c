<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "mcdi_port_common.h"
#समावेश "ethtool_common.h"
#समावेश "ef100_ethtool.h"
#समावेश "mcdi_functions.h"

/* This is the maximum number of descriptor rings supported by the QDMA */
#घोषणा EFX_EF100_MAX_DMAQ_SIZE 16384UL

अटल व्योम ef100_ethtool_get_ringparam(काष्ठा net_device *net_dev,
					काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	ring->rx_max_pending = EFX_EF100_MAX_DMAQ_SIZE;
	ring->tx_max_pending = EFX_EF100_MAX_DMAQ_SIZE;
	ring->rx_pending = efx->rxq_entries;
	ring->tx_pending = efx->txq_entries;
पूर्ण

/*	Ethtool options available
 */
स्थिर काष्ठा ethtool_ops ef100_ethtool_ops = अणु
	.get_drvinfo		= efx_ethtool_get_drvinfo,
	.get_msglevel		= efx_ethtool_get_msglevel,
	.set_msglevel		= efx_ethtool_set_msglevel,
	.get_छोड़ोparam         = efx_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam         = efx_ethtool_set_छोड़ोparam,
	.get_sset_count		= efx_ethtool_get_sset_count,
	.self_test		= efx_ethtool_self_test,
	.get_strings		= efx_ethtool_get_strings,
	.get_link_ksettings	= efx_ethtool_get_link_ksettings,
	.set_link_ksettings	= efx_ethtool_set_link_ksettings,
	.get_link		= ethtool_op_get_link,
	.get_ringparam		= ef100_ethtool_get_ringparam,
	.get_fecparam		= efx_ethtool_get_fecparam,
	.set_fecparam		= efx_ethtool_set_fecparam,
	.get_ethtool_stats	= efx_ethtool_get_stats,
	.get_rxnfc              = efx_ethtool_get_rxnfc,
	.set_rxnfc              = efx_ethtool_set_rxnfc,
	.reset                  = efx_ethtool_reset,

	.get_rxfh_indir_size	= efx_ethtool_get_rxfh_indir_size,
	.get_rxfh_key_size	= efx_ethtool_get_rxfh_key_size,
	.get_rxfh		= efx_ethtool_get_rxfh,
	.set_rxfh		= efx_ethtool_set_rxfh,
	.get_rxfh_context	= efx_ethtool_get_rxfh_context,
	.set_rxfh_context	= efx_ethtool_set_rxfh_context,

	.get_module_info	= efx_ethtool_get_module_info,
	.get_module_eeprom	= efx_ethtool_get_module_eeprom,
पूर्ण;
