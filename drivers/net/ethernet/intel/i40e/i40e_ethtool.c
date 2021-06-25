<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

/* ethtool support क्रम i40e */

#समावेश "i40e.h"
#समावेश "i40e_diag.h"
#समावेश "i40e_txrx_common.h"

/* ethtool statistics helpers */

/**
 * काष्ठा i40e_stats - definition क्रम an ethtool statistic
 * @stat_string: statistic name to display in ethtool -S output
 * @माप_stat: the माप() the stat, must be no greater than माप(u64)
 * @stat_offset: दुरत्व() the stat from a base poपूर्णांकer
 *
 * This काष्ठाure defines a statistic to be added to the ethtool stats buffer.
 * It defines a statistic as offset from a common base poपूर्णांकer. Stats should
 * be defined in स्थिरant arrays using the I40E_STAT macro, with every element
 * of the array using the same _type क्रम calculating the माप_stat and
 * stat_offset.
 *
 * The @माप_stat is expected to be माप(u8), माप(u16), माप(u32) or
 * माप(u64). Other sizes are not expected and will produce a WARN_ONCE from
 * the i40e_add_ethtool_stat() helper function.
 *
 * The @stat_string is पूर्णांकerpreted as a क्रमmat string, allowing क्रमmatted
 * values to be inserted जबतक looping over multiple काष्ठाures क्रम a given
 * statistics array. Thus, every statistic string in an array should have the
 * same type and number of क्रमmat specअगरiers, to be क्रमmatted by variadic
 * arguments to the i40e_add_stat_string() helper function.
 **/
काष्ठा i40e_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

/* Helper macro to define an i40e_stat काष्ठाure with proper size and type.
 * Use this when defining स्थिरant statistics arrays. Note that @_type expects
 * only a type name and is used multiple बार.
 */
#घोषणा I40E_STAT(_type, _name, _stat) अणु \
	.stat_string = _name, \
	.माप_stat = माप_field(_type, _stat), \
	.stat_offset = दुरत्व(_type, _stat) \
पूर्ण

/* Helper macro क्रम defining some statistics directly copied from the netdev
 * stats काष्ठाure.
 */
#घोषणा I40E_NETDEV_STAT(_net_stat) \
	I40E_STAT(काष्ठा rtnl_link_stats64, #_net_stat, _net_stat)

/* Helper macro क्रम defining some statistics related to queues */
#घोषणा I40E_QUEUE_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_ring, _name, _stat)

/* Stats associated with a Tx or Rx ring */
अटल स्थिर काष्ठा i40e_stats i40e_gstrings_queue_stats[] = अणु
	I40E_QUEUE_STAT("%s-%u.packets", stats.packets),
	I40E_QUEUE_STAT("%s-%u.bytes", stats.bytes),
पूर्ण;

/**
 * i40e_add_one_ethtool_stat - copy the stat पूर्णांकo the supplied buffer
 * @data: location to store the stat value
 * @poपूर्णांकer: basis क्रम where to copy from
 * @stat: the stat definition
 *
 * Copies the stat data defined by the poपूर्णांकer and stat काष्ठाure pair पूर्णांकo
 * the memory supplied as data. Used to implement i40e_add_ethtool_stats and
 * i40e_add_queue_stats. If the poपूर्णांकer is null, data will be zero'd.
 */
अटल व्योम
i40e_add_one_ethtool_stat(u64 *data, व्योम *poपूर्णांकer,
			  स्थिर काष्ठा i40e_stats *stat)
अणु
	अक्षर *p;

	अगर (!poपूर्णांकer) अणु
		/* ensure that the ethtool data buffer is zero'd क्रम any stats
		 * which करोn't have a valid poपूर्णांकer.
		 */
		*data = 0;
		वापस;
	पूर्ण

	p = (अक्षर *)poपूर्णांकer + stat->stat_offset;
	चयन (stat->माप_stat) अणु
	हाल माप(u64):
		*data = *((u64 *)p);
		अवरोध;
	हाल माप(u32):
		*data = *((u32 *)p);
		अवरोध;
	हाल माप(u16):
		*data = *((u16 *)p);
		अवरोध;
	हाल माप(u8):
		*data = *((u8 *)p);
		अवरोध;
	शेष:
		WARN_ONCE(1, "unexpected stat size for %s",
			  stat->stat_string);
		*data = 0;
	पूर्ण
पूर्ण

/**
 * __i40e_add_ethtool_stats - copy stats पूर्णांकo the ethtool supplied buffer
 * @data: ethtool stats buffer
 * @poपूर्णांकer: location to copy stats from
 * @stats: array of stats to copy
 * @size: the size of the stats definition
 *
 * Copy the stats defined by the stats array using the poपूर्णांकer as a base पूर्णांकo
 * the data buffer supplied by ethtool. Updates the data poपूर्णांकer to poपूर्णांक to
 * the next empty location क्रम successive calls to __i40e_add_ethtool_stats.
 * If poपूर्णांकer is null, set the data values to zero and update the poपूर्णांकer to
 * skip these stats.
 **/
अटल व्योम
__i40e_add_ethtool_stats(u64 **data, व्योम *poपूर्णांकer,
			 स्थिर काष्ठा i40e_stats stats[],
			 स्थिर अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		i40e_add_one_ethtool_stat((*data)++, poपूर्णांकer, &stats[i]);
पूर्ण

/**
 * i40e_add_ethtool_stats - copy stats पूर्णांकo ethtool supplied buffer
 * @data: ethtool stats buffer
 * @poपूर्णांकer: location where stats are stored
 * @stats: अटल स्थिर array of stat definitions
 *
 * Macro to ease the use of __i40e_add_ethtool_stats by taking a अटल
 * स्थिरant stats array and passing the ARRAY_SIZE(). This aव्योमs typos by
 * ensuring that we pass the size associated with the given stats array.
 *
 * The parameter @stats is evaluated twice, so parameters with side effects
 * should be aव्योमed.
 **/
#घोषणा i40e_add_ethtool_stats(data, poपूर्णांकer, stats) \
	__i40e_add_ethtool_stats(data, poपूर्णांकer, stats, ARRAY_SIZE(stats))

/**
 * i40e_add_queue_stats - copy queue statistics पूर्णांकo supplied buffer
 * @data: ethtool stats buffer
 * @ring: the ring to copy
 *
 * Queue statistics must be copied जबतक रक्षित by
 * u64_stats_fetch_begin_irq, so we can't directly use i40e_add_ethtool_stats.
 * Assumes that queue stats are defined in i40e_gstrings_queue_stats. If the
 * ring poपूर्णांकer is null, zero out the queue stat values and update the data
 * poपूर्णांकer. Otherwise safely copy the stats from the ring पूर्णांकo the supplied
 * buffer and update the data poपूर्णांकer when finished.
 *
 * This function expects to be called जबतक under rcu_पढ़ो_lock().
 **/
अटल व्योम
i40e_add_queue_stats(u64 **data, काष्ठा i40e_ring *ring)
अणु
	स्थिर अचिन्हित पूर्णांक size = ARRAY_SIZE(i40e_gstrings_queue_stats);
	स्थिर काष्ठा i40e_stats *stats = i40e_gstrings_queue_stats;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक i;

	/* To aव्योम invalid statistics values, ensure that we keep retrying
	 * the copy until we get a consistent value according to
	 * u64_stats_fetch_retry_irq. But first, make sure our ring is
	 * non-null beक्रमe attempting to access its syncp.
	 */
	करो अणु
		start = !ring ? 0 : u64_stats_fetch_begin_irq(&ring->syncp);
		क्रम (i = 0; i < size; i++) अणु
			i40e_add_one_ethtool_stat(&(*data)[i], ring,
						  &stats[i]);
		पूर्ण
	पूर्ण जबतक (ring && u64_stats_fetch_retry_irq(&ring->syncp, start));

	/* Once we successfully copy the stats in, update the data poपूर्णांकer */
	*data += size;
पूर्ण

/**
 * __i40e_add_stat_strings - copy stat strings पूर्णांकo ethtool buffer
 * @p: ethtool supplied buffer
 * @stats: stat definitions array
 * @size: size of the stats array
 *
 * Format and copy the strings described by stats पूर्णांकo the buffer poपूर्णांकed at
 * by p.
 **/
अटल व्योम __i40e_add_stat_strings(u8 **p, स्थिर काष्ठा i40e_stats stats[],
				    स्थिर अचिन्हित पूर्णांक size, ...)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		बहु_सूची args;

		बहु_शुरू(args, size);
		vsnम_लिखो(*p, ETH_GSTRING_LEN, stats[i].stat_string, args);
		*p += ETH_GSTRING_LEN;
		बहु_पूर्ण(args);
	पूर्ण
पूर्ण

/**
 * i40e_add_stat_strings - copy stat strings पूर्णांकo ethtool buffer
 * @p: ethtool supplied buffer
 * @stats: stat definitions array
 *
 * Format and copy the strings described by the स्थिर अटल stats value पूर्णांकo
 * the buffer poपूर्णांकed at by p.
 *
 * The parameter @stats is evaluated twice, so parameters with side effects
 * should be aव्योमed. Additionally, stats must be an array such that
 * ARRAY_SIZE can be called on it.
 **/
#घोषणा i40e_add_stat_strings(p, stats, ...) \
	__i40e_add_stat_strings(p, stats, ARRAY_SIZE(stats), ## __VA_ARGS__)

#घोषणा I40E_PF_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_pf, _name, _stat)
#घोषणा I40E_VSI_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_vsi, _name, _stat)
#घोषणा I40E_VEB_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_veb, _name, _stat)
#घोषणा I40E_VEB_TC_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_cp_veb_tc_stats, _name, _stat)
#घोषणा I40E_PFC_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_pfc_stats, _name, _stat)
#घोषणा I40E_QUEUE_STAT(_name, _stat) \
	I40E_STAT(काष्ठा i40e_ring, _name, _stat)

अटल स्थिर काष्ठा i40e_stats i40e_gstrings_net_stats[] = अणु
	I40E_NETDEV_STAT(rx_packets),
	I40E_NETDEV_STAT(tx_packets),
	I40E_NETDEV_STAT(rx_bytes),
	I40E_NETDEV_STAT(tx_bytes),
	I40E_NETDEV_STAT(rx_errors),
	I40E_NETDEV_STAT(tx_errors),
	I40E_NETDEV_STAT(rx_dropped),
	I40E_NETDEV_STAT(tx_dropped),
	I40E_NETDEV_STAT(collisions),
	I40E_NETDEV_STAT(rx_length_errors),
	I40E_NETDEV_STAT(rx_crc_errors),
पूर्ण;

अटल स्थिर काष्ठा i40e_stats i40e_gstrings_veb_stats[] = अणु
	I40E_VEB_STAT("veb.rx_bytes", stats.rx_bytes),
	I40E_VEB_STAT("veb.tx_bytes", stats.tx_bytes),
	I40E_VEB_STAT("veb.rx_unicast", stats.rx_unicast),
	I40E_VEB_STAT("veb.tx_unicast", stats.tx_unicast),
	I40E_VEB_STAT("veb.rx_multicast", stats.rx_multicast),
	I40E_VEB_STAT("veb.tx_multicast", stats.tx_multicast),
	I40E_VEB_STAT("veb.rx_broadcast", stats.rx_broadcast),
	I40E_VEB_STAT("veb.tx_broadcast", stats.tx_broadcast),
	I40E_VEB_STAT("veb.rx_discards", stats.rx_discards),
	I40E_VEB_STAT("veb.tx_discards", stats.tx_discards),
	I40E_VEB_STAT("veb.tx_errors", stats.tx_errors),
	I40E_VEB_STAT("veb.rx_unknown_protocol", stats.rx_unknown_protocol),
पूर्ण;

काष्ठा i40e_cp_veb_tc_stats अणु
	u64 tc_rx_packets;
	u64 tc_rx_bytes;
	u64 tc_tx_packets;
	u64 tc_tx_bytes;
पूर्ण;

अटल स्थिर काष्ठा i40e_stats i40e_gstrings_veb_tc_stats[] = अणु
	I40E_VEB_TC_STAT("veb.tc_%u_tx_packets", tc_tx_packets),
	I40E_VEB_TC_STAT("veb.tc_%u_tx_bytes", tc_tx_bytes),
	I40E_VEB_TC_STAT("veb.tc_%u_rx_packets", tc_rx_packets),
	I40E_VEB_TC_STAT("veb.tc_%u_rx_bytes", tc_rx_bytes),
पूर्ण;

अटल स्थिर काष्ठा i40e_stats i40e_gstrings_misc_stats[] = अणु
	I40E_VSI_STAT("rx_unicast", eth_stats.rx_unicast),
	I40E_VSI_STAT("tx_unicast", eth_stats.tx_unicast),
	I40E_VSI_STAT("rx_multicast", eth_stats.rx_multicast),
	I40E_VSI_STAT("tx_multicast", eth_stats.tx_multicast),
	I40E_VSI_STAT("rx_broadcast", eth_stats.rx_broadcast),
	I40E_VSI_STAT("tx_broadcast", eth_stats.tx_broadcast),
	I40E_VSI_STAT("rx_unknown_protocol", eth_stats.rx_unknown_protocol),
	I40E_VSI_STAT("tx_linearize", tx_linearize),
	I40E_VSI_STAT("tx_force_wb", tx_क्रमce_wb),
	I40E_VSI_STAT("tx_busy", tx_busy),
	I40E_VSI_STAT("rx_alloc_fail", rx_buf_failed),
	I40E_VSI_STAT("rx_pg_alloc_fail", rx_page_failed),
पूर्ण;

/* These PF_STATs might look like duplicates of some NETDEV_STATs,
 * but they are separate.  This device supports Virtualization, and
 * as such might have several netdevs supporting VMDq and FCoE going
 * through a single port.  The NETDEV_STATs are क्रम inभागidual netdevs
 * seen at the top of the stack, and the PF_STATs are क्रम the physical
 * function at the bottom of the stack hosting those netdevs.
 *
 * The PF_STATs are appended to the netdev stats only when ethtool -S
 * is queried on the base PF netdev, not on the VMDq or FCoE netdev.
 */
अटल स्थिर काष्ठा i40e_stats i40e_gstrings_stats[] = अणु
	I40E_PF_STAT("port.rx_bytes", stats.eth.rx_bytes),
	I40E_PF_STAT("port.tx_bytes", stats.eth.tx_bytes),
	I40E_PF_STAT("port.rx_unicast", stats.eth.rx_unicast),
	I40E_PF_STAT("port.tx_unicast", stats.eth.tx_unicast),
	I40E_PF_STAT("port.rx_multicast", stats.eth.rx_multicast),
	I40E_PF_STAT("port.tx_multicast", stats.eth.tx_multicast),
	I40E_PF_STAT("port.rx_broadcast", stats.eth.rx_broadcast),
	I40E_PF_STAT("port.tx_broadcast", stats.eth.tx_broadcast),
	I40E_PF_STAT("port.tx_errors", stats.eth.tx_errors),
	I40E_PF_STAT("port.rx_dropped", stats.eth.rx_discards),
	I40E_PF_STAT("port.tx_dropped_link_down", stats.tx_dropped_link_करोwn),
	I40E_PF_STAT("port.rx_crc_errors", stats.crc_errors),
	I40E_PF_STAT("port.illegal_bytes", stats.illegal_bytes),
	I40E_PF_STAT("port.mac_local_faults", stats.mac_local_faults),
	I40E_PF_STAT("port.mac_remote_faults", stats.mac_remote_faults),
	I40E_PF_STAT("port.tx_timeout", tx_समयout_count),
	I40E_PF_STAT("port.rx_csum_bad", hw_csum_rx_error),
	I40E_PF_STAT("port.rx_length_errors", stats.rx_length_errors),
	I40E_PF_STAT("port.link_xon_rx", stats.link_xon_rx),
	I40E_PF_STAT("port.link_xoff_rx", stats.link_xoff_rx),
	I40E_PF_STAT("port.link_xon_tx", stats.link_xon_tx),
	I40E_PF_STAT("port.link_xoff_tx", stats.link_xoff_tx),
	I40E_PF_STAT("port.rx_size_64", stats.rx_size_64),
	I40E_PF_STAT("port.rx_size_127", stats.rx_size_127),
	I40E_PF_STAT("port.rx_size_255", stats.rx_size_255),
	I40E_PF_STAT("port.rx_size_511", stats.rx_size_511),
	I40E_PF_STAT("port.rx_size_1023", stats.rx_size_1023),
	I40E_PF_STAT("port.rx_size_1522", stats.rx_size_1522),
	I40E_PF_STAT("port.rx_size_big", stats.rx_size_big),
	I40E_PF_STAT("port.tx_size_64", stats.tx_size_64),
	I40E_PF_STAT("port.tx_size_127", stats.tx_size_127),
	I40E_PF_STAT("port.tx_size_255", stats.tx_size_255),
	I40E_PF_STAT("port.tx_size_511", stats.tx_size_511),
	I40E_PF_STAT("port.tx_size_1023", stats.tx_size_1023),
	I40E_PF_STAT("port.tx_size_1522", stats.tx_size_1522),
	I40E_PF_STAT("port.tx_size_big", stats.tx_size_big),
	I40E_PF_STAT("port.rx_undersize", stats.rx_undersize),
	I40E_PF_STAT("port.rx_fragments", stats.rx_fragments),
	I40E_PF_STAT("port.rx_oversize", stats.rx_oversize),
	I40E_PF_STAT("port.rx_jabber", stats.rx_jabber),
	I40E_PF_STAT("port.VF_admin_queue_requests", vf_aq_requests),
	I40E_PF_STAT("port.arq_overflows", arq_overflows),
	I40E_PF_STAT("port.tx_hwtstamp_timeouts", tx_hwtstamp_समयouts),
	I40E_PF_STAT("port.rx_hwtstamp_cleared", rx_hwtstamp_cleared),
	I40E_PF_STAT("port.tx_hwtstamp_skipped", tx_hwtstamp_skipped),
	I40E_PF_STAT("port.fdir_flush_cnt", fd_flush_cnt),
	I40E_PF_STAT("port.fdir_atr_match", stats.fd_atr_match),
	I40E_PF_STAT("port.fdir_atr_tunnel_match", stats.fd_atr_tunnel_match),
	I40E_PF_STAT("port.fdir_atr_status", stats.fd_atr_status),
	I40E_PF_STAT("port.fdir_sb_match", stats.fd_sb_match),
	I40E_PF_STAT("port.fdir_sb_status", stats.fd_sb_status),

	/* LPI stats */
	I40E_PF_STAT("port.tx_lpi_status", stats.tx_lpi_status),
	I40E_PF_STAT("port.rx_lpi_status", stats.rx_lpi_status),
	I40E_PF_STAT("port.tx_lpi_count", stats.tx_lpi_count),
	I40E_PF_STAT("port.rx_lpi_count", stats.rx_lpi_count),
पूर्ण;

काष्ठा i40e_pfc_stats अणु
	u64 priority_xon_rx;
	u64 priority_xoff_rx;
	u64 priority_xon_tx;
	u64 priority_xoff_tx;
	u64 priority_xon_2_xoff;
पूर्ण;

अटल स्थिर काष्ठा i40e_stats i40e_gstrings_pfc_stats[] = अणु
	I40E_PFC_STAT("port.tx_priority_%u_xon_tx", priority_xon_tx),
	I40E_PFC_STAT("port.tx_priority_%u_xoff_tx", priority_xoff_tx),
	I40E_PFC_STAT("port.rx_priority_%u_xon_rx", priority_xon_rx),
	I40E_PFC_STAT("port.rx_priority_%u_xoff_rx", priority_xoff_rx),
	I40E_PFC_STAT("port.rx_priority_%u_xon_2_xoff", priority_xon_2_xoff),
पूर्ण;

#घोषणा I40E_NETDEV_STATS_LEN	ARRAY_SIZE(i40e_gstrings_net_stats)

#घोषणा I40E_MISC_STATS_LEN	ARRAY_SIZE(i40e_gstrings_misc_stats)

#घोषणा I40E_VSI_STATS_LEN	(I40E_NETDEV_STATS_LEN + I40E_MISC_STATS_LEN)

#घोषणा I40E_PFC_STATS_LEN	(ARRAY_SIZE(i40e_gstrings_pfc_stats) * \
				 I40E_MAX_USER_PRIORITY)

#घोषणा I40E_VEB_STATS_LEN	(ARRAY_SIZE(i40e_gstrings_veb_stats) + \
				 (ARRAY_SIZE(i40e_gstrings_veb_tc_stats) * \
				  I40E_MAX_TRAFFIC_CLASS))

#घोषणा I40E_GLOBAL_STATS_LEN	ARRAY_SIZE(i40e_gstrings_stats)

#घोषणा I40E_PF_STATS_LEN	(I40E_GLOBAL_STATS_LEN + \
				 I40E_PFC_STATS_LEN + \
				 I40E_VEB_STATS_LEN + \
				 I40E_VSI_STATS_LEN)

/* Length of stats क्रम a single queue */
#घोषणा I40E_QUEUE_STATS_LEN	ARRAY_SIZE(i40e_gstrings_queue_stats)

क्रमागत i40e_ethtool_test_id अणु
	I40E_ETH_TEST_REG = 0,
	I40E_ETH_TEST_EEPROM,
	I40E_ETH_TEST_INTR,
	I40E_ETH_TEST_LINK,
पूर्ण;

अटल स्थिर अक्षर i40e_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register test  (offline)",
	"Eeprom test    (offline)",
	"Interrupt test (offline)",
	"Link test   (on/offline)"
पूर्ण;

#घोषणा I40E_TEST_LEN (माप(i40e_gstrings_test) / ETH_GSTRING_LEN)

काष्ठा i40e_priv_flags अणु
	अक्षर flag_string[ETH_GSTRING_LEN];
	u64 flag;
	bool पढ़ो_only;
पूर्ण;

#घोषणा I40E_PRIV_FLAG(_name, _flag, _पढ़ो_only) अणु \
	.flag_string = _name, \
	.flag = _flag, \
	.पढ़ो_only = _पढ़ो_only, \
पूर्ण

अटल स्थिर काष्ठा i40e_priv_flags i40e_gstrings_priv_flags[] = अणु
	/* NOTE: MFP setting cannot be changed */
	I40E_PRIV_FLAG("MFP", I40E_FLAG_MFP_ENABLED, 1),
	I40E_PRIV_FLAG("total-port-shutdown",
		       I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED, 1),
	I40E_PRIV_FLAG("LinkPolling", I40E_FLAG_LINK_POLLING_ENABLED, 0),
	I40E_PRIV_FLAG("flow-director-atr", I40E_FLAG_FD_ATR_ENABLED, 0),
	I40E_PRIV_FLAG("veb-stats", I40E_FLAG_VEB_STATS_ENABLED, 0),
	I40E_PRIV_FLAG("hw-atr-eviction", I40E_FLAG_HW_ATR_EVICT_ENABLED, 0),
	I40E_PRIV_FLAG("link-down-on-close",
		       I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED, 0),
	I40E_PRIV_FLAG("legacy-rx", I40E_FLAG_LEGACY_RX, 0),
	I40E_PRIV_FLAG("disable-source-pruning",
		       I40E_FLAG_SOURCE_PRUNING_DISABLED, 0),
	I40E_PRIV_FLAG("disable-fw-lldp", I40E_FLAG_DISABLE_FW_LLDP, 0),
	I40E_PRIV_FLAG("rs-fec", I40E_FLAG_RS_FEC, 0),
	I40E_PRIV_FLAG("base-r-fec", I40E_FLAG_BASE_R_FEC, 0),
पूर्ण;

#घोषणा I40E_PRIV_FLAGS_STR_LEN ARRAY_SIZE(i40e_gstrings_priv_flags)

/* Private flags with a global effect, restricted to PF 0 */
अटल स्थिर काष्ठा i40e_priv_flags i40e_gl_gstrings_priv_flags[] = अणु
	I40E_PRIV_FLAG("vf-true-promisc-support",
		       I40E_FLAG_TRUE_PROMISC_SUPPORT, 0),
पूर्ण;

#घोषणा I40E_GL_PRIV_FLAGS_STR_LEN ARRAY_SIZE(i40e_gl_gstrings_priv_flags)

/**
 * i40e_partition_setting_complaपूर्णांक - generic complaपूर्णांक क्रम MFP restriction
 * @pf: the PF काष्ठा
 **/
अटल व्योम i40e_partition_setting_complaपूर्णांक(काष्ठा i40e_pf *pf)
अणु
	dev_info(&pf->pdev->dev,
		 "The link settings are allowed to be changed only from the first partition of a given port. Please switch to the first partition in order to change the setting.\n");
पूर्ण

/**
 * i40e_phy_type_to_ethtool - convert the phy_types to ethtool link modes
 * @pf: PF काष्ठा with phy_types
 * @ks: ethtool link ksettings काष्ठा to fill out
 *
 **/
अटल व्योम i40e_phy_type_to_ethtool(काष्ठा i40e_pf *pf,
				     काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा i40e_link_status *hw_link_info = &pf->hw.phy.link_info;
	u64 phy_types = pf->hw.phy.phy_types;

	ethtool_link_ksettings_zero_link_mode(ks, supported);
	ethtool_link_ksettings_zero_link_mode(ks, advertising);

	अगर (phy_types & I40E_CAP_PHY_TYPE_SGMII) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_1GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     1000baseT_Full);
		अगर (pf->hw_features & I40E_HW_100M_SGMII_CAPABLE) अणु
			ethtool_link_ksettings_add_link_mode(ks, supported,
							     100baseT_Full);
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     100baseT_Full);
		पूर्ण
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_XAUI ||
	    phy_types & I40E_CAP_PHY_TYPE_XFI ||
	    phy_types & I40E_CAP_PHY_TYPE_SFI ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_SFPP_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_AOC) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseT_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_10GBASE_T) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseT_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_2_5GBASE_T) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     2500baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_2_5GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     2500baseT_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_5GBASE_T) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     5000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_5GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     5000baseT_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_XLAUI ||
	    phy_types & I40E_CAP_PHY_TYPE_XLPPI ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_AOC)
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseCR4_Full);
	अगर (phy_types & I40E_CAP_PHY_TYPE_40GBASE_CR4_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_CR4) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseCR4_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_40GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     40000baseCR4_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_100BASE_TX) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_100MB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     100baseT_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_1000BASE_T) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_1GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     1000baseT_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_40GBASE_SR4) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseSR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseSR4_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_40GBASE_LR4) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseLR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseLR4_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_40GBASE_KR4) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseKR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseKR4_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_20GBASE_KR2) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     20000baseKR2_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_20GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     20000baseKR2_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_10GBASE_KX4) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseKX4_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseKX4_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_10GBASE_KR &&
	    !(pf->hw_features & I40E_HW_HAVE_CRT_RETIMER)) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseKR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseKR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_1000BASE_KX &&
	    !(pf->hw_features & I40E_HW_HAVE_CRT_RETIMER)) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseKX_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_1GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     1000baseKX_Full);
	पूर्ण
	/* need to add 25G PHY types */
	अगर (phy_types & I40E_CAP_PHY_TYPE_25GBASE_KR) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseKR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_25GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     25000baseKR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_25GBASE_CR) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseCR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_25GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     25000baseCR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_25GBASE_SR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_LR) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseSR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_25GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     25000baseSR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_25GBASE_AOC ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_ACC) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseCR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_25GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     25000baseCR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_25GBASE_KR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_CR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_SR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_LR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_AOC ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_ACC) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_NONE);
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_RS);
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_BASER);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_25GB) अणु
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     FEC_NONE);
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     FEC_RS);
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     FEC_BASER);
		पूर्ण
	पूर्ण
	/* need to add new 10G PHY types */
	अगर (phy_types & I40E_CAP_PHY_TYPE_10GBASE_CR1 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_CR1_CU) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseCR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseCR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_10GBASE_SR) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseSR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseSR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_10GBASE_LR) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseLR_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseLR_Full);
	पूर्ण
	अगर (phy_types & I40E_CAP_PHY_TYPE_1000BASE_SX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_LX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_T_OPTICAL) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseX_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_1GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     1000baseX_Full);
	पूर्ण
	/* Autoneg PHY types */
	अगर (phy_types & I40E_CAP_PHY_TYPE_SGMII ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_KR4 ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_CR4_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_CR4 ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_SR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_LR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_KR ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_CR ||
	    phy_types & I40E_CAP_PHY_TYPE_20GBASE_KR2 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_SR ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_LR ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_KX4 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_KR ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_CR1_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_CR1 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_5GBASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_2_5GBASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_T_OPTICAL ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_SX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_LX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_KX ||
	    phy_types & I40E_CAP_PHY_TYPE_100BASE_TX) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Autoneg);
	पूर्ण
पूर्ण

/**
 * i40e_get_settings_link_up_fec - Get the FEC mode encoding from mask
 * @req_fec_info: mask request FEC info
 * @ks: ethtool ksettings to fill in
 **/
अटल व्योम i40e_get_settings_link_up_fec(u8 req_fec_info,
					  काष्ठा ethtool_link_ksettings *ks)
अणु
	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_NONE);
	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_RS);
	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_BASER);

	अगर ((I40E_AQ_SET_FEC_REQUEST_RS & req_fec_info) &&
	    (I40E_AQ_SET_FEC_REQUEST_KR & req_fec_info)) अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     FEC_NONE);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     FEC_BASER);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_RS);
	पूर्ण अन्यथा अगर (I40E_AQ_SET_FEC_REQUEST_RS & req_fec_info) अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_RS);
	पूर्ण अन्यथा अगर (I40E_AQ_SET_FEC_REQUEST_KR & req_fec_info) अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     FEC_BASER);
	पूर्ण अन्यथा अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     FEC_NONE);
	पूर्ण
पूर्ण

/**
 * i40e_get_settings_link_up - Get the Link settings क्रम when link is up
 * @hw: hw काष्ठाure
 * @ks: ethtool ksettings to fill in
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @pf: poपूर्णांकer to physical function काष्ठा
 **/
अटल व्योम i40e_get_settings_link_up(काष्ठा i40e_hw *hw,
				      काष्ठा ethtool_link_ksettings *ks,
				      काष्ठा net_device *netdev,
				      काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_link_status *hw_link_info = &hw->phy.link_info;
	काष्ठा ethtool_link_ksettings cap_ksettings;
	u32 link_speed = hw_link_info->link_speed;

	/* Initialize supported and advertised settings based on phy settings */
	चयन (hw_link_info->phy_type) अणु
	हाल I40E_PHY_TYPE_40GBASE_CR4:
	हाल I40E_PHY_TYPE_40GBASE_CR4_CU:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseCR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseCR4_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_XLAUI:
	हाल I40E_PHY_TYPE_XLPPI:
	हाल I40E_PHY_TYPE_40GBASE_AOC:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseCR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseCR4_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_40GBASE_SR4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseSR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseSR4_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_40GBASE_LR4:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseLR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseLR4_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_25GBASE_SR:
	हाल I40E_PHY_TYPE_25GBASE_LR:
	हाल I40E_PHY_TYPE_10GBASE_SR:
	हाल I40E_PHY_TYPE_10GBASE_LR:
	हाल I40E_PHY_TYPE_1000BASE_SX:
	हाल I40E_PHY_TYPE_1000BASE_LX:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseSR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     25000baseSR_Full);
		i40e_get_settings_link_up_fec(hw_link_info->req_fec_info, ks);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseSR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     10000baseSR_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseLR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     10000baseLR_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseX_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     1000baseX_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		अगर (hw_link_info->module_type[2] &
		    I40E_MODULE_TYPE_1000BASE_SX ||
		    hw_link_info->module_type[2] &
		    I40E_MODULE_TYPE_1000BASE_LX) अणु
			ethtool_link_ksettings_add_link_mode(ks, supported,
							     1000baseT_Full);
			अगर (hw_link_info->requested_speeds &
			    I40E_LINK_SPEED_1GB)
				ethtool_link_ksettings_add_link_mode(
				     ks, advertising, 1000baseT_Full);
		पूर्ण
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseT_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_10GBASE_T:
	हाल I40E_PHY_TYPE_5GBASE_T_LINK_STATUS:
	हाल I40E_PHY_TYPE_2_5GBASE_T_LINK_STATUS:
	हाल I40E_PHY_TYPE_1000BASE_T:
	हाल I40E_PHY_TYPE_100BASE_TX:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     5000baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     2500baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_5GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     5000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_2_5GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     2500baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_1GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     1000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_100MB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     100baseT_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_1000BASE_T_OPTICAL:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     1000baseT_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_10GBASE_CR1_CU:
	हाल I40E_PHY_TYPE_10GBASE_CR1:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     10000baseT_Full);
		अवरोध;
	हाल I40E_PHY_TYPE_XAUI:
	हाल I40E_PHY_TYPE_XFI:
	हाल I40E_PHY_TYPE_SFI:
	हाल I40E_PHY_TYPE_10GBASE_SFPP_CU:
	हाल I40E_PHY_TYPE_10GBASE_AOC:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_10GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     10000baseT_Full);
		i40e_get_settings_link_up_fec(hw_link_info->req_fec_info, ks);
		अवरोध;
	हाल I40E_PHY_TYPE_SGMII:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		अगर (hw_link_info->requested_speeds & I40E_LINK_SPEED_1GB)
			ethtool_link_ksettings_add_link_mode(ks, advertising,
							     1000baseT_Full);
		अगर (pf->hw_features & I40E_HW_100M_SGMII_CAPABLE) अणु
			ethtool_link_ksettings_add_link_mode(ks, supported,
							     100baseT_Full);
			अगर (hw_link_info->requested_speeds &
			    I40E_LINK_SPEED_100MB)
				ethtool_link_ksettings_add_link_mode(
				      ks, advertising, 100baseT_Full);
		पूर्ण
		अवरोध;
	हाल I40E_PHY_TYPE_40GBASE_KR4:
	हाल I40E_PHY_TYPE_25GBASE_KR:
	हाल I40E_PHY_TYPE_20GBASE_KR2:
	हाल I40E_PHY_TYPE_10GBASE_KR:
	हाल I40E_PHY_TYPE_10GBASE_KX4:
	हाल I40E_PHY_TYPE_1000BASE_KX:
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseKR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseKR_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     20000baseKR2_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseKR_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseKX4_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseKX_Full);
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     40000baseKR4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     25000baseKR_Full);
		i40e_get_settings_link_up_fec(hw_link_info->req_fec_info, ks);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     20000baseKR2_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     10000baseKR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     10000baseKX4_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     1000baseKX_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		अवरोध;
	हाल I40E_PHY_TYPE_25GBASE_CR:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseCR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     25000baseCR_Full);
		i40e_get_settings_link_up_fec(hw_link_info->req_fec_info, ks);

		अवरोध;
	हाल I40E_PHY_TYPE_25GBASE_AOC:
	हाल I40E_PHY_TYPE_25GBASE_ACC:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseCR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     25000baseCR_Full);
		i40e_get_settings_link_up_fec(hw_link_info->req_fec_info, ks);

		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseCR_Full);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     10000baseCR_Full);
		अवरोध;
	शेष:
		/* अगर we got here and link is up something bad is afoot */
		netdev_info(netdev,
			    "WARNING: Link is up but PHY type 0x%x is not recognized.\n",
			    hw_link_info->phy_type);
	पूर्ण

	/* Now that we've worked out everything that could be supported by the
	 * current PHY type, get what is supported by the NVM and पूर्णांकersect
	 * them to get what is truly supported
	 */
	स_रखो(&cap_ksettings, 0, माप(काष्ठा ethtool_link_ksettings));
	i40e_phy_type_to_ethtool(pf, &cap_ksettings);
	ethtool_पूर्णांकersect_link_masks(ks, &cap_ksettings);

	/* Set speed and duplex */
	चयन (link_speed) अणु
	हाल I40E_LINK_SPEED_40GB:
		ks->base.speed = SPEED_40000;
		अवरोध;
	हाल I40E_LINK_SPEED_25GB:
		ks->base.speed = SPEED_25000;
		अवरोध;
	हाल I40E_LINK_SPEED_20GB:
		ks->base.speed = SPEED_20000;
		अवरोध;
	हाल I40E_LINK_SPEED_10GB:
		ks->base.speed = SPEED_10000;
		अवरोध;
	हाल I40E_LINK_SPEED_5GB:
		ks->base.speed = SPEED_5000;
		अवरोध;
	हाल I40E_LINK_SPEED_2_5GB:
		ks->base.speed = SPEED_2500;
		अवरोध;
	हाल I40E_LINK_SPEED_1GB:
		ks->base.speed = SPEED_1000;
		अवरोध;
	हाल I40E_LINK_SPEED_100MB:
		ks->base.speed = SPEED_100;
		अवरोध;
	शेष:
		ks->base.speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
	ks->base.duplex = DUPLEX_FULL;
पूर्ण

/**
 * i40e_get_settings_link_करोwn - Get the Link settings क्रम when link is करोwn
 * @hw: hw काष्ठाure
 * @ks: ethtool ksettings to fill in
 * @pf: poपूर्णांकer to physical function काष्ठा
 *
 * Reports link settings that can be determined when link is करोwn
 **/
अटल व्योम i40e_get_settings_link_करोwn(काष्ठा i40e_hw *hw,
					काष्ठा ethtool_link_ksettings *ks,
					काष्ठा i40e_pf *pf)
अणु
	/* link is करोwn and the driver needs to fall back on
	 * supported phy types to figure out what info to display
	 */
	i40e_phy_type_to_ethtool(pf, ks);

	/* With no link speed and duplex are unknown */
	ks->base.speed = SPEED_UNKNOWN;
	ks->base.duplex = DUPLEX_UNKNOWN;
पूर्ण

/**
 * i40e_get_link_ksettings - Get Link Speed and Duplex settings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ks: ethtool ksettings
 *
 * Reports speed/duplex settings based on media_type
 **/
अटल पूर्णांक i40e_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_link_status *hw_link_info = &hw->phy.link_info;
	bool link_up = hw_link_info->link_info & I40E_AQ_LINK_UP;

	ethtool_link_ksettings_zero_link_mode(ks, supported);
	ethtool_link_ksettings_zero_link_mode(ks, advertising);

	अगर (link_up)
		i40e_get_settings_link_up(hw, ks, netdev, pf);
	अन्यथा
		i40e_get_settings_link_करोwn(hw, ks, pf);

	/* Now set the settings that करोn't rely on link being up/करोwn */
	/* Set स्वतःneg settings */
	ks->base.स्वतःneg = ((hw_link_info->an_info & I40E_AQ_AN_COMPLETED) ?
			    AUTONEG_ENABLE : AUTONEG_DISABLE);

	/* Set media type settings */
	चयन (hw->phy.media_type) अणु
	हाल I40E_MEDIA_TYPE_BACKPLANE:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported, Backplane);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Backplane);
		ks->base.port = PORT_NONE;
		अवरोध;
	हाल I40E_MEDIA_TYPE_BASET:
		ethtool_link_ksettings_add_link_mode(ks, supported, TP);
		ethtool_link_ksettings_add_link_mode(ks, advertising, TP);
		ks->base.port = PORT_TP;
		अवरोध;
	हाल I40E_MEDIA_TYPE_DA:
	हाल I40E_MEDIA_TYPE_CX4:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FIBRE);
		ks->base.port = PORT_DA;
		अवरोध;
	हाल I40E_MEDIA_TYPE_FIBER:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FIBRE);
		ks->base.port = PORT_FIBRE;
		अवरोध;
	हाल I40E_MEDIA_TYPE_UNKNOWN:
	शेष:
		ks->base.port = PORT_OTHER;
		अवरोध;
	पूर्ण

	/* Set flow control settings */
	ethtool_link_ksettings_add_link_mode(ks, supported, Pause);
	ethtool_link_ksettings_add_link_mode(ks, supported, Asym_Pause);

	चयन (hw->fc.requested_mode) अणु
	हाल I40E_FC_FULL:
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		अवरोध;
	हाल I40E_FC_TX_PAUSE:
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
		अवरोध;
	हाल I40E_FC_RX_PAUSE:
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
		अवरोध;
	शेष:
		ethtool_link_ksettings_del_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_del_link_mode(ks, advertising,
						     Asym_Pause);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_set_link_ksettings - Set Speed and Duplex
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ks: ethtool ksettings
 *
 * Set speed/duplex per media_types advertised/क्रमced
 **/
अटल पूर्णांक i40e_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	काष्ठा ethtool_link_ksettings safe_ks;
	काष्ठा ethtool_link_ksettings copy_ks;
	काष्ठा i40e_aq_set_phy_config config;
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_hw *hw = &pf->hw;
	bool स्वतःneg_changed = false;
	i40e_status status = 0;
	पूर्णांक समयout = 50;
	पूर्णांक err = 0;
	u8 स्वतःneg;

	/* Changing port settings is not supported अगर this isn't the
	 * port's controlling PF
	 */
	अगर (hw->partition_id != 1) अणु
		i40e_partition_setting_complaपूर्णांक(pf);
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (vsi != pf->vsi[pf->lan_vsi])
		वापस -EOPNOTSUPP;
	अगर (hw->phy.media_type != I40E_MEDIA_TYPE_BASET &&
	    hw->phy.media_type != I40E_MEDIA_TYPE_FIBER &&
	    hw->phy.media_type != I40E_MEDIA_TYPE_BACKPLANE &&
	    hw->phy.media_type != I40E_MEDIA_TYPE_DA &&
	    hw->phy.link_info.link_info & I40E_AQ_LINK_UP)
		वापस -EOPNOTSUPP;
	अगर (hw->device_id == I40E_DEV_ID_KX_B ||
	    hw->device_id == I40E_DEV_ID_KX_C ||
	    hw->device_id == I40E_DEV_ID_20G_KR2 ||
	    hw->device_id == I40E_DEV_ID_20G_KR2_A ||
	    hw->device_id == I40E_DEV_ID_25G_B ||
	    hw->device_id == I40E_DEV_ID_KX_X722) अणु
		netdev_info(netdev, "Changing settings is not supported on backplane.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* copy the ksettings to copy_ks to aव्योम modअगरying the origin */
	स_नकल(&copy_ks, ks, माप(काष्ठा ethtool_link_ksettings));

	/* save स्वतःneg out of ksettings */
	स्वतःneg = copy_ks.base.स्वतःneg;

	/* get our own copy of the bits to check against */
	स_रखो(&safe_ks, 0, माप(काष्ठा ethtool_link_ksettings));
	safe_ks.base.cmd = copy_ks.base.cmd;
	safe_ks.base.link_mode_masks_nwords =
		copy_ks.base.link_mode_masks_nwords;
	i40e_get_link_ksettings(netdev, &safe_ks);

	/* Get link modes supported by hardware and check against modes
	 * requested by the user.  Return an error अगर unsupported mode was set.
	 */
	अगर (!biपंचांगap_subset(copy_ks.link_modes.advertising,
			   safe_ks.link_modes.supported,
			   __ETHTOOL_LINK_MODE_MASK_NBITS))
		वापस -EINVAL;

	/* set स्वतःneg back to what it currently is */
	copy_ks.base.स्वतःneg = safe_ks.base.स्वतःneg;

	/* If copy_ks.base and safe_ks.base are not the same now, then they are
	 * trying to set something that we करो not support.
	 */
	अगर (स_भेद(&copy_ks.base, &safe_ks.base,
		   माप(काष्ठा ethtool_link_settings)))
		वापस -EOPNOTSUPP;

	जबतक (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state)) अणु
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
		usleep_range(1000, 2000);
	पूर्ण

	/* Get the current phy config */
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      शून्य);
	अगर (status) अणु
		err = -EAGAIN;
		जाओ करोne;
	पूर्ण

	/* Copy abilities to config in हाल स्वतःneg is not
	 * set below
	 */
	स_रखो(&config, 0, माप(काष्ठा i40e_aq_set_phy_config));
	config.abilities = abilities.abilities;

	/* Check स्वतःneg */
	अगर (स्वतःneg == AUTONEG_ENABLE) अणु
		/* If स्वतःneg was not alपढ़ोy enabled */
		अगर (!(hw->phy.link_info.an_info & I40E_AQ_AN_COMPLETED)) अणु
			/* If स्वतःneg is not supported, वापस error */
			अगर (!ethtool_link_ksettings_test_link_mode(&safe_ks,
								   supported,
								   Autoneg)) अणु
				netdev_info(netdev, "Autoneg not supported on this phy\n");
				err = -EINVAL;
				जाओ करोne;
			पूर्ण
			/* Autoneg is allowed to change */
			config.abilities = abilities.abilities |
					   I40E_AQ_PHY_ENABLE_AN;
			स्वतःneg_changed = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If स्वतःneg is currently enabled */
		अगर (hw->phy.link_info.an_info & I40E_AQ_AN_COMPLETED) अणु
			/* If स्वतःneg is supported 10GBASE_T is the only PHY
			 * that can disable it, so otherwise वापस error
			 */
			अगर (ethtool_link_ksettings_test_link_mode(&safe_ks,
								  supported,
								  Autoneg) &&
			    hw->phy.link_info.phy_type !=
			    I40E_PHY_TYPE_10GBASE_T) अणु
				netdev_info(netdev, "Autoneg cannot be disabled on this phy\n");
				err = -EINVAL;
				जाओ करोne;
			पूर्ण
			/* Autoneg is allowed to change */
			config.abilities = abilities.abilities &
					   ~I40E_AQ_PHY_ENABLE_AN;
			स्वतःneg_changed = true;
		पूर्ण
	पूर्ण

	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  100baseT_Full))
		config.link_speed |= I40E_LINK_SPEED_100MB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  1000baseT_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  1000baseX_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  1000baseKX_Full))
		config.link_speed |= I40E_LINK_SPEED_1GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseT_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseKX4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseKR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseCR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseSR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseLR_Full))
		config.link_speed |= I40E_LINK_SPEED_10GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  2500baseT_Full))
		config.link_speed |= I40E_LINK_SPEED_2_5GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  5000baseT_Full))
		config.link_speed |= I40E_LINK_SPEED_5GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  20000baseKR2_Full))
		config.link_speed |= I40E_LINK_SPEED_20GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  25000baseCR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  25000baseKR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  25000baseSR_Full))
		config.link_speed |= I40E_LINK_SPEED_25GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseKR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseCR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseSR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseLR4_Full))
		config.link_speed |= I40E_LINK_SPEED_40GB;

	/* If speed didn't get set, set it to what it currently is.
	 * This is needed because अगर advertise is 0 (as it is when स्वतःneg
	 * is disabled) then speed won't get set.
	 */
	अगर (!config.link_speed)
		config.link_speed = abilities.link_speed;
	अगर (स्वतःneg_changed || abilities.link_speed != config.link_speed) अणु
		/* copy over the rest of the abilities */
		config.phy_type = abilities.phy_type;
		config.phy_type_ext = abilities.phy_type_ext;
		config.eee_capability = abilities.eee_capability;
		config.eeer = abilities.eeer_val;
		config.low_घातer_ctrl = abilities.d3_lpan;
		config.fec_config = abilities.fec_cfg_curr_mod_ext_info &
				    I40E_AQ_PHY_FEC_CONFIG_MASK;

		/* save the requested speeds */
		hw->phy.link_info.requested_speeds = config.link_speed;
		/* set link and स्वतः negotiation so changes take effect */
		config.abilities |= I40E_AQ_PHY_ENABLE_ATOMIC_LINK;
		/* If link is up put link करोwn */
		अगर (hw->phy.link_info.link_info & I40E_AQ_LINK_UP) अणु
			/* Tell the OS link is going करोwn, the link will go
			 * back up when fw says it is पढ़ोy asynchronously
			 */
			i40e_prपूर्णांक_link_message(vsi, false);
			netअगर_carrier_off(netdev);
			netअगर_tx_stop_all_queues(netdev);
		पूर्ण

		/* make the aq call */
		status = i40e_aq_set_phy_config(hw, &config, शून्य);
		अगर (status) अणु
			netdev_info(netdev,
				    "Set phy config failed, err %s aq_err %s\n",
				    i40e_stat_str(hw, status),
				    i40e_aq_str(hw, hw->aq.asq_last_status));
			err = -EAGAIN;
			जाओ करोne;
		पूर्ण

		status = i40e_update_link_info(hw);
		अगर (status)
			netdev_dbg(netdev,
				   "Updating link info failed with err %s aq_err %s\n",
				   i40e_stat_str(hw, status),
				   i40e_aq_str(hw, hw->aq.asq_last_status));

	पूर्ण अन्यथा अणु
		netdev_info(netdev, "Nothing changed, exiting without setting anything.\n");
	पूर्ण

करोne:
	clear_bit(__I40E_CONFIG_BUSY, pf->state);

	वापस err;
पूर्ण

अटल पूर्णांक i40e_set_fec_cfg(काष्ठा net_device *netdev, u8 fec_cfg)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status status = 0;
	u32 flags = 0;
	पूर्णांक err = 0;

	flags = READ_ONCE(pf->flags);
	i40e_set_fec_in_flags(fec_cfg, &flags);

	/* Get the current phy config */
	स_रखो(&abilities, 0, माप(abilities));
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      शून्य);
	अगर (status) अणु
		err = -EAGAIN;
		जाओ करोne;
	पूर्ण

	अगर (abilities.fec_cfg_curr_mod_ext_info != fec_cfg) अणु
		काष्ठा i40e_aq_set_phy_config config;

		स_रखो(&config, 0, माप(config));
		config.phy_type = abilities.phy_type;
		config.abilities = abilities.abilities |
				   I40E_AQ_PHY_ENABLE_ATOMIC_LINK;
		config.phy_type_ext = abilities.phy_type_ext;
		config.link_speed = abilities.link_speed;
		config.eee_capability = abilities.eee_capability;
		config.eeer = abilities.eeer_val;
		config.low_घातer_ctrl = abilities.d3_lpan;
		config.fec_config = fec_cfg & I40E_AQ_PHY_FEC_CONFIG_MASK;
		status = i40e_aq_set_phy_config(hw, &config, शून्य);
		अगर (status) अणु
			netdev_info(netdev,
				    "Set phy config failed, err %s aq_err %s\n",
				    i40e_stat_str(hw, status),
				    i40e_aq_str(hw, hw->aq.asq_last_status));
			err = -EAGAIN;
			जाओ करोne;
		पूर्ण
		pf->flags = flags;
		status = i40e_update_link_info(hw);
		अगर (status)
			/* debug level message only due to relation to the link
			 * itself rather than to the FEC settings
			 * (e.g. no physical connection etc.)
			 */
			netdev_dbg(netdev,
				   "Updating link info failed with err %s aq_err %s\n",
				   i40e_stat_str(hw, status),
				   i40e_aq_str(hw, hw->aq.asq_last_status));
	पूर्ण

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक i40e_get_fec_param(काष्ठा net_device *netdev,
			      काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	i40e_status status = 0;
	पूर्णांक err = 0;
	u8 fec_cfg;

	/* Get the current phy config */
	स_रखो(&abilities, 0, माप(abilities));
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      शून्य);
	अगर (status) अणु
		err = -EAGAIN;
		जाओ करोne;
	पूर्ण

	fecparam->fec = 0;
	fec_cfg = abilities.fec_cfg_curr_mod_ext_info;
	अगर (fec_cfg & I40E_AQ_SET_FEC_AUTO)
		fecparam->fec |= ETHTOOL_FEC_AUTO;
	अन्यथा अगर (fec_cfg & (I40E_AQ_SET_FEC_REQUEST_RS |
		 I40E_AQ_SET_FEC_ABILITY_RS))
		fecparam->fec |= ETHTOOL_FEC_RS;
	अन्यथा अगर (fec_cfg & (I40E_AQ_SET_FEC_REQUEST_KR |
		 I40E_AQ_SET_FEC_ABILITY_KR))
		fecparam->fec |= ETHTOOL_FEC_BASER;
	अगर (fec_cfg == 0)
		fecparam->fec |= ETHTOOL_FEC_OFF;

	अगर (hw->phy.link_info.fec_info & I40E_AQ_CONFIG_FEC_KR_ENA)
		fecparam->active_fec = ETHTOOL_FEC_BASER;
	अन्यथा अगर (hw->phy.link_info.fec_info & I40E_AQ_CONFIG_FEC_RS_ENA)
		fecparam->active_fec = ETHTOOL_FEC_RS;
	अन्यथा
		fecparam->active_fec = ETHTOOL_FEC_OFF;
करोne:
	वापस err;
पूर्ण

अटल पूर्णांक i40e_set_fec_param(काष्ठा net_device *netdev,
			      काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u8 fec_cfg = 0;

	अगर (hw->device_id != I40E_DEV_ID_25G_SFP28 &&
	    hw->device_id != I40E_DEV_ID_25G_B &&
	    hw->device_id != I40E_DEV_ID_KX_X722)
		वापस -EPERM;

	अगर (hw->mac.type == I40E_MAC_X722 &&
	    !(hw->flags & I40E_HW_FLAG_X722_FEC_REQUEST_CAPABLE)) अणु
		netdev_err(netdev, "Setting FEC encoding not supported by firmware. Please update the NVM image.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (fecparam->fec) अणु
	हाल ETHTOOL_FEC_AUTO:
		fec_cfg = I40E_AQ_SET_FEC_AUTO;
		अवरोध;
	हाल ETHTOOL_FEC_RS:
		fec_cfg = (I40E_AQ_SET_FEC_REQUEST_RS |
			     I40E_AQ_SET_FEC_ABILITY_RS);
		अवरोध;
	हाल ETHTOOL_FEC_BASER:
		fec_cfg = (I40E_AQ_SET_FEC_REQUEST_KR |
			     I40E_AQ_SET_FEC_ABILITY_KR);
		अवरोध;
	हाल ETHTOOL_FEC_OFF:
	हाल ETHTOOL_FEC_NONE:
		fec_cfg = 0;
		अवरोध;
	शेष:
		dev_warn(&pf->pdev->dev, "Unsupported FEC mode: %d",
			 fecparam->fec);
		वापस -EINVAL;
	पूर्ण

	वापस i40e_set_fec_cfg(netdev, fec_cfg);
पूर्ण

अटल पूर्णांक i40e_nway_reset(काष्ठा net_device *netdev)
अणु
	/* restart स्वतःnegotiation */
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	bool link_up = hw->phy.link_info.link_info & I40E_AQ_LINK_UP;
	i40e_status ret = 0;

	ret = i40e_aq_set_link_restart_an(hw, link_up, शून्य);
	अगर (ret) अणु
		netdev_info(netdev, "link restart failed, err %s aq_err %s\n",
			    i40e_stat_str(hw, ret),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_get_छोड़ोparam -  Get Flow Control status
 * @netdev: netdevice काष्ठाure
 * @छोड़ो: buffer to वापस छोड़ो parameters
 *
 * Return tx/rx-छोड़ो status
 **/
अटल व्योम i40e_get_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_link_status *hw_link_info = &hw->phy.link_info;
	काष्ठा i40e_dcbx_config *dcbx_cfg = &hw->local_dcbx_config;

	छोड़ो->स्वतःneg =
		((hw_link_info->an_info & I40E_AQ_AN_COMPLETED) ?
		  AUTONEG_ENABLE : AUTONEG_DISABLE);

	/* PFC enabled so report LFC as off */
	अगर (dcbx_cfg->pfc.pfcenable) अणु
		छोड़ो->rx_छोड़ो = 0;
		छोड़ो->tx_छोड़ो = 0;
		वापस;
	पूर्ण

	अगर (hw->fc.current_mode == I40E_FC_RX_PAUSE) अणु
		छोड़ो->rx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == I40E_FC_TX_PAUSE) अणु
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == I40E_FC_FULL) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

/**
 * i40e_set_छोड़ोparam - Set Flow Control parameter
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @छोड़ो: वापस tx/rx flow control status
 **/
अटल पूर्णांक i40e_set_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_link_status *hw_link_info = &hw->phy.link_info;
	काष्ठा i40e_dcbx_config *dcbx_cfg = &hw->local_dcbx_config;
	bool link_up = hw_link_info->link_info & I40E_AQ_LINK_UP;
	i40e_status status;
	u8 aq_failures;
	पूर्णांक err = 0;
	u32 is_an;

	/* Changing the port's flow control is not supported if this isn't the
	 * port's controlling PF
	 */
	अगर (hw->partition_id != 1) अणु
		i40e_partition_setting_complaपूर्णांक(pf);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vsi != pf->vsi[pf->lan_vsi])
		वापस -EOPNOTSUPP;

	is_an = hw_link_info->an_info & I40E_AQ_AN_COMPLETED;
	अगर (छोड़ो->स्वतःneg != is_an) अणु
		netdev_info(netdev, "To change autoneg please use: ethtool -s <dev> autoneg <on|off>\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If we have link and करोn't have स्वतःneg */
	अगर (!test_bit(__I40E_DOWN, pf->state) && !is_an) अणु
		/* Send message that it might not necessarily work*/
		netdev_info(netdev, "Autoneg did not complete so changing settings may not result in an actual change.\n");
	पूर्ण

	अगर (dcbx_cfg->pfc.pfcenable) अणु
		netdev_info(netdev,
			    "Priority flow control enabled. Cannot set link flow control.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		hw->fc.requested_mode = I40E_FC_FULL;
	अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		hw->fc.requested_mode = I40E_FC_RX_PAUSE;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		hw->fc.requested_mode = I40E_FC_TX_PAUSE;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		hw->fc.requested_mode = I40E_FC_NONE;
	अन्यथा
		वापस -EINVAL;

	/* Tell the OS link is going करोwn, the link will go back up when fw
	 * says it is पढ़ोy asynchronously
	 */
	i40e_prपूर्णांक_link_message(vsi, false);
	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(netdev);

	/* Set the fc mode and only restart an अगर link is up*/
	status = i40e_set_fc(hw, &aq_failures, link_up);

	अगर (aq_failures & I40E_SET_FC_AQ_FAIL_GET) अणु
		netdev_info(netdev, "Set fc failed on the get_phy_capabilities call with err %s aq_err %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		err = -EAGAIN;
	पूर्ण
	अगर (aq_failures & I40E_SET_FC_AQ_FAIL_SET) अणु
		netdev_info(netdev, "Set fc failed on the set_phy_config call with err %s aq_err %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		err = -EAGAIN;
	पूर्ण
	अगर (aq_failures & I40E_SET_FC_AQ_FAIL_UPDATE) अणु
		netdev_info(netdev, "Set fc failed on the get_link_info call with err %s aq_err %s\n",
			    i40e_stat_str(hw, status),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		err = -EAGAIN;
	पूर्ण

	अगर (!test_bit(__I40E_DOWN, pf->state) && is_an) अणु
		/* Give it a little more समय to try to come back */
		msleep(75);
		अगर (!test_bit(__I40E_DOWN, pf->state))
			वापस i40e_nway_reset(netdev);
	पूर्ण

	वापस err;
पूर्ण

अटल u32 i40e_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	u32 debug_mask = pf->hw.debug_mask;

	अगर (debug_mask)
		netdev_info(netdev, "i40e debug_mask: 0x%08X\n", debug_mask);

	वापस pf->msg_enable;
पूर्ण

अटल व्योम i40e_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;

	अगर (I40E_DEBUG_USER & data)
		pf->hw.debug_mask = data;
	अन्यथा
		pf->msg_enable = data;
पूर्ण

अटल पूर्णांक i40e_get_regs_len(काष्ठा net_device *netdev)
अणु
	पूर्णांक reg_count = 0;
	पूर्णांक i;

	क्रम (i = 0; i40e_reg_list[i].offset != 0; i++)
		reg_count += i40e_reg_list[i].elements;

	वापस reg_count * माप(u32);
पूर्ण

अटल व्योम i40e_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs,
			  व्योम *p)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 *reg_buf = p;
	अचिन्हित पूर्णांक i, j, ri;
	u32 reg;

	/* Tell ethtool which driver-version-specअगरic regs output we have.
	 *
	 * At some poपूर्णांक, अगर we have ethtool करोing special क्रमmatting of
	 * this data, it will rely on this version number to know how to
	 * पूर्णांकerpret things.  Hence, this needs to be updated अगर/when the
	 * diags रेजिस्टर table is changed.
	 */
	regs->version = 1;

	/* loop through the diags reg table क्रम what to prपूर्णांक */
	ri = 0;
	क्रम (i = 0; i40e_reg_list[i].offset != 0; i++) अणु
		क्रम (j = 0; j < i40e_reg_list[i].elements; j++) अणु
			reg = i40e_reg_list[i].offset
				+ (j * i40e_reg_list[i].stride);
			reg_buf[ri++] = rd32(hw, reg);
		पूर्ण
	पूर्ण

पूर्ण

अटल पूर्णांक i40e_get_eeprom(काष्ठा net_device *netdev,
			   काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_hw *hw = &np->vsi->back->hw;
	काष्ठा i40e_pf *pf = np->vsi->back;
	पूर्णांक ret_val = 0, len, offset;
	u8 *eeprom_buff;
	u16 i, sectors;
	bool last;
	u32 magic;

#घोषणा I40E_NVM_SECTOR_SIZE  4096
	अगर (eeprom->len == 0)
		वापस -EINVAL;

	/* check क्रम NVMUpdate access method */
	magic = hw->venकरोr_id | (hw->device_id << 16);
	अगर (eeprom->magic && eeprom->magic != magic) अणु
		काष्ठा i40e_nvm_access *cmd = (काष्ठा i40e_nvm_access *)eeprom;
		पूर्णांक त्रुटि_सं = 0;

		/* make sure it is the right magic क्रम NVMUpdate */
		अगर ((eeprom->magic >> 16) != hw->device_id)
			त्रुटि_सं = -EINVAL;
		अन्यथा अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
			 test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
			त्रुटि_सं = -EBUSY;
		अन्यथा
			ret_val = i40e_nvmupd_command(hw, cmd, bytes, &त्रुटि_सं);

		अगर ((त्रुटि_सं || ret_val) && (hw->debug_mask & I40E_DEBUG_NVM))
			dev_info(&pf->pdev->dev,
				 "NVMUpdate read failed err=%d status=0x%x errno=%d module=%d offset=0x%x size=%d\n",
				 ret_val, hw->aq.asq_last_status, त्रुटि_सं,
				 (u8)(cmd->config & I40E_NVM_MOD_PNT_MASK),
				 cmd->offset, cmd->data_size);

		वापस त्रुटि_सं;
	पूर्ण

	/* normal ethtool get_eeprom support */
	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);

	eeprom_buff = kzalloc(eeprom->len, GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ret_val = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret_val) अणु
		dev_info(&pf->pdev->dev,
			 "Failed Acquiring NVM resource for read err=%d status=0x%x\n",
			 ret_val, hw->aq.asq_last_status);
		जाओ मुक्त_buff;
	पूर्ण

	sectors = eeprom->len / I40E_NVM_SECTOR_SIZE;
	sectors += (eeprom->len % I40E_NVM_SECTOR_SIZE) ? 1 : 0;
	len = I40E_NVM_SECTOR_SIZE;
	last = false;
	क्रम (i = 0; i < sectors; i++) अणु
		अगर (i == (sectors - 1)) अणु
			len = eeprom->len - (I40E_NVM_SECTOR_SIZE * i);
			last = true;
		पूर्ण
		offset = eeprom->offset + (I40E_NVM_SECTOR_SIZE * i),
		ret_val = i40e_aq_पढ़ो_nvm(hw, 0x0, offset, len,
				(u8 *)eeprom_buff + (I40E_NVM_SECTOR_SIZE * i),
				last, शून्य);
		अगर (ret_val && hw->aq.asq_last_status == I40E_AQ_RC_EPERM) अणु
			dev_info(&pf->pdev->dev,
				 "read NVM failed, invalid offset 0x%x\n",
				 offset);
			अवरोध;
		पूर्ण अन्यथा अगर (ret_val &&
			   hw->aq.asq_last_status == I40E_AQ_RC_EACCES) अणु
			dev_info(&pf->pdev->dev,
				 "read NVM failed, access, offset 0x%x\n",
				 offset);
			अवरोध;
		पूर्ण अन्यथा अगर (ret_val) अणु
			dev_info(&pf->pdev->dev,
				 "read NVM failed offset %d err=%d status=0x%x\n",
				 offset, ret_val, hw->aq.asq_last_status);
			अवरोध;
		पूर्ण
	पूर्ण

	i40e_release_nvm(hw);
	स_नकल(bytes, (u8 *)eeprom_buff, eeprom->len);
मुक्त_buff:
	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल पूर्णांक i40e_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_hw *hw = &np->vsi->back->hw;
	u32 val;

#घोषणा X722_EEPROM_SCOPE_LIMIT 0x5B9FFF
	अगर (hw->mac.type == I40E_MAC_X722) अणु
		val = X722_EEPROM_SCOPE_LIMIT + 1;
		वापस val;
	पूर्ण
	val = (rd32(hw, I40E_GLPCI_LBARCTRL)
		& I40E_GLPCI_LBARCTRL_FL_SIZE_MASK)
		>> I40E_GLPCI_LBARCTRL_FL_SIZE_SHIFT;
	/* रेजिस्टर वापसs value in घातer of 2, 64Kbyte chunks. */
	val = (64 * 1024) * BIT(val);
	वापस val;
पूर्ण

अटल पूर्णांक i40e_set_eeprom(काष्ठा net_device *netdev,
			   काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_hw *hw = &np->vsi->back->hw;
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_nvm_access *cmd = (काष्ठा i40e_nvm_access *)eeprom;
	पूर्णांक ret_val = 0;
	पूर्णांक त्रुटि_सं = 0;
	u32 magic;

	/* normal ethtool set_eeprom is not supported */
	magic = hw->venकरोr_id | (hw->device_id << 16);
	अगर (eeprom->magic == magic)
		त्रुटि_सं = -EOPNOTSUPP;
	/* check क्रम NVMUpdate access method */
	अन्यथा अगर (!eeprom->magic || (eeprom->magic >> 16) != hw->device_id)
		त्रुटि_सं = -EINVAL;
	अन्यथा अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
		 test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		त्रुटि_सं = -EBUSY;
	अन्यथा
		ret_val = i40e_nvmupd_command(hw, cmd, bytes, &त्रुटि_सं);

	अगर ((त्रुटि_सं || ret_val) && (hw->debug_mask & I40E_DEBUG_NVM))
		dev_info(&pf->pdev->dev,
			 "NVMUpdate write failed err=%d status=0x%x errno=%d module=%d offset=0x%x size=%d\n",
			 ret_val, hw->aq.asq_last_status, त्रुटि_सं,
			 (u8)(cmd->config & I40E_NVM_MOD_PNT_MASK),
			 cmd->offset, cmd->data_size);

	वापस त्रुटि_सं;
पूर्ण

अटल व्योम i40e_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;

	strlcpy(drvinfo->driver, i40e_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->fw_version, i40e_nvm_version_str(&pf->hw),
		माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(pf->pdev),
		माप(drvinfo->bus_info));
	drvinfo->n_priv_flags = I40E_PRIV_FLAGS_STR_LEN;
	अगर (pf->hw.pf_id == 0)
		drvinfo->n_priv_flags += I40E_GL_PRIV_FLAGS_STR_LEN;
पूर्ण

अटल व्योम i40e_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vsi *vsi = pf->vsi[pf->lan_vsi];

	ring->rx_max_pending = I40E_MAX_NUM_DESCRIPTORS;
	ring->tx_max_pending = I40E_MAX_NUM_DESCRIPTORS;
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_pending = vsi->rx_rings[0]->count;
	ring->tx_pending = vsi->tx_rings[0]->count;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
पूर्ण

अटल bool i40e_active_tx_ring_index(काष्ठा i40e_vsi *vsi, u16 index)
अणु
	अगर (i40e_enabled_xdp_vsi(vsi)) अणु
		वापस index < vsi->num_queue_pairs ||
			(index >= vsi->alloc_queue_pairs &&
			 index < vsi->alloc_queue_pairs + vsi->num_queue_pairs);
	पूर्ण

	वापस index < vsi->num_queue_pairs;
पूर्ण

अटल पूर्णांक i40e_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा i40e_ring *tx_rings = शून्य, *rx_rings = शून्य;
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_hw *hw = &np->vsi->back->hw;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	u32 new_rx_count, new_tx_count;
	u16 tx_alloc_queue_pairs;
	पूर्णांक समयout = 50;
	पूर्णांक i, err = 0;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	अगर (ring->tx_pending > I40E_MAX_NUM_DESCRIPTORS ||
	    ring->tx_pending < I40E_MIN_NUM_DESCRIPTORS ||
	    ring->rx_pending > I40E_MAX_NUM_DESCRIPTORS ||
	    ring->rx_pending < I40E_MIN_NUM_DESCRIPTORS) अणु
		netdev_info(netdev,
			    "Descriptors requested (Tx: %d / Rx: %d) out of range [%d-%d]\n",
			    ring->tx_pending, ring->rx_pending,
			    I40E_MIN_NUM_DESCRIPTORS, I40E_MAX_NUM_DESCRIPTORS);
		वापस -EINVAL;
	पूर्ण

	new_tx_count = ALIGN(ring->tx_pending, I40E_REQ_DESCRIPTOR_MULTIPLE);
	new_rx_count = ALIGN(ring->rx_pending, I40E_REQ_DESCRIPTOR_MULTIPLE);

	/* अगर nothing to करो वापस success */
	अगर ((new_tx_count == vsi->tx_rings[0]->count) &&
	    (new_rx_count == vsi->rx_rings[0]->count))
		वापस 0;

	/* If there is a AF_XDP page pool attached to any of Rx rings,
	 * disallow changing the number of descriptors -- regardless
	 * अगर the netdev is running or not.
	 */
	अगर (i40e_xsk_any_rx_ring_enabled(vsi))
		वापस -EBUSY;

	जबतक (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state)) अणु
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
		usleep_range(1000, 2000);
	पूर्ण

	अगर (!netअगर_running(vsi->netdev)) अणु
		/* simple हाल - set क्रम the next समय the netdev is started */
		क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
			vsi->tx_rings[i]->count = new_tx_count;
			vsi->rx_rings[i]->count = new_rx_count;
			अगर (i40e_enabled_xdp_vsi(vsi))
				vsi->xdp_rings[i]->count = new_tx_count;
		पूर्ण
		vsi->num_tx_desc = new_tx_count;
		vsi->num_rx_desc = new_rx_count;
		जाओ करोne;
	पूर्ण

	/* We can't just मुक्त everything and then setup again,
	 * because the ISRs in MSI-X mode get passed poपूर्णांकers
	 * to the Tx and Rx ring काष्ठाs.
	 */

	/* alloc updated Tx and XDP Tx resources */
	tx_alloc_queue_pairs = vsi->alloc_queue_pairs *
			       (i40e_enabled_xdp_vsi(vsi) ? 2 : 1);
	अगर (new_tx_count != vsi->tx_rings[0]->count) अणु
		netdev_info(netdev,
			    "Changing Tx descriptor count from %d to %d.\n",
			    vsi->tx_rings[0]->count, new_tx_count);
		tx_rings = kसुस्मृति(tx_alloc_queue_pairs,
				   माप(काष्ठा i40e_ring), GFP_KERNEL);
		अगर (!tx_rings) अणु
			err = -ENOMEM;
			जाओ करोne;
		पूर्ण

		क्रम (i = 0; i < tx_alloc_queue_pairs; i++) अणु
			अगर (!i40e_active_tx_ring_index(vsi, i))
				जारी;

			tx_rings[i] = *vsi->tx_rings[i];
			tx_rings[i].count = new_tx_count;
			/* the desc and bi poपूर्णांकers will be पुनः_स्मृतिated in the
			 * setup call
			 */
			tx_rings[i].desc = शून्य;
			tx_rings[i].rx_bi = शून्य;
			err = i40e_setup_tx_descriptors(&tx_rings[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					अगर (!i40e_active_tx_ring_index(vsi, i))
						जारी;
					i40e_मुक्त_tx_resources(&tx_rings[i]);
				पूर्ण
				kमुक्त(tx_rings);
				tx_rings = शून्य;

				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	/* alloc updated Rx resources */
	अगर (new_rx_count != vsi->rx_rings[0]->count) अणु
		netdev_info(netdev,
			    "Changing Rx descriptor count from %d to %d\n",
			    vsi->rx_rings[0]->count, new_rx_count);
		rx_rings = kसुस्मृति(vsi->alloc_queue_pairs,
				   माप(काष्ठा i40e_ring), GFP_KERNEL);
		अगर (!rx_rings) अणु
			err = -ENOMEM;
			जाओ मुक्त_tx;
		पूर्ण

		क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
			u16 unused;

			/* clone ring and setup updated count */
			rx_rings[i] = *vsi->rx_rings[i];
			rx_rings[i].count = new_rx_count;
			/* the desc and bi poपूर्णांकers will be पुनः_स्मृतिated in the
			 * setup call
			 */
			rx_rings[i].desc = शून्य;
			rx_rings[i].rx_bi = शून्य;
			/* Clear cloned XDP RX-queue info beक्रमe setup call */
			स_रखो(&rx_rings[i].xdp_rxq, 0, माप(rx_rings[i].xdp_rxq));
			/* this is to allow wr32 to have something to ग_लिखो to
			 * during early allocation of Rx buffers
			 */
			rx_rings[i].tail = hw->hw_addr + I40E_PRTGEN_STATUS;
			err = i40e_setup_rx_descriptors(&rx_rings[i]);
			अगर (err)
				जाओ rx_unwind;
			err = i40e_alloc_rx_bi(&rx_rings[i]);
			अगर (err)
				जाओ rx_unwind;

			/* now allocate the Rx buffers to make sure the OS
			 * has enough memory, any failure here means पात
			 */
			unused = I40E_DESC_UNUSED(&rx_rings[i]);
			err = i40e_alloc_rx_buffers(&rx_rings[i], unused);
rx_unwind:
			अगर (err) अणु
				करो अणु
					i40e_मुक्त_rx_resources(&rx_rings[i]);
				पूर्ण जबतक (i--);
				kमुक्त(rx_rings);
				rx_rings = शून्य;

				जाओ मुक्त_tx;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Bring पूर्णांकerface करोwn, copy in the new ring info,
	 * then restore the पूर्णांकerface
	 */
	i40e_करोwn(vsi);

	अगर (tx_rings) अणु
		क्रम (i = 0; i < tx_alloc_queue_pairs; i++) अणु
			अगर (i40e_active_tx_ring_index(vsi, i)) अणु
				i40e_मुक्त_tx_resources(vsi->tx_rings[i]);
				*vsi->tx_rings[i] = tx_rings[i];
			पूर्ण
		पूर्ण
		kमुक्त(tx_rings);
		tx_rings = शून्य;
	पूर्ण

	अगर (rx_rings) अणु
		क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
			i40e_मुक्त_rx_resources(vsi->rx_rings[i]);
			/* get the real tail offset */
			rx_rings[i].tail = vsi->rx_rings[i]->tail;
			/* this is to fake out the allocation routine
			 * पूर्णांकo thinking it has to पुनः_स्मृति everything
			 * but the recycling logic will let us re-use
			 * the buffers allocated above
			 */
			rx_rings[i].next_to_use = 0;
			rx_rings[i].next_to_clean = 0;
			rx_rings[i].next_to_alloc = 0;
			/* करो a काष्ठा copy */
			*vsi->rx_rings[i] = rx_rings[i];
		पूर्ण
		kमुक्त(rx_rings);
		rx_rings = शून्य;
	पूर्ण

	vsi->num_tx_desc = new_tx_count;
	vsi->num_rx_desc = new_rx_count;
	i40e_up(vsi);

मुक्त_tx:
	/* error cleanup अगर the Rx allocations failed after getting Tx */
	अगर (tx_rings) अणु
		क्रम (i = 0; i < tx_alloc_queue_pairs; i++) अणु
			अगर (i40e_active_tx_ring_index(vsi, i))
				i40e_मुक्त_tx_resources(vsi->tx_rings[i]);
		पूर्ण
		kमुक्त(tx_rings);
		tx_rings = शून्य;
	पूर्ण

करोne:
	clear_bit(__I40E_CONFIG_BUSY, pf->state);

	वापस err;
पूर्ण

/**
 * i40e_get_stats_count - वापस the stats count क्रम a device
 * @netdev: the netdev to वापस the count क्रम
 *
 * Returns the total number of statistics क्रम this netdev. Note that even
 * though this is a function, it is required that the count क्रम a specअगरic
 * netdev must never change. Basing the count on अटल values such as the
 * maximum number of queues or the device type is ok. However, the API क्रम
 * obtaining stats is *not* safe against changes based on non-अटल
 * values such as the *current* number of queues, or runसमय flags.
 *
 * If a statistic is not always enabled, वापस it as part of the count
 * anyways, always वापस its string, and report its value as zero.
 **/
अटल पूर्णांक i40e_get_stats_count(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक stats_len;

	अगर (vsi == pf->vsi[pf->lan_vsi] && pf->hw.partition_id == 1)
		stats_len = I40E_PF_STATS_LEN;
	अन्यथा
		stats_len = I40E_VSI_STATS_LEN;

	/* The number of stats reported क्रम a given net_device must reमुख्य
	 * स्थिरant throughout the lअगरe of that device.
	 *
	 * This is because the API क्रम obtaining the size, strings, and stats
	 * is spपढ़ो out over three separate ethtool ioctls. There is no safe
	 * way to lock the number of stats across these calls, so we must
	 * assume that they will never change.
	 *
	 * Due to this, we report the maximum number of queues, even अगर not
	 * every queue is currently configured. Since we always allocate
	 * queues in pairs, we'll just use netdev->num_tx_queues * 2. This
	 * works because the num_tx_queues is set at device creation and never
	 * changes.
	 */
	stats_len += I40E_QUEUE_STATS_LEN * 2 * netdev->num_tx_queues;

	वापस stats_len;
पूर्ण

अटल पूर्णांक i40e_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;

	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस I40E_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस i40e_get_stats_count(netdev);
	हाल ETH_SS_PRIV_FLAGS:
		वापस I40E_PRIV_FLAGS_STR_LEN +
			(pf->hw.pf_id == 0 ? I40E_GL_PRIV_FLAGS_STR_LEN : 0);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * i40e_get_veb_tc_stats - copy VEB TC statistics to क्रमmatted काष्ठाure
 * @tc: the TC statistics in VEB काष्ठाure (veb->tc_stats)
 * @i: the index of traffic class in (veb->tc_stats) काष्ठाure to copy
 *
 * Copy VEB TC statistics from काष्ठाure of arrays (veb->tc_stats) to
 * one dimensional काष्ठाure i40e_cp_veb_tc_stats.
 * Produce क्रमmatted i40e_cp_veb_tc_stats काष्ठाure of the VEB TC
 * statistics क्रम the given TC.
 **/
अटल काष्ठा i40e_cp_veb_tc_stats
i40e_get_veb_tc_stats(काष्ठा i40e_veb_tc_stats *tc, अचिन्हित पूर्णांक i)
अणु
	काष्ठा i40e_cp_veb_tc_stats veb_tc = अणु
		.tc_rx_packets = tc->tc_rx_packets[i],
		.tc_rx_bytes = tc->tc_rx_bytes[i],
		.tc_tx_packets = tc->tc_tx_packets[i],
		.tc_tx_bytes = tc->tc_tx_bytes[i],
	पूर्ण;

	वापस veb_tc;
पूर्ण

/**
 * i40e_get_pfc_stats - copy HW PFC statistics to क्रमmatted काष्ठाure
 * @pf: the PF device काष्ठाure
 * @i: the priority value to copy
 *
 * The PFC stats are found as arrays in pf->stats, which is not easy to pass
 * पूर्णांकo i40e_add_ethtool_stats. Produce a क्रमmatted i40e_pfc_stats काष्ठाure
 * of the PFC stats क्रम the given priority.
 **/
अटल अंतरभूत काष्ठा i40e_pfc_stats
i40e_get_pfc_stats(काष्ठा i40e_pf *pf, अचिन्हित पूर्णांक i)
अणु
#घोषणा I40E_GET_PFC_STAT(stat, priority) \
	.stat = pf->stats.stat[priority]

	काष्ठा i40e_pfc_stats pfc = अणु
		I40E_GET_PFC_STAT(priority_xon_rx, i),
		I40E_GET_PFC_STAT(priority_xoff_rx, i),
		I40E_GET_PFC_STAT(priority_xon_tx, i),
		I40E_GET_PFC_STAT(priority_xoff_tx, i),
		I40E_GET_PFC_STAT(priority_xon_2_xoff, i),
	पूर्ण;
	वापस pfc;
पूर्ण

/**
 * i40e_get_ethtool_stats - copy stat values पूर्णांकo supplied buffer
 * @netdev: the netdev to collect stats क्रम
 * @stats: ethtool stats command काष्ठाure
 * @data: ethtool supplied buffer
 *
 * Copy the stats values क्रम this netdev पूर्णांकo the buffer. Expects data to be
 * pre-allocated to the size वापसed by i40e_get_stats_count.. Note that all
 * statistics must be copied in a अटल order, and the count must not change
 * क्रम a given netdev. See i40e_get_stats_count क्रम more details.
 *
 * If a statistic is not currently valid (such as a disabled queue), this
 * function reports its value as zero.
 **/
अटल व्योम i40e_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_veb *veb = शून्य;
	अचिन्हित पूर्णांक i;
	bool veb_stats;
	u64 *p = data;

	i40e_update_stats(vsi);

	i40e_add_ethtool_stats(&data, i40e_get_vsi_stats_काष्ठा(vsi),
			       i40e_gstrings_net_stats);

	i40e_add_ethtool_stats(&data, vsi, i40e_gstrings_misc_stats);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < netdev->num_tx_queues; i++) अणु
		i40e_add_queue_stats(&data, READ_ONCE(vsi->tx_rings[i]));
		i40e_add_queue_stats(&data, READ_ONCE(vsi->rx_rings[i]));
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (vsi != pf->vsi[pf->lan_vsi] || pf->hw.partition_id != 1)
		जाओ check_data_poपूर्णांकer;

	veb_stats = ((pf->lan_veb != I40E_NO_VEB) &&
		     (pf->lan_veb < I40E_MAX_VEB) &&
		     (pf->flags & I40E_FLAG_VEB_STATS_ENABLED));

	अगर (veb_stats) अणु
		veb = pf->veb[pf->lan_veb];
		i40e_update_veb_stats(veb);
	पूर्ण

	/* If veb stats aren't enabled, pass शून्य instead of the veb so that
	 * we initialize stats to zero and update the data poपूर्णांकer
	 * पूर्णांकelligently
	 */
	i40e_add_ethtool_stats(&data, veb_stats ? veb : शून्य,
			       i40e_gstrings_veb_stats);

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		अगर (veb_stats) अणु
			काष्ठा i40e_cp_veb_tc_stats veb_tc =
				i40e_get_veb_tc_stats(&veb->tc_stats, i);

			i40e_add_ethtool_stats(&data, &veb_tc,
					       i40e_gstrings_veb_tc_stats);
		पूर्ण अन्यथा अणु
			i40e_add_ethtool_stats(&data, शून्य,
					       i40e_gstrings_veb_tc_stats);
		पूर्ण

	i40e_add_ethtool_stats(&data, pf, i40e_gstrings_stats);

	क्रम (i = 0; i < I40E_MAX_USER_PRIORITY; i++) अणु
		काष्ठा i40e_pfc_stats pfc = i40e_get_pfc_stats(pf, i);

		i40e_add_ethtool_stats(&data, &pfc, i40e_gstrings_pfc_stats);
	पूर्ण

check_data_poपूर्णांकer:
	WARN_ONCE(data - p != i40e_get_stats_count(netdev),
		  "ethtool stats count mismatch!");
पूर्ण

/**
 * i40e_get_stat_strings - copy stat strings पूर्णांकo supplied buffer
 * @netdev: the netdev to collect strings क्रम
 * @data: supplied buffer to copy strings पूर्णांकo
 *
 * Copy the strings related to stats क्रम this netdev. Expects data to be
 * pre-allocated with the size reported by i40e_get_stats_count. Note that the
 * strings must be copied in a अटल order and the total count must not
 * change क्रम a given netdev. See i40e_get_stats_count क्रम more details.
 **/
अटल व्योम i40e_get_stat_strings(काष्ठा net_device *netdev, u8 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	अचिन्हित पूर्णांक i;
	u8 *p = data;

	i40e_add_stat_strings(&data, i40e_gstrings_net_stats);

	i40e_add_stat_strings(&data, i40e_gstrings_misc_stats);

	क्रम (i = 0; i < netdev->num_tx_queues; i++) अणु
		i40e_add_stat_strings(&data, i40e_gstrings_queue_stats,
				      "tx", i);
		i40e_add_stat_strings(&data, i40e_gstrings_queue_stats,
				      "rx", i);
	पूर्ण

	अगर (vsi != pf->vsi[pf->lan_vsi] || pf->hw.partition_id != 1)
		जाओ check_data_poपूर्णांकer;

	i40e_add_stat_strings(&data, i40e_gstrings_veb_stats);

	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		i40e_add_stat_strings(&data, i40e_gstrings_veb_tc_stats, i);

	i40e_add_stat_strings(&data, i40e_gstrings_stats);

	क्रम (i = 0; i < I40E_MAX_USER_PRIORITY; i++)
		i40e_add_stat_strings(&data, i40e_gstrings_pfc_stats, i);

check_data_poपूर्णांकer:
	WARN_ONCE(data - p != i40e_get_stats_count(netdev) * ETH_GSTRING_LEN,
		  "stat strings count mismatch!");
पूर्ण

अटल व्योम i40e_get_priv_flag_strings(काष्ठा net_device *netdev, u8 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	अचिन्हित पूर्णांक i;
	u8 *p = data;

	क्रम (i = 0; i < I40E_PRIV_FLAGS_STR_LEN; i++)
		ethtool_प्र_लिखो(&p, i40e_gstrings_priv_flags[i].flag_string);
	अगर (pf->hw.pf_id != 0)
		वापस;
	क्रम (i = 0; i < I40E_GL_PRIV_FLAGS_STR_LEN; i++)
		ethtool_प्र_लिखो(&p, i40e_gl_gstrings_priv_flags[i].flag_string);
पूर्ण

अटल व्योम i40e_get_strings(काष्ठा net_device *netdev, u32 stringset,
			     u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, i40e_gstrings_test,
		       I40E_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		i40e_get_stat_strings(netdev, data);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		i40e_get_priv_flag_strings(netdev, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक i40e_get_ts_info(काष्ठा net_device *dev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);

	/* only report HW बारtamping अगर PTP is enabled */
	अगर (!(pf->flags & I40E_FLAG_PTP))
		वापस ethtool_op_get_ts_info(dev, info);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	अगर (pf->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(pf->ptp_घड़ी);
	अन्यथा
		info->phc_index = -1;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ);

	अगर (pf->hw_features & I40E_HW_PTP_L4_CAPABLE)
		info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
				    BIT(HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
				    BIT(HWTSTAMP_FILTER_PTP_V2_EVENT) |
				    BIT(HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
				    BIT(HWTSTAMP_FILTER_PTP_V2_SYNC) |
				    BIT(HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
				    BIT(HWTSTAMP_FILTER_PTP_V2_DELAY_REQ) |
				    BIT(HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ);

	वापस 0;
पूर्ण

अटल u64 i40e_link_test(काष्ठा net_device *netdev, u64 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	i40e_status status;
	bool link_up = false;

	netअगर_info(pf, hw, netdev, "link test\n");
	status = i40e_get_link_status(&pf->hw, &link_up);
	अगर (status) अणु
		netअगर_err(pf, drv, netdev, "link query timed out, please retry test\n");
		*data = 1;
		वापस *data;
	पूर्ण

	अगर (link_up)
		*data = 0;
	अन्यथा
		*data = 1;

	वापस *data;
पूर्ण

अटल u64 i40e_reg_test(काष्ठा net_device *netdev, u64 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;

	netअगर_info(pf, hw, netdev, "register test\n");
	*data = i40e_diag_reg_test(&pf->hw);

	वापस *data;
पूर्ण

अटल u64 i40e_eeprom_test(काष्ठा net_device *netdev, u64 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;

	netअगर_info(pf, hw, netdev, "eeprom test\n");
	*data = i40e_diag_eeprom_test(&pf->hw);

	/* क्रमcebly clear the NVM Update state machine */
	pf->hw.nvmupd_state = I40E_NVMUPD_STATE_INIT;

	वापस *data;
पूर्ण

अटल u64 i40e_पूर्णांकr_test(काष्ठा net_device *netdev, u64 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	u16 swc_old = pf->sw_पूर्णांक_count;

	netअगर_info(pf, hw, netdev, "interrupt test\n");
	wr32(&pf->hw, I40E_PFINT_DYN_CTL0,
	     (I40E_PFINT_DYN_CTL0_INTENA_MASK |
	      I40E_PFINT_DYN_CTL0_SWINT_TRIG_MASK |
	      I40E_PFINT_DYN_CTL0_ITR_INDX_MASK |
	      I40E_PFINT_DYN_CTL0_SW_ITR_INDX_ENA_MASK |
	      I40E_PFINT_DYN_CTL0_SW_ITR_INDX_MASK));
	usleep_range(1000, 2000);
	*data = (swc_old == pf->sw_पूर्णांक_count);

	वापस *data;
पूर्ण

अटल अंतरभूत bool i40e_active_vfs(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_vf *vfs = pf->vf;
	पूर्णांक i;

	क्रम (i = 0; i < pf->num_alloc_vfs; i++)
		अगर (test_bit(I40E_VF_STATE_ACTIVE, &vfs[i].vf_states))
			वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool i40e_active_vmdqs(काष्ठा i40e_pf *pf)
अणु
	वापस !!i40e_find_vsi_by_type(pf, I40E_VSI_VMDQ2);
पूर्ण

अटल व्योम i40e_diag_test(काष्ठा net_device *netdev,
			   काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	bool अगर_running = netअगर_running(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;

	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		/* Offline tests */
		netअगर_info(pf, drv, netdev, "offline testing starting\n");

		set_bit(__I40E_TESTING, pf->state);

		अगर (i40e_active_vfs(pf) || i40e_active_vmdqs(pf)) अणु
			dev_warn(&pf->pdev->dev,
				 "Please take active VFs and Netqueues offline and restart the adapter before running NIC diagnostics\n");
			data[I40E_ETH_TEST_REG]		= 1;
			data[I40E_ETH_TEST_EEPROM]	= 1;
			data[I40E_ETH_TEST_INTR]	= 1;
			data[I40E_ETH_TEST_LINK]	= 1;
			eth_test->flags |= ETH_TEST_FL_FAILED;
			clear_bit(__I40E_TESTING, pf->state);
			जाओ skip_ol_tests;
		पूर्ण

		/* If the device is online then take it offline */
		अगर (अगर_running)
			/* indicate we're in test mode */
			i40e_बंद(netdev);
		अन्यथा
			/* This reset करोes not affect link - अगर it is
			 * changed to a type of reset that करोes affect
			 * link then the following link test would have
			 * to be moved to beक्रमe the reset
			 */
			i40e_करो_reset(pf, BIT(__I40E_PF_RESET_REQUESTED), true);

		अगर (i40e_link_test(netdev, &data[I40E_ETH_TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (i40e_eeprom_test(netdev, &data[I40E_ETH_TEST_EEPROM]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (i40e_पूर्णांकr_test(netdev, &data[I40E_ETH_TEST_INTR]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* run reg test last, a reset is required after it */
		अगर (i40e_reg_test(netdev, &data[I40E_ETH_TEST_REG]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(__I40E_TESTING, pf->state);
		i40e_करो_reset(pf, BIT(__I40E_PF_RESET_REQUESTED), true);

		अगर (अगर_running)
			i40e_खोलो(netdev);
	पूर्ण अन्यथा अणु
		/* Online tests */
		netअगर_info(pf, drv, netdev, "online testing starting\n");

		अगर (i40e_link_test(netdev, &data[I40E_ETH_TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Offline only tests, not run in online; pass by शेष */
		data[I40E_ETH_TEST_REG] = 0;
		data[I40E_ETH_TEST_EEPROM] = 0;
		data[I40E_ETH_TEST_INTR] = 0;
	पूर्ण

skip_ol_tests:

	netअगर_info(pf, drv, netdev, "testing finished\n");
पूर्ण

अटल व्योम i40e_get_wol(काष्ठा net_device *netdev,
			 काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 wol_nvm_bits;

	/* NVM bit on means WoL disabled क्रम the port */
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_WAKE_ON_LAN, &wol_nvm_bits);
	अगर ((BIT(hw->port) & wol_nvm_bits) || (hw->partition_id != 1)) अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण अन्यथा अणु
		wol->supported = WAKE_MAGIC;
		wol->wolopts = (pf->wol_en ? WAKE_MAGIC : 0);
	पूर्ण
पूर्ण

/**
 * i40e_set_wol - set the WakeOnLAN configuration
 * @netdev: the netdev in question
 * @wol: the ethtool WoL setting data
 **/
अटल पूर्णांक i40e_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_hw *hw = &pf->hw;
	u16 wol_nvm_bits;

	/* WoL not supported अगर this isn't the controlling PF on the port */
	अगर (hw->partition_id != 1) अणु
		i40e_partition_setting_complaपूर्णांक(pf);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vsi != pf->vsi[pf->lan_vsi])
		वापस -EOPNOTSUPP;

	/* NVM bit on means WoL disabled क्रम the port */
	i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_WAKE_ON_LAN, &wol_nvm_bits);
	अगर (BIT(hw->port) & wol_nvm_bits)
		वापस -EOPNOTSUPP;

	/* only magic packet is supported */
	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EOPNOTSUPP;

	/* is this a new value? */
	अगर (pf->wol_en != !!wol->wolopts) अणु
		pf->wol_en = !!wol->wolopts;
		device_set_wakeup_enable(&pf->pdev->dev, pf->wol_en);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i40e_set_phys_id(काष्ठा net_device *netdev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	i40e_status ret = 0;
	काष्ठा i40e_pf *pf = np->vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक blink_freq = 2;
	u16 temp_status;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		अगर (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS)) अणु
			pf->led_status = i40e_led_get(hw);
		पूर्ण अन्यथा अणु
			अगर (!(hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE))
				i40e_aq_set_phy_debug(hw, I40E_PHY_DEBUG_ALL,
						      शून्य);
			ret = i40e_led_get_phy(hw, &temp_status,
					       &pf->phy_led_val);
			pf->led_status = temp_status;
		पूर्ण
		वापस blink_freq;
	हाल ETHTOOL_ID_ON:
		अगर (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS))
			i40e_led_set(hw, 0xf, false);
		अन्यथा
			ret = i40e_led_set_phy(hw, true, pf->led_status, 0);
		अवरोध;
	हाल ETHTOOL_ID_OFF:
		अगर (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS))
			i40e_led_set(hw, 0x0, false);
		अन्यथा
			ret = i40e_led_set_phy(hw, false, pf->led_status, 0);
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		अगर (!(pf->hw_features & I40E_HW_PHY_CONTROLS_LEDS)) अणु
			i40e_led_set(hw, pf->led_status, false);
		पूर्ण अन्यथा अणु
			ret = i40e_led_set_phy(hw, false, pf->led_status,
					       (pf->phy_led_val |
					       I40E_PHY_LED_MODE_ORIG));
			अगर (!(hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE))
				i40e_aq_set_phy_debug(hw, 0, शून्य);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (ret)
		वापस -ENOENT;
	अन्यथा
		वापस 0;
पूर्ण

/* NOTE: i40e hardware uses a conversion factor of 2 क्रम Interrupt
 * Throttle Rate (ITR) ie. ITR(1) = 2us ITR(10) = 20 us, and also
 * 125us (8000 पूर्णांकerrupts per second) == ITR(62)
 */

/**
 * __i40e_get_coalesce - get per-queue coalesce settings
 * @netdev: the netdev to check
 * @ec: ethtool coalesce data काष्ठाure
 * @queue: which queue to pick
 *
 * Gets the per-queue settings क्रम coalescence. Specअगरically Rx and Tx usecs
 * are per queue. If queue is <0 then we शेष to queue 0 as the
 * representative value.
 **/
अटल पूर्णांक __i40e_get_coalesce(काष्ठा net_device *netdev,
			       काष्ठा ethtool_coalesce *ec,
			       पूर्णांक queue)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_ring *rx_ring, *tx_ring;
	काष्ठा i40e_vsi *vsi = np->vsi;

	ec->tx_max_coalesced_frames_irq = vsi->work_limit;
	ec->rx_max_coalesced_frames_irq = vsi->work_limit;

	/* rx and tx usecs has per queue value. If user करोesn't specअगरy the
	 * queue, वापस queue 0's value to represent.
	 */
	अगर (queue < 0)
		queue = 0;
	अन्यथा अगर (queue >= vsi->num_queue_pairs)
		वापस -EINVAL;

	rx_ring = vsi->rx_rings[queue];
	tx_ring = vsi->tx_rings[queue];

	अगर (ITR_IS_DYNAMIC(rx_ring->itr_setting))
		ec->use_adaptive_rx_coalesce = 1;

	अगर (ITR_IS_DYNAMIC(tx_ring->itr_setting))
		ec->use_adaptive_tx_coalesce = 1;

	ec->rx_coalesce_usecs = rx_ring->itr_setting & ~I40E_ITR_DYNAMIC;
	ec->tx_coalesce_usecs = tx_ring->itr_setting & ~I40E_ITR_DYNAMIC;

	/* we use the _usecs_high to store/set the पूर्णांकerrupt rate limit
	 * that the hardware supports, that almost but not quite
	 * fits the original पूर्णांकent of the ethtool variable,
	 * the rx_coalesce_usecs_high limits total पूर्णांकerrupts
	 * per second from both tx/rx sources.
	 */
	ec->rx_coalesce_usecs_high = vsi->पूर्णांक_rate_limit;
	ec->tx_coalesce_usecs_high = vsi->पूर्णांक_rate_limit;

	वापस 0;
पूर्ण

/**
 * i40e_get_coalesce - get a netdev's coalesce settings
 * @netdev: the netdev to check
 * @ec: ethtool coalesce data काष्ठाure
 *
 * Gets the coalesce settings क्रम a particular netdev. Note that अगर user has
 * modअगरied per-queue settings, this only guarantees to represent queue 0. See
 * __i40e_get_coalesce क्रम more details.
 **/
अटल पूर्णांक i40e_get_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	वापस __i40e_get_coalesce(netdev, ec, -1);
पूर्ण

/**
 * i40e_get_per_queue_coalesce - माला_लो coalesce settings क्रम particular queue
 * @netdev: netdev काष्ठाure
 * @ec: ethtool's coalesce settings
 * @queue: the particular queue to पढ़ो
 *
 * Will पढ़ो a specअगरic queue's coalesce settings
 **/
अटल पूर्णांक i40e_get_per_queue_coalesce(काष्ठा net_device *netdev, u32 queue,
				       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __i40e_get_coalesce(netdev, ec, queue);
पूर्ण

/**
 * i40e_set_itr_per_queue - set ITR values क्रम specअगरic queue
 * @vsi: the VSI to set values क्रम
 * @ec: coalesce settings from ethtool
 * @queue: the queue to modअगरy
 *
 * Change the ITR settings क्रम a specअगरic queue.
 **/
अटल व्योम i40e_set_itr_per_queue(काष्ठा i40e_vsi *vsi,
				   काष्ठा ethtool_coalesce *ec,
				   पूर्णांक queue)
अणु
	काष्ठा i40e_ring *rx_ring = vsi->rx_rings[queue];
	काष्ठा i40e_ring *tx_ring = vsi->tx_rings[queue];
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा i40e_q_vector *q_vector;
	u16 पूर्णांकrl;

	पूर्णांकrl = i40e_पूर्णांकrl_usec_to_reg(vsi->पूर्णांक_rate_limit);

	rx_ring->itr_setting = ITR_REG_ALIGN(ec->rx_coalesce_usecs);
	tx_ring->itr_setting = ITR_REG_ALIGN(ec->tx_coalesce_usecs);

	अगर (ec->use_adaptive_rx_coalesce)
		rx_ring->itr_setting |= I40E_ITR_DYNAMIC;
	अन्यथा
		rx_ring->itr_setting &= ~I40E_ITR_DYNAMIC;

	अगर (ec->use_adaptive_tx_coalesce)
		tx_ring->itr_setting |= I40E_ITR_DYNAMIC;
	अन्यथा
		tx_ring->itr_setting &= ~I40E_ITR_DYNAMIC;

	q_vector = rx_ring->q_vector;
	q_vector->rx.target_itr = ITR_TO_REG(rx_ring->itr_setting);

	q_vector = tx_ring->q_vector;
	q_vector->tx.target_itr = ITR_TO_REG(tx_ring->itr_setting);

	/* The पूर्णांकerrupt handler itself will take care of programming
	 * the Tx and Rx ITR values based on the values we have entered
	 * पूर्णांकo the q_vector, no need to ग_लिखो the values now.
	 */

	wr32(hw, I40E_PFINT_RATEN(q_vector->reg_idx), पूर्णांकrl);
	i40e_flush(hw);
पूर्ण

/**
 * __i40e_set_coalesce - set coalesce settings क्रम particular queue
 * @netdev: the netdev to change
 * @ec: ethtool coalesce settings
 * @queue: the queue to change
 *
 * Sets the coalesce settings क्रम a particular queue.
 **/
अटल पूर्णांक __i40e_set_coalesce(काष्ठा net_device *netdev,
			       काष्ठा ethtool_coalesce *ec,
			       पूर्णांक queue)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	u16 पूर्णांकrl_reg, cur_rx_itr, cur_tx_itr;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक i;

	अगर (ec->tx_max_coalesced_frames_irq || ec->rx_max_coalesced_frames_irq)
		vsi->work_limit = ec->tx_max_coalesced_frames_irq;

	अगर (queue < 0) अणु
		cur_rx_itr = vsi->rx_rings[0]->itr_setting;
		cur_tx_itr = vsi->tx_rings[0]->itr_setting;
	पूर्ण अन्यथा अगर (queue < vsi->num_queue_pairs) अणु
		cur_rx_itr = vsi->rx_rings[queue]->itr_setting;
		cur_tx_itr = vsi->tx_rings[queue]->itr_setting;
	पूर्ण अन्यथा अणु
		netअगर_info(pf, drv, netdev, "Invalid queue value, queue range is 0 - %d\n",
			   vsi->num_queue_pairs - 1);
		वापस -EINVAL;
	पूर्ण

	cur_tx_itr &= ~I40E_ITR_DYNAMIC;
	cur_rx_itr &= ~I40E_ITR_DYNAMIC;

	/* tx_coalesce_usecs_high is ignored, use rx-usecs-high instead */
	अगर (ec->tx_coalesce_usecs_high != vsi->पूर्णांक_rate_limit) अणु
		netअगर_info(pf, drv, netdev, "tx-usecs-high is not used, please program rx-usecs-high\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ec->rx_coalesce_usecs_high > INTRL_REG_TO_USEC(I40E_MAX_INTRL)) अणु
		netअगर_info(pf, drv, netdev, "Invalid value, rx-usecs-high range is 0-%lu\n",
			   INTRL_REG_TO_USEC(I40E_MAX_INTRL));
		वापस -EINVAL;
	पूर्ण

	अगर (ec->rx_coalesce_usecs != cur_rx_itr &&
	    ec->use_adaptive_rx_coalesce) अणु
		netअगर_info(pf, drv, netdev, "RX interrupt moderation cannot be changed if adaptive-rx is enabled.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ec->rx_coalesce_usecs > I40E_MAX_ITR) अणु
		netअगर_info(pf, drv, netdev, "Invalid value, rx-usecs range is 0-8160\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ec->tx_coalesce_usecs != cur_tx_itr &&
	    ec->use_adaptive_tx_coalesce) अणु
		netअगर_info(pf, drv, netdev, "TX interrupt moderation cannot be changed if adaptive-tx is enabled.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ec->tx_coalesce_usecs > I40E_MAX_ITR) अणु
		netअगर_info(pf, drv, netdev, "Invalid value, tx-usecs range is 0-8160\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ec->use_adaptive_rx_coalesce && !cur_rx_itr)
		ec->rx_coalesce_usecs = I40E_MIN_ITR;

	अगर (ec->use_adaptive_tx_coalesce && !cur_tx_itr)
		ec->tx_coalesce_usecs = I40E_MIN_ITR;

	पूर्णांकrl_reg = i40e_पूर्णांकrl_usec_to_reg(ec->rx_coalesce_usecs_high);
	vsi->पूर्णांक_rate_limit = INTRL_REG_TO_USEC(पूर्णांकrl_reg);
	अगर (vsi->पूर्णांक_rate_limit != ec->rx_coalesce_usecs_high) अणु
		netअगर_info(pf, drv, netdev, "Interrupt rate limit rounded down to %d\n",
			   vsi->पूर्णांक_rate_limit);
	पूर्ण

	/* rx and tx usecs has per queue value. If user करोesn't specअगरy the
	 * queue, apply to all queues.
	 */
	अगर (queue < 0) अणु
		क्रम (i = 0; i < vsi->num_queue_pairs; i++)
			i40e_set_itr_per_queue(vsi, ec, i);
	पूर्ण अन्यथा अणु
		i40e_set_itr_per_queue(vsi, ec, queue);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_set_coalesce - set coalesce settings क्रम every queue on the netdev
 * @netdev: the netdev to change
 * @ec: ethtool coalesce settings
 *
 * This will set each queue to the same coalesce settings.
 **/
अटल पूर्णांक i40e_set_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	वापस __i40e_set_coalesce(netdev, ec, -1);
पूर्ण

/**
 * i40e_set_per_queue_coalesce - set specअगरic queue's coalesce settings
 * @netdev: the netdev to change
 * @ec: ethtool's coalesce settings
 * @queue: the queue to change
 *
 * Sets the specअगरied queue's coalesce settings.
 **/
अटल पूर्णांक i40e_set_per_queue_coalesce(काष्ठा net_device *netdev, u32 queue,
				       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __i40e_set_coalesce(netdev, ec, queue);
पूर्ण

/**
 * i40e_get_rss_hash_opts - Get RSS hash Input Set क्रम each flow type
 * @pf: poपूर्णांकer to the physical function काष्ठा
 * @cmd: ethtool rxnfc command
 *
 * Returns Success अगर the flow is supported, अन्यथा Invalid Input.
 **/
अटल पूर्णांक i40e_get_rss_hash_opts(काष्ठा i40e_pf *pf, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u8 flow_pctype = 0;
	u64 i_set = 0;

	cmd->data = 0;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_TCP;
		अवरोध;
	हाल UDP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_UDP;
		अवरोध;
	हाल TCP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_TCP;
		अवरोध;
	हाल UDP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_UDP;
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल IPV4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV6_FLOW:
		/* Default is src/dest क्रम IP, no matter the L4 hashing */
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Read flow based hash input set रेजिस्टर */
	अगर (flow_pctype) अणु
		i_set = (u64)i40e_पढ़ो_rx_ctl(hw, I40E_GLQF_HASH_INSET(0,
					      flow_pctype)) |
			((u64)i40e_पढ़ो_rx_ctl(hw, I40E_GLQF_HASH_INSET(1,
					       flow_pctype)) << 32);
	पूर्ण

	/* Process bits of hash input set */
	अगर (i_set) अणु
		अगर (i_set & I40E_L4_SRC_MASK)
			cmd->data |= RXH_L4_B_0_1;
		अगर (i_set & I40E_L4_DST_MASK)
			cmd->data |= RXH_L4_B_2_3;

		अगर (cmd->flow_type == TCP_V4_FLOW ||
		    cmd->flow_type == UDP_V4_FLOW) अणु
			अगर (i_set & I40E_L3_SRC_MASK)
				cmd->data |= RXH_IP_SRC;
			अगर (i_set & I40E_L3_DST_MASK)
				cmd->data |= RXH_IP_DST;
		पूर्ण अन्यथा अगर (cmd->flow_type == TCP_V6_FLOW ||
			  cmd->flow_type == UDP_V6_FLOW) अणु
			अगर (i_set & I40E_L3_V6_SRC_MASK)
				cmd->data |= RXH_IP_SRC;
			अगर (i_set & I40E_L3_V6_DST_MASK)
				cmd->data |= RXH_IP_DST;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_check_mask - Check whether a mask field is set
 * @mask: the full mask value
 * @field: mask of the field to check
 *
 * If the given mask is fully set, वापस positive value. If the mask क्रम the
 * field is fully unset, वापस zero. Otherwise वापस a negative error code.
 **/
अटल पूर्णांक i40e_check_mask(u64 mask, u64 field)
अणु
	u64 value = mask & field;

	अगर (value == field)
		वापस 1;
	अन्यथा अगर (!value)
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

/**
 * i40e_parse_rx_flow_user_data - Deस्थिरruct user-defined data
 * @fsp: poपूर्णांकer to rx flow specअगरication
 * @data: poपूर्णांकer to userdef data काष्ठाure क्रम storage
 *
 * Read the user-defined data and deस्थिरruct the value पूर्णांकo a काष्ठाure. No
 * other code should पढ़ो the user-defined data, so as to ensure that every
 * place consistently पढ़ोs the value correctly.
 *
 * The user-defined field is a 64bit Big Endian क्रमmat value, which we
 * deस्थिरruct by पढ़ोing bits or bit fields from it. Single bit flags shall
 * be defined starting from the highest bits, जबतक small bit field values
 * shall be defined starting from the lowest bits.
 *
 * Returns 0 अगर the data is valid, and non-zero अगर the userdef data is invalid
 * and the filter should be rejected. The data काष्ठाure will always be
 * modअगरied even अगर FLOW_EXT is not set.
 *
 **/
अटल पूर्णांक i40e_parse_rx_flow_user_data(काष्ठा ethtool_rx_flow_spec *fsp,
					काष्ठा i40e_rx_flow_userdef *data)
अणु
	u64 value, mask;
	पूर्णांक valid;

	/* Zero memory first so it's always consistent. */
	स_रखो(data, 0, माप(*data));

	अगर (!(fsp->flow_type & FLOW_EXT))
		वापस 0;

	value = be64_to_cpu(*((__be64 *)fsp->h_ext.data));
	mask = be64_to_cpu(*((__be64 *)fsp->m_ext.data));

#घोषणा I40E_USERDEF_FLEX_WORD		GENMASK_ULL(15, 0)
#घोषणा I40E_USERDEF_FLEX_OFFSET	GENMASK_ULL(31, 16)
#घोषणा I40E_USERDEF_FLEX_FILTER	GENMASK_ULL(31, 0)

	valid = i40e_check_mask(mask, I40E_USERDEF_FLEX_FILTER);
	अगर (valid < 0) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (valid) अणु
		data->flex_word = value & I40E_USERDEF_FLEX_WORD;
		data->flex_offset =
			(value & I40E_USERDEF_FLEX_OFFSET) >> 16;
		data->flex_filter = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_fill_rx_flow_user_data - Fill in user-defined data field
 * @fsp: poपूर्णांकer to rx_flow specअगरication
 * @data: poपूर्णांकer to वापस userdef data
 *
 * Reads the userdef data काष्ठाure and properly fills in the user defined
 * fields of the rx_flow_spec.
 **/
अटल व्योम i40e_fill_rx_flow_user_data(काष्ठा ethtool_rx_flow_spec *fsp,
					काष्ठा i40e_rx_flow_userdef *data)
अणु
	u64 value = 0, mask = 0;

	अगर (data->flex_filter) अणु
		value |= data->flex_word;
		value |= (u64)data->flex_offset << 16;
		mask |= I40E_USERDEF_FLEX_FILTER;
	पूर्ण

	अगर (value || mask)
		fsp->flow_type |= FLOW_EXT;

	*((__be64 *)fsp->h_ext.data) = cpu_to_be64(value);
	*((__be64 *)fsp->m_ext.data) = cpu_to_be64(mask);
पूर्ण

/**
 * i40e_get_ethtool_fdir_all - Populates the rule count of a command
 * @pf: Poपूर्णांकer to the physical function काष्ठा
 * @cmd: The command to get or set Rx flow classअगरication rules
 * @rule_locs: Array of used rule locations
 *
 * This function populates both the total and actual rule count of
 * the ethtool flow classअगरication command
 *
 * Returns 0 on success or -EMSGSIZE अगर entry not found
 **/
अटल पूर्णांक i40e_get_ethtool_fdir_all(काष्ठा i40e_pf *pf,
				     काष्ठा ethtool_rxnfc *cmd,
				     u32 *rule_locs)
अणु
	काष्ठा i40e_fdir_filter *rule;
	काष्ठा hlist_node *node2;
	पूर्णांक cnt = 0;

	/* report total rule count */
	cmd->data = i40e_get_fd_cnt_all(pf);

	hlist_क्रम_each_entry_safe(rule, node2,
				  &pf->fdir_filter_list, fdir_node) अणु
		अगर (cnt == cmd->rule_cnt)
			वापस -EMSGSIZE;

		rule_locs[cnt] = rule->fd_id;
		cnt++;
	पूर्ण

	cmd->rule_cnt = cnt;

	वापस 0;
पूर्ण

/**
 * i40e_get_ethtool_fdir_entry - Look up a filter based on Rx flow
 * @pf: Poपूर्णांकer to the physical function काष्ठा
 * @cmd: The command to get or set Rx flow classअगरication rules
 *
 * This function looks up a filter based on the Rx flow classअगरication
 * command and fills the flow spec info क्रम it अगर found
 *
 * Returns 0 on success or -EINVAL अगर filter not found
 **/
अटल पूर्णांक i40e_get_ethtool_fdir_entry(काष्ठा i40e_pf *pf,
				       काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
			(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा i40e_rx_flow_userdef userdef = अणु0पूर्ण;
	काष्ठा i40e_fdir_filter *rule = शून्य;
	काष्ठा hlist_node *node2;
	u64 input_set;
	u16 index;

	hlist_क्रम_each_entry_safe(rule, node2,
				  &pf->fdir_filter_list, fdir_node) अणु
		अगर (fsp->location <= rule->fd_id)
			अवरोध;
	पूर्ण

	अगर (!rule || fsp->location != rule->fd_id)
		वापस -EINVAL;

	fsp->flow_type = rule->flow_type;
	अगर (fsp->flow_type == IP_USER_FLOW) अणु
		fsp->h_u.usr_ip4_spec.ip_ver = ETH_RX_NFC_IP4;
		fsp->h_u.usr_ip4_spec.proto = 0;
		fsp->m_u.usr_ip4_spec.proto = 0;
	पूर्ण

	अगर (fsp->flow_type == IPV6_USER_FLOW ||
	    fsp->flow_type == UDP_V6_FLOW ||
	    fsp->flow_type == TCP_V6_FLOW ||
	    fsp->flow_type == SCTP_V6_FLOW) अणु
		/* Reverse the src and dest notion, since the HW views them
		 * from Tx perspective where as the user expects it from
		 * Rx filter view.
		 */
		fsp->h_u.tcp_ip6_spec.psrc = rule->dst_port;
		fsp->h_u.tcp_ip6_spec.pdst = rule->src_port;
		स_नकल(fsp->h_u.tcp_ip6_spec.ip6dst, rule->src_ip6,
		       माप(__be32) * 4);
		स_नकल(fsp->h_u.tcp_ip6_spec.ip6src, rule->dst_ip6,
		       माप(__be32) * 4);
	पूर्ण अन्यथा अणु
		/* Reverse the src and dest notion, since the HW views them
		 * from Tx perspective where as the user expects it from
		 * Rx filter view.
		 */
		fsp->h_u.tcp_ip4_spec.psrc = rule->dst_port;
		fsp->h_u.tcp_ip4_spec.pdst = rule->src_port;
		fsp->h_u.tcp_ip4_spec.ip4src = rule->dst_ip;
		fsp->h_u.tcp_ip4_spec.ip4dst = rule->src_ip;
	पूर्ण

	चयन (rule->flow_type) अणु
	हाल SCTP_V4_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_SCTP;
		अवरोध;
	हाल TCP_V4_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_TCP;
		अवरोध;
	हाल UDP_V4_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_UDP;
		अवरोध;
	हाल SCTP_V6_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_SCTP;
		अवरोध;
	हाल TCP_V6_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_TCP;
		अवरोध;
	हाल UDP_V6_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_UDP;
		अवरोध;
	हाल IP_USER_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_OTHER;
		अवरोध;
	हाल IPV6_USER_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_OTHER;
		अवरोध;
	शेष:
		/* If we have stored a filter with a flow type not listed here
		 * it is almost certainly a driver bug. WARN(), and then
		 * assign the input_set as अगर all fields are enabled to aव्योम
		 * पढ़ोing unasचिन्हित memory.
		 */
		WARN(1, "Missing input set index for flow_type %d\n",
		     rule->flow_type);
		input_set = 0xFFFFFFFFFFFFFFFFULL;
		जाओ no_input_set;
	पूर्ण

	input_set = i40e_पढ़ो_fd_input_set(pf, index);

no_input_set:
	अगर (input_set & I40E_L3_V6_SRC_MASK) अणु
		fsp->m_u.tcp_ip6_spec.ip6src[0] = htonl(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6src[1] = htonl(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6src[2] = htonl(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6src[3] = htonl(0xFFFFFFFF);
	पूर्ण

	अगर (input_set & I40E_L3_V6_DST_MASK) अणु
		fsp->m_u.tcp_ip6_spec.ip6dst[0] = htonl(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6dst[1] = htonl(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6dst[2] = htonl(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6dst[3] = htonl(0xFFFFFFFF);
	पूर्ण

	अगर (input_set & I40E_L3_SRC_MASK)
		fsp->m_u.tcp_ip4_spec.ip4src = htonl(0xFFFFFFFF);

	अगर (input_set & I40E_L3_DST_MASK)
		fsp->m_u.tcp_ip4_spec.ip4dst = htonl(0xFFFFFFFF);

	अगर (input_set & I40E_L4_SRC_MASK)
		fsp->m_u.tcp_ip4_spec.psrc = htons(0xFFFF);

	अगर (input_set & I40E_L4_DST_MASK)
		fsp->m_u.tcp_ip4_spec.pdst = htons(0xFFFF);

	अगर (rule->dest_ctl == I40E_FILTER_PROGRAM_DESC_DEST_DROP_PACKET)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		fsp->ring_cookie = rule->q_index;

	अगर (rule->vlan_tag) अणु
		fsp->h_ext.vlan_etype = rule->vlan_etype;
		fsp->m_ext.vlan_etype = htons(0xFFFF);
		fsp->h_ext.vlan_tci = rule->vlan_tag;
		fsp->m_ext.vlan_tci = htons(0xFFFF);
		fsp->flow_type |= FLOW_EXT;
	पूर्ण

	अगर (rule->dest_vsi != pf->vsi[pf->lan_vsi]->id) अणु
		काष्ठा i40e_vsi *vsi;

		vsi = i40e_find_vsi_from_id(pf, rule->dest_vsi);
		अगर (vsi && vsi->type == I40E_VSI_SRIOV) अणु
			/* VFs are zero-indexed by the driver, but ethtool
			 * expects them to be one-indexed, so add one here
			 */
			u64 ring_vf = vsi->vf_id + 1;

			ring_vf <<= ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF;
			fsp->ring_cookie |= ring_vf;
		पूर्ण
	पूर्ण

	अगर (rule->flex_filter) अणु
		userdef.flex_filter = true;
		userdef.flex_word = be16_to_cpu(rule->flex_word);
		userdef.flex_offset = rule->flex_offset;
	पूर्ण

	i40e_fill_rx_flow_user_data(fsp, &userdef);

	वापस 0;
पूर्ण

/**
 * i40e_get_rxnfc - command to get RX flow classअगरication rules
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool rxnfc command
 * @rule_locs: poपूर्णांकer to store rule data
 *
 * Returns Success अगर the command is supported.
 **/
अटल पूर्णांक i40e_get_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd,
			  u32 *rule_locs)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = vsi->rss_size;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ret = i40e_get_rss_hash_opts(pf, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = pf->fdir_pf_active_filters;
		/* report total rule count */
		cmd->data = i40e_get_fd_cnt_all(pf);
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = i40e_get_ethtool_fdir_entry(pf, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = i40e_get_ethtool_fdir_all(pf, cmd, rule_locs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_get_rss_hash_bits - Read RSS Hash bits from रेजिस्टर
 * @nfc: poपूर्णांकer to user request
 * @i_setc: bits currently set
 *
 * Returns value of bits to be set per user request
 **/
अटल u64 i40e_get_rss_hash_bits(काष्ठा ethtool_rxnfc *nfc, u64 i_setc)
अणु
	u64 i_set = i_setc;
	u64 src_l3 = 0, dst_l3 = 0;

	अगर (nfc->data & RXH_L4_B_0_1)
		i_set |= I40E_L4_SRC_MASK;
	अन्यथा
		i_set &= ~I40E_L4_SRC_MASK;
	अगर (nfc->data & RXH_L4_B_2_3)
		i_set |= I40E_L4_DST_MASK;
	अन्यथा
		i_set &= ~I40E_L4_DST_MASK;

	अगर (nfc->flow_type == TCP_V6_FLOW || nfc->flow_type == UDP_V6_FLOW) अणु
		src_l3 = I40E_L3_V6_SRC_MASK;
		dst_l3 = I40E_L3_V6_DST_MASK;
	पूर्ण अन्यथा अगर (nfc->flow_type == TCP_V4_FLOW ||
		  nfc->flow_type == UDP_V4_FLOW) अणु
		src_l3 = I40E_L3_SRC_MASK;
		dst_l3 = I40E_L3_DST_MASK;
	पूर्ण अन्यथा अणु
		/* Any other flow type are not supported here */
		वापस i_set;
	पूर्ण

	अगर (nfc->data & RXH_IP_SRC)
		i_set |= src_l3;
	अन्यथा
		i_set &= ~src_l3;
	अगर (nfc->data & RXH_IP_DST)
		i_set |= dst_l3;
	अन्यथा
		i_set &= ~dst_l3;

	वापस i_set;
पूर्ण

/**
 * i40e_set_rss_hash_opt - Enable/Disable flow types क्रम RSS hash
 * @pf: poपूर्णांकer to the physical function काष्ठा
 * @nfc: ethtool rxnfc command
 *
 * Returns Success अगर the flow input set is supported.
 **/
अटल पूर्णांक i40e_set_rss_hash_opt(काष्ठा i40e_pf *pf, काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u64 hena = (u64)i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_HENA(0)) |
		   ((u64)i40e_पढ़ो_rx_ctl(hw, I40E_PFQF_HENA(1)) << 32);
	u8 flow_pctype = 0;
	u64 i_set, i_setc;

	अगर (pf->flags & I40E_FLAG_MFP_ENABLED) अणु
		dev_err(&pf->pdev->dev,
			"Change of RSS hash input set is not supported when MFP mode is enabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* RSS करोes not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	अगर (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_TCP;
		अगर (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK);
		अवरोध;
	हाल TCP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_TCP;
		अगर (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK);
		अगर (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK);
		अवरोध;
	हाल UDP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_UDP;
		अगर (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_UNICAST_IPV4_UDP) |
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV4_UDP);

		hena |= BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV4);
		अवरोध;
	हाल UDP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_UDP;
		अगर (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_UNICAST_IPV6_UDP) |
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV6_UDP);

		hena |= BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV6);
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		अगर ((nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_OTHER);
		अवरोध;
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		अगर ((nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_OTHER);
		अवरोध;
	हाल IPV4_FLOW:
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_OTHER) |
			BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV4);
		अवरोध;
	हाल IPV6_FLOW:
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_OTHER) |
			BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV6);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (flow_pctype) अणु
		i_setc = (u64)i40e_पढ़ो_rx_ctl(hw, I40E_GLQF_HASH_INSET(0,
					       flow_pctype)) |
			((u64)i40e_पढ़ो_rx_ctl(hw, I40E_GLQF_HASH_INSET(1,
					       flow_pctype)) << 32);
		i_set = i40e_get_rss_hash_bits(nfc, i_setc);
		i40e_ग_लिखो_rx_ctl(hw, I40E_GLQF_HASH_INSET(0, flow_pctype),
				  (u32)i_set);
		i40e_ग_लिखो_rx_ctl(hw, I40E_GLQF_HASH_INSET(1, flow_pctype),
				  (u32)(i_set >> 32));
		hena |= BIT_ULL(flow_pctype);
	पूर्ण

	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_HENA(0), (u32)hena);
	i40e_ग_लिखो_rx_ctl(hw, I40E_PFQF_HENA(1), (u32)(hena >> 32));
	i40e_flush(hw);

	वापस 0;
पूर्ण

/**
 * i40e_update_ethtool_fdir_entry - Updates the fdir filter entry
 * @vsi: Poपूर्णांकer to the targeted VSI
 * @input: The filter to update or शून्य to indicate deletion
 * @sw_idx: Software index to the filter
 * @cmd: The command to get or set Rx flow classअगरication rules
 *
 * This function updates (or deletes) a Flow Director entry from
 * the hlist of the corresponding PF
 *
 * Returns 0 on success
 **/
अटल पूर्णांक i40e_update_ethtool_fdir_entry(काष्ठा i40e_vsi *vsi,
					  काष्ठा i40e_fdir_filter *input,
					  u16 sw_idx,
					  काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा i40e_fdir_filter *rule, *parent;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा hlist_node *node2;
	पूर्णांक err = -EINVAL;

	parent = शून्य;
	rule = शून्य;

	hlist_क्रम_each_entry_safe(rule, node2,
				  &pf->fdir_filter_list, fdir_node) अणु
		/* hash found, or no matching entry */
		अगर (rule->fd_id >= sw_idx)
			अवरोध;
		parent = rule;
	पूर्ण

	/* अगर there is an old rule occupying our place हटाओ it */
	अगर (rule && (rule->fd_id == sw_idx)) अणु
		/* Remove this rule, since we're either deleting it, or
		 * replacing it.
		 */
		err = i40e_add_del_fdir(vsi, rule, false);
		hlist_del(&rule->fdir_node);
		kमुक्त(rule);
		pf->fdir_pf_active_filters--;
	पूर्ण

	/* If we weren't given an input, this is a delete, so just वापस the
	 * error code indicating अगर there was an entry at the requested slot
	 */
	अगर (!input)
		वापस err;

	/* Otherwise, install the new rule as requested */
	INIT_HLIST_NODE(&input->fdir_node);

	/* add filter to the list */
	अगर (parent)
		hlist_add_behind(&input->fdir_node, &parent->fdir_node);
	अन्यथा
		hlist_add_head(&input->fdir_node,
			       &pf->fdir_filter_list);

	/* update counts */
	pf->fdir_pf_active_filters++;

	वापस 0;
पूर्ण

/**
 * i40e_prune_flex_pit_list - Cleanup unused entries in FLX_PIT table
 * @pf: poपूर्णांकer to PF काष्ठाure
 *
 * This function searches the list of filters and determines which FLX_PIT
 * entries are still required. It will prune any entries which are no दीर्घer
 * in use after the deletion.
 **/
अटल व्योम i40e_prune_flex_pit_list(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_flex_pit *entry, *पंचांगp;
	काष्ठा i40e_fdir_filter *rule;

	/* First, we'll check the l3 table */
	list_क्रम_each_entry_safe(entry, पंचांगp, &pf->l3_flex_pit_list, list) अणु
		bool found = false;

		hlist_क्रम_each_entry(rule, &pf->fdir_filter_list, fdir_node) अणु
			अगर (rule->flow_type != IP_USER_FLOW)
				जारी;
			अगर (rule->flex_filter &&
			    rule->flex_offset == entry->src_offset) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		/* If we didn't find the filter, then we can prune this entry
		 * from the list.
		 */
		अगर (!found) अणु
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
	पूर्ण

	/* Followed by the L4 table */
	list_क्रम_each_entry_safe(entry, पंचांगp, &pf->l4_flex_pit_list, list) अणु
		bool found = false;

		hlist_क्रम_each_entry(rule, &pf->fdir_filter_list, fdir_node) अणु
			/* Skip this filter अगर it's L3, since we alपढ़ोy
			 * checked those in the above loop
			 */
			अगर (rule->flow_type == IP_USER_FLOW)
				जारी;
			अगर (rule->flex_filter &&
			    rule->flex_offset == entry->src_offset) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		/* If we didn't find the filter, then we can prune this entry
		 * from the list.
		 */
		अगर (!found) अणु
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_del_fdir_entry - Deletes a Flow Director filter entry
 * @vsi: Poपूर्णांकer to the targeted VSI
 * @cmd: The command to get or set Rx flow classअगरication rules
 *
 * The function हटाओs a Flow Director filter entry from the
 * hlist of the corresponding PF
 *
 * Returns 0 on success
 */
अटल पूर्णांक i40e_del_fdir_entry(काष्ठा i40e_vsi *vsi,
			       काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret = 0;

	अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
	    test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		वापस -EBUSY;

	अगर (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		वापस -EBUSY;

	ret = i40e_update_ethtool_fdir_entry(vsi, शून्य, fsp->location, cmd);

	i40e_prune_flex_pit_list(pf);

	i40e_fdir_check_and_reenable(pf);
	वापस ret;
पूर्ण

/**
 * i40e_unused_pit_index - Find an unused PIT index क्रम given list
 * @pf: the PF data काष्ठाure
 *
 * Find the first unused flexible PIT index entry. We search both the L3 and
 * L4 flexible PIT lists so that the वापसed index is unique and unused by
 * either currently programmed L3 or L4 filters. We use a bit field as storage
 * to track which indexes are alपढ़ोy used.
 **/
अटल u8 i40e_unused_pit_index(काष्ठा i40e_pf *pf)
अणु
	अचिन्हित दीर्घ available_index = 0xFF;
	काष्ठा i40e_flex_pit *entry;

	/* We need to make sure that the new index isn't in use by either L3
	 * or L4 filters so that IP_USER_FLOW filters can program both L3 and
	 * L4 to use the same index.
	 */

	list_क्रम_each_entry(entry, &pf->l4_flex_pit_list, list)
		clear_bit(entry->pit_index, &available_index);

	list_क्रम_each_entry(entry, &pf->l3_flex_pit_list, list)
		clear_bit(entry->pit_index, &available_index);

	वापस find_first_bit(&available_index, 8);
पूर्ण

/**
 * i40e_find_flex_offset - Find an existing flex src_offset
 * @flex_pit_list: L3 or L4 flex PIT list
 * @src_offset: new src_offset to find
 *
 * Searches the flex_pit_list क्रम an existing offset. If no offset is
 * currently programmed, then this will वापस an ERR_PTR अगर there is no space
 * to add a new offset, otherwise it वापसs शून्य.
 **/
अटल
काष्ठा i40e_flex_pit *i40e_find_flex_offset(काष्ठा list_head *flex_pit_list,
					    u16 src_offset)
अणु
	काष्ठा i40e_flex_pit *entry;
	पूर्णांक size = 0;

	/* Search क्रम the src_offset first. If we find a matching entry
	 * alपढ़ोy programmed, we can simply re-use it.
	 */
	list_क्रम_each_entry(entry, flex_pit_list, list) अणु
		size++;
		अगर (entry->src_offset == src_offset)
			वापस entry;
	पूर्ण

	/* If we haven't found an entry yet, then the provided src offset has
	 * not yet been programmed. We will program the src offset later on,
	 * but we need to indicate whether there is enough space to करो so
	 * here. We'll make use of ERR_PTR क्रम this purpose.
	 */
	अगर (size >= I40E_FLEX_PIT_TABLE_SIZE)
		वापस ERR_PTR(-ENOSPC);

	वापस शून्य;
पूर्ण

/**
 * i40e_add_flex_offset - Add src_offset to flex PIT table list
 * @flex_pit_list: L3 or L4 flex PIT list
 * @src_offset: new src_offset to add
 * @pit_index: the PIT index to program
 *
 * This function programs the new src_offset to the list. It is expected that
 * i40e_find_flex_offset has alपढ़ोy been tried and वापसed शून्य, indicating
 * that this offset is not programmed, and that the list has enough space to
 * store another offset.
 *
 * Returns 0 on success, and negative value on error.
 **/
अटल पूर्णांक i40e_add_flex_offset(काष्ठा list_head *flex_pit_list,
				u16 src_offset,
				u8 pit_index)
अणु
	काष्ठा i40e_flex_pit *new_pit, *entry;

	new_pit = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!new_pit)
		वापस -ENOMEM;

	new_pit->src_offset = src_offset;
	new_pit->pit_index = pit_index;

	/* We need to insert this item such that the list is sorted by
	 * src_offset in ascending order.
	 */
	list_क्रम_each_entry(entry, flex_pit_list, list) अणु
		अगर (new_pit->src_offset < entry->src_offset) अणु
			list_add_tail(&new_pit->list, &entry->list);
			वापस 0;
		पूर्ण

		/* If we found an entry with our offset alपढ़ोy programmed we
		 * can simply वापस here, after मुक्तing the memory. However,
		 * अगर the pit_index करोes not match we need to report an error.
		 */
		अगर (new_pit->src_offset == entry->src_offset) अणु
			पूर्णांक err = 0;

			/* If the PIT index is not the same we can't re-use
			 * the entry, so we must report an error.
			 */
			अगर (new_pit->pit_index != entry->pit_index)
				err = -EINVAL;

			kमुक्त(new_pit);
			वापस err;
		पूर्ण
	पूर्ण

	/* If we reached here, then we haven't yet added the item. This means
	 * that we should add the item at the end of the list.
	 */
	list_add_tail(&new_pit->list, flex_pit_list);
	वापस 0;
पूर्ण

/**
 * __i40e_reprogram_flex_pit - Re-program specअगरic FLX_PIT table
 * @pf: Poपूर्णांकer to the PF काष्ठाure
 * @flex_pit_list: list of flexible src offsets in use
 * @flex_pit_start: index to first entry क्रम this section of the table
 *
 * In order to handle flexible data, the hardware uses a table of values
 * called the FLX_PIT table. This table is used to indicate which sections of
 * the input correspond to what PIT index values. Unक्रमtunately, hardware is
 * very restrictive about programming this table. Entries must be ordered by
 * src_offset in ascending order, without duplicates. Additionally, unused
 * entries must be set to the unused index value, and must have valid size and
 * length according to the src_offset ordering.
 *
 * This function will reprogram the FLX_PIT रेजिस्टर from a book-keeping
 * काष्ठाure that we guarantee is alपढ़ोy ordered correctly, and has no more
 * than 3 entries.
 *
 * To make things easier, we only support flexible values of one word length,
 * rather than allowing variable length flexible values.
 **/
अटल व्योम __i40e_reprogram_flex_pit(काष्ठा i40e_pf *pf,
				      काष्ठा list_head *flex_pit_list,
				      पूर्णांक flex_pit_start)
अणु
	काष्ठा i40e_flex_pit *entry = शून्य;
	u16 last_offset = 0;
	पूर्णांक i = 0, j = 0;

	/* First, loop over the list of flex PIT entries, and reprogram the
	 * रेजिस्टरs.
	 */
	list_क्रम_each_entry(entry, flex_pit_list, list) अणु
		/* We have to be careful when programming values क्रम the
		 * largest SRC_OFFSET value. It is possible that adding
		 * additional empty values at the end would overflow the space
		 * क्रम the SRC_OFFSET in the FLX_PIT रेजिस्टर. To aव्योम this,
		 * we check here and add the empty values prior to adding the
		 * largest value.
		 *
		 * To determine this, we will use a loop from i+1 to 3, which
		 * will determine whether the unused entries would have valid
		 * SRC_OFFSET. Note that there cannot be extra entries past
		 * this value, because the only valid values would have been
		 * larger than I40E_MAX_FLEX_SRC_OFFSET, and thus would not
		 * have been added to the list in the first place.
		 */
		क्रम (j = i + 1; j < 3; j++) अणु
			u16 offset = entry->src_offset + j;
			पूर्णांक index = flex_pit_start + i;
			u32 value = I40E_FLEX_PREP_VAL(I40E_FLEX_DEST_UNUSED,
						       1,
						       offset - 3);

			अगर (offset > I40E_MAX_FLEX_SRC_OFFSET) अणु
				i40e_ग_लिखो_rx_ctl(&pf->hw,
						  I40E_PRTQF_FLX_PIT(index),
						  value);
				i++;
			पूर्ण
		पूर्ण

		/* Now, we can program the actual value पूर्णांकo the table */
		i40e_ग_लिखो_rx_ctl(&pf->hw,
				  I40E_PRTQF_FLX_PIT(flex_pit_start + i),
				  I40E_FLEX_PREP_VAL(entry->pit_index + 50,
						     1,
						     entry->src_offset));
		i++;
	पूर्ण

	/* In order to program the last entries in the table, we need to
	 * determine the valid offset. If the list is empty, we'll just start
	 * with 0. Otherwise, we'll start with the last item offset and add 1.
	 * This ensures that all entries have valid sizes. If we करोn't करो this
	 * correctly, the hardware will disable flexible field parsing.
	 */
	अगर (!list_empty(flex_pit_list))
		last_offset = list_prev_entry(entry, list)->src_offset + 1;

	क्रम (; i < 3; i++, last_offset++) अणु
		i40e_ग_लिखो_rx_ctl(&pf->hw,
				  I40E_PRTQF_FLX_PIT(flex_pit_start + i),
				  I40E_FLEX_PREP_VAL(I40E_FLEX_DEST_UNUSED,
						     1,
						     last_offset));
	पूर्ण
पूर्ण

/**
 * i40e_reprogram_flex_pit - Reprogram all FLX_PIT tables after input set change
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * This function reprograms both the L3 and L4 FLX_PIT tables. See the
 * पूर्णांकernal helper function क्रम implementation details.
 **/
अटल व्योम i40e_reprogram_flex_pit(काष्ठा i40e_pf *pf)
अणु
	__i40e_reprogram_flex_pit(pf, &pf->l3_flex_pit_list,
				  I40E_FLEX_PIT_IDX_START_L3);

	__i40e_reprogram_flex_pit(pf, &pf->l4_flex_pit_list,
				  I40E_FLEX_PIT_IDX_START_L4);

	/* We also need to program the L3 and L4 GLQF ORT रेजिस्टर */
	i40e_ग_लिखो_rx_ctl(&pf->hw,
			  I40E_GLQF_ORT(I40E_L3_GLQF_ORT_IDX),
			  I40E_ORT_PREP_VAL(I40E_FLEX_PIT_IDX_START_L3,
					    3, 1));

	i40e_ग_लिखो_rx_ctl(&pf->hw,
			  I40E_GLQF_ORT(I40E_L4_GLQF_ORT_IDX),
			  I40E_ORT_PREP_VAL(I40E_FLEX_PIT_IDX_START_L4,
					    3, 1));
पूर्ण

/**
 * i40e_flow_str - Converts a flow_type पूर्णांकo a human पढ़ोable string
 * @fsp: the flow specअगरication
 *
 * Currently only flow types we support are included here, and the string
 * value attempts to match what ethtool would use to configure this flow type.
 **/
अटल स्थिर अक्षर *i40e_flow_str(काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	चयन (fsp->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
		वापस "tcp4";
	हाल UDP_V4_FLOW:
		वापस "udp4";
	हाल SCTP_V4_FLOW:
		वापस "sctp4";
	हाल IP_USER_FLOW:
		वापस "ip4";
	हाल TCP_V6_FLOW:
		वापस "tcp6";
	हाल UDP_V6_FLOW:
		वापस "udp6";
	हाल SCTP_V6_FLOW:
		वापस "sctp6";
	हाल IPV6_USER_FLOW:
		वापस "ip6";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/**
 * i40e_pit_index_to_mask - Return the FLEX mask क्रम a given PIT index
 * @pit_index: PIT index to convert
 *
 * Returns the mask क्रम a given PIT index. Will वापस 0 अगर the pit_index is
 * of range.
 **/
अटल u64 i40e_pit_index_to_mask(पूर्णांक pit_index)
अणु
	चयन (pit_index) अणु
	हाल 0:
		वापस I40E_FLEX_50_MASK;
	हाल 1:
		वापस I40E_FLEX_51_MASK;
	हाल 2:
		वापस I40E_FLEX_52_MASK;
	हाल 3:
		वापस I40E_FLEX_53_MASK;
	हाल 4:
		वापस I40E_FLEX_54_MASK;
	हाल 5:
		वापस I40E_FLEX_55_MASK;
	हाल 6:
		वापस I40E_FLEX_56_MASK;
	हाल 7:
		वापस I40E_FLEX_57_MASK;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * i40e_prपूर्णांक_input_set - Show changes between two input sets
 * @vsi: the vsi being configured
 * @old: the old input set
 * @new: the new input set
 *
 * Prपूर्णांक the dअगरference between old and new input sets by showing which series
 * of words are toggled on or off. Only displays the bits we actually support
 * changing.
 **/
अटल व्योम i40e_prपूर्णांक_input_set(काष्ठा i40e_vsi *vsi, u64 old, u64 new)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	bool old_value, new_value;
	पूर्णांक i;

	old_value = !!(old & I40E_L3_SRC_MASK);
	new_value = !!(new & I40E_L3_SRC_MASK);
	अगर (old_value != new_value)
		netअगर_info(pf, drv, vsi->netdev, "L3 source address: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_L3_DST_MASK);
	new_value = !!(new & I40E_L3_DST_MASK);
	अगर (old_value != new_value)
		netअगर_info(pf, drv, vsi->netdev, "L3 destination address: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_L4_SRC_MASK);
	new_value = !!(new & I40E_L4_SRC_MASK);
	अगर (old_value != new_value)
		netअगर_info(pf, drv, vsi->netdev, "L4 source port: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_L4_DST_MASK);
	new_value = !!(new & I40E_L4_DST_MASK);
	अगर (old_value != new_value)
		netअगर_info(pf, drv, vsi->netdev, "L4 destination port: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	old_value = !!(old & I40E_VERIFY_TAG_MASK);
	new_value = !!(new & I40E_VERIFY_TAG_MASK);
	अगर (old_value != new_value)
		netअगर_info(pf, drv, vsi->netdev, "SCTP verification tag: %s -> %s\n",
			   old_value ? "ON" : "OFF",
			   new_value ? "ON" : "OFF");

	/* Show change of flexible filter entries */
	क्रम (i = 0; i < I40E_FLEX_INDEX_ENTRIES; i++) अणु
		u64 flex_mask = i40e_pit_index_to_mask(i);

		old_value = !!(old & flex_mask);
		new_value = !!(new & flex_mask);
		अगर (old_value != new_value)
			netअगर_info(pf, drv, vsi->netdev, "FLEX index %d: %s -> %s\n",
				   i,
				   old_value ? "ON" : "OFF",
				   new_value ? "ON" : "OFF");
	पूर्ण

	netअगर_info(pf, drv, vsi->netdev, "  Current input set: %0llx\n",
		   old);
	netअगर_info(pf, drv, vsi->netdev, "Requested input set: %0llx\n",
		   new);
पूर्ण

/**
 * i40e_check_fdir_input_set - Check that a given rx_flow_spec mask is valid
 * @vsi: poपूर्णांकer to the targeted VSI
 * @fsp: poपूर्णांकer to Rx flow specअगरication
 * @userdef: userdefined data from flow specअगरication
 *
 * Ensures that a given ethtool_rx_flow_spec has a valid mask. Some support
 * क्रम partial matches exists with a few limitations. First, hardware only
 * supports masking by word boundary (2 bytes) and not per inभागidual bit.
 * Second, hardware is limited to using one mask क्रम a flow type and cannot
 * use a separate mask क्रम each filter.
 *
 * To support these limitations, अगर we alपढ़ोy have a configured filter क्रम
 * the specअगरied type, this function enक्रमces that new filters of the type
 * match the configured input set. Otherwise, अगर we करो not have a filter of
 * the specअगरied type, we allow the input set to be updated to match the
 * desired filter.
 *
 * To help ensure that administrators understand why filters weren't displayed
 * as supported, we prपूर्णांक a diagnostic message displaying how the input set
 * would change and warning to delete the preexisting filters अगर required.
 *
 * Returns 0 on successful input set match, and a negative वापस code on
 * failure.
 **/
अटल पूर्णांक i40e_check_fdir_input_set(काष्ठा i40e_vsi *vsi,
				     काष्ठा ethtool_rx_flow_spec *fsp,
				     काष्ठा i40e_rx_flow_userdef *userdef)
अणु
	अटल स्थिर __be32 ipv6_full_mask[4] = अणुcpu_to_be32(0xffffffff),
		cpu_to_be32(0xffffffff), cpu_to_be32(0xffffffff),
		cpu_to_be32(0xffffffff)पूर्ण;
	काष्ठा ethtool_tcpip6_spec *tcp_ip6_spec;
	काष्ठा ethtool_usrip6_spec *usr_ip6_spec;
	काष्ठा ethtool_tcpip4_spec *tcp_ip4_spec;
	काष्ठा ethtool_usrip4_spec *usr_ip4_spec;
	काष्ठा i40e_pf *pf = vsi->back;
	u64 current_mask, new_mask;
	bool new_flex_offset = false;
	bool flex_l3 = false;
	u16 *fdir_filter_count;
	u16 index, src_offset = 0;
	u8 pit_index = 0;
	पूर्णांक err;

	चयन (fsp->flow_type & ~FLOW_EXT) अणु
	हाल SCTP_V4_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_SCTP;
		fdir_filter_count = &pf->fd_sctp4_filter_cnt;
		अवरोध;
	हाल TCP_V4_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_TCP;
		fdir_filter_count = &pf->fd_tcp4_filter_cnt;
		अवरोध;
	हाल UDP_V4_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_UDP;
		fdir_filter_count = &pf->fd_udp4_filter_cnt;
		अवरोध;
	हाल SCTP_V6_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_SCTP;
		fdir_filter_count = &pf->fd_sctp6_filter_cnt;
		अवरोध;
	हाल TCP_V6_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_TCP;
		fdir_filter_count = &pf->fd_tcp6_filter_cnt;
		अवरोध;
	हाल UDP_V6_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_UDP;
		fdir_filter_count = &pf->fd_udp6_filter_cnt;
		अवरोध;
	हाल IP_USER_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV4_OTHER;
		fdir_filter_count = &pf->fd_ip4_filter_cnt;
		flex_l3 = true;
		अवरोध;
	हाल IPV6_USER_FLOW:
		index = I40E_FILTER_PCTYPE_NONF_IPV6_OTHER;
		fdir_filter_count = &pf->fd_ip6_filter_cnt;
		flex_l3 = true;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Read the current input set from रेजिस्टर memory. */
	current_mask = i40e_पढ़ो_fd_input_set(pf, index);
	new_mask = current_mask;

	/* Determine, अगर any, the required changes to the input set in order
	 * to support the provided mask.
	 *
	 * Hardware only supports masking at word (2 byte) granularity and करोes
	 * not support full bitwise masking. This implementation simplअगरies
	 * even further and only supports fully enabled or fully disabled
	 * masks क्रम each field, even though we could split the ip4src and
	 * ip4dst fields.
	 */
	चयन (fsp->flow_type & ~FLOW_EXT) अणु
	हाल SCTP_V4_FLOW:
		new_mask &= ~I40E_VERIFY_TAG_MASK;
		fallthrough;
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		tcp_ip4_spec = &fsp->m_u.tcp_ip4_spec;

		/* IPv4 source address */
		अगर (tcp_ip4_spec->ip4src == htonl(0xFFFFFFFF))
			new_mask |= I40E_L3_SRC_MASK;
		अन्यथा अगर (!tcp_ip4_spec->ip4src)
			new_mask &= ~I40E_L3_SRC_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* IPv4 destination address */
		अगर (tcp_ip4_spec->ip4dst == htonl(0xFFFFFFFF))
			new_mask |= I40E_L3_DST_MASK;
		अन्यथा अगर (!tcp_ip4_spec->ip4dst)
			new_mask &= ~I40E_L3_DST_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* L4 source port */
		अगर (tcp_ip4_spec->psrc == htons(0xFFFF))
			new_mask |= I40E_L4_SRC_MASK;
		अन्यथा अगर (!tcp_ip4_spec->psrc)
			new_mask &= ~I40E_L4_SRC_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* L4 destination port */
		अगर (tcp_ip4_spec->pdst == htons(0xFFFF))
			new_mask |= I40E_L4_DST_MASK;
		अन्यथा अगर (!tcp_ip4_spec->pdst)
			new_mask &= ~I40E_L4_DST_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* Filtering on Type of Service is not supported. */
		अगर (tcp_ip4_spec->tos)
			वापस -EOPNOTSUPP;

		अवरोध;
	हाल SCTP_V6_FLOW:
		new_mask &= ~I40E_VERIFY_TAG_MASK;
		fallthrough;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		tcp_ip6_spec = &fsp->m_u.tcp_ip6_spec;

		/* Check अगर user provided IPv6 source address. */
		अगर (ipv6_addr_equal((काष्ठा in6_addr *)&tcp_ip6_spec->ip6src,
				    (काष्ठा in6_addr *)&ipv6_full_mask))
			new_mask |= I40E_L3_V6_SRC_MASK;
		अन्यथा अगर (ipv6_addr_any((काष्ठा in6_addr *)
				       &tcp_ip6_spec->ip6src))
			new_mask &= ~I40E_L3_V6_SRC_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* Check अगर user provided destination address. */
		अगर (ipv6_addr_equal((काष्ठा in6_addr *)&tcp_ip6_spec->ip6dst,
				    (काष्ठा in6_addr *)&ipv6_full_mask))
			new_mask |= I40E_L3_V6_DST_MASK;
		अन्यथा अगर (ipv6_addr_any((काष्ठा in6_addr *)
				       &tcp_ip6_spec->ip6dst))
			new_mask &= ~I40E_L3_V6_DST_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* L4 source port */
		अगर (tcp_ip6_spec->psrc == htons(0xFFFF))
			new_mask |= I40E_L4_SRC_MASK;
		अन्यथा अगर (!tcp_ip6_spec->psrc)
			new_mask &= ~I40E_L4_SRC_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* L4 destination port */
		अगर (tcp_ip6_spec->pdst == htons(0xFFFF))
			new_mask |= I40E_L4_DST_MASK;
		अन्यथा अगर (!tcp_ip6_spec->pdst)
			new_mask &= ~I40E_L4_DST_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* Filtering on Traffic Classes is not supported. */
		अगर (tcp_ip6_spec->tclass)
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल IP_USER_FLOW:
		usr_ip4_spec = &fsp->m_u.usr_ip4_spec;

		/* IPv4 source address */
		अगर (usr_ip4_spec->ip4src == htonl(0xFFFFFFFF))
			new_mask |= I40E_L3_SRC_MASK;
		अन्यथा अगर (!usr_ip4_spec->ip4src)
			new_mask &= ~I40E_L3_SRC_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* IPv4 destination address */
		अगर (usr_ip4_spec->ip4dst == htonl(0xFFFFFFFF))
			new_mask |= I40E_L3_DST_MASK;
		अन्यथा अगर (!usr_ip4_spec->ip4dst)
			new_mask &= ~I40E_L3_DST_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* First 4 bytes of L4 header */
		अगर (usr_ip4_spec->l4_4_bytes == htonl(0xFFFFFFFF))
			new_mask |= I40E_L4_SRC_MASK | I40E_L4_DST_MASK;
		अन्यथा अगर (!usr_ip4_spec->l4_4_bytes)
			new_mask &= ~(I40E_L4_SRC_MASK | I40E_L4_DST_MASK);
		अन्यथा
			वापस -EOPNOTSUPP;

		/* Filtering on Type of Service is not supported. */
		अगर (usr_ip4_spec->tos)
			वापस -EOPNOTSUPP;

		/* Filtering on IP version is not supported */
		अगर (usr_ip4_spec->ip_ver)
			वापस -EINVAL;

		/* Filtering on L4 protocol is not supported */
		अगर (usr_ip4_spec->proto)
			वापस -EINVAL;

		अवरोध;
	हाल IPV6_USER_FLOW:
		usr_ip6_spec = &fsp->m_u.usr_ip6_spec;

		/* Check अगर user provided IPv6 source address. */
		अगर (ipv6_addr_equal((काष्ठा in6_addr *)&usr_ip6_spec->ip6src,
				    (काष्ठा in6_addr *)&ipv6_full_mask))
			new_mask |= I40E_L3_V6_SRC_MASK;
		अन्यथा अगर (ipv6_addr_any((काष्ठा in6_addr *)
				       &usr_ip6_spec->ip6src))
			new_mask &= ~I40E_L3_V6_SRC_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		/* Check अगर user provided destination address. */
		अगर (ipv6_addr_equal((काष्ठा in6_addr *)&usr_ip6_spec->ip6dst,
				    (काष्ठा in6_addr *)&ipv6_full_mask))
			new_mask |= I40E_L3_V6_DST_MASK;
		अन्यथा अगर (ipv6_addr_any((काष्ठा in6_addr *)
				       &usr_ip6_spec->ip6src))
			new_mask &= ~I40E_L3_V6_DST_MASK;
		अन्यथा
			वापस -EOPNOTSUPP;

		अगर (usr_ip6_spec->l4_4_bytes == htonl(0xFFFFFFFF))
			new_mask |= I40E_L4_SRC_MASK | I40E_L4_DST_MASK;
		अन्यथा अगर (!usr_ip6_spec->l4_4_bytes)
			new_mask &= ~(I40E_L4_SRC_MASK | I40E_L4_DST_MASK);
		अन्यथा
			वापस -EOPNOTSUPP;

		/* Filtering on Traffic class is not supported. */
		अगर (usr_ip6_spec->tclass)
			वापस -EOPNOTSUPP;

		/* Filtering on L4 protocol is not supported */
		अगर (usr_ip6_spec->l4_proto)
			वापस -EINVAL;

		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (fsp->flow_type & FLOW_EXT) अणु
		/* Allow only 802.1Q and no etype defined, as
		 * later it's modअगरied to 0x8100
		 */
		अगर (fsp->h_ext.vlan_etype != htons(ETH_P_8021Q) &&
		    fsp->h_ext.vlan_etype != 0)
			वापस -EOPNOTSUPP;
		अगर (fsp->m_ext.vlan_tci == htons(0xFFFF))
			new_mask |= I40E_VLAN_SRC_MASK;
		अन्यथा
			new_mask &= ~I40E_VLAN_SRC_MASK;
	पूर्ण

	/* First, clear all flexible filter entries */
	new_mask &= ~I40E_FLEX_INPUT_MASK;

	/* If we have a flexible filter, try to add this offset to the correct
	 * flexible filter PIT list. Once finished, we can update the mask.
	 * If the src_offset changed, we will get a new mask value which will
	 * trigger an input set change.
	 */
	अगर (userdef->flex_filter) अणु
		काष्ठा i40e_flex_pit *l3_flex_pit = शून्य, *flex_pit = शून्य;

		/* Flexible offset must be even, since the flexible payload
		 * must be aligned on 2-byte boundary.
		 */
		अगर (userdef->flex_offset & 0x1) अणु
			dev_warn(&pf->pdev->dev,
				 "Flexible data offset must be 2-byte aligned\n");
			वापस -EINVAL;
		पूर्ण

		src_offset = userdef->flex_offset >> 1;

		/* FLX_PIT source offset value is only so large */
		अगर (src_offset > I40E_MAX_FLEX_SRC_OFFSET) अणु
			dev_warn(&pf->pdev->dev,
				 "Flexible data must reside within first 64 bytes of the packet payload\n");
			वापस -EINVAL;
		पूर्ण

		/* See अगर this offset has alपढ़ोy been programmed. If we get
		 * an ERR_PTR, then the filter is not safe to add. Otherwise,
		 * अगर we get a शून्य poपूर्णांकer, this means we will need to add
		 * the offset.
		 */
		flex_pit = i40e_find_flex_offset(&pf->l4_flex_pit_list,
						 src_offset);
		अगर (IS_ERR(flex_pit))
			वापस PTR_ERR(flex_pit);

		/* IP_USER_FLOW filters match both L4 (ICMP) and L3 (unknown)
		 * packet types, and thus we need to program both L3 and L4
		 * flexible values. These must have identical flexible index,
		 * as otherwise we can't correctly program the input set. So
		 * we'll find both an L3 and L4 index and make sure they are
		 * the same.
		 */
		अगर (flex_l3) अणु
			l3_flex_pit =
				i40e_find_flex_offset(&pf->l3_flex_pit_list,
						      src_offset);
			अगर (IS_ERR(l3_flex_pit))
				वापस PTR_ERR(l3_flex_pit);

			अगर (flex_pit) अणु
				/* If we alपढ़ोy had a matching L4 entry, we
				 * need to make sure that the L3 entry we
				 * obtained uses the same index.
				 */
				अगर (l3_flex_pit) अणु
					अगर (l3_flex_pit->pit_index !=
					    flex_pit->pit_index) अणु
						वापस -EINVAL;
					पूर्ण
				पूर्ण अन्यथा अणु
					new_flex_offset = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				flex_pit = l3_flex_pit;
			पूर्ण
		पूर्ण

		/* If we didn't find an existing flex offset, we need to
		 * program a new one. However, we करोn't immediately program it
		 * here because we will रुको to program until after we check
		 * that it is safe to change the input set.
		 */
		अगर (!flex_pit) अणु
			new_flex_offset = true;
			pit_index = i40e_unused_pit_index(pf);
		पूर्ण अन्यथा अणु
			pit_index = flex_pit->pit_index;
		पूर्ण

		/* Update the mask with the new offset */
		new_mask |= i40e_pit_index_to_mask(pit_index);
	पूर्ण

	/* If the mask and flexible filter offsets क्रम this filter match the
	 * currently programmed values we करोn't need any input set change, so
	 * this filter is safe to install.
	 */
	अगर (new_mask == current_mask && !new_flex_offset)
		वापस 0;

	netअगर_info(pf, drv, vsi->netdev, "Input set change requested for %s flows:\n",
		   i40e_flow_str(fsp));
	i40e_prपूर्णांक_input_set(vsi, current_mask, new_mask);
	अगर (new_flex_offset) अणु
		netअगर_info(pf, drv, vsi->netdev, "FLEX index %d: Offset -> %d",
			   pit_index, src_offset);
	पूर्ण

	/* Hardware input sets are global across multiple ports, so even the
	 * मुख्य port cannot change them when in MFP mode as this would impact
	 * any filters on the other ports.
	 */
	अगर (pf->flags & I40E_FLAG_MFP_ENABLED) अणु
		netअगर_err(pf, drv, vsi->netdev, "Cannot change Flow Director input sets while MFP is enabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* This filter requires us to update the input set. However, hardware
	 * only supports one input set per flow type, and करोes not support
	 * separate masks क्रम each filter. This means that we can only support
	 * a single mask क्रम all filters of a specअगरic type.
	 *
	 * If we have preexisting filters, they obviously depend on the
	 * current programmed input set. Display a diagnostic message in this
	 * हाल explaining why the filter could not be accepted.
	 */
	अगर (*fdir_filter_count) अणु
		netअगर_err(pf, drv, vsi->netdev, "Cannot change input set for %s flows until %d preexisting filters are removed\n",
			  i40e_flow_str(fsp),
			  *fdir_filter_count);
		वापस -EOPNOTSUPP;
	पूर्ण

	i40e_ग_लिखो_fd_input_set(pf, index, new_mask);

	/* IP_USER_FLOW filters match both IPv4/Other and IPv4/Fragmented
	 * frames. If we're programming the input set क्रम IPv4/Other, we also
	 * need to program the IPv4/Fragmented input set. Since we करोn't have
	 * separate support, we'll always assume and enक्रमce that the two flow
	 * types must have matching input sets.
	 */
	अगर (index == I40E_FILTER_PCTYPE_NONF_IPV4_OTHER)
		i40e_ग_लिखो_fd_input_set(pf, I40E_FILTER_PCTYPE_FRAG_IPV4,
					new_mask);

	/* Add the new offset and update table, अगर necessary */
	अगर (new_flex_offset) अणु
		err = i40e_add_flex_offset(&pf->l4_flex_pit_list, src_offset,
					   pit_index);
		अगर (err)
			वापस err;

		अगर (flex_l3) अणु
			err = i40e_add_flex_offset(&pf->l3_flex_pit_list,
						   src_offset,
						   pit_index);
			अगर (err)
				वापस err;
		पूर्ण

		i40e_reprogram_flex_pit(pf);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_match_fdir_filter - Return true of two filters match
 * @a: poपूर्णांकer to filter काष्ठा
 * @b: poपूर्णांकer to filter काष्ठा
 *
 * Returns true अगर the two filters match exactly the same criteria. I.e. they
 * match the same flow type and have the same parameters. We करोn't need to
 * check any input-set since all filters of the same flow type must use the
 * same input set.
 **/
अटल bool i40e_match_fdir_filter(काष्ठा i40e_fdir_filter *a,
				   काष्ठा i40e_fdir_filter *b)
अणु
	/* The filters करो not much अगर any of these criteria dअगरfer. */
	अगर (a->dst_ip != b->dst_ip ||
	    a->src_ip != b->src_ip ||
	    a->dst_port != b->dst_port ||
	    a->src_port != b->src_port ||
	    a->flow_type != b->flow_type ||
	    a->ipl4_proto != b->ipl4_proto ||
	    a->vlan_tag != b->vlan_tag ||
	    a->vlan_etype != b->vlan_etype)
		वापस false;

	वापस true;
पूर्ण

/**
 * i40e_disallow_matching_filters - Check that new filters dअगरfer
 * @vsi: poपूर्णांकer to the targeted VSI
 * @input: new filter to check
 *
 * Due to hardware limitations, it is not possible क्रम two filters that match
 * similar criteria to be programmed at the same समय. This is true क्रम a few
 * reasons:
 *
 * (a) all filters matching a particular flow type must use the same input
 * set, that is they must match the same criteria.
 * (b) dअगरferent flow types will never match the same packet, as the flow type
 * is decided by hardware beक्रमe checking which rules apply.
 * (c) hardware has no way to distinguish which order filters apply in.
 *
 * Due to this, we can't really support using the location data to order
 * filters in the hardware parsing. It is technically possible क्रम the user to
 * request two filters matching the same criteria but which select dअगरferent
 * queues. In this हाल, rather than keep both filters in the list, we reject
 * the 2nd filter when the user requests adding it.
 *
 * This aव्योमs needing to track location क्रम programming the filter to
 * hardware, and ensures that we aव्योम some strange scenarios involving
 * deleting filters which match the same criteria.
 **/
अटल पूर्णांक i40e_disallow_matching_filters(काष्ठा i40e_vsi *vsi,
					  काष्ठा i40e_fdir_filter *input)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_fdir_filter *rule;
	काष्ठा hlist_node *node2;

	/* Loop through every filter, and check that it करोesn't match */
	hlist_क्रम_each_entry_safe(rule, node2,
				  &pf->fdir_filter_list, fdir_node) अणु
		/* Don't check the filters match अगर they share the same fd_id,
		 * since the new filter is actually just updating the target
		 * of the old filter.
		 */
		अगर (rule->fd_id == input->fd_id)
			जारी;

		/* If any filters match, then prपूर्णांक a warning message to the
		 * kernel message buffer and bail out.
		 */
		अगर (i40e_match_fdir_filter(rule, input)) अणु
			dev_warn(&pf->pdev->dev,
				 "Existing user defined filter %d already matches this flow.\n",
				 rule->fd_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_add_fdir_ethtool - Add/Remove Flow Director filters
 * @vsi: poपूर्णांकer to the targeted VSI
 * @cmd: command to get or set RX flow classअगरication rules
 *
 * Add Flow Director filters क्रम a specअगरic flow spec based on their
 * protocol.  Returns 0 अगर the filters were successfully added.
 **/
अटल पूर्णांक i40e_add_fdir_ethtool(काष्ठा i40e_vsi *vsi,
				 काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा i40e_rx_flow_userdef userdef;
	काष्ठा ethtool_rx_flow_spec *fsp;
	काष्ठा i40e_fdir_filter *input;
	u16 dest_vsi = 0, q_index = 0;
	काष्ठा i40e_pf *pf;
	पूर्णांक ret = -EINVAL;
	u8 dest_ctl;

	अगर (!vsi)
		वापस -EINVAL;
	pf = vsi->back;

	अगर (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
		वापस -EOPNOTSUPP;

	अगर (test_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state))
		वापस -ENOSPC;

	अगर (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
	    test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		वापस -EBUSY;

	अगर (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		वापस -EBUSY;

	fsp = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	/* Parse the user-defined field */
	अगर (i40e_parse_rx_flow_user_data(fsp, &userdef))
		वापस -EINVAL;

	/* Extended MAC field is not supported */
	अगर (fsp->flow_type & FLOW_MAC_EXT)
		वापस -EINVAL;

	ret = i40e_check_fdir_input_set(vsi, fsp, &userdef);
	अगर (ret)
		वापस ret;

	अगर (fsp->location >= (pf->hw.func_caps.fd_filters_best_efक्रमt +
			      pf->hw.func_caps.fd_filters_guaranteed)) अणु
		वापस -EINVAL;
	पूर्ण

	/* ring_cookie is either the drop index, or is a mask of the queue
	 * index and VF id we wish to target.
	 */
	अगर (fsp->ring_cookie == RX_CLS_FLOW_DISC) अणु
		dest_ctl = I40E_FILTER_PROGRAM_DESC_DEST_DROP_PACKET;
	पूर्ण अन्यथा अणु
		u32 ring = ethtool_get_flow_spec_ring(fsp->ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(fsp->ring_cookie);

		अगर (!vf) अणु
			अगर (ring >= vsi->num_queue_pairs)
				वापस -EINVAL;
			dest_vsi = vsi->id;
		पूर्ण अन्यथा अणु
			/* VFs are zero-indexed, so we subtract one here */
			vf--;

			अगर (vf >= pf->num_alloc_vfs)
				वापस -EINVAL;
			अगर (ring >= pf->vf[vf].num_queue_pairs)
				वापस -EINVAL;
			dest_vsi = pf->vf[vf].lan_vsi_id;
		पूर्ण
		dest_ctl = I40E_FILTER_PROGRAM_DESC_DEST_सूचीECT_PACKET_QINDEX;
		q_index = ring;
	पूर्ण

	input = kzalloc(माप(*input), GFP_KERNEL);

	अगर (!input)
		वापस -ENOMEM;

	input->fd_id = fsp->location;
	input->q_index = q_index;
	input->dest_vsi = dest_vsi;
	input->dest_ctl = dest_ctl;
	input->fd_status = I40E_FILTER_PROGRAM_DESC_FD_STATUS_FD_ID;
	input->cnt_index  = I40E_FD_SB_STAT_IDX(pf->hw.pf_id);
	input->dst_ip = fsp->h_u.tcp_ip4_spec.ip4src;
	input->src_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
	input->flow_type = fsp->flow_type & ~FLOW_EXT;

	input->vlan_etype = fsp->h_ext.vlan_etype;
	अगर (!fsp->m_ext.vlan_etype && fsp->h_ext.vlan_tci)
		input->vlan_etype = cpu_to_be16(ETH_P_8021Q);
	अगर (fsp->m_ext.vlan_tci && input->vlan_etype)
		input->vlan_tag = fsp->h_ext.vlan_tci;
	अगर (input->flow_type == IPV6_USER_FLOW ||
	    input->flow_type == UDP_V6_FLOW ||
	    input->flow_type == TCP_V6_FLOW ||
	    input->flow_type == SCTP_V6_FLOW) अणु
		/* Reverse the src and dest notion, since the HW expects them
		 * to be from Tx perspective where as the input from user is
		 * from Rx filter view.
		 */
		input->ipl4_proto = fsp->h_u.usr_ip6_spec.l4_proto;
		input->dst_port = fsp->h_u.tcp_ip6_spec.psrc;
		input->src_port = fsp->h_u.tcp_ip6_spec.pdst;
		स_नकल(input->dst_ip6, fsp->h_u.ah_ip6_spec.ip6src,
		       माप(__be32) * 4);
		स_नकल(input->src_ip6, fsp->h_u.ah_ip6_spec.ip6dst,
		       माप(__be32) * 4);
	पूर्ण अन्यथा अणु
		/* Reverse the src and dest notion, since the HW expects them
		 * to be from Tx perspective where as the input from user is
		 * from Rx filter view.
		 */
		input->ipl4_proto = fsp->h_u.usr_ip4_spec.proto;
		input->dst_port = fsp->h_u.tcp_ip4_spec.psrc;
		input->src_port = fsp->h_u.tcp_ip4_spec.pdst;
		input->dst_ip = fsp->h_u.tcp_ip4_spec.ip4src;
		input->src_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
	पूर्ण

	अगर (userdef.flex_filter) अणु
		input->flex_filter = true;
		input->flex_word = cpu_to_be16(userdef.flex_word);
		input->flex_offset = userdef.flex_offset;
	पूर्ण

	/* Aव्योम programming two filters with identical match criteria. */
	ret = i40e_disallow_matching_filters(vsi, input);
	अगर (ret)
		जाओ मुक्त_filter_memory;

	/* Add the input filter to the fdir_input_list, possibly replacing
	 * a previous filter. Do not मुक्त the input काष्ठाure after adding it
	 * to the list as this would cause a use-after-मुक्त bug.
	 */
	i40e_update_ethtool_fdir_entry(vsi, input, fsp->location, शून्य);
	ret = i40e_add_del_fdir(vsi, input, true);
	अगर (ret)
		जाओ हटाओ_sw_rule;
	वापस 0;

हटाओ_sw_rule:
	hlist_del(&input->fdir_node);
	pf->fdir_pf_active_filters--;
मुक्त_filter_memory:
	kमुक्त(input);
	वापस ret;
पूर्ण

/**
 * i40e_set_rxnfc - command to set RX flow classअगरication rules
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool rxnfc command
 *
 * Returns Success अगर the command is supported.
 **/
अटल पूर्णांक i40e_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = i40e_set_rss_hash_opt(pf, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		ret = i40e_add_fdir_ethtool(vsi, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = i40e_del_fdir_entry(vsi, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i40e_max_channels - get Max number of combined channels supported
 * @vsi: vsi poपूर्णांकer
 **/
अटल अचिन्हित पूर्णांक i40e_max_channels(काष्ठा i40e_vsi *vsi)
अणु
	/* TODO: This code assumes DCB and FD is disabled क्रम now. */
	वापस vsi->alloc_queue_pairs;
पूर्ण

/**
 * i40e_get_channels - Get the current channels enabled and max supported etc.
 * @dev: network पूर्णांकerface device काष्ठाure
 * @ch: ethtool channels काष्ठाure
 *
 * We करोn't support separate tx and rx queues as channels. The other count
 * represents how many queues are being used क्रम control. max_combined counts
 * how many queue pairs we can support. They may not be mapped 1 to 1 with
 * q_vectors since we support a lot more queue pairs than q_vectors.
 **/
अटल व्योम i40e_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;

	/* report maximum channels */
	ch->max_combined = i40e_max_channels(vsi);

	/* report info क्रम other vector */
	ch->other_count = (pf->flags & I40E_FLAG_FD_SB_ENABLED) ? 1 : 0;
	ch->max_other = ch->other_count;

	/* Note: This code assumes DCB is disabled क्रम now. */
	ch->combined_count = vsi->num_queue_pairs;
पूर्ण

/**
 * i40e_set_channels - Set the new channels count.
 * @dev: network पूर्णांकerface device काष्ठाure
 * @ch: ethtool channels काष्ठाure
 *
 * The new channels count may not be the same as requested by the user
 * since it माला_लो rounded करोwn to a घातer of 2 value.
 **/
अटल पूर्णांक i40e_set_channels(काष्ठा net_device *dev,
			     काष्ठा ethtool_channels *ch)
अणु
	स्थिर u8 drop = I40E_FILTER_PROGRAM_DESC_DEST_DROP_PACKET;
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	अचिन्हित पूर्णांक count = ch->combined_count;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_fdir_filter *rule;
	काष्ठा hlist_node *node2;
	पूर्णांक new_count;
	पूर्णांक err = 0;

	/* We करो not support setting channels क्रम any other VSI at present */
	अगर (vsi->type != I40E_VSI_MAIN)
		वापस -EINVAL;

	/* We करो not support setting channels via ethtool when TCs are
	 * configured through mqprio
	 */
	अगर (pf->flags & I40E_FLAG_TC_MQPRIO)
		वापस -EINVAL;

	/* verअगरy they are not requesting separate vectors */
	अगर (!count || ch->rx_count || ch->tx_count)
		वापस -EINVAL;

	/* verअगरy other_count has not changed */
	अगर (ch->other_count != ((pf->flags & I40E_FLAG_FD_SB_ENABLED) ? 1 : 0))
		वापस -EINVAL;

	/* verअगरy the number of channels करोes not exceed hardware limits */
	अगर (count > i40e_max_channels(vsi))
		वापस -EINVAL;

	/* verअगरy that the number of channels करोes not invalidate any current
	 * flow director rules
	 */
	hlist_क्रम_each_entry_safe(rule, node2,
				  &pf->fdir_filter_list, fdir_node) अणु
		अगर (rule->dest_ctl != drop && count <= rule->q_index) अणु
			dev_warn(&pf->pdev->dev,
				 "Existing user defined filter %d assigns flow to queue %d\n",
				 rule->fd_id, rule->q_index);
			err = -EINVAL;
		पूर्ण
	पूर्ण

	अगर (err) अणु
		dev_err(&pf->pdev->dev,
			"Existing filter rules must be deleted to reduce combined channel count to %d\n",
			count);
		वापस err;
	पूर्ण

	/* update feature limits from largest to smallest supported values */
	/* TODO: Flow director limit, DCB etc */

	/* use rss_reconfig to rebuild with new queue count and update traffic
	 * class queue mapping
	 */
	new_count = i40e_reconfig_rss_queues(pf, count);
	अगर (new_count > 0)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

/**
 * i40e_get_rxfh_key_size - get the RSS hash key size
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the table size.
 **/
अटल u32 i40e_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस I40E_HKEY_ARRAY_SIZE;
पूर्ण

/**
 * i40e_get_rxfh_indir_size - get the rx flow hash indirection table size
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the table size.
 **/
अटल u32 i40e_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस I40E_HLUT_ARRAY_SIZE;
पूर्ण

/**
 * i40e_get_rxfh - get the rx flow hash indirection table
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @indir: indirection table
 * @key: hash key
 * @hfunc: hash function
 *
 * Reads the indirection table directly from the hardware. Returns 0 on
 * success.
 **/
अटल पूर्णांक i40e_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			 u8 *hfunc)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	u8 *lut, *seed = शून्य;
	पूर्णांक ret;
	u16 i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (!indir)
		वापस 0;

	seed = key;
	lut = kzalloc(I40E_HLUT_ARRAY_SIZE, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;
	ret = i40e_get_rss(vsi, seed, lut, I40E_HLUT_ARRAY_SIZE);
	अगर (ret)
		जाओ out;
	क्रम (i = 0; i < I40E_HLUT_ARRAY_SIZE; i++)
		indir[i] = (u32)(lut[i]);

out:
	kमुक्त(lut);

	वापस ret;
पूर्ण

/**
 * i40e_set_rxfh - set the rx flow hash indirection table
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @indir: indirection table
 * @key: hash key
 * @hfunc: hash function to use
 *
 * Returns -EINVAL अगर the table specअगरies an invalid queue id, otherwise
 * वापसs 0 after programming the table.
 **/
अटल पूर्णांक i40e_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	u8 *seed = शून्य;
	u16 i;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (key) अणु
		अगर (!vsi->rss_hkey_user) अणु
			vsi->rss_hkey_user = kzalloc(I40E_HKEY_ARRAY_SIZE,
						     GFP_KERNEL);
			अगर (!vsi->rss_hkey_user)
				वापस -ENOMEM;
		पूर्ण
		स_नकल(vsi->rss_hkey_user, key, I40E_HKEY_ARRAY_SIZE);
		seed = vsi->rss_hkey_user;
	पूर्ण
	अगर (!vsi->rss_lut_user) अणु
		vsi->rss_lut_user = kzalloc(I40E_HLUT_ARRAY_SIZE, GFP_KERNEL);
		अगर (!vsi->rss_lut_user)
			वापस -ENOMEM;
	पूर्ण

	/* Each 32 bits poपूर्णांकed by 'indir' is stored with a lut entry */
	अगर (indir)
		क्रम (i = 0; i < I40E_HLUT_ARRAY_SIZE; i++)
			vsi->rss_lut_user[i] = (u8)(indir[i]);
	अन्यथा
		i40e_fill_rss_lut(pf, vsi->rss_lut_user, I40E_HLUT_ARRAY_SIZE,
				  vsi->rss_size);

	वापस i40e_config_rss(vsi, seed, vsi->rss_lut_user,
			       I40E_HLUT_ARRAY_SIZE);
पूर्ण

/**
 * i40e_get_priv_flags - report device निजी flags
 * @dev: network पूर्णांकerface device काष्ठाure
 *
 * The get string set count and the string set should be matched क्रम each
 * flag वापसed.  Add new strings क्रम each flag to the i40e_gstrings_priv_flags
 * array.
 *
 * Returns a u32 biपंचांगap of flags.
 **/
अटल u32 i40e_get_priv_flags(काष्ठा net_device *dev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	u32 i, j, ret_flags = 0;

	क्रम (i = 0; i < I40E_PRIV_FLAGS_STR_LEN; i++) अणु
		स्थिर काष्ठा i40e_priv_flags *priv_flags;

		priv_flags = &i40e_gstrings_priv_flags[i];

		अगर (priv_flags->flag & pf->flags)
			ret_flags |= BIT(i);
	पूर्ण

	अगर (pf->hw.pf_id != 0)
		वापस ret_flags;

	क्रम (j = 0; j < I40E_GL_PRIV_FLAGS_STR_LEN; j++) अणु
		स्थिर काष्ठा i40e_priv_flags *priv_flags;

		priv_flags = &i40e_gl_gstrings_priv_flags[j];

		अगर (priv_flags->flag & pf->flags)
			ret_flags |= BIT(i + j);
	पूर्ण

	वापस ret_flags;
पूर्ण

/**
 * i40e_set_priv_flags - set निजी flags
 * @dev: network पूर्णांकerface device काष्ठाure
 * @flags: bit flags to be set
 **/
अटल पूर्णांक i40e_set_priv_flags(काष्ठा net_device *dev, u32 flags)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	u64 orig_flags, new_flags, changed_flags;
	क्रमागत i40e_admin_queue_err adq_err;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	u32 reset_needed = 0;
	i40e_status status;
	u32 i, j;

	orig_flags = READ_ONCE(pf->flags);
	new_flags = orig_flags;

	क्रम (i = 0; i < I40E_PRIV_FLAGS_STR_LEN; i++) अणु
		स्थिर काष्ठा i40e_priv_flags *priv_flags;

		priv_flags = &i40e_gstrings_priv_flags[i];

		अगर (flags & BIT(i))
			new_flags |= priv_flags->flag;
		अन्यथा
			new_flags &= ~(priv_flags->flag);

		/* If this is a पढ़ो-only flag, it can't be changed */
		अगर (priv_flags->पढ़ो_only &&
		    ((orig_flags ^ new_flags) & ~BIT(i)))
			वापस -EOPNOTSUPP;
	पूर्ण

	अगर (pf->hw.pf_id != 0)
		जाओ flags_complete;

	क्रम (j = 0; j < I40E_GL_PRIV_FLAGS_STR_LEN; j++) अणु
		स्थिर काष्ठा i40e_priv_flags *priv_flags;

		priv_flags = &i40e_gl_gstrings_priv_flags[j];

		अगर (flags & BIT(i + j))
			new_flags |= priv_flags->flag;
		अन्यथा
			new_flags &= ~(priv_flags->flag);

		/* If this is a पढ़ो-only flag, it can't be changed */
		अगर (priv_flags->पढ़ो_only &&
		    ((orig_flags ^ new_flags) & ~BIT(i)))
			वापस -EOPNOTSUPP;
	पूर्ण

flags_complete:
	changed_flags = orig_flags ^ new_flags;

	अगर (changed_flags & I40E_FLAG_DISABLE_FW_LLDP)
		reset_needed = I40E_PF_RESET_AND_REBUILD_FLAG;
	अगर (changed_flags & (I40E_FLAG_VEB_STATS_ENABLED |
	    I40E_FLAG_LEGACY_RX | I40E_FLAG_SOURCE_PRUNING_DISABLED))
		reset_needed = BIT(__I40E_PF_RESET_REQUESTED);

	/* Beक्रमe we finalize any flag changes, we need to perक्रमm some
	 * checks to ensure that the changes are supported and safe.
	 */

	/* ATR eviction is not supported on all devices */
	अगर ((new_flags & I40E_FLAG_HW_ATR_EVICT_ENABLED) &&
	    !(pf->hw_features & I40E_HW_ATR_EVICT_CAPABLE))
		वापस -EOPNOTSUPP;

	/* If the driver detected FW LLDP was disabled on init, this flag could
	 * be set, however we करो not support _changing_ the flag:
	 * - on XL710 अगर NPAR is enabled or FW API version < 1.7
	 * - on X722 with FW API version < 1.6
	 * There are situations where older FW versions/NPAR enabled PFs could
	 * disable LLDP, however we _must_ not allow the user to enable/disable
	 * LLDP with this flag on unsupported FW versions.
	 */
	अगर (changed_flags & I40E_FLAG_DISABLE_FW_LLDP) अणु
		अगर (!(pf->hw.flags & I40E_HW_FLAG_FW_LLDP_STOPPABLE)) अणु
			dev_warn(&pf->pdev->dev,
				 "Device does not support changing FW LLDP\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (changed_flags & I40E_FLAG_RS_FEC &&
	    pf->hw.device_id != I40E_DEV_ID_25G_SFP28 &&
	    pf->hw.device_id != I40E_DEV_ID_25G_B) अणु
		dev_warn(&pf->pdev->dev,
			 "Device does not support changing FEC configuration\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (changed_flags & I40E_FLAG_BASE_R_FEC &&
	    pf->hw.device_id != I40E_DEV_ID_25G_SFP28 &&
	    pf->hw.device_id != I40E_DEV_ID_25G_B &&
	    pf->hw.device_id != I40E_DEV_ID_KX_X722) अणु
		dev_warn(&pf->pdev->dev,
			 "Device does not support changing FEC configuration\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Process any additional changes needed as a result of flag changes.
	 * The changed_flags value reflects the list of bits that were
	 * changed in the code above.
	 */

	/* Flush current ATR settings अगर ATR was disabled */
	अगर ((changed_flags & I40E_FLAG_FD_ATR_ENABLED) &&
	    !(new_flags & I40E_FLAG_FD_ATR_ENABLED)) अणु
		set_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state);
		set_bit(__I40E_FD_FLUSH_REQUESTED, pf->state);
	पूर्ण

	अगर (changed_flags & I40E_FLAG_TRUE_PROMISC_SUPPORT) अणु
		u16 sw_flags = 0, valid_flags = 0;
		पूर्णांक ret;

		अगर (!(new_flags & I40E_FLAG_TRUE_PROMISC_SUPPORT))
			sw_flags = I40E_AQ_SET_SWITCH_CFG_PROMISC;
		valid_flags = I40E_AQ_SET_SWITCH_CFG_PROMISC;
		ret = i40e_aq_set_चयन_config(&pf->hw, sw_flags, valid_flags,
						0, शून्य);
		अगर (ret && pf->hw.aq.asq_last_status != I40E_AQ_RC_ESRCH) अणु
			dev_info(&pf->pdev->dev,
				 "couldn't set switch config bits, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			/* not a fatal problem, just keep going */
		पूर्ण
	पूर्ण

	अगर ((changed_flags & I40E_FLAG_RS_FEC) ||
	    (changed_flags & I40E_FLAG_BASE_R_FEC)) अणु
		u8 fec_cfg = 0;

		अगर (new_flags & I40E_FLAG_RS_FEC &&
		    new_flags & I40E_FLAG_BASE_R_FEC) अणु
			fec_cfg = I40E_AQ_SET_FEC_AUTO;
		पूर्ण अन्यथा अगर (new_flags & I40E_FLAG_RS_FEC) अणु
			fec_cfg = (I40E_AQ_SET_FEC_REQUEST_RS |
				   I40E_AQ_SET_FEC_ABILITY_RS);
		पूर्ण अन्यथा अगर (new_flags & I40E_FLAG_BASE_R_FEC) अणु
			fec_cfg = (I40E_AQ_SET_FEC_REQUEST_KR |
				   I40E_AQ_SET_FEC_ABILITY_KR);
		पूर्ण
		अगर (i40e_set_fec_cfg(dev, fec_cfg))
			dev_warn(&pf->pdev->dev, "Cannot change FEC config\n");
	पूर्ण

	अगर ((changed_flags & I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED) &&
	    (orig_flags & I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED)) अणु
		dev_err(&pf->pdev->dev,
			"Setting link-down-on-close not supported on this port (because total-port-shutdown is enabled)\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((changed_flags & new_flags &
	     I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED) &&
	    (new_flags & I40E_FLAG_MFP_ENABLED))
		dev_warn(&pf->pdev->dev,
			 "Turning on link-down-on-close flag may affect other partitions\n");

	अगर (changed_flags & I40E_FLAG_DISABLE_FW_LLDP) अणु
		अगर (new_flags & I40E_FLAG_DISABLE_FW_LLDP) अणु
#अगर_घोषित CONFIG_I40E_DCB
			i40e_dcb_sw_शेष_config(pf);
#पूर्ण_अगर /* CONFIG_I40E_DCB */
			i40e_aq_cfg_lldp_mib_change_event(&pf->hw, false, शून्य);
			i40e_aq_stop_lldp(&pf->hw, true, false, शून्य);
		पूर्ण अन्यथा अणु
			status = i40e_aq_start_lldp(&pf->hw, false, शून्य);
			अगर (status) अणु
				adq_err = pf->hw.aq.asq_last_status;
				चयन (adq_err) अणु
				हाल I40E_AQ_RC_EEXIST:
					dev_warn(&pf->pdev->dev,
						 "FW LLDP agent is already running\n");
					reset_needed = 0;
					अवरोध;
				हाल I40E_AQ_RC_EPERM:
					dev_warn(&pf->pdev->dev,
						 "Device configuration forbids SW from starting the LLDP agent.\n");
					वापस -EINVAL;
				शेष:
					dev_warn(&pf->pdev->dev,
						 "Starting FW LLDP agent failed: error: %s, %s\n",
						 i40e_stat_str(&pf->hw,
							       status),
						 i40e_aq_str(&pf->hw,
							     adq_err));
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Now that we've checked to ensure that the new flags are valid, load
	 * them पूर्णांकo place. Since we only modअगरy flags either (a) during
	 * initialization or (b) जबतक holding the RTNL lock, we करोn't need
	 * anything fancy here.
	 */
	pf->flags = new_flags;

	/* Issue reset to cause things to take effect, as additional bits
	 * are added we will need to create a mask of bits requiring reset
	 */
	अगर (reset_needed)
		i40e_करो_reset(pf, reset_needed, true);

	वापस 0;
पूर्ण

/**
 * i40e_get_module_info - get (Q)SFP+ module type info
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @modinfo: module EEPROM size and layout inक्रमmation काष्ठाure
 **/
अटल पूर्णांक i40e_get_module_info(काष्ठा net_device *netdev,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 sff8472_comp = 0;
	u32 sff8472_swap = 0;
	u32 sff8636_rev = 0;
	i40e_status status;
	u32 type = 0;

	/* Check अगर firmware supports पढ़ोing module EEPROM. */
	अगर (!(hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE)) अणु
		netdev_err(vsi->netdev, "Module EEPROM memory read not supported. Please update the NVM image.\n");
		वापस -EINVAL;
	पूर्ण

	status = i40e_update_link_info(hw);
	अगर (status)
		वापस -EIO;

	अगर (hw->phy.link_info.phy_type == I40E_PHY_TYPE_EMPTY) अणु
		netdev_err(vsi->netdev, "Cannot read module EEPROM memory. No module connected.\n");
		वापस -EINVAL;
	पूर्ण

	type = hw->phy.link_info.module_type[0];

	चयन (type) अणु
	हाल I40E_MODULE_TYPE_SFP:
		status = i40e_aq_get_phy_रेजिस्टर(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				I40E_I2C_EEPROM_DEV_ADDR, true,
				I40E_MODULE_SFF_8472_COMP,
				&sff8472_comp, शून्य);
		अगर (status)
			वापस -EIO;

		status = i40e_aq_get_phy_रेजिस्टर(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				I40E_I2C_EEPROM_DEV_ADDR, true,
				I40E_MODULE_SFF_8472_SWAP,
				&sff8472_swap, शून्य);
		अगर (status)
			वापस -EIO;

		/* Check अगर the module requires address swap to access
		 * the other EEPROM memory page.
		 */
		अगर (sff8472_swap & I40E_MODULE_SFF_ADDR_MODE) अणु
			netdev_warn(vsi->netdev, "Module address swap to access page 0xA2 is not supported.\n");
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अगर (sff8472_comp == 0x00) अणु
			/* Module is not SFF-8472 compliant */
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अगर (!(sff8472_swap & I40E_MODULE_SFF_DDM_IMPLEMENTED)) अणु
			/* Module is SFF-8472 compliant but करोesn't implement
			 * Digital Diagnostic Monitoring (DDM).
			 */
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		पूर्ण
		अवरोध;
	हाल I40E_MODULE_TYPE_QSFP_PLUS:
		/* Read from memory page 0. */
		status = i40e_aq_get_phy_रेजिस्टर(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				0, true,
				I40E_MODULE_REVISION_ADDR,
				&sff8636_rev, शून्य);
		अगर (status)
			वापस -EIO;
		/* Determine revision compliance byte */
		अगर (sff8636_rev > 0x02) अणु
			/* Module is SFF-8636 compliant */
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = I40E_MODULE_QSFP_MAX_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = I40E_MODULE_QSFP_MAX_LEN;
		पूर्ण
		अवरोध;
	हाल I40E_MODULE_TYPE_QSFP28:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = I40E_MODULE_QSFP_MAX_LEN;
		अवरोध;
	शेष:
		netdev_err(vsi->netdev, "Module type unrecognized\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i40e_get_module_eeprom - fills buffer with (Q)SFP+ module memory contents
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ee: EEPROM dump request काष्ठाure
 * @data: buffer to be filled with EEPROM contents
 **/
अटल पूर्णांक i40e_get_module_eeprom(काष्ठा net_device *netdev,
				  काष्ठा ethtool_eeprom *ee,
				  u8 *data)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	bool is_sfp = false;
	i40e_status status;
	u32 value = 0;
	पूर्णांक i;

	अगर (!ee || !ee->len || !data)
		वापस -EINVAL;

	अगर (hw->phy.link_info.module_type[0] == I40E_MODULE_TYPE_SFP)
		is_sfp = true;

	क्रम (i = 0; i < ee->len; i++) अणु
		u32 offset = i + ee->offset;
		u32 addr = is_sfp ? I40E_I2C_EEPROM_DEV_ADDR : 0;

		/* Check अगर we need to access the other memory page */
		अगर (is_sfp) अणु
			अगर (offset >= ETH_MODULE_SFF_8079_LEN) अणु
				offset -= ETH_MODULE_SFF_8079_LEN;
				addr = I40E_I2C_EEPROM_DEV_ADDR2;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (offset >= ETH_MODULE_SFF_8436_LEN) अणु
				/* Compute memory page number and offset. */
				offset -= ETH_MODULE_SFF_8436_LEN / 2;
				addr++;
			पूर्ण
		पूर्ण

		status = i40e_aq_get_phy_रेजिस्टर(hw,
				I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
				addr, true, offset, &value, शून्य);
		अगर (status)
			वापस -EIO;
		data[i] = value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i40e_get_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_aq_get_phy_abilities_resp phy_cfg;
	क्रमागत i40e_status_code status = 0;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;

	/* Get initial PHY capabilities */
	status = i40e_aq_get_phy_capabilities(hw, false, true, &phy_cfg, शून्य);
	अगर (status)
		वापस -EAGAIN;

	/* Check whether NIC configuration is compatible with Energy Efficient
	 * Ethernet (EEE) mode.
	 */
	अगर (phy_cfg.eee_capability == 0)
		वापस -EOPNOTSUPP;

	edata->supported = SUPPORTED_Autoneg;
	edata->lp_advertised = edata->supported;

	/* Get current configuration */
	status = i40e_aq_get_phy_capabilities(hw, false, false, &phy_cfg, शून्य);
	अगर (status)
		वापस -EAGAIN;

	edata->advertised = phy_cfg.eee_capability ? SUPPORTED_Autoneg : 0U;
	edata->eee_enabled = !!edata->advertised;
	edata->tx_lpi_enabled = pf->stats.tx_lpi_status;

	edata->eee_active = pf->stats.tx_lpi_status && pf->stats.rx_lpi_status;

	वापस 0;
पूर्ण

अटल पूर्णांक i40e_is_eee_param_supported(काष्ठा net_device *netdev,
				       काष्ठा ethtool_eee *edata)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_ethtool_not_used अणु
		u32 value;
		स्थिर अक्षर *name;
	पूर्ण param[] = अणु
		अणुedata->advertised & ~SUPPORTED_Autoneg, "advertise"पूर्ण,
		अणुedata->tx_lpi_समयr, "tx-timer"पूर्ण,
		अणुedata->tx_lpi_enabled != pf->stats.tx_lpi_status, "tx-lpi"पूर्ण
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(param); i++) अणु
		अगर (param[i].value) अणु
			netdev_info(netdev,
				    "EEE setting %s not supported\n",
				    param[i].name);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i40e_set_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_aq_get_phy_abilities_resp abilities;
	क्रमागत i40e_status_code status = I40E_SUCCESS;
	काष्ठा i40e_aq_set_phy_config config;
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	__le16 eee_capability;

	/* Deny parameters we करोn't support */
	अगर (i40e_is_eee_param_supported(netdev, edata))
		वापस -EOPNOTSUPP;

	/* Get initial PHY capabilities */
	status = i40e_aq_get_phy_capabilities(hw, false, true, &abilities,
					      शून्य);
	अगर (status)
		वापस -EAGAIN;

	/* Check whether NIC configuration is compatible with Energy Efficient
	 * Ethernet (EEE) mode.
	 */
	अगर (abilities.eee_capability == 0)
		वापस -EOPNOTSUPP;

	/* Cache initial EEE capability */
	eee_capability = abilities.eee_capability;

	/* Get current PHY configuration */
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      शून्य);
	अगर (status)
		वापस -EAGAIN;

	/* Cache current PHY configuration */
	config.phy_type = abilities.phy_type;
	config.phy_type_ext = abilities.phy_type_ext;
	config.link_speed = abilities.link_speed;
	config.abilities = abilities.abilities |
			   I40E_AQ_PHY_ENABLE_ATOMIC_LINK;
	config.eeer = abilities.eeer_val;
	config.low_घातer_ctrl = abilities.d3_lpan;
	config.fec_config = abilities.fec_cfg_curr_mod_ext_info &
			    I40E_AQ_PHY_FEC_CONFIG_MASK;

	/* Set desired EEE state */
	अगर (edata->eee_enabled) अणु
		config.eee_capability = eee_capability;
		config.eeer |= cpu_to_le32(I40E_PRTPM_EEER_TX_LPI_EN_MASK);
	पूर्ण अन्यथा अणु
		config.eee_capability = 0;
		config.eeer &= cpu_to_le32(~I40E_PRTPM_EEER_TX_LPI_EN_MASK);
	पूर्ण

	/* Apply modअगरied PHY configuration */
	status = i40e_aq_set_phy_config(hw, &config, शून्य);
	अगर (status)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops i40e_ethtool_recovery_mode_ops = अणु
	.get_drvinfo		= i40e_get_drvinfo,
	.set_eeprom		= i40e_set_eeprom,
	.get_eeprom_len		= i40e_get_eeprom_len,
	.get_eeprom		= i40e_get_eeprom,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops i40e_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES_IRQ |
				     ETHTOOL_COALESCE_USE_ADAPTIVE |
				     ETHTOOL_COALESCE_RX_USECS_HIGH |
				     ETHTOOL_COALESCE_TX_USECS_HIGH,
	.get_drvinfo		= i40e_get_drvinfo,
	.get_regs_len		= i40e_get_regs_len,
	.get_regs		= i40e_get_regs,
	.nway_reset		= i40e_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_wol		= i40e_get_wol,
	.set_wol		= i40e_set_wol,
	.set_eeprom		= i40e_set_eeprom,
	.get_eeprom_len		= i40e_get_eeprom_len,
	.get_eeprom		= i40e_get_eeprom,
	.get_ringparam		= i40e_get_ringparam,
	.set_ringparam		= i40e_set_ringparam,
	.get_छोड़ोparam		= i40e_get_छोड़ोparam,
	.set_छोड़ोparam		= i40e_set_छोड़ोparam,
	.get_msglevel		= i40e_get_msglevel,
	.set_msglevel		= i40e_set_msglevel,
	.get_rxnfc		= i40e_get_rxnfc,
	.set_rxnfc		= i40e_set_rxnfc,
	.self_test		= i40e_diag_test,
	.get_strings		= i40e_get_strings,
	.get_eee		= i40e_get_eee,
	.set_eee		= i40e_set_eee,
	.set_phys_id		= i40e_set_phys_id,
	.get_sset_count		= i40e_get_sset_count,
	.get_ethtool_stats	= i40e_get_ethtool_stats,
	.get_coalesce		= i40e_get_coalesce,
	.set_coalesce		= i40e_set_coalesce,
	.get_rxfh_key_size	= i40e_get_rxfh_key_size,
	.get_rxfh_indir_size	= i40e_get_rxfh_indir_size,
	.get_rxfh		= i40e_get_rxfh,
	.set_rxfh		= i40e_set_rxfh,
	.get_channels		= i40e_get_channels,
	.set_channels		= i40e_set_channels,
	.get_module_info	= i40e_get_module_info,
	.get_module_eeprom	= i40e_get_module_eeprom,
	.get_ts_info		= i40e_get_ts_info,
	.get_priv_flags		= i40e_get_priv_flags,
	.set_priv_flags		= i40e_set_priv_flags,
	.get_per_queue_coalesce	= i40e_get_per_queue_coalesce,
	.set_per_queue_coalesce	= i40e_set_per_queue_coalesce,
	.get_link_ksettings	= i40e_get_link_ksettings,
	.set_link_ksettings	= i40e_set_link_ksettings,
	.get_fecparam = i40e_get_fec_param,
	.set_fecparam = i40e_set_fec_param,
	.flash_device = i40e_ddp_flash,
पूर्ण;

व्योम i40e_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_pf		*pf = np->vsi->back;

	अगर (!test_bit(__I40E_RECOVERY_MODE, pf->state))
		netdev->ethtool_ops = &i40e_ethtool_ops;
	अन्यथा
		netdev->ethtool_ops = &i40e_ethtool_recovery_mode_ops;
पूर्ण
