<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2021, Microsoft Corporation. */

#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>

#समावेश "mana.h"

अटल स्थिर काष्ठा अणु
	अक्षर name[ETH_GSTRING_LEN];
	u16 offset;
पूर्ण mana_eth_stats[] = अणु
	अणु"stop_queue", दुरत्व(काष्ठा mana_ethtool_stats, stop_queue)पूर्ण,
	अणु"wake_queue", दुरत्व(काष्ठा mana_ethtool_stats, wake_queue)पूर्ण,
पूर्ण;

अटल पूर्णांक mana_get_sset_count(काष्ठा net_device *ndev, पूर्णांक stringset)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	अचिन्हित पूर्णांक num_queues = apc->num_queues;

	अगर (stringset != ETH_SS_STATS)
		वापस -EINVAL;

	वापस ARRAY_SIZE(mana_eth_stats) + num_queues * 4;
पूर्ण

अटल व्योम mana_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	अचिन्हित पूर्णांक num_queues = apc->num_queues;
	u8 *p = data;
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(mana_eth_stats); i++) अणु
		स_नकल(p, mana_eth_stats[i].name, ETH_GSTRING_LEN);
		p += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (i = 0; i < num_queues; i++) अणु
		प्र_लिखो(p, "rx_%d_packets", i);
		p += ETH_GSTRING_LEN;
		प्र_लिखो(p, "rx_%d_bytes", i);
		p += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (i = 0; i < num_queues; i++) अणु
		प्र_लिखो(p, "tx_%d_packets", i);
		p += ETH_GSTRING_LEN;
		प्र_लिखो(p, "tx_%d_bytes", i);
		p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल व्योम mana_get_ethtool_stats(काष्ठा net_device *ndev,
				   काष्ठा ethtool_stats *e_stats, u64 *data)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	अचिन्हित पूर्णांक num_queues = apc->num_queues;
	व्योम *eth_stats = &apc->eth_stats;
	काष्ठा mana_stats *stats;
	अचिन्हित पूर्णांक start;
	u64 packets, bytes;
	पूर्णांक q, i = 0;

	अगर (!apc->port_is_up)
		वापस;

	क्रम (q = 0; q < ARRAY_SIZE(mana_eth_stats); q++)
		data[i++] = *(u64 *)(eth_stats + mana_eth_stats[q].offset);

	क्रम (q = 0; q < num_queues; q++) अणु
		stats = &apc->rxqs[q]->stats;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		data[i++] = packets;
		data[i++] = bytes;
	पूर्ण

	क्रम (q = 0; q < num_queues; q++) अणु
		stats = &apc->tx_qp[q].txq.stats;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		data[i++] = packets;
		data[i++] = bytes;
	पूर्ण
पूर्ण

अटल पूर्णांक mana_get_rxnfc(काष्ठा net_device *ndev, काष्ठा ethtool_rxnfc *cmd,
			  u32 *rules)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = apc->num_queues;
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 mana_get_rxfh_key_size(काष्ठा net_device *ndev)
अणु
	वापस MANA_HASH_KEY_SIZE;
पूर्ण

अटल u32 mana_rss_indir_size(काष्ठा net_device *ndev)
अणु
	वापस MANA_INसूचीECT_TABLE_SIZE;
पूर्ण

अटल पूर्णांक mana_get_rxfh(काष्ठा net_device *ndev, u32 *indir, u8 *key,
			 u8 *hfunc)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	पूर्णांक i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP; /* Toeplitz */

	अगर (indir) अणु
		क्रम (i = 0; i < MANA_INसूचीECT_TABLE_SIZE; i++)
			indir[i] = apc->indir_table[i];
	पूर्ण

	अगर (key)
		स_नकल(key, apc->hashkey, MANA_HASH_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक mana_set_rxfh(काष्ठा net_device *ndev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	bool update_hash = false, update_table = false;
	u32 save_table[MANA_INसूचीECT_TABLE_SIZE];
	u8 save_key[MANA_HASH_KEY_SIZE];
	पूर्णांक i, err;

	अगर (!apc->port_is_up)
		वापस -EOPNOTSUPP;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (indir) अणु
		क्रम (i = 0; i < MANA_INसूचीECT_TABLE_SIZE; i++)
			अगर (indir[i] >= apc->num_queues)
				वापस -EINVAL;

		update_table = true;
		क्रम (i = 0; i < MANA_INसूचीECT_TABLE_SIZE; i++) अणु
			save_table[i] = apc->indir_table[i];
			apc->indir_table[i] = indir[i];
		पूर्ण
	पूर्ण

	अगर (key) अणु
		update_hash = true;
		स_नकल(save_key, apc->hashkey, MANA_HASH_KEY_SIZE);
		स_नकल(apc->hashkey, key, MANA_HASH_KEY_SIZE);
	पूर्ण

	err = mana_config_rss(apc, TRI_STATE_TRUE, update_hash, update_table);

	अगर (err) अणु /* recover to original values */
		अगर (update_table) अणु
			क्रम (i = 0; i < MANA_INसूचीECT_TABLE_SIZE; i++)
				apc->indir_table[i] = save_table[i];
		पूर्ण

		अगर (update_hash)
			स_नकल(apc->hashkey, save_key, MANA_HASH_KEY_SIZE);

		mana_config_rss(apc, TRI_STATE_TRUE, update_hash, update_table);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mana_get_channels(काष्ठा net_device *ndev,
			      काष्ठा ethtool_channels *channel)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);

	channel->max_combined = apc->max_queues;
	channel->combined_count = apc->num_queues;
पूर्ण

अटल पूर्णांक mana_set_channels(काष्ठा net_device *ndev,
			     काष्ठा ethtool_channels *channels)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	अचिन्हित पूर्णांक new_count = channels->combined_count;
	अचिन्हित पूर्णांक old_count = apc->num_queues;
	पूर्णांक err, err2;

	अगर (!apc->port_is_up)
		वापस -EOPNOTSUPP;

	err = mana_detach(ndev, false);
	अगर (err) अणु
		netdev_err(ndev, "mana_detach failed: %d\n", err);
		वापस err;
	पूर्ण

	apc->num_queues = new_count;
	err = mana_attach(ndev);
	अगर (!err)
		वापस 0;

	netdev_err(ndev, "mana_attach failed: %d\n", err);

	/* Try to roll it back to the old configuration. */
	apc->num_queues = old_count;
	err2 = mana_attach(ndev);
	अगर (err2)
		netdev_err(ndev, "mana re-attach failed: %d\n", err2);

	वापस err;
पूर्ण

स्थिर काष्ठा ethtool_ops mana_ethtool_ops = अणु
	.get_ethtool_stats	= mana_get_ethtool_stats,
	.get_sset_count		= mana_get_sset_count,
	.get_strings		= mana_get_strings,
	.get_rxnfc		= mana_get_rxnfc,
	.get_rxfh_key_size	= mana_get_rxfh_key_size,
	.get_rxfh_indir_size	= mana_rss_indir_size,
	.get_rxfh		= mana_get_rxfh,
	.set_rxfh		= mana_set_rxfh,
	.get_channels		= mana_get_channels,
	.set_channels		= mana_set_channels,
पूर्ण;
