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
#समावेश "filter.h"
#समावेश "nic.h"

काष्ठा ef4_sw_stat_desc अणु
	स्थिर अक्षर *name;
	क्रमागत अणु
		EF4_ETHTOOL_STAT_SOURCE_nic,
		EF4_ETHTOOL_STAT_SOURCE_channel,
		EF4_ETHTOOL_STAT_SOURCE_tx_queue
	पूर्ण source;
	अचिन्हित offset;
	u64(*get_stat) (व्योम *field); /* Reader function */
पूर्ण;

/* Initialiser क्रम a काष्ठा ef4_sw_stat_desc with type-checking */
#घोषणा EF4_ETHTOOL_STAT(stat_name, source_name, field, field_type, \
				get_stat_function) अणु			\
	.name = #stat_name,						\
	.source = EF4_ETHTOOL_STAT_SOURCE_##source_name,		\
	.offset = ((((field_type *) 0) ==				\
		      &((काष्ठा ef4_##source_name *)0)->field) ?	\
		    दुरत्व(काष्ठा ef4_##source_name, field) :		\
		    दुरत्व(काष्ठा ef4_##source_name, field)),		\
	.get_stat = get_stat_function,					\
पूर्ण

अटल u64 ef4_get_uपूर्णांक_stat(व्योम *field)
अणु
	वापस *(अचिन्हित पूर्णांक *)field;
पूर्ण

अटल u64 ef4_get_atomic_stat(व्योम *field)
अणु
	वापस atomic_पढ़ो((atomic_t *) field);
पूर्ण

#घोषणा EF4_ETHTOOL_ATOMIC_NIC_ERROR_STAT(field)		\
	EF4_ETHTOOL_STAT(field, nic, field,			\
			 atomic_t, ef4_get_atomic_stat)

#घोषणा EF4_ETHTOOL_UINT_CHANNEL_STAT(field)			\
	EF4_ETHTOOL_STAT(field, channel, n_##field,		\
			 अचिन्हित पूर्णांक, ef4_get_uपूर्णांक_stat)

#घोषणा EF4_ETHTOOL_UINT_TXQ_STAT(field)			\
	EF4_ETHTOOL_STAT(tx_##field, tx_queue, field,		\
			 अचिन्हित पूर्णांक, ef4_get_uपूर्णांक_stat)

अटल स्थिर काष्ठा ef4_sw_stat_desc ef4_sw_stat_desc[] = अणु
	EF4_ETHTOOL_UINT_TXQ_STAT(merge_events),
	EF4_ETHTOOL_UINT_TXQ_STAT(pushes),
	EF4_ETHTOOL_UINT_TXQ_STAT(cb_packets),
	EF4_ETHTOOL_ATOMIC_NIC_ERROR_STAT(rx_reset),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_tobe_disc),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_ip_hdr_chksum_err),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_tcp_udp_chksum_err),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_mcast_mismatch),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_frm_trunc),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_merge_events),
	EF4_ETHTOOL_UINT_CHANNEL_STAT(rx_merge_packets),
पूर्ण;

#घोषणा EF4_ETHTOOL_SW_STAT_COUNT ARRAY_SIZE(ef4_sw_stat_desc)

#घोषणा EF4_ETHTOOL_EEPROM_MAGIC 0xEFAB

/**************************************************************************
 *
 * Ethtool operations
 *
 **************************************************************************
 */

/* Identअगरy device by flashing LEDs */
अटल पूर्णांक ef4_ethtool_phys_id(काष्ठा net_device *net_dev,
			       क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	क्रमागत ef4_led_mode mode = EF4_LED_DEFAULT;

	चयन (state) अणु
	हाल ETHTOOL_ID_ON:
		mode = EF4_LED_ON;
		अवरोध;
	हाल ETHTOOL_ID_OFF:
		mode = EF4_LED_OFF;
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		mode = EF4_LED_DEFAULT;
		अवरोध;
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */
	पूर्ण

	efx->type->set_id_led(efx, mode);
	वापस 0;
पूर्ण

/* This must be called with rtnl_lock held. */
अटल पूर्णांक
ef4_ethtool_get_link_ksettings(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा ef4_link_state *link_state = &efx->link_state;

	mutex_lock(&efx->mac_lock);
	efx->phy_op->get_link_ksettings(efx, cmd);
	mutex_unlock(&efx->mac_lock);

	/* Both MACs support छोड़ो frames (bidirectional and respond-only) */
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Asym_Pause);

	अगर (LOOPBACK_INTERNAL(efx)) अणु
		cmd->base.speed = link_state->speed;
		cmd->base.duplex = link_state->fd ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण

	वापस 0;
पूर्ण

/* This must be called with rtnl_lock held. */
अटल पूर्णांक
ef4_ethtool_set_link_ksettings(काष्ठा net_device *net_dev,
			       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	/* GMAC करोes not support 1000Mbps HD */
	अगर ((cmd->base.speed == SPEED_1000) &&
	    (cmd->base.duplex != DUPLEX_FULL)) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "rejecting unsupported 1000Mbps HD setting\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&efx->mac_lock);
	rc = efx->phy_op->set_link_ksettings(efx, cmd);
	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण

अटल व्योम ef4_ethtool_get_drvinfo(काष्ठा net_device *net_dev,
				    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->version, EF4_DRIVER_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(efx->pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक ef4_ethtool_get_regs_len(काष्ठा net_device *net_dev)
अणु
	वापस ef4_nic_get_regs_len(netdev_priv(net_dev));
पूर्ण

अटल व्योम ef4_ethtool_get_regs(काष्ठा net_device *net_dev,
				 काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	regs->version = efx->type->revision;
	ef4_nic_get_regs(efx, buf);
पूर्ण

अटल u32 ef4_ethtool_get_msglevel(काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	वापस efx->msg_enable;
पूर्ण

अटल व्योम ef4_ethtool_set_msglevel(काष्ठा net_device *net_dev, u32 msg_enable)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	efx->msg_enable = msg_enable;
पूर्ण

/**
 * ef4_fill_test - fill in an inभागidual self-test entry
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
अटल व्योम ef4_fill_test(अचिन्हित पूर्णांक test_index, u8 *strings, u64 *data,
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

#घोषणा EF4_CHANNEL_NAME(_channel) "chan%d", _channel->channel
#घोषणा EF4_TX_QUEUE_NAME(_tx_queue) "txq%d", _tx_queue->queue
#घोषणा EF4_RX_QUEUE_NAME(_rx_queue) "rxq%d", _rx_queue->queue
#घोषणा EF4_LOOPBACK_NAME(_mode, _counter)			\
	"loopback.%s." _counter, STRING_TABLE_LOOKUP(_mode, ef4_loopback_mode)

/**
 * ef4_fill_loopback_test - fill in a block of loopback self-test entries
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
अटल पूर्णांक ef4_fill_loopback_test(काष्ठा ef4_nic *efx,
				  काष्ठा ef4_loopback_self_tests *lb_tests,
				  क्रमागत ef4_loopback_mode mode,
				  अचिन्हित पूर्णांक test_index,
				  u8 *strings, u64 *data)
अणु
	काष्ठा ef4_channel *channel =
		ef4_get_channel(efx, efx->tx_channel_offset);
	काष्ठा ef4_tx_queue *tx_queue;

	ef4_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
		ef4_fill_test(test_index++, strings, data,
			      &lb_tests->tx_sent[tx_queue->queue],
			      EF4_TX_QUEUE_NAME(tx_queue),
			      EF4_LOOPBACK_NAME(mode, "tx_sent"));
		ef4_fill_test(test_index++, strings, data,
			      &lb_tests->tx_करोne[tx_queue->queue],
			      EF4_TX_QUEUE_NAME(tx_queue),
			      EF4_LOOPBACK_NAME(mode, "tx_done"));
	पूर्ण
	ef4_fill_test(test_index++, strings, data,
		      &lb_tests->rx_good,
		      "rx", 0,
		      EF4_LOOPBACK_NAME(mode, "rx_good"));
	ef4_fill_test(test_index++, strings, data,
		      &lb_tests->rx_bad,
		      "rx", 0,
		      EF4_LOOPBACK_NAME(mode, "rx_bad"));

	वापस test_index;
पूर्ण

/**
 * ef4_ethtool_fill_self_tests - get self-test details
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
अटल पूर्णांक ef4_ethtool_fill_self_tests(काष्ठा ef4_nic *efx,
				       काष्ठा ef4_self_tests *tests,
				       u8 *strings, u64 *data)
अणु
	काष्ठा ef4_channel *channel;
	अचिन्हित पूर्णांक n = 0, i;
	क्रमागत ef4_loopback_mode mode;

	ef4_fill_test(n++, strings, data, &tests->phy_alive,
		      "phy", 0, "alive", शून्य);
	ef4_fill_test(n++, strings, data, &tests->nvram,
		      "core", 0, "nvram", शून्य);
	ef4_fill_test(n++, strings, data, &tests->पूर्णांकerrupt,
		      "core", 0, "interrupt", शून्य);

	/* Event queues */
	ef4_क्रम_each_channel(channel, efx) अणु
		ef4_fill_test(n++, strings, data,
			      &tests->eventq_dma[channel->channel],
			      EF4_CHANNEL_NAME(channel),
			      "eventq.dma", शून्य);
		ef4_fill_test(n++, strings, data,
			      &tests->eventq_पूर्णांक[channel->channel],
			      EF4_CHANNEL_NAME(channel),
			      "eventq.int", शून्य);
	पूर्ण

	ef4_fill_test(n++, strings, data, &tests->memory,
		      "core", 0, "memory", शून्य);
	ef4_fill_test(n++, strings, data, &tests->रेजिस्टरs,
		      "core", 0, "registers", शून्य);

	अगर (efx->phy_op->run_tests != शून्य) अणु
		EF4_BUG_ON_PARANOID(efx->phy_op->test_name == शून्य);

		क्रम (i = 0; true; ++i) अणु
			स्थिर अक्षर *name;

			EF4_BUG_ON_PARANOID(i >= EF4_MAX_PHY_TESTS);
			name = efx->phy_op->test_name(efx, i);
			अगर (name == शून्य)
				अवरोध;

			ef4_fill_test(n++, strings, data, &tests->phy_ext[i],
				      "phy", 0, name, शून्य);
		पूर्ण
	पूर्ण

	/* Loopback tests */
	क्रम (mode = LOOPBACK_NONE; mode <= LOOPBACK_TEST_MAX; mode++) अणु
		अगर (!(efx->loopback_modes & (1 << mode)))
			जारी;
		n = ef4_fill_loopback_test(efx,
					   &tests->loopback[mode], mode, n,
					   strings, data);
	पूर्ण

	वापस n;
पूर्ण

अटल माप_प्रकार ef4_describe_per_queue_stats(काष्ठा ef4_nic *efx, u8 *strings)
अणु
	माप_प्रकार n_stats = 0;
	काष्ठा ef4_channel *channel;

	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (ef4_channel_has_tx_queues(channel)) अणु
			n_stats++;
			अगर (strings != शून्य) अणु
				snम_लिखो(strings, ETH_GSTRING_LEN,
					 "tx-%u.tx_packets",
					 channel->tx_queue[0].queue /
					 EF4_TXQ_TYPES);

				strings += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
	पूर्ण
	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (ef4_channel_has_rx_queue(channel)) अणु
			n_stats++;
			अगर (strings != शून्य) अणु
				snम_लिखो(strings, ETH_GSTRING_LEN,
					 "rx-%d.rx_packets", channel->channel);
				strings += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस n_stats;
पूर्ण

अटल पूर्णांक ef4_ethtool_get_sset_count(काष्ठा net_device *net_dev,
				      पूर्णांक string_set)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस efx->type->describe_stats(efx, शून्य) +
		       EF4_ETHTOOL_SW_STAT_COUNT +
		       ef4_describe_per_queue_stats(efx, शून्य);
	हाल ETH_SS_TEST:
		वापस ef4_ethtool_fill_self_tests(efx, शून्य, शून्य, शून्य);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ef4_ethtool_get_strings(काष्ठा net_device *net_dev,
				    u32 string_set, u8 *strings)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक i;

	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		strings += (efx->type->describe_stats(efx, strings) *
			    ETH_GSTRING_LEN);
		क्रम (i = 0; i < EF4_ETHTOOL_SW_STAT_COUNT; i++)
			strlcpy(strings + i * ETH_GSTRING_LEN,
				ef4_sw_stat_desc[i].name, ETH_GSTRING_LEN);
		strings += EF4_ETHTOOL_SW_STAT_COUNT * ETH_GSTRING_LEN;
		strings += (ef4_describe_per_queue_stats(efx, strings) *
			    ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_TEST:
		ef4_ethtool_fill_self_tests(efx, शून्य, strings, शून्य);
		अवरोध;
	शेष:
		/* No other string sets */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ef4_ethtool_get_stats(काष्ठा net_device *net_dev,
				  काष्ठा ethtool_stats *stats,
				  u64 *data)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	स्थिर काष्ठा ef4_sw_stat_desc *stat;
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_tx_queue *tx_queue;
	काष्ठा ef4_rx_queue *rx_queue;
	पूर्णांक i;

	spin_lock_bh(&efx->stats_lock);

	/* Get NIC statistics */
	data += efx->type->update_stats(efx, data, शून्य);

	/* Get software statistics */
	क्रम (i = 0; i < EF4_ETHTOOL_SW_STAT_COUNT; i++) अणु
		stat = &ef4_sw_stat_desc[i];
		चयन (stat->source) अणु
		हाल EF4_ETHTOOL_STAT_SOURCE_nic:
			data[i] = stat->get_stat((व्योम *)efx + stat->offset);
			अवरोध;
		हाल EF4_ETHTOOL_STAT_SOURCE_channel:
			data[i] = 0;
			ef4_क्रम_each_channel(channel, efx)
				data[i] += stat->get_stat((व्योम *)channel +
							  stat->offset);
			अवरोध;
		हाल EF4_ETHTOOL_STAT_SOURCE_tx_queue:
			data[i] = 0;
			ef4_क्रम_each_channel(channel, efx) अणु
				ef4_क्रम_each_channel_tx_queue(tx_queue, channel)
					data[i] +=
						stat->get_stat((व्योम *)tx_queue
							       + stat->offset);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	data += EF4_ETHTOOL_SW_STAT_COUNT;

	spin_unlock_bh(&efx->stats_lock);

	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (ef4_channel_has_tx_queues(channel)) अणु
			*data = 0;
			ef4_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
				*data += tx_queue->tx_packets;
			पूर्ण
			data++;
		पूर्ण
	पूर्ण
	ef4_क्रम_each_channel(channel, efx) अणु
		अगर (ef4_channel_has_rx_queue(channel)) अणु
			*data = 0;
			ef4_क्रम_each_channel_rx_queue(rx_queue, channel) अणु
				*data += rx_queue->rx_packets;
			पूर्ण
			data++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ef4_ethtool_self_test(काष्ठा net_device *net_dev,
				  काष्ठा ethtool_test *test, u64 *data)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा ef4_self_tests *ef4_tests;
	bool alपढ़ोy_up;
	पूर्णांक rc = -ENOMEM;

	ef4_tests = kzalloc(माप(*ef4_tests), GFP_KERNEL);
	अगर (!ef4_tests)
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

	rc = ef4_selftest(efx, ef4_tests, test->flags);

	अगर (!alपढ़ोy_up)
		dev_बंद(efx->net_dev);

	netअगर_info(efx, drv, efx->net_dev, "%s %sline self-tests\n",
		   rc == 0 ? "passed" : "failed",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

out:
	ef4_ethtool_fill_self_tests(efx, ef4_tests, शून्य, data);
	kमुक्त(ef4_tests);
fail:
	अगर (rc)
		test->flags |= ETH_TEST_FL_FAILED;
पूर्ण

/* Restart स्वतःnegotiation */
अटल पूर्णांक ef4_ethtool_nway_reset(काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	वापस mdio45_nway_restart(&efx->mdio);
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

अटल पूर्णांक ef4_ethtool_get_coalesce(काष्ठा net_device *net_dev,
				    काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	अचिन्हित पूर्णांक tx_usecs, rx_usecs;
	bool rx_adaptive;

	ef4_get_irq_moderation(efx, &tx_usecs, &rx_usecs, &rx_adaptive);

	coalesce->tx_coalesce_usecs = tx_usecs;
	coalesce->tx_coalesce_usecs_irq = tx_usecs;
	coalesce->rx_coalesce_usecs = rx_usecs;
	coalesce->rx_coalesce_usecs_irq = rx_usecs;
	coalesce->use_adaptive_rx_coalesce = rx_adaptive;

	वापस 0;
पूर्ण

अटल पूर्णांक ef4_ethtool_set_coalesce(काष्ठा net_device *net_dev,
				    काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा ef4_channel *channel;
	अचिन्हित पूर्णांक tx_usecs, rx_usecs;
	bool adaptive, rx_may_override_tx;
	पूर्णांक rc;

	ef4_get_irq_moderation(efx, &tx_usecs, &rx_usecs, &adaptive);

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

	rc = ef4_init_irq_moderation(efx, tx_usecs, rx_usecs, adaptive,
				     rx_may_override_tx);
	अगर (rc != 0)
		वापस rc;

	ef4_क्रम_each_channel(channel, efx)
		efx->type->push_irq_moderation(channel);

	वापस 0;
पूर्ण

अटल व्योम ef4_ethtool_get_ringparam(काष्ठा net_device *net_dev,
				      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	ring->rx_max_pending = EF4_MAX_DMAQ_SIZE;
	ring->tx_max_pending = EF4_MAX_DMAQ_SIZE;
	ring->rx_pending = efx->rxq_entries;
	ring->tx_pending = efx->txq_entries;
पूर्ण

अटल पूर्णांक ef4_ethtool_set_ringparam(काष्ठा net_device *net_dev,
				     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	u32 txq_entries;

	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending ||
	    ring->rx_pending > EF4_MAX_DMAQ_SIZE ||
	    ring->tx_pending > EF4_MAX_DMAQ_SIZE)
		वापस -EINVAL;

	अगर (ring->rx_pending < EF4_RXQ_MIN_ENT) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "RX queues cannot be smaller than %u\n",
			  EF4_RXQ_MIN_ENT);
		वापस -EINVAL;
	पूर्ण

	txq_entries = max(ring->tx_pending, EF4_TXQ_MIN_ENT(efx));
	अगर (txq_entries != ring->tx_pending)
		netअगर_warn(efx, drv, efx->net_dev,
			   "increasing TX queue size to minimum of %u\n",
			   txq_entries);

	वापस ef4_पुनः_स्मृति_channels(efx, ring->rx_pending, txq_entries);
पूर्ण

अटल पूर्णांक ef4_ethtool_set_छोड़ोparam(काष्ठा net_device *net_dev,
				      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	u8 wanted_fc, old_fc;
	u32 old_adv;
	पूर्णांक rc = 0;

	mutex_lock(&efx->mac_lock);

	wanted_fc = ((छोड़ो->rx_छोड़ो ? EF4_FC_RX : 0) |
		     (छोड़ो->tx_छोड़ो ? EF4_FC_TX : 0) |
		     (छोड़ो->स्वतःneg ? EF4_FC_AUTO : 0));

	अगर ((wanted_fc & EF4_FC_TX) && !(wanted_fc & EF4_FC_RX)) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Flow control unsupported: tx ON rx OFF\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((wanted_fc & EF4_FC_AUTO) && !efx->link_advertising) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Autonegotiation is disabled\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Hook क्रम Falcon bug 11482 workaround */
	अगर (efx->type->prepare_enable_fc_tx &&
	    (wanted_fc & EF4_FC_TX) && !(efx->wanted_fc & EF4_FC_TX))
		efx->type->prepare_enable_fc_tx(efx);

	old_adv = efx->link_advertising;
	old_fc = efx->wanted_fc;
	ef4_link_set_wanted_fc(efx, wanted_fc);
	अगर (efx->link_advertising != old_adv ||
	    (efx->wanted_fc ^ old_fc) & EF4_FC_AUTO) अणु
		rc = efx->phy_op->reconfigure(efx);
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
	ef4_mac_reconfigure(efx);

out:
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

अटल व्योम ef4_ethtool_get_छोड़ोparam(काष्ठा net_device *net_dev,
				       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	छोड़ो->rx_छोड़ो = !!(efx->wanted_fc & EF4_FC_RX);
	छोड़ो->tx_छोड़ो = !!(efx->wanted_fc & EF4_FC_TX);
	छोड़ो->स्वतःneg = !!(efx->wanted_fc & EF4_FC_AUTO);
पूर्ण

अटल व्योम ef4_ethtool_get_wol(काष्ठा net_device *net_dev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	वापस efx->type->get_wol(efx, wol);
पूर्ण


अटल पूर्णांक ef4_ethtool_set_wol(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	वापस efx->type->set_wol(efx, wol->wolopts);
पूर्ण

अटल पूर्णांक ef4_ethtool_reset(काष्ठा net_device *net_dev, u32 *flags)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	rc = efx->type->map_reset_flags(flags);
	अगर (rc < 0)
		वापस rc;

	वापस ef4_reset(efx, rc);
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

अटल पूर्णांक ef4_ethtool_get_class_rule(काष्ठा ef4_nic *efx,
				      काष्ठा ethtool_rx_flow_spec *rule)
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
	काष्ठा ef4_filter_spec spec;
	पूर्णांक rc;

	rc = ef4_filter_get_filter_safe(efx, EF4_FILTER_PRI_MANUAL,
					rule->location, &spec);
	अगर (rc)
		वापस rc;

	अगर (spec.dmaq_id == EF4_FILTER_RX_DMAQ_ID_DROP)
		rule->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		rule->ring_cookie = spec.dmaq_id;

	अगर ((spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE) &&
	    spec.ether_type == htons(ETH_P_IP) &&
	    (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) &&
	    (spec.ip_proto == IPPROTO_TCP || spec.ip_proto == IPPROTO_UDP) &&
	    !(spec.match_flags &
	      ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_PORT | EF4_FILTER_MATCH_REM_PORT))) अणु
		rule->flow_type = ((spec.ip_proto == IPPROTO_TCP) ?
				   TCP_V4_FLOW : UDP_V4_FLOW);
		अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) अणु
			ip_entry->ip4dst = spec.loc_host[0];
			ip_mask->ip4dst = IP4_ADDR_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) अणु
			ip_entry->ip4src = spec.rem_host[0];
			ip_mask->ip4src = IP4_ADDR_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_PORT) अणु
			ip_entry->pdst = spec.loc_port;
			ip_mask->pdst = PORT_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_PORT) अणु
			ip_entry->psrc = spec.rem_port;
			ip_mask->psrc = PORT_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर ((spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE) &&
	    spec.ether_type == htons(ETH_P_IPV6) &&
	    (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) &&
	    (spec.ip_proto == IPPROTO_TCP || spec.ip_proto == IPPROTO_UDP) &&
	    !(spec.match_flags &
	      ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_PORT | EF4_FILTER_MATCH_REM_PORT))) अणु
		rule->flow_type = ((spec.ip_proto == IPPROTO_TCP) ?
				   TCP_V6_FLOW : UDP_V6_FLOW);
		अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) अणु
			स_नकल(ip6_entry->ip6dst, spec.loc_host,
			       माप(ip6_entry->ip6dst));
			ip6_fill_mask(ip6_mask->ip6dst);
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) अणु
			स_नकल(ip6_entry->ip6src, spec.rem_host,
			       माप(ip6_entry->ip6src));
			ip6_fill_mask(ip6_mask->ip6src);
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_PORT) अणु
			ip6_entry->pdst = spec.loc_port;
			ip6_mask->pdst = PORT_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_PORT) अणु
			ip6_entry->psrc = spec.rem_port;
			ip6_mask->psrc = PORT_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर (!(spec.match_flags &
		     ~(EF4_FILTER_MATCH_LOC_MAC | EF4_FILTER_MATCH_LOC_MAC_IG |
		       EF4_FILTER_MATCH_REM_MAC | EF4_FILTER_MATCH_ETHER_TYPE |
		       EF4_FILTER_MATCH_OUTER_VID))) अणु
		rule->flow_type = ETHER_FLOW;
		अगर (spec.match_flags &
		    (EF4_FILTER_MATCH_LOC_MAC | EF4_FILTER_MATCH_LOC_MAC_IG)) अणु
			ether_addr_copy(mac_entry->h_dest, spec.loc_mac);
			अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_MAC)
				eth_broadcast_addr(mac_mask->h_dest);
			अन्यथा
				ether_addr_copy(mac_mask->h_dest,
						mac_addr_ig_mask);
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_MAC) अणु
			ether_addr_copy(mac_entry->h_source, spec.rem_mac);
			eth_broadcast_addr(mac_mask->h_source);
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE) अणु
			mac_entry->h_proto = spec.ether_type;
			mac_mask->h_proto = ETHER_TYPE_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर (spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE &&
		   spec.ether_type == htons(ETH_P_IP) &&
		   !(spec.match_flags &
		     ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		       EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		       EF4_FILTER_MATCH_IP_PROTO))) अणु
		rule->flow_type = IPV4_USER_FLOW;
		uip_entry->ip_ver = ETH_RX_NFC_IP4;
		अगर (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) अणु
			uip_mask->proto = IP_PROTO_FULL_MASK;
			uip_entry->proto = spec.ip_proto;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) अणु
			uip_entry->ip4dst = spec.loc_host[0];
			uip_mask->ip4dst = IP4_ADDR_FULL_MASK;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) अणु
			uip_entry->ip4src = spec.rem_host[0];
			uip_mask->ip4src = IP4_ADDR_FULL_MASK;
		पूर्ण
	पूर्ण अन्यथा अगर (spec.match_flags & EF4_FILTER_MATCH_ETHER_TYPE &&
		   spec.ether_type == htons(ETH_P_IPV6) &&
		   !(spec.match_flags &
		     ~(EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_OUTER_VID |
		       EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_REM_HOST |
		       EF4_FILTER_MATCH_IP_PROTO))) अणु
		rule->flow_type = IPV6_USER_FLOW;
		अगर (spec.match_flags & EF4_FILTER_MATCH_IP_PROTO) अणु
			uip6_mask->l4_proto = IP_PROTO_FULL_MASK;
			uip6_entry->l4_proto = spec.ip_proto;
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_LOC_HOST) अणु
			स_नकल(uip6_entry->ip6dst, spec.loc_host,
			       माप(uip6_entry->ip6dst));
			ip6_fill_mask(uip6_mask->ip6dst);
		पूर्ण
		अगर (spec.match_flags & EF4_FILTER_MATCH_REM_HOST) अणु
			स_नकल(uip6_entry->ip6src, spec.rem_host,
			       माप(uip6_entry->ip6src));
			ip6_fill_mask(uip6_mask->ip6src);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The above should handle all filters that we insert */
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (spec.match_flags & EF4_FILTER_MATCH_OUTER_VID) अणु
		rule->flow_type |= FLOW_EXT;
		rule->h_ext.vlan_tci = spec.outer_vid;
		rule->m_ext.vlan_tci = htons(0xfff);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
ef4_ethtool_get_rxnfc(काष्ठा net_device *net_dev,
		      काष्ठा ethtool_rxnfc *info, u32 *rule_locs)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = efx->n_rx_channels;
		वापस 0;

	हाल ETHTOOL_GRXFH: अणु
		अचिन्हित min_revision = 0;

		info->data = 0;
		चयन (info->flow_type) अणु
		हाल TCP_V4_FLOW:
			info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			fallthrough;
		हाल UDP_V4_FLOW:
		हाल SCTP_V4_FLOW:
		हाल AH_ESP_V4_FLOW:
		हाल IPV4_FLOW:
			info->data |= RXH_IP_SRC | RXH_IP_DST;
			min_revision = EF4_REV_FALCON_B0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (ef4_nic_rev(efx) < min_revision)
			info->data = 0;
		वापस 0;
	पूर्ण

	हाल ETHTOOL_GRXCLSRLCNT:
		info->data = ef4_filter_get_rx_id_limit(efx);
		अगर (info->data == 0)
			वापस -EOPNOTSUPP;
		info->data |= RX_CLS_LOC_SPECIAL;
		info->rule_cnt =
			ef4_filter_count_rx_used(efx, EF4_FILTER_PRI_MANUAL);
		वापस 0;

	हाल ETHTOOL_GRXCLSRULE:
		अगर (ef4_filter_get_rx_id_limit(efx) == 0)
			वापस -EOPNOTSUPP;
		वापस ef4_ethtool_get_class_rule(efx, &info->fs);

	हाल ETHTOOL_GRXCLSRLALL: अणु
		s32 rc;
		info->data = ef4_filter_get_rx_id_limit(efx);
		अगर (info->data == 0)
			वापस -EOPNOTSUPP;
		rc = ef4_filter_get_rx_ids(efx, EF4_FILTER_PRI_MANUAL,
					   rule_locs, info->rule_cnt);
		अगर (rc < 0)
			वापस rc;
		info->rule_cnt = rc;
		वापस 0;
	पूर्ण

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

अटल पूर्णांक ef4_ethtool_set_class_rule(काष्ठा ef4_nic *efx,
				      काष्ठा ethtool_rx_flow_spec *rule)
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
	काष्ठा ef4_filter_spec spec;
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

	ef4_filter_init_rx(&spec, EF4_FILTER_PRI_MANUAL,
			   efx->rx_scatter ? EF4_FILTER_FLAG_RX_SCATTER : 0,
			   (rule->ring_cookie == RX_CLS_FLOW_DISC) ?
			   EF4_FILTER_RX_DMAQ_ID_DROP : rule->ring_cookie);

	चयन (rule->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		spec.match_flags = (EF4_FILTER_MATCH_ETHER_TYPE |
				    EF4_FILTER_MATCH_IP_PROTO);
		spec.ether_type = htons(ETH_P_IP);
		spec.ip_proto = ((rule->flow_type & ~FLOW_EXT) == TCP_V4_FLOW ?
				 IPPROTO_TCP : IPPROTO_UDP);
		अगर (ip_mask->ip4dst) अणु
			अगर (ip_mask->ip4dst != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_LOC_HOST;
			spec.loc_host[0] = ip_entry->ip4dst;
		पूर्ण
		अगर (ip_mask->ip4src) अणु
			अगर (ip_mask->ip4src != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_HOST;
			spec.rem_host[0] = ip_entry->ip4src;
		पूर्ण
		अगर (ip_mask->pdst) अणु
			अगर (ip_mask->pdst != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_LOC_PORT;
			spec.loc_port = ip_entry->pdst;
		पूर्ण
		अगर (ip_mask->psrc) अणु
			अगर (ip_mask->psrc != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_PORT;
			spec.rem_port = ip_entry->psrc;
		पूर्ण
		अगर (ip_mask->tos)
			वापस -EINVAL;
		अवरोध;

	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		spec.match_flags = (EF4_FILTER_MATCH_ETHER_TYPE |
				    EF4_FILTER_MATCH_IP_PROTO);
		spec.ether_type = htons(ETH_P_IPV6);
		spec.ip_proto = ((rule->flow_type & ~FLOW_EXT) == TCP_V6_FLOW ?
				 IPPROTO_TCP : IPPROTO_UDP);
		अगर (!ip6_mask_is_empty(ip6_mask->ip6dst)) अणु
			अगर (!ip6_mask_is_full(ip6_mask->ip6dst))
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_LOC_HOST;
			स_नकल(spec.loc_host, ip6_entry->ip6dst, माप(spec.loc_host));
		पूर्ण
		अगर (!ip6_mask_is_empty(ip6_mask->ip6src)) अणु
			अगर (!ip6_mask_is_full(ip6_mask->ip6src))
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_HOST;
			स_नकल(spec.rem_host, ip6_entry->ip6src, माप(spec.rem_host));
		पूर्ण
		अगर (ip6_mask->pdst) अणु
			अगर (ip6_mask->pdst != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_LOC_PORT;
			spec.loc_port = ip6_entry->pdst;
		पूर्ण
		अगर (ip6_mask->psrc) अणु
			अगर (ip6_mask->psrc != PORT_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_PORT;
			spec.rem_port = ip6_entry->psrc;
		पूर्ण
		अगर (ip6_mask->tclass)
			वापस -EINVAL;
		अवरोध;

	हाल IPV4_USER_FLOW:
		अगर (uip_mask->l4_4_bytes || uip_mask->tos || uip_mask->ip_ver ||
		    uip_entry->ip_ver != ETH_RX_NFC_IP4)
			वापस -EINVAL;
		spec.match_flags = EF4_FILTER_MATCH_ETHER_TYPE;
		spec.ether_type = htons(ETH_P_IP);
		अगर (uip_mask->ip4dst) अणु
			अगर (uip_mask->ip4dst != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_LOC_HOST;
			spec.loc_host[0] = uip_entry->ip4dst;
		पूर्ण
		अगर (uip_mask->ip4src) अणु
			अगर (uip_mask->ip4src != IP4_ADDR_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_HOST;
			spec.rem_host[0] = uip_entry->ip4src;
		पूर्ण
		अगर (uip_mask->proto) अणु
			अगर (uip_mask->proto != IP_PROTO_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_IP_PROTO;
			spec.ip_proto = uip_entry->proto;
		पूर्ण
		अवरोध;

	हाल IPV6_USER_FLOW:
		अगर (uip6_mask->l4_4_bytes || uip6_mask->tclass)
			वापस -EINVAL;
		spec.match_flags = EF4_FILTER_MATCH_ETHER_TYPE;
		spec.ether_type = htons(ETH_P_IPV6);
		अगर (!ip6_mask_is_empty(uip6_mask->ip6dst)) अणु
			अगर (!ip6_mask_is_full(uip6_mask->ip6dst))
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_LOC_HOST;
			स_नकल(spec.loc_host, uip6_entry->ip6dst, माप(spec.loc_host));
		पूर्ण
		अगर (!ip6_mask_is_empty(uip6_mask->ip6src)) अणु
			अगर (!ip6_mask_is_full(uip6_mask->ip6src))
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_HOST;
			स_नकल(spec.rem_host, uip6_entry->ip6src, माप(spec.rem_host));
		पूर्ण
		अगर (uip6_mask->l4_proto) अणु
			अगर (uip6_mask->l4_proto != IP_PROTO_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_IP_PROTO;
			spec.ip_proto = uip6_entry->l4_proto;
		पूर्ण
		अवरोध;

	हाल ETHER_FLOW:
		अगर (!is_zero_ether_addr(mac_mask->h_dest)) अणु
			अगर (ether_addr_equal(mac_mask->h_dest,
					     mac_addr_ig_mask))
				spec.match_flags |= EF4_FILTER_MATCH_LOC_MAC_IG;
			अन्यथा अगर (is_broadcast_ether_addr(mac_mask->h_dest))
				spec.match_flags |= EF4_FILTER_MATCH_LOC_MAC;
			अन्यथा
				वापस -EINVAL;
			ether_addr_copy(spec.loc_mac, mac_entry->h_dest);
		पूर्ण
		अगर (!is_zero_ether_addr(mac_mask->h_source)) अणु
			अगर (!is_broadcast_ether_addr(mac_mask->h_source))
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_REM_MAC;
			ether_addr_copy(spec.rem_mac, mac_entry->h_source);
		पूर्ण
		अगर (mac_mask->h_proto) अणु
			अगर (mac_mask->h_proto != ETHER_TYPE_FULL_MASK)
				वापस -EINVAL;
			spec.match_flags |= EF4_FILTER_MATCH_ETHER_TYPE;
			spec.ether_type = mac_entry->h_proto;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((rule->flow_type & FLOW_EXT) && rule->m_ext.vlan_tci) अणु
		अगर (rule->m_ext.vlan_tci != htons(0xfff))
			वापस -EINVAL;
		spec.match_flags |= EF4_FILTER_MATCH_OUTER_VID;
		spec.outer_vid = rule->h_ext.vlan_tci;
	पूर्ण

	rc = ef4_filter_insert_filter(efx, &spec, true);
	अगर (rc < 0)
		वापस rc;

	rule->location = rc;
	वापस 0;
पूर्ण

अटल पूर्णांक ef4_ethtool_set_rxnfc(काष्ठा net_device *net_dev,
				 काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	अगर (ef4_filter_get_rx_id_limit(efx) == 0)
		वापस -EOPNOTSUPP;

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		वापस ef4_ethtool_set_class_rule(efx, &info->fs);

	हाल ETHTOOL_SRXCLSRLDEL:
		वापस ef4_filter_हटाओ_id_safe(efx, EF4_FILTER_PRI_MANUAL,
						 info->fs.location);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 ef4_ethtool_get_rxfh_indir_size(काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	वापस ((ef4_nic_rev(efx) < EF4_REV_FALCON_B0 ||
		 efx->n_rx_channels == 1) ?
		0 : ARRAY_SIZE(efx->rx_indir_table));
पूर्ण

अटल पूर्णांक ef4_ethtool_get_rxfh(काष्ठा net_device *net_dev, u32 *indir, u8 *key,
				u8 *hfunc)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (indir)
		स_नकल(indir, efx->rx_indir_table, माप(efx->rx_indir_table));
	वापस 0;
पूर्ण

अटल पूर्णांक ef4_ethtool_set_rxfh(काष्ठा net_device *net_dev, स्थिर u32 *indir,
				स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);

	/* We करो not allow change in unsupported parameters */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;
	अगर (!indir)
		वापस 0;

	वापस efx->type->rx_push_rss_config(efx, true, indir);
पूर्ण

अटल पूर्णांक ef4_ethtool_get_module_eeprom(काष्ठा net_device *net_dev,
					 काष्ठा ethtool_eeprom *ee,
					 u8 *data)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक ret;

	अगर (!efx->phy_op || !efx->phy_op->get_module_eeprom)
		वापस -EOPNOTSUPP;

	mutex_lock(&efx->mac_lock);
	ret = efx->phy_op->get_module_eeprom(efx, ee, data);
	mutex_unlock(&efx->mac_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ef4_ethtool_get_module_info(काष्ठा net_device *net_dev,
				       काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	पूर्णांक ret;

	अगर (!efx->phy_op || !efx->phy_op->get_module_info)
		वापस -EOPNOTSUPP;

	mutex_lock(&efx->mac_lock);
	ret = efx->phy_op->get_module_info(efx, modinfo);
	mutex_unlock(&efx->mac_lock);

	वापस ret;
पूर्ण

स्थिर काष्ठा ethtool_ops ef4_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USECS_IRQ |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_drvinfo		= ef4_ethtool_get_drvinfo,
	.get_regs_len		= ef4_ethtool_get_regs_len,
	.get_regs		= ef4_ethtool_get_regs,
	.get_msglevel		= ef4_ethtool_get_msglevel,
	.set_msglevel		= ef4_ethtool_set_msglevel,
	.nway_reset		= ef4_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= ef4_ethtool_get_coalesce,
	.set_coalesce		= ef4_ethtool_set_coalesce,
	.get_ringparam		= ef4_ethtool_get_ringparam,
	.set_ringparam		= ef4_ethtool_set_ringparam,
	.get_छोड़ोparam         = ef4_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam         = ef4_ethtool_set_छोड़ोparam,
	.get_sset_count		= ef4_ethtool_get_sset_count,
	.self_test		= ef4_ethtool_self_test,
	.get_strings		= ef4_ethtool_get_strings,
	.set_phys_id		= ef4_ethtool_phys_id,
	.get_ethtool_stats	= ef4_ethtool_get_stats,
	.get_wol                = ef4_ethtool_get_wol,
	.set_wol                = ef4_ethtool_set_wol,
	.reset			= ef4_ethtool_reset,
	.get_rxnfc		= ef4_ethtool_get_rxnfc,
	.set_rxnfc		= ef4_ethtool_set_rxnfc,
	.get_rxfh_indir_size	= ef4_ethtool_get_rxfh_indir_size,
	.get_rxfh		= ef4_ethtool_get_rxfh,
	.set_rxfh		= ef4_ethtool_set_rxfh,
	.get_module_info	= ef4_ethtool_get_module_info,
	.get_module_eeprom	= ef4_ethtool_get_module_eeprom,
	.get_link_ksettings	= ef4_ethtool_get_link_ksettings,
	.set_link_ksettings	= ef4_ethtool_set_link_ksettings,
पूर्ण;
