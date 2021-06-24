<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश "net_driver.h"
#समावेश "mcdi.h"
#समावेश "nic.h"
#समावेश "selftest.h"
#समावेश "rx_common.h"
#समावेश "ethtool_common.h"
#समावेश "mcdi_port_common.h"

काष्ठा efx_sw_stat_desc अणु
	स्थिर अक्षर *name;
	क्रमागत अणु
		EFX_ETHTOOL_STAT_SOURCE_nic,
		EFX_ETHTOOL_STAT_SOURCE_channel,
		EFX_ETHTOOL_STAT_SOURCE_tx_queue
	पूर्ण source;
	अचिन्हित पूर्णांक offset;
	u64 (*get_stat)(व्योम *field); /* Reader function */
पूर्ण;

/* Initialiser क्रम a काष्ठा efx_sw_stat_desc with type-checking */
#घोषणा EFX_ETHTOOL_STAT(stat_name, source_name, field, field_type, \
				get_stat_function) अणु			\
	.name = #stat_name,						\
	.source = EFX_ETHTOOL_STAT_SOURCE_##source_name,		\
	.offset = ((((field_type *) 0) ==				\
		      &((काष्ठा efx_##source_name *)0)->field) ?	\
		    दुरत्व(काष्ठा efx_##source_name, field) :		\
		    दुरत्व(काष्ठा efx_##source_name, field)),		\
	.get_stat = get_stat_function,					\
पूर्ण

अटल u64 efx_get_uपूर्णांक_stat(व्योम *field)
अणु
	वापस *(अचिन्हित पूर्णांक *)field;
पूर्ण

अटल u64 efx_get_atomic_stat(व्योम *field)
अणु
	वापस atomic_पढ़ो((atomic_t *) field);
पूर्ण

#घोषणा EFX_ETHTOOL_ATOMIC_NIC_ERROR_STAT(field)		\
	EFX_ETHTOOL_STAT(field, nic, field,			\
			 atomic_t, efx_get_atomic_stat)

#घोषणा EFX_ETHTOOL_UINT_CHANNEL_STAT(field)			\
	EFX_ETHTOOL_STAT(field, channel, n_##field,		\
			 अचिन्हित पूर्णांक, efx_get_uपूर्णांक_stat)
#घोषणा EFX_ETHTOOL_UINT_CHANNEL_STAT_NO_N(field)		\
	EFX_ETHTOOL_STAT(field, channel, field,			\
			 अचिन्हित पूर्णांक, efx_get_uपूर्णांक_stat)

#घोषणा EFX_ETHTOOL_UINT_TXQ_STAT(field)			\
	EFX_ETHTOOL_STAT(tx_##field, tx_queue, field,		\
			 अचिन्हित पूर्णांक, efx_get_uपूर्णांक_stat)

अटल स्थिर काष्ठा efx_sw_stat_desc efx_sw_stat_desc[] = अणु
	EFX_ETHTOOL_UINT_TXQ_STAT(merge_events),
	EFX_ETHTOOL_UINT_TXQ_STAT(tso_bursts),
	EFX_ETHTOOL_UINT_TXQ_STAT(tso_दीर्घ_headers),
	EFX_ETHTOOL_UINT_TXQ_STAT(tso_packets),
	EFX_ETHTOOL_UINT_TXQ_STAT(tso_fallbacks),
	EFX_ETHTOOL_UINT_TXQ_STAT(pushes),
	EFX_ETHTOOL_UINT_TXQ_STAT(pio_packets),
	EFX_ETHTOOL_UINT_TXQ_STAT(cb_packets),
	EFX_ETHTOOL_ATOMIC_NIC_ERROR_STAT(rx_reset),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_tobe_disc),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_ip_hdr_chksum_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_tcp_udp_chksum_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_inner_ip_hdr_chksum_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_inner_tcp_udp_chksum_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_outer_ip_hdr_chksum_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_outer_tcp_udp_chksum_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_eth_crc_err),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_mcast_mismatch),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_frm_trunc),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_merge_events),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_merge_packets),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_xdp_drops),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_xdp_bad_drops),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_xdp_tx),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rx_xdp_redirect),
#अगर_घोषित CONFIG_RFS_ACCEL
	EFX_ETHTOOL_UINT_CHANNEL_STAT_NO_N(rfs_filter_count),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rfs_succeeded),
	EFX_ETHTOOL_UINT_CHANNEL_STAT(rfs_failed),
#पूर्ण_अगर
पूर्ण;

#घोषणा EFX_ETHTOOL_SW_STAT_COUNT ARRAY_SIZE(efx_sw_stat_desc)

व्योम efx_ethtool_get_drvinfo(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	efx_mcdi_prपूर्णांक_fwver(efx, info->fw_version,
			     माप(info->fw_version));
	strlcpy(info->bus_info, pci_name(efx->pci_dev), माप(info->bus_info));
पूर्ण

u32 efx_ethtool_get_msglevel(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	वापस efx->msg_enable;
पूर्ण

व्योम efx_ethtool_set_msglevel(काष्ठा net_device *net_dev, u32 msg_enable)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	efx->msg_enable = msg_enable;
पूर्ण

व्योम efx_ethtool_self_test(काष्ठा net_device *net_dev,
			   काष्ठा ethtool_test *test, u64 *data)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_self_tests *efx_tests;
	bool alपढ़ोy_up;
	पूर्णांक rc = -ENOMEM;

	efx_tests = kzalloc(माप(*efx_tests), GFP_KERNEL);
	अगर (!efx_tests)
		जाओ fail;

	अगर (efx->state != STATE_READY) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	netअगर_info(efx, drv, efx->net_dev, "starting %sline testing\n",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

	/* We need rx buffers and पूर्णांकerrupts. */
	alपढ़ोy_up = (efx->net_dev->flags & IFF_UP);
	अगर (!alपढ़ोy_up) अणु
		rc = dev_खोलो(efx->net_dev, शून्य);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "failed opening device.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	rc = efx_selftest(efx, efx_tests, test->flags);

	अगर (!alपढ़ोy_up)
		dev_बंद(efx->net_dev);

	netअगर_info(efx, drv, efx->net_dev, "%s %sline self-tests\n",
		   rc == 0 ? "passed" : "failed",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

out:
	efx_ethtool_fill_self_tests(efx, efx_tests, शून्य, data);
	kमुक्त(efx_tests);
fail:
	अगर (rc)
		test->flags |= ETH_TEST_FL_FAILED;
पूर्ण

व्योम efx_ethtool_get_छोड़ोparam(काष्ठा net_device *net_dev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	छोड़ो->rx_छोड़ो = !!(efx->wanted_fc & EFX_FC_RX);
	छोड़ो->tx_छोड़ो = !!(efx->wanted_fc & EFX_FC_TX);
	छोड़ो->स्वतःneg = !!(efx->wanted_fc & EFX_FC_AUTO);
पूर्ण

पूर्णांक efx_ethtool_set_छोड़ोparam(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	u8 wanted_fc, old_fc;
	u32 old_adv;
	पूर्णांक rc = 0;

	mutex_lock(&efx->mac_lock);

	wanted_fc = ((छोड़ो->rx_छोड़ो ? EFX_FC_RX : 0) |
		     (छोड़ो->tx_छोड़ो ? EFX_FC_TX : 0) |
		     (छोड़ो->स्वतःneg ? EFX_FC_AUTO : 0));

	अगर ((wanted_fc & EFX_FC_TX) && !(wanted_fc & EFX_FC_RX)) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Flow control unsupported: tx ON rx OFF\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((wanted_fc & EFX_FC_AUTO) && !efx->link_advertising[0]) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Autonegotiation is disabled\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Hook क्रम Falcon bug 11482 workaround */
	अगर (efx->type->prepare_enable_fc_tx &&
	    (wanted_fc & EFX_FC_TX) && !(efx->wanted_fc & EFX_FC_TX))
		efx->type->prepare_enable_fc_tx(efx);

	old_adv = efx->link_advertising[0];
	old_fc = efx->wanted_fc;
	efx_link_set_wanted_fc(efx, wanted_fc);
	अगर (efx->link_advertising[0] != old_adv ||
	    (efx->wanted_fc ^ old_fc) & EFX_FC_AUTO) अणु
		rc = efx_mcdi_port_reconfigure(efx);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "Unable to advertise requested flow "
				  "control setting\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Reconfigure the MAC. The PHY *may* generate a link state change event
	 * अगर the user just changed the advertised capabilities, but there's no
	 * harm करोing this twice */
	efx_mac_reconfigure(efx, false);

out:
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

/**
 * efx_fill_test - fill in an inभागidual self-test entry
 * @test_index:		Index of the test
 * @strings:		Ethtool strings, or %शून्य
 * @data:		Ethtool test results, or %शून्य
 * @test:		Poपूर्णांकer to test result (used only अगर data != %शून्य)
 * @unit_क्रमmat:	Unit name क्रमmat (e.g. "chan\%d")
 * @unit_id:		Unit id (e.g. 0 क्रम "chan0")
 * @test_क्रमmat:	Test name क्रमmat (e.g. "loopback.\%s.tx.sent")
 * @test_id:		Test id (e.g. "PHYXS" क्रम "loopback.PHYXS.tx_sent")
 *
 * Fill in an inभागidual self-test entry.
 */
अटल व्योम efx_fill_test(अचिन्हित पूर्णांक test_index, u8 *strings, u64 *data,
			  पूर्णांक *test, स्थिर अक्षर *unit_क्रमmat, पूर्णांक unit_id,
			  स्थिर अक्षर *test_क्रमmat, स्थिर अक्षर *test_id)
अणु
	अक्षर unit_str[ETH_GSTRING_LEN], test_str[ETH_GSTRING_LEN];

	/* Fill data value, अगर applicable */
	अगर (data)
		data[test_index] = *test;

	/* Fill string, अगर applicable */
	अगर (strings) अणु
		अगर (म_अक्षर(unit_क्रमmat, '%'))
			snम_लिखो(unit_str, माप(unit_str),
				 unit_क्रमmat, unit_id);
		अन्यथा
			म_नकल(unit_str, unit_क्रमmat);
		snम_लिखो(test_str, माप(test_str), test_क्रमmat, test_id);
		snम_लिखो(strings + test_index * ETH_GSTRING_LEN,
			 ETH_GSTRING_LEN,
			 "%-6s %-24s", unit_str, test_str);
	पूर्ण
पूर्ण

#घोषणा EFX_CHANNEL_NAME(_channel) "chan%d", _channel->channel
#घोषणा EFX_TX_QUEUE_NAME(_tx_queue) "txq%d", _tx_queue->label
#घोषणा EFX_LOOPBACK_NAME(_mode, _counter)			\
	"loopback.%s." _counter, STRING_TABLE_LOOKUP(_mode, efx_loopback_mode)

/**
 * efx_fill_loopback_test - fill in a block of loopback self-test entries
 * @efx:		Efx NIC
 * @lb_tests:		Efx loopback self-test results काष्ठाure
 * @mode:		Loopback test mode
 * @test_index:		Starting index of the test
 * @strings:		Ethtool strings, or %शून्य
 * @data:		Ethtool test results, or %शून्य
 *
 * Fill in a block of loopback self-test entries.  Return new test
 * index.
 */
अटल पूर्णांक efx_fill_loopback_test(काष्ठा efx_nic *efx,
				  काष्ठा efx_loopback_self_tests *lb_tests,
				  क्रमागत efx_loopback_mode mode,
				  अचिन्हित पूर्णांक test_index,
				  u8 *strings, u64 *data)
अणु
	काष्ठा efx_channel *channel =
		efx_get_channel(efx, efx->tx_channel_offset);
	काष्ठा efx_tx_queue *tx_queue;

	efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		efx_fill_test(test_index++, strings, data,
			      &lb_tests->tx_sent[tx_queue->label],
			      EFX_TX_QUEUE_NAME(tx_queue),
			      EFX_LOOPBACK_NAME(mode, "tx_sent"));
		efx_fill_test(test_index++, strings, data,
			      &lb_tests->tx_करोne[tx_queue->label],
			      EFX_TX_QUEUE_NAME(tx_queue),
			      EFX_LOOPBACK_NAME(mode, "tx_done"));
	पूर्ण
	efx_fill_test(test_index++, strings, data,
		      &lb_tests->rx_good,
		      "rx", 0,
		      EFX_LOOPBACK_NAME(mode, "rx_good"));
	efx_fill_test(test_index++, strings, data,
		      &lb_tests->rx_bad,
		      "rx", 0,
		      EFX_LOOPBACK_NAME(mode, "rx_bad"));

	वापस test_index;
पूर्ण

/**
 * efx_ethtool_fill_self_tests - get self-test details
 * @efx:		Efx NIC
 * @tests:		Efx self-test results काष्ठाure, or %शून्य
 * @strings:		Ethtool strings, or %शून्य
 * @data:		Ethtool test results, or %शून्य
 *
 * Get self-test number of strings, strings, and/or test results.
 * Return number of strings (== number of test results).
 *
 * The reason क्रम merging these three functions is to make sure that
 * they can never be inconsistent.
 */
पूर्णांक efx_ethtool_fill_self_tests(काष्ठा efx_nic *efx,
				काष्ठा efx_self_tests *tests,
				u8 *strings, u64 *data)
अणु
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक n = 0, i;
	क्रमागत efx_loopback_mode mode;

	efx_fill_test(n++, strings, data, &tests->phy_alive,
		      "phy", 0, "alive", शून्य);
	efx_fill_test(n++, strings, data, &tests->nvram,
		      "core", 0, "nvram", शून्य);
	efx_fill_test(n++, strings, data, &tests->पूर्णांकerrupt,
		      "core", 0, "interrupt", शून्य);

	/* Event queues */
	efx_क्रम_each_channel(channel, efx) अणु
		efx_fill_test(n++, strings, data,
			      &tests->eventq_dma[channel->channel],
			      EFX_CHANNEL_NAME(channel),
			      "eventq.dma", शून्य);
		efx_fill_test(n++, strings, data,
			      &tests->eventq_पूर्णांक[channel->channel],
			      EFX_CHANNEL_NAME(channel),
			      "eventq.int", शून्य);
	पूर्ण

	efx_fill_test(n++, strings, data, &tests->memory,
		      "core", 0, "memory", शून्य);
	efx_fill_test(n++, strings, data, &tests->रेजिस्टरs,
		      "core", 0, "registers", शून्य);

	क्रम (i = 0; true; ++i) अणु
		स्थिर अक्षर *name;

		EFX_WARN_ON_PARANOID(i >= EFX_MAX_PHY_TESTS);
		name = efx_mcdi_phy_test_name(efx, i);
		अगर (name == शून्य)
			अवरोध;

		efx_fill_test(n++, strings, data, &tests->phy_ext[i], "phy", 0, name, शून्य);
	पूर्ण

	/* Loopback tests */
	क्रम (mode = LOOPBACK_NONE; mode <= LOOPBACK_TEST_MAX; mode++) अणु
		अगर (!(efx->loopback_modes & (1 << mode)))
			जारी;
		n = efx_fill_loopback_test(efx,
					   &tests->loopback[mode], mode, n,
					   strings, data);
	पूर्ण

	वापस n;
पूर्ण

अटल माप_प्रकार efx_describe_per_queue_stats(काष्ठा efx_nic *efx, u8 *strings)
अणु
	माप_प्रकार n_stats = 0;
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx) अणु
		अगर (efx_channel_has_tx_queues(channel)) अणु
			n_stats++;
			अगर (strings != शून्य) अणु
				snम_लिखो(strings, ETH_GSTRING_LEN,
					 "tx-%u.tx_packets",
					 channel->tx_queue[0].queue /
					 EFX_MAX_TXQ_PER_CHANNEL);

				strings += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
	पूर्ण
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (efx_channel_has_rx_queue(channel)) अणु
			n_stats++;
			अगर (strings != शून्य) अणु
				snम_लिखो(strings, ETH_GSTRING_LEN,
					 "rx-%d.rx_packets", channel->channel);
				strings += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (efx->xdp_tx_queue_count && efx->xdp_tx_queues) अणु
		अचिन्हित लघु xdp;

		क्रम (xdp = 0; xdp < efx->xdp_tx_queue_count; xdp++) अणु
			n_stats++;
			अगर (strings) अणु
				snम_लिखो(strings, ETH_GSTRING_LEN,
					 "tx-xdp-cpu-%hu.tx_packets", xdp);
				strings += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस n_stats;
पूर्ण

पूर्णांक efx_ethtool_get_sset_count(काष्ठा net_device *net_dev, पूर्णांक string_set)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस efx->type->describe_stats(efx, शून्य) +
		       EFX_ETHTOOL_SW_STAT_COUNT +
		       efx_describe_per_queue_stats(efx, शून्य) +
		       efx_ptp_describe_stats(efx, शून्य);
	हाल ETH_SS_TEST:
		वापस efx_ethtool_fill_self_tests(efx, शून्य, शून्य, शून्य);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम efx_ethtool_get_strings(काष्ठा net_device *net_dev,
			     u32 string_set, u8 *strings)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक i;

	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		strings += (efx->type->describe_stats(efx, strings) *
			    ETH_GSTRING_LEN);
		क्रम (i = 0; i < EFX_ETHTOOL_SW_STAT_COUNT; i++)
			strlcpy(strings + i * ETH_GSTRING_LEN,
				efx_sw_stat_desc[i].name, ETH_GSTRING_LEN);
		strings += EFX_ETHTOOL_SW_STAT_COUNT * ETH_GSTRING_LEN;
		strings += (efx_describe_per_queue_stats(efx, strings) *
			    ETH_GSTRING_LEN);
		efx_ptp_describe_stats(efx, strings);
		अवरोध;
	हाल ETH_SS_TEST:
		efx_ethtool_fill_self_tests(efx, शून्य, strings, शून्य);
		अवरोध;
	शेष:
		/* No other string sets */
		अवरोध;
	पूर्ण
पूर्ण

व्योम efx_ethtool_get_stats(काष्ठा net_device *net_dev,
			   काष्ठा ethtool_stats *stats,
			   u64 *data)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	स्थिर काष्ठा efx_sw_stat_desc *stat;
	काष्ठा efx_channel *channel;
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;
	पूर्णांक i;

	spin_lock_bh(&efx->stats_lock);

	/* Get NIC statistics */
	data += efx->type->update_stats(efx, data, शून्य);

	/* Get software statistics */
	क्रम (i = 0; i < EFX_ETHTOOL_SW_STAT_COUNT; i++) अणु
		stat = &efx_sw_stat_desc[i];
		चयन (stat->source) अणु
		हाल EFX_ETHTOOL_STAT_SOURCE_nic:
			data[i] = stat->get_stat((व्योम *)efx + stat->offset);
			अवरोध;
		हाल EFX_ETHTOOL_STAT_SOURCE_channel:
			data[i] = 0;
			efx_क्रम_each_channel(channel, efx)
				data[i] += stat->get_stat((व्योम *)channel +
							  stat->offset);
			अवरोध;
		हाल EFX_ETHTOOL_STAT_SOURCE_tx_queue:
			data[i] = 0;
			efx_क्रम_each_channel(channel, efx) अणु
				efx_क्रम_each_channel_tx_queue(tx_queue, channel)
					data[i] +=
						stat->get_stat((व्योम *)tx_queue
							       + stat->offset);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	data += EFX_ETHTOOL_SW_STAT_COUNT;

	spin_unlock_bh(&efx->stats_lock);

	efx_क्रम_each_channel(channel, efx) अणु
		अगर (efx_channel_has_tx_queues(channel)) अणु
			*data = 0;
			efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
				*data += tx_queue->tx_packets;
			पूर्ण
			data++;
		पूर्ण
	पूर्ण
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (efx_channel_has_rx_queue(channel)) अणु
			*data = 0;
			efx_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
				*data += rx_queue->rx_packets;
			पूर्ण
			data++;
		पूर्ण
	पूर्ण
	अगर (efx->xdp_tx_queue_count && efx->xdp_tx_queues) अणु
		पूर्णांक xdp;

		क्रम (xdp = 0; xdp < efx->xdp_tx_queue_count; xdp++) अणु
			data[0] = efx->xdp_tx_queues[xdp]->tx_packets;
			data++;
		पूर्ण
	पूर्ण

	efx_ptp_update_stats(efx, data);
पूर्ण

/* This must be called with rtnl_lock held. */
पूर्णांक efx_ethtool_get_link_ksettings(काष्ठा net_device *net_dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_link_state *link_state = &efx->link_state;
	u32 supported;

	mutex_lock(&efx->mac_lock);
	efx_mcdi_phy_get_link_ksettings(efx, cmd);
	mutex_unlock(&efx->mac_lock);

	/* Both MACs support छोड़ो frames (bidirectional and respond-only) */
	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);

	supported |= SUPPORTED_Pause | SUPPORTED_Asym_Pause;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	अगर (LOOPBACK_INTERNAL(efx)) अणु
		cmd->base.speed = link_state->speed;
		cmd->base.duplex = link_state->fd ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण

	वापस 0;
पूर्ण

/* This must be called with rtnl_lock held. */
पूर्णांक efx_ethtool_set_link_ksettings(काष्ठा net_device *net_dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	/* GMAC करोes not support 1000Mbps HD */
	अगर ((cmd->base.speed == SPEED_1000) &&
	    (cmd->base.duplex != DUPLEX_FULL)) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "rejecting unsupported 1000Mbps HD setting\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&efx->mac_lock);
	rc = efx_mcdi_phy_set_link_ksettings(efx, cmd);
	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण

पूर्णांक efx_ethtool_get_fecparam(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	mutex_lock(&efx->mac_lock);
	rc = efx_mcdi_phy_get_fecparam(efx, fecparam);
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

पूर्णांक efx_ethtool_set_fecparam(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	mutex_lock(&efx->mac_lock);
	rc = efx_mcdi_phy_set_fecparam(efx, fecparam);
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

/* MAC address mask including only I/G bit */
अटल स्थिर u8 mac_addr_ig_mask[ETH_ALEN] __aligned(2) = अणु0x01, 0, 0, 0, 0, 0पूर्ण;

#घोषणा IP4_ADDR_FULL_MASK	((__क्रमce __be32)~0)
#घोषणा IP_PROTO_FULL_MASK	0xFF
#घोषणा PORT_FULL_MASK		((__क्रमce __be16)~0)
#घोषणा ETHER_TYPE_FULL_MASK	((__क्रमce __be16)~0)

अटल अंतरभूत व्योम ip6_fill_mask(__be32 *mask)
अणु
	mask[0] = mask[1] = mask[2] = mask[3] = ~(__be32)0;
पूर्ण

अटल पूर्णांक efx_ethtool_get_class_rule(काष्ठा efx_nic *efx,
				      काष्ठा ethtool_rx_flow_spec *rule,
				      u32 *rss_context)
अणु
	काष्ठा ethtool_tcpip4_spec *ip_entry = &rule->h_u.tcp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec *ip_mask = &rule->m_u.tcp_ip4_spec;
	काष्ठा ethtool_usrip4_spec *uip_entry = &rule->h_u.usr_ip4_spec;
	काष्ठा ethtool_usrip4_spec *uip_mask = &rule->m_u.usr_ip4_spec;
	काष्ठा ethtool_tcpip6_spec *ip6_entry = &rule->h_u.tcp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec *ip6_mask = &rule->m_u.tcp_ip6_spec;
	काष्ठा ethtool_usrip6_spec *uip6_entry = &rule->h_u.usr_ip6_spec;
	काष्ठा ethtool_usrip6_spec *uip6_mask = &rule->m_u.usr_ip6_spec;
	काष्ठा ethhdr *mac_entry = &rule->h_u.ether_spec;
	काष्ठा ethhdr *mac_mask = &rule->m_u.ether_spec;
	काष्ठा efx_filter_spec spec;
	पूर्णांक rc;

	rc = efx_filter_get_filter_safe(efx, EFX_FILTER_PRI_MANUAL,
					rule->location, &spec);
	अगर (rc)
		वापस rc;

	अगर (spec.dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP)
		rule->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		rule->ring_cookie = spec.dmaq_id;

	अगर ((spec.match_flags & EFX_FILTER_MATCH_ETHER_TYPE) &&
	    spec.ether_type == htons(ETH_P_IP) &&
	    (spec.match_flags & EFX_FILTER_MATCH_IP_PROTO) &&
	    (spec.ip_proto == IPPROTO_TCP || spec.ip_proto == IPPROTO_UDP) &&
	    !(spec.match_flags &
	      ~(EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_OUTER_VID |
		EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_REM_HOST |
		EFX_FILTER_MATCH_IP_PROTO |
		EFX_FILTER_MATCH_LOC_PORT | EFX_FILTER_MATCH_REM_PORT))) अणु
		rule->flow_type = ((spec.ip_proto == IPPROTO_TCP) ?
				   TCP_V4_FLOW : UDP_V4_FLOW);
		अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_HOST) अणु
			ip_entry->ip4dst = spec.loc_host[0];
			ip_mask->ip4dst = IP4_ADDR_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_HOST) अणु
			ip_entry->ip4src = spec.rem_host[0];
			ip_mask->ip4src = IP4_ADDR_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_PORT) अणु
			ip_entry->pdst = spec.loc_port;
			ip_mask->pdst = PORT_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_PORT) अणु
			ip_entry->psrc = spec.rem_port;
			ip_mask->psrc = PORT_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर ((spec.match_flags & EFX_FILTER_MATCH_ETHER_TYPE) &&
	    spec.ether_type == htons(ETH_P_IPV6) &&
	    (spec.match_flags & EFX_FILTER_MATCH_IP_PROTO) &&
	    (spec.ip_proto == IPPROTO_TCP || spec.ip_proto == IPPROTO_UDP) &&
	    !(spec.match_flags &
	      ~(EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_OUTER_VID |
		EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_REM_HOST |
		EFX_FILTER_MATCH_IP_PROTO |
		EFX_FILTER_MATCH_LOC_PORT | EFX_FILTER_MATCH_REM_PORT))) अणु
		rule->flow_type = ((spec.ip_proto == IPPROTO_TCP) ?
				   TCP_V6_FLOW : UDP_V6_FLOW);
		अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_HOST) अणु
			स_नकल(ip6_entry->ip6dst, spec.loc_host,
			       माप(ip6_entry->ip6dst));
			ip6_fill_mask(ip6_mask->ip6dst);
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_HOST) अणु
			स_नकल(ip6_entry->ip6src, spec.rem_host,
			       माप(ip6_entry->ip6src));
			ip6_fill_mask(ip6_mask->ip6src);
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_PORT) अणु
			ip6_entry->pdst = spec.loc_port;
			ip6_mask->pdst = PORT_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_PORT) अणु
			ip6_entry->psrc = spec.rem_port;
			ip6_mask->psrc = PORT_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर (!(spec.match_flags &
		     ~(EFX_FILTER_MATCH_LOC_MAC | EFX_FILTER_MATCH_LOC_MAC_IG |
		       EFX_FILTER_MATCH_REM_MAC | EFX_FILTER_MATCH_ETHER_TYPE |
		       EFX_FILTER_MATCH_OUTER_VID))) अणु
		rule->flow_type = ETHER_FLOW;
		अगर (spec.match_flags &
		    (EFX_FILTER_MATCH_LOC_MAC | EFX_FILTER_MATCH_LOC_MAC_IG)) अणु
			ether_addr_copy(mac_entry->h_dest, spec.loc_mac);
			अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_MAC)
				eth_broadcast_addr(mac_mask->h_dest);
			अन्यथा
				ether_addr_copy(mac_mask->h_dest,
						mac_addr_ig_mask);
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_MAC) अणु
			ether_addr_copy(mac_entry->h_source, spec.rem_mac);
			eth_broadcast_addr(mac_mask->h_source);
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_ETHER_TYPE) अणु
			mac_entry->h_proto = spec.ether_type;
			mac_mask->h_proto = ETHER_TYPE_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर (spec.match_flags & EFX_FILTER_MATCH_ETHER_TYPE &&
		   spec.ether_type == htons(ETH_P_IP) &&
		   !(spec.match_flags &
		     ~(EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_OUTER_VID |
		       EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_REM_HOST |
		       EFX_FILTER_MATCH_IP_PROTO))) अणु
		rule->flow_type = IPV4_USER_FLOW;
		uip_entry->ip_ver = ETH_RX_NFC_IP4;
		अगर (spec.match_flags & EFX_FILTER_MATCH_IP_PROTO) अणु
			uip_mask->proto = IP_PROTO_FULL_MASK;
			uip_entry->proto = spec.ip_proto;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_HOST) अणु
			uip_entry->ip4dst = spec.loc_host[0];
			uip_mask->ip4dst = IP4_ADDR_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_HOST) अणु
			uip_entry->ip4src = spec.rem_host[0];
			uip_mask->ip4src = IP4_ADDR_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर (spec.match_flags & EFX_FILTER_MATCH_ETHER_TYPE &&
		   spec.ether_type == htons(ETH_P_IPV6) &&
		   !(spec.match_flags &
		     ~(EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_OUTER_VID |
		       EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_REM_HOST |
		       EFX_FILTER_MATCH_IP_PROTO))) अणु
		rule->flow_type = IPV6_USER_FLOW;
		अगर (spec.match_flags & EFX_FILTER_MATCH_IP_PROTO) अणु
			uip6_mask->l4_proto = IP_PROTO_FULL_MASK;
			uip6_entry->l4_proto = spec.ip_proto;
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_LOC_HOST) अणु
			स_नकल(uip6_entry->ip6dst, spec.loc_host,
			       माप(uip6_entry->ip6dst));
			ip6_fill_mask(uip6_mask->ip6dst);
		पूर्ण
		अगर (spec.match_flags & EFX_FILTER_MATCH_REM_HOST) अणु
			स_नकल(uip6_entry->ip6src, spec.rem_host,
			       माप(uip6_entry->ip6src));
			ip6_fill_mask(uip6_mask->ip6src);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The above should handle all filters that we insert */
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (spec.match_flags & EFX_FILTER_MATCH_OUTER_VID) अणु
		rule->flow_type |= FLOW_EXT;
		rule->h_ext.vlan_tci = spec.outer_vid;
		rule->m_ext.vlan_tci = htons(0xfff);
	पूर्ण

	अगर (spec.flags & EFX_FILTER_FLAG_RX_RSS) अणु
		rule->flow_type |= FLOW_RSS;
		*rss_context = spec.rss_context;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक efx_ethtool_get_rxnfc(काष्ठा net_device *net_dev,
			  काष्ठा ethtool_rxnfc *info, u32 *rule_locs)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	u32 rss_context = 0;
	s32 rc = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = efx->n_rx_channels;
		वापस 0;

	हाल ETHTOOL_GRXFH: अणु
		काष्ठा efx_rss_context *ctx = &efx->rss_context;
		__u64 data;

		mutex_lock(&efx->rss_lock);
		अगर (info->flow_type & FLOW_RSS && info->rss_context) अणु
			ctx = efx_find_rss_context_entry(efx, info->rss_context);
			अगर (!ctx) अणु
				rc = -ENOENT;
				जाओ out_unlock;
			पूर्ण
		पूर्ण

		data = 0;
		अगर (!efx_rss_active(ctx)) /* No RSS */
			जाओ out_setdata_unlock;

		चयन (info->flow_type & ~FLOW_RSS) अणु
		हाल UDP_V4_FLOW:
		हाल UDP_V6_FLOW:
			अगर (ctx->rx_hash_udp_4tuple)
				data = (RXH_L4_B_0_1 | RXH_L4_B_2_3 |
					RXH_IP_SRC | RXH_IP_DST);
			अन्यथा
				data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल TCP_V4_FLOW:
		हाल TCP_V6_FLOW:
			data = (RXH_L4_B_0_1 | RXH_L4_B_2_3 |
				RXH_IP_SRC | RXH_IP_DST);
			अवरोध;
		हाल SCTP_V4_FLOW:
		हाल SCTP_V6_FLOW:
		हाल AH_ESP_V4_FLOW:
		हाल AH_ESP_V6_FLOW:
		हाल IPV4_FLOW:
		हाल IPV6_FLOW:
			data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
out_setdata_unlock:
		info->data = data;
out_unlock:
		mutex_unlock(&efx->rss_lock);
		वापस rc;
	पूर्ण

	हाल ETHTOOL_GRXCLSRLCNT:
		info->data = efx_filter_get_rx_id_limit(efx);
		अगर (info->data == 0)
			वापस -EOPNOTSUPP;
		info->data |= RX_CLS_LOC_SPECIAL;
		info->rule_cnt =
			efx_filter_count_rx_used(efx, EFX_FILTER_PRI_MANUAL);
		वापस 0;

	हाल ETHTOOL_GRXCLSRULE:
		अगर (efx_filter_get_rx_id_limit(efx) == 0)
			वापस -EOPNOTSUPP;
		rc = efx_ethtool_get_class_rule(efx, &info->fs, &rss_context);
		अगर (rc < 0)
			वापस rc;
		अगर (info->fs.flow_type & FLOW_RSS)
			info->rss_context = rss_context;
		वापस 0;

	हाल ETHTOOL_GRXCLSRLALL:
		info->data = efx_filter_get_rx_id_limit(efx);
		अगर (info->data == 0)
			वापस -EOPNOTSUPP;
		rc = efx_filter_get_rx_ids(efx, EFX_FILTER_PRI_MANUAL,
					   rule_locs, info->rule_cnt);
		अगर (rc < 0)
			वापस rc;
		info->rule_cnt = rc;
		वापस 0;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल अंतरभूत bool ip6_mask_is_full(__be32 mask[4])
अणु
	वापस !~(mask[0] & mask[1] & mask[2] & mask[3]);
पूर्ण

अटल अंतरभूत bool ip6_mask_is_empty(__be32 mask[4])
अणु
	वापस !(mask[0] | mask[1] | mask[2] | mask[3]);
पूर्ण

अटल पूर्णांक efx_ethtool_set_class_rule(काष्ठा efx_nic *efx,
				      काष्ठा ethtool_rx_flow_spec *rule,
				      u32 rss_context)
अणु
	काष्ठा ethtool_tcpip4_spec *ip_entry = &rule->h_u.tcp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec *ip_mask = &rule->m_u.tcp_ip4_spec;
	काष्ठा ethtool_usrip4_spec *uip_entry = &rule->h_u.usr_ip4_spec;
	काष्ठा ethtool_usrip4_spec *uip_mask = &rule->m_u.usr_ip4_spec;
	काष्ठा ethtool_tcpip6_spec *ip6_entry = &rule->h_u.tcp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec *ip6_mask = &rule->m_u.tcp_ip6_spec;
	काष्ठा ethtool_usrip6_spec *uip6_entry = &rule->h_u.usr_ip6_spec;
	काष्ठा ethtool_usrip6_spec *uip6_mask = &rule->m_u.usr_ip6_spec;
	u32 flow_type = rule->flow_type & ~(FLOW_EXT | FLOW_RSS);
	काष्ठा ethhdr *mac_entry = &rule->h_u.ether_spec;
	काष्ठा ethhdr *mac_mask = &rule->m_u.ether_spec;
	क्रमागत efx_filter_flags flags = 0;
	काष्ठा efx_filter_spec spec;
	पूर्णांक rc;

	/* Check that user wants us to choose the location */
	अगर (rule->location != RX_CLS_LOC_ANY)
		वापस -EINVAL;

	/* Range-check ring_cookie */
	अगर (rule->ring_cookie >= efx->n_rx_channels &&
	    rule->ring_cookie != RX_CLS_FLOW_DISC)
		वापस -EINVAL;

	/* Check क्रम unsupported extensions */
	अगर ((rule->flow_type & FLOW_EXT) &&
	    (rule->m_ext.vlan_etype || rule->m_ext.data[0] ||
	     rule->m_ext.data[1]))
		वापस -EINVAL;

	अगर (efx->rx_scatter)
		flags |= EFX_FILTER_FLAG_RX_SCATTER;
	अगर (rule->flow_type & FLOW_RSS)
		flags |= EFX_FILTER_FLAG_RX_RSS;

	efx_filter_init_rx(&spec, EFX_FILTER_PRI_MANUAL, flags,
			   (rule->ring_cookie == RX_CLS_FLOW_DISC) ?
			   EFX_FILTER_RX_DMAQ_ID_DROP : rule->ring_cookie);

	अगर (rule->flow_type & FLOW_RSS)
		spec.rss_context = rss_context;

	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		spec.match_flags = (EFX_FILTER_MATCH_ETHER_TYPE |
				    EFX_FILTER_MATCH_IP_PROTO);
		spec.ether_type = htons(ETH_P_IP);
		spec.ip_proto = flow_type == TCP_V4_FLOW ? IPPROTO_TCP
							 : IPPROTO_UDP;
		अगर (ip_mask->ip4dst) अणु
			अगर (ip_mask->ip4dst != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_LOC_HOST;
			spec.loc_host[0] = ip_entry->ip4dst;
		पूर्ण
		अगर (ip_mask->ip4src) अणु
			अगर (ip_mask->ip4src != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_HOST;
			spec.rem_host[0] = ip_entry->ip4src;
		पूर्ण
		अगर (ip_mask->pdst) अणु
			अगर (ip_mask->pdst != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_LOC_PORT;
			spec.loc_port = ip_entry->pdst;
		पूर्ण
		अगर (ip_mask->psrc) अणु
			अगर (ip_mask->psrc != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_PORT;
			spec.rem_port = ip_entry->psrc;
		पूर्ण
		अगर (ip_mask->tos)
			वापस -EINVAL;
		अवरोध;

	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		spec.match_flags = (EFX_FILTER_MATCH_ETHER_TYPE |
				    EFX_FILTER_MATCH_IP_PROTO);
		spec.ether_type = htons(ETH_P_IPV6);
		spec.ip_proto = flow_type == TCP_V6_FLOW ? IPPROTO_TCP
							 : IPPROTO_UDP;
		अगर (!ip6_mask_is_empty(ip6_mask->ip6dst)) अणु
			अगर (!ip6_mask_is_full(ip6_mask->ip6dst))
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_LOC_HOST;
			स_नकल(spec.loc_host, ip6_entry->ip6dst, माप(spec.loc_host));
		पूर्ण
		अगर (!ip6_mask_is_empty(ip6_mask->ip6src)) अणु
			अगर (!ip6_mask_is_full(ip6_mask->ip6src))
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_HOST;
			स_नकल(spec.rem_host, ip6_entry->ip6src, माप(spec.rem_host));
		पूर्ण
		अगर (ip6_mask->pdst) अणु
			अगर (ip6_mask->pdst != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_LOC_PORT;
			spec.loc_port = ip6_entry->pdst;
		पूर्ण
		अगर (ip6_mask->psrc) अणु
			अगर (ip6_mask->psrc != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_PORT;
			spec.rem_port = ip6_entry->psrc;
		पूर्ण
		अगर (ip6_mask->tclass)
			वापस -EINVAL;
		अवरोध;

	हाल IPV4_USER_FLOW:
		अगर (uip_mask->l4_4_bytes || uip_mask->tos || uip_mask->ip_ver ||
		    uip_entry->ip_ver != ETH_RX_NFC_IP4)
			वापस -EINVAL;
		spec.match_flags = EFX_FILTER_MATCH_ETHER_TYPE;
		spec.ether_type = htons(ETH_P_IP);
		अगर (uip_mask->ip4dst) अणु
			अगर (uip_mask->ip4dst != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_LOC_HOST;
			spec.loc_host[0] = uip_entry->ip4dst;
		पूर्ण
		अगर (uip_mask->ip4src) अणु
			अगर (uip_mask->ip4src != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_HOST;
			spec.rem_host[0] = uip_entry->ip4src;
		पूर्ण
		अगर (uip_mask->proto) अणु
			अगर (uip_mask->proto != IP_PROTO_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_IP_PROTO;
			spec.ip_proto = uip_entry->proto;
		पूर्ण
		अवरोध;

	हाल IPV6_USER_FLOW:
		अगर (uip6_mask->l4_4_bytes || uip6_mask->tclass)
			वापस -EINVAL;
		spec.match_flags = EFX_FILTER_MATCH_ETHER_TYPE;
		spec.ether_type = htons(ETH_P_IPV6);
		अगर (!ip6_mask_is_empty(uip6_mask->ip6dst)) अणु
			अगर (!ip6_mask_is_full(uip6_mask->ip6dst))
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_LOC_HOST;
			स_नकल(spec.loc_host, uip6_entry->ip6dst, माप(spec.loc_host));
		पूर्ण
		अगर (!ip6_mask_is_empty(uip6_mask->ip6src)) अणु
			अगर (!ip6_mask_is_full(uip6_mask->ip6src))
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_HOST;
			स_नकल(spec.rem_host, uip6_entry->ip6src, माप(spec.rem_host));
		पूर्ण
		अगर (uip6_mask->l4_proto) अणु
			अगर (uip6_mask->l4_proto != IP_PROTO_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_IP_PROTO;
			spec.ip_proto = uip6_entry->l4_proto;
		पूर्ण
		अवरोध;

	हाल ETHER_FLOW:
		अगर (!is_zero_ether_addr(mac_mask->h_dest)) अणु
			अगर (ether_addr_equal(mac_mask->h_dest,
					     mac_addr_ig_mask))
				spec.match_flags |= EFX_FILTER_MATCH_LOC_MAC_IG;
			अन्यथा अगर (is_broadcast_ether_addr(mac_mask->h_dest))
				spec.match_flags |= EFX_FILTER_MATCH_LOC_MAC;
			अन्यथा
				वापस -EINVAL;
			ether_addr_copy(spec.loc_mac, mac_entry->h_dest);
		पूर्ण
		अगर (!is_zero_ether_addr(mac_mask->h_source)) अणु
			अगर (!is_broadcast_ether_addr(mac_mask->h_source))
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_REM_MAC;
			ether_addr_copy(spec.rem_mac, mac_entry->h_source);
		पूर्ण
		अगर (mac_mask->h_proto) अणु
			अगर (mac_mask->h_proto != ETHER_TYPE_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EFX_FILTER_MATCH_ETHER_TYPE;
			spec.ether_type = mac_entry->h_proto;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((rule->flow_type & FLOW_EXT) && rule->m_ext.vlan_tci) अणु
		अगर (rule->m_ext.vlan_tci != htons(0xfff))
			वापस -EINVAL;
		spec.match_flags |= EFX_FILTER_MATCH_OUTER_VID;
		spec.outer_vid = rule->h_ext.vlan_tci;
	पूर्ण

	rc = efx_filter_insert_filter(efx, &spec, true);
	अगर (rc < 0)
		वापस rc;

	rule->location = rc;
	वापस 0;
पूर्ण

पूर्णांक efx_ethtool_set_rxnfc(काष्ठा net_device *net_dev,
			  काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx_filter_get_rx_id_limit(efx) == 0)
		वापस -EOPNOTSUPP;

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		वापस efx_ethtool_set_class_rule(efx, &info->fs,
						  info->rss_context);

	हाल ETHTOOL_SRXCLSRLDEL:
		वापस efx_filter_हटाओ_id_safe(efx, EFX_FILTER_PRI_MANUAL,
						 info->fs.location);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

u32 efx_ethtool_get_rxfh_indir_size(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->n_rx_channels == 1)
		वापस 0;
	वापस ARRAY_SIZE(efx->rss_context.rx_indir_table);
पूर्ण

u32 efx_ethtool_get_rxfh_key_size(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	वापस efx->type->rx_hash_key_size;
पूर्ण

पूर्णांक efx_ethtool_get_rxfh(काष्ठा net_device *net_dev, u32 *indir, u8 *key,
			 u8 *hfunc)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	rc = efx->type->rx_pull_rss_config(efx);
	अगर (rc)
		वापस rc;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (indir)
		स_नकल(indir, efx->rss_context.rx_indir_table,
		       माप(efx->rss_context.rx_indir_table));
	अगर (key)
		स_नकल(key, efx->rss_context.rx_hash_key,
		       efx->type->rx_hash_key_size);
	वापस 0;
पूर्ण

पूर्णांक efx_ethtool_set_rxfh(काष्ठा net_device *net_dev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	/* Hash function is Toeplitz, cannot be changed */
	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;
	अगर (!indir && !key)
		वापस 0;

	अगर (!key)
		key = efx->rss_context.rx_hash_key;
	अगर (!indir)
		indir = efx->rss_context.rx_indir_table;

	वापस efx->type->rx_push_rss_config(efx, true, indir, key);
पूर्ण

पूर्णांक efx_ethtool_get_rxfh_context(काष्ठा net_device *net_dev, u32 *indir,
				 u8 *key, u8 *hfunc, u32 rss_context)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_rss_context *ctx;
	पूर्णांक rc = 0;

	अगर (!efx->type->rx_pull_rss_context_config)
		वापस -EOPNOTSUPP;

	mutex_lock(&efx->rss_lock);
	ctx = efx_find_rss_context_entry(efx, rss_context);
	अगर (!ctx) अणु
		rc = -ENOENT;
		जाओ out_unlock;
	पूर्ण
	rc = efx->type->rx_pull_rss_context_config(efx, ctx);
	अगर (rc)
		जाओ out_unlock;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (indir)
		स_नकल(indir, ctx->rx_indir_table, माप(ctx->rx_indir_table));
	अगर (key)
		स_नकल(key, ctx->rx_hash_key, efx->type->rx_hash_key_size);
out_unlock:
	mutex_unlock(&efx->rss_lock);
	वापस rc;
पूर्ण

पूर्णांक efx_ethtool_set_rxfh_context(काष्ठा net_device *net_dev,
				 स्थिर u32 *indir, स्थिर u8 *key,
				 स्थिर u8 hfunc, u32 *rss_context,
				 bool delete)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_rss_context *ctx;
	bool allocated = false;
	पूर्णांक rc;

	अगर (!efx->type->rx_push_rss_context_config)
		वापस -EOPNOTSUPP;
	/* Hash function is Toeplitz, cannot be changed */
	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	mutex_lock(&efx->rss_lock);

	अगर (*rss_context == ETH_RXFH_CONTEXT_ALLOC) अणु
		अगर (delete) अणु
			/* alloc + delete == Nothing to करो */
			rc = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		ctx = efx_alloc_rss_context_entry(efx);
		अगर (!ctx) अणु
			rc = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		ctx->context_id = EFX_MCDI_RSS_CONTEXT_INVALID;
		/* Initialise indir table and key to शेषs */
		efx_set_शेष_rx_indir_table(efx, ctx);
		netdev_rss_key_fill(ctx->rx_hash_key, माप(ctx->rx_hash_key));
		allocated = true;
	पूर्ण अन्यथा अणु
		ctx = efx_find_rss_context_entry(efx, *rss_context);
		अगर (!ctx) अणु
			rc = -ENOENT;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (delete) अणु
		/* delete this context */
		rc = efx->type->rx_push_rss_context_config(efx, ctx, शून्य, शून्य);
		अगर (!rc)
			efx_मुक्त_rss_context_entry(ctx);
		जाओ out_unlock;
	पूर्ण

	अगर (!key)
		key = ctx->rx_hash_key;
	अगर (!indir)
		indir = ctx->rx_indir_table;

	rc = efx->type->rx_push_rss_context_config(efx, ctx, indir, key);
	अगर (rc && allocated)
		efx_मुक्त_rss_context_entry(ctx);
	अन्यथा
		*rss_context = ctx->user_id;
out_unlock:
	mutex_unlock(&efx->rss_lock);
	वापस rc;
पूर्ण

पूर्णांक efx_ethtool_reset(काष्ठा net_device *net_dev, u32 *flags)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	rc = efx->type->map_reset_flags(flags);
	अगर (rc < 0)
		वापस rc;

	वापस efx_reset(efx, rc);
पूर्ण

पूर्णांक efx_ethtool_get_module_eeprom(काष्ठा net_device *net_dev,
				  काष्ठा ethtool_eeprom *ee,
				  u8 *data)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक ret;

	mutex_lock(&efx->mac_lock);
	ret = efx_mcdi_phy_get_module_eeprom(efx, ee, data);
	mutex_unlock(&efx->mac_lock);

	वापस ret;
पूर्ण

पूर्णांक efx_ethtool_get_module_info(काष्ठा net_device *net_dev,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक ret;

	mutex_lock(&efx->mac_lock);
	ret = efx_mcdi_phy_get_module_info(efx, modinfo);
	mutex_unlock(&efx->mac_lock);

	वापस ret;
पूर्ण
