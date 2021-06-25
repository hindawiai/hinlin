<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/debugfs.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अक्रमom.h>

#समावेश "netdevsim.h"

अटल व्योम
nsim_get_छोड़ो_stats(काष्ठा net_device *dev,
		     काष्ठा ethtool_छोड़ो_stats *छोड़ो_stats)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	अगर (ns->ethtool.छोड़ोparam.report_stats_rx)
		छोड़ो_stats->rx_छोड़ो_frames = 1;
	अगर (ns->ethtool.छोड़ोparam.report_stats_tx)
		छोड़ो_stats->tx_छोड़ो_frames = 2;
पूर्ण

अटल व्योम
nsim_get_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	छोड़ो->स्वतःneg = 0; /* We करोn't support ksettings, so can't pretend */
	छोड़ो->rx_छोड़ो = ns->ethtool.छोड़ोparam.rx;
	छोड़ो->tx_छोड़ो = ns->ethtool.छोड़ोparam.tx;
पूर्ण

अटल पूर्णांक
nsim_set_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	अगर (छोड़ो->स्वतःneg)
		वापस -EINVAL;

	ns->ethtool.छोड़ोparam.rx = छोड़ो->rx_छोड़ो;
	ns->ethtool.छोड़ोparam.tx = छोड़ो->tx_छोड़ो;
	वापस 0;
पूर्ण

अटल पूर्णांक nsim_get_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	स_नकल(coal, &ns->ethtool.coalesce, माप(ns->ethtool.coalesce));
	वापस 0;
पूर्ण

अटल पूर्णांक nsim_set_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	स_नकल(&ns->ethtool.coalesce, coal, माप(ns->ethtool.coalesce));
	वापस 0;
पूर्ण

अटल व्योम nsim_get_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	स_नकल(ring, &ns->ethtool.ring, माप(ns->ethtool.ring));
पूर्ण

अटल पूर्णांक nsim_set_ringparam(काष्ठा net_device *dev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	स_नकल(&ns->ethtool.ring, ring, माप(ns->ethtool.ring));
	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_get_fecparam(काष्ठा net_device *dev, काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);

	अगर (ns->ethtool.get_err)
		वापस -ns->ethtool.get_err;
	स_नकल(fecparam, &ns->ethtool.fec, माप(ns->ethtool.fec));
	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_set_fecparam(काष्ठा net_device *dev, काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा netdevsim *ns = netdev_priv(dev);
	u32 fec;

	अगर (ns->ethtool.set_err)
		वापस -ns->ethtool.set_err;
	स_नकल(&ns->ethtool.fec, fecparam, माप(ns->ethtool.fec));
	fec = fecparam->fec;
	अगर (fec == ETHTOOL_FEC_AUTO)
		fec |= ETHTOOL_FEC_OFF;
	fec |= ETHTOOL_FEC_NONE;
	ns->ethtool.fec.active_fec = 1 << (fls(fec) - 1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops nsim_ethtool_ops = अणु
	.supported_coalesce_params	= ETHTOOL_COALESCE_ALL_PARAMS,
	.get_छोड़ो_stats	        = nsim_get_छोड़ो_stats,
	.get_छोड़ोparam		        = nsim_get_छोड़ोparam,
	.set_छोड़ोparam		        = nsim_set_छोड़ोparam,
	.set_coalesce			= nsim_set_coalesce,
	.get_coalesce			= nsim_get_coalesce,
	.get_ringparam			= nsim_get_ringparam,
	.set_ringparam			= nsim_set_ringparam,
	.get_fecparam			= nsim_get_fecparam,
	.set_fecparam			= nsim_set_fecparam,
पूर्ण;

अटल व्योम nsim_ethtool_ring_init(काष्ठा netdevsim *ns)
अणु
	ns->ethtool.ring.rx_max_pending = 4096;
	ns->ethtool.ring.rx_jumbo_max_pending = 4096;
	ns->ethtool.ring.rx_mini_max_pending = 4096;
	ns->ethtool.ring.tx_max_pending = 4096;
पूर्ण

व्योम nsim_ethtool_init(काष्ठा netdevsim *ns)
अणु
	काष्ठा dentry *ethtool, *dir;

	ns->netdev->ethtool_ops = &nsim_ethtool_ops;

	nsim_ethtool_ring_init(ns);

	ns->ethtool.fec.fec = ETHTOOL_FEC_NONE;
	ns->ethtool.fec.active_fec = ETHTOOL_FEC_NONE;

	ethtool = debugfs_create_dir("ethtool", ns->nsim_dev_port->ddir);

	debugfs_create_u32("get_err", 0600, ethtool, &ns->ethtool.get_err);
	debugfs_create_u32("set_err", 0600, ethtool, &ns->ethtool.set_err);

	dir = debugfs_create_dir("pause", ethtool);
	debugfs_create_bool("report_stats_rx", 0600, dir,
			    &ns->ethtool.छोड़ोparam.report_stats_rx);
	debugfs_create_bool("report_stats_tx", 0600, dir,
			    &ns->ethtool.छोड़ोparam.report_stats_tx);

	dir = debugfs_create_dir("ring", ethtool);
	debugfs_create_u32("rx_max_pending", 0600, dir,
			   &ns->ethtool.ring.rx_max_pending);
	debugfs_create_u32("rx_jumbo_max_pending", 0600, dir,
			   &ns->ethtool.ring.rx_jumbo_max_pending);
	debugfs_create_u32("rx_mini_max_pending", 0600, dir,
			   &ns->ethtool.ring.rx_mini_max_pending);
	debugfs_create_u32("tx_max_pending", 0600, dir,
			   &ns->ethtool.ring.tx_max_pending);
पूर्ण
