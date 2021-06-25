<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/version.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/capability.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/phylink.h>

#समावेश "qede.h"
#समावेश "qede_ptp.h"

#घोषणा QEDE_RQSTAT_OFFSET(stat_name) \
	 (दुरत्व(काष्ठा qede_rx_queue, stat_name))
#घोषणा QEDE_RQSTAT_STRING(stat_name) (#stat_name)
#घोषणा QEDE_RQSTAT(stat_name) \
	 अणुQEDE_RQSTAT_OFFSET(stat_name), QEDE_RQSTAT_STRING(stat_name)पूर्ण

#घोषणा QEDE_SELFTEST_POLL_COUNT 100
#घोषणा QEDE_DUMP_VERSION	0x1
#घोषणा QEDE_DUMP_NVM_ARG_COUNT	2

अटल स्थिर काष्ठा अणु
	u64 offset;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण qede_rqstats_arr[] = अणु
	QEDE_RQSTAT(rcv_pkts),
	QEDE_RQSTAT(rx_hw_errors),
	QEDE_RQSTAT(rx_alloc_errors),
	QEDE_RQSTAT(rx_ip_frags),
	QEDE_RQSTAT(xdp_no_pass),
पूर्ण;

#घोषणा QEDE_NUM_RQSTATS ARRAY_SIZE(qede_rqstats_arr)
#घोषणा QEDE_TQSTAT_OFFSET(stat_name) \
	(दुरत्व(काष्ठा qede_tx_queue, stat_name))
#घोषणा QEDE_TQSTAT_STRING(stat_name) (#stat_name)
#घोषणा QEDE_TQSTAT(stat_name) \
	अणुQEDE_TQSTAT_OFFSET(stat_name), QEDE_TQSTAT_STRING(stat_name)पूर्ण
#घोषणा QEDE_NUM_TQSTATS ARRAY_SIZE(qede_tqstats_arr)
अटल स्थिर काष्ठा अणु
	u64 offset;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण qede_tqstats_arr[] = अणु
	QEDE_TQSTAT(xmit_pkts),
	QEDE_TQSTAT(stopped_cnt),
	QEDE_TQSTAT(tx_mem_alloc_err),
पूर्ण;

#घोषणा QEDE_STAT_OFFSET(stat_name, type, base) \
	(दुरत्व(type, stat_name) + (base))
#घोषणा QEDE_STAT_STRING(stat_name)	(#stat_name)
#घोषणा _QEDE_STAT(stat_name, type, base, attr) \
	अणुQEDE_STAT_OFFSET(stat_name, type, base), \
	 QEDE_STAT_STRING(stat_name), \
	 attrपूर्ण
#घोषणा QEDE_STAT(stat_name) \
	_QEDE_STAT(stat_name, काष्ठा qede_stats_common, 0, 0x0)
#घोषणा QEDE_PF_STAT(stat_name) \
	_QEDE_STAT(stat_name, काष्ठा qede_stats_common, 0, \
		   BIT(QEDE_STAT_PF_ONLY))
#घोषणा QEDE_PF_BB_STAT(stat_name) \
	_QEDE_STAT(stat_name, काष्ठा qede_stats_bb, \
		   दुरत्व(काष्ठा qede_stats, bb), \
		   BIT(QEDE_STAT_PF_ONLY) | BIT(QEDE_STAT_BB_ONLY))
#घोषणा QEDE_PF_AH_STAT(stat_name) \
	_QEDE_STAT(stat_name, काष्ठा qede_stats_ah, \
		   दुरत्व(काष्ठा qede_stats, ah), \
		   BIT(QEDE_STAT_PF_ONLY) | BIT(QEDE_STAT_AH_ONLY))
अटल स्थिर काष्ठा अणु
	u64 offset;
	अक्षर string[ETH_GSTRING_LEN];
	अचिन्हित दीर्घ attr;
#घोषणा QEDE_STAT_PF_ONLY	0
#घोषणा QEDE_STAT_BB_ONLY	1
#घोषणा QEDE_STAT_AH_ONLY	2
पूर्ण qede_stats_arr[] = अणु
	QEDE_STAT(rx_ucast_bytes),
	QEDE_STAT(rx_mcast_bytes),
	QEDE_STAT(rx_bcast_bytes),
	QEDE_STAT(rx_ucast_pkts),
	QEDE_STAT(rx_mcast_pkts),
	QEDE_STAT(rx_bcast_pkts),

	QEDE_STAT(tx_ucast_bytes),
	QEDE_STAT(tx_mcast_bytes),
	QEDE_STAT(tx_bcast_bytes),
	QEDE_STAT(tx_ucast_pkts),
	QEDE_STAT(tx_mcast_pkts),
	QEDE_STAT(tx_bcast_pkts),

	QEDE_PF_STAT(rx_64_byte_packets),
	QEDE_PF_STAT(rx_65_to_127_byte_packets),
	QEDE_PF_STAT(rx_128_to_255_byte_packets),
	QEDE_PF_STAT(rx_256_to_511_byte_packets),
	QEDE_PF_STAT(rx_512_to_1023_byte_packets),
	QEDE_PF_STAT(rx_1024_to_1518_byte_packets),
	QEDE_PF_BB_STAT(rx_1519_to_1522_byte_packets),
	QEDE_PF_BB_STAT(rx_1519_to_2047_byte_packets),
	QEDE_PF_BB_STAT(rx_2048_to_4095_byte_packets),
	QEDE_PF_BB_STAT(rx_4096_to_9216_byte_packets),
	QEDE_PF_BB_STAT(rx_9217_to_16383_byte_packets),
	QEDE_PF_AH_STAT(rx_1519_to_max_byte_packets),
	QEDE_PF_STAT(tx_64_byte_packets),
	QEDE_PF_STAT(tx_65_to_127_byte_packets),
	QEDE_PF_STAT(tx_128_to_255_byte_packets),
	QEDE_PF_STAT(tx_256_to_511_byte_packets),
	QEDE_PF_STAT(tx_512_to_1023_byte_packets),
	QEDE_PF_STAT(tx_1024_to_1518_byte_packets),
	QEDE_PF_BB_STAT(tx_1519_to_2047_byte_packets),
	QEDE_PF_BB_STAT(tx_2048_to_4095_byte_packets),
	QEDE_PF_BB_STAT(tx_4096_to_9216_byte_packets),
	QEDE_PF_BB_STAT(tx_9217_to_16383_byte_packets),
	QEDE_PF_AH_STAT(tx_1519_to_max_byte_packets),
	QEDE_PF_STAT(rx_mac_crtl_frames),
	QEDE_PF_STAT(tx_mac_ctrl_frames),
	QEDE_PF_STAT(rx_छोड़ो_frames),
	QEDE_PF_STAT(tx_छोड़ो_frames),
	QEDE_PF_STAT(rx_pfc_frames),
	QEDE_PF_STAT(tx_pfc_frames),

	QEDE_PF_STAT(rx_crc_errors),
	QEDE_PF_STAT(rx_align_errors),
	QEDE_PF_STAT(rx_carrier_errors),
	QEDE_PF_STAT(rx_oversize_packets),
	QEDE_PF_STAT(rx_jabbers),
	QEDE_PF_STAT(rx_undersize_packets),
	QEDE_PF_STAT(rx_fragments),
	QEDE_PF_BB_STAT(tx_lpi_entry_count),
	QEDE_PF_BB_STAT(tx_total_collisions),
	QEDE_PF_STAT(brb_truncates),
	QEDE_PF_STAT(brb_discards),
	QEDE_STAT(no_buff_discards),
	QEDE_PF_STAT(mftag_filter_discards),
	QEDE_PF_STAT(mac_filter_discards),
	QEDE_PF_STAT(gft_filter_drop),
	QEDE_STAT(tx_err_drop_pkts),
	QEDE_STAT(ttl0_discard),
	QEDE_STAT(packet_too_big_discard),

	QEDE_STAT(coalesced_pkts),
	QEDE_STAT(coalesced_events),
	QEDE_STAT(coalesced_पातs_num),
	QEDE_STAT(non_coalesced_pkts),
	QEDE_STAT(coalesced_bytes),

	QEDE_STAT(link_change_count),
	QEDE_STAT(ptp_skip_txts),
पूर्ण;

#घोषणा QEDE_NUM_STATS	ARRAY_SIZE(qede_stats_arr)
#घोषणा QEDE_STAT_IS_PF_ONLY(i) \
	test_bit(QEDE_STAT_PF_ONLY, &qede_stats_arr[i].attr)
#घोषणा QEDE_STAT_IS_BB_ONLY(i) \
	test_bit(QEDE_STAT_BB_ONLY, &qede_stats_arr[i].attr)
#घोषणा QEDE_STAT_IS_AH_ONLY(i) \
	test_bit(QEDE_STAT_AH_ONLY, &qede_stats_arr[i].attr)

क्रमागत अणु
	QEDE_PRI_FLAG_CMT,
	QEDE_PRI_FLAG_SMART_AN_SUPPORT, /* MFW supports SmartAN */
	QEDE_PRI_FLAG_RECOVER_ON_ERROR,
	QEDE_PRI_FLAG_LEN,
पूर्ण;

अटल स्थिर अक्षर qede_निजी_arr[QEDE_PRI_FLAG_LEN][ETH_GSTRING_LEN] = अणु
	"Coupled-Function",
	"SmartAN capable",
	"Recover on error",
पूर्ण;

क्रमागत qede_ethtool_tests अणु
	QEDE_ETHTOOL_INT_LOOPBACK,
	QEDE_ETHTOOL_INTERRUPT_TEST,
	QEDE_ETHTOOL_MEMORY_TEST,
	QEDE_ETHTOOL_REGISTER_TEST,
	QEDE_ETHTOOL_CLOCK_TEST,
	QEDE_ETHTOOL_NVRAM_TEST,
	QEDE_ETHTOOL_TEST_MAX
पूर्ण;

अटल स्थिर अक्षर qede_tests_str_arr[QEDE_ETHTOOL_TEST_MAX][ETH_GSTRING_LEN] = अणु
	"Internal loopback (offline)",
	"Interrupt (online)\t",
	"Memory (online)\t\t",
	"Register (online)\t",
	"Clock (online)\t\t",
	"Nvram (online)\t\t",
पूर्ण;

/* Forced speed capabilities maps */

काष्ठा qede_क्रमced_speed_map अणु
	u32		speed;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(caps);

	स्थिर u32	*cap_arr;
	u32		arr_size;
पूर्ण;

#घोषणा QEDE_FORCED_SPEED_MAP(value)					\
अणु									\
	.speed		= SPEED_##value,				\
	.cap_arr	= qede_क्रमced_speed_##value,			\
	.arr_size	= ARRAY_SIZE(qede_क्रमced_speed_##value),	\
पूर्ण

अटल स्थिर u32 qede_क्रमced_speed_1000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
पूर्ण;

अटल स्थिर u32 qede_क्रमced_speed_10000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
	ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT,
पूर्ण;

अटल स्थिर u32 qede_क्रमced_speed_20000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qede_क्रमced_speed_25000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
पूर्ण;

अटल स्थिर u32 qede_क्रमced_speed_40000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
पूर्ण;

अटल स्थिर u32 qede_क्रमced_speed_50000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qede_क्रमced_speed_100000[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
पूर्ण;

अटल काष्ठा qede_क्रमced_speed_map qede_क्रमced_speed_maps[] __ro_after_init = अणु
	QEDE_FORCED_SPEED_MAP(1000),
	QEDE_FORCED_SPEED_MAP(10000),
	QEDE_FORCED_SPEED_MAP(20000),
	QEDE_FORCED_SPEED_MAP(25000),
	QEDE_FORCED_SPEED_MAP(40000),
	QEDE_FORCED_SPEED_MAP(50000),
	QEDE_FORCED_SPEED_MAP(100000),
पूर्ण;

व्योम __init qede_क्रमced_speed_maps_init(व्योम)
अणु
	काष्ठा qede_क्रमced_speed_map *map;
	u32 i;

	क्रम (i = 0; i < ARRAY_SIZE(qede_क्रमced_speed_maps); i++) अणु
		map = qede_क्रमced_speed_maps + i;

		linkmode_set_bit_array(map->cap_arr, map->arr_size, map->caps);
		map->cap_arr = शून्य;
		map->arr_size = 0;
	पूर्ण
पूर्ण

/* Ethtool callbacks */

अटल व्योम qede_get_strings_stats_txq(काष्ठा qede_dev *edev,
				       काष्ठा qede_tx_queue *txq, u8 **buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QEDE_NUM_TQSTATS; i++) अणु
		अगर (txq->is_xdp)
			प्र_लिखो(*buf, "%d [XDP]: %s",
				QEDE_TXQ_XDP_TO_IDX(edev, txq),
				qede_tqstats_arr[i].string);
		अन्यथा
			प्र_लिखो(*buf, "%d_%d: %s", txq->index, txq->cos,
				qede_tqstats_arr[i].string);
		*buf += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल व्योम qede_get_strings_stats_rxq(काष्ठा qede_dev *edev,
				       काष्ठा qede_rx_queue *rxq, u8 **buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QEDE_NUM_RQSTATS; i++) अणु
		प्र_लिखो(*buf, "%d: %s", rxq->rxq_id,
			qede_rqstats_arr[i].string);
		*buf += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल bool qede_is_irrelevant_stat(काष्ठा qede_dev *edev, पूर्णांक stat_index)
अणु
	वापस (IS_VF(edev) && QEDE_STAT_IS_PF_ONLY(stat_index)) ||
	       (QEDE_IS_BB(edev) && QEDE_STAT_IS_AH_ONLY(stat_index)) ||
	       (QEDE_IS_AH(edev) && QEDE_STAT_IS_BB_ONLY(stat_index));
पूर्ण

अटल व्योम qede_get_strings_stats(काष्ठा qede_dev *edev, u8 *buf)
अणु
	काष्ठा qede_fastpath *fp;
	पूर्णांक i;

	/* Account क्रम queue statistics */
	क्रम (i = 0; i < QEDE_QUEUE_CNT(edev); i++) अणु
		fp = &edev->fp_array[i];

		अगर (fp->type & QEDE_FASTPATH_RX)
			qede_get_strings_stats_rxq(edev, fp->rxq, &buf);

		अगर (fp->type & QEDE_FASTPATH_XDP)
			qede_get_strings_stats_txq(edev, fp->xdp_tx, &buf);

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos)
				qede_get_strings_stats_txq(edev,
							   &fp->txq[cos], &buf);
		पूर्ण
	पूर्ण

	/* Account क्रम non-queue statistics */
	क्रम (i = 0; i < QEDE_NUM_STATS; i++) अणु
		अगर (qede_is_irrelevant_stat(edev, i))
			जारी;
		म_नकल(buf, qede_stats_arr[i].string);
		buf += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल व्योम qede_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		qede_get_strings_stats(edev, buf);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(buf, qede_निजी_arr,
		       ETH_GSTRING_LEN * QEDE_PRI_FLAG_LEN);
		अवरोध;
	हाल ETH_SS_TEST:
		स_नकल(buf, qede_tests_str_arr,
		       ETH_GSTRING_LEN * QEDE_ETHTOOL_TEST_MAX);
		अवरोध;
	शेष:
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "Unsupported stringset 0x%08x\n", stringset);
	पूर्ण
पूर्ण

अटल व्योम qede_get_ethtool_stats_txq(काष्ठा qede_tx_queue *txq, u64 **buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QEDE_NUM_TQSTATS; i++) अणु
		**buf = *((u64 *)(((व्योम *)txq) + qede_tqstats_arr[i].offset));
		(*buf)++;
	पूर्ण
पूर्ण

अटल व्योम qede_get_ethtool_stats_rxq(काष्ठा qede_rx_queue *rxq, u64 **buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QEDE_NUM_RQSTATS; i++) अणु
		**buf = *((u64 *)(((व्योम *)rxq) + qede_rqstats_arr[i].offset));
		(*buf)++;
	पूर्ण
पूर्ण

अटल व्योम qede_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *stats, u64 *buf)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_fastpath *fp;
	पूर्णांक i;

	qede_fill_by_demand_stats(edev);

	/* Need to protect the access to the fastpath array */
	__qede_lock(edev);

	क्रम (i = 0; i < QEDE_QUEUE_CNT(edev); i++) अणु
		fp = &edev->fp_array[i];

		अगर (fp->type & QEDE_FASTPATH_RX)
			qede_get_ethtool_stats_rxq(fp->rxq, &buf);

		अगर (fp->type & QEDE_FASTPATH_XDP)
			qede_get_ethtool_stats_txq(fp->xdp_tx, &buf);

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos)
				qede_get_ethtool_stats_txq(&fp->txq[cos], &buf);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < QEDE_NUM_STATS; i++) अणु
		अगर (qede_is_irrelevant_stat(edev, i))
			जारी;
		*buf = *((u64 *)(((व्योम *)&edev->stats) +
				 qede_stats_arr[i].offset));

		buf++;
	पूर्ण

	__qede_unlock(edev);
पूर्ण

अटल पूर्णांक qede_get_sset_count(काष्ठा net_device *dev, पूर्णांक stringset)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक num_stats = QEDE_NUM_STATS, i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < QEDE_NUM_STATS; i++)
			अगर (qede_is_irrelevant_stat(edev, i))
				num_stats--;

		/* Account क्रम the Regular Tx statistics */
		num_stats += QEDE_TSS_COUNT(edev) * QEDE_NUM_TQSTATS *
				edev->dev_info.num_tc;

		/* Account क्रम the Regular Rx statistics */
		num_stats += QEDE_RSS_COUNT(edev) * QEDE_NUM_RQSTATS;

		/* Account क्रम XDP statistics [अगर needed] */
		अगर (edev->xdp_prog)
			num_stats += QEDE_RSS_COUNT(edev) * QEDE_NUM_TQSTATS;
		वापस num_stats;

	हाल ETH_SS_PRIV_FLAGS:
		वापस QEDE_PRI_FLAG_LEN;
	हाल ETH_SS_TEST:
		अगर (!IS_VF(edev))
			वापस QEDE_ETHTOOL_TEST_MAX;
		अन्यथा
			वापस 0;
	शेष:
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "Unsupported stringset 0x%08x\n", stringset);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 qede_get_priv_flags(काष्ठा net_device *dev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u32 flags = 0;

	अगर (edev->dev_info.common.num_hwfns > 1)
		flags |= BIT(QEDE_PRI_FLAG_CMT);

	अगर (edev->dev_info.common.smart_an)
		flags |= BIT(QEDE_PRI_FLAG_SMART_AN_SUPPORT);

	अगर (edev->err_flags & BIT(QEDE_ERR_IS_RECOVERABLE))
		flags |= BIT(QEDE_PRI_FLAG_RECOVER_ON_ERROR);

	वापस flags;
पूर्ण

अटल पूर्णांक qede_set_priv_flags(काष्ठा net_device *dev, u32 flags)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u32 cflags = qede_get_priv_flags(dev);
	u32 dflags = flags ^ cflags;

	/* can only change RECOVER_ON_ERROR flag */
	अगर (dflags & ~BIT(QEDE_PRI_FLAG_RECOVER_ON_ERROR))
		वापस -EINVAL;

	अगर (flags & BIT(QEDE_PRI_FLAG_RECOVER_ON_ERROR))
		set_bit(QEDE_ERR_IS_RECOVERABLE, &edev->err_flags);
	अन्यथा
		clear_bit(QEDE_ERR_IS_RECOVERABLE, &edev->err_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	typeof(cmd->link_modes) *link_modes = &cmd->link_modes;
	काष्ठा ethtool_link_settings *base = &cmd->base;
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output current_link;

	__qede_lock(edev);

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	linkmode_copy(link_modes->supported, current_link.supported_caps);
	linkmode_copy(link_modes->advertising, current_link.advertised_caps);
	linkmode_copy(link_modes->lp_advertising, current_link.lp_caps);

	अगर ((edev->state == QEDE_STATE_OPEN) && (current_link.link_up)) अणु
		base->speed = current_link.speed;
		base->duplex = current_link.duplex;
	पूर्ण अन्यथा अणु
		base->speed = SPEED_UNKNOWN;
		base->duplex = DUPLEX_UNKNOWN;
	पूर्ण

	__qede_unlock(edev);

	base->port = current_link.port;
	base->स्वतःneg = (current_link.स्वतःneg) ? AUTONEG_ENABLE :
			AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक qede_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा ethtool_link_settings *base = &cmd->base;
	काष्ठा qede_dev *edev = netdev_priv(dev);
	स्थिर काष्ठा qede_क्रमced_speed_map *map;
	काष्ठा qed_link_output current_link;
	काष्ठा qed_link_params params;
	u32 i;

	अगर (!edev->ops || !edev->ops->common->can_link_change(edev->cdev)) अणु
		DP_INFO(edev, "Link settings are not allowed to be changed\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	स_रखो(&current_link, 0, माप(current_link));
	स_रखो(&params, 0, माप(params));
	edev->ops->common->get_link(edev->cdev, &current_link);

	params.override_flags |= QED_LINK_OVERRIDE_SPEED_ADV_SPEEDS;
	params.override_flags |= QED_LINK_OVERRIDE_SPEED_AUTONEG;

	अगर (base->स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (!phylink_test(current_link.supported_caps, Autoneg)) अणु
			DP_INFO(edev, "Auto negotiation is not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		params.स्वतःneg = true;
		params.क्रमced_speed = 0;

		linkmode_copy(params.adv_speeds, cmd->link_modes.advertising);
	पूर्ण अन्यथा अणु		/* क्रमced speed */
		params.override_flags |= QED_LINK_OVERRIDE_SPEED_FORCED_SPEED;
		params.स्वतःneg = false;
		params.क्रमced_speed = base->speed;

		क्रम (i = 0; i < ARRAY_SIZE(qede_क्रमced_speed_maps); i++) अणु
			map = qede_क्रमced_speed_maps + i;

			अगर (base->speed != map->speed ||
			    !linkmode_पूर्णांकersects(current_link.supported_caps,
						 map->caps))
				जारी;

			linkmode_and(params.adv_speeds,
				     current_link.supported_caps, map->caps);
			जाओ set_link;
		पूर्ण

		DP_INFO(edev, "Unsupported speed %u\n", base->speed);
		वापस -EINVAL;
	पूर्ण

set_link:
	params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &params);

	वापस 0;
पूर्ण

अटल व्योम qede_get_drvinfo(काष्ठा net_device *ndev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	अक्षर mfw[ETHTOOL_FWVERS_LEN], storm[ETHTOOL_FWVERS_LEN];
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	अक्षर mbi[ETHTOOL_FWVERS_LEN];

	strlcpy(info->driver, "qede", माप(info->driver));

	snम_लिखो(storm, ETHTOOL_FWVERS_LEN, "%d.%d.%d.%d",
		 edev->dev_info.common.fw_major,
		 edev->dev_info.common.fw_minor,
		 edev->dev_info.common.fw_rev,
		 edev->dev_info.common.fw_eng);

	snम_लिखो(mfw, ETHTOOL_FWVERS_LEN, "%d.%d.%d.%d",
		 (edev->dev_info.common.mfw_rev >> 24) & 0xFF,
		 (edev->dev_info.common.mfw_rev >> 16) & 0xFF,
		 (edev->dev_info.common.mfw_rev >> 8) & 0xFF,
		 edev->dev_info.common.mfw_rev & 0xFF);

	अगर ((म_माप(storm) + म_माप(DRV_MODULE_VERSION) + म_माप("[storm]  ")) <
	    माप(info->version))
		snम_लिखो(info->version, माप(info->version),
			 "%s [storm %s]", DRV_MODULE_VERSION, storm);
	अन्यथा
		snम_लिखो(info->version, माप(info->version),
			 "%s %s", DRV_MODULE_VERSION, storm);

	अगर (edev->dev_info.common.mbi_version) अणु
		snम_लिखो(mbi, ETHTOOL_FWVERS_LEN, "%d.%d.%d",
			 (edev->dev_info.common.mbi_version &
			  QED_MBI_VERSION_2_MASK) >> QED_MBI_VERSION_2_OFFSET,
			 (edev->dev_info.common.mbi_version &
			  QED_MBI_VERSION_1_MASK) >> QED_MBI_VERSION_1_OFFSET,
			 (edev->dev_info.common.mbi_version &
			  QED_MBI_VERSION_0_MASK) >> QED_MBI_VERSION_0_OFFSET);
		snम_लिखो(info->fw_version, माप(info->fw_version),
			 "mbi %s [mfw %s]", mbi, mfw);
	पूर्ण अन्यथा अणु
		snम_लिखो(info->fw_version, माप(info->fw_version),
			 "mfw %s", mfw);
	पूर्ण

	strlcpy(info->bus_info, pci_name(edev->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम qede_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	अगर (edev->dev_info.common.wol_support) अणु
		wol->supported = WAKE_MAGIC;
		wol->wolopts = edev->wol_enabled ? WAKE_MAGIC : 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qede_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	bool wol_requested;
	पूर्णांक rc;

	अगर (wol->wolopts & ~WAKE_MAGIC) अणु
		DP_INFO(edev,
			"Can't support WoL options other than magic-packet\n");
		वापस -EINVAL;
	पूर्ण

	wol_requested = !!(wol->wolopts & WAKE_MAGIC);
	अगर (wol_requested == edev->wol_enabled)
		वापस 0;

	/* Need to actually change configuration */
	अगर (!edev->dev_info.common.wol_support) अणु
		DP_INFO(edev, "Device doesn't support WoL\n");
		वापस -EINVAL;
	पूर्ण

	rc = edev->ops->common->update_wol(edev->cdev, wol_requested);
	अगर (!rc)
		edev->wol_enabled = wol_requested;

	वापस rc;
पूर्ण

अटल u32 qede_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	वापस ((u32)edev->dp_level << QED_LOG_LEVEL_SHIFT) | edev->dp_module;
पूर्ण

अटल व्योम qede_set_msglevel(काष्ठा net_device *ndev, u32 level)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	u32 dp_module = 0;
	u8 dp_level = 0;

	qede_config_debug(level, &dp_module, &dp_level);

	edev->dp_level = dp_level;
	edev->dp_module = dp_module;
	edev->ops->common->update_msglvl(edev->cdev,
					 dp_module, dp_level);
पूर्ण

अटल पूर्णांक qede_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output current_link;
	काष्ठा qed_link_params link_params;

	अगर (!edev->ops || !edev->ops->common->can_link_change(edev->cdev)) अणु
		DP_INFO(edev, "Link settings are not allowed to be changed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!netअगर_running(dev))
		वापस 0;

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);
	अगर (!current_link.link_up)
		वापस 0;

	/* Toggle the link */
	स_रखो(&link_params, 0, माप(link_params));
	link_params.link_up = false;
	edev->ops->common->set_link(edev->cdev, &link_params);
	link_params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &link_params);

	वापस 0;
पूर्ण

अटल u32 qede_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output current_link;

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	वापस current_link.link_up;
पूर्ण

अटल पूर्णांक qede_flash_device(काष्ठा net_device *dev,
			     काष्ठा ethtool_flash *flash)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	वापस edev->ops->common->nvm_flash(edev->cdev, flash->data);
पूर्ण

अटल पूर्णांक qede_get_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *coal)
अणु
	व्योम *rx_handle = शून्य, *tx_handle = शून्य;
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u16 rx_coal, tx_coal, i, rc = 0;
	काष्ठा qede_fastpath *fp;

	rx_coal = QED_DEFAULT_RX_USECS;
	tx_coal = QED_DEFAULT_TX_USECS;

	स_रखो(coal, 0, माप(काष्ठा ethtool_coalesce));

	__qede_lock(edev);
	अगर (edev->state == QEDE_STATE_OPEN) अणु
		क्रम_each_queue(i) अणु
			fp = &edev->fp_array[i];

			अगर (fp->type & QEDE_FASTPATH_RX) अणु
				rx_handle = fp->rxq->handle;
				अवरोध;
			पूर्ण
		पूर्ण

		rc = edev->ops->get_coalesce(edev->cdev, &rx_coal, rx_handle);
		अगर (rc) अणु
			DP_INFO(edev, "Read Rx coalesce error\n");
			जाओ out;
		पूर्ण

		क्रम_each_queue(i) अणु
			काष्ठा qede_tx_queue *txq;

			fp = &edev->fp_array[i];

			/* All TX queues of given fastpath uses same
			 * coalescing value, so no need to iterate over
			 * all TCs, TC0 txq should suffice.
			 */
			अगर (fp->type & QEDE_FASTPATH_TX) अणु
				txq = QEDE_FP_TC0_TXQ(fp);
				tx_handle = txq->handle;
				अवरोध;
			पूर्ण
		पूर्ण

		rc = edev->ops->get_coalesce(edev->cdev, &tx_coal, tx_handle);
		अगर (rc)
			DP_INFO(edev, "Read Tx coalesce error\n");
	पूर्ण

out:
	__qede_unlock(edev);

	coal->rx_coalesce_usecs = rx_coal;
	coal->tx_coalesce_usecs = tx_coal;

	वापस rc;
पूर्ण

पूर्णांक qede_set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_fastpath *fp;
	पूर्णांक i, rc = 0;
	u16 rxc, txc;

	अगर (!netअगर_running(dev)) अणु
		DP_INFO(edev, "Interface is down\n");
		वापस -EINVAL;
	पूर्ण

	अगर (coal->rx_coalesce_usecs > QED_COALESCE_MAX ||
	    coal->tx_coalesce_usecs > QED_COALESCE_MAX) अणु
		DP_INFO(edev,
			"Can't support requested %s coalesce value [max supported value %d]\n",
			coal->rx_coalesce_usecs > QED_COALESCE_MAX ? "rx" :
			"tx", QED_COALESCE_MAX);
		वापस -EINVAL;
	पूर्ण

	rxc = (u16)coal->rx_coalesce_usecs;
	txc = (u16)coal->tx_coalesce_usecs;
	क्रम_each_queue(i) अणु
		fp = &edev->fp_array[i];

		अगर (edev->fp_array[i].type & QEDE_FASTPATH_RX) अणु
			rc = edev->ops->common->set_coalesce(edev->cdev,
							     rxc, 0,
							     fp->rxq->handle);
			अगर (rc) अणु
				DP_INFO(edev,
					"Set RX coalesce error, rc = %d\n", rc);
				वापस rc;
			पूर्ण
			edev->coal_entry[i].rxc = rxc;
			edev->coal_entry[i].isvalid = true;
		पूर्ण

		अगर (edev->fp_array[i].type & QEDE_FASTPATH_TX) अणु
			काष्ठा qede_tx_queue *txq;

			/* All TX queues of given fastpath uses same
			 * coalescing value, so no need to iterate over
			 * all TCs, TC0 txq should suffice.
			 */
			txq = QEDE_FP_TC0_TXQ(fp);

			rc = edev->ops->common->set_coalesce(edev->cdev,
							     0, txc,
							     txq->handle);
			अगर (rc) अणु
				DP_INFO(edev,
					"Set TX coalesce error, rc = %d\n", rc);
				वापस rc;
			पूर्ण
			edev->coal_entry[i].txc = txc;
			edev->coal_entry[i].isvalid = true;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम qede_get_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	ering->rx_max_pending = NUM_RX_BDS_MAX;
	ering->rx_pending = edev->q_num_rx_buffers;
	ering->tx_max_pending = NUM_TX_BDS_MAX;
	ering->tx_pending = edev->q_num_tx_buffers;
पूर्ण

अटल पूर्णांक qede_set_ringparam(काष्ठा net_device *dev,
			      काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "Set ring params command parameters: rx_pending = %d, tx_pending = %d\n",
		   ering->rx_pending, ering->tx_pending);

	/* Validate legality of configuration */
	अगर (ering->rx_pending > NUM_RX_BDS_MAX ||
	    ering->rx_pending < NUM_RX_BDS_MIN ||
	    ering->tx_pending > NUM_TX_BDS_MAX ||
	    ering->tx_pending < NUM_TX_BDS_MIN) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "Can only support Rx Buffer size [0%08x,...,0x%08x] and Tx Buffer size [0x%08x,...,0x%08x]\n",
			   NUM_RX_BDS_MIN, NUM_RX_BDS_MAX,
			   NUM_TX_BDS_MIN, NUM_TX_BDS_MAX);
		वापस -EINVAL;
	पूर्ण

	/* Change ring size and re-load */
	edev->q_num_rx_buffers = ering->rx_pending;
	edev->q_num_tx_buffers = ering->tx_pending;

	qede_reload(edev, शून्य, false);

	वापस 0;
पूर्ण

अटल व्योम qede_get_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output current_link;

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	अगर (current_link.छोड़ो_config & QED_LINK_PAUSE_AUTONEG_ENABLE)
		eछोड़ो->स्वतःneg = true;
	अगर (current_link.छोड़ो_config & QED_LINK_PAUSE_RX_ENABLE)
		eछोड़ो->rx_छोड़ो = true;
	अगर (current_link.छोड़ो_config & QED_LINK_PAUSE_TX_ENABLE)
		eछोड़ो->tx_छोड़ो = true;

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "ethtool_pauseparam: cmd %d  autoneg %d  rx_pause %d  tx_pause %d\n",
		   eछोड़ो->cmd, eछोड़ो->स्वतःneg, eछोड़ो->rx_छोड़ो,
		   eछोड़ो->tx_छोड़ो);
पूर्ण

अटल पूर्णांक qede_set_छोड़ोparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_params params;
	काष्ठा qed_link_output current_link;

	अगर (!edev->ops || !edev->ops->common->can_link_change(edev->cdev)) अणु
		DP_INFO(edev,
			"Pause settings are not allowed to be changed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	स_रखो(&params, 0, माप(params));
	params.override_flags |= QED_LINK_OVERRIDE_PAUSE_CONFIG;

	अगर (eछोड़ो->स्वतःneg) अणु
		अगर (!phylink_test(current_link.supported_caps, Autoneg)) अणु
			DP_INFO(edev, "autoneg not supported\n");
			वापस -EINVAL;
		पूर्ण

		params.छोड़ो_config |= QED_LINK_PAUSE_AUTONEG_ENABLE;
	पूर्ण

	अगर (eछोड़ो->rx_छोड़ो)
		params.छोड़ो_config |= QED_LINK_PAUSE_RX_ENABLE;
	अगर (eछोड़ो->tx_छोड़ो)
		params.छोड़ो_config |= QED_LINK_PAUSE_TX_ENABLE;

	params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &params);

	वापस 0;
पूर्ण

अटल व्योम qede_get_regs(काष्ठा net_device *ndev,
			  काष्ठा ethtool_regs *regs, व्योम *buffer)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	regs->version = 0;
	स_रखो(buffer, 0, regs->len);

	अगर (edev->ops && edev->ops->common)
		edev->ops->common->dbg_all_data(edev->cdev, buffer);
पूर्ण

अटल पूर्णांक qede_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	अगर (edev->ops && edev->ops->common)
		वापस edev->ops->common->dbg_all_data_size(edev->cdev);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम qede_update_mtu(काष्ठा qede_dev *edev,
			    काष्ठा qede_reload_args *args)
अणु
	edev->ndev->mtu = args->u.mtu;
पूर्ण

/* Netdevice NDOs */
पूर्णांक qede_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	काष्ठा qede_reload_args args;

	DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "Configuring MTU size of %d\n", new_mtu);

	अगर (new_mtu > PAGE_SIZE)
		ndev->features &= ~NETIF_F_GRO_HW;

	/* Set the mtu field and re-start the पूर्णांकerface अगर needed */
	args.u.mtu = new_mtu;
	args.func = &qede_update_mtu;
	qede_reload(edev, &args, false);
#अगर IS_ENABLED(CONFIG_QED_RDMA)
	qede_rdma_event_change_mtu(edev);
#पूर्ण_अगर
	edev->ops->common->update_mtu(edev->cdev, new_mtu);

	वापस 0;
पूर्ण

अटल व्योम qede_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	channels->max_combined = QEDE_MAX_RSS_CNT(edev);
	channels->max_rx = QEDE_MAX_RSS_CNT(edev);
	channels->max_tx = QEDE_MAX_RSS_CNT(edev);
	channels->combined_count = QEDE_QUEUE_CNT(edev) - edev->fp_num_tx -
					edev->fp_num_rx;
	channels->tx_count = edev->fp_num_tx;
	channels->rx_count = edev->fp_num_rx;
पूर्ण

अटल पूर्णांक qede_set_channels(काष्ठा net_device *dev,
			     काष्ठा ethtool_channels *channels)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u32 count;

	DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "set-channels command parameters: rx = %d, tx = %d, other = %d, combined = %d\n",
		   channels->rx_count, channels->tx_count,
		   channels->other_count, channels->combined_count);

	count = channels->rx_count + channels->tx_count +
			channels->combined_count;

	/* We करोn't support `other' channels */
	अगर (channels->other_count) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "command parameters not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(channels->combined_count || (channels->rx_count &&
					   channels->tx_count))) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "need to request at least one transmit and one receive channel\n");
		वापस -EINVAL;
	पूर्ण

	अगर (count > QEDE_MAX_RSS_CNT(edev)) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "requested channels = %d max supported channels = %d\n",
			   count, QEDE_MAX_RSS_CNT(edev));
		वापस -EINVAL;
	पूर्ण

	/* Check अगर there was a change in the active parameters */
	अगर ((count == QEDE_QUEUE_CNT(edev)) &&
	    (channels->tx_count == edev->fp_num_tx) &&
	    (channels->rx_count == edev->fp_num_rx)) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "No change in active parameters\n");
		वापस 0;
	पूर्ण

	/* We need the number of queues to be भागisible between the hwfns */
	अगर ((count % edev->dev_info.common.num_hwfns) ||
	    (channels->tx_count % edev->dev_info.common.num_hwfns) ||
	    (channels->rx_count % edev->dev_info.common.num_hwfns)) अणु
		DP_VERBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "Number of channels must be divisible by %04x\n",
			   edev->dev_info.common.num_hwfns);
		वापस -EINVAL;
	पूर्ण

	/* Set number of queues and reload अगर necessary */
	edev->req_queues = count;
	edev->req_num_tx = channels->tx_count;
	edev->req_num_rx = channels->rx_count;
	/* Reset the indirection table अगर rx queue count is updated */
	अगर ((edev->req_queues - edev->req_num_tx) != QEDE_RSS_COUNT(edev)) अणु
		edev->rss_params_inited &= ~QEDE_RSS_INसूची_INITED;
		स_रखो(edev->rss_ind_table, 0, माप(edev->rss_ind_table));
	पूर्ण

	qede_reload(edev, शून्य, false);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_ts_info(काष्ठा net_device *dev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	वापस qede_ptp_get_ts_info(edev, info);
पूर्ण

अटल पूर्णांक qede_set_phys_id(काष्ठा net_device *dev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u8 led_state = 0;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		led_state = QED_LED_MODE_ON;
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		led_state = QED_LED_MODE_OFF;
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		led_state = QED_LED_MODE_RESTORE;
		अवरोध;
	पूर्ण

	edev->ops->common->set_led(edev->cdev, led_state);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_rss_flags(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *info)
अणु
	info->data = RXH_IP_SRC | RXH_IP_DST;

	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (edev->rss_caps & QED_RSS_IPV4_UDP)
			info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (edev->rss_caps & QED_RSS_IPV6_UDP)
			info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		अवरोध;
	शेष:
		info->data = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
			  u32 *rule_locs)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक rc = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = QEDE_RSS_COUNT(edev);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		rc = qede_get_rss_flags(edev, info);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		info->rule_cnt = qede_get_arfs_filter_count(edev);
		info->data = QEDE_RFS_MAX_FLTR;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		rc = qede_get_cls_rule_entry(edev, info);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		rc = qede_get_cls_rule_all(edev, info, rule_locs);
		अवरोध;
	शेष:
		DP_ERR(edev, "Command parameters not supported\n");
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qede_set_rss_flags(काष्ठा qede_dev *edev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा qed_update_vport_params *vport_update_params;
	u8 set_caps = 0, clr_caps = 0;
	पूर्णांक rc = 0;

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "Set rss flags command parameters: flow type = %d, data = %llu\n",
		   info->flow_type, info->data);

	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		/* For TCP only 4-tuple hash is supported */
		अगर (info->data ^ (RXH_IP_SRC | RXH_IP_DST |
				  RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
			DP_INFO(edev, "Command parameters not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	हाल UDP_V4_FLOW:
		/* For UDP either 2-tuple hash or 4-tuple hash is supported */
		अगर (info->data == (RXH_IP_SRC | RXH_IP_DST |
				   RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
			set_caps = QED_RSS_IPV4_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple enabled\n");
		पूर्ण अन्यथा अगर (info->data == (RXH_IP_SRC | RXH_IP_DST)) अणु
			clr_caps = QED_RSS_IPV4_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple disabled\n");
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल UDP_V6_FLOW:
		/* For UDP either 2-tuple hash or 4-tuple hash is supported */
		अगर (info->data == (RXH_IP_SRC | RXH_IP_DST |
				   RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
			set_caps = QED_RSS_IPV6_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple enabled\n");
		पूर्ण अन्यथा अगर (info->data == (RXH_IP_SRC | RXH_IP_DST)) अणु
			clr_caps = QED_RSS_IPV6_UDP;
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tuple disabled\n");
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		/* For IP only 2-tuple hash is supported */
		अगर (info->data ^ (RXH_IP_SRC | RXH_IP_DST)) अणु
			DP_INFO(edev, "Command parameters not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IP_USER_FLOW:
	हाल ETHER_FLOW:
		/* RSS is not supported क्रम these protocols */
		अगर (info->data) अणु
			DP_INFO(edev, "Command parameters not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* No action is needed अगर there is no change in the rss capability */
	अगर (edev->rss_caps == ((edev->rss_caps & ~clr_caps) | set_caps))
		वापस 0;

	/* Update पूर्णांकernal configuration */
	edev->rss_caps = ((edev->rss_caps & ~clr_caps) | set_caps);
	edev->rss_params_inited |= QEDE_RSS_CAPS_INITED;

	/* Re-configure अगर possible */
	__qede_lock(edev);
	अगर (edev->state == QEDE_STATE_OPEN) अणु
		vport_update_params = vzalloc(माप(*vport_update_params));
		अगर (!vport_update_params) अणु
			__qede_unlock(edev);
			वापस -ENOMEM;
		पूर्ण
		qede_fill_rss_params(edev, &vport_update_params->rss_params,
				     &vport_update_params->update_rss_flg);
		rc = edev->ops->vport_update(edev->cdev, vport_update_params);
		vमुक्त(vport_update_params);
	पूर्ण
	__qede_unlock(edev);

	वापस rc;
पूर्ण

अटल पूर्णांक qede_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक rc;

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXFH:
		rc = qede_set_rss_flags(edev, info);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		rc = qede_add_cls_rule(edev, info);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		rc = qede_delete_flow_filter(edev, info->fs.location);
		अवरोध;
	शेष:
		DP_INFO(edev, "Command parameters not supported\n");
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

अटल u32 qede_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	वापस QED_RSS_IND_TABLE_SIZE;
पूर्ण

अटल u32 qede_get_rxfh_key_size(काष्ठा net_device *dev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	वापस माप(edev->rss_key);
पूर्ण

अटल पूर्णांक qede_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key, u8 *hfunc)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (!indir)
		वापस 0;

	क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++)
		indir[i] = edev->rss_ind_table[i];

	अगर (key)
		स_नकल(key, edev->rss_key, qede_get_rxfh_key_size(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक qede_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा qed_update_vport_params *vport_update_params;
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक i, rc = 0;

	अगर (edev->dev_info.common.num_hwfns > 1) अणु
		DP_INFO(edev,
			"RSS configuration is not supported for 100G devices\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (!indir && !key)
		वापस 0;

	अगर (indir) अणु
		क्रम (i = 0; i < QED_RSS_IND_TABLE_SIZE; i++)
			edev->rss_ind_table[i] = indir[i];
		edev->rss_params_inited |= QEDE_RSS_INसूची_INITED;
	पूर्ण

	अगर (key) अणु
		स_नकल(&edev->rss_key, key, qede_get_rxfh_key_size(dev));
		edev->rss_params_inited |= QEDE_RSS_KEY_INITED;
	पूर्ण

	__qede_lock(edev);
	अगर (edev->state == QEDE_STATE_OPEN) अणु
		vport_update_params = vzalloc(माप(*vport_update_params));
		अगर (!vport_update_params) अणु
			__qede_unlock(edev);
			वापस -ENOMEM;
		पूर्ण
		qede_fill_rss_params(edev, &vport_update_params->rss_params,
				     &vport_update_params->update_rss_flg);
		rc = edev->ops->vport_update(edev->cdev, vport_update_params);
		vमुक्त(vport_update_params);
	पूर्ण
	__qede_unlock(edev);

	वापस rc;
पूर्ण

/* This function enables the पूर्णांकerrupt generation and the NAPI on the device */
अटल व्योम qede_netअगर_start(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	अगर (!netअगर_running(edev->ndev))
		वापस;

	क्रम_each_queue(i) अणु
		/* Update and reenable पूर्णांकerrupts */
		qed_sb_ack(edev->fp_array[i].sb_info, IGU_INT_ENABLE, 1);
		napi_enable(&edev->fp_array[i].napi);
	पूर्ण
पूर्ण

/* This function disables the NAPI and the पूर्णांकerrupt generation on the device */
अटल व्योम qede_netअगर_stop(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	क्रम_each_queue(i) अणु
		napi_disable(&edev->fp_array[i].napi);
		/* Disable पूर्णांकerrupts */
		qed_sb_ack(edev->fp_array[i].sb_info, IGU_INT_DISABLE, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक qede_selftest_transmit_traffic(काष्ठा qede_dev *edev,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा qede_tx_queue *txq = शून्य;
	काष्ठा eth_tx_1st_bd *first_bd;
	dma_addr_t mapping;
	पूर्णांक i, idx;
	u16 val;

	क्रम_each_queue(i) अणु
		काष्ठा qede_fastpath *fp = &edev->fp_array[i];

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			txq = QEDE_FP_TC0_TXQ(fp);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!txq) अणु
		DP_NOTICE(edev, "Tx path is not available\n");
		वापस -1;
	पूर्ण

	/* Fill the entry in the SW ring and the BDs in the FW ring */
	idx = txq->sw_tx_prod;
	txq->sw_tx_ring.skbs[idx].skb = skb;
	first_bd = qed_chain_produce(&txq->tx_pbl);
	स_रखो(first_bd, 0, माप(*first_bd));
	val = 1 << ETH_TX_1ST_BD_FLAGS_START_BD_SHIFT;
	first_bd->data.bd_flags.bitfields = val;
	val = skb->len & ETH_TX_DATA_1ST_BD_PKT_LEN_MASK;
	val = val << ETH_TX_DATA_1ST_BD_PKT_LEN_SHIFT;
	first_bd->data.bitfields |= cpu_to_le16(val);

	/* Map skb linear data क्रम DMA and set in the first BD */
	mapping = dma_map_single(&edev->pdev->dev, skb->data,
				 skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(&edev->pdev->dev, mapping))) अणु
		DP_NOTICE(edev, "SKB mapping failed\n");
		वापस -ENOMEM;
	पूर्ण
	BD_SET_UNMAP_ADDR_LEN(first_bd, mapping, skb_headlen(skb));

	/* update the first BD with the actual num BDs */
	first_bd->data.nbds = 1;
	txq->sw_tx_prod = (txq->sw_tx_prod + 1) % txq->num_tx_buffers;
	/* 'next page' entries are counted in the producer value */
	val = qed_chain_get_prod_idx(&txq->tx_pbl);
	txq->tx_db.data.bd_prod = cpu_to_le16(val);

	/* wmb makes sure that the BDs data is updated beक्रमe updating the
	 * producer, otherwise FW may पढ़ो old data from the BDs.
	 */
	wmb();
	barrier();
	ग_लिखोl(txq->tx_db.raw, txq->करोorbell_addr);

	क्रम (i = 0; i < QEDE_SELFTEST_POLL_COUNT; i++) अणु
		अगर (qede_txq_has_work(txq))
			अवरोध;
		usleep_range(100, 200);
	पूर्ण

	अगर (!qede_txq_has_work(txq)) अणु
		DP_NOTICE(edev, "Tx completion didn't happen\n");
		वापस -1;
	पूर्ण

	first_bd = (काष्ठा eth_tx_1st_bd *)qed_chain_consume(&txq->tx_pbl);
	dma_unmap_single(&edev->pdev->dev, BD_UNMAP_ADDR(first_bd),
			 BD_UNMAP_LEN(first_bd), DMA_TO_DEVICE);
	txq->sw_tx_cons = (txq->sw_tx_cons + 1) % txq->num_tx_buffers;
	txq->sw_tx_ring.skbs[idx].skb = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक qede_selftest_receive_traffic(काष्ठा qede_dev *edev)
अणु
	u16 sw_rx_index, len;
	काष्ठा eth_fast_path_rx_reg_cqe *fp_cqe;
	काष्ठा qede_rx_queue *rxq = शून्य;
	काष्ठा sw_rx_data *sw_rx_data;
	जोड़ eth_rx_cqe *cqe;
	पूर्णांक i, iter, rc = 0;
	u8 *data_ptr;

	क्रम_each_queue(i) अणु
		अगर (edev->fp_array[i].type & QEDE_FASTPATH_RX) अणु
			rxq = edev->fp_array[i].rxq;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rxq) अणु
		DP_NOTICE(edev, "Rx path is not available\n");
		वापस -1;
	पूर्ण

	/* The packet is expected to receive on rx-queue 0 even though RSS is
	 * enabled. This is because the queue 0 is configured as the शेष
	 * queue and that the loopback traffic is not IP.
	 */
	क्रम (iter = 0; iter < QEDE_SELFTEST_POLL_COUNT; iter++) अणु
		अगर (!qede_has_rx_work(rxq)) अणु
			usleep_range(100, 200);
			जारी;
		पूर्ण

		/* Get the CQE from the completion ring */
		cqe = (जोड़ eth_rx_cqe *)qed_chain_consume(&rxq->rx_comp_ring);

		/* Get the data from the SW ring */
		sw_rx_index = rxq->sw_rx_cons & NUM_RX_BDS_MAX;
		sw_rx_data = &rxq->sw_rx_ring[sw_rx_index];
		fp_cqe = &cqe->fast_path_regular;
		len =  le16_to_cpu(fp_cqe->len_on_first_bd);
		data_ptr = (u8 *)(page_address(sw_rx_data->data) +
				  fp_cqe->placement_offset +
				  sw_rx_data->page_offset +
				  rxq->rx_headroom);
		अगर (ether_addr_equal(data_ptr,  edev->ndev->dev_addr) &&
		    ether_addr_equal(data_ptr + ETH_ALEN,
				     edev->ndev->dev_addr)) अणु
			क्रम (i = ETH_HLEN; i < len; i++)
				अगर (data_ptr[i] != (अचिन्हित अक्षर)(i & 0xff)) अणु
					rc = -1;
					अवरोध;
				पूर्ण

			qede_recycle_rx_bd_ring(rxq, 1);
			qed_chain_recycle_consumed(&rxq->rx_comp_ring);
			अवरोध;
		पूर्ण

		DP_INFO(edev, "Not the transmitted packet\n");
		qede_recycle_rx_bd_ring(rxq, 1);
		qed_chain_recycle_consumed(&rxq->rx_comp_ring);
	पूर्ण

	अगर (iter == QEDE_SELFTEST_POLL_COUNT) अणु
		DP_NOTICE(edev, "Failed to receive the traffic\n");
		वापस -1;
	पूर्ण

	qede_update_rx_prod(edev, rxq);

	वापस rc;
पूर्ण

अटल पूर्णांक qede_selftest_run_loopback(काष्ठा qede_dev *edev, u32 loopback_mode)
अणु
	काष्ठा qed_link_params link_params;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक rc = 0, i;
	u32 pkt_size;
	u8 *packet;

	अगर (!netअगर_running(edev->ndev)) अणु
		DP_NOTICE(edev, "Interface is down\n");
		वापस -EINVAL;
	पूर्ण

	qede_netअगर_stop(edev);

	/* Bring up the link in Loopback mode */
	स_रखो(&link_params, 0, माप(link_params));
	link_params.link_up = true;
	link_params.override_flags = QED_LINK_OVERRIDE_LOOPBACK_MODE;
	link_params.loopback_mode = loopback_mode;
	edev->ops->common->set_link(edev->cdev, &link_params);

	/* Wait क्रम loopback configuration to apply */
	msleep_पूर्णांकerruptible(500);

	/* Setting max packet size to 1.5K to aव्योम data being split over
	 * multiple BDs in हालs where MTU > PAGE_SIZE.
	 */
	pkt_size = (((edev->ndev->mtu < ETH_DATA_LEN) ?
		     edev->ndev->mtu : ETH_DATA_LEN) + ETH_HLEN);

	skb = netdev_alloc_skb(edev->ndev, pkt_size);
	अगर (!skb) अणु
		DP_INFO(edev, "Can't allocate skb\n");
		rc = -ENOMEM;
		जाओ test_loopback_निकास;
	पूर्ण
	packet = skb_put(skb, pkt_size);
	ether_addr_copy(packet, edev->ndev->dev_addr);
	ether_addr_copy(packet + ETH_ALEN, edev->ndev->dev_addr);
	स_रखो(packet + (2 * ETH_ALEN), 0x77, (ETH_HLEN - (2 * ETH_ALEN)));
	क्रम (i = ETH_HLEN; i < pkt_size; i++)
		packet[i] = (अचिन्हित अक्षर)(i & 0xff);

	rc = qede_selftest_transmit_traffic(edev, skb);
	अगर (rc)
		जाओ test_loopback_निकास;

	rc = qede_selftest_receive_traffic(edev);
	अगर (rc)
		जाओ test_loopback_निकास;

	DP_VERBOSE(edev, NETIF_MSG_RX_STATUS, "Loopback test successful\n");

test_loopback_निकास:
	dev_kमुक्त_skb(skb);

	/* Bring up the link in Normal mode */
	स_रखो(&link_params, 0, माप(link_params));
	link_params.link_up = true;
	link_params.override_flags = QED_LINK_OVERRIDE_LOOPBACK_MODE;
	link_params.loopback_mode = QED_LINK_LOOPBACK_NONE;
	edev->ops->common->set_link(edev->cdev, &link_params);

	/* Wait क्रम loopback configuration to apply */
	msleep_पूर्णांकerruptible(500);

	qede_netअगर_start(edev);

	वापस rc;
पूर्ण

अटल व्योम qede_self_test(काष्ठा net_device *dev,
			   काष्ठा ethtool_test *etest, u64 *buf)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "Self-test command parameters: offline = %d, external_lb = %d\n",
		   (etest->flags & ETH_TEST_FL_OFFLINE),
		   (etest->flags & ETH_TEST_FL_EXTERNAL_LB) >> 2);

	स_रखो(buf, 0, माप(u64) * QEDE_ETHTOOL_TEST_MAX);

	अगर (etest->flags & ETH_TEST_FL_OFFLINE) अणु
		अगर (qede_selftest_run_loopback(edev,
					       QED_LINK_LOOPBACK_INT_PHY)) अणु
			buf[QEDE_ETHTOOL_INT_LOOPBACK] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण
	पूर्ण

	अगर (edev->ops->common->selftest->selftest_पूर्णांकerrupt(edev->cdev)) अणु
		buf[QEDE_ETHTOOL_INTERRUPT_TEST] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (edev->ops->common->selftest->selftest_memory(edev->cdev)) अणु
		buf[QEDE_ETHTOOL_MEMORY_TEST] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (edev->ops->common->selftest->selftest_रेजिस्टर(edev->cdev)) अणु
		buf[QEDE_ETHTOOL_REGISTER_TEST] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (edev->ops->common->selftest->selftest_घड़ी(edev->cdev)) अणु
		buf[QEDE_ETHTOOL_CLOCK_TEST] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (edev->ops->common->selftest->selftest_nvram(edev->cdev)) अणु
		buf[QEDE_ETHTOOL_NVRAM_TEST] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
पूर्ण

अटल पूर्णांक qede_set_tunable(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_tunable *tuna,
			    स्थिर व्योम *data)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u32 val;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		val = *(u32 *)data;
		अगर (val < QEDE_MIN_PKT_LEN || val > QEDE_RX_HDR_SIZE) अणु
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "Invalid rx copy break value, range is [%u, %u]",
				   QEDE_MIN_PKT_LEN, QEDE_RX_HDR_SIZE);
			वापस -EINVAL;
		पूर्ण

		edev->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_tunable(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = edev->rx_copyअवरोध;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output current_link;

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	अगर (!current_link.eee_supported) अणु
		DP_INFO(edev, "EEE is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (current_link.eee.adv_caps & QED_EEE_1G_ADV)
		edata->advertised = ADVERTISED_1000baseT_Full;
	अगर (current_link.eee.adv_caps & QED_EEE_10G_ADV)
		edata->advertised |= ADVERTISED_10000baseT_Full;
	अगर (current_link.sup_caps & QED_EEE_1G_ADV)
		edata->supported = ADVERTISED_1000baseT_Full;
	अगर (current_link.sup_caps & QED_EEE_10G_ADV)
		edata->supported |= ADVERTISED_10000baseT_Full;
	अगर (current_link.eee.lp_adv_caps & QED_EEE_1G_ADV)
		edata->lp_advertised = ADVERTISED_1000baseT_Full;
	अगर (current_link.eee.lp_adv_caps & QED_EEE_10G_ADV)
		edata->lp_advertised |= ADVERTISED_10000baseT_Full;

	edata->tx_lpi_समयr = current_link.eee.tx_lpi_समयr;
	edata->eee_enabled = current_link.eee.enable;
	edata->tx_lpi_enabled = current_link.eee.tx_lpi_enable;
	edata->eee_active = current_link.eee_active;

	वापस 0;
पूर्ण

अटल पूर्णांक qede_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output current_link;
	काष्ठा qed_link_params params;

	अगर (!edev->ops->common->can_link_change(edev->cdev)) अणु
		DP_INFO(edev, "Link settings are not allowed to be changed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&current_link, 0, माप(current_link));
	edev->ops->common->get_link(edev->cdev, &current_link);

	अगर (!current_link.eee_supported) अणु
		DP_INFO(edev, "EEE is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.override_flags |= QED_LINK_OVERRIDE_EEE_CONFIG;

	अगर (!(edata->advertised & (ADVERTISED_1000baseT_Full |
				   ADVERTISED_10000baseT_Full)) ||
	    ((edata->advertised & (ADVERTISED_1000baseT_Full |
				   ADVERTISED_10000baseT_Full)) !=
	     edata->advertised)) अणु
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "Invalid advertised capabilities %d\n",
			   edata->advertised);
		वापस -EINVAL;
	पूर्ण

	अगर (edata->advertised & ADVERTISED_1000baseT_Full)
		params.eee.adv_caps = QED_EEE_1G_ADV;
	अगर (edata->advertised & ADVERTISED_10000baseT_Full)
		params.eee.adv_caps |= QED_EEE_10G_ADV;
	params.eee.enable = edata->eee_enabled;
	params.eee.tx_lpi_enable = edata->tx_lpi_enabled;
	params.eee.tx_lpi_समयr = edata->tx_lpi_समयr;

	params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &params);

	वापस 0;
पूर्ण

अटल u32 qede_link_to_ethtool_fec(u32 link_fec)
अणु
	u32 eth_fec = 0;

	अगर (link_fec & QED_FEC_MODE_NONE)
		eth_fec |= ETHTOOL_FEC_OFF;
	अगर (link_fec & QED_FEC_MODE_FIRECODE)
		eth_fec |= ETHTOOL_FEC_BASER;
	अगर (link_fec & QED_FEC_MODE_RS)
		eth_fec |= ETHTOOL_FEC_RS;
	अगर (link_fec & QED_FEC_MODE_AUTO)
		eth_fec |= ETHTOOL_FEC_AUTO;
	अगर (link_fec & QED_FEC_MODE_UNSUPPORTED)
		eth_fec |= ETHTOOL_FEC_NONE;

	वापस eth_fec;
पूर्ण

अटल u32 qede_ethtool_to_link_fec(u32 eth_fec)
अणु
	u32 link_fec = 0;

	अगर (eth_fec & ETHTOOL_FEC_OFF)
		link_fec |= QED_FEC_MODE_NONE;
	अगर (eth_fec & ETHTOOL_FEC_BASER)
		link_fec |= QED_FEC_MODE_FIRECODE;
	अगर (eth_fec & ETHTOOL_FEC_RS)
		link_fec |= QED_FEC_MODE_RS;
	अगर (eth_fec & ETHTOOL_FEC_AUTO)
		link_fec |= QED_FEC_MODE_AUTO;
	अगर (eth_fec & ETHTOOL_FEC_NONE)
		link_fec |= QED_FEC_MODE_UNSUPPORTED;

	वापस link_fec;
पूर्ण

अटल पूर्णांक qede_get_fecparam(काष्ठा net_device *dev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_output curr_link;

	स_रखो(&curr_link, 0, माप(curr_link));
	edev->ops->common->get_link(edev->cdev, &curr_link);

	fecparam->active_fec = qede_link_to_ethtool_fec(curr_link.active_fec);
	fecparam->fec = qede_link_to_ethtool_fec(curr_link.sup_fec);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_set_fecparam(काष्ठा net_device *dev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qed_link_params params;

	अगर (!edev->ops || !edev->ops->common->can_link_change(edev->cdev)) अणु
		DP_INFO(edev, "Link settings are not allowed to be changed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.override_flags |= QED_LINK_OVERRIDE_FEC_CONFIG;
	params.fec = qede_ethtool_to_link_fec(fecparam->fec);
	params.link_up = true;

	edev->ops->common->set_link(edev->cdev, &params);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_module_info(काष्ठा net_device *dev,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u8 buf[4];
	पूर्णांक rc;

	/* Read first 4 bytes to find the sfp type */
	rc = edev->ops->common->पढ़ो_module_eeprom(edev->cdev, buf,
						   QED_I2C_DEV_ADDR_A0, 0, 4);
	अगर (rc) अणु
		DP_ERR(edev, "Failed reading EEPROM data %d\n", rc);
		वापस rc;
	पूर्ण

	चयन (buf[0]) अणु
	हाल 0x3: /* SFP, SFP+, SFP-28 */
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अवरोध;
	हाल 0xc: /* QSFP */
	हाल 0xd: /* QSFP+ */
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		अवरोध;
	हाल 0x11: /* QSFP-28 */
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		अवरोध;
	शेष:
		DP_ERR(edev, "Unknown transceiver type 0x%x\n", buf[0]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_module_eeprom(काष्ठा net_device *dev,
				  काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	u32 start_addr = ee->offset, size = 0;
	u8 *buf = data;
	पूर्णांक rc = 0;

	/* Read A0 section */
	अगर (ee->offset < ETH_MODULE_SFF_8079_LEN) अणु
		/* Limit transfer size to the A0 section boundary */
		अगर (ee->offset + ee->len > ETH_MODULE_SFF_8079_LEN)
			size = ETH_MODULE_SFF_8079_LEN - ee->offset;
		अन्यथा
			size = ee->len;

		rc = edev->ops->common->पढ़ो_module_eeprom(edev->cdev, buf,
							   QED_I2C_DEV_ADDR_A0,
							   start_addr, size);
		अगर (rc) अणु
			DP_ERR(edev, "Failed reading A0 section  %d\n", rc);
			वापस rc;
		पूर्ण

		buf += size;
		start_addr += size;
	पूर्ण

	/* Read A2 section */
	अगर (start_addr >= ETH_MODULE_SFF_8079_LEN &&
	    start_addr < ETH_MODULE_SFF_8472_LEN) अणु
		size = ee->len - size;
		/* Limit transfer size to the A2 section boundary */
		अगर (start_addr + size > ETH_MODULE_SFF_8472_LEN)
			size = ETH_MODULE_SFF_8472_LEN - start_addr;
		start_addr -= ETH_MODULE_SFF_8079_LEN;
		rc = edev->ops->common->पढ़ो_module_eeprom(edev->cdev, buf,
							   QED_I2C_DEV_ADDR_A2,
							   start_addr, size);
		अगर (rc) अणु
			DP_VERBOSE(edev, QED_MSG_DEBUG,
				   "Failed reading A2 section %d\n", rc);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qede_set_dump(काष्ठा net_device *dev, काष्ठा ethtool_dump *val)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक rc = 0;

	अगर (edev->dump_info.cmd == QEDE_DUMP_CMD_NONE) अणु
		अगर (val->flag > QEDE_DUMP_CMD_MAX) अणु
			DP_ERR(edev, "Invalid command %d\n", val->flag);
			वापस -EINVAL;
		पूर्ण
		edev->dump_info.cmd = val->flag;
		edev->dump_info.num_args = 0;
		वापस 0;
	पूर्ण

	अगर (edev->dump_info.num_args == QEDE_DUMP_MAX_ARGS) अणु
		DP_ERR(edev, "Arg count = %d\n", edev->dump_info.num_args);
		वापस -EINVAL;
	पूर्ण

	चयन (edev->dump_info.cmd) अणु
	हाल QEDE_DUMP_CMD_NVM_CFG:
		edev->dump_info.args[edev->dump_info.num_args] = val->flag;
		edev->dump_info.num_args++;
		अवरोध;
	हाल QEDE_DUMP_CMD_GRCDUMP:
		rc = edev->ops->common->set_grc_config(edev->cdev,
						       val->flag, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qede_get_dump_flag(काष्ठा net_device *dev,
			      काष्ठा ethtool_dump *dump)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!edev->ops || !edev->ops->common) अणु
		DP_ERR(edev, "Edev ops not populated\n");
		वापस -EINVAL;
	पूर्ण

	dump->version = QEDE_DUMP_VERSION;
	चयन (edev->dump_info.cmd) अणु
	हाल QEDE_DUMP_CMD_NVM_CFG:
		dump->flag = QEDE_DUMP_CMD_NVM_CFG;
		dump->len = edev->ops->common->पढ़ो_nvm_cfg_len(edev->cdev,
						edev->dump_info.args[0]);
		अवरोध;
	हाल QEDE_DUMP_CMD_GRCDUMP:
		dump->flag = QEDE_DUMP_CMD_GRCDUMP;
		dump->len = edev->ops->common->dbg_all_data_size(edev->cdev);
		अवरोध;
	शेष:
		DP_ERR(edev, "Invalid cmd = %d\n", edev->dump_info.cmd);
		वापस -EINVAL;
	पूर्ण

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "dump->version = 0x%x dump->flag = %d dump->len = %d\n",
		   dump->version, dump->flag, dump->len);
	वापस 0;
पूर्ण

अटल पूर्णांक qede_get_dump_data(काष्ठा net_device *dev,
			      काष्ठा ethtool_dump *dump, व्योम *buf)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक rc = 0;

	अगर (!edev->ops || !edev->ops->common) अणु
		DP_ERR(edev, "Edev ops not populated\n");
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	चयन (edev->dump_info.cmd) अणु
	हाल QEDE_DUMP_CMD_NVM_CFG:
		अगर (edev->dump_info.num_args != QEDE_DUMP_NVM_ARG_COUNT) अणु
			DP_ERR(edev, "Arg count = %d required = %d\n",
			       edev->dump_info.num_args,
			       QEDE_DUMP_NVM_ARG_COUNT);
			rc = -EINVAL;
			जाओ err;
		पूर्ण
		rc =  edev->ops->common->पढ़ो_nvm_cfg(edev->cdev, (u8 **)&buf,
						      edev->dump_info.args[0],
						      edev->dump_info.args[1]);
		अवरोध;
	हाल QEDE_DUMP_CMD_GRCDUMP:
		स_रखो(buf, 0, dump->len);
		rc = edev->ops->common->dbg_all_data(edev->cdev, buf);
		अवरोध;
	शेष:
		DP_ERR(edev, "Invalid cmd = %d\n", edev->dump_info.cmd);
		rc = -EINVAL;
		अवरोध;
	पूर्ण

err:
	edev->dump_info.cmd = QEDE_DUMP_CMD_NONE;
	edev->dump_info.num_args = 0;
	स_रखो(edev->dump_info.args, 0, माप(edev->dump_info.args));

	वापस rc;
पूर्ण

पूर्णांक qede_set_per_coalesce(काष्ठा net_device *dev, u32 queue,
			  काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_fastpath *fp;
	u16 rxc, txc;
	पूर्णांक rc = 0;

	अगर (coal->rx_coalesce_usecs > QED_COALESCE_MAX ||
	    coal->tx_coalesce_usecs > QED_COALESCE_MAX) अणु
		DP_INFO(edev,
			"Can't support requested %s coalesce value [max supported value %d]\n",
			coal->rx_coalesce_usecs > QED_COALESCE_MAX ? "rx"
								   : "tx",
			QED_COALESCE_MAX);
		वापस -EINVAL;
	पूर्ण

	rxc = (u16)coal->rx_coalesce_usecs;
	txc = (u16)coal->tx_coalesce_usecs;

	__qede_lock(edev);
	अगर (queue >= edev->num_queues) अणु
		DP_INFO(edev, "Invalid queue\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (edev->state != QEDE_STATE_OPEN) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	fp = &edev->fp_array[queue];

	अगर (edev->fp_array[queue].type & QEDE_FASTPATH_RX) अणु
		rc = edev->ops->common->set_coalesce(edev->cdev,
						     rxc, 0,
						     fp->rxq->handle);
		अगर (rc) अणु
			DP_INFO(edev,
				"Set RX coalesce error, rc = %d\n", rc);
			जाओ out;
		पूर्ण
		edev->coal_entry[queue].rxc = rxc;
		edev->coal_entry[queue].isvalid = true;
	पूर्ण

	अगर (edev->fp_array[queue].type & QEDE_FASTPATH_TX) अणु
		rc = edev->ops->common->set_coalesce(edev->cdev,
						     0, txc,
						     fp->txq->handle);
		अगर (rc) अणु
			DP_INFO(edev,
				"Set TX coalesce error, rc = %d\n", rc);
			जाओ out;
		पूर्ण
		edev->coal_entry[queue].txc = txc;
		edev->coal_entry[queue].isvalid = true;
	पूर्ण
out:
	__qede_unlock(edev);

	वापस rc;
पूर्ण

अटल पूर्णांक qede_get_per_coalesce(काष्ठा net_device *dev,
				 u32 queue,
				 काष्ठा ethtool_coalesce *coal)
अणु
	व्योम *rx_handle = शून्य, *tx_handle = शून्य;
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_fastpath *fp;
	u16 rx_coal, tx_coal;
	पूर्णांक rc = 0;

	rx_coal = QED_DEFAULT_RX_USECS;
	tx_coal = QED_DEFAULT_TX_USECS;

	स_रखो(coal, 0, माप(काष्ठा ethtool_coalesce));

	__qede_lock(edev);
	अगर (queue >= edev->num_queues) अणु
		DP_INFO(edev, "Invalid queue\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (edev->state != QEDE_STATE_OPEN) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	fp = &edev->fp_array[queue];

	अगर (fp->type & QEDE_FASTPATH_RX)
		rx_handle = fp->rxq->handle;

	rc = edev->ops->get_coalesce(edev->cdev, &rx_coal,
				     rx_handle);
	अगर (rc) अणु
		DP_INFO(edev, "Read Rx coalesce error\n");
		जाओ out;
	पूर्ण

	fp = &edev->fp_array[queue];
	अगर (fp->type & QEDE_FASTPATH_TX)
		tx_handle = fp->txq->handle;

	rc = edev->ops->get_coalesce(edev->cdev, &tx_coal,
				      tx_handle);
	अगर (rc)
		DP_INFO(edev, "Read Tx coalesce error\n");

out:
	__qede_unlock(edev);

	coal->rx_coalesce_usecs = rx_coal;
	coal->tx_coalesce_usecs = tx_coal;

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops qede_ethtool_ops = अणु
	.supported_coalesce_params	= ETHTOOL_COALESCE_USECS,
	.get_link_ksettings		= qede_get_link_ksettings,
	.set_link_ksettings		= qede_set_link_ksettings,
	.get_drvinfo			= qede_get_drvinfo,
	.get_regs_len			= qede_get_regs_len,
	.get_regs			= qede_get_regs,
	.get_wol			= qede_get_wol,
	.set_wol			= qede_set_wol,
	.get_msglevel			= qede_get_msglevel,
	.set_msglevel			= qede_set_msglevel,
	.nway_reset			= qede_nway_reset,
	.get_link			= qede_get_link,
	.get_coalesce			= qede_get_coalesce,
	.set_coalesce			= qede_set_coalesce,
	.get_ringparam			= qede_get_ringparam,
	.set_ringparam			= qede_set_ringparam,
	.get_छोड़ोparam			= qede_get_छोड़ोparam,
	.set_छोड़ोparam			= qede_set_छोड़ोparam,
	.get_strings			= qede_get_strings,
	.set_phys_id			= qede_set_phys_id,
	.get_ethtool_stats		= qede_get_ethtool_stats,
	.get_priv_flags			= qede_get_priv_flags,
	.set_priv_flags			= qede_set_priv_flags,
	.get_sset_count			= qede_get_sset_count,
	.get_rxnfc			= qede_get_rxnfc,
	.set_rxnfc			= qede_set_rxnfc,
	.get_rxfh_indir_size		= qede_get_rxfh_indir_size,
	.get_rxfh_key_size		= qede_get_rxfh_key_size,
	.get_rxfh			= qede_get_rxfh,
	.set_rxfh			= qede_set_rxfh,
	.get_ts_info			= qede_get_ts_info,
	.get_channels			= qede_get_channels,
	.set_channels			= qede_set_channels,
	.self_test			= qede_self_test,
	.get_module_info		= qede_get_module_info,
	.get_module_eeprom		= qede_get_module_eeprom,
	.get_eee			= qede_get_eee,
	.set_eee			= qede_set_eee,
	.get_fecparam			= qede_get_fecparam,
	.set_fecparam			= qede_set_fecparam,
	.get_tunable			= qede_get_tunable,
	.set_tunable			= qede_set_tunable,
	.get_per_queue_coalesce		= qede_get_per_coalesce,
	.set_per_queue_coalesce		= qede_set_per_coalesce,
	.flash_device			= qede_flash_device,
	.get_dump_flag			= qede_get_dump_flag,
	.get_dump_data			= qede_get_dump_data,
	.set_dump			= qede_set_dump,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops qede_vf_ethtool_ops = अणु
	.supported_coalesce_params	= ETHTOOL_COALESCE_USECS,
	.get_link_ksettings		= qede_get_link_ksettings,
	.get_drvinfo			= qede_get_drvinfo,
	.get_msglevel			= qede_get_msglevel,
	.set_msglevel			= qede_set_msglevel,
	.get_link			= qede_get_link,
	.get_coalesce			= qede_get_coalesce,
	.set_coalesce			= qede_set_coalesce,
	.get_ringparam			= qede_get_ringparam,
	.set_ringparam			= qede_set_ringparam,
	.get_strings			= qede_get_strings,
	.get_ethtool_stats		= qede_get_ethtool_stats,
	.get_priv_flags			= qede_get_priv_flags,
	.get_sset_count			= qede_get_sset_count,
	.get_rxnfc			= qede_get_rxnfc,
	.set_rxnfc			= qede_set_rxnfc,
	.get_rxfh_indir_size		= qede_get_rxfh_indir_size,
	.get_rxfh_key_size		= qede_get_rxfh_key_size,
	.get_rxfh			= qede_get_rxfh,
	.set_rxfh			= qede_set_rxfh,
	.get_channels			= qede_get_channels,
	.set_channels			= qede_set_channels,
	.get_per_queue_coalesce		= qede_get_per_coalesce,
	.set_per_queue_coalesce		= qede_set_per_coalesce,
	.get_tunable			= qede_get_tunable,
	.set_tunable			= qede_set_tunable,
पूर्ण;

व्योम qede_set_ethtool_ops(काष्ठा net_device *dev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (IS_VF(edev))
		dev->ethtool_ops = &qede_vf_ethtool_ops;
	अन्यथा
		dev->ethtool_ops = &qede_ethtool_ops;
पूर्ण
