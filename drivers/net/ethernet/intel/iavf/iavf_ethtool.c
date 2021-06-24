<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

/* ethtool support क्रम iavf */
#समावेश "iavf.h"

#समावेश <linux/uaccess.h>

/* ethtool statistics helpers */

/**
 * काष्ठा iavf_stats - definition क्रम an ethtool statistic
 * @stat_string: statistic name to display in ethtool -S output
 * @माप_stat: the माप() the stat, must be no greater than माप(u64)
 * @stat_offset: दुरत्व() the stat from a base poपूर्णांकer
 *
 * This काष्ठाure defines a statistic to be added to the ethtool stats buffer.
 * It defines a statistic as offset from a common base poपूर्णांकer. Stats should
 * be defined in स्थिरant arrays using the IAVF_STAT macro, with every element
 * of the array using the same _type क्रम calculating the माप_stat and
 * stat_offset.
 *
 * The @माप_stat is expected to be माप(u8), माप(u16), माप(u32) or
 * माप(u64). Other sizes are not expected and will produce a WARN_ONCE from
 * the iavf_add_ethtool_stat() helper function.
 *
 * The @stat_string is पूर्णांकerpreted as a क्रमmat string, allowing क्रमmatted
 * values to be inserted जबतक looping over multiple काष्ठाures क्रम a given
 * statistics array. Thus, every statistic string in an array should have the
 * same type and number of क्रमmat specअगरiers, to be क्रमmatted by variadic
 * arguments to the iavf_add_stat_string() helper function.
 **/
काष्ठा iavf_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

/* Helper macro to define an iavf_stat काष्ठाure with proper size and type.
 * Use this when defining स्थिरant statistics arrays. Note that @_type expects
 * only a type name and is used multiple बार.
 */
#घोषणा IAVF_STAT(_type, _name, _stat) अणु \
	.stat_string = _name, \
	.माप_stat = माप_field(_type, _stat), \
	.stat_offset = दुरत्व(_type, _stat) \
पूर्ण

/* Helper macro क्रम defining some statistics related to queues */
#घोषणा IAVF_QUEUE_STAT(_name, _stat) \
	IAVF_STAT(काष्ठा iavf_ring, _name, _stat)

/* Stats associated with a Tx or Rx ring */
अटल स्थिर काष्ठा iavf_stats iavf_gstrings_queue_stats[] = अणु
	IAVF_QUEUE_STAT("%s-%u.packets", stats.packets),
	IAVF_QUEUE_STAT("%s-%u.bytes", stats.bytes),
पूर्ण;

/**
 * iavf_add_one_ethtool_stat - copy the stat पूर्णांकo the supplied buffer
 * @data: location to store the stat value
 * @poपूर्णांकer: basis क्रम where to copy from
 * @stat: the stat definition
 *
 * Copies the stat data defined by the poपूर्णांकer and stat काष्ठाure pair पूर्णांकo
 * the memory supplied as data. Used to implement iavf_add_ethtool_stats and
 * iavf_add_queue_stats. If the poपूर्णांकer is null, data will be zero'd.
 */
अटल व्योम
iavf_add_one_ethtool_stat(u64 *data, व्योम *poपूर्णांकer,
			  स्थिर काष्ठा iavf_stats *stat)
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
 * __iavf_add_ethtool_stats - copy stats पूर्णांकo the ethtool supplied buffer
 * @data: ethtool stats buffer
 * @poपूर्णांकer: location to copy stats from
 * @stats: array of stats to copy
 * @size: the size of the stats definition
 *
 * Copy the stats defined by the stats array using the poपूर्णांकer as a base पूर्णांकo
 * the data buffer supplied by ethtool. Updates the data poपूर्णांकer to poपूर्णांक to
 * the next empty location क्रम successive calls to __iavf_add_ethtool_stats.
 * If poपूर्णांकer is null, set the data values to zero and update the poपूर्णांकer to
 * skip these stats.
 **/
अटल व्योम
__iavf_add_ethtool_stats(u64 **data, व्योम *poपूर्णांकer,
			 स्थिर काष्ठा iavf_stats stats[],
			 स्थिर अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		iavf_add_one_ethtool_stat((*data)++, poपूर्णांकer, &stats[i]);
पूर्ण

/**
 * iavf_add_ethtool_stats - copy stats पूर्णांकo ethtool supplied buffer
 * @data: ethtool stats buffer
 * @poपूर्णांकer: location where stats are stored
 * @stats: अटल स्थिर array of stat definitions
 *
 * Macro to ease the use of __iavf_add_ethtool_stats by taking a अटल
 * स्थिरant stats array and passing the ARRAY_SIZE(). This aव्योमs typos by
 * ensuring that we pass the size associated with the given stats array.
 *
 * The parameter @stats is evaluated twice, so parameters with side effects
 * should be aव्योमed.
 **/
#घोषणा iavf_add_ethtool_stats(data, poपूर्णांकer, stats) \
	__iavf_add_ethtool_stats(data, poपूर्णांकer, stats, ARRAY_SIZE(stats))

/**
 * iavf_add_queue_stats - copy queue statistics पूर्णांकo supplied buffer
 * @data: ethtool stats buffer
 * @ring: the ring to copy
 *
 * Queue statistics must be copied जबतक रक्षित by
 * u64_stats_fetch_begin_irq, so we can't directly use iavf_add_ethtool_stats.
 * Assumes that queue stats are defined in iavf_gstrings_queue_stats. If the
 * ring poपूर्णांकer is null, zero out the queue stat values and update the data
 * poपूर्णांकer. Otherwise safely copy the stats from the ring पूर्णांकo the supplied
 * buffer and update the data poपूर्णांकer when finished.
 *
 * This function expects to be called जबतक under rcu_पढ़ो_lock().
 **/
अटल व्योम
iavf_add_queue_stats(u64 **data, काष्ठा iavf_ring *ring)
अणु
	स्थिर अचिन्हित पूर्णांक size = ARRAY_SIZE(iavf_gstrings_queue_stats);
	स्थिर काष्ठा iavf_stats *stats = iavf_gstrings_queue_stats;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक i;

	/* To aव्योम invalid statistics values, ensure that we keep retrying
	 * the copy until we get a consistent value according to
	 * u64_stats_fetch_retry_irq. But first, make sure our ring is
	 * non-null beक्रमe attempting to access its syncp.
	 */
	करो अणु
		start = !ring ? 0 : u64_stats_fetch_begin_irq(&ring->syncp);
		क्रम (i = 0; i < size; i++)
			iavf_add_one_ethtool_stat(&(*data)[i], ring, &stats[i]);
	पूर्ण जबतक (ring && u64_stats_fetch_retry_irq(&ring->syncp, start));

	/* Once we successfully copy the stats in, update the data poपूर्णांकer */
	*data += size;
पूर्ण

/**
 * __iavf_add_stat_strings - copy stat strings पूर्णांकo ethtool buffer
 * @p: ethtool supplied buffer
 * @stats: stat definitions array
 * @size: size of the stats array
 *
 * Format and copy the strings described by stats पूर्णांकo the buffer poपूर्णांकed at
 * by p.
 **/
अटल व्योम __iavf_add_stat_strings(u8 **p, स्थिर काष्ठा iavf_stats stats[],
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
 * iavf_add_stat_strings - copy stat strings पूर्णांकo ethtool buffer
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
#घोषणा iavf_add_stat_strings(p, stats, ...) \
	__iavf_add_stat_strings(p, stats, ARRAY_SIZE(stats), ## __VA_ARGS__)

#घोषणा VF_STAT(_name, _stat) \
	IAVF_STAT(काष्ठा iavf_adapter, _name, _stat)

अटल स्थिर काष्ठा iavf_stats iavf_gstrings_stats[] = अणु
	VF_STAT("rx_bytes", current_stats.rx_bytes),
	VF_STAT("rx_unicast", current_stats.rx_unicast),
	VF_STAT("rx_multicast", current_stats.rx_multicast),
	VF_STAT("rx_broadcast", current_stats.rx_broadcast),
	VF_STAT("rx_discards", current_stats.rx_discards),
	VF_STAT("rx_unknown_protocol", current_stats.rx_unknown_protocol),
	VF_STAT("tx_bytes", current_stats.tx_bytes),
	VF_STAT("tx_unicast", current_stats.tx_unicast),
	VF_STAT("tx_multicast", current_stats.tx_multicast),
	VF_STAT("tx_broadcast", current_stats.tx_broadcast),
	VF_STAT("tx_discards", current_stats.tx_discards),
	VF_STAT("tx_errors", current_stats.tx_errors),
पूर्ण;

#घोषणा IAVF_STATS_LEN	ARRAY_SIZE(iavf_gstrings_stats)

#घोषणा IAVF_QUEUE_STATS_LEN	ARRAY_SIZE(iavf_gstrings_queue_stats)

/* For now we have one and only one निजी flag and it is only defined
 * when we have support क्रम the SKIP_CPU_SYNC DMA attribute.  Instead
 * of leaving all this code sitting around empty we will strip it unless
 * our one निजी flag is actually available.
 */
काष्ठा iavf_priv_flags अणु
	अक्षर flag_string[ETH_GSTRING_LEN];
	u32 flag;
	bool पढ़ो_only;
पूर्ण;

#घोषणा IAVF_PRIV_FLAG(_name, _flag, _पढ़ो_only) अणु \
	.flag_string = _name, \
	.flag = _flag, \
	.पढ़ो_only = _पढ़ो_only, \
पूर्ण

अटल स्थिर काष्ठा iavf_priv_flags iavf_gstrings_priv_flags[] = अणु
	IAVF_PRIV_FLAG("legacy-rx", IAVF_FLAG_LEGACY_RX, 0),
पूर्ण;

#घोषणा IAVF_PRIV_FLAGS_STR_LEN ARRAY_SIZE(iavf_gstrings_priv_flags)

/**
 * iavf_get_link_ksettings - Get Link Speed and Duplex settings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool command
 *
 * Reports speed/duplex settings. Because this is a VF, we करोn't know what
 * kind of link we really have, so we fake it.
 **/
अटल पूर्णांक iavf_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	cmd->base.port = PORT_NONE;
	cmd->base.duplex = DUPLEX_FULL;

	अगर (ADV_LINK_SUPPORT(adapter)) अणु
		अगर (adapter->link_speed_mbps &&
		    adapter->link_speed_mbps < U32_MAX)
			cmd->base.speed = adapter->link_speed_mbps;
		अन्यथा
			cmd->base.speed = SPEED_UNKNOWN;

		वापस 0;
	पूर्ण

	चयन (adapter->link_speed) अणु
	हाल VIRTCHNL_LINK_SPEED_40GB:
		cmd->base.speed = SPEED_40000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_25GB:
		cmd->base.speed = SPEED_25000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_20GB:
		cmd->base.speed = SPEED_20000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_10GB:
		cmd->base.speed = SPEED_10000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_5GB:
		cmd->base.speed = SPEED_5000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_2_5GB:
		cmd->base.speed = SPEED_2500;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_1GB:
		cmd->base.speed = SPEED_1000;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_100MB:
		cmd->base.speed = SPEED_100;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_get_sset_count - Get length of string set
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @sset: id of string set
 *
 * Reports size of various string tables.
 **/
अटल पूर्णांक iavf_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस IAVF_STATS_LEN +
			(IAVF_QUEUE_STATS_LEN * 2 * IAVF_MAX_REQ_QUEUES);
	अन्यथा अगर (sset == ETH_SS_PRIV_FLAGS)
		वापस IAVF_PRIV_FLAGS_STR_LEN;
	अन्यथा
		वापस -EINVAL;
पूर्ण

/**
 * iavf_get_ethtool_stats - report device statistics
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @stats: ethtool statistics काष्ठाure
 * @data: poपूर्णांकer to data buffer
 *
 * All statistics are added to the data buffer as an array of u64.
 **/
अटल व्योम iavf_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक i;

	iavf_add_ethtool_stats(&data, adapter, iavf_gstrings_stats);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < IAVF_MAX_REQ_QUEUES; i++) अणु
		काष्ठा iavf_ring *ring;

		/* Aव्योम accessing un-allocated queues */
		ring = (i < adapter->num_active_queues ?
			&adapter->tx_rings[i] : शून्य);
		iavf_add_queue_stats(&data, ring);

		/* Aव्योम accessing un-allocated queues */
		ring = (i < adapter->num_active_queues ?
			&adapter->rx_rings[i] : शून्य);
		iavf_add_queue_stats(&data, ring);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * iavf_get_priv_flag_strings - Get निजी flag strings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @data: buffer क्रम string data
 *
 * Builds the निजी flags string table
 **/
अटल व्योम iavf_get_priv_flag_strings(काष्ठा net_device *netdev, u8 *data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IAVF_PRIV_FLAGS_STR_LEN; i++) अणु
		snम_लिखो(data, ETH_GSTRING_LEN, "%s",
			 iavf_gstrings_priv_flags[i].flag_string);
		data += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

/**
 * iavf_get_stat_strings - Get stat strings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @data: buffer क्रम string data
 *
 * Builds the statistics string table
 **/
अटल व्योम iavf_get_stat_strings(काष्ठा net_device *netdev, u8 *data)
अणु
	अचिन्हित पूर्णांक i;

	iavf_add_stat_strings(&data, iavf_gstrings_stats);

	/* Queues are always allocated in pairs, so we just use num_tx_queues
	 * क्रम both Tx and Rx queues.
	 */
	क्रम (i = 0; i < netdev->num_tx_queues; i++) अणु
		iavf_add_stat_strings(&data, iavf_gstrings_queue_stats,
				      "tx", i);
		iavf_add_stat_strings(&data, iavf_gstrings_queue_stats,
				      "rx", i);
	पूर्ण
पूर्ण

/**
 * iavf_get_strings - Get string set
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @sset: id of string set
 * @data: buffer क्रम string data
 *
 * Builds string tables क्रम various string sets
 **/
अटल व्योम iavf_get_strings(काष्ठा net_device *netdev, u32 sset, u8 *data)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		iavf_get_stat_strings(netdev, data);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		iavf_get_priv_flag_strings(netdev, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * iavf_get_priv_flags - report device निजी flags
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The get string set count and the string set should be matched क्रम each
 * flag वापसed.  Add new strings क्रम each flag to the iavf_gstrings_priv_flags
 * array.
 *
 * Returns a u32 biपंचांगap of flags.
 **/
अटल u32 iavf_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u32 i, ret_flags = 0;

	क्रम (i = 0; i < IAVF_PRIV_FLAGS_STR_LEN; i++) अणु
		स्थिर काष्ठा iavf_priv_flags *priv_flags;

		priv_flags = &iavf_gstrings_priv_flags[i];

		अगर (priv_flags->flag & adapter->flags)
			ret_flags |= BIT(i);
	पूर्ण

	वापस ret_flags;
पूर्ण

/**
 * iavf_set_priv_flags - set निजी flags
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @flags: bit flags to be set
 **/
अटल पूर्णांक iavf_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u32 orig_flags, new_flags, changed_flags;
	u32 i;

	orig_flags = READ_ONCE(adapter->flags);
	new_flags = orig_flags;

	क्रम (i = 0; i < IAVF_PRIV_FLAGS_STR_LEN; i++) अणु
		स्थिर काष्ठा iavf_priv_flags *priv_flags;

		priv_flags = &iavf_gstrings_priv_flags[i];

		अगर (flags & BIT(i))
			new_flags |= priv_flags->flag;
		अन्यथा
			new_flags &= ~(priv_flags->flag);

		अगर (priv_flags->पढ़ो_only &&
		    ((orig_flags ^ new_flags) & ~BIT(i)))
			वापस -EOPNOTSUPP;
	पूर्ण

	/* Beक्रमe we finalize any flag changes, any checks which we need to
	 * perक्रमm to determine अगर the new flags will be supported should go
	 * here...
	 */

	/* Compare and exchange the new flags पूर्णांकo place. If we failed, that
	 * is अगर cmpxchg वापसs anything but the old value, this means
	 * something अन्यथा must have modअगरied the flags variable since we
	 * copied it. We'll just punt with an error and log something in the
	 * message buffer.
	 */
	अगर (cmpxchg(&adapter->flags, orig_flags, new_flags) != orig_flags) अणु
		dev_warn(&adapter->pdev->dev,
			 "Unable to update adapter->flags as it was modified by another thread...\n");
		वापस -EAGAIN;
	पूर्ण

	changed_flags = orig_flags ^ new_flags;

	/* Process any additional changes needed as a result of flag changes.
	 * The changed_flags value reflects the list of bits that were changed
	 * in the code above.
	 */

	/* issue a reset to क्रमce legacy-rx change to take effect */
	अगर (changed_flags & IAVF_FLAG_LEGACY_RX) अणु
		अगर (netअगर_running(netdev)) अणु
			adapter->flags |= IAVF_FLAG_RESET_NEEDED;
			queue_work(iavf_wq, &adapter->reset_task);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_get_msglevel - Get debug message level
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns current debug message level.
 **/
अटल u32 iavf_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

/**
 * iavf_set_msglevel - Set debug message level
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @data: message level
 *
 * Set current debug message level. Higher values cause the driver to
 * be noisier.
 **/
अटल व्योम iavf_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	अगर (IAVF_DEBUG_USER & data)
		adapter->hw.debug_mask = data;
	adapter->msg_enable = data;
पूर्ण

/**
 * iavf_get_drvinfo - Get driver info
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @drvinfo: ethool driver info काष्ठाure
 *
 * Returns inक्रमmation about the driver and device क्रम display to the user.
 **/
अटल व्योम iavf_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, iavf_driver_name, 32);
	strlcpy(drvinfo->fw_version, "N/A", 4);
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev), 32);
	drvinfo->n_priv_flags = IAVF_PRIV_FLAGS_STR_LEN;
पूर्ण

/**
 * iavf_get_ringparam - Get ring parameters
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ring: ethtool ringparam काष्ठाure
 *
 * Returns current ring parameters. TX and RX rings are reported separately,
 * but the number of rings is not reported.
 **/
अटल व्योम iavf_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = IAVF_MAX_RXD;
	ring->tx_max_pending = IAVF_MAX_TXD;
	ring->rx_pending = adapter->rx_desc_count;
	ring->tx_pending = adapter->tx_desc_count;
पूर्ण

/**
 * iavf_set_ringparam - Set ring parameters
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ring: ethtool ringparam काष्ठाure
 *
 * Sets ring parameters. TX and RX rings are controlled separately, but the
 * number of rings is not specअगरied, so all rings get the same settings.
 **/
अटल पूर्णांक iavf_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u32 new_rx_count, new_tx_count;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_tx_count = clamp_t(u32, ring->tx_pending,
			       IAVF_MIN_TXD,
			       IAVF_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, IAVF_REQ_DESCRIPTOR_MULTIPLE);

	new_rx_count = clamp_t(u32, ring->rx_pending,
			       IAVF_MIN_RXD,
			       IAVF_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, IAVF_REQ_DESCRIPTOR_MULTIPLE);

	/* अगर nothing to करो वापस success */
	अगर ((new_tx_count == adapter->tx_desc_count) &&
	    (new_rx_count == adapter->rx_desc_count))
		वापस 0;

	adapter->tx_desc_count = new_tx_count;
	adapter->rx_desc_count = new_rx_count;

	अगर (netअगर_running(netdev)) अणु
		adapter->flags |= IAVF_FLAG_RESET_NEEDED;
		queue_work(iavf_wq, &adapter->reset_task);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __iavf_get_coalesce - get per-queue coalesce settings
 * @netdev: the netdev to check
 * @ec: ethtool coalesce data काष्ठाure
 * @queue: which queue to pick
 *
 * Gets the per-queue settings क्रम coalescence. Specअगरically Rx and Tx usecs
 * are per queue. If queue is <0 then we शेष to queue 0 as the
 * representative value.
 **/
अटल पूर्णांक __iavf_get_coalesce(काष्ठा net_device *netdev,
			       काष्ठा ethtool_coalesce *ec, पूर्णांक queue)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_vsi *vsi = &adapter->vsi;
	काष्ठा iavf_ring *rx_ring, *tx_ring;

	ec->tx_max_coalesced_frames = vsi->work_limit;
	ec->rx_max_coalesced_frames = vsi->work_limit;

	/* Rx and Tx usecs per queue value. If user करोesn't specअगरy the
	 * queue, वापस queue 0's value to represent.
	 */
	अगर (queue < 0)
		queue = 0;
	अन्यथा अगर (queue >= adapter->num_active_queues)
		वापस -EINVAL;

	rx_ring = &adapter->rx_rings[queue];
	tx_ring = &adapter->tx_rings[queue];

	अगर (ITR_IS_DYNAMIC(rx_ring->itr_setting))
		ec->use_adaptive_rx_coalesce = 1;

	अगर (ITR_IS_DYNAMIC(tx_ring->itr_setting))
		ec->use_adaptive_tx_coalesce = 1;

	ec->rx_coalesce_usecs = rx_ring->itr_setting & ~IAVF_ITR_DYNAMIC;
	ec->tx_coalesce_usecs = tx_ring->itr_setting & ~IAVF_ITR_DYNAMIC;

	वापस 0;
पूर्ण

/**
 * iavf_get_coalesce - Get पूर्णांकerrupt coalescing settings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ec: ethtool coalesce काष्ठाure
 *
 * Returns current coalescing settings. This is referred to अन्यथाwhere in the
 * driver as Interrupt Throttle Rate, as this is how the hardware describes
 * this functionality. Note that अगर per-queue settings have been modअगरied this
 * only represents the settings of queue 0.
 **/
अटल पूर्णांक iavf_get_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	वापस __iavf_get_coalesce(netdev, ec, -1);
पूर्ण

/**
 * iavf_get_per_queue_coalesce - get coalesce values क्रम specअगरic queue
 * @netdev: netdev to पढ़ो
 * @ec: coalesce settings from ethtool
 * @queue: the queue to पढ़ो
 *
 * Read specअगरic queue's coalesce settings.
 **/
अटल पूर्णांक iavf_get_per_queue_coalesce(काष्ठा net_device *netdev, u32 queue,
				       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __iavf_get_coalesce(netdev, ec, queue);
पूर्ण

/**
 * iavf_set_itr_per_queue - set ITR values क्रम specअगरic queue
 * @adapter: the VF adapter काष्ठा to set values क्रम
 * @ec: coalesce settings from ethtool
 * @queue: the queue to modअगरy
 *
 * Change the ITR settings क्रम a specअगरic queue.
 **/
अटल व्योम iavf_set_itr_per_queue(काष्ठा iavf_adapter *adapter,
				   काष्ठा ethtool_coalesce *ec, पूर्णांक queue)
अणु
	काष्ठा iavf_ring *rx_ring = &adapter->rx_rings[queue];
	काष्ठा iavf_ring *tx_ring = &adapter->tx_rings[queue];
	काष्ठा iavf_q_vector *q_vector;

	rx_ring->itr_setting = ITR_REG_ALIGN(ec->rx_coalesce_usecs);
	tx_ring->itr_setting = ITR_REG_ALIGN(ec->tx_coalesce_usecs);

	rx_ring->itr_setting |= IAVF_ITR_DYNAMIC;
	अगर (!ec->use_adaptive_rx_coalesce)
		rx_ring->itr_setting ^= IAVF_ITR_DYNAMIC;

	tx_ring->itr_setting |= IAVF_ITR_DYNAMIC;
	अगर (!ec->use_adaptive_tx_coalesce)
		tx_ring->itr_setting ^= IAVF_ITR_DYNAMIC;

	q_vector = rx_ring->q_vector;
	q_vector->rx.target_itr = ITR_TO_REG(rx_ring->itr_setting);

	q_vector = tx_ring->q_vector;
	q_vector->tx.target_itr = ITR_TO_REG(tx_ring->itr_setting);

	/* The पूर्णांकerrupt handler itself will take care of programming
	 * the Tx and Rx ITR values based on the values we have entered
	 * पूर्णांकo the q_vector, no need to ग_लिखो the values now.
	 */
पूर्ण

/**
 * __iavf_set_coalesce - set coalesce settings क्रम particular queue
 * @netdev: the netdev to change
 * @ec: ethtool coalesce settings
 * @queue: the queue to change
 *
 * Sets the coalesce settings क्रम a particular queue.
 **/
अटल पूर्णांक __iavf_set_coalesce(काष्ठा net_device *netdev,
			       काष्ठा ethtool_coalesce *ec, पूर्णांक queue)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_vsi *vsi = &adapter->vsi;
	पूर्णांक i;

	अगर (ec->tx_max_coalesced_frames_irq || ec->rx_max_coalesced_frames_irq)
		vsi->work_limit = ec->tx_max_coalesced_frames_irq;

	अगर (ec->rx_coalesce_usecs == 0) अणु
		अगर (ec->use_adaptive_rx_coalesce)
			netअगर_info(adapter, drv, netdev, "rx-usecs=0, need to disable adaptive-rx for a complete disable\n");
	पूर्ण अन्यथा अगर ((ec->rx_coalesce_usecs < IAVF_MIN_ITR) ||
		   (ec->rx_coalesce_usecs > IAVF_MAX_ITR)) अणु
		netअगर_info(adapter, drv, netdev, "Invalid value, rx-usecs range is 0-8160\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ec->tx_coalesce_usecs == 0) अणु
		अगर (ec->use_adaptive_tx_coalesce)
			netअगर_info(adapter, drv, netdev, "tx-usecs=0, need to disable adaptive-tx for a complete disable\n");
	पूर्ण अन्यथा अगर ((ec->tx_coalesce_usecs < IAVF_MIN_ITR) ||
		   (ec->tx_coalesce_usecs > IAVF_MAX_ITR)) अणु
		netअगर_info(adapter, drv, netdev, "Invalid value, tx-usecs range is 0-8160\n");
		वापस -EINVAL;
	पूर्ण

	/* Rx and Tx usecs has per queue value. If user करोesn't specअगरy the
	 * queue, apply to all queues.
	 */
	अगर (queue < 0) अणु
		क्रम (i = 0; i < adapter->num_active_queues; i++)
			iavf_set_itr_per_queue(adapter, ec, i);
	पूर्ण अन्यथा अगर (queue < adapter->num_active_queues) अणु
		iavf_set_itr_per_queue(adapter, ec, queue);
	पूर्ण अन्यथा अणु
		netअगर_info(adapter, drv, netdev, "Invalid queue value, queue range is 0 - %d\n",
			   adapter->num_active_queues - 1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iavf_set_coalesce - Set पूर्णांकerrupt coalescing settings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ec: ethtool coalesce काष्ठाure
 *
 * Change current coalescing settings क्रम every queue.
 **/
अटल पूर्णांक iavf_set_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	वापस __iavf_set_coalesce(netdev, ec, -1);
पूर्ण

/**
 * iavf_set_per_queue_coalesce - set specअगरic queue's coalesce settings
 * @netdev: the netdev to change
 * @ec: ethtool's coalesce settings
 * @queue: the queue to modअगरy
 *
 * Modअगरies a specअगरic queue's coalesce settings.
 */
अटल पूर्णांक iavf_set_per_queue_coalesce(काष्ठा net_device *netdev, u32 queue,
				       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __iavf_set_coalesce(netdev, ec, queue);
पूर्ण

/**
 * iavf_fltr_to_ethtool_flow - convert filter type values to ethtool
 * flow type values
 * @flow: filter type to be converted
 *
 * Returns the corresponding ethtool flow type.
 */
अटल पूर्णांक iavf_fltr_to_ethtool_flow(क्रमागत iavf_fdir_flow_type flow)
अणु
	चयन (flow) अणु
	हाल IAVF_Fसूची_FLOW_IPV4_TCP:
		वापस TCP_V4_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV4_UDP:
		वापस UDP_V4_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV4_SCTP:
		वापस SCTP_V4_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV4_AH:
		वापस AH_V4_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV4_ESP:
		वापस ESP_V4_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV4_OTHER:
		वापस IPV4_USER_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV6_TCP:
		वापस TCP_V6_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV6_UDP:
		वापस UDP_V6_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV6_SCTP:
		वापस SCTP_V6_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV6_AH:
		वापस AH_V6_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV6_ESP:
		वापस ESP_V6_FLOW;
	हाल IAVF_Fसूची_FLOW_IPV6_OTHER:
		वापस IPV6_USER_FLOW;
	हाल IAVF_Fसूची_FLOW_NON_IP_L2:
		वापस ETHER_FLOW;
	शेष:
		/* 0 is undefined ethtool flow */
		वापस 0;
	पूर्ण
पूर्ण

/**
 * iavf_ethtool_flow_to_fltr - convert ethtool flow type to filter क्रमागत
 * @eth: Ethtool flow type to be converted
 *
 * Returns flow क्रमागत
 */
अटल क्रमागत iavf_fdir_flow_type iavf_ethtool_flow_to_fltr(पूर्णांक eth)
अणु
	चयन (eth) अणु
	हाल TCP_V4_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV4_TCP;
	हाल UDP_V4_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV4_UDP;
	हाल SCTP_V4_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV4_SCTP;
	हाल AH_V4_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV4_AH;
	हाल ESP_V4_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV4_ESP;
	हाल IPV4_USER_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV4_OTHER;
	हाल TCP_V6_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV6_TCP;
	हाल UDP_V6_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV6_UDP;
	हाल SCTP_V6_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV6_SCTP;
	हाल AH_V6_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV6_AH;
	हाल ESP_V6_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV6_ESP;
	हाल IPV6_USER_FLOW:
		वापस IAVF_Fसूची_FLOW_IPV6_OTHER;
	हाल ETHER_FLOW:
		वापस IAVF_Fसूची_FLOW_NON_IP_L2;
	शेष:
		वापस IAVF_Fसूची_FLOW_NONE;
	पूर्ण
पूर्ण

/**
 * iavf_is_mask_valid - check mask field set
 * @mask: full mask to check
 * @field: field क्रम which mask should be valid
 *
 * If the mask is fully set वापस true. If it is not valid क्रम field वापस
 * false.
 */
अटल bool iavf_is_mask_valid(u64 mask, u64 field)
अणु
	वापस (mask & field) == field;
पूर्ण

/**
 * iavf_parse_rx_flow_user_data - deस्थिरruct user-defined data
 * @fsp: poपूर्णांकer to ethtool Rx flow specअगरication
 * @fltr: poपूर्णांकer to Flow Director filter क्रम userdef data storage
 *
 * Returns 0 on success, negative error value on failure
 */
अटल पूर्णांक
iavf_parse_rx_flow_user_data(काष्ठा ethtool_rx_flow_spec *fsp,
			     काष्ठा iavf_fdir_fltr *fltr)
अणु
	काष्ठा iavf_flex_word *flex;
	पूर्णांक i, cnt = 0;

	अगर (!(fsp->flow_type & FLOW_EXT))
		वापस 0;

	क्रम (i = 0; i < IAVF_FLEX_WORD_NUM; i++) अणु
#घोषणा IAVF_USERDEF_FLEX_WORD_M	GENMASK(15, 0)
#घोषणा IAVF_USERDEF_FLEX_OFFS_S	16
#घोषणा IAVF_USERDEF_FLEX_OFFS_M	GENMASK(31, IAVF_USERDEF_FLEX_OFFS_S)
#घोषणा IAVF_USERDEF_FLEX_FLTR_M	GENMASK(31, 0)
		u32 value = be32_to_cpu(fsp->h_ext.data[i]);
		u32 mask = be32_to_cpu(fsp->m_ext.data[i]);

		अगर (!value || !mask)
			जारी;

		अगर (!iavf_is_mask_valid(mask, IAVF_USERDEF_FLEX_FLTR_M))
			वापस -EINVAL;

		/* 504 is the maximum value क्रम offsets, and offset is measured
		 * from the start of the MAC address.
		 */
#घोषणा IAVF_USERDEF_FLEX_MAX_OFFS_VAL 504
		flex = &fltr->flex_words[cnt++];
		flex->word = value & IAVF_USERDEF_FLEX_WORD_M;
		flex->offset = (value & IAVF_USERDEF_FLEX_OFFS_M) >>
			     IAVF_USERDEF_FLEX_OFFS_S;
		अगर (flex->offset > IAVF_USERDEF_FLEX_MAX_OFFS_VAL)
			वापस -EINVAL;
	पूर्ण

	fltr->flex_cnt = cnt;

	वापस 0;
पूर्ण

/**
 * iavf_fill_rx_flow_ext_data - fill the additional data
 * @fsp: poपूर्णांकer to ethtool Rx flow specअगरication
 * @fltr: poपूर्णांकer to Flow Director filter to get additional data
 */
अटल व्योम
iavf_fill_rx_flow_ext_data(काष्ठा ethtool_rx_flow_spec *fsp,
			   काष्ठा iavf_fdir_fltr *fltr)
अणु
	अगर (!fltr->ext_mask.usr_def[0] && !fltr->ext_mask.usr_def[1])
		वापस;

	fsp->flow_type |= FLOW_EXT;

	स_नकल(fsp->h_ext.data, fltr->ext_data.usr_def, माप(fsp->h_ext.data));
	स_नकल(fsp->m_ext.data, fltr->ext_mask.usr_def, माप(fsp->m_ext.data));
पूर्ण

/**
 * iavf_get_ethtool_fdir_entry - fill ethtool काष्ठाure with Flow Director filter data
 * @adapter: the VF adapter काष्ठाure that contains filter list
 * @cmd: ethtool command data काष्ठाure to receive the filter data
 *
 * Returns 0 as expected क्रम success by ethtool
 */
अटल पूर्णांक
iavf_get_ethtool_fdir_entry(काष्ठा iavf_adapter *adapter,
			    काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा iavf_fdir_fltr *rule = शून्य;
	पूर्णांक ret = 0;

	अगर (!Fसूची_FLTR_SUPPORT(adapter))
		वापस -EOPNOTSUPP;

	spin_lock_bh(&adapter->fdir_fltr_lock);

	rule = iavf_find_fdir_fltr_by_loc(adapter, fsp->location);
	अगर (!rule) अणु
		ret = -EINVAL;
		जाओ release_lock;
	पूर्ण

	fsp->flow_type = iavf_fltr_to_ethtool_flow(rule->flow_type);

	स_रखो(&fsp->m_u, 0, माप(fsp->m_u));
	स_रखो(&fsp->m_ext, 0, माप(fsp->m_ext));

	चयन (fsp->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		fsp->h_u.tcp_ip4_spec.ip4src = rule->ip_data.v4_addrs.src_ip;
		fsp->h_u.tcp_ip4_spec.ip4dst = rule->ip_data.v4_addrs.dst_ip;
		fsp->h_u.tcp_ip4_spec.psrc = rule->ip_data.src_port;
		fsp->h_u.tcp_ip4_spec.pdst = rule->ip_data.dst_port;
		fsp->h_u.tcp_ip4_spec.tos = rule->ip_data.tos;
		fsp->m_u.tcp_ip4_spec.ip4src = rule->ip_mask.v4_addrs.src_ip;
		fsp->m_u.tcp_ip4_spec.ip4dst = rule->ip_mask.v4_addrs.dst_ip;
		fsp->m_u.tcp_ip4_spec.psrc = rule->ip_mask.src_port;
		fsp->m_u.tcp_ip4_spec.pdst = rule->ip_mask.dst_port;
		fsp->m_u.tcp_ip4_spec.tos = rule->ip_mask.tos;
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		fsp->h_u.ah_ip4_spec.ip4src = rule->ip_data.v4_addrs.src_ip;
		fsp->h_u.ah_ip4_spec.ip4dst = rule->ip_data.v4_addrs.dst_ip;
		fsp->h_u.ah_ip4_spec.spi = rule->ip_data.spi;
		fsp->h_u.ah_ip4_spec.tos = rule->ip_data.tos;
		fsp->m_u.ah_ip4_spec.ip4src = rule->ip_mask.v4_addrs.src_ip;
		fsp->m_u.ah_ip4_spec.ip4dst = rule->ip_mask.v4_addrs.dst_ip;
		fsp->m_u.ah_ip4_spec.spi = rule->ip_mask.spi;
		fsp->m_u.ah_ip4_spec.tos = rule->ip_mask.tos;
		अवरोध;
	हाल IPV4_USER_FLOW:
		fsp->h_u.usr_ip4_spec.ip4src = rule->ip_data.v4_addrs.src_ip;
		fsp->h_u.usr_ip4_spec.ip4dst = rule->ip_data.v4_addrs.dst_ip;
		fsp->h_u.usr_ip4_spec.l4_4_bytes = rule->ip_data.l4_header;
		fsp->h_u.usr_ip4_spec.tos = rule->ip_data.tos;
		fsp->h_u.usr_ip4_spec.ip_ver = ETH_RX_NFC_IP4;
		fsp->h_u.usr_ip4_spec.proto = rule->ip_data.proto;
		fsp->m_u.usr_ip4_spec.ip4src = rule->ip_mask.v4_addrs.src_ip;
		fsp->m_u.usr_ip4_spec.ip4dst = rule->ip_mask.v4_addrs.dst_ip;
		fsp->m_u.usr_ip4_spec.l4_4_bytes = rule->ip_mask.l4_header;
		fsp->m_u.usr_ip4_spec.tos = rule->ip_mask.tos;
		fsp->m_u.usr_ip4_spec.ip_ver = 0xFF;
		fsp->m_u.usr_ip4_spec.proto = rule->ip_mask.proto;
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		स_नकल(fsp->h_u.usr_ip6_spec.ip6src, &rule->ip_data.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->h_u.usr_ip6_spec.ip6dst, &rule->ip_data.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->h_u.tcp_ip6_spec.psrc = rule->ip_data.src_port;
		fsp->h_u.tcp_ip6_spec.pdst = rule->ip_data.dst_port;
		fsp->h_u.tcp_ip6_spec.tclass = rule->ip_data.tclass;
		स_नकल(fsp->m_u.usr_ip6_spec.ip6src, &rule->ip_mask.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->m_u.usr_ip6_spec.ip6dst, &rule->ip_mask.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->m_u.tcp_ip6_spec.psrc = rule->ip_mask.src_port;
		fsp->m_u.tcp_ip6_spec.pdst = rule->ip_mask.dst_port;
		fsp->m_u.tcp_ip6_spec.tclass = rule->ip_mask.tclass;
		अवरोध;
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		स_नकल(fsp->h_u.ah_ip6_spec.ip6src, &rule->ip_data.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->h_u.ah_ip6_spec.ip6dst, &rule->ip_data.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->h_u.ah_ip6_spec.spi = rule->ip_data.spi;
		fsp->h_u.ah_ip6_spec.tclass = rule->ip_data.tclass;
		स_नकल(fsp->m_u.ah_ip6_spec.ip6src, &rule->ip_mask.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->m_u.ah_ip6_spec.ip6dst, &rule->ip_mask.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->m_u.ah_ip6_spec.spi = rule->ip_mask.spi;
		fsp->m_u.ah_ip6_spec.tclass = rule->ip_mask.tclass;
		अवरोध;
	हाल IPV6_USER_FLOW:
		स_नकल(fsp->h_u.usr_ip6_spec.ip6src, &rule->ip_data.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->h_u.usr_ip6_spec.ip6dst, &rule->ip_data.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->h_u.usr_ip6_spec.l4_4_bytes = rule->ip_data.l4_header;
		fsp->h_u.usr_ip6_spec.tclass = rule->ip_data.tclass;
		fsp->h_u.usr_ip6_spec.l4_proto = rule->ip_data.proto;
		स_नकल(fsp->m_u.usr_ip6_spec.ip6src, &rule->ip_mask.v6_addrs.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->m_u.usr_ip6_spec.ip6dst, &rule->ip_mask.v6_addrs.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->m_u.usr_ip6_spec.l4_4_bytes = rule->ip_mask.l4_header;
		fsp->m_u.usr_ip6_spec.tclass = rule->ip_mask.tclass;
		fsp->m_u.usr_ip6_spec.l4_proto = rule->ip_mask.proto;
		अवरोध;
	हाल ETHER_FLOW:
		fsp->h_u.ether_spec.h_proto = rule->eth_data.etype;
		fsp->m_u.ether_spec.h_proto = rule->eth_mask.etype;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iavf_fill_rx_flow_ext_data(fsp, rule);

	अगर (rule->action == VIRTCHNL_ACTION_DROP)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		fsp->ring_cookie = rule->q_index;

release_lock:
	spin_unlock_bh(&adapter->fdir_fltr_lock);
	वापस ret;
पूर्ण

/**
 * iavf_get_fdir_fltr_ids - fill buffer with filter IDs of active filters
 * @adapter: the VF adapter काष्ठाure containing the filter list
 * @cmd: ethtool command data काष्ठाure
 * @rule_locs: ethtool array passed in from OS to receive filter IDs
 *
 * Returns 0 as expected क्रम success by ethtool
 */
अटल पूर्णांक
iavf_get_fdir_fltr_ids(काष्ठा iavf_adapter *adapter, काष्ठा ethtool_rxnfc *cmd,
		       u32 *rule_locs)
अणु
	काष्ठा iavf_fdir_fltr *fltr;
	अचिन्हित पूर्णांक cnt = 0;
	पूर्णांक val = 0;

	अगर (!Fसूची_FLTR_SUPPORT(adapter))
		वापस -EOPNOTSUPP;

	cmd->data = IAVF_MAX_Fसूची_FILTERS;

	spin_lock_bh(&adapter->fdir_fltr_lock);

	list_क्रम_each_entry(fltr, &adapter->fdir_list_head, list) अणु
		अगर (cnt == cmd->rule_cnt) अणु
			val = -EMSGSIZE;
			जाओ release_lock;
		पूर्ण
		rule_locs[cnt] = fltr->loc;
		cnt++;
	पूर्ण

release_lock:
	spin_unlock_bh(&adapter->fdir_fltr_lock);
	अगर (!val)
		cmd->rule_cnt = cnt;

	वापस val;
पूर्ण

/**
 * iavf_add_fdir_fltr_info - Set the input set क्रम Flow Director filter
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @fsp: poपूर्णांकer to ethtool Rx flow specअगरication
 * @fltr: filter काष्ठाure
 */
अटल पूर्णांक
iavf_add_fdir_fltr_info(काष्ठा iavf_adapter *adapter, काष्ठा ethtool_rx_flow_spec *fsp,
			काष्ठा iavf_fdir_fltr *fltr)
अणु
	u32 flow_type, q_index = 0;
	क्रमागत virtchnl_action act;
	पूर्णांक err;

	अगर (fsp->ring_cookie == RX_CLS_FLOW_DISC) अणु
		act = VIRTCHNL_ACTION_DROP;
	पूर्ण अन्यथा अणु
		q_index = fsp->ring_cookie;
		अगर (q_index >= adapter->num_active_queues)
			वापस -EINVAL;

		act = VIRTCHNL_ACTION_QUEUE;
	पूर्ण

	fltr->action = act;
	fltr->loc = fsp->location;
	fltr->q_index = q_index;

	अगर (fsp->flow_type & FLOW_EXT) अणु
		स_नकल(fltr->ext_data.usr_def, fsp->h_ext.data,
		       माप(fltr->ext_data.usr_def));
		स_नकल(fltr->ext_mask.usr_def, fsp->m_ext.data,
		       माप(fltr->ext_mask.usr_def));
	पूर्ण

	flow_type = fsp->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT | FLOW_RSS);
	fltr->flow_type = iavf_ethtool_flow_to_fltr(flow_type);

	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		fltr->ip_data.v4_addrs.src_ip = fsp->h_u.tcp_ip4_spec.ip4src;
		fltr->ip_data.v4_addrs.dst_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
		fltr->ip_data.src_port = fsp->h_u.tcp_ip4_spec.psrc;
		fltr->ip_data.dst_port = fsp->h_u.tcp_ip4_spec.pdst;
		fltr->ip_data.tos = fsp->h_u.tcp_ip4_spec.tos;
		fltr->ip_mask.v4_addrs.src_ip = fsp->m_u.tcp_ip4_spec.ip4src;
		fltr->ip_mask.v4_addrs.dst_ip = fsp->m_u.tcp_ip4_spec.ip4dst;
		fltr->ip_mask.src_port = fsp->m_u.tcp_ip4_spec.psrc;
		fltr->ip_mask.dst_port = fsp->m_u.tcp_ip4_spec.pdst;
		fltr->ip_mask.tos = fsp->m_u.tcp_ip4_spec.tos;
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		fltr->ip_data.v4_addrs.src_ip = fsp->h_u.ah_ip4_spec.ip4src;
		fltr->ip_data.v4_addrs.dst_ip = fsp->h_u.ah_ip4_spec.ip4dst;
		fltr->ip_data.spi = fsp->h_u.ah_ip4_spec.spi;
		fltr->ip_data.tos = fsp->h_u.ah_ip4_spec.tos;
		fltr->ip_mask.v4_addrs.src_ip = fsp->m_u.ah_ip4_spec.ip4src;
		fltr->ip_mask.v4_addrs.dst_ip = fsp->m_u.ah_ip4_spec.ip4dst;
		fltr->ip_mask.spi = fsp->m_u.ah_ip4_spec.spi;
		fltr->ip_mask.tos = fsp->m_u.ah_ip4_spec.tos;
		अवरोध;
	हाल IPV4_USER_FLOW:
		fltr->ip_data.v4_addrs.src_ip = fsp->h_u.usr_ip4_spec.ip4src;
		fltr->ip_data.v4_addrs.dst_ip = fsp->h_u.usr_ip4_spec.ip4dst;
		fltr->ip_data.l4_header = fsp->h_u.usr_ip4_spec.l4_4_bytes;
		fltr->ip_data.tos = fsp->h_u.usr_ip4_spec.tos;
		fltr->ip_data.proto = fsp->h_u.usr_ip4_spec.proto;
		fltr->ip_mask.v4_addrs.src_ip = fsp->m_u.usr_ip4_spec.ip4src;
		fltr->ip_mask.v4_addrs.dst_ip = fsp->m_u.usr_ip4_spec.ip4dst;
		fltr->ip_mask.l4_header = fsp->m_u.usr_ip4_spec.l4_4_bytes;
		fltr->ip_mask.tos = fsp->m_u.usr_ip4_spec.tos;
		fltr->ip_mask.proto = fsp->m_u.usr_ip4_spec.proto;
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		स_नकल(&fltr->ip_data.v6_addrs.src_ip, fsp->h_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr->ip_data.v6_addrs.dst_ip, fsp->h_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		fltr->ip_data.src_port = fsp->h_u.tcp_ip6_spec.psrc;
		fltr->ip_data.dst_port = fsp->h_u.tcp_ip6_spec.pdst;
		fltr->ip_data.tclass = fsp->h_u.tcp_ip6_spec.tclass;
		स_नकल(&fltr->ip_mask.v6_addrs.src_ip, fsp->m_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr->ip_mask.v6_addrs.dst_ip, fsp->m_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		fltr->ip_mask.src_port = fsp->m_u.tcp_ip6_spec.psrc;
		fltr->ip_mask.dst_port = fsp->m_u.tcp_ip6_spec.pdst;
		fltr->ip_mask.tclass = fsp->m_u.tcp_ip6_spec.tclass;
		अवरोध;
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
		स_नकल(&fltr->ip_data.v6_addrs.src_ip, fsp->h_u.ah_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr->ip_data.v6_addrs.dst_ip, fsp->h_u.ah_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		fltr->ip_data.spi = fsp->h_u.ah_ip6_spec.spi;
		fltr->ip_data.tclass = fsp->h_u.ah_ip6_spec.tclass;
		स_नकल(&fltr->ip_mask.v6_addrs.src_ip, fsp->m_u.ah_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr->ip_mask.v6_addrs.dst_ip, fsp->m_u.ah_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		fltr->ip_mask.spi = fsp->m_u.ah_ip6_spec.spi;
		fltr->ip_mask.tclass = fsp->m_u.ah_ip6_spec.tclass;
		अवरोध;
	हाल IPV6_USER_FLOW:
		स_नकल(&fltr->ip_data.v6_addrs.src_ip, fsp->h_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr->ip_data.v6_addrs.dst_ip, fsp->h_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		fltr->ip_data.l4_header = fsp->h_u.usr_ip6_spec.l4_4_bytes;
		fltr->ip_data.tclass = fsp->h_u.usr_ip6_spec.tclass;
		fltr->ip_data.proto = fsp->h_u.usr_ip6_spec.l4_proto;
		स_नकल(&fltr->ip_mask.v6_addrs.src_ip, fsp->m_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		स_नकल(&fltr->ip_mask.v6_addrs.dst_ip, fsp->m_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		fltr->ip_mask.l4_header = fsp->m_u.usr_ip6_spec.l4_4_bytes;
		fltr->ip_mask.tclass = fsp->m_u.usr_ip6_spec.tclass;
		fltr->ip_mask.proto = fsp->m_u.usr_ip6_spec.l4_proto;
		अवरोध;
	हाल ETHER_FLOW:
		fltr->eth_data.etype = fsp->h_u.ether_spec.h_proto;
		fltr->eth_mask.etype = fsp->m_u.ether_spec.h_proto;
		अवरोध;
	शेष:
		/* not करोing un-parsed flow types */
		वापस -EINVAL;
	पूर्ण

	अगर (iavf_fdir_is_dup_fltr(adapter, fltr))
		वापस -EEXIST;

	err = iavf_parse_rx_flow_user_data(fsp, fltr);
	अगर (err)
		वापस err;

	वापस iavf_fill_fdir_add_msg(adapter, fltr);
पूर्ण

/**
 * iavf_add_fdir_ethtool - add Flow Director filter
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @cmd: command to add Flow Director filter
 *
 * Returns 0 on success and negative values क्रम failure
 */
अटल पूर्णांक iavf_add_fdir_ethtool(काष्ठा iavf_adapter *adapter, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = &cmd->fs;
	काष्ठा iavf_fdir_fltr *fltr;
	पूर्णांक count = 50;
	पूर्णांक err;

	अगर (!Fसूची_FLTR_SUPPORT(adapter))
		वापस -EOPNOTSUPP;

	अगर (fsp->flow_type & FLOW_MAC_EXT)
		वापस -EINVAL;

	अगर (adapter->fdir_active_fltr >= IAVF_MAX_Fसूची_FILTERS) अणु
		dev_err(&adapter->pdev->dev,
			"Unable to add Flow Director filter because VF reached the limit of max allowed filters (%u)\n",
			IAVF_MAX_Fसूची_FILTERS);
		वापस -ENOSPC;
	पूर्ण

	spin_lock_bh(&adapter->fdir_fltr_lock);
	अगर (iavf_find_fdir_fltr_by_loc(adapter, fsp->location)) अणु
		dev_err(&adapter->pdev->dev, "Failed to add Flow Director filter, it already exists\n");
		spin_unlock_bh(&adapter->fdir_fltr_lock);
		वापस -EEXIST;
	पूर्ण
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	fltr = kzalloc(माप(*fltr), GFP_KERNEL);
	अगर (!fltr)
		वापस -ENOMEM;

	जबतक (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section)) अणु
		अगर (--count == 0) अणु
			kमुक्त(fltr);
			वापस -EINVAL;
		पूर्ण
		udelay(1);
	पूर्ण

	err = iavf_add_fdir_fltr_info(adapter, fsp, fltr);
	अगर (err)
		जाओ ret;

	spin_lock_bh(&adapter->fdir_fltr_lock);
	iavf_fdir_list_add_fltr(adapter, fltr);
	adapter->fdir_active_fltr++;
	fltr->state = IAVF_Fसूची_FLTR_ADD_REQUEST;
	adapter->aq_required |= IAVF_FLAG_AQ_ADD_Fसूची_FILTER;
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	mod_delayed_work(iavf_wq, &adapter->watchकरोg_task, 0);

ret:
	अगर (err && fltr)
		kमुक्त(fltr);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
	वापस err;
पूर्ण

/**
 * iavf_del_fdir_ethtool - delete Flow Director filter
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @cmd: command to delete Flow Director filter
 *
 * Returns 0 on success and negative values क्रम failure
 */
अटल पूर्णांक iavf_del_fdir_ethtool(काष्ठा iavf_adapter *adapter, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा iavf_fdir_fltr *fltr = शून्य;
	पूर्णांक err = 0;

	अगर (!Fसूची_FLTR_SUPPORT(adapter))
		वापस -EOPNOTSUPP;

	spin_lock_bh(&adapter->fdir_fltr_lock);
	fltr = iavf_find_fdir_fltr_by_loc(adapter, fsp->location);
	अगर (fltr) अणु
		अगर (fltr->state == IAVF_Fसूची_FLTR_ACTIVE) अणु
			fltr->state = IAVF_Fसूची_FLTR_DEL_REQUEST;
			adapter->aq_required |= IAVF_FLAG_AQ_DEL_Fसूची_FILTER;
		पूर्ण अन्यथा अणु
			err = -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अगर (adapter->fdir_active_fltr) अणु
		err = -EINVAL;
	पूर्ण
	spin_unlock_bh(&adapter->fdir_fltr_lock);

	अगर (fltr && fltr->state == IAVF_Fसूची_FLTR_DEL_REQUEST)
		mod_delayed_work(iavf_wq, &adapter->watchकरोg_task, 0);

	वापस err;
पूर्ण

/**
 * iavf_adv_rss_parse_hdrs - parses headers from RSS hash input
 * @cmd: ethtool rxnfc command
 *
 * This function parses the rxnfc command and वापसs पूर्णांकended
 * header types क्रम RSS configuration
 */
अटल u32 iavf_adv_rss_parse_hdrs(काष्ठा ethtool_rxnfc *cmd)
अणु
	u32 hdrs = IAVF_ADV_RSS_FLOW_SEG_HDR_NONE;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		hdrs |= IAVF_ADV_RSS_FLOW_SEG_HDR_TCP |
			IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4;
		अवरोध;
	हाल UDP_V4_FLOW:
		hdrs |= IAVF_ADV_RSS_FLOW_SEG_HDR_UDP |
			IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4;
		अवरोध;
	हाल SCTP_V4_FLOW:
		hdrs |= IAVF_ADV_RSS_FLOW_SEG_HDR_SCTP |
			IAVF_ADV_RSS_FLOW_SEG_HDR_IPV4;
		अवरोध;
	हाल TCP_V6_FLOW:
		hdrs |= IAVF_ADV_RSS_FLOW_SEG_HDR_TCP |
			IAVF_ADV_RSS_FLOW_SEG_HDR_IPV6;
		अवरोध;
	हाल UDP_V6_FLOW:
		hdrs |= IAVF_ADV_RSS_FLOW_SEG_HDR_UDP |
			IAVF_ADV_RSS_FLOW_SEG_HDR_IPV6;
		अवरोध;
	हाल SCTP_V6_FLOW:
		hdrs |= IAVF_ADV_RSS_FLOW_SEG_HDR_SCTP |
			IAVF_ADV_RSS_FLOW_SEG_HDR_IPV6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस hdrs;
पूर्ण

/**
 * iavf_adv_rss_parse_hash_flds - parses hash fields from RSS hash input
 * @cmd: ethtool rxnfc command
 *
 * This function parses the rxnfc command and वापसs पूर्णांकended hash fields क्रम
 * RSS configuration
 */
अटल u64 iavf_adv_rss_parse_hash_flds(काष्ठा ethtool_rxnfc *cmd)
अणु
	u64 hfld = IAVF_ADV_RSS_HASH_INVALID;

	अगर (cmd->data & RXH_IP_SRC || cmd->data & RXH_IP_DST) अणु
		चयन (cmd->flow_type) अणु
		हाल TCP_V4_FLOW:
		हाल UDP_V4_FLOW:
		हाल SCTP_V4_FLOW:
			अगर (cmd->data & RXH_IP_SRC)
				hfld |= IAVF_ADV_RSS_HASH_FLD_IPV4_SA;
			अगर (cmd->data & RXH_IP_DST)
				hfld |= IAVF_ADV_RSS_HASH_FLD_IPV4_DA;
			अवरोध;
		हाल TCP_V6_FLOW:
		हाल UDP_V6_FLOW:
		हाल SCTP_V6_FLOW:
			अगर (cmd->data & RXH_IP_SRC)
				hfld |= IAVF_ADV_RSS_HASH_FLD_IPV6_SA;
			अगर (cmd->data & RXH_IP_DST)
				hfld |= IAVF_ADV_RSS_HASH_FLD_IPV6_DA;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cmd->data & RXH_L4_B_0_1 || cmd->data & RXH_L4_B_2_3) अणु
		चयन (cmd->flow_type) अणु
		हाल TCP_V4_FLOW:
		हाल TCP_V6_FLOW:
			अगर (cmd->data & RXH_L4_B_0_1)
				hfld |= IAVF_ADV_RSS_HASH_FLD_TCP_SRC_PORT;
			अगर (cmd->data & RXH_L4_B_2_3)
				hfld |= IAVF_ADV_RSS_HASH_FLD_TCP_DST_PORT;
			अवरोध;
		हाल UDP_V4_FLOW:
		हाल UDP_V6_FLOW:
			अगर (cmd->data & RXH_L4_B_0_1)
				hfld |= IAVF_ADV_RSS_HASH_FLD_UDP_SRC_PORT;
			अगर (cmd->data & RXH_L4_B_2_3)
				hfld |= IAVF_ADV_RSS_HASH_FLD_UDP_DST_PORT;
			अवरोध;
		हाल SCTP_V4_FLOW:
		हाल SCTP_V6_FLOW:
			अगर (cmd->data & RXH_L4_B_0_1)
				hfld |= IAVF_ADV_RSS_HASH_FLD_SCTP_SRC_PORT;
			अगर (cmd->data & RXH_L4_B_2_3)
				hfld |= IAVF_ADV_RSS_HASH_FLD_SCTP_DST_PORT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस hfld;
पूर्ण

/**
 * iavf_set_adv_rss_hash_opt - Enable/Disable flow types क्रम RSS hash
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @cmd: ethtool rxnfc command
 *
 * Returns Success अगर the flow input set is supported.
 */
अटल पूर्णांक
iavf_set_adv_rss_hash_opt(काष्ठा iavf_adapter *adapter,
			  काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा iavf_adv_rss *rss_old, *rss_new;
	bool rss_new_add = false;
	पूर्णांक count = 50, err = 0;
	u64 hash_flds;
	u32 hdrs;

	अगर (!ADV_RSS_SUPPORT(adapter))
		वापस -EOPNOTSUPP;

	hdrs = iavf_adv_rss_parse_hdrs(cmd);
	अगर (hdrs == IAVF_ADV_RSS_FLOW_SEG_HDR_NONE)
		वापस -EINVAL;

	hash_flds = iavf_adv_rss_parse_hash_flds(cmd);
	अगर (hash_flds == IAVF_ADV_RSS_HASH_INVALID)
		वापस -EINVAL;

	rss_new = kzalloc(माप(*rss_new), GFP_KERNEL);
	अगर (!rss_new)
		वापस -ENOMEM;

	अगर (iavf_fill_adv_rss_cfg_msg(&rss_new->cfg_msg, hdrs, hash_flds)) अणु
		kमुक्त(rss_new);
		वापस -EINVAL;
	पूर्ण

	जबतक (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section)) अणु
		अगर (--count == 0) अणु
			kमुक्त(rss_new);
			वापस -EINVAL;
		पूर्ण

		udelay(1);
	पूर्ण

	spin_lock_bh(&adapter->adv_rss_lock);
	rss_old = iavf_find_adv_rss_cfg_by_hdrs(adapter, hdrs);
	अगर (rss_old) अणु
		अगर (rss_old->state != IAVF_ADV_RSS_ACTIVE) अणु
			err = -EBUSY;
		पूर्ण अन्यथा अगर (rss_old->hash_flds != hash_flds) अणु
			rss_old->state = IAVF_ADV_RSS_ADD_REQUEST;
			rss_old->hash_flds = hash_flds;
			स_नकल(&rss_old->cfg_msg, &rss_new->cfg_msg,
			       माप(rss_new->cfg_msg));
			adapter->aq_required |= IAVF_FLAG_AQ_ADD_ADV_RSS_CFG;
		पूर्ण अन्यथा अणु
			err = -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		rss_new_add = true;
		rss_new->state = IAVF_ADV_RSS_ADD_REQUEST;
		rss_new->packet_hdrs = hdrs;
		rss_new->hash_flds = hash_flds;
		list_add_tail(&rss_new->list, &adapter->adv_rss_list_head);
		adapter->aq_required |= IAVF_FLAG_AQ_ADD_ADV_RSS_CFG;
	पूर्ण
	spin_unlock_bh(&adapter->adv_rss_lock);

	अगर (!err)
		mod_delayed_work(iavf_wq, &adapter->watchकरोg_task, 0);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	अगर (!rss_new_add)
		kमुक्त(rss_new);

	वापस err;
पूर्ण

/**
 * iavf_get_adv_rss_hash_opt - Retrieve hash fields क्रम a given flow-type
 * @adapter: poपूर्णांकer to the VF adapter काष्ठाure
 * @cmd: ethtool rxnfc command
 *
 * Returns Success अगर the flow input set is supported.
 */
अटल पूर्णांक
iavf_get_adv_rss_hash_opt(काष्ठा iavf_adapter *adapter,
			  काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा iavf_adv_rss *rss;
	u64 hash_flds;
	u32 hdrs;

	अगर (!ADV_RSS_SUPPORT(adapter))
		वापस -EOPNOTSUPP;

	cmd->data = 0;

	hdrs = iavf_adv_rss_parse_hdrs(cmd);
	अगर (hdrs == IAVF_ADV_RSS_FLOW_SEG_HDR_NONE)
		वापस -EINVAL;

	spin_lock_bh(&adapter->adv_rss_lock);
	rss = iavf_find_adv_rss_cfg_by_hdrs(adapter, hdrs);
	अगर (rss)
		hash_flds = rss->hash_flds;
	अन्यथा
		hash_flds = IAVF_ADV_RSS_HASH_INVALID;
	spin_unlock_bh(&adapter->adv_rss_lock);

	अगर (hash_flds == IAVF_ADV_RSS_HASH_INVALID)
		वापस -EINVAL;

	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_IPV4_SA |
			 IAVF_ADV_RSS_HASH_FLD_IPV6_SA))
		cmd->data |= (u64)RXH_IP_SRC;

	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_IPV4_DA |
			 IAVF_ADV_RSS_HASH_FLD_IPV6_DA))
		cmd->data |= (u64)RXH_IP_DST;

	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_TCP_SRC_PORT |
			 IAVF_ADV_RSS_HASH_FLD_UDP_SRC_PORT |
			 IAVF_ADV_RSS_HASH_FLD_SCTP_SRC_PORT))
		cmd->data |= (u64)RXH_L4_B_0_1;

	अगर (hash_flds & (IAVF_ADV_RSS_HASH_FLD_TCP_DST_PORT |
			 IAVF_ADV_RSS_HASH_FLD_UDP_DST_PORT |
			 IAVF_ADV_RSS_HASH_FLD_SCTP_DST_PORT))
		cmd->data |= (u64)RXH_L4_B_2_3;

	वापस 0;
पूर्ण

/**
 * iavf_set_rxnfc - command to set Rx flow rules.
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool rxnfc command
 *
 * Returns 0 क्रम success and negative values क्रम errors
 */
अटल पूर्णांक iavf_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		ret = iavf_add_fdir_ethtool(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = iavf_del_fdir_ethtool(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_SRXFH:
		ret = iavf_set_adv_rss_hash_opt(adapter, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * iavf_get_rxnfc - command to get RX flow classअगरication rules
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool rxnfc command
 * @rule_locs: poपूर्णांकer to store rule locations
 *
 * Returns Success अगर the command is supported.
 **/
अटल पूर्णांक iavf_get_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd,
			  u32 *rule_locs)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_active_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		अगर (!Fसूची_FLTR_SUPPORT(adapter))
			अवरोध;
		cmd->rule_cnt = adapter->fdir_active_fltr;
		cmd->data = IAVF_MAX_Fसूची_FILTERS;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = iavf_get_ethtool_fdir_entry(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = iavf_get_fdir_fltr_ids(adapter, cmd, (u32 *)rule_locs);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ret = iavf_get_adv_rss_hash_opt(adapter, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
/**
 * iavf_get_channels: get the number of channels supported by the device
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ch: channel inक्रमmation काष्ठाure
 *
 * For the purposes of our device, we only use combined channels, i.e. a tx/rx
 * queue pair. Report one extra channel to match our "other" MSI-X vector.
 **/
अटल व्योम iavf_get_channels(काष्ठा net_device *netdev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	/* Report maximum channels */
	ch->max_combined = adapter->vsi_res->num_queue_pairs;

	ch->max_other = NONQ_VECS;
	ch->other_count = NONQ_VECS;

	ch->combined_count = adapter->num_active_queues;
पूर्ण

/**
 * iavf_set_channels: set the new channel count
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ch: channel inक्रमmation काष्ठाure
 *
 * Negotiate a new number of channels with the PF then करो a reset.  During
 * reset we'll पुनः_स्मृति queues and fix the RSS table.  Returns 0 on success,
 * negative on failure.
 **/
अटल पूर्णांक iavf_set_channels(काष्ठा net_device *netdev,
			     काष्ठा ethtool_channels *ch)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u32 num_req = ch->combined_count;

	अगर ((adapter->vf_res->vf_cap_flags & VIRTCHNL_VF_OFFLOAD_ADQ) &&
	    adapter->num_tc) अणु
		dev_info(&adapter->pdev->dev, "Cannot set channels since ADq is enabled.\n");
		वापस -EINVAL;
	पूर्ण

	/* All of these should have alपढ़ोy been checked by ethtool beक्रमe this
	 * even माला_लो to us, but just to be sure.
	 */
	अगर (num_req > adapter->vsi_res->num_queue_pairs)
		वापस -EINVAL;

	अगर (num_req == adapter->num_active_queues)
		वापस 0;

	अगर (ch->rx_count || ch->tx_count || ch->other_count != NONQ_VECS)
		वापस -EINVAL;

	adapter->num_req_queues = num_req;
	adapter->flags |= IAVF_FLAG_REINIT_ITR_NEEDED;
	iavf_schedule_reset(adapter);
	वापस 0;
पूर्ण

/**
 * iavf_get_rxfh_key_size - get the RSS hash key size
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the table size.
 **/
अटल u32 iavf_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	वापस adapter->rss_key_size;
पूर्ण

/**
 * iavf_get_rxfh_indir_size - get the rx flow hash indirection table size
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the table size.
 **/
अटल u32 iavf_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);

	वापस adapter->rss_lut_size;
पूर्ण

/**
 * iavf_get_rxfh - get the rx flow hash indirection table
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @indir: indirection table
 * @key: hash key
 * @hfunc: hash function in use
 *
 * Reads the indirection table directly from the hardware. Always वापसs 0.
 **/
अटल पूर्णांक iavf_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			 u8 *hfunc)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u16 i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!indir)
		वापस 0;

	स_नकल(key, adapter->rss_key, adapter->rss_key_size);

	/* Each 32 bits poपूर्णांकed by 'indir' is stored with a lut entry */
	क्रम (i = 0; i < adapter->rss_lut_size; i++)
		indir[i] = (u32)adapter->rss_lut[i];

	वापस 0;
पूर्ण

/**
 * iavf_set_rxfh - set the rx flow hash indirection table
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @indir: indirection table
 * @key: hash key
 * @hfunc: hash function to use
 *
 * Returns -EINVAL अगर the table specअगरies an inavlid queue id, otherwise
 * वापसs 0 after programming the table.
 **/
अटल पूर्णांक iavf_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	u16 i;

	/* We करो not allow change in unsupported parameters */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;
	अगर (!indir)
		वापस 0;

	अगर (key)
		स_नकल(adapter->rss_key, key, adapter->rss_key_size);

	/* Each 32 bits poपूर्णांकed by 'indir' is stored with a lut entry */
	क्रम (i = 0; i < adapter->rss_lut_size; i++)
		adapter->rss_lut[i] = (u8)(indir[i]);

	वापस iavf_config_rss(adapter);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops iavf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_MAX_FRAMES_IRQ |
				     ETHTOOL_COALESCE_USE_ADAPTIVE,
	.get_drvinfo		= iavf_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ringparam		= iavf_get_ringparam,
	.set_ringparam		= iavf_set_ringparam,
	.get_strings		= iavf_get_strings,
	.get_ethtool_stats	= iavf_get_ethtool_stats,
	.get_sset_count		= iavf_get_sset_count,
	.get_priv_flags		= iavf_get_priv_flags,
	.set_priv_flags		= iavf_set_priv_flags,
	.get_msglevel		= iavf_get_msglevel,
	.set_msglevel		= iavf_set_msglevel,
	.get_coalesce		= iavf_get_coalesce,
	.set_coalesce		= iavf_set_coalesce,
	.get_per_queue_coalesce = iavf_get_per_queue_coalesce,
	.set_per_queue_coalesce = iavf_set_per_queue_coalesce,
	.set_rxnfc		= iavf_set_rxnfc,
	.get_rxnfc		= iavf_get_rxnfc,
	.get_rxfh_indir_size	= iavf_get_rxfh_indir_size,
	.get_rxfh		= iavf_get_rxfh,
	.set_rxfh		= iavf_set_rxfh,
	.get_channels		= iavf_get_channels,
	.set_channels		= iavf_set_channels,
	.get_rxfh_key_size	= iavf_get_rxfh_key_size,
	.get_link_ksettings	= iavf_get_link_ksettings,
पूर्ण;

/**
 * iavf_set_ethtool_ops - Initialize ethtool ops काष्ठा
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Sets ethtool ops काष्ठा in our netdev so that ethtool can call
 * our functions.
 **/
व्योम iavf_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &iavf_ethtool_ops;
पूर्ण
